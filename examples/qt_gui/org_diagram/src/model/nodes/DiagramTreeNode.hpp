#pragma once

#include <hstd/stdlib/Vec.hpp>
#include <QObject>
#include <haxorg/sem/ImmOrg.hpp>

#define _cat "model.diagram"

struct DiagramTreeNode
    : public QObject
    , public hstd::SharedPtrApi<DiagramTreeNode> {
    Q_OBJECT

  public:
    org::imm::ImmAdapter                  id;
    hstd::Vec<hstd::SPtr<DiagramTreeNode>> subnodes;
    std::weak_ptr<DiagramTreeNode>         parent;

    std::string formatToString() const { return hstd::fmt("id:{}", id); }

    DiagramTreeNode(org::imm::ImmAdapter const& id);

    org::imm::ImmUniqId uniq() const { return id.uniq(); }

    int getColumnCount() const;

    void addSubnode(hstd::SPtr<DiagramTreeNode> node);
    void removeSubnode(int index);
    void updateData();
    void insertSubnode(hstd::SPtr<DiagramTreeNode> const& node, int index);

    hstd::ColText format() const;

    static DiagramTreeNode::Ptr FromDocument(
        org::imm::ImmAdapterT<org::imm::ImmDocument> const& root);

  signals:
    void subnodeAdded(int index);
    void subnodeAboutToBeRemoved(int index);
    void subnodeRemoved();
    void dataChanged();
};
