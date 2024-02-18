#pragma once
#include <QObject>
#include <sem/SemBaseApi.hpp>
#include "org_qml_model.hpp"
#include <QVariant>

struct OrgBackend : public QObject {
    Q_OBJECT
  public:
    sem::SemId<sem::Document>     document;
    SPtr<OrgDocumentModel>        model;
    SPtr<OrgDocumentSearchFilter> filter;
    SPtr<OrgSubtreeSearchModel>   outline;

    OrgBackend() {}

    void parseString(CR<std::string> text) {
        document = org::parseString(text);
        model    = std::make_shared<OrgDocumentModel>(document);
        filter   = std::make_shared<OrgDocumentSearchFilter>(model.get());
        outline  = std::make_shared<OrgSubtreeSearchModel>(model.get());

        filter->acceptNode = [](CR<sem::SemId<sem::Org>> id) -> bool {
            return id->getKind() != OrgSemKind::Newline;
        };

        emit hasDocumentChanged(getHasDocument());
    }

    Q_INVOKABLE void parseDocumentString(CR<QString> text) {
        parseString(to_std(text));
    }

    Q_INVOKABLE void parseDocumentFile(CR<QString> path) {
        parseString(readFile(to_std(path)));
    }

    Q_PROPERTY(
        bool hasDocument READ getHasDocument NOTIFY hasDocumentChanged)

    bool getHasDocument() const { return !document.isNil(); }

    Q_INVOKABLE OrgDocumentSearchFilter* getOutlineModel() {
        return &outline.get()->filter;
    }

    Q_INVOKABLE OrgDocumentSearchFilter* getDocumentModel() {
        return filter.get();
    }

    Q_INVOKABLE org_qml::Document getDocument() {
        return org_qml::serde<
            org_qml::Document,
            sem::SemId<sem::Document>>::cxx_to_qml(document);
    }

    Q_INVOKABLE void saveDocumentToJson(CR<QString> path) {
        writeFile(to_std(path), org::toJson(document.asOrg()).dump(2));
    }
  signals:
    void hasDocumentChanged(bool status);
};

Q_DECLARE_METATYPE(OrgBackend)
