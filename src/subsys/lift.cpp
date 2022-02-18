#include "main.h"
using namespace okapi;

namespace lift {
    liftState curState;

    Motor lift(LIFT, false, AbstractMotor::gearset::red, AbstractMotor::encoderUnits::degrees);
    auto pot = Potentiometer(LPOT);
    auto pot2 = Potentiometer(RPOT);

    double upTarget = 690; //should be higher for turtling
    double downTarget = 15;
    double platTarget = 550;
    double curTarget = 0;

    AsyncPosIntegratedController liftController(
        std::shared_ptr<Motor>(&lift),
        AbstractMotor::gearset::red,
        100
    ); //figure out how to use pots with AsyncPosIntegratedController

    void togglePID() {
        liftController.flipDisable(!liftController.isDisabled());
    }

    void init() {
        curState = hold;
        lift.tarePosition();
    }

    void act() {
        switch(curState) {
            case move:
                togglePID();
                lift.moveVelocity(controller.getAnalog(ControllerAnalog::rightY));
                break;
            case hold:
                togglePID();
                liftController.setTarget(curTarget);
                break;
        };
    }

    void update() {
        if (controller.getAnalog(ControllerAnalog::rightY) != 0) {
            curState = move;
            return;
        }
        curState = hold;
        if (controller.getDigital(ControllerDigital::up)) {
            curTarget = upTarget;
        } else if (controller.getDigital(ControllerDigital::down)) {
            curTarget = downTarget;
        } else if (controller.getDigital(ControllerDigital::left)) {
            curTarget = platTarget;
        } else {
            curTarget = (pot.get()+pot2.get())/2;
        }
    }
}
