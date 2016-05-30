#pragma once
#include <iostream>
#include <Vector>

namespace GameGraphics{ class Graphics; };
class PlayerEntity;
class Tile;
class MapLoader;

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

	MapLoader *mapLoader_{nullptr};
	std::vector<Tile*> tiles;
	std::vector<int> mapData_;
};

