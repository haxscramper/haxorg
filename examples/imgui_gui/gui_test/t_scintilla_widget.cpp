#include "im_test_common.hpp"
#include <gui_lib/scintilla_editor_widget.hpp>

#define TEST_GRP_NAME "scintilla"

struct SciVars : public ImTestVarsBase {};


namespace {

ImGuiTest* _init(ImGuiTestEngine* e, char const* name) {
    ImGuiTest* t = IM_REGISTER_TEST(e, TEST_GRP_NAME, name);
    t->SetVarsDataType<SciVars>();
    return t;
}

void _Create_Editor(ImGuiTestEngine* e) {
    auto t = _init(e, "Create editor");

    t->GuiFunc = ImWrapGuiFuncT<SciVars>(
        [](ImGuiTestContext* ctx, SciVars& vars) {
            auto ed  = ImGui::ScInputText("editor");
            auto act = ed->HandleInput();
            ed->Render();
            ;
        });
}

void _Edit_SingleLineText(ImGuiTestEngine* e) {
    auto t     = _init(e, "Edit single line");
    t->GuiFunc = ImWrapGuiFuncT<SciVars>(
        [](ImGuiTestContext* ctx, SciVars& vars) {
            auto ed = ImGui::ScInputText("editor");
            if (ctx->IsFirstGuiFrame()) { ed->AddText("oneline"); }
            auto act = ed->HandleInput();
            ed->Render();
        });

    t->TestFunc = ImWrapTestFuncT<SciVars>(
        [](ImGuiTestContext* ctx, SciVars& vars) {
            auto ed = ImGui::ScInputText("editor");
            IM_CHECK_EQ(ed->GetText(), "oneline");
            auto wpos = getContentPos(ctx);
            ctx->MouseMoveToPos(wpos + ImVec2{10, 10});
            ctx->SuspendTestFunc();
        });
}
} // namespace

void RegisterApptests_scintilla_editor(ImGuiTestEngine* e) {
    _Create_Editor(e);
    _Edit_SingleLineText(e);
}
