#pragma once

#include <haxorg/exporters/Exporter.hpp>
#include <hstd/stdlib/Yaml.hpp>

namespace org::algo {
struct ExporterYaml : public Exporter<ExporterYaml, yaml> {
    using Base = Exporter<ExporterYaml, yaml>;
#define __ExporterBase Base
    EXPORTER_USING()
#undef __ExporterBase

    template <typename T>
    yaml newRes(hstd::Opt<T> const& arg) {
        if (arg) {
            return newRes(*arg);
        } else {
            return yaml();
        }
    }


    yaml eval(hstd::Str const& value) {
        yaml tmp = yaml(value);
        return tmp;
    }

    template <typename T>
    yaml newRes(T const&) {
        return yaml();
    }


    yaml eval(bool value) { return yaml(value); }
    yaml eval(int value) { return yaml(value); }
    yaml eval(std::string const& value) { return yaml(value); }

    template <typename E>
    yaml eval(E value)
        requires(std::is_enum<E>::value)
    {
        return yaml(std::format("{}", value));
    }

    template <typename T>
    yaml eval(T const& arg)
        requires(!std::is_enum<T>::value)
    {
        yaml tmp = _this()->newRes(arg);
        _this()->visit(tmp, arg);
        return tmp;
    }

    yaml newRes(sem::SemId<sem::Org> org);

    template <typename T>
    void visitField(
        yaml&         j,
        const char*         name,
        hstd::Opt<T> const& value) {
        if (value) {
            j[name] = eval(value.value());
        } else {
            if (!skipNullFields) { j[name] = yaml(); }
        }
    }

    template <typename T>
    yaml eval(hstd::Vec<T> const& values) {
        yaml tmp;
        for (const auto& it : values) { tmp.push_back(eval(it)); }
        return tmp;
    }

    template <typename T>
    yaml eval(hstd::UnorderedMap<hstd::Str, T> const& map) {
        yaml tmp;
        for (const auto& [key, val] : map) { tmp[key] = eval(val); }
        return tmp;
    }

    void visitField(
        yaml& y,
        char const* name,
        hstd::UnorderedMap<int, sem::SemId<sem::Org>> const&) {}

    void visitField(yaml& j, const char* name, int field) {
        yaml result = eval(field);
        if (!skipZeroFields || field != 0) { j[name] = result; }
    }

    void visitField(yaml& j, const char* name, bool field) {
        if (!skipFalseFields || field != false) { j[name] = eval(field); }
    }


    template <typename T>
    void visitField(yaml& j, const char* name, T const& field) {
        yaml result = eval(field);
        if (!skipNullFields || !result.IsNull()) { j[name] = result; }
    }

    template <typename T>
    void visit(yaml& res, sem::SemId<T> const& arg) {
        visitDispatch(res, arg.asOrg());
    }

    bool skipNullFields  = false;
    bool skipFalseFields = false;
    bool skipZeroFields  = false;
    bool skipLocation    = false;
    bool skipId          = false;
};

extern template class Exporter<ExporterYaml, yaml>;
} // namespace org::algo
