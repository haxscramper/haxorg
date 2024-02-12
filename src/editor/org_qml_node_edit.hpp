#pragma once
#include <QObject>
#include <sem/SemOrg.hpp>
#include <sem/SemBaseApi.hpp>
#include <QVariant>
#include "org_qml.hpp"

namespace org_qml {
#define _case(__Kind)                                                     \
    template <>                                                           \
    struct serde<::org_qml::__Kind, ::sem::SemId<::sem::__Kind>> {        \
        using qml_type = ::org_qml::__Kind;                               \
        using cxx_type = ::sem::SemId<::sem::__Kind>;                     \
        static qml_type cxx_to_qml(cxx_type value) {                      \
            return qml_type{value};                                       \
        }                                                                 \
        static cxx_type qml_to_cxx(qml_type value) {                      \
            return value.__data.as<::sem::__Kind>();                      \
        }                                                                 \
    };

EACH_SEM_ORG_KIND(_case)
#undef _case
} // namespace org_qml

inline std::string to_std(QString const& value) {
    QByteArray tmp = value.toLatin1();
    return std::string{tmp.data(), static_cast<size_t>(tmp.size())};
}

class OrgNodeCursor;

class OrgNodeTextWrapper {
    Q_GADGET
    Q_PROPERTY(QString text READ getRichText WRITE setRichText);

  public:
    void           setRichText(QString const& value);
    QString        getRichText();
    OrgNodeCursor* cursor;
};

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

    OrgNodeCursor* getparent() { return parent; }

    std::vector<UPtr<OrgNodeCursor>> item_cache;
    sem::SemId<sem::Org>             node;
    OrgNodeCursor*                   parent;

    QVariant getNodeRich() {
        return QVariant::fromValue(OrgNodeTextWrapper{this});
    }

    QVariant getNodeHandle();
};


struct OrgBackend : public QObject {
    Q_OBJECT
  public:
    sem::SemId<sem::Document> document;
    Q_INVOKABLE void          saveDocument() {
        writeFile(
            "/tmp/result.json", org::toJson(document.asOrg()).dump(2));
    }
};

Q_DECLARE_METATYPE(OrgNodeTextWrapper)
