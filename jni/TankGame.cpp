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
}

void TankGame::renderFrame()
{
    k3d::mat4 modelView;

    modelView.translatef(1.0, 0.0, 1.0);
    modelView.scalef(0.5, 0.5, 1.0);
    modelView.glUniform(gmModelViewHandle);
    floor.draw(gvPositionHandle, gvNormalHandle);
}

void TankGame::step()
{
    renderFrame();
}
