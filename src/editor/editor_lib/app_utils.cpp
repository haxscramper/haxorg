#include <editor/editor_lib/app_utils.hpp>
#include <hstd/stdlib/Enumerate.hpp>
#include <hstd/stdlib/Map.hpp>

QModelIndex mapToNestedSource(const QModelIndex& index) {
    QModelIndex currentIndex = index;
    auto currentProxyModel   = qobject_cast<QSortFilterProxyModel const*>(
        index.model());

    while (currentProxyModel) {
        currentIndex      = currentProxyModel->mapToSource(currentIndex);
        currentProxyModel = qobject_cast<QSortFilterProxyModel const*>(
            currentProxyModel->sourceModel());
    }

    return currentIndex;
}

QModelIndex mapToNestedProxy(
    const QModelIndex&          index,
    Vec<QSortFilterProxyModel*> proxies) {
    QModelIndex currentIndex = index;

    for (QSortFilterProxyModel* proxyModel : proxies) {
        currentIndex = proxyModel->mapFromSource(currentIndex);
    }

    return currentIndex;
}

std::string printModelTree(
    const QAbstractItemModel*             model,
    const QModelIndex&                    parent,
    Func<std::string(QModelIndex const&)> toString) {
    if (!model) { return ""; }

    struct ModelProxyRecord {
        QModelIndex index;
    };

    struct ModelLevelRecord {
        int                   depth;
        Vec<ModelProxyRecord> proxies;
        Str                   finalRepr;
    };

    Func<void(CR<QModelIndex> index, int level)> aux;
    Vec<ModelLevelRecord>                        records;
    aux = [&](CR<QModelIndex> index, int level) -> void {
        ModelLevelRecord record{.depth = level};

        QModelIndex currentIndex      = index;
        auto        currentProxyModel = qobject_cast<
            QSortFilterProxyModel const*>(index.model());

        auto add_proxy = [&](CR<QModelIndex> index) {
            record.proxies.push_back(ModelProxyRecord{
                .index = index

            });
        };

        add_proxy(currentIndex);

        while (currentProxyModel) {
            auto mapped  = currentProxyModel->mapToSource(currentIndex);
            currentIndex = mapped;
            add_proxy(currentIndex);
            currentProxyModel = qobject_cast<QSortFilterProxyModel const*>(
                currentProxyModel->sourceModel());
        }

        record.finalRepr = toString(index);
        records.push_back(record);

        int rowCount = model->rowCount(index);
        for (int row = 0; row < rowCount; ++row) {
            QModelIndex sub = model->index(row, 0, index);
            aux(sub, level + 1);
        }
    };

    aux(parent, 0);

    std::ostringstream out;

    UnorderedMap<QAbstractItemModel const*, Str> model_names;
    for (auto const& level : records) {
        for (auto const& proxy : level.proxies) {
            if (!model_names.contains(proxy.index.model())) {
                if (proxy.index.model() == nullptr) {
                    model_names.insert_or_assign(
                        proxy.index.model(), "0x0");
                } else if (proxy.index.model()->objectName().isEmpty()) {
                    model_names.insert_or_assign(
                        proxy.index.model(),
                        fmt("M{}", model_names.size()));
                } else {
                    model_names.insert_or_assign(
                        proxy.index.model(),
                        proxy.index.model()->objectName().toStdString());
                }
            }
        }
    }

    for (auto const& level : enumerator(records)) {
        auto const& l = level.value();
        out << std::string(l.depth * 2, ' ');
        for (auto const& proxy : enumerator(l.proxies)) {
            if (proxy.is_first()) {
                out << " ";
            } else {
                out << "->";
            }

            auto const& p = proxy.value();
            out << fmt(
                "[{}:{}, @{}, {}]",
                p.index.row(),
                p.index.column(),
                fmt("{:p}", p.index.internalPointer()),
                model_names.at(p.index.model()));
        }

        out << " " << l.finalRepr;
        if (!level.is_last()) { out << "\n"; }
    }

    return out.str();
}

Func<std::string(const QModelIndex&)> store_index_printer(
    OrgStore* store) {
    return [store](QModelIndex const& idx) -> std::string {
        OrgBoxId box = qvariant_cast<OrgBoxId>(idx.data());
        if (store->data.contains(box)) {
            auto node = store->node(box);
            return fmt("{}", node->getKind());
        } else {
            return fmt("[err:{}]", box.value);
        }
    };
}
