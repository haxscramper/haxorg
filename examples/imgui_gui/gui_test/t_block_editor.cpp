#include "im_test_common.hpp"
#include <gui_lib/doc_editor.hpp>
#include <haxorg/sem/ImmOrgBase.hpp>
#include <haxorg/sem/SemBaseApi.hpp>
#include <haxorg/sem/SemOrgFormat.hpp>

struct DocEditVars : public ImTestVarsBase {
    DocBlockModel       model;
    org::ImmAstContext  start;
    EditableOrgDocGroup docs;
    DocBlockConfig      conf;

    void add_text(std::string const& text) {
        int root_idx = docs.init_root(sem::parseString(text));
        model.root   = to_doc_block(docs.getCurrentRoot(root_idx));
    }

    void init_section(ImGuiTestContext* ctx, std::string const& text) {
        if (ctx->IsFirstGuiFrame()) { add_text(text); }
    }

    void run_app_loop_iteration(ImGuiTestContext* ctx) {
        conf.pos = getContentPos(ctx);
    }
};

namespace {
ImGuiTest* _init(ImGuiTestEngine* e, char const* name) {
    ImGuiTest* t = IM_REGISTER_TEST(e, "doc_edit", name);
    t->SetVarsDataType<DocEditVars>();
    return t;
}

void _SimpleDocumentEdit(ImGuiTestEngine* e) {
    auto t = _init(e, "Simple document edit");

    ImTestFuncStartupParams params;
    params.windowSize.x = 700;
    params.windowSize.y = 700;

    t->GuiFunc = ImWrapGuiFuncT<DocEditVars>(
        params, [](ImGuiTestContext* ctx, DocEditVars& vars) {
            if (ctx->IsFirstGuiFrame()) {
                vars.init_section(ctx, R"(
* Subtree

Paragraph 1

Paragraph 2
)");
            }

            vars.run_app_loop_iteration(ctx);
        });

    t->TestFunc = ImWrapTestFuncT<DocEditVars>(
        params, [](ImGuiTestContext* ctx, DocEditVars& vars) {
            ctx->SuspendTestFunc();
        });
}

} // namespace

void RegisterApptests_doc_edit(ImGuiTestEngine* e) {
    _SimpleDocumentEdit(e);
}
