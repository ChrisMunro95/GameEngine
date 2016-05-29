#pragma once

#include "Vector2D.h"

class Tile
{
public:
	Tile(Vector2D position, int xFrame, int yFrame);
	~Tile();

	Vector2D getPosition() const { return position_; };

private:
	int xFrame_ = 0;
	int yFrame_ = 0;

	Vector2D position_{0, 0};

};

