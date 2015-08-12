#ifndef ACTORS_H
#define ACTORS_H

#include<vector>
#include<string>
#include<iostream>
#include<map>

namespace textAdventure{
	//class inventory;
	//class Weapon;
	//class healthPack;
	
	class katana{
		int strengthPoints = 10;
	public:
		katana(){}
		int getStrength();

	};

	class Weapon{
		int damagePoints = 0;
		std::string weaponName;
	public:
		Weapon(const std::string& wName);
		std::string useWeapon();
		int getWeaponStrength();
		std::string getName();
		

	};
	class healthPack{
		int hpStrength = 0;
	public:
		healthPack(int hp);
		int getHealthValue();
		//void addHealth(mainActor* anActor);
	};
	
	class inventory{
		typedef std::map<std::string, Weapon*> WeaponsContainer;
		typedef std::pair<std::string, Weapon*> MyPair;
		WeaponsContainer weapons;
		std::vector<healthPack*> healthPacks;
		//map<int, hints> hintsContainer;


	public:
		void discardHealthPack(healthPack* hp);
		void addHealthPack(healthPack* anHp);
		void addWeapon(Weapon* aWeapon);
		void displayWeapons();
		void displayhealthPacks();
		std::vector<healthPack*> getHealthPacks();
		Weapon* selectWeapon(std::string weaponName);
	};
	class enemy{
		std::string enemyName;
		double battleRatio;
		int currentHP;
		//int effectivness;
		int enemyStrength;
		Weapon* enemyWeapon;

	public:
		enemy(const std::string& eName);
		std::string getEnemyName();
		int getEnemyStrength();
		void setStrength(int battleRatio);
		//void setHp(int battleRatio);
		//void decreaseHP(int hp);
		void setWeapon(Weapon* aWeapon);
		int enemyWeaponStrength();
		bool dead = false;

	};
	class mainActor{
		std::string actorName;
		int battleRatio = 0;
		int currentHP = 100;
		inventory* userInventory;
		//vector<weapon> Inventory;
		int effectivness;
	public:
		mainActor(const std::string& nName , inventory* startInventory);
		std::string getActorName();
		void destroyHP(healthPack* hp);
		void setStrength(int battleRatio);
		void changeHP(int hp);
		//void addHealthPoints(int hp);
		//void addStrength(int str);
		int getActorHealth();
		//void addWeapon(Weapon* aWeapon);
		void pickUpHP(healthPack* hp);
		void displayInventory();
		void pickUpWeapon(Weapon* weapon);
		void applyHealth();
		Weapon* selectWeapon(std::string weaponName);
		bool dead = false;

	};




	

	
}


#endif
