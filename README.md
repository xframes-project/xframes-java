# xframes-java

## Building the JNI DLL

(You need to open a developer prompt on Windows)

`cd native`
`cmake -S . build`
`cmake --build build`

## Run the app

### Prerequisites

The JNI DLL depends on other DLLs, which must be discoverable by adding them to Path/PATH

on Windows, in a terminal:

`set PATH=%PATH%;</path/to/dlls/folder>`


### With Gradle

`gradle runMain`

### Without Gradle

(assuming `./native/build/Debug` is where the JNI DLL has been generated)

java -Djava.library.path=./native/build/Debug -cp "build/classes/java/main;~/.m2/repository/org/json/json/20201115/json-20201115.jar" dev.xframes.XFramesWrapper


