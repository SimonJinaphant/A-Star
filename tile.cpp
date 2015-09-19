#include "tile.h"


Tile::Tile(unsigned int x, unsigned int y, double cost) : 
	x(x), 
	y(y)
{

	this->cost = cost;
	this->g = 0;
	this->h = 0;

	this->isClose = false;
	this->isOpen = false;

	this->parent = 0;
}

Tile::Tile(const Tile &copy) : 
	x(copy.x),
	y(copy.y)
{
	this->cost = copy.cost;
	this->h = copy.h;
	this->g = copy.g;

	this->isClose = copy.isClose;
	this->isOpen = copy.isOpen;
	
	//Shallow copy
	this->parent = copy.parent;
}


void Tile::info(){
	printf("[(%u, %u) C: %lf    H: %lf   G: %lf\n", 
		this->x, this->y, this->cost, this->h, this->g
	);
}