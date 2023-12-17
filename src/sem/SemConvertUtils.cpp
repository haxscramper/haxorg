import org.sem.SemConvert;
import hstd.stdlib.Func;


using namespace sem;

using org = OrgNodeKind;
using otk = OrgTokenKind;
using Err = OrgConverter::Errors;


OrgConverter::ConvertError OrgConverter::wrapError(
    CR<Error>      err,
    CR<OrgAdapter> adapter) {
    ConvertError result{err};
    auto         loc = getLoc(adapter);

    if (!result.getAdapter().has_value()) {
        result.setAdapter(adapter);
    }

    if (loc.has_value()) {
        result.setLoc(loc.value());
    }

    return result;
}

Opt<LineCol> OrgConverter::getLoc(CR<OrgAdapter> adapter) {
    int   offset  = 0;
    auto& g       = *adapter.group;
    bool  inRange = true;
    while (inRange) {
        bool leftOk  = false;
        bool rightOk = false;
        for (int i : Vec{-1, 1}) {
            int idx = adapter.id.getIndex() + offset * i;
            if (0 <= idx && idx < g.size()) {
                if (i == -1) {
                    leftOk = true;
                }
                if (i == 1) {
                    rightOk = true;
                }
                if (g.at(OrgId(idx)).isTerminal()) {
                    auto tok = g.tokens->at(g.at(OrgId(idx)).getToken());
                    if (!tok->isEmpty()) {
                        return LineCol{tok->getLine(), tok->getCol()};
                    }
                }
            }
        }
        if (!(leftOk || rightOk)) {
            inRange = false;
        }
        ++offset;
    }

    return std::nullopt;
}

std::string OrgConverter::getLocMsg(CR<OrgAdapter> adapter) {
    Opt<LineCol>    loc = getLoc(adapter);
    Opt<OrgTokenId> tok;
    if (adapter.get().isTerminal()) {
        tok = adapter.get().getToken();
    }

    return "$#:$# (node $#, token $#, pos $#)"
         % to_string_vec(
               loc ? loc->line : -1,
               loc ? loc->column : -1,
               adapter.id.getIndex(),
               tok ? fmt1(tok->getIndex()) : fmt1("<none>"),
               loc ? loc->pos : -1);
}

void OrgConverter::report(CR<OrgConverter::Report> in) {
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


    auto getLoc = [&]() -> std::string {
        std::string res;
        if (in.node.has_value()) {
            Opt<LineCol> loc = this->getLoc(in.node.value());
            if (loc.has_value()) {
                res = "$#:$# " % to_string_vec(loc->line, loc->column);
            }
        }
        return res;
    };

    if (in.kind == ReportKind::Enter
        || in.kind == ReportKind::EnterField) {
        ++depth;
    }

    ColStream os = getStream();
    os << repeat("  ", depth);


    switch (in.kind) {
        case ReportKind::EnterField: {
            os << "@{ " << fmt1(in.field.value()) << " " << getLoc();
            break;
        }

        case ReportKind::LeaveField: {
            os << "@} " << fmt1(in.field.value()) << " " << getLoc();
            break;
        }

        case ReportKind::Json: {
            break;
        }

        case ReportKind::Enter: {
            os << "> " << in.name.value();
            if (in.node.has_value() && in.node->isValid()) {
                os << " " << fmt1(in.node->kind())
                   << " ID:" << in.node->id.getUnmasked();
            }

            os << " " << getLoc();
            if (in.node.has_value() && in.node->isValid()
                && in.node->get().isTerminal()) {
                os << escape_literal(in.node->val().getText());
            }
            break;
        }
        case ReportKind::Leave: {
            os << "< " << in.name.value() << " " << getLoc();
            break;
        }
    }

    endStream(os);


    if (in.kind == ReportKind::Leave
        || in.kind == ReportKind::LeaveField) {
        --depth;
    }

    if (traceUpdateHook) {
        traceUpdateHook(in, trace, false);
    }
}
