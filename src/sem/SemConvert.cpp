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

UPtr<sem::Table> OrgConverter::convertTable(
    Org*       parent,
    OrgAdapter adapter) {
    auto result = Sem<Table>(parent, adapter);

    return result;
};


UPtr<sem::HashTag> OrgConverter::convertHashTag(
    Org*       parent,
    OrgAdapter adapter) {
    auto                      result = Sem<HashTag>(parent, adapter);
    Func<HashTag(OrgAdapter)> aux;
    result->head = strip(
        adapter.at(0).strVal(), CharSet{QChar('#')}, CharSet{});
    aux = [parent, &aux](OrgAdapter adapter) -> HashTag {
        HashTag result{parent, adapter};
        result.head = strip(
            adapter.at(0).strVal(), CharSet{QChar('#')}, CharSet{});
        if (1 < adapter.size()) {
            for (auto& node : adapter.at(slice(1, 1_B))) {
                result.subtags.push_back(aux(node));
            }
        }
        return result;
    };

    if (1 < adapter.size()) {
        for (auto& node : adapter.at(slice(1, 1_B))) {
            result->subtags.push_back(aux(node));
        }
    }

    return result;
};

UPtr<sem::Subtree> OrgConverter::convertSubtree(
    sem::Org*  parent,
    OrgAdapter adapter) {}

UPtr<sem::StmtList> OrgConverter::convertStmtList(
    sem::Org*  parent,
    OrgAdapter adapter) {
    auto stmt = Sem<StmtList>(parent, adapter);

    for (OrgAdapter const& sub : adapter) {
        stmt->push_back(convert(stmt.get(), sub));
    }

    return stmt;
}


UPtr<sem::Org> OrgConverter::convert(
    sem::Org*  parent,
    OrgAdapter adapter) {
    switch (adapter.kind()) {
        case org::StmtList: return convertStmtList(parent, adapter); break;
        default:
            throw wrapError(Err::UnhandledKind(adapter.kind()), adapter);
    }
}
