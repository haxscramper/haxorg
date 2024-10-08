#pragma once

#include <haxorg/exporters/Exporter.hpp>
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
            [this](auto const& it) -> json { return eval(it); }, var);
    }

    json eval(CR<Str> value) { return json(value); }
    json eval(CR<std::string> value) { return json(value); }
    json eval(CR<bool> value) { return json(value); }
    json eval(CR<int> value) { return json(value); }

    template <typename T>
    json eval(CR<T> arg);

    json newRes(sem::SemId<sem::Org> org);

    template <typename T>
    json newRes(sem::SemId<T> org) {
        return newRes(org.template as<sem::Org>());
    }

    template <typename T>
    void visitField(json& j, const char* name, CR<Opt<T>> value);

    template <typename T>
    json eval(CR<Vec<T>> values);

    template <typename T>
    json eval(CR<UnorderedMap<Str, T>> map);

    template <typename T>
    void visitField(json& j, const char* name, CR<T> field) {
        j[name] = eval(field);
    }

    template <typename T>
    void visitField(json& j, const char* name, CVec<T> field) {
        if (!skipEmptyLists || !field.empty()) { j[name] = eval(field); }
    }

    template <typename T>
    void visit(json& res, sem::SemId<T> const& arg) {
        visitDispatch(res, arg.asOrg());
    }

    bool skipEmptyLists = false;
    bool skipLocation   = false;
    bool skipId         = false;
    bool skipNullFields = false;

    virtual void visitDispatchHook(json&, sem::SemId<sem::Org>) {}
};

extern template class Exporter<ExporterJson, json>;
