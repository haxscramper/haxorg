#pragma once
#include <QObject>
#include <sem/SemOrg.hpp>
#include <sem/SemBaseApi.hpp>

inline std::string to_std(QString const& value) {
    QByteArray tmp = value.toLatin1();
    return std::string{tmp.data(), static_cast<size_t>(tmp.size())};
}


class OrgNodeTextWrapper {
    Q_GADGET
    Q_PROPERTY(QString text READ getRichText WRITE setRichText);

  public:
    void setRichText(QString const& value) {
        LOG(INFO) << "Set rich text " << to_std(value);
        if (node->is(OrgSemKind::Word)) {
            node.getAs<sem::Word>()->text = to_std(value);
        }
    }

    QString getRichText() {
        if (node->is(OrgSemKind::Word)) {
            return QString::fromStdString(node.getAs<sem::Word>()->text);
        } else {
            return "none";
        }
    }

    sem::SemId<sem::Org> node;
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
