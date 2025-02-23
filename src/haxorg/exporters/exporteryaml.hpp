#pragma once

#include <haxorg/exporters/Exporter.hpp>
#include <hstd/stdlib/Yaml.hpp>

namespace org::algo {
struct ExporterYaml : public Exporter<ExporterYaml, hstd::yaml> {
    using Base = Exporter<ExporterYaml, hstd::yaml>;
#define __ExporterBase Base
    EXPORTER_USING()
#undef __ExporterBase

    template <typename T>
    hstd::yaml newRes(hstd::Opt<T> const& arg) {
        if (arg) {
            return newRes(*arg);
        } else {
            return hstd::yaml();
        }
    }


    hstd::yaml eval(hstd::Str const& value) {
        hstd::yaml tmp = hstd::yaml(value);
        return tmp;
    }

    template <typename T>
    hstd::yaml newRes(T const&) {
        return hstd::yaml();
    }


    hstd::yaml eval(bool value) { return hstd::yaml(value); }
    hstd::yaml eval(int value) { return hstd::yaml(value); }
    hstd::yaml eval(std::string const& value) { return hstd::yaml(value); }

    template <typename E>
    hstd::yaml eval(E value)
        requires(std::is_enum<E>::value)
    {
        return hstd::yaml(std::format("{}", value));
    }

    template <typename T>
    hstd::yaml eval(T const& arg)
        requires(!std::is_enum<T>::value)
    {
        hstd::yaml tmp = _this()->newRes(arg);
        _this()->visit(tmp, arg);
        return tmp;
    }

    hstd::yaml newRes(sem::SemId<sem::Org> org);

    template <typename T>
    void visitField(
        hstd::yaml&         j,
        const char*         name,
        hstd::Opt<T> const& value) {
        if (value) {
            j[name] = eval(value.value());
        } else {
            if (!skipNullFields) { j[name] = hstd::yaml(); }
        }
    }

    template <typename T>
    hstd::yaml eval(hstd::Vec<T> const& values) {
        hstd::yaml tmp;
        for (const auto& it : values) { tmp.push_back(eval(it)); }
        return tmp;
    }

    template <typename T>
    hstd::yaml eval(hstd::UnorderedMap<hstd::Str, T> const& map) {
        hstd::yaml tmp;
        for (const auto& [key, val] : map) { tmp[key] = eval(val); }
        return tmp;
    }

    void visitField(
        hstd::yaml& y,
        char const* name,
        hstd::UnorderedMap<int, sem::SemId<sem::Org>> const&) {}

    void visitField(hstd::yaml& j, const char* name, int field) {
        hstd::yaml result = eval(field);
        if (!skipZeroFields || field != 0) { j[name] = result; }
    }

    void visitField(hstd::yaml& j, const char* name, bool field) {
        if (!skipFalseFields || field != false) { j[name] = eval(field); }
    }


    template <typename T>
    void visitField(hstd::yaml& j, const char* name, T const& field) {
        hstd::yaml result = eval(field);
        if (!skipNullFields || !result.IsNull()) { j[name] = result; }
    }

    template <typename T>
    void visit(hstd::yaml& res, sem::SemId<T> const& arg) {
        visitDispatch(res, arg.asOrg());
    }

    bool skipNullFields  = false;
    bool skipFalseFields = false;
    bool skipZeroFields  = false;
    bool skipLocation    = false;
    bool skipId          = false;
};

extern template class Exporter<ExporterYaml, hstd::yaml>;
} // namespace org::algo
