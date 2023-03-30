#include <sem/SemConvert.hpp>
#include <hstd/stdlib/Func.hpp>

using namespace sem;
using namespace properties;

using org = OrgNodeKind;
using otk = OrgTokenKind;
using Err = OrgConverter::Errors;

template <typename T>
UPtr<T> Sem(sem::Org* parent, OrgAdapter adapter) {
    return std::make_unique<T>(parent, adapter);
}

#define __args Org *p, OrgAdapter a

UPtr<sem::Table> OrgConverter::convertTable(__args) {
    auto result = Sem<Table>(p, a);

    return result;
};


UPtr<sem::HashTag> OrgConverter::convertHashTag(__args) {
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

UPtr<sem::Subtree> OrgConverter::convertSubtree(__args) {
    auto tree = Sem<Subtree>(p, a);

    return tree;
}

UPtr<sem::StmtList> OrgConverter::convertStmtList(__args) {
    auto stmt = Sem<StmtList>(p, a);

    for (OrgAdapter const& sub : a) {
        stmt->push_back(convert(stmt.get(), sub));
    }

    return stmt;
}

UPtr<sem::Word> OrgConverter::convertWord(__args) {
    auto word = Sem<Word>(p, a);
    return word;
}

UPtr<sem::SkipNewline> OrgConverter::convertSkipNewline(__args) {
    return Sem<SkipNewline>(p, a);
}

UPtr<sem::Org> OrgConverter::convert(__args) {
    switch (a.kind()) {
        case org::SkipNewline: return convertSkipNewline(p, a); break;
        case org::StmtList: return convertStmtList(p, a); break;
        case org::Subtree: return convertSubtree(p, a); break;
        default: throw wrapError(Err::UnhandledKind(a.kind()), a);
    }
}
