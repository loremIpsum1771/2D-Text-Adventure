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

void renderMap(vector<string> roomNames, vector<string> roomDescriptions){
	ifstream txtFile("adventureExposition.txt");
	if (!txtFile) { cerr << "File not found"; return; }
	string fileLine;
	getline(txtFile, fileLine);

	while (getline(txtFile, fileLine)) {
		vector<string> roomInfo;
		char delim[] = "|";
		char* charStopLine = new char[fileLine.size() + 1];
		strcpy(charStopLine, fileLine.c_str());

		tokenizer(charStopLine, roomInfo, delim);
		roomNames.push_back(*(roomInfo.begin()));
		cout << "room Names " << *(roomNames.begin()) << endl;
		roomDescriptions.push_back(*(roomInfo.begin()+1));
		cout << "room Descriptions " << *(roomDescriptions.begin()) << endl;
		roomInfo.pop_back();
		roomInfo.pop_back();
		delete[] charStopLine;
	}

}
void gameLoop(){
	string userControl;

	cout << "Enter Character name" << endl;
	string cName;
	cin >> cName;
	mainActor anActor(cName);
	gameMap map;

	string roomName1 = "Spawn Point1";

	//Room room1(roomName1,0,0);
	Room* room1Ptr = new Room(roomName1, 0, 0);

	map.addRoom(room1Ptr);
	room1Ptr->setRoomDesc("this is spawn point 1");

	string roomName2 = "Spawn Point2";
	Room* room2Ptr = new Room(roomName2, 0, 1);

	map.addRoom(room2Ptr);
	room2Ptr->setRoomDesc("this is spawn point 2");

	string roomName3 = "Spawn Point3";
	Room* room3Ptr = new Room(roomName3, 1, 0);
	map.addRoom(room3Ptr);
	room3Ptr->setRoomDesc("this is spawn point 3");

	string roomName4 = "Spawn Point4";
	Room* room4Ptr = new Room(roomName4, 1, 1);
	map.addRoom(room4Ptr);
	room4Ptr->setRoomDesc("this is spawn point 4");

	/*string roomName5 = "Spawn Point5";
	Room* room5Ptr = new Room(roomName5, 1, 0);
	map.addRoom(room5Ptr);
	room5Ptr->setRoomDesc("this is spawn point 5");

	string roomName6 = "Spawn Point6";
	Room* room6Ptr = new Room(roomName6, 2, 0);
	map.addRoom(room6Ptr);
	room6Ptr->setRoomDesc("this is spawn point 6");*/
	map.setCurrentPosition(0, 0);
	while (userControl != "quit"){
		cout << "choose a direction" << endl;
		cin >> userControl;
		if (userControl == "left"){
			map.navigateLeft();
		}
		if (userControl == "right"){
			map.navigateRight();
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
	vector<string> roomNames;
	vector<string> roomDescriptions;
	renderMap(roomNames, roomDescriptions);
	//gameLoop();
	return 0;
}
