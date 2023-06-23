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

    void visitField(int& a, const char* name, sem::SemId id) {
        visit(a, id);
    }

    template <typename T>
    void visit(int& arg, CR<T> opt) {}

    void visitField(int& a, const char* name, CVec<sem::SemId> sub) {
        for (auto const& it : sub) {
            visit(a, it);
        }
    }

    template <typename T>
    void visitField(int& a, const char* name, CVec<sem::SemIdT<T>> sub) {
        for (auto const& it : sub) {
            visit(a, it);
        }
    }

    template <typename T>
    void visitField(int& arg, const char* name, sem::SemIdT<T> org) {
        visit(arg, org.toId());
    }

    template <typename T>
    void visit(int& arg, sem::SemIdT<T> org) {
        visit(arg, org.toId());
    }

    template <typename T>
    void visitField(int& j, const char*, CR<T> value) {
        visit(j, value);
    }


    template <typename T>
    void visitField(int& j, const char* name, CR<Opt<T>> value) {
        if (value) {
            visit(j, value.value());
        }
    }
};

#endif // EXPORTERGANTT_HPP
