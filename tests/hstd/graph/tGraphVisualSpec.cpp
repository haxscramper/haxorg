#include "../t_graph_tests_common.hpp"

#include <algorithm>
#include <cctype>
#include <filesystem>
#include <hstd/ext/graph/visual/graph_diagram.hpp>
#include <hstd/ext/graph/visual/graph_diagram_validate.hpp>
#include <string>
#include <vector>

#include <google/protobuf/util/json_util.h>
#include <gtest/gtest.h>

namespace {

using DiagramTest = hstd::ext::graph::diagram::proto::DiagramTest;
namespace fs      = std::filesystem;

std::vector<fs::path> getDiagramTestFiles() {
    std::vector<fs::path> result;
    fs::path const        testDir = __CURRENT_FILE_DIR__ / "diagram_tests";

    for (auto const& entry : fs::directory_iterator(testDir)) {
        if (entry.is_regular_file() && entry.path().extension() == ".json") {
            result.push_back(entry.path());
        }
    }

    std::ranges::sort(result);
    return result;
}

std::string diagramTestName(testing::TestParamInfo<fs::path> const& info) {
    std::string result = info.param.stem().string();

    for (char& character : result) {
        if (!std::isalnum(static_cast<unsigned char>(character))) { character = '_'; }
    }

    if (result.empty() || std::isdigit(static_cast<unsigned char>(result.front()))) {
        result.insert(result.begin(), '_');
    }

    return result;
}

class GraphDiagramSpecTest : public testing::TestWithParam<fs::path> {};

TEST_P(GraphDiagramSpecTest, HasValidGeometry) {
    fs::path const& path   = GetParam();
    auto            test   = hstd::serde::read_message_from_json_file<DiagramTest>(path);
    auto const      errors = hstd::ext::graph::diagram::runSpec(test);

    for (auto const& error : errors) {
        ADD_FAILURE() << path << '\n'
                      << "Geometry check #" << error.checkIndex << " (" << error.checkId
                      << ") failed:\n"
                      << error.check.DebugString() << '\n'
                      << error.result.error().what();
    }
}

INSTANTIATE_TEST_SUITE_P(
    GraphDiagramSpec,
    GraphDiagramSpecTest,
    testing::ValuesIn(getDiagramTestFiles()),
    diagramTestName);

} // namespace
