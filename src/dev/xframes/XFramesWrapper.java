package dev.xframes;

public class XFramesWrapper {
    // Native method declaration
    public native void printElement(String elementJson);

    static {
        // Load the native library
        System.loadLibrary("xframesjni"); // This should match the name of your compiled C library (e.g., xframes.dll or libxframes.so)
    }

    public static void main(String[] args) {
        var xframes = new XFramesWrapper();
        xframes.printElement("{\"type\":\"button\", \"label\":\"Click Me\"}"); // Calling the native method
    }
}
