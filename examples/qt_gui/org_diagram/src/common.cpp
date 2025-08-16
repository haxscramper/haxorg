#include "common.hpp"

static std::shared_ptr<hstd::log::log_graph_tracker> tracker = nullptr;
static std::shared_ptr<hstd::log::graphviz_processor>
    graph_processor = nullptr;
static std::shared_ptr<hstd::log::logger_processor>
    log_processor = nullptr;

std::shared_ptr<hstd::log::log_graph_tracker> get_tracker() {

    if (tracker.get() == nullptr) {
        tracker         = std::make_shared<hstd::log::log_graph_tracker>();
        graph_processor = std::make_shared<
            hstd::log::graphviz_processor>();
        tracker->add_processor(graph_processor);
        log_processor = std::make_shared<hstd::log::logger_processor>();
        tracker->add_processor(log_processor);
    }

    return tracker;
}


hstd::ext::Graphviz::Graph get_tracker_graph() {
    return graph_processor->get_graphviz();
}
