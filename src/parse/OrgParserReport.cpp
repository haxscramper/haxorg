#include <parse/OrgParser.hpp>

std::string OrgParser::Error::getLocMsg() const {
    return "$#:$# (tok $#, pos $#)"
         % to_string_vec(
               loc ? loc->line : -1,
               loc ? loc->column : -1,
               id.isNil() ? "<none>" : fmt1(id.getIndex()),
               loc ? loc->pos : -1);
}

const char* OrgParser::UnexpectedToken::what() const noexcept {
    return strdup(
        "Expected $#, but got $# at $# ($#)"
        % to_string_vec(
            std::visit(
                overloaded{
                    [](CR<TokenWithValue> it) {
                        return "$# ('$#')"
                             % to_string_vec(it.kind, it.value);
                    },
                    [](auto const& it) { return std::format("{}", it); }},
                wanted),
            this->token,
            getLocMsg(),
            this->extraMsg));
}

const char* OrgParser::UnhandledToken::what() const noexcept {
    return strdup(
        std::format(
            "Encountered {} at {}, which is was not expected ({})",
            token,
            getLocMsg(),
            extraMsg)
            .c_str());
}


void OrgParser::report(CR<Report> in) {
    using fg = TermColorFg8Bit;

    if (reportHook) {
        reportHook(in);
    }

    if (traceUpdateHook) {
        traceUpdateHook(in, trace, true);
    }
    if (!trace) {
        if (traceUpdateHook) {
            traceUpdateHook(in, trace, false);
        }

        return;
    }

    if (in.kind == ReportKind::EnterParse
        || in.kind == ReportKind::StartNode) {
        ++depth;
    }

    ColStream os = getStream();
    os << repeat("  ", depth);
    auto print_token = [](ColStream& os, OrgToken const& t) {
        os << escape_for_write(t->getText());
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

    CHECK(0 <= treeDepth()) << "Negative tree depth";

    switch (in.kind) {
        case ReportKind::Error: {
            os << "  error";
            break;
        }

        case ReportKind::Print: {
            os << std::format(
                "  {} {}:{} ", in.line, getLoc(), in.subname.value());
            printTokens();
            break;
        }

        case ReportKind::AddToken: {
            auto id = in.node.value();
            os << std::format(
                "  # add [{}] {} at {} with {}",
                id.getIndex(),
                group->at(id).kind,
                in.line,
                escape_literal(group->val(id).getText()));
            break;
        }

        case ReportKind::StartNode:
        case ReportKind::EndNode: {
            auto id = in.node.value();
            if (in.kind == ReportKind::StartNode) {
                os << std::format(
                    "+ started node, level is {}", treeDepth());
            } else {
                os << std::format(
                    "- ended node, level is {}", treeDepth());
            }

            os << std::format(
                " [{}] {} at {}",
                id.getIndex(),
                group->at(id).kind,
                in.line);

            if (in.kind == ReportKind::EndNode) {
                os << " ext="
                   << std::format("{}", group->at(id).getExtent());
            }
            break;
        }

        case ReportKind::EnterParse:
        case ReportKind::LeaveParse: {
            os << std::format(
                "{} ~ {} ",
                in.kind == ReportKind::EnterParse ? "> " : "< ",
                treeDepth())
               << fg::Green << fmt1(in.name.value()) << os.end() << ":"
               << fg::Cyan << fmt1(in.line) << os.end();

            if (in.subname.has_value()) {
                os << " <@" << in.subname.value() << ">";
            }

            printTokens();

            break;
        }
    }

    endStream(os);

    if (in.kind == ReportKind::LeaveParse
        || in.kind == ReportKind::EndNode) {
        --depth;
    }

    if (traceUpdateHook) {
        traceUpdateHook(in, trace, false);
    }
}
