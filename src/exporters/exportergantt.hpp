#ifndef EXPORTERGANTT_HPP
#define EXPORTERGANTT_HPP

#include <hstd/wrappers/plantuml.hpp>
#include <exporters/Exporter.hpp>

struct GanttExporter : Exporter<GanttExporter, int> {

#define __ExporterBase Exporter<GanttExporter, int>
    EXPORTER_USING()
#undef __ExporterBase

    using Event = puml::Gantt::Event;
    Vec<Event> stack;

    void pushVisit(int&, sem::Wrap<sem::Subtree> tree);

    void popVisit(int&, sem::Wrap<sem::Subtree> tree);
};

#endif // EXPORTERGANTT_HPP
