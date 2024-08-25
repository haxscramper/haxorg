#include <haxorg/exporters/ExporterJson.hpp>

#include <boost/mp11.hpp>

#include <haxorg/exporters/Exporter.cpp>

template class Exporter<ExporterJson, json>;

json ExporterJson::newRes(sem::SemId<sem::Org> org) {
    if (org.isNil()) {
        return json();
    } else {
        json res    = json::object();
        res["kind"] = fmt1(org->getKind());
        if (!skipLocation) {
            json loc    = json::object();
            loc["line"] = org->loc ? json(org->loc->line) : json();
            loc["col"]  = org->loc ? json(org->loc->column) : json();
            loc["id"]   = org->original.id.isNil()
                            ? json()
                            : json(org->original.id.getValue());
            res["loc"]  = loc;
        }

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


template json ExporterJson::eval<sem::SemId<sem::Org>>(
    CR<sem::SemId<sem::Org>>);


template <typename T>
void ExporterJson::visitField(
    json&       j,
    const char* name,
    CR<Opt<T>>  value) {
    if (value) {
        j[name] = eval(value.value());
    } else if (!skipNullFields) {
        j[name] = json();
    }
}

template <typename T>
json ExporterJson::eval(CR<UnorderedMap<Str, T>> map) {
    json tmp = json::object();
    for (const auto& [key, val] : map) { tmp[key] = eval(val); }
    return tmp;
}

template <typename T>
json ExporterJson::eval(CR<Vec<T>> values) {
    json tmp = json::array();
    for (const auto& it : values) { tmp.push_back(eval(it)); }
    return tmp;
}

template <typename T>
json ExporterJson::eval(CR<T> arg) {
    if constexpr (std::is_enum<T>::value) {
        return json(fmt1(arg));
    } else {
        json tmp = _this()->newRes(arg);
        _this()->visit(tmp, arg);
        return tmp;
    }
}


void tmp() { ExporterJson().evalTop(sem::SemId<sem::Org>::Nil()); }
