#pragma once
#include <haxorg/lexbase/AstDiff.hpp>
#include <haxorg/sem/SemOrg.hpp>

struct OrgNodeStore : diff::NodeStore {
    sem::SemId<sem::Org> root;

    using value_type = Opt<Str>;
    using node_type  = sem::Org;

    OrgNodeStore(sem::SemId<sem::Org> root) : root{root} {}

    Opt<Str> getNodeValue(NodeStore::Id const& id) {
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

    virtual diff::ASTNodeKind getNodeKind(const Id& node) const override {
        return static_cast<int>(get(node)->getKind());
    }

    Func<ColText(CR<NodeStore::Id>)> getToStr();
};

struct OrgNodeDiff {
    SPtr<diff::SyntaxTree> srcSyntax;
    SPtr<diff::SyntaxTree> dstSyntax;
    SPtr<diff::ASTDiff>    diff;
    sem::SemId<sem::Org>   src;
    sem::SemId<sem::Org>   dst;
    SPtr<OrgNodeStore>     srcStore;
    SPtr<OrgNodeStore>     dstStore;


    ColText formatDiff();

    sem::Org* getSrc(diff::NodeStore::Id const& id) {
        return srcStore->get(id);
    }
    sem::Org* getDst(diff::NodeStore::Id const& id) {
        return dstStore->get(id);
    }

    sem::Org* getSrc(diff::NodeIdx const& id) {
        return getSrc(srcSyntax->getNode(id).ASTNode);
    }

    sem::Org* getDst(diff::NodeIdx const& id) {
        return getDst(dstSyntax->getNode(id).ASTNode);
    }

    template <typename T>
    T* getSrcT(diff::NodeIdx const& id) {
        return dynamic_cast<T*>(getSrc(srcSyntax->getNode(id).ASTNode));
    }

    template <typename T>
    T* getDstT(diff::NodeIdx const& id) {
        return dynamic_cast<T*>(getDst(dstSyntax->getNode(id).ASTNode));
    }

    void setDiffTrees(
        sem::SemId<sem::Org> const&    src,
        sem::SemId<sem::Org> const&    dst,
        diff::ComparisonOptions const& Options);

    diff::ComparisonOptions getOptions();
};
