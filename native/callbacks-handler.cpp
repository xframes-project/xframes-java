#include "callbacks-handler.h"

CallbackHandler::CallbackHandler(JNIEnv* env, jobject callbacks)
    : m_env(env), m_callbacks(callbacks) {
    // Keep a global reference to prevent GC from collecting it
    m_callbacks = env->NewGlobalRef(callbacks);
};

CallbackHandler::~CallbackHandler() {
    // Release the global reference when done
    m_env->DeleteGlobalRef(m_callbacks);
};

void CallbackHandler::onInit() {
    jclass callbackClass = m_env->GetObjectClass(m_callbacks);
    jmethodID onInitMethod = m_env->GetMethodID(callbackClass, "onInit", "()V");
    if (onInitMethod != NULL) {
        m_env->CallVoidMethod(m_callbacks, onInitMethod);
    }
};

void CallbackHandler::onTextChanged(int id, const char* text) {
    jclass callbackClass = m_env->GetObjectClass(m_callbacks);
    jmethodID onTextChangedMethod = m_env->GetMethodID(callbackClass, "onTextChanged", "(ILjava/lang/String;)V");
    if (onTextChangedMethod != NULL) {
        jstring jText = m_env->NewStringUTF(text);
        m_env->CallVoidMethod(m_callbacks, onTextChangedMethod, id, jText);
        m_env->DeleteLocalRef(jText);  // Delete local reference to the string
    }
}

void CallbackHandler::onComboChanged(int id, int value) {
    jclass callbackClass = m_env->GetObjectClass(m_callbacks);
    jmethodID onComboChangedMethod = m_env->GetMethodID(callbackClass, "onComboChanged", "(II)V");
    if (onComboChangedMethod != NULL) {
        m_env->CallVoidMethod(m_callbacks, onComboChangedMethod, id, value);
    }
}

void CallbackHandler::onNumericValueChanged(int id, float value) {
    jclass callbackClass = m_env->GetObjectClass(m_callbacks);
    jmethodID onNumericValueChangedMethod = m_env->GetMethodID(callbackClass, "onNumericValueChanged", "(IF)V");
    if (onNumericValueChangedMethod != NULL) {
        m_env->CallVoidMethod(m_callbacks, onNumericValueChangedMethod, id, value);
    }
}

void CallbackHandler::onBooleanValueChanged(int id, bool value) {
    jclass callbackClass = m_env->GetObjectClass(m_callbacks);
    jmethodID onBooleanValueChangedMethod = m_env->GetMethodID(callbackClass, "onBooleanValueChanged", "(IZ)V");
    if (onBooleanValueChangedMethod != NULL) {
        m_env->CallVoidMethod(m_callbacks, onBooleanValueChangedMethod, id, value ? JNI_TRUE : JNI_FALSE);
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
