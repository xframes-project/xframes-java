package dev.xframes;

public class XFramesWrapper {
    // Declare the native methods
    public native void resizeWindow(int width, int height);
    public native void setElement(String elementJson);

    static {
        // Load the native library
        System.loadLibrary("xframes"); // This should match the name of your compiled C library (e.g., xframes.dll or libxframes.so)
    }

    public static void main(String[] args) {
        var xframes = new XFramesWrapper();
        xframes.resizeWindow(800, 600); // Calling the native method
        xframes.setElement("{\"type\":\"button\", \"label\":\"Click Me\"}"); // Calling the native method
    }
}
