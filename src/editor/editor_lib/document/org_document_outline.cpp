#include "org_document_outline.hpp"
#include "org_document_render.hpp"
#include <QPainter>
#include <QStandardItemModel>
#include <QStyledItemDelegate>
#include <QMouseEvent>
#include <editor/editor_lib/common/app_utils.hpp>


void OrgOutlineItemDelegate::paint(
    QPainter*                   painter,
    const QStyleOptionViewItem& option,
    const QModelIndex&          index) const {
    auto node = store->getBoxedNode(qvariant_cast<OrgBoxId>(index.data()));
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
    expandRecursively(rootIndex());
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

QSize OrgOutlineItemDelegate::sizeHint(
    const QStyleOptionViewItem& option,
    const QModelIndex&          index) const {
    if (index.isValid()) {
        OrgBoxId box = qvariant_cast<OrgBoxId>(
            index.data(Qt::DisplayRole));
        SPtr<QWidget> widget = make_render(store->getBoxedNode(box));
        return get_width_fit(widget.get(), parent());
    } else {
        return QStyledItemDelegate::sizeHint(option, index);
    }
}

bool OrgOutlineItemDelegate::editorEvent(
    QEvent*                     event,
    QAbstractItemModel*         model,
    const QStyleOptionViewItem& option,
    const QModelIndex&          index) {
    if (event->type() == QEvent::MouseButtonDblClick) {
        QMouseEvent* mouseEvent = static_cast<QMouseEvent*>(event);
        if (mouseEvent->button() == Qt::LeftButton) {
            emit qobject_cast<OrgDocumentOutline*>(parent())
                ->outlineFocusRequested(mapToNestedSource(index));
            return true;
        } else {
            return false;
        }
    } else {
        return QStyledItemDelegate::editorEvent(
            event, model, option, index);
    }
}


OrgDocumentOutline::OrgDocumentOutline(OrgStore* store, QWidget* parent)
    : QTreeView(parent)
    , store(store)
//
{
    this->setItemDelegate(new OrgOutlineItemDelegate(store, this));
}
