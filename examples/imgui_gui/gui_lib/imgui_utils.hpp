#pragma once

#include <GLFW/glfw3.h>
#include <hstd/stdlib/Ptrs.hpp>
#include <hstd/stdlib/TraceBase.hpp>
#include <hstd/system/reflection.hpp>
#include "imgui.h"
#include "imgui_internal.h"
#include <hstd/stdlib/Opt.hpp>
#include <hstd/stdlib/Str.hpp>

#include <stb/stb_truetype.h>


void frame_start();
void frame_end(GLFWwindow* window);
void fullscreen_window_begin();
int  push_frameless_window_vars();
void render_debug_rect(
    ImVec2 const& size,
    int           border = 2,
    const ImU32&  col    = IM_COL32(255, 255, 255, 255));

void quit_on_q(GLFWwindow* window);

/// \brief Return full path for the font with a given name, if it could be
/// found.
Opt<Str> get_fontconfig_path(Str const& fontname);

BOOST_DESCRIBE_STRUCT(ImVec2, (), (x, y));
BOOST_DESCRIBE_STRUCT(ImVec4, (), (x, y, z, w));
BOOST_DESCRIBE_STRUCT(ImRect, (), (Min, Max));

template <>
struct std::formatter<ImVec2> : std::formatter<std::string> {
    template <typename FormatContext>
    auto format(const ImVec2& p, FormatContext& ctx) const {
        fmt_ctx("(", ctx);
        fmt_ctx(p.x, ctx);
        fmt_ctx(", ", ctx);
        fmt_ctx(p.y, ctx);
        return fmt_ctx(")", ctx);
    }
};

struct StbFontMetrics {
    stbtt_fontinfo             font;
    float                      fontSize;
    float                      scale;
    std::vector<unsigned char> buffer;

    static SPtr<StbFontMetrics> FromPath(
        std::string const& fontPath,
        float              fontSize);

    int WidthChar(char ch) const;

    Pair<int, int> GetAscentDescent() const;

    int GetTextWidth(std::string_view const& text) const;
};

struct ImRenderTraceRecord {
    char const*              file;
    int                      line;
    int                      col;
    char const*              function;
    Opt<std::string>         im_id;
    Opt<std::string>         im_function;
    Opt<ImVec2>              cursor_screenpos;
    Opt<ImVec2>              cursor_winpos;
    Vec<ImRenderTraceRecord> nested;
    // Vec<std::string> im_id_stack

    static Vec<ImRenderTraceRecord> stack;
    static bool                     TraceState;

    static void StartTrace() {
        stack.clear();
        TraceState = true;
    }

    static void EndTrace() { TraceState = false; }

    static void PushRecord(ImRenderTraceRecord const& rec) {
        if (TraceState) { stack.push_back(rec); }
    }

    static void PushUnitRecord(ImRenderTraceRecord const& rec) {
        if (TraceState) {
            if (stack.empty()) {
                stack.push_back(ImRenderTraceRecord::init());
            }
            stack.back().nested.push_back(rec);
        }
    }

    static void PopRecord() {
        if (TraceState) { PushUnitRecord(stack.pop_back_v()); }
    }

    static ImRenderTraceRecord init(
        char const* function = __builtin_FUNCTION(),
        int         line     = __builtin_LINE(),
        char const* file     = __builtin_FILE());

    static bool ImRenderBegin(
        bool        expr,
        char const* im_function,
        char const* im_id,
        char const* function = __builtin_FUNCTION(),
        int         line     = __builtin_LINE(),
        char const* file     = __builtin_FILE());

    static void ImRenderUnit(
        char const* im_function,
        char const* im_id,
        char const* function = __builtin_FUNCTION(),
        int         line     = __builtin_LINE(),
        char const* file     = __builtin_FILE());

    static bool ImRenderExpr(
        bool        expr,
        char const* im_function,
        char const* function = __builtin_FUNCTION(),
        int         line     = __builtin_LINE(),
        char const* file     = __builtin_FILE());

    static void ImRenderUnit(
        std::string const& im_function,
        std::string const& im_id,
        char const*        function = __builtin_FUNCTION(),
        int                line     = __builtin_LINE(),
        char const*        file     = __builtin_FILE());

    static finally ImScopeRecord(
        std::string const& _What,
        std::string const& _Msg,
        char const*        function = __builtin_FUNCTION(),
        int                line     = __builtin_LINE(),
        char const*        file     = __builtin_FILE()) {
        (void)ImRenderTraceRecord::ImRenderBegin(
            true, _What.c_str(), _Msg.c_str(), function, line, file);
        return finally{[]() { ImRenderTraceRecord::ImRenderEnd(); }};
    }

    static void ImRenderEnd() { PopRecord(); }

    static void WriteTrace(OperationsTracer& trace);
    void        WriteRecord(OperationsTracer& trace, int level) const;
};

#define IM_SCOPE_BEGIN(_What, _Msg)                                       \
    ImRenderTraceRecord::ImScopeRecord(_What, _Msg);

#define IM_SEC_BEGIN(_Im_Func, ...)                                       \
    (void)ImRenderTraceRecord::ImRenderBegin(true, #_Im_Func, nullptr);   \
    ImGui::_Im_Func(__VA_ARGS__)

#define IM_SEC_END(_Im_Func, ...)                                         \
    ImREnderTraceRecord::ImRenderEnd();                                   \
    ImGui::_Im_Func(__VA_ARGS__);

#define IM_FN_BEGIN(_Im_Func, _Im_Id, ...)                                \
    ImRenderTraceRecord::ImRenderBegin(                                   \
        ImGui::_Im_Func((_Im_Id)__VA_OPT__(, ) __VA_ARGS__),              \
        #_Im_Func,                                                        \
        (_Im_Id))

#define IM_FN_END(_Im_Func)                                               \
    ImRenderTraceRecord::ImRenderEnd();                                   \
    ImGui::_Im_Func();

#define IM_FN_UNIT(_Im_Func, _Im_Id, ...)                                 \
    ImRenderTraceRecord::ImRenderUnit(#_Im_Func, (_Im_Id));               \
    ImGui::_Im_Func((_Im_Id)__VA_OPT__(, ) __VA_ARGS__)

#define IM_FN_EXPR(_Im_Func, ...)                                         \
    ImRenderTraceRecord::ImRenderExpr(                                    \
        ImGui::_Im_Func(__VA_ARGS__), #_Im_Func)


#define IM_FN_STMT(_Im_Func, ...)                                         \
    ImRenderTraceRecord::ImRenderUnit(#_Im_Func, nullptr);                \
    ImGui::_Im_Func(__VA_ARGS__)

#define IM_FN_PRINT(_What, _Msg)                                          \
    ImRenderTraceRecord::ImRenderUnit(_What, _Msg);
