#include "SemAstDiff.hpp"

int OrgNodeStore::getSubnodeCount(const Id& id) {
    auto n = get(id);
    switch (n->getKind()) {
        case OrgSemKind::Table: {
            return n->dyn_cast<sem::Table>()->rows.size();
        }
        case OrgSemKind::Row: {
            return n->dyn_cast<sem::Row>()->cells.size();
        }
        default: {
            return get(id)->subnodes.size();
        }
    }
}

diff::NodeStore::Id OrgNodeStore::getSubnodeAt(const Id& node, int index) {
    auto n = get(node);
    switch (n->getKind()) {
        case OrgSemKind::Row: {
            return NodeStore::Id::FromPtr(
                n->dyn_cast<sem::Row>()->cells.at(index).get());
        }
        case OrgSemKind::Table: {
            return NodeStore::Id::FromPtr(
                n->dyn_cast<sem::Table>()->rows.at(index).get());
        }
        default: {
            return NodeStore::Id::FromPtr(
                get(node)->subnodes.at(index).get());
        }
    }
}

Func<ColText(CR<diff::NodeStore::Id>)> OrgNodeStore::getToStr() {
    return [](CR<diff::NodeStore::Id> arg) -> ColText {
        auto      org = arg.ToPtr<sem::Org>();
        ColStream res;
        res << res.cyan() << fmt1(org->getKind()) << res.end();
        if (auto leaf = org->dyn_cast<sem::Leaf>()) {
            res << " " << res.yellow() << escape_literal(leaf->text)
                << res.end();
        }
        return res.getBuffer();
    };
}

ColText OrgNodeDiff::formatDiff() {
    ColStream os;
    printMapping(
        os,
        *diff,
        *srcSyntax,
        *dstSyntax,
        srcStore->getToStr(),
        dstStore->getToStr());
    return os;
}

void OrgNodeDiff::setDiffTrees(
    const sem::SemId<sem::Org>&    src,
    const sem::SemId<sem::Org>&    dst,
    const diff::ComparisonOptions& Options) {
    this->src = src;
    this->dst = dst;
    srcSyntax = std::make_shared<diff::SyntaxTree>(Options);
    dstSyntax = std::make_shared<diff::SyntaxTree>(Options);
    srcStore  = std::make_shared<OrgNodeStore>(src.asOrg());
    dstStore  = std::make_shared<OrgNodeStore>(dst.asOrg());
    srcSyntax->FromNode(srcStore.get());
    dstSyntax->FromNode(dstStore.get());
    diff = std::make_shared<diff::ASTDiff>(
        *srcSyntax, *dstSyntax, Options);
}

diff::ComparisonOptions OrgNodeDiff::getOptions() {
    SemSet LeafKinds{
        OrgSemKind::Word,
        OrgSemKind::BigIdent,
        OrgSemKind::Punctuation,
        OrgSemKind::Escaped,
        OrgSemKind::Newline,
        OrgSemKind::Empty,
    };

    return diff::ComparisonOptions{
        .getUpdateCost  = [](diff::Node const& Src,
                            diff::Node const& Dst) -> double { return 1; },
        .areValuesEqual = [LeafKinds](
                              diff::Node const& Src,
                              diff::Node const& Dst) -> bool {
            auto S = Src.ASTNode.ToPtr<sem::Org>();
            auto D = Dst.ASTNode.ToPtr<sem::Org>();
            if (LeafKinds.contains(S->getKind())
                && LeafKinds.contains(D->getKind())) {
                return Src.getStore<OrgNodeStore>()->getNodeValue(
                           Src.ASTNode)
                    == Dst.getStore<OrgNodeStore>()->getNodeValue(
                        Dst.ASTNode);
            } else if (
                S->is(OrgSemKind::BlockCode)
                && D->is(OrgSemKind::BlockCode)) {
                auto SrcCode = S->dyn_cast<sem::BlockCode>();
                auto DstCode = D->dyn_cast<sem::BlockCode>();
                // TODO
                return true;
            } else {
                return true;
            }
        },
        .isMatchingAllowed = [LeafKinds](
                                 diff::Node const& Src,
                                 diff::Node const& Dst) -> bool {
            auto SrcKind = static_cast<OrgSemKind>(
                Src.getNodeKind().value);
            auto DstKind = static_cast<OrgSemKind>(
                Dst.getNodeKind().value);
            if (SrcKind == DstKind) {
                return true;
            } else {
                return LeafKinds.contains(SrcKind)
                    && LeafKinds.contains(DstKind);
            }
        },
    };
}
