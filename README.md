# xframes-java

## Building the JNI DLL

(You need to open a developer prompt on Windows)

`cd native`
`cmake -S . build`
`cmake --build build`

## Run the app

### Prerequisites

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

`gradle runMain`

### Without Gradle

(assuming `./native/build/Debug` is where the JNI DLL has been generated)

java -Djava.library.path=./native/build/Debug -cp "build/classes/java/main;~/.m2/repository/org/json/json/20201115/json-20201115.jar" dev.xframes.XFramesWrapper


