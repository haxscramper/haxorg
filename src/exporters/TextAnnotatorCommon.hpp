#pragma once

#include <hstd/stdlib/Vec.hpp>
#include <sem/SemOrg.hpp>
#include <hstd/system/aux_utils.hpp>

struct OrgText {
    struct Word {
        QString    text;
        sem::SemId id = sem::SemId::Nil();
    };

    Vec<Word> text;

    Vec<sem::SemId> overlappingNodes(Slice<int> characterRange) const {
        Vec<Pair<Slice<int>, sem::SemId>> rangeForId;
        int                               offset = 0;
        Vec<sem::SemId>                   result;
        for (auto const& word : text) {
            Slice<int> range = slice1<int>(
                offset, offset + word.text.length());
            offset += word.text.length();
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
        activeRequest = Request{};
        for (auto const& sub : par->subnodes) {
            _this()->visit(t, sub);
        }
        onFinishedRequestVisit(std::move(activeRequest.value()));
        activeRequest = std::nullopt;
    }

    virtual void onFinishedRequestVisit(Request const& request) = 0;
};
