#pragma once

#include <QTreeView>
#include <editor/editor_lib/document/org_document_model.hpp>
#include <QStyledItemDelegate>
#include <QLineEdit>
#include <QPainter>
#include <QLabel>
#include <QTextEdit>
#include <haxorg/sem/SemBaseApi.hpp>

struct OrgEditItemDelegate : public QStyledItemDelegate {
    OrgStore* store;
    OrgEditItemDelegate(OrgStore* store, QWidget* parent)
        : QStyledItemDelegate(parent), store(store) {}

    QWidget* createEditor(
        QWidget*                    parent,
        const QStyleOptionViewItem& option,
        const QModelIndex&          index) const override;

    void paint(
        QPainter*                   painter,
        const QStyleOptionViewItem& option,
        const QModelIndex&          index) const override;

    OrgBoxId box(QModelIndex const& index) const;

    void setEditorData(QWidget* editor, const QModelIndex& index)
        const override;

    void setModelData(
        QWidget*            editor,
        QAbstractItemModel* model,
        const QModelIndex&  index) const override;

    void updateEditorGeometry(
        QWidget*                    editor,
        const QStyleOptionViewItem& option,
        const QModelIndex&          index) const override {
        editor->setGeometry(option.rect);
    }

    QSize sizeHint(
        const QStyleOptionViewItem& option,
        const QModelIndex&          index) const override;

    int getNestingLevel(const QModelIndex& index) const {
        int         level   = 0;
        QModelIndex current = index;
        while (current.parent().isValid()) {
            level++;
            current = current.parent();
        }
        return level;
    }
};

class OrgDocumentEdit : public QTreeView {
    Q_OBJECT
  public:
    OrgDocumentModel*        docModel;
    OrgDocumentSearchFilter* filter;
    OrgDocumentEdit(
        OrgStore*         store,
        OrgDocumentModel* model,
        QWidget*          parent);

  signals:
    void focusedOn(QModelIndex index);

  public slots:
    void focusOn(QModelIndex index);

    void movePositionUp(QModelIndex index, int offset) {
        docModel->changePosition(filter->mapToSource(index), -offset);
    }

    void movePositionDown(QModelIndex index, int offset) {
        docModel->changePosition(filter->mapToSource(index), offset);
    }

    void demoteSubtreeSingle(QModelIndex index, int levels = 1) {
        docModel->changeLevel(filter->mapToSource(index), levels, false);
    }

    void promoteSubtreeSingle(QModelIndex index, int levels = 1) {
        docModel->changeLevel(filter->mapToSource(index), -levels, false);
    }

    void demoteSubtreeRecursive(QModelIndex index, int levels = 1) {
        docModel->changeLevel(filter->mapToSource(index), levels, true);
    }

    void promoteSubtreeRecursive(QModelIndex index, int levels = 1) {
        docModel->changeLevel(filter->mapToSource(index), -levels, true);
    }
};
