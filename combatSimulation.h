#ifndef COMBATSIMULATION_H
#define COMBATSIMULATION_H

#include<vector>
#include<string>
#include<map>
#include <cstdlib>
#include <ctime>
#include "actors.h"

using namespace std;
namespace textAdventure{
	int randomGen(int low, int high){
		srand((int)time(0));
		int r = (rand() % high) + low;
		return r;
		
	}
	void firstEnemyCombatSim(enemy* anEnemy, mainActor* user);


}
#endif
