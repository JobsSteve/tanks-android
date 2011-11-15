#ifndef _TANKGAME_H
#define _TANKGAME_H

#include <GLES2/gl2.h>
#include <vector>

#include "libk3d/k3d.h"
#include "Tank.h"

class Tank;

class TankGame
{
friend class Tank;
    GLuint gProgram;
    GLuint gvPositionHandle;
    GLuint gvNormalHandle;
    GLuint gmModelViewHandle;
    GLuint gmModelViewProjectionHandle;
    GLuint gmNormalMatrixHandle;
    GLuint gvColorHandle;
    GLuint gvLightSource0Handle;

    k3d::mat4 mProjection;
    k3d::mat4 modelView;
    k3d::model floor;
    k3d::model walls;
    std::vector<Tank> tanks;

    void loadlevel();

    void renderFrame();
public:
    TankGame() { loadlevel(); }

    bool reshape(int w, int h);

    void initialize();

    void step();
};

#endif //_TANKGAME_H
