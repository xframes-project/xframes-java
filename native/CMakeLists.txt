cmake_minimum_required(VERSION 3.10)
project(MyJNIProject C)

# Find Java (JNI)
find_package(Java REQUIRED)

include_directories($ENV{JAVA_HOME}/include)
include_directories($ENV{JAVA_HOME}/include/win32)
include_directories(${Java_INCLUDE_DIRS})  # Include the JDK headers, including jni.h

# Add your source files
add_library(xframesjni SHARED main.c)

# Link Java libraries
target_link_libraries(xframesjni ${Java_JAVA_LIBRARY})