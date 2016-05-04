/**
 @file   Kinect.cpp
 @author Pedro Américo Toledano López
 @date   May, 2015
 @brief  Class to handle the kinect sensor, using OpenNI and NiTE.
*/

#include "Kinect.h"
#include <iostream>

using namespace std;
using namespace openni;
using namespace nite;
using namespace cv;


/**
 Constructor
*/
Kinect::Kinect()
{
	usersNumber = 0;
}

/**
 Destructor. Stops the device, closes OpenNI and NiTE.
*/
Kinect::~Kinect()
{
	// Stops the depth stream
	depth.stop();
	// Stops the color stream
	color.stop();
	// Destroys the depth stream
	depth.destroy();
	// Destroys the color stream
	color.destroy();
	// Closes the device
	device.close();
	// Closes NiTE
	NiTE::shutdown();
	// Closes OpenNI
	OpenNI::shutdown();
}

/**
 Initializes OpenNI and NiTE libraries

 @return If OpenNI initialization failed returns -1, if NiTE initialization failed returns -2,
	if OpenNI and NiTE were initialized successfully returns 1.
*/
int Kinect::init()
{
	rc = openni::STATUS_OK;
	niteRc = nite::STATUS_OK;

	// Initializes OpenNI
	rc = OpenNI::initialize();

	if (rc != openni::STATUS_OK)
	{
		cout << "ERROR: After OpenNI initialization: " << endl << openni::OpenNI::getExtendedError() << endl;

		return (-1);
	}
	else
	{
		cout << "OpenNI initialized." << endl;
	}

	// Initializes NiTE
	niteRc = NiTE::initialize();

	if (niteRc != nite::STATUS_OK)
	{
		cout << "ERROR: After NiTE initialization." << endl;

		return (-2);
	}
	else
	{
		cout << "NiTE initialized." << endl;
	}

	return 1;
}


/////////////////////////////////////////////////////////////////////
/////////////// OPENNI FUNCTIONS ////////////////////////////////////
/////////////////////////////////////////////////////////////////////

/**
 Opens the Kinect device.

 @param [in] deviceURI String containing the URI of the device to be opened.

 @return True if the device was opened, false otherwise.
*/
bool Kinect::openDevice(const char* deviceURI)
{
	// Opens the device
	rc = device.open(deviceURI);

	if (rc != openni::STATUS_OK)
	{
		cout << "ERROR: Device open failed: " <<endl << openni::OpenNI::getExtendedError() << endl;
		return false;
	}
	else
	{
		cout << "Device opened." << endl;
		return true;
	}
}

/**
 Creates and starts the depth stream.

 @return If the depth stream is not found returns -1, if it cannot be started returns -2, 
	if it is not valid returns -3, if it is created and started successfully returns 1.
*/
int Kinect::createDepthStream()
{
	// Creates the depth stream of frames throught the depth sensor
	rc = depth.create(device, openni::SENSOR_DEPTH);
	if (rc == openni::STATUS_OK)
	{
		rc = depth.start();
		if (rc != openni::STATUS_OK)
		{
			cout << "Couldn't start depth stream: " << endl << openni::OpenNI::getExtendedError() << endl;
			return (-2);
		}
	}
	else
	{
		cout << "Couldn't find depth stream: " << endl<<openni::OpenNI::getExtendedError() << endl;
		return (-1);
	}

	// Verifies if the depth stream is valid
	if (!depth.isValid())
	{
		cout << "No valid streams." << endl;
		return (-3);
	}

	return 1;
}

/**
 Creates and starts the RBG stream.

 @return If the RGB stream is not found returns -1, if it cannot be started returns -2, 
	if it is not valid returns -3, if it is created and started successfully returns 1.
*/
int Kinect::createColorStream()
{
	// Creates the color stream of frames throught the RGB sensor
	rc = color.create(device, openni::SENSOR_COLOR);
	if (rc == openni::STATUS_OK)
	{
		rc = color.start();
		if (rc != openni::STATUS_OK)
		{
			cout << "ERROR: Couldn't start color stream: " << endl << openni::OpenNI::getExtendedError() << endl;
			return (-2);
		}
	}
	else
	{
		cout << "ERROR: Couldn't find color stream: " << endl << openni::OpenNI::getExtendedError() << endl;
		return (-1);
	}

	// Verifies if the RGB stream is valid
	if (!color.isValid())
	{
		cout << "ERROR: No valid RBG stream." << endl;
		return (-3);
	}

	return 1;
}


/**
 Superimposes the images from RGB and depth sensors, since they are located at different points in space.

 @return True if RBG and depth streams were synchronized, false otherwise.
*/
bool Kinect::syncDepthColor()
{
	rc = device.setImageRegistrationMode(openni::IMAGE_REGISTRATION_DEPTH_TO_COLOR);
	
	if (rc != openni::STATUS_OK)
	{
		cout << "ERROR: Couldn't enable depth and color images synchronization: " << endl << openni::OpenNI::getExtendedError() << endl;
		return false;
	}

	return true;
}


/**
 Starts recording the stream/s chosen with the file name indicated.

 @param [in] fileName Name of the output file where the recording will be saved.
 @param [in] streamOption Indicates the stream to be recorder. It can be RBG stream (1), depth stream (2) or both (3).
 @return 
*/
int Kinect::startRecordStream(const char * fileName, StreamOption streamOption)
{
	// Initializes a recorder
	rc = recorder.create(fileName);
	if (rc != openni::STATUS_OK)
	{
		cout << "ERROR: Couldn't create a recorder: " << endl << openni::OpenNI::getExtendedError() << endl;
		return (-1);
	}

	// Attaches the stream/s to be recorded
	// Stream options: 1=color, 2=depth, 3=color&depth
	switch (streamOption)
	{
		case (RGB):
			rc = recorder.attach(color, true);

			if (rc != openni::STATUS_OK)
			{
				cout << "ERROR: Couldn't attach RGB stream to the recorder: " << endl << openni::OpenNI::getExtendedError() << endl;
				return (-2);
			}

			break;

		case (DEPTH):
			rc = recorder.attach(depth, true);
			if (rc != openni::STATUS_OK)
			{
				cout << "ERROR: Couldn't attach depth stream to the recorder: " << endl << openni::OpenNI::getExtendedError() << endl;
				return (-2);
			}

			break;

		case (RGB_AND_DEPTH):
			rc = recorder.attach(color, true);

			if (rc != openni::STATUS_OK)
			{
				cout << "ERROR: Couldn't attach RGB stream to the recorder: " << endl << openni::OpenNI::getExtendedError() << endl;
				return (-2);
			}

			rc = recorder.attach(depth, true);
			if (rc != openni::STATUS_OK)
			{
				cout << "ERROR: Couldn't attach depth stream to the recorder: " << endl << openni::OpenNI::getExtendedError() << endl;
				return (-2);
			}

			break;
	}

	// Verifies if the recorder is valid
	if (!recorder.isValid())
	{
		cout << "ERROR: No valid recorder." << endl;
		return (-3);
	}
	
	// Starts to record
	recorder.start();

	return 1;
}


/**
 Stops recording the stream.

 @return Nothing.
*/
void Kinect::stopRecordStream()
{
	// Stops to record
	recorder.stop();

	// Destroys the recorder object
	recorder.destroy();
}


/**
 Reads a frame.

 @return If no frame can be read or the frame read is not valid returns false, otherwise returns true.
*/
bool Kinect::readFrame(cv::Mat &frame, CameraMode camMode)
{
	VideoFrameRef irf;
	int hIr, wIr;

	VideoFrameRef colorf; 
	int hColor, wColor;


	switch (camMode)
	{
		case (NI_SENSOR_DEPTH):

			rc = depth.readFrame(&irf);
			if (irf.isValid())
			{
				const uint16_t* imgBufIr = (const uint16_t*)irf.getData();
				hIr = irf.getHeight();
        		wIr = irf.getWidth();
        		frame.create(hIr, wIr, CV_16U);
        		memcpy(frame.data, imgBufIr, hIr * wIr * sizeof(uint16_t));
        		frame.convertTo(frame, CV_8U);
				return true;
			}
			else
			{
				cout << "ERROR: Frame not valid." << endl;
				return false;
			}

		case (NI_SENSOR_COLOR):

			rc = color.readFrame(&colorf);
			if(colorf.isValid())
			{
				const openni::RGB888Pixel* imgBufColor = (const openni::RGB888Pixel*)colorf.getData();
				hColor = colorf.getHeight();
        		wColor = colorf.getWidth();
        		frame.create(hColor, wColor, CV_8UC3);
        		memcpy(frame.data, imgBufColor,  3 * hColor * wColor * sizeof(uint8_t));
        		cvtColor(frame, frame, CV_BGR2RGB);
        		return true;
			}
			else
			{
				cout << "ERROR: Frame not valid." << endl;
				return false;
			}

		default:
			cout << "ERROR: No frame to be read. Object not initialize." << endl;
			return false;
	}
}


/////////////////////////////////////////////////////////////////////
/////////////// NITE FUNCTIONS //////////////////////////////////////
/////////////////////////////////////////////////////////////////////

/**
 Starts to track users.

 @return True if the tracking started successfully, false otherwise.
*/
bool Kinect::startUserTracking()
{
	niteRc = userTracker.create();
	if (niteRc != nite::STATUS_OK)
	{
		cout << "ERROR: Couldn't create user tracker." << endl;
		return false;
	}
	else
	{
		cout << endl << "Skeleton calibration, start moving around to get detected." <<endl;
		return true;
	}
}

/**
 Gets the next snapshot of the skeleton tracking algorithm.

 @return True if the frame was readed, false if it failed.
*/
bool Kinect::readTrackerFrame()
{
	niteRc = userTracker.readFrame(&userTrackerFrame);
	if (niteRc == nite::STATUS_OK)
	{
		return true;
	}
	else
	{
		return false;
	}
}


/**
 Gets the coordinates of a given joint and stores it in a User structure

 @param [out] user User skeleton data.
 @param [in] jointType Name of the joint to get the coordinates.
 @param [out] coordX Returns the value of the x-coordinate.
 @param [out] coordY Returns the value of the y-coordinate.

 @return True if the coordinates were obtained, false otherwise.
*/
int Kinect::getJointCoordinates(const nite::UserData& user, nite::JointType jointType, float &coordX, float &coordY)
{
	// Gets the requested joint
	const nite::SkeletonJoint& joint = user.getSkeleton().getJoint(jointType);

	// If there is enough confidence in the coordinates
	if (joint.getPositionConfidence() > 0.5)
	{
		// Gets the depth frame
		depthFrame = userTrackerFrame.getDepthFrame();

		// Converts the coordinates from the 'Real World' system to the 'Projective' system
		niteRc = userTracker.convertJointCoordinatesToDepth(joint.getPosition().x, joint.getPosition().y, joint.getPosition().z, &coordX, &coordY);

		if(niteRc != nite::STATUS_OK)
			cout << "ERROR: Coordinates convertion failed." << endl;

		// Gets the resolution of the frame
		int g_nXRes = depthFrame.getVideoMode().getResolutionX();
		int g_nYRes = depthFrame.getVideoMode().getResolutionY();

		// Adjusts the coordinates to the window size
		coordX *= WIN_SIZE_X/(float)g_nXRes;
		coordY *= WIN_SIZE_Y/(float)g_nYRes;

		return 1;
	}
	else
	{
		return 0;
	}
}


/**
 Detects all the users and stores them.

 @return Nothing.
*/
void Kinect::usersManagement()
{
	float jointCoordX = 0;
	float jointCoordY = 0;


	// Gets a list with the data of every user
	const nite::Array<nite::UserData>& users = userTrackerFrame.getUsers();

	// Gets the number of users detected
	usersNumber = users.getSize();

	// For every user detected
	for (int i = 0; i < users.getSize(); ++i)
	{
		// Saves in 'user' the data of the current user
		const nite::UserData& user = users[i];

		// If the user is new
		if (user.isNew())
		{
			// Starts to track the user
			userTracker.startSkeletonTracking( user.getId() );

			// Set that user as 'found'
			usersInfo[i].userState = USER_FOUND;
		}
		// If the user is not new and their skeleton is being tracked
		else if (user.getSkeleton().getState() == nite::SKELETON_TRACKED)
		{
			// If the joint of the left hand is detected (right hand in NiTE is, in fact, the left hand)
			if ( getJointCoordinates(user, nite::JOINT_RIGHT_HAND, jointCoordX, jointCoordY) )
			{
				// Saves the coordinates of the joint
				usersInfo[i].leftHandX = jointCoordX;
				usersInfo[i].leftHandY = jointCoordY;
			}
			else
			{
				// Sets the coordinates as -1 to indicate they are not available
				usersInfo[i].leftHandX = -1;
				usersInfo[i].leftHandY = -1;
			}

			// If the joint of the right hand is detected (left hand in NiTE is, in fact, the right hand)
			if ( getJointCoordinates(user, nite::JOINT_LEFT_HAND, jointCoordX, jointCoordY) )
			{
				// Saves the coordinates of the joint
				usersInfo[i].rightHandX = jointCoordX;
				usersInfo[i].rightHandY = jointCoordY;
			}
			else
			{
				// Sets the coordinates as -1 to indicate they are not available
				usersInfo[i].rightHandX = -1;
				usersInfo[i].rightHandY = -1;
			}

			// If the joint of the head is detected
			if ( getJointCoordinates(user, nite::JOINT_HEAD, jointCoordX, jointCoordY) )
			{
				// Saves the coordinates of the joint
				usersInfo[i].headX = jointCoordX;
				usersInfo[i].headY = jointCoordY;
			}
			else
			{
				// Sets the coordinates as -1 to indicate they are not available
				usersInfo[i].headX = -1;
				usersInfo[i].headY = -1;
			}

			// If the joint of the neck is detected
			if ( getJointCoordinates(user, nite::JOINT_NECK, jointCoordX, jointCoordY) )
			{
				// Saves the coordinates of the joint
				usersInfo[i].neckX = jointCoordX;
				usersInfo[i].neckY = jointCoordY;
			}
			else
			{
				// Sets the coordinates as -1 to indicate they are not available
				usersInfo[i].neckX = -1;
				usersInfo[i].neckY = -1;
			}

			// If the joint of the left shoulder is detected
			if ( getJointCoordinates(user, nite::JOINT_LEFT_SHOULDER, jointCoordX, jointCoordY) )
			{
				// Saves the coordinates of the joint
				usersInfo[i].leftShoulderX = jointCoordX;
				usersInfo[i].leftShoulderY = jointCoordY;
			}
			else
			{
				// Sets the coordinates as -1 to indicate they are not available
				usersInfo[i].leftShoulderX = -1;
				usersInfo[i].leftShoulderY = -1;
			}

			// If the joint of the right shoulder is detected
			if ( getJointCoordinates(user, nite::JOINT_RIGHT_SHOULDER, jointCoordX, jointCoordY) )
			{
				// Saves the coordinates of the joint
				usersInfo[i].rightShoulderX = jointCoordX;
				usersInfo[i].rightShoulderY = jointCoordY;
			}
			else
			{
				// Sets the coordinates as -1 to indicate they are not available
				usersInfo[i].rightShoulderX = -1;
				usersInfo[i].rightShoulderY = -1;
			}

			// If the joint of the left elbow is detected
			if ( getJointCoordinates(user, nite::JOINT_LEFT_ELBOW, jointCoordX, jointCoordY) )
			{
				// Saves the coordinates of the joint
				usersInfo[i].leftElbowX = jointCoordX;
				usersInfo[i].leftElbowY = jointCoordY;
			}
			else
			{
				// Sets the coordinates as -1 to indicate they are not available
				usersInfo[i].leftElbowX = -1;
				usersInfo[i].leftElbowY = -1;
			}

			// If the joint of the right elbow is detected
			if ( getJointCoordinates(user, nite::JOINT_RIGHT_ELBOW, jointCoordX, jointCoordY) )
			{
				// Saves the coordinates of the joint
				usersInfo[i].rightElbowX = jointCoordX;
				usersInfo[i].rightElbowY = jointCoordY;
			}
			else
			{
				// Sets the coordinates as -1 to indicate they are not available
				usersInfo[i].rightElbowX = -1;
				usersInfo[i].rightElbowY = -1;
			}

			// If the left joint of the hip is detected
			if ( getJointCoordinates(user, nite::JOINT_LEFT_HIP, jointCoordX, jointCoordY) )
			{
				// Saves the coordinates of the joint
				usersInfo[i].leftHipX = jointCoordX;
				usersInfo[i].leftHipY = jointCoordY;
			}
			else
			{
				// Sets the coordinates as -1 to indicate they are not available
				usersInfo[i].leftHipX = -1;
				usersInfo[i].leftHipY = -1;
			}

			// If the right joint of hip is detected
			if ( getJointCoordinates(user, nite::JOINT_RIGHT_HIP, jointCoordX, jointCoordY) )
			{
				// Saves the coordinates of the joint
				usersInfo[i].rightHipX = jointCoordX;
				usersInfo[i].rightHipY = jointCoordY;
			}
			else
			{
				// Sets the coordinates as -1 to indicate they are not available
				usersInfo[i].rightHipX = -1;
				usersInfo[i].rightHipY = -1;
			}

			// Sets the state of the user as 'tracking'
			usersInfo[i].userState = TRACKING;
		}
		// If the user is not new and their skeleton is being calibrated
		else if (user.getSkeleton().getState() == nite::SKELETON_CALIBRATING)
		{
			// Sets the state of the user as 'calibrating'
			usersInfo[i].userState = CALIBRATING;
		}
		// If the user is not new and their skeleton is not detected
		else if (user.getSkeleton().getState() == nite::SKELETON_NONE)
		{
			// Sets the state of the user as 'stopped'
			usersInfo[i].userState = STOPPED;

			// Tries to track the skeleton of the user again
			userTracker.startSkeletonTracking(user.getId());
		}
	}

	// If no user was detected
	if (users.getSize() == 0)
	{
		usersInfo[0].userState = USER_NOT_FOUND;
		usersInfo[1].userState = USER_NOT_FOUND; // ¿? por qué solo para los dos primeros usuarios? -> cambiar
	}
}


/////////////////////////////////////////////////////////////////////
/////////////// OTHER FUNCTIONS /////////////////////////////////////
/////////////////////////////////////////////////////////////////////

/**
 Inserts a image that overwrite all points of the RGB frame where there is not any user, as if it were a chroma.

 @param [out] frameColor Frame containing the image of the RGB sensor.
 @param [in] frameImageLoaded Image to show in the background.

 @return Nothing.
*/
void Kinect::insertChroma(cv::Mat &frameColor, cv::Mat frameImageLoaded)
{
	Vec3b color;

	// Specifies a size equal to screen size
	Size size(WIN_SIZE_X, WIN_SIZE_Y);

	// Resizes background image in a new frame
	Mat frameChroma;
	resize(frameImageLoaded, frameChroma, size);

	
	if ( userTracker.readFrame( &userTrackerFrame ) == nite::STATUS_OK )
	{
		const nite::UserMap& userMap = userTrackerFrame.getUserMap();
		const nite::UserId* mapaUsuario = userMap.getPixels();

		for (int y = 0; y < userMap.getHeight(); y++)
		{
			for (int x = 0; x < userMap.getWidth(); x++)
			{
				unsigned int uIdx = x + userMap.getWidth() * y;
			
				// If in that pixel there is no user
				if (mapaUsuario[uIdx] == 0)
				{
					color = frameChroma.at<Vec3b>(cv::Point(x, y));
					// Draws the pixel with the color of the background image
					circle(frameColor, cv::Point(x, y), 1, cv::Scalar(color[0],color[1],color[2]), -1);
				}
			}
		}
	}
}


/**
 Gets the number of users.

 @return Number of users.
*/
int Kinect::getUsersNumber()
{
	return usersNumber;
}
