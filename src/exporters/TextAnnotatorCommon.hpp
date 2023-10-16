#pragma once

#include <hstd/stdlib/Vec.hpp>
#include <sem/SemOrg.hpp>
#include <hstd/system/aux_utils.hpp>

struct OrgText {
    struct Word {
        std::string text;
        sem::SemId  id = sem::SemId::Nil();

        std::string getText() const { return text; }
    };

    Vec<Word> text;

    bool empty() const {
        return text.empty()
            || std::all_of(
                   text.begin(), text.end(), [](Word const& str) -> bool {
                       return str.text.isEmpty();
                   });
    }

    std::string flatText() const {
        std::string res;
        for (auto const& word : this->text) {
            res += word.getText();
        }
        return res;
    }

    Vec<sem::SemId> overlappingNodes(Slice<int> characterRange) const {
        Vec<Pair<Slice<int>, sem::SemId>> rangeForId;
        int                               offset = 0;
        Vec<sem::SemId>                   result;
        for (auto const& word : text) {
            std::string text = word.getText();
            Slice<int> range = slice1<int>(offset, offset + text.length());
            offset += text.length();
            rangeForId.push_back({range, word.id});
        }

        for (auto const& rng : rangeForId) {
            if (rng.first.contains(characterRange)
                && !result.contains(rng.second)) {
                result.push_back(rng.second);
            }
        }

        if (result.empty()) {
            for (auto const& rng : rangeForId) {
                if (characterRange.overlap(rng.first).has_value()) {
                    result.push_back(rng.second);
                }
            }
        }

        return result;
    }
};

template <typename Exporter, typename ResultType>
struct AnnotatingVisitorBase : public CRTP_this_method<Exporter> {
    using CRTP_this_method<Exporter>::_this;

    struct Request {
        OrgText sentence;
    };

    Opt<Request> activeRequest;

    template <typename T>
    void visitLeafToken(sem::SemIdT<T> leaf) {
        if (activeRequest) {
            activeRequest->sentence.text.push_back(
                OrgText::Word{.text = leaf->text, .id = leaf.toId()});
        }
    }

    void asSeparateRequest(ResultType& t, sem::SemId par) {
        if (activeRequest) {
            for (auto const& sub : par->subnodes) {
                _this()->visit(t, sub);
            }
        } else {
            activeRequest = Request{};
            for (auto const& sub : par->subnodes) {
                _this()->visit(t, sub);
            }

            if (!activeRequest->sentence.empty()) {
                onFinishedRequestVisit(std::move(activeRequest.value()));
            }

            activeRequest = std::nullopt;
        }
    }

    virtual void onFinishedRequestVisit(Request const& request) = 0;
};
