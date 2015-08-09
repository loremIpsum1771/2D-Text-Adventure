#include "combatSimulation.h"

namespace textAdventure{

	void firstEnemyCombatSim(enemy* anEnemy, mainActor* user){
		cout << "The " << anEnemy->getEnemyName() << " from the case you were tipped on has snuck up on you from behind having slashed you with a knife!\n  " << endl;
		cout << "It seems that the suspect has performed some kind of mind control experiment on the missing persons, causing them to be violent with abnormal strength. You must fight to survive! \n" << endl;
		cout << "Type 'fight' to continue " << endl;
		string userControl;
		cin >> userControl;
		if (userControl == "fight"){
			cout << "Which is your weapon of choice? Type weapons to see weapons inventory." << endl;
			cin >> userControl;
			if (userControl == "weapons"){
				user->displayInventory();
			}
			cout << "  Type the weapon name to select it " << endl;
			string currentWeapon;
			cin >> currentWeapon;
			weapon* weapon = user->selectWeapon(currentWeapon);
			cout << "In this battle you can choose to either block or attack. Type 'a' for attack or 'd' for dodge" << endl;
			while (user->getActorHealth() != 0 &&  anEnemy->getEnemyStrength() != 0){
				cout << "'a' or 'd'?" << endl;
				string choice;
				if (choice == "a"){
					int hitProbability = randomGen(1, 7);
					//Checks whether the user is able to land the hit
					if (hitProbability > 2){
						//calculates strength of weapon plus strength of the individual attack
						int enemyDamage = randomGen(5, 7) + weapon->getWeaponStrength();
						anEnemy->decreaseHP(-enemyDamage);
						cout << " You landed a " << weapon->useWeapon() << " on " << anEnemy->getEnemyName() << " for " << enemyDamage << " life points " << endl;
					}
					else{
						int dodgeProbability = randomGen(1, 8);
						if (dodgeProbability > 6){
							int userDamage = randomGen(5, 10) + weapon->getWeaponStrength();
							user->addHealthPoints(-userDamage);
							cout <<  anEnemy->getEnemyName() << " dodged and counter your attack for "  << userDamage << " life points " << endl;
						}
					}
				}
				//if user blocks
				else if(choice == "d"){
					int dodgeProbability = randomGen(1, 5);
					if (dodgeProbability >= 3){
						int enemyDamage = randomGen(4,6) + weapon->getWeaponStrength();
						anEnemy->decreaseHP(-enemyDamage);
						cout << " You dodged the attack of " << anEnemy->getEnemyName() << " and countered for a "<< weapon->useWeapon() << " that took "<< enemyDamage << " life points " << endl;
					}
				}
				else{
					cout << "enter a valid option" << endl;
				}
			
			}
			if (user->getActorHealth() == 0){
				cout << " You have been killed by " << anEnemy->getEnemyName() << ". She is taking you into the bedroom to be harvested for the dinner of the suspect who is soon to arrive " << endl;

			}
			else{
				cout << "You have killed the " << anEnemy->getEnemyName() << ". As you weren't even authorized to investigate this case in the first place, this could be bad.\n Better get to you car before the suspect gets back!" << endl;
			}
		}
		

	}
}
