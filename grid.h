#pragma once
#include "tile.h"
#include <vector>
#include <algorithm>
#include <cmath>

#define PF_INFINITY INT_MAX
#define SQRT2 1.4142135623

class Grid{
private:
	std::vector<Tile> gridmap;
	std::vector<Tile*> path;

	Tile* start;
	Tile* goal;

	void calculateHeuristics(Tile*& tile);
	double calculateCost(Tile*& tileA, Tile*& tileB);


	bool withinMap(unsigned int x, unsigned int y);
	Tile* getTileAt(unsigned int x, unsigned int y);

	double length, width;

public:
	Grid(unsigned int length, unsigned int width);

	void printPath();
	void generatePath();
	void updateCost(unsigned int x, unsigned int y, double cost);
};