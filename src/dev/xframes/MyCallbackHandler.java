package dev.xframes;

public class MyCallbackHandler implements AllCallbacks {

    private final XFramesWrapper xframes;

    public MyCallbackHandler(XFramesWrapper xframes) {
        this.xframes = xframes;
    }

    @Override
    public void onInit() {
        System.out.println("Initialization callback called!");

        this.xframes.setElement("{\"type\":\"button\", \"label\":\"Click Me\"}");
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
    public void onMultipleNumericValuesChanged(int id, float[] values, int numValues) {
        System.out.print("Multiple numeric values changed (ID: " + id + ", Values: ");
        for (int i = 0; i < numValues; i++) {
            System.out.print(values[i] + " ");
        }
        System.out.println(")");
    }

    @Override
    public void onClick(int id) {
        System.out.println("Click callback (ID: " + id + ")");
    }
}
