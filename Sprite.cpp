#include "Sprite.h"

#if defined(DEBUG) | defined(_DEBUG)
#include<crtdbg.h>
#define new new(_NORMAL_BLOCK,__FILE__,__LINE__)
#endif

//Loads a Sprite into memory
Sprite::Sprite()
{

}

Sprite::~Sprite()
{
	delete[] sprite_;
	delete mask_;
}

bool Sprite::loadSprite(std::string spriteName, int frameWidth, int frameHeight, int numXframes, int numYframes)
{
	if (!HAPI->LoadTexture(spriteName, &sprite_, &spriteWidth_, &spriteHeight_)){
		HAPI->UserMessage("Cannot Load Sprite: " + spriteName, "ERROR: ");
		return false;
	}
	else{
		frameWidth_ = frameWidth;
		frameHeight_ = frameHeight;
		numXframes_ = numXframes;
		numYframes_ = numYframes;
		return true;
	}
}

int Sprite::getSpriteWidth() const
{
	return spriteWidth_;
}

int Sprite::getSpriteHeight() const
{
	return spriteHeight_;
}

//Blits A Sprite ignoring all Alpha Values
void Sprite::blitSpriteBG(bool scrolling, BYTE *destPnter, int destWidth, BYTE* sourcePnter, int posX, int posY)
{
	int sourceWidth = spriteWidth_;
	int sourceHeight = spriteHeight_;

	if (scrolling){

		CRectangle scrollRect(0, spriteHeight_, 0, spriteWidth_);
		CRectangle screenRect(0, spriteHeight_, 0, spriteWidth_);

		//clip the rectangle
		scrollRect.translate(posX, posY);
		scrollRect.ClipTo(screenRect);
		scrollRect.translate(-posX, -posY);

		if (posX < 0)
			posX = 0;
		if (posY < 0)
			posY = 0;

		destPnter += (posX + posY * screenRect.getWidth()) * 4;
		sourcePnter = sprite_ + (scrollRect.left + scrollRect.top * spriteWidth_) * 4;

		int offset = (sourceWidth - scrollRect.getWidth()) * 4;
		int sourceOffest = (spriteWidth_ - scrollRect.getWidth()) * 4;

		for (int y = 0; y < sourceHeight; y++){

			memcpy(destPnter, sourcePnter, scrollRect.getWidth() * 4);

			sourcePnter += (spriteWidth_ * 4);
			destPnter += destWidth * 4;
		}

	}
	else{

		destPnter += (posX + posY * destWidth) * 4;
		sourcePnter = sprite_;

		for (int y = 0; y < sourceHeight; y++){
			memcpy(destPnter, sourcePnter, sourceWidth * 4);

			sourcePnter += sourceWidth * 4;
			destPnter += destWidth * 4;
		}

	}

}

//Blits A Sprite with Alpha Values
void Sprite::blitSprite(BYTE *destPnter, BYTE* sourcePnter, const CRectangle &destRect,
						int frameXpos, int frameYPos, int posX, int posY)
{
	CRectangle clippedRect(0, frameHeight_, 0, frameWidth_);

	//clip the rectangle
	clippedRect.translate(posX, posY);
	clippedRect.ClipTo(destRect);
	clippedRect.translate(-posX, -posY);

	if (posX < 0)
		posX = 0;
	if (posY < 0)
		posY = 0;

	//translate the clipped rect to the correct frame
	clippedRect.translate(frameXpos * frameWidth_, frameYPos * frameHeight_);

	//blit the image
	destPnter += (posX + posY * destRect.getWidth()) * 4;
	sourcePnter = sprite_ + (clippedRect.left + clippedRect.top * spriteWidth_) * 4;

	int sourceOffset = (spriteWidth_ - clippedRect.getWidth()) * 4;

	for (int y = 0; y < clippedRect.getHeight(); y++){
		memcpy(destPnter, sourcePnter, clippedRect.getWidth() * 4);

		sourcePnter += sourceOffset + clippedRect.getWidth() * 4;
		destPnter += destRect.getWidth() * 4;
	}

}

void Sprite::clipBlit(BYTE *destPnter, const CRectangle &destRect, BYTE* sourcePnter,
					  int frameXpos, int frameYPos, int posX, int posY)
{
	CRectangle clippedRect(0, frameHeight_, 0, frameWidth_);

	//clip the rectangle
	clippedRect.translate(posX, posY);
	clippedRect.ClipTo(destRect);
	clippedRect.translate(-posX, -posY);

	if (posX < 0)
		posX = 0;
	if (posY < 0)
		posY = 0;

/*	//clamp the frames to their max i.e they cant go over the total number
	//of frames
	if (frameXpos >= numXframes_)
		frameXpos = numXframes_;

	if (frameYPos >= numYframes_)
		frameYPos = numYframes_;
*/
	//translate the clipped rect to the correct frame
	clippedRect.translate(frameXpos * frameWidth_, frameYPos * frameHeight_);

	//blit the image
	destPnter += (posX + posY * destRect.getWidth()) * 4;
	sourcePnter = sprite_ + (clippedRect.left + clippedRect.top * spriteWidth_) * 4;

	int offset = (destRect.getWidth() - clippedRect.getWidth()) * 4;
	int sourceOffest = (spriteWidth_ - clippedRect.getWidth()) * 4;

	for (int y = 0; y < clippedRect.getHeight(); y++){
		for (int x = 0; x < clippedRect.getWidth(); x++){

			BYTE alpha = sourcePnter[3];

			if (alpha > 255){
				memcpy(destPnter, sourcePnter, clippedRect.getWidth() * 4);
			}
			else{
				BYTE blue = sourcePnter[0];
				BYTE green = sourcePnter[1];
				BYTE red = sourcePnter[2];

				destPnter[0] = destPnter[0] + ((alpha *(blue - destPnter[0])) >> 8);
				destPnter[1] = destPnter[1] + ((alpha *(green - destPnter[1])) >> 8);
				destPnter[2] = destPnter[2] + ((alpha *(red - destPnter[2])) >> 8);
			}
			destPnter += 4;
			sourcePnter += 4;
		}

		sourcePnter += sourceOffest;
		destPnter += offset;

	}
}

DWORD* Sprite::createCollisionMask(const CRectangle& rect,
	int &numDwordsAcross)
{
	//calculate how many DWORD across is needed
	numDwordsAcross = (rect.getWidth() + 31) / 32;

	//allocate memory for the mask
	mask_ = new DWORD[numDwordsAcross * rect.getHeight()];
	memset(mask_, 0, numDwordsAcross * rect.getHeight() * 4);

	BYTE *srcPnter = sprite_;
	DWORD *maskPnter = mask_;
	DWORD currentBit = 0;

	for (int y = 0; y < rect.getHeight(); y++){
		for (int x = 0; x < rect.getWidth(); x++){

			BYTE alpha = srcPnter[3];

			//each pixel is represented as a bit, 1 for solid and 0 for empty
			//so when alpha is 255 its solid, so we make a bit
			if (alpha == 255){
				*maskPnter = *maskPnter | (1 << currentBit);
			}

			srcPnter += 4;
			currentBit++;

			//when current bit is 32, move onto the next DWORD
			if (currentBit == 32){
				currentBit = 0;
				maskPnter++;
			}

		}
	}
	return mask_;
}


