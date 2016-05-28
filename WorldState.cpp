#include <HAPI_lib.h>

#include "WorldState.h"
#include <cstdlib>

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
}


bool WorldState::createWorld()
{
	try{
		graphics_ = new GameGraphics::Graphics();
		graphics_->createWindow(1080, 720);

		graphics_->createSprite("Resources/SpriteSheet.png", 0, 32, 32, 3, 4);

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
	while (HAPI->Update()){

		graphics_->clearToBlack();
		player_->setAliveFlag(true);
		graphics_->renderSprite(0, player_->getPosition(), player_->getFrameX(), player_->getFrameY());

		player_->update();
	}
}
