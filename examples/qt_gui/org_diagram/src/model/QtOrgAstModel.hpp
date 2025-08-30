#pragma once

#include <QAbstractItemModel>
#include <QObject>
#include <memory>
#include <vector>
#include <unordered_map>
#include <haxorg/sem/ImmOrg.hpp>
#include <src/utils/log_graph_tracker.hpp>
#include <src/utils/common.hpp>

struct OrgDiagramNode
    : public QObject
    , public std::enable_shared_from_this<OrgDiagramNode> {
    Q_OBJECT

  public:
    org::imm::ImmUniqId                   id;
    hstd::Vec<hstd::SPtr<OrgDiagramNode>> subnodes;
    std::weak_ptr<OrgDiagramNode>         parent;

    std::string formatToString() const { return hstd::fmt("id:{}", id); }

    OrgDiagramNode(org::imm::ImmUniqId const& id);

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

struct OrgDiagramModel : public QAbstractItemModel {
    Q_OBJECT

  private:
    hstd::SPtr<OrgDiagramNode>                                   rootNode;
    mutable std::unordered_map<org::imm::ImmUniqId, QModelIndex> nodeMap;

  public:
    explicit OrgDiagramModel(
        std::shared_ptr<OrgDiagramNode> root,
        QObject*                        parent = nullptr);

    hstd::ColText format();

    QModelIndex index(
        int                row,
        int                column,
        const QModelIndex& parent = QModelIndex{}) const override;

    QModelIndex parent(const QModelIndex& index) const override;

    OrgDiagramNode* getNode(QModelIndex const& index) const;

    int rowCount(const QModelIndex& parent = QModelIndex{}) const override;

    int columnCount(
        const QModelIndex& parent = QModelIndex{}) const override {
        return getNode(parent)->getColumnCount();
    }

    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole)
        const override;

    bool insertRows(
        int                row,
        int                count,
        const QModelIndex& parent = QModelIndex{}) override;

    bool removeRows(
        int                row,
        int                count,
        const QModelIndex& parent = QModelIndex{}) override;

    void addNodeToParent(
        std::shared_ptr<OrgDiagramNode> node,
        const QModelIndex&              parentIndex);

    QModelIndex getIndexForId(const org::imm::ImmUniqId& id) const;


  private slots:
    void onSubnodeAdded(int index);

    void onSubnodeAboutToBeRemoved(int index);

    void onSubnodeRemoved() {
        TRACKED_SLOT(onSubnodeRemoved);
        endRemoveRows();
    }

    void onDataChanged();

  private:
    void buildNodeMap() const {
        nodeMap.clear();
        buildNodeMapRecursive(QModelIndex{});
    }

    void buildNodeMapRecursive(const QModelIndex& parent) const;

    void removeFromNodeMap(std::shared_ptr<OrgDiagramNode> node) {
        nodeMap.erase(node->id);
        for (auto& subnode : node->subnodes) {
            removeFromNodeMap(subnode);
        }
    }

    void invalidateNodeMapAfterIndex(
        const QModelIndex& parent,
        int                startRow);

    QModelIndex findIndexForId(
        const org::imm::ImmUniqId& id,
        const QModelIndex&         parent) const;

    void connectNode(std::shared_ptr<OrgDiagramNode> node);

    void disconnectNode(std::shared_ptr<OrgDiagramNode> node) {
        disconnect(node.get(), nullptr, this, nullptr);
        for (auto& subnode : node->subnodes) { disconnectNode(subnode); }
    }

    QModelIndex getIndexForNode(OrgDiagramNode* node) const {
        if (node == rootNode.get()) { return QModelIndex{}; }

        return getIndexForId(node->id);
    }
};
