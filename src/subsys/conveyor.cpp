#include "main.h"
using namespace okapi;

namespace conveyor {
    conveyorState curState;

    Motor conveyor(CONVEYOR, false, AbstractMotor::gearset::blue, AbstractMotor::encoderUnits::degrees);

    void init() {
        curState = rest;
        conveyor.moveVoltage(0);
    }

    void act() {
        switch(curState) {
            case in:
                conveyor.moveVelocity(-600); //shit ion know
                break;
            case out:
                conveyor.moveVelocity(600);
                break;
            case rest:
                conveyor.moveVoltage(0);
                break;
        };
    }

    void update() {
        if (controller.getDigital(ControllerDigital::R1)) {
            curState = in;
        } else if (controller.getDigital(ControllerDigital::R2)) {
            curState = out;
        } else {
            curState = rest;
        }
    }
}
