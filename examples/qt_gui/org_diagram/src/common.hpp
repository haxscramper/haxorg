#pragma once

#include <hstd/ext/logger.hpp>
#include "log_graph_tracker.hpp"

std::shared_ptr<hstd::log::log_graph_tracker> get_tracker();
hstd::ext::Graphviz::Graph                    get_tracker_graph();
