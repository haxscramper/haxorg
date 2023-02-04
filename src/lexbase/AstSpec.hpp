#pragma once

#include <hstd/stdlib/Vec.hpp>
#include <hstd/stdlib/IntSet.hpp>
#include <hstd/stdlib/ColorText.hpp>
#include <hstd/stdlib/Func.hpp>
#include <hstd/stdlib/Opt.hpp>
#include <hstd/stdlib/Table.hpp>

#include <unordered_map>
#include <stdexcept>
#include <functional>

struct GetterError : public std::runtime_error {
    explicit GetterError(const std::string& message)
        : std::runtime_error(message) {}
};

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

    Slice<int> toSlice(const int& maxLen) const {
        switch (kind) {
            case AstRangeKind::Point: return slice(idx, idx);
            case AstRangeKind::InversePoint:
                return slice(maxLen - idx, maxLen - idx);
            case AstRangeKind::DirectSlice: return slice(first, last);
            case AstRangeKind::InverseSlice:
                return slice(maxLen - first, maxLen - last);
            case AstRangeKind::MixedSlice:
                return slice(first, maxLen - last);
        }
    }

    bool contains(const int& idx, const int& maxLen) const {
        return toSlice(maxLen).contains(idx);
    }
};

template <typename N, typename K>
struct AstCheckFail {
    bool      isMissing;
    Str       msg;
    Vec<int>  path;
    K         parent;
    IntSet<K> expected;
    Opt<K>    got;
    AstRange  range;

    AstCheckFail() {}

    Vec<AstCheckFail<N, K>> nested;


    bool isEmpty(const bool& withNested = true) const {
        return !isMissing && msg.size() == 0 && expected.size() == 0
            && (withNested ? nested.size() == 0 : true);
    }

    int count() const {
        int result;
        for (const auto& nested : nested) {
            result += nested.count();
        }
        if (isMissing || 0 < msg.size() || 0 < expected.size()) {
            ++result;
        }
        return result;
    };


    ColText format(const N& node) const {
        if (count() == 0) {
            return ColText{};
        }

        using fg = TermColorFg8Bit;
        ColStream s;

        Func<void(const AstCheckFail<N, K>&, const int&)> aux;

        aux = [&s, &aux, &node](
                  const AstCheckFail<N, K>& fail, const int& level) {
            s.indent(level);
            auto parentFailed = false;
            if (!fail.isEmpty(false)) {
                parentFailed = true;
                if (0 < fail.msg.size()) {
                    s << fail.msg << " ";
                }
                if (0 < fail.expected.size()) {
                    if (fail.isMissing) {
                        s << "missing subnode " << fg::Green << fail.range
                          << s.end();
                        if (0 < fail.range.fieldName.size()) {
                            s << " (" << fg::Green << fail.range.fieldName
                              << s.end() << ")";
                        }
                        s << " " << fg::Red << fail.expected << s.end();
                    } else {
                        s << "wanted " << fg::Red << fail.expected
                          << s.end() << " in " << fg::Green << fail.range
                          << s.end();

                        if (0 < fail.range.fieldName.size()) {
                            s << " (" << fg::Green << fail.range.fieldName
                              << s.end() << ")";
                        }

                        if (fail.got.has_value()) {
                            s << ", but got "
                              << hshow(s, fail.got.value());
                        }
                    }
                } else if (fail.isMissing) {
                    s << "missing subnode " << fg::Cyan << fail.range
                      << s.end();
                    if (0 < fail.range.fieldName.size()) {
                        s << " (" << fg::Cyan << fail.range.fieldName
                          << s.end() << ")";
                    }
                }

                if (0 < fail.path.size()) {
                    s << " on path " << fg::Green
                      << toPath(node, fail.path) << s.end();
                } else {
                    s << " for " << fg::Green << fail.parent << s.end();
                }

                if (0 < fail.range.fieldDoc.size()) {
                    s << "\n"
                      << fg::Yellow
                      << indent(fail.range.fieldDoc, (level * 2) + 2)
                      << s.end();
                }
            }

            auto idx = 0;
            for (const auto& nested : fail.nested) {
                if (!nested.isEmpty() && 0 < nested.count()) {
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
            if (arange.arange.contains(idx, maxLen)) {
                for (const auto alt : arange.alts) {
                    if (alt.expected.contains(subnode)) {
                        result.nested.add(AstCheckFail<N, K>{
                            .parent   = kind,
                            .path     = path,
                            .expected = alt.expected,
                            .got      = some(subnode),
                            .arange   = arange.arange,
                        });
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
        if (0 < ranges.size()) {
            auto altFound = Vec(ranges.size(), false);
            auto idx      = 0;
            while (idx < node.size()) {
                for (const auto [rangeIdx, arange] : enumerate(ranges)) {
                    if (arange.range.contains(idx, node.size())) {
                        altFound[rangeIdx] = true;
                        for (const auto alt : arange.alts) {
                            const auto& n = alt.findMissing(
                                node, path + idx);
                            if (!n.isEmpty()) {
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

        Opt<ColText> result;
        const auto   fail = formatFail(
            validateAst(node, sub, idx, maxIdx, {idx}), N());

        if (0 < fail.size()) {
            return fail;
        } else {
            return std::nullopt;
        }
    }
};

template <typename N, typename K>
struct AstSpec {
    TypArray<K, Opt<AstPattern<N, K>>> spec;

    AstSpec(const Vec<Pair<K, AstPattern<N, K>>>& patterns) {
        for (const auto& [kind, pattern] : patterns) {
            spec[kind] = pattern;
        }
    }

    AstPattern<N, K> getPattern(const K& kind) const {
        return spec[kind].get();
    }

    bool hasPattern(K kind) const { return spec[kind].has_value(); }

    TypArray<K, Table<Str, AstRange>> getNodeRanges() const {
        TypArray<K, Table<Str, AstRange>> result;
        for (const auto& [kind, pattern] : spec) {
            if (pattern.has_value()) {
                for (const auto& arange : pattern.get().ranges) {
                    if (0 < arange.arange.name.size()) {
                        result[kind][arange.arange.name] = arange.arange;
                    }
                }
            }
        }
        return result;
    }


    ColText validateAst(const N& node) const {
        if (spec[node.kind].has_value()) {
            return formatFail(
                spec[node.kind].value().findMissing(node), node);
        } else {
            return ColText{};
        }
    }

    Opt<ColText> validateSelf(const N& node) const {
        Opt<ColText> result;
        if (spec[node.getKind()].has_value()) {
            const auto missing = spec[node.getKind()].value().findMissing(
                node);
            if (0 < missing.count()) {
                const auto fail = missing.format(node);
                if (0 < fail.size()) {
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
            const auto fail = formatFail(
                spec[node.getKind()].value().validateAst(
                    node.getKind(), sub.getKind(), idx, node.size()),
                node);
            if (0 < fail.size()) {
                return fail;
            }
        }
        return std::nullopt;
    }


    Opt<ColText> validateSub(const N& node, const int& idx) const {
        return validateSub(node, idx, node[idx]);
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

            if (0 < failCount(fail1)) {
                s << formatFail(fail1, node) << "\n";
            }

            s << formatFail(
                findMissing(spec[node.getKind()].value(), node), node);
        }

        return s.getBuffer();
    }

    ColText treeRepr() const {
        using fg = TermColorFg8Bit;

        ColStream s;

        Func<void(const AstPattern<N, K>&, const int&)> aux;

        aux = [&s, &aux](const AstPattern<N, K>& p, const int& level) {
            s.indent(level);
            if (0 < p.doc.size()) {
                s << fg::Yellow << indent(p.doc, 2 * (level + 1))
                  << s.end();
            }

            if (0 < p.expected.size()) {
                s << to_string(p.expected);
            }

            for (const auto arange : p.ranges) {
                s << "\n" << s.indent(level + 1);
                s << fg::Yellow << arange.range << s.end();
                if (0 < arange.range.fieldName.size()) {
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

    int getSingleSubnodeIdx(const N& node, const Str& name) {
        int        result;
        const auto table = getNodeRanges(spec);
        if (table[node.getKind()].contains(name)) {
            const auto arange = table[node.getKind()][name];
            const auto slice  = arange.toSlice(len(node));
            assertHasIdx(
                node,
                slice.a,
                "Range " + name + " for node kind "
                    + to_string(node.getKind())
                    + " was resolved into slice " + to_string(slice)
                    + "(required ast range is " + to_string(arange) + ")");
            return slice.a;
        } else {
            noPositional(spec, node.getKind(), name);
        }
        return result;
    }

    N getSingleSubnode(const N& node, const Str& name) {
        return node[getSingleSubnodeIDx(spec, node, name)];
    }

    Vec<N> getMultipleSubnode(const N& node, const Str& name) {
        Vec<N> result;

        const auto table = getNodeRanges(spec);
        if (table[node.getKind()].contains(name)) {
            const auto arange = table[node.getKind()][name];
            const auto slice  = arange.toSlice(len(node));
            for (const auto idx : slice) {
                assertHasIdx(
                    node,
                    idx,
                    "Range " + name + " for node kind "
                        + to_string(node.getKind())
                        + " was resolved into slice " + to_string(slice)
                        + "(required ast range is " + to_string(arange)
                        + ")");
                result.add(node[idx]);
            }
        } else {
            noPositional(spec, node.getKind(), name);
        }
        return result;
    }

    Opt<AstRange> fieldRange(const N& node, const int& idx) {
        Opt<AstRange> result;
        if (spec.spec[node.getKind()].has_value()) {
            const auto pattern = spec.spec[node.getKind()].get();
            for (const auto field : pattern.ranges) {
                if (field.arange.contains(idx, node.size())) {
                    return some(field.arange);
                }
            }
        }
        return result;
    }

    Opt<Str> fieldName(const N& node, const int& idx) {
        Opt<Str>   result;
        const auto field = spec.fieldRange(node, idx);
        if (field.has_value()) {
            return some(field.value().name);
        }
        return result;
    }

    bool isSingleField(const N& node, const int& idx) {
        const auto field = spec.fieldRange(node, idx);
        return field.has_value()
            && (IntSet<AstRangeKind>{
                    AstRangeKind::Point, AstRangeKind::InversePoint})
                   .contains(field.value().getKind());
    }

    Opt<Str> fieldDoc(const N& node, const int& idx) {
        Opt<Str>   result;
        const auto field = spec.fieldRange(node, idx);
        if (field.has_value()) {
            return some(field.value().doc);
        }
        return result;
    }

    int getSingleSubnodeIdx(
        const K&        kind,
        const Str&      name,
        const Opt<int>& nodeLen = Opt<int>{}) {
        const auto table = getNodeRanges();
        if (table[kind].contains(name)) {
            const auto arange = table[kind][name];
            if (arange.getKind() == AstRangeKind::Point) {
                return arange.idx;
            } else if (nodeLen.has_value()) {
                return arange.toSlice(nodeLen.value()).a;
            } else {
                throw newUnexpectedKindError(
                    "Cannot get single subnode index for element " + name
                    + " of node kind " + kind
                    + " - field exists, but allowed AST range is of kind "
                    + arange.getKind()
                    + " and requires node lenght, but it "
                    + "wasn't specified.");
            }
        } else {
            noPositional(spec, kind, name);
        }
    }
};


std::ostream& operator<<(std::ostream& os, AstRange const& arange) {
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


}; // namespace astspec
