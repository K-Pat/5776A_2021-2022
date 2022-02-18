#include "main.h"
using namespace okapi;

namespace tilter {
    tilterState curState;

    pros::ADIDigitalOut rtilt(RTILT);
    pros::ADIDigitalOut ltilt(LTILT);
    pros::ADIDigitalOut bclamp(BCLAMP);

    void init() {
        bclamp.set_value(1);
        rtilt.set_value(0);
        ltilt.set_value(0);
        curState = soft;
    }

    void act() {
        switch(curState) {
            case hard:
                rtilt.set_value(1);
                ltilt.set_value(1);
                pros::delay(50);
                bclamp.set_value(0);
                break;
            case soft:
                bclamp.set_value(1);
                pros::delay(50);
                rtilt.set_value(0);
                ltilt.set_value(0);
                break;
        }
    }

    void update() {
        if (controller.getDigital(ControllerDigital::B)) {
            curState = hard;
        } else if (controller.getDigital(ControllerDigital::X)) {
            curState = soft;
        }
    }
}
