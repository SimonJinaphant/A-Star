#pragma once
#include <iostream>
#include <ostream>

struct Tile{
	const unsigned int x, y;

	double g, h, cost;
	Tile* parent;

	bool isClose;
	bool isOpen;


	Tile();
	Tile(unsigned int x, unsigned int y, double cost);
	Tile(const Tile &copyTile);
	void info();

	struct Compare{
		//To be used with the make_heap(), push_heap(), and pop_heap() functions
		bool operator()(const Tile* left, const Tile* right) const {
			//Returns the tile with the lowest movement cost and heuristic
			return (left->g + left->h) < (right->g + right->h);
		}
	};

};
