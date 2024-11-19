#include <algorithm>
#include <assert.h>
#include <cstring>
#include <map>
#include <stddef.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <set>

#include "scintilla_editor_widget.hpp"
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

#include <stb/stb_truetype.h>

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
            fmt("[({}, {})+({}, {})]", p.left, p.top, p.right, p.bottom),
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
    WindowImpl() { show = false; }

    PRectangle position;
    bool       show;
};


WindowImpl* AllocateWindowImpl() { return new WindowImpl; }

struct ScEditor : public Scintilla::Internal::ScintillaBase {
  private:
    int width;
    int height;
    int wheelVRotation;
    int wheelHRotation;

  public:
    ScEditor()
        : width(0), height(0), wheelVRotation(0), wheelHRotation(0) {}

    virtual ~ScEditor() {}


    void Update() {}

    void ScrollTo(Sci::Line line, bool moveThumb = true) {
        Scintilla::Internal::ScintillaBase::ScrollTo(line, moveThumb);
    }

    void ToggleBreakpoint() {}


    bool IsComment(int position) {
        sptr_t style = SendCommand(
            Scintilla::Message::GetStyleAt, (uptr_t)position);

        return style == 2;
    }


    int GetWordStartPosition(int position, bool onlyWordCharacters) {
        return (int)SendCommand(
            Scintilla::Message::WordStartPosition,
            (uptr_t)position,
            (sptr_t)onlyWordCharacters);
    }


    int GetWordEndPosition(int position, bool onlyWordCharacters) {
        return (int)SendCommand(
            Scintilla::Message::WordEndPosition,
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

        SendCommand(
            Scintilla::Message::GetTextRange, 0, sptr_t(&textRange));
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


    void HandleInput() {}


    void Render() {
        PRectangle rcPaint = GetClientRectangle();

        AutoSurface surfaceWindow{this};
        if (surfaceWindow) {
            Paint(surfaceWindow, rcPaint);
            surfaceWindow->Release();
        }
    }


    void Initialise() override {
        wMain = AllocateWindowImpl();


        ImGuiIO& io = ImGui::GetIO();
        wMain.SetPosition(PRectangle::FromInts(
            0, 0, int(io.DisplaySize.x), int(io.DisplaySize.y)));

        // We need to disable buffered draw so Scintilla doesn't keep a
        // yoffset of 0 when rendering text, thinking we are blitting
        // through a pixmap. We want a single draw list for efficiency.
        view.bufferedDraw = false;

        std::string text{"asfasdfasdf"};

        SendCommand(
            Scintilla::Message::AddText,
            text.size(),
            reinterpret_cast<sptr_t>(
                static_cast<const char*>(text.data())));

        SetFocusState(true);
        CaretSetPeriod(0);
    }


    void Resize(int x, int y, int width, int height) {
        this->width  = width;
        this->height = height;
        wMain.SetPosition(PRectangle::FromInts(0, 0, width, height));
    }


    virtual void SetVerticalScrollPos() override {}


    virtual void SetHorizontalScrollPos() override { xOffset = 0; }


    bool ModifyScrollBars(int nMax, int nPage) { return false; }


    virtual void CreateCallTipWindow(PRectangle rc) override {
        if (!ct.wCallTip.Created()) {
            // ct.wCallTip = new CallTip(stc, &ct, this);
            ct.wCallTip = AllocateWindowImpl();
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

ScEditor* ScInputText(
    const char* label,
    float       xSize,
    float       ySize,
    void (*callback)(void*),
    void* userData) {
    ImGuiWindow*  window = GetCurrentWindow();
    const ImGuiID id     = window->GetID(label);

    ImGuiStorage* storage = GetStateStorage();
    ScEditor*     editor  = (ScEditor*)storage->GetVoidPtr(id);

    if (!editor) {
        editor = new ScEditor();
        editor->Initialise();
        storage->SetVoidPtr(id, (void*)editor);
    }

    float textSize = 26;

    editor->Resize(0, 0, (int)window->Size.x - 20, (int)window->Size.y);

    int lineCount = editor->SendCommand(
        Scintilla::Message::GetLineCount, 0, 0);

    ImGuiListClipper clipper{};
    clipper.ItemsCount  = lineCount;
    clipper.ItemsHeight = textSize;

    editor->ScrollTo(clipper.DisplayStart);
    clipper.End();
    return editor;
}

} // namespace ImGui

void run_scintilla_editor_widget_test(GLFWwindow* window) {
    while (!glfwWindowShouldClose(window)) {
        frame_start();
        fullscreen_window_begin();
        {
            auto ed = ImGui::ScInputText(
                "editor", 200, 200, nullptr, nullptr);

            ed->Render();
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
    SurfaceImpl() {}
    virtual ~SurfaceImpl() {}

    ImDrawList* DrawList() { return ImGui::GetWindowDrawList(); }
    ImVec2      GetPos() { return ImVec2{}; }

    void FillRectangle(PRectangle rc, ColourRGBA color) {}


    // clang-format off
    virtual void Init(WindowID wid) override {  }
    virtual void Init(SurfaceID sid, WindowID wid) override { }
    virtual void SetMode(SurfaceMode mode) override { }

    virtual void Release() noexcept override  { }
    virtual int SupportsFeature(Scintilla::Supports feature) noexcept override  { return false; }
    virtual bool Initialised() override  { return true; }
    virtual int LogPixelsY() override  { return 72; }
    virtual int PixelDivisions() override  {  logic_todo_impl(); }

    virtual void LineDraw(Point start, Point end, Stroke stroke) override  {  logic_todo_impl(); }
    virtual void PolyLine(const Point *pts, size_t npts, Stroke stroke) override  {  logic_todo_impl(); }
    virtual void Polygon(const Point *pts, size_t npts, FillStroke fillStroke) override  {  logic_todo_impl(); }
    virtual void RectangleDraw(PRectangle rc, FillStroke fillStroke) override  {  logic_todo_impl(); }
    virtual void RectangleFrame(PRectangle rc, Stroke stroke) override  {  logic_todo_impl(); }


    virtual void RoundedRectangle(PRectangle rc, FillStroke fillStroke) override  {  logic_todo_impl(); }
    virtual void AlphaRectangle(PRectangle rc, XYPOSITION cornerSize, FillStroke fillStroke) override  {  logic_todo_impl(); }
    virtual void GradientRectangle(PRectangle rc, const std::vector<ColourStop> &stops, GradientOptions options) override  {  logic_todo_impl(); }
    virtual void DrawRGBAImage(PRectangle rc, int width, int height, const unsigned char *pixelsImage) override {}
    virtual void Ellipse(PRectangle rc, FillStroke fillStroke) override  {  logic_todo_impl(); }
    virtual void Stadium(PRectangle rc, FillStroke fillStroke, Ends ends) override  {  logic_todo_impl(); }
    virtual void Copy(PRectangle rc, Point from, Surface &surfaceSource) override  {  logic_todo_impl(); }

    virtual std::unique_ptr<IScreenLineLayout> Layout(const IScreenLine *screenLine) override { logic_todo_impl(); }

    virtual void DrawTextNoClip(PRectangle rc, const Font *font_, XYPOSITION ybase, std::string_view text, ColourRGBA fore, ColourRGBA back) override { logic_todo_impl(); }
    virtual void DrawTextClipped(PRectangle rc, const Font *font_, XYPOSITION ybase, std::string_view text, ColourRGBA fore, ColourRGBA back) override { logic_todo_impl(); }
    virtual void DrawTextTransparent(PRectangle rc, const Font *font_, XYPOSITION ybase, std::string_view text, ColourRGBA fore) override { logic_todo_impl(); }
    virtual void MeasureWidths(const Font *font_, std::string_view text, XYPOSITION *positions) override { logic_todo_impl(); }

    virtual void DrawTextNoClipUTF8(PRectangle rc, const Font *font_, XYPOSITION ybase, std::string_view text, ColourRGBA fore, ColourRGBA back) override { logic_todo_impl(); }
    virtual void DrawTextClippedUTF8(PRectangle rc, const Font *font_, XYPOSITION ybase, std::string_view text, ColourRGBA fore, ColourRGBA back) override { logic_todo_impl(); }
    virtual void DrawTextTransparentUTF8(PRectangle rc, const Font *font_, XYPOSITION ybase, std::string_view text, ColourRGBA fore) override { logic_todo_impl(); }
    virtual void MeasureWidthsUTF8(const Font *font_, std::string_view text, XYPOSITION *positions) override { logic_todo_impl(); }
    virtual XYPOSITION WidthTextUTF8(const Font *font_, std::string_view text) override { logic_todo_impl(); }


    virtual XYPOSITION InternalLeading(const Font *font_) override  { return 0; }
    virtual XYPOSITION Height(const Font *font_) override  {  logic_todo_impl(); }

    virtual void SetClip(PRectangle rc) override  { }
    virtual void PopClip() override  { }
    virtual void FlushCachedState() override  { }
    virtual void FlushDrawing() override  { }
    // clang-format on

    virtual void FillRectangle(PRectangle rc, Surface& surfacePattern)
        override {
        _dfmt(rc);
        DrawList()->AddDrawCmd();
        DrawList()->AddRectFilled(
            ImVec2(rc.left + GetPos().x, rc.top + GetPos().y),
            ImVec2(rc.right + GetPos().x, rc.bottom + GetPos().y),
            ToImGui(pen));
    }

    virtual void FillRectangle(PRectangle rc, Fill fill) override {
        _dfmt(rc);
        DrawList()->AddDrawCmd();
        DrawList()->AddRectFilled(
            ImVec2(rc.left + GetPos().x, rc.top + GetPos().y),
            ImVec2(rc.right + GetPos().x, rc.bottom + GetPos().y),
            ToImGui(fill.colour));
    }

    virtual void FillRectangleAligned(PRectangle rc, Fill fill) override {
        _dfmt(rc);
        FillRectangle(rc, fill);
    }

    virtual std::unique_ptr<Surface> AllocatePixMap(int width, int height)
        override {
        return std::make_unique<SurfaceImpl>();
    }

    virtual int DeviceHeightFont(int points) override {
        _dfmt(points);
        int logPix = LogPixelsY();
        return (int)((points * logPix + logPix / 2) / 72.0f);
    }

    // TODO
    virtual XYPOSITION AverageCharWidth(const Font* font_) override {
        return 16;
    }
    virtual XYPOSITION Ascent(const Font* font_) override { return 16; }
    virtual XYPOSITION Descent(const Font* font_) override { return 16; }
    virtual XYPOSITION WidthText(const Font* font_, std::string_view text)
        override {
        _dfmt(text);
        return text.size() * 16;
    }

  private:
    ColourRGBA pen;
};

PRectangle Window::GetPosition() const {
    LOG(INFO) << "----";
    return PRectangle{};
}


std::unique_ptr<Scintilla::Internal::Surface> Scintilla::Internal::
    Surface::Allocate(Scintilla::Technology technology) {
    return std::make_unique<SurfaceImpl>();
}
