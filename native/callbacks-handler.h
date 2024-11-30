//
// Created by manes on 29/11/2024.
//

#ifndef CALLBACKS_HANDLER_H
#define CALLBACKS_HANDLER_H

#include <jni.h>

class CallbackHandler {
public:
    CallbackHandler(JavaVM* jvm, JNIEnv* env, jobject xframes, jobject callbacks);

    ~CallbackHandler();

    void onInit();

    // onTextChanged callback
    void onTextChanged(int id, const char* text);

    // onComboChanged callback
    void onComboChanged(int id, int value);

    // onNumericValueChanged callback
    void onNumericValueChanged(int id, float value);

    // onBooleanValueChanged callback
    void onBooleanValueChanged(int id, bool value);

    // onMultipleNumericValuesChanged callback
    void onMultipleNumericValuesChanged(int id, float* values, int numValues);

    // onClick callback
    void onClick(int id);

private:
    JavaVM* m_jvm;
    JNIEnv* m_env;
    jobject m_xframes;
    jobject m_callbacks;
};

#endif //CALLBACKS_HANDLER_H
