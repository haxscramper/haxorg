#pragma once

#include <hstd/ext/logger.hpp>
#include "imgui_internal.h"
#include <GLFW/glfw3.h>
#include <hstd/stdlib/Str.hpp>
#include <hstd/stdlib/Vec.hpp>
#include <imgui.h>
#include <ScintillaMessages.h>

#include <map>
#include <set>

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
void run_scintilla_editor_widget_test(GLFWwindow* window);

struct SciWindowImpl {
    ImGuiWindow*                    im;
    Scintilla::Internal::PRectangle frame{};
};

struct ScEditor : public Scintilla::Internal::ScintillaBase {
    using SCI_M = Scintilla::Message;

    hstd::log::log_builder message(
        ::hstd::log::severity_level level,
        hstd::Str const&            msg,
        int                         line     = __builtin_LINE(),
        char const*                 function = __builtin_FUNCTION(),
        char const*                 file     = __builtin_FILE());

    void SetDefaultFont(std::string const& family);

    void AddText(std::string const& text);
    void SetText(std::string const& text);
    void WrapOnWord() { SendCommand(SCI_M::SetWrapMode, SC_WRAP_WORD); }
    void WrapOnChar() { SendCommand(SCI_M::SetWrapMode, SC_WRAP_CHAR); }
    void SetMarginWidth(int margin, int pixelWidth) {
        SendCommand(SCI_M::SetMarginWidthN, margin, pixelWidth);
    }

    int  GetPosition() { return SendCommand(SCI_M::GetCurrentPos); }
    int  GetMarginCount() { return SendCommand(SCI_M::GetMargins); }
    void HideAllMargins() {
        for (int i = 0; i < GetMarginCount(); ++i) {
            SetMarginWidth(i, 0);
        }
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


    int GetWordEndPosition(int position, bool onlyWordCharacters);


    char* GetTextRange(int startPosition, int endPosition);


    char* GetWordFromPosition(int position, int& start, int& end);


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

    InputResult HandleInput();


    void Render();

    static SciWindowImpl* NewWindowImpl() {
        auto windowImpl = new SciWindowImpl{};
        windowImpl->im  = ImGui::GetCurrentWindow();
        return windowImpl;
    }

    void Initialise() override;

    ImVec2 globalCursor;
    ImVec2 windowCursor;

    void Resize(ImVec2 const& size);


    virtual void SetVerticalScrollPos() override {}


    virtual void SetHorizontalScrollPos() override { xOffset = 0; }


    bool ModifyScrollBars(int nMax, int nPage) { return false; }


    virtual void CreateCallTipWindow(
        Scintilla::Internal::PRectangle rc) override;


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
    const char*   label,
    ImVec2 const& size = ImVec2{0, 0});
}
