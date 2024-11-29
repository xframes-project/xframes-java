//
// Created by manes on 29/11/2024.
//

#ifndef CALLBACKS_HANDLER_H
#define CALLBACKS_HANDLER_H

#include <jni.h>

class CallbackHandler {
public:
    CallbackHandler(JNIEnv* env, jobject callbacks);

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
    JNIEnv* m_env;
    jobject m_callbacks;
};

#endif //CALLBACKS_HANDLER_H
