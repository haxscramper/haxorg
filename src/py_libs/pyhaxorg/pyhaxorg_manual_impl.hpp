#    undef slots
#    include <pybind11/pybind11.h>
#    include <sem/SemOrg.hpp>
#    include <pybind11/stl.h>

#    include <sem/SemConvert.hpp>
#    include <parse/OrgParser.hpp>
#    include <parse/OrgTokenizer.hpp>
#    include <parse/OrgTypes.hpp>

namespace py = pybind11;

struct OrgContext {
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
        , converter(sem::OrgConverter(&store)) {}
};

void init_py_manual_api(py::module& m) {
    py::class_<OrgContext>(m, "OrgContext")

               //
        ;
}
