#include <math.h>

#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

#include "util.h"
#include "TankGame.h"

bool TankGame::setupGraphics(int w, int h)
{
    const char *vsfilename = "/sdcard/tanks/tanks.vs";
    const char *fsfilename = "/sdcard/tanks/tanks.fs";

    printGLString("Version", GL_VERSION);
    printGLString("Vendor", GL_VENDOR);
    printGLString("Renderer", GL_RENDERER);
    printGLString("Extensions", GL_EXTENSIONS);

    LOGI("setupGraphics(%d, %d)", w, h);
    gProgram = createProgram(readFile(vsfilename), readFile(fsfilename));
    if (!gProgram) {
        LOGE("Could not create program.");
        return false;
    }

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

    gvColorHandle = glGetUniformLocation(gProgram, "vColor");
    checkGlError("glGetUniformLocation");
    LOGI("glGetUniformLocation(\"vColor\") = %d\n",
            gmModelViewHandle);

    glViewport(0, 0, w, h);
    checkGlError("glViewport");

    glClearColor(0.0, 0.0, 0.0, 1.0f);
    checkGlError("glClearColor");

    glUseProgram(gProgram);
    checkGlError("glUseProgram");

    return true;
}

void TankGame::loadlevel()
{
    floor.loadObj("/sdcard/tanks/floor.obj");
    walls.loadObj("/sdcard/tanks/wall.obj");
}

void TankGame::renderFrame()
{
    static float angle = 0.0;

    glClear(GL_COLOR_BUFFER_BIT);

    k3d::mat4 modelView;
    k3d::mat4 temp;

    modelView.infPerspective();
    modelView.lookAt(k3d::vec3(1.0, 2.0, 5.0), k3d::vec3(0.0, 0.0, 0.0), k3d::vec3(0.0, 1.0, 0.0));
    temp = modelView;

    modelView.scalef(5.0, 5.0, 1.0);
    modelView.glUniform(gmModelViewHandle);

    glUniform4f(gvColorHandle, 0.3, 0.26, 0.1, 1.0);
    floor.draw(gvPositionHandle, gvNormalHandle);

    modelView = temp;
    modelView.translatef(2.0, 1.0, 1.0);
    modelView.scalef(0.5, 0.5, 0.5);
    modelView.glUniform(gmModelViewHandle);

    glUniform4f(gvColorHandle, 0.0, 1.0, 0.0, 1.0);
    walls.draw(gvPositionHandle, gvNormalHandle);

    angle += 0.01;
}

void TankGame::step()
{
    renderFrame();
}
