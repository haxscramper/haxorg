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


#define __id(I) , sem::DefaultSemId<sem::I>
/// \brief Global variant of all sem node derivations
using OrgDefaultVariant = std::variant<EACH_SEM_ORG_KIND_CSV(__id)>;
#undef __id

template <typename T>
struct TypedPySemId;

struct [[refl]] PySemId {
    sem::SemId id = sem::SemId::Nil();

    PySemId() {}
    PySemId(sem::SemId id) : id(id) {}

    [[refl]] OrgSemKind getKind() const { return id->getKind(); }

    [[refl]] std::vector<PySemId> getSubnodeRange(pybind11::slice slice);

    [[refl]] PySemId getSingleSubnode(int index);

    [[refl]] OrgDefaultVariant castAs() {}

    [[refl]] PySemId operator[](int index) {
        return getSingleSubnode(index);
    }

    [[refl]] std::vector<PySemId> operator[](pybind11::slice slice) {
        return getSubnodeRange(slice);
    }

    template <typename T>
    sem::SemIdT<T> as() const {
        return this->id.as<T>();
    }
};

template <typename T>
struct TypedPySemId : PySemId {
    TypedPySemId() {}
    TypedPySemId(PySemId const& id) : PySemId(id) {}
    TypedPySemId(TypedPySemId<T> const& id) : PySemId(id) {}
    operator TypedPySemId<T>() const { return id; }
};

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
