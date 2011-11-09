#ifndef _TANKGAME_H
#define _TANKGAME_H

#include <GLES2/gl2.h>
#include <vector>

#include "k3d.h"

class TankGame
{
    GLuint gProgram;
    GLuint gvPositionHandle;
    GLuint gvNormalHandle;
    GLuint gmModelViewHandle;

    k3d::model floor;
    k3d::model walls;
    std::vector<k3d::model> tanks;

    void loadlevel();

    void renderFrame();
public:
    TankGame() { loadlevel(); }

    bool setupGraphics(int w, int h);

    void step();
};

#endif //_TANKGAME_H
