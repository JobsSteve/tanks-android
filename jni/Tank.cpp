#include "Tank.h"
#include "util.h"

using k3d::gl;

const char * const Tank::treadsObj = "/sdcard/tanks/tank_treads.obj";
const char * const Tank::headObj = "/sdcard/tanks/tank_head.obj";

k3d::model Tank::mTreads;
k3d::model Tank::mHead;

void Tank::initialize()
{
    mTreads.loadObj(Tank::treadsObj);
    mHead.loadObj(Tank::headObj);
}

void Tank::draw()
{
    /**
     * Tank models draw a tank centred and on the xy plane
     * i.e. the tank lies in z > 0. It also is within the
     * canonical GL volume. It is aiming and facing in -Y
     */

    k3d::mat4 mMVBackup(gl::mModelView);
    k3d::mat4 normalMatrix;

    // TODO: rotate to velocity vector
    gl::mModelView.translatef(pos.x, pos.y, 0.0);
    gl::sendMatrices();
    mTreads.draw();

    gl::mModelView = mMVBackup;
    // TODO: rotate to aim
    gl::mModelView.translatef(pos.x, pos.y, 0.0);
    // now re glUniform() (TODO)
    mHead.draw();

    gl::mModelView = mMVBackup;
}

void Tank::step()
{
    //TODO
}
