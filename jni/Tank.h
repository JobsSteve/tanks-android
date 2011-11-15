#ifndef _TANK_H
#define _TANK_H

#include "libk3d/k3d.h"
#include "TankGame.h"

class TankGame; // To Get Around circular dependency

class Tank {
    const static char * const treadsObj;
    const static char * const headObj;
    static k3d::model mTreads;
    static k3d::model mHead;

    k3d::vec2 pos;
    k3d::vec2 velocity; // direction
    float speed; // magnitude
    k3d::vec2 aim;

public:
    Tank(k3d::vec2 ppos) : pos(ppos), aim(0.0, 0.0), velocity(0.0, 0.0) {}

    static void initialize();

    void draw();

    void step();
};

#endif // _TANK_H
