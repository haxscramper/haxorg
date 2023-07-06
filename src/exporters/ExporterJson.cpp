#include <exporters/ExporterJson.hpp>

#include <boost/mp11.hpp>


template <typename T, typename U>
constexpr bool is_same_decayed_v = std::
    is_same_v<std::decay_t<T>, std::decay_t<U>>;


namespace {
template <typename T>
json export_to_json(CR<T> arg) {
    return json::object();
}

template <typename T>
json export_to_json(CVec<T> arg) {
    return json::array();
}

template <typename T>
json export_to_json(CR<Opt<T>> arg) {
    if (arg) {
        return newRes(*arg);
    } else {
        return json();
    }
}

json export_to_json(sem::SemId arg) {
    if (arg.isNil()) {
        return json();
    } else {
        json res      = json::object();
        res["kind"]   = to_string(arg->getKind());
        json loc      = json::object();
        loc["line"]   = arg->loc ? json(arg->loc->line) : json();
        loc["col"]    = arg->loc ? json(arg->loc->column) : json();
        loc["parent"] = arg->parent.id;
        loc["id"]     = arg->original.id.isNil()
                          ? json()
                          : json(arg->original.id.getValue());
        res["loc"]    = loc;
        res["id"]     = arg.id;
        return res;
    }
}

template <typename T>
json export_to_json(sem::SemIdT<T> arg) {
    return export_to_json(arg.toId());
}

} // namespace

template <typename T>
void ExporterJson::visitField(json& j, const char* name, CR<T> field) {
    j[name] = visit(field);
}

#define _define_static(__Kind)                                            \
    template <>                                                           \
    void ExporterJson::visitField<sem::SemIdT<sem::__Kind>>(              \
        json&, const char*, CR<sem::SemIdT<sem::__Kind>>);

EACH_SEM_ORG_KIND(_define_static)

#undef _define_static


template <typename T>
json ExporterJson::newRes(CR<T> arg) {
    return export_to_json(arg);
}

template <>
json ExporterJson::visit(CR<Str> value) {
    return json(value);
}

template <>
json ExporterJson::visit(CR<QString> value) {
    return json(value);
}

template <>
json ExporterJson::visit(CR<bool> value) {
    return json(value);
}

template <>
json ExporterJson::visit(CR<int> value) {
    return json(value);
}

template <>
json ExporterJson::visit(CR<QDate> value) {
    return json(value.toString(Qt::ISODate).toStdString());
}

template <>
json ExporterJson::visit(CR<QTime> value) {
    return json(value.toString(Qt::ISODate).toStdString());
}

template <>
json ExporterJson::visit(CR<QDateTime> value) {
    return json(value.toString(Qt::ISODate).toStdString());
}


template <typename T>
json ExporterJson::visit(T const& value) {
    if constexpr (std::is_enum<T>::value) {
        return json(to_string(value).toStdString());
    } else {
        json tmp = _this()->newRes(value);
        _this()->visit(tmp, value);
        return tmp;
    }
}

template <typename T>
void ExporterJson::visitField(
    json&       j,
    const char* name,
    CR<Opt<T>>  value) {
    if (value) {
        j[name] = visit(value.value());
    } else {
        j[name] = json();
    }
}

template <typename T>
json ExporterJson::visit(CR<Vec<T>> values) {
    json tmp = json::array();
    for (const auto& it : values) {
        tmp.push_back(visit(it));
    }
    return tmp;
}

template <typename T>
json ExporterJson::visit(CR<UnorderedMap<Str, T>> map) {
    json tmp = json::object();
    for (const auto& [key, val] : map) {
        tmp[key.toStdString()] = visit(val);
    }
    return tmp;
}

void ExporterJson::visitDocument(json& j, In<sem::Document> doc) {
    visitField(j, "subnodes", doc->subnodes);
}

void ExporterJson::visitSubtreeValueFields(
    json&            j,
    In<sem::Subtree> tree) {
    using Md = describe_members<sem::Subtree, mod_any_access>;
    mp_for_each<Md>([&](auto const& field) {
        if (field.name != "subnodes" && field.name != "title") {
            visitField(
                j,
                field.name,
                (*static_cast<sem::Subtree const*>(tree.get()))
                    .*field.pointer);
        }
    });
}


template class Exporter<ExporterJson, json>;

void tmp() { ExporterJson().visitTop(sem::SemId::Nil()); }
