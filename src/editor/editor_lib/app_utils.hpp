#pragma once

#include <string>
#include <QAbstractItemModel>
#include <hstd/stdlib/Func.hpp>
#include <editor/editor_lib/org_document_model.hpp>

std::string printModelTree(
    const QAbstractItemModel*             model,
    const QModelIndex&                    parent,
    Func<std::string(QModelIndex const&)> toString);

Func<std::string(QModelIndex const&)> store_index_printer(OrgStore* store);

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
