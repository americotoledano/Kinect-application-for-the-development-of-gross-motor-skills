/**
 @file   Graphics.h
 @author Pedro Américo Toledano López
 @date   August, 2015
 @brief  Class to handle the graphics of the game.
*/

#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "cvaux.h" // Include for OpenCV

//Macros
#define WIN_SIZE_X	640
#define WIN_SIZE_Y	480

#define WHITE	Scalar(255, 255, 255)
#define YELLOW	Scalar(0, 100, 255)
#define BLUE	Scalar(255, 0, 0)
#define GREEN	Scalar(0, 255, 0)
#define RED		Scalar(0, 0, 255)


using namespace cv;

/** Hold the values and positions of the keys of the keyboard */
const string qwertyKeyboard[4][10] = {{"Q", "W", "E", "R", "T", "Y", "U", "I", "O", "P"}, {"A", "S", "D", "F", "G", "H", "J", "K", "L", "Ñ"}, {"Z", "X", "C", "V", "B", "N", "M", " ", " ", "delete"}, {"1", "2", "3", "4", "5", "6", "7", "8", "9", "0"}};

/** Hold the value of a image */
struct ImageInfo
{
	/* Width of the image */
	int width;
	/* Height of the image */
	int height;
	/* X-coordinate of the image */
	float x;
	/* Y-coordinate of the image */
	float y;
};



class Graphics
{
	public:
		Graphics();
		~Graphics();

		////////////////////////////
		/// Graphics of the game ///
		////////////////////////////
		// Functions to insert graphics in the game
		void showGameJoint(Mat &frameColor, float x, float y);
		void showFruit(Mat &frameColor);
		void showFruitClock(Mat &frameColor, unsigned long long int time, int fruitDuration);
		void showBottomBar(Mat &frameColor);
		void showScore(Mat &frameColor, string successes, string failures);
		void showTimer(Mat &frameColor, int duration);
		void showUserState(Mat &frameColor, string userState);
		void showScoreScreen(Mat &frameColor, string successes, string failures);
		void showPauseScreen(Mat &frameColor);

		// Functions to calculate the intersection with graphics of the game
		bool intersectionFruit(float x, float y);
		bool intersectionNewGameButton(float x, float y);
		bool intersectionExitButton(float x, float y);

		// Others
		void changeFruit(float &x, float &y);


		////////////////////////////////
		/// Graphics of the keyboard ///
		////////////////////////////////
		// Functions to insert graphics in the keyboard
		void showSelectJoint(Mat &frameColor, float x, float y);
		void showKeyboard(Mat &frameColor);
		void showDialog(Mat &frameColor, string query);

		// Functions to calculate the intersection with graphics of the keyboard
		bool intersectionKey(int row, int column, float x, float y);
		bool intersectionEnterKey(float x, float y);
		bool intersectionDialog(float x, float y, int &answer);

		// Others
		string getQwertyKey(int row, int column);

		///////////////////////////
		/// Auxiliary functions ///
		///////////////////////////
		bool intersection(int imageWidth, int imageHeight, float imageCoordX, float imageCoordY, float jointCoordX, float jointCoordY);

		void insertImage(cv::Mat &frameColor, cv::Mat &frameImagen, float coordX, float coordY, int imageSizeX, int imageSizeY);
		void showText(string text, int x, int y, cv::Mat &frameColor);
		void putTextCairo(cv::Mat &targetImage, string const& text, Point2d centerPoint, string const& fontFace, double fontSize, Scalar textColor, bool centered);
		string itos(int number);
		int getQuadrant(float x, float y);
		float flipXCoordinate(float x, int width);


		ImageInfo enterKey;


	private:
		// Keys of the keyboard
		Mat frameA, frameB, frameC, frameD, frameE, frameF, frameG, frameH, frameI, frameJ, frameK, frameL, frameM, frameN, frameNN, frameO, frameP, frameQ, frameR, frameS, frameT, frameU, frameV, frameW, frameX, frameY, frameZ;
		Mat frame1, frame2, frame3, frame4, frame5, frame6, frame7, frame8, frame9, frame0;
		Mat frameSpace;
		Mat frameDelete;
		Mat frameEnterKey;
		Mat frameKeyboardBackground;
		Mat frameYesButton, frameNoButton;
		Mat frameNewGameButton, frameExitButton; // Buttons of the score screen

		Mat frameApple, frameCherry, frameOrange, frameTomato, frameWatermelon; // Fruit images
		Mat frameFruit; // Fruit to be shown

		Mat frameGameJoint; // Round marker of joints in the game
		Mat frameSelectJoint; // Round marker of joints in the keyboard
		Mat frameBottomBar; // Bottom bar of the game interface

		ImageInfo fruit; // Size and position of the fruit
		ImageInfo yesButton, noButton; // Size and position of the yes/no buttons
		ImageInfo newGameButton, exitButton; // Size and position of the buttons of the score screen
		ImageInfo gameJoint, selectJoint; // Size and position of the joint markers
		ImageInfo bottomBar;  // Size and position of the bottom bar of the game interface
		ImageInfo keyboardBackground;

		int keySize;
		int keySeparation; //Separation between x coordinate of a key and the x coordinate of the key beside
		int keyboardInitialX;
		int keyboardInitialY;
		int chosenImage; // Number of fruit chosen
};


#endif
