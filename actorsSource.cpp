#include "actors.h"

namespace textAdventure{
	
	enemy::enemy(const std::string& eName){
		enemyName = eName;
	}
	std::string enemy::getEnemyName(){
		return enemyName;
	}
	void enemy::setStrength(int strength){
		enemyStrength += strength;
	}
	int enemy::getEnemyStrength(){
		return enemyStrength;
	}
	//Could be used if enemy has both  health and strength
	/*void enemy::decreaseHP(int healthLoss){
		enemyStrength += healthLoss;
	}*/
	void enemy::setWeapon(Weapon* aWeapon){
		enemyWeapon = aWeapon;
	}
	int enemy::enemyWeaponStrength(){
		return enemyWeapon->getWeaponStrength();
	}
	mainActor::mainActor(const std::string& nName, inventory* anInventory) : actorName(nName){
		userInventory = anInventory;
	}
	std::string mainActor::getActorName(){
		return actorName;
	}
	void mainActor::setStrength(int str){
		battleRatio = str;
	}
	
	int mainActor::getActorHealth(){
		return currentHP;
	}
	void mainActor::changeHP(int healthChange){
		currentHP += healthChange;
	}
	void mainActor::pickUpWeapon(Weapon* aWeapon){
		userInventory->addWeapon(aWeapon);
	}
	void mainActor::pickUpHP(healthPack* hp){
		userInventory->addHealthPack(hp);
	}
	void mainActor::displayInventory(){
		userInventory->displayWeapons();
		userInventory->displayhealthPacks();
	}
	void mainActor::applyHealth(){
		healthPack* aHP = userInventory->getHealthPacks().back();
		currentHP += aHP->getHealthValue();
	}
	Weapon* mainActor::selectWeapon(std::string weaponName){
		return userInventory->selectWeapon(weaponName);
	}

	Weapon::Weapon(const std::string& wName) : weaponName(wName){		
		if (wName == "knife"){
			damagePoints = 7;
		}
		else if (wName == "hatchet"){
			damagePoints = 9;
		}
		else if (wName == "bat"){
			damagePoints = 5;
		}
	}

	
	
	std::string Weapon::useWeapon(){
		return "stab";
	}
	int Weapon::getWeaponStrength(){
		return damagePoints;
	}
	std::string Weapon::getName(){
		return weaponName;
	}
	healthPack::healthPack(int hp) : hpStrength(hp){}

	int healthPack::getHealthValue(){
		return hpStrength;
	}
	void inventory::discardHealthPack(healthPack* hp){
		for (healthPack* eachHp : healthPacks){
			if (hp->getHealthValue() == eachHp->getHealthValue()){
				delete eachHp;
			}
		}
	}
	void mainActor::destroyHP(healthPack* hp){
		userInventory->discardHealthPack(hp);
	}
	/*void healthPack::addHealth(mainActor* anActor){
		anActor->changeHP(hpStrength);
	}*/

	std::vector<healthPack*> inventory::getHealthPacks(){
		return healthPacks;
	}
	void inventory::addHealthPack(healthPack* anHp){
		healthPacks.push_back(anHp);
	}

	void inventory::addWeapon(Weapon* aWeapon){
		//Add check for duplicate weapons

		weapons.insert(MyPair(aWeapon->getName(), aWeapon));
	}

	void inventory::displayWeapons(){
		std::map<std::string, Weapon*>::iterator iter;
		std::cout << "weapons list " << std::endl;
		for (iter = weapons.begin(); iter != weapons.end(); iter++){
			std::cout << iter->first << " strength " << iter->second->getWeaponStrength() << std::endl;
		}
	}
	void inventory::displayhealthPacks(){
	for (healthPack* eachHP : healthPacks){
		if (eachHP != nullptr){
			std::cout << "You have a health pack with " << eachHP->getHealthValue() << " hp" << std::endl;
		}
	}
	}

	Weapon* inventory::selectWeapon(std::string weaponName){
		std::map<std::string, Weapon*>::iterator iter;
		std::cout << "weapons list " << std::endl;
		for (iter = weapons.begin(); iter != weapons.end(); iter++){
			if (iter->second->getName() == weaponName){
				return iter->second;
			}
			else{
				continue;
			}

		}

	}


}
