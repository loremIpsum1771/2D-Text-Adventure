#include "actors.h"
#include "gameboard.h"
#include "inventory.h"
#include<iostream>
#include<vector>
#include<string>

using namespace std;
using namespace textAdventure;
	

void gameLoop(){
	string userControl;
	cin >> userControl;
	while (userControl != "quit"){
		cout << "Enter Character name" << endl;
		string cName;
		cin >> cName;
		mainActor anActor(cName);
		gameMap map;
		string roomName1 = "Spawn Point1";
		Room room1(roomName1,0,0);
		room1.setRoomDesc("this is spawn point 1");
		string roomName2 = "Spawn Point2";
		Room room2(roomName2, 0, 1);
		room1.setRoomDesc("this is spawn point 2");
		string roomName3 = "Spawn Point3";
		Room room3(roomName3, 0, 2);
		room1.setRoomDesc("this is spawn point 3");
		string roomName4 = "Spawn Point4";
		Room room4(roomName4, 0, 3);
		room1.setRoomDesc("this is spawn point 4");
		string roomName5 = "Spawn Point5";
		Room room5(roomName5, 1, 0);
		room1.setRoomDesc("this is spawn point 5");
		string roomName6 = "Spawn Point6";
		Room room6(roomName6, 2, 0);
		room1.setRoomDesc("this is spawn point 6");
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
	gameLoop();
	return 0;
}
