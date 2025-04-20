#pragma once

#include <hstd/stdlib/Vec.hpp>
#include <hstd/stdlib/IntSet.hpp>
#include <hstd/stdlib/ColText.hpp>
#include <hstd/stdlib/Func.hpp>
#include <hstd/stdlib/Opt.hpp>
#include <hstd/stdlib/Map.hpp>
#include <hstd/stdlib/Array.hpp>
#include <hstd/system/exceptions.hpp>
#include <hstd/system/reflection.hpp>
#include <hstd/stdlib/strutils.hpp>
#include <hstd/stdlib/algorithms.hpp>
#include <hstd/stdlib/Set.hpp>
#include <hstd/system/Formatter.hpp>

#include <unordered_set>
#include <unordered_map>
#include <functional>


namespace org::parse {
struct FieldAccessError : hstd::CRTP_hexception<FieldAccessError> {};


enum class AstRangeKind : hstd::u8
{
    Point,        ///< `idx`
    InversePoint, ///< `^idx`
    DirectSlice,  ///< `idx1 .. idx2`
    InverseSlice, ///< `^idx1 .. ^idx2`
    MixedSlice,   ///< `idx1 .. ^idx2`
};

BOOST_DESCRIBE_ENUM(
    AstRangeKind,
    Point,
    InversePoint,
    DirectSlice,
    InverseSlice,
    MixedSlice);


inline auto tmp = hstd::value_domain<AstRangeKind>::low();

template <typename N>
hstd::Str toPath(const N& ast, const hstd::Vec<int>& path) {
    hstd::Func<hstd::Vec<hstd::Str>(
        N const&, hstd::Span<const int> const&)>
        aux;
    aux = [&aux](const N& a, const hstd::Span<const int>& path) {
        hstd::Vec<hstd::Str> result;
        result.push_back(fmt1(a.getKind()));
        if (1 < path.size()) {
            result.append(aux(a[path[0]], path[slice(1, 1_B)]));
        } else if (path.size() == 1) {
            result.push_back("[" + hstd::fmt1(path[0]) + "]");
        }
        return result;
    };

    return join(".", aux(ast, path));
}


/// \brief Range of AST nodes, effectively represents a field for
/// fixed-position homogeneous AST.
template <typename Name>
struct AstRange {
    bool         isOptional = false; /*!Whether the field is optional */
    hstd::Str    fieldDoc;           /*!Documentation for a field */
    Name         fieldName;          /*!Field name */
    AstRangeKind kind = AstRangeKind::Point;

    int idx   = 0; /*!Single subnode with either direct or inverse index */
    int first = 0; /*!first of the subnode range, left part of `..` */
    int last  = 0; /*!End of the subnode range, right part of `..` */

    /// \brief Set field documentation
    AstRange<Name>& doc(hstd::CR<hstd::Str> _doc) {
        fieldDoc = _doc;
        return *this;
    }

    AstRange<Name>& optional(bool _optional = true) {
        isOptional = _optional;
        return *this;
    }

    // TODO REFACTOR use `std::variant` with different slice overloads and
    // `std::visit` + `overload` pattern to get the values instead of
    // manually implementing switch over kind.

    inline AstRange() = default;
    /// \brief Construct point AST range
    inline AstRange(int point, Name name)
        : idx(point), kind(AstRangeKind::Point), fieldName(name) {}
    /// \brief  Construct inverse point AST range
    inline AstRange(hstd::BackwardsIndex point, Name name)
        : idx(point.value)
        , kind(AstRangeKind::InversePoint)
        , fieldName(name) {}
    /// \brief Construct direct slice AST range
    inline AstRange(hstd::Slice<int> slice, Name name)
        : first(slice.first)
        , last(slice.last)
        , kind(AstRangeKind::DirectSlice)
        , fieldName(name) {}
    /// \brief Construct mixed slice AST range
    inline AstRange(
        hstd::HSlice<int, hstd::BackwardsIndex> slice,
        Name                                    name)
        : first(slice.first)
        , last(slice.last.value)
        , kind(AstRangeKind::MixedSlice)
        , fieldName(name) {}
    /// \brief  Construct inverse slice AST range
    inline AstRange(hstd::Slice<hstd::BackwardsIndex> slice, Name name)
        : first(slice.first.value)
        , last(slice.last.value)
        , kind(AstRangeKind::InverseSlice)
        , fieldName(name) {}

    /// \brief Get resolved subnode slice if the range is applicable for
    /// node of provided range size. Otherwise return empty option.
    hstd::Opt<hstd::Slice<int>> toSlice(const int& maxLen) const {
        hstd::Pair<int, int> range;
        switch (kind) {
            case AstRangeKind::Point: range = {idx, idx}; break;
            case AstRangeKind::InversePoint:
                range = {maxLen - idx, maxLen - idx};
                break;
            case AstRangeKind::DirectSlice: range = {first, last}; break;
            case AstRangeKind::InverseSlice:
                range = {maxLen - first, maxLen - last};
                break;
            case AstRangeKind::MixedSlice:
                range = {first, maxLen - last};
                break;
        }

        if (range.first <= range.second && range.second <= maxLen) {
            return hstd::slice(range.first, range.second);
        } else {
            return std::nullopt;
        }
    }

    bool contains(const int& idx, const int& maxLen) const {
        auto slice = toSlice(maxLen);
        return slice.has_value() && slice->contains(idx);
    }
};
} // namespace org::parse


template <typename Name>
struct std::formatter<org::parse::AstRange<Name>>
    : std::formatter<std::string> {
    template <typename FormatContext>
    FormatContext::iterator format(
        org::parse::AstRange<Name> const& p,
        FormatContext&                    ctx) const {
        switch (p.kind) {
            case org::parse::AstRangeKind::Point: {
                hstd::fmt_ctx(p.idx, ctx);
                break;
            }
            case org::parse::AstRangeKind::InversePoint: {
                hstd::fmt_ctx("^", ctx);
                hstd::fmt_ctx(p.idx, ctx);
                break;
            }
            case org::parse::AstRangeKind::DirectSlice: {
                hstd::fmt_ctx(p.first, ctx);
                hstd::fmt_ctx("..", ctx);
                hstd::fmt_ctx(p.last, ctx);
                break;
            }
            case org::parse::AstRangeKind::InverseSlice: {
                hstd::fmt_ctx("^", ctx);
                hstd::fmt_ctx(p.first, ctx);
                hstd::fmt_ctx("..^", ctx);
                hstd::fmt_ctx(p.last, ctx);
                break;
            }
            case org::parse::AstRangeKind::MixedSlice: {
                hstd::fmt_ctx(p.first, ctx);
                hstd::fmt_ctx("..^", ctx);
                hstd::fmt_ctx(p.last, ctx);
                break;
            }
        }
        return ctx.out();
    }
};

namespace org::parse {

template <typename Node, typename Kind, typename Name>
struct AstCheckFail {
    bool               isMissing = false;
    hstd::Str          msg;
    hstd::Vec<int>     path;
    Kind               parent = hstd::value_domain<Kind>::low();
    hstd::IntSet<Kind> expected;
    hstd::Opt<Kind>    got;
    AstRange<Name>     range;

    AstCheckFail() {}

    hstd::Vec<AstCheckFail<Node, Kind, Name>> nested;

    bool empty(const bool& withNested = true) const {
        return !isMissing && msg.size() == 0 && expected.size() == 0
            && (withNested ? nested.size() == 0 : true);
    }

    int count() const {
        int result = 0;
        for (const auto& nested : nested) { result += nested.count(); }
        if (isMissing || !msg.empty() || !expected.empty()) { ++result; }
        return result;
    };


    hstd::ColText format(Node const& node) const {
        using fg = hstd::TermColorFg8Bit;
        hstd::ColStream s;

        hstd::Func<void(const AstCheckFail<Node, Kind, Name>&, const int&)>
            aux;

        aux = [&s, &aux, &node](
                  const AstCheckFail<Node, Kind, Name>& fail,
                  const int&                            level) {
            s.indent(level);
            auto parentFailed = false;
            if (!fail.empty(false)) {
                parentFailed = true;
                if (!fail.msg.empty()) { s << fail.msg << " "; }
                if (!fail.expected.empty()) {
                    if (fail.isMissing) {
                        s << "missing subnode " << fg::Green << fail.range
                          << s.end();
                        // if (!fail.range.fieldName.empty()) {
                        s << " (" << fg::Green << fail.range.fieldName
                          << s.end() << ")";
                        // }
                        s << " " << fg::Red << fail.expected << s.end();
                    } else {
                        s << "wanted " << fg::Red << fail.expected
                          << s.end() << " in " << fg::Green << fail.range
                          << s.end();

                        // if (!fail.range.fieldName.empty()) {
                        s << " (" << fg::Green << fail.range.fieldName
                          << s.end() << ")";
                        // }

                        if (fail.got.has_value()) {
                            s << ", but got " << fmt1(fail.got.value());
                        }
                    }
                } else if (fail.isMissing) {
                    s << "missing subnode " << fg::Cyan << fail.range
                      << s.end();
                    // if (!fail.range.fieldName.empty()) {
                    s << " (" << fg::Cyan << fail.range.fieldName
                      << s.end() << ")";
                    // }
                }

                if (!fail.path.empty()) {
                    s << " on path " << fg::Green
                      << toPath(node, fail.path) << s.end();
                } else {
                    s << " for subnode of " << fg::Green
                      << fmt1(fail.parent) << s.end();
                }

                if (!fail.range.fieldDoc.empty()) {
                    s << "\n"
                      << fg::Yellow
                      << indent(fail.range.fieldDoc, (level * 2) + 2)
                      << s.end();
                }
            }

            auto idx = 0;
            for (const auto& nested : fail.nested) {
                if (!nested.empty() && 0 < nested.count()) {
                    if (0 < idx) { s << "\n"; }
                    aux(nested, parentFailed ? level + 1 : level);
                    ++idx;
                }
            }
        };

        aux(*this, 0);

        return s.getBuffer();
    }
};

struct AstCheckError : public std::runtime_error {};


/// \brief User-defined validation callback
template <typename Node, typename Kind, typename Name>
using AstCheckProc = hstd::Func<hstd::Opt<AstCheckFail<Node, Kind, Name>>(
    Node)>;


template <typename Node, typename Kind, typename Name>
struct AstPattern;

/// \brief Description of the AST field with provided structural pattern
template <typename Node, typename Kind, typename Name>
struct AstPatternRange {
    AstRange<Name>                          range;
    hstd::Vec<AstPattern<Node, Kind, Name>> alts;
    AstPatternRange(
        hstd::CR<AstRange<Name>>               range,
        hstd::CR<AstPattern<Node, Kind, Name>> pattern)
        : range(range), alts({pattern}) {}
    AstPatternRange(
        hstd::CR<AstRange<Name>>                          range,
        hstd::CR<hstd::Vec<AstPattern<Node, Kind, Name>>> alts = {})
        : range(range), alts(alts) {}
};

/// \brief Entry describing AST structure expected at some specific point
/// in the tree comparison.
template <typename Node, typename Kind, typename Name>
struct AstPattern {
    /// \brief Documentation for AST pattern at specific place in the tree
    hstd::Str doc;
    /// \brief Extra user-provided validation procedure
    AstCheckProc<Node, Kind, Name> check;
    /// \brief Set of node kinds expected at point, mostly used for
    /// leaf-level nodes
    hstd::IntSet<Kind> expected;
    /// \brief List of subnode ranges, mostly used for describing the
    /// structure of upper-level nodes
    hstd::Vec<AstPatternRange<Node, Kind, Name>> ranges;

    /// \brief Construt upper-level AST patter specification, containing
    /// one or more pattern ranges for fields
    AstPattern(
        hstd::CR<hstd::Vec<AstPatternRange<Node, Kind, Name>>> ranges)
        : ranges(ranges) {}
    /// \brief Construct leaf-level AST pattern specification, containing
    /// set of expected nodes
    AstPattern(hstd::CR<hstd::IntSet<Kind>> expected)
        : expected(expected) {}
    AstPattern(Kind expected) : expected(hstd::IntSet<Kind>{expected}) {}
    /// \brief Appent subranges to the already constructed pattern object.
    /// Used for constructing patterns that have constrained kind and
    /// pattern range.
    AstPattern& sub(
        hstd::CR<hstd::Vec<AstPatternRange<Node, Kind, Name>>> subr) {
        ranges.append(subr);
        return *this;
    }


    AstCheckFail<Node, Kind, Name> validateAst(
        Kind const&           kind,
        Kind const&           subnode,
        const int&            idx,
        const int&            maxLen,
        const hstd::Vec<int>& path = hstd::Vec<int>{}) const {
        AstCheckFail<Node, Kind, Name> result;
        result.path = path;
        for (const auto arange : ranges) {
            if (arange.range.contains(idx, maxLen)) {
                for (const auto alt : arange.alts) {
                    if (!alt.expected.contains(subnode)) {
                        AstCheckFail<Node, Kind, Name> fail;
                        fail.parent   = kind;
                        fail.path     = path;
                        fail.expected = alt.expected;
                        fail.got      = subnode;
                        fail.range    = arange.range;

                        result.nested.push_back(fail);
                    }
                }
            }
        }
        return result;
    }


    AstCheckFail<Node, Kind, Name> findMissing(
        Node const&           node,
        const hstd::Vec<int>& path = hstd::Vec<int>{}) const {
        AstCheckFail<Node, Kind, Name> result;
        result.path = path;
        if (!ranges.empty()) {
            auto altFound = Vec(ranges.size(), false);
            auto idx      = 0;
            while (idx < node.size()) {
                for (const auto [rangeIdx, arange] : enumerate(ranges)) {
                    if (arange.range.contains(idx, node.size())) {
                        altFound[rangeIdx] = true;
                        for (const auto alt : arange.alts) {
                            const auto& n = alt.findMissing(
                                node, path + idx);
                            if (!n.empty()) { result.nested.push_back(n); }
                        }
                        break;
                    }
                }
                ++idx;
            }

            for (const auto& [rangeIdx, found] : enumerate(altFound)) {
                if (!found && !ranges[rangeIdx].range.isOptional) {
                    hstd::IntSet<Kind> expected;
                    for (const auto alt : ranges[rangeIdx].alts) {
                        expected.incl(alt.expected);
                    }

                    AstCheckFail<Node, Kind, Name> fail;
                    fail.isMissing = true;
                    fail.parent    = node.getKind();
                    fail.path      = path + rangeIdx;
                    fail.range     = ranges[rangeIdx].range;
                    fail.expected  = expected;

                    result.nested.push_back(fail);
                }
            }
        }
        return result;
    }

    hstd::Opt<hstd::ColText> validateSub(
        Kind const& node,
        Kind const& sub,
        const int&  idx,
        const int&  maxIdx) const {

        const auto fail = formatFail(
            validateAst(node, sub, idx, maxIdx, {idx}), Node());

        if (fail.empty()) {
            return std::nullopt;
        } else {
            return fail;
        }
    }
};

template <typename Node, typename Kind, typename Name>
struct AstSpec {
  private:
    hstd::UnorderedMap<Kind, AstPattern<Node, Kind, Name>> spec;
    hstd::UnorderedMap<Kind, hstd::UnorderedMap<Name, AstRange<Name>>>
        nodeRanges;

    hstd::UnorderedMap<Kind, hstd::UnorderedMap<Name, AstRange<Name>>> getNodeRanges()
        const {
        hstd::UnorderedMap<Kind, hstd::UnorderedMap<Name, AstRange<Name>>>
            result;
        for (const auto& [kind, pattern] : spec) {
            for (const auto& range : pattern.ranges) {
                result[kind][range.range.fieldName] = range.range;
            }
        }
        return result;
    }

  public:
    AstSpec(
        const hstd::Vec<hstd::Pair<Kind, AstPattern<Node, Kind, Name>>>&
            patterns) {
        for (const auto& [kind, pattern] : patterns) {
            spec.insert_or_assign(kind, pattern);
        }
        nodeRanges = getNodeRanges();
    }

    AstPattern<Node, Kind, Name> getPattern(Kind const& kind) const {
        return spec[kind].get();
    }

    bool hasPattern(Kind kind) const { return spec[kind].has_value(); }

    hstd::ColText validateAst(Node const& node) const {
        if (spec[node.kind].has_value()) {
            return formatFail(
                spec[node.kind].value().findMissing(node), node);
        } else {
            return hstd::ColText{};
        }
    }

    hstd::Opt<hstd::ColText> validateSelf(Node const& node) const {
        if (spec[node.getKind()].has_value()) {
            const auto missing = spec[node.getKind()].value().findMissing(
                node);
            if (0 < missing.count()) {
                const auto fail = missing.format(node);
                if (!fail.empty()) { return fail; }
            }
        }
        return std::nullopt;
    }


    hstd::Opt<hstd::ColText> validateSub(
        Node const& node,
        int const&  idx,
        Node const& sub) const {
        hstd::Opt<hstd::ColText> result;
        if (spec[node.getKind()].has_value()) {
            const auto fail = spec[node.getKind()].value().validateAst(
                node.getKind(), sub.getKind(), idx, node.size());
            if (!fail.empty()) { return fail.format(node); }
        }
        return std::nullopt;
    }


    hstd::Opt<hstd::ColText> validateSub(Node const& node, const int& idx)
        const {
        return validateSub(node, idx, node[idx]);
    }

    hstd::UnorderedMap<Name, AstRange<Name>> nodeFields(Kind kind) const {
        return nodeRanges.at(kind);
    }

    hstd::Vec<hstd::Pair<Name, hstd::Slice<int>>> resolveNodeFields(
        Kind kind,
        int  size) const {
        hstd::Vec<hstd::Pair<Name, hstd::Slice<int>>> result;
        if (size == 0 && nodeRanges.at(kind).size() == 0) {
            return result;
        }

        for (const auto& [name, range] : nodeRanges.at(kind)) {
            auto slice = range.toSlice(size);
            if (slice.has_value()) {
                result.push_back({name, slice.value()});
            }
        }

        sort<hstd::Pair<Name, hstd::Slice<int>>>(
            result, [](auto const& lhs, auto const& rhs) {
                return lhs.first < rhs.first;
            });

        for (const auto& [lhs, rhs] : carthesian(result, result)) {
            if (lhs == rhs) { continue; }

            auto overlap = lhs->second.overlap(rhs->second);
            if (overlap.has_value()) {
                throw org::parse::FieldAccessError(
                    "Cannot access field with overlapping ranges: '$#' "
                    "and '$#' had ast ranges specified as '$#' and '$#' "
                    "respectively which resolved to $# and $# for node of "
                    "size $# kind $#"
                    % fmt1_vec(
                        lhs->first,
                        rhs->first,
                        nodeRanges.at(kind).at(lhs->first),
                        nodeRanges.at(kind).at(rhs->first),
                        lhs->second,
                        rhs->second,
                        size,
                        fmt1(kind)));
            }
        }

        int                     max = result.back().second.last;
        hstd::UnorderedSet<int> visited;
        for (const auto& [_, range] : result) {
            max = std::max(max, range.last);
            for (const auto& value : range) { visited.insert(value); }
        }

        hstd::UnorderedSet<int> all;
        for (int i = 0; i < max; ++i) { all.insert(i); }

        auto diff = all - visited;
        if (!diff.empty()) {
            throw FieldAccessError(std::format(
                "Indices missing from the field description {} are not "
                "covered in spec for node {}",
                diff,
                kind));
        }

        return result;
    }

    hstd::ColText validateAst(
        Node const& node,
        Node const& subnode,
        const int&  idx) const {
        hstd::ColStream s;
        if (spec[node.getKind()].has_value()) {
            const auto fail1 = validateAst(
                spec[node.getKind()].value(),
                node.getKind(),
                subnode.getKind(),
                idx,
                node.size(),
                hstd::Vec<int>({idx}));

            if (0 < fail1.count()) {
                s << formatFail(fail1, node) << "\n";
            }

            s << formatFail(
                spec[node.getKind()].value().findMissing(node), node);
        }

        return s.getBuffer();
    }

    hstd::ColText treeRepr() const {
        using fg = hstd::TermColorFg8Bit;

        hstd::ColStream s;

        hstd::Func<void(const AstPattern<Node, Kind, Name>&, const int&)>
            aux;

        aux = [&s, &aux](
                  const AstPattern<Node, Kind, Name>& p,
                  const int&                          level) {
            s.indent(level);
            if (!p.doc.empty()) {
                s << fg::Yellow
                  << indent(p.doc, 2 * (level + 1), ' ', "## ") << s.end();
            }

            if (!p.expected.empty()) { s << fmt1(p.expected); }

            for (const auto [idx, arange] : enumerate(p.ranges)) {
                s << "\n"
                  << s.indent(level + 1) << fg::Yellow << arange.range
                  << s.end();
                if (!arange.range.fieldName.empty()) {
                    s << " " << fg::Blue << arange.range.fieldName
                      << s.end();
                }

                for (const auto alt : arange.alts) {
                    s << "\n";
                    aux(alt, level + 2);
                }
            }
        };

        for (const auto [kind, pattern] : spec.pairs()) {
            if (pattern->has_value()) {
                s << fmt1(kind) << "\n";
                aux(pattern->value(), 1);
                s << "\n";
            }
        }

        return s.getBuffer();
    }

    int getSingleSubnodeIdx(
        Kind const&           kind,
        Name const&           name,
        const hstd::Opt<int>& nodeLen = hstd::Opt<int>{}) const {
        if (nodeRanges.at(kind).contains(name)) {
            const auto range = nodeRanges.at(kind).at(name);
            if (range.kind == AstRangeKind::Point) {
                return range.idx;
            } else if (nodeLen.has_value()) {
                auto slice = range.toSlice(nodeLen.value());
                if (slice.has_value()) {
                    return slice->first;
                } else {
                    throw makeMissingSlice(kind, name, slice, range);
                }
            } else {
                throw UnexpectedKindError(
                    "Cannot get single subnode index for element "
                    + fmt1(name) + " of node kind " + fmt1(kind)
                    + " - field exists, but allowed AST range is of kind "
                    + hstd::enum_serde<AstRangeKind>::to_string(range.kind)
                    + " and requires node length, but it "
                    + "wasn't specified.");
            }
        } else {
            throw makeMissingPositional(kind, name);
        }
    }

    int getSingleSubnodeIdx(Node const& node, Name const& name) const {
        if (nodeRanges.at(node.getKind()).contains(name)) {
            const auto range = nodeRanges.at(node.getKind()).at(name);
            const auto slice = range.toSlice(node.size());
            if (slice.has_value()) {
                return slice->first;
            } else {
                throw makeMissingSlice(node.getKind(), name, slice, range);
            }
        } else {
            throw makeMissingPositional(node.getKind(), name);
        }
    }

    FieldAccessError makeMissingSlice(
        Kind                        kind,
        hstd::CR<Name>              name,
        hstd::Opt<hstd::Slice<int>> slice,
        hstd::CR<AstRange<Name>>    range) const {
        return FieldAccessError::init(std::format(
            "Range {} for node kind {} was resolved into slice {} "
            "(required ast range is {})",
            hstd::fmt1(name),
            hstd::fmt1(kind),
            hstd::fmt1(slice),
            hstd::fmt1(range)));
    }

    FieldAccessError makeMissingPositional(Kind kind, hstd::CR<Name> name)
        const {
        hstd::Str names;
        if (nodeRanges.at(kind).empty()) {
            names = "No named subnodes specified.";
        } else {
            hstd::Vec<hstd::Str> tmp;
            for (const auto& key : nodeRanges.at(kind).keys()) {
                tmp.push_back(hstd::fmt1(key));
            }

            names = "Available names: " + join(", ", tmp);
        }

        return FieldAccessError::init(
            "Cannot get positional node with name '" + hstd::fmt1(name)
            + "' from node of kind '" + hstd::fmt1(kind) + "'. "
            + names.toBase());
    }

    Node getSingleSubnode(Node const& node, Name const& name) const {
        return node.at(getSingleSubnodeIdx(node, name));
    }

    hstd::Vec<Node> getMultipleSubnode(Node const& node, Name const& name)
        const {
        if (nodeRanges.at(node.getKind()).contains(name)) {
            hstd::Vec<Node> result;
            const auto      range = nodeRanges.at(node.getKind()).at(name);
            const auto      slice = range.toSlice(node.size());
            if (!slice.has_value()) {
                throw makeMissingSlice(node.getKind(), name, slice, range);
            }
            for (auto const& idx : slice.value()) {
                result.push_back(node.at(idx));
            }
            return result;
        } else {
            throw makeMissingPositional(node.getKind(), name);
        }
    }

    hstd::Opt<AstRange<Name>> fieldRange(Node const& node, const int& idx)
        const {
        if (spec.contains(node.getKind())) {
            auto const& pattern = spec.at(node.getKind());
            for (auto const& field : pattern.ranges) {
                if (field.range.contains(idx, node.size())) {
                    return field.range;
                }
            }
        }
        return std::nullopt;
    }

    hstd::Opt<Name> fieldName(Node const& node, const int& idx) const {
        const auto field = fieldRange(node, idx);
        if (field.has_value()) {
            return field.value().fieldName;
        } else {
            return std::nullopt;
        }
    }

    bool isSingleField(Node const& node, const int& idx) const {
        const auto field = fieldRange(node, idx);
        return field.has_value()
            && hstd::IntSet<
                   AstRangeKind>{AstRangeKind::Point, AstRangeKind::InversePoint}
                   .contains(field.value().kind);
    }

    hstd::Opt<hstd::Str> fieldDoc(Node const& node, const int& idx) const {
        const auto field = fieldRange(node, idx);
        if (field.has_value()) {
            return field.value().fieldDoc;
        } else {
            return std::nullopt;
        }
    }
};


}; // namespace org::parse
