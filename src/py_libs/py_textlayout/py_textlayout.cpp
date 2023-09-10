#include <codegen/py_wrapper.hpp>
#include <codegen/py_converters.hpp>
#include <hstd/wrappers/textlayouter.hpp>
#include <hstd/stdlib/Vec.hpp>

using namespace layout;

struct TextLayout {
    BlockStore        b;
    SimpleStringStore store;
    TextLayout() : store{&b} {}

    BlockId text(QString t) { return store.text(t); }
    BlockId stack(CVec<BlockId> ids) { return b.stack(ids); }
    BlockId line(CVec<BlockId> ids) { return b.line(ids); }
    BlockId choice(CVec<BlockId> ids) { return b.choice(ids); }
    BlockId space(int count) { return b.space(count); }
    BlockId empty() { return b.empty(); }

    BlockId wrap(CVec<BlockId> ids, QString sep) {
        return b.wrap(ids, store.str(sep));
    }


    QString toString(BlockId id, CR<Options> options) {
        return store.toString(id);
    }
};

BOOST_DESCRIBE_STRUCT(
    Options,
    (),
    (leftMargin,
     rightMargin,
     leftMarginCost,
     rightMarginCost,
     linebreakCost,
     indentSpaces,
     cpack));

BOOST_PYTHON_MODULE(TextLayout) {
    using namespace boost::python;

    class_<TextLayout>("TextLayout")
        .def("text", &TextLayout::text)
        .def("line", &TextLayout::line)
        .def("stack", &TextLayout::stack)
        .def("choice", &TextLayout::choice)
        .def("space", &TextLayout::space)
        .def("empty", &TextLayout::empty)
        .def("toString", &TextLayout::toString)
        //
        ;

    class_<layout::Options>("TextOptions")
        .def_readwrite("leftMargin", &Options::leftMargin)
        .def_readwrite("rightMargin", &Options::rightMargin)
        .def_readwrite("leftMarginCost", &Options::leftMarginCost)
        .def_readwrite("rightMarginCost", &Options::rightMarginCost)
        .def_readwrite("linebreakCost", &Options::linebreakCost)
        .def_readwrite("indentSpaces", &Options::indentSpaces)
        .def_readwrite("cpack", &Options::cpack)
        //
        ;
}
