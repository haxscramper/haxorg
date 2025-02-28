#pragma once
#include <hstd/ext/astdiff.hpp>
#include <haxorg/sem/SemOrg.hpp>

namespace org::algo {

struct OrgNodeStore : hstd::ext::diff::NodeStore {
    sem::SemId<sem::Org> root;

    using value_type = hstd::Opt<hstd::Str>;
    using node_type  = sem::Org;

    OrgNodeStore(sem::SemId<sem::Org> root) : root{root} {}

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

struct OrgNodeDiff {
    hstd::SPtr<hstd::ext::diff::SyntaxTree> srcSyntax;
    hstd::SPtr<hstd::ext::diff::SyntaxTree> dstSyntax;
    hstd::SPtr<hstd::ext::diff::ASTDiff>    diff;
    sem::SemId<sem::Org>                    src;
    sem::SemId<sem::Org>                    dst;
    hstd::SPtr<OrgNodeStore>                srcStore;
    hstd::SPtr<OrgNodeStore>                dstStore;


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

} // namespace org::algo
