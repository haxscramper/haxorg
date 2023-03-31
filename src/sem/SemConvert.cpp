#include <sem/SemConvert.hpp>
#include <hstd/stdlib/Func.hpp>
#include <parse/OrgSpec.hpp>

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
    auto result = Sem<Table>(p, a);

    return result;
};


Wrap<HashTag> OrgConverter::convertHashTag(__args) {
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
    auto tree   = Sem<Subtree>(p, a);
    tree->title = convertParagraph(tree.get(), one(a, N::Title));

    return tree;
}

Wrap<Time> OrgConverter::convertTime(__args) {
    auto time = Sem<Time>(p, a);

    return time;
}

Wrap<TimeRange> OrgConverter::convertTimeRange(__args) {
    auto range  = Sem<TimeRange>(p, a);
    range->from = convertTime(range.get(), one(a, N::From));
    range->to   = convertTime(range.get(), one(a, N::To));
    return range;
}

Wrap<Paragraph> OrgConverter::convertParagraph(__args) {
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
    return SemLeaf<Word>(p, a);
}

Wrap<SkipNewline> OrgConverter::convertSkipNewline(__args) {
    return SemLeaf<SkipNewline>(p, a);
}

Wrap<Space> OrgConverter::convertSpace(__args) {
    return SemLeaf<Space>(p, a);
}

Wrap<Punctuation> OrgConverter::convertPunctuation(__args) {
    return SemLeaf<Punctuation>(p, a);
}

Wrap<BigIdent> OrgConverter::convertBigIdent(__args) {
    return SemLeaf<BigIdent>(p, a);
}

Wrap<Link> OrgConverter::convertLink(__args) {
    auto link = Sem<Link>(p, a);

    return link;
}

Wrap<Org> OrgConverter::convert(__args) {
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
