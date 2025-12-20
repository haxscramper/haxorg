#include <haxorg/exporters/exporteryaml.hpp>

#include <haxorg/exporters/Exporter.cpp>
#include <hstd/stdlib/Formatter.hpp>

namespace org::algo {
template class Exporter<ExporterYaml, yaml>;


using osm = OrgSemKind;

yaml ExporterYaml::newRes(sem::SemId<sem::Org> org) {
    yaml res;
    res["kind"] = std::format("{}", org->getKind());

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
        loc["line"] = org->loc ? yaml(org->loc->line) : yaml();
        loc["col"]  = org->loc ? yaml(org->loc->column) : yaml();
        res["loc"]  = loc;
    }


    return res;
}
} // namespace org::algo
