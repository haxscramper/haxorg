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

    if (!result.getAdapter().has_value()) { result.setAdapter(adapter); }

    if (loc.has_value()) { result.setLoc(loc.value()); }

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
                if (i == -1) { leftOk = true; }
                if (i == 1) { rightOk = true; }
                if (g.at(OrgId(idx)).isTerminal()) {
                    auto tok = g.tokens->at(g.at(OrgId(idx)).getToken());
                    if (!tok->isFake()) {
                        return LineCol{tok->line, tok->col};
                    }
                }
            }
        }
        if (!(leftOk || rightOk)) { inRange = false; }
        ++offset;
    }

    return std::nullopt;
}

std::string OrgConverter::getLocMsg(CR<OrgAdapter> adapter) {
    Opt<LineCol>    loc = getLoc(adapter);
    Opt<OrgTokenId> tok;
    if (adapter.get().isTerminal()) { tok = adapter.get().getToken(); }

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

    if (reportHook) { reportHook(in); }

    if (traceUpdateHook) { traceUpdateHook(in, TraceState, true); }
    if (!TraceState) {
        if (traceUpdateHook) { traceUpdateHook(in, TraceState, false); }

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
            os << "{ " << fmt1(in.field.value()) << fmt(" @{}", in.line)
               << " " << getLoc();
            break;
        }

        case ReportKind::LeaveField: {
            os << "} " << fmt1(in.field.value()) << " " << getLoc();
            break;
        }

        case ReportKind::Json: {
            break;
        }

        case ReportKind::Enter: {
            os << "> " << (in.function ? in.function : "")
               << fmt(" @{}", in.line);
            if (in.node.has_value() && in.node->isValid()) {
                os << " " << fmt1(in.node->kind())
                   << " ID:" << fmt1(in.node->id.getUnmasked());
            }

            os << " " << getLoc();
            if (in.node.has_value() && in.node->isValid()
                && in.node->get().isTerminal()) {
                os << escape_literal(in.node->val().text);
            }
            break;
        }
        case ReportKind::Leave: {
            os << "< " << (in.function ? in.function : "") << " "
               << getLoc();
            break;
        }

        case ReportKind::Print: {
            os << "  " << (in.function ? in.function : "")
               << fmt(" @{}", in.line);
            if (in.msg) { os << *in.msg; }
        }
    }

    endStream(os);


    if (in.kind == ReportKind::Leave
        || in.kind == ReportKind::LeaveField) {
        --depth;
    }

    if (traceUpdateHook) { traceUpdateHook(in, TraceState, false); }
}


struct Builder : OperationsMsgBulder<Builder, OrgConverter::Report> {
    Builder& with_sem(SemId sem) {
        report.semResult = sem;
        return *this;
    }

    Builder& with_node(OrgAdapter node) {
        report.node = node;
        return *this;
    }

    Builder& with_field(OrgSpecName field) {
        report.field = field;
        return *this;
    }

    Builder(
        OrgConverter::ReportKind kind,
        char const*              file     = __builtin_FILE_NAME(),
        int                      line     = __builtin_LINE(),
        char const*              function = __builtin_FUNCTION()) {
        this->report = OrgConverter::Report{
            OperationsMsg{
                .file     = file,
                .line     = line,
                .function = function,
            },
            .kind = kind,
        };
    }
};

finally OrgConverter::trace(
    In          adapter,
    Opt<Str>    subname,
    int         line,
    const char* function) {
    if (TraceState) {
        report(
            Builder(
                OrgConverter::ReportKind::Enter, nullptr, line, function)
                .with_node(adapter)
                .with_msg(subname)
                .report);

        return finally{[this, line, function, adapter, subname]() {
            report(Builder(
                       OrgConverter::ReportKind::Leave,
                       nullptr,
                       line,
                       function)
                       .with_node(adapter)
                       .with_msg(subname)
                       .report);
        }};

    } else {
        return finally{[]() {}};
    }
}


finally OrgConverter::field(
    OrgSpecName name,
    In          adapter,
    Opt<Str>    subname,
    int         line,
    const char* function) {
    if (TraceState) {
        report(Builder(
                   OrgConverter::ReportKind::EnterField,
                   nullptr,
                   line,
                   function)
                   .with_node(adapter)
                   .with_msg(subname)
                   .with_field(name)
                   .report);

        return finally{[this, line, function, adapter, name, subname]() {
            report(Builder(
                       OrgConverter::ReportKind::LeaveField,
                       nullptr,
                       line,
                       function)
                       .with_node(adapter)
                       .with_msg(subname)
                       .with_field(name)
                       .report);
        }};

    } else {
        return finally{[]() {}};
    }
}

void OrgConverter::print_json(
    SemId<Org>  semResult,
    int         line,
    const char* function) {
    if (TraceState) {
        report(Builder(
                   OrgConverter::ReportKind::Json, nullptr, line, function)
                   .with_sem(semResult)
                   .report);
    }
}

void OrgConverter::print(std::string msg, int line, const char* function) {
    if (TraceState) {
        report(
            Builder(
                OrgConverter::ReportKind::Print, nullptr, line, function)
                .with_msg(msg)
                .report);
    }
}
