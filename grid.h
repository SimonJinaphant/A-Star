#ifndef __ASTAR_GRID___
#define __ASTAR_GRID___

#include "tile.h"
#include <vector>
#include <algorithm>
#include <cmath>

class Grid{
private:
	std::vector< std::vector<Tile> > gridWorld_;
	std::vector<Tile*> path;

	Tile* start_;
	Tile* goal_;

	void calculateHeuristics(Tile*& tile);
	
	bool withinMap(unsigned int x, unsigned int y);
	
	Tile* getTileAt(unsigned int x, unsigned int y);

public:
	Grid(unsigned int xSize, unsigned int ySize);
	virtual ~Grid();

	void printPath();
	void generatePath();
	void toggleWall(unsigned int x, unsigned int y);
};

#endif