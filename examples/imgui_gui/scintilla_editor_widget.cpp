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

struct WindowImpl {
    ImGuiWindow* im;
    PRectangle   frame{};
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

struct ScEditor : public Scintilla::Internal::ScintillaBase {
    using SCI_M = Scintilla::Message;

    void SetDefaultFont(std::string const& family) {
        SendCommand(
            SCI_M::StyleSetFont,
            STYLE_DEFAULT,
            reinterpret_cast<sptr_t>(family.data()));
        SendCommand(SCI_M::StyleClearAll);
    }

    void FullRedraw() {
        SendCommand(SCI_M::StyleClearAll);
        // SendCommand(SCI_M::Colourise, 0, -1);
        // SendCommand(SCI_M::Inva)
    }

    void ScrollTo(Sci::Line line, bool moveThumb = true) {
        Scintilla::Internal::ScintillaBase::ScrollTo(line, moveThumb);
    }

    void ToggleBreakpoint() {}


    bool IsComment(int position) {
        sptr_t style = SendCommand(SCI_M::GetStyleAt, (uptr_t)position);

        return style == 2;
    }


    int GetWordStartPosition(int position, bool onlyWordCharacters) {
        return (int)SendCommand(
            SCI_M::WordStartPosition,
            (uptr_t)position,
            (sptr_t)onlyWordCharacters);
    }


    int GetWordEndPosition(int position, bool onlyWordCharacters) {
        return (int)SendCommand(
            SCI_M::WordEndPosition,
            uptr_t(position),
            sptr_t(onlyWordCharacters));
    }


    char* GetTextRange(int startPosition, int endPosition) {
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


    char* GetWordFromPosition(int position, int& start, int& end) {
        end   = GetWordEndPosition(position, true);
        start = GetWordStartPosition(position, true);
        return GetTextRange(start, end);
    }


    static bool IsKeyPressedMap(ImGuiKey key, bool repeat = false) {
        return ImGui::IsKeyPressed(key, repeat);
    }


    struct InputResult {
        bool inputChanged;
        bool hadEvents;
        DESC_FIELDS(InputResult, (inputChanged, hadEvents));
    };

    ImVec2 GlobalSpaceToScintilla(ImVec2 const& windowSpace) {
        return windowSpace - globalCursor;
    }

    std::string GetText() {
        int   textLength = SendCommand(SCI_M::GetTextLength);
        char* buffer     = new char[textLength + 1];
        SendCommand(
            SCI_M::GetText,
            textLength + 1,
            reinterpret_cast<sptr_t>(buffer));

        std::string text(buffer);
        delete[] buffer;
        return text;
    }

    InputResult HandleInput() {
        InputResult res;
        ImGuiIO&    io               = ImGui::GetIO();
        int         beforeTextLength = SendCommand(SCI_M::GetTextLength);
        if (ImGui::IsMouseClicked(0)) {
            auto pos = GlobalSpaceToScintilla(io.MouseClickedPos[0]);
            LOG(INFO) << fmt(
                "Clicked mouse at {} sci pos {}", io.MouseClickedPos, pos);
            auto pt = Point::FromInts(pos.x, pos.y);
            ButtonDownWithModifiers(
                pt, io.MouseDownDuration[0], Scintilla::KeyMod::Norm);
            res.hadEvents = true;
        } else if (!io.KeyCtrl && !io.KeyAlt && !io.KeySuper) {
            for (int i = 0; i < io.InputQueueCharacters.Size; ++i) {
                ImWchar c = io.InputQueueCharacters[i];
                if (32 <= c && c < 127) {
                    char charAsStr[2] = {static_cast<char>(c), '\0'};
                    SendCommand(
                        SCI_M::ReplaceSel,
                        0,
                        reinterpret_cast<sptr_t>(charAsStr));
                    res.hadEvents = true;
                }
            }

            io.InputQueueCharacters.clear();
        }

        int afterTextLength = SendCommand(SCI_M::GetTextLength);

        if (beforeTextLength != afterTextLength) {
            res.inputChanged = true;
        }

        return res;
    }


    void Render();

    static WindowImpl* NewWindowImpl() {
        auto windowImpl = new WindowImpl{};
        windowImpl->im  = ImGui::GetCurrentWindow();
        return windowImpl;
    }

    void Initialise() override {
        wMain = NewWindowImpl();

        ImGuiIO& io = ImGui::GetIO();
        wMain.SetPosition(PRectangle::FromInts(
            0, 0, int(io.DisplaySize.x), int(io.DisplaySize.y)));

        // We need to disable buffered draw so Scintilla doesn't keep a
        // yoffset of 0 when rendering text, thinking we are blitting
        // through a pixmap. We want a single draw list for efficiency.
        view.bufferedDraw = false;

        std::string text{
            " asdf asd fd d d asd fas df asdf as dfas df as df asdf asdf "
            "as dfas df asdf as dfa sdf asd fas df asd fas dfas df "
            "asd\n\n\n\n\n\n 923423aksf sadf sadf asdfasdf asfj asdjf"};

        SendCommand(
            SCI_M::AddText,
            text.size(),
            reinterpret_cast<sptr_t>(
                static_cast<const char*>(text.data())));

        SendCommand(SCI_M::SetWrapMode, SC_WRAP_WORD);
        SendCommand(SCI_M::StyleSetSize, STYLE_DEFAULT, 16);

        SetFocusState(true);
        CaretSetPeriod(0);
    }

    ImVec2 globalCursor;
    ImVec2 windowCursor;

    void Resize(ImVec2 const& pos, ImVec2 const& size) {
        wMain.SetPosition(PRectangle::FromInts(
            pos.x, pos.y, pos.x + size.x, pos.y + size.y));
    }


    virtual void SetVerticalScrollPos() override {}


    virtual void SetHorizontalScrollPos() override { xOffset = 0; }


    bool ModifyScrollBars(int nMax, int nPage) { return false; }


    virtual void CreateCallTipWindow(PRectangle rc) override {
        if (!ct.wCallTip.Created()) {
            // ct.wCallTip = new CallTip(stc, &ct, this);
            ct.wCallTip = NewWindowImpl();
            ct.wDraw    = &ct.wCallTip;
        }
    }


    virtual void AddToPopUp(
        const char* label,
        int         cmd     = 0,
        bool        enabled = true) override {}


    void ClaimSelection() override {}
    void Copy() override {}
    void Paste() override {}
    void NotifyChange() override {}
    void NotifyParent(SCNotification scn) { (void)scn; }
    void SetMouseCapture(bool on) override { (void)on; }
    bool HaveMouseCapture() override { return false; }

    virtual bool ModifyScrollBars(Sci::Line nMax, Sci::Line nPage)
        override {
        return false;
    }
    virtual void NotifyParent(Scintilla::NotificationData scn) override {}
    virtual void CopyToClipboard(
        const Scintilla::Internal::SelectionText& selectedText) override {}
    virtual std::string UTF8FromEncoded(
        std::string_view encoded) const override {
        abort();
    }
    virtual std::string EncodedFromUTF8(
        std::string_view utf8) const override {
        abort();
    }
    virtual Scintilla::sptr_t DefWndProc(
        Scintilla::Message iMessage,
        Scintilla::uptr_t  wParam,
        Scintilla::sptr_t  lParam) override {
        abort();
    }

    sptr_t SendCommand(
        Scintilla::Message iMessage,
        uptr_t             wParam = 0,
        sptr_t             lParam = 0) {
        return WndProc(iMessage, wParam, lParam);
    }


    std::vector<unsigned int> m_breakpointLines;
};

namespace ImGui {

ScEditor* ScInputText(const char* label, const ImVec2& size) {
    auto frameless_vars = push_frameless_window_vars();

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
    // if (size.x != 0 && size.y != 0) {
    //     render_debug_rect(size, 0, IM_COL32(255, 0, 0, 255));
    // }

    ImGui::BeginChild(
        fmt("##{}_container", label).c_str(),
        size,
        false,
        ImGuiWindowFlags_NoScrollbar);


    if (size.x == 0 || size.y == 0) {
        ImVec2 available = ImGui::GetContentRegionAvail();
        editor->Resize(ImVec2{0, 0}, available);
    } else {
        editor->Resize(ImVec2{0, 0}, size);
    }

    ImGui::EndChild();
    ImGui::PopStyleVar(frameless_vars);
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
                LOG(INFO) << fmt(
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
            LOG(INFO) << fmt("Creating font for parameters {}", font->fp);
            auto font_path = get_fontconfig_path(font->fp.faceName);
            LOGIC_ASSERTION_CHECK(
                font_path.has_value(),
                "Could not find font path for '{}'",
                font->fp.faceName);
            LOG(INFO) << fmt("Using font file {}", *font_path);

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
            LOG(INFO) << fmt("Added font for {}", font->fp);
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
        } else {
            return fp.size;
        }
    }

    int GetTextWidth(std::string_view const& text) const {
        if (metrics) {
            return metrics->GetTextWidth(text);
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
            if (action.hadEvents) { LOG(INFO) << fmt1(action); }

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


// template <>
// struct std::formatter<Scintilla::Internal::FontParameters>
//     : std::formatter<std::string> {
//     template <typename FormatContext>
//     FormatContext::iterator format(
//         Scintilla::Internal::FontParameters const& p,
//         FormatContext&                             ctx) const {
//         bool first = true;
//         fmt_ctx("{", ctx);
//         for_each_field_value_with_bases(
//             p, [&](char const* name, auto const& value) {
//                 if (!first) { fmt_ctx(", ", ctx); }
//                 fmt_ctx(".", ctx);
//                 fmt_ctx(name, ctx);
//                 fmt_ctx(" = ", ctx);
//                 fmt_ctx(value, ctx);
//                 first = false;
//             });
//         return fmt_ctx("}", ctx);
//     }
// };


class SurfaceImpl : public Scintilla::Internal::Surface {
  public:
    SurfaceImpl() {}
    virtual ~SurfaceImpl() {}

    ImVec2 pos;

    ImDrawList*       DrawList() { return ImGui::GetWindowDrawList(); }
    ImVec2            GetPos() { return pos; }
    ImFontWrap const* GetFont(Font const* f) {
        return dynamic_cast<ImFontWrap const*>(f);
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

    virtual void SetClip(PRectangle rc) override  { }
    virtual void PopClip() override  { }
    virtual void FlushCachedState() override  { }
    virtual void FlushDrawing() override  { }
    // clang-format on

    virtual void FillRectangle(PRectangle rc, Surface& surfacePattern)
        override {
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
WindowImpl* window(WindowID wid) { return static_cast<WindowImpl*>(wid); }
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
