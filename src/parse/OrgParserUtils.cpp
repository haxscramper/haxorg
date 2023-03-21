#include <parse/OrgParser.hpp>
#include <hstd/stdlib/Debug.hpp>

Opt<LineCol> OrgParser::getLoc(CR<OrgLexer> lex) {
    qDebug() << "get location for" << lex;
    if (lex.finished()) {
        return std::nullopt;
    } else {
        OrgToken tok = lex.tok();
        if (tok.hasData()) {
            PosStr str{tok.getText()};
            return locationResolver(str);
        } else {
            return std::nullopt;
        }
    }
}


OrgParser::ParserError OrgParser::wrapError(
    CR<Error>    err,
    CR<OrgLexer> lex) {
    ParserError result{err};
    auto        loc = getLoc(lex);

    if (loc.has_value()) {
        result.setLoc(loc.value());
    }

    return result;
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

    switch (in.kind) {
        case ReportKind::AddToken: {
            auto id = in.node.value();
            os << " # add [" << id.getIndex() << "] "
               << to_string(group->at(id).kind) << " at " << in.line;
            break;
        }

        case ReportKind::StartNode:
        case ReportKind::EndNode: {
            auto id = in.node.value();
            if (in.kind == ReportKind::StartNode) {
                os << " + start";
            } else {
                os << " - end";
            }

            os << " [" << id.getIndex() << "] "
               << to_string(group->at(id).kind) << " at " << in.line;
            if (in.kind == ReportKind::EndNode) {
                os << " ext=" << group->at(id).getExtent();
            }
            break;
        }

        case ReportKind::EnterParse:
        case ReportKind::LeaveParse: {
            os << (in.kind == ReportKind::EnterParse ? "> " : "< ")
               << fg::Green << in.name.value() << os.end() << ":"
               << fg::Cyan << in.line << os.end();

            if (in.lex != nullptr) {
                os << " [";
                OrgLexer::PrintParams params;
                in.lex->print(os, params);
                os << "]";
            }

            if (in.subname.has_value()) {
                os << " " << in.subname.value();
            }
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
