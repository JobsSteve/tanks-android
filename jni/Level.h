#ifndef _LEVEL_H
#define _LEVEL_H

#include "libk3d/k3d.h"

class Level {
    static k3d::model mFloor;
    static k3d::model mCube;

public:
    int width, height;
    Level() : width(24), height(18) {}

    void draw();
    //TODO void loadFromFile(filename);

};

#endif // _LEVEL_H
