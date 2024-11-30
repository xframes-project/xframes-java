package dev.xframes;
import org.json.JSONObject;

import java.util.*;
import java.util.concurrent.*;

public class XFramesWrapper {
    // Native method declaration
    public native void setElement(String elementJson);
    public native void setChildren(int parentId, String childrenJson);

    // Declare the native method
    public native void init(String assetsBasePath,
                            String rawFontDefinitions,
                            String rawStyleOverrideDefinitions,
                            AllCallbacks allCallbacks);

    static {
        // Load the native library
        System.loadLibrary("xframesjni"); // This should match the name of your compiled C library (e.g., xframes.dll or libxframes.so)
    }

    public enum ImGuiCol {
        Text(0), TextDisabled(1), WindowBg(2), ChildBg(3), PopupBg(4),
        Border(5), BorderShadow(6), FrameBg(7), FrameBgHovered(8), FrameBgActive(9),
        TitleBg(10), TitleBgActive(11), TitleBgCollapsed(12), MenuBarBg(13),
        ScrollbarBg(14), ScrollbarGrab(15), ScrollbarGrabHovered(16),
        ScrollbarGrabActive(17), CheckMark(18), SliderGrab(19), SliderGrabActive(20),
        Button(21), ButtonHovered(22), ButtonActive(23), Header(24),
        HeaderHovered(25), HeaderActive(26), Separator(27), SeparatorHovered(28),
        SeparatorActive(29), ResizeGrip(30), ResizeGripHovered(31), ResizeGripActive(32),
        Tab(33), TabHovered(34), TabActive(35), TabUnfocused(36),
        TabUnfocusedActive(37), PlotLines(38), PlotLinesHovered(39), PlotHistogram(40),
        PlotHistogramHovered(41), TableHeaderBg(42), TableBorderStrong(43),
        TableBorderLight(44), TableRowBg(45), TableRowBgAlt(46),
        TextSelectedBg(47), DragDropTarget(48), NavHighlight(49),
        NavWindowingHighlight(50), NavWindowingDimBg(51), ModalWindowDimBg(52),
        COUNT(53);

        private final int value;

        ImGuiCol(int value) {
            this.value = value;
        }

        public int getValue() {
            return this.value;
        }
    }

    public static void main(String[] args) {
        System.out.println(getFontDefinitions());

        var xframes = new XFramesWrapper();
        var allCallbacks = MyCallbackHandler.getInstance(xframes);

        xframes.init("C:\\dev\\xframes-java\\assets", getFontDefinitions(), getStyleOverrides(), allCallbacks);

        // Now start the periodic task
        keepProcessRunning();
    }

    public static void keepProcessRunning() {
        ScheduledExecutorService scheduler = Executors.newScheduledThreadPool(1);

        // Define the task to run periodically
        Runnable task = () -> {
            // Simulate periodic work (for example, printing to console)
//            System.out.println("Process is running.................");

            // Here, you can call your native methods if necessary
            // e.g., xframes.setElement("someElementJson");
        };

        // Schedule the task to run every second (1,000 milliseconds)
        scheduler.scheduleAtFixedRate(task, 0, 1, TimeUnit.SECONDS);

        // Optionally, stop the task after a certain amount of time
        // For example, after 10 seconds
        // scheduler.shutdown();
    }

    private static String getFontDefinitions() {
        JSONObject fontDefs = new JSONObject();

        List<Map<String, Object>> defs = new ArrayList<>();
        Map<String, Object> entry = new HashMap<>();
        entry.put("name", "roboto-regular");
        entry.put("sizes", Arrays.asList(16, 18, 20, 24, 28, 32, 36, 48));
        defs.add(entry);

        // Transform the font definitions to a flattened list of font objects with name and size
        List<Map<String, Object>> flattenedDefs = new ArrayList<>();
        for (Map<String, Object> fontEntry : defs) {
            String fontName = (String) fontEntry.get("name");
            List<Integer> sizes = (List<Integer>) fontEntry.get("sizes");

            for (Integer size : sizes) {
                Map<String, Object> fontDef = new HashMap<>();
                fontDef.put("name", fontName);
                fontDef.put("size", size);
                flattenedDefs.add(fontDef);
            }
        }

        fontDefs.put("defs", flattenedDefs);

        return fontDefs.toString();
    }

    private static String getStyleOverrides() {
        Map<String, Object> theme2Colors = new HashMap<>();
        theme2Colors.put("darkestGrey", "#141f2c");
        theme2Colors.put("darkerGrey", "#2a2e39");
        theme2Colors.put("darkGrey", "#363b4a");
        theme2Colors.put("lightGrey", "#5a5a5a");
        theme2Colors.put("lighterGrey", "#7A818C");
        theme2Colors.put("evenLighterGrey", "#8491a3");
        theme2Colors.put("black", "#0A0B0D");
        theme2Colors.put("green", "#75f986");
        theme2Colors.put("red", "#ff0062");
        theme2Colors.put("white", "#fff");

        Map<String, Object> theme2 = new HashMap<>();

        Map<Integer, String> colorMap = new HashMap<>();
        colorMap.put(ImGuiCol.Text.value, "white");
        colorMap.put(ImGuiCol.TextDisabled.value, "lighterGrey");
        colorMap.put(ImGuiCol.WindowBg.value, "black");
        colorMap.put(ImGuiCol.ChildBg.value, "black");
        colorMap.put(ImGuiCol.PopupBg.value, "white");
        colorMap.put(ImGuiCol.Border.value, "lightGrey");
        colorMap.put(ImGuiCol.BorderShadow.value, "darkestGrey");
        colorMap.put(ImGuiCol.FrameBg.value, "black");
        colorMap.put(ImGuiCol.FrameBgHovered.value, "darkerGrey");
        colorMap.put(ImGuiCol.FrameBgActive.value, "lightGrey");
        colorMap.put(ImGuiCol.TitleBg.value, "lightGrey");
        colorMap.put(ImGuiCol.TitleBgActive.value, "darkerGrey");
        colorMap.put(ImGuiCol.TitleBgCollapsed.value, "lightGrey");
        colorMap.put(ImGuiCol.MenuBarBg.value, "lightGrey");
        colorMap.put(ImGuiCol.ScrollbarBg.value, "darkerGrey");
        colorMap.put(ImGuiCol.ScrollbarGrab.value, "darkerGrey");
        colorMap.put(ImGuiCol.ScrollbarGrabHovered.value, "lightGrey");
        colorMap.put(ImGuiCol.ScrollbarGrabActive.value, "darkestGrey");
        colorMap.put(ImGuiCol.CheckMark.value, "darkestGrey");
        colorMap.put(ImGuiCol.SliderGrab.value, "darkerGrey");
        colorMap.put(ImGuiCol.SliderGrabActive.value, "lightGrey");
        colorMap.put(ImGuiCol.Button.value, "black");
        colorMap.put(ImGuiCol.ButtonHovered.value, "darkerGrey");
        colorMap.put(ImGuiCol.ButtonActive.value, "black");
        colorMap.put(ImGuiCol.Header.value, "black");
        colorMap.put(ImGuiCol.HeaderHovered.value, "black");
        colorMap.put(ImGuiCol.HeaderActive.value, "lightGrey");
        colorMap.put(ImGuiCol.Separator.value, "darkestGrey");
        colorMap.put(ImGuiCol.SeparatorHovered.value, "lightGrey");
        colorMap.put(ImGuiCol.SeparatorActive.value, "lightGrey");
        colorMap.put(ImGuiCol.ResizeGrip.value, "black");
        colorMap.put(ImGuiCol.ResizeGripHovered.value, "lightGrey");
        colorMap.put(ImGuiCol.ResizeGripActive.value, "darkerGrey");
        colorMap.put(ImGuiCol.Tab.value, "black");
        colorMap.put(ImGuiCol.TabHovered.value, "darkerGrey");
        colorMap.put(ImGuiCol.TabActive.value, "lightGrey");
        colorMap.put(ImGuiCol.TabUnfocused.value, "black");
        colorMap.put(ImGuiCol.TabUnfocusedActive.value, "lightGrey");
        colorMap.put(ImGuiCol.PlotLines.value, "darkerGrey");
        colorMap.put(ImGuiCol.PlotLinesHovered.value, "lightGrey");
        colorMap.put(ImGuiCol.PlotHistogram.value, "darkerGrey");
        colorMap.put(ImGuiCol.PlotHistogramHovered.value, "lightGrey");
        colorMap.put(ImGuiCol.TableHeaderBg.value, "black");
        colorMap.put(ImGuiCol.TableBorderStrong.value, "lightGrey");
        colorMap.put(ImGuiCol.TableBorderLight.value, "darkerGrey");
        colorMap.put(ImGuiCol.TableRowBg.value, "darkGrey");
        colorMap.put(ImGuiCol.TableRowBgAlt.value, "darkerGrey");
        colorMap.put(ImGuiCol.TextSelectedBg.value, "darkerGrey");
        colorMap.put(ImGuiCol.DragDropTarget.value, "darkerGrey");
        colorMap.put(ImGuiCol.NavHighlight.value, "darkerGrey");
        colorMap.put(ImGuiCol.NavWindowingHighlight.value, "darkerGrey");
        colorMap.put(ImGuiCol.NavWindowingDimBg.value, "darkerGrey");
        colorMap.put(ImGuiCol.ModalWindowDimBg.value, "darkerGrey");

        theme2.put("colors", colorMap);

        return new JSONObject(theme2).toString();
    }
}
