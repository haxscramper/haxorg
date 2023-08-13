#pragma once

#include <exporters/Exporter.hpp>
#include <hstd/stdlib/Variant.hpp>
#include <hstd/stdlib/Opt.hpp>
#include <QUrl>

class QNetworkAccessManager;
class QNetworkReply;

struct ExporterNLP : public Exporter<ExporterNLP, std::monostate> {
  public:
#define __ExporterBase Exporter<ExporterNLP, std::monostate>
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

    template <typename T>
    void visitField(R& res, const char* name, CR<T> field) {
        visit(res, field);
    }

  public:
    struct OrgText {
        struct Word {
            QString    text;
            sem::SemId id = sem::SemId::Nil();
        };

        Vec<Word> text;
    };

    struct Parsed {
        OrgText original;
        int     posStart;
        int     posEnd;
        struct Constituency {
            QString           tag;
            QString           lexem;
            Vec<Constituency> nested;

            inline QString treeRepr(int indent = 0) const {
                auto res = QString("  ").repeated(indent);
                res.append(QString("%1 '%2'").arg(tag).arg(lexem));
                for (const auto& sub : nested) {
                    res.append("\n");
                    res.append(sub.treeRepr(indent + 1));
                }

                return res;
            }

            static Constituency parse(QString const& text);

          private:
            struct lexer;
            static Constituency parse(lexer& lex);
        };

        Constituency constituency;

        struct Dependency {
            QString dep;
            int     governor;
            QString governorGloss;
            int     dependent;
            QString dependentGloss;
        };

        struct Sentence {
            int             index;
            Constituency    parse;
            Vec<Dependency> basicDependencies;
            Vec<Dependency> enhancedDependencies;
            Vec<Dependency> enhancedPlusPlusDependencies;
        };

        struct Token {
            int     index;
            QString word;
            QString originalText;
            int     characterOffsetBegin;
            int     characterOffsetEnd;
            QString pos;
            QString before;
            QString after;
        };

        Sentence   sentence;
        Vec<Token> tokens;
    };

    struct Request {
        OrgText sentence;
    };

    struct Response {
        bool             valid;
        Vec<Parsed>      sentences;
        Parsed::Sentence original;
        int              posStart;
        int              posEnd;
    };

    QUrl                         requestUrl;
    Vec<Pair<Request, Response>> exchange;
    ExporterNLP(QUrl const& resp) : requestUrl(resp) {}
    void executeRequests();

  private:
    QNetworkAccessManager* netManager = nullptr;

    void sendRequest(Request const& request, int index);
    void addRequestHooks(QNetworkReply* reply);
    void onFinishedResponse(QNetworkReply* reply);
};
