#pragma once

#include <string>
#include <QAbstractItemModel>
#include <hstd/stdlib/Func.hpp>
#include <editor/editor_lib/org_document_model.hpp>
#include <QEvent>

std::string printModelTree(
    const QAbstractItemModel*             model,
    const QModelIndex&                    parent,
    Func<std::string(QModelIndex const&)> toString);

Func<std::string(QModelIndex const&)> store_index_printer(
    const OrgStore* store);

template <typename T>
std::string qdebug_to_str(T const& index) {
    QString output;
    QDebug(&output) << index;
    return output.toStdString();
}

QModelIndex mapToNestedSource(QModelIndex const& index);
QModelIndex mapToNestedProxy(
    QModelIndex const&          index,
    Vec<QSortFilterProxyModel*> proxies);


inline QModelIndex index(
    QAbstractItemModel*        model,
    Vec<Pair<int, int>> const& path) {
    QModelIndex result = model->index(path.at(0).first, path.at(0).second);
    for (int i = 1; i < path.size(); ++i) {
        result = model->index(path.at(i).first, path.at(i).second, result);
    }

    return result;
}

inline QModelIndex index(
    QAbstractItemModel* model,
    Vec<int> const&     path,
    int                 alwaysColumn = 0) {
    QModelIndex result = model->index(path.at(0), alwaysColumn);
    for (int i = 1; i < path.size(); ++i) {
        result = model->index(path.at(i), alwaysColumn, result);
    }

    return result;
}


class DebugEventFilter : public QObject {
  public:
    DebugEventFilter(QObject* parent) : QObject(parent) {}

  protected:
    bool eventFilter(QObject* obj, QEvent* event) override {
        qDebug().noquote().nospace()
            << "Object: '" << obj->metaObject()->className()
            << "::" << obj->objectName() << //
            "' Type: " << event->type() <<  //
            " Event: " << event <<          //
            " Receiver: " << obj;
        return false;
    }

    static void add(QObject* obj) {
        obj->installEventFilter(new DebugEventFilter(obj));
    }

    static finally scoped(QObject* obj) {
        SPtr<DebugEventFilter> filter = std::make_shared<DebugEventFilter>(
            obj);

        obj->installEventFilter(filter.get());
        return finally(
            [filter, obj]() { obj->removeEventFilter(filter.get()); });
    }
};
