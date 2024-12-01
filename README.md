# xframes-java

## Prerequisites

Either [download](https://github.com/xframes-project/xframes-jni-library/releases) or build the JNI DLL and dependent DLL files.

The JNI DLL requires the generated DLL files to be in your system PATH.

On Windows:
- fmt.dll (fmtd.dll in Debug mode)
- glfw3.dll

#### Windows
Temporary (Command Prompt):
`set PATH=%PATH%;C:\path\to\dlls\folder`

Temporary (PowerShell):
`$env:PATH += ";C:\path\to\dlls\folder"`

#### Linux/macOS
`export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/path/to/dlls/folder`

### With Gradle

No need to run batch/bash files if you already installed gradle globally

#### On Windows

`.\gradlew.bat runMain`

#### On Linux/macOS

`./gradlew runMain`

#### Additional build options

`./gradlew runMain --info`    # For detailed build information
`./gradlew clean runMain`     # For clean build

### Without Gradle

(assuming `./native/build/Debug` is where the JNI DLL has been generated)

java -Djava.library.path=./native/build/Debug -cp "build/classes/java/main;~/.m2/repository/org/json/json/20201115/json-20201115.jar" dev.xframes.XFramesWrapper

### Screenshots

Java, OpenJDK 23, Windows 11

![image](https://github.com/user-attachments/assets/87c63d02-0ec9-4333-ae0e-ccb285d76493)

