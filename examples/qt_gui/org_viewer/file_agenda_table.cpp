#include "file_agenda_table.hpp"

bool operator<(hstd::UserTime const& lhs, hstd::UserTime const& rhs) {
    return lhs.time < rhs.time;
}

bool OrgTreeProxyModel::lessThan(
    const QModelIndex& left,
    const QModelIndex& right) const {
    int  column       = left.column();
    bool is_ascending = model->sort_order == Qt::AscendingOrder;

    if (model->isFlatSorting()) {
        auto left_node = static_cast<OrgAgendaNode*>(
            left.internalPointer());
        auto right_node = static_cast<OrgAgendaNode*>(
            right.internalPointer());

        auto earlyEmptyResult =
            [&](bool left_empty, bool right_empty) -> std::optional<bool> {
            if (left_empty && right_empty) { return false; }
            if (left_empty) { return !is_ascending; }
            if (right_empty) { return is_ascending; }
            return std::nullopt;
        };

        auto compareWithEmptyHandling = hstd::overloaded{
            [&]<typename T>(
                hstd::Opt<T> const& left_value,
                hstd::Opt<T> const& right_value) -> bool {
                auto early = earlyEmptyResult(
                    !left_value.has_value(), !right_value.has_value());
                if (early.has_value()) { return early.value(); }
                return left_value.value() < right_value.value();
            },
            [&](auto left_value,
                auto right_value,
                auto empty_value) -> bool {
                auto early = earlyEmptyResult(
                    left_value == empty_value, right_value == empty_value);
                if (early.has_value()) { return early.value(); }
                return left_value < right_value;
            },
        };

        switch (static_cast<TableColumns>(column)) {
            case TableColumns::PRIORITY_INDEX:
                return compareWithEmptyHandling(
                    left_node->getPriorityOrder(),
                    right_node->getPriorityOrder(),
                    -1);
            case TableColumns::TAGS:
                return compareWithEmptyHandling(
                    left_node->getTags().size(),
                    right_node->getTags().size(),
                    size_t{0});
            case TableColumns::TODO_INDEX:
                return compareWithEmptyHandling(
                    left_node->getTodo(),
                    right_node->getTodo(),
                    std::string{""});
            case TableColumns::CLOCKED:
                return compareWithEmptyHandling(
                    left_node->getClockedSeconds(),
                    right_node->getClockedSeconds(),
                    0);
            case TableColumns::CREATION_DATE:
                return compareWithEmptyHandling(
                    left_node->getCreatedTime(),
                    right_node->getCreatedTime());
            case TableColumns::TASK_AGE:
                return compareWithEmptyHandling(
                    left_node->getAgeSeconds(),
                    right_node->getAgeSeconds(),
                    0);
            default: return QSortFilterProxyModel::lessThan(left, right);
        }
    } else {
        return QSortFilterProxyModel::lessThan(left, right);
    }
}
