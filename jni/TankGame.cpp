#include <math.h>

#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

#include "util.h"
#include "TankGame.h"

void TankGame::initialize()
{
    const char *vsfilename = "/sdcard/tanks/tanks.vs";
    const char *fsfilename = "/sdcard/tanks/tanks.fs";

    Tank::initialize();

    LOGI("TankGame::initialize()\n");

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

    gvPositionHandle = glGetAttribLocation(gProgram, "vPosition");
    checkGlError("glGetAttribLocation");
    LOGI("glGetAttribLocation(\"vPosition\") = %d\n",
            gvPositionHandle);

    gvNormalHandle = glGetAttribLocation(gProgram, "vNormal");
    checkGlError("glGetAttribLocation");
    LOGI("glGetAttribLocation(\"vNormal\") = %d\n",
            gvNormalHandle);

    gmModelViewHandle = glGetUniformLocation(gProgram, "mModelView");
    checkGlError("glGetUniformLocation");
    LOGI("glGetUniformLocation(\"mModelView\") = %d\n",
            gmModelViewHandle);

    gmNormalMatrixHandle = glGetUniformLocation(gProgram, "mNormalMatrix");
    checkGlError("glGetUniformLocation");
    LOGI("glGetUniformLocation(\"mNormalMatrix\") = %d\n",
            gmNormalMatrixHandle);

    gmModelViewProjectionHandle = glGetUniformLocation(gProgram, "mModelViewProjection");
    LOGI("glGetUniformLocation(\"mModelViewProjection\") = %d\n",
            gmModelViewProjectionHandle);

    gvLightSource0Handle = glGetUniformLocation(gProgram, "vLightSource0");
    LOGI("glGetUniformLocation(\"vLightSource0\") = %d\n",
            gvLightSource0Handle);

    gvColorHandle = glGetUniformLocation(gProgram, "vColor");
    checkGlError("glGetUniformLocation");
    LOGI("glGetUniformLocation(\"vColor\") = %d\n",
            gmModelViewHandle);

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

    mProjection.loadIdentity();
    mProjection.perspective(-1.0, 1.0, 1.0*ratio, -1.0*ratio, -1.5, -20);

    return true;
}

void TankGame::loadlevel()
{
    floor.loadObj("/sdcard/tanks/floor.obj");
    walls.loadObj("/sdcard/tanks/wall.obj");
    tanks.push_back(Tank(this, k3d::vec2(-6.0, 0.0)));
}

void TankGame::renderFrame()
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    checkGlError("glClear");

    k3d::mat4 tmpMat;
    k3d::mat4 normalMatrix;
    k3d::vec3 light(0.5, 0.8, 5.0);

    glUseProgram(gProgram);
    checkGlError("glUseProgram");

    modelView.loadIdentity();
    modelView.lookAt(k3d::vec3(-8.0, 0.0, 0.2), k3d::vec3(0.0, 0.0, 0.0), k3d::vec3(0.0, 0.0, 1.0));

    light = modelView * light;
    glUniform3f(gvLightSource0Handle, light.x, light.y, light.z);
    checkGlError("glUniform3f");

    tmpMat = modelView;

    modelView.scalef(8.0, 8.0, 1.0);

    modelView.glUniform(gmModelViewHandle);
    checkGlError("glUniformMatrix4fv1");
    normalMatrix = modelView;
    normalMatrix.inverse().transpose();
    normalMatrix.glUniform(gmNormalMatrixHandle);
    checkGlError("glUniformMatrix4fv2");
    (mProjection * modelView).glUniform(gmModelViewProjectionHandle);
    checkGlError("glUniformMatrix4fv3");

    glUniform4f(gvColorHandle, 0.4, 0.33, 0.29, 1.0);
    checkGlError("glUniform4f");
    floor.draw(gvPositionHandle, gvNormalHandle);

    modelView = tmpMat;

    modelView.glUniform(gmModelViewHandle);
    checkGlError("glUniformMatrix4fv1");
    normalMatrix = modelView;
    normalMatrix.inverse().transpose();
    normalMatrix.glUniform(gmNormalMatrixHandle);
    checkGlError("glUniformMatrix4fv2");
    (mProjection * modelView).glUniform(gmModelViewProjectionHandle);
    checkGlError("glUniformMatrix4fv3");

    glUniform4f(gvColorHandle, 0.1, 0.8, 2.9, 1.0);
    checkGlError("glUniform4f");

    for (unsigned i = 0; i < tanks.size(); i++)
        tanks[i].draw(gvPositionHandle, gvNormalHandle);
}

void TankGame::step()
{
    for (unsigned i = 0; i < tanks.size(); i++)
        tanks[i].step();

    renderFrame();
}
