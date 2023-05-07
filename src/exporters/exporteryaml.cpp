#include <exporters/exporteryaml.hpp>

using osm = OrgSemKind;

yaml ExporterYaml::newRes(In<sem::Org> org) {
    yaml res;
    res["kind"] = to_string(org->getKind());

    if (IntSet<osm>{
            osm::Word,
            osm::Space,
            osm::Punctuation,
            osm::BigIdent,
            osm::Newline}
            .contains(org->getKind())) {
        res.SetStyle(YAML::EmitterStyle::Flow);
    }


    yaml loc;
    loc.SetStyle(YAML::EmitterStyle::Flow);
    loc["line"] = org->loc ? yaml(org->loc->line) : yaml();
    loc["col"]  = org->loc ? yaml(org->loc->column) : yaml();
    loc["id"]   = org->original.id.isNil()
                    ? yaml()
                    : yaml(org->original.id.getValue());
    res["loc"]  = loc;
    res["id"]   = org->id ? yaml(*(org->id)) : yaml();
    return res;
}
