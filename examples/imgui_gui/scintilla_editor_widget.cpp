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

using AutoSurface = Scintilla::Internal::AutoSurface;


// These are keycodes return by the getKeyPressed function in PDUI

/* Taken from glfw and renamed and slightly
 * These key codes are inspired by the *USB HID Usage Tables v1.12* (p.
 * 53-60), but re-arranged to map to 7-bit ASCII for printable keys
 * (function keys are put in the 256+ range).
 *
 * The naming of the key codes follow these rules:
 *  - The US keyboard layout is used
 *  - Names of printable alpha-numeric characters are used (e.g. "A", "R",
 *    "3", etc.)
 *  - For non-alphanumeric characters, Unicode:ish names are used (e.g.
 *    "COMMA", "LEFT_SQUARE_BRACKET", etc.). Note that some names do not
 *    correspond to the Unicode standard (usually for brevity)
 *  - Keys that lack a clear US mapping are named "WORLD_x"
 *  - For non-printable keys, custom names are used (e.g. "F4",
 *    "BACKSPACE", etc.)
 */

#ifndef PD_KEYS_H_
#    define PD_KEYS_H_

#    define PDKEY_UNKNOWN 0
#    define PDKEY_SPACE 32
#    define PDKEY_APOSTROPHE 39
#    define PDKEY_COMMA 44
#    define PDKEY_MINUS 45
#    define PDKEY_PERIOD 46
#    define PDKEY_SLASH 47
#    define PDKEY_0 48
#    define PDKEY_1 49
#    define PDKEY_2 50
#    define PDKEY_3 51
#    define PDKEY_4 52
#    define PDKEY_5 53
#    define PDKEY_6 54
#    define PDKEY_7 55
#    define PDKEY_8 56
#    define PDKEY_9 57
#    define PDKEY_SEMICOLON 59
#    define PDKEY_EQUAL 61
#    define PDKEY_A 65
#    define PDKEY_B 66
#    define PDKEY_C 67
#    define PDKEY_D 68
#    define PDKEY_E 69
#    define PDKEY_F 70
#    define PDKEY_G 71
#    define PDKEY_H 72
#    define PDKEY_I 73
#    define PDKEY_J 74
#    define PDKEY_K 75
#    define PDKEY_L 76
#    define PDKEY_M 77
#    define PDKEY_N 78
#    define PDKEY_O 79
#    define PDKEY_P 80
#    define PDKEY_Q 81
#    define PDKEY_R 82
#    define PDKEY_S 83
#    define PDKEY_T 84
#    define PDKEY_U 85
#    define PDKEY_V 86
#    define PDKEY_W 87
#    define PDKEY_X 88
#    define PDKEY_Y 89
#    define PDKEY_Z 90
#    define PDKEY_LEFT_BRACKET 91
#    define PDKEY_BACKSLASH 92
#    define PDKEY_RIGHT_BRACKET 93
#    define PDKEY_GRAVE_ACCENT 96

// Function keys

#    define PDKEY_ESCAPE 256
#    define PDKEY_ENTER 257
#    define PDKEY_TAB 258
#    define PDKEY_BACKSPACE 259
#    define PDKEY_INSERT 260
#    define PDKEY_DELETE 261
#    define PDKEY_RIGHT 262
#    define PDKEY_LEFT 263
#    define PDKEY_DOWN 264
#    define PDKEY_UP 265
#    define PDKEY_PAGE_UP 266
#    define PDKEY_PAGE_DOWN 267
#    define PDKEY_HOME 268
#    define PDKEY_END 269
#    define PDKEY_CAPS_LOCK 280
#    define PDKEY_SCROLL_LOCK 281
#    define PDKEY_NUM_LOCK 282
#    define PDKEY_PRINT_SCREEN 283
#    define PDKEY_PAUSE 284
#    define PDKEY_F1 290
#    define PDKEY_F2 291
#    define PDKEY_F3 292
#    define PDKEY_F4 293
#    define PDKEY_F5 294
#    define PDKEY_F6 295
#    define PDKEY_F7 296
#    define PDKEY_F8 297
#    define PDKEY_F9 298
#    define PDKEY_F10 299
#    define PDKEY_F11 300
#    define PDKEY_F12 301
#    define PDKEY_F13 302
#    define PDKEY_F14 303
#    define PDKEY_F15 304
#    define PDKEY_F16 305
#    define PDKEY_F17 306
#    define PDKEY_F18 307
#    define PDKEY_F19 308
#    define PDKEY_F20 309
#    define PDKEY_F21 310
#    define PDKEY_F22 311
#    define PDKEY_F23 312
#    define PDKEY_F24 313
#    define PDKEY_F25 314
#    define PDKEY_KP_0 320
#    define PDKEY_KP_1 321
#    define PDKEY_KP_2 322
#    define PDKEY_KP_3 323
#    define PDKEY_KP_4 324
#    define PDKEY_KP_5 325
#    define PDKEY_KP_6 326
#    define PDKEY_KP_7 327
#    define PDKEY_KP_8 328
#    define PDKEY_KP_9 329
#    define PDKEY_KP_DECIMAL 330
#    define PDKEY_KP_DIVIDE 331
#    define PDKEY_KP_MULTIPLY 332
#    define PDKEY_KP_SUBTRACT 333
#    define PDKEY_KP_ADD 334
#    define PDKEY_KP_ENTER 335
#    define PDKEY_KP_EQUAL 336
#    define PDKEY_LEFT_SHIFT 340
#    define PDKEY_LEFT_CONTROL 341
#    define PDKEY_LEFT_ALT 342
#    define PDKEY_LEFT_SUPER 343
#    define PDKEY_RIGHT_SHIFT 344
#    define PDKEY_RIGHT_CONTROL 345
#    define PDKEY_RIGHT_ALT 346
#    define PDKEY_RIGHT_SUPER 347
#    define PDKEY_MENU 348
#    define PDKEY_MAX 349

#    define PDKEY_SHIFT 1
#    define PDKEY_ALT 2
#    define PDKEY_CTRL 4
#    define PDKEY_SUPER 8

#    define PDWHEEL_AXIS_VERTICAL 0
#    define PDWHEEL_AXIS_HORIZONTAL 1

// TODO: Refactor this?

using PRectangle = Scintilla::Internal::PRectangle;

struct PDMouseWheelEvent {
    float deltaX;
    float deltaY;
    short wheelDelta;
    short rotation;
    int   wheelAxis;
    int   keyFlags;
    int   linesPerRotation;
    int   columnsPerRotation;
};

#endif

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


    void HandleMouseWheel(const PDMouseWheelEvent& wheelEvent) {}


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

using namespace Scintilla::Internal;


ImU32 ToImGui(ColourRGBA const& c) {
    return IM_COL32(c.GetRed(), c.GetGreen(), c.GetBlue(), c.GetAlpha());
}


class SurfaceImpl : public Scintilla::Internal::Surface {
  public:
    SurfaceImpl() {}
    virtual ~SurfaceImpl() {}

    ImDrawList* DrawList();
    ImVec2      GetPos();

    void FillRectangle(PRectangle rc, ColourRGBA color) {
        DrawList()->AddDrawCmd();
        DrawList()->AddRectFilled(
            ImVec2(rc.left + GetPos().x, rc.top + GetPos().y),
            ImVec2(rc.right + GetPos().x, rc.bottom + GetPos().y),
            ToImGui(color));
    }


    // clang-format off
    virtual void Init(WindowID wid) override {  }
    virtual void Init(SurfaceID sid, WindowID wid) override { }
    virtual std::unique_ptr<Surface> AllocatePixMap(int width, int height) override {  logic_todo_impl(); }

    virtual void SetMode(SurfaceMode mode) override {  logic_todo_impl(); }
    virtual void Release() noexcept override  { }
    virtual int SupportsFeature(Scintilla::Supports feature) noexcept override  { }
    virtual bool Initialised() override  { return true; }
    virtual int LogPixelsY() override  {  logic_todo_impl(); }
    virtual int PixelDivisions() override  {  logic_todo_impl(); }
    virtual int DeviceHeightFont(int points) override  {  logic_todo_impl(); }
    virtual void LineDraw(Point start, Point end, Stroke stroke) override  {  logic_todo_impl(); }
    virtual void PolyLine(const Point *pts, size_t npts, Stroke stroke) override  {  logic_todo_impl(); }
    virtual void Polygon(const Point *pts, size_t npts, FillStroke fillStroke) override  {  logic_todo_impl(); }
    virtual void RectangleDraw(PRectangle rc, FillStroke fillStroke) override  {  logic_todo_impl(); }
    virtual void RectangleFrame(PRectangle rc, Stroke stroke) override  {  logic_todo_impl(); }
    virtual void FillRectangle(PRectangle rc, Fill fill) override  {  logic_todo_impl(); }
    virtual void FillRectangleAligned(PRectangle rc, Fill fill) override  {  logic_todo_impl(); }
    virtual void FillRectangle(PRectangle rc, Surface &surfacePattern) override  {  logic_todo_impl(); }
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
    virtual XYPOSITION WidthText(const Font *font_, std::string_view text) override { logic_todo_impl(); }

    virtual void DrawTextNoClipUTF8(PRectangle rc, const Font *font_, XYPOSITION ybase, std::string_view text, ColourRGBA fore, ColourRGBA back) override { logic_todo_impl(); }
    virtual void DrawTextClippedUTF8(PRectangle rc, const Font *font_, XYPOSITION ybase, std::string_view text, ColourRGBA fore, ColourRGBA back) override { logic_todo_impl(); }
    virtual void DrawTextTransparentUTF8(PRectangle rc, const Font *font_, XYPOSITION ybase, std::string_view text, ColourRGBA fore) override { logic_todo_impl(); }
    virtual void MeasureWidthsUTF8(const Font *font_, std::string_view text, XYPOSITION *positions) override { logic_todo_impl(); }
    virtual XYPOSITION WidthTextUTF8(const Font *font_, std::string_view text) override { logic_todo_impl(); }

    virtual XYPOSITION Ascent(const Font *font_) override  {  logic_todo_impl(); }
    virtual XYPOSITION Descent(const Font *font_) override  {  logic_todo_impl(); }
    virtual XYPOSITION InternalLeading(const Font *font_) override  {  logic_todo_impl(); }
    virtual XYPOSITION Height(const Font *font_) override  {  logic_todo_impl(); }
    virtual XYPOSITION AverageCharWidth(const Font *font_) override  {  logic_todo_impl(); }

    virtual void SetClip(PRectangle rc) override  {  logic_todo_impl(); }
    virtual void PopClip() override  {  logic_todo_impl(); }
    virtual void FlushCachedState() override  {  logic_todo_impl(); }
    virtual void FlushDrawing() override  {  logic_todo_impl(); }
    // clang-format on

  private:
    ColourRGBA m_penColour;
};


std::unique_ptr<Scintilla::Internal::Surface> Scintilla::Internal::
    Surface::Allocate(Scintilla::Technology technology) {
    return std::make_unique<SurfaceImpl>();
}
