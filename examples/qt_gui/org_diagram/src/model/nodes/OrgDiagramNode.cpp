#include "OrgDiagramNode.hpp"

#include <src/utils/common.hpp>


int OrgDiagramNode::getColumnCount() const { return 1; }

void OrgDiagramNode::addSubnode(std::shared_ptr<OrgDiagramNode> node) {
    node->parent = shared_from_this();
    subnodes.push_back(node);
    HSLOG_TRACKED_EMIT(
        get_tracker(),
        subnodeAdded,
        static_cast<int>(subnodes.size()) - 1);
}

void OrgDiagramNode::removeSubnode(int index) {
    if (index >= 0 && index < static_cast<int>(subnodes.size())) {
        subnodes.at(index)->parent.reset();
        HSLOG_TRACKED_EMIT(get_tracker(), subnodeAboutToBeRemoved, index);
        subnodes.erase(subnodes.begin() + index);
        HSLOG_TRACKED_EMIT(get_tracker(), subnodeRemoved);
    }
}

void OrgDiagramNode::updateData() {
    HSLOG_TRACKED_EMIT(get_tracker(), dataChanged);
}

hstd::ColText OrgDiagramNode::format() const {
    hstd::ColStream                                                os;
    hstd::Func<void(hstd::SPtr<OrgDiagramNode const> const&, int)> aux;

    aux = [&](hstd::SPtr<OrgDiagramNode const> const& node, int level) {
        os.indent(level * 2);
        os << hstd::fmt1(node->id);
        os << "\n";

        for (auto const& sub : node->subnodes) { aux(sub, level + 1); }
    };

    aux(shared_from_this(), 0);

    return os;
}

OrgDiagramNode::OrgDiagramNode(const org::imm::ImmAdapter& id) : id{id} {}


#include "OrgDiagramNode.moc"
