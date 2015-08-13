#include "gameboard.h"



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

	enemy* Room::getRoomEnemy(){
		return *(roomEnemies.begin());
	}
	void Room::addRoomHP(healthPack* hp){
		roomHealthPacks.push_back(hp);
	}
	void Room::addRoomWeapon(Weapon* weapon){
		roomWeapons.push_back(weapon);
	}
	bool Room::existPickups(){
		if (!roomWeapons.empty() && !roomHealthPacks.empty()){
			return true;
		}
		else{
			return false;
		}
	}
	string Room::getWeaponNames(){
		string weaponName;
		for (Weapon* eachWeapon : roomWeapons){
			weaponName = eachWeapon->getName();
		}
		return weaponName;
	}

	vector<healthPack*> Room::getRoomhps(){
		return roomHealthPacks;
	}
	vector<Weapon*> Room::getRoomWeapons(){
		return roomWeapons;
	}
	//void Room::addEvent(Event* anEvent){
	//	roomEvents.push_back(anEvent);
	//}



	void gameMap::initializeMap(){
		pair<int, int> position(0, 0);
		lastRoom.push(position);
		currentRow = 0;
		currentColumn = 0;

	}
	void gameMap::addGameUser(mainActor* userToAdd){
		user = userToAdd;
	}
	void gameMap::addRoom(Room* aRoom){
		int row = aRoom->currentPosition().first;
		int column = aRoom->currentPosition().second;
		gameBoard[row][column] = aRoom;
	}
	void gameMap::getNearbyRooms(int row, int column, Room* aRoom){
	
		if (row != 0 && gameBoard[row+1][column]->getRoomName() != "closed room "){
			string roomForwardName = gameBoard[row + 1][column]->getRoomName();
			pair<string, string> roomUpInfo(roomForwardName, "forward");
			roomVect.push_back(roomUpInfo);
		}
		/*if (row != 3 && gameBoard[row - 1][column]->getRoomName() != "closed room "){
			string roomBackwardsName = gameBoard[row-1][column]->getRoomName();
			pair<string, string> roomBackwardsInfo(roomBackwardsName, "backward");
			roomVect.push_back(roomBackwardsInfo);
		}*/
		if (column != 0 && gameBoard[row ][column -1 ]->getRoomName() != "closed room "){
			string roomLeftName = gameBoard[row][column-1]->getRoomName();
			pair<string, string> roomLeftInfo(roomLeftName, "left");
			roomVect.push_back(roomLeftInfo);
		}
		if (column != 3 && gameBoard[row][column + 1]->getRoomName() != "closed room "){
			string roomRightName = gameBoard[row][column+1]->getRoomName();
			pair<string, string> roomRightInfo(roomRightName, "Right");
			roomVect.push_back(roomRightInfo);
		}
		cout << "Available exits: " << endl;
		for (pair<string, string> eachPair : roomVect){
			cout << eachPair.second << ": " << eachPair.first << endl;
		}
		roomVect.clear();
	}
	//called when room is entered to display the room name, information, and nearby rooms
	void gameMap::enterRoom(Room* aRoom){
		//cout << "DEBUG:  enterRoom method entered" << endl;
		cout << "You are now in the " << aRoom->getRoomName()  << " room\n\n" << aRoom->getRoomDesc() <<"\n" << endl;
		/*for (pair<string, string> eachPair : roomVect){
			cout << "The room in the " << eachPair.second << " direction is the " << eachPair.first << " room " << endl;
		}*/
		getNearbyRooms(currentRow, currentColumn, aRoom);
		Room* currentRoom = gameBoard[currentRow][currentColumn];

		//checks to see if the room has anything to pick up as well as if the user has already gotten to the bedroom fight
		//and if so displays it and gives the option to pick it up
		if (currentRoom->existPickups() && bedroomVisited){
			char choice = '0';
			
			cout << "There is a helathPack in the cabinet and a " << currentRoom->getWeaponNames() << " in the corner. Press 'w' to pick up weapon, 'h' to pick up health pack, 'b' to pick up both, or 'i' to ignore" << endl;
			cin >> choice;
			vector<Weapon*> weapons = currentRoom->getRoomWeapons();
			vector<healthPack*> healthPacks = currentRoom->getRoomhps();
			switch (choice){
			case 'w':
				user->pickUpWeapon(*(weapons.begin()));
			case 'h':
				user->pickUpHP(*(healthPacks.begin()));
			case 'b':
				user->pickUpWeapon(*(weapons.begin()));
				user->pickUpHP(*(healthPacks.begin()));
			case 'i':
				break;
			default:
				break;
			}
			cout << "If you want to use the healthpack now, type 'u', otherwise, type 'n' " << endl;
			cin >> choice;
			switch (choice){
			case 'u':
				user->applyHealth();
				cout << "Your now have " << user->getActorHealth() << " health points \n\n" << endl;
				user->destroyHP(*(healthPacks.begin()));
			case 'n':
				break;
				cout << "\n\n" << endl;
			default:
				break;
			}
			
		}
		//if the user has reached the Bedroom, the combat simulation will begin
		if (currentRoom->getRoomName() == "Bedroom "){
			enemy* roomEnemy = currentRoom->getRoomEnemy();
			//time delay in seconds
			Sleep(3000);
			enemyCombatSim(roomEnemy, user);
			bedroomVisited = true;
		}
		
		//Once the user has gotten to the bedroom, the suspect can arrive in the foyer when the user returns there and the fight will begin
		if (bedroomVisited && currentRoom->getRoomName() == "foyer"){
			enemy* roomEnemy = currentRoom->getRoomEnemy();
			Sleep(3000);
			enemyCombatSim(roomEnemy, user);
		}

	}
	//used to moved to the left
	void gameMap::navigateLeft(){
		//checks to see if the user isn't already at the edge of the matrix or that they aren't trying to enter a closed room
		if (currentColumn != 0 && gameBoard[currentRow][currentColumn -1]->getRoomName() != "closed room "){
			--currentColumn;
			Room* currentRoom = gameBoard[currentRow][currentColumn];
			enterRoom(currentRoom);
			//coordinate pairs for the matrix position
			pair<int, int> position(currentRow, currentColumn);
			//stack used to allow the user to go to the previous room
			lastRoom.push(position);
		}
		else{
			cout << "You can't go in that direction" << endl;
		}
	}
	//enables the user to move right
	void gameMap::navigateRight(){
		
		//checks to see if the user isn't already at the edge of the matrix or that they aren't trying to enter a closed room
		if (currentColumn != 3 && gameBoard[currentRow][currentColumn + 1]->getRoomName() != "closed room "){
			Room* currentRoom = gameBoard[currentRow][currentColumn];
			//determines wheter or not to rotate the matrix -90 degrees depending on which room the user is currently in
			if (currentRoom->getRoomName() == "Inside your car " || currentRoom->getRoomName() == "Main Hallway "){
				rotateNegative90();
				
			}
			else{
				++currentColumn;
				enterRoom(gameBoard[currentRow][currentColumn]);
				pair<int, int> position(currentRow, currentColumn);
				lastRoom.push(position);

			}

			cout << "\ncurrent Row: " << currentRow << " column: " << currentColumn << endl;
			
					}
		else{
			cout << "You can't go in that direction" << endl;
		}
	}
	//enables the user to move forward
	void gameMap::navigateForward(){
		if (currentRow != 0 && gameBoard[currentRow - 1][currentColumn]->getRoomName() != "closed room "){
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
	//enables the user to move backward
	void gameMap::navigateBackward(){
		if (currentRow != 3){
			goBack();

		}
		else{
			cout << "You can't go in that direction" << endl;
		}
	}

	/*void gameMap::chooseUserDirection(string userInput){
		if (userInput == "left")navigateLeft();
		if (userInput == "right")navigateRight();
		if (userInput == "forward")navigateForward();
		if (userInput == "back")navigateBackward();
	}*/

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
				swap(gameBoard[i][j], gameBoard[j][i]);//transposes the matrix by switching the rows with the columns and the columns with the rows
		//swap(currentRow, currentColumn);

		for (int i = 0; i < n / 2; ++i)
			for (int j = 0; j < n; ++j)
				swap(gameBoard[i][j], gameBoard[n - 1 - i][j]);//inverts the matrix  rows

		for (int i = 0; i < n; ++i){
			for (int j = 0; j < n; ++j){
				if (lastRoom.top().first == 0 && lastRoom.top().second == 0){
					if (gameBoard[i][j]->getRoomName() == "foyer"){//finds the location of the foyer in the rotated matrix
						currentRow = i;
						currentColumn = j;
					}
				}
				else if (lastRoom.top().first == 2 && lastRoom.top().second == 1){
					if (gameBoard[i][j]->getRoomName() == "Upstairs hallway "){//finds the location of the upstairs hallway in the rotated matrix
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
		
	}
	//called when the user goes back downstairs to maintain continuity of the navigation system
	void gameMap::rotatePositive90(){
		int n = 4;
		for (int i = 0; i<n; ++i)
			for (int j = i + 1; j < n; ++j){
				swap(gameBoard[i][j], gameBoard[j][i]); //transposes the matrix
			
			}
		//printBoard();
		

		for (int i = 0; i < n; ++i){
			for (int j = 0; j < n / 2; ++j){
				//cout << "invert\n\n\n" << endl;
				//An alternative to using the swap function
				/*Room* temp = gameBoard[i][j];
				gameBoard[i][j] = gameBoard[i][n - 1 - j];
				gameBoard[i][n - 1 - j] = temp;*/

				swap(gameBoard[i][n - 1 - j], gameBoard[i][j]); //inverts the columns of the matrix
				
			}
		}
		//cout << " final matrix\n\n\n\n" << endl;
		//printBoard();
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
	
}
