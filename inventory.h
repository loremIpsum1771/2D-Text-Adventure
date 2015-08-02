#ifndef INVENTORY_H
#define INVENTORY_H

#include<vector>
#include<string>
#include<map>
#include "actors.h"

using namespace std;
namespace textAdventure{
	class mainActor;
	class enemy;
	/*class weapon{
	int damagePoints;
	string weaponName;
	public:
	virtual void useWeapon(mainActor& theActor, enemy& theEnemy);
	virtual int getWeaponStrength();
	virtual string getName();
	};

	class gun : public weapon{
	int damagePoints =0;
	public:
	gun();
	};

	class knife : public weapon{
	int damagePoints = 0;
	public:
	knife();
	};*/
	class healthPack{
		int hpStrength = 0;
	public:
		healthPack(int hp);
		int getHealthValue();
		void addHealth(mainActor anActor);
	};

	//class hints{


	//};

	class inventory{
		//typedef std::map<std::string, weapon*> WeaponsContainer;
		//typedef std::pair<std::string, weapon*> MyPair;
		//WeaponsContainer weapons;
		/*map<string, weapon* > weaponsContainer;*/
		vector<healthPack*> healthPacks;
		/*map<int, hints> hintsContainer;*/


	public:
		void pickUpHealth(healthPack* anHp);
		/*void pickUpWeapon(weapon aWeapon);*/
	};


}



#endif
