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
