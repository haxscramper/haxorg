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
