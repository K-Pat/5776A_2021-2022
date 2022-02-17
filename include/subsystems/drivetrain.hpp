#include "main.h"

using namespace okapi;

extern Motor leftBack;
extern Motor leftFront;
extern Motor rightBack;
extern Motor rightFront;
extern IMU inertial_sensor;
extern IMU inertial_sensor2; 

extern std::shared_ptr<ChassisController> drive;

void updateDrive();

void translatePID(double distance, int ms);

void rotatePID(double turnDegrees, int ms);
