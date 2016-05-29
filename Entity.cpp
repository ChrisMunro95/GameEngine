#include "Entity.h"

Entity::Entity(int GFX_ID) : GFX_ID_(GFX_ID)
{
}


Entity::~Entity()
{
}

void Entity::setAliveFlag(bool isAlive)
{
	aliveFlag_ = isAlive;
}

void Entity::setPosition(int x, int y)
{
	position_.x = (float)x;
	position_.y = (float)y;
}

void Entity::setMaxFrames(int maxX, int maxY)
{
	maxFrameX_ = maxX;
	maxFrameY_ = maxY;
}

void Entity::setFrames(int frameX, int frameY)
{
	frameX_ = frameX;
	frameY_ = frameY;
}

void Entity::setBoundingRect(int width, int height)
{
	rect_.left = 0;
	rect_.right = width - 10;
	rect_.top = 0;
	rect_.bottom = height - 10;
}

void Entity::addHealth(int value)
{
	//sanity check that the value passed in isnt a negative
	if (value <= 0)
		health_ = health_;
	else
		health_ += value;
}

void Entity::subtractHealth(int value)
{
	//sanity check that the value passed in isnt a negative
	if (value <= 0)
		health_ = health_;
	else
		health_ -= value;
}


void Entity::checkForCollision(Vector2D entityPos, const CRectangle &entityRect,
					   DWORD *entityColMask, int entityNumDwordsAcross,
					   Vector2D otherEntityPos, const CRectangle &otherEntityRect,
					   DWORD *otherEntityColMask, int otherEntityNumDwordsAcross,
					   bool &rectColDetected, bool &pixelColDetected)
{
	rectColDetected = false;
	pixelColDetected = false;

	//translate the rectangles to screen space
	CRectangle screenSpaceEntity(entityRect);
	screenSpaceEntity.translate((int)entityPos.x, (int)entityPos.y);

	CRectangle screenSpaceOtherEntity(otherEntityRect);
	screenSpaceOtherEntity.translate((int)otherEntityPos.x, (int)otherEntityPos.y);

	//now check for rectangle collsion, exists if there is no rect collision
	if (!screenSpaceEntity.intersects(screenSpaceOtherEntity))
		return;

	rectColDetected = true;

	//now start pixel perfect collision

	//find the collision area between the two entitys
	CRectangle entityColRect(screenSpaceEntity);
	entityColRect.ClipTo(screenSpaceOtherEntity);
	entityColRect.translate((int)-entityPos.x, (int)-entityPos.y);

	CRectangle otherEntityColRect(screenSpaceOtherEntity);
	otherEntityColRect.ClipTo(screenSpaceEntity);
	otherEntityColRect.translate((int)-otherEntityPos.x, (int)-otherEntityPos.y);

	for (int y = 0; y < entityColRect.getHeight(); y++){

		//work out the starting DWORD and bit offset for the entity
		int entityMaskOffset = entityColRect.left / 32;
		int entityMaskBitOffset = entityColRect.left % 32;
		DWORD *entityMaskHere = entityColMask + entityMaskOffset + ((entityColRect.top + y) 
								* entityNumDwordsAcross);

		//work out the starting DWORD and bit offset for the OTHER entity
		int otherEntityMaskOffset = otherEntityColRect.left / 32;
		int otherEntityMaskBitOffset = otherEntityColRect.left % 32;
		DWORD *otherEntityMaskHere = otherEntityColMask + otherEntityMaskOffset + ((otherEntityColRect.top + y)
								     * otherEntityNumDwordsAcross);

		for (int x = 0; x < entityColRect.getWidth(); x++){

			//Bit test alone
			bool entityBitHere = (*entityMaskHere & (1 << entityMaskBitOffset)) > 0;
			bool otherEntityBitHere = (*otherEntityMaskHere & (1 << otherEntityMaskBitOffset)) > 0;

			// if boths bits in question are 1's there's a collsion
			if (entityBitHere && otherEntityBitHere){
				pixelColDetected = true;
				return;
			}

			//advance through the masks bit by bit
			//move onto next DWORD
			entityMaskBitOffset++;
			if (entityMaskBitOffset == 32){
				entityMaskBitOffset = 0;
				entityMaskHere++;
			}

			otherEntityMaskBitOffset++;
			if (otherEntityMaskOffset == 32){
				otherEntityMaskBitOffset = 0;
				otherEntityMaskHere++;
			}

		}
	}

}
