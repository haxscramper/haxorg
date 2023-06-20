#include <exporters/Exporter.hpp>

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


    json newRes(CR<sem::Link::Data>) { return json::object(); }
    json newRes(CR<sem::Time::TimeVariant>) { return json::object(); }
    json newRes(CR<sem::Time::Repeat>) { return json::object(); }
    json newRes(CR<sem::SubtreeLog::LogEntry>) { return json::object(); }
    json newRes(CR<sem::Subtree::Property>) { return json::object(); }
    json newRes(CR<sem::Code::Switch>) { return json::object(); }
    json newRes(CR<sem::Include::Data>) { return json::object(); }
    json newRes(CR<sem::Subtree::Property::Data>) {
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
    json visit(CR<QDateTime> value) {
        return json(value.toString(Qt::ISODate).toStdString());
    }


    template <typename E>
    json visit(E value)
        requires(std::is_enum<E>::value)
    {
        return json(to_string(value).toStdString());
    }

    template <typename T>
    json visit(CR<T> arg)
        requires(!std::is_enum<T>::value)
    {
        json tmp = _this()->newRes(arg);
        _this()->visit(tmp, arg);
        return tmp;
    }

    json newRes(sem::SemId org);

    template <typename T>
    void visitField(json& j, const char* name, CR<Opt<T>> value) {
        if (value) {
            j[name] = visit(value.value());
        } else {
            j[name] = json();
        }
    }

    template <typename T>
    json visit(CR<Vec<T>> values) {
        json tmp = json::array();
        for (const auto& it : values) {
            tmp.push_back(visit(it));
        }
        return tmp;
    }

    template <typename T>
    json visit(CR<UnorderedMap<Str, T>> map) {
        json tmp = json::object();
        for (const auto& [key, val] : map) {
            tmp[key.toStdString()] = visit(val);
        }
        return tmp;
    }

    template <typename T>
    void visitField(json& j, const char* name, CR<T> field) {
        j[name] = visit(field);
    }

    void visitDocument(json& j, In<sem::Document> doc) {
        visitField(j, "subnodes", doc->subnodes);
    }
};
