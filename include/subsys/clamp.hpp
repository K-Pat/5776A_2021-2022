#include "main.h"
using namespace okapi;

namespace clamp {
    enum clampState {
        hard = 'h',
        soft = 's'
    };
    extern clampState curState;
    extern void init();
    extern void update();
    extern void act();
};