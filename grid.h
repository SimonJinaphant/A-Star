#pragma once
#include "tile.h"
#include <vector>
#include <algorithm>
#include <cmath>

//PF_INFINITY is used to denote an obsticle cost
#define PF_INFINITY INT_MAX
#define STANDARD_COST 10.0
#define SQRT2 1.4142135623


class Grid{
private:
	/*
		Gridmap - Contains the Tile as a 2D grid via a 1D array: given a pair of (x, y)
				coordinates the corresponding index is f(x, y) = y * width + x
	*/
	std::vector<Tile> gridmap;

	Tile* start;
	Tile* goal;
	double length, width;
	
	void calculateHeuristics(Tile*& tile);
	double calculateCost(Tile*& tileA, Tile*& tileB);

	bool withinMap(unsigned int x, unsigned int y);
	Tile* getTileAt(unsigned int x, unsigned int y);

public:
	Grid(unsigned int length, unsigned int width);

	void computeShortestPath();
	void updateCost(unsigned int x, unsigned int y, double cost);
};