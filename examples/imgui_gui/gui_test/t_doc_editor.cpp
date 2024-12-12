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
        int root_idx    = docs.init_root(sem::parseString(text));
        model.root.root = to_doc_block(docs.getCurrentRoot(root_idx), conf)
                              .value();

        model.root.syncPositions(model.ctx, conf);
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
        params, [params](ImGuiTestContext* ctx, DocEditVars& vars) {
            if (ctx->IsFirstGuiFrame()) {
                vars.conf.gridViewport = params.windowSize;
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

            auto wpos = getContentPos(ctx);

            auto r = vars.model.root;

            ColStream os;
            vars.model.root.root->treeRepr(os);
            writeFile(
                getDebugFile(ctx->Test, "doc_repr.txt"),
                os.getBuffer().toString(false));

            IM_CHECK(r.root->isDocument());
            IM_CHECK(r.at(0)->isSubtree());
            IM_CHECK(r.at({0, 0})->isParagraph());

            auto st  = r.at(0);
            auto par = r.at({0, 0});

            {
                ImVec2 par_pos0  = par->getPos();
                ImVec2 par_size0 = par->getSize();
                ImVec2 st_pos0   = st->getPos();
                ImVec2 st_size0  = st->getSize();
                ctx->MouseMoveToPos(wpos + st_pos0);
                MouseMoveRelative(ctx, ImVec2{10, 0});
                ctx->SuspendTestFunc();
                ctx->MouseClick(0);

                IM_CHECK_NE(st_size0, st->getSize());
                IM_CHECK_EQ(st_pos0, st->getPos());

                IM_CHECK_NE(par_size0, par->getSize());
                IM_CHECK_NE(par_pos0, par->getPos());
            }


            ctx->SuspendTestFunc();
        });
}

} // namespace

void RegisterApptests_doc_edit(ImGuiTestEngine* e) {
    _SimpleDocumentEdit(e);
}
