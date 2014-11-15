#include "tile.h"

Tile::Tile(){

}

Tile::Tile(unsigned int x, unsigned int y, bool isWall){
	this->x_ = x;
	this->y_ = y;
	this->isWall_ = isWall;
	
	this->isOpened_ = false;
	this->heuristic = 0;
	this->movementCost = 0;
	this->parent_ = 0;
}

Tile::Tile(const Tile &copyTile){
	this->x_ = copyTile.x_;
	this->y_ = copyTile.y_;
	this->isWall_ = copyTile.isWall_;

	this->isOpened_ = copyTile.isOpened_;
	this->heuristic = copyTile.heuristic;
	this->movementCost = copyTile.movementCost;

	//Shallow copy
	this->parent_ = copyTile.parent_;
}


unsigned int Tile::getX(){
	return x_;
}

unsigned int Tile::getY(){
	return y_;
}

bool Tile::isWall(){
	return isWall_;
}

bool Tile::isClosed(){
	return isClosed_ == true;
}

void Tile::close(){
	isClosed_ = true;
}

bool Tile::isOpened(){
	return isOpened_ == true;
}

void Tile::open(){
	isOpened_ = true;
}

void Tile::toggleWall(){
	isWall_ = !isWall_;
}

void Tile::setParent(Tile* parent){
	this->parent_ = parent;
}

Tile* Tile::getParent(){
	return parent_;
}


std::ostream& operator<<(std::ostream& out, Tile*& tile){
	//out << "(" << tile->x_ << ", " << tile->y_ << ", " << tile->heuristic << ", " << tile->movementCost <<")";
	out << *tile;
	return out;
}

std::ostream& operator<<(std::ostream& out, Tile& tile){
	out << "(" << tile.x_ << ", " << tile.y_ << ", " << tile.heuristic << ", " << tile.movementCost <<")";
	return out;
}
