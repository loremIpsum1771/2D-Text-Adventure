#include "gameboard.h"
#include "actors.h"


namespace textAdventure{
	Room::Room(string& rName, int row, int column) : roomName(rName) {
		roomRow = row;
		roomColumn = column;
	}
	string Room::getRoomDesc(){
		return roomDescription;
	}

	string Room::getRoomName(){	
		return roomName;
	}

	void Room::setRoomDesc(string description){
		roomDescription = description;
	}
	void Room::addRoomEnemy(enemy& anEnemy){
		roomEnemies.push_back(anEnemy);
	}
	pair<int, int> Room::currentPosition(){
		pair<int, int> coordinates(roomRow, roomColumn);
		return coordinates;
	}


	void gameMap::addRoom(Room* aRoom){
		int row = aRoom->currentPosition().first;
		int column = aRoom->currentPosition().second;
		gameBoard[row][column] = aRoom;
	}
	void gameMap::getNearbyRooms(int row, int column, Room* aRoom){
		if (row != 0){
			string roomForwardName = gameBoard[++row][column]->getRoomName();
			pair<string, string> roomUpInfo(roomForwardName, "forward");
			roomVect.push_back(roomUpInfo);
		}
		if (row != 3){
			string roomBackwardsName = gameBoard[--row][column]->getRoomName();
			pair<string, string> roomBackwardsInfo(roomBackwardsName, "backward");
			roomVect.push_back(roomBackwardsInfo);
		}
		if (column != 0){
			string roomLeftName = gameBoard[row][--column]->getRoomName( );
			pair<string, string> roomLeftInfo(roomLeftName, "left");
			roomVect.push_back(roomLeftInfo);
		}
		if (column != 3){
			string roomRightName = gameBoard[row][++column]->getRoomName( );
			pair<string, string> roomRightInfo(roomRightName, "Right");
			roomVect.push_back(roomRightInfo);
		}
	}
	void gameMap::enterRoom(Room* aRoom){
		//getNearbyRooms(currentRow, currentColumn, aRoom);
		cout << "DEBUG:  enterRoom method entered" << endl;
		cout << "You are now in the " << aRoom->getRoomName() << endl << " room\n" << aRoom->getRoomDesc() << endl;
		for (pair<string, string> eachPair : roomVect){
			cout << "The room in the " << eachPair.second << " direction is the " << eachPair.first << " room " << endl;
		}
	}

	void gameMap::navigateLeft(){
		if (currentColumn != 0){
			--currentColumn;
			Room* currentRoom = gameBoard[currentRow][currentColumn];
			enterRoom(currentRoom);
		}
		else{
			cout << "You can't go in that direction" << endl;
		}
	}

	void gameMap::navigateRight(){
		if (currentColumn != 3){
			++currentColumn;
			Room* currentRoom = gameBoard[currentRow][currentColumn];

			enterRoom(currentRoom);
		}
		else{
			cout << "You can't go in that direction" << endl;
		}
	}
	void gameMap::navigateForward(){
		if (currentRow != 0){
			--currentRow;
			Room* currentRoom = gameBoard[currentRow][currentColumn];
			enterRoom(currentRoom);
		}
		else{
			cout << "You can't go in that direction" << endl;
		}
	}
	void gameMap::navigateBackward(){
		if (currentRow != 3){
			++currentRow;
			Room* currentRoom = gameBoard[currentRow][currentColumn];
			enterRoom(currentRoom);
		}
		else{
			cout << "You can't go in that direction" << endl;
		}
	}

	void gameMap::chooseUserDirection(string userInput){
		if (userInput == "left")navigateLeft();
		if (userInput == "right")navigateRight();
		if (userInput == "forward")navigateForward();
		if (userInput == "back")navigateBackward();
	}

	void gameMap::setCurrentPosition(int curRow, int curColumn){
		currentRow = curRow;
		currentColumn = curColumn;
	}
	Room* gameMap::roomAtPosition(int row, int col){

		Room* room = gameBoard[row][col];
		return room;
	}
}
