#include "org_document_edit.hpp"
#include "org_document_model.hpp"

OrgDocumentEdit::OrgDocumentEdit(OrgDocumentModel* model, QWidget* parent)
    : QTreeView(parent) {
    setModel(model);
    this->setItemDelegate(new OrgNodeEditWidget(this));
}

void OrgNodeEditWidget::paint(
    QPainter*                   painter,
    const QStyleOptionViewItem& option,
    const QModelIndex&          index) const {
    SPtr<QWidget> widget = qvariant_cast<SPtr<QWidget>>(
        index.data(Qt::DisplayRole));
    if (widget) {
        widget->setGeometry(option.rect);
        widget->setSizePolicy(
            QSizePolicy::Expanding, QSizePolicy::Expanding);
        QPixmap pixmap(widget->size());
        widget->render(&pixmap);
        painter->drawPixmap(option.rect.topLeft(), pixmap);
    } else {
        QStyledItemDelegate::paint(painter, option, index);
    }
}
