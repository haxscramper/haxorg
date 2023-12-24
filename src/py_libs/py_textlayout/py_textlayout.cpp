#include <hstd/wrappers/textlayouter.hpp>
#include <hstd/stdlib/Vec.hpp>
#include <boost/stacktrace.hpp>
#include <hstd/stdlib/Debug.hpp>
#undef slots
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <hstd/stdlib/algorithms.hpp>

#include <py_type_casters.hpp>
#include <absl/log/log.h>

using namespace layout;

void exception_breakpoint() {
    // std::cout << "Stacktrace:\n"
    //           << boost::stacktrace::stacktrace() << std::endl;
    throw; // rethrow the same exception
}


struct TextLayout {
    BlockStore        b;
    SimpleStringStore store;

    struct Id {
        BlockId id = BlockId::Nil();
        Id() {}
        Id(BlockId id) : id(id) {}
        operator BlockId() const { return id; }
    };


    TextLayout() : store{&b} {}
    ~TextLayout() {}

    void dbg() {
        DLOG(INFO) << __LINE__ << b.store.size() << store.strings.size();
    }

    Id text(std::string t) { return store.text(t); }

    Vec<BlockId> tmpVec(std::vector<Id> const& ids) {
        return map(ids, [](Id t) { return t.id; });
    }

    Id stack(std::vector<Id> const& ids) { return b.stack(tmpVec(ids)); }

    Id line(std::vector<Id> const& ids) { return b.line(tmpVec(ids)); }

    Id choice(std::vector<Id> const& ids) { return b.choice(tmpVec(ids)); }
    Id indent(int indent, CR<Id> block) { return b.indent(indent, block); }

    Id space(int count) { return b.space(count); }

    Id empty() { return b.empty(); }

    Id join(
        std::vector<Id> const& items,
        CR<Id>                 join,
        bool                   isLine,
        bool                   isTrailing) {
        return b.join(tmpVec(items), join, isLine, isTrailing);
    }

    Id wrap(std::vector<Id> const& ids, std::string sep) {
        return b.wrap(tmpVec(ids), store.str(sep));
    }

    std::string toString(Id id, CR<Options> options) {
        // try {
            return store.toString(id);
        // } catch (...) { exception_breakpoint(); }
    }

    std::string toTreeRepr(Id id) {
        // try {
            return store.toTreeRepr(id);
        // } catch (...) { exception_breakpoint(); }
    }

    void add_at(Id const& id, Id const& next) { b.add_at(id, next); }

    void add_at(Id const& id, std::vector<Id> const& next) {
        b.add_at(id, tmpVec(next));
    }

    bool isStack(Id id) { return b.at(id).isStack(); }
    bool isLine(Id id) { return b.at(id).isLine(); }

    Id surround_non_empty(Id content, Id before, Id after) {
        return b.surround_non_empty(content, before, after);
    }

    static void py_define(pybind11::module& m) {
        LOG(INFO) << "Py define";
        pybind11::class_<TextLayout>(m, "TextLayout")
            .def(pybind11::init<>())
            .def("dbg", &TextLayout::dbg)
            .def("text", &TextLayout::text)
            .def("line", &TextLayout::line)
            .def("isLine", &TextLayout::isLine)
            .def("isStack", &TextLayout::isStack)
            .def("surround_non_empty", &TextLayout::surround_non_empty)
            .def(
                "stack",
                &TextLayout::stack,
                pybind11::arg("ids") = std::vector<Id>{})
            .def(
                "join",
                &TextLayout::join,
                pybind11::arg("items"),
                pybind11::arg("join"),
                pybind11::arg("isLine")     = true,
                pybind11::arg("isTrailing") = false)
            .def("choice", &TextLayout::choice)
            .def("indent", &TextLayout::indent)
            .def("space", &TextLayout::space)
            .def("empty", &TextLayout::empty)
            .def("toString", &TextLayout::toString)
            .def("toTreeRepr", &TextLayout::toTreeRepr)
            .def(
                "add_at",
                pybind11::overload_cast<Id const&, Id const&>(
                    &TextLayout::add_at))
            .def(
                "add_at_list",
                pybind11::overload_cast<Id const&, std::vector<Id> const&>(
                    &TextLayout::add_at))
            //
            ;
        LOG(INFO) << "Py define done";
    }
};

namespace PYBIND11_NAMESPACE {
namespace detail {
    template <>
    struct type_caster<TextLayout::Id> {
      public:
        PYBIND11_TYPE_CASTER(TextLayout::Id, const_name("BlockId"));
        bool load(handle src, bool) {
            PyObject* source = src.ptr();
            PyObject* tmp    = PyNumber_Long(source);
            if (!tmp) {
                return false;
            }
            value.id.setValue(PyLong_AsUnsignedLong(tmp));
            Py_DECREF(tmp);
            return !PyErr_Occurred();
        }

        static handle cast(
            TextLayout::Id src,
            return_value_policy /* policy */,
            handle /* parent */) {
            return PyLong_FromUnsignedLongLong(src.id.getValue());
        }
    };
} // namespace detail
} // namespace PYBIND11_NAMESPACE


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


PYBIND11_MODULE(py_textlayout, m) {
    using namespace pybind11;
    LOG(INFO) << "Constructing text layout module";

    TextLayout::py_define(m);

    class_<layout::Options>(m, "TextOptions")
        .def(pybind11::init<>())
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
