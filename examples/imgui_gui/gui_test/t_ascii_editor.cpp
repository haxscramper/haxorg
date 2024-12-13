#include "im_test_common.hpp"
#include <gui_lib/ascii_editor.hpp>

#define TEST_GROUP "ascii_editor"

IM_FMT_DECL(Vec2i);

struct SceneVars {
    Scene scene;
    bool  setup;
};


void RegisterApptests_ascii_editor(ImGuiTestEngine* e) {
    {
        ImGuiTest* t = IM_REGISTER_TEST(
            e, TEST_GROUP, "Drag rectangle diagonally");
        t->SetVarsDataType<SceneVars>();
        t->GuiFunc = [](ImGuiTestContext* ctx) {
            ImGui::SetNextWindowSize(ImVec2{250, 250});
            ImGui::Begin(
                "Test Window", NULL, ImGuiWindowFlags_NoSavedSettings);
            DisplayBuffer buf;
            SceneVars&    vars = ctx->GetVars<SceneVars>();

            Scene& scene = vars.scene;
            if (!vars.setup) {
                scene.stack.layers.push_back(Layer{});

                auto& l0 = scene.stack.layers.at(0);
                l0.add(Shape{
                    .position = Vec2i{1, 1},
                    .data     = Shape::Rectangle{.size = Vec2i{10, 10}}});

                ImGui::LogText("Scene initialization done");
                vars.setup = true;
            }


            scene.render(buf);
            ImVec2 window_pos = ImGui::GetWindowPos();
            scene.im_draw(window_pos, ImGui::GetFont(), buf);
            ImGui::End();
        };

        t->TestFunc = [](ImGuiTestContext* ctx) {
            SceneVars& vars  = ctx->GetVars<SceneVars>();
            Scene&     scene = vars.scene;
            auto       shape = ShapeOrigin{.stack = 0, .index = 0};

            IM_CHECK_EQ(scene.at(shape).position, (Vec2i{1, 1}));

            ctx->SetRef("Test Window");
            auto win_info = ctx->GetWindowByRef(ctx->GetRef());
            ctx->MouseMoveToPos(win_info->Pos + ImVec2{35, 35});
            ctx->MouseDragWithDelta(ImVec2{25, 25});
            ctx->Yield(2);
            IM_CHECK_EQ(scene.at(shape).position, (Vec2i{2, 2}));
        };
    }
}
