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

    void show_test_base_window();
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

ImGuiWindow* GetWindowByName(std::string const& name);

template <typename T>
ImFuncPtr(ImGuiTestGuiFunc) ImWrapTestFuncT(
    ImTestFuncStartupParams const&                 params,
    std::function<void(ImGuiTestContext* ctx, T&)> cb) {
    return [params, cb](ImGuiTestContext* ctx) {
        T&   vars = ctx->GetVars<T>();
        auto wref = GetWindowByName(params.windowName);
        LOGIC_ASSERTION_CHECK(
            wref, "Cannot find window with name {}", params.windowName);
        ctx->SetRef(wref);
        cb(ctx, vars);
    };
}


template <typename T>
ImFuncPtr(ImGuiTestTestFunc)
    ImWrapTestFuncT(std::function<void(ImGuiTestContext* ctx, T&)> cb) {
    return ImWrapTestFuncT<T>(ImTestFuncStartupParams{}, cb);
}


ImVec2 getContentPos(ImGuiTestContext* ctx);

std::string __im_test_utils_format_va_args_list() { return ")"; }

template <typename T, typename... Args>
std::string __im_test_utils_format_va_args_list(
    T const& head,
    Args&&... args) {
    return fmt(", {}", head, __im_test_utils_format_va_args_list(args...));
}

float ImVec2Length(const ImVec2& vec) {
    return std::sqrt(vec.x * vec.x + vec.y * vec.y);
}

bool is_within_distance(
    ImVec2 const& lhs,
    ImVec2 const& rhs,
    float         distance) {
    return ImVec2Length(rhs - lhs) <= distance;
}

#define IM_CHECK_BINARY_PRED(_LHS, _RHS, __pred, ...)                     \
    do {                                                                  \
        auto __lhs = _LHS; /* Cache to avoid side effects */              \
        auto __rhs = _RHS;                                                \
        bool __res = __pred(__lhs, __rhs __VA_OPT__(, ) __VA_ARGS__);     \
        std::string arglist_buf = __im_test_utils_format_va_args_list(    \
            __VA_ARGS__);                                                 \
        std::string expr_buf = fmt(                                       \
            "{} [{}] !{}(_, _ {} [{}]",                                   \
            #_LHS,                                                        \
            __lhs,                                                        \
            #__pred,                                                      \
            arglist_buf,                                                  \
            #_RHS,                                                        \
            __rhs);                                                       \
        if (ImGuiTestEngine_Check(                                        \
                __FILE__,                                                 \
                __func__,                                                 \
                __LINE__,                                                 \
                ImGuiTestCheckFlags_None,                                 \
                __res,                                                    \
                expr_buf.c_str())) {                                      \
            IM_ASSERT(__res);                                             \
        }                                                                 \
        if (!__res) { return; }                                           \
    } while (0)
