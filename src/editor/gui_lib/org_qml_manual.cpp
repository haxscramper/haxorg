#include "org_qml_manual.hpp"
#include "org_qml_manual2.hpp"
#include "exporterhtml.hpp"

#include <lexbor/html/parser.h>
#include <lexbor/html/interface.h>
#include <lexbor/html/node.h>
#include <lexbor/html/serialize.h>
#include <exporters/exportertree.hpp>
#include <exporters/ExporterJson.hpp>
#include <QJsonArray>
#include <QJsonValue>
#include <sem/SemOrgFormat.hpp>

using namespace sem;

using LxbDoc  = SPtr<lxb_html_document_t>;
using LxbNode = lxb_dom_node_t*;

LxbDoc parseHtmlFragmentToLxb(const QString& html) {
    QByteArray result   = html.toUtf8();
    LxbDoc     document = LxbDoc{
        lxb_html_document_create(),
        lxb_html_document_destroy,
    };

    if (document == nullptr) { LOG(FATAL) << "Cannot create"; }

    const lexbor_str_t lxb_html = lexbor_str(result.constData());
    lxb_status_t       status   = lxb_html_document_parse(
        document.get(), lxb_html.data, result.length());

    if (status != LXB_STATUS_OK) { LOG(FATAL) << "Cannot parse"; }

    return document;
}

Vec<LxbNode> getSubnodes(LxbNode node) {
    Vec<LxbNode>    result;
    lxb_dom_node_t* sub = lxb_dom_node_first_child(node);
    while (sub != nullptr) {
        result.push_back(sub);
        sub = lxb_dom_node_next(sub);
    }
    return result;
}

std::string getText(LxbNode node) {
    auto           text = lxb_dom_interface_text(node);
    std::size_t    len{};
    CP<lxb_char_t> text_content = lxb_dom_node_text_content(node, &len);
    return std::string(reinterpret_cast<const char*>(text_content));
}

std::string getTag(LxbNode node) {
    auto           element = lxb_dom_interface_element(node);
    std::size_t    len{};
    CP<lxb_char_t> tag_name = lxb_dom_element_qualified_name(
        element, &len);

    return std::string(reinterpret_cast<const char*>(tag_name));
}

BOOST_DESCRIBE_ENUM(
    lxb_dom_node_type_t,
    LXB_DOM_NODE_TYPE_UNDEF,
    LXB_DOM_NODE_TYPE_ELEMENT,
    LXB_DOM_NODE_TYPE_ATTRIBUTE,
    LXB_DOM_NODE_TYPE_TEXT,
    LXB_DOM_NODE_TYPE_CDATA_SECTION,
    LXB_DOM_NODE_TYPE_ENTITY_REFERENCE,
    LXB_DOM_NODE_TYPE_ENTITY,
    LXB_DOM_NODE_TYPE_PROCESSING_INSTRUCTION,
    LXB_DOM_NODE_TYPE_COMMENT,
    LXB_DOM_NODE_TYPE_DOCUMENT,
    LXB_DOM_NODE_TYPE_DOCUMENT_TYPE,
    LXB_DOM_NODE_TYPE_DOCUMENT_FRAGMENT,
    LXB_DOM_NODE_TYPE_NOTATION,
    LXB_DOM_NODE_TYPE_LAST_ENTRY)

std::string getHtmlTree(LxbNode node) {
    Func<void(LxbNode node, int depth)> aux;
    std::stringstream                   ss;
    aux = [&](LxbNode node, int depth) {
        if (node == nullptr) { return; }
        ss << std::string(depth * 2, ' ');

        switch (node->type) {
            case LXB_DOM_NODE_TYPE_ELEMENT: {
                ss << "<element> " << escape_literal(getTag(node));
                break;
            }
            case LXB_DOM_NODE_TYPE_TEXT: {
                ss << "<text> " << escape_literal(getText(node));
                break;
            }
            case LXB_DOM_NODE_TYPE_UNDEF: {
                ss << "<LXB_DOM_NODE_TYPE_UNDEF>";
                break;
            }
            case LXB_DOM_NODE_TYPE_ATTRIBUTE: {
                ss << "<LXB_DOM_NODE_TYPE_ATTRIBUTE>";
                break;
            }
            case LXB_DOM_NODE_TYPE_CDATA_SECTION: {
                ss << "<LXB_DOM_NODE_TYPE_CDATA_SECTION>";
                break;
            }
            case LXB_DOM_NODE_TYPE_ENTITY_REFERENCE: {
                ss << "<LXB_DOM_NODE_TYPE_ENTITY_REFERENCE>";
                break;
            }
            case LXB_DOM_NODE_TYPE_ENTITY: {
                ss << "<LXB_DOM_NODE_TYPE_ENTITY>";
                break;
            }
            case LXB_DOM_NODE_TYPE_PROCESSING_INSTRUCTION: {
                ss << "<LXB_DOM_NODE_TYPE_PROCESSING_INSTRUCTION>";
                break;
            }
            case LXB_DOM_NODE_TYPE_COMMENT: {
                ss << "<LXB_DOM_NODE_TYPE_COMMENT>";
                break;
            }
            case LXB_DOM_NODE_TYPE_DOCUMENT: {
                ss << "<LXB_DOM_NODE_TYPE_DOCUMENT>";
                break;
            }
            case LXB_DOM_NODE_TYPE_DOCUMENT_TYPE: {
                ss << "<LXB_DOM_NODE_TYPE_DOCUMENT_TYPE>";
                break;
            }
            case LXB_DOM_NODE_TYPE_DOCUMENT_FRAGMENT: {
                ss << "<LXB_DOM_NODE_TYPE_DOCUMENT_FRAGMENT>";
                break;
            }
            case LXB_DOM_NODE_TYPE_NOTATION: {
                ss << "<LXB_DOM_NODE_TYPE_NOTATION>";
                break;
            }
            case LXB_DOM_NODE_TYPE_LAST_ENTRY: {
                ss << "<LXB_DOM_NODE_TYPE_LAST_ENTRY>";
                break;
            }
        }

        ss << "\n";

        for (auto const& sub : getSubnodes(node)) { aux(sub, depth + 1); }
    };

    aux(node, 0);
    return ss.str();
}

Opt<SemId<Org>> toNode(LxbNode node) {
    std::string     tag = getTag(node);
    Opt<SemId<Org>> result;

    auto add = [&](CR<Opt<SemId<Org>>> subOrg) {
        if (subOrg) { (*result)->push_back(subOrg.value()); }
    };

    switch (node->type) {
        case LXB_DOM_NODE_TYPE_ELEMENT: {
            if (tag == "p") {
                result = SemId<Paragraph>::New();
                for (auto const& sub : getSubnodes(node)) {
                    if (sub->type == LXB_DOM_NODE_TYPE_TEXT) {
                        Str  text    = getText(sub);
                        bool isFirst = true;
                        for (auto const& word : text.split(' ')) {
                            if (word.empty()) {
                                continue;
                            } else if (!isFirst) {
                                auto space  = SemId<Space>::New();
                                space->text = " ";
                                add(space);
                            }

                            auto wordOrg  = SemId<Word>::New();
                            wordOrg->text = word;
                            add(wordOrg);
                            isFirst = false;
                        }
                    } else {
                        add(toNode(sub));
                    }
                }
            } else if (tag == "body") {
                result                = SemId<StmtList>::New();
                Vec<LxbNode> subnodes = getSubnodes(node);
                for (int i = 0; i < subnodes.size(); ++i) {
                    LxbNode sub = subnodes.at(i);
                    if (i == 0 && sub->type == LXB_DOM_NODE_TYPE_TEXT
                        && getText(sub) == "\n") {
                        continue;
                    } else {
                        add(toNode(sub));
                    }
                }
            } else {
                LOG(ERROR) << "Unhandled tag conversion HTML->org";
                LOG(ERROR) << getHtmlTree(node);
            }
            break;
        }
        case LXB_DOM_NODE_TYPE_TEXT: {
            auto word  = SemId<Word>::New();
            word->text = getText(node);
            result     = std::move(word);
            break;
        }
        default: {
            LOG(FATAL) << fmt(
                "Unhandled node type conversion {}:\n{}",
                node->type,
                getHtmlTree(node));
        }
    }


    return result;
}


QString org_qml::Org::getRichText() const {
    ExporterHtml    exp;
    layout::BlockId block  = exp.evalTop(__data);
    Str             result = exp.store.toString(block);
    return QString::fromStdString(result);
}

void org_qml::Org::setRichText(const QString& value) {
    LxbDoc               doc = parseHtmlFragmentToLxb(value);
    Opt<SemId<sem::Org>> org = toNode(lxb_dom_interface_node(doc->body));
    // ExporterTree::treeRepr(org.value());
    // std::cout << std::endl;
    *__data.get() = *org.value().value.get();
}

QJsonValue org_qml::Org::getJson() const {
    ExporterJson exp{};
    json         result = exp.evalTop(__data);

    Func<QJsonValue(CR<json> in)> aux;
    aux = [&aux](CR<json> in) -> QJsonValue {
        switch (in.type()) {
            case json::value_t::array: {
                QJsonArray result;
                for (auto const& it : in) { result.append(aux(it)); }
                return result;
            }

            case json::value_t::object: {
                QJsonObject result;
                for (auto const& [key, sub] : in.items()) {
                    result.insert(QString::fromStdString(key), aux(sub));
                }
                return result;
            }

            case json::value_t::number_integer: {
                return in.get<int>();
            }

            case json::value_t::string: {
                return QString::fromStdString(in.get<std::string>());
            }

            case json::value_t::boolean: {
                return in.get<bool>();
            }

            case json::value_t::binary:
            case json::value_t::discarded:
            case json::value_t::null: {
                return QJsonValue();
            }

            case json::value_t::number_float: {
                return in.get<float>();
            }

            case json::value_t::number_unsigned: {
                return QJsonValue(
                    static_cast<qint64>(in.get<unsigned int>()));
            }
        }
    };


    return aux(result);
}

org_qml::Org org_qml::Org::at(int index) {
    return org_qml::serde<Org, sem::SemId<sem::Org>>::cxx_to_qml(
        __data->at(index));
}

QString org_qml::Org::getOrgText() {
    return QString::fromStdString(sem::Formatter::format(__data));
}
