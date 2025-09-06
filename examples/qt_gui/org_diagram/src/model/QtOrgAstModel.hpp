#pragma once

#include <QAbstractItemModel>
#include <QObject>
#include <haxorg/sem/ImmOrg.hpp>
#include <src/utils/log_graph_tracker.hpp>
#include <src/utils/common.hpp>
#include <src/model/nodes/DiagramTreeNode.hpp>


struct OrgDiagramModel : public QAbstractItemModel {
    Q_OBJECT

  private:
    DiaAdapter rootNode;

  public:
    explicit OrgDiagramModel(
        DiaAdapter const& root,
        QObject*          parent = nullptr);

    void setRoot(DiaAdapter const& root);

    hstd::ColText format();

    struct IndexData {
        DiaUniqId const& uniq;
    };

    mutable hstd::UnorderedMap<DiaUniqId, std::shared_ptr<IndexData>>
        adapters;

    mutable hstd::UnorderedMap<DiaUniqId, QPersistentModelIndex> indexMap;

    hstd::UnorderedMap<DiaUniqId, DiaUniqId> parentMap;

    hstd::Opt<DiaUniqId> getParentId(DiaUniqId const& id) const {
        return parentMap.get(id);
    }

    hstd::Opt<QPersistentModelIndex> getParentIndex(
        DiaUniqId const& id) const {
        if (auto parent = getParentId(id); parent.has_value()) {
            return getNodeIndex(parent.value());
        } else {
            return std::nullopt;
        }
    }

    hstd::Opt<QPersistentModelIndex> getNodeIndex(
        DiaUniqId const& id) const {
        return indexMap.get(id);
    }

    QModelIndex indexForData(int row, int column, DiaAdapter const& id)
        const {
        adapters.insert_or_assign(
            id.id, std::make_shared<IndexData>(id.id));
        auto index = createIndex(row, column, adapters.at(id.id).get());
        indexMap.insert_or_assign(id.id, index);
        return index;
    }

    std::shared_ptr<IndexData> getData(DiaUniqId const& id) const {
        return adapters.at(id);
    }

    void removeData(DiaUniqId const& id) { adapters.erase(id); }


    QModelIndex index(
        int                row,
        int                column,
        const QModelIndex& parent = QModelIndex{}) const override;

    QModelIndex parent(const QModelIndex& index) const override;

    DiaAdapter getNode(QModelIndex const& index) const;

    int rowCount(const QModelIndex& parent = QModelIndex{}) const override;

    int columnCount(
        const QModelIndex& parent = QModelIndex{}) const override {
        return 1;
    }

    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole)
        const override;

    QModelIndex getIndexForId(const org::imm::ImmUniqId& id) const;
};
