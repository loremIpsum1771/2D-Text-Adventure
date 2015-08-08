#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include<vector>
#include<string>
#include<iostream>
#include<utility>
#include<stack>
#include "actors.h"
using namespace std;

namespace textAdventure{
	class enemy;
	class Room{
		string roomName;
		string roomDescription;
		int roomRow;
		int roomColumn;
		vector<enemy*> roomEnemies;
	public:
		Room(string& rName, int row, int column);
		string getRoomDesc();
		string getRoomName();
		void addRoomEnemy(enemy* anEnemy);
		void setRoomDesc(string description);
		pair<int, int> currentPosition();
		

		
	};
	class gameMap{

		//vector< vector<Room>> gameBoard;
		Room* gameBoard[4][4];
		int currentRow = 0;
		int currentColumn = 0;
		stack<pair<int, int>> lastRoom;
		bool movedBack = false;
		vector<pair<string, string>> roomVect;
	public:
		gameMap(){}
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
		//void setMapSize(int row, int column);
		
	};

}


#endif	 
