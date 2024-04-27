#pragma once

#include <QTreeView>
#include <editor/org_document_model.hpp>
#include <QStyledItemDelegate>
#include <QLineEdit>

class TreeWidgetSetup : public QObject {
    Q_OBJECT

  public:
    TreeWidgetSetup(QTreeView* treeView, QObject* parent = nullptr)
        : QObject(parent), view(treeView) {
        connect(
            view->model(),
            &QAbstractItemModel::rowsInserted,
            this,
            &TreeWidgetSetup::updateWidgets);
        connect(
            view->model(),
            &QAbstractItemModel::modelReset,
            this,
            &TreeWidgetSetup::updateWidgets);
    }

    void updateWidgets(
        const QModelIndex& parent = QModelIndex(),
        int                first  = 0,
        int                last   = -1) {
        if (!view || !view->model()) { return; }

        if (last == -1) { last = view->model()->rowCount(parent) - 1; }

        for (int row = first; row <= last; ++row) {
            QModelIndex index = view->model()->index(row, 0, parent);
            setCustomWidget(index);
            if (view->model()->hasChildren(index)) {
                updateWidgets(index);
            }
        }
    }

  private:
    QTreeView* view;

    void setCustomWidget(const QModelIndex& index) {
        QLineEdit* lineEdit = new QLineEdit(view);
        lineEdit->setText(QString("Item %1").arg(index.row() + 1));
        view->setIndexWidget(index, lineEdit);
    }
};

struct OrgNodeEditWidget : public QStyledItemDelegate {
    OrgNodeEditWidget(QObject* parent = nullptr)
        : QStyledItemDelegate(parent) {}

    QWidget* createEditor(
        QWidget*                    parent,
        const QStyleOptionViewItem& option,
        const QModelIndex&          index) const override {
        if (index.column() == 0) {
            QLineEdit* editor = new QLineEdit(parent);
            return editor;
        } else {
            return QStyledItemDelegate::createEditor(
                parent, option, index);
        }
    }

    void setEditorData(QWidget* editor, const QModelIndex& index)
        const override {}

    void setModelData(
        QWidget*            editor,
        QAbstractItemModel* model,
        const QModelIndex&  index) const override {}

    void updateEditorGeometry(
        QWidget*                    editor,
        const QStyleOptionViewItem& option,
        const QModelIndex&          index) const override {
        editor->setGeometry(option.rect);
    }
};

struct OrgDocumentEdit : public QTreeView {
    OrgDocumentEdit(OrgDocumentModel* model, QWidget* parent);
};
