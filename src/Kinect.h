/**
 @file   Kinect.h
 @author Pedro Américo Toledano López
 @date   May, 2015
 @brief  Class to handle the kinect sensor, using OpenNI and NiTE.
*/

#ifndef KINECT_H
#define KINECT_H

#include <OpenNI.h>
#include <NiTE.h>

//OpenCV includes
#include "cv.h"
#include "highgui.h"
#include "cvaux.h"

//Freenect includes
#include "../../libfreenect-master/wrappers/c_sync/libfreenect_sync.h"
#include "../../libfreenect-master/include/libfreenect.h"

#include <cstring>


//Macros
#define WIN_SIZE_X	640
#define WIN_SIZE_Y	480

#define MAX_USERS	10


using namespace std;

/** Origins of a frame */
enum CameraMode {NI_SENSOR_DEPTH, NI_SENSOR_COLOR};

/** State of a user */
enum UserState {USER_NOT_FOUND, USER_FOUND, CALIBRATING, TRACKING, STOPPED};

/** Options of streams */
enum StreamOption {RGB, DEPTH, RGB_AND_DEPTH};

/** Holds the coordinates and user state of an user */
struct userInfo
{
	/* X-coordinate of the right hand */
	float rightHandX;
	/* Y-coordinate of the right hand */
	float rightHandY;
	/* X-coordinate of the left hand */
	float leftHandX;
	/* Y-coordinate of the left hand */
	float leftHandY;
	/* X-coordinate of the head */
	float headX;
	/* Y-coordinate of the head */
	float headY;
	/* X-coordinate of the neck */
	float neckX;
	/* Y-coordinate of the neck */
	float neckY;
	/* X-coordinate of the left shoulder */
	float leftShoulderX;
	/* Y-coordinate of the left shoulder */
	float leftShoulderY;
	/* X-coordinate of the right shoulder */
	float rightShoulderX;
	/* Y-coordinate of the right shoulder */
	float rightShoulderY;
	/* X-coordinate of the left elbow */
	float leftElbowX;
	/* Y-coordinate of the left elbow */
	float leftElbowY;
	/* X-coordinate of the right elbow */
	float rightElbowX;
	/* Y-coordinate of the right elbow */
	float rightElbowY;
	/* X-coordinate of the left hip */
	float leftHipX;
	/* Y-coordinate of the left hip */
	float leftHipY;
	/* X-coordinate of the right hip */
	float rightHipX;
	/* Y-coordinate of the right hip */
	float rightHipY;
	/* State of the user */
	UserState userState;
};


class Kinect
{
	public:
		Kinect();
		~Kinect();
		int init();

		// OpenNI functions
		bool openDevice(const char* deviceURI);
		int createDepthStream();
		int createColorStream();
		bool syncDepthColor();
		int startRecordStream(const char * fileName, StreamOption streamOption);
		void stopRecordStream();
		bool readFrame(cv::Mat &frame, CameraMode camMode);

		// NITE functions
		bool startUserTracking();
		bool readTrackerFrame();
		int getJointCoordinates(const nite::UserData& user, nite::JointType jointType, float &coordX, float &coordY);
		void usersManagement();

		// Other functions
		void insertChroma(cv::Mat &frameColor, cv::Mat frameImageLoaded);
		int getUsersNumber();

		userInfo usersInfo[MAX_USERS];

	private:
		// openni
		openni::Status rc;
		openni::Device device;
		openni::VideoStream depth;
		openni::VideoStream color;
		openni::Recorder recorder;
		openni::VideoFrameRef depthFrame;
		// nite
		nite::Status niteRc;
		nite::UserTracker userTracker;
		nite::UserTrackerFrameRef userTrackerFrame;


		int usersNumber;
};

#endif
