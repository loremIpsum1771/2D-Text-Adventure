#ifndef ACTORS_H
#define ACTORS_H

#include<vector>
#include<string>
#include<iostream>
#include "inventory.h"

using namespace std;
namespace textAdventure{
	class inventory;
	class weapon;
	class healthPack;
	class enemy{
		string enemyName;
		double battleRatio;
		int currentHP;
		//int effectivness;
		int enemyStrength;
		weapon* enemyWeapon;

	public:
		enemy(const string& eName);
		string getEnemyName();
		int getEnemyStrength();
		void setStrength(int battleRatio); 
		void setHp(int battleRatio);
		void decreaseHP(int hp);
		void setWeapon(weapon* aWeapon);
		bool dead = false;

	};
	class mainActor{
		string actorName;
		int battleRatio = 0;
		int currentHP = 100;
		inventory* inventory;
		//vector<weapon> Inventory;
		int effectivness;
	public:
		mainActor(const string& nName);
		string getActorName();
		void setStrength(int battleRatio);
		void changeHP(int hp);
		void addHealthPoints(int hp);
		//void addStrength(int str);
		int getActorStrength();
		void addWeapon(weapon* aWeapon);
		void addHealthPack(healthPack* hp);
		void displayInventory();
		void battle(enemy& nobleOpponent);
		bool dead = false;

	};
}


#endif
