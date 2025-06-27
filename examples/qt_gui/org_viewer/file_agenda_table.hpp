#include <QtCore/QAbstractItemModel>
#include <QtCore/QSortFilterProxyModel>
#include <QtGui/QColor>
#include <QtGui/QFont>
#include <QtWidgets/QWidget>
#include <QtWidgets/QTreeView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QHeaderView>
#include <QtGui/QShortcut>
#include <QtGui/QKeySequence>
#include <QtCore/QModelIndex>
#include <QtWidgets/QDialog>

#include <vector>
#include <unordered_map>
#include <string>
#include <optional>

#include "shared_org_logic.hpp"

enum class TableColumns
{
    TITLE          = 0,
    COMPLETION     = 1,
    PRIORITY_INDEX = 2,
    TODO_INDEX     = 3,
    CREATION_DATE  = 4,
    CLOCKED        = 5,
    TASK_AGE       = 6,
    TAGS           = 7
};

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

class OrgTreeModel : public QAbstractItemModel {
    Q_OBJECT

  public:
    explicit OrgTreeModel(OrgAgendaNode* root_node)
        : root_node{root_node}
        , focused{nullptr}
        , sort_column{0}
        , sort_order{Qt::AscendingOrder} {
        setFlatListFrom(getRoot());
    }

    OrgAgendaNode* getRoot() const {
        return focused ? focused : root_node;
    }

    void setFocused(OrgAgendaNode* node) {
        beginResetModel();
        focused = node;
        setFlatListFrom(getRoot());
        endResetModel();
    }

    void setFlatListFrom(OrgAgendaNode* node) {
        flat_nodes.clear();
        collectAllNodes(node);
    }

    bool isFlatSorting() const {
        return sort_column != static_cast<int>(TableColumns::TITLE);
    }

    QModelIndex index(
        int                row,
        int                column,
        const QModelIndex& parent = QModelIndex()) const override {
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
                        row, column, getRoot()->children[row]);
                }
            } else {
                auto parent_node = static_cast<OrgAgendaNode*>(
                    parent.internalPointer());
                if (row < parent_node->children.size()) {
                    auto child_node = parent_node->children[row];
                    return createIndex(row, column, child_node);
                }
            }
        }

        return QModelIndex{};
    }

    QModelIndex parent(const QModelIndex& index) const override {
        if (!index.isValid() || isFlatSorting()) { return QModelIndex{}; }

        auto node = static_cast<OrgAgendaNode*>(index.internalPointer());
        auto parent_node = node->parent;

        if (!parent_node || parent_node == getRoot()) {
            return QModelIndex{};
        }

        auto grandparent = parent_node->parent;
        if (grandparent) {
            auto it = std::find(
                grandparent->children.begin(),
                grandparent->children.end(),
                parent_node);
            if (it != grandparent->children.end()) {
                int row = std::distance(grandparent->children.begin(), it);
                return createIndex(row, 0, parent_node);
            }
        }

        return QModelIndex{};
    }

    int rowCount(
        const QModelIndex& parent = QModelIndex()) const override {
        if (isFlatSorting()) {
            if (!parent.isValid()) { return flat_nodes.size(); }
            return 0;
        } else {
            if (!parent.isValid()) { return getRoot()->children.size(); }
            auto node = static_cast<OrgAgendaNode*>(
                parent.internalPointer());
            return node->children.size();
        }
    }

    int columnCount(
        const QModelIndex& parent = QModelIndex()) const override {
        return 8;
    }

    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole)
        const override {
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
                case TableColumns::CREATION_DATE:
                    return QString::fromStdString(
                        fmt1(node->getCreatedTime()));
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
                    return QString::fromStdString(
                        std::format("{}/{}", a, b));
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
            std::transform(
                todo.begin(), todo.end(), todo.begin(), ::tolower);
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

    QVariant headerData(
        int             section,
        Qt::Orientation orientation,
        int             role = Qt::DisplayRole) const override {
        if (orientation == Qt::Horizontal && role == Qt::DisplayRole) {
            if (section >= 0 && section < 8) {
                return QString::fromStdString(
                    getColumnName(static_cast<TableColumns>(section)));
            }
        } else if (
            orientation == Qt::Vertical && role == Qt::DisplayRole) {
            return QString::number(section);
        }

        return QVariant{};
    }

  private:
    void collectAllNodes(OrgAgendaNode* node) {
        if (node != getRoot()) { flat_nodes.push_back(node); }
        for (auto child : node->children) { collectAllNodes(child); }
    }

  public:
    OrgAgendaNode*              focused;
    OrgAgendaNode*              root_node;
    int                         sort_column;
    Qt::SortOrder               sort_order;
    std::vector<OrgAgendaNode*> flat_nodes;
};

class OrgTreeProxyModel : public QSortFilterProxyModel {
    Q_OBJECT

  public:
    explicit OrgTreeProxyModel(QObject* parent, OrgTreeModel* model)
        : QSortFilterProxyModel{parent}
        , model{model}
        , hide_tasks_without_todo_on_flat{false}
        , hide_completed_tasks{false}
        , hide_nested{false} {
        setSortRole(Qt::DisplayRole);
        if (model) {
            // connect(
            //     model,
            //     &QAbstractItemModel::modelReset,
            //     this,
            //     &QSortFilterProxyModel::invalidateFilter);
        }
    }

    void sort(int column, Qt::SortOrder order) override {
        model->sort_column = column;
        model->sort_order  = order;

        invalidate();
        if (column != static_cast<int>(TableColumns::TITLE)) {
            QSortFilterProxyModel::sort(column, order);
        }

        invalidateFilter();
    }

  protected:
    bool filterAcceptsRow(int source_row, const QModelIndex& source_parent)
        const override {
        if (model->isFlatSorting()) {
            auto node = model->flat_nodes[source_row];
            if (hide_completed_tasks && isCompletedTask(node->getTodo())) {
                return false;
            }

            if (hide_tasks_without_todo_on_flat
                && node->getTodo().empty()) {
                return false;
            }

            return true;
        } else {
            OrgAgendaNode* node;
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

    bool lessThan(const QModelIndex& left, const QModelIndex& right)
        const override;

  private:
    bool isCompletedTask(const std::string& todo) const {
        static const std::unordered_set<std::string> completed_tasks = {
            "done", "completed"};
        std::string lower_todo = todo;
        std::transform(
            lower_todo.begin(),
            lower_todo.end(),
            lower_todo.begin(),
            ::tolower);
        return completed_tasks.find(lower_todo) != completed_tasks.end();
    }

  public:
    OrgTreeModel* model;
    bool          hide_tasks_without_todo_on_flat;
    bool          hide_completed_tasks;
    bool          hide_nested;
};

class CommandPaletteItem {
  public:
    std::string title;
    std::string full_path;
    QModelIndex model_index;
    double      score{0.0};

    CommandPaletteItem(
        const std::string& title,
        const std::string& full_path,
        const QModelIndex& model_index)
        : title{title}, full_path{full_path}, model_index{model_index} {}
};

class CommandPalette : public QDialog {
    Q_OBJECT

  public:
    explicit CommandPalette(QWidget* parent = nullptr) : QDialog{parent} {
        setupUi();
        setWindowFlags(Qt::FramelessWindowHint | Qt::Popup);
    }

    void setupUi() {
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

    void positionOverParent() {
        if (parentWidget()) {
            auto parent_rect   = parentWidget()->geometry();
            int  palette_width = static_cast<int>(
                parent_rect.width() * 0.6);
            int x = parent_rect.x()
                  + (parent_rect.width() - palette_width) / 2;
            int y = parent_rect.y() + 50;
            setGeometry(x, y, palette_width, 400);
        }
    }

    void populateItems(
        QAbstractItemModel*    model,
        QSortFilterProxyModel* proxy_model = nullptr) {
        items.clear();
        extractItemsRecursive(model, QModelIndex{}, {}, proxy_model);
        filtered_items = items;
        updateResultsList();
    }

  signals:
    void itemSelected(const QModelIndex& index);

  protected:
    void keyPressEvent(QKeyEvent* event) override {
        auto key = event->key();

        if (key == Qt::Key_Escape) {
            reject();
        } else if (key == Qt::Key_Return || key == Qt::Key_Enter) {
            selectCurrentItem();
        } else if (key == Qt::Key_Down) {
            moveSelection(1);
        } else if (key == Qt::Key_Up) {
            moveSelection(-1);
        } else {
            if (!search_input->hasFocus()) { search_input->setFocus(); }
            QDialog::keyPressEvent(event);
        }
    }

  private slots:
    void onSearchChanged(const QString& text) {
        if (text.trimmed().isEmpty()) {
            filtered_items = items;
        } else {
            filtered_items = filterAndScoreItems(
                text.toLower().toStdString());
        }
        updateResultsList();
    }

    void onItemActivated(QListWidgetItem* item) {
        auto item_data = item->data(Qt::UserRole)
                             .value<CommandPaletteItem*>();
        if (item_data) {
            emit itemSelected(item_data->model_index);
            accept();
        }
    }

  private:
    void moveSelection(int direction) {
        int current_row = results_list->currentRow();
        int new_row     = current_row + direction;

        if (new_row >= 0 && new_row < results_list->count()) {
            results_list->setCurrentRow(new_row);
        }
    }

    void selectCurrentItem() {
        auto current_item = results_list->currentItem();
        if (current_item) { onItemActivated(current_item); }
    }

    void extractItemsRecursive(
        QAbstractItemModel*      model,
        const QModelIndex&       parent_index,
        std::vector<std::string> path,
        QSortFilterProxyModel*   proxy_model) {
        int row_count = model->rowCount(parent_index);

        for (int row = 0; row < row_count; ++row) {
            auto index = model->index(row, 0, parent_index);
            if (!index.isValid()) { continue; }

            auto title = model->data(index, Qt::DisplayRole)
                             .toString()
                             .toStdString();
            auto current_path = path;
            current_path.push_back(title);

            std::string full_path;
            for (size_t i = 0; i < current_path.size(); ++i) {
                if (i > 0) { full_path += " > "; }
                full_path += current_path[i];
            }

            auto display_index = index;
            if (proxy_model) {
                display_index = proxy_model->mapFromSource(index);
            }

            items.emplace_back(title, full_path, display_index);

            extractItemsRecursive(model, index, current_path, proxy_model);
        }
    }

    std::vector<CommandPaletteItem> filterAndScoreItems(
        const std::string& search_text) {
        std::vector<CommandPaletteItem> scored_items;

        for (auto& item : items) {
            double score = calculateScore(item, search_text);
            if (score > 0) {
                item.score = score;
                scored_items.push_back(item);
            }
        }

        std::sort(
            scored_items.begin(),
            scored_items.end(),
            [](const auto& a, const auto& b) {
                if (a.score != b.score) { return a.score > b.score; }
                return a.full_path.length() < b.full_path.length();
            });

        return scored_items;
    }

    double calculateScore(
        const CommandPaletteItem& item,
        const std::string&        search_text) {
        std::string title_lower = item.title;
        std::string path_lower  = item.full_path;
        std::transform(
            title_lower.begin(),
            title_lower.end(),
            title_lower.begin(),
            ::tolower);
        std::transform(
            path_lower.begin(),
            path_lower.end(),
            path_lower.begin(),
            ::tolower);

        if (search_text == title_lower) { return 100.0; }

        if (title_lower.starts_with(search_text)) { return 90.0; }

        if (title_lower.find(search_text) != std::string::npos) {
            return 80.0;
        }

        if (path_lower.find(search_text) != std::string::npos) {
            return 70.0;
        }

        double title_ratio = calculateSimilarity(search_text, title_lower);
        double path_ratio  = calculateSimilarity(search_text, path_lower);
        double fuzzy_score = std::max(title_ratio, path_ratio) * 60.0;

        return fuzzy_score > 20.0 ? fuzzy_score : 0.0;
    }

    double calculateSimilarity(
        const std::string& a,
        const std::string& b) {
        if (a.empty() && b.empty()) { return 1.0; }
        if (a.empty() || b.empty()) { return 0.0; }

        std::vector<std::vector<int>> dp(
            a.length() + 1, std::vector<int>(b.length() + 1));

        for (size_t i = 0; i <= a.length(); ++i) { dp[i][0] = i; }
        for (size_t j = 0; j <= b.length(); ++j) { dp[0][j] = j; }

        for (size_t i = 1; i <= a.length(); ++i) {
            for (size_t j = 1; j <= b.length(); ++j) {
                if (a[i - 1] == b[j - 1]) {
                    dp[i][j] = dp[i - 1][j - 1];
                } else {
                    dp[i][j] = 1
                             + std::min(
                                   {dp[i - 1][j],
                                    dp[i][j - 1],
                                    dp[i - 1][j - 1]});
                }
            }
        }

        int max_len = std::max(a.length(), b.length());
        return 1.0
             - static_cast<double>(dp[a.length()][b.length()]) / max_len;
    }

    void updateResultsList() {
        results_list->clear();

        for (const auto& item : filtered_items) {
            auto list_item = new QListWidgetItem{};
            list_item->setText(QString::fromStdString(item.full_path));
            list_item->setData(
                Qt::UserRole,
                QVariant::fromValue(
                    const_cast<CommandPaletteItem*>(&item)));

            if (!search_input->text().trimmed().isEmpty()) {
                std::string search_text = search_input->text()
                                              .toLower()
                                              .toStdString();
                std::string title_lower = item.title;
                std::transform(
                    title_lower.begin(),
                    title_lower.end(),
                    title_lower.begin(),
                    ::tolower);

                if (title_lower.find(search_text) != std::string::npos) {
                    auto font = list_item->font();
                    font.setBold(true);
                    list_item->setFont(font);
                }
            }

            results_list->addItem(list_item);
        }

        if (results_list->count() > 0) { results_list->setCurrentRow(0); }
    }

    QLineEdit*                      search_input;
    QListWidget*                    results_list;
    std::vector<CommandPaletteItem> items;
    std::vector<CommandPaletteItem> filtered_items;
};

Q_DECLARE_METATYPE(CommandPaletteItem*)


class TreeViewWithCommandPalette : public QObject {
    Q_OBJECT

  public:
    TreeViewWithCommandPalette(
        QTreeView*         tree_view,
        OrgTreeModel*      model,
        OrgTreeProxyModel* proxy_model = nullptr)
        : tree_view{tree_view}
        , model{model}
        , proxy_model{proxy_model}
        , command_palette{nullptr} {

        shortcut = new QShortcut{QKeySequence{"Ctrl+P"}, tree_view};
        connect(
            shortcut,
            &QShortcut::activated,
            this,
            &TreeViewWithCommandPalette::showCommandPalette);
    }

    void showCommandPalette() {
        if (!command_palette) {
            command_palette = new CommandPalette{tree_view};
            connect(
                command_palette,
                &CommandPalette::itemSelected,
                this,
                &TreeViewWithCommandPalette::onItemSelected);
        }

        auto source_model = proxy_model ? proxy_model->sourceModel()
                                        : model;
        command_palette->populateItems(source_model, proxy_model);

        command_palette->positionOverParent();
        command_palette->exec();
        command_palette->raise();
        command_palette->activateWindow();
    }

  private slots:
    void onItemSelected(const QModelIndex& model_index) {
        if (model_index.isValid()) {
            tree_view->scrollTo(model_index);
            tree_view->setCurrentIndex(model_index);

            auto parent = model_index.parent();
            while (parent.isValid()) {
                tree_view->expand(parent);
                parent = parent.parent();
            }

            tree_view->scrollTo(model_index);
            tree_view->setFocus();
        }
    }

  private:
    QTreeView*         tree_view;
    OrgTreeModel*      model;
    OrgTreeProxyModel* proxy_model;
    CommandPalette*    command_palette;
    QShortcut*         shortcut;
};

class AgendaWidget : public QWidget {
    Q_OBJECT

  public:
    explicit AgendaWidget(OrgAgendaNode* root_node) : QWidget{} {
        model = new OrgTreeModel{root_node};
        setupUi();
    }

  private slots:
    void onModelReset() {
        if (!model->isFlatSorting()) { tree_view->expandAll(); }
    }

    void onFocusLifted() { model->setFocused(nullptr); }

    void onRowFocused(const QModelIndex& index) {
        if (!index.isValid()) { return; }

        QModelIndex source_index;
        if (index.model() == sort_model) {
            source_index = sort_model->mapToSource(index);
        } else {
            source_index = index;
        }

        auto node = static_cast<OrgAgendaNode*>(
            source_index.internalPointer());
        model->setFocused(node);
    }

    void onHideCompletedTasks(bool state) {
        sort_model->hide_completed_tasks = state;
        sort_model->invalidate();
    }

    void onHideTasksWithoutTodoOnFlatChanged(bool state) {
        sort_model->hide_tasks_without_todo_on_flat = state;
        sort_model->invalidate();
    }

    void onHideNested(bool state) {
        sort_model->hide_nested = state;
        sort_model->invalidate();
        tree_view->expandAll();
    }

  private:
    void setupUi() {
        auto layout = new QVBoxLayout{};

        tree_view  = new QTreeView{};
        sort_model = new OrgTreeProxyModel{this, model};
        sort_model->setSourceModel(model);
        tree_view->setModel(sort_model);
        tree_view->setAlternatingRowColors(true);
        tree_view->setSortingEnabled(true);
        connect(
            tree_view->model(),
            &QAbstractItemModel::modelReset,
            this,
            &AgendaWidget::onModelReset);

        command_palette_handler = new TreeViewWithCommandPalette{
            tree_view, model, sort_model};

        connect(
            tree_view,
            &QTreeView::doubleClicked,
            this,
            &AgendaWidget::onRowFocused);

        auto header = tree_view->header();
        for (int i = 0; i < static_cast<int>(TableColumns::TAGS) + 1;
             ++i) {
            header->setSectionResizeMode(i, QHeaderView::ResizeToContents);
        }

        auto configuration_layout = new QFormLayout{};
        configuration_layout->setContentsMargins(0, 0, 0, 0);
        auto configuration_widget = new QWidget{};
        configuration_widget->setContentsMargins(0, 0, 0, 0);
        configuration_widget->setLayout(configuration_layout);

        auto hide_tasks_without_todo_on_flat = new QCheckBox{};
        hide_tasks_without_todo_on_flat->setText(
            "Hide tasks without todo");
        connect(
            hide_tasks_without_todo_on_flat,
            &QCheckBox::toggled,
            this,
            &AgendaWidget::onHideTasksWithoutTodoOnFlatChanged);
        hide_tasks_without_todo_on_flat->setToolTip(
            "If enabled, flat sorting operations (priority, todo, "
            "creation date, task age etc.) "
            "will not show the rows that have no creation date.");
        configuration_layout->addWidget(hide_tasks_without_todo_on_flat);

        auto hide_completed_task = new QCheckBox{};
        hide_completed_task->setText("Hide completed tasks");
        connect(
            hide_completed_task,
            &QCheckBox::toggled,
            this,
            &AgendaWidget::onHideCompletedTasks);
        configuration_layout->addWidget(hide_completed_task);

        auto hide_nested = new QCheckBox{};
        hide_nested->setText("Hide nested");
        connect(
            hide_nested,
            &QCheckBox::toggled,
            this,
            &AgendaWidget::onHideNested);
        configuration_layout->addWidget(hide_nested);

        auto unfocus = new QPushButton{};
        unfocus->setText("Unfocus");
        connect(
            unfocus,
            &QPushButton::clicked,
            this,
            &AgendaWidget::onFocusLifted);
        configuration_layout->addWidget(unfocus);

        layout->addWidget(tree_view);
        layout->addWidget(configuration_widget);
        setLayout(layout);

        setWindowTitle("Org Agenda");
        resize(1400, 600);
        tree_view->expandAll();
    }

    OrgTreeModel*               model;
    QTreeView*                  tree_view;
    OrgTreeProxyModel*          sort_model;
    TreeViewWithCommandPalette* command_palette_handler;
};

#include "file_agenda_table.moc"
