#pragma once

#include "Entity.h"
namespace GameGraphics{ class Graphics; };

class PlayerEntity : public Entity
{
public:
	PlayerEntity(int GFX_ID, int maxFramesX, int maxFramesY);
	~PlayerEntity();

	void update() override;

	//void render();
	//void makeSprite(std::string filename, int ID, int frameW, int frameH, int numXframes, int numYframes);
	//DWORD *getColMask();

	std::string getLifeTime() const;

	void fire();
	bool canFire() const { return canFire_; };

private:

	int GFX_ID_{10};

	int health_{0};
	const int maxHealth = 200;

	//std::string filename_;
	//GameGraphics::Graphics *graphics_{ nullptr };

	float fireCooldown{ 1.5f };
	bool canFire_{ false };

	const DWORD startLifeTime = 0;
	DWORD endLifeTime;

	DWORD lastTimeCheck = 0;
	DWORD timeInterval = 300;

	DWORD tickTimeCheck_ = 0;
	DWORD tickInterval_ = 10;

	DWORD padTimeCheck_ = 0;
	DWORD padTickInterval_ = 100;
	 
	Vector2D position_{0, 0};

	float moveSpeed_{ 10 };
	
	int frameX = 0;
	int frameY = 0;

	CRectangle rect_{ 0, 0, 0, 0 };

	HAPI_TKeyboardData keyData;
	HAPI_TControllerData padData;

	//int controllerCount = -1;

};

