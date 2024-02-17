#include "org_qml_model.hpp"
#include <hstd/stdlib/diffs.hpp>
#include <exporters/ExporterUltraplain.hpp>

OrgSubtreeSearchModel::OrgSubtreeSearchModel(OrgDocumentModel* baseModel)
    : filter(baseModel) {
    filter.acceptNode = [this](sem::OrgArg arg) -> bool {
        bool score_ok = pattern.empty() || -1 < getScore(arg);
        bool result   = arg->is(OrgSemKind::Document)
                   || (arg->is(OrgSemKind::Subtree) && score_ok);
        return result;
    };

    setScoreSorted(true);
}

int OrgSubtreeSearchModel::getScore(sem::OrgArg arg) {
    u64 addr = (u64)arg.get();
    if (!scoreCache.contains(addr)) {
        FuzzyMatcher<char const> matcher;
        std::string              title = ExporterUltraplain::toStr(
            arg.as<sem::Subtree>()->title);
        scoreCache[addr] = matcher.get_score(title, pattern);
    }

    return scoreCache[addr];
}

void OrgSubtreeSearchModel::setPattern(CR<QString> pattern) {
    filter.invalidate();
    this->pattern = to_std(pattern);
    scoreCache.clear();
}

void OrgSubtreeSearchModel::setScoreSorted(bool sorted) {
    if (sorted) {
        filter.nodeLessThan =
            [this](sem::OrgArg lhs, sem::OrgArg rhs) -> bool {
            return getScore(lhs) < getScore(rhs);
        };
    } else {
        filter.nodeLessThan = nullptr;
    }
}
