#pragma once

#include <exporters/Exporter.hpp>

struct ExporterSubtreeStructure
    : public Exporter<ExporterSubtreeStructure, json> {

    using Base = Exporter<ExporterSubtreeStructure, json>;
#define __ExporterBase Base
    EXPORTER_USING()
#undef __ExporterBase

    template <typename T>
    json newRes(CR<T>) {
        return json::object();
    }

    json newRes(In<sem::Subtree> tree);

    template <typename T>
    void visitField(json&, const char*, CR<T>) {}

    void visitStructuralCommon(json& j, In<sem::Org> node);
    void visitSubtree(json& j, In<sem::Subtree> tree);
    void visitDocument(json& j, In<sem::Document> doc);
};
