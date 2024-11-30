#ifndef XFRAMES_RUNNER_H
#define XFRAMES_RUNNER_H

#include <cstdio>
#include <utility>
#include <vector>
#include <optional>
#include <functional>
#include <string>
#include <set>

#include <jni.h>

#include <GLFW/glfw3.h>
#include <GLES3/gl3.h>
#include "imgui.h"
#include "implot.h"
#include "implot_internal.h"
#include <nlohmann/json.hpp>

#include "color_helpers.h"
#include "xframes.h"
#include "implot_renderer.h"

#include <nlohmann/json.hpp>

#include "callbacks-handler.h"

using json = nlohmann::json;

typedef void (*OnInitCb)();
typedef void (*OnTextChangedCb)(int, const char*);
typedef void (*OnComboChangedCb)(int, int);
typedef void (*OnNumericValueChangedCb)(int, float);
typedef void (*OnBooleanValueChangedCb)(int, bool);
typedef void (*OnMultipleNumericValuesChangedCb)(int, float*, int numValues);
typedef void (*OnClickCb)(int);

template <typename T>
std::vector<T> JsonToVector(std::string& data) {
    auto parsedData = json::parse(data);
    std::vector<T> vec;
    for (auto& [key, item] : parsedData.items()) {
        vec.push_back(item.template get<T>());
    }
    return vec;
}

template <typename T>
std::set<T> JsonToSet(std::string& data) {
    auto parsedData = json::parse(data);
    std::set<T> set;
    for (auto& [key, item] : parsedData.items()) {
        set.insert(item.template get<T>());
    }
    return set;
}

json IntVectorToJson(const std::vector<int>& data);
json IntSetToJson(const std::set<int>& data);

class Runner {
    protected:
        XFrames* m_xframes{};
        ImGuiRenderer* m_renderer{};

        std::string m_rawFontDefs;
        std::string m_assetsBasePath;
        std::optional<std::string> m_rawStyleOverridesDefs;

        std::function<void()> m_onInit;
        std::function<void(int, const std::string&)> m_onTextChange;
        std::function<void(int, int)> m_onComboChange;
        std::function<void(int, float)> m_onNumericValueChange;
        std::function<void(int, bool)> m_onBooleanValueChange;
        std::function<void(int, std::vector<float>)> m_onMultipleNumericValuesChange;
        std::function<void(int)> m_onClick;

        std::unique_ptr<CallbackHandler> m_callbackHandler;

        static Runner* instance;

        Runner();
    public:
        static Runner* getInstance();

        ~Runner();

        static void OnInit();

        static void OnTextChange(const int id, const std::string& value);

        static void OnComboChange(const int id, const int value);

        static void OnNumericValueChange(const int id, const float value);

        static void OnBooleanValueChange(const int id, const bool value);

        // todo: improve
        static void OnMultipleNumericValuesChange(const int id, const float* values, const int numValues);

        static void OnClick(int id);

        void SetHandlers(CallbackHandler& callbackHandler);

        void SetRawFontDefs(std::string rawFontDefs);

        void SetAssetsBasePath(std::string basePath);

        void SetRawStyleOverridesDefs(const std::string& rawStyleOverridesDefs);

        void Init();

        void Run();

        void StartThread();

        void Exit();

        void ResizeWindow(const int width, const int height);

        void SetElement(std::string& elementJsonAsString);

        void PatchElement(const int id, std::string& elementJsonAsString);

        void ElementInternalOp(const int id, std::string& elementJsonAsString);

        void SetChildren(const int id, const std::vector<int>& childrenIds);

        void AppendChild(const int parentId, const int childId);

        std::vector<int> GetChildren(const int id);

        std::string GetAvailableFonts();

        void AppendTextToClippedMultiLineTextRenderer(const int id, const std::string& data);

        std::string GetStyle();

        void PatchStyle(std::string& styleDef);

        void SetDebug(const bool debug);

        void ShowDebugWindow();
};

#endif // XFRAMES_RUNNER_H