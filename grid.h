#pragma once
#include "tile.h"
#include <vector>
#include <algorithm>
#include <cmath>

//PF_INFINITY denotes a cost which is an obsticle tile.
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
	

	//Estimate -doesn't have to be 100% accurate- the total cost to move the goal tile, 
	//starting at the current input tile.
	void calculateHeuristics(Tile*& tile);

	//Calculates the cost to move between two adjacent tiles.
	double calculateCost(Tile*& tileA, Tile*& tileB) const;

	//Determines if a certain tile is inside the map.
	bool withinMap(unsigned int x, unsigned int y) const;

	//Gives a pointer to the tile at (x, y), provided that it exist in the map.
	Tile* getTileAt(unsigned int x, unsigned int y);

public:
	Grid(unsigned int length, unsigned int width);

	//The main part of the code for A* Pathfinding.
	void computeShortestPath();

	//If you want to change a tile's cost manually. NOTE: Only do this BEFORE
	//running computeShortestPath() as A* is a static pathfinder.
	void updateCost(unsigned int x, unsigned int y, double cost);
};