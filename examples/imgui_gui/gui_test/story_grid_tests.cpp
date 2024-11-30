#include "im_test_common.hpp"
#include <gui_lib/story_grid.hpp>


#define TEST_GRP_NAME "story_grid"

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
            e, TEST_GRP_NAME, "Load one paragraph");
        t->SetVarsDataType<StoryGridVars>();
        ImTestFuncStartupParams params;
        params.windowSize.x = 700;
        params.windowSize.y = 700;
        t->GuiFunc          = ImWrapGuiFuncT<StoryGridVars>(
            params, [](ImGuiTestContext* ctx, StoryGridVars& vars) {
                if (vars.is_first()) {
                    vars.model.conf.setTraceFile(
                        getDebugFile(ctx->Test, "subtree_init"));

                    vars.trace.setTraceFile("/tmp/im_render_trace");
                    vars.add_text(R"(
* One subtree in grid
** Subtree 2
*** Subtree 2 3

- =story_event= :: Event 2
- =story_location= :: Location 2
- =story_note= :: Note 4


** Sub-tad 2
* sub-eq

- =story_event= :: Event 1
- =story_location= :: Location 1
- =story_note= :: Note 2

)");
                }

                vars.model.shift = getContentPos(ctx);
                run_story_grid_annotated_cycle(vars.model);
                apply_story_grid_changes(vars.model, TreeGridDocument{});

                if (vars.is_im_traced()) {
                    ImRenderTraceRecord::WriteTrace(vars.trace);
                }
            });

        t->TestFunc = ImWrapTestFuncT<StoryGridVars>(
            params, [](ImGuiTestContext* ctx, StoryGridVars& vars) {
                // ImGui::LogToFile(-1, "/tmp/imgui_file_log.txt");

                ImVec2 wpos = getContentPos(ctx);
                auto&  doc  = vars.model.rectGraph.nodes.at(0)
                                .getTreeGrid()
                                .node;
                ctx->MouseMoveToPos(
                    wpos + doc.getCellPos(0, "title") + ImVec2{0, 5});
                IM_CHECK_EQ(
                    doc.getExistingCell(0, "title").getValue().value,
                    "One subtree in grid");
                IM_CHECK_EQ(
                    doc.getExistingCell(2, "event").getValue().value,
                    "Event 2");
                IM_CHECK_EQ(
                    doc.getExistingCell(2, "location").getValue().value,
                    "Location 2");
                IM_CHECK_EQ(
                    doc.getExistingCell(2, "note").getValue().value,
                    "Note 4");
                vars.set_im_trace(1);
                ctx->Yield(2);
                ctx->MouseClick(0);
                vars.set_im_trace(1);
                ctx->Yield(2);
                ctx->MouseClick(0);
                ctx->KeyChars("test");
                ctx->MouseMoveToPos(ImGui::GetMousePos() + ImVec2{0, 50});
                ctx->MouseClick(0);
                IM_CHECK_EQ(
                    doc.getExistingCell(0, "title").getValue().value,
                    "testOne subtree in grid");

                ctx->MouseMoveToPos(wpos + doc.getCellPos(0, "title"));
                ctx->MouseMoveToPos(
                    ImGui::GetMousePos()
                    - ImVec2(doc.treeFoldWidth - 10, 0));
                ctx->MouseClick(0);

                ctx->SuspendTestFunc();
            });
    }
}
