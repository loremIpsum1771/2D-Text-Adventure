#include "combatSimulation.h"

namespace textAdventure{
	
	int randomGen(int low, int high){
		srand((int)time(0));
		int r = (rand() % high) + low;
		return r;
	}

	void enemyCombatSim(enemy* anEnemy, mainActor* user){
		std::cout << "\n\n\n -------------------------------------------------------------------\n----------------------------------------------------------\n----------------------------------------------------------- ";
		if (anEnemy->getEnemyName() == "Missing Victim 3 "){
			std::cout << "\n\n\nThe " << anEnemy->getEnemyName() << " from the case you were tipped on has snuck up on you from behind having slashed you with a knife!\n  " << std::endl;
			std::cout << "It seems that the suspect has performed some kind of mind control experiment on the missing persons, causing them to be violent with abnormal strength. You must fight to survive! \n" << std::endl;
			user->changeHP(-8); //initial damage
			std::cout << "You have taken damage!!" << std::endl;
		}
		else{
			std::cout << "\n\n\nThe " << anEnemy->getEnemyName() << " has now shown up in the house having just stepped in the door. As he walks into the foyer, he says 'You are tresspassing on private property! How did you find this place ?' \n  " << std::endl;
			std::cout << "you reply: 'That's not important. You have kidnapped missing persons and have done some kind of unethical operations on them. I'm here to stop you! \n" << std::endl;
			std::cout << "he says: 'So you've seen my subjects have you. Well rest assured that they are now serving a greater purpose than they ever have. I'm sure I can find something to use you for! \n" << std::endl;
			std::cout << "you reply: 'You can go ahead and try! I'm going to take you in!\n" << std::endl;
		}
		std::cout << "Type 'fight' to continue " << std::endl;
		std::string userControl;
		std::cin >> userControl;
		if (userControl == "fight"){
			std::cout << "Which is your weapon of choice? Type weapons to see weapons inventory. Or press 'c' to continue" << std::endl;
			std::cin >> userControl;
			if (userControl == "weapons"){
				user->displayInventory();
			}
			std::cout << "  Type the weapon name to select it " << std::endl;
			std::string currentWeapon;
			std::cin >> currentWeapon;
			Weapon* weapon = user->selectWeapon(currentWeapon);
			std::cout << "In this battle you can choose to either block or attack. Type 'a' for attack or 'd' for dodge. " << std::endl;
			//time delay (in milliseconds)
			Sleep(2000);
			std::cout << "\n\n\n -------------------------------------------------------------------" ;
			std::cout << "\n----------------------------------------------------------" << std::endl;
			std::cout << "The fight has begun!!!" << std::endl;
			while (user->getActorHealth() > 0 && anEnemy->getEnemyStrength() > 0){
				std::cout << "Your life points: " << user->getActorHealth() << " Enemy life points: " << anEnemy->getEnemyStrength() << " \n'a' or 'd'?" << std::endl;
				std::string choice;
				std::cin >> choice;
				if (choice == "a"){
					int hitProbability = randomGen(1, 7);
					//Checks whether the user is able to land the hit
					if (hitProbability > 2){
						//calculates strength of weapon plus strength of the individual attack
						int enemyDamage = randomGen(5, 7) + weapon->getWeaponStrength();
						anEnemy->setStrength(-enemyDamage);
						std::cout << " You land a " << weapon->useWeapon() << " on " << anEnemy->getEnemyName() << " for " << enemyDamage << " life points\n " << std::endl;
					}
					else{//if you don't land the hit
						int dodgeProbability = randomGen(1, 8);
						if (dodgeProbability > 6){//enemy dodges and counters
							int userDamage = randomGen(5, 10) + anEnemy->enemyWeaponStrength();
							user->changeHP(-userDamage);
							std::cout << anEnemy->getEnemyName() << " dodges and counters your attack for " << userDamage << " life points\n " << std::endl;
						}
						else{//enemy diverts the attack
							std::cout << anEnemy->getEnemyName() << " diverts your attack and pushes you backward!\n " << std::endl;
						}
					}
				}
				//if user dodges
				else if (choice == "d"){
					int dodgeProbability = randomGen(1, 5);
					if (dodgeProbability >= 3){
						int enemyDamage = randomGen(4, 6) + weapon->getWeaponStrength();
						anEnemy->setStrength(-enemyDamage);
						std::cout << " You dodge the attack of " << anEnemy->getEnemyName() << " and counter for a " << weapon->useWeapon() << " that takes " << enemyDamage << " life points\n " << std::endl;
					}
					//if user is unable to dodge
					else{
						int userDamage = randomGen(4, 6) + anEnemy->enemyWeaponStrength();
						user->changeHP(-userDamage);
						std::cout << " You are unable to divert the attack and " << anEnemy->getEnemyName() << " lands the hit for " << userDamage << " life points\n " << std::endl;
					}
				}
				else{
					std::cout << "enter a valid option" << std::endl;
				}

			}
			std::cout << "\n\n\n -------------------------------------------------------------------";
			std::cout << "\n----------------------------------------------------------" << std::endl;
			//entered for the first battle
			if (anEnemy->getEnemyName() == "Missing Victim 3 "){
				//called in the event of a loss
				if (user->getActorHealth() == 0){
					std::cout << "\n\n\n You have been killed by " << anEnemy->getEnemyName() << ". She is taking you into the bedroom to be harvested for the dinner of the suspect who is soon to arrive \n\n" << std::endl;

				}
				//called in the event of a win
				else{
					std::cout << "\n\n\nYou have killed the " << anEnemy->getEnemyName() << ". As you weren't even authorized to investigate this case in the first place, this could be bad.\n Better get to you car before the suspect gets back!\n\n" << std::endl;
				}
			}
			else{
				if (user->getActorHealth() == 0){
					std::cout << "\n\n\n You have been killed by " << anEnemy->getEnemyName() << ". He is taking you into the bedroom to be harvested for his dinner. Don't worry, he won't waste any part of you!\n\n" << std::endl;
					exit(0);
				}
				else{
					std::cout << "\n\n\nYou have killed the " << anEnemy->getEnemyName() << ". As you weren't even authorized to investigate this case in the first place, this will be hard to explain to your boss back at work.\n But seeing that you have been able to solve this case before it even started, you might get an award instead!\n Wait, but who was the person that gave you the tip? And how did he know this was happening in the first place????\n\n\n" << std::endl;
					exit(0);
				}
			}
		}


	}
}
