#include "inventory.h"
#include "actors.h"

namespace textAdventure{





	/*void weapon::useWeapon(mainActor& theActor, enemy& theEnemy){

	}
	int weapon::getWeaponStrength(){
	return damagePoints;
	}
	string weapon::getName(){
	return weaponName;
	}*/
	healthPack::healthPack(int hp) : hpStrength(hp){}

	int healthPack::getHealthValue(){
		return hpStrength;
	}

	void healthPack::addHealth(mainActor anActor){
		anActor.addHealthPoints(hpStrength);
	}

	void inventory::pickUpHealth(healthPack* anHp){
		healthPacks.push_back(anHp);
	}

	//void inventory::pickUpWeapon(weapon* aWeapon){
	//	//Add check for duplicate weapons
	//	
	//	weapons.insert(MyPair(aWeapon->getName(), aWeapon));

	//
	//}




}
