/**
 @file   Database.cpp
 @author Pedro Américo Toledano López
 @date   August, 2015
 @brief  Class to handle the database, using SQLite3.
*/

#include "Database.h"

#include <sqlite3.h> // Include for SQLite
#include <sstream> // Include for string type
#include <cstring>
#include <cstdlib> // Include for atoi() function

using namespace std;


/**
 Constructor
*/
Database::Database()
{
	// Opens the database everytime an object is declarated
	openDatabase();
	// Creates the tables of the database if they do not exist yet
	createTables();
}

/**
 Destructor.
*/
Database::~Database()
{
	// Closes the database
	closeDatabase();
}


/**
 Opens the database and creates a database connection. If the database file does not exist, it is created.

 @return True if the database was opened successfully, false if it failed.
*/
bool Database::openDatabase()
{
	// Opens the database saved in the file 'database.db'
	rc = sqlite3_open("database.db", &db);

	if ( rc != SQLITE_OK )
		return false;

	return true;
}


/**
 Closes the database.
*/
void Database::closeDatabase()
{
	do
	{
		// Destroys the sqlite3 object
		rc = sqlite3_close(db);
	}while(rc == SQLITE_BUSY); // If the database connection has outstanding statements, then tries again.
}



/**
 Creates the tables of the database if they do not exist yet.

 @return True if the tables were created successfully, false otherwise.
*/
bool Database::createTables()
{
	// SQL statement to create the 'users' table
	const char *statement = "CREATE TABLE IF NOT EXISTS USERS ("  \
		"ID                     TEXT PRIMARY KEY UNIQUE    NOT NULL," \
		"NAME                   TEXT                       NOT NULL," \
		"TOTAL_SUCCESSES		INTEGER DEFAULT 0," \
		"TOTAL_FAILURES			INTEGER DEFAULT 0);";

	// Runs the previous SQL statement
	rc = sqlite3_exec(db, statement, 0, 0, NULL);

	if ( rc != SQLITE_OK )
		return false;


	// SQL statement to create the 'specialists' table
	statement = "CREATE TABLE IF NOT EXISTS SPECIALISTS ("  \
		"ID                     TEXT PRIMARY KEY UNIQUE    NOT NULL," \
		"NAME                   TEXT                       NOT NULL," \
		"SPECIALTY              TEXT DEFAULT 'No especificado');";

	// Runs the previous SQL statement
	rc = sqlite3_exec(db, statement, 0, 0, NULL);

	if( rc != SQLITE_OK )
		return false;


	// SQL statement to create the 'user_specialist' table
	statement = "CREATE TABLE IF NOT EXISTS USER_SPECIALIST ("  \
		"USER_ID             TEXT      " \
		"REFERENCES USERS(ID) ON DELETE CASCADE ON UPDATE CASCADE," \
		"SPECIALIST_ID          TEXT      " \
		"REFERENCES SPECIALISTS(ID) ON DELETE CASCADE ON UPDATE CASCADE," \
		"PRIMARY KEY(USER_ID, SPECIALIST_ID));";

	// Runs the previous SQL statement
	rc = sqlite3_exec(db, statement, 0, 0, NULL);

	if( rc != SQLITE_OK )
		return false;


	// SQL statement to create the 'games' table
	statement = "CREATE TABLE IF NOT EXISTS GAMES ("  \
		"GAME_ID                INT PRIMARY KEY," \
		"USER_ID                TEXT " \
		"REFERENCES USERS(ID) ON DELETE CASCADE ON UPDATE CASCADE," \
		"START_DATE             TEXT                       NOT NULL," \
		"END_DATE               TEXT                       NOT NULL," \
		"SUCCESSES              INT                        NOT NULL," \
		"FAILURES               INT                        NOT NULL);";

	// Runs the previous SQL statement
	rc = sqlite3_exec(db, statement, 0, 0, NULL);

	if( rc != SQLITE_OK )
		return false;


	// SQL statement to create the 'game_data' table
	statement = "CREATE TABLE IF NOT EXISTS GAME_DATA ("  \
		"TIME                    CURRENT_TIMESTAMP PRIMARY KEY," \
		"GAME_ID                 INT " \
		"REFERENCES GAME(GAME_ID) ON DELETE CASCADE ON UPDATE CASCADE," \
		"JOINT_HEAD_X            REAL               NOT NULL," \
		"JOINT_HEAD_Y            REAL               NOT NULL," \
		"JOINT_NECK_X            REAL               NOT NULL," \
		"JOINT_NECK_Y            REAL               NOT NULL," \
		"JOINT_LEFT_SHOULDER_X   REAL               NOT NULL," \
		"JOINT_LEFT_SHOULDER_Y   REAL               NOT NULL," \
		"JOINT_RIGHT_SHOULDER_X  REAL               NOT NULL," \
		"JOINT_RIGHT_SHOULDER_Y  REAL               NOT NULL," \
		"JOINT_LEFT_ELBOW_X      REAL               NOT NULL," \
		"JOINT_LEFT_ELBOW_Y      REAL               NOT NULL," \
		"JOINT_RIGHT_ELBOW_X     REAL               NOT NULL," \
		"JOINT_RIGHT_ELBOW_Y     REAL               NOT NULL," \
		"JOINT_LEFT_HAND_X       REAL               NOT NULL," \
		"JOINT_LEFT_HAND_Y       REAL               NOT NULL," \
		"JOINT_RIGHT_HAND_X      REAL               NOT NULL," \
		"JOINT_RIGHT_HAND_Y      REAL               NOT NULL," \
		"JOINT_LEFT_HIP_X        REAL               NOT NULL," \
		"JOINT_LEFT_HIP_Y        REAL               NOT NULL," \
		"JOINT_RIGHT_HIP_X       REAL               NOT NULL," \
		"JOINT_RIGHT_HIP_Y       REAL               NOT NULL," \
		"FRUIT_X                 REAL               NOT NULL," \
		"FRUIT_Y                 REAL               NOT NULL);";

	// Runs the previous SQL statement
	rc = sqlite3_exec(db, statement, 0, 0, NULL);

	if( rc != SQLITE_OK )
		return false;


	return true;
}


/**
 Inserts a new user in the database.

 @param id [in] Identification number of the user.
 @param name [in] Name of the user.

 @return A @ref DatabaseMessage to report if the operation was successful or if any type of error happen.
*/
DatabaseMessage Database::insertUser(string id, string name)
{
	name = upperFirstLetter(name);

	if( id.empty() || name.empty() )
	{
		return FORMAT_ERROR;
	}
	else
	{
		// SQL statement to insert a user into the 'users' table
		string statement = "INSERT INTO USERS (ID, NAME) VALUES ('"+id+"', '"+name+"');";

		// Runs the previous SQL statement
		rc = sqlite3_exec(db, statement.c_str(), 0, 0, NULL);
	}

	if( rc != SQLITE_OK )
		return ERROR;

	return OK;
}


/**
 Inserts a new specialist in the database.

 @param id [in] Identification number of the specialist.
 @param name [in] Name of the specialist.
 @param specialty [in] Type of specialty.

 @return A @ref DatabaseMessage to report if the operation was successful or if any type of error happen.
*/
DatabaseMessage Database::insertSpecialist(string id, string name, string specialty)
{
	// Uppercases the first letter of every word
	name = upperFirstLetter(name);
	specialty = upperFirstLetter(specialty);

	// If the data are empty
	if( id.empty() || name.empty() )
	{
		return FORMAT_ERROR;
	}
	else
	{
		// If no specialty has been specified
		if( specialty.empty() )
			specialty = "No especificado";

		// SQL statement to insert a specialist into the 'specialists' table
		string statement = "INSERT INTO SPECIALISTS (ID, NAME, SPECIALTY) VALUES ('"+id+"', '"+name+"', '"+specialty+"');";

		// Runs the previous SQL statement
		rc = sqlite3_exec(db, statement.c_str(), 0, 0, NULL);
	}

	if( rc != SQLITE_OK )
		return ERROR;

	return OK;
}


/**
 Inserts a new game in the database.

 @param userId [in] Identification number of the game user.
 @param startDate [in] Start date of the game.
 @param endDate [in] End date of the game.
 @param successes [in] Score of successes.
 @param failures [in] Score of failures.

 @return True if game was inserted successfully, false otherwise.
*/
bool Database::insertGame(string userId, string startDate, string endDate, int successes, int failures)
{
	int gameID;

	// Gets the game ID. The game ID is selected according to the number of position in the 'games' table.
	getGameTableSize(gameID);

	// SQL statement to insert a game into the 'games' table
	string statement = "INSERT INTO GAMES (GAME_ID, USER_ID, START_DATE, END_DATE, SUCCESSES, FAILURES) VALUES ('"+itos(gameID)+"', '"+userId+"', '"+startDate+"', '"+endDate+"', '"+itos(successes)+"', '"+itos(failures)+"');";

	// Runs the previous SQL statement
	rc = sqlite3_exec(db, statement.c_str(), 0, 0, NULL);

	if( rc != SQLITE_OK )
		return false;

	return true;
}



/**
 Inserts a new record with the data of a game in a particular time.

 @param [in] time A particular time of the game in seconds.
 @param [in] gameId ID number of the game.
 @param [in] fruitX X coordinate of the fruit.
 @param [in] fruitY Y coordinate of the fruit.
 @param [in] headX X coordinate of the joint of the head.
 @param [in] headY Y coordinate of the joint of the head.
 @param [in] neckX X coordinate of the joint of the neck.
 @param [in] neckY Y coordinate of the joint of the neck.
 @param [in] leftShoulderX X coordinate of the joint of the left shoulder.
 @param [in] leftShoulderY Y coordinate of the joint of the left shoulder.
 @param [in] rightShoulderX X coordinate of the joint of the right shoulder.
 @param [in] rightShoulderY Y coordinate of the joint of the right shoulder.
 @param [in] leftElbowX X coordinate of the joint of the left elbow.
 @param [in] leftElbowY Y coordinate of the joint of the left elbow.
 @param [in] rightElbowX X coordinate of the joint of the right elbow.
 @param [in] rightElbowY Y coordinate of the joint of the right elbow.
 @param [in] leftHandX X coordinate of the joint of the left hand.
 @param [in] leftHandY Y coordinate of the joint of the left hand.
 @param [in] rightHandX X coordinate of the joint of the right hand.
 @param [in] rightHandY Y coordinate of the joint of the right hand.
 @param [in] leftHipX X coordinate of the joint of the left hip.
 @param [in] leftHipY Y coordinate of the joint of the left hip.
 @param [in] rightHipX X coordinate of the joint of the right hip.
 @param [in] rightHipY Y coordinate of the joint of the right hip.

 @return True if the record was inserted successfully, false otherwise.
*/
bool Database::insertGameData(int time, int gameId, float fruitX, float fruitY, float headX, float headY, float neckX, float neckY, float leftShoulderX, float leftShoulderY, float rightShoulderX, float rightShoulderY, float leftElbowX, float leftElbowY, float rightElbowX, float rightElbowY, float leftHandX, float leftHandY, float rightHandX, float rightHandY, float leftHipX, float leftHipY, float rightHipX, float rightHipY)
{
	// SQL statement to insert a new record into 'game_data' table
	string statement = "INSERT INTO GAME_DATA (TIME, GAME_ID, JOINT_HEAD_X, JOINT_HEAD_Y, JOINT_NECK_X, JOINT_NECK_Y, JOINT_LEFT_SHOULDER_X, JOINT_LEFT_SHOULDER_Y, JOINT_RIGHT_SHOULDER_X, JOINT_RIGHT_SHOULDER_Y, JOINT_LEFT_ELBOW_X, JOINT_LEFT_ELBOW_Y, JOINT_RIGHT_ELBOW_X, JOINT_RIGHT_ELBOW_Y, JOINT_LEFT_HAND_X, JOINT_LEFT_HAND_Y, JOINT_RIGHT_HAND_X, JOINT_RIGHT_HAND_Y, JOINT_LEFT_HIP_X, JOINT_LEFT_HIP_Y, JOINT_RIGHT_HIP_X, JOINT_RIGHT_HIP_Y, FRUIT_X, FRUIT_Y) VALUES ('"+itos(time)+"', '"+itos(gameId)+"', '"+ftos(headX)+"', '"+ftos(headY)+"', '"+ftos(neckX)+"', '"+ftos(neckY)+"', '"+ftos(leftShoulderX)+"', '"+ftos(leftShoulderY)+"', '"+ftos(rightShoulderX)+"', '"+ftos(rightShoulderY)+"', '"+ftos(leftElbowX)+"', '"+ftos(leftElbowY)+"', '"+ftos(rightElbowX)+"', '"+ftos(rightElbowY)+"', '"+ftos(leftHandX)+"', '"+ftos(leftHandY)+"', '"+ftos(rightHandX)+"', '"+ftos(rightHandY)+"', '"+ftos(leftHipX)+"', '"+ftos(leftHipY)+"', '"+ftos(rightHipX)+"', '"+ftos(rightHipY)+"', '"+ftos(fruitX)+"', '"+ftos(fruitY)+"');";

	// Runs the previous SQL statement
	rc = sqlite3_exec(db, statement.c_str(), 0, 0, NULL);

	if( rc != SQLITE_OK )
		return false;

	return true;
}


/**
 Links an user and a specialist in the 'user_specialist' table of the database.

 @param userId [in] Identification number of the user.
 @param specialistId [in] Identification number of the specialist.

 @return A @ref DatabaseMessage to report if the operation was successful or if any type of error happen.
*/
DatabaseMessage Database::insertLinkUserSpecialist(string userId, string specialistId)
{
	// If the data are empty
	if( userId.empty() || specialistId.empty() )
	{
		return FORMAT_ERROR;
	}
	else
	{
		// SQL statement to insert in the 'user_specialist' table a link between an user and a specialist
		string statement = "INSERT INTO USER_SPECIALIST (USER_ID, SPECIALIST_ID) VALUES ('"+userId+"', '"+specialistId+"');";

		// Runs the previous SQL statement
		rc = sqlite3_exec(db, statement.c_str(), 0, 0, NULL);
	}

	if( rc != SQLITE_OK )
		return ERROR;

	return OK;
}


/**
 Deletes a user from the database, given its id.

 @param id [in] Identification number of the user.

 @return A @ref DatabaseMessage to report if the operation was successful or if any type of error happen.
*/
DatabaseMessage Database::deleteUser(string id)
{
	// If the data is empty
	if( id.empty() )
	{
		return FORMAT_ERROR;
	}
	else
	{
		// SQL statement to delete a user given its id
		string statement = "DELETE FROM USERS WHERE ID='" + id + "';";

		// Runs the previous SQL statement
		rc = sqlite3_exec(db, statement.c_str(), NULL, NULL, NULL);
	}

	if( rc != SQLITE_OK )
		return ERROR;

	return OK;
}


/**
 Deletes a specialist from the database, given its id.

 @param id [in] Identification number of the specialist.

 @return A @ref DatabaseMessage to report if the operation was successful or if any type of error happen.
*/
DatabaseMessage Database::deleteSpecialist(string id)
{
	// If the data is empty
	if( id.empty() )
	{
		return FORMAT_ERROR;
	}
	else
	{
		// SQL statement to delete a specialist given its id
		string statement = "DELETE FROM SPECIALISTS WHERE ID='" + id + "';";

		// Runs the previous SQL statement
		rc = sqlite3_exec(db, statement.c_str(), NULL, NULL, NULL);
	}

	if( rc != SQLITE_OK )
		return ERROR;

	return OK;
}


/**
 Unlinks an user and a specialist in the 'user_specialist' table of the database.

 @param userId [in] Identification number of the user.
 @param specialistId [in] Identification number of the specialist.

 @return A @ref DatabaseMessage to report if the operation was successful or if any type of error happen.
*/
DatabaseMessage Database::deleteLinkUserSpecialist(string userId, string specialistId)
{
	int num;

	// If the data are empty
	if( userId.empty() || specialistId.empty() )
	{
		return FORMAT_ERROR;
	}
	else
	{
		// SQL statement to count how many rows can be deleted
		string statement = "SELECT count(*) FROM USER_SPECIALIST WHERE USER_ID='"+userId+"' AND SPECIALIST_ID='"+specialistId+"';";

		// Runs the previous SQL statement
		rc = sqlite3_exec(db, statement.c_str(), callbackCountOperation, &num, NULL);

		// If there is a row to delete
		if( num > 0 )
		{
			// SQL statement to delete from the 'user_specialist' table a link between an user and a specialist
			string statement = "DELETE FROM USER_SPECIALIST WHERE USER_ID='"+userId+"' AND SPECIALIST_ID='"+specialistId+"';";

			// Runs the previous SQL statement
			rc = sqlite3_exec(db, statement.c_str(), 0, 0, NULL);
		}
		else
		{
			return ERROR;
		}
	}

	if( rc != SQLITE_OK )
		return ERROR;

	return OK;
}


/**
 Updates any value for any user in 'users' table, given the user ID, the name of the column to update and the new value.

 @param id [in] Identification number of the user to update.
 @param column [in] Column name in the 'users' table to update.
 @param value [in] New value for the column of the user indicated.

 @return A @ref DatabaseMessage to report if the operation was successful or if any type of error happen.
*/
DatabaseMessage Database::updateUser(string id, string column, string value)
{
	// If the data is empty
	if( id.empty() || column.empty() || value.empty() )
	{
		return FORMAT_ERROR;
	}
	else
	{
		// SQL statement to update a user given the user ID, the column to update and the new value
		string statement = "UPDATE USERS SET " + column + " = '" + value + "' WHERE ID='" + id + "';";

		// Runs the previous SQL statement
		rc = sqlite3_exec(db, statement.c_str(), NULL, NULL, NULL);
	}

	if( rc != SQLITE_OK )
		return ERROR;

	return OK;
}


/**
 Updates the name of a user in the database, given the user ID.

 @param id [in] ID of the user.
 @param userName [in] New name of the user.

 @return A @ref DatabaseMessage to report if the operation was successful or if any type of error happen.
*/
DatabaseMessage Database::updateUserName(string id, string userName)
{
	return( updateUser(id, "NAME", userName) );
}



/**
 Updates the identification number (ID) of a user in the database, given its current ID.

 @param id [in] Identification number of the user.
 @param newId [in] New id of the user.

 @return A @ref DatabaseMessage to report if the operation was successful or if any type of error happen.
*/
DatabaseMessage Database::updateUserId(string id, string newId)
{
	return( updateUser(id, "ID", newId) );
}


/**
 Updates the score (successes and failures) of a user, given its ID

 @param id [in] Identification number of the user.
 @param successes [in] Number of successes in the game.
 @param failures [in] Number of failures in the game.

 @return Nothing
*/
void Database::updateUserTotalScore(string id, int successes, int failures)
{
	User user;

	// Gets the data of the user
	getUserById(id, user);

	// Sums the successes and failures in the user data
	updateUser(id, "TOTAL_SUCCESSES", itos(user.successes + successes));
	updateUser(id, "TOTAL_FAILURES", itos(user.failures + failures));
}


/**
 Updates any value for any specialist in "specialists" table.

 @param id [in] Identification number of the specialist to update.
 @param column [in] Column name in the "specialists" table to update.
 @param value [in] New value for the column of the specialist indicated.

 @return A @ref DatabaseMessage to report if the operation was successful or if any type of error happen.
*/
DatabaseMessage Database::updateSpecialist(string id, string column, string value)
{
	// If the data are empty
	if( id.empty() || column.empty() || value.empty() )	
	{
		return FORMAT_ERROR;
	}
	else
	{
		// SQL statement to update a specialist given the specialist ID, the column to update and the new value
		string statement = "UPDATE SPECIALISTS SET " + column + " = '" + value + "' WHERE ID='" + id + "';";

		// Runs the previous SQL statement
		rc = sqlite3_exec(db, statement.c_str(), NULL, NULL, NULL);
	}

	if( rc != SQLITE_OK )
		return ERROR;

	return OK;
}


/**
 Updates a specialist name in the database, given the specialist ID.

 @param id [in] Identification number of the specialist.
 @param patientName [in] New name of the specialist.

 @return A @ref DatabaseMessage to report if the operation was successful or if any type of error happen.
*/
DatabaseMessage Database::updateSpecialistName(string id, string userName)
{
	return( updateSpecialist(id, "NAME", userName) );
}



/**
 Updates the identification number (ID) of a specialist in the database, given its current ID.

 @param id [in] Identification number of the specialist.
 @param newId [in] New id of the specialist.

 @return A @ref DatabaseMessage to report if the operation was successful or if any type of error happen.
*/
DatabaseMessage Database::updateSpecialistId(string id, string newId)
{
	return( updateSpecialist(id, "ID", newId) );
}


/**
 Updates the specialty of a specialist in the database, given the specialist ID.

 @param id [in] Identification number of the specialist.
 @param newSpecialty [in] New specialty of a specialist.

 @return A @ref DatabaseMessage to report if the operation was successful or if any type of error happen.
*/
DatabaseMessage Database::updateSpecialistSpecialty(string id, string newSpecialty)
{
	if( newSpecialty.empty() )
		newSpecialty = "No especificado";		

	return( updateSpecialist(id, "SPECIALTY", newSpecialty) );
}


/**
 Gets the size of a table, given the name of the table.

 @param tableName [in] Name of the table.
 @param tableSize [out] Variable where is saved and returned the size of the table.

 @return True if the size of the table was obtained, false otherwise.
*/
bool Database::getTableSize(string tableName, int &tableSize)
{
	// SQL statement to count how many rows there are in a table, given the name of the table
	string statement = "SELECT COUNT(*) FROM "+tableName+";";

	// Runs the previous SQL statement
	rc = sqlite3_exec(db, statement.c_str(), callbackCountOperation, &tableSize, NULL);

	if( rc != SQLITE_OK )
		return false;

	return true;
}


/**
 Gets the size of the 'users' table.

 @param tableSize [out] Variable where is saved and returned the size of the table
 @see getTableSize()

 @return True if the size of the table was obtained, false otherwise.
*/
bool Database::getUsersTableSize(int &tableSize)
{
	return( getTableSize("USERS", tableSize) );
}


/**
 Gets the size of the 'specialist' table.

 @param tableSize [out] Variable where is saved and returned the size of the table
 @see getTableSize()

 @return True if the size of the table was obtained, false otherwise.
*/
bool Database::getSpecialistsTableSize(int &tableSize)
{
	return( getTableSize("SPECIALISTS", tableSize) );
}


/**
 Gets the size of the 'games' table.

 @param tableSize [out] Variable where is saved and returned the size of the table
 @see getTableSize()

 @return True if the size of the table was obtained, false otherwise.
*/
bool Database::getGameTableSize(int &tableSize)
{
	return( getTableSize("GAMES", tableSize) );
}


/**
 Callback function for @ref getGameTableSize.

 @param param [out] Value returned with the size of the table
 @param colNum [in] Number of arguments, it means number of columns of the table.
 @param colValue [in] Values of the arguments, it means values of the columns of the table.
 @param colName [in] Names of the columns sent.

 @return The function return the value 0 meaning that all was fine.
*/
int Database::callbackCountOperation(void *param, int colNum, char **colValue, char **colName)
{
	int *count = (int*)param;
	*count = atoi(colValue[0]);
    
    return 0;
}


/**
 Returns a user from the 'users' table given its position in the table.

 @param row [in] Position of the user in the table.
 @param user [out] Stores the user data.

 @return True if the user was obtained, false otherwise.
*/
bool Database::getNUser(int row, User &user)
{
	// SQL statement to select a user from the "users" table given its position.
	string statement = "SELECT * FROM USERS LIMIT " + itos(row) + ",1;";

	// Runs the previous SQL statement
	rc = sqlite3_exec(db, statement.c_str(), callbackNUser, &user, NULL);

	if( rc != SQLITE_OK )
		return false;
	else
		return true;
}


/**
 Callback function for @ref getNUser.

 @param param [out] Return an @ref User structure with the data of the user.
 @param colNum [in] Number of arguments, it means number of columns of the table.
 @param colValue [in] Values of the arguments, it means values of the columns of the table.
 @param colName [in] Names of the columns sent.

 @return The function return the value 0 meaning that all was fine.
*/
int Database::callbackNUser(void *param, int colNum, char **colValue, char **colName)
{
    User *user = (User*)param;
    
	user->id = colValue[0];
	user->name = colValue[1];
	user->successes = atoi( colValue[2] );
	user->failures = atoi( colValue[3] );
    
    return 0;
}



/**
 Returns a specialist from the 'specialists' table given its position in the table.

 @param row [in] Position of the specialist in the table.
 @param user [out] Stores the specialist data.

 @return True if the specialist was obtained, false otherwise.
*/
bool Database::getNSpecialist(int row, Specialist &specialist)
{
	// SQL statement to select a specialist from the "specialist" table given its position.
	string statement = "SELECT * FROM SPECIALISTS LIMIT " + itos(row) + ",1;";

	// Runs the previous SQL statement
	rc = sqlite3_exec(db, statement.c_str(), callbackNSpecialist, &specialist, NULL);

	if( rc != SQLITE_OK )
		return false;
	else
		return true;
}


/**
 Callback function for @ref getNSpecialist.

 @param param [out] Return an @ref Specialist structure with the data of the specialist.
 @param colNum [in] Number of arguments, it means number of columns of the table.
 @param colValue [in] Values of the arguments, it means values of the columns of the table.
 @param colName [in] Names of the columns sent.

 @return The function return the value 0 meaning that all was fine.
*/
int Database::callbackNSpecialist(void *param, int colNum, char **colValue, char **colName)
{
    Specialist *specialist = (Specialist*)param;
    
	specialist->id = colValue[0];
	specialist->name = colValue[1];
	specialist->specialty = colValue[2];

    
    return 0;
}


/**
 Gets the 'n' game of a user. It is used to list the games of a specific user.

 @param userId [in] ID of the user.
 @param row [in] Number of game among all the games of a user.
 @param game [out] Game struct where is saved the information of that game.

 @return True if the game was found, false otherwise.
*/
bool Database::getNGamesbyUser(string userId, int row, Game &game)
{
	// SQL statement to select a specific game (given its position) of a specific user
	string statement = "SELECT GAME_ID, START_DATE FROM GAMES WHERE USER_ID='"+userId+"' LIMIT " + itos(row) + ",1;";

	// Runs the previous SQL statement
	rc = sqlite3_exec(db, statement.c_str(), callbackNGamesByUser, &game, NULL);

	if( rc != SQLITE_OK )
		return false;
	else
		return true;
}


/**
 Callback function for @ref getNGamesByUser.

 @param param [out] Return an @ref Game structure with the data of a game.
 @param colNum [in] Number of arguments, it means number of columns of the table.
 @param colValue [in] Values of the arguments, it means values of the columns of the table.
 @param colName [in] Names of the columns sent.

 @return The function return the value 0 meaning that all was fine.
*/
int Database::callbackNGamesByUser(void *param, int colNum, char **colValue, char **colName)
{
    Game *game = (Game*)param;
    
	game->gameId = colValue[0];
	game->date = colValue[1];

    
    return 0;
}


/**
 Returns a user from the 'users' table given its id.

 @param id [in] Identification number of the user.
 @param user [out] Stores the user data.

 @return True if the user was obtained, false otherwise.
*/
bool Database::getUserById(string id, User &user)
{
	// SQL statement to select a user from the "users" table given its id.
	string statement = "SELECT * FROM USERS WHERE ID = '" + id + "';";

	// Runs the previous SQL statement
	rc = sqlite3_exec(db, statement.c_str(), callbackNUser, &user, NULL);

	if( rc != SQLITE_OK )
		return false;
	else
		return true;
}


/**
 Gets how many games of a specific user have been saved in the database. It is used to list the games of a specific user.

 @param userId [in] Identification number of the user
 @param gamesNum [out] Variable where is saved and returned the number of games.

 @return True if the number of games was obtained, false otherwise.
*/
bool Database::getUserGamesNum(string userId, int &gamesNum)
{
	// SQL statement to count how many games there are saved from a specific user
	string statement = "SELECT COUNT(*) FROM GAMES WHERE USER_ID='"+userId+"';";

	// Runs the previous SQL statement
	rc = sqlite3_exec(db, statement.c_str(), callbackUserGamesNum, &gamesNum, NULL);

	if( rc != SQLITE_OK )
		return false;

	return true;
}


/**
 Callback function for @ref getUserGamesNum.

 @param param [out] Return the value of the first column, it means the result of count rows.
 @param colNum [in] Number of arguments, it means number of columns of the table.
 @param colValue [in] Values of the arguments, it means values of the columns of the table.
 @param colName [in] Names of the columns sent.

 @return The function return the value 0 meaning that all was fine.
*/
int Database::callbackUserGamesNum(void *param, int colNum, char **colValue, char **colName)
{
	int *gamesNum = (int*)param;
	*gamesNum = atoi(colValue[0]);
    
    return 0;
}


/**
 Converts int to string.

 @param [in] num Integer to be converted.

 @return The value of the integer converted in string.
*/
string Database::itos(int num)
{
	stringstream ss; // stream used for the conversion
	ss << num; // insert the textual representation of int in the characters in the stream
	return( ss.str() );
}


/**
 Converts float to string.

 @param [in] num float to be converted.

 @return The value of the float converted in string.
*/
string Database::ftos(float num)
{
	stringstream ss;
	ss << num;
	return( ss.str() );
}


/**
 Transforms a string so the first letter of every word are uppercase and the others are lowercase.

 @param [in] text Text to be transformed.

 @return The text transformed.
*/
string Database::upperFirstLetter(string text)
{
	// Calculates the length of the string
	int letters = text.length();

	// Transform the string in uppercase
	for(int i=0; i<letters; i++)
	{
		text[i] = tolower( text[i] );
	}

	// First letter of the string is uppercase
	text[0] = toupper(text[0]);

	for(int j=1; j<letters; j++)
	{
        // If a space is found
		if( text[j] == ' ')
		{
			// The next letter is uppercase
			j++;
			text[j] = toupper( text[j] );
		}
	}
	
	return text;
}
