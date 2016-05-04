/**
 @file   keyboard.cpp
 @author Pedro Américo Toledano López
 @date   August, 2015
 @brief  Virtual keyboard to enter data from the kinect sensor.
*/

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <cstring>

#include "Kinect.h"
#include "Database.h"
#include "Graphics.h"

using namespace cv;
using namespace std;

/** Keyboard states */
enum Mode {KEYBOARD, KEYBOARD_CONFIRM, LEAVING};
/** Tables **/
enum Table {USERS=1, SPECIALISTS=2};
/** Data requested to users */
enum UserReqData {NO_USER_REQUEST, USER_ID, USER_NAME};
/** Data requested to specialists */
enum SpecialistReqData {NO_SPECIALIST_REQUEST, SPECIALIST_ID, SPECIALIST_NAME, SPECIALTY};
/** Command to do */
enum Command {INSERT=1, UPDATE=2, DELETE=3};


int main(int argc, char** argv)
{
	Mat frameChroma = imread("./img/background.jpg", CV_LOAD_IMAGE_COLOR); // Loads the background image
	Mat frameColor; // Frame to store the image from the RGB camera
	Mat frameColorFlipped; // Auxiliary frame used to flip the color frame.

	Mode mode = KEYBOARD; // By default, the mode is keyboard
	const char* deviceURI; // Uniform Resource Identifier of the device

	string textInput = "";
	string patientID;
	string patientName;
	string doctorName;
	Table table;
	Command command;
	UserReqData uRequestedData = USER_ID;
	SpecialistReqData sRequestedData = SPECIALIST_ID;
	User user;
	Specialist specialist;
	int dialogAnswer = -1;

	bool rc = false;

	bool keyButtonPressed = false;

	Kinect *kinect1 = new Kinect();
	Database *db1 = new Database();
	Graphics *graphics = new Graphics();


	if(argc == 3)
	{
		switch( atoi(argv[1]) )
		{
			case 1: table = USERS; break;
			case 2: table = SPECIALISTS; break;
			default: return 0;
		}

		switch( atoi(argv[2]) )
		{
			case 1: command = INSERT; break;
			case 2: command = UPDATE; break;
			case 3: command = DELETE; break;
			default: return 0;
		}
	}
	else
	{
		return 0;
	}


	// Initializes OpenNI and NiTE
	kinect1->init();

	// Selects the device (kinect)
	deviceURI = openni::ANY_DEVICE;

	// Opens the device
	rc = kinect1->openDevice(deviceURI);
	if( !rc )
	{
		cout<<"ERROR: Device open failed."<<endl;
		return 0;
	}

	rc = kinect1->createDepthStream();
	if( !rc )
	{
		cout<<"ERROR: Create depth stream failed."<<endl;
		return 0;
	}

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
	namedWindow("Teclado virtual: Sistema Kinect para el desarrollo de la motricidad gruesa", CV_WINDOW_AUTOSIZE);


	while(true)
	{
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

		// Flips the RGB frame
		cv::flip(frameColor, frameColorFlipped, 1);
		frameColor = frameColorFlipped;


		// For each user detected
		for (int i = 0; i < kinect1->getUsersNumber(); i++)
		{
			// If the user is been tracked
			if( kinect1->usersInfo[i].userState == TRACKING )
			{
				// If the right hand coordinates are available
				if(kinect1->usersInfo[i].rightHandX != -1)
				{
					// Shows a marker around the right hand
					graphics->showSelectJoint(frameColor, kinect1->usersInfo[i].rightHandX, kinect1->usersInfo[i].rightHandY);
				}

				// If the left hand coordinates are available
				if(kinect1->usersInfo[i].leftHandX != -1)
				{
					// Shows a marker around the left hand
					graphics->showSelectJoint(frameColor, kinect1->usersInfo[i].leftHandX, kinect1->usersInfo[i].leftHandY);
				}

				if(mode == KEYBOARD)
				{
					// Calculates the intersection between the left hand and the intro button
					if( graphics->intersectionEnterKey(kinect1->usersInfo[i].leftHandX, kinect1->usersInfo[i].leftHandY) )
					{
						// Calculates the intersection between the right hand and the intro button
						if( graphics->intersectionEnterKey(kinect1->usersInfo[i].rightHandX, kinect1->usersInfo[i].rightHandY) && !keyButtonPressed )
						{
							if( table == USERS )
							{
								if( command == INSERT )
								{
									if( (uRequestedData == USER_ID) && (textInput != "") )
									{
										// Saves the user id
										user.id = textInput;
										// Resets the text input
										textInput = "";
										// Goes to the next request
										uRequestedData = USER_NAME;
									}
									else if( (uRequestedData == USER_NAME) && (textInput != "") )
									{
										// Saves the user name
										user.name = textInput;
										// Resets the text input
										textInput = "";
										// There are not more requests
										uRequestedData = NO_USER_REQUEST;

										// Asks for confirmation
										mode = KEYBOARD_CONFIRM;
									}
								}
							}
							else if( table == SPECIALISTS )
							{
								if( command == INSERT )
								{
									if( (sRequestedData == SPECIALIST_ID) && (textInput != "") )
									{
										// Saves the specialist id
										specialist.id = textInput;
										// Resets the text input
										textInput = "";
										// Goes to the next request
										sRequestedData = SPECIALIST_NAME;
									}
									else if( (sRequestedData == SPECIALIST_NAME) && (textInput != "") )
									{
										// Saves the user name
										specialist.name = textInput;
										// Resets the text input
										textInput = "";
										// Goes to the next request
										sRequestedData = SPECIALTY;
									}
									else if( (sRequestedData == SPECIALTY) && (textInput != "") )
									{
										// Saves the user name
										specialist.specialty = textInput;
										// Resets the text input
										textInput = "";
										// There are not more requests
										sRequestedData = NO_SPECIALIST_REQUEST;

										// Asks for confirmation
										mode = KEYBOARD_CONFIRM;
									}
								}
							}

							keyButtonPressed = true;
						}
						else
						{
							// Calculates the intersection between the right hand and every key
							for(int row = 0; row<4; row++)
							{
								for(int column = 0; column<10; column++)
								{
									if( graphics->intersectionKey(row, column, kinect1->usersInfo[i].rightHandX, kinect1->usersInfo[i].rightHandY) && !keyButtonPressed)
									{
										// If the key selected is the delete key
										if( graphics->getQwertyKey(row, column) == "delete" )
										{
											if( textInput.length() != 0 )
												textInput.erase( textInput.length() - 1 );
										}
										else
										{
											textInput = textInput + graphics->getQwertyKey(row, column);
										}

										keyButtonPressed = true;
									}
								}
							}
						}

					}
					// Calculates the intersection between the right hand and the intro button
					else if( graphics->intersectionEnterKey(kinect1->usersInfo[i].rightHandX, kinect1->usersInfo[i].rightHandY) )
					{
						// Calculates the intersection between the left hand and every key
						for(int row = 0; row<4; row++)
						{
							for(int column = 0; column<10; column++)
							{
								if( graphics->intersectionKey(row, column, kinect1->usersInfo[i].leftHandX, kinect1->usersInfo[i].leftHandY) && !keyButtonPressed)
								{
									// If the key selected is the delete key
									if( graphics->getQwertyKey(row, column) == "delete" )
									{
										if( textInput.length() != 0 )
											textInput.erase( textInput.length() - 1 );
									}
									else
									{
										textInput = textInput + graphics->getQwertyKey(row, column);
									}

									keyButtonPressed = true;
								}
							}
						}

					}
					// If there is not intersection, the user is been tracked and the hands are under the intro button
					else if(kinect1->usersInfo[i].leftHandY != -1 && kinect1->usersInfo[i].rightHandY != -1 && kinect1->usersInfo[i].leftHandY > graphics->enterKey.y+graphics->enterKey.height && kinect1->usersInfo[i].rightHandY > graphics->enterKey.y+graphics->enterKey.height)
					{
						keyButtonPressed = false;
					}
				}
				else if(mode == KEYBOARD_CONFIRM)
				{
					// Calculates the intersection between any hand and the yes/no buttons, and gets the answer
					if( (graphics->intersectionDialog(kinect1->usersInfo[i].leftHandX, kinect1->usersInfo[i].leftHandY, dialogAnswer)
						|| graphics->intersectionDialog(kinect1->usersInfo[i].rightHandX, kinect1->usersInfo[i].rightHandY, dialogAnswer))
						&& !keyButtonPressed )
					{
						keyButtonPressed = true;
						break;
					}
					else
					{
						dialogAnswer = -1;
					}
				}


				// If the user is been tracked and the hands are under the intro button
				if(kinect1->usersInfo[i].leftHandY != -1 && kinect1->usersInfo[i].rightHandY != -1 && kinect1->usersInfo[i].leftHandY > graphics->enterKey.y+graphics->enterKey.height && kinect1->usersInfo[i].rightHandY > graphics->enterKey.y+graphics->enterKey.height)
				{
					keyButtonPressed = false;
				}
			}
		}


		// Sets the user state
		if(kinect1->getUsersNumber() == 0) // If no user has been detected ever
		{
			graphics->showUserState(frameColor, "BUSCANDO USUARIO");
			
		}
		else
		{
			for(int i = 0; i < kinect1->getUsersNumber(); i++)
			{
				// If the user is been tracked
				if(kinect1->usersInfo[i].leftHandY != -1 || kinect1->usersInfo[i].rightHandY != -1)
				{
					switch(kinect1->usersInfo[i].userState)
					{
						case(USER_FOUND): graphics->showUserState(frameColor, "USUARIO DETECTADO"); break;
						case(CALIBRATING): graphics->showUserState(frameColor, "CALIBRANDO"); break;
						case(TRACKING): graphics->showUserState(frameColor, "SIGUIENDO"); break;
						case(STOPPED): graphics->showUserState(frameColor, "DETENIDO"); break;
						case(USER_NOT_FOUND): break;
					}
				
					break;
				}
				// If it is the last user, and none of them is been tracked
				else if(i == kinect1->getUsersNumber()-1)
				{
					graphics->showUserState(frameColor, "BUSCANDO USUARIO");
				}
			}
		}


		if(mode == KEYBOARD)
		{
			// Shows the keyboard
			graphics->showKeyboard(frameColor);

			if(table == USERS)
			{
				// Shows a message requesting data
				switch(uRequestedData)
				{
					case (USER_ID): graphics->putTextCairo(frameColor, "Introduce ID de usuario:", cv::Point2d(WIN_SIZE_X/2, 360), "arial", 30, Scalar(255,255,255), true); break;
					case (USER_NAME): graphics->putTextCairo(frameColor, "Introduce nombre de usuario:", cv::Point2d(WIN_SIZE_X/2, 360), "arial", 30, Scalar(255,255,255), true); break;
					case (NO_USER_REQUEST): break;
				}
			}
			else if(table == SPECIALISTS)
			{
				// Shows a message requesting data
				switch(sRequestedData)
				{
					case (SPECIALIST_ID): graphics->putTextCairo(frameColor, "Introduce ID de especialista:", cv::Point2d(WIN_SIZE_X/2, 360), "arial", 30, Scalar(255,255,255), true); break;
					case (SPECIALIST_NAME): graphics->putTextCairo(frameColor, "Introduce nombre de especialista:", cv::Point2d(WIN_SIZE_X/2, 360), "arial", 30, Scalar(255,255,255), true); break;
					case (SPECIALTY): graphics->putTextCairo(frameColor, "Introduce la especialidad:", cv::Point2d(WIN_SIZE_X/2, 360), "arial", 30, Scalar(255,255,255), true); break;
					case (NO_SPECIALIST_REQUEST): break;
				}
			}
			

			// Shows the written text
			graphics->putTextCairo(frameColor, textInput, cv::Point2d(WIN_SIZE_X/2, 420), "arial", 30, Scalar(255,255,255), true);
		}

		// Shows a confirm screen
		if(mode == KEYBOARD_CONFIRM)
		{
			if(table == USERS)
			{
				if(command == INSERT)
				{
					graphics->showDialog(frameColor, user.id + ", " + user.name);

					if(dialogAnswer == 1)
					{
						db1->insertUser(user.id, user.name);

						dialogAnswer = -1;
						return 0;
					}
					else if(dialogAnswer == 0)
					{
						textInput = "";
						user.id = "";
						user.name = "";
						mode = KEYBOARD;
						uRequestedData = USER_ID;
						dialogAnswer = -1;
					}
				}
			}
			else if(table == SPECIALISTS)
			{
				if(command == INSERT)
				{
					graphics->showDialog(frameColor, specialist.id + ", " + specialist.name + ", " + specialist.specialty);

					if(dialogAnswer == 1)
					{
						db1->insertSpecialist(specialist.id, specialist.name, specialist.specialty);

						dialogAnswer = -1;
						return 0;
					}
					else if(dialogAnswer == 0)
					{
						textInput = "";
						specialist.id = "";
						specialist.name = "";
						specialist.specialty = "";
						mode = KEYBOARD;
						sRequestedData = SPECIALIST_ID;
						dialogAnswer = -1;
					}
				}
			}
		}

		// Shows the color frame if it is not empty
		if( !frameColor.empty() )
		{
        	imshow("Teclado virtual: Sistema Kinect para el desarrollo de la motricidad gruesa", frameColor);
    	}


		// Waits for a keyboard input
		char key = waitKey(5);

		if (key == 27 || mode == LEAVING) // Escape -> Exit
		{
			break;
		}
		else if (key == 49) // 1
		{
			mode = KEYBOARD;
		}
	}

	
	delete kinect1;
	delete db1;
	delete graphics;

	return 0;
}
