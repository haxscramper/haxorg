#include <sem/SemConvert.hpp>
#include <hstd/stdlib/Ptrs.hpp>

using namespace sem;
using namespace properties;

UPtr<sem::Table> convertTable(Org* parent, OrgAdapter adapter) {
    auto result = std::make_unique<sem::Table>(parent, adapter);

    return result;
};
