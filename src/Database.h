/**
 @file   Database.h
 @author Pedro Américo Toledano López
 @date   August, 2015
 @brief  Class to handle the data base, using SQLite3.
*/

#ifndef DATABASE_H
#define DATABASE_H

#include <sqlite3.h> // Include for SQLite
#include <sstream> // Include for string type


using namespace std;


/** Values returned when an operation is done. */
enum DatabaseMessage {OK, ERROR, FORMAT_ERROR};

/** Holds the data of an user. */
struct User
{
	/* Id value of this user. */
	string id;
	/* Name value of this user. */
	string name;
	/* Number of successes in the score of this user. */
	int successes;
	/* Number of failures in the score of this user. */
	int failures;
};

/** Holds the data of a specialist. */
struct Specialist
{
	/* Id value of this specialist. */
	string id;
	/* Name value of this specialist. */
	string name;
	/* Specialty value of this specialist. */
	string specialty;
};

/** Holds the data of a game. */
struct Game
{
	/* Id value of this game. */
	string gameId;
	/* Date of this game. */
	string date;
};


class Database
{
	public:
		Database();
		~Database();
		bool openDatabase();
		void closeDatabase();
		bool createTables();

		DatabaseMessage insertUser(string id, string name);
		DatabaseMessage insertSpecialist(string id, string name, string specialty);
		bool insertGame(string userId, string startDate, string endDate, int successes, int failures);
		bool insertGameData(int time, int gameId, float fruitX, float fruitY, float headX, float headY, float neckX, float neckY, float leftShoulderX, float leftShoulderY, float rightShoulderX, float rightShoulderY, float leftElbowX, float leftElbowY, float rightElbowX, float rightElbowY, float leftHandX, float leftHandY, float rightHandX, float rightHandY, float leftHipX, float leftHipY, float rightHipX, float rightHipY);
		DatabaseMessage insertLinkUserSpecialist(string userId, string specialistId);

		DatabaseMessage deleteUser(string id);
		DatabaseMessage deleteSpecialist(string id);
		DatabaseMessage deleteLinkUserSpecialist(string userId, string specialistId);

		DatabaseMessage updateUser(string id, string column, string value);
		DatabaseMessage updateUserName(string id, string userName);
		DatabaseMessage updateUserId(string id, string newId);
		void updateUserTotalScore(string id, int successes, int failures);
		DatabaseMessage updateSpecialist(string id, string column, string value);
		DatabaseMessage updateSpecialistName(string id, string userName);
		DatabaseMessage updateSpecialistId(string id, string newId);
		DatabaseMessage updateSpecialistSpecialty(string id, string newSpecialty);

		bool getTableSize(string tableName, int &tableSize);
		bool getUsersTableSize(int &tableSize);
		bool getSpecialistsTableSize(int &tableSize);
		bool getGameTableSize(int &tableSize);
		static int callbackCountOperation(void *param, int colNum, char **colValue, char **colName);

		bool getNUser(int row, User &user);
		static int callbackNUser(void *param, int colNum, char **colValue, char **colName);
		bool getNSpecialist(int row, Specialist &specialist);
		static int callbackNSpecialist(void *param, int colNum, char **colValue, char **colName);
		bool getUserById(string id, User &user);

		bool getNGamesbyUser(string userId, int row, Game &game);
		static int callbackNGamesByUser(void *param, int colNum, char **colValue, char **colName);
		bool getUserGamesNum(string userId, int &gamesNum);
		static int callbackUserGamesNum(void *param, int colNum, char **colValue, char **colName);

		static string itos(int num);
		static string ftos(float num);
		string upperFirstLetter(string text);

	private:
		sqlite3 *db; /** Variable for the SQLite database */
		int rc;	/** Return code for sqlite functions */
};


#endif
