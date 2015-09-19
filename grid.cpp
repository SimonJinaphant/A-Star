#include "grid.h"

Grid::Grid(unsigned int length, unsigned int width){
	this->length = length;
	this->width = width;

	for (unsigned int y = 0; y < length; y++){
		for (unsigned int x = 0; x < width; x++){
			gridmap.push_back(Tile(x, y, STANDARD_COST));
		}
	}

	
	start = getTileAt(0, 0);
	goal = getTileAt(width - 1, length - 1);
}


void Grid::computeShortestPath(){
	//Set-up the algorithm by creating OPEN list and placing our starting point inside
	std::vector<Tile*> open;
	
	goal->isOpen = true;
	open.push_back(goal);

	//This is the main part of the algorithm
	while (open.size() != 0){

		//CURRENT is a Tile* inside OPEN with the lowest G + H scores
		Tile* current = open.back();
		open.pop_back();

		//Close the CURRENT tile to prevent it from being re-analysed again by another tile
		current->isClose = true;
		
		std::cout << "Current tile: " << std::endl;
		current->info();

		if (current == start){
			std::cout << "A path has been found!" << std::endl;
			while (start->parent != 0){
				start->info();
				start = start->parent;
			}
			break;
		}

		//Get all neigbouring tiles of CURRENT
		//See Reference Note: 1 for more detail on how this loop works
		for (int dy = -1; dy <= 1; dy++){
			for (int dx = -1; dx <= 1; dx++){
				if (abs(dy) + abs(dx) != 0){

					//Get the pointer to a neighbouring tile
					Tile* neighbour = getTileAt(current->x + dx, current->y + dy);
					
					//Determine if this neighbouring tile should be analysed
					if (neighbour == 0 || neighbour->isClose || neighbour->cost == PF_INFINITY){
						continue;
					}

					if (abs(dy) + abs(dx) == 2){
						/*
							This tile is located diagonally from CURRENT
							
							However, not all diagonal tiles can be reached without hitting a sharp corner,
							we need to test if this tile is reachable
							
							See Reference Note: 2 for more detail
						*/
						Tile* a = getTileAt(current->x, current->y + dy);
						Tile* b = getTileAt(current->x + dx, current->x);

						if (a != 0 && a->cost == PF_INFINITY || b != 0 && b->cost == PF_INFINITY){
							continue;
						}
					}

					//Calculate the new g value
					double newGValue = current->g + calculateCost(current, neighbour);

					//Determine if this tile is currently "inside" the OPEN list
					bool isCurrentlyOpen = neighbour->isOpen;

					if (!isCurrentlyOpen || newGValue < neighbour->g){
						//(NEIGHBOUR is not in the OPEN list) OR (it's already in OPEN but we found a shorter path to it)

						//Open/Reopen this neighbouring tile
						neighbour->isOpen = true;

						//Update the NEIGHBOUR'S cost and parents
						neighbour->parent = current;
						neighbour->g = newGValue;
						calculateHeuristics(neighbour);

						//Use the previously stored value to determine what to do with the updated neighbour
						if (!isCurrentlyOpen){
							//Since NEIGHBOUR was not inside OPEN beforehand, we add it to OPEN
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

	std::cout << "No path found :(" << std::endl;
}

bool Grid::withinMap(unsigned int x, unsigned int y){
	//Determines if the coordinate is within the bounds of the grid map
	return y >= 0 && y < length && x >= 0 && x < width;
}

void Grid::calculateHeuristics(Tile*& tile){
	//This is a calculation used to estimate the distance a tile and the goal tile

	unsigned int dx = labs(tile->x - goal->x);
	unsigned int dy = labs(tile->y - goal->y);

	if (dx > dy){
		std::swap(dx, dy);
	}

	return ((SQRT2 - 1) * dx + dy) * STANDARD_COST;
}

double Grid::calculateCost(Tile*& tileA, Tile*& tileB){
	if (tileA->cost == PF_INFINITY || tileB->cost == PF_INFINITY){
		//Should prevent an obvious binary overflow
		return PF_INFINITY;
	}

	if (labs(tileA->x - tileB->x) + labs(tileA->y - tileB->y) == 2){
		//These two tiles are diagonally adjacent to each other

		//Note: We assume that the map isn't big enough to make cost approach PF_INFINITY/2,
		//becareful of potential binary overflow here.
		return SQRT2 * (tileA->cost + tileB->cost) / 2;
	}

	return (tileA->cost + tileB->cost) / 2;
}


void Grid::updateCost(unsigned int x, unsigned int y, double cost){
	getTileAt(x, y)->cost = cost;
}


Tile* Grid::getTileAt(unsigned int x, unsigned int y){
	return withinMap(x, y) ? &(gridmap[y * width + x]) : NULL;
}
