#include "grid.h"

Grid::Grid(unsigned int xSize, unsigned int ySize){
	for (unsigned int y = 0; y < ySize; y++){
		std::vector<Tile> row;

		for (unsigned int x = 0; x < xSize; x++){
			row.push_back(Tile(x, y, false));
		}
		gridWorld_.push_back(row);
	}


	//For simplicity we make the START and FINISH at opposite corners of the map
	start_ = getTileAt(0, 0);
	goal_ = getTileAt(gridWorld_.size() - 1, gridWorld_.at(0).size() - 1);
}

Grid::~Grid(){
	std::cout << "Destructor called" << std::endl;
	for (unsigned int y = 0; y < gridWorld_.size(); y++){
		for (unsigned int x = 0; x < gridWorld_.at(0).size(); x++){
			gridWorld_.at(y).at(x).setParent(0);
		}
	}

}


void Grid::generatePath(){
	//Reset the path incase we're re-running this algorithm again
	path.empty();

	//Set-up the algorithm by creating OPEN and placing START inside
	std::vector<Tile*> openTiles;
	openTiles.push_back(start_);

	//This is the main part of the algorithm
	while(openTiles.size() != 0){

		//CURRENT := Tile* inside OPEN with the lowest (HEURISTIC + MOVEMENTCOST)
		Tile* current = openTiles.back();	
		openTiles.pop_back();

		//CLOSE the CURRENT tile to prevent it from being re-analysed again by another tile
		current->close();

		if(current == goal_){
			//End case: we've reached our GOAL
			while (current != 0){
				path.push_back(current);
				current = current->getParent();
			}

			break;
		}

		//Get all neigbouring tiles of the CURRENT
		//See Reference Note: 1 for more detail on how this loop works
		for (int y = -1; y <= 1; y++){
			for (int x = -1; x <= 1; x++){
				if(abs(y) + abs(x) != 0){

					//Get the pointer to the neighbouring tile
					Tile* neighbour = getTileAt(current->getX() + x, current->getY() + y);

					//Determine if this neighbouring tile shouldn't be analysed
					if(neighbour == 0 || neighbour->isClosed() || neighbour->isWall()){
						continue;
					}

					if(abs(y) + abs(x) == 2){
						/*
							This tile is located diagonally from CURRENT.
							However, not all diagonal tiles can be reached; we need to test if this tile is reachable

							See Reference Note: 2 for more detail
						*/
						Tile* a = getTileAt(current->getX(), current->getY() + y);
						Tile* b = getTileAt(current->getX() + x, current->getY());
						
						if(a != 0 && a->isWall() || b != 0 && b->isWall()){
							continue;
						}
					}

					//Calculate the new momvement cost
					unsigned int newMovementCost = current->movementCost + (abs(y) + abs(x) == 2 ? 14 : 10);
					
					//Determine if this tile is currently "in" the OPEN list
					bool isCurrentlyOpen = neighbour->isOpened();

					if(!isCurrentlyOpen || newMovementCost < neighbour->movementCost){
						//(NEIGHBOUR is not in the OPEN list) OR (it's already in OPEN but we found a shorter path to it)
						
						//Open this neighbouring tile, but remember that we still have its previous state stored in @isCurrentlyOpen
						neighbour->open();
						
						//Update the NEIGHBOUR'S cost and parents
						neighbour->setParent(current);
						neighbour->movementCost = newMovementCost;
						calculateHeuristics(neighbour);

						//Use the previously stored value to determine what to do with the updated neighbour
						if(!isCurrentlyOpen){
							//Since NEIGHBOUR is not inside OPEN, we add it to OPEN
							openTiles.push_back(neighbour);
							push_heap(openTiles.begin(), openTiles.end(), Tile::Compare());
						} else {
							//NEIGHBOUR is already inside OPEN, we need to update it's priority in the queue
							
							//Since I'm using pointers I don't need to remove it, update it, and add it back in
							//Instead I can just update it and make the Priority Queue re-organize itself
							make_heap(openTiles.begin(), openTiles.end(), Tile::Compare());
							
						}

					}
				}

			}

		}
	}


	if(path.size() == 0){
		std::cout << "No path found :(" << std::endl;
	} else {
		std::reverse(path.begin(), path.end());
	}
	
}

bool Grid::withinMap(unsigned int x, unsigned int y){
	//Determines if the coordinate is within the bounds of the grid map
	return y >= 0 && y < gridWorld_.size() && x >= 0 && x < gridWorld_.at(0).size();
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
	int dx1 = tile->getX() - goal_->getX();
	int dy1 = tile->getY() - goal_->getY();

	int dx2 = start_->getX() - goal_->getX();
	int dy2 = start_->getY() - goal_->getY();
	int cross = abs( dx1 * dy2 - dx2 * dy1);

	int x = abs(dx1);
	int y = abs(dy1);

	if(x > y){
		tile->heuristic = ((14*y + 10*(x-y)) + cross*0.5);
    } else {
		tile->heuristic = ((14*x + 10*(y-x)) + cross*0.5);
	}
}

void Grid::toggleWall(unsigned int x, unsigned int y){
	getTileAt(x,y)->toggleWall();
}


Tile* Grid::getTileAt(unsigned int x, unsigned int y){
	if(withinMap(x,y)){
		return &(gridWorld_.at(y).at(x));
	}
	return NULL;
}

void Grid::printPath(){
	for(Tile* t : path){
		std::cout << *t << std::endl;
	}
}