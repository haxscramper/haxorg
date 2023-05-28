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


    yaml visit(CR<Str> value) {
        yaml tmp = yaml(value.toStdString());
        return tmp;
    }

    yaml newRes(CR<sem::Link::Data>) { return yaml(); }
    yaml newRes(CR<sem::Time::TimeVariant>) { return yaml(); }
    yaml newRes(CR<sem::Time::Repeat>) { return yaml(); }
    yaml newRes(CR<sem::SubtreeLog::LogEntry>) { return yaml(); }
    yaml newRes(CR<sem::Subtree::Property>) { return yaml(); }
    yaml newRes(CR<sem::Subtree::Property::Data>) { return yaml(); }
    yaml newRes(CR<sem::Include::Data>) { return yaml(); }
    yaml newRes(CR<sem::Code::Switch>) { return yaml(); }

    yaml visit(CR<bool> value) { return yaml(value); }
    yaml visit(CR<int> value) { return yaml(value); }
    yaml visit(CR<QString> value) { return yaml(value); }
    yaml visit(CR<QDateTime> value) {
        return yaml(value.toString(Qt::ISODate).toStdString());
    }


    template <typename E>
    yaml visit(E value)
        requires(std::is_enum<E>::value)
    {
        return yaml(to_string(value).toStdString());
    }

    template <typename T>
    yaml visit(CR<T> arg)
        requires(!std::is_enum<T>::value)
    {
        yaml tmp = _this()->newRes(arg);
        _this()->visit(tmp, arg);
        return tmp;
    }

    yaml newRes(In<sem::Org> org);

    template <typename T>
    void visitField(yaml& j, const char* name, CR<Opt<T>> value) {
        if (value) {
            j[name] = visit(value.value());
        } else {
            j[name] = yaml();
        }
    }

    template <typename T>
    yaml visit(CR<Vec<T>> values) {
        yaml tmp;
        for (const auto& it : values) {
            tmp.push_back(visit(it));
        }
        return tmp;
    }

    template <typename T>
    yaml visit(CR<UnorderedMap<Str, T>> map) {
        yaml tmp;
        for (const auto& [key, val] : map) {
            tmp[key.toStdString()] = visit(val);
        }
        return tmp;
    }

    void visitField(
        yaml&       y,
        char const* name,
        CR<UnorderedMap<int, sem::Org::Ptr>>) {}

    template <typename T>
    void visitField(yaml& j, const char* name, CR<T> field) {
        j[name] = visit(field);
    }
};

#endif // EXPORTERYAML_HPP
