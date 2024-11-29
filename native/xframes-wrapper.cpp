#ifndef XFRAMES_WRAPPER_H
#define XFRAMES_WRAPPER_H

#include <string>
#include <jni.h>
#include <xframes-wrapper.h>
#include <xframes-runner.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 *
    * {
        // Convert the Java string into a UTF-8 C string
        const char *element = (*env)->GetStringUTFChars(env, elementJson, NULL);

        // Print the string in C
        printf("Received element: %s\n", element);

        // Release the memory allocated for the C string
        (*env)->ReleaseStringUTFChars(env, elementJson, element);
    }
 *
 * @param width
 * @param height
 */
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

jstring Java_dev_xframes_XFramesWrapper_getChildren(int id) {
    Runner* pRunner = Runner::getInstance();

    return IntVectorToJson(pRunner->GetChildren(id)).dump().c_str();
}

void Java_dev_xframes_XFramesWrapper_appendTextToClippedMultiLineTextRenderer(JNIEnv *env, jobject obj, jint id, jstring dataJString) {
    Runner* pRunner = Runner::getInstance();
    const char* dataCStr = env->GetStringUTFChars(dataJString, nullptr);

    std::string data(dataCStr);

    pRunner->AppendTextToClippedMultiLineTextRenderer(id, data);

    env->ReleaseStringUTFChars(dataJString, dataCStr);
}

jstring Java_dev_xframes_XFramesWrapper_getStyle() {
    Runner* pRunner = Runner::getInstance();

    return pRunner->GetStyle().c_str();
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

/**
 * [0] assets base path
 * [1] raw font definitions (stringified JSON)
 * [2] raw style override definitions (stringified JSON)
 * [3] onInit function
 * [4] onTextChanged function
 * [5] onComboChanged function
 * [6] onNumericValueChanged function
 * [7] OnBooleanValueChanged function
 * [8] OnMultipleNumericValuesChanged function
 * [9] OnClick function
 */
void Java_dev_xframes_XFramesWrapper_init(JNIEnv *env, jobject obj,
       jstring assetsBasePath,
       jstring rawFontDefinitions,
       jstring rawStyleOverrideDefinitions,
       jobject allCallbacks
    ) {
    Runner* pRunner = Runner::getInstance();

    // Convert the Java strings to C strings
    const char* assetsBasePathStr = (*env)->GetStringUTFChars(env, assetsBasePath, 0);
    const char* rawFontDefinitionsStr = (*env)->GetStringUTFChars(env, rawFontDefinitions, 0);
    const char* rawStyleOverrideDefinitionsStr = (*env)->GetStringUTFChars(env, rawStyleOverrideDefinitions, 0);

    pRunner->SetAssetsBasePath(assetsBasePathStr);
    pRunner->SetRawFontDefs(rawFontDefinitionsStr);
    pRunner->SetRawStyleOverridesDefs(rawStyleOverrideDefinitionsStr);

    pRunner->SetHandlers(allCallbacks);

    pRunner->Init();

    // Don't forget to release the strings
    (*env)->ReleaseStringUTFChars(env, assetsBasePath, assetsBasePathStr);
    (*env)->ReleaseStringUTFChars(env, rawFontDefinitions, rawFontDefinitionsStr);
    (*env)->ReleaseStringUTFChars(env, rawStyleOverrideDefinitions, rawStyleOverrideDefinitionsStr);

    // uiThread = std::thread(run);
    // uiThread.detach();
}

#ifdef __cplusplus
}
#endif

#endif // XFRAMES_WRAPPER_H