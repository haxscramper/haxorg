#pragma once

#include <hstd/stdlib/Formatter.hpp>
#include <hstd/system/macros.hpp>
#include <hstd/system/reflection.hpp>
#include <map>
#include <ostream>
#include <string>
#include <vector>

namespace hstd {
class XmlNode {
  public:
    DECL_DESCRIBED_ENUM(Kind, Element, Comment, CData, Raw);

    explicit XmlNode(std::string tag);

    static XmlNode comment(std::string const& text);
    static XmlNode cdata(std::string const& text);
    static XmlNode raw(std::string const& data);

    void set_attr(std::string const& name, std::string const& value);

    template <typename T>
    void set_attr(std::string const& name, T const& value) {
        set_attr(name, hstd::fmt1(value));
    }

    void               push_back(XmlNode child);
    void               set_text(std::string const& text);
    std::string const& get_text() const { return text; }

    void        serialize(std::ostream& os, int indent = 2) const;
    std::string to_string(int indent = 2) const;

    bool isRaw() const { return type == Kind::Raw; }
    bool isCData() const { return type == Kind::CData; }
    bool isComment() const { return type == Kind::Comment; }
    bool isElement() const { return type == Kind::Element; }

  private:
    XmlNode(Kind type, std::string content);

    void serialize_impl(std::ostream& os, int depth, int indent) const;

    static void write_comment_escaped(std::ostream& os, std::string const& input);
    static void write_escaped(std::ostream& os, std::string const& text);
    static void write_attr_escaped(std::ostream& os, std::string const& text);

    Kind                                             type;
    std::string                                      tag;
    std::string                                      text;
    std::vector<std::pair<std::string, std::string>> attrs;
    std::vector<XmlNode>                             subnodes;
};

} // namespace hstd
