#include <exporters/ExporterJson.hpp>

#include <boost/mp11.hpp>


json ExporterJson::newRes(sem::SemId org) {
    if (org.isNil()) {
        return json();
    } else {
        json res    = json::object();
        res["kind"] = to_string(org->getKind());
        json loc    = json::object();
        loc["line"] = org->loc ? json(org->loc->line) : json();
        loc["col"]  = org->loc ? json(org->loc->column) : json();
        loc["id"]   = org->original.id.isNil()
                        ? json()
                        : json(org->original.id.getValue());
        res["loc"]  = loc;
        res["id"]   = org.id;
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
