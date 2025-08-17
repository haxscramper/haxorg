#pragma once
#include <hstd/ext/astdiff.hpp>
#include <haxorg/sem/SemOrg.hpp>
#include <haxorg/sem/ImmOrg.hpp>
#include <hstd/ext/bimap_wrap.hpp>

namespace org::algo {

struct SemNodeStore : hstd::ext::diff::NodeStore {
    sem::SemId<sem::Org> root;

    using value_type = hstd::Opt<hstd::Str>;
    using node_type  = sem::Org;

    SemNodeStore(sem::SemId<sem::Org> root) : root{root} {}

    hstd::Opt<hstd::Str> getNodeValue(NodeStore::Id const& id) {
        auto node = get(id);
        if (auto leaf = node->dyn_cast<sem::Leaf>()) {
            return leaf->text;
        } else {
            return std::nullopt;
        }
    }

    sem::Org const* get(Id const& id) const {
        return id.ToPtr<sem::Org>();
    }

    sem::Org* get(Id const& id) {
        return const_cast<sem::Org*>(id.ToPtr<sem::Org>());
    }

    virtual int getSubnodeCount(const Id& id) override;

    virtual Id getSubnodeAt(const Id& node, int index) override;

    virtual Id getRoot() override {
        return NodeStore::Id::FromPtr(root.get());
    }

    virtual hstd::ext::diff::ASTNodeKind getNodeKind(
        const Id& node) const override {
        return static_cast<int>(get(node)->getKind());
    }

    hstd::Func<hstd::ColText(NodeStore::Id const&)> getToStr();
};

struct SemNodeDiff {
    hstd::SPtr<hstd::ext::diff::SyntaxTree> srcSyntax;
    hstd::SPtr<hstd::ext::diff::SyntaxTree> dstSyntax;
    hstd::SPtr<hstd::ext::diff::ASTDiff>    diff;
    sem::SemId<sem::Org>                    src;
    sem::SemId<sem::Org>                    dst;
    hstd::SPtr<SemNodeStore>                srcStore;
    hstd::SPtr<SemNodeStore>                dstStore;


    hstd::ColText formatDiff();

    sem::Org* getSrc(hstd::ext::diff::NodeStore::Id const& id) {
        return srcStore->get(id);
    }
    sem::Org* getDst(hstd::ext::diff::NodeStore::Id const& id) {
        return dstStore->get(id);
    }

    sem::Org* getSrc(hstd::ext::diff::NodeIdx const& id) {
        return getSrc(srcSyntax->getNode(id).ASTNode);
    }

    sem::Org* getDst(hstd::ext::diff::NodeIdx const& id) {
        return getDst(dstSyntax->getNode(id).ASTNode);
    }

    template <typename T>
    T* getSrcT(hstd::ext::diff::NodeIdx const& id) {
        return dynamic_cast<T*>(getSrc(srcSyntax->getNode(id).ASTNode));
    }

    template <typename T>
    T* getDstT(hstd::ext::diff::NodeIdx const& id) {
        return dynamic_cast<T*>(getDst(dstSyntax->getNode(id).ASTNode));
    }

    void setDiffTrees(
        sem::SemId<sem::Org> const&               src,
        sem::SemId<sem::Org> const&               dst,
        hstd::ext::diff::ComparisonOptions const& Options);

    hstd::ext::diff::ComparisonOptions getOptions();
};

struct ImmNodeStore : hstd::ext::diff::NodeStore {
    org::imm::ImmAdapter         root;
    org::imm::ImmAstContext::Ptr context;
    bool                         DirectSubnodes;

    using value_type = org::imm::ImmId;
    using node_type  = org::imm::ImmAdapter;

    hstd::ext::Unordered1to1Bimap<org::imm::ImmUniqId, NodeStore::Id> map;

    ImmNodeStore(org::imm::ImmAdapter const& root, bool DirectSubnodes)
        : root{root}, DirectSubnodes{DirectSubnodes} {
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
    }

    NodeStore::Id getStoreId(org::imm::ImmUniqId const& id) {
        return map.at_right(id);
    }

    org::imm::ImmId getNodeValue(NodeStore::Id const& id) {
        return get(id).id;
    }

    org::imm::ImmAdapter get(Id const& id) const {
        return context->adapt(map.at_left(id));
    }

    org::imm::ImmUniqId getUniq(Id const& id) const {
        return map.at_left(id);
    }


    virtual int getSubnodeCount(const Id& id) override;

    virtual Id getSubnodeAt(const Id& node, int index) override;

    virtual Id getRoot() override { return getStoreId(root.uniq()); }

    virtual hstd::ext::diff::ASTNodeKind getNodeKind(
        const Id& node) const override {
        return static_cast<int>(get(node).getKind());
    }

    hstd::Func<hstd::ColText(NodeStore::Id const&)> getToStr();
};

struct ImmNodeDiff {
    /// \brief Only compare direct subtrees of the node -- exclude nodes
    /// stored in the fields.
    bool DirectSubnodes = true;

    hstd::SPtr<hstd::ext::diff::SyntaxTree> srcSyntax;
    hstd::SPtr<hstd::ext::diff::SyntaxTree> dstSyntax;
    hstd::SPtr<hstd::ext::diff::ASTDiff>    diff;
    imm::ImmAdapter                         src;
    imm::ImmAdapter                         dst;
    hstd::SPtr<ImmNodeStore>                srcStore;
    hstd::SPtr<ImmNodeStore>                dstStore;

    void setDiffTrees(
        imm::ImmAdapter const&                    src,
        imm::ImmAdapter const&                    dst,
        hstd::ext::diff::ComparisonOptions const& Options);

    hstd::ext::diff::ComparisonOptions getOptions();

    hstd::Func<hstd::ColText(ImmNodeStore::NodeStore::Id const&)> getFormatTreeValue(
        hstd::SPtr<ImmNodeStore> const& store);

    void printDstChange(
        hstd::ColStream&                   OS,
        hstd::ext::diff::ASTDiff const&    Diff,
        hstd::ext::diff::SyntaxTree const& SrcTree,
        hstd::ext::diff::SyntaxTree const& DstTree,
        hstd::ext::diff::NodeIdx           Dst);

    void printMapping(
        hstd::ColStream&                   os,
        hstd::ext::diff::ASTDiff const&    Diff,
        hstd::ext::diff::SyntaxTree const& SrcTree,
        hstd::ext::diff::SyntaxTree const& DstTree);

    hstd::ColText printMapping();
};

} // namespace org::algo
