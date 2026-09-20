#include "SemOrg.hpp"


void org::sem::SubtreeLog::setDescription(sem::SemId<sem::StmtList> desc) {
    LOGIC_ASSERTION_CHECK(!desc.isNil(), "");
    this->desc = desc;
}
