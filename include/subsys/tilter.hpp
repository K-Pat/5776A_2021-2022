#include "main.h"
using namespace okapi;

namespace tilter {
    enum tilterState {
        hard = 'h',
        soft = 's'
    };
    extern tilterState curState;
    extern void init();
    extern void update();
    extern void act();
};