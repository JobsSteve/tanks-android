#include "Level.h"

using k3d::gl;

k3d::model Level::mFloor("/sdcard/tanks/floor.obj");
k3d::model Level::mCube("/sdcard/tanks/wall.obj");

void Level::draw()
{
    // the floor model is a square with side length = 2
    // and centred at the origin in the xy plane

    k3d::mat4 mMVBackup(gl::mModelView);

    gl::sendColor(0.4, 0.33, 0.29, 1.0);

    gl::mModelView.scalef(width, height, 1.0);
    gl::mModelView.scalef(0.5, 0.5, 1.0);
    gl::mModelView.translatef(1.0, 1.0, 0.0);
    gl::sendMatrices();
    Level::mFloor.draw();

    // the cube model is a cube from 0,0,0 to 1,1,1

    gl::mModelView = mMVBackup;
    gl::sendColor(1.0, 0.00, 0.0, 1.0);

    gl::mModelView.translatef(1.0, 3.0, 0.0);
    gl::mModelView.scalef(3.0, 1.0, 0.3);
    gl::sendMatrices();
    mCube.draw();

    gl::mModelView = mMVBackup;
}
