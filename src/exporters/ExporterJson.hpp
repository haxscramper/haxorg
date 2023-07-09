#pragma once

#include <exporters/Exporter.hpp>
#include <hstd/stdlib/Time.hpp>
#include <hstd/stdlib/Json.hpp>

struct ExporterJson : public Exporter<ExporterJson, json> {
    using Base = Exporter<ExporterJson, json>;
#define __ExporterBase Base
    EXPORTER_USING()
#undef __ExporterBase

    void visitSubtreeValueFields(json&, In<sem::Subtree> tree);

    template <typename T>
    json newRes(CVec<T>) {
        return json::array();
    }


    template <typename T>
    json newRes(CR<T>) {
        return json::object();
    }


    template <typename T>
    json newRes(CR<Opt<T>> arg) {
        if (arg) {
            return newRes(*arg);
        } else {
            return json();
        }
    }

    template <typename... Args>
    json newRes(CR<Variant<Args...>> var) {
        return std::visit(
            [this](auto const& it) -> json { return visit(it); }, var);
    }

    json visit(CR<Str> value) { return json(value); }
    json visit(CR<QString> value) { return json(value); }
    json visit(CR<bool> value) { return json(value); }
    json visit(CR<int> value) { return json(value); }

    json visit(CR<QDate> value) {
        return json(value.toString(Qt::ISODate).toStdString());
    }

    json visit(CR<QTime> value) {
        return json(value.toString(Qt::ISODate).toStdString());
    }

    json visit(CR<QDateTime> value) {
        return json(value.toString(Qt::ISODate).toStdString());
    }

    template <typename T>
    json visit(CR<T> arg);

    json newRes(sem::SemId org);

    template <typename T>
    void visitField(json& j, const char* name, CR<Opt<T>> value);

    template <typename T>
    json visit(CR<Vec<T>> values);

    template <typename T>
    json visit(CR<UnorderedMap<Str, T>> map);

    template <typename T>
    void visitField(json& j, const char* name, CR<T> field) {
        j[name] = visit(field);
    }

    void visitDocument(json& j, In<sem::Document> doc) {
        visitField(j, "subnodes", doc->subnodes);
    }
};

extern template class Exporter<ExporterJson, json>;
