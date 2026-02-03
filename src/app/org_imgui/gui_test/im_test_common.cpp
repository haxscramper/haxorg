#include "im_test_common.hpp"
#include "imgui_internal.h"
#include <hstd/stdlib/Filesystem.hpp>

using namespace hstd;

void PrintAllWindows() {
    ImGuiContext& g = *GImGui;
    for (int i = 0; i < g.Windows.Size; i++) {
        ImGuiWindow* window = g.Windows[i];
        HSLOG_INFO(
            "im-test-common",
            "Window Name:\"{}\", ID:{} POS:{} SIZE:{}",
            window->Name,
            window->ID,
            window->Pos,
            window->Size);
    }
}

ImGuiWindow* GetWindowByName(std::string const& name) {
    ImGuiContext& g = *GImGui;
    for (int i = 0; i < g.Windows.Size; i++) {
        ImGuiWindow* window = g.Windows[i];
        if (window && window->Name == name) { return window; }
    }
    return nullptr;
}


Str getDebugFile(ImGuiTest* t, const Str& suffix) {
    auto res = fs::path{
        fmt("/tmp/haxorg_tests/imgui/{}/{}/{}",
            normalize(t->Category),
            normalize(t->Name),
            suffix)};
    if (!fs::is_directory(res.parent_path())) {
        createDirectory(res.parent_path());
    }

    return res.native();
}

ImVec2 getContentPos(ImGuiTestContext* ctx) {
    if (!ctx || !ctx->GetWindowByRef(ctx->GetRef())) {
        return ImGui::GetWindowPos()
             + ImVec2{0, ImGui::GetCurrentWindow()->TitleBarHeight};
    } else {
        return ctx->GetWindowByRef(ctx->GetRef())->Pos
             + ImVec2{
                 0, ctx->GetWindowByRef(ctx->GetRef())->TitleBarHeight};
    }
}

void ImTestVarsBase::show_test_base_window() {
    if (ImGui::Begin("Test base window")) {
        if (ImGui::Button("+1 trace run")) { ++TraceCounter; }
        ImGui::Text("Executing %d trace runs", TraceCounter);
        if (ImGui::Button("Print all windows")) { PrintAllWindows(); }
        ImGui::End();
    }
}

void MouseMoveRelative(ImGuiTestContext* ctx, const ImVec2& shift) {
    ctx->MouseMoveToPos(ImGui::GetMousePos() + shift);
}
