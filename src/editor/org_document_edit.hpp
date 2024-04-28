#pragma once

#include <QTreeView>
#include <editor/org_document_model.hpp>
#include <QStyledItemDelegate>
#include <QLineEdit>
#include <QPainter>
#include <QLabel>
#include <QTextEdit>
#include <sem/SemBaseApi.hpp>

struct OrgEditItemDelegate : public QStyledItemDelegate {
    OrgStore* store;
    OrgEditItemDelegate(OrgStore* store, QWidget* parent)
        : QStyledItemDelegate(parent), store(store) {}

    QWidget* createEditor(
        QWidget*                    parent,
        const QStyleOptionViewItem& option,
        const QModelIndex&          index) const override {
        if (index.column() == 0) {
            auto res = new QTextEdit(parent);
            res->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
            res->setContentsMargins(0, 0, 0, 0);
            res->document()->setDocumentMargin(0);
            res->setStyleSheet("QTextEdit { border: none; }");
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

    OrgBoxId box(QModelIndex const& index) const;

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
        const QModelIndex&  index) const override {
        QTextEdit* edit = qobject_cast<QTextEdit*>(editor);
        model->setData(index, edit->toPlainText(), Qt::EditRole);
    }

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
    OrgDocumentModel* docModel;
    OrgDocumentEdit(
        OrgStore*         store,
        OrgDocumentModel* model,
        QWidget*          parent);

  public slots:
    void focusOn(QModelIndex index);
};
