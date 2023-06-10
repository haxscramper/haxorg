#ifndef EXPORTERGANTT_HPP
#define EXPORTERGANTT_HPP

#include <hstd/wrappers/plantuml.hpp>
#include <exporters/Exporter.hpp>

struct ExporterGantt : Exporter<ExporterGantt, int> {

#define __ExporterBase Exporter<ExporterGantt, int>
    EXPORTER_USING()
#undef __ExporterBase

    using Event = puml::Gantt::Event;
    puml::Gantt gantt;
    struct Ctx {
        Event event;
        bool  filled = false;
    };

    Vec<Ctx> stack;

    void pushVisit(int&, sem::SemIdT<sem::Subtree> tree);

    void popVisit(int&, sem::SemIdT<sem::Subtree> tree);

    template <typename T>
    void visitField(int&, const char*, CR<T>) {}
};

#endif // EXPORTERGANTT_HPP
