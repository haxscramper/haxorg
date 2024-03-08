#include "org_qml_model.hpp"
#include <hstd/stdlib/diffs.hpp>
#include <exporters/ExporterUltraplain.hpp>

OrgSubtreeSearchModel::OrgSubtreeSearchModel(
    OrgDocumentModel* baseModel,
    QObject*          parent)
    : QObject(parent)
    , filter(
          std::make_shared<OrgDocumentSearchFilter>(baseModel, parent)) {
    filter->acceptNode = [this](sem::OrgArg arg) -> bool {
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
    filter->invalidate();
    this->pattern = to_std(pattern);
    scoreCache.clear();
}

void OrgSubtreeSearchModel::setScoreSorted(bool sorted) {
    if (sorted) {
        filter->nodeLessThan =
            [this](sem::OrgArg lhs, sem::OrgArg rhs) -> bool {
            return getScore(lhs) < getScore(rhs);
        };
    } else {
        filter->nodeLessThan = nullptr;
    }
}

QVariant OrgDocumentModel::data(const QModelIndex& index, int role) const {

    if (!index.isValid()) { return QVariant(); }

    OrgNodeCursor* item = static_cast<OrgNodeCursor*>(
        index.internalPointer());

    if (item == nullptr) {
        return QVariant();
    } else {
        switch (role) {
            case Qt::DisplayRole: {
                return item->data(index.column());
            }

            case OrgNodeItemRole::KindRole: {
                return QString::fromStdString(fmt1(item->node->getKind()));
            }

            case OrgNodeItemRole::DataRole: {
                return item->getNodeHandle();
            }

            default: {
                return QVariant();
            }
        }
    }
}
