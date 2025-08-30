#pragma once

#include <hstd/stdlib/Vec.hpp>
#include <QObject>
#include <haxorg/sem/ImmOrg.hpp>

struct OrgDiagramNode
    : public QObject
    , public std::enable_shared_from_this<OrgDiagramNode> {
    Q_OBJECT

  public:
    org::imm::ImmAdapter                  id;
    hstd::Vec<hstd::SPtr<OrgDiagramNode>> subnodes;
    std::weak_ptr<OrgDiagramNode>         parent;

    std::string formatToString() const { return hstd::fmt("id:{}", id); }

    OrgDiagramNode(org::imm::ImmAdapter const& id);

    org::imm::ImmUniqId uniq() const { return id.uniq(); }

    int getColumnCount() const;

    void addSubnode(hstd::SPtr<OrgDiagramNode> node);
    void removeSubnode(int index);
    void updateData();

    hstd::ColText format() const;

  signals:
    void subnodeAdded(int index);
    void subnodeAboutToBeRemoved(int index);
    void subnodeRemoved();
    void dataChanged();
};
