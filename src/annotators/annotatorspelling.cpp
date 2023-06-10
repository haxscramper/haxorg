#include "annotatorspelling.hpp"
#include <enchant++.h>
#include <hstd/stdlib/Debug.hpp>

static enchant::Broker* get_enchant_broker() {
    static enchant::Broker broker;
    return &broker;
}

UnorderedMap<sem::SemId, AnnotatorSpelling::Diagnostic> AnnotatorSpelling::
    annotate(sem::SemId org) {

    UnorderedMap<sem::SemId, AnnotatorSpelling::Diagnostic> result;
    org.eachSubnodeRec([&](sem::SemId org) {
        if (org.isNil()) {
            return;
        }

        if (SemSet{OrgSemKind::Word, OrgSemKind::BigIdent}.contains(
                org->getKind())) {
            auto leaf = org.as<sem::Leaf>();
            if (!checkWord(leaf->text)) {
                // qDebug() << leaf->id << "{" + leaf->text + "}"
                //          << "must be corrected to"
                //          << getSuggestions(leaf->text);

                result[org] = Diagnostic{};
            }
        }
    });

    return result;
}

void AnnotatorSpelling::setSpeller(const QString& lang) {
    try {
        speller.reset(
            get_enchant_broker()->request_dict(lang.toStdString()));
    } catch (enchant::Exception& e) {
        qWarning() << "Failed to load dictionary: " << e.what();
        return false;
    }
}

Vec<QString> AnnotatorSpelling::getSuggestions(const QString& word) {
    Vec<QString> list;
    if (speller) {
        std::vector<std::string> suggestions;
        speller->suggest(word.toUtf8().data(), suggestions);
        for (std::size_t i = 0, n = suggestions.size(); i < n; ++i) {
            list.push_back(QString::fromUtf8(suggestions[i].c_str()));
        }
    }
    return list;
}

void AnnotatorSpelling::ignoreWord(const QString& word) {
    Q_CHECK_PTR(speller);
    speller->add_to_session(word.toUtf8().data());
}

bool AnnotatorSpelling::checkWord(const QString& word) {
    Q_CHECK_PTR(speller);

    try {
        return speller->check(word.toUtf8().data());
    } catch (const enchant::Exception&) { return true; }
}
