#ifndef __ASTAR_TILE__
#define __ASTAR_TILE__

#include <iostream>
#include <ostream>

class Tile{
private:
	unsigned int x_, y_;

	bool isWall_;	//Determines if a tile can be walked on or not;
	Tile* parent_;	//Allows a tile to be back-traced to the starting tile

	/*
		In the original algorithm, we have a CLOSED and OPEN list,
		Every time we analyse a TILE we needed to determine if that
		TILE is already in the CLOSED or OPEN list.

		Since membership lookup can be expensive in some data structure,
		we can imitate all of this by implementing two boolean field values
		which tell if a TILE is "inside" the CLOSED or OPEN list

		isClosed_ - Tells if a TILE is "in" the CLOSED list
		isOpened_ - Tells if a TILE is "in" the OPEN list
	*/
	bool isClosed_;
	bool isOpened_;
	

public:
	unsigned int movementCost;	//Holds the sum of movement cost from START to the current Tile
	double heuristic;			//Holds an estimated sum of movement cost from the current Tile to FINISH
	
	Tile();
	Tile(unsigned int x, unsigned int y, bool isWall);
	Tile(const Tile &copyTile);

	unsigned int getX();
	unsigned int getY();

	friend std::ostream& operator<<(std::ostream& out, Tile*& tile);
	friend std::ostream& operator<<(std::ostream& out, Tile& tile);


	bool isWall();
	bool isClosed();
	bool isOpened();

	void open();
	void close();
	void toggleWall();
	void setParent(Tile* parent);

	Tile* getParent();

	struct Compare{
		//To be used with the make_heap(), push_heap(), and pop_heap() functions
		bool operator()(const Tile* left, const Tile* right) const {
			//Returns the tile with the lowest movement cost and heuristic
			return (left->movementCost + left->heuristic) < (right->movementCost + right->heuristic);
		}
	};

};

#endif