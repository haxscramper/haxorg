#include "org_qml_node_edit.hpp"
#include "exporter_qtextdocument.hpp"

void OrgNodeTextWrapper::setRichText(const QString& value) {
    if (cursor->node->is(OrgSemKind::Word)) {
        cursor->node.getAs<sem::Word>()->text = to_std(value);
    }
}

QString OrgNodeTextWrapper::getRichText() {
    ExporterQTextDocument exp;
    exp.evalTop(cursor->node);
    return exp.document->toHtml();
}

QVariant OrgNodeCursor::getNodeHandle() {
    switch (node->getKind()) {
#define _case(__Kind)                                                     \
    case OrgSemKind::__Kind:                                              \
        return QVariant::fromValue(                                       \
            org_qml::serde<org_qml::__Kind, sem::SemId<sem::__Kind>>::    \
                cxx_to_qml(node.as<sem::__Kind>()));

        EACH_SEM_ORG_KIND(_case)
#undef _case
    }
}
