#include "grid.h"
#include <cstdlib>

int main(){
	Grid world(10,10);
	
	//Play around by toggling walls at certain coordinates
	world.toggleWall(0,1);
	//world.toggleWall(1,0);


	world.generatePath();
	world.printPath();

	system("PAUSE");
	return 0;
}