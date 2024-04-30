#include <editor/editor_lib/app_utils.hpp>

std::string printModelTree(
    const QAbstractItemModel*             model,
    const QModelIndex&                    parent,
    Func<std::string(QModelIndex const&)> toString,
    int                                   level) {
    if (!model) { return ""; }
    std::ostringstream out;
    int                rowCount = model->rowCount(parent);
    for (int row = 0; row < rowCount; ++row) {
        QModelIndex index = model->index(row, 0, parent);
        out << std::string(level * 2, ' ') << toString(index) << "\n";
        if (model->hasChildren(index)) {
            out << printModelTree(model, index, toString, level + 1);
        }
    }
    return out.str();
}
