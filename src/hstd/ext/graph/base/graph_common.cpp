#include "graph_common.hpp"

using namespace hstd::ext::graph;

std::string IGraphObjectBase::getStableId() const {
    return std::format("IGraphObjectBase-{}", getHash());
}
