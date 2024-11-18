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
#include <scintilla/src/Debugging.h>
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

using AutoSurface = Scintilla::Internal::AutoSurface;

static const char* breakpoint_xpm[] = {
    "16 16 72 1",       "   c None",        ".	c #772B1A",
    "+	c #903B2D",     "@	c #F17A78", "#	c #C65C55",
    "$	c #F17876",     "%	c #FF7E7E", "&	c #FF7B7B",
    "*	c #C65750",     "=	c #8F3A2C", "-	c #EF7573",
    ";	c #FD7B7B",     ">	c #FD7878", ",	c #FD7575",
    "'	c #FD7272",     ")	c #C5524B", "!	c #8E392C",
    "~	c #E7716F",     "{	c #F47676", "]	c #F47373",
    "^	c #F47070",     "/	c #F46D6D", "(	c #F46A6A",
    "_	c #F46767",     ":	c #C04C45", "<	c #8B382A",
    "[	c #DB6B69",     "}	c #E77070", "|	c #E76D6D",
    "1	c #E76A6A",     "2	c #E76868", "3	c #E76565",
    "4	c #E76161",     "5	c #E75F5F", "6	c #E75D5D",
    "7	c #B8453E",     "8	c #8D392B", "9	c #DB6867",
    "0	c #E56C6C",     "a	c #E56A6A", "b	c #E56767",
    "c	c #E56363",     "d	c #E56161", "e	c #E55E5E",
    "f	c #E55C5C",     "g	c #E55959", "h	c #B8443D",
    "i	c #8A3729",     "j	c #CD5D5B", "k	c #D66060",
    "l	c #D65E5E",     "m	c #D65A5A", "n	c #D65858",
    "o	c #D65656",     "p	c #D65353", "q	c #AF413A",
    "r	c #863326",     "s	c #BB514F", "t	c #C25252",
    "u	c #C25050",     "v	c #C24E4E", "w	c #C24C4C",
    "x	c #A33C36",     "y	c #813023", "z	c #A54241",
    "A	c #AA4444",     "B	c #AA4242", "C	c #953730",
    "D	c #7B2D1F",     "E	c #893432", "F	c #822F28",
    "G	c #772B1D",     "       .        ", "      ...       ",
    "     ..+..      ", "    ..+@#..     ", "   ..+$%&*..    ",
    "  ..=-;>,')..   ", " ..!~{]^/(_:..  ", "..<[}|1234567.. ",
    "..890abcdefgh.. ", " ..ijklmnopq..  ", "  ..rstuvwx..   ",
    "   ..yzABC..    ", "    ..DEF..     ", "     ..G..      ",
    "      ...       ", "       .        "};


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


namespace ImGui {

ImScEditor* ScInputText(
    const char* label,
    float       xSize,
    float       ySize,
    void (*callback)(void*),
    void* userData) {
    ImGuiWindow*  window = GetCurrentWindow();
    const ImGuiID id     = window->GetID(label);

    (void)callback;
    (void)userData;

    ImGuiStorage* storage = GetStateStorage();
    ScEditor*     editor  = (ScEditor*)storage->GetVoidPtr(id);

    if (!editor) {
        (void)xSize;
        (void)ySize;
        editor = ScEditor_create((int)xSize, (int)ySize);
        storage->SetVoidPtr(id, (void*)editor);
    }

    ImScEditor* editorInterface = ScEditor_getInterface(editor);

    float textSize = 26;

    ScEditor_resize(
        editor, 0, 0, (int)window->Size.x - 20, (int)window->Size.y);

    int lineCount = (int)editorInterface->SendCommand(
        SCI_GETLINECOUNT, 0, 0);

    editorInterface->HandleInput();

    ImGuiListClipper clipper{};
    clipper.ItemsCount  = lineCount;
    clipper.ItemsHeight = textSize;


    ScEditor_setDrawList(GetWindowDrawList());
    // ScEditor_setFont(GetWindowFont());
    ScEditor_setPos(window->Pos.x, window->Pos.y + 14.0f);

    editorInterface->ScrollTo(clipper.DisplayStart);

    clipper.End();

    return editorInterface;
}

} // namespace ImGui


WindowImpl* AllocateWindowImpl() { return new WindowImpl; }

struct ScEditor : public Scintilla::Internal::ScintillaBase {
  private:
    int m_width;
    int m_height;
    int m_wheelVRotation;
    int m_wheelHRotation;

  public:
    ScEditor()
        : m_width(0)
        , m_height(0)
        , m_wheelVRotation(0)
        , m_wheelHRotation(0) {
        memset(&interface, 0, sizeof(interface));
    }

    virtual ~ScEditor() {}


    void Update() {
        // HandleInput();
        // Tick();
    }


    void ToggleBreakpoint() {}


    bool IsComment(int position) {
        // position = max(0, position - 1);
        sptr_t style = SendCommand(SCI_GETSTYLEAT, (uptr_t)position);

        // TODO: How to map this cleanly?
        return style == 2;
    }


    int GetWordStartPosition(int position, bool onlyWordCharacters) {
        return (int)SendCommand(
            SCI_WORDSTARTPOSITION,
            (uptr_t)position,
            (sptr_t)onlyWordCharacters);
    }


    int GetWordEndPosition(int position, bool onlyWordCharacters) {
        return (int)SendCommand(
            SCI_WORDENDPOSITION,
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

        SendCommand(SCI_GETTEXTRANGE, 0, sptr_t(&textRange));
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

        AutoSurface surfaceWindow(this);
        if (surfaceWindow) {
            Paint(surfaceWindow, rcPaint);
            surfaceWindow->Release();
        }
    }


    void Initialise() override {
        wMain = AllocateWindowImpl();

        // TODO: TEMP! Hook up properly to ImGui
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
        m_width  = width;
        m_height = height;

        (void)x;
        (void)y;

        wMain.SetPosition(PRectangle::FromInts(0, 0, m_width, m_height));
    }


    virtual void SetVerticalScrollPos() override {}


    virtual void SetHorizontalScrollPos() override { xOffset = 0; }


    bool ModifyScrollBars(int nMax, int nPage) {
        (void)nMax;
        (void)nPage;
        return false;
    }


    virtual void CreateCallTipWindow(PRectangle rc) override {
        (void)rc;
        if (!ct.wCallTip.Created()) {
            // ct.wCallTip = new CallTip(stc, &ct, this);
            ct.wCallTip = AllocateWindowImpl();
            ct.wDraw    = ct.wCallTip;
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

    sptr_t SendCommand(
        Scintilla::Message iMessage,
        uptr_t             wParam = 0,
        sptr_t             lParam = 0) {
        return WndProc(iMessage, wParam, lParam);
    }


    std::vector<unsigned int> m_breakpointLines;

    // Interface sent to external code

    ImScEditor interface;
};

ScEditor* ScEditor_create(int width, int height) {
    ScEditor* ed = new ScEditor;

    ed->interface.userData    = 0;
    ed->interface.privateData = ed;

    ed->Initialise();
    ScEditor_resize(ed, 0, 0, width, height);

    return ed;
}

void run_scintilla_editor_widget_test(GLFWwindow* window) {
    while (!glfwWindowShouldClose(window)) {
        frame_start();
        fullscreen_window_begin();
        {}
        ImGui::End();
        frame_end(window);
    }
}
