#include "grid.h"
#include <cstdlib>

int main(){
	Grid world(1000, 1000);

	//Play around by toggling walls at certain coordinates
	//TODO: Find a better way to test
	//world.updateCost(2, 2, PF_INFINITY);
	world.computeShortestPath();


	system("PAUSE");
	return 0;
}