#pragma once

#include <hstd/stdlib/Formatter.hpp>
#include <string>
#include <vector>
#include <map>
#include <ostream>
#include <hstd/system/reflection.hpp>
#include <hstd/system/macros.hpp>

namespace hstd {
class XmlNode {
  public:
    DECL_DESCRIBED_ENUM(Kind, Element, Comment, CData);

    explicit XmlNode(std::string tag);

    static XmlNode comment(std::string const& text);
    static XmlNode cdata(std::string const& text);

    void set_attr(std::string const& name, std::string const& value);

    template <typename T>
    void set_attr(std::string const& name, T const& value) {
        set_attr(name, hstd::fmt1(value));
    }

    void push_back(XmlNode child);
    void set_text(std::string const& text);

    void        serialize(std::ostream& os, int indent = 2) const;
    std::string to_string(int indent = 2) const;

  private:
    XmlNode(Kind type, std::string content);

    void serialize_impl(std::ostream& os, int depth, int indent) const;

    static void write_escaped(std::ostream& os, std::string const& text);
    static void write_attr_escaped(
        std::ostream&      os,
        std::string const& text);

    Kind                                             type;
    std::string                                      tag;
    std::string                                      text;
    std::vector<std::pair<std::string, std::string>> attrs;
    std::vector<XmlNode>                             subnodes;
};

} // namespace hstd
