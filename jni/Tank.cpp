#include "Tank.h"
#include "util.h"

const char * const Tank::treadsObj = "/sdcard/tanks/tank_treads.obj";
const char * const Tank::headObj = "/sdcard/tanks/tank_head.obj";

k3d::model Tank::mTreads;
k3d::model Tank::mHead;

void Tank::initialize()
{
    LOGI("Tank::initialize()\n");
    mTreads.loadObj(Tank::treadsObj);
    mHead.loadObj(Tank::headObj);
}

void Tank::draw(GLuint gvPositionHandle, GLuint gvNormalHandle)
{
    /**
     * Tank models draw a tank centred and on the xy plane
     * i.e. the tank lies in z > 0. It also is within the
     * canonical GL volume
     */

    k3d::mat4 t = game->modelView;
    k3d::mat4 normalMatrix;

    // TODO: rotate to velocity vector
    t.translatef(pos.x, pos.y, 0.0);

    t.glUniform(game->gmModelViewHandle);
    checkGlError("glUniformMatrix4fv");
    normalMatrix = t;
    normalMatrix.inverse().transpose();
    normalMatrix.glUniform(game->gmNormalMatrixHandle);
    checkGlError("glUniformMatrix4fv");
    (game->mProjection * t).glUniform(game->gmModelViewProjectionHandle);
    checkGlError("glUniformMatrix4fv");

    mTreads.draw(gvPositionHandle, gvNormalHandle);

    t = game->modelView;
    // TODO: rotate to aim
    t.translatef(pos.x, pos.y, 0.0);
    // now re glUniform() (TODO)

    mHead.draw(gvPositionHandle, gvNormalHandle);
}

void Tank::step()
{
    //TODO
}
