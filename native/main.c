#include <jni.h>
#include <stdio.h>

JNIEXPORT void JNICALL Java_com_example_HelloWorld_sayHello(JNIEnv *env, jobject obj) {
    printf("Hello from JNI!\n");
}