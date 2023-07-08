#include <exporters/ExporterJson.hpp>

#include <boost/mp11.hpp>


json ExporterJson::newRes(sem::SemId org) {
    if (org.isNil()) {
        return json();
    } else {
        json res      = json::object();
        res["kind"]   = to_string(org->getKind());
        json loc      = json::object();
        loc["line"]   = org->loc ? json(org->loc->line) : json();
        loc["col"]    = org->loc ? json(org->loc->column) : json();
        loc["parent"] = org->parent.id;
        loc["id"]     = org->original.id.isNil()
                          ? json()
                          : json(org->original.id.getValue());
        res["loc"]    = loc;
        res["id"]     = org.id;
        return res;
    }
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

template json ExporterJson::visit<sem::SemId>(CR<sem::SemId>);


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
json ExporterJson::visit(CR<UnorderedMap<Str, T>> map) {
    json tmp = json::object();
    for (const auto& [key, val] : map) {
        tmp[key.toStdString()] = visit(val);
    }
    return tmp;
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
json ExporterJson::visit(CR<T> arg) {
    if constexpr (std::is_enum<T>::value) {
        return json(to_string(arg).toStdString());
    } else {
        json tmp = _this()->newRes(arg);
        _this()->visit(tmp, arg);
        return tmp;
    }
}


void tmp() { ExporterJson().visitTop(sem::SemId::Nil()); }
