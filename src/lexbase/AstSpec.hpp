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

#include <unordered_set>
#include <unordered_map>
#include <functional>

template <typename T>
std::ostream& operator<<(
    std::ostream&                os,
    std::unordered_set<T> const& value) {
    return os << "{" << join(os, ", ", value) << "}";
}

template <typename T>
std::string to_string(std::unordered_set<T> const& value) {
    std::stringstream os;
    os << value;
    return os.str();
}


namespace astspec {

struct FieldAccessError : public GetterError {
    explicit FieldAccessError(const std::string& message)
        : GetterError(message) {}
};


enum class AstRangeKind : u8
{
    Point,        /*!`idx` */
    InversePoint, /*!`^idx` */
    DirectSlice,  /*!`idx1 .. idx2` */
    InverseSlice, /*!`^idx1 .. ^idx2` */
    MixedSlice,   /*!`idx1 .. ^idx2` */
};

BOOST_DESCRIBE_ENUM(
    AstRangeKind,
    Point,
    InversePoint,
    DirectSlice,
    InverseSlice,
    MixedSlice);


inline auto tmp = low<AstRangeKind>();

template <typename N>
Str toPath(const N& ast, const Vec<int>& path) {
    Func<Vec<Str>(N const&, Span<const int> const&)> aux;
    aux = [&aux](const N& a, const Span<const int>& path) {
        Vec<Str> result;
        result.push_back(to_string(a.getKind()));
        if (1 < path.size()) {
            result.append(aux(a[path[0]], path[slice(1, 1_B)]));
        } else if (path.size() == 1) {
            result.push_back("[" + to_string(path[0]) + "]");
        }
        return result;
    };

    return join(".", aux(ast, path));
}


/// \brief Range of AST nodes, effectively represents a field for
/// fixed-position homogeneous AST.
struct AstRange {
    bool         isOptional = false; /*!Whether the field is optional */
    Str          fieldDoc;           /*!Documentation for a field */
    Str          fieldName;          /*!Field name */
    AstRangeKind kind = AstRangeKind::Point;

    int idx;   /*!Single subnode with either direct or inverse index */
    int first; /*!first of the subnode range, left part of `..` */
    int last;  /*!End of the subnode range, right part of `..` */

    /// \brief Set field documentation
    AstRange& doc(CR<Str> _doc) {
        fieldDoc = _doc;
        return *this;
    }

    AstRange& optional(bool _optional = true) {
        isOptional = _optional;
        return *this;
    }

    // TODO REFACTOR use `std::variant` with different slice overloads and
    // `std::visit` + `overload` pattern to get the values instead of
    // manually implementing switch over kind.

    inline AstRange() = default;
    /// \brief Construct point AST range
    inline AstRange(int point, Str name)
        : idx(point), kind(AstRangeKind::Point), fieldName(name) {}
    /// \brief  Construct inverse point AST range
    inline AstRange(BackwardsIndex point, Str name)
        : idx(point.value)
        , kind(AstRangeKind::InversePoint)
        , fieldName(name) {}
    /// \brief Construct direct slice AST range
    inline AstRange(Slice<int> slice, Str name)
        : first(slice.first)
        , last(slice.last)
        , kind(AstRangeKind::DirectSlice)
        , fieldName(name) {}
    /// \brief Construct mixed slice AST range
    inline AstRange(HSlice<int, BackwardsIndex> slice, Str name)
        : first(slice.first)
        , last(slice.last.value)
        , kind(AstRangeKind::MixedSlice)
        , fieldName(name) {}
    /// \brief  Construct inverse slice AST range
    inline AstRange(Slice<BackwardsIndex> slice, Str name)
        : first(slice.first.value)
        , last(slice.last.value)
        , kind(AstRangeKind::InverseSlice)
        , fieldName(name) {}

    /// \brief Get resolved subnode slice if the range is applicable for
    /// node of provided range size. Otherwise return empty option.
    Opt<Slice<int>> toSlice(const int& maxLen) const {
        Pair<int, int> range;
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
            return slice(range.first, range.second);
        } else {
            return std::nullopt;
        }
    }

    bool contains(const int& idx, const int& maxLen) const {
        auto slice = toSlice(maxLen);
        return slice.has_value() && slice->contains(idx);
    }
};


inline std::ostream& operator<<(std::ostream& os, AstRange const& arange) {
    switch (arange.kind) {
        case AstRangeKind::Point: return os << arange.idx;
        case AstRangeKind::InversePoint: return os << "^" << arange.idx;
        case AstRangeKind::DirectSlice:
            return os << arange.first << ".." << arange.last;
        case AstRangeKind::InverseSlice:
            return os << "^" << arange.first << "..^" << arange.last;
        case AstRangeKind::MixedSlice:
            return os << arange.first << "..^" << arange.last;
    }
}


template <typename N, typename K>
struct AstCheckFail {
    bool      isMissing = false;
    Str       msg;
    Vec<int>  path;
    K         parent = low<K>();
    IntSet<K> expected;
    Opt<K>    got;
    AstRange  range;

    AstCheckFail() {}

    Vec<AstCheckFail<N, K>> nested;


    bool empty(const bool& withNested = true) const {
        return !isMissing && msg.size() == 0 && expected.size() == 0
            && (withNested ? nested.size() == 0 : true);
    }

    int count() const {
        int result = 0;
        for (const auto& nested : nested) {
            result += nested.count();
        }
        if (isMissing || !msg.empty() || !expected.empty()) {
            ++result;
        }
        return result;
    };


    ColText format(const N& node) const {
        using fg = TermColorFg8Bit;
        ColStream s;

        Func<void(const AstCheckFail<N, K>&, const int&)> aux;

        aux = [&s, &aux, &node](
                  const AstCheckFail<N, K>& fail, const int& level) {
            s.indent(level);
            auto parentFailed = false;
            if (!fail.empty(false)) {
                parentFailed = true;
                if (!fail.msg.empty()) {
                    s << fail.msg << " ";
                }
                if (!fail.expected.empty()) {
                    if (fail.isMissing) {
                        s << "missing subnode " << fg::Green << fail.range
                          << s.end();
                        if (!fail.range.fieldName.empty()) {
                            s << " (" << fg::Green << fail.range.fieldName
                              << s.end() << ")";
                        }
                        s << " " << fg::Red << fail.expected << s.end();
                    } else {
                        s << "wanted " << fg::Red << fail.expected
                          << s.end() << " in " << fg::Green << fail.range
                          << s.end();

                        if (!fail.range.fieldName.empty()) {
                            s << " (" << fg::Green << fail.range.fieldName
                              << s.end() << ")";
                        }

                        if (fail.got.has_value()) {
                            s << ", but got "
                              << to_string(fail.got.value());
                        }
                    }
                } else if (fail.isMissing) {
                    s << "missing subnode " << fg::Cyan << fail.range
                      << s.end();
                    if (!fail.range.fieldName.empty()) {
                        s << " (" << fg::Cyan << fail.range.fieldName
                          << s.end() << ")";
                    }
                }

                if (!fail.path.empty()) {
                    s << " on path " << fg::Green
                      << toPath(node, fail.path) << s.end();
                } else {
                    s << " for subnode of " << fg::Green
                      << to_string(fail.parent) << s.end();
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
                    if (0 < idx) {
                        s << "\n";
                    }
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
template <typename N, typename K>
using AstCheckProc = Func<Opt<AstCheckFail<N, K>>(N)>;


template <typename N, typename K>
struct AstPattern;

/// \brief Description of the AST field with provided structural pattern
template <typename N, typename K>
struct AstPatternRange {
    AstRange              range;
    Vec<AstPattern<N, K>> alts;
    AstPatternRange(CR<AstRange> range, CR<AstPattern<N, K>> pattern)
        : range(range), alts({pattern}) {}
    AstPatternRange(
        CR<AstRange>              range,
        CR<Vec<AstPattern<N, K>>> alts = {})
        : range(range), alts(alts) {}
};

/// \brief Entry describing AST structure expected at some specific point
/// in the tree comparison.
template <typename N, typename K>
struct AstPattern {
    /// \brief Documentation for AST pattern at specific place in the tree
    Str doc;
    /// \brief Extra user-provided validation procedure
    AstCheckProc<N, K> check;
    /// \brief Set of node kinds expected at point, mostly used for
    /// leaf-level nodes
    IntSet<K> expected;
    /// \brief List of subnode ranges, mostly used for describing the
    /// structure of upper-level nodes
    Vec<AstPatternRange<N, K>> ranges;

    /// \brief Construt upper-level AST patter specification, containing
    /// one or more pattern ranges for fields
    AstPattern(CR<Vec<AstPatternRange<N, K>>> ranges) : ranges(ranges) {}
    /// \brief Construct leaf-level AST pattern specification, containing
    /// set of expected nodes
    AstPattern(CR<IntSet<K>> expected) : expected(expected) {}
    AstPattern(K expected) : expected(IntSet<K>{expected}) {}
    /// \brief Appent subranges to the already constructed pattern object.
    /// Used for constructing patterns that have constrained kind and
    /// pattern range.
    AstPattern& sub(CR<Vec<AstPatternRange<N, K>>> subr) {
        ranges.append(subr);
        return *this;
    }


    AstCheckFail<N, K> validateAst(
        const K&        kind,
        const K&        subnode,
        const int&      idx,
        const int&      maxLen,
        const Vec<int>& path = Vec<int>{}) const {
        AstCheckFail<N, K> result;
        result.path = path;
        for (const auto arange : ranges) {
            if (arange.range.contains(idx, maxLen)) {
                for (const auto alt : arange.alts) {
                    if (!alt.expected.contains(subnode)) {
                        AstCheckFail<N, K> fail;
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


    AstCheckFail<N, K> findMissing(
        const N&        node,
        const Vec<int>& path = Vec<int>{}) const {
        AstCheckFail<N, K> result;
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
                            if (!n.empty()) {
                                result.nested.push_back(n);
                            }
                        }
                        break;
                    }
                }
                ++idx;
            }

            for (const auto& [rangeIdx, found] : enumerate(altFound)) {
                if (!found && !ranges[rangeIdx].range.isOptional) {
                    IntSet<K> expected;
                    for (const auto alt : ranges[rangeIdx].alts) {
                        expected.incl(alt.expected);
                    }

                    AstCheckFail<N, K> fail;
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

    Opt<ColText> validateSub(
        const K&   node,
        const K&   sub,
        const int& idx,
        const int& maxIdx) const {

        const auto fail = formatFail(
            validateAst(node, sub, idx, maxIdx, {idx}), N());

        if (fail.empty()) {
            return std::nullopt;
        } else {
            return fail;
        }
    }
};

template <typename N, typename K>
struct AstSpec {
  private:
    TypArray<K, Opt<AstPattern<N, K>>>       spec;
    TypArray<K, UnorderedMap<Str, AstRange>> nodeRanges;

    TypArray<K, UnorderedMap<Str, AstRange>> getNodeRanges() const {
        TypArray<K, UnorderedMap<Str, AstRange>> result;
        for (const auto& [kind, pattern] : spec.pairs()) {
            if (pattern->has_value()) {
                for (const auto& range : pattern->value().ranges) {
                    if (!range.range.fieldName.empty()) {
                        result[kind][range.range.fieldName] = range.range;
                    }
                }
            }
        }
        return result;
    }

  public:
    AstSpec(const Vec<Pair<K, AstPattern<N, K>>>& patterns) {
        for (const auto& [kind, pattern] : patterns) {
            spec[kind] = pattern;
        }
        nodeRanges = getNodeRanges();
    }

    AstPattern<N, K> getPattern(const K& kind) const {
        return spec[kind].get();
    }

    bool hasPattern(K kind) const { return spec[kind].has_value(); }

    ColText validateAst(const N& node) const {
        if (spec[node.kind].has_value()) {
            return formatFail(
                spec[node.kind].value().findMissing(node), node);
        } else {
            return ColText{};
        }
    }

    Opt<ColText> validateSelf(const N& node) const {
        if (spec[node.getKind()].has_value()) {
            const auto missing = spec[node.getKind()].value().findMissing(
                node);
            if (0 < missing.count()) {
                const auto fail = missing.format(node);
                if (!fail.empty()) {
                    return fail;
                }
            }
        }
        return std::nullopt;
    }


    Opt<ColText> validateSub(const N& node, const int& idx, const N& sub)
        const {
        Opt<ColText> result;
        if (spec[node.getKind()].has_value()) {
            const auto fail = spec[node.getKind()].value().validateAst(
                node.getKind(), sub.getKind(), idx, node.size());
            if (!fail.empty()) {
                return fail.format(node);
            }
        }
        return std::nullopt;
    }


    Opt<ColText> validateSub(const N& node, const int& idx) const {
        return validateSub(node, idx, node[idx]);
    }

    UnorderedMap<Str, AstRange> nodeFields(K kind) const {
        return nodeRanges.at(kind);
    }

    Vec<Pair<Str, Slice<int>>> resolveNodeFields(K kind, int size) const {
        Vec<Pair<Str, Slice<int>>> result;
        if (size == 0 && nodeRanges.at(kind).size() == 0) {
            return result;
        }

        for (const auto& [name, range] : nodeRanges.at(kind)) {
            auto slice = range.toSlice(size);
            if (slice.has_value()) {
                result.push_back({name, slice.value()});
            }
        }

        sort<Pair<Str, Slice<int>>>(
            result, [](auto const& lhs, auto const& rhs) {
                return lhs.first < rhs.first;
            });

        for (const auto& [lhs, rhs] : carthesian(result, result)) {
            if (lhs == rhs) {
                continue;
            }

            auto overlap = lhs->second.overlap(rhs->second);
            if (overlap.has_value()) {
                throw astspec::FieldAccessError(
                    "Cannot access field with overlapping ranges: '$#' "
                    "and '$#' had ast ranges specified as '$#' and '$#' "
                    "respectively which resolved to $# and $# for node of "
                    "size $# kind $#"
                    % to_string_vec(
                        lhs->first,
                        rhs->first,
                        nodeRanges.at(kind).at(lhs->first),
                        nodeRanges.at(kind).at(rhs->first),
                        lhs->second,
                        rhs->second,
                        size,
                        to_string(kind)));
            }
        }

        int               max = result.back().second.last;
        UnorderedSet<int> visited;
        for (const auto& [_, range] : result) {
            max = std::max(max, range.last);
            for (const auto& value : range) {
                visited.insert(value);
            }
        }

        UnorderedSet<int> all;
        for (int i = 0; i < max; ++i) {
            all.insert(i);
        }

        auto diff = all - visited;
        if (!diff.empty()) {
            throw astspec::FieldAccessError(
                "Indices missing from the field description $# are not "
                "covered in spec for node $#"
                % to_string_vec(to_string(diff), to_string(kind)));
        }

        return result;
    }

    ColText validateAst(const N& node, const N& subnode, const int& idx)
        const {
        ColStream s;
        if (spec[node.getKind()].has_value()) {
            const auto fail1 = validateAst(
                spec[node.getKind()].value(),
                node.getKind(),
                subnode.getKind(),
                idx,
                node.size(),
                Vec<int>({idx}));

            if (0 < fail1.count()) {
                s << formatFail(fail1, node) << "\n";
            }

            s << formatFail(
                spec[node.getKind()].value().findMissing(node), node);
        }

        return s.getBuffer();
    }

    ColText treeRepr() const {
        using fg = TermColorFg8Bit;

        ColStream s;

        Func<void(const AstPattern<N, K>&, const int&)> aux;

        aux = [&s, &aux](const AstPattern<N, K>& p, const int& level) {
            s.indent(level);
            if (!p.doc.empty()) {
                s << fg::Yellow
                  << indent(p.doc, 2 * (level + 1), ' ', "## ") << s.end();
            }

            if (!p.expected.empty()) {
                s << to_string(p.expected);
            }

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
                s << to_string(kind) << "\n";
                aux(pattern->value(), 1);
                s << "\n";
            }
        }

        return s.getBuffer();
    }

    int getSingleSubnodeIdx(
        const K&        kind,
        const Str&      name,
        const Opt<int>& nodeLen = Opt<int>{}) const {
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
                    + to_string(name) + " of node kind " + to_string(kind)
                    + " - field exists, but allowed AST range is of kind "
                    + enum_to_string(range.kind)
                    + " and requires node length, but it "
                    + "wasn't specified.");
            }
        } else {
            throw makeMissingPositional(kind, name);
        }
    }

    int getSingleSubnodeIdx(const N& node, const Str& name) const {
        if (nodeRanges[node.getKind()].contains(name)) {
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
        K               kind,
        CR<Str>         name,
        Opt<Slice<int>> slice,
        CR<AstRange>    range) const {
        return FieldAccessError(
            "Range " + name + " for node kind " + to_string(kind)
            + " was resolved into slice " + to_string(slice)
            + "(required ast range is " + to_string(range) + ")");
    }

    FieldAccessError makeMissingPositional(K kind, CR<Str> name) const {
        Str names;
        if (nodeRanges.at(kind).empty()) {
            names = "No named subnodes specified.";
        } else {
            names = "Available names - "
                  + join(", ", nodeRanges.at(kind).keys());
        }

        return FieldAccessError(
            "Cannot get positional node with name '" + name
            + "' from node of kind '" + to_string(kind) + "'. " + names);
    }

    N getSingleSubnode(const N& node, const Str& name) const {
        return node.at(getSingleSubnodeIDx(spec, node, name));
    }

    Vec<N> getMultipleSubnode(const N& node, const Str& name) const {
        if (nodeRanges[node.getKind()].contains(name)) {
            Vec<N>     result;
            const auto range = nodeRanges.at(node.getKind()).at(name);
            const auto slice = range.toSlice(node.size());
            if (!slice.has_value()) {
                throw makeMissingSlice(node.getKind(), name, slice, range);
            }
            return result;
        } else {
            throw makeMissingPositional(node.getKind(), name);
        }
    }

    Opt<AstRange> fieldRange(const N& node, const int& idx) const {
        if (spec.at(node.getKind()).has_value()) {
            const auto pattern = spec.at(node.getKind()).value();
            for (const auto field : pattern.ranges) {
                if (field.range.contains(idx, node.size())) {
                    return field.range;
                }
            }
        }
        return std::nullopt;
    }

    Opt<Str> fieldName(const N& node, const int& idx) const {
        const auto field = fieldRange(node, idx);
        if (field.has_value()) {
            return field.value().fieldName;
        } else {
            return std::nullopt;
        }
    }

    bool isSingleField(const N& node, const int& idx) const {
        const auto field = fieldRange(node, idx);
        return field.has_value()
            && IntSet<
                   AstRangeKind>{AstRangeKind::Point, AstRangeKind::InversePoint}
                   .contains(field.value().kind);
    }

    Opt<Str> fieldDoc(const N& node, const int& idx) const {
        const auto field = fieldRange(node, idx);
        if (field.has_value()) {
            return field.value().fieldDoc;
        } else {
            return std::nullopt;
        }
    }
};


}; // namespace astspec
