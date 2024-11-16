#include "SemOrg.hpp"


void sem::SubtreeLog::setDescription(sem::SemId<sem::StmtList> desc) {
    CHECK(!desc.isNil());
    this->desc = desc;
}
