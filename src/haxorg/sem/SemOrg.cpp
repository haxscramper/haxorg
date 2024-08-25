#include "SemOrg.hpp"


void sem::SubtreeLog::setDescription(sem::SemId<sem::StmtList> desc) {
    CHECK(!desc.isNil());
    std::visit(
        overloaded{
            [](Clock&) {},
            [&](auto& value) { value.desc = desc; },
        },
        log);
}
