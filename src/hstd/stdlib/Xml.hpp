#pragma once

#include <string>
#include <vector>
#include <map>
#include <ostream>

namespace hstd {
/// \brief A lightweight XML document builder and serializer.
///
/// Supports constructing XML trees with nested elements, text content,
/// and attributes, then serializing them to an indented string
/// representation.
///
/// \code{.cpp}
/// XmlNode svg("svg");
/// svg.set_attr("xmlns", "http://www.w3.org/2000/svg");
/// svg.set_attr("width", "100");
///
/// XmlNode rect("rect");
/// rect.set_attr("fill", "white");
/// svg.append_child(std::move(rect));
///
/// svg.serialize(std::cout);
/// \endcode
class XmlNode {
  public:
    /// \brief Construct a node with the given tag name.
    /// \param tag The element tag name.
    explicit XmlNode(std::string tag);

    /// \brief Set or overwrite an attribute on this element.
    /// \param name  Attribute name.
    /// \param value Attribute value (will be XML-escaped on output).
    void set_attr(std::string const& name, std::string const& value);

    /// \brief Append a child element.
    /// \param child The child node to append (moved).
    void push_back(XmlNode child);

    /// \brief Set the text content of this element.
    ///
    /// Text content is written inside the element body. If the element
    /// also has children, text is written before the first child.
    /// \param text The text content (will be XML-escaped on output).
    void set_text(std::string const& text);

    /// \brief Serialize the XML tree to an output stream with
    ///        indentation.
    /// \param os     Output stream to write to.
    /// \param indent Number of spaces per indentation level.
    void serialize(std::ostream& os, int indent = 2) const;

    /// \brief Serialize the XML tree to a string.
    /// \param indent Number of spaces per indentation level.
    /// \return The serialized XML string.
    std::string to_string(int indent = 2) const;

  private:
    void serialize_impl(std::ostream& os, int depth, int indent) const;

    static void write_escaped(std::ostream& os, std::string const& text);
    static void write_attr_escaped(
        std::ostream&      os,
        std::string const& text);

    std::string                                      tag;
    std::string                                      text;
    std::vector<std::pair<std::string, std::string>> attrs;
    std::vector<XmlNode>                             subnodes;
};

} // namespace hstd
