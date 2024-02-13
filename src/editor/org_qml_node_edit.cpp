#include "org_qml_node_edit.hpp"
#include <lexbor/html/parser.h>
#include <lexbor/html/interface.h>
#include <lexbor/html/node.h>
#include <lexbor/html/serialize.h>
#include "exporterhtml.hpp"

using LxbDoc = SPtr<lxb_html_document_t>;
using namespace sem;

LxbDoc parseHtmlFragmentToLxb(const QString& html) {
    QByteArray result   = html.toUtf8();
    LxbDoc     document = LxbDoc{
        lxb_html_document_create(),
        lxb_html_document_destroy,
    };

    if (document == nullptr) { LOG(FATAL) << "Cannot create"; }

    const lexbor_str_t lxb_html = lexbor_str(result.constData());
    lxb_status_t       status   = lxb_html_document_parse(
        document.get(), lxb_html.data, lxb_html.length);

    if (status != LXB_STATUS_OK) { LOG(FATAL) << "Cannot parse"; }

    return document;
}

void printHtmlStructure(lxb_dom_node_t* node, int depth = 0) {
    if (node == nullptr) { return; }
    std::cout << std::string(depth * 2, ' ');

    switch (node->type) {
        case LXB_DOM_NODE_TYPE_ELEMENT: {
            auto           element  = lxb_dom_interface_element(node);
            CP<lxb_char_t> tag_name = lxb_dom_element_qualified_name(
                element, nullptr);

            std::cout << "<element> "
                      << std::string(
                             reinterpret_cast<const char*>(tag_name));
            break;
        }
        case LXB_DOM_NODE_TYPE_TEXT: {
            auto           text = lxb_dom_interface_text(node);
            std::size_t    len{};
            CP<lxb_char_t> text_content = lxb_dom_node_text_content(
                node, &len);
            std::cout << "<text> "
                      << std::string(
                             reinterpret_cast<const char*>(text_content));
        }
        default: {
            std::cout << fmt1(node->type);
        }
    }

    std::cout << "\n";


    // Recursively iterate over sub nodes
    lxb_dom_node_t* sub = node->first_child;
    while (sub != nullptr) {
        printHtmlStructure(sub, depth + 1);
        sub = sub->next;
    }
}

void OrgNodeTextWrapper::setRichText(const QString& value) {
    LxbDoc doc = parseHtmlFragmentToLxb(value);
    printHtmlStructure(lxb_dom_interface_node(doc.get()));
}

QString OrgNodeTextWrapper::getRichText() {
    ExporterHtml    exp;
    layout::BlockId block  = exp.evalTop(cursor->node);
    Str             result = exp.store.toString(block);
    return QString::fromStdString(result);
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
