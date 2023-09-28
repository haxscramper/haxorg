#pragma once
#undef slots
#include <pybind11/pybind11.h>
#include <sem/SemOrg.hpp>
#include <pybind11/stl.h>
#include <hstd/stdlib/Yaml.hpp>
#include <hstd/stdlib/Json.hpp>

#include <sem/SemConvert.hpp>
#include <parse/OrgParser.hpp>
#include <parse/OrgTokenizer.hpp>
#include <parse/OrgTypes.hpp>

namespace py = pybind11;

namespace sem {
struct ExporterJson;
struct ExporterYaml;
}; // namespace sem


struct [[refl]] ExporterJson {
    SPtr<ExporterJson> impl;
    json               result;

    ExporterJson();
    /// Visit top-level node of the exporter, filling in the internal
    /// return state.
    [[refl]] void    visitNode(sem::SemId node /*! Input node */);
    [[refl]] QString exportToString();
    [[refl]] void    exportToFile(QString path);
};

struct [[refl]] ExporterTreeOpts {
    [[refl]] withLineCol     = true;
    [[refl]] withOriginalId  = true;
    [[refl]] withSubnodeIdx  = true;
    [[refl]] skipEmptyFields = true;
    [[refl]] startLevel      = 0;
    [[refl]] withColor       = true;
};

struct [[refl]] ExporterTree {
    SPtr<ExporterJson> impl;
    ExporterTree();
    [[refl]] QString toString(sem::SemId node, ExporterTreeOpts opts);
    [[refl]] void    toFile(
           sem::SemId       node,
           QString          path,
           ExporterTreeOpts opts);

    void stream(
        QTextStream&     stream,
        sem::SemId       node,
        ExporterTreeOpts opts);
}


struct [[refl]] ExporterYaml {
    SPtr<ExporterYaml> impl;
    yaml               result;

    ExporterYaml();
    /// Visit top-level node of the exporter, filling in the internal
    /// return state.
    [[refl]] void    visitNode(sem::SemId node);
    [[refl]] QString exportToString();
    [[refl]] void    exportToFile(QString path);
};

struct [[refl]] OrgContext {
    OrgTokenGroup              tokens;
    SPtr<OrgTokenizer>         tokenizer;
    OrgNodeGroup               nodes;
    SPtr<OrgParser>            parser;
    QString                    source;
    sem::OrgConverter          converter;
    LineColInfo                info;
    Lexer<OrgTokenKind>        lex;
    sem::SemIdT<sem::Document> node = sem::SemIdT<sem::Document>::Nil();
    SPtr<PosStr>               str;
    Func<LineCol(CR<PosStr>)>  locationResolver;
    sem::ContextStore          store;

    OrgContext()
        : tokenizer()
        , nodes(&tokens)
        , lex(&tokens)
        , converter(sem::OrgConverter(&store)) {
        qDebug() << "Init Org context in PY";
    }

    [[refl]] void initLocationResolvers() {
        locationResolver = [&](CR<PosStr> str) -> LineCol {
            Slice<int> absolute = tokens.toAbsolute(str.view);
            return {
                info.whichLine(absolute.first + str.pos) + 1,
                info.whichColumn(absolute.first + str.pos),
                absolute.first + str.pos,
            };
        };

        converter.locationResolver = locationResolver;
        tokenizer->setLocationResolver(locationResolver);
        parser->setLocationResolver(locationResolver);
    }

    [[refl]] void run(std::string file) {
        source      = readFile(QFileInfo(QString::fromStdString(file)));
        tokens.base = source.data();
        info        = LineColInfo{source};
        parser      = OrgParser::initImpl(&nodes, false);
        tokenizer   = OrgTokenizer::initImpl(&tokens, false);
        str         = std::make_shared<PosStr>(source);

        tokenizer->reserve(source.size() / 3);
        parser->reserve(source.size() / 3);


        initLocationResolvers();

        tokenizer->lexGlobal(*str);
        parser->parseFull(lex);
        node = converter.toDocument(OrgAdapter(&nodes, OrgId(0)));
    }

    [[refl]] sem::DefaultSemId<sem::Document> getNode() { return node; }
};

QTextStream qcout;

void init_py_manual_api(py::module& m) {
    // py::class_<OrgContext>(m, "OrgContext")
    //     .def(py::init<>())
    //     .def("run", &OrgContext::run)
    //     .def("getNode", &OrgContext::getNode)
    //     //
    //     ;
}
