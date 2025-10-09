#pragma clang diagnostic error "-Wswitch"

#include <haxorg/parse/OrgParser.hpp>
#include <hstd/stdlib/Json.hpp>
#include <haxorg/lexbase/TraceStructured.hpp>

using namespace hstd;
using namespace org::parse;

void OrgParser::report(CR<Report> in) {
    using fg = TermColorFg8Bit;

    if (reportHook) { reportHook(in); }

    if (in.kind == ReportKind::EnterParse
        || in.kind == ReportKind::StartNode) {
        ++activeLevel;
    }

    ColStream os = getStream();


    if (traceStructured) {
        using namespace org::report;

        EntryParser res;
        res.depth = activeLevel;
#define __kind(K)                                                         \
    case ReportKind::K: {                                                 \
        res.kind = EntryParser::Kind::K;                                  \
        break;                                                            \
    }
        switch (in.kind) {
            __kind(Error);
            __kind(EnterParse);
            __kind(LeaveParse);
            __kind(StartNode);
            __kind(EndNode);
            __kind(AddToken);
            __kind(Print);
            __kind(FailTree);
        }

        if (in.lex != nullptr) {
            ValueLexPosition val;
            val.maxPos = in.lex->in->size();

            Opt<LineCol> loc = this->getLoc(*in.lex);
            if (loc.has_value()) {
                val.line   = loc->line;
                val.column = loc->column;
            }

            if (!in.lex->pos.isNil()) {
                val.nowPos = in.lex->pos.getIndex();
            }

            for (int i = 0; i < 10; ++i) {
                if (in.lex->hasNext(i)) {
                    val.tokens.push_back(ValueToken{
                        .kind  = fmt1(in.lex->tok(i).kind),
                        .index = in.lex->pos.isNil()
                                   ? -1
                                   : static_cast<int>(
                                         in.lex->pos.getIndex() + i),
                        .value = in.lex->tok(i).value.text,
                    });
                }
            }
            res.lex = val;
        }

        if (in.msg) { res.message = in.msg; }
        if (in.function) { res.codeFunction = in.function; }
        if (in.line) { res.codeLine = in.line; }

        if (in.node && !in.node->isNil()) {
            ValueOrgNode node;
            node.kind = fmt1(group->at(*in.node).kind);
            node.id   = fmt1(in.node->getValue());
            res.node  = node;
        }

        os << to_json_eval(res).dump();

    } else {
        os << repeat("  ", activeLevel);
        auto print_token = [](ColStream& os, OrgToken const& t) {
            os << escape_for_write(t->text);
        };

        auto printTokens = [&]() {
            if (in.lex != nullptr) {
                os << " [";
                OrgLexer::PrintParams params;
                in.lex->print(os, print_token, params);
                os << "]";
            }
        };

        auto getLoc = [&]() -> std::string {
            std::string res;
            if (in.lex != nullptr) {
                Opt<LineCol> loc = this->getLoc(*in.lex);
                if (loc.has_value()) {
                    res = "$#:$# " % to_string_vec(loc->line, loc->column);
                }
            }
            return res;
        };

        auto printSourceLoc = [&]() {
            if (in.function) { os << " " << in.function; }
            os << fmt(":{}", in.line);
        };

        auto printNode = [&]() {
            auto id = in.node.value();
            if (in.node && !in.node.value().isNil()) {
                os << std::format(
                    "{} {} ID:{} @{}",
                    (in.kind == ReportKind::StartNode ? "+" : "-"),
                    group->at(id).kind,
                    id.getUnmasked(),
                    in.line);
            }
        };

        LOGIC_ASSERTION_CHECK(0 <= treeDepth(), "Negative tree depth");

        switch (in.kind) {
            case ReportKind::Error: {
                os << "  ERR";
                printSourceLoc();
                if (in.lex) { os << " " << getLoc(); }
                if (in.msg) { os << " " << *in.msg; }
                if (in.node) { printNode(); }
                printTokens();
                break;
            }

            case ReportKind::FailTree: {
                os << "  FAIL ";
                printSourceLoc();
                if (in.lex) { os << " " << getLoc(); }
                if (in.msg) { os << " " << *in.msg; }
                if (in.node) {
                    os << "Reverting to ";
                    printNode();
                }
                printTokens();
                break;
            }

            case ReportKind::Print: {
                if (in.msg) { os << "  " << *in.msg; }
                os << std::format(" @{}", in.line);
                printTokens();
                break;
            }

            case ReportKind::AddToken: {
                auto id = in.node.value();
                os << std::format(
                    "  add {} ID:{} @{} with '{}'",
                    group->at(id).kind,
                    id.getUnmasked(),
                    in.line,
                    escape_literal(
                        group->at(id).isMono() ? "<mono>"
                                               : group->val(id).text));
                if (in.msg && !in.msg->empty()) {
                    os << " " << in.msg.value();
                }
                break;
            }

            case ReportKind::StartNode:
            case ReportKind::EndNode: {
                printNode();
                auto id = in.node.value();
                if (in.kind == ReportKind::EndNode) {
                    os << " ext="
                       << std::format("{}", group->at(id).getExtent());
                }
                break;
            }

            case ReportKind::EnterParse:
            case ReportKind::LeaveParse: {
                os << std::format(
                    "{} [{}] ",
                    in.kind == ReportKind::EnterParse ? ">" : "<",
                    treeDepth())
                   << fg::Green << fmt1(in.function ? in.function : "")
                   << os.end() << ":" << fg::Cyan << fmt1(in.line)
                   << os.end();

                printTokens();

                break;
            }
        }
    }


    endStream(os);

    if (in.kind == ReportKind::LeaveParse
        || in.kind == ReportKind::EndNode) {
        --activeLevel;
    }
}
