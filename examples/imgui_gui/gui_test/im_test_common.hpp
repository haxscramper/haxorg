#pragma once

#include <hstd/stdlib/Debug.hpp>
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
    OperationsTracer trace;
    bool             startup      = true;
    int              TraceCounter = 0;
    bool             is_first() {
        if (startup) {
            startup = false;
            return true;
        } else {
            return false;
        }
    }

    bool is_im_traced() { return 0 < TraceCounter; }
    void im_trace_run() {
        if (is_im_traced()) { --TraceCounter; }
    }
    void set_im_trace(int count) { TraceCounter = count; }

    void show_test_base_window() {
        if (ImGui::Begin("Test base window")) {
            if (ImGui::Button("+1 trace run")) { ++TraceCounter; }
            ImGui::Text("Executing %d trace runs", TraceCounter);
            ImGui::End();
        }
    }
};

template <typename T>
ImFuncPtr(ImGuiTestGuiFunc) ImWrapGuiFuncT(
    ImTestFuncStartupParams const&                 params,
    std::function<void(ImGuiTestContext* ctx, T&)> cb) {
    return [params, cb](ImGuiTestContext* ctx) {
        T& vars = ctx->GetVars<T>();
        vars.show_test_base_window();
        if (vars.is_im_traced()) { ImRenderTraceRecord::StartTrace(); }

        ImGui::SetNextWindowSize(params.windowSize);
        if (IM_FN_BEGIN(
                Begin,
                params.windowName.c_str(),
                NULL,
                ImGuiWindowFlags_NoSavedSettings)) {

            cb(ctx, vars);

            IM_FN_END(End);
        }

        if (vars.is_im_traced()) {
            ImRenderTraceRecord::EndTrace();
            vars.im_trace_run();
        }
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


ImVec2 getContentPos(ImGuiTestContext* ctx);
