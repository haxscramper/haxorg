#pragma once

#define IMGUI_DEFINE_MATH_OPERATORS
#include "imgui.h"
#include "imgui_test_engine/imgui_te_context.h"
#include <hstd/stdlib/Str.hpp>
#include <gui_lib/imgui_utils.hpp>

#define IM_FMT_DECL(T)                                                    \
    template <>                                                           \
    void ImGuiTestEngineUtil_appendf_auto(ImGuiTextBuffer* buf, T v) {    \
        buf->append(fmt1(v).c_str());                                     \
        IM_UNUSED(v);                                                     \
    }

Str getDebugFile(ImGuiTest* t, const Str& suffix);

struct ImTestFuncStartupParams {
    ImVec2      windowSize{250, 250};
    std::string windowName = "Test Window";
};

struct ImTestVarsBase {
    bool startup = true;
    bool is_first() {
        if (startup) {
            startup = false;
            return true;
        } else {
            return false;
        }
    }
};

template <typename T>
ImFuncPtr(ImGuiTestGuiFunc) ImWrapGuiFuncT(
    ImTestFuncStartupParams const&                 params,
    std::function<void(ImGuiTestContext* ctx, T&)> cb) {
    return [params, cb](ImGuiTestContext* ctx) {
        ImGui::SetNextWindowSize(params.windowSize);
        ImGui::Begin(
            params.windowName.c_str(),
            NULL,
            ImGuiWindowFlags_NoSavedSettings);
        T& vars = ctx->GetVars<T>();
        cb(ctx, vars);
        ImGui::End();
    };
}


template <typename T>
ImFuncPtr(ImGuiTestGuiFunc)
    ImWrapGuiFuncT(std::function<void(ImGuiTestContext* ctx, T&)> cb) {
    return ImWrapGuiFuncT<T>(ImTestFuncStartupParams{}, cb);
}

template <typename T>
ImFuncPtr(ImGuiTestGuiFunc) ImWrapTestFuncT(
    ImTestFuncStartupParams const&                 params,
    std::function<void(ImGuiTestContext* ctx, T&)> cb) {
    return [params, cb](ImGuiTestContext* ctx) {
        T& vars = ctx->GetVars<T>();
        ctx->SetRef(params.windowName.c_str());
        cb(ctx, vars);
    };
}


template <typename T>
ImFuncPtr(ImGuiTestTestFunc)
    ImWrapTestFuncT(std::function<void(ImGuiTestContext* ctx, T&)> cb) {
    return ImWrapTestFuncT<T>(ImTestFuncStartupParams{}, cb);
}


inline ImVec2 getWindowPos(ImGuiTestContext* ctx) {
    if (!ctx || !ctx->GetWindowByRef(ctx->GetRef())) {
        return ImGui::GetWindowPos();
    } else {
        return ctx->GetWindowByRef(ctx->GetRef())->Pos;
    }
}
