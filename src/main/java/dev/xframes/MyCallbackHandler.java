package dev.xframes;

import org.json.JSONArray;
import org.json.JSONObject;

public class MyCallbackHandler implements AllCallbacks {

    private static volatile MyCallbackHandler INSTANCE;
    private final XFramesWrapper xframes;

    private MyCallbackHandler(XFramesWrapper xframes) {
        this.xframes = xframes;
    }

    public static MyCallbackHandler getInstance(XFramesWrapper xframes) {
        if (INSTANCE == null) {
            synchronized (MyCallbackHandler.class) { // Thread-safe singleton initialization
                if (INSTANCE == null) {
                    INSTANCE = new MyCallbackHandler(xframes);
                }
            }
        }
        return INSTANCE;
    }

    @Override
    public void onInit() {
        System.out.println("Initialization callback called!");

        // Create root node
        JSONObject rootNode = new JSONObject();
        rootNode.put("id", 0);
        rootNode.put("type", "node");
        rootNode.put("root", true);

        // Create text node
        JSONObject textNode = new JSONObject();
        textNode.put("id", 1);
        textNode.put("type", "unformatted-text");
        textNode.put("text", "Hello, world!");

        // Set elements
        xframes.setElement(rootNode.toString());
        xframes.setElement(textNode.toString());
        xframes.setChildren(0, new JSONArray().put(1).toString());
    }

    @Override
    public void onTextChanged(int id, String text) {
        System.out.println("Text changed (ID: " + id + ", Text: " + text + ")");
    }

    @Override
    public void onComboChanged(int id, int value) {
        System.out.println("Combo changed (ID: " + id + ", Value: " + value + ")");
    }

    @Override
    public void onNumericValueChanged(int id, float value) {
        System.out.println("Numeric value changed (ID: " + id + ", Value: " + value + ")");
    }

    @Override
    public void onBooleanValueChanged(int id, boolean value) {
        System.out.println("Boolean value changed (ID: " + id + ", Value: " + value + ")");
    }

    @Override
    public void onMultipleNumericValuesChanged(int id, float[] values) {
        System.out.print("Multiple numeric values changed (ID: " + id + ", Values: ");
        for (float value : values) {
            System.out.print(value + " ");
        }
        System.out.println(")");
    }

    @Override
    public void onClick(int id) {
        System.out.println("Click callback (ID: " + id + ")");
    }
}
