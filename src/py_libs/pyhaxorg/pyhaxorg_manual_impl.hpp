#undef slots
#include <pybind11/pybind11.h>
#include <sem/SemOrg.hpp>
#include <pybind11/stl.h>

#include <sem/SemConvert.hpp>
#include <parse/OrgParser.hpp>
#include <parse/OrgTokenizer.hpp>
#include <parse/OrgTypes.hpp>

namespace py = pybind11;

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


    void initLocationResolvers() {
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

    void run(std::string file) {
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

    sem::DefaultSemId<sem::Document> getNode() { return node; }
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
