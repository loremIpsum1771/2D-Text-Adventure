#ifndef COMBATSIMULATION_H
#define COMBATSIMULATION_H

#include<vector>
#include<string>
#include<map>
#include <cstdlib>
#include <ctime>
#include <windows.h>
#include "actors.h"

namespace textAdventure{
	/*class Weapon;
	class enemy;*/
	class mainActor;
	int randomGen(int low, int high);
	void enemyCombatSim(enemy* anEnemy, mainActor* user);


}
#endif
