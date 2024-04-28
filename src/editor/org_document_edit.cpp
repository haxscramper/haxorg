#include "org_document_edit.hpp"
#include "org_document_model.hpp"
#include "org_exporter_html.hpp"

OrgDocumentEdit::OrgDocumentEdit(
    OrgStore*           store,
    QAbstractItemModel* model,
    QWidget*            parent)
    : QTreeView(parent) {
    setModel(model);
    this->setItemDelegate(new OrgNodeEditWidget(store, this));
    this->setSelectionMode(QAbstractItemView::SingleSelection);
    this->setDragEnabled(true);
    this->setAcceptDrops(true);
    this->setDropIndicatorShown(true);
    this->setDragDropMode(QAbstractItemView::InternalMove);
}

SPtr<QWidget> make_label(Str const& node) {
    auto label = std::make_shared<QLabel>();
    label->setText(QString::fromStdString(node));
    label->setWordWrap(true);
    label->setStyleSheet("QLabel { background-color : white; }");
    return label;
}


SPtr<QWidget> make_label(sem::OrgArg node) {
    ExporterHtml exp;
    auto         html_tree = exp.evalTop(node);
    return make_label(exp.store.toString(html_tree));
}

SPtr<QWidget> make_render(sem::OrgArg node) {
    switch (node->getKind()) {
        case OrgSemKind::Subtree:
            return make_label(node.as<sem::Subtree>()->title);
        case OrgSemKind::AnnotatedParagraph:
        case OrgSemKind::Paragraph: return make_label(node);
        default: return make_label(fmt1(node->getKind()));
    }
}

void OrgNodeEditWidget::paint(
    QPainter*                   painter,
    const QStyleOptionViewItem& option,
    const QModelIndex&          index) const {
    SPtr<QWidget> widget = make_render(store->node(box(index)));
    if (widget) {
        widget->setGeometry(option.rect);
        widget->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
        QPixmap pixmap(widget->size());
        widget->render(&pixmap);
        painter->drawPixmap(option.rect.topLeft(), pixmap);
        widget->deleteLater();
    } else {
        QStyledItemDelegate::paint(painter, option, index);
    }
}

OrgBoxId OrgNodeEditWidget::box(const QModelIndex& index) const {
    return qvariant_cast<OrgBoxId>(
        index.model()->data(index, Qt::DisplayRole));
}

QSize OrgNodeEditWidget::sizeHint(
    const QStyleOptionViewItem& option,
    const QModelIndex&          index) const {
    if (index.isValid()) {
        SPtr<QWidget> widget = make_render(store->node(box(index)));
        Q_ASSERT(widget);
        widget->setFixedWidth(
            qobject_cast<QWidget*>(parent())->width()
            - (getNestingLevel(index) * 20));
        QSize size = widget->sizeHint();
        widget->deleteLater();
        return size;
    } else {
        return QStyledItemDelegate::sizeHint(option, index);
    }
}
