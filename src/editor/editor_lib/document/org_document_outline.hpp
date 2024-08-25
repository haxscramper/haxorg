#pragma once
#include <QTreeView>
#include "org_document_model.hpp"
#include <QStyledItemDelegate>
#include <QTextEdit>
#include <haxorg/sem/SemBaseApi.hpp>


class OrgDocumentOutline;

struct OrgOutlineItemDelegate : public QStyledItemDelegate {
    OrgStore* store;
    OrgOutlineItemDelegate(OrgStore* store, QWidget* parent)
        : QStyledItemDelegate(parent), store(store) {}

    void paint(
        QPainter*                   painter,
        const QStyleOptionViewItem& option,
        const QModelIndex&          index) const override;

    QSize sizeHint(
        const QStyleOptionViewItem& option,
        const QModelIndex&          index) const override;

    virtual bool editorEvent(
        QEvent*                     event,
        QAbstractItemModel*         model,
        const QStyleOptionViewItem& option,
        const QModelIndex&          index) override;
};

class OrgDocumentOutline : public QTreeView {
    Q_OBJECT
  public:
    SPtr<OrgSubtreeSearchModel> filter;
    OrgStore*                   store;
    void setFilter(SPtr<OrgSubtreeSearchModel> model);
    OrgDocumentOutline(OrgStore* store, QWidget* parent);

  signals:
    void outlineFocusRequested(QModelIndex index);
};
