#include "inventory.h"
#include "actors.h"

namespace textAdventure{

	void weapon::useWeapon(mainActor& theActor, enemy& theEnemy){

	}
	int weapon::getWeaponStrength(){
	return damagePoints;
	}
	string weapon::getName(){
	return weaponName;
	}
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

	void inventory::pickUpWeapon(weapon* aWeapon){
		//Add check for duplicate weapons
	
		weapons.insert(MyPair(aWeapon->getName(), aWeapon));
	}

	void inventory::displayWeapons(){
		map<string, weapon*>::iterator iter;
		cout << "weapons list " << endl;
		for (iter = weaponsContainer.begin(); iter != weaponsContainer.end(); iter++){
			cout << iter->first << " strength " << iter->second->getWeaponStrength() << endl;
		}
	}
	void inventory::displayhealthPacks(){
		for (healthPack* eachHP : healthPacks){
			cout <<"You have a health pack with " <<eachHP->getHealthValue() << " hp" << endl;
		}
	}



}
