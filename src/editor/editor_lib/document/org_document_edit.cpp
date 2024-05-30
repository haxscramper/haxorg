#include <editor/editor_lib/document/org_document_edit.hpp>
#include <editor/editor_lib/document/org_document_model.hpp>
#include <editor/editor_lib/document/org_document_render.hpp>
#include <editor/editor_lib/common/app_utils.hpp>

OrgDocumentEdit::OrgDocumentEdit(
    OrgStore*         store,
    OrgDocumentModel* model,
    QWidget*          parent)
    : QTreeView(parent)
    , docModel(model)
//
{
    if (model != nullptr) {
        filter             = new OrgDocumentSearchFilter(model, this);
        filter->acceptNode = [this, store](OrgBoxId id) -> bool {
            return store->getBoxedNode(id)->getKind() != OrgSemKind::Newline;
        };

        setModel(filter);
    }

    this->setItemDelegate(new OrgEditItemDelegate(store, this));
    this->setSelectionMode(QAbstractItemView::SingleSelection);
    this->setDragEnabled(true);
    this->setAcceptDrops(true);
    this->setDropIndicatorShown(true);
    this->setDragDropMode(QAbstractItemView::InternalMove);
}

void OrgDocumentEdit::focusOn(QModelIndex index) {
    if (index.isValid()) {
        auto mapped = mapToNestedProxy(index, {filter});
        this->scrollTo(mapped);
        emit this->focusedOn(mapped);
    }
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


QWidget* OrgEditItemDelegate::createEditor(
    QWidget*                    parent,
    const QStyleOptionViewItem& option,
    const QModelIndex&          index) const {
    if (index.column() == 0) {
        auto res = new QTextEdit(parent);
        res->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        res->setContentsMargins(0, 0, 0, 0);
        res->document()->setDocumentMargin(0);
        res->setStyleSheet("QTextEdit { border: none; }");
        res->setObjectName("OrgEditDelegateActive");
        return res;
    } else {
        return QStyledItemDelegate::createEditor(parent, option, index);
    }
}

void OrgEditItemDelegate::paint(
    QPainter*                   painter,
    const QStyleOptionViewItem& option,
    const QModelIndex&          index) const {
    SPtr<QWidget> widget = make_render(store->getBoxedNode(box(index)));
    if (widget) {
        draw(widget.get(), painter, option, index);
    } else {
        QStyledItemDelegate::paint(painter, option, index);
    }
}

OrgBoxId OrgEditItemDelegate::box(const QModelIndex& index) const {
    return qvariant_cast<OrgBoxId>(
        index.model()->data(index, Qt::DisplayRole));
}

void OrgEditItemDelegate::setEditorData(
    QWidget*           editor,
    const QModelIndex& index) const {
    OrgBoxId id   = qvariant_cast<OrgBoxId>(index.data(Qt::EditRole));
    auto     node = store->getBoxedNode(id);
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

void OrgEditItemDelegate::setModelData(
    QWidget*            editor,
    QAbstractItemModel* model,
    const QModelIndex&  index) const {
    QTextEdit* edit = qobject_cast<QTextEdit*>(editor);
    model->setData(index, edit->toPlainText(), Qt::EditRole);
}

QSize OrgEditItemDelegate::sizeHint(
    const QStyleOptionViewItem& option,
    const QModelIndex&          index) const {
    if (index.isValid()) {
        SPtr<QWidget> widget = make_render(store->getBoxedNode(box(index)));
        return get_width_fit(widget.get(), parent());
    } else {
        return QStyledItemDelegate::sizeHint(option, index);
    }
}
