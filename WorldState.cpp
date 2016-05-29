#include <HAPI_lib.h>

#include "WorldState.h"
#include <cstdlib>

#include "Tile.h"

#include "Entity.h"
#include "PlayerEntity.h"

#include "Graphics.h"
#include "CRectangle.h"
#include "Vector2D.h"

#include <iostream>

#if defined(DEBUG) | defined(_DEBUG)
#include<crtdbg.h>
#define new new(_NORMAL_BLOCK,__FILE__,__LINE__)
#endif

WorldState::WorldState()
{

}


WorldState::~WorldState()
{
	delete graphics_;
	delete player_;

	for (unsigned int i = 0; i < tiles.size(); i++){
		delete tiles[i];
	}
}


bool WorldState::createWorld()
{
	try{
		graphics_ = new GameGraphics::Graphics();
		graphics_->createWindow(1080, 720);

		graphics_->createSprite("Resources/TileSet.png", 0, 32, 32, 0, 0);
		graphics_->createSprite("Resources/SpriteSheet.png", 1, 32, 32, 3, 4);

		float xPos = 0;
		float yPos = 0;

		for (unsigned int i = 0; i < 23; i++){
			for (unsigned int j = 0; j < 34; j++){

				Tile *tile = new Tile(Vector2D(xPos, yPos), 0, 0);

				tiles.push_back(tile);

				xPos += 32;
			}
			xPos = 0;
			yPos += 32;

		}

		player_ = new PlayerEntity(1, 3, 4);
		player_->setAliveFlag(true);
		player_->setPosition(540, 360);
		player_->setBoundingRect(32, 32);

		return true;
	}
	catch (...){
		std::cerr << "Failed to Create Game World" << std::endl;
		return false;
	}
}

void WorldState::updateWorld()
{

	float xPos = 0;

	while (HAPI->Update()){

		for (auto tile : tiles){
			graphics_->renderFastSprite(0, tile->getPosition(), 0, 1);
		}

		player_->setAliveFlag(true);
		graphics_->renderSprite(1, player_->getPosition(), player_->getFrameX(), player_->getFrameY());

		player_->update();
	}
}
