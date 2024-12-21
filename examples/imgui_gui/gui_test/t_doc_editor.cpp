#define NDEBUG 0

#include "im_test_common.hpp"
#include <gui_lib/doc_editor.hpp>
#include <haxorg/sem/ImmOrgBase.hpp>
#include <haxorg/sem/SemBaseApi.hpp>
#include <haxorg/sem/SemOrgFormat.hpp>


struct DocEditVars : public ImTestVarsBase {
    org::ImmAstContext::Ptr ctx;
    DocBlockModel           model;
    EditableOrgDocGroup     docs;
    DocBlockConfig          conf;
    DocRootId               root_idx = DocRootId::Nil();

    DocEditVars()
        : ctx{org::ImmAstContext::init_start_context()}, docs{ctx} {}

    Str get_text() {
        auto sem = org::sem_from_immer(
            docs.getCurrentRoot(root_idx).id,
            *docs.getCurrentAst().context);
        return sem::Formatter::format(sem);
    }

    void add_text(std::string const& text) {
        root_idx = docs.initRoot(sem::parseString(text));
        model.syncFull(docs.getCurrentRoot(root_idx), conf);
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
            vars.model.root->treeRepr(os);
            writeFile(
                getDebugFile(ctx->Test, "doc_repr.txt"),
                os.getBuffer().toString(false));

            IM_CHECK(r->isDocument());
            IM_CHECK(r->at(0)->isSubtree());
            IM_CHECK(r->at({0, 0})->isParagraph());

            auto st  = r->at(0);
            auto par = r->at({0, 0});

            { // when document block is being edited, its size can change.
              // Positions of other blocks should account for that.
                ImVec2 par_pos0  = par->getPos();
                ImVec2 par_size0 = par->getSize();
                ImVec2 st_pos0   = st->getPos();
                ImVec2 st_size0  = st->getSize();
                ctx->MouseMoveToPos(wpos + st_pos0);
                MouseMoveRelative(ctx, ImVec2{10, 10});
                ctx->MouseClick(0);

                IM_CHECK_NE(st_size0, st->getSize());
                IM_CHECK_EQ(st_pos0, st->getPos());

                IM_CHECK_EQ(par_size0, par->getSize());
                IM_CHECK_NE(par_pos0, par->getPos());

                ctx->MouseMoveToPos(
                    wpos + st_pos0 + ImVec2{10, st->getSize().y - 15});
                ctx->MouseClick(0);

                IM_CHECK_EQ(st_size0, st->getSize());
                IM_CHECK_EQ(st_pos0, st->getPos());

                IM_CHECK_EQ(par_size0, par->getSize());
                IM_CHECK_EQ(par_pos0, par->getPos());
            }

            {

                ctx->MouseMoveToPos(wpos + st->getPos());
                MouseMoveRelative(ctx, ImVec2{10, 10});
                ctx->MouseClick(0);
                ctx->MouseClick(0);
                ctx->KeyChars("Title add ");
                ctx->MouseMoveToPos(
                    wpos + st->getPos()
                    + ImVec2{10, st->getSize().y - 15});
                ctx->MouseClick(0);
            }

            ctx->SuspendTestFunc();
        });
}

} // namespace

void RegisterApptests_doc_edit(ImGuiTestEngine* e) {
    _SimpleDocumentEdit(e);
}
