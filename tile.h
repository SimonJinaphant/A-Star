#pragma once
#include <iostream>

struct Tile{
	const unsigned int x, y;

	/*	A tile/node in A* keeps track of 4 important information

		G - Keeps track of the cost accumulated so far from the starting point
		
		H - An estimation -doesn't have to be 100% accurate- of how much it 
			would cost to move from here to the goal point.

		Cost - The cost to move to this tile: If the cost is PF_INFINITY then it is
				considered a wall/obsticle.

		Parent - A way to keep track of the path back to the starting point.
				(Think of Linked-List keepng pointers to find the next Node)
	*/
	double g, h, cost;
	Tile* parent;
	
	/*
		The following two booleans are for making this A* implementation simple,
		other implementations of A* will vary.

		isClose - A boolean flag to indicate whether this tile is currently inside the
				CLOSED list, once a tile is inside it should never be removed from this list.
				This prevents A* from analysising the same tile over and over again.

		isOpen - A boolean flag to indicate whether this tile is currently inside the
				OPEN list. Tiles can freely be inserted and removed from this list.
	*/
	bool isClose;
	bool isOpen;


	Tile();
	Tile(unsigned int x, unsigned int y, double cost);
	Tile(const Tile &copyTile);
	void info();

	struct Compare{
		//To be used with the make_heap(), push_heap(), and pop_heap() functions
		bool operator()(const Tile* left, const Tile* right) const {
			//Returns the tile with the lowest g and h value
			return (left->g + left->h) > (right->g + right->h);
		}
	};

};
