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
	void Room::addRoomEnemy(enemy* anEnemy){
		roomEnemies.push_back(anEnemy);
	}
	pair<int, int> Room::currentPosition(){
		pair<int, int> coordinates(roomRow, roomColumn);
		return coordinates;
	}

	void gameMap::initializeMap(){
		pair<int, int> position(0, 0);
		lastRoom.push(position);
		currentRow = 0;
		currentColumn = 0;

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
			pair<int, int> position(currentRow, currentColumn);
			lastRoom.push(position);

		}
		else{
			cout << "You can't go in that direction" << endl;
		}
	}

	void gameMap::navigateRight(){
		//bool rotate = false;
		if (currentColumn != 3){
			/*if (!movedBack){
				setCurrentPosition(currentRow, ++currentColumn);
				Room* currentRoom = gameBoard[currentRow][currentCol]9543   umn];
				enterRoom(currentRoom);
				pair<int, int> position(currentRow, currentColumn);
				lastRoom.push(position);
			}*/
			Room* currentRoom = gameBoard[currentRow][currentColumn];
			if (currentRoom->getRoomName() == "Inside your car " || currentRoom->getRoomName() == "Main Hallway "){
				rotateNegative90();
				//rotate = true;
			}
			else{
				++currentColumn;
				enterRoom(gameBoard[currentRow][currentColumn]);
				pair<int, int> position(currentRow, currentColumn);
				lastRoom.push(position);

			}

			cout << "current Row: " << currentRow << " column: " << currentColumn << endl;
			if (currentRoom->getRoomName() == "Spawn Point4"){ 
				//cout << "Board after move to spawn point 4\n" << endl; 
				//cout << "current Row: " << currentRow << " column: " << currentColumn << endl;
				//printBoard(); 
			}
			//if (!rotate){
				
			//}
			//rotate = false;
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
			pair<int, int> position(currentRow, currentColumn);
			lastRoom.push(position);

		}
		else{
			cout << "You can't go in that direction" << endl;
		}
	}
	void gameMap::navigateBackward(){
		if (currentRow != 3){
			
			goBack();
			
			/*++currentRow;
			Room* currentRoom = gameBoard[currentRow][currentColumn];
			enterRoom(currentRoom);
			pair<int, int> position(currentRow, currentColumn);
			lastRoom.push(position);
*/

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
	void gameMap::printBoard(){
		for (int i = 0; i<4; ++i){
			for (int j = 0; j<4; ++j)
				cout << gameBoard[i][j]->getRoomName() << " ";
			cout << endl;
		}
		cout << endl;
	}
	void gameMap::rotateNegative90(){
		movedBack = false;
		int n = 4;
		for (int i = 0; i<n; ++i)
			for (int j = i + 1; j<n; ++j)
				swap(gameBoard[i][j], gameBoard[j][i]);
		swap(currentRow, currentColumn);
		
		for (int i = 0; i < n / 2; ++i)
			for (int j = 0; j < n; ++j)
				swap(gameBoard[i][j], gameBoard[n - 1 - i][j]);
				
		for (int i = 0; i < n; ++i){
			for (int j = 0; j < n; ++j){
				if (lastRoom.top().first == 0 && lastRoom.top().second == 0){
					if (gameBoard[i][j]->getRoomName() == "foyer"){
						currentRow = i;
						currentColumn = j;
					}
				}
				else if (lastRoom.top().first == 2 && lastRoom.top().second == 1){
					if (gameBoard[i][j]->getRoomName() == "Upstairs hallway "){
						currentRow = i;
						currentColumn = j;
					}
				}
			}
		}
		Room* currentRoom = gameBoard[currentRow][currentColumn];
		enterRoom(currentRoom);

		
		pair<int, int> position(currentRow, currentColumn);
		lastRoom.push(position);
		/*cout << " final currentRow " << currentRow << "final currentColumn " << currentColumn <<  endl;
		printBoard();*/
	}

	void gameMap::rotatePositive90(){
		int n = 4;
		for (int i = 0; i<n; ++i)
			for (int j = i + 1; j < n; ++j){
				cout << "transpose\n\n\n" << endl;
				swap(gameBoard[i][j], gameBoard[j][i]);
				cout << gameBoard[i][j]->getRoomName() << " -> " << gameBoard[j][i]->getRoomName() << "\n" ;
			}
		printBoard();
		//swap(currentRow, currentColumn);

		for (int i = 0; i < n ; ++i){
			for (int j = 0; j < n/2; ++j){
				cout << "invert\n\n\n" << endl;
				/*Room* temp = gameBoard[i][j];
				gameBoard[i][j] = gameBoard[i][n - 1 - j];
				gameBoard[i][n - 1 - j] = temp;*/
				swap(gameBoard[i][n - 1 - j], gameBoard[i][j]);
				//cout << gameBoard[i][j]->getRoomName() << " -> " << gameBoard[j][n - 1 - j]->getRoomName() << "\n";
			}
		}
		cout << " final matrix\n\n\n\n" << endl;
		printBoard();
		for (int i = 0; i < n; ++i){
			for (int j = 0; j < n; ++j){
				if (lastRoom.top().first == 0 && lastRoom.top().second == 0){
					if (gameBoard[i][j]->getRoomName() == "foyer"){
						currentRow = i;
						currentColumn = j;
					}
				}
				else if (lastRoom.top().first == 2 && lastRoom.top().second == 2){
					if (gameBoard[i][j]->getRoomName() == "Upstairs hallway "){
						int hallwayRow = i;
						int hallwayColumn = j;
					}
				}
			}
		}
		
		/*pair<int, int> position(currentRow, currentColumn );
		lastRoom.push(position);
		*/
		
	}
	void gameMap::goBack(){
		Room* currentRoom = gameBoard[currentRow][currentColumn];
		/*if (currentRoom->getRoomName() == "foyer"){
			cout << "Why are you back in your car? You can't leave yet!" << endl;
			
		}*/
		movedBack = true;
		lastRoom.pop();
		
		if (currentRoom->getRoomName() == "Inside Your Car")return;
		if (currentRoom->getRoomName() == "foyer" || currentRoom->getRoomName() == "Upstairs hallway "){ 
			rotatePositive90(); 
		}
		currentRow = lastRoom.top().first;
		currentColumn = lastRoom.top().second;
		Room* previousRoom = gameBoard[currentRow][currentColumn];
		enterRoom(previousRoom);
		printBoard();
	}

	pair<int, int> gameMap::getCurrentPosition(){
		pair<int, int> position(currentRow, currentColumn);
		return position;
	}
	/*void transpose(int a[][4], int n){
		for (int i = 0; i<n; ++i)
			for (int j = i + 1; j<n; ++j)
				swap(a[i][j], a[j][i]);
		printBoard();
		for (int i = 0; i<n / 2; ++i)
			for (int j = 0; j<n; ++j)
				swap(a[i][j], a[n - 1 - i][j]);
		printMatrix(a);
	}*/
}
