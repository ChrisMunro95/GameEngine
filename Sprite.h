#pragma once

#include <iostream>
#include <HAPI_lib.h>
#include "CRectangle.h"

class Sprite 
{
public:
	Sprite();
	
	~Sprite();

	bool loadSprite(std::string spriteName, int frameWidth, int frameHeight, 
					int numXframes, int numYframes);

	void blitSprite(bool scrolling, BYTE *destPnter, int destWidth, BYTE* sourcePnter,
		int posX, int posY);
	void blitAlphaSprite(BYTE *destPnter, int destWidth,
		BYTE* sourcePnter, int posX, int posY);

	void clipBlit(BYTE *destPnter, const CRectangle &destRect,
				  BYTE *sourcePnter, int frameNumber,
				  int frameYPos, int posX, int posY);

	DWORD *createCollisionMask(const CRectangle& rect, int &numDwordsAcross);

	int getSpriteWidth() const;
	int getSpriteHeight() const;

private:
	int spriteWidth_;
	int spriteHeight_;

	int frameWidth_;
	int frameHeight_;

	int numXframes_;
	int numYframes_;

	BYTE *sprite_{ nullptr };
	DWORD *mask_{ nullptr };
};

