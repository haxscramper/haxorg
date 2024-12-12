#pragma once

#include <hstd/stdlib/Debug.hpp>
#define IMGUI_DEFINE_MATH_OPERATORS
#include "imgui.h"
#include "imgui_test_engine/imgui_te_context.h"
#include <hstd/stdlib/Str.hpp>
#include <gui_lib/imgui_utils.hpp>
#include <gui_lib/org_logger.hpp>

#define IM_TEST_LOG(__cat)                                                \
    ::org_logging::log_builder{}                                          \
        .set_callsite()                                                   \
        .category(__cat)                                                  \
        .severity(ol_info)                                                \
        .source_scope({"gui", "test"})


inline void join_fmt_varargs_impl(
    std::string&       buf,
    std::string const& sep) {}

template <typename T>
inline std::string format_for_log(T const& t) {
    return fmt1(t);
}

inline std::string format_for_log(char const* str) {
    return escape_literal(str);
}

inline std::string format_for_log(Str const& str) {
    return escape_literal(str);
}

inline std::string format_for_log(std::string const& str) {
    return escape_literal(str);
}

template <typename T, typename... Args>
inline void join_fmt_varargs_impl(
    std::string&       buf,
    std::string const& sep,
    T const&           head,
    Args&&... args) {
    if (!buf.empty()) { buf += sep; }
    buf += format_for_log(head);
    join_fmt_varargs_impl(buf, sep, std::forward<Args>(args)...);
}

template <typename... Args>
std::string join_fmt_varargs(std::string const& sep, Args&&... args) {
    std::string res;
    join_fmt_varargs_impl(res, sep, std::forward<Args>(args)...);
    return res;
}

template <typename Func, typename... Args>
void im_ctx_act_impl(
    ImGuiTestContext* ctx,
    Func              func,
    char const*       funcname,
    int               line,
    char const*       file,
    char const*       function,
    Args&&... args) {
    IM_TEST_LOG("ctx")
        .fmt_message(
            "Run {} with {}",
            funcname,
            join_fmt_varargs(", ", std::forward<Args>(args)...))
        .file(file)
        .line(line)
        .function(function);
    (ctx->*func)(std::forward<Args>(args)...);
}

#define IM_CTX_ACT(Func, ...)                                             \
    im_ctx_act_impl(                                                      \
        ctx,                                                              \
        &ImGuiTestContext::Func,                                          \
        #Func,                                                            \
        __LINE__,                                                         \
        __FILE__,                                                         \
        __FUNCTION__ __VA_OPT__(, ) __VA_ARGS__)


#define IM_FMT_DECL(T)                                                    \
    template <>                                                           \
    inline void ImGuiTestEngineUtil_appendf_auto(                         \
        ImGuiTextBuffer* buf, T v) {                                      \
        buf->append(fmt1(v).c_str());                                     \
        IM_UNUSED(v);                                                     \
    }

IM_FMT_DECL(std::string);
IM_FMT_DECL(Str);

Str getDebugFile(ImGuiTest* t, const Str& suffix);

struct ImTestFuncStartupParams {
    ImVec2      windowSize{250, 250};
    std::string windowName = "Test Window";
};

struct ImTestVarsBase {
    OperationsTracer trace;
    int              TraceCounter = 0;

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

void MouseMoveRelative(ImGuiTestContext* ctx, ImVec2 const& shift);

inline std::string __im_test_utils_format_va_args_list() { return ")"; }

template <typename T, typename... Args>
inline std::string __im_test_utils_format_va_args_list(
    T const& head,
    Args&&... args) {
    return fmt(
        ", {}{}", head, __im_test_utils_format_va_args_list(args...));
}

inline float ImVec2Length(const ImVec2& vec) {
    return std::sqrt(vec.x * vec.x + vec.y * vec.y);
}


struct PredicateResult {
    bool     ok = false;
    Opt<Str> explanation;
};


inline PredicateResult is_within_distance(
    ImVec2 const& lhs,
    ImVec2 const& rhs,
    float         distance) {
    PredicateResult res;
    float           dist = ImVec2Length(rhs - lhs);
    res.ok               = dist <= distance;
    if (!res.ok) { res.explanation = fmt("distance is {}", dist); }
    return res;
}

inline PredicateResult has_substring(Str const& lhs, Str const& rhs) {
    PredicateResult res;
    res.ok = lhs.contains(rhs);
    return res;
}

inline PredicateResult has_substring_normalized(
    Str const& lhs,
    Str const& rhs) {
    return has_substring(normalize(lhs), normalize(rhs));
}

inline PredicateResult not_has_substring(Str const& lhs, Str const& rhs) {
    PredicateResult res;
    int             idx = lhs.find(rhs);
    if (idx == std::string::npos) {
        res.ok = true;
    } else {
        res.ok          = false;
        res.explanation = fmt(
            "Found substring starting {} ({} ...)",
            idx,
            lhs.substr(
                idx, std::clamp<int>(idx + 20, lhs.length(), idx + 20)));
    }
    return res;
}

inline PredicateResult not_has_substring_normalized(
    Str const& lhs,
    Str const& rhs) {
    return not_has_substring(normalize(lhs), normalize(rhs));
}


#define IM_CHECK_BINARY_PRED(_LHS, _RHS, __pred, ...)                     \
    do {                                                                  \
        auto            __lhs = _LHS; /* Cache to avoid side effects */   \
        auto            __rhs = _RHS;                                     \
        PredicateResult __res = __pred(                                   \
            __lhs, __rhs __VA_OPT__(, ) __VA_ARGS__);                     \
        std::string arglist_buf = __im_test_utils_format_va_args_list(    \
            __VA_ARGS__);                                                 \
        std::string expr_buf = fmt(                                       \
            "{} [{}] !{}(_, _{} {} [{}]",                                 \
            #_LHS,                                                        \
            __lhs,                                                        \
            #__pred,                                                      \
            arglist_buf,                                                  \
            #_RHS,                                                        \
            __rhs);                                                       \
        if (!__res.ok && __res.explanation) {                             \
            expr_buf += " ";                                              \
            expr_buf += __res.explanation.value();                        \
        }                                                                 \
        if (ImGuiTestEngine_Check(                                        \
                __FILE__,                                                 \
                __func__,                                                 \
                __LINE__,                                                 \
                ImGuiTestCheckFlags_None,                                 \
                __res.ok,                                                 \
                expr_buf.c_str())) {                                      \
            IM_ASSERT(__res);                                             \
        }                                                                 \
        if (!__res.ok) { return; }                                        \
    } while (0)
