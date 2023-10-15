#include <exporters/exporteryaml.hpp>


#include <exporters/Exporter.cpp>
template class Exporter<ExporterYaml, yaml>;


using osm = OrgSemKind;

yaml ExporterYaml::newRes(sem::SemId org) {
    yaml res;
    res["kind"] = to_string(org->getKind());

    if (IntSet<osm>{
            osm::Word,
            osm::Space,
            osm::Punctuation,
            osm::BigIdent,
            osm::Newline,
        }
            .contains(org->getKind())) {
        res.SetStyle(YAML::EmitterStyle::Flow);
    }

    if (!skipLocation) {
        yaml loc;
        loc.SetStyle(YAML::EmitterStyle::Flow);
        loc["parent"] = org->parent.id;
        loc["line"]   = org->loc ? yaml(org->loc->line) : yaml();
        loc["col"]    = org->loc ? yaml(org->loc->column) : yaml();
        loc["id"]     = org->original.id.isNil()
                          ? yaml()
                          : yaml(org->original.id.getValue());
        res["loc"]    = loc;
    }

    if (!skipId) {
        res["id"] = org.getReadableId();
    }

    return res;
}
