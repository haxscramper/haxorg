#pragma once
#include <QObject>
#include <sem/SemOrg.hpp>
#include <sem/SemBaseApi.hpp>
#include <QVariant>
#include "org_qml.hpp"
#include "org_qml_manual2.hpp"


class OrgNodeCursor {
  public:
    explicit OrgNodeCursor(
        const sem::SemId<sem::Org>& data,
        OrgNodeCursor*              parent)
        : node(data), parent(parent) {}

    OrgNodeCursor* at(int row) {
        if (row < item_cache.size()) {
            return item_cache.at(row).get();
        } else {
            if (row < node->subnodes.size()) {
                auto& sub = item_cache.emplace_back(
                    std::make_unique<OrgNodeCursor>(
                        node->subnodes.at(row), this));
                return sub.get();
            } else {
                return nullptr;
            }
        }
    }

    int size() const {
        if (node->is(OrgSemKind::Paragraph)) {
            return 0;
        } else {
            return node->subnodes.size();
        }
    }
    int columnCount() const { return 1; }

    QVariant data(int column) const {
        if (column == 0) {
            return QString::fromStdString(fmt1(node->getKind()));
        } else {
            return QVariant();
        }
    }

    int row() const {
        if (parent) {
            for (int idx = 0; idx < parent->size(); ++idx) {
                if (parent->at(idx)->node.get() == this->node.get()) {
                    return idx;
                }
            }
            return 0;
        } else {
            return 0;
        }
    }

    OrgNodeCursor*                   getparent() { return parent; }
    std::vector<UPtr<OrgNodeCursor>> item_cache;
    sem::SemId<sem::Org>             node;
    OrgNodeCursor*                   parent;
    QVariant                         getNodeHandle();
};

