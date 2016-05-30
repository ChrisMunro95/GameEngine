#include "MapLoader.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include "Graphics.h"
#include "Tile.h"
#include <string>

MapLoader::MapLoader()
{
	graphics_ = new GameGraphics::Graphics();
}


MapLoader::~MapLoader()
{
	delete graphics_;
}

bool MapLoader::loadMap(std::string filepath)
{
	try{
		std::ifstream mapFile;
		mapFile.open(filepath);

		if (!mapFile.good()){
			return false;
		}
		else{

			for (unsigned int y = 0; y < 23; y++){
				std::string line;

				std::getline(mapFile, line);

				int value = -1;
				char a;

				std::stringstream ss(line);

				while (ss >> value){

					mapData_.push_back(value);

					if (ss.peek() == ',' || ss.peek() == ' ')
						ss.ignore();
				}
			}

		}
		return true;
	}
	catch (...){
		std::cerr << "Failed to LoadMap" << std::endl;
		return false;
	}

	indexToFrameNo();
}

void MapLoader::drawMap()
{


}

void MapLoader::indexToFrameNo()
{
	int indexNo = 0;
	Frame thisFrame;

	for (unsigned int y = 0; y < 19; y++){
		for (unsigned int x = 0; x < 9; x++){

			thisFrame.yFrame = y;
			thisFrame.xFrame = x;

			std::pair<int, Frame> valueToAdd(indexNo, thisFrame);

			indexedFrames_.insert(valueToAdd);

			indexNo++;
		}
	}
}

Frame MapLoader::getIndexedFrame(int index)
{
	indexToFrameNo();

	std::unordered_map<int, Frame>::const_iterator got = indexedFrames_.find(index);
	if (index == -1){
		Frame newFrame;
		newFrame.xFrame = 0;
		newFrame.yFrame = 0;
		return newFrame;
	}
	else{
		if (got == indexedFrames_.end()){
			//nothing
		}
		else{
			Frame newFrame = got->second;
			return newFrame;
		}
	}
}
