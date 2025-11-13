#include "ElkLayoutManager.hpp"

#include <hstd/ext/logger.hpp>

std::string ElkLayoutManager::layoutDiagram(const std::string& graphJson) {
    LOGIC_ASSERTION_CHECK(
        elkEngine->isInitialized(),
        "Initialization failed earlier, cannot execute layout");

    return elkEngine->performLayout(graphJson);
}

dia::layout::elk::Graph ElkLayoutManager::layoutDiagram(
    const dia::layout::elk::Graph& graph) {
    json serial = hstd::to_json_eval(graph);
    HSLOG_TRACE("{}", serial.dump(2));
    dia::layout::elk::validate(graph);
    std::string tmp    = serial.dump();
    auto        layout = layoutDiagram(tmp);
    HSLOG_TRACE("{}", layout);
    return hstd::from_json_eval<dia::layout::elk::Graph>(
        json::parse(layout));
}
