#pragma once

#include <hstd/stdlib/Vec.hpp>
#include <hstd/stdlib/IntSet.hpp>
#include <unordered_map>
#include <stdexcept>
#include <functional>
#include <optional>

enum class AstRangeKind
{
    akPoint,        /*!`idx` */
    akInversePoint, /*!`^idx` */
    akDirectSlice,  /*!`idx1 .. idx2` */
    akInverseSlice, /*!`^idx1 .. ^idx2` */
    akMixedSlice,   /*!`idx1 .. ^idx2` */
};

struct AstRange {
    bool         optional; /*!Whether the field is optional */
    Str          doc;      /*!Documentation for a field */
    Str          name;     /*!Field name */
    AstRangeKind kind;

    int idx;    /*!Single subnode with either direct or inverse index */
    int start;  /*!Start of the subnode range, left part of `..` */
    int finish; /*!End of the subnode range, right part of `..` */
};

template <typename K>
struct AstCheckFail {
    bool                 isMissing;
    Str                  msg;
    Vec<int>             path;
    K                    parent;
    IntSet<K>            expected;
    std::optional<K>     got;
    AstRange             arange;
    Vec<AstCheckFail<K>> nested;
};

struct AstCheckError : public std::runtime_error {};


template <typename N, typename K>
// std::option<AstCheckFail<K>>(N)
using AstCheckProc = std::function<std::optional<AstCheckFail<K>>(N)>;


template <typename N, typename K>
struct AstPattern;

template <typename N, typename K>
using AstPatternRange = std::tuple<AstRange, Vec<AstPattern<N, K>>>;

template <typename N, typename K>
struct AstPattern {
    Str                        doc;
    AstCheckProc<N, K>         check;
    IntSet<K>                  expected;
    Vec<AstPatternRange<N, K>> ranges;
};

template <typename N, typename K>
struct AstSpec {
    TypArray<K, std::optional<AstPattern<N, K>>> spec;
};

template <typename N, typename K>
AstSpec<N, K> astSpec(const Vec<Pair<K, AstPattern<N, K>>>& patterns) {
    AstSpec<N, K> result;
    for (const auto& [kind, pattern] : patterns) {
        result.spec[kind] = some(pattern);
    };
    return result;
};

template <typename N, typename K>
AstPattern<N, K> getPattern(const AstSpec<N, K>& spec, const K& kind) {
    AstPattern<N, K> result;
    spec.spec[kind].get();
    return result;
};

template <typename N, typename K>
TypArray<K, std::unordered_map<std::string, AstRange>> getNodeRanges(
    const AstSpec<N, K>& spec) {
    TypArray<K, std::unordered_map<std::string, AstRange>> result;
    for (const auto [kind, pattern] : spec.spec) {
        if (pattern.isSome()) {
            for (const auto arange : pattern.get().ranges) {
                if (((arange.arange.name.len) > (0))) {
                    result[kind][arange.arange.name] = arange.arange;
                }
            }
        }
    }
    return result;
}

template <typename N, typename K>
int getSingleSubnodeIdx(
    const AstSpec<N, K>&      spec,
    const K&                  kind,
    const Str&                name,
    const std::optional<int>& nodeLen = none(int)) {
    int result;
    /* TODO CONST SECTION */;
    if (((name)in(table[kind]))) {
        const auto arange = table[kind][name];
        if (((arange.kind) == (akPoint))) {
            return arange.idx;
        } else if (nodeLen.isSome()) {
            return arange.toSlice(nodeLen.get()).a;
        } else {
            throw newUnexpectedKindError(
                R"(Cannot get single subnode index for element )",
                mq(name),
                R"( of node kind )",
                mkind(kind),
                R"( - field exists, but allowed AST range is of kind )",
                mkind(arange.kind),
                R"( and requires node lenght, but it )",
                R"(wasn't specified.)");
        }
    } else {
        noPositional(spec, kind, name);
    }
    return result;
}

template <typename N, typename K>
int getSingleSubnodeIdx(
    const AstSpec<N, K>& spec,
    const N&             node,
    const Str&           name) {
    int result;
    if (((name)in(table[node.kind]))) {
        const auto arange = table[node.kind][name];
        const auto slice  = arange.toSlice(len(node));
        assertHasIdx(
            node,
            slice.a,
            (&({R"(Range )",
                name,
                R"( for node kind )",
                toStr(node.kind),
                R"( was resolved into slice )",
                toStr(slice),
                R"((required ast range is )",
                toStr(arange),
                R"())"})));
        return slice.a;
    } else {
        noPositional(spec, node.kind, name);
    };
    return result;
};

template <typename N, typename K>
N getSingleSubnode(
    const AstSpec<N, K>& spec,
    const N&             node,
    const Str&           name) {
    N result;
    node[getSingleSubnodeIDx(spec, node, name)];
    return result;
}

template <typename N, typename K>
Vec<N> getMultipleSubnode(
    const AstSpec<N, K>& spec,
    const N&             node,
    const Str&           name) {
    Vec<N> result;
    if (((name)in(table[node.kind]))) {
        const auto arange = table[node.kind][name];
        const auto slice  = arange.toSlice(len(node));
        for (const auto idx : slice) {
            assertHasIdx(
                node,
                idx,
                (&({R"(Range )",
                    name,
                    R"( for node kind )",
                    toStr(node.kind),
                    R"( was resolved into slice )",
                    toStr(slice),
                    R"((required ast range is )",
                    toStr(arange),
                    R"())"})));
            result.add(node[idx]);
        }
    } else {
        noPositional(spec, node.kind, name);
    }
    return result;
}

template <typename N, typename K>
std::optional<AstRange> fieldRange(
    const AstSpec<N, K>& spec,
    const N&             node,
    const int&           idx) {
    std::optional<AstRange> result;
    if (spec.spec[node.kind].isSome()) {
        const auto pattern = spec.spec[node.kind].get();
        for (const auto field : pattern.ranges) {
            if (field.arange.contains(idx, node.len)) {
                return some(field.arange);
            }
        }
    }
    return result;
}

template <typename N, typename K>
std::optional<string> fieldName(
    const AstSpec<N, K>& spec,
    const N&             node,
    const int&           idx) {
    std::optional<string> result;
    const auto            field = spec.fieldRange(node, idx);
    if (field.isSome()) {
        return some(field.get().name);
    }
    return result;
}

template <typename N, typename K>
bool isSingleField(
    const AstSpec<N, K>& spec,
    const N&             node,
    const int&           idx) {
    bool       result;
    const auto field = spec.fieldRange(node, idx);
    return (
        (field.isSome())
        && (((field.get().kind)in({akPoint, akInversePoint}))));
    return result;
}

template <typename N, typename K>
std::optional<string> fieldDoc(
    const AstSpec<N, K>& spec,
    const N&             node,
    const int&           idx) {
    std::optional<string> result;
    const auto            field = spec.fieldRange(node, idx);
    if (field.isSome()) {
        return some(field.get().doc);
    }
    return result;
}

Slice<int> toSlice(const AstRange& arange, const int& maxLen) {
    Slice<int> result;
    switch (arange.kind) {
        case akPoint: {
            slice(arange.idx, arange.idx);
            break;
        }
        case akInversePoint: {
            slice(maxLen - arange.idx, maxLen - arange.idx);
            break;
        }
        case akDirectSlice: {
            slice(arange.start, arange.finish);
            break;
        }
        case akInverseSlice: {
            slice(maxLen - arange.start, maxLen - arange.finish);
            break;
        }
        case akMixedSlice: {
            slice(arange.start, maxLen - arange.finish);
            break;
        }
    };
    return result;
};

bool contains(const AstRange& arange, const int& idx const int& maxLen, ) {
    bool result;
    ((idx)in(toSlice(arange, maxLen)));
    return result;
};


std::ostream& operator<<(std::ostream& os, AstRange const& arange) {
    string result;
    switch (arange.kind) {
        case akPoint: return os << arange.idx;
        case akInversePoint: return os << "^" << arange.idx;
        case akDirectSlice:
            return os << arange.start << ".." << arange.finish;
        case akInverseSlice:
            return os << "^" << arange.start << "..^" << arange.finish;
        case akMixedSlice:
            return os << arange.start << "..^" << arange.finish;
    }
}

template <typename N, typename K>
string operator $(const AstPattern<N, K>& spec) {
    string result;
    result.add(toStr(spec.expected));
    return result;
};

template <typename N>
string toPath(const N& ast, const Vec<int>& path) {
    string result;
    constexpr if (((ast)is(/* REF TYPECLASS */))) {
        if (isNil(ast)) {
            return strutils.join(
                path.mapIt(((((R"([)") & (toStr(it)))) & (R"(])"))),
                R"(.)");
            ;
        };
    };
    /* MIXIN mixin `[]` */;

    seq[string] aux(const N& a, const Vec<int>& path) {
        seq[string] result;
        result.add(toStr(a.kind));
        if (((path.len) > (1))) {
            result.add(aux(a[path[0]], path[((1)..^ (1))]));
        } else if (((path.len) == (1))) {
            result.add(((((R"([)") & (toStr(path[0])))) & (R"(])")));
        };
        return result;
    };
    return strutils.join(aux(ast, path), R"(.)");
    ;
    return result;
};

template <typename K>
bool isEmpty(const AstCheckFail<K>& fail, const bool& withNested = true) {
    bool result;
    ((((((fail.isMissing.!()) && (((fail.msg.len) == (0)))))
       && (((fail.expected.len) == (0)))))
     && (/* FIXME STMT LIST EXPR */
         else { withNested } else {true}));
    return result;
};

template <typename K>
int failCount(const AstCheckFail<K>& fail) {
    int result;
    for (const auto nested : fail.nested) {
        ((result) += (nested.failCount));
    };
    if (((fail.isMissing)
         || ((
             ((((fail.msg.len) > (0)))
              || (((fail.expected.len) > (0)))))))) {
        += result;
    };
    return result;
};

template <typename N, typename K>
AstCheckFail[K] findMissing(
    const AstPattern<N, K>& spec,
    const N&                node,
    const Vec<int>&         path = (@({}))) {
    AstCheckFail[K] result;
    result.path = path;
    ;
    if (((spec.ranges.len) > (0))) {

        auto altFound = newSeqWith(spec.ranges.len, false);
        ;
        ;

        auto idx = 0;
        ;
        ;
        while (((idx) < (node.len))) {
            for (const auto [rangeIdx, arange] : spec.ranges) {
                if (arange.arange.contains(idx, node.len)) {
                    altFound[rangeIdx] = true;
                    ;
                    for (const auto alt : arange.alts) {

                        const auto n = findMissing(
                            alt, node, ((path) & ((@({idx})))));
                        ;
                        ;
                        if ((!(n.isEmpty()))) {
                            result.nested.add(n);
                        };
                    };
                    break;
                    ;
                };
            };
            += idx;
        };
        for (const auto [rangeIdx, found] : altFound) {
            if (((((!(found))))
                 && (((!(spec.ranges[rangeIdx].arange.optional)))))) {

                IntSet<K> expected;
                ;
                ;
                for (const auto alt : spec.ranges[rangeIdx].alts) {
                    expected.incl(alt.expected);
                };
                result.nested.add(AstCheckFail[K]{
                    .isMissing = true,
                    .parent    = node.kind,
                    .path      = ((path) & (rangeIdx)),
                    .arange    = spec.ranges[rangeIdx].arange,
                    .expected  = expected,
                });
            };
        };
    };
    return result;
};

template <typename N, typename K>
AstCheckFail[K] validateAst(
    const AstPattern<N, K>& spec,
    const K& kind const K&  subnode,
    ,
    const int&      idx,
    const int&      maxLen,
    const Vec<int>& path = (@({}))) {
    AstCheckFail[K] result;
    result.path = path;
    ;
    for (const auto arange : spec.ranges) {
        if (arange.arange.contains(idx, maxLen)) {
            for (const auto alt : arange.alts) {
                if (((subnode)notin(alt.expected))) {
                    result.nested.add(AstCheckFail[K]{
                        .parent   = kind,
                        .path     = path,
                        .expected = alt.expected,
                        .got      = some(subnode),
                        .arange   = arange.arange,
                    });
                };
            };
        };
    };
    return result;
};

template <typename N, typename K>
ColoredText treeRepr(const AstSpec<N, K>& spec) {
    ColoredText result;
    coloredResult();

    void aux(const AstPattern<N, K>& p, const int& level) {
        addIndent(level);
        if (((p.doc.len) > (0))) {
            add(toYellow(p.doc.indent(((level) + (1)))));
        };
        if (((p.expected.len) > (0))) {
            add(hshow(p.expected));
        };
        for (const auto arange : p.ranges) {
            add(R"(\n)");
            addIndent(((level) + (1)));
            add(toYellow(toStr(arange.arange)));
            if (((arange.arange.name.len) > (0))) {
                add(R"( )");
                add(toBlue(arange.arange.name));
            };
            for (const auto alt : arange.alts) {
                add(R"(\n)");
                aux(alt, ((level) + (2)));
            };
        };
    };
    for (const auto [kind, pattern] : pairs(spec.spec)) {
        if (pattern.isSome()) {
            add(hshow(kind));
            add(R"(\n)");
            aux(pattern.get(), 1);
            add(R"(\n)");
        };
    };
    endResult();
    return result;
};

template <typename N, typename K>
ColoredText formatFail(const AstCheckFail<K>& fail, const N& node) {
    ColoredText result;
    coloredResult();
    if (((failCount(fail)) == (0))) {
        endResult();
    };

    void aux(const AstCheckFail<K>& fail, const int& level) {
        addIndent(level);

        auto parentFailed = false;
        ;
        ;
        if ((!(fail.isEmpty(withNested = false)))) {
            parentFailed = true;
            ;
            if (((fail.msg.len) > (0))) {
                add(fail.msg);
                add(R"( )");
            };
            if (((fail.expected.len) > (0))) {
                if (fail.isMissing) {
                    add(R"(missing subnode )");
                    add(toGreen(toStr(fail.arange)));
                    if (((fail.arange.name.len) > (0))) {
                        add(R"( ()");
                        add(toCyan(fail.arange.name));
                        add(R"())");
                    };
                    add(R"( )");
                    add(toRed(toStr(fail.expected)));
                } else {
                    add(R"(wanted )");
                    add(toRed(toStr(fail.expected)));
                    add(R"( in )");
                    add(toGreen(toStr(fail.arange)));
                    if (((fail.arange.name.len) > (0))) {
                        add(R"( ()");
                        add(toCyan(fail.arange.name));
                        add(R"())");
                    };
                    if (fail.got.isSome()) {
                        add(R"(, but got )");
                        add(hshow(fail.got.get()));
                    };
                };
            } else if (fail.isMissing) {
                add(R"(missing subnode )");
                add(toGreen(toStr(fail.arange)));
                if (((fail.arange.name.len) > (0))) {
                    add(R"( ()");
                    add(toCyan(fail.arange.name));
                    add(R"())");
                };
            };
            if (((fail.path.len) > (0))) {
                add(R"( on path )");
                add(toPath(node, fail.path).toGreen());
            } else {
                add(R"( for )");
                add(toGreen(toStr(fail.parent)));
            };
            if (((fail.arange.doc.len) > (0))) {
                add(R"(\n)");
                add(fail.arange.doc.indent(((((level) * (2))) + (2)))
                        .toYellow());
            };
        };

        auto idx = 0;
        ;
        ;
        for (const auto nested : items(fail.nested)) {
            if ((((!(nested.isEmpty())))
                 && (((failCount(nested)) > (0))))) {
                if (((idx) > (0))) {
                    add(R"(\n)");
                };
                aux(nested, tern(parentFailed, ((level) + (1)), level));
                += idx;
            };
        };
    };
    aux(fail, 0);
    endResult();
    return result;
};

template <typename N, typename K>
ColoredText validateAst(
    const AstSpec<N, K>& spec,
    const N&             node,
    const N&             subnode,
    const int&           idx) {
    ColoredText result;
    if (spec.spec[node.kind].isSome()) {

        const auto fail1 = validateAst(
            spec.spec[node.kind].get(),
            node.kind,
            subnode.kind,
            idx,
            node.len,
            (@({idx})));
        ;
        ;
        if (((failCount(fail1)) > (0))) {
            result.add(formatFail(fail1, node));
            result.add(R"(\n)");
        };
        result.add(formatFail(
            findMissing(spec.spec[node.kind].get(), node), node));
    };
    return result;
};

template <typename N, typename K>
std::optional[ColoredText] validateSub(
    const AstPattern<N, K>& spec,
    const K& node const K&  sub,
    ,
    const int& idx const int& maxIdx, ) {
    std::optional[ColoredText] result;

    const auto fail = formatFail(
        validateAst(spec, node, sub, idx, maxIdx, (@({idx}))),
        N(/* NIL LIT */));
    ;
    ;
    if (((fail.len()) > (0))) {
        return some(fail);
        ;
    };
    return result;
};

template <typename N, typename K>
std::optional<ColoredText> validateSub(
    const AstSpec<N, K>& spec,
    const N&             node,
    const int&           idx,
    const N&             sub) {
    std::optional<ColoredText> result;
    if (spec.spec[node.kind].isSome()) {

        const auto fail = formatFail(
            validateAst(
                spec.spec[node.kind].get(),
                node.kind,
                sub.kind,
                idx,
                node.len),
            node);
        if (fail.len() > 0) {
            return some(fail);
        }
    }
    return result;
}

template <typename N, typename K>
std::optional[ColoredText] validateSub(
    const AstSpec<N, K>& spec,
    const N&             node,
    const int&           idx) {
    std::optional[ColoredText] result;
    validateSub(spec, node, idx, node[idx]);
    return result;
};

template <typename N, typename K>
std::optional[ColoredText] validateSelf(
    const AstSpec<N, K>& spec,
    const N&             node) {
    std::optional[ColoredText] result;
    if (spec.spec[node.kind].isSome()) {

        const auto findMissing = findMissing(
            spec.spec[node.kind].get(), node);
        if (failCount(findMissing) > 0) {
            const auto fail = formatFail(findMissing, node);
            if (fail.len() > 0) {
                return some(fail);
            };
        };
    };
    return result;
};

template <typename N, typename K>
ColoredText validateAst(const AstSpec<N, K>& spec, const N& node) {
    ColoredText result;
    if (spec.spec[node.kind].isSome()) {
        result.add(formatFail(
            findMissing(spec.spec[node.kind].get(), node), node));
    };
    return result;
};
