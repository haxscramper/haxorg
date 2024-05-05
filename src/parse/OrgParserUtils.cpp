#include <parse/OrgParser.hpp>
#include <hstd/stdlib/Debug.hpp>

std::string OrgParser::getLocMsg(CR<OrgLexer> lex) {
    std::string result;
    std::string pos = lex.pos.isNil() ? "<nil>" : fmt1(lex.pos.getIndex());

    if (auto loc = getLoc(lex)) {
        result = "$#:$# (tok $#, pos $#)"
               % to_string_vec(loc->line, loc->column, pos, loc->pos);
    } else {
        result = "(tok $#, pos $#)" % to_string_vec(pos, loc->pos);
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

OrgId OrgParser::start(OrgNodeKind kind, int line, const char* function) {
    auto res = group->startTree(kind);
    if (TraceState) {
        report(
            Builder(
                OrgParser::ReportKind::StartNode, nullptr, line, function)
                .with_node(res)
                .report);
    }
    return res;
}

OrgId OrgParser::end(int line, const char* function) {
    CHECK(0 <= group->treeDepth());
    auto res = group->endTree();
    if (TraceState) {
        report(Builder(
                   OrgParser::ReportKind::EndNode, nullptr, line, function)
                   .with_node(res)
                   .report);
    }
    return res;
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
        report(
            Builder(
                OrgParser::ReportKind::AddToken, nullptr, line, function)
                .with_node(res)
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

void OrgParser::expect(
    CR<OrgLexer>      lex,
    CR<OrgExpectable> item,
    int               line,
    char const*       function) {

    if (!(at(lex, item))) {
        auto msg = fmt(
            "{}: Expected token {} {} but got '{}'",
            line,
            item,
            getLocMsg(lex),
            lex.finished() ? "<lexer-finished>" : fmt1(lex.kind()));
        if (TraceState) {
            report(
                Builder(
                    OrgParser::ReportKind::Error, nullptr, line, function)
                    .with_msg(msg)
                    .report);
        }

        fatalError(lex, msg, line, function);
    }
}

OrgTokenId OrgParser::pop(
    OrgLexer&          lex,
    Opt<OrgExpectable> tok,
    int                line,
    char const*        function) {
    if (tok) { expect(lex, *tok, line, function); }
    if (TraceState) {
        print(fmt("pop {}", lex.tok()), line, function, &lex);
    }
    return lex.pop();
}


void OrgParser::skip(
    OrgLexer&          lex,
    Opt<OrgExpectable> item,
    int                line,
    char const*        function) {

    if (item) { expect(lex, *item, line, function); }

    if (TraceState) {
        print(fmt("skip {}", lex.tok()), line, function, &lex);
    }

    lex.next();
}

finally OrgParser::trace(
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

        return finally([line, function, this, &lex]() {
            report(Builder(
                       OrgParser::ReportKind::LeaveParse,
                       nullptr,
                       line,
                       function)
                       .with_lex(lex)
                       .report);
        });

    } else {
        return finally{[]() {}};
    }
}

void OrgParser::print(
    const std::string& msg,
    int                line,
    const char*        function,
    OrgLexer*          lexer) {
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
            lex.finished() ? "<lexer-finished>" : fmt1(lex.tok()),
            getLocMsg(lex),
            tok,
            lex.printToString([](ColStream& os, OrgToken const& t) {
                os << os.yellow() << escape_for_write(t.value.text)
                   << os.end() << fmt1(t.value);
            })),
        line,
        function);
}
