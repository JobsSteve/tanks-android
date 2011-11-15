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
    GLuint gvLightSource0;

    // Again this is a load level kinda thing
    // but we need to do it only once so.....
    Tank::initialize();

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
                        gmNormalMatrix, gvLightSource0);

    int depth;
    glEnable(GL_DEPTH_TEST);
    glGetIntegerv(GL_DEPTH_BITS, &depth);
    LOGI("GL_DEPTH_BITS = %d\n", depth);
}

bool TankGame::reshape(int w, int h)
{
    float ratio = (float)h/(float)w;

    LOGI("TankGame::reshape()\n");

    glViewport(0, 0, w, h);
    checkGlError("glViewport");

    gl::mProjection.loadIdentity();
    gl::mProjection.perspective(-1.0, 1.0, 1.0*ratio, -1.0*ratio, -1.5, -20);

    return true;
}

void TankGame::loadLevel()
{
    floor.loadObj("/sdcard/tanks/floor.obj");
    walls.loadObj("/sdcard/tanks/wall.obj");
    tanks.clear();
    tanks.push_back(Tank(k3d::vec2(-6.0, 0.0)));
    tanks.push_back(Tank(k3d::vec2(1.0, 1.0)));
}

void TankGame::renderFrame()
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    checkGlError("glClear");

    k3d::mat4 tmpMat;
    k3d::vec3 light(0.5, 0.8, 5.0);

    glUseProgram(gProgram);
    checkGlError("glUseProgram");

    gl::mModelView.loadIdentity();
    gl::mModelView.lookAt(k3d::vec3(0.0, -3.0, 15.0), k3d::vec3(0.0, 0.0, 0.0), k3d::vec3(0.0, 1.0, 0.0));

    gl::vLight0 = light;
    gl::sendLight0();

    tmpMat = gl::mModelView;

    gl::mModelView.scalef(8.0, 8.0, 1.0);
    gl::sendMatrices();
    glUniform4f(gvColor, 0.4, 0.33, 0.29, 1.0);
    checkGlError("glUniform4f");
    floor.draw();

    gl::mModelView = tmpMat;
    gl::sendMatrices();
    glUniform4f(gvColor, 0.1, 0.8, 2.9, 1.0);
    checkGlError("glUniform4f");
    for (unsigned i = 0; i < tanks.size(); i++)
        tanks[i].draw();
}

void TankGame::step()
{
    for (unsigned i = 0; i < tanks.size(); i++)
        tanks[i].step();

    renderFrame();
}
