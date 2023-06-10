#ifndef ANNOTATORSPELLING_HPP
#define ANNOTATORSPELLING_HPP

#include <hstd/stdlib/Ptrs.hpp>
#include <sem/SemOrg.hpp>
#include <hstd/stdlib/Map.hpp>

namespace enchant {
class Dict;
}

struct AnnotatorSpelling {
    SPtr<enchant::Dict> speller = nullptr;

    struct Diagnostic {};

    UnorderedMap<sem::SemId, Diagnostic> annotate(sem::SemId org);

    void         setSpeller(QString const& lang);
    Vec<QString> getSuggestions(QString const& word);
    void         ignoreWord(QString const& word);
    bool         checkWord(QString const& word);
};

#endif // ANNOTATORSPELLING_HPP
