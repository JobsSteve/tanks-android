#include <jni.h>

#include "TankGame.h"

TankGame *game;

extern "C" {
    JNIEXPORT void JNICALL Java_com_blur_tanks_GL2JNILib_init(JNIEnv * env, jobject obj);
    JNIEXPORT void JNICALL Java_com_blur_tanks_GL2JNILib_reshape(JNIEnv * env, jobject obj,  jint width, jint height);
    JNIEXPORT void JNICALL Java_com_blur_tanks_GL2JNILib_step(JNIEnv * env, jobject obj);
};
JNIEXPORT void JNICALL Java_com_blur_tanks_GL2JNILib_reshape(JNIEnv * env, jobject obj,  jint width, jint height)
{
    game->reshape(width, height);
}

JNIEXPORT void JNICALL Java_com_blur_tanks_GL2JNILib_init(JNIEnv * env, jobject obj)
{
    game = new TankGame();
    game->initialize();
}

JNIEXPORT void JNICALL Java_com_blur_tanks_GL2JNILib_step(JNIEnv * env, jobject obj)
{
    game->step();
}
