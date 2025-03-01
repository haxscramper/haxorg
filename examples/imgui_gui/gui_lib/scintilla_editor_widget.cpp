#include <algorithm>
#include <assert.h>
#include <cstring>
#include <hstd/stdlib/Ptrs.hpp>
#include <map>
#include <stddef.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <set>

#include "scintilla_editor_widget.hpp"
#include "imgui_impl_opengl3.h"
#include "imgui_utils.hpp"
#include "imgui.h"
#include "imgui_internal.h"

#include <scintilla/src/Debugging.h>
#include <scintilla/include/Scintilla.h>
#include <scintilla/include/ScintillaTypes.h>
#include <scintilla/src/Geometry.h>
#include <scintilla/src/Platform.h>
#include <scintilla/include/Scintilla.h>
#include <scintilla/include/ILexer.h>
#include <lexilla/include/SciLexer.h>
#include <lexilla/lexlib/LexerModule.h>
#include <lexilla/lexlib/PropSetSimple.h>
#include <scintilla/src/CharClassify.h>
#include <scintilla/src/SplitVector.h>
#include <scintilla/src/Partitioning.h>
#include <scintilla/src/RunStyles.h>
#include <scintilla/src/Position.h>
#include <scintilla/src/ContractionState.h>
#include <scintilla/src/CellBuffer.h>
#include <scintilla/include/ScintillaMessages.h>
#include <scintilla/src/KeyMap.h>
#include <scintilla/src/Indicator.h>
#include <scintilla/src/XPM.h>
#include <scintilla/src/LineMarker.h>
#include <scintilla/src/Style.h>
#include <scintilla/src/UniqueString.h>
#include <scintilla/src/ViewStyle.h>
#include <scintilla/src/Decoration.h>
#include <scintilla/src/CharClassify.h>
#include <scintilla/src/CaseFolder.h>
#include <scintilla/include/ILoader.h>
#include <lexilla/lexlib/CharacterCategory.h>
using CharacterCategoryMap = Lexilla::CharacterCategoryMap;
#include <scintilla/src/Document.h>
#include <scintilla/src/Selection.h>
#include <scintilla/src/PositionCache.h>
#include <scintilla/src/EditModel.h>
#include <scintilla/src/MarginView.h>
#include <scintilla/include/ScintillaStructures.h>
#include <scintilla/src/EditView.h>
#include <scintilla/src/Editor.h>
#include <scintilla/src/AutoComplete.h>
#include <scintilla/src/CallTip.h>
#include <scintilla/src/ScintillaBase.h>

#include <hstd/stdlib/Exception.hpp>
#include <hstd/stdlib/Debug.hpp>
#include <hstd/system/Formatter.hpp>
#include <hstd/system/reflection.hpp>

#include <boost/mp11.hpp>
#include <boost/describe.hpp>

#define SCI_LOG_ROOT(__cat, __severity)                                   \
    ::hstd::log::log_builder{}.set_callsite().category(__cat).severity(   \
        __severity)

using namespace hstd;

const Vec<Str> scintilla_logging_scope{
    "gui",
    "widget",
    "scintilla_editor"};


namespace Scintilla::Internal {
BOOST_DESCRIBE_STRUCT(
    FontParameters,
    (),
    (faceName,
     size,
     weight,
     italic,
     extraFontFlag,
     technology,
     characterSet,
     localeName,
     stretch));


} // namespace Scintilla::Internal

namespace Scintilla {
BOOST_DESCRIBE_ENUM(CaseVisible, Mixed, Upper, Lower, Camel);
BOOST_DESCRIBE_ENUM(FontWeight, Normal, SemiBold, Bold);
BOOST_DESCRIBE_ENUM(
    FontQuality,
    QualityMask,
    QualityDefault,
    QualityNonAntialiased,
    QualityAntialiased,
    QualityLcdOptimized);

BOOST_DESCRIBE_ENUM(
    Technology,
    Default,
    DirectWrite,
    DirectWriteRetain,
    DirectWriteDC);

BOOST_DESCRIBE_ENUM(
    CharacterSet,
    Ansi,
    Default,
    Baltic,
    ChineseBig5,
    EastEurope,
    GB2312,
    Greek,
    Hangul,
    Mac,
    Oem,
    Russian,
    Oem866,
    Cyrillic,
    ShiftJis,
    Symbol,
    Turkish,
    Johab,
    Hebrew,
    Arabic,
    Vietnamese,
    Thai,
    Iso8859_15);


BOOST_DESCRIBE_ENUM(
    FontStretch,
    UltraCondensed,
    ExtraCondensed,
    Condensed,
    SemiCondensed,
    Normal,
    SemiExpanded,
    Expanded,
    ExtraExpanded,
    UltraExpanded);
} // namespace Scintilla

struct stbtt_Font {
    stbtt_fontinfo  fontinfo;
    stbtt_bakedchar cdata[96]; // ASCII 32..126 is 95 glyphs
    float           scale;
    float           fontSize;
};

using AutoSurface = Scintilla::Internal::AutoSurface;


using namespace Scintilla::Internal;

BOOST_DESCRIBE_STRUCT(
    Scintilla::Internal::PRectangle,
    (),
    (left, top, right, bottom));

template <>
struct std::formatter<PRectangle> : std::formatter<std::string> {
    template <typename FormatContext>
    auto format(const PRectangle& p, FormatContext& ctx) const {
        return fmt_ctx(
            fmt("[({}, {})+({}, {})]",
                p.left,
                p.top,
                p.right - p.left,
                p.bottom - p.top),
            ctx);
    }
};

template <>
struct std::formatter<ColourRGBA> : std::formatter<std::string> {
    template <typename FormatContext>
    auto format(const ColourRGBA& p, FormatContext& ctx) const {
        return fmt_ctx(
            fmt("({}, {}, {}, {})",
                p.GetRed(),
                p.GetGreen(),
                p.GetBlue(),
                p.GetAlpha()),
            ctx);
    }
};


template <typename T>
concept NotChar = !std::is_same_v<T, char>
               && !std::is_same_v<T, unsigned char>
               && !std::is_same_v<T, signed char>;

template <NotChar T, int Size>
struct std::formatter<T[Size]> : std::formatter<std::string> {
    template <typename FormatContext>
    auto format(T p[Size], FormatContext& ctx) const {
        fmt_ctx("[", ctx);
        bool first = true;
        for (int i = 0; i < Size; ++i) {
            T const& value = p[i];
            if (!first) { fmt_ctx(", ", ctx); }
            first = false;
            fmt_ctx(value, ctx);
        }
        return fmt_ctx("]", ctx);
    }
};


namespace ImGui {

ScEditor* ScInputText(const char* label, const ImVec2& size) {


    ImGuiID const id      = GetCurrentWindow()->GetID(label);
    ImGuiStorage* storage = GetStateStorage();
    ScEditor*     editor  = (ScEditor*)storage->GetVoidPtr(id);

    if (!editor) {
        editor = new ScEditor();
        editor->Initialise();
        storage->SetVoidPtr(id, (void*)editor);
        editor->SetDefaultFont("Iosevka");
    }

    editor->globalCursor = ImGui::GetCursorScreenPos();
    editor->windowCursor = ImGui::GetCursorPos();
    if (size.x != 0 && size.y != 0) {
        render_debug_rect(size, IM_COL32(0, 255, 0, 255));
    }

    if (size.x == 0 || size.y == 0) {
        ImVec2 available = ImGui::GetContentRegionAvail();
        editor->Resize(available);
    } else {
        editor->Resize(size);
    }

    return editor;
}

} // namespace ImGui


struct CacheMapEqImpl {
    bool operator()(FontParameters const& lhs, FontParameters const& rhs)
        const {
        bool res = std::string_view{lhs.faceName}
                    == std::string_view{rhs.faceName}     //
                && lhs.size == rhs.size                   //
                && lhs.weight == rhs.weight               //
                && lhs.italic == rhs.italic               //
                && lhs.extraFontFlag == rhs.extraFontFlag //
                && lhs.technology == rhs.technology       //
                && lhs.characterSet == rhs.characterSet;
        return res;
    }
};

struct CacheMapHashImpl {
    std::size_t operator()(FontParameters const& h) const {
        std::size_t hash = 0;
        hax_hash_combine(hash, std::string{h.faceName});
        hax_hash_combine(hash, h.size);
        hax_hash_combine(hash, h.italic);
        hax_hash_combine(hash, h.extraFontFlag);
        hax_hash_combine(hash, h.technology);
        hax_hash_combine(hash, h.characterSet);
        return hash;
    }
};

struct ImFontWrap : public Font {
    using CacheMapType = std::unordered_map<
        FontParameters,
        SPtr<ImFontWrap>,
        CacheMapHashImpl,
        CacheMapEqImpl>;

    static CacheMapType fontCache;

    static Vec<SPtr<ImFontWrap>> pending_fonts;

    static SPtr<ImFontWrap> LoadFont(FontParameters const& fp) {
        auto result = std::make_shared<ImFontWrap>(fp);
        pending_fonts.push_back(result);
        return result;
    }

    static SPtr<ImFontWrap> GetFontForParameters(
        FontParameters const& fp) {
        auto iter = fontCache.find(fp);
        if (iter == fontCache.end()) {
            return LoadFont(fp);

            // for debug
            std::string msg;
            for (auto const& [k, _] : fontCache) {
                SCI_LOG_ROOT("font", hstd::log::l_info)
                    .fmt_message(
                        "== -> {}\n{} {}\n{} {}",
                        CacheMapEqImpl{}(fp, k),
                        CacheMapHashImpl{}(fp),
                        fp,
                        CacheMapHashImpl{}(k),
                        k);

                msg += fmt("\n{}", k);
            }
            throw std::logic_error(
                fmt("Cannot load font at runtime, parameters were\n{}\n"
                    "Already loaded fonts{}",
                    fp,
                    msg));
        } else {
            return iter->second;
        }
    }

    static bool ResolvePendingFonts() {
        ImGuiIO& io = ImGui::GetIO();
        for (auto& font : pending_fonts) {
            SCI_LOG_ROOT("font", hstd::log::l_info)
                .fmt_message("Creating font for parameters {}", font->fp);
            auto font_path = get_fontconfig_path(font->fp.faceName);
            LOGIC_ASSERTION_CHECK(
                font_path.has_value(),
                "Could not find font path for '{}'",
                font->fp.faceName);
            SCI_LOG_ROOT("font", hstd::log::l_info)
                .fmt_message("Using font file {}", *font_path);

            ImFontConfig fontConfig;
            fontConfig.SizePixels           = font->fp.size;
            fontConfig.RasterizerMultiply   = 1.0f;
            fontConfig.OversampleH          = 3;
            fontConfig.OversampleV          = 1;
            fontConfig.FontDataOwnedByAtlas = true;
            fontConfig.MergeMode            = false;

            fontConfig.GlyphExtraSpacing.x = ((int)font->fp.weight > 500)
                                               ? 1.0f
                                               : 0.0f;
            fontConfig.GlyphOffset         = ImVec2(
                0, font->fp.italic ? 1.0f : 0.0f);

            font->pfont = io.Fonts->AddFontFromFileTTF(
                font_path->c_str(), font->fp.size, &fontConfig);

            font->metrics = StbFontMetrics::FromPath(
                font_path.value(), font->fp.size);

            fontCache.insert_or_assign(font->fp, font);
            SCI_LOG_ROOT("font", hstd::log::l_info)
                .fmt_message("Added font for {}", font->fp);
        }

        if (pending_fonts.empty()) {
            return false;
        } else {
            int            width, height;
            unsigned char* pixels = nullptr;
            io.Fonts->GetTexDataAsRGBA32(&pixels, &width, &height);
            ImGui_ImplOpenGL3_CreateFontsTexture();
            pending_fonts.clear();
            return true;
        }
    }

    FontParameters       fp;
    ImFont*              pfont;
    SPtr<StbFontMetrics> metrics;

    int GetCharWidth(char ch) const {
        if (metrics) {
            return metrics->WidthChar(ch);
        } else if (ImFont* font = ImGui::GetFont()) {
            return font->GetCharAdvance(ch);
        } else {
            return 16;
        }
    }

    int GetAscent() const {
        if (metrics) {
            return metrics->GetAscentDescent().first;
        } else {
            return 9;
        }
    }

    int GetDescent() const {
        if (metrics) {
            return metrics->GetAscentDescent().second;
        } else {
            return -2;
        }
    }

    int AverageCharWidth() const {
        if (metrics) {
            return metrics->WidthChar('\n');
        } else if (ImFont* font = ImGui::GetFont()) {
            return font->GetCharAdvance('\n');
        } else {
            return fp.size;
        }
    }

    int GetTextWidth(std::string_view const& text) const {
        if (metrics) {
            return metrics->GetTextWidth(text);
        } else if (ImFont* font = ImGui::GetFont()) {
            return font
                ->CalcTextSizeA(
                    font->FontSize,
                    FLT_MAX,
                    0.0f,
                    text.data(),
                    text.data() + text.size())
                .x;
        } else {
            return text.size() * AverageCharWidth();
        }
    }


    explicit ImFontWrap(const FontParameters& fp) : fp{fp} {
        pfont = ImGui::GetFont();
    }
};

Vec<SPtr<ImFontWrap>>    ImFontWrap::pending_fonts;
ImFontWrap::CacheMapType ImFontWrap::fontCache;

void run_scintilla_editor_widget_test(GLFWwindow* window) {
    while (!glfwWindowShouldClose(window)) {
        bool updatedFont = ImFontWrap::ResolvePendingFonts();

        frame_start();
        // const ImGuiViewport* viewport = ImGui::GetMainViewport();
        // ImGui::SetNextWindowPos(viewport->WorkPos);
        // ImGui::SetNextWindowSize(viewport->WorkSize);

        ImGui::Begin("Fullscreen Window", nullptr);
        if (ImGui::BeginTable(
                "test_table",
                1,
                ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg)) {


            ImGui::TableNextRow();
            ImGui::TableSetColumnIndex(0);
            ImGui::Text("Some random text");
            ImGui::TableNextRow();

            ImGui::TableSetColumnIndex(0);
            auto ed = ImGui::ScInputText("editor");

            auto action = ed->HandleInput();
            if (action.hadEvents) {
                SCI_LOG_ROOT("font", hstd::log::l_trace)
                    .fmt_message("{}", action);
            }

            if (updatedFont) { ed->FullRedraw(); }

            ed->Render();
            ImGui::TableNextRow();
            ImGui::TableSetColumnIndex(0);
            ImGui::Text("After text input");
            ImGui::EndTable();
        }
        ImGui::End();
        frame_end(window);
    }
}


ImU32 ToImGui(ColourRGBA const& c) {
    return IM_COL32(c.GetRed(), c.GetGreen(), c.GetBlue(), c.GetAlpha());
}

class SurfaceImpl : public Scintilla::Internal::Surface {
  public:
    SurfaceImpl() { message("Create surface impl"); }
    virtual ~SurfaceImpl() {}

    ImVec2 pos;

    ImDrawList*       DrawList() { return ImGui::GetWindowDrawList(); }
    ImVec2            GetPos() { return pos; }
    ImFontWrap const* GetFont(Font const* f) {
        return dynamic_cast<ImFontWrap const*>(f);
    }

    void message(
        std::string const& msg,
        bool               reset    = false,
        int                line     = __builtin_LINE(),
        char const*        function = __builtin_FUNCTION(),
        char const*        file     = __builtin_FILE()) {
        HSLOG_BUILDER()
            .set_callsite(line, function, file)
            .category("surface")
            .severity(hstd::log::l_trace)
            .message(msg)
            .source_scope(scintilla_logging_scope)
            .set_finalizer(HSLOG_UNIQUE_VALUE_FILTER_FINALIZER(reset));
    }

    // clang-format off
    virtual void Init(WindowID wid) override {  }
    virtual void Init(SurfaceID sid, WindowID wid) override { }
    virtual void SetMode(SurfaceMode mode) override { }

    virtual void Release() noexcept override  { }
    virtual int SupportsFeature(Scintilla::Supports feature) noexcept override  { return false; }
    virtual bool Initialised() override  { return true; }
    virtual int LogPixelsY() override  { return 72; }
    virtual int PixelDivisions() override  {  abort(); }

    virtual void LineDraw(Point start, Point end, Stroke stroke) override  {  abort(); }
    virtual void PolyLine(const Point *pts, size_t npts, Stroke stroke) override  {  abort(); }
    virtual void Polygon(const Point *pts, size_t npts, FillStroke fillStroke) override  {  abort(); }
    virtual void RectangleDraw(PRectangle rc, FillStroke fillStroke) override  {  abort(); }
    virtual void RectangleFrame(PRectangle rc, Stroke stroke) override  {  abort(); }


    virtual void RoundedRectangle(PRectangle rc, FillStroke fillStroke) override  {  abort(); }
    virtual void AlphaRectangle(PRectangle rc, XYPOSITION cornerSize, FillStroke fillStroke) override  {  abort(); }
    virtual void GradientRectangle(PRectangle rc, const std::vector<ColourStop> &stops, GradientOptions options) override  {  abort(); }
    virtual void DrawRGBAImage(PRectangle rc, int width, int height, const unsigned char *pixelsImage) override {}
    virtual void Ellipse(PRectangle rc, FillStroke fillStroke) override  {  abort(); }
    virtual void Stadium(PRectangle rc, FillStroke fillStroke, Ends ends) override  {  abort(); }
    virtual void Copy(PRectangle rc, Point from, Surface &surfaceSource) override  {  abort(); }

    virtual std::unique_ptr<IScreenLineLayout> Layout(const IScreenLine *screenLine) override { abort(); }

    virtual void DrawTextNoClip(PRectangle rc, const Font *font_, XYPOSITION ybase, std::string_view text, ColourRGBA fore, ColourRGBA back) override { abort(); }
    virtual void DrawTextClipped(PRectangle rc, const Font *font_, XYPOSITION ybase, std::string_view text, ColourRGBA fore, ColourRGBA back) override { abort(); }

    virtual void MeasureWidths(const Font *font_, std::string_view text, XYPOSITION *positions) override { abort(); }

    virtual void DrawTextNoClipUTF8(PRectangle rc, const Font *font_, XYPOSITION ybase, std::string_view text, ColourRGBA fore, ColourRGBA back) override { abort(); }
    virtual void DrawTextClippedUTF8(PRectangle rc, const Font *font_, XYPOSITION ybase, std::string_view text, ColourRGBA fore, ColourRGBA back) override { abort(); }
    virtual void DrawTextTransparentUTF8(PRectangle rc, const Font *font_, XYPOSITION ybase, std::string_view text, ColourRGBA fore) override { abort(); }

    virtual XYPOSITION WidthTextUTF8(const Font *font_, std::string_view text) override { abort(); }


    virtual XYPOSITION InternalLeading(const Font *font_) override  { return 0; }
    virtual XYPOSITION Height(const Font *font_) override  {  abort(); }

    virtual void FlushCachedState() override  { }
    virtual void FlushDrawing() override  { }
    // clang-format on


    virtual void SetClip(PRectangle rc) override {
        message(fmt("Set clip {}", rc));
        DrawList()->PushClipRect(
            GetPos() + ImVec2(rc.left, rc.top),
            GetPos() + ImVec2(rc.right, rc.bottom),
            true);
    }

    virtual void PopClip() override {
        message(fmt("Pop clip"));
        DrawList()->PopClipRect();
    }

    virtual void FillRectangle(PRectangle rc, Surface& surfacePattern)
        override {

        message(fmt("Fill rectangle {}", rc));

        DrawList()->AddRectFilled(
            GetPos() + ImVec2(rc.left, rc.top),
            GetPos() + ImVec2(rc.right, rc.bottom),
            ToImGui(pen));
    }

    virtual void MeasureWidthsUTF8(
        const Font*      font_,
        std::string_view text,
        XYPOSITION*      positions) override {
        float position = 0;
        for (auto const& c : text) {
            position += GetFont(font_)->GetCharWidth(c);
            *positions++ = position;
        }
    }

    void DrawTextBase(
        PRectangle       rc,
        Font const*      font_,
        float            ybase,
        std::string_view s,
        ColourRGBA       f) {
        message(
            fmt("Draw text '{}' in {} base {}",
                escape_literal(std::string{s.begin(), s.end()}),
                rc,
                ybase));

        int vfix = 0;
        vfix += std::abs(GetFont(font_)->GetAscent());
        vfix += std::abs(GetFont(font_)->GetDescent());

        DrawList()->AddText(
            GetFont(font_)->pfont,
            GetFont(font_)->pfont->FontSize,
            GetPos() + ImVec2(rc.left, ybase - vfix),
            ToImGui(f),
            s.data(),
            s.data() + s.size());
    }

    virtual void DrawTextTransparent(
        PRectangle       rc,
        const Font*      font_,
        XYPOSITION       ybase,
        std::string_view text,
        ColourRGBA       fore) override {
        DrawTextBase(rc, font_, ybase, text, fore);
    }

    virtual void FillRectangle(PRectangle rc, Fill fill) override {
        DrawList()->AddRectFilled(
            GetPos() + ImVec2(rc.left, rc.top),
            GetPos() + ImVec2(rc.right, rc.bottom),
            ToImGui(fill.colour));
    }

    virtual void FillRectangleAligned(PRectangle rc, Fill fill) override {
        FillRectangle(rc, fill);
    }

    virtual std::unique_ptr<Surface> AllocatePixMap(int width, int height)
        override {
        return std::make_unique<SurfaceImpl>();
    }

    virtual int DeviceHeightFont(int points) override {
        int logPix = LogPixelsY();
        return (int)((points * logPix + logPix / 2) / 72.0f);
    }

    virtual XYPOSITION AverageCharWidth(const Font* font_) override {
        return GetFont(font_)->AverageCharWidth();
    }

    virtual XYPOSITION Ascent(const Font* font_) override {
        return GetFont(font_)->GetAscent();
    }

    virtual XYPOSITION Descent(const Font* font_) override {
        return GetFont(font_)->GetDescent();
    }

    virtual XYPOSITION WidthText(const Font* font_, std::string_view text)
        override {
        return GetFont(font_)->GetTextWidth(text);
    }

  private:
    ColourRGBA pen;
};

namespace {
SciWindowImpl* window(WindowID wid) {
    return static_cast<SciWindowImpl*>(wid);
}
} // namespace

PRectangle Window::GetPosition() const { return window(wid)->frame; }

void Window::SetPosition(PRectangle rc) { window(wid)->frame = rc; }

void Window::InvalidateRectangle(PRectangle rc) {
    if (wid) {}
}


std::unique_ptr<Scintilla::Internal::Surface> Scintilla::Internal::
    Surface::Allocate(Scintilla::Technology technology) {
    return std::make_unique<SurfaceImpl>();
}

std::shared_ptr<Font> Font::Allocate(const FontParameters& fp) {
    return ImFontWrap::GetFontForParameters(fp);
}

::hstd::log::log_builder ScEditor::message(
    ::hstd::log::severity_level level,
    const Str&                  msg,
    int                         line,
    const char*                 function,
    const char*                 file) {
    return ::hstd::log::log_builder{}
        .category("edit")
        .severity(level)
        .source_scope(scintilla_logging_scope)
        .source_id(fmt("_{:p}", static_cast<void const*>(this)))
        .message(msg)
        .function(function)
        .line(line)
        .file(file);
}

void ScEditor::SetDefaultFont(const std::string& family) {
    SendCommand(
        SCI_M::StyleSetFont,
        STYLE_DEFAULT,
        reinterpret_cast<sptr_t>(family.data()));
    SendCommand(SCI_M::StyleClearAll);
}

void ScEditor::AddText(const std::string& text) {
    SendCommand(
        SCI_M::AddText,
        text.size(),
        reinterpret_cast<sptr_t>(static_cast<const char*>(text.data())));
}

void ScEditor::SetText(const std::string& text) {
    SendCommand(
        SCI_M::SetText,
        text.size(),
        reinterpret_cast<sptr_t>(static_cast<const char*>(text.data())));
}

int ScEditor::GetWordEndPosition(int position, bool onlyWordCharacters) {
    return (int)SendCommand(
        SCI_M::WordEndPosition,
        uptr_t(position),
        sptr_t(onlyWordCharacters));
}

char* ScEditor::GetTextRange(int startPosition, int endPosition) {
    if (endPosition < startPosition) {
        int temp      = startPosition;
        startPosition = endPosition;
        endPosition   = temp;
    }

    int length = endPosition - startPosition;
    if (!length) { return nullptr; }

    char* result = static_cast<char*>(
        malloc(sizeof(char) * (size_t)length + 1));

    Sci_TextRange textRange;
    textRange.lpstrText  = result;
    textRange.chrg.cpMin = startPosition;
    textRange.chrg.cpMax = endPosition;

    SendCommand(SCI_M::GetTextRange, 0, sptr_t(&textRange));
    result[length] = '\0';

    return result;
}

char* ScEditor::GetWordFromPosition(int position, int& start, int& end) {
    end   = GetWordEndPosition(position, true);
    start = GetWordStartPosition(position, true);
    return GetTextRange(start, end);
}

ScEditor::InputResult ScEditor::HandleInput() {
    InputResult res;
    ImGuiIO&    io               = ImGui::GetIO();
    int         beforeTextLength = SendCommand(SCI_M::GetTextLength);
    if (ImGui::IsMouseClicked(0)) {
        auto pos = GlobalSpaceToScintilla(io.MouseClickedPos[0]);


        auto pt = Point::FromInts(pos.x, pos.y);
        ButtonDownWithModifiers(
            pt, io.MouseDownDuration[0], Scintilla::KeyMod::Norm);
        res.hadEvents = true;
        message(
            hstd::log::l_trace,
            fmt("Clicked mouse at {}, sci pos {}, cursor pos {}",
                io.MouseClickedPos[0],
                pos,
                GetPosition()));
    } else if (
        !io.KeyCtrl     //
        && !io.KeyAlt   //
        && !io.KeySuper //
        && 0 < io.InputQueueCharacters.Size) {
        auto debug //
            = message(hstd::log::l_trace, "Typed ")
                  .fmt_message(
                      "{} characters at {}:",
                      io.InputQueueCharacters.Size,
                      GetPosition())
                  .get_record();

        for (int i = 0; i < io.InputQueueCharacters.Size; ++i) {
            ImWchar c = io.InputQueueCharacters[i];
            if (32 <= c && c < 127 || c == '\n') {
                debug.fmt_message(
                    " '{}'", visibleName(static_cast<char>(c)).first);
                char charAsStr[2] = {static_cast<char>(c), '\0'};
                SendCommand(
                    SCI_M::ReplaceSel,
                    0,
                    reinterpret_cast<sptr_t>(charAsStr));
                res.hadEvents = true;
            } else {
                debug.fmt_message(" '{}'", c);
            }
        }

        debug.fmt_message(". End position {}", GetPosition());

        debug.end();

        io.InputQueueCharacters.clear();
    }

    int afterTextLength = SendCommand(SCI_M::GetTextLength);

    if (beforeTextLength != afterTextLength) { res.inputChanged = true; }

    return res;
}

void ScEditor::Render() {
    PRectangle rcPaint = GetClientRectangle();

    AutoSurface surf{this};
    auto        impl = dynamic_cast<SurfaceImpl*>(surf.operator->());
    impl->pos        = globalCursor;

    if (surf) {
        Paint(surf, rcPaint);
        surf->Release();
    }
}

void ScEditor::Initialise() {
    wMain = NewWindowImpl();

    ImGuiIO& io = ImGui::GetIO();
    wMain.SetPosition(PRectangle::FromInts(
        0, 0, int(io.DisplaySize.x), int(io.DisplaySize.y)));

    // We need to disable buffered draw so Scintilla doesn't keep a
    // yoffset of 0 when rendering text, thinking we are blitting
    // through a pixmap. We want a single draw list for efficiency.
    view.bufferedDraw = false;


    SendCommand(SCI_M::StyleSetSize, STYLE_DEFAULT, 16);

    SetFocusState(true);
    CaretSetPeriod(0);
}

void ScEditor::Resize(const ImVec2& size) {
    wMain.SetPosition(PRectangle::FromInts(0, 0, size.x, size.y));
}

void ScEditor::CreateCallTipWindow(Scintilla::Internal::PRectangle rc) {
    if (!ct.wCallTip.Created()) {
        // ct.wCallTip = new CallTip(stc, &ct, this);
        ct.wCallTip = NewWindowImpl();
        ct.wDraw    = &ct.wCallTip;
    }
}
