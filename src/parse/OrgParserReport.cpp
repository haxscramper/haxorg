#include <parse/OrgParser.hpp>

void OrgParser::report(CR<Report> in) {
    using fg = TermColorFg8Bit;

    if (reportHook) { reportHook(in); }

    if (in.kind == ReportKind::EnterParse
        || in.kind == ReportKind::StartNode) {
        ++depth;
    }

    ColStream os = getStream();
    os << repeat("  ", depth);
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
        os << std::format(
            "{} {} ID:{} @{}",
            (in.kind == ReportKind::StartNode ? "+" : "-"),
            group->at(id).kind,
            id.getUnmasked(),
            in.line);
    };

    CHECK(0 <= treeDepth()) << "Negative tree depth";

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
            break;
        }

        case ReportKind::StartNode:
        case ReportKind::EndNode: {
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
               << os.end() << ":" << fg::Cyan << fmt1(in.line) << os.end();

            printTokens();

            break;
        }
    }

    endStream(os);

    if (in.kind == ReportKind::LeaveParse
        || in.kind == ReportKind::EndNode) {
        --depth;
    }
}
