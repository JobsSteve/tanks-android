#include <math.h>

#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

#include "util.h"
#include "TankGame.h"

void TankGame::initialize()
{
    const char *vsfilename = "/sdcard/tanks/tanks.vs";
    const char *fsfilename = "/sdcard/tanks/tanks.fs";

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

    glViewport(0, 0, w, h);
    checkGlError("glViewport");

    mProjection.loadIdentity();
    mProjection.perspective(-1.0, 1.0, 1.0*ratio, -1.0*ratio, -1.5, -20);

    return true;
}

void TankGame::loadlevel()
{
    floor.loadObj("/sdcard/tanks/floor.obj");
    walls.loadObj("/sdcard/tanks/teapot.obj");
}

void TankGame::renderFrame()
{
    static float angle = 0.0;

    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    checkGlError("glClear");

    k3d::mat4 modelView;
    k3d::mat4 normalMatrix;
    k3d::vec3 light(1.5, 2.8, 2.4);

    glUseProgram(gProgram);
    checkGlError("glUseProgram");

    modelView.lookAt(k3d::vec3(3.2, 4.2, 5.9), k3d::vec3(0.0, 0.0, 0.0), k3d::vec3(0.0, 1.0, 0.0));

    light = modelView * light;
    glUniform3f(gvLightSource0Handle, light.x, light.y, light.z);
    checkGlError("glUniform3f");

    modelView.glUniform(gmModelViewHandle);
    checkGlError("glUniformMatrix4fv1");
    normalMatrix = modelView;
    normalMatrix.inverse().transpose();
    normalMatrix.glUniform(gmNormalMatrixHandle);
    checkGlError("glUniformMatrix4fv2");
    (mProjection * modelView).glUniform(gmModelViewProjectionHandle);
    checkGlError("glUniformMatrix4fv3");

    glUniform4f(gvColorHandle, 1.0, 1.0, 1.0, 1.0);
    checkGlError("glUniform4f");
    walls.draw(gvPositionHandle, gvNormalHandle);

    angle += 0.01;
}

void TankGame::step()
{
    renderFrame();
}
