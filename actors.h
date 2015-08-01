#ifndef ACTORS_H
#define ACTORS_H

#include<vector>
#include<string>
#include<iostream>

using namespace std;
namespace textAdventure{
	class weapon;
	class enemy{
		string enemyName;
		double battleRatio;
		int currentHP;
		int effectivness;
		int enemyStrength;
	public:
		enemy(const string& eName);
		string getEnemyName();
		virtual void setLoserStrength(double loserStr);
		virtual void setWinnerStrength(double battleRatio);
		virtual double getEnemyStrength();
		bool dead = false;

	};
	class mainActor{
		string actorName;
		double battleRatio = 0;
		int currentHP = 100;
		
		vector<weapon> Inventory;
		int effectivness;
	public:
		mainActor(const string& nName);
		string getActorName();
		virtual void setLoserStrength(double loserStr);
		virtual void setWinnerStrength(double battleRatio);
		virtual double getActorStrength();
		virtual void battle(enemy& nobleOpponent);
		bool dead = false;
		
	};
}


#endif
