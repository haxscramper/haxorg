#include "im_test_common.hpp"
#include <gui_lib/story_grid.hpp>

#define TEST_GROUP "story_grid"

struct StoryGridVars : public ImTestVarsBase {
    StoryGridModel     model;
    org::ImmAstContext start;

    void add_text(std::string const& text) {
        model.history.push_back(StoryGridHistory{
            .ast = start.init(sem::parseString(text)),
        });
        model.updateNeeded.incl(StoryGridModel::UpdateNeeded::Graph);
        model.updateNeeded.incl(StoryGridModel::UpdateNeeded::Scroll);
        TreeGridDocument doc;
        model.updateDocument(doc);
    }
};


void RegisterApptests_story_grid(ImGuiTestEngine* e) {
    {
        ImGuiTest* t = IM_REGISTER_TEST(
            e, TEST_GROUP, "Load one paragraph");
        t->SetVarsDataType<StoryGridVars>();
        ImTestFuncStartupParams params;
        params.windowSize.x = 500;
        t->GuiFunc          = ImWrapGuiFuncT<StoryGridVars>(
            params, [](ImGuiTestContext* ctx, StoryGridVars& vars) {
                if (vars.is_first()) {
                    vars.model.conf.setTraceFile(
                        getDebugFile(ctx->Test, "subtree_init"));

                    vars.trace.setTraceFile("/tmp/im_render_trace");
                    vars.add_text("* One subtree in grid");
                }

                vars.model.shift        = getContentPos(ctx);
                Vec<GridAction> actions = render_story_grid(vars.model);

                if (vars.is_im_traced()) {
                    ImRenderTraceRecord::WriteTrace(vars.trace);
                }
            });

        t->TestFunc = ImWrapTestFuncT<StoryGridVars>(
            params, [](ImGuiTestContext* ctx, StoryGridVars& vars) {
                ImGui::LogToFile(-1, "/tmp/imgui_file_log.txt");
                vars.set_im_trace(3);
                ctx->SuspendTestFunc();
            });
    }
}
