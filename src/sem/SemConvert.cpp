#include <sem/SemConvert.hpp>
#include <hstd/stdlib/Func.hpp>

using namespace sem;
using namespace properties;

UPtr<sem::Table> convertTable(Org* parent, OrgAdapter adapter) {
    auto result = std::make_unique<sem::Table>(parent, adapter);

    return result;
};


UPtr<sem::HashTag> convertHashTag(Org* parent, OrgAdapter adapter) {
    auto result = std::make_unique<sem::HashTag>(parent, adapter);
    Func<HashTag(OrgAdapter)> aux;
    result->head = strip(
        adapter.at(0).strVal(), CharSet{QChar('#')}, CharSet{});
    aux = [parent, &aux](OrgAdapter adapter) -> HashTag {
        HashTag result{parent, adapter};
        result.head = strip(
            adapter.at(0).strVal(), CharSet{QChar('#')}, CharSet{});
        if (1 < adapter.size()) {
            for (const auto& node : adapter.at(slice(1, 1_B))) {
                result.subtags.push_back(aux(node));
            }
        }
        return result;
    };

    if (1 < adapter.size()) {
        for (const auto& node : adapter.at(slice(1, 1_B))) {
            result->subtags.push_back(aux(node));
        }
    }

    return result;
};
