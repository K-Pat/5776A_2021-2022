#include "main.h"
using namespace okapi;

namespace drive {
    enum driveState {
        hold = 'h',
        coast = 'c'
    };
    extern driveState curState;
    extern std::shared_ptr<ChassisController> drive;
    extern void init();
    extern void update();
    extern void act();
    extern IterativePosPIDController translatePID;
    extern IterativePosPIDController turnPID;
    extern IterativePosPIDController swervePID;
    extern IMU imu;
    extern IMU imu2;
};