#pragma once

#include <QTreeView>
#include <editor/org_document_model.hpp>
#include <QStyledItemDelegate>
#include <QLineEdit>
#include <QPainter>
#include <QLabel>

struct OrgNodeEditWidget : public QStyledItemDelegate {
    OrgNodeEditWidget(QObject* parent) : QStyledItemDelegate(parent) {}

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

    void paint(
        QPainter*                   painter,
        const QStyleOptionViewItem& option,
        const QModelIndex&          index) const override;

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

    QSize sizeHint(
        const QStyleOptionViewItem& option,
        const QModelIndex&          index) const override {
        QWidget* widget = qvariant_cast<QWidget*>(
            index.data(Qt::DisplayRole));
        if (widget) {
            return widget->sizeHint();
        } else {
            return QStyledItemDelegate::sizeHint(option, index);
        }
    }
};

struct OrgDocumentEdit : public QTreeView {
    OrgDocumentEdit(OrgDocumentModel* model, QWidget* parent);
};
