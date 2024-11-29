#include "callbacks-handler.h"
#ifndef XFRAMES_WRAPPER_H
#define XFRAMES_WRAPPER_H

#include <string>
#include <jni.h>
#include <xframes-wrapper.h>
#include <xframes-runner.h>

#ifdef __cplusplus
extern "C" {
#endif

void Java_dev_xframes_XFramesWrapper_resizeWindow(JNIEnv *env, jobject obj, jint width, jint height) {
    Runner* pRunner = Runner::getInstance();
    pRunner->ResizeWindow(width, height);
}

void Java_dev_xframes_XFramesWrapper_setElement(JNIEnv *env, jobject obj, jstring elementJsonJString) {
    Runner* pRunner = Runner::getInstance();

    const char* elementJsonCStr = env->GetStringUTFChars(elementJsonJString, nullptr);

    std::string elementJson(elementJsonCStr);

    pRunner->SetElement(elementJson);

    env->ReleaseStringUTFChars(elementJsonJString, elementJsonCStr);
}

void Java_dev_xframes_XFramesWrapper_patchElement(JNIEnv *env, jobject obj, jint id, jstring elementJsonJString) {
    Runner* pRunner = Runner::getInstance();
    const char* elementJsonCStr = env->GetStringUTFChars(elementJsonJString, nullptr);

    std::string elementJson(elementJsonCStr);

    pRunner->PatchElement(id, elementJson);

    env->ReleaseStringUTFChars(elementJsonJString, elementJsonCStr);
}

void Java_dev_xframes_XFramesWrapper_elementInternalOp(JNIEnv *env, jobject obj, jint id, jstring elementJsonJString) {
    Runner* pRunner = Runner::getInstance();
    const char* elementJsonCStr = env->GetStringUTFChars(elementJsonJString, nullptr);

    std::string elementJson(elementJsonCStr);

    pRunner->ElementInternalOp(id, elementJson);

    env->ReleaseStringUTFChars(elementJsonJString, elementJsonCStr);
}

void Java_dev_xframes_XFramesWrapper_setChildren(JNIEnv *env, jobject obj, jint id, jstring childrenIdsJString) {
    Runner* pRunner = Runner::getInstance();
    const char* childrenIdsCStr = env->GetStringUTFChars(childrenIdsJString, nullptr);

    std::string childrenIds(childrenIdsCStr);
    // todo: use array of numbers instead of parsing JSON
    pRunner->SetChildren((int)id, JsonToVector<int>(childrenIds));

    env->ReleaseStringUTFChars(childrenIdsJString, childrenIdsCStr);
}

void Java_dev_xframes_XFramesWrapper_appendChild(JNIEnv *env, jobject obj, jint parentId, jint childId) {
    Runner* pRunner = Runner::getInstance();

    pRunner->AppendChild(parentId, childId);
}

jstring Java_dev_xframes_XFramesWrapper_getChildren(JNIEnv* env, jobject obj, jint id) {
    Runner* pRunner = Runner::getInstance();

    // Convert the result of GetChildren(id) to a JSON string
    std::string jsonString = IntVectorToJson(pRunner->GetChildren(id)).dump();

    // Convert std::string to a jstring and return it
    return env->NewStringUTF(jsonString.c_str());
}

void Java_dev_xframes_XFramesWrapper_appendTextToClippedMultiLineTextRenderer(JNIEnv *env, jobject obj, jint id, jstring dataJString) {
    Runner* pRunner = Runner::getInstance();
    const char* dataCStr = env->GetStringUTFChars(dataJString, nullptr);

    std::string data(dataCStr);

    pRunner->AppendTextToClippedMultiLineTextRenderer(id, data);

    env->ReleaseStringUTFChars(dataJString, dataCStr);
}

jstring Java_dev_xframes_XFramesWrapper_getStyle(JNIEnv* env, jobject obj) {
    Runner* pRunner = Runner::getInstance();

    // Get the style as a std::string (assuming GetStyle returns a std::string)
    std::string styleString = pRunner->GetStyle();

    // Convert the std::string to a jstring and return it
    return env->NewStringUTF(styleString.c_str());
}

void Java_dev_xframes_XFramesWrapper_patchStyle(JNIEnv *env, jobject obj, jstring styleDefJString) {
    Runner* pRunner = Runner::getInstance();
    const char* styleDefCStr = env->GetStringUTFChars(styleDefJString, nullptr);

    std::string styleDef(styleDefCStr);

    pRunner->PatchStyle(styleDef);

    env->ReleaseStringUTFChars(styleDefJString, styleDefCStr);
}

void Java_dev_xframes_XFramesWrapper_setDebug(JNIEnv *env, jobject obj, jboolean debug) {
    Runner* pRunner = Runner::getInstance();

    pRunner->SetDebug(debug);
}

void Java_dev_xframes_XFramesWrapper_showDebugWindow(JNIEnv *env, jobject obj) {
    Runner* pRunner = Runner::getInstance();

    pRunner->ShowDebugWindow();
}

void Java_dev_xframes_XFramesWrapper_init(JNIEnv *env, jobject obj,
       jstring assetsBasePath,
       jstring rawFontDefinitions,
       jstring rawStyleOverrideDefinitions,
       jobject allCallbacks
    ) {
    Runner* pRunner = Runner::getInstance();

    // Convert the Java strings to C strings
    const char* assetsBasePathStr = env->GetStringUTFChars(assetsBasePath, nullptr);
    const char* rawFontDefinitionsStr = env->GetStringUTFChars(rawFontDefinitions, nullptr);
    const char* rawStyleOverrideDefinitionsStr = env->GetStringUTFChars(rawStyleOverrideDefinitions, nullptr);

    pRunner->SetAssetsBasePath(assetsBasePathStr);
    pRunner->SetRawFontDefs(rawFontDefinitionsStr);
    pRunner->SetRawStyleOverridesDefs(rawStyleOverrideDefinitionsStr);

    env->ReleaseStringUTFChars(assetsBasePath, assetsBasePathStr);
    env->ReleaseStringUTFChars(rawFontDefinitions, rawFontDefinitionsStr);
    env->ReleaseStringUTFChars(rawStyleOverrideDefinitions, rawStyleOverrideDefinitionsStr);

    // Create a shared pointer to manage the CallbackHandler's lifecycle
    auto handler = std::make_shared<CallbackHandler>(env, allCallbacks);

    // Pass the handler to SetHandlers
    pRunner->SetHandlers(handler);

    pRunner->Init();
}

#ifdef __cplusplus
}
#endif

#endif // XFRAMES_WRAPPER_H