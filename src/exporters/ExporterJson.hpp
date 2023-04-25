#include <exporters/Exporter.hpp>

struct ExporterJson : public Exporter<ExporterJson, json> {
#define __ExporterBase Exporter<ExporterJson, json>
    EXPORTER_USING()
#undef __ExporterBase

    template <typename T>
    json newRes(CR<T> arg) {
        json tmp    = json::object();
        tmp["kind"] = demangle(typeid(arg).name());
        return tmp;
    }

    json newRes(CR<sem::Time::Static> time) {
        json res          = json::object();
        res["time"]       = time.time.toString(Qt::ISODate);
        res["simpleTime"] = time.simpleTime;
        json repeat;
        if (time.repeat) {
            repeat["count"]  = time.repeat->count;
            repeat["period"] = to_string(time.repeat->period);
            repeat["mode"]   = to_string(time.repeat->mode);
        }
        res["repeat"] = repeat;
        return res;
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

    template <DescribedEnum E>
    json newRes(CR<E> value) {
        return json(to_string(value).toStdString());
    }

    json newRes(CR<Str> value) { return json(value); }
    json newRes(CR<int> value) { return json(value); }

    void eachSub(json& j, In<sem::Org> org) {
        j["subnodes"] = visit(org->subnodes);
    }

    json newRes(In<sem::Org> org) {
        json res    = json::object();
        res["kind"] = to_string(org->getKind());
        json loc    = json::object();
        loc["line"] = org->loc ? json(org->loc->line) : json();
        loc["col"]  = org->loc ? json(org->loc->column) : json();
        loc["id"]   = org->original.id.isNil()
                        ? json()
                        : json(org->original.id.getValue());
        res["loc"]  = loc;
        return res;
    }

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

    void visitDocument(json& j, In<sem::Document> doc) { eachSub(j, doc); }
};
