#include "SemAstDiff.hpp"
#include <haxorg/imm/ImmOrgAdapter.hpp>


using namespace org::algo;
using namespace hstd::ext;
using namespace hstd;

int SemNodeStore::getSubnodeCount(Id const& id) {
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

hstd::ext::diff::NodeStore::Id SemNodeStore::getSubnodeAt(
    Id const& node,
    int       index) {
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

Func<hstd::ColText(diff::NodeStore::Id const&)> SemNodeStore::getToStr() {
    return [](diff::NodeStore::Id const& arg) -> ColText {
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

ColText SemNodeDiff::formatDiff() {
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

void SemNodeDiff::setDiffTrees(
    sem::SemId<sem::Org> const&    src,
    sem::SemId<sem::Org> const&    dst,
    diff::ComparisonOptions const& Options) {
    this->src = src;
    this->dst = dst;
    srcSyntax = std::make_shared<diff::SyntaxTree>(Options);
    dstSyntax = std::make_shared<diff::SyntaxTree>(Options);
    srcStore  = std::make_shared<SemNodeStore>(src.asOrg());
    dstStore  = std::make_shared<SemNodeStore>(dst.asOrg());
    srcSyntax->FromNode(srcStore.get());
    dstSyntax->FromNode(dstStore.get());
    diff = std::make_shared<diff::ASTDiff>(
        *srcSyntax, *dstSyntax, Options);
}

namespace {
SemSet LeafKinds{
    OrgSemKind::Word,
    OrgSemKind::BigIdent,
    OrgSemKind::Punctuation,
    OrgSemKind::Escaped,
    OrgSemKind::Newline,
    OrgSemKind::Empty,
};
}

diff::ComparisonOptions SemNodeDiff::getOptions() {
    return diff::ComparisonOptions{
        .isMatchingAllowed = [](diff::Node const& Src,
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
        .areValuesEqual = [](diff::Node const& Src,
                             diff::Node const& Dst) -> bool {
            auto S = Src.ASTNode.ToPtr<sem::Org>();
            auto D = Dst.ASTNode.ToPtr<sem::Org>();
            if (LeafKinds.contains(S->getKind())
                && LeafKinds.contains(D->getKind())) {
                return Src.getStore<SemNodeStore>()->getNodeValue(
                           Src.ASTNode)
                    == Dst.getStore<SemNodeStore>()->getNodeValue(
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

        .getUpdateCost = [](diff::Node const& Src,
                            diff::Node const& Dst) -> double { return 1; },
    };
}

hstd::Vec<ImmNodeDiff::AstEdit> ImmNodeDiff::getEdits(bool WithKeeps) {
    using hstd::ext::diff::NodeIdx;
    using hstd::ext::diff::NodeStore;
    hstd::Vec<AstEdit> result;
    for (NodeIdx Dst : *dstSyntax) {
        NodeStore::Id DstId = dstSyntax->getStoreId(Dst);
        NodeIdx       Src   = diff->getMapped(*srcSyntax, Dst);
        if (Src.isValid()) {
            NodeStore::Id       SrcId    = srcSyntax->getStoreId(Src);
            org::imm::ImmUniqId ImmDstId = dstStore->getUniq(DstId);
            org::imm::ImmUniqId ImmSrcId = srcStore->getUniq(SrcId);
            if (ImmDstId.id == ImmSrcId.id) {
                if (WithKeeps) {
                    result.push_back(
                        AstEdit{
                            .data = AstEdit::Keep{.id = ImmDstId},
                        });
                }
            } else {
                result.push_back(
                    AstEdit{
                        .data = AstEdit::
                            Replace{.src = ImmSrcId, .dst = ImmDstId},
                    });
            }
        } else {
            org::imm::ImmUniqId ImmDstId = dstStore->getUniq(DstId);
            result.push_back(
                AstEdit{
                    .data = AstEdit::Insert{.id = ImmDstId},
                });
        }
    }

    for (NodeIdx Src : *srcSyntax) {
        NodeStore::Id SrcId = srcSyntax->getStoreId(Src);
        NodeIdx       Dst   = diff->getMapped(*dstSyntax, Src);
        if (!Dst.isValid()) {
            org::imm::ImmUniqId ImmSrcId = srcStore->getUniq(SrcId);
            result.push_back(
                AstEdit{
                    .data = AstEdit::Delete{.id = ImmSrcId},
                });
        }
    }

    return result;
}

void ImmNodeDiff::setDiffTrees(
    imm::ImmAdapter const&                    src,
    imm::ImmAdapter const&                    dst,
    hstd::ext::diff::ComparisonOptions const& Options) {
    this->src = src;
    this->dst = dst;
    srcSyntax = std::make_shared<diff::SyntaxTree>(Options);
    dstSyntax = std::make_shared<diff::SyntaxTree>(Options);
    srcStore  = std::make_shared<ImmNodeStore>(
        src, this->DirectSubnodes, context);
    dstStore = std::make_shared<ImmNodeStore>(
        dst, this->DirectSubnodes, context);
    srcSyntax->FromNode(srcStore.get());
    dstSyntax->FromNode(dstStore.get());
    diff = std::make_shared<diff::ASTDiff>(
        *srcSyntax, *dstSyntax, Options);
}

hstd::Func<ColText(ImmNodeStore::NodeStore::Id const&)> ImmNodeDiff::
    getFormatTreeValue(hstd::SPtr<ImmNodeStore> const& store) {
    return
        [store](ImmNodeStore::NodeStore::Id const& id) -> hstd::ColText {
            ColStream os;
            os << hstd::fmt1(store->get(id));
            return os;
        };
}

void ImmNodeDiff::printDstChange(
    hstd::ColStream&                   OS,
    hstd::ext::diff::ASTDiff const&    Diff,
    hstd::ext::diff::SyntaxTree const& SrcTree,
    hstd::ext::diff::SyntaxTree const& DstTree,
    hstd::ext::diff::NodeIdx           Dst) {
    hstd::ext::diff::printMapping(
        OS,
        Diff,
        SrcTree,
        DstTree,
        getFormatTreeValue(srcStore),
        getFormatTreeValue(dstStore));
}

void ImmNodeDiff::printMapping(
    hstd::ColStream&                   os,
    hstd::ext::diff::ASTDiff const&    Diff,
    hstd::ext::diff::SyntaxTree const& SrcTree,
    hstd::ext::diff::SyntaxTree const& DstTree) {
    hstd::ext::diff::printMapping(
        os,
        Diff,
        SrcTree,
        DstTree,
        getFormatTreeValue(srcStore),
        getFormatTreeValue(dstStore));
}

ColText ImmNodeDiff::printMapping() {
    ColStream os;
    printMapping(os, *diff, *srcSyntax, *dstSyntax);
    return os.getBuffer();
}

diff::ComparisonOptions ImmNodeDiff::getOptions() {
    return diff::ComparisonOptions{
        .isMatchingAllowed =
            [this](diff::Node const& Src, diff::Node const& Dst) -> bool {
            auto SrcKind = static_cast<OrgSemKind>(
                Src.getNodeKind().value);
            auto DstKind = static_cast<OrgSemKind>(
                Dst.getNodeKind().value);
            return true;
        },
        .areValuesEqual =
            [this](diff::Node const& Src, diff::Node const& Dst) -> bool {
            return srcStore->getUniq(Src.ASTNode).id
                == dstStore->getUniq(Dst.ASTNode).id;
        },
        .getUpdateCost = [](diff::Node const& Src,
                            diff::Node const& Dst) -> double { return 1; },
    };
}

ImmNodeStore::ImmNodeStore(
    imm::ImmAdapter const&       root,
    bool                         DirectSubnodes,
    org::imm::ImmAstContext::Ptr context)
    : root{root}, DirectSubnodes{DirectSubnodes}, context{context} {
    std::function<void(org::imm::ImmAdapter const&)> aux;
    hstd::i64                                        idCounter = 0;
    if (DirectSubnodes) {
        aux = [&](org::imm::ImmAdapter const& it) {
            map.add_unique(
                it.uniq(), NodeStore::Id::FromNumber(++idCounter));
            for (auto const& sub : it.sub()) { aux(sub); }
        };
    } else {
        logic_todo_impl();
    }

    aux(root);
}

int ImmNodeStore::getSubnodeCount(Id const& id) {
    if (DirectSubnodes) {
        return get(id).sub(false).size();
    } else {
        return get(id).getAllSubnodes(get(id).path, false).size();
    }
}

diff::NodeStore::Id ImmNodeStore::getSubnodeAt(Id const& node, int index) {
    if (DirectSubnodes) {
        return getStoreId(get(node).sub().at(index).uniq());
    } else {
        return getStoreId(
            get(node).getAllSubnodes(get(node).path).at(index).uniq());
    }
}
