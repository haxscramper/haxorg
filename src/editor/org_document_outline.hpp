#pragma once
#include <QTreeView>
#include "org_document_model.hpp"
#include <QStyledItemDelegate>
#include <QTextEdit>
#include <sem/SemBaseApi.hpp>


struct OrgOutlineItemDelegate : public QStyledItemDelegate {
    // OrgStore* store;
    // OrgOutlineItemDelegate(OrgStore* store, QWidget* parent)
    //     : QStyledItemDelegate(parent), store(store) {}

    // void paint(
    //     QPainter*                   painter,
    //     const QStyleOptionViewItem& option,
    //     const QModelIndex&          index) const override;

    // QSize sizeHint(
    //     const QStyleOptionViewItem& option,
    //     const QModelIndex&          index) const override;

    OrgStore* store;
    OrgOutlineItemDelegate(OrgStore* store, QWidget* parent)
        : QStyledItemDelegate(parent), store(store) {}

    void paint(
        QPainter*                   painter,
        const QStyleOptionViewItem& option,
        const QModelIndex&          index) const override;

    OrgBoxId box(QModelIndex const& index) const;

    QSize sizeHint(
        const QStyleOptionViewItem& option,
        const QModelIndex&          index) const override;
};

class OrgDocumentOutline : public QTreeView {
    Q_OBJECT
  public:
    SPtr<OrgSubtreeSearchModel> filter;
    OrgStore*                   store;

    //   OrgDocumentOutline(OrgStore* store, QWidget* parent)
    //       : QTreeView(parent)
    //       , store(store)
    //   //
    //   {

    //   }

    void setFilter(SPtr<OrgSubtreeSearchModel> model);

    OrgDocumentModel* docModel;
    OrgDocumentOutline(
        OrgStore*         store,
        OrgDocumentModel* model,
        QWidget*          parent);
};
