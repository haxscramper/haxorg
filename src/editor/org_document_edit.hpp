#pragma once

#include <QTreeView>
#include <editor/org_document_model.hpp>
#include <QStyledItemDelegate>
#include <QLineEdit>
#include <QPainter>
#include <QLabel>
#include <QTextEdit>
#include <sem/SemBaseApi.hpp>

struct OrgNodeEditWidget : public QStyledItemDelegate {
    OrgStore* store;
    OrgNodeEditWidget(OrgStore* store, QWidget* parent)
        : QStyledItemDelegate(parent), store(store) {}

    QWidget* createEditor(
        QWidget*                    parent,
        const QStyleOptionViewItem& option,
        const QModelIndex&          index) const override {
        if (index.column() == 0) {
            auto res = new QTextEdit(parent);
            res->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
            return res;
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
        const override {
        OrgBoxId id   = qvariant_cast<OrgBoxId>(index.data(Qt::EditRole));
        auto     node = store->node(id);
        switch (node->getKind()) {
            case OrgSemKind::Paragraph: {
                QTextEdit* edit = qobject_cast<QTextEdit*>(editor);
                edit->setText(
                    QString::fromStdString(sem::formatToString(node)));
                break;
            }
            default: {
            }
        }
    }

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
        if (index.isValid()) {
            QVariant var = index.data(Qt::DisplayRole);
            Q_ASSERT(var.isValid());
            SPtr<QWidget> widget = qvariant_cast<SPtr<QWidget>>(var);
            Q_ASSERT(widget);
            widget->setFixedWidth(
                qobject_cast<QWidget*>(parent())->width()
                - (getNestingLevel(index) * 20));
            QSize size = widget->sizeHint();
            size.setHeight(size.height() + 20);
            return size;
        } else {
            return QStyledItemDelegate::sizeHint(option, index);
        }
    }

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

struct OrgDocumentEdit : public QTreeView {
    OrgDocumentEdit(
        OrgStore*           store,
        QAbstractItemModel* model,
        QWidget*            parent);
};
