#ifndef EXPORTERYAML_HPP
#define EXPORTERYAML_HPP

#include <exporters/Exporter.hpp>
#include <hstd/stdlib/Yaml.hpp>

struct ExporterYaml : public Exporter<ExporterYaml, yaml> {
    using Base = Exporter<ExporterYaml, yaml>;
#define __ExporterBase Base
    EXPORTER_USING()
#undef __ExporterBase

    template <typename T>
    yaml newRes(CR<Opt<T>> arg) {
        if (arg) {
            return newRes(*arg);
        } else {
            return yaml();
        }
    }


    yaml eval(CR<Str> value) {
        yaml tmp = yaml(value);
        return tmp;
    }

    template <typename T>
    yaml newRes(CR<T>) {
        return yaml();
    }


    yaml eval(CR<bool> value) { return yaml(value); }
    yaml eval(CR<int> value) { return yaml(value); }
    yaml eval(CR<std::string> value) { return yaml(value); }

    template <typename E>
    yaml eval(E value)
        requires(std::is_enum<E>::value)
    {
        return yaml(std::format("{}", value));
    }

    template <typename T>
    yaml eval(CR<T> arg)
        requires(!std::is_enum<T>::value)
    {
        yaml tmp = _this()->newRes(arg);
        _this()->visit(tmp, arg);
        return tmp;
    }

    yaml newRes(sem::SemId<sem::Org> org);

    template <typename T>
    void visitField(yaml& j, const char* name, CR<Opt<T>> value) {
        if (value) {
            j[name] = eval(value.value());
        } else {
            if (!skipNullFields) { j[name] = yaml(); }
        }
    }

    template <typename T>
    yaml eval(CR<Vec<T>> values) {
        yaml tmp;
        for (const auto& it : values) { tmp.push_back(eval(it)); }
        return tmp;
    }

    template <typename T>
    yaml eval(CR<UnorderedMap<Str, T>> map) {
        yaml tmp;
        for (const auto& [key, val] : map) { tmp[key] = eval(val); }
        return tmp;
    }

    void visitField(
        yaml&       y,
        char const* name,
        CR<UnorderedMap<int, sem::SemId<sem::Org>>>) {}

    void visitField(yaml& j, const char* name, int field) {
        yaml result = eval(field);
        if (!skipZeroFields || field != 0) { j[name] = result; }
    }

    void visitField(yaml& j, const char* name, bool field) {
        if (!skipFalseFields || field != false) { j[name] = eval(field); }
    }


    template <typename T>
    void visitField(yaml& j, const char* name, CR<T> field) {
        yaml result = eval(field);
        if (!skipNullFields || !result.IsNull()) { j[name] = result; }
    }

    bool skipNullFields  = false;
    bool skipFalseFields = false;
    bool skipZeroFields  = false;
    bool skipLocation    = false;
    bool skipId          = false;
};

extern template class Exporter<ExporterYaml, yaml>;

#endif // EXPORTERYAML_HPP
