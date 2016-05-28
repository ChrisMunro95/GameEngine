#pragma once

#include "Vector2D.h"
#include "HAPI\HAPI_lib.h"
#include "CRectangle.h"

class Entity
{
public:
	Entity() = default;
	Entity(int GFX_ID);
	virtual ~Entity();

	virtual void update() = 0;
	//virtual void render() = 0;

	int getGFX_ID() const { return GFX_ID_; };

	void setPosition(int x, int y);
	Vector2D getPosition(){ return position_; };

	void setAliveFlag(bool isAlive);
	bool isAlive() const { return aliveFlag_; };
	
	void setMaxFrames(int maxX, int maxY);
	void setFrames(int frameX, int frameY);
	int getFrameX() { return frameX_; };
	int getFrameY() { return frameY_; };

	void setBoundingRect(int width, int height);
	CRectangle getBoundingRect() { return rect_; };

	void addHealth(int value);
	void subtractHealth(int value);
	int getHealth(){ return health_; };

	void checkForCollision(Vector2D entityPos, const CRectangle &entityRect,
						   DWORD *entityColMask, int entityNumDwordsAcross,
						   Vector2D otherEntityPos, const CRectangle &otherEntityRect,
						   DWORD *otherEntityColMask, int otherEntityNumDwordsAcross,
						   bool &rectColDetected, bool &pixelColDetected);

private:
	
	int GFX_ID_{ 0 };
	Vector2D position_{-100, -100};

	bool aliveFlag_{ false };
	int health_{ 0 };

	int numberOfFrames_{ 0 };
	int frameX_{ 0 };
	int frameY_{ 0 };

	int maxFrameX_{ 0 };
	int maxFrameY_{ 0 };

	CRectangle rect_{0, 0, 0, 0};
};

