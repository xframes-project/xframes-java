#ifndef XFRAMES_WRAPPER_H
#define XFRAMES_WRAPPER_H

#include <jni.h>
#include <stdio.h>

#include <stdbool.h>
#include <xframes-runner.h>

#ifdef __cplusplus
extern "C" {
#endif

JNIEXPORT void JNICALL Java_dev_xframes_XFramesWrapper_resizeWindow(JNIEnv *env, jobject obj, jint width, jint height);
JNIEXPORT void JNICALL Java_dev_xframes_XFramesWrapper_setElement(JNIEnv *env, jobject obj, jstring elementJson);
JNIEXPORT void JNICALL Java_dev_xframes_XFramesWrapper_patchElement(JNIEnv *env, jobject obj, jint id, jstring elementJson);
JNIEXPORT void JNICALL Java_dev_xframes_XFramesWrapper_elementInternalOp(JNIEnv *env, jobject obj, jint id, jstring elementJson);
JNIEXPORT void JNICALL Java_dev_xframes_XFramesWrapper_setChildren(JNIEnv *env, jobject obj, jint id, jstring childrenIds);
JNIEXPORT void JNICALL Java_dev_xframes_XFramesWrapper_appendChild(JNIEnv *env, jobject obj, jint parentId, jint childId);
JNIEXPORT jstring JNICALL Java_dev_xframes_XFramesWrapper_getChildren(JNIEnv *env, jobject obj, jint id);
JNIEXPORT void JNICALL Java_dev_xframes_XFramesWrapper_appendTextToClippedMultiLineTextRenderer(JNIEnv *env, jobject obj, jint id, jstring data);
JNIEXPORT jstring JNICALL Java_dev_xframes_XFramesWrapper_getStyle(JNIEnv *env, jobject obj);
JNIEXPORT void JNICALL Java_dev_xframes_XFramesWrapper_patchStyle(JNIEnv *env, jobject obj, jstring styleDef);
JNIEXPORT void JNICALL Java_dev_xframes_XFramesWrapper_setDebug(JNIEnv *env, jobject obj, jboolean debug);
JNIEXPORT void JNICALL Java_dev_xframes_XFramesWrapper_showDebugWindow(JNIEnv *env, jobject obj);
JNIEXPORT void JNICALL Java_dev_xframes_XFramesWrapper_init(JNIEnv *env, jobject obj, jstring assetsBasePath, jstring rawFontDefinitions, jstring rawStyleOverrideDefinitions, jobject allCallbacks);

#ifdef __cplusplus
}
#endif

#endif // XFRAMES_WRAPPER_H