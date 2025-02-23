#include <haxorg/exporters/Exporter.hpp>
#include <hstd/stdlib/Json.hpp>
#include <haxorg/lexbase/TraceStructured.hpp>

using namespace hstd;
using namespace org::algo;

void ExporterEventBase::report(CR<VisitReport> ev) {
    using K = typename VisitReport::Kind;
    auto os = getStream();

    if (traceStructured) {
        using namespace org::report;
        EntryExport exp{};

#define __kind(K)                                                         \
    case VisitReport::Kind::K: {                                          \
        exp.kind = EntryExport::Kind::K;                                  \
        break;                                                            \
    }

        switch (ev.kind) {
            __kind(VisitField);
            __kind(VisitSubnode);
            __kind(NewRes);
            __kind(VisitToEval);
            __kind(VisitValue);
            __kind(VisitDispatchHook);
            __kind(VisitStart);
            __kind(VisitEnd);
            __kind(VisitDispatch);
            __kind(VisitSpecificKind);
            __kind(PushVisit);
            __kind(PopVisit);
            __kind(VisitGeneric);
            __kind(VisitTop);
            __kind(VisitVariant);
            __kind(Print);
        }

        if (ev.function) { exp.codeFunction = ev.function; }
        if (ev.msg) { exp.msg = ev.msg; }
        if (ev.line) { exp.codeLine = ev.line; }
        if (ev.field) { exp.field = ev.field; }
        if (ev.type) { exp.type = ev.type; }
        exp.level = ev.level;

        os << to_json_eval(exp).dump();
    } else {
        os << os.indent(ev.level * 2) << (ev.isStart ? ">" : "<") << " "
           << fmt1(ev.kind);

        if (ev.node) {
            os << " node:" << fmt1((*ev.node)->getKind());
            if (auto const& l = ev.node->value->loc) {
                os << " loc:" << os.cyan() << l->line << ":" << l->column
                   << os.end();
            }
        }
        if (ev.field) { os << " field:" << ev.field.value(); }
        if (ev.msg) {
            os << " msg:" << os.yellow() << *ev.msg << os.end();
        }
        os << " on";
        if (ev.file) {
            os << " " << fs::path(ev.file).stem() << ":" << fmt1(ev.line)
               << " " << os.end();
        } else {
            os << " " << fmt1(ev.line) << " " << os.end();
        }
    }

    endStream(os);
}
