#pragma once

#include <iostream>
#include <unordered_map>

class Tile;
namespace GameGraphics{ class Graphics; };

struct Frame{
	int xFrame;
	int yFrame;
};

class MapLoader
{
public:
	MapLoader();
	~MapLoader();

	void indexToFrameNo();

	bool loadMap(std::string filepath);
	void drawMap();

	std::vector<int> getMapData() const { return mapData_; };

	Frame getIndexedFrame(int index);

private:

	GameGraphics::Graphics *graphics_{ nullptr };

	std::vector<int> mapData_;

	std::unordered_map<int, Frame> indexedFrames_;

};

