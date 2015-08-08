#define _CRT_SECURE_NO_WARNINGS
#include "actors.h"
#include "gameboard.h"
#include "inventory.h"
#include<iostream>
#include<vector>
#include<string>
#include<fstream>
#include<sstream>

using namespace std;
using namespace textAdventure;

void tokenizer(char str[], vector<string>& tokens, const char delim[]) {
	tokens.clear();
	char* tok = strtok(str, delim);
	while (tok != nullptr) {
		tokens.push_back(tok);

		tok = strtok(nullptr, delim);
	}
}

void renderMap(gameMap& map){
	ifstream txtFile("adventureExposition.txt");
	if (!txtFile) { cerr << "File not found"; return; }
	string fileLine;
	//getline(txtFile, fileLine);
	int i = 0;
	vector<Room*> roomPtrs;
	vector<enemy*> enemyPtrs;
	while (getline(txtFile, fileLine)) {
		if (i < 16){
			vector<string> roomInfo;
			vector<string> enemyInfo;
			char delim[] = "|";
			char delim2[] = "$";
			char* charStopLine = new char[fileLine.size() + 1];
			strcpy(charStopLine, fileLine.c_str());

			tokenizer(charStopLine, roomInfo, delim);
			tokenizer(charStopLine, enemyInfo, delim2);
			string roomName = *(roomInfo.begin());
			string roomDescription = *(roomInfo.begin() + 1);
			int roomXdim = stoi(*(roomInfo.begin() + 2));
			int roomYdim = stoi(*(roomInfo.begin() + 3));
			Room* roomPtr = new Room(roomName, roomXdim, roomYdim);
			
			roomPtr->setRoomDesc(roomDescription);
			

			/*string enemyName = *(enemyInfo.begin());
			int enemyHp = stoi(*(enemyInfo.begin() + 1));
			int enemyStrength = stoi(*(enemyInfo.begin() + 2));
			string weaponName = *(enemyInfo.begin() + 3);
			enemy* enemyPtr = new enemy(enemyName);

			knife* enemyWeapon = new knife();
			enemyPtr->setStrength(enemyStrength);
			enemyPtr->setHp(enemyHp);
			enemyPtr->setWeapon(enemyWeapon);
			roomPtr->addRoomEnemy(enemyPtr);*/
			//enemyPtrs.push_back(enemyPtr);

			map.addRoom(roomPtr);
			/*roomNames.push_back(*(roomInfo.begin()));
			cout << "room Names " << *(roomNames.begin()) << endl;
			roomDescriptions.push_back(*(roomInfo.begin()+1));
			cout << "room Descriptions " << *(roomDescriptions.begin()) << endl;*/

			delete[] charStopLine;
		}
		i++;
	}
}


void gameLoop(){
	string userControl;

	cout << "Enter Character name" << endl;
	string cName;
	cin >> cName;
	mainActor anActor(cName);
	gameMap map;
	renderMap(map);

	map.initializeMap();
	map.printBoard();
	
	while (userControl != "quit"){
		cout << "choose a direction" << endl;
		cin >> userControl;
		if (userControl == "left"){
			map.navigateLeft();
		}
		if (userControl == "right"){
			map.navigateRight();
			map.printBoard();
			
		}
		if (userControl == "forward"){
			map.navigateForward();
		}
		if (userControl == "back"){
		
			map.navigateBackward();
		}
	}
}

int main(){
	

	gameLoop();
	return 0;
}
