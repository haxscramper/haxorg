#include "imgui_utils.hpp"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <hstd/system/Formatter.hpp>

#include <fontconfig/fontconfig.h>

#define STBTT_STATIC
#define STB_TRUETYPE_IMPLEMENTATION
#include <stb/stb_truetype.h>

#include <fstream>

Vec<ImRenderTraceRecord> ImRenderTraceRecord::stack;
bool                     ImRenderTraceRecord::TraceState;


void AddTextWithBackground(
    ImDrawList*        draw_list,
    const ImVec2&      position,
    ImU32              text_color,
    const std::string& text,
    ImU32              background_color) {
    ImFont* font      = ImGui::GetFont();
    ImVec2  text_size = font->CalcTextSizeA(
        font->FontSize, FLT_MAX, 0.0f, text.c_str());
    ImVec2 rect_min = position;
    ImVec2 rect_max = ImVec2(
        position.x + text_size.x, position.y + text_size.y);
    draw_list->AddRectFilled(rect_min, rect_max, background_color);
    draw_list->AddText(
        font, font->FontSize, position, text_color, text.c_str());
}


void frame_start() {
    glfwPollEvents();

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void frame_end(GLFWwindow* window) {
    ImGui::Render();
    int display_w, display_h;
    glfwGetFramebufferSize(window, &display_w, &display_h);
    glViewport(0, 0, display_w, display_h);
    glClearColor(0.45f, 0.55f, 0.60f, 1.00f);
    glClear(GL_COLOR_BUFFER_BIT);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    glfwSwapBuffers(window);
}

void quit_on_q(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}


void fullscreen_window_begin() {
    const ImGuiViewport* viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(viewport->WorkPos);
    ImGui::SetNextWindowSize(viewport->WorkSize);

    ImGui::Begin(
        "Fullscreen Window",
        nullptr,
        ImGuiWindowFlags_NoDecoration
            | ImGuiWindowFlags_NoBringToFrontOnFocus
            | ImGuiWindowFlags_NoNav);
}

int push_frameless_window_vars() {
    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0);
    ImGui::PushStyleVar(ImGuiStyleVar_ChildBorderSize, 0);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
    return 3;
}

void render_debug_rect(const ImVec2& size, ImU32 const& col) {
    render_debug_rect(
        ImRect(
            ImGui::GetCursorScreenPos(),
            ImGui::GetCursorScreenPos() + size),
        col);
}


void render_debug_rect(const ImRect& rect, const ImU32& col) {
    ImGui::GetForegroundDrawList()->AddRect(rect.Min, rect.Max, col);
}


Opt<Str> get_fontconfig_path(Str const& fontname) {
    FcInit();
    FcPattern* pattern = FcNameParse((const FcChar8*)fontname.c_str());
    FcConfigSubstitute(nullptr, pattern, FcMatchPattern);
    FcDefaultSubstitute(pattern);

    FcResult   result;
    FcPattern* match = FcFontMatch(nullptr, pattern, &result);

    FcChar8* font_path = nullptr;
    if (match) { FcPatternGetString(match, FC_FILE, 0, &font_path); }
    Opt<Str> opt_result;
    if (font_path != nullptr) { opt_result = (char const*)font_path; }
    FcPatternDestroy(pattern);
    FcPatternDestroy(match);
    FcFini();
    return opt_result;
}

SPtr<StbFontMetrics> StbFontMetrics::FromPath(
    const std::string& fontPath,
    float              fontSize) {
    auto result      = std::make_shared<StbFontMetrics>();
    result->fontSize = fontSize;
    std::ifstream fontFile{fontPath, std::ios::binary | std::ios::ate};
    if (!fontFile.is_open()) {
        throw std::runtime_error(
            fmt("Failed to open font file {}", fontPath));
    }

    std::streamsize size = fontFile.tellg();
    fontFile.seekg(0, std::ios::beg);
    result->buffer.resize(size);
    if (!fontFile.read((char*)result->buffer.data(), size)) {
        throw std::runtime_error(
            fmt("Failed to read font file {}", fontPath));
    }

    if (!stbtt_InitFont(
            &result->font,
            result->buffer.data(),
            stbtt_GetFontOffsetForIndex(result->buffer.data(), 0))) {
        throw std::runtime_error(
            fmt("Failed to initialize font from file {}", fontPath));
    }

    result->scale = stbtt_ScaleForPixelHeight(&result->font, fontSize);

    result->GetAscentDescent();


    return result;
}

int StbFontMetrics::WidthChar(char ch) const {
    int advance, leftBearing;
    stbtt_GetCodepointHMetrics(&font, ch, &advance, &leftBearing);
    return advance * scale;
}

Pair<int, int> StbFontMetrics::GetAscentDescent() const {
    int ascent  = 0;
    int descent = 0;
    int lineGap = 0;
    stbtt_GetFontVMetrics(&font, &ascent, &descent, &lineGap);
    ascent  = static_cast<int>(ascent * scale);
    descent = static_cast<int>(descent * scale);
    return std::make_pair(ascent, descent);
}

int StbFontMetrics::GetTextWidth(const std::string_view& text) const {
    int textWidth = 0;
    for (char c : text) {
        int advanceWidth, leftSideBearing;
        stbtt_GetCodepointHMetrics(
            &font, c, &advanceWidth, &leftSideBearing);
        textWidth += static_cast<int>(advanceWidth * scale);
    }

    return textWidth;
}

org_logging::log_record ImRenderTraceRecord::to_org_log_record() const {
    org_logging::log_record res;
    res.set_callsite(line, function, file);
    if (cursor_winpos) {
        res.metadata("cursor_winpos", fmt1(cursor_winpos.value()));
    }
    if (cursor_screenpos) {
        res.metadata("cursor_screenpos", fmt1(cursor_screenpos.value()));
    }
    if (im_function) { res.fmt_message("Call {}", im_function.value()); }
    if (im_id) { res.fmt_message("", fmt1(im_id)); }
    res.source_scope({"gui", "imgui"});
    return res;
}

void ImRenderTraceRecord::StartTrace() {
    stack.clear();
    TraceState = true;
}

void ImRenderTraceRecord::EndTrace() { TraceState = false; }

void ImRenderTraceRecord::PushRecord(const ImRenderTraceRecord& rec) {
    if (TraceState) { stack.push_back(rec); }
}

void ImRenderTraceRecord::PushUnitRecord(const ImRenderTraceRecord& rec) {
    if (TraceState) {
        if (stack.empty()) {
            stack.push_back(ImRenderTraceRecord::init());
        }
        stack.back().nested.push_back(rec);
    }
}

void ImRenderTraceRecord::PopRecord() {
    if (TraceState) { PushUnitRecord(stack.pop_back_v()); }
}

ImRenderTraceRecord ImRenderTraceRecord::init(
    const char* function,
    int         line,
    const char* file) {
    ImRenderTraceRecord res;
    if (TraceState) {
        res.function         = function;
        res.line             = line;
        res.file             = file;
        res.cursor_screenpos = ImGui::GetCursorScreenPos();
        res.cursor_winpos    = ImGui::GetCursorPos();
    }
    return res;
}

bool ImRenderTraceRecord::ImRenderBegin(
    bool        expr,
    const char* im_function,
    const char* im_id,
    const char* function,
    int         line,
    const char* file) {
    if (TraceState) {
        auto rec        = ImRenderTraceRecord::init(function, line, file);
        rec.im_function = im_function;
        if (im_id) { rec.im_id = im_id; }
        PushRecord(rec);
    }
    return expr;
}

void ImRenderTraceRecord::ImRenderUnit(
    const char* im_function,
    const char* im_id,
    const char* function,
    int         line,
    const char* file) {
    if (TraceState) {
        auto rec        = ImRenderTraceRecord::init(function, line, file);
        rec.im_function = im_function;
        if (im_id) { rec.im_id = im_id; }
        PushUnitRecord(rec);
    }
}

bool ImRenderTraceRecord::ImRenderExpr(
    bool        expr,
    const char* im_function,
    const char* function,
    int         line,
    const char* file) {
    if (TraceState) {
        auto rec        = ImRenderTraceRecord::init(function, line, file);
        rec.im_function = im_function;
        rec.im_id       = fmt("Evaluated to {}", expr);
        PushUnitRecord(rec);
        auto tmp = rec.to_org_log_record();
        tmp.source_scope_add("expr");
        tmp.end();
    }
    return expr;
}

void ImRenderTraceRecord::ImRenderUnit(
    const std::string& im_function,
    const std::string& im_id,
    const char*        function,
    int                line,
    const char*        file) {
    if (TraceState) {
        auto rec        = ImRenderTraceRecord::init(function, line, file);
        rec.im_function = im_function;
        rec.im_id       = im_id;
        PushUnitRecord(rec);
    }
}

void ImRenderTraceRecord::WriteTrace(OperationsTracer& trace) {
    for (auto const& [idx, s] : enumerate(stack)) {
        auto os = trace.getStream();
        os << fmt("[{}] -- ", idx);
        trace.endStream(os);
        s.WriteRecord(trace, idx + 1);
    }
}

void ImRenderTraceRecord::WriteRecord(OperationsTracer& trace, int level)
    const {
    auto os = trace.getStream();

    os.indent(level * 2);
    os << fmt(
        "{} at {}:{} to draw {}",
        im_function.value_or("<>"),
        file ? fs::path{file}.filename() : "",
        line,
        escape_for_write(im_id.value_or("?")));

    if (cursor_screenpos) {
        os << fmt(" screen {}", cursor_screenpos.value());
    }

    if (cursor_winpos) { os << fmt(" win {}", cursor_winpos.value()); }

    trace.endStream(os);

    for (auto const& sub : nested) { sub.WriteRecord(trace, level + 1); }
}

ImVec2 getCurrentWindowContentPos() {
    return ImGui::GetWindowPos()
         + ImVec2{0, ImGui::GetCurrentWindow()->TitleBarHeight};
}

void AddText(
    ImDrawList*        list,
    ImVec2 const&      pos,
    const ImU32&       color,
    const std::string& text) {
    list->AddText(pos, color, text.data(), text.data() + text.size());
}
