#pragma once
#include <QObject>
#include <sem/SemBaseApi.hpp>
#include "org_qml_model.hpp"
#include <QVariant>

struct OrgBackend : public QObject {
    sem::SemId<sem::Document>     document;
    SPtr<OrgDocumentModel>        model;
    SPtr<OrgDocumentSearchFilter> filter;
    SPtr<OrgSubtreeSearchModel>   fuzzySorted;

    OrgBackend() {}

    Q_INVOKABLE void loadDocument(CR<QString> path) {
        document    = org::parseString(readFile(to_std(path)));
        model       = std::make_shared<OrgDocumentModel>(document);
        filter      = std::make_shared<OrgDocumentSearchFilter>(&model);
        fuzzySorted = std::make_shared<OrgSubtreeSearchModel>(&model);

        filter->acceptNode = [](CR<sem::SemId<sem::Org>> id) -> bool {
            return id->getKind() != OrgSemKind::Newline;
        };
    }

    Q_INVOKABLE OrgDocumentSearchFilter* getOutlineModel() {
        return &fuzzySorted.get()->filter;
    }

    Q_INVOKABLE OrgDocumentSearchFilter* getDocumentModel() {
        return filter.get();
    }

    Q_INVOKABLE void saveDocumentToJson(CR<QString> path) {
        writeFile(to_std(path), org::toJson(document.asOrg()).dump(2));
    }
};

Q_DECLARE_METATYPE(OrgBackend)
