#include "PlayerEntity.h"
#include "Graphics.h"
#include "HAPI_lib.h"

PlayerEntity::PlayerEntity(int GFX_ID, int maxFramesX, int maxFramesY) : GFX_ID_(GFX_ID)
{
	//graphics_ = new GameGraphics::Graphics();
	setMaxFrames(maxFramesX, maxFramesY);
}


PlayerEntity::~PlayerEntity()
{
	//delete graphics_;
}

void PlayerEntity::update()
{
	//check for key input to move the texture and change blit type/add textures
	HAPI->GetKeyboardData(&keyData);

	//int controllerCount = HAPI->GetMaxControllers();

	position_ = getPosition();

	DWORD timeNow = HAPI->GetTime();
	if (timeNow - tickTimeCheck_ > tickInterval_){

		tickTimeCheck_ = timeNow;

		if (isAlive() != false){

			if (getHealth() <= 0){
				setAliveFlag(false);
				endLifeTime = timeNow;
			}
			if (getHealth() >= maxHealth){
				health_ = maxHealth;
			}

			Vector2D endPos(0, 0);
			Vector2D direction(0, 0);
			Vector2D movement(0, 0);

			//checks for keyboard input
			if (keyData.scanCode[HK_DOWN] || keyData.scanCode['S']){
				frameX++;
				frameY = 0;
				endPos.y = getPosition().y + 80;
				endPos.x = getPosition().x;

				direction = endPos - getPosition();
				direction.NormaliseInPlace();

				movement = position_ + direction * moveSpeed_;
				position_.y = movement.y;
			}
			if (keyData.scanCode[HK_UP] || keyData.scanCode['W']){
				frameX = 0;
				frameY = 3;

				endPos.y = getPosition().y - 80;
				endPos.x = getPosition().x;

				direction = endPos - getPosition();
				direction.NormaliseInPlace();

				movement = position_ + direction * moveSpeed_;
				position_.y = movement.y;

				frameX++;
			}
			if (keyData.scanCode[HK_RIGHT] || keyData.scanCode['D']){
				frameX = 0;
				frameY = 2;

				endPos.y = getPosition().y;
				endPos.x = getPosition().x + 80;

				direction = endPos - getPosition();
				direction.NormaliseInPlace();

				movement = position_ + direction * moveSpeed_;
				position_.x = movement.x;

				frameX++;
			}
			if (keyData.scanCode[HK_LEFT] || keyData.scanCode['A']){
				frameX = 0;
				frameY = 1;

				endPos.y = getPosition().y;
				endPos.x = getPosition().x - 80;

				direction = endPos - getPosition();
				direction.NormaliseInPlace();

				movement = position_ + direction * moveSpeed_;
				position_.x = movement.x;
				
				frameX++;
			}
			HAPI->RenderText(450, 100, (255), "FrameX: " + std::to_string(frameX));

			setPosition((int)position_.x, (int)position_.y);
			setFrames(frameX, frameY);
		}
	}


}

/* 
############################################################# 
The code below was the start of adding a render function to the entity.
However it resulted in an Invisible / No sprite Render 
Due to time constraints I couldnt find a solution
#############################################################
*/

//void PlayerEntity::render()
//{
//	if (isAlive()){
//		HAPI->RenderText(0, 460, (255, 255, 255), "RENDERING: " + std::to_string(GFX_ID_));
//		graphics_->renderSprite(GFX_ID_, getPosition(), getFrameX(), getFrameY());
//	}
//}
//
//void PlayerEntity::makeSprite(std::string filename, int ID, int frameW, int frameH, int numXframes, int numYframes)
//{
//	GFX_ID_ = ID;
//	graphics_->createSprite(filename, ID, frameW, frameH, numXframes, numYframes);
//}
//
//DWORD *PlayerEntity::getColMask()
//{
//	int NumDwordsAcross = 0;
//	return graphics_->getSpriteColMask(GFX_ID_, 64, 64, NumDwordsAcross);
//}
