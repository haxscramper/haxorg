#include "org_document_edit.hpp"

OrgDocumentEdit::OrgDocumentEdit(OrgDocumentModel* model, QWidget* parent)
    : QTreeView(parent) {
    setModel(model);
}
