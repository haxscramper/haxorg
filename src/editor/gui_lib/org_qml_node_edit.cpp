#include "org_qml_node_edit.hpp"

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
