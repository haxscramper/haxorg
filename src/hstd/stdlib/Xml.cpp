#include "Xml.hpp"
#include <sstream>

using namespace hstd;

XmlNode::XmlNode(std::string tag)
    : type(Kind::Element), tag(std::move(tag)) {}

XmlNode::XmlNode(Kind type, std::string content)
    : type(type), text(std::move(content)) {}

XmlNode XmlNode::comment(std::string const& text) {
    return XmlNode(Kind::Comment, text);
}

XmlNode XmlNode::cdata(std::string const& text) {
    return XmlNode(Kind::CData, text);
}

void XmlNode::set_attr(std::string const& name, std::string const& value) {
    for (auto& [k, v] : attrs) {
        if (k == name) {
            v = value;
            return;
        }
    }
    attrs.emplace_back(name, value);
}

void XmlNode::push_back(XmlNode child) {
    subnodes.push_back(std::move(child));
}

void XmlNode::set_text(std::string const& text_) { text = text_; }

void XmlNode::serialize(std::ostream& os, int indent) const {
    serialize_impl(os, 0, indent);
}

std::string XmlNode::to_string(int indent) const {
    std::ostringstream os;
    serialize(os, indent);
    return os.str();
}

void XmlNode::serialize_impl(std::ostream& os, int depth, int indent)
    const {
    std::string pad(depth * indent, ' ');

    if (type == Kind::Comment) {
        os << pad << "<!--" << text << "-->\n";
        return;
    }

    if (type == Kind::CData) {
        os << pad << "<![CDATA[" << text << "]]>\n";
        return;
    }

    os << pad << "<" << tag;
    for (auto const& [name, value] : attrs) {
        os << " " << name << "=\"";
        write_attr_escaped(os, value);
        os << "\"";
    }

    bool has_body = !text.empty() || !subnodes.empty();

    if (!has_body) {
        os << "/>\n";
        return;
    }

    os << ">";

    if (!subnodes.empty()) {
        os << "\n";
        if (!text.empty()) {
            std::string child_pad((depth + 1) * indent, ' ');
            os << child_pad;
            write_escaped(os, text);
            os << "\n";
        }
        for (auto const& child : subnodes) {
            child.serialize_impl(os, depth + 1, indent);
        }
        os << pad << "</" << tag << ">\n";
    } else {
        write_escaped(os, text);
        os << "</" << tag << ">\n";
    }
}

void XmlNode::write_escaped(std::ostream& os, std::string const& text) {
    for (char c : text) {
        switch (c) {
            case '&': os << "&amp;"; break;
            case '<': os << "&lt;"; break;
            case '>': os << "&gt;"; break;
            default: os << c; break;
        }
    }
}

void XmlNode::write_attr_escaped(
    std::ostream&      os,
    std::string const& text) {
    for (char c : text) {
        switch (c) {
            case '&': os << "&amp;"; break;
            case '<': os << "&lt;"; break;
            case '>': os << "&gt;"; break;
            case '"': os << "&quot;"; break;
            case '\'': os << "&apos;"; break;
            default: os << c; break;
        }
    }
}
