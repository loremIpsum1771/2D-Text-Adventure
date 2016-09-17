#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include<vector>
#include<string>
#include<iostream>
#include<utility>
#include<stack>
#include "actors.h"
#include "combatSimulation.h"

using namespace std;

namespace textAdventure{
	class enemy;
	class mainActor;
	
	class Room{
		string roomName;
		string roomDescription;
		int roomRow;
		int roomColumn;
		vector<enemy*> roomEnemies;
		vector<healthPack*> roomHealthPacks;
		vector<Weapon*> roomWeapons;
	public:
		Room(string& rName, int row, int column);
		string getRoomDesc();
		string getRoomName();
		void addRoomEnemy(enemy* anEnemy);
		string getWeaponNames();
		vector<healthPack*> getRoomhps();
		vector<Weapon*> getRoomWeapons();
		bool existPickups();
		enemy* getRoomEnemy();
		void setRoomDesc(string description);
		pair<int, int> currentPosition();
		void addRoomHP(healthPack* hp);
		void addRoomWeapon(Weapon* weapon);
		void checkEvents();

	};

	class gameMap{
		mainActor* user;
		Room* gameBoard[4][4];
		int currentRow = 0;
		int currentColumn = 0;
		stack<pair<int, int>> lastRoom;
		bool movedBack = false;
		vector<pair<string, string>> roomVect;
		bool bedroomVisited = false;
	public:
		gameMap(){}
		void addGameUser(mainActor* userToAdd);
		void addRoom(Room* aRoom);
		void initializeMap();
		void getNearbyRooms(int row, int column, Room* aRoom);
		pair<int, int> getCoordinates();
		void enterRoom(Room* aRoom);
		void navigateLeft();
		void navigateRight();
		void navigateForward();
		void navigateBackward();
		void chooseUserDirection(string userInput);
		void setCurrentPosition(int curRow, int curColumn);
		void rotateNegative90();
		void rotatePositive90();
		void printBoard();
		pair<int, int> getCurrentPosition();
		Room* roomAtPosition(int row, int column);
		void goBack();
	};

}


#endif	 
