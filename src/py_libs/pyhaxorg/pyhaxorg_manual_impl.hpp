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

#include <py_type_casters.hpp>

namespace py = pybind11;

struct ExporterJson;
struct ExporterYaml;
struct ExporterTree;

struct [[refl]] OrgExporterJson {
    SPtr<ExporterJson> impl;
    json               result;

    OrgExporterJson();
    /// Visit top-level node of the exporter, filling in the internal
    /// return state.
    [[refl]] void    visitNode(sem::SemId node /*! Input node */);
    [[refl]] QString exportToString();
    [[refl]] void    exportToFile(QString path);
};

struct [[refl]] ExporterTreeOpts {
    [[refl]] bool withLineCol     = true;
    [[refl]] bool withOriginalId  = true;
    [[refl]] bool withSubnodeIdx  = true;
    [[refl]] bool skipEmptyFields = true;
    [[refl]] int  startLevel      = 0;
    [[refl]] bool withColor       = true;
};

struct [[refl]] OrgExporterTree {
    SPtr<ExporterTree> impl;
    OrgExporterTree();
    ColStream        os;
    [[refl]] QString toString(sem::SemId node, ExporterTreeOpts opts);
    [[refl]] void    toFile(
           sem::SemId       node,
           QString          path,
           ExporterTreeOpts opts);

    void stream(
        QTextStream&     stream,
        sem::SemId       node,
        ExporterTreeOpts opts);
};


struct [[refl]] OrgExporterYaml {
    SPtr<ExporterYaml> impl;
    yaml               result;

    OrgExporterYaml();
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

    void run();


    [[refl]] void parseFile(std::string file) {
        source = readFile(QFileInfo(QString::fromStdString(file)));
        run();
    }

    [[refl]] void parseString(QString text) {
        source = text;
        run();
    }


    [[refl]] sem::DefaultSemId<sem::Document> getNode() { return node; }
};

inline void init_py_manual_api(py::module& m) {
    // py::class_<OrgContext>(m, "OrgContext")
    //     .def(py::init<>())
    //     .def("run", &OrgContext::run)
    //     .def("getNode", &OrgContext::getNode)
    //     //
    //     ;
}
