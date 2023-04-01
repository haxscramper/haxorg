#include <sem/SemConvert.hpp>
#include <hstd/stdlib/Func.hpp>
#include <parse/OrgSpec.hpp>


#include <boost/preprocessor/facilities/overload.hpp>
#include <boost/preprocessor/facilities/empty.hpp>


#define __INIT_REPORT(__subname, __node)                                  \
    (Report{                                                              \
        .line     = __LINE__,                                             \
        .location = __CURRENT_FILE_PATH__,                                \
        .name     = __func__,                                             \
        .node     = __node,                                               \
        .subname  = __subname,                                            \
    })

#define __trace2(__subname, __lex)                                        \
    {                                                                     \
        Report rep = __INIT_REPORT(__subname, __lex);                     \
        rep.kind   = ReportKind::Enter;                                   \
        rep.name   = __func__;                                            \
        report(rep);                                                      \
    }                                                                     \
                                                                          \
    finally CONCAT(close, __COUNTER__) = finally::init<Str>(              \
        ([&](CR<Str> name) {                                              \
            Report rep = __INIT_REPORT(__subname, __lex);                 \
            rep.kind   = ReportKind::Leave;                               \
            rep.name   = name;                                            \
            report(rep);                                                  \
        }),                                                               \
        Str(__func__));


#define __trace1(__subname) __trace2(__subname, a)
#define __trace0() __trace2(std::nullopt, a)

#define __trace(...)                                                      \
    BOOST_PP_CAT(                                                         \
        BOOST_PP_OVERLOAD(__trace, __VA_ARGS__)(__VA_ARGS__),             \
        BOOST_PP_EMPTY())


#define __field3(__field, __subname, __lex)                               \
    {                                                                     \
        Report rep = __INIT_REPORT(__subname, __lex);                     \
        rep.kind   = ReportKind::EnterField;                              \
        rep.field  = __field;                                             \
        report(rep);                                                      \
    }                                                                     \
                                                                          \
    finally CONCAT(close, __COUNTER__) = finally::init<Str>(              \
        ([&](CR<Str> name) {                                              \
            Report rep = __INIT_REPORT(__subname, __lex);                 \
            rep.kind   = ReportKind::LeaveField;                          \
            rep.name   = name;                                            \
            rep.field  = __field;                                         \
            report(rep);                                                  \
        }),                                                               \
        Str(__func__));


#define __field2(__field, __subname) __field3(__field, __subname, a)
#define __field1(__field) __field3(__field, std::nullopt, a)

#define __field(...)                                                      \
    BOOST_PP_CAT(                                                         \
        BOOST_PP_OVERLOAD(__field, __VA_ARGS__)(__VA_ARGS__),             \
        BOOST_PP_EMPTY())


#define __json3(__org_node, __subname, __a)                               \
    {                                                                     \
        Report rep    = __INIT_REPORT(__subname, __a);                    \
        rep.kind      = ReportKind::Json;                                 \
        rep.semResult = (__org_node).get();                               \
        report(rep);                                                      \
    }

#define __json2(__org_node, __subname) __json3(__org_node, __subname, a);
#define __json1(__org_node) __json3(__org_node, std::nullopt, a);

#define __json(...)                                                       \
    BOOST_PP_CAT(                                                         \
        BOOST_PP_OVERLOAD(__json, __VA_ARGS__)(__VA_ARGS__),              \
        BOOST_PP_EMPTY())

using namespace sem;
using namespace properties;

using org = OrgNodeKind;
using otk = OrgTokenKind;
using Err = OrgConverter::Errors;

template <typename T>
Wrap<T> Sem(sem::Org* parent, OrgAdapter adapter) {
    return std::make_shared<T>(parent, adapter);
}

template <typename T>
Wrap<T> SemLeaf(sem::Org* parent, OrgAdapter adapter) {
    auto res  = Sem<T>(parent, adapter);
    res->text = adapter.strVal();
    return res;
}

#define __args Org *p, OrgAdapter a

using N = OrgSpecName;


OrgAdapter one(OrgAdapter node, OrgSpecName name) {
    return spec.getSingleSubnode(node, name);
}

Vec<OrgAdapter> many(OrgAdapter node, OrgSpecName name) {
    return spec.getMultipleSubnode(node, name);
}

Wrap<Table> OrgConverter::convertTable(__args) {
    __trace();
    auto result = Sem<Table>(p, a);

    return result;
};


Wrap<HashTag> OrgConverter::convertHashTag(__args) {
    __trace();
    auto                      result = Sem<HashTag>(p, a);
    Func<HashTag(OrgAdapter)> aux;
    result->head = strip(a.at(0).strVal(), CharSet{QChar('#')}, CharSet{});

    aux = [p, &aux](OrgAdapter a) -> HashTag {
        HashTag result{p, a};
        result.head = strip(
            a.at(0).strVal(), CharSet{QChar('#')}, CharSet{});
        if (1 < a.size()) {
            for (auto& node : a.at(slice(1, 1_B))) {
                result.subtags.push_back(aux(node));
            }
        }
        return result;
    };

    if (1 < a.size()) {
        for (auto& node : a.at(slice(1, 1_B))) {
            result->subtags.push_back(aux(node));
        }
    }

    return result;
};

Wrap<Subtree> OrgConverter::convertSubtree(__args) {
    __trace();
    auto tree = Sem<Subtree>(p, a);

    {
        __field(N::Title);
        tree->title = convertParagraph(tree.get(), one(a, N::Title));
    }

    { __field(N::Todo); }

    {
        __field(N::Body);
        for (auto const& sub : one(a, N::Body)) {
            tree->push_back(convert(tree.get(), sub));
        }
    }

    return tree;
}

Wrap<Time> OrgConverter::convertTime(__args) {
    __trace();
    auto time = Sem<Time>(p, a);


    __json(time);
    return time;
}

Wrap<TimeRange> OrgConverter::convertTimeRange(__args) {
    __trace();
    auto range = Sem<TimeRange>(p, a);
    {
        __field(N::From);
        range->from = convertTime(range.get(), one(a, N::From));
    }
    {
        __field(N::To);
        range->to = convertTime(range.get(), one(a, N::To));
    }
    return range;
}

Wrap<Paragraph> OrgConverter::convertParagraph(__args) {
    __trace();
    auto par = Sem<Paragraph>(p, a);
    for (const auto& item : a) {
        par->push_back(convert(par.get(), item));
    }

    return par;
}

Wrap<StmtList> OrgConverter::convertStmtList(__args) {
    auto stmt = Sem<StmtList>(p, a);

    for (OrgAdapter const& sub : a) {
        stmt->push_back(convert(stmt.get(), sub));
    }

    return stmt;
}

Wrap<Word> OrgConverter::convertWord(__args) {
    __trace();
    return SemLeaf<Word>(p, a);
}

Wrap<SkipNewline> OrgConverter::convertSkipNewline(__args) {
    __trace();
    return SemLeaf<SkipNewline>(p, a);
}

Wrap<Space> OrgConverter::convertSpace(__args) {
    return SemLeaf<Space>(p, a);
}

Wrap<Punctuation> OrgConverter::convertPunctuation(__args) {
    __trace();
    return SemLeaf<Punctuation>(p, a);
}

Wrap<BigIdent> OrgConverter::convertBigIdent(__args) {
    __trace();
    return SemLeaf<BigIdent>(p, a);
}

Wrap<Link> OrgConverter::convertLink(__args) {
    __trace();
    auto link = Sem<Link>(p, a);

    return link;
}

Wrap<Org> OrgConverter::convert(__args) {
    __trace();
#define CASE(Kind)                                                        \
    case org::Kind: return convert##Kind(p, a);
    switch (a.kind()) {
        CASE(SkipNewline);
        CASE(StmtList);
        CASE(Subtree);
        CASE(TimeRange);
        CASE(Time);
        CASE(Paragraph);
        CASE(Space);
        CASE(Word);
        CASE(Punctuation);
        CASE(Link);
        CASE(BigIdent);
        default: throw wrapError(Err::UnhandledKind(a.kind()), a);
    }
#undef CASE
}
