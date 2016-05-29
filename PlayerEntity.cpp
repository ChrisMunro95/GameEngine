#include "PlayerEntity.h"
#include "Graphics.h"
#include "HAPI_lib.h"

PlayerEntity::PlayerEntity(int GFX_ID, int maxFramesX, int maxFramesY) : GFX_ID_(GFX_ID), maxFrameX_(maxFramesX), maxFrameY_(maxFramesY)
{
	//graphics_ = new GameGraphics::Graphics();
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
				frameY = 0;

				//advance the frame using time ticks
				if (timeNow - frameTimeCheck_ > frameTickInterval_){

					frameTimeCheck_ = timeNow;
					frameX++;
				}
				
				//Constrain the frames
				if (frameX > maxFrameX_){
					frameX = 0;
				}

				endPos.y = getPosition().y + 32;
				endPos.x = getPosition().x;

				direction = endPos - getPosition();
				direction.NormaliseInPlace();

				movement = position_ + direction * moveSpeed_;
				position_.y = movement.y;
			}
			if (keyData.scanCode[HK_UP] || keyData.scanCode['W']){

				frameY = 3;

				//advance the frame using time ticks
				if (timeNow - frameTimeCheck_ > frameTickInterval_){

					frameTimeCheck_ = timeNow;
					frameX++;
				}

				//Constrain the frames
				if (frameX > maxFrameX_){
					frameX = 0;
				}

				endPos.y = getPosition().y - 32;
				endPos.x = getPosition().x;

				direction = endPos - getPosition();
				direction.NormaliseInPlace();

				movement = position_ + direction * moveSpeed_;
				position_.y = movement.y;
			}
			if (keyData.scanCode[HK_RIGHT] || keyData.scanCode['D']){

				frameY = 2;

				//advance the frame using time ticks
				if (timeNow - frameTimeCheck_ > frameTickInterval_){

					frameTimeCheck_ = timeNow;
					frameX++;
				}

				//Constrain the frames
				if (frameX > maxFrameX_){
					frameX = 0;
				}

				endPos.y = getPosition().y;
				endPos.x = getPosition().x + 32;

				direction = endPos - getPosition();
				direction.NormaliseInPlace();

				movement = position_ + direction * moveSpeed_;
				position_.x = movement.x;
			}
			if (keyData.scanCode[HK_LEFT] || keyData.scanCode['A']){
				
				frameY = 1;

				//advance the frame using time ticks
				if (timeNow - frameTimeCheck_ > frameTickInterval_){

					frameTimeCheck_ = timeNow;
					frameX++;
				}

				//Constrain the frames
				if (frameX > maxFrameX_){
					frameX = 0;
				}

				endPos.y = getPosition().y;
				endPos.x = getPosition().x - 32;

				direction = endPos - getPosition();
				direction.NormaliseInPlace();

				movement = position_ + direction * moveSpeed_;
				position_.x = movement.x;
			}
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
