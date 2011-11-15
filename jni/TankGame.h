#ifndef _TANKGAME_H
#define _TANKGAME_H

#include <GLES2/gl2.h>
#include <vector>

#include "libk3d/k3d.h"
#include "Tank.h"

class Tank;

// This could be a static class
// i.e. since only one instance of TankGame will be used by an app
// anyways, there's no point of allowing creation of multiple instances.
// but it could have some uses when it comes to multiplayer (I doubt it tho)
class TankGame
{
friend class Tank;
    GLuint gProgram;
    GLuint gvColor;

    k3d::model floor;
    k3d::model walls;
    std::vector<Tank> tanks;

    void renderFrame();
public:
    void loadLevel();

    bool reshape(int w, int h);

    void initialize();

    void step();
};

#endif //_TANKGAME_H
