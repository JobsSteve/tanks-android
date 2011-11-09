#ifndef _UTIL_H
#define _UTIL_H

#include <android/log.h>

#define  LOG_TAG    "tanks"
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)


extern void printGLString(const char *name, GLenum s);
extern void checkGlError(const char* op);
extern const char *readFile(const char *filename);
extern GLuint loadShader(GLenum shaderType, const char* pSource);
extern GLuint createProgram(const char* pVertexSource, const char* pFragmentSource);

#endif //_UTIL_H
