#define _CRT_SECURE_NO_WARNINGS
#include "actors.h"// header for main actor, enemy, weapons, healthpacks, and inventory classes
#include "gameboard.h" //header for gameboard  and room objects
#include "combatSimulation.h"// header for combat simulation and random number generator
#include<iostream>
#include<vector>
#include<string>
#include<fstream>
#include<sstream>

using namespace std;
using namespace textAdventure;


//splits each line from the file based on a specified delimiter and fills in the passed in vector which is parsed in the render map function
void tokenizer(char str[], vector<string>& tokens, const char delim[]) {
	tokens.clear();
	char* tok = strtok(str, delim);
	while (tok != nullptr) {
		tokens.push_back(tok);

		tok = strtok(nullptr, delim);
	}
}
//creates the map for the game and constructs the enemy and pickup (i.e. the weapons and health packs that can be picked up) objects
void renderMap(gameMap& map){
	ifstream txtFile("gameSetUp.txt");
	if (!txtFile) { cerr << "File not found"; return; }
	string fileLine;
	int i = 0;
	vector<Room*> roomPtrs;
	vector<enemy*> enemyPtrs;
	vector<healthPack*> hpPtrs;
	vector<Weapon*> weaponPtrs;
	while (getline(txtFile, fileLine)) {
		//# file lines = 20
		if (i < 20){
			vector<string> roomInfo; //vector for room info to be parsed
			vector<string> enemyInfo; // vector for enemy info to be parsed
			char* charStopLine = new char[fileLine.size() + 1]; //container for each file line
			strcpy(charStopLine, fileLine.c_str());
			//the room info extends from line 1 to line 16 (i lags 1 unit behind the line number)
			if (i < 16){
				//this branch is used exlusively to parse all of the room info
				char delim[] = "|";
				tokenizer(charStopLine, roomInfo, delim);
				string roomName = *(roomInfo.begin());
				string roomDescription = *(roomInfo.begin() + 1);
				int roomXdim = stoi(*(roomInfo.begin() + 2));
				int roomYdim = stoi(*(roomInfo.begin() + 3));
				Room* roomPtr = new Room(roomName, roomXdim, roomYdim);
				roomPtr->setRoomDesc(roomDescription);
				map.addRoom(roomPtr);
				if (i >= 13 && i < 16){ //used to hold pointers to the rooms where enemies will be positioned
					roomPtrs.push_back(roomPtr);
				}

			}
			if (i >= 16 && i < 18){
				//this branch is used exlusively to parse all of the enemy info
				char delim2[] = "$";
				tokenizer(charStopLine, enemyInfo, delim2);
				string enemyName = *(enemyInfo.begin());
				int enemyHp = stoi(*(enemyInfo.begin() + 1));
				int enemyStrength = stoi(*(enemyInfo.begin() + 2));
				string weaponName = *(enemyInfo.begin() + 3);
				enemy* enemyPtr = new enemy(enemyName);

				Weapon* enemyWeapon = new Weapon(weaponName);
				enemyPtr->setStrength(enemyHp);
				//enemyPtr->decreaseHP(enemyHp);
				enemyPtr->setWeapon(enemyWeapon);
				enemyPtrs.push_back(enemyPtr);
			}

			if (i == 18){
				//this branch is used exlusively to parse the info for the health pack that can be picked up
				char delim3[] = "=";
				vector<string> hpInfo;
				tokenizer(charStopLine, hpInfo, delim3);
				int hpStrength = stoi(*(hpInfo.begin() + 1));
				healthPack* hpPtr = new healthPack(hpStrength);
				hpPtrs.push_back(hpPtr);
			}
			if (i == 19){
				//this branch is used exlusively to parse the info for the weapon that can be picked up
				char delim4[] = "!";
				vector<string> weaponInfo;
				tokenizer(charStopLine, weaponInfo, delim4);
				string weaponName = *(weaponInfo.begin());
				Weapon* weaponPtr = new Weapon(weaponName);
				weaponPtrs.push_back(weaponPtr);
			}
			
			delete[] charStopLine;
		}
		i++;

	}
		roomPtrs[2]->addRoomHP(hpPtrs[0]);//Positions the health pack from the file inside of the specified room
		roomPtrs[2]->addRoomWeapon(weaponPtrs[0]);//Positions the weapon from the file inside of the specified room
		int j = 1;
		for (int i = 0; i < roomPtrs.size()-1; i++, j--){//Positions the enemies in the intended rooms
			roomPtrs[j]->addRoomEnemy(enemyPtrs[i]);

		

	}
}
//Main loop for the game
void gameLoop(){
	//char userControl = '0';
	string userControl;
	cout << "Enter Character name" << endl;
	string cName;
	cin >> cName;
	

	gameMap map;
	renderMap(map);//renders the gameMap and assigns it to the "map" instantiation
	Weapon* weaponPtr1 = new Weapon("knife");//weapons that the player spawns with
	Weapon* weaponPtr2 = new Weapon("bat");
	
	inventory* startInventory = new inventory();//inventory that the player spawns with
	startInventory->addWeapon(weaponPtr1);
	startInventory->addWeapon(weaponPtr2);
	mainActor* actorPtr = new mainActor(cName, startInventory);//initiallizes the player
	
	map.addGameUser(actorPtr);//spawns player inside of the map

	map.initializeMap();//sets the users's start positions
	map.printBoard();
	//game loop menu
	while (userControl != "q"){
		cout << "choose a direction\n enter 'l' to go left, 'r' for right, 'f' to go forward, 'b' to go to the previous room" << endl;
		cin >> userControl;
		if (userControl == "l"){
			map.navigateLeft();
		}
		if (userControl == "r"){
			map.navigateRight();
	

		}
		if (userControl == "f"){
			map.navigateForward();
		}
		if (userControl == "b"){

			map.navigateBackward();
		}
		
	}
}

int main(){


	gameLoop();
	return 0;
}
