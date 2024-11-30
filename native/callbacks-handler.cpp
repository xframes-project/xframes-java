#include "callbacks-handler.h"

CallbackHandler::CallbackHandler(JavaVM* jvm, JNIEnv* env, jobject xframes, jobject callbacks)
    : m_jvm(jvm), m_env(env) {
    // Keep a global reference to prevent GC from collecting it
    m_callbacks = env->NewGlobalRef(callbacks);
    m_xframes = env->NewGlobalRef(xframes);
};

CallbackHandler::~CallbackHandler() {
    // Release the global reference when done
    m_env->DeleteGlobalRef(m_callbacks);
    m_env->DeleteGlobalRef(m_xframes);

    // Only detach if the thread is actually attached
    JNIEnv* env;
    if (m_jvm->GetEnv((void**)&env, JNI_VERSION_1_6) == JNI_OK) {
        m_jvm->DetachCurrentThread();
    }
};

void CallbackHandler::onInit() {
    jint res = m_jvm->AttachCurrentThread((void**)&m_env, nullptr);
    if (res != JNI_OK) {
        fprintf(stderr, "Error: Unable to attach thread to JVM\n");
        return;
    }

    jclass callbackClasss = m_env->FindClass("dev/xframes/MyCallbackHandler");
    if (callbackClasss == nullptr) {
        m_env->ExceptionDescribe();
        return;
    }

    // Get the method ID for the 'onInit' instance method
    jmethodID onInitMethod = m_env->GetMethodID(callbackClasss, "onInit", "()V");
    if (onInitMethod == nullptr) {
        printf("onInit method not found\n");
        m_env->ExceptionDescribe();
        return;
    }

    // Now get the singleton instance of MyCallbackHandler
    jmethodID getInstanceMethod = m_env->GetStaticMethodID(callbackClasss, "getInstance", "(Ldev/xframes/XFramesWrapper;)Ldev/xframes/MyCallbackHandler;");
    if (getInstanceMethod == nullptr) {
        printf("getInstance method not found\n");
        m_env->ExceptionDescribe();
        return;
    }

    // Call getInstance() to get the singleton instance
    jobject callbackHandlerInstance = m_env->CallStaticObjectMethod(callbackClasss, getInstanceMethod, m_xframes);
    if (callbackHandlerInstance == nullptr) {
        printf("Failed to get MyCallbackHandler instance\n");
        return;
    }

    // Call the onInit method on the singleton instance
    m_env->CallVoidMethod(callbackHandlerInstance, onInitMethod);
};

void CallbackHandler::onTextChanged(int id, const char* text) {
    jclass callbackClass = m_env->GetObjectClass(m_callbacks);
    jmethodID onTextChangedMethod = m_env->GetMethodID(callbackClass, "onTextChanged", "(ILjava/lang/String;)V");
    if (onTextChangedMethod != NULL) {
        jstring jText = m_env->NewStringUTF(text);
        m_env->CallVoidMethod(m_callbacks, onTextChangedMethod, id, jText);
        m_env->DeleteLocalRef(jText);  // Delete local reference to the string

        if (m_env->ExceptionCheck()) {
            m_env->ExceptionDescribe();
            m_env->ExceptionClear();
        }
    }
}

void CallbackHandler::onComboChanged(int id, int value) {
    jclass callbackClass = m_env->GetObjectClass(m_callbacks);
    jmethodID onComboChangedMethod = m_env->GetMethodID(callbackClass, "onComboChanged", "(II)V");
    if (onComboChangedMethod != NULL) {
        m_env->CallVoidMethod(m_callbacks, onComboChangedMethod, id, value);

        if (m_env->ExceptionCheck()) {
            m_env->ExceptionDescribe();
            m_env->ExceptionClear();
        }
    }
}

void CallbackHandler::onNumericValueChanged(int id, float value) {
    jclass callbackClass = m_env->GetObjectClass(m_callbacks);
    jmethodID onNumericValueChangedMethod = m_env->GetMethodID(callbackClass, "onNumericValueChanged", "(IF)V");
    if (onNumericValueChangedMethod != NULL) {
        m_env->CallVoidMethod(m_callbacks, onNumericValueChangedMethod, id, value);

        if (m_env->ExceptionCheck()) {
            m_env->ExceptionDescribe();
            m_env->ExceptionClear();
        }
    }
}

void CallbackHandler::onBooleanValueChanged(int id, bool value) {
    jclass callbackClass = m_env->GetObjectClass(m_callbacks);
    jmethodID onBooleanValueChangedMethod = m_env->GetMethodID(callbackClass, "onBooleanValueChanged", "(IZ)V");
    if (onBooleanValueChangedMethod != NULL) {
        m_env->CallVoidMethod(m_callbacks, onBooleanValueChangedMethod, id, value ? JNI_TRUE : JNI_FALSE);

        if (m_env->ExceptionCheck()) {
            m_env->ExceptionDescribe();
            m_env->ExceptionClear();
        }
    }
}

void CallbackHandler::onMultipleNumericValuesChanged(int id, float* values, int numValues) {
    jclass callbackClass = m_env->GetObjectClass(m_callbacks);
    jmethodID onMultipleNumericValuesChangedMethod = m_env->GetMethodID(callbackClass, "onMultipleNumericValuesChanged", "(I[F)V");
    if (onMultipleNumericValuesChangedMethod != NULL) {
        jfloatArray jValues = m_env->NewFloatArray(numValues);
        m_env->SetFloatArrayRegion(jValues, 0, numValues, values);
        m_env->CallVoidMethod(m_callbacks, onMultipleNumericValuesChangedMethod, id, jValues);
        m_env->DeleteLocalRef(jValues);  // Delete local reference to the array

        if (m_env->ExceptionCheck()) {
            m_env->ExceptionDescribe();
            m_env->ExceptionClear();
        }
    }
}

// onClick callback
void CallbackHandler::onClick(int id) {
    jclass callbackClass = m_env->GetObjectClass(m_callbacks);
    jmethodID onClickMethod = m_env->GetMethodID(callbackClass, "onClick", "(I)V");
    if (onClickMethod != NULL) {
        m_env->CallVoidMethod(m_callbacks, onClickMethod, id);
    }
}
