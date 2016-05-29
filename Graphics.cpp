#include "Graphics.h"
#include "Sprite.h"

GameGraphics::Graphics::Graphics()
{
}

GameGraphics::Graphics::~Graphics()
{
	for (unsigned int i = 0; i < sprites_.size(); i++)
		delete sprites_[i];
}

//intialises HAPI/Creates a window;
void GameGraphics::Graphics::createWindow(int width, int height)
{
	screenWidth_ = width;
	screenHeight_ = height;

	if (!HAPI->Initialise(&screenWidth_, &screenHeight_)){
		HAPI->UserMessage("Cannot Initialise HAPI ", "ERROR: ");
		return;
	}

	screen_ = HAPI->GetScreenPointer();

}

const int GameGraphics::Graphics::getScreenWidth()
{
	return screenWidth_;
}

const int GameGraphics::Graphics::getScreenHeight()
{
	return screenHeight_;
}

//clears the screen to black
void GameGraphics::Graphics::clearToBlack()
{
	memset(screen_, 0, screenWidth_ * screenHeight_ * 4);
}

//clears the screen to White
void GameGraphics::Graphics::clearToWhite()
{
	memset(screen_, 255, screenWidth_ * screenHeight_ * 4);
}

//clears the screen colour to any specified arbitrary colour; 
void GameGraphics::Graphics::clearToScreen(HAPI_TColour colour)
{
	int width = getScreenWidth();
	int height = getScreenHeight();

	BYTE *temp = screen_;
	for (int i = 0; i < width * height; i++, temp += 4){
		memcpy(temp, &colour, 4);
	}

}

//clears the a pixel on the screen to any specified arbitrary colour and location; 
void GameGraphics::Graphics::clearToPixel(int xPos, int yPos, HAPI_TColour colour)
{
	BYTE* temp = screen_;
	int offset = (xPos + yPos * screenWidth_) * 4;
	memcpy(temp + offset, &colour, 4);
}

bool GameGraphics::Graphics::createSprite(const std::string& filename, int ID, int frameWidth, int frameHeight, 
										  int numXframes, int numYframes)
{
	Sprite *newSprite = new Sprite;

	if (!newSprite->loadSprite(filename, frameWidth, frameHeight, numXframes, numYframes))
	{
		delete[] newSprite;
		return false;
	}
 
	ID = sprites_.size();

	sprites_.push_back(newSprite);
	return true;

}

DWORD* GameGraphics::Graphics::getSpriteColMask(int ID, int spriteWidth, int spriteHeight, int numDwordsAcross)
{
	CRectangle tempRect(0, spriteHeight, 0, spriteWidth);
	return sprites_[ID]->createCollisionMask(tempRect, numDwordsAcross);
}

void GameGraphics::Graphics::renderSprite(int ID, Vector2D position, int frameXNumber, int frameYNumber)
						
{
	CRectangle screenRect(0, screenHeight_, 0, screenWidth_);
	//BYTE *tempScreen = screen_;
	//BYTE *tempSource = nullptr;
	sprites_[ID]->clipBlit(screen_, screenRect, nullptr, frameXNumber, frameYNumber, (int)position.x, (int)position.y);
}

void GameGraphics::Graphics::renderFastSprite(int ID, Vector2D position, int frameXNumber, int frameYNumber)
{
	CRectangle screenRect(0, screenHeight_, 0, screenWidth_);
	BYTE *tempSource = nullptr;
	sprites_[ID]->blitSprite(screen_, nullptr, screenRect, frameXNumber, frameYNumber, position.x, position.y);
}

void GameGraphics::Graphics::renderBG(int ID, int posX, int posY, bool scrolling)
{
	BYTE *tempScreen = screen_;
	BYTE *tempSource = nullptr;
	sprites_[ID]->blitSpriteBG(scrolling, tempScreen, screenWidth_, tempSource, posX, posY);
}
