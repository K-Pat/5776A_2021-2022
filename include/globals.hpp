#include "main.h";

//contoller
extern Controller controller;

//motors
const int LIFT = 16;
const int LB = 6; //left bottom drive
const int LM = 13; //left mid drive
const int LT = 5; //left top drive
const int RB = 10; 
const int RM = 11; 
const int RT = 1; 
const int CONVEYOR = 2;

//sensors
const int _IMU = 14;
const int _IMU2 = 20;
const char LPOT = 'A';
const char RPOT = 'B';

//pneumatics
const char LTILT = 'C';
const char RTILT = 'D';
const char FCLAMP = 'E';
const char BCLAMP = 'F';
