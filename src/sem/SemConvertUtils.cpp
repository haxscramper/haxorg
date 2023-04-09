#include <sem/SemConvert.hpp>
#include <hstd/stdlib/Func.hpp>


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
    if (!locationResolver) {
        return std::nullopt;
    }

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
                    if (tok.hasData()) {
                        PosStr str{tok.getText()};
                        return locationResolver(str);
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


    auto getLoc = [&]() -> QString {
        QString res;
        if (locationResolver && in.node.has_value()) {
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
            os << "@{ " << to_string(in.field.value()) << " " << getLoc();
            break;
        }

        case ReportKind::LeaveField: {
            os << "@} " << to_string(in.field.value()) << " " << getLoc();
            break;
        }

        case ReportKind::Json: {
            break;
        }

        case ReportKind::Enter: {
            os << "> " << in.name.value();
            if (in.node.has_value() && in.node->isValid()) {
                os << " " << to_string(in.node->kind())
                   << " ID:" << in.node->id.getUnmasked();
            }

            os << " " << getLoc();
            if (in.node.has_value() && in.node->isValid()
                && in.node->get().isTerminal()) {
                os << escape_literal(in.node->strVal());
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
