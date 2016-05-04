/**
 @file   game.cpp
 @author Pedro Américo Toledano López
 @date   August, 2015
 @brief  Game to improve the motor skills.
*/

#include <sstream>
#include <ctime>
#include <cmath>
#include "cvaux.h" // Include for OpenCV
#include "highgui.h" // Include for OpenCV

#include "Kinect.h"
#include "Database.h"
#include "Graphics.h"

using namespace cv;
using namespace std;


/** Values of the different game states */
enum Mode {STARTING, GAME, PAUSING, PAUSE, DISPAUSING, USER_LOST_PAUSING, USER_LOST_PAUSE, USER_LOST_DISPAUSING, SCORE_SCREEN, LEAVING};


/**
 Gets the hour and date from the system.

 @return A string containing the hour and date.
*/
const string getDate()
{
	time_t now = time(0);
	struct tm tstruct;
	char buf[80];

	tstruct = *localtime(&now);

	strftime(buf, sizeof(buf), "%Y/%m/%d, %X", &tstruct);

	return buf;
}


/**
 Gets the value in usec from a timeval struct.

 @param [in] tval Timeval struct.

 @return The value in usec of the timeval struct.
*/
long int getTimevalUsec(timeval tval)
{
	return ((tval.tv_sec * 1000000) + tval.tv_usec);
}


/**
 Converts a integer in a string.

 @param [in] number The number to be converted.

 @return A string containing the number.
*/
string intToString(int number)
{
	ostringstream convert;   // stream used for the conversion
	convert << number;      // insert the textual representation of 'score' in the characters in the stream

	return ( convert.str() );
}



int main(int argc, char** argv)
{
	Mat frameChroma = imread("./img/background.jpg", CV_LOAD_IMAGE_COLOR); // Loads background image
	Mat frameColor; // Frame to store the image from the RGB camera
	Mat frameColorFlipped; // Auxiliary frame used to flip the color frame.

	Mode mode = STARTING; // By default, the mode is starting
	UserState uState = USER_NOT_FOUND; // Saves the state of the user
	const char* deviceURI; // Uniform Resource Identifier of the device

	timeval currentTimeGame; // Current moment
	timeval initTimeGame; // Moment when the game is started
	timeval totalTimeGame = (struct timeval){0}; // Current duration of the game
	timeval initTimeFruit; // Moment when the fruit was drawn
	timeval initTimePause; // Moment when the pause mode was activated
	timeval durationTimePause = (struct timeval){0}; // Duration of a pause
	timeval accumulatedTimePause = (struct timeval){0}; // Total duration of all the pauses of the game

	string idUser = ""; // ID of the user playing
	int score[2] = {0, 0}; // Game score (score[0] successes, score[1] failures)
	int tableSize = 0; // Size of a table of the database
	string startDate; // Date when the game started
	string endDate; // Date when the game finished
	bool fruitIntersected = false; // Flag indicating if a fruit was intersected
	bool rc = false;
	float fruitX = 460, fruitY = 40; //Coger estos valores de clase Graphics
	int fruitDuration = 3; // Duration of the fruit (3 seconds by default)
	int maxDuration = 60; // Duration of the game (60 seconds by default)
	unsigned long long int fruitClockProgress = 0;
	char key = ' '; // Saves the keyboard input

	Kinect *kinect1 = new Kinect();
	Database *db1 = new Database();
	Graphics *graphics = new Graphics();



	// Initializes OpenNI and NiTE
	kinect1->init();

	// If a *.oni file is passed as a parameter
	if(argc == 2)
	{
		// Our device will be the *.oni file
		deviceURI = argv[1];
	}
	else
	{
		// Our device will be the kinect sensor
		deviceURI = openni::ANY_DEVICE;

		if(argc == 4)
		{
			fruitDuration = atoi(argv[1]);
			maxDuration = atoi(argv[2]);
			idUser = argv[3];
		}
		else if(argc == 3)
		{
			fruitDuration = atoi(argv[1]);
			maxDuration = atoi(argv[2]);
		}
	}

	// Opens the device
	rc = kinect1->openDevice(deviceURI);
	if( !rc )
	{
		cout<<"ERROR: Device open failed."<<endl;
		return 0;
	}

	// Creates and starts the depth stream
	rc = kinect1->createDepthStream();
	if( !rc )
	{
		cout<<"ERROR: Create depth stream failed."<<endl;
		return 0;
	}

	// Creates and starts the RBG stream
	rc = kinect1->createColorStream();
	if( !rc )
	{
		cout<<"ERROR: Create RGB stream failed."<<endl;
		return 0;
	}

	// Sinchronyzes the RGB and depth sensors
	kinect1->syncDepthColor();

	// Starts users tracking
	kinect1->startUserTracking();

	// Sets the name of the window
	namedWindow("Sistema Kinect para el desarrollo de la motricidad gruesa", CV_WINDOW_AUTOSIZE);


	// Infinite loop
	while(true)
	{
		// Gets the current moment in the time
		gettimeofday(&currentTimeGame, NULL);

		// Gets the next snapshot of the skeleton tracking algorithm
		if (!kinect1->readTrackerFrame())
		{
			cout<<"Get next frame failed!"<<endl;
			continue;
		}

		// Reads a frame from the RGB camera and store it in 'frameColor'
		kinect1->readFrame(frameColor, NI_SENSOR_COLOR);

		// Inserts a background image, as if it were a chroma
		kinect1->insertChroma(frameColor, frameChroma);

		// Detects the users and stores the coordinates of the joints
		kinect1->usersManagement();

		// Flips the RGB frame so the image looks like a mirror
		cv::flip(frameColor, frameColorFlipped, 1);
		frameColor = frameColorFlipped;


		// For each user detected
		for (int i = 0; i < kinect1->getUsersNumber(); i++)
		{
			// If the user is been tracking
			if( kinect1->usersInfo[i].userState == TRACKING )
			{
				// If the right hand coordinates are available
				if(kinect1->usersInfo[i].rightHandX != -1)
				{
					// Shows a marker around the right hand
					if(mode == GAME)
						graphics->showGameJoint(frameColor, kinect1->usersInfo[i].rightHandX, kinect1->usersInfo[i].rightHandY);
					else if(mode == SCORE_SCREEN)
						graphics->showSelectJoint(frameColor, kinect1->usersInfo[i].rightHandX, kinect1->usersInfo[i].rightHandY);
				}

				// If the left hand coordinates are available
				if(kinect1->usersInfo[i].leftHandX != -1)
				{
					// Shows a marker around the left hand
					if(mode == GAME)
						graphics->showGameJoint(frameColor, kinect1->usersInfo[i].leftHandX, kinect1->usersInfo[i].leftHandY);
					else if(mode == SCORE_SCREEN)
						graphics->showSelectJoint(frameColor, kinect1->usersInfo[i].leftHandX, kinect1->usersInfo[i].leftHandY);
				}


				if(mode == STARTING)
				{
					// Saves the date and hour when the game has started
					startDate = getDate();

					// Saves the moment when the game has started
					gettimeofday(&initTimeGame, NULL);

					// Saves the moment when the first fruit has been drawn 
					gettimeofday(&initTimeFruit, NULL);

					// Starts the game
					mode = GAME;
				}

				if(mode == GAME)
				{
					// Gets the size of the 'games' table. This way, we can know which the game id must be
					db1->getGameTableSize(tableSize);

					// Inserts the data of the game in this moment in the database
					db1->insertGameData(totalTimeGame.tv_sec, tableSize, fruitX, fruitY, kinect1->usersInfo[i].headX, kinect1->usersInfo[i].headY, kinect1->usersInfo[i].neckX, kinect1->usersInfo[i].neckY, kinect1->usersInfo[i].leftShoulderX, kinect1->usersInfo[i].leftShoulderY, kinect1->usersInfo[i].rightShoulderX, kinect1->usersInfo[i].rightShoulderY, kinect1->usersInfo[i].leftElbowX, kinect1->usersInfo[i].leftElbowY, kinect1->usersInfo[i].rightElbowX, kinect1->usersInfo[i].rightElbowY, kinect1->usersInfo[i].leftHandX, kinect1->usersInfo[i].leftHandY, kinect1->usersInfo[i].rightHandX, kinect1->usersInfo[i].rightHandY, kinect1->usersInfo[i].leftHipX, kinect1->usersInfo[i].leftHipY, kinect1->usersInfo[i].rightHipX, kinect1->usersInfo[i].rightHipY);

					// Calculates intersection between right hand and fruit image
					if( graphics->intersectionFruit(kinect1->usersInfo[i].rightHandX, kinect1->usersInfo[i].rightHandY) )
					{
						fruitIntersected = true;
						break;
					}
					// Calculates intersection between left hand and fruit image
					else if( graphics->intersectionFruit(kinect1->usersInfo[i].leftHandX, kinect1->usersInfo[i].leftHandY) )
					{
						fruitIntersected = true;
						break;
					}
				}
				else if(mode == SCORE_SCREEN)
				{
					// Calculates intersection between any hand and the "new game" button
					if( graphics->intersectionNewGameButton(kinect1->usersInfo[i].rightHandX, kinect1->usersInfo[i].rightHandY) 
						|| graphics->intersectionNewGameButton(kinect1->usersInfo[i].leftHandX, kinect1->usersInfo[i].leftHandY) )
					{
						// Resets score
						score[0] = 0;
						score[1] = 0;

						// Changes mode to "game mode"
						mode = STARTING;
					}
					// Calculates intersection between any hand and the "exit" button
					else if( graphics->intersectionExitButton(kinect1->usersInfo[i].rightHandX, kinect1->usersInfo[i].rightHandY) 
						|| graphics->intersectionExitButton(kinect1->usersInfo[i].leftHandX, kinect1->usersInfo[i].leftHandY) )
					{
						mode = LEAVING;
					}
				}
			}
		}


		// Sets the user state
		if(kinect1->getUsersNumber() == 0) // If no user has been detected ever
		{
			uState = USER_NOT_FOUND;
			
		}
		else
		{
			for(int j = 0; j < kinect1->getUsersNumber(); j++)
			{
				// If the user is being tracked
				if(kinect1->usersInfo[j].leftHandY != -1 || kinect1->usersInfo[j].rightHandY != -1)
				{
					uState = kinect1->usersInfo[j].userState;

					break;
				}
				else if(j == kinect1->getUsersNumber()-1) //Si es el último usuario y no hay ninguno activo
				{
					uState = USER_NOT_FOUND;

					if(mode != USER_LOST_PAUSE && mode == GAME)
						mode = USER_LOST_PAUSING;
				}
			}
		}


		if(mode == GAME)
		{
			// If the playing time is over
			if( getTimevalUsec(currentTimeGame) - getTimevalUsec(initTimeGame) - getTimevalUsec(accumulatedTimePause) > (maxDuration*1000000) )
			{
				// Changes to score screen
				mode = SCORE_SCREEN;
				// Stores the date when the game ended.
				endDate = getDate();
			}
			// Else, if the game continues
			else
			{
				// If the fruit image was intersected
				if(fruitIntersected)
				{
					// Increases the successes score
					score[0]++;

					// Creates a new fruit
					graphics->changeFruit(fruitX, fruitY);

					// Saves the moment when the new fruit has been drawn 
					gettimeofday(&initTimeFruit, NULL);

					// As the fruit is new, the delay by the pause is reset
					durationTimePause = (struct timeval){0};

					// Resets the 'fruitIntersected' flag to false
					fruitIntersected = false;
				}
				// If the fruit time is end
				else if( currentTimeGame.tv_sec - initTimeFruit.tv_sec - durationTimePause.tv_sec > (fruitDuration) )
				{
					// Increases the failures score
					score[1]++;

					// Creates a new fruit
					graphics->changeFruit(fruitX, fruitY);

					// Saves the moment when the new fruit has been drawn 
					gettimeofday(&initTimeFruit, NULL);

					// As the fruit is new, the delay by the pause is reset
					durationTimePause = (struct timeval){0};
				}

				// Shows bottom bar
				graphics->showBottomBar(frameColor);

				// Shows the fruit of the game
				graphics->showFruit(frameColor);

				// Calculates the progress of the fruit
				fruitClockProgress = getTimevalUsec(currentTimeGame) - getTimevalUsec(initTimeFruit) - getTimevalUsec(durationTimePause);
				cout<<"PreEnvio: "<<fruitClockProgress<<endl;
				// Shows the progress bar of the fruit
				graphics->showFruitClock( frameColor, fruitClockProgress, fruitDuration );

				// Shows score
				graphics->showScore( frameColor, intToString(score[0]), intToString(score[1]) );

				// Calculates the current duration of the game
				totalTimeGame.tv_sec = currentTimeGame.tv_sec - initTimeGame.tv_sec - accumulatedTimePause.tv_sec;
				totalTimeGame.tv_usec = currentTimeGame.tv_usec - initTimeGame.tv_usec - accumulatedTimePause.tv_usec;

				// Shows the timer with the countdown
				graphics->showTimer( frameColor, maxDuration-(totalTimeGame.tv_sec) );
			}
		}
		else if(mode == PAUSING || mode == PAUSE || mode == DISPAUSING || mode == USER_LOST_PAUSING || mode == USER_LOST_PAUSE || mode == USER_LOST_DISPAUSING)
		{
			// Shows bottom bar
			graphics->showBottomBar(frameColor);

			// Shows the fruit of the game
			graphics->showFruit(frameColor);

			// Shows the progress bar of the fruit
			graphics->showFruitClock( frameColor, fruitClockProgress, fruitDuration );

			// Shows score
			graphics->showScore( frameColor, intToString(score[0]), intToString(score[1]) );

			// Shows the timer with the countdown
			graphics->showTimer( frameColor, maxDuration-(totalTimeGame.tv_sec) );

			if(mode == PAUSING)
			{
				// Saves the moment when the pause was started
				gettimeofday(&initTimePause, NULL);

				// Starts pause mode
				mode = PAUSE;
			}
			else if(mode == PAUSE)
			{
				graphics->showPauseScreen(frameColor);
			}
			else if(mode == DISPAUSING)
			{
				// Saves the duration of the pause
				durationTimePause.tv_sec = currentTimeGame.tv_sec - initTimePause.tv_sec;
				durationTimePause.tv_usec = currentTimeGame.tv_usec - initTimePause.tv_usec;

				// Adds the duration of the pause to the sum of all the pauses of the game
				accumulatedTimePause.tv_sec = accumulatedTimePause.tv_sec + durationTimePause.tv_sec;
				accumulatedTimePause.tv_usec = accumulatedTimePause.tv_usec + durationTimePause.tv_usec;

				// Returns to the game
				mode = GAME;
			}
			else if(mode == USER_LOST_PAUSING)
			{
				// Saves the moment when the pause was started
				gettimeofday(&initTimePause, NULL);

				// Starts pause mode
				mode = USER_LOST_PAUSE;
			}
			else if(mode == USER_LOST_PAUSE)
			{
				//graphics->showPauseScreen(frameColor);

				if(uState == TRACKING)
					mode = USER_LOST_DISPAUSING;
			}
			else if(mode == USER_LOST_DISPAUSING)
			{
				// Saves the duration of the pause
				durationTimePause.tv_sec = currentTimeGame.tv_sec - initTimePause.tv_sec;
				durationTimePause.tv_usec = currentTimeGame.tv_usec - initTimePause.tv_usec;

				// Adds the duration of the pause to the sum of all the pauses of the game
				accumulatedTimePause.tv_sec = accumulatedTimePause.tv_sec + durationTimePause.tv_sec;
				accumulatedTimePause.tv_usec = accumulatedTimePause.tv_usec + durationTimePause.tv_usec;

				// Returns to the game
				mode = GAME;
			}
		}
		else if(mode == SCORE_SCREEN)
		{
			// Shows the score screen
			graphics->showScoreScreen( frameColor, intToString(score[0]), intToString(score[1]) );
		}
		else if(mode == LEAVING)
		{
			// If the user is identified
			if(idUser != "")
			{
				db1->insertGame(idUser, startDate, endDate, score[0], score[1]);
				db1->updateUserTotalScore(idUser, score[0], score[1]);
			}
		}


		// Shows the user state
		switch(uState)
		{
			case(USER_FOUND): graphics->showUserState(frameColor, "USUARIO DETECTADO"); break;
			case(CALIBRATING): graphics->showUserState(frameColor, "CALIBRANDO"); break;
			case(TRACKING): graphics->showUserState(frameColor, "SIGUIENDO"); break;
			case(STOPPED): graphics->showUserState(frameColor, "DETENIDO"); break;
			case(USER_NOT_FOUND): graphics->showUserState(frameColor, "BUSCANDO USUARIO"); break;
		}

	
		// Shows the color frame if it is not empty
		if( !frameColor.empty() )
		{
        	imshow("Sistema Kinect para el desarrollo de la motricidad gruesa", frameColor);
    	}


		// Waits for a key input
		key = waitKey(2);

		if (key == 27 || mode == LEAVING) // Escape -> Exit
		{
			break;
		}
		else if (key == 80 || key == 112) // P -> Pause
		{
			if(mode == GAME)
			{
				mode = PAUSING;
			}
			else if(mode == PAUSE)
			{
				mode = DISPAUSING;
			}
		}
		else if (key == 82 || key == 114) // R -> Records a file *.oni
		{
			kinect1->startRecordStream("gameVideo.oni", RGB_AND_DEPTH);
		}
		else if (key == 83 || key == 115) // S -> Stops recording
		{
			kinect1->stopRecordStream();
		}

	}

	delete kinect1;
	delete db1;
	delete graphics;

	return 0;
}
