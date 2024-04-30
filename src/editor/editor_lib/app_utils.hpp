#pragma once

#include <string>
#include <QAbstractItemModel>
#include <hstd/stdlib/Func.hpp>

std::string printModelTree(
    const QAbstractItemModel*             model,
    const QModelIndex&                    parent,
    Func<std::string(QModelIndex const&)> toString,
    int                                   level = 0);

template <typename T>
std::string qdebug_to_str(T const& index) {
    QString output;
    QDebug(&output) << index;
    return output.toStdString();
}
