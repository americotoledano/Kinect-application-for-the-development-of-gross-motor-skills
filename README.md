Kinect Application for the Development of Gross Motor Skills
=======
## Introduction

Application that identifies and tracks the different parts of the user's body using the Kinect sensor. This application is aimed at people with gross motor problems, with the aim of improving their motor skills by proposing different motor challenges to the user.

This application, which was developed as a degree project, runs on an Ubuntu GNU/Linux operating system. It is coded in c++, using the OpenNI and NiTE open source Kinect libraries, the OpenCV and Cairo graphic libraries and the SQLite database management system.

## Requirements
* GNU/Linux Ubuntu 12.04 LTS, 32 bits
* Microsoft Kinect sensor
* Kinect USB adapter cable

## Operation
Running the program, it shows a window with three tabs: play, database management, and data export.
 
The **database management tab** consist of three sections: user management, specialist management, and user-specialist connection. In these sections is possible to add, update, remove or show users or specialist, and link a user with a specific specialist.

![alt text](https://raw.githubusercontent.com/erictol/Kinect-application-for-the-development-of-gross-motor-skills/master/img/screenshots/dbmanagement-tab.png)

In the **data export tab** is possible to export the information of the data base to a \*.csv file. These data are the games of a user, the data of a game, the list of registered users and the list of specialists.

![alt text](https://raw.githubusercontent.com/erictol/Kinect-application-for-the-development-of-gross-motor-skills/master/img/screenshots/export-data-tab.png)
 
In the **play tab**, the game options must be configured to run it. The first parameter is the user, who is choosen between the users registered in the database. Others parameters are the duration of the game and the duration of the fruit (difficulty level). Clicking the button below, the game will be run.

![alt text](https://raw.githubusercontent.com/erictol/Kinect-application-for-the-development-of-gross-motor-skills/master/img/screenshots/play-tab.png)

### Game interface
![alt text](https://raw.githubusercontent.com/erictol/Kinect-application-for-the-development-of-gross-motor-skills/master/img/screenshots/game-interface.png)
1. User image
2. Indicator circle of hand position
3. User status
4. Fruit
5. Progress bar timer
6. Mistakes scoreboard
7. Successes scoreboard
8. Clock
