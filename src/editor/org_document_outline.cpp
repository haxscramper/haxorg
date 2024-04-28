#include "org_document_outline.hpp"
#include "org_document_render.hpp"
#include <QPainter>

void OrgOutlineItemDelegate::paint(
    QPainter*                   painter,
    const QStyleOptionViewItem& option,
    const QModelIndex&          index) const {
    auto tree = static_cast<OrgDocumentModel::TreeNode*>(
        index.internalPointer());
    auto node = store->node(tree->boxId);
    if (node->is(OrgSemKind::Subtree)) {
        auto widget = make_label(node.as<sem::Subtree>()->title);
        draw(widget.get(), painter, option, index);
    } else {
        painter->drawText(
            QPoint(0, 0), QString::fromStdString(fmt1(node->getKind())));
    }
}

void OrgDocumentOutline::setFilter(SPtr<OrgSubtreeSearchModel> model) {
    filter = model;
    setModel(filter.get()->filter.get());
    setItemDelegate(new OrgOutlineItemDelegate(store, this));
}

// QSize OrgOutlineItemDelegate::sizeHint(
//     const QStyleOptionViewItem& option,
//     const QModelIndex&          index) const {
//     if (index.isValid()) {
//         auto tree = static_cast<OrgDocumentModel::TreeNode*>(
//             index.internalPointer());
//         SPtr<QWidget> widget = make_label(store->node(tree->boxId));
//         return get_width_fit(widget.get(), parent());
//     } else {
//         return QStyledItemDelegate::sizeHint(option, index);
//     }
// }


OrgDocumentOutline::OrgDocumentOutline(
    OrgStore*         store,
    OrgDocumentModel* model,
    QWidget*          parent)
    : QTreeView(parent)
    , docModel(model)
    , store(store)
//
{
    if (model != nullptr) {
        auto filter        = new OrgDocumentSearchFilter(model, this);
        filter->acceptNode = [this, store](OrgBoxId id) -> bool {
            return store->node(id)->getKind() != OrgSemKind::Newline;
        };

        setModel(filter);
    }

    this->setItemDelegate(new OrgOutlineItemDelegate(store, this));
    this->setSelectionMode(QAbstractItemView::SingleSelection);
    this->setDragEnabled(true);
    this->setAcceptDrops(true);
    this->setDropIndicatorShown(true);
    this->setDragDropMode(QAbstractItemView::InternalMove);
}

namespace {
SPtr<QWidget> make_render(sem::OrgArg node) {
    switch (node->getKind()) {
        case OrgSemKind::Subtree:
            return make_label(node.as<sem::Subtree>()->title);
        case OrgSemKind::AnnotatedParagraph:
        case OrgSemKind::Paragraph: return make_label(node);
        default: return make_label(fmt1(node->getKind()));
    }
}
} // namespace


// void OrgOutlineItemDelegate::paint(
//     QPainter*                   painter,
//     const QStyleOptionViewItem& option,
//     const QModelIndex&          index) const {
//     SPtr<QWidget> widget = make_render(store->node(box(index)));
//     if (widget) {
//         draw(widget.get(), painter, option, index);
//     } else {
//         QStyledItemDelegate::paint(painter, option, index);
//     }
// }

OrgBoxId OrgOutlineItemDelegate::box(const QModelIndex& index) const {
    return qvariant_cast<OrgBoxId>(
        index.model()->data(index, Qt::DisplayRole));
}

QSize OrgOutlineItemDelegate::sizeHint(
    const QStyleOptionViewItem& option,
    const QModelIndex&          index) const {
    if (index.isValid()) {
        SPtr<QWidget> widget = make_render(store->node(box(index)));
        return get_width_fit(widget.get(), parent());
    } else {
        return QStyledItemDelegate::sizeHint(option, index);
    }
}
