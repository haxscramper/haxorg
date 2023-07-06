#pragma once

#include <exporters/Exporter.hpp>
#include <hstd/stdlib/Time.hpp>

struct ExporterJson : public Exporter<ExporterJson, json> {
    using Base = Exporter<ExporterJson, json>;
#define __ExporterBase Base
    EXPORTER_USING()
#undef __ExporterBase

    void visitSubtreeValueFields(json&, In<sem::Subtree> tree);

    template <typename T>
    json newRes(CR<T>);

    template <typename T>
    json visit(CR<T>);

    template <typename T>
    void visitField(json& j, const char* name, CR<Opt<T>> value);

    template <typename T>
    json visit(CR<Vec<T>> values);

    template <typename T>
    json visit(CR<UnorderedMap<Str, T>> map);

    template <typename T>
    void visitField(json& j, const char* name, CR<T> field);

    void visitDocument(json& j, In<sem::Document> doc);
};

extern template class Exporter<ExporterJson, json>;
extern class ExporterJson;
