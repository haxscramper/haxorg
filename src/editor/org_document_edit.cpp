#include "org_document_edit.hpp"
#include "org_document_model.hpp"
#include <kdescendantsproxymodel.h>
#include <QVBoxLayout>
#include <QScrollArea>

QAbstractItemModel* OrgDocumentEdit::model() { return flatProxy.get(); }

OrgDocumentEdit::OrgDocumentEdit(
    OrgStore*           store,
    QAbstractItemModel* model,
    QWidget*            parent)
    : baseModel(model)
    , flatProxy(new KDescendantsProxyModel(this))
    , layout(new QVBoxLayout())
//
{
    flatProxy->setSourceModel(model);
    auto mainLayout = new QVBoxLayout();
    this->setLayout(mainLayout);
    auto scroll = new QScrollArea(this);
    scroll->setWidgetResizable(true);
    mainLayout->addWidget(scroll);
    scroll->setLayout(layout.get());
    layout->setContentsMargins(0, 0, 0, 0);
    populateList();

    connect(
        model,
        &QAbstractItemModel::rowsInserted,
        this,
        &OrgDocumentEdit::onRowsInserted);
    connect(
        model,
        &QAbstractItemModel::rowsRemoved,
        this,
        &OrgDocumentEdit::onRowsRemoved);
}

void OrgDocumentEdit::populateList() {
    for (int row = 0; row < model()->rowCount(); ++row) {
        layout->addWidget(getWidget(model()->index(row, 0)));
    }
}

QWidget* OrgDocumentEdit::getWidget(CR<QModelIndex> index) {
    QWidget* widget = qvariant_cast<QWidget*>(
        flatProxy->data(index, Qt::DisplayRole));
    Q_ASSERT(widget);
    widget->setParent(this);
    widget->setVisible(true);
    return widget;
}


void OrgDocumentEdit::onRowsInserted(
    const QModelIndex& parent,
    int                first,
    int                last) {
    for (int row = first; row <= last; ++row) {
        layout->insertWidget(row, getWidget(model()->index(row, 0)));
    }
}

void OrgDocumentEdit::onRowsRemoved(
    const QModelIndex& parent,
    int                first,
    int                last) {
    for (int i = first; i <= last; ++i) { layout->takeAt(first); }
}
