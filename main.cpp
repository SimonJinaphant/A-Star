#include "grid.h"
#include <cstdlib>

int main(){
	Grid world(5, 5);

	//Play around by toggling walls at certain coordinates
	world.updateCost(2, 2, PF_INFINITY);
	world.generatePath();

	printf("PATH IS: \n");
	world.printPath();

	system("PAUSE");
	return 0;
}