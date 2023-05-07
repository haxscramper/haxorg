#include <exporters/ExporterJson.hpp>

json ExporterJson::newRes(In<sem::Org> org) {
    json res    = json::object();
    res["kind"] = to_string(org->getKind());
    json loc    = json::object();
    loc["line"] = org->loc ? json(org->loc->line) : json();
    loc["col"]  = org->loc ? json(org->loc->column) : json();
    loc["id"]   = org->original.id.isNil()
                    ? json()
                    : json(org->original.id.getValue());
    res["loc"]  = loc;
    res["id"]   = org->id ? json(*(org->id)) : json();
    return res;
}
