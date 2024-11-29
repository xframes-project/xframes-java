package dev.xframes;

public class XFramesWrapper {
    // Native method declaration
    public native void setElement(String elementJson);

    // Declare the native method
    public native void init(String assetsBasePath,
                            String rawFontDefinitions,
                            String rawStyleOverrideDefinitions,
                            AllCallbacks allCallbacks);

    static {
        // Load the native library
        System.loadLibrary("xframesjni"); // This should match the name of your compiled C library (e.g., xframes.dll or libxframes.so)
    }

    public static void main(String[] args) {
        var xframes = new XFramesWrapper();
        var allCallbacks = new MyCallbackHandler(xframes);

        xframes.init("/path/to/assets", "font_definitions", "style_overrides", allCallbacks);
    }
}
