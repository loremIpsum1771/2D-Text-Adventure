#include "actors.h"

namespace textAdventure{
	enemy::enemy(const string& eName){
		enemyName = eName;
	}
	string enemy::getEnemyName(){
		return enemyName;
	}
	void enemy::setLoserStrength(double loserStr){
		enemyStrength = loserStr;
	}
	void enemy::setWinnerStrength(double battleRatio){
		enemyStrength = battleRatio;
	}
	double enemy::getEnemyStrength(){
		return enemyStrength;
	}
	
	mainActor::mainActor(const string& nName) : actorName(nName){}
	string mainActor:: getActorName(){
		return actorName;
	}
	void mainActor::setLoserStrength(double loserStr){
		battleRatio = loserStr;
	}
	void mainActor::setWinnerStrength(double battleRatio){

	}
	double mainActor::getActorStrength(){
		return battleRatio;
	}
	string mainActor::getActorName(){
		//Returns Noble Name
		return this->actorName;
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
			anEnemy.setLoserStrength(0);
			anEnemy.dead = true;
			this->setWinnerStrength(battleRatio);

			cout << this->getActorName() << " defeats " << anEnemy.getEnemyName() << endl;
		}
		else if (anEnemy.getEnemyStrength() > this->getActorStrength()){

			battleRatio = (anEnemy.getEnemyStrength() - this->getActorStrength()) / anEnemy.getEnemyStrength();
			this->setLoserStrength(0);
			this->dead = true;
			anEnemy.setWinnerStrength(battleRatio);

			cout << anEnemy.getEnemyName() << " defeats " << this->getActorName() << endl;
		}
		else if (this->getActorStrength() == anEnemy.getEnemyStrength()){

			this->setLoserStrength(0);
			anEnemy.setLoserStrength(0);
			this->dead = true;
			anEnemy.dead = true;

			cout << "Mutual Annihalation: " << this->getActorName()
				<< " and " << anEnemy.getEnemyName() << " die at each other's hands." << endl;
		}
	}


}
