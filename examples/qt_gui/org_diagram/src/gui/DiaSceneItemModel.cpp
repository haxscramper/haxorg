#include "DiaSceneItemModel.hpp"

#include <sanitizer/asan_interface.h>

hstd::ColText DiaSceneItemModel::format() {
    return printModelTree(
        this,
        QModelIndex{},
        [](QModelIndex const& idx) -> hstd::ColText {
            hstd::ColStream os;
            DiaSceneItem*   ptr = static_cast<DiaSceneItem*>(
                idx.internalPointer());
            if (ptr == nullptr) {
                os << "nullptr " << qdebug_to_str(idx);
            } else {
                // os << "object-desc:" << hstd::deObjectPtr(ptr);
                os << "adapter:" << hstd::fmt1(ptr->adapter);
                // os << "\nindex:" << qdebug_to_str(idx);
                // if (ptr->hasParent()) {
                //     os << "\nself-path:"
                //        << hstd::fmt1(ptr->getSelfPathFromRoot());
                // } else {
                //     os << "\nself-path:[]";
                // }

                if (__asan_address_is_poisoned(ptr)) {
                    __asan_describe_address(ptr);
                }

                // if (ptr->getParent() != nullptr) {
                //     os << "\nparent:"
                //        << hstd::descObjectPtr(ptr->getParent());
                // }

                auto selfFormat = ptr->formatSelf();
                switch (selfFormat.size()) {
                    case 0: break;
                    case 1: os << "\nself:" << selfFormat.at(0); break;
                    default:
                        for (auto const& line : selfFormat) {
                            os << "\nself:";
                            os << line;
                        }
                }
            }
            return os;
        },
        true);
}

hstd::Opt<QModelIndex> DiaSceneItemModel::indexAtPath(
    const hstd::Vec<int>& path) const {
    QModelIndex result;
    for (auto const& i : path) {
        if (i < rowCount(result)) {
            result = index(i, 0, result);
        } else {
            return std::nullopt;
        }
    }
    return result;
}

QModelIndex DiaSceneItemModel::index(
    int                row,
    int                column,
    const QModelIndex& parent) const {
    hstd::logic_assertion_check_not_nil(rootNode);
    if (!hasIndex(row, column, parent)) { return QModelIndex{}; }

    DiaSceneItem* parentNode{};
    if (!parent.isValid()) {
        parentNode = rootNode;
    } else {
        parentNode = static_cast<DiaSceneItem*>(parent.internalPointer());
    }

    if (row < static_cast<int>(parentNode->size())) {
        return createIndex(row, column, parentNode->at(row));
    }

    return QModelIndex{};
}
QModelIndex DiaSceneItemModel::parent(const QModelIndex& index) const {
    if (!index.isValid()) { return QModelIndex{}; }

    DiaSceneItem* childNode = static_cast<DiaSceneItem*>(
        index.internalPointer());
    DiaSceneItem* parentNode = childNode->getParent();

    if (parentNode == rootNode) { return QModelIndex{}; }

    DiaSceneItem* grandParent = parentNode->getParent();
    if (!grandParent) { return QModelIndex{}; }

    for (int i = 0; i < grandParent->size(); ++i) {
        if (grandParent->at(i) == parentNode) {
            return createIndex(i, 0, parentNode);
        }
    }

    return QModelIndex{};
}
QVariant DiaSceneItemModel::data(const QModelIndex& index, int role)
    const {
    hstd::logic_assertion_check_not_nil(rootNode);
    if (!index.isValid()) { return QVariant{}; }

    if (role == Qt::DisplayRole) {
        DiaSceneItem* node = static_cast<DiaSceneItem*>(
            index.internalPointer());
        return node->name;
    }

    return QVariant{};
}

QModelIndex DiaSceneItemModel::findNodeIndex(
    const QModelIndex& parent,
    DiaSceneItem*      targetNode) const {
    hstd::logic_assertion_check_not_nil(rootNode);
    DiaSceneItem* parentNode = parent.isValid()
                                 ? static_cast<DiaSceneItem*>(
                                       parent.internalPointer())
                                 : rootNode;
    if (!parentNode) { return QModelIndex{}; }

    // Check direct children
    for (int i = 0; i < parentNode->size(); ++i) {
        if (parentNode->at(i) == targetNode) {
            return index(i, 0, parent);
        }
    }

    // Search recursively in children
    for (int i = 0; i < parentNode->size(); ++i) {
        QModelIndex childIndex = index(i, 0, parent);
        QModelIndex found      = findNodeIndex(childIndex, targetNode);
        if (found.isValid()) { return found; }
    }

    HSLOG_WARNING(
        _cat,
        "Could not find index for target node ",
        targetNode->name.toStdString());

    return QModelIndex{};
}


void DiaSceneItemModel::beginEditApply(
    const DiaEdit&         edit,
    DiaEditTransientState& state) {
    TRACKED_FUNCTION("beginEditApply");

    auto getParent = [&](DiaAdapter const& adapter) {
        auto parentPath = adapter.getParentPathFromRoot();
        hstd::Opt<QModelIndex> parentItem = indexAtPath(parentPath);

        LOGIC_ASSERTION_CHECK(
            parentItem.has_value(),
            "No node found at path {}, cannot execute insert "
            "operation",
            parentPath);

        return std::pair{parentPath, parentItem.value()};
    };

    switch (edit.getKind()) {
        case DiaEdit::Kind::Delete: {
            auto [parentPath, parentIndex] = getParent(edit.getSrc());
            int idx                        = state.updateIdx(
                edit.getDelete().srcIndex, parentPath);
            HSLOG_INFO(
                _cat,
                hstd::fmt(
                    "About to remove item {} from {}",
                    idx,
                    qdebug_to_str(parentIndex)));

            beginRemoveRows(parentIndex, idx, idx);
            break;
        }

        case DiaEdit::Kind::Move: {
            auto [parentPath, parentIndex] = getParent(edit.getSrc());
            LOGIC_ASSERTION_CHECK(
                parentIndex == getIdParentIndex(edit.getDst()),
                "Dia edit moves should happen under the same parent");

            int src = state.updateIdx(edit.getMove().srcIndex, parentPath);
            int dst = state.updateIdx(edit.getMove().dstIndex, parentPath);

            if (src < dst) { dst += 1; }

            bool isValid = beginMoveRows(
                parentIndex, src, src, parentIndex, dst);

            LOGIC_ASSERTION_CHECK(
                isValid,
                "Move src={} dst={} under parent={} is not valid.",
                src,
                dst,
                parentPath);

            break;
        }

        case DiaEdit::Kind::Insert: {
            auto [parentPath, parentIndex] = getParent(edit.getDst());
            int idx                        = state.updateIdx(
                edit.getInsert().dstIndex, parentPath);
            HSLOG_INFO(
                _cat,
                hstd::fmt(
                    "About to insert item {} under {}",
                    idx,
                    qdebug_to_str(parentIndex)));
            beginInsertRows(parentIndex, idx, idx);
            break;
        }

        case DiaEdit::Kind::Update: {
            break;
        }

        default: {
            logic_todo_impl();
        }
    }
}

void DiaSceneItemModel::endEditApply(
    const DiaEdit&         edit,
    DiaEditTransientState& state) {
    TRACKED_FUNCTION("endEditApply");
    switch (edit.getKind()) {
        case DiaEdit::Kind::Delete: {
            endRemoveRows();
            break;
        }

        case DiaEdit::Kind::Insert: {
            endInsertRows();
            break;
        }

        case DiaEdit::Kind::Move: {
            endMoveRows();
            break;
        }

        case DiaEdit::Kind::Update: {
            auto item = indexAtPath(edit.getDst().getSelfPathFromRoot());
            LOGIC_ASSERTION_CHECK(
                item.has_value(),
                "No index associated from the DST item {} at path {}",
                edit.getDst().id,
                edit.getDst().getSelfPathFromRoot());

            dataChanged(item.value(), item.value());
            break;
        }

        default: {
            logic_todo_impl();
        }
    }
}
