#include <math.h>

#include "Tank.h"
#include "util.h"

using k3d::gl;

k3d::model Tank::mTreads("/sdcard/tanks/tank_treads.obj");
k3d::model Tank::mHead("/sdcard/tanks/tank_head.obj");

void Tank::draw()
{
    /**
     * Tank models draw a tank centred and on the xy plane
     * i.e. the tank lies in z > 0. It also is within the
     * canonical GL volume. It is aiming and facing in -Y
     */

    float _velRotation[4][4] = {
        { -velocity.y,  velocity.x, 0.0, 0.0 },
        { -velocity.x, -velocity.y, 0.0, 0.0 },
        { 0.0, 0.0, 1.0, 0.0 },
        { 0.0, 0.0, 0.0, 1.0 },
    };

    float _aimRotation[4][4] = {
        { -aim.y,  aim.x, 0.0, 0.0 },
        { -aim.x, -aim.y, 0.0, 0.0 },
        { 0.0, 0.0, 1.0, 0.0 },
        { 0.0, 0.0, 0.0, 1.0 },
    };

    k3d::mat4 mMVBackup(gl::mModelView);
    k3d::mat4 velRotation(_velRotation);
    k3d::mat4 aimRotation(_aimRotation);

    gl::sendColor(0.1, 0.8, 0.29, 1.0);

    gl::mModelView.translatef(pos.x, pos.y, 0.0);
    gl::mModelView = gl::mModelView * velRotation;
    gl::sendMatrices();
    mTreads.draw();

    gl::mModelView = mMVBackup;
    gl::mModelView.translatef(pos.x, pos.y, 0.0);
    gl::mModelView = gl::mModelView * aimRotation;
    gl::sendMatrices();
    mHead.draw();

    gl::mModelView = mMVBackup;
}
