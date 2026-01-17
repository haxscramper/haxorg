#pragma once

#include <haxorg/exporters/Exporter.hpp>
#include <hstd/stdlib/Time.hpp>
#include <hstd/stdlib/Json.hpp>
#include <hstd/stdlib/JsonUse.hpp>

namespace org::algo {

struct ExporterJson : public Exporter<ExporterJson, json> {
    using Base = Exporter<ExporterJson, json>;
#define __ExporterBase Base
    EXPORTER_USING()
#undef __ExporterBase

    void visitSubtreeValueFields(json&, In<sem::Subtree> tree);

    template <typename T>
    json newRes(hstd::CVec<T>) {
        return json::array();
    }


    template <typename T>
    json newRes(T const&) {
        return json::object();
    }


    template <typename T>
    json newRes(hstd::Opt<T> const& arg) {
        if (arg) {
            return newRes(*arg);
        } else {
            return json();
        }
    }

    template <typename... Args>
    json newRes(hstd::Variant<Args...> const& var) {
        return std::visit(
            [this](auto const& it) -> json { return eval(it); }, var);
    }

    json eval(hstd::Str const& value) { return json(value); }
    json eval(std::string const& value) { return json(value); }
    json eval(bool value) { return json(value); }
    json eval(int value) { return json(value); }
    json eval(json value) { return value; }

    template <typename T>
    json eval(T const& arg);

    json newRes(sem::SemId<sem::Org> org);

    template <typename T>
    json newRes(sem::SemId<T> org) {
        return newRes(org.template as<sem::Org>());
    }

    template <typename T>
    void visitField(json& j, const char* name, hstd::Opt<T> const& value);

    template <typename T>
    json eval(hstd::Vec<T> const& values);

    template <typename T>
    json eval(hstd::UnorderedMap<hstd::Str, T> const& map);

    template <typename T>
    void visitField(json& j, const char* name, T const& field) {
        j[name] = eval(field);
    }

    template <typename T>
    void visitField(json& j, const char* name, hstd::CVec<T> field) {
        if (!skipEmptyLists || !field.empty()) { j[name] = eval(field); }
    }

    template <typename T>
    void visit(json& res, sem::SemId<T> const& arg) {
        visitDispatch(res, arg.asOrg());
    }

    void visit(json& res, sem::SemId<org::sem::Space> const& arg);

    bool skipEmptyLists = false;
    bool skipLocation   = false;
    bool skipId         = false;
    bool skipNullFields = false;
    /// \brief Replace multi-character space with a single one on export.
    bool normalizeSpaces = false;

    virtual void visitDispatchHook(json&, sem::SemId<sem::Org>) {}

    static json toJson(sem::SemId<sem::Org> node) {
        ExporterJson exp{};
        return exp.eval(node);
    }
};

extern template class Exporter<ExporterJson, json>;
} // namespace org::algo
