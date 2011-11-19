#ifndef _TANK_H
#define _TANK_H

#include "libk3d/k3d.h"
#include "TankGame.h"

class Tank {
    static k3d::model mTreads;
    static k3d::model mHead;

public:
    k3d::vec2 pos;
    k3d::vec2 velocity; // direction
    float speed; // magnitude
    k3d::vec2 aim;

    Tank() {}
    Tank(k3d::vec2 ppos, k3d::vec2 vel, k3d::vec2 aaim) : pos(ppos), velocity(vel), aim(aaim), speed(0.0) {}

    void draw();
};

#endif // _TANK_H
