#include "main.h"
using namespace okapi;

namespace lift {
    enum liftState {
        move = 'm',
        hold = 'h',
    };
    extern double upTarget;
    extern double downTarget;
    extern double platTarget;
    extern double curTarget;
    extern liftState curState;
    extern void init();
    extern void update();
    extern void act();
    extern AsyncPosIntegratedController liftController;
};
