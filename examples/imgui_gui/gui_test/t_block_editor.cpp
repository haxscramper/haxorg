#define NDEBUG 0

#include "im_test_common.hpp"
#include <gui_lib/doc_editor.hpp>
#include <haxorg/sem/ImmOrgBase.hpp>
#include <haxorg/sem/SemBaseApi.hpp>
#include <haxorg/sem/SemOrgFormat.hpp>


struct DocEditVars : public ImTestVarsBase {
    DocBlockModel       model;
    EditableOrgDocGroup docs;
    DocBlockConfig      conf;

    void add_text(std::string const& text) {
        int root_idx = docs.init_root(sem::parseString(text));
        model.root   = to_doc_block(docs.getCurrentRoot(root_idx), conf)
                         .value();
    }

    void init_section(ImGuiTestContext* ctx, std::string const& text) {
        if (ctx->IsFirstGuiFrame()) {
            trace.setTraceFile(
                getDebugFile(ctx->Test, "imgui_render.log"));

            model.ctx.setTraceFile(
                getDebugFile(ctx->Test, "block_editor.log"));

            add_text(text);
        }
    }

    void run_app_loop_iteration(ImGuiTestContext* ctx) {
        {
            auto __scope = IM_SCOPE_BEGIN("App loop iteration", "");
            conf.pos     = getContentPos(ctx);
            render_doc_block(model, conf);
            apply_doc_block_actions(docs, model, conf);
        }
        if (is_im_traced()) { ImRenderTraceRecord::WriteTrace(trace); }
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
            vars.set_im_trace(1);
            ctx->SuspendTestFunc();
        });
}

} // namespace

void RegisterApptests_doc_edit(ImGuiTestEngine* e) {
    _SimpleDocumentEdit(e);
}
