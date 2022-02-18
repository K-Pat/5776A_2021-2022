#include "main.h"
using namespace okapi;

namespace drive {
    driveState curState;

    Motor leftBottom(LB, false, AbstractMotor::gearset::blue, AbstractMotor::encoderUnits::degrees);
    Motor leftMid(LM, false, AbstractMotor::gearset::blue, AbstractMotor::encoderUnits::degrees);
    Motor leftTop(LT, false, AbstractMotor::gearset::blue, AbstractMotor::encoderUnits::degrees);
    Motor rightBottom(RB, true, AbstractMotor::gearset::blue, AbstractMotor::encoderUnits::degrees);
    Motor rightMid(RM, true, AbstractMotor::gearset::blue, AbstractMotor::encoderUnits::degrees);
    Motor rightTop(RT, true, AbstractMotor::gearset::blue, AbstractMotor::encoderUnits::degrees);

    MotorGroup leftDrive = {leftBottom, leftMid, leftTop};
    MotorGroup rightDrive = {rightBottom, rightMid, rightTop};

    IMU imu(_IMU, IMUAxes::z);
    IMU imu2(_IMU2, IMUAxes::z);

    std::shared_ptr<ChassisController> chassis =
        ChassisControllerBuilder()
        .withMotors(leftDrive, rightDrive)
        .withDimensions(AbstractMotor::gearset::blue, {{4_in, 10_in}, imev5BlueTPR})
        .build();

    IterativePosPIDController translatePID = IterativeControllerFactory::posPID(0.0045, 0, 0.0002);
    IterativePosPIDController turnPID = IterativeControllerFactory::posPID(0.016, 0.00003, 0.0084);
    IterativePosPIDController swervePID = IterativeControllerFactory::posPID(0, 0, 0); //TODO

    void setMotors(auto mode) {
        leftDrive.setBrakeMode(mode);
        rightDrive.setBrakeMode(mode);
    }

    void init() {
        curState = coast;
    }

    void act() {
        switch(curState) {
            case hold:
                setMotors(AbstractMotor::brakeMode::hold);
                break;
            case coast:
                setMotors(AbstractMotor::brakeMode::coast);
                break;
        }
        chassis->getModel()->arcade(controller.getAnalog(ControllerAnalog::leftY), controller.getAnalog(ControllerAnalog::leftX));
    }

    void update() {
        if (controller.getDigital(ControllerDigital::A) == 1) {
            if (curState == coast) {
                setMotors(AbstractMotor::brakeMode::hold);
            } else {
                setMotors(AbstractMotor::brakeMode::coast);
            }
        }
    }
}
