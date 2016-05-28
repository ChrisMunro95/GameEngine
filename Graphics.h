#pragma once

#include <HAPI_lib.h>
#include <vector>
#include "CRectangle.h"
#include "Vector2D.h"

class Sprite;

namespace GameGraphics{

	class Graphics
	{
	public:
		Graphics();
		~Graphics();

		void createWindow(int width, int height);

		void clearToBlack();
		void clearToWhite();
		void clearToScreen(HAPI_TColour colour);
		void clearToPixel(int xPos, int yPos, HAPI_TColour colour);

		bool createSprite(const std::string& filename, int ID, int frameWidth,
			int frameHeight, int numXframes, int numYframes);

		DWORD *getSpriteColMask(int ID, int spriteWidth, int spriteHeight,
						        int numDwordsAcross);

		void renderSprite(int ID, Vector2D position, int frameXNumber,
			int frameYNumber);
		void renderBG(int ID, int posX, int posY, bool scrolling);

		const int getScreenWidth();
		const int getScreenHeight();

	private:
		int screenWidth_;
		int screenHeight_;

		BYTE *screen_{ nullptr };

		std::vector<Sprite *> sprites_;

	};

}

