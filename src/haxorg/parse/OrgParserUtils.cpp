#include <haxorg/parse/OrgParser.hpp>
#include <hstd/stdlib/Debug.hpp>

using namespace hstd;
using namespace org::parse;

std::string OrgParser::getLocMsg(CR<OrgLexer> lex) {
    std::string result;
    std::string pos = lex.pos.isNil() ? "<nil>" : fmt1(lex.pos.getIndex());

    if (auto loc = getLoc(lex)) {
        result = "$#:$# (tok $#, pos $#)"
               % to_string_vec(loc->line, loc->column, pos, loc->pos);
    } else {
        result = "(tok $#)" % to_string_vec(pos);
    }

    return result;
}


Opt<LineCol> OrgParser::getLoc(CR<OrgLexer> lex) {
    if (lex.finished()) {
        return std::nullopt;
    } else {
        for (int offset = 0; lex.hasNext(-offset) || lex.hasNext(offset);
             ++offset) {
            // Try incrementally widening lookarounds on the current
            // lexer position until there is a token that has proper
            // location information.
            for (int i : Vec<int>{-1, 1}) {
                if (lex.hasNext(offset * i)) {
                    OrgToken tok = lex.tok(offset * i);
                    if (!tok->isFake()) {
                        return LineCol{tok.value.line, tok.value.col};
                    }
                    // If offset falls out of the lexer range on both
                    // ends, terminate lookup.
                }
            }
        }
        return std::nullopt;
    }
}

struct Builder : OperationsMsgBulder<Builder, OrgParser::Report> {
    Builder& with_node(OrgId const& node) {
        report.node = node;
        return *this;
    }

    Builder& with_kind(OrgParser::ReportKind const& kind) {
        report.kind = kind;
        return *this;
    }

    Builder& with_lex(OrgLexer const& lex) {
        report.lex = &lex;
        return *this;
    }

    Builder(
        OrgParser::ReportKind kind,
        char const*           file     = __builtin_FILE_NAME(),
        int                   line     = __builtin_LINE(),
        char const*           function = __builtin_FUNCTION()) {
        this->report = OrgParser::Report{
            OperationsMsg{
                .file     = file,
                .line     = line,
                .function = function,
            },
            .kind = kind,
        };
    }
};

org::parse::OrgParser::NodeGuard OrgParser::start(
    OrgNodeKind kind,
    int         line,
    const char* function) {
    int const startingDepth = treeDepth();
    auto      res           = group->startTree(kind);
    if (TraceState) {
        report(
            Builder(
                OrgParser::ReportKind::StartNode, nullptr, line, function)
                .with_node(res)
                .report);
    }
    return NodeGuard{startingDepth, this, res};
}

OrgId OrgParser::end_impl(
    const std::string& desc,
    int                line,
    const char*        function) {
    LOGIC_ASSERTION_CHECK(0 <= group->treeDepth(), "");
    auto res = group->endTree();
    if (TraceState) {
        report(Builder(
                   OrgParser::ReportKind::EndNode, nullptr, line, function)
                   .with_node(res)
                   .with_msg(desc)
                   .report);
    }
    return res;
}

OrgParser::ParseResult OrgParser::error_end(
    OrgNodeMono::Error const& err,
    int                       line,
    char const*               function) {
    error_token(err, line, function);
    return ParseFail{};
}


void OrgParser::fail(
    CR<OrgLexer> lex,
    CR<OrgNode>  replace,
    int          line,
    const char*  function) {
    LOGIC_ASSERTION_CHECK(0 <= group->treeDepth(), "");
    auto res = group->failTree(replace);
    if (TraceState) {
        report(
            Builder(
                OrgParser::ReportKind::FailTree, nullptr, line, function)
                .with_node(res)
                .report);
    }
}


OrgId OrgParser::fake(OrgNodeKind kind, int line, const char* function) {
    auto res = group->token(
        kind, group->tokens->add(OrgToken(OrgTokenKind::Unknown)));
    if (TraceState) {
        report(
            Builder(
                OrgParser::ReportKind::AddToken, nullptr, line, function)
                .with_node(res)
                .report);
    }
    return res;
}


OrgId OrgParser::token(CR<OrgNode> node, int line, const char* function) {
    auto res = group->token(node);
    if (TraceState) {
        std::string msg;
        if (node.isMono()) {
            if (node.getMono().isError()) {
                msg = hstd::fmt("{}", *node.getMono().getError().box);
            }
        }
        report(
            Builder(
                OrgParser::ReportKind::AddToken, nullptr, line, function)
                .with_node(res)
                .with_msg(msg)
                .report);
    }
    return res;
}

OrgId OrgParser::token(
    OrgNodeKind kind,
    OrgTokenId  tok,
    int         line,
    const char* function) {
    auto res = group->token(kind, tok);

    if (TraceState) {
        report(
            Builder(
                OrgParser::ReportKind::AddToken, nullptr, line, function)
                .with_node(res)
                .report);
    }
    return res;
}

OrgNodeMono::Error OrgParser::error_value(
    org::sem::OrgDiagnostics::ParseError const& message,
    OrgLexer const&                             lex,
    int                                         line,
    char const*                                 function) {
    auto box = std::make_shared<OrgNodeMono::Error::Box>();
    org::parse::OrgNodeMono::Error::Box::ParseTokenFail fail;
    fail.err.brief          = message.brief;
    fail.err.detail         = message.detail;
    fail.err.parserFunction = function;
    fail.err.parserLine     = line;
    fail.err.errCode        = message.errCode;
    fail.err.errName        = message.errName;
    std::optional<OrgToken> failToken;
    if (lex.finished()) {
        if (lex.lastToken) { failToken = lex.lastToken.value(); }
    } else {
        failToken = lex.tok();
    }

    if (failToken) {
        fail.err.loc        = org::sem::SourceLocation{};
        fail.err.loc.column = failToken->value.col;
        fail.err.loc.line   = failToken->value.line;
        fail.err.tokenText  = failToken->value.text;
        fail.err.loc.file   = currentFile;
    }

    box->data = fail;

    return OrgNodeMono::Error{.box = box};
}

OrgId OrgParser::error_token(
    const OrgNodeMono::Error& err,
    int                       line,
    const char*               function) {
    OrgNodeMono mono;
    mono.data     = err;
    OrgNode error = OrgNode{OrgNodeKind::ErrorInfoToken, mono};
    return token(error);
}

OrgParser::ParseResult OrgParser::maybe_recursive_error_end(
    ParseResult const&                          res,
    org::sem::OrgDiagnostics::ParseError const& on_fail_message,
    OrgLexer&                                   lex,
    int                                         line,
    const char*                                 function) {
    if (res.has_value()) {
        return res;
    } else {
        auto fail = error_end(on_fail_message, lex, line, function);
        end_impl();
        return fail;
    }
}

OrgParser::ParseResult OrgParser::maybe_error_end(
    const MaybeTokenFail& err,
    int                   line,
    const char*           function) {
    if (err.has_error()) {
        return error_end(err.assume_error(), line, function);
    } else {
        return ParseOk{};
    }
}

OrgParser::ParseResult OrgParser::expect(
    CR<OrgLexer>                                           lex,
    CR<OrgExpectable>                                      item,
    hstd::Opt<org::sem::OrgDiagnostics::ParseError> const& message,
    int                                                    line,
    char const*                                            function) {

    if (at(lex, item)) {
        return ParseOk{};
    } else {
        auto msg = fmt(
            "{}: Expected token {} {} but got '{}'",
            line,
            item,
            getLocMsg(lex),
            lex.finished() ? "<lexer-finished>" : fmt1(lex.kind()));

        org::sem::OrgDiagnostics::ParseError err;
        if (message) { err = message.value(); }

        if (err.detail.empty()) {
            err.detail = msg;
        } else {
            err.detail += "\n\n" + msg;
        }

        if (TraceState) {
            report(
                Builder(
                    OrgParser::ReportKind::Error, nullptr, line, function)
                    .with_msg(msg)
                    .report);
        }

        return error_end(error_value(err, lex, line, function));
    }
}

OrgParser::LexResult OrgParser::pop(
    OrgLexer&          lex,
    Opt<OrgExpectable> tok,
    int                line,
    char const*        function) {
    if (tok) {
        BOOST_OUTCOME_TRY(expect(lex, *tok, std::nullopt, line, function));
    }
    if (TraceState) {
        print(fmt("pop {}", lex.tok()), &lex, line, function);
    }
    return lex.pop();
}


OrgParser::ParseResult OrgParser::skip(
    OrgLexer&                                              lex,
    Opt<OrgExpectable>                                     item,
    hstd::Opt<org::sem::OrgDiagnostics::ParseError> const& message,
    int                                                    line,
    char const*                                            function) {

    if (item) {
        BOOST_OUTCOME_TRY(expect(lex, *item, message, line, function));
    }

    if (TraceState) {
        print(fmt("skip {}", lex.tok()), &lex, line, function);
    }

    lex.next();
    return ParseOk{};
}

finally_std OrgParser::trace(
    OrgLexer&        lex,
    Opt<std::string> msg,
    int              line,
    const char*      function) {
    if (TraceState) {
        report(
            Builder(
                OrgParser::ReportKind::EnterParse, nullptr, line, function)
                .with_lex(lex)
                .report);

        return finally_std([line, function, this, &lex]() {
            report(Builder(
                       OrgParser::ReportKind::LeaveParse,
                       nullptr,
                       line,
                       function)
                       .with_lex(lex)
                       .report);
        });

    } else {
        return finally_std::nop();
    }
}

void OrgParser::print(
    const std::string& msg,
    OrgLexer*          lexer,
    int                line,
    const char*        function) {
    if (TraceState) {
        auto build = Builder(
                         OrgParser::ReportKind::Print,
                         nullptr,
                         line,
                         function)
                         .with_msg(msg);

        if (lexer) { build.with_lex(*lexer); }
        report(build.report);
    }
}

parse_error OrgParser::fatalError(
    OrgLexer const& lex,
    CR<Str>         msg,
    int             line,
    const char*     function) {
    if (TraceState) {
        auto build = Builder(
                         OrgParser::ReportKind::Error,
                         nullptr,
                         line,
                         function)
                         .with_msg(msg)
                         .with_lex(lex);
        report(build.report);
    }

    Opt<OrgToken> tok = lex.hasNext(-1) ? Opt<OrgToken>{lex.tok(-1)}
                                        : std::nullopt;

    return parse_error::init(
        fmt("{} {} at {} in (prev: {}) {}",
            msg,
            lex.finished() ? (lex.lastToken ? fmt1(lex.lastToken.value())
                                            : "<lexer-finished>")
                           : fmt1(lex.tok()),
            getLocMsg(lex),
            tok,
            lex.printToString([](ColStream& os, OrgToken const& t) {
                os << os.yellow() << escape_for_write(t.value.text)
                   << os.end() << fmt1(t.value);
            })),
        line,
        function);
}
