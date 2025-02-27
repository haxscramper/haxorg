#include "im_test_common.hpp"
#include <gui_lib/scintilla_editor_widget.hpp>

#define TEST_GRP_NAME "scintilla"

using namespace hstd;

struct SciVars : public ImTestVarsBase {
    std::string text;
};


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
        });
}

void _Edit_SingleLineText(ImGuiTestEngine* e) {
    auto t     = _init(e, "Edit single line");
    t->GuiFunc = ImWrapGuiFuncT<SciVars>(
        [](ImGuiTestContext* ctx, SciVars& vars) {
            auto ed = ImGui::ScInputText("editor");
            if (ctx->IsFirstGuiFrame()) { ed->AddText("oneline"); }
            auto act = ed->HandleInput();
            if (act.inputChanged) { LOG(INFO) << fmt1(act); }
            ed->Render();
            vars.text = ed->GetText();
        });

    t->TestFunc = ImWrapTestFuncT<SciVars>(
        [](ImGuiTestContext* ctx, SciVars& vars) {
            auto ed = ImGui::ScInputText("editor");
            ctx->Yield(5);
            IM_CHECK_EQ(vars.text, "oneline");
            auto wpos = getContentPos(ctx);
            ctx->MouseMoveToPos(wpos + ImVec2{30, 10});
            ctx->MouseClick(0);
            ctx->Yield(3);
            ctx->KeyChars("y");
            IM_CHECK_EQ(vars.text, "yoneline");
            ctx->MouseMoveToPos(ImGui::GetMousePos() + ImVec2{40, 0});
            ctx->MouseClick(0);
            ctx->Yield(3);
            ctx->KeyChars("z");
            IM_CHECK_EQ(vars.text, "yonzeline");
            ctx->SuspendTestFunc();
        });
}
} // namespace

void RegisterApptests_scintilla_editor(ImGuiTestEngine* e) {
    _Create_Editor(e);
    _Edit_SingleLineText(e);
}
