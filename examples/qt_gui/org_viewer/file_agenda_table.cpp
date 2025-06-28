#include "file_agenda_table.hpp"

#include "moc_file_agenda_table.cpp"

bool operator<(hstd::UserTime const& lhs, hstd::UserTime const& rhs) {
    return lhs.time < rhs.time;
}

std::string getColumnName(TableColumns column) {
    static const std::unordered_map<TableColumns, std::string> names = {
        {TableColumns::TITLE, "title"},
        {TableColumns::COMPLETION, "[/]"},
        {TableColumns::PRIORITY_INDEX, "[#]"},
        {TableColumns::TODO_INDEX, "todo"},
        {TableColumns::CREATION_DATE, "created"},
        {TableColumns::CLOCKED, "clocked"},
        {TableColumns::TAGS, "tags"},
        {TableColumns::TASK_AGE, "age"}};
    return names.at(column);
}


bool OrgTreeProxyModel::filterAcceptsRow(
    int                source_row,
    const QModelIndex& source_parent) const {
    if (model->isFlatSorting()) {
        auto node = model->flat_nodes[source_row];
        if (hide_completed_tasks && isCompletedTask(node->getTodo())) {
            return false;
        }

        if (hide_tasks_without_todo_on_flat && node->getTodo().empty()) {
            return false;
        }

        return true;
    } else {
        OrgAgendaNode::Ptr node;
        if (source_parent.isValid()) {
            auto parent_node = static_cast<OrgAgendaNode*>(
                source_parent.internalPointer());
            if (source_row < parent_node->children.size()) {
                node = parent_node->children[source_row];
            } else {
                return true;
            }
        } else {
            if (source_row < model->getRoot()->children.size()) {
                node = model->getRoot()->children[source_row];
            } else {
                return true;
            }
        }

        auto [completed, total] = node->getRecursiveCompletion();
        if (hide_completed_tasks && isCompletedTask(node->getTodo())
                && (hide_nested || node->children.empty())
            || (completed == total)) {
            return false;
        }

        if (hide_tasks_without_todo_on_flat && node->getTodo().empty()
            && (hide_nested || node->children.empty())) {
            return false;
        }

        return true;
    }
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


QModelIndex OrgTreeModel::index(
    int                row,
    int                column,
    const QModelIndex& parent) const {
    if (!hasIndex(row, column, parent)) { return QModelIndex{}; }

    if (isFlatSorting()) {
        if (!parent.isValid() && row < flat_nodes.size()) {
            return createIndex(row, column, flat_nodes[row]);
        }
        return QModelIndex{};
    } else {
        if (!parent.isValid()) {
            if (row < getRoot()->children.size()) {
                return createIndex(
                    row, column, getRoot()->children[row].get());
            }
        } else {
            auto parent_node = static_cast<OrgAgendaNode*>(
                parent.internalPointer());
            if (row < parent_node->children.size()) {
                auto child_node = parent_node->children[row];
                return createIndex(row, column, child_node.get());
            }
        }
    }

    return QModelIndex{};
}

QModelIndex OrgTreeModel::parent(const QModelIndex& index) const {
    if (!index.isValid() || isFlatSorting()) { return QModelIndex{}; }

    auto node = static_cast<OrgAgendaNode*>(index.internalPointer());
    auto parent_node = node->parent.lock().get();

    if (!parent_node || parent_node == getRoot()) { return QModelIndex{}; }

    auto grandparent = parent_node->parent.lock().get();
    if (grandparent) {
        auto it = std::find_if(
            grandparent->children.begin(),
            grandparent->children.end(),
            [&](OrgAgendaNode::Ptr const& ch) {
                return parent_node == ch.get();
            });
        if (it != grandparent->children.end()) {
            int row = std::distance(grandparent->children.begin(), it);
            return createIndex(row, 0, parent_node);
        }
    }

    return QModelIndex{};
}

QVariant OrgTreeModel::data(const QModelIndex& index, int role) const {
    if (!index.isValid()) { return QVariant{}; }

    auto node   = static_cast<OrgAgendaNode*>(index.internalPointer());
    int  column = index.column();

    if (role == Qt::DisplayRole) {
        switch (static_cast<TableColumns>(column)) {
            case TableColumns::TITLE:
                return QString::fromStdString(node->getTitle());
            case TableColumns::PRIORITY_INDEX:
                return QString::fromStdString(node->getPriority());
            case TableColumns::TODO_INDEX:
                return QString::fromStdString(node->getTodo());
            case TableColumns::CREATION_DATE: {
                auto created = node->getCreatedTime();
                return QString::fromStdString(
                    created ? created->format() : "");
            }
            case TableColumns::TASK_AGE:
                return QString::fromStdString(node->getAgeDisplay());
            case TableColumns::TAGS: {
                auto        tags = node->getTags();
                std::string result;
                for (size_t i = 0; i < tags.size(); ++i) {
                    if (i > 0) { result += ", "; }
                    result += tags[i];
                }
                return QString::fromStdString(result);
            }
            case TableColumns::COMPLETION: {
                auto [a, b] = node->getRecursiveCompletion();
                return QString::fromStdString(std::format("{}/{}", a, b));
            }
            case TableColumns::CLOCKED: {
                int sec     = node->getClockedSeconds();
                int hours   = sec / (60 * 60);
                int minutes = (sec / 60) % 60;
                return QString::fromStdString(
                    std::format("{}:{}", hours, minutes));
            }
        }
    } else if (
        role == Qt::BackgroundRole
        && column == static_cast<int>(TableColumns::PRIORITY_INDEX)) {
        std::string priority = node->getPriority();
        static const std::unordered_map<std::string, QColor> colors = {
            {"X", QColor{255, 0, 0}},
            {"S", QColor{253, 95, 240}},
            {"A", QColor{240, 223, 175}},
            {"B", QColor{253, 151, 31}},
            {"C", QColor{102, 217, 239}},
            {"D", QColor{161, 239, 228}},
            {"E", QColor{166, 226, 46}},
            {"F", QColor{174, 129, 255}}};
        auto it = colors.find(priority);
        if (it != colors.end()) { return it->second; }
    } else if (
        role == Qt::FontRole
        && column == static_cast<int>(TableColumns::PRIORITY_INDEX)) {
        std::string priority = node->getPriority();
        QFont       font;
        if (priority == "A") {
            font.setBold(true);
            font.setUnderline(true);
            return font;
        } else if (priority == "E" || priority == "F") {
            font.setWeight(QFont::Light);
            return font;
        }
    } else if (
        role == Qt::BackgroundRole
        && column == static_cast<int>(TableColumns::TODO_INDEX)) {
        std::string todo = node->getTodo();
        std::transform(todo.begin(), todo.end(), todo.begin(), ::tolower);
        if (todo == "done" || todo == "completed") {
            return QColor{144, 238, 144};
        } else if (todo == "wip" || todo == "next") {
            return QColor{255, 165, 0};
        } else if (todo == "todo") {
            return QColor{255, 182, 193};
        }
    } else if (
        role == Qt::BackgroundRole
        && column == static_cast<int>(TableColumns::TASK_AGE)) {
        int age_seconds = node->getAgeSeconds();
        if (age_seconds == 0) {
            return QVariant{};
        } else if (age_seconds <= 24 * 3600) {
            return QColor{200, 255, 200};
        } else if (age_seconds <= 7 * 24 * 3600) {
            return QColor{255, 255, 200};
        } else if (age_seconds <= 30 * 24 * 3600) {
            return QColor{255, 220, 200};
        } else {
            return QColor{255, 200, 200};
        }
    }

    return QVariant{};
}

QVariant OrgTreeModel::headerData(
    int             section,
    Qt::Orientation orientation,
    int             role) const {
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole) {
        if (section >= 0 && section < 8) {
            return QString::fromStdString(
                getColumnName(static_cast<TableColumns>(section)));
        }
    } else if (orientation == Qt::Vertical && role == Qt::DisplayRole) {
        return QString::number(section);
    }

    return QVariant{};
}

void CommandPalette::setupUi() {
    setWindowTitle("Go to Item");
    setModal(true);
    resize(600, 400);

    auto layout = new QVBoxLayout{this};
    layout->setContentsMargins(10, 10, 10, 10);

    search_input = new QLineEdit{};
    search_input->setPlaceholderText("Type to search items...");
    connect(
        search_input,
        &QLineEdit::textChanged,
        this,
        &CommandPalette::onSearchChanged);
    layout->addWidget(search_input);

    results_list = new QListWidget{};
    connect(
        results_list,
        &QListWidget::itemActivated,
        this,
        &CommandPalette::onItemActivated);
    results_list->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    results_list->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    layout->addWidget(results_list);

    search_input->setFocus();
}
