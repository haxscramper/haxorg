#include <haxorg/sem/SemConvert.hpp>
#include <hstd/stdlib/Func.hpp>
#include <haxorg/lexbase/TraceStructured.hpp>


using namespace sem;

using onk = OrgNodeKind;
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
    if (adapter.isTerminal()) {
        if (adapter.val().isFake()) {
            return std::nullopt;
        } else {
            return LineCol{adapter.val().line, adapter.val().col};
        }
    } else if (adapter.isMono()) {
        return std::nullopt;

    } else if (auto nested = adapter.get().nestedNodes(adapter.id);
               nested) {
        for (OrgId const& id : nested.value()) {
            OrgAdapter sub{adapter.group, id};
            if (sub.isTerminal() && !sub.val().isFake()) {
                return LineCol{sub.val().line, sub.val().col};
            }
        }
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

    if (!TraceState) { return; }

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
    if (traceStructured) {
        using namespace org::report;
        EntrySem res;
        res.indent = depth;
#define __kind(K)                                                         \
    case ReportKind::K: {                                                 \
        res.kind = EntrySem::Kind::K;                                     \
        break;                                                            \
    }
        switch (in.kind) {
            __kind(EnterField);
            __kind(LeaveField);
            __kind(Leave);
            __kind(Print);
            __kind(Enter);
            __kind(Json);
        }

        if (in.node && !in.node->isNil()) {
            ValueOrgNode node;
            node.kind = fmt1(in.node->kind());
            node.id   = fmt1(in.node->id);
            if (in.node->isTerminal()) {
                node.value = in.node->val().text;
            }
            res.node = node;
        }

        if (in.msg) { res.message = in.msg; }
        if (in.function) { res.codeFunction = in.function; }
        if (in.line) { res.codeLine = in.line; }

        os << to_json_eval(res).dump();
    } else {
        os << repeat("  ", depth);


        switch (in.kind) {
            case ReportKind::EnterField: {
                os << "{ " << fmt1(in.field.value())
                   << fmt(" @{}", in.line) << " " << getLoc();
                if (in.msg) { os << " " << *in.msg; }
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
                if (in.msg) { os << " " << *in.msg; }
                if (in.node.has_value() && in.node->isValid()
                    && in.node->get().isTerminal()) {
                    os << " " << escape_literal(in.node->val().text);
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
                if (in.msg) { os << " " << *in.msg; }
            }
        }
    }


    endStream(os);


    if (in.kind == ReportKind::Leave
        || in.kind == ReportKind::LeaveField) {
        --depth;
    }
}


struct Builder : OperationsMsgBulder<Builder, OrgConverter::Report> {
    Builder& with_sem(SemId<Org> sem) {
        report.semResult = sem;
        return *this;
    }

    Builder& with_node(CR<Opt<OrgAdapter>> node) {
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
    Opt<In>     adapter,
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
