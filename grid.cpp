#include "grid.h"

Grid::Grid(unsigned int length, unsigned int width){
	this->length = length;
	this->width = width;

	for (unsigned int y = 0; y < length; y++){
		for (unsigned int x = 0; x < width; x++){
			gridmap.push_back(Tile(x, y, 10.0));
		}
	}

	start = getTileAt(0, 0);
	goal = getTileAt(width - 1, length - 1);
}


void Grid::generatePath(){
	//Reset the path incase we're re-running this algorithm again
	path.empty();

	//Set-up the algorithm by creating OPEN and placing START inside
	std::vector<Tile*> open;
	goal->isOpen = true;
	open.push_back(goal);

	//This is the main part of the algorithm
	while (open.size() != 0){

		//CURRENT := Tile* inside OPEN with the lowest (HEURISTIC + MOVEMENTCOST)
		Tile* current = open.back();
		open.pop_back();

		//CLOSE the CURRENT tile to prevent it from being re-analysed again by another tile
		current->isClose = true;
		current->info();
		if (current == start){
			//End case: we've reached our GOAL
			while (current != 0){
				path.push_back(current);
				current = current->parent;
			}

			break;
		}

		//Get all neigbouring tiles of the CURRENT
		//See Reference Note: 1 for more detail on how this loop works
		for (int dy = -1; dy <= 1; dy++){
			for (int dx = -1; dx <= 1; dx++){
				if (abs(dy) + abs(dx) != 0){

					//Get the pointer to the neighbouring tile
					Tile* neighbour = getTileAt(current->x + dx, current->y + dy);
					
					//Determine if this neighbouring tile shouldn't be analysed
					if (neighbour == 0 || neighbour->isClose || neighbour->cost == PF_INFINITY){
						continue;
					}

					if (abs(dy) + abs(dx) == 2){
						/*
						This tile is located diagonally from CURRENT.
						However, not all diagonal tiles can be reached; we need to test if this tile is reachable
						See Reference Note: 2 for more detail
						*/
						Tile* a = getTileAt(current->x, current->y + dy);
						Tile* b = getTileAt(current->x + dx, current->x);

						if (a != 0 && a->cost == PF_INFINITY || b != 0 && b->cost == PF_INFINITY){
							continue;
						}
					}

					//Calculate the new momvement cost
					double newGValue = current->g + calculateCost(current, neighbour);

					//Determine if this tile is currently "in" the OPEN list
					bool isCurrentlyOpen = neighbour->isOpen;

					if (!isCurrentlyOpen || newGValue < neighbour->g){
						//(NEIGHBOUR is not in the OPEN list) OR (it's already in OPEN but we found a shorter path to it)

						//Open this neighbouring tile, but remember that we still have its previous state stored in @isCurrentlyOpen
						neighbour->isOpen = true;

						//Update the NEIGHBOUR'S cost and parents
						neighbour->parent = current;
						neighbour->g = newGValue;
						calculateHeuristics(neighbour);

						//Use the previously stored value to determine what to do with the updated neighbour
						if (!isCurrentlyOpen){
							//Since NEIGHBOUR is not inside OPEN, we add it to OPEN
							printf("\tAdding:");
							neighbour->info();
							open.push_back(neighbour);
							push_heap(open.begin(), open.end(), Tile::Compare());
						}
						else {
							//NEIGHBOUR is already inside OPEN, we need to update it's priority in the queue
							printf("\t Updating:");
							neighbour->info();
							//Since I'm using pointers I don't need to remove it, update it, and add it back in
							//Instead I can just update it and make the Priority Queue re-organize itself
							make_heap(open.begin(), open.end(), Tile::Compare());

						}

					}
				}

			}

		}
	}


	if (path.size() == 0){
		std::cout << "No path found :(" << std::endl;
	}
	else {
		//std::reverse(path.begin(), path.end());
	}

}

bool Grid::withinMap(unsigned int x, unsigned int y){
	//Determines if the coordinate is within the bounds of the grid map
	return y >= 0 && y < length && x >= 0 && x < width;
}

void Grid::calculateHeuristics(Tile*& tile){
	/*
	This algorimth is based on an exmaple of one of the tutorial I've read

	It calculates cross vector product between the vector of CURRENT and FINISH
	and the vector of START and FINISH
	DON'T ASK ME HOW THE MATH WORKS...I HAVE NO IDEA...

	All I know is that this heuristic makes sure our path doesn't
	look weird by preventing multiple zig-zag
	*/
	int dx1 = tile->x - goal->x;
	int dy1 = tile->y - goal->y;

	int dx2 = start->x - goal->x;
	int dy2 = start->y - goal->y;
	int cross = abs(dx1 * dy2 - dx2 * dy1);

	int x = abs(dx1);
	int y = abs(dy1);

	if (x > y){
		tile->h = ((14 * y + 10 * (x - y)) + cross*0.5);
	}
	else {
		tile->h = ((14 * x + 10 * (y - x)) + cross*0.5);
	}
}

double Grid::calculateCost(Tile*& tileA, Tile*& tileB){
	if (tileA->cost == PF_INFINITY || tileB->cost == PF_INFINITY){
		return PF_INFINITY;
	}
	if (labs(tileA->x - tileB->x) + labs(tileA->y - tileB->y) == 2){
		//These two tiles are diagonally adjacent to each other
		return SQRT2 * (tileA->cost + tileB->cost) / 2;
	}
	return (tileA->cost + tileB->cost) / 2;
}

void Grid::updateCost(unsigned int x, unsigned int y, double cost){
	getTileAt(x, y)->cost = cost;
}


Tile* Grid::getTileAt(unsigned int x, unsigned int y){
	if (withinMap(x, y)){
		return &(gridmap[y * width + x]);
	}
	return NULL;
}

void Grid::printPath(){
	for (Tile* t : path){
		t->info();
	}
}