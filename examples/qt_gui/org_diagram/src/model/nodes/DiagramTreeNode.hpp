#pragma once

#include <hstd/stdlib/Vec.hpp>
#include <QObject>
#include <haxorg/sem/ImmOrg.hpp>
#include <src/model/HistoryManager.hpp>

#define _cat "model.diagram"

struct DiagramTreeNode
    : public QObject
    , public hstd::SharedPtrApi<DiagramTreeNode> {
    Q_OBJECT

  public:
    struct Context : hstd::SharedPtrApi<DiagramTreeNode> {
        hstd::
            UnorderedMap<org::imm::ImmUniqId, hstd::WPtr<DiagramTreeNode>>
                trackingTreeId;
        DESC_FIELDS(Context, (trackingTreeId));

        hstd::SPtr<DiagramTreeNode> getNode(
            org::imm::ImmUniqId const& id) const {
            return hstd::safe_wptr_lock(trackingTreeId.at(id));
        }

        void incl(hstd::SPtr<DiagramTreeNode> const& node);
        void excl(org::imm::ImmUniqId const& id);
    };


    org::imm::ImmAdapter                   id;
    hstd::Vec<hstd::SPtr<DiagramTreeNode>> subnodes;
    std::weak_ptr<DiagramTreeNode>         parent;
    hstd::WPtr<Context>                    context;

    hstd::SPtr<Context> getContext() const {
        return hstd::safe_wptr_lock(this->context);
    }

    std::string formatToString() const { return hstd::fmt("id:{}", id); }

    DiagramTreeNode(org::imm::ImmAdapter const& id);

    org::imm::ImmUniqId uniq() const { return id.uniq(); }

    int getColumnCount() const;

    void addSubnode(hstd::SPtr<DiagramTreeNode> node);
    void removeSubnode(int index);
    void updateData();
    void insertSubnode(hstd::SPtr<DiagramTreeNode> const& node, int index);

    void apply(hstd::Vec<HistoryManager::AstEdit> const& edit);

    hstd::ColText format() const;

    static DiagramTreeNode::Ptr FromDocument(
        org::imm::ImmAdapterT<org::imm::ImmDocument> const& root);

    template <typename T>
    std::shared_ptr<T> as() {
        return std::dynamic_pointer_cast<T>(this->shared_from_this());
    }

  signals:
    void subnodeAdded(int index);
    void subnodeAboutToBeRemoved(int index);
    void subnodeRemoved();
    void dataChanged();
};
