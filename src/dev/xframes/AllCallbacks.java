package dev.xframes;

public interface AllCallbacks {
    void onInit();
    void onTextChanged(int id, String text);
    void onComboChanged(int id, int value);
    void onNumericValueChanged(int id, float value);
    void onBooleanValueChanged(int id, boolean value);
    void onMultipleNumericValuesChanged(int id, float[] values, int numValues);
    void onClick(int id);
}
