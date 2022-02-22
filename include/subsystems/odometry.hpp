#include "main.h"

using namespace okapi;

namespace odometry{
  extern ADIEncoder Left;
  extern ADIEncoder Right;
  extern ADIEncoder Back;
  extern double posX;//X position of robot
  extern double posY;//Y position of robot
  extern double orientation; //orientation of robot
  extern const double Tl; //distance between tracking center to the Left Tracker wheel
  extern const double Tr; //distance between tracking center to the right Tracker wheel
  extern const double Tb; //distance between tracking center to the back Tracker wheel
  extern void initOdometry();
  extern void updateOdometry();
  extern void OdomDriveToPoint();
  extern void OdomTranslate();
  extern void OdomRotate();
}
