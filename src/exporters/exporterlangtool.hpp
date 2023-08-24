#pragma once

#include <exporters/Exporter.hpp>
#include "TextAnnotatorCommon.hpp"
#include "HttpDataProvider.hpp"
#include <QUrl>

class ExporterLangtool
    : public AnnotatingVisitorBase<ExporterLangtool, std::monostate>
    , public Exporter<ExporterLangtool, std::monostate> {

  public:
#define __ExporterBase Exporter<ExporterLangtool, std::monostate>
    EXPORTER_USING()
#undef __ExporterBase


    using R = std::monostate;

    template <sem::NotOrg T>
    void visit(R& res, CR<T> value) {}

    template <typename T>
    void visit(R& res, CVec<T> values) {
        for (const auto& value : values) {
            visit(res, value);
        }
    }

    template <typename T>
    void visit(R& res, CR<Opt<T>> opt) {
        if (opt) {
            visit(res, *opt);
        }
    }

    struct LangtoolResponse {
        struct Match {
            struct Context {
                DECL_FIELDS(
                    Context,
                    (),
                    ((int), length, 0),
                    ((int), offset, 0),
                    ((QString), text, ""));
            };

            struct Rule {
                struct Category {
                    DECL_FIELDS(
                        Category,
                        (),
                        ((QString), id, ""),
                        ((QString), name, ""));
                };

                DECL_FIELDS(
                    Rule,
                    (),
                    ((Category), category, Category{}),
                    ((QString), id, ""),
                    ((QString), issueType, ""),
                    ((QString), description, ""))
            };

            struct Replacement {
                DECL_FIELDS(Replacement, (), ((QString), value, ""));
            };

            DECL_FIELDS(
                Match,
                (),
                ((Context), context, Context{}),
                ((int), contextForSureMatch, 0),
                ((int), length, 0),
                ((QString), message, ""),
                ((int), offset, 0),
                ((Vec<Replacement>), replacements, {}),
                ((Rule), rule, Rule{}),
                ((QString), shortMessage, ""));
        };

        DECL_FIELDS(
            LangtoolResponse,
            (),
            ((Vec<Match>), matches, {}),
            ((Vec<Vec<int>>), sentenceRanges, {}));
    };

    struct Diagnostic {
        Vec<sem::SemId>  orgIds;
        LangtoolResponse resp;
    };

    struct Response {
        DECL_FIELDS(
            Response,
            (),
            ((LangtoolResponse), resp, LangtoolResponse{}),
            ((bool), valid, false),
            ((int), posStart, 0),
            ((int), posEnd, 0));
    };

    Vec<Pair<Request, Response>> exchange;

    void format(ColStream& os);

    template <typename T>
    void visitField(R& res, const char* name, CR<T> field) {
        visit(res, field);
    }
    virtual void onFinishedRequestVisit(Request const& req) override {
        exchange.push_back({req, Response{}});
    }

    void visitParagraph(R& t, sem::SemIdT<sem::Paragraph> par) {
        asSeparateRequest(t, par.toId());
    }

#define __visit(__Kind)                                                   \
    void visit##__Kind(R& res, In<sem::__Kind> leaf) {                    \
        visitLeafToken(leaf);                                             \
    }

    __visit(Word);
    __visit(Space);
    __visit(Punctuation);
    __visit(BigIdent);
    __visit(Placeholder);
    __visit(RawText);
    __visit(Newline);

    void executeRequests(QUrl const& url, SPtr<HttpDataProvider> http);
    void onFinishedResponse(
        HttpDataProvider::ResponseData const& reply,
        int                                   targetIndex);
};
