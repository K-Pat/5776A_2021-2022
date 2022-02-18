#include "main.h"
using namespace okapi;

namespace clamp {
    clampState curState;

    pros::ADIDigitalOut fclamp(FCLAMP);

    void init() {
        fclamp.set_value(1);
        curState = hard;
    }

    void act() {
        switch(curState) {
            case hard:
                fclamp.set_value(1);
                break;
            case soft:
                fclamp.set_value(0);
                break;
        }
    }

    void update() {
        if (controller.getDigital(ControllerDigital::L1)) {
            curState = hard;
        } else if (controller.getDigital(ControllerDigital::L2)) {
            curState = soft;
        }
    }
}
