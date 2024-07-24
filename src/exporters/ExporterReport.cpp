#include <exporters/Exporter.hpp>


void ExporterEventBase::report(CR<VisitReport> ev) {
    using K = typename VisitReport::Kind;
    if (((ev.kind == K::PushVisit || ev.kind == K::VisitStart)
         && !ev.isStart)
        || ((ev.kind == K::PopVisit || ev.kind == K::VisitEnd)
            && ev.isStart)) {
        return;
    }

    auto os = getStream();

    os << os.indent(ev.level * 2) << (ev.isStart ? ">" : "<") << " "
       << fmt1(ev.kind);

    if (ev.visitedNode) {
        os << " node:" << fmt1((*ev.visitedNode)->getKind());
    }

    if (ev.field) { os << " field:" << ev.field.value(); }

    if (ev.msg) { os << " msg:" << os.yellow() << *ev.msg << os.end(); }

    os << " on " << fs::path(ev.file).stem() << ":" << fmt1(ev.line) << " "
       << " " << os.end();

    endStream(os);
}
