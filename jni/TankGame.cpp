#include <math.h>

#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

#include "util.h"
#include "TankGame.h"

using k3d::gl;

// There's some oop non intuitiveness here
// this should really be called only once...
// again this stems from the fact that TankGame
// should basically be static
void TankGame::initialize()
{
    const char *vsfilename = "/sdcard/tanks/tanks.vs";
    const char *fsfilename = "/sdcard/tanks/tanks.fs";
    GLuint gvPosition, gvNormal;
    GLuint gmModelView;
    GLuint gmModelViewProjection;
    GLuint gmNormalMatrix;
    GLuint gvColor;
    GLuint gvLightSource0;

    glClearColor(0.0, 0.0, 0.0, 1.0f);
    checkGlError("glClearColor");

    printGLString("Version", GL_VERSION);
    printGLString("Vendor", GL_VENDOR);
    printGLString("Renderer", GL_RENDERER);
    printGLString("Extensions", GL_EXTENSIONS);

    gProgram = createProgram(readFile(vsfilename), readFile(fsfilename));
    if (!gProgram) {
        LOGE("Could not create program.");
        return;
    }

    glUseProgram(gProgram);
    checkGlError("glUseProgram");

    gvPosition = glGetAttribLocation(gProgram, "vPosition");
    checkGlError("glGetAttribLocation");
    LOGI("glGetAttribLocation(\"vPosition\") = %d\n",
            gvPosition);

    gvNormal = glGetAttribLocation(gProgram, "vNormal");
    checkGlError("glGetAttribLocation");
    LOGI("glGetAttribLocation(\"vNormal\") = %d\n",
            gvNormal);

    gmModelView = glGetUniformLocation(gProgram, "mModelView");
    checkGlError("glGetUniformLocation");
    LOGI("glGetUniformLocation(\"mModelView\") = %d\n",
            gmModelView);

    gmNormalMatrix = glGetUniformLocation(gProgram, "mNormalMatrix");
    checkGlError("glGetUniformLocation");
    LOGI("glGetUniformLocation(\"mNormalMatrix\") = %d\n",
            gmNormalMatrix);

    gmModelViewProjection = glGetUniformLocation(gProgram, "mModelViewProjection");
    LOGI("glGetUniformLocation(\"mModelViewProjection\") = %d\n",
            gmModelViewProjection);

    gvLightSource0 = glGetUniformLocation(gProgram, "vLightSource0");
    LOGI("glGetUniformLocation(\"vLightSource0\") = %d\n",
            gvLightSource0);

    gvColor = glGetUniformLocation(gProgram, "vColor");
    checkGlError("glGetUniformLocation");
    LOGI("glGetUniformLocation(\"vColor\") = %d\n",
            gmModelView);

    k3d::gl::initialize(gvPosition, gvNormal, gmModelView, gmModelViewProjection,
            gmNormalMatrix, gvColor, gvLightSource0);

    int depth;
    glEnable(GL_DEPTH_TEST);
    glGetIntegerv(GL_DEPTH_BITS, &depth);
    LOGI("GL_DEPTH_BITS = %d\n\tmeander\n", depth);
}

bool TankGame::reshape(int w, int h)
{
    touchW = w;
    touchH = h;

    float ratio = (float)h/(float)w;

    glViewport(0, 0, w, h);
    checkGlError("glViewport");

    gl::mProjection.loadIdentity();
    gl::mProjection.perspective(-1.0, 1.0, 1.0*ratio, -1.0*ratio, -1.0, -40);

    return true;
}

void TankGame::loadLevel()
{
    me.pos = k3d::vec2(3.0, 4.0);
    me.aim =  k3d::vec2(1.0, 0.0);
    me.velocity = k3d::vec2(1.0,0.0);

    eye = k3d::vec3(0.0, -3.0, 15.0);

    lvl.width = 24;
    lvl.height = 18;
}

void TankGame::renderFrame()
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    checkGlError("glClear");

    k3d::mat4 tmpMat;
    k3d::vec3 light(4.0, 3.0, 20.0);

    glUseProgram(gProgram);
    checkGlError("glUseProgram");

    gl::mModelView.loadIdentity();
    gl::mModelView.lookAt(k3d::vec3(me.pos.x, me.pos.y - 1.5, 7.0), k3d::vec3(me.pos.x, me.pos.y, 0.0), k3d::vec3(0.0, 1.0, 0.0));

    gl::vLight0 = light;
    gl::sendLight0();

    tmpMat = gl::mModelView;

    lvl.draw();

    gl::mModelView = tmpMat;
    gl::sendMatrices();
    me.draw();
}

void TankGame::step()
{
    renderFrame();
    me.pos = me.pos + me.speed*me.velocity;
}

void TankGame::touch(int x, int y, bool down)
{
    LOGI("touch(%d,%d)\n", x, y);
    if (down == true) {
        me.velocity = (k3d::vec2(x - touchW/2, touchH/2 - y).normalize());
        me.speed = 0.1;
    } else {
        me.speed = 0.0;
    }
}
