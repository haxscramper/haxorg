#include "org_document_model.hpp"
#include <hstd/stdlib/diffs.hpp>
#include <exporters/ExporterUltraplain.hpp>
#include <sem/SemBaseApi.hpp>
#include <QLabel>
#include <QTextEdit>
#include "org_exporter_html.hpp"

OrgSubtreeSearchModel::OrgSubtreeSearchModel(
    OrgDocumentModel* baseModel,
    QObject*          parent,
    OrgStore*         store)
    : QObject(parent)
    , filter(
          std::make_shared<OrgDocumentSearchFilter>(baseModel, parent)) {
    filter->acceptNode = [this](OrgBoxId arg) -> bool {
        auto const& node     = this->store->node(arg);
        bool        score_ok = pattern.empty() || -1 < getScore(arg);
        bool        result   = node->is(OrgSemKind::Document)
                   || (node->is(OrgSemKind::Subtree) && score_ok);
        return result;
    };

    setScoreSorted(true);
}

int OrgSubtreeSearchModel::getScore(OrgBoxId arg) {
    auto const& node = store->node(arg);
    u64         addr = (u64)node.get();
    if (!scoreCache.contains(addr)) {
        FuzzyMatcher<char const> matcher;
        std::string              title = ExporterUltraplain::toStr(
            node.as<sem::Subtree>()->title);
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
        filter->nodeLessThan = [this](OrgBoxId lhs, OrgBoxId rhs) -> bool {
            return getScore(lhs) < getScore(rhs);
        };
    } else {
        filter->nodeLessThan = nullptr;
    }
}

void OrgDocumentModel::loadFile(const fs::path& path) {
    auto document = sem::parseFile(path, sem::OrgParseParameters{});
    this->root = std::make_unique<TreeNode>(store->add(document), nullptr);
    buildTree(this->root.get());
}

QWidget* make_label(Str const& node) {
    auto label = new QTextEdit();
    label->setText(QString::fromStdString(node));
    label->setSizePolicy(
        QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
    label->setMinimumHeight(20);
    return label;
}


QWidget* make_label(sem::OrgArg node) {
    ExporterHtml exp;
    auto         html_tree = exp.evalTop(node);
    return make_label(exp.store.toString(html_tree));
}

QVariant OrgDocumentModel::data(const QModelIndex& index, int role) const {
    if (!index.isValid()) { return QVariant(); }
    TreeNode* node = static_cast<TreeNode*>(index.internalPointer());
    if (role == Qt::DisplayRole) {
        sem::OrgArg res = store->node(node->boxId);
        switch (res->getKind()) {
            case OrgSemKind::Subtree: {
                return QVariant::fromValue(
                    make_label(res.as<sem::Subtree>()->title));
            }
            case OrgSemKind::Paragraph: {
                return QVariant::fromValue(make_label(res));
            }
            default: {
                return QVariant::fromValue(
                    make_label(fmt1(res->getKind())));
            }
        }
    } else if (role == Qt::EditRole) {
        return QVariant::fromValue(node->boxId);
    } else {
        return QVariant();
    }
}

sem::SemId<sem::Org> copy(sem::OrgArg node) {
    switch (node->getKind()) {
#define _case(__Kind)                                                     \
    case OrgSemKind::__Kind: {                                            \
        sem::SemId<sem::__Kind> new_id = sem::SemId<sem::__Kind>::New();  \
        *new_id.get()                  = *node.getAs<sem::__Kind>();      \
        return new_id.asOrg();                                            \
    }
        EACH_SEM_ORG_KIND(_case)
#undef _case
    }
}
