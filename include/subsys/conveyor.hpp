#include "main.h"
using namespace okapi;

namespace conveyor {
    enum conveyorState {
        in = 'i',
        out = 'o',
        rest = 'r'
    };
    extern conveyorState curState;
    extern void init();
    extern void update();
    extern void act();
};