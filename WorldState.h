#pragma once
#include <iostream>

namespace GameGraphics{ class Graphics; };
class PlayerEntity;

class WorldState
{
public:
	WorldState();
	~WorldState();

	bool createWorld();
	void updateWorld();

private:

	GameGraphics::Graphics *graphics_{ nullptr };

	PlayerEntity *player_{ nullptr };
};

