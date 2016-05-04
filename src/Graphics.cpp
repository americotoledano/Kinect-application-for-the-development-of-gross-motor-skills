/**
 @file   Graphics.cpp
 @author Pedro Américo Toledano López
 @date   August, 2015
 @brief  Class to handle the graphics of the game.
*/

#include "Graphics.h"
#include "cvaux.h" // Include for OpenCV
#include "highgui.h" // Include for imread() function of OpenCV
#include <cairo/cairo.h> // Include of Cairo Graphic Library

using namespace std;
using namespace cv;


/**
 Constructor.
*/
Graphics::Graphics()
{
	//Seed for random numbers
	srand(time(NULL));

	//Loads keyboard images
	frameA = imread("./img/keyboard/A.png", CV_LOAD_IMAGE_COLOR);
	frameB = imread("./img/keyboard/B.png", CV_LOAD_IMAGE_COLOR);
	frameC = imread("./img/keyboard/C.png", CV_LOAD_IMAGE_COLOR);
	frameD = imread("./img/keyboard/D.png", CV_LOAD_IMAGE_COLOR);
	frameE = imread("./img/keyboard/E.png", CV_LOAD_IMAGE_COLOR);
	frameF = imread("./img/keyboard/F.png", CV_LOAD_IMAGE_COLOR);
	frameG = imread("./img/keyboard/G.png", CV_LOAD_IMAGE_COLOR);
	frameH = imread("./img/keyboard/H.png", CV_LOAD_IMAGE_COLOR);
	frameI = imread("./img/keyboard/I.png", CV_LOAD_IMAGE_COLOR);
	frameJ = imread("./img/keyboard/J.png", CV_LOAD_IMAGE_COLOR);
	frameK = imread("./img/keyboard/K.png", CV_LOAD_IMAGE_COLOR);
	frameL = imread("./img/keyboard/L.png", CV_LOAD_IMAGE_COLOR);
	frameM = imread("./img/keyboard/M.png", CV_LOAD_IMAGE_COLOR);
	frameN = imread("./img/keyboard/N.png", CV_LOAD_IMAGE_COLOR);
	frameNN = imread("./img/keyboard/NN.png", CV_LOAD_IMAGE_COLOR);
	frameO = imread("./img/keyboard/O.png", CV_LOAD_IMAGE_COLOR);
	frameP = imread("./img/keyboard/P.png", CV_LOAD_IMAGE_COLOR);
	frameQ = imread("./img/keyboard/Q.png", CV_LOAD_IMAGE_COLOR);
	frameR = imread("./img/keyboard/R.png", CV_LOAD_IMAGE_COLOR);
	frameS = imread("./img/keyboard/S.png", CV_LOAD_IMAGE_COLOR);
	frameT = imread("./img/keyboard/T.png", CV_LOAD_IMAGE_COLOR);
	frameU = imread("./img/keyboard/U.png", CV_LOAD_IMAGE_COLOR);
	frameV = imread("./img/keyboard/V.png", CV_LOAD_IMAGE_COLOR);
	frameW = imread("./img/keyboard/W.png", CV_LOAD_IMAGE_COLOR);
	frameX = imread("./img/keyboard/X.png", CV_LOAD_IMAGE_COLOR);
	frameY = imread("./img/keyboard/Y.png", CV_LOAD_IMAGE_COLOR);
	frameZ = imread("./img/keyboard/Z.png", CV_LOAD_IMAGE_COLOR);
	frame0 = imread("./img/keyboard/0.png", CV_LOAD_IMAGE_COLOR);
	frame1 = imread("./img/keyboard/1.png", CV_LOAD_IMAGE_COLOR);
	frame2 = imread("./img/keyboard/2.png", CV_LOAD_IMAGE_COLOR);
	frame3 = imread("./img/keyboard/3.png", CV_LOAD_IMAGE_COLOR);
	frame4 = imread("./img/keyboard/4.png", CV_LOAD_IMAGE_COLOR);
	frame5 = imread("./img/keyboard/5.png", CV_LOAD_IMAGE_COLOR);
	frame6 = imread("./img/keyboard/6.png", CV_LOAD_IMAGE_COLOR);
	frame7 = imread("./img/keyboard/7.png", CV_LOAD_IMAGE_COLOR);
	frame8 = imread("./img/keyboard/8.png", CV_LOAD_IMAGE_COLOR);
	frame9 = imread("./img/keyboard/9.png", CV_LOAD_IMAGE_COLOR);
	frameSpace = imread("./img/keyboard/space.png", CV_LOAD_IMAGE_COLOR);
	frameDelete = imread("./img/keyboard/delete.png", CV_LOAD_IMAGE_COLOR);
	frameEnterKey = imread("./img/keyboard/enter.png", CV_LOAD_IMAGE_COLOR);
	frameKeyboardBackground = imread("./img/keyboard/keyboardInputBackground.png", CV_LOAD_IMAGE_COLOR);

	keySize = 46;
	keySeparation = 51; //Separation between x coordinate of a key and the x coordinate of the key beside
	keyboardInitialX = 540;
	keyboardInitialY = 120;

	enterKey.width = 497;
	enterKey.height = 46;
	enterKey.x = 85;
	enterKey.y = 40;

	keyboardBackground.width = 640;
	keyboardBackground.height = 140;
	keyboardBackground.x = 0;
	keyboardBackground.y = 340;


	frameYesButton = imread("./img/yesButton.png", CV_LOAD_IMAGE_COLOR);
	frameNoButton = imread("./img/noButton.png", CV_LOAD_IMAGE_COLOR);
	yesButton.width = 245;
	noButton.width = 245;
	yesButton.height = 46;
	noButton.height = 46;

	yesButton.y = 40;
	noButton.y = 40;
	noButton.x = 85;
	yesButton.x = 337;


	frameNewGameButton = imread("./img/newGameButton.png", CV_LOAD_IMAGE_COLOR);
	frameExitButton = imread("./img/exitButton.png", CV_LOAD_IMAGE_COLOR);
	newGameButton.width = 150;
	exitButton.width = 150;
	newGameButton.height = 90;
	exitButton.height = 90;

	newGameButton.y = 80;
	exitButton.y = 80;
	newGameButton.x = 370;
	exitButton.x = 105;

	frameApple = imread("./img/fruits/apple80.png", CV_LOAD_IMAGE_COLOR);
	frameCherry = imread("./img/fruits/cherry80.png", CV_LOAD_IMAGE_COLOR);
	frameOrange = imread("./img/fruits/orange80.png", CV_LOAD_IMAGE_COLOR);
	frameTomato = imread("./img/fruits/tomato80.png", CV_LOAD_IMAGE_COLOR);
	frameWatermelon = imread("./img/fruits/watermelon80.png", CV_LOAD_IMAGE_COLOR);
	frameFruit = frameApple;

	fruit.x = 460;
	fruit.y = 40;
	fruit.width = 80;
	fruit.height = 80;

	keySize = 46;
	keySeparation = 51; //Separation between x coordinate of a key and the x coordinate of the key beside
	keyboardInitialX = 540;
	keyboardInitialY = 120;//90

	frameGameJoint = imread("./img/handjoint.png", CV_LOAD_IMAGE_COLOR);
	frameSelectJoint = imread("./img/keyboard/keyButton60.png", CV_LOAD_IMAGE_COLOR);

	gameJoint.width = 100;
	gameJoint.height = 100;
	selectJoint.width = 60;
	selectJoint.height = 60;

	
	frameBottomBar = imread("./img/bottomBar.png", CV_LOAD_IMAGE_COLOR);

	bottomBar.width = 640;
	bottomBar.height = 76;
	bottomBar.x = 0;
	bottomBar.y = 404;

	chosenImage = 0;
}


/**
 Empty destructor.
*/
Graphics::~Graphics()
{
	
}


/**
 Inserts a joint marker for the game.

 @param [out] frameColor Frame containing the image of the RGB sensor.
 @param [in] x Coordinate x of the joint.
 @param [in] y Coordinate y of the joint.

 @return Nothing.
*/
void Graphics::showGameJoint(Mat &frameColor, float x, float y)
{
	insertImage(frameColor, frameGameJoint, x-(gameJoint.width/2), y-(gameJoint.height/2), gameJoint.width, gameJoint.height);
}


/**
 Shows the fruit of the game.

 @param [out] frameColor Frame containing the image of the RGB sensor.

 @return Nothing.
*/
void Graphics::showFruit(Mat &frameColor)
{
	//Inserts a fruit image
	insertImage(frameColor, frameFruit, fruit.x, fruit.y, fruit.width, fruit.height);
}


/**
 Shows a clock around the fruit so the user can know how much time is left before it dissapears.

 @param [out] frameColor Frame containing the image of the RGB sensor.
 @param [in] time Time of the fruit in microseconds.
 @param [in] fruitDuration Maximum duration of the fruit before it dissapears.

 @return Nothing;
*/
void Graphics::showFruitClock(Mat &frameColor, unsigned long long int time, int fruitDuration)
{
	unsigned long long int angle = 360 * time / (fruitDuration*1000000);

	if(angle > 0)
		cv::ellipse(frameColor, Point(flipXCoordinate(fruit.x, fruit.width) + fruit.width/2, fruit.y + fruit.height/2), cvSize(50,50), 90., /*startAngle*/0, /*endAngle*/angle, RED, 7, 8, 0);
}


/**
 Shows the bottom bar of the game interface.

 @param [out] frameColor Frame containing the image of the RGB sensor.

 @return Nothing.
*/
void Graphics::showBottomBar(Mat &frameColor)
{
	insertImage(frameColor, frameBottomBar, bottomBar.x, bottomBar.y, bottomBar.width, bottomBar.height);
}


/**
 Shows a scoring marker.

 @param [out] frameColor Frame containing the image of the RGB sensor.
 @param [in] successes Score of successes of the game.
 @param [in] failures Score of failures of the game.

 @return Nothing.
*/
void Graphics::showScore(Mat &frameColor, string successes, string failures)
{
	putTextCairo(frameColor, successes, cv::Point2d(130, 440), "arial", 40, WHITE, true);
	putTextCairo(frameColor, failures, cv::Point2d(55, 440), "arial", 40, WHITE, true);
}


/**
 Shows a timer.

 @param [out] frameColor Frame containing the image of the RGB sensor.
 @param [in] duration Current duration of the game.

 @return Nothing.
*/
void Graphics::showTimer(Mat &frameColor, int duration)
{
	int minutes, seconds;
	string timer;

	if(duration >= 60)
	{
		minutes = duration / 60;
		seconds = duration - (minutes*60);
	}
	else
	{
		minutes = 0;
		seconds = duration;
	}

	if(seconds>9)
		timer = itos(minutes) + ":" + itos(seconds);
	else
		timer = itos(minutes) + ":0" + itos(seconds);

	putTextCairo(frameColor, timer, cv::Point2d(220, 455), "arial", 40, WHITE, true);
}


/**
 Inserts a text to show what is the state of the user.

 @param [out] frameColor Frame containing the image of the RGB sensor.
 @param [in] x userState Description of the state to be shown.

 @return Nothing.
*/
void Graphics::showUserState(Mat &frameColor, string userState)
{
	putTextCairo(frameColor, userState, cv::Point2d(630, 465), "arial", 30, WHITE, false);
}


/**
 Shows the score screen when the game ends.

 @param [out] frameColor Frame containing the image of the RGB sensor.
 @param [in] successes Number of successes in the game.
 @param [in] failures Number of failures in the game.

 @return Nothing.
*/
void Graphics::showScoreScreen(Mat &frameColor, string successes, string failures)
{
	putTextCairo(frameColor, "Fin de juego", cv::Point2d(WIN_SIZE_X/2, 220), "arial", 60, WHITE, true);
	putTextCairo(frameColor, successes, cv::Point2d(410, 340), "arial", 60, GREEN, true);
	putTextCairo(frameColor, failures, cv::Point2d(220, 340), "arial", 60, RED, true);

	insertImage(frameColor, frameExitButton, exitButton.x, exitButton.y, exitButton.width, exitButton.height);
	insertImage(frameColor, frameNewGameButton, newGameButton.x, newGameButton.y, newGameButton.width, newGameButton.height);
}


/**
 Shows the pause screen when the game is paused.

 @param [out] frameColor Frame containing the image of the RGB sensor.

 @return Nothing.
*/
void Graphics::showPauseScreen(Mat &frameColor)
{
	putTextCairo(frameColor, "JUEGO EN PAUSA", cv::Point2d(320, 240), "arial", 40, WHITE, true);
}


/**
 Calculates if a joint intersects with a fruit.

 @param [in] x Coordinate in x-axis of the joint.
 @param [in] y Coordinate in y-axis of the joint.
 @return True if coordinates of the joint intersects with the fruit, false otherwise.
*/
bool Graphics::intersectionFruit(float x, float y)
{
	return( intersection(fruit.width, fruit.height, fruit.x, fruit.y, x, y) );
}


/**
 Calculates the intersection between the 'new game' button and a joint (a hand).

 @param [in] x Coordinate x of the joint.
 @param [in] y Coordinate y of the joint.

 @return True if coordinates of the joint intersects with a image, false otherwise.
*/
bool Graphics::intersectionNewGameButton(float x, float y)
{
	if( intersection(newGameButton.width, newGameButton.height, newGameButton.x, newGameButton.y, x, y) )
		return true;
	else
		return false;
}


/**
 Calculates the intersection between the 'exit' button and a joint (a hand).

 @param [in] x Coordinate x of the joint.
 @param [in] y Coordinate y of the joint.

 @return True if coordinates of the joint intersects with a image, false otherwise.
*/
bool Graphics::intersectionExitButton(float x, float y)
{
	if( intersection(exitButton.width, exitButton.height, exitButton.x, exitButton.y, x, y) )
		return true;
	else
		return false;
}


/**
 Change the position of the fruit with a random position.

 @param [out] x Coordinate x.
 @param [out] y Coordinate y.

 @return Nothing.
*/
void Graphics::changeFruit(float &x, float &y)
{
	int previousImage = chosenImage;
	int fruitQuadrant = getQuadrant(fruit.x, fruit.y);

	// Selects a new fruit image randomly, but not the same image that before
	do
	{
		chosenImage = rand() % 5;
	}while( previousImage == chosenImage );

	// Changes the image for the new image selected.
	switch(chosenImage)
	{
		case 0: frameFruit = frameApple; break;
		case 1: frameFruit = frameCherry; break;
		case 2: frameFruit = frameOrange; break;
		case 3: frameFruit = frameTomato; break;
		case 4: frameFruit = frameWatermelon; break;
	}
	
	// Changes the position of the fruit image ramdomly, but not in the same quadrant
	do
	{
		//number = rand () % (N-M+1) + M;   // Number is between M and N
		fruit.x = rand() % ((WIN_SIZE_X-fruit.width) - 0 + 1) + 0;
		fruit.y = rand() % ((WIN_SIZE_Y-fruit.height-bottomBar.height) - 0 + 1) + 0;
	}while(fruitQuadrant == getQuadrant(fruit.x, fruit.y));

	// Sends the new position values
	x = fruit.x;
	y = fruit.y;
}


/**
 Inserts a joint marker for the keyboard.

 @param [out] frameColor Frame containing the image of the RGB sensor.
 @param [in] x Coordinate x of the joint.
 @param [in] y Coordinate y of the joint.

 @return Nothing.
*/
void Graphics::showSelectJoint(Mat &frameColor, float x, float y)
{
	insertImage(frameColor, frameSelectJoint, x-(selectJoint.width/2), y-(selectJoint.height/2), selectJoint.width, selectJoint.height);
}


/**
 Inserts the keys of the keyboard.

 @param [out] frameColor Frame containing the image of the RGB sensor.

 @return Nothing.
*/
void Graphics::showKeyboard(Mat &frameColor)
{
			// Inserts the enter key
			insertImage(frameColor, frameEnterKey, enterKey.x, enterKey.y, enterKey.width, enterKey.height);

			// Inserts the keys of the first row of the keyboard
			insertImage(frameColor, frameQ, keyboardInitialX, keyboardInitialY, keySize, keySize);
			insertImage(frameColor, frameW, keyboardInitialX-1*keySeparation, keyboardInitialY, keySize, keySize);
			insertImage(frameColor, frameE, keyboardInitialX-2*keySeparation, keyboardInitialY, keySize, keySize);
			insertImage(frameColor, frameR, keyboardInitialX-3*keySeparation, keyboardInitialY, keySize, keySize);
			insertImage(frameColor, frameT, keyboardInitialX-4*keySeparation, keyboardInitialY, keySize, keySize);
			insertImage(frameColor, frameY, keyboardInitialX-5*keySeparation, keyboardInitialY, keySize, keySize);
			insertImage(frameColor, frameU, keyboardInitialX-6*keySeparation, keyboardInitialY, keySize, keySize);
			insertImage(frameColor, frameI, keyboardInitialX-7*keySeparation, keyboardInitialY, keySize, keySize);
			insertImage(frameColor, frameO, keyboardInitialX-8*keySeparation, keyboardInitialY, keySize, keySize);
			insertImage(frameColor, frameP, keyboardInitialX-9*keySeparation, keyboardInitialY, keySize, keySize);

			// Inserts the keys of the second row of the keyboard
			insertImage(frameColor, frameA, keyboardInitialX, keyboardInitialY+1*keySeparation, keySize, keySize);
			insertImage(frameColor, frameS, keyboardInitialX-1*keySeparation, keyboardInitialY+1*keySeparation, keySize, keySize);
			insertImage(frameColor, frameD, keyboardInitialX-2*keySeparation, keyboardInitialY+1*keySeparation, keySize, keySize);
			insertImage(frameColor, frameF, keyboardInitialX-3*keySeparation, keyboardInitialY+1*keySeparation, keySize, keySize);
			insertImage(frameColor, frameG, keyboardInitialX-4*keySeparation, keyboardInitialY+1*keySeparation, keySize, keySize);
			insertImage(frameColor, frameH, keyboardInitialX-5*keySeparation, keyboardInitialY+1*keySeparation, keySize, keySize);
			insertImage(frameColor, frameJ, keyboardInitialX-6*keySeparation, keyboardInitialY+1*keySeparation, keySize, keySize);
			insertImage(frameColor, frameK, keyboardInitialX-7*keySeparation, keyboardInitialY+1*keySeparation, keySize, keySize);
			insertImage(frameColor, frameL, keyboardInitialX-8*keySeparation, keyboardInitialY+1*keySeparation, keySize, keySize);
			insertImage(frameColor, frameNN, keyboardInitialX-9*keySeparation, keyboardInitialY+1*keySeparation, keySize, keySize);

			// Inserts the keys of the third row of the keyboard
			insertImage(frameColor, frameZ, keyboardInitialX, keyboardInitialY+2*keySeparation, keySize, keySize);
			insertImage(frameColor, frameX, keyboardInitialX-1*keySeparation, keyboardInitialY+2*keySeparation, keySize, keySize);
			insertImage(frameColor, frameC, keyboardInitialX-2*keySeparation, keyboardInitialY+2*keySeparation, keySize, keySize);
			insertImage(frameColor, frameV, keyboardInitialX-3*keySeparation, keyboardInitialY+2*keySeparation, keySize, keySize);
			insertImage(frameColor, frameB, keyboardInitialX-4*keySeparation, keyboardInitialY+2*keySeparation, keySize, keySize);
			insertImage(frameColor, frameN, keyboardInitialX-5*keySeparation, keyboardInitialY+2*keySeparation, keySize, keySize);
			insertImage(frameColor, frameM, keyboardInitialX-6*keySeparation, keyboardInitialY+2*keySeparation, keySize, keySize);
			insertImage(frameColor, frameSpace, keyboardInitialX-8*keySeparation, keyboardInitialY+2*keySeparation, keySize*2+4/*(keySeparation-keySize)*/, keySize);
			insertImage(frameColor, frameDelete, keyboardInitialX-9*keySeparation, keyboardInitialY+2*keySeparation, keySize, keySize);

			// Inserts the numbers keys of the keyboard
			insertImage(frameColor, frame1, keyboardInitialX, keyboardInitialY+3*keySeparation, keySize, keySize);
			insertImage(frameColor, frame2, keyboardInitialX-1*keySeparation, keyboardInitialY+3*keySeparation, keySize, keySize);
			insertImage(frameColor, frame3, keyboardInitialX-2*keySeparation, keyboardInitialY+3*keySeparation, keySize, keySize);
			insertImage(frameColor, frame4, keyboardInitialX-3*keySeparation, keyboardInitialY+3*keySeparation, keySize, keySize);
			insertImage(frameColor, frame5, keyboardInitialX-4*keySeparation, keyboardInitialY+3*keySeparation, keySize, keySize);
			insertImage(frameColor, frame6, keyboardInitialX-5*keySeparation, keyboardInitialY+3*keySeparation, keySize, keySize);
			insertImage(frameColor, frame7, keyboardInitialX-6*keySeparation, keyboardInitialY+3*keySeparation, keySize, keySize);
			insertImage(frameColor, frame8, keyboardInitialX-7*keySeparation, keyboardInitialY+3*keySeparation, keySize, keySize);
			insertImage(frameColor, frame9, keyboardInitialX-8*keySeparation, keyboardInitialY+3*keySeparation, keySize, keySize);
			insertImage(frameColor, frame0, keyboardInitialX-9*keySeparation, keyboardInitialY+3*keySeparation, keySize, keySize);

			// Inserts the keyboard text input background
			insertImage(frameColor, frameKeyboardBackground, keyboardBackground.x, keyboardBackground.y, keyboardBackground.width, keyboardBackground.height);
}


/**
 Shows two button with 'yes' and 'no' options.

 @param [out] frameColor Frame containing the image of the RGB sensor.
 @param [in] query String containing the question.

 @return Nothing.
*/
void Graphics::showDialog(Mat &frameColor, string query)
{
	insertImage(frameColor, frameYesButton, yesButton.x, yesButton.y, yesButton.width, yesButton.height);
	insertImage(frameColor, frameNoButton, noButton.x, noButton.y, noButton.width, noButton.height);

	// Inserts the keyboard text input background
	insertImage(frameColor, frameKeyboardBackground, keyboardBackground.x, keyboardBackground.y, keyboardBackground.width, keyboardBackground.height);

	putTextCairo(frameColor, query, cv::Point2d(WIN_SIZE_X/2, 360), "arial", 30, Scalar(255,255,255), true);
	putTextCairo(frameColor, "¿Es correcto?", cv::Point2d(WIN_SIZE_X/2, 400), "arial", 30, Scalar(255,255,255), true);
}


/**
 Calculates if a joint intersects with a key of the keyboard.

 @param [in] row Row in the keyboard where the key is.
 @param [in] column Column in the keyboard where the key is.
 @param [in] x Coordinate in x-axis of the joint.
 @param [in] y Coordinate in y-axis of the joint.
 @returns True if coordinates of the joint intersects the key, false otherwise.
*/
bool Graphics::intersectionKey(int row, int column, float x, float y)
{
	return( intersection(keySize, keySize, keyboardInitialX-(column*keySeparation), keyboardInitialY+(row*keySeparation), x, y) );
}


/**
 Calculates if a joint intersects with the "return to menu" button.

 @param [in] x Coordinate in x-axis of the joint.
 @param [in] y Coordinate in y-axis of the joint.
 @returns True if coordinates of the joint intersects with the enter key, false otherwise.
*/
bool Graphics::intersectionEnterKey(float x, float y)
{
	return( intersection(enterKey.width+40, enterKey.height, enterKey.x, enterKey.y, x, y) );
}


/**
 Calculates the intersection between a joint and any button of a dialog.

 @param [in] x X-coordinate of the joint.
 @param [in] y Y-coordinate of the joint.
 @param [out] answer A number with a value according to the button intersected.

 @return True if any button was intersected, false otherwise.
*/
bool Graphics::intersectionDialog(float x, float y, int &answer)
{
	if( intersection(yesButton.width, yesButton.height, yesButton.x, yesButton.y, x, y) )
	{
		answer = 1;
		return true;
	}
	else if( intersection(noButton.width, noButton.height, noButton.x, noButton.y, x, y) )
	{
		answer = 0;
		return true;
	}
	else
	{
		answer = -1;
		return false;
	}
}


/**
 Gets the value of a key of the keyboard given its row and column.

 @param [in] row Row of the key.
 @param [in] column Column of the key.

 @return A string containing the value of the key.
*/
string Graphics::getQwertyKey(int row, int column)
{
	return( qwertyKeyboard[row][column] );
}


/**
 Calculates if a joint intersects with an area (e.g. a image).

 @param [in] imageWidth Width of the area.
 @param [in] imageHeight Height of the area.
 @param [in] imageCoordX Coordinate in x-axis of the area.
 @param [in] imageCoordY Coordinate in y-axis of the area.
 @param [in] jointCoordX Coordinate in x-axis of the joint.
 @param [in] jointCoordY Coordinate in y-axis of the joint.

 @return True if coordinates of the joint intersects with a image, false otherwise.
*/
bool Graphics::intersection(int imageWidth, int imageHeight, float imageCoordX, float imageCoordY, float jointCoordX, float jointCoordY)
{
	if( (jointCoordX >= imageCoordX) && (jointCoordX <= imageCoordX + imageWidth) )
	{
		if( (jointCoordY >= imageCoordY) && (jointCoordY <= imageCoordY + imageHeight) )
			return true;
		else
			return false;
	}
	else
	{
		return false;
	}
}


/**
 Inserts a image in the RGB frame.

 @param [out] frameColor Frame containing the image of the RGB sensor.
 @param [out] frameImagen Frame containing the image to insert.
 @param [in] coordX Coordinate in x-axis of the destination of the image.
 @param [in] coordY Coordinate in y-axis of the destination of the image.
 @param [in] imageWidth Width of the area.
 @param [in] imageHeight Height of the area.

 @return Nothing.
*/
void Graphics::insertImage(cv::Mat &frameColor, cv::Mat &frameImagen, float coordX, float coordY, int imageWidth, int imageHeight)
{
	Mat dst, img2gray, mask, mask_inv, img1_bg, img2_fg;

	coordX = flipXCoordinate(coordX, imageWidth);

	if ( !(coordX + imageWidth > WIN_SIZE_X || coordY + imageHeight > WIN_SIZE_Y || coordX < 0 || coordY < 0) )
	{
		// Selects a region of interest (ROI)
		Mat roi(frameColor, Rect(coordX, coordY, imageWidth, imageHeight));

		// Makes the image mask and the image inverse
		//// Gets the image mask in greyscale
		cvtColor(frameImagen, img2gray, COLOR_BGR2GRAY, 0);
		//// Makes the image mask
		threshold(img2gray, mask, 10, 255, THRESH_BINARY);
		//// Inverts the bits of the image mask to gets the inverse
		bitwise_not(mask, mask_inv);

		Mat aux = mask;

		// Black colour in the ROI
		bitwise_and(roi, roi, img1_bg, mask = mask_inv);

		// Gets the image area
		bitwise_and(frameImagen, frameImagen, img2_fg, mask = aux);

		// Inserts the image in the ROI
		add(img1_bg, img2_fg, dst);
	

		dst.copyTo(roi);
	}
}


/**
 Inserts a text in the RGB frame.

 @param [in] text Text to be inserted.
 @param [in] x Coordinate in x-axis of the position of the text.
 @param [in] y Coordinate in y-axis of the position of the text.
 @param [out] frameColor Frame containing the image of the RGB sensor.

 @return Nothing.
*/
void Graphics::showText(string text, int x, int y, cv::Mat &frameColor) // ya no se usa
{
	Point coord;
    coord.x = x;
    coord.y = y;

	putText(frameColor, text, coord, cv::FONT_HERSHEY_DUPLEX, 1, cv::Scalar(255,255,255), 1, 8, false);
}


/**
 Inserts a text in the RGB frame.

 @param [out] frameColor Frame containing the image of the RGB sensor.
 @param [in] text Text to be inserted.
 @param [in] centerPoint Coordinate of the center point of the text.
 @param [in] fontFace Text font for the text.
 @param [in] fontSize Size of the text.
 @param [in] textColor Color of the text.
 @param [in] centered Sets if the text must be centered in the coordinate or begin from there.

 @return Nothing.
*/
void Graphics::putTextCairo(cv::Mat &frameColor, string const& text, Point2d centerPoint, string const& fontFace, double fontSize, Scalar textColor, bool centered)
{
    // Create Cairo
    cairo_surface_t* surface =
            cairo_image_surface_create(
                CAIRO_FORMAT_ARGB32,
                frameColor.cols,
                frameColor.rows);

    cairo_t* cairo = cairo_create(surface);

    // Wrap Cairo with a Mat
    cv::Mat cairoTarget(
                cairo_image_surface_get_height(surface),
                cairo_image_surface_get_width(surface),
                CV_8UC4,
                cairo_image_surface_get_data(surface),
                cairo_image_surface_get_stride(surface));

    // Put image onto Cairo
    cv::cvtColor(frameColor, cairoTarget, cv::COLOR_BGR2BGRA);

    // Set font and write text
    cairo_select_font_face (
                cairo,
                fontFace.c_str(),
                CAIRO_FONT_SLANT_NORMAL,
                CAIRO_FONT_WEIGHT_NORMAL);

    cairo_set_font_size(cairo, fontSize);
    cairo_set_source_rgb(cairo, textColor[2], textColor[1], textColor[0]);

    cairo_text_extents_t extents;
    cairo_text_extents(cairo, text.c_str(), &extents);

	// If option 'centered' was set
	if(centered)
	{
		cairo_move_to(
		            cairo,
		            flipXCoordinate(centerPoint.x, 0) - extents.width/2 - extents.x_bearing,
		            centerPoint.y - extents.height/2- extents.y_bearing);
	}
	else
	{
		cairo_move_to(
		            cairo,
		            flipXCoordinate(centerPoint.x, 0),
		            centerPoint.y);		
	}




    cairo_show_text(cairo, text.c_str());

    // Copy the data to the output image
    cv::cvtColor(cairoTarget, frameColor, cv::COLOR_BGRA2BGR);

    cairo_destroy(cairo);
    cairo_surface_destroy(surface);
}


/**
 Converts an integer in a string.

 @param [in] number Number to be converted.

 @return The string containing the number.
*/
string Graphics::itos(int number)
{
	ostringstream convert;

	// Inserts the textual representation of 'score' in the characters in the stream
	convert << number;      

	return ( convert.str() );
}


/**
 Calculates the quadrant of a coordinate.

 @param [in] x Coordinate x.
 @param [in] y Coordinate y.

 @return Number of quadrant.
*/
int Graphics::getQuadrant(float x, float y)
{
	if(x >= WIN_SIZE_X/2)
	{
		if(y >= WIN_SIZE_Y/2)
			return 3;
		else// if(y < WIN_SIZE_Y/2)
			return 2;
	}
	else// if(x < WIN_SIZE_X/2)
	{
		if(y >= WIN_SIZE_Y/2)
			return 4;
		else// if(y < WIN_SIZE_Y/2)
			return 1;
	}
}


/**
 Changes the coordinates system for this images inserted after the RGB frame is flipped

 @param [in] x Coordinate in x-axis to be converted.
 @param [in] width Width of the image.

 @return A value for x in the new coordinates system.
*/
float Graphics::flipXCoordinate(float x, int width)
{
	if (x < (WIN_SIZE_X/2))
		return( (WIN_SIZE_X/2) + abs((WIN_SIZE_X/2) - x) ) - width;
	else if (x > (WIN_SIZE_X/2))
		return( (WIN_SIZE_X/2) - abs((WIN_SIZE_X/2) - x) ) - width;
	else// if (x == (WIN_SIZE_X/2))
		return x;
}
