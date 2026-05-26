#include "graph_common.hpp"

using namespace hstd::ext::graph;

std::size_t IGraphObjectBase::getHash() const {
    std::size_t res;
    hstd::hax_hash_combine(res, stable_id);
    return res;
}

bool IGraphObjectBase::isEqual(IGraphObjectBase const* other) const {
    return this->stable_id == other->stable_id;
}

std::string IGraphObjectBase::getRepr() const { return stable_id; }

std::string IGraphObjectBase::getStableId() const { return stable_id; }
