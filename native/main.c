#include <jni.h>
#include <stdio.h>

JNIEXPORT void JNICALL Java_dev_xframes_XFramesWrapper_printElement(JNIEnv *env, jobject obj, jstring elementJson) {
    // Convert the Java string into a UTF-8 C string
    const char *element = (*env)->GetStringUTFChars(env, elementJson, NULL);

    // Print the string in C
    printf("Received element: %s\n", element);

    // Release the memory allocated for the C string
    (*env)->ReleaseStringUTFChars(env, elementJson, element);
}