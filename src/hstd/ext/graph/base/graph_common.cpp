#include "graph_common.hpp"

std::string IGraphObjectBase::getStableId() const {
    return std::format("IGraphObjectBase-{}", getHash());
}
