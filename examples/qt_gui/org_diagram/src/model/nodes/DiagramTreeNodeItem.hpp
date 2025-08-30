#include "DiagramTreeNode.hpp"
#include <src/utils/common.hpp>


struct DiagramTreeNodeItem : public DiagramTreeNode {
    using DiagramTreeNode::DiagramTreeNode;

    struct Pos {
        int x;
        int y;
        DESC_FIELDS(Pos, (x, y));
    };

    struct PropertyNames {
        inline static const std::string diagramPosition
            = "HAXORG_DIAGRAM_POSITION";

        inline static const std::string isDiagramNode
            = "HAXORG_DIAGRAM_NODE";
    };

    org::imm::ImmAdapterT<org::imm::ImmSubtree> getSubtree() const {
        return id.as<org::imm::ImmSubtree>();
    }

    Pos getPos() const {
        return getStructuredProperty<Pos>(
                   getSubtree(), PropertyNames::diagramPosition)
            .value();
    }


    static hstd::SPtr<DiagramTreeNodeItem> FromSubtreeItem(
        org::imm::ImmAdapterT<org::imm::ImmSubtree> const& subtree);
};
