#include <thread>

#include <nlohmann/json.hpp>
#include <utility>

#include "callbacks-handler.h"
#include "xframes-runner.h"

using json = nlohmann::json;

json IntVectorToJson(const std::vector<int>& data) {
    auto jsonArray = json::array();
    for (auto& item : data) {
        jsonArray.push_back(item);
    }
    return jsonArray;
}

json IntSetToJson(const std::set<int>& data) {
    auto jsonArray = json::array();
    for (auto& item : data) {
        jsonArray.push_back(item);
    }
    return jsonArray;
}

Runner::Runner() {};
Runner::~Runner() {};

Runner* Runner::getInstance() {
    if (nullptr == instance) {
        instance = new Runner();
    }
    return instance;
};

void Runner::OnInit() {
    auto pRunner = getInstance();

    pRunner->m_onInit();
};

void Runner::OnTextChange(const int id, const std::string& value) {
    auto pRunner = getInstance();

};

void Runner::OnComboChange(const int id, const int value) {
    auto pRunner = getInstance();

};

void Runner::OnNumericValueChange(const int id, const float value) {
    auto pRunner = getInstance();

};

void Runner::OnBooleanValueChange(const int id, const bool value) {
    auto pRunner = getInstance();

};

// todo: improve
void Runner::OnMultipleNumericValuesChange(const int id, const float* values, const int numValues) {
    auto pRunner = getInstance();


};

void Runner::OnClick(int id) {
    auto pRunner = getInstance();

    pRunner->m_onClick(id);
};

void Runner::SetHandlers(CallbackHandler& callbackHandler) {
        m_callbackHandler = std::make_unique<CallbackHandler>(std::move(callbackHandler));

        m_onInit = [this]() {
            m_callbackHandler->onInit();
        };
        m_onTextChange = [this](int id, const std::string& value){ m_callbackHandler->onTextChanged(id, value.c_str()); };
        m_onComboChange = [this](int id, int value){ m_callbackHandler->onComboChanged(id, value); };
        m_onNumericValueChange = [this](int id, float value){ m_callbackHandler->onNumericValueChanged(id, value); };
        m_onBooleanValueChange = [this](int id, bool value){ m_callbackHandler->onBooleanValueChanged(id, value); };
        m_onMultipleNumericValuesChange = [this](int id, std::vector<float> values){ m_callbackHandler->onMultipleNumericValuesChanged(id, values.data(), (int)values.size()); };
        m_onClick = [this](int id){ m_callbackHandler->onClick(id); };
};

void Runner::SetRawFontDefs(std::string rawFontDefs) {
    m_rawFontDefs = std::move(rawFontDefs);
};

void Runner::SetAssetsBasePath(std::string basePath) {
    m_assetsBasePath = basePath;
};

void Runner::SetRawStyleOverridesDefs(const std::string& rawStyleOverridesDefs) {
    m_rawStyleOverridesDefs.emplace(rawStyleOverridesDefs);
};

void Runner::Init() {
    m_xframes = new XFrames("XFrames", m_rawStyleOverridesDefs);
    m_renderer = new ImPlotRenderer(
        m_xframes,
        "XFrames",
        "XFrames",
        m_rawFontDefs,
        m_assetsBasePath
    );
    // todo: do we need this?
    m_renderer->SetCurrentContext();

    m_xframes->SetEventHandlers(
        OnInit,
        OnTextChange,
        OnComboChange,
        OnNumericValueChange,
        OnMultipleNumericValuesChange,
        OnBooleanValueChange,
        OnClick
    );
};

void Runner::Run() {
    m_renderer->Init();
};

void Runner::StartThread() {
    std::thread runnerThread(&Runner::Run, this);
    runnerThread.detach();  // Detach the thread to run independently
};

void Runner::Exit() {
    // emscripten_cancel_main_loop();
    // emscripten_force_exit(0);
};

void Runner::ResizeWindow(const int width, const int height) {
    m_renderer->SetWindowSize(width, height);
};

void Runner::SetElement(std::string& elementJsonAsString) {
    m_xframes->QueueCreateElement(elementJsonAsString);
};

void Runner::PatchElement(const int id, std::string& elementJsonAsString) {
    m_xframes->QueuePatchElement(id, elementJsonAsString);
};

void Runner::ElementInternalOp(const int id, std::string& elementJsonAsString) {
    m_xframes->QueueElementInternalOp(id, elementJsonAsString);
};

void Runner::SetChildren(const int id, const std::vector<int>& childrenIds) {
    m_xframes->QueueSetChildren(id, childrenIds);
};

void Runner::AppendChild(const int parentId, const int childId) {
    m_xframes->QueueAppendChild(parentId, childId);
};

std::vector<int> Runner::GetChildren(const int id) {
    return m_xframes->GetChildren(id);
};

std::string Runner::GetAvailableFonts() {
    return m_renderer->GetAvailableFonts().dump();
};

void Runner::AppendTextToClippedMultiLineTextRenderer(const int id, const std::string& data) {
    m_xframes->AppendTextToClippedMultiLineTextRenderer(id, data);
};

std::string Runner::GetStyle() {
    json style;

    style["alpha"] = m_xframes->m_appStyle.Alpha;
    style["disabledAlpha"] = m_xframes->m_appStyle.DisabledAlpha;
    style["windowPadding"] = { m_xframes->m_appStyle.WindowPadding.x, m_xframes->m_appStyle.WindowPadding.y };
    style["windowRounding"] = m_xframes->m_appStyle.WindowRounding;
    style["windowBorderSize"] = m_xframes->m_appStyle.WindowBorderSize;
    style["windowMinSize"] = { m_xframes->m_appStyle.WindowMinSize.x, m_xframes->m_appStyle.WindowMinSize.y };
    style["windowTitleAlign"] = { m_xframes->m_appStyle.WindowTitleAlign.x, m_xframes->m_appStyle.WindowTitleAlign.y };
    style["windowMenuButtonPosition"] = m_xframes->m_appStyle.WindowMenuButtonPosition;
    style["childRounding"] = m_xframes->m_appStyle.ChildRounding;
    style["childBorderSize"] = m_xframes->m_appStyle.ChildBorderSize;
    style["popupRounding"] = m_xframes->m_appStyle.PopupRounding;
    style["popupBorderSize"] = m_xframes->m_appStyle.PopupBorderSize;
    style["framePadding"] = { m_xframes->m_appStyle.FramePadding.x, m_xframes->m_appStyle.FramePadding.y };
    style["frameRounding"] = m_xframes->m_appStyle.FrameRounding;
    style["frameBorderSize"] = m_xframes->m_appStyle.FrameBorderSize;
    style["itemSpacing"] = { m_xframes->m_appStyle.ItemSpacing.x, m_xframes->m_appStyle.ItemSpacing.y };
    style["itemInnerSpacing"] = { m_xframes->m_appStyle.ItemInnerSpacing.x, m_xframes->m_appStyle.ItemInnerSpacing.y };
    style["cellPadding"] = { m_xframes->m_appStyle.CellPadding.x, m_xframes->m_appStyle.CellPadding.y };
    style["touchExtraPadding"] = { m_xframes->m_appStyle.TouchExtraPadding.x, m_xframes->m_appStyle.TouchExtraPadding.y };
    style["indentSpacing"] = m_xframes->m_appStyle.IndentSpacing;
    style["columnsMinSpacing"] = m_xframes->m_appStyle.ColumnsMinSpacing;
    style["scrollbarSize"] = m_xframes->m_appStyle.ScrollbarSize;
    style["scrollbarRounding"] = m_xframes->m_appStyle.ScrollbarRounding;
    style["grabMinSize"] = m_xframes->m_appStyle.GrabMinSize;
    style["grabRounding"] = m_xframes->m_appStyle.GrabRounding;
    style["logSliderDeadzone"] = m_xframes->m_appStyle.LogSliderDeadzone;
    style["tabRounding"] = m_xframes->m_appStyle.TabRounding;
    style["tabBorderSize"] = m_xframes->m_appStyle.TabBorderSize;
    style["tabMinWidthForCloseButton"] = m_xframes->m_appStyle.TabMinWidthForCloseButton;
    style["tabBarBorderSize"] = m_xframes->m_appStyle.TabBarBorderSize;
    style["tableAngledHeadersAngle"] = m_xframes->m_appStyle.TableAngledHeadersAngle;
    style["tableAngledHeadersTextAlign"] = { m_xframes->m_appStyle.TableAngledHeadersTextAlign.x, m_xframes->m_appStyle.TableAngledHeadersTextAlign.y };
    style["colorButtonPosition"] = m_xframes->m_appStyle.ColorButtonPosition;
    style["buttonTextAlign"] = { m_xframes->m_appStyle.ButtonTextAlign.x, m_xframes->m_appStyle.ButtonTextAlign.y };
    style["selectableTextAlign"] = { m_xframes->m_appStyle.SelectableTextAlign.x, m_xframes->m_appStyle.SelectableTextAlign.y };
    style["separatorTextPadding"] = { m_xframes->m_appStyle.SeparatorTextPadding.x, m_xframes->m_appStyle.SeparatorTextPadding.y };
    style["displayWindowPadding"] = { m_xframes->m_appStyle.DisplayWindowPadding.x, m_xframes->m_appStyle.DisplayWindowPadding.y };
    style["displaySafeAreaPadding"] = { m_xframes->m_appStyle.DisplaySafeAreaPadding.x, m_xframes->m_appStyle.DisplaySafeAreaPadding.y };
    style["mouseCursorScale"] = m_xframes->m_appStyle.MouseCursorScale;
    style["antiAliasedLines"] = m_xframes->m_appStyle.AntiAliasedLines;
    style["antiAliasedLinesUseTex"] = m_xframes->m_appStyle.AntiAliasedLinesUseTex;
    style["antiAliasedFill"] = m_xframes->m_appStyle.AntiAliasedFill;
    style["curveTessellationTol"] = m_xframes->m_appStyle.CurveTessellationTol;
    style["circleTessellationMaxError"] = m_xframes->m_appStyle.CircleTessellationMaxError;

    style["hoverStationaryDelay"] = m_xframes->m_appStyle.HoverStationaryDelay;
    style["hoverDelayShort"] = m_xframes->m_appStyle.HoverDelayShort;
    style["hoverDelayNormal"] = m_xframes->m_appStyle.HoverDelayNormal;

    style["hoverFlagsForTooltipMouse"] = m_xframes->m_appStyle.HoverFlagsForTooltipMouse;
    style["hoverFlagsForTooltipNav"] = m_xframes->m_appStyle.HoverFlagsForTooltipNav;

    style["colors"] = json::array();

    for (int i = 0; i < ImGuiCol_COUNT; i++) {
        auto maybeValue = IV4toJsonHEXATuple(m_xframes->m_appStyle.Colors[i]);

        if (maybeValue.has_value()) {
            style["colors"].push_back(maybeValue.value());
        }
    }

    return style.dump();
};

void Runner::PatchStyle(std::string& styleDef) {
    m_xframes->PatchStyle(json::parse(styleDef));
};

void Runner::SetDebug(const bool debug) {
    m_xframes->SetDebug(debug);
};

void Runner::ShowDebugWindow() {
    m_xframes->ShowDebugWindow();
};

Runner* Runner::instance = nullptr;
