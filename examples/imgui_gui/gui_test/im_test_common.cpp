#include "im_test_common.hpp"

#include <hstd/stdlib/Filesystem.hpp>

Str getDebugFile(ImGuiTest* t, const Str& suffix) {
    auto res = fs::path{fmt(
        "/tmp/haxorg_tests/imgui/{}/{}/{}", t->Category, t->Name, suffix)};
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
