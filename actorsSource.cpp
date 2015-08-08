#include "actors.h"

namespace textAdventure{
	enemy::enemy(const string& eName){
		enemyName = eName;
	}
	string enemy::getEnemyName(){
		return enemyName;
	}
	void enemy::setStrength(int strength){
		enemyStrength = strength;
	}
	int enemy::getEnemyStrength(){
		return enemyStrength;
	}
	void enemy::decreaseHP(int healthLoss){
		enemyStrength += healthLoss;
	}
	void enemy::setWeapon(weapon* aWeapon){
		enemyWeapon = aWeapon;
	}

	mainActor::mainActor(const string& nName) : actorName(nName){}
	string mainActor::getActorName(){
		return actorName;
	}
	void mainActor::setStrength(int str){
		battleRatio = str;
	}
	void mainActor::addHealthPoints(int str){
		currentHP += str;
	}

	int mainActor::getActorStrength(){
		return battleRatio;
	}
	void mainActor::changeHP(int healthChange){
		currentHP += healthChange;
	}
	void mainActor::addWeapon(weapon* aWeapon){
		inventory->pickUpWeapon(aWeapon);
	}

	void mainActor::addHealthPack(healthPack* hp){
		inventory->pickUpHealth(hp);
	}
	void mainActor::displayInventory(){
		inventory->displayWeapons();
		inventory->displayhealthPacks();
	}
	void mainActor::battle(enemy& anEnemy){
		//Simulates Battle 
		cout << this->getActorName() << " battles " << anEnemy.getEnemyName() << endl;
		if (this->dead == true && anEnemy.dead == true){
			cout << "Oh, NO! They're both dead!" << endl;
		}

		else if (anEnemy.dead == true){
			cout << anEnemy.getEnemyName() << "is already dead." << endl;
		}
		else if (this->getActorStrength() > anEnemy.getEnemyStrength()){

			battleRatio = (this->getActorStrength() - anEnemy.getEnemyStrength()) / this->getActorStrength();
			anEnemy.decreaseHP(0);
			anEnemy.dead = true;
			this->setStrength(battleRatio);

			cout << this->getActorName() << " defeats " << anEnemy.getEnemyName() << endl;
		}
		else if (anEnemy.getEnemyStrength() > this->getActorStrength()){

			battleRatio = (anEnemy.getEnemyStrength() - this->getActorStrength()) / anEnemy.getEnemyStrength();
			this->setStrength(0);
			this->dead = true;
			anEnemy.setStrength(battleRatio);

			cout << anEnemy.getEnemyName() << " defeats " << this->getActorName() << endl;
		}
		else if (this->getActorStrength() == anEnemy.getEnemyStrength()){

			this->setStrength(0);
			anEnemy.setStrength(0);
			this->dead = true;
			anEnemy.dead = true;

			cout << "Mutual Annihalation: " << this->getActorName()
				<< " and " << anEnemy.getEnemyName() << " die at each other's hands." << endl;
		}
	}


}
