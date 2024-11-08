/* clang-format off */
#undef slots
#define PYBIND11_DETAILED_ERROR_MESSAGES
#include <pybind11/pybind11.h>
#include <haxorg/sem/SemOrg.hpp>
#include <pybind11/stl.h>
#include "pyhaxorg_manual_impl.hpp"
PYBIND11_MAKE_OPAQUE(std::vector<sem::SemId<sem::Org>>)
PYBIND11_MAKE_OPAQUE(Vec<sem::SemId<sem::Org>>)
PYBIND11_MAKE_OPAQUE(std::vector<sem::Tblfm::Expr>)
PYBIND11_MAKE_OPAQUE(Vec<sem::Tblfm::Expr>)
PYBIND11_MAKE_OPAQUE(std::vector<sem::Tblfm::Expr::Assign::Flag>)
PYBIND11_MAKE_OPAQUE(Vec<sem::Tblfm::Expr::Assign::Flag>)
PYBIND11_MAKE_OPAQUE(std::vector<Str>)
PYBIND11_MAKE_OPAQUE(Vec<Str>)
PYBIND11_MAKE_OPAQUE(std::vector<sem::BlockCodeLine::Part>)
PYBIND11_MAKE_OPAQUE(Vec<sem::BlockCodeLine::Part>)
PYBIND11_MAKE_OPAQUE(std::vector<int>)
PYBIND11_MAKE_OPAQUE(Vec<int>)
PYBIND11_MAKE_OPAQUE(std::unordered_map<Str, Str>)
PYBIND11_MAKE_OPAQUE(UnorderedMap<Str, Str>)
PYBIND11_MAKE_OPAQUE(std::vector<sem::AttrValue>)
PYBIND11_MAKE_OPAQUE(Vec<sem::AttrValue>)
PYBIND11_MAKE_OPAQUE(std::vector<sem::SemId<sem::Attr>>)
PYBIND11_MAKE_OPAQUE(Vec<sem::SemId<sem::Attr>>)
PYBIND11_MAKE_OPAQUE(std::unordered_map<Str, sem::SemId<sem::AttrList>>)
PYBIND11_MAKE_OPAQUE(UnorderedMap<Str, sem::SemId<sem::AttrList>>)
PYBIND11_MAKE_OPAQUE(std::vector<sem::SemId<sem::ErrorItem>>)
PYBIND11_MAKE_OPAQUE(Vec<sem::SemId<sem::ErrorItem>>)
PYBIND11_MAKE_OPAQUE(std::vector<sem::SemId<sem::HashTag>>)
PYBIND11_MAKE_OPAQUE(Vec<sem::SemId<sem::HashTag>>)
PYBIND11_MAKE_OPAQUE(std::vector<Vec<Str>>)
PYBIND11_MAKE_OPAQUE(Vec<Vec<Str>>)
PYBIND11_MAKE_OPAQUE(std::vector<sem::Symbol::Param>)
PYBIND11_MAKE_OPAQUE(Vec<sem::Symbol::Param>)
PYBIND11_MAKE_OPAQUE(std::vector<sem::BlockCodeSwitch>)
PYBIND11_MAKE_OPAQUE(Vec<sem::BlockCodeSwitch>)
PYBIND11_MAKE_OPAQUE(std::vector<sem::BlockCodeLine>)
PYBIND11_MAKE_OPAQUE(Vec<sem::BlockCodeLine>)
PYBIND11_MAKE_OPAQUE(std::vector<sem::SemId<sem::SubtreeLog>>)
PYBIND11_MAKE_OPAQUE(Vec<sem::SemId<sem::SubtreeLog>>)
PYBIND11_MAKE_OPAQUE(std::vector<sem::NamedProperty>)
PYBIND11_MAKE_OPAQUE(Vec<sem::NamedProperty>)
PYBIND11_MAKE_OPAQUE(std::vector<sem::SubtreePeriod>)
PYBIND11_MAKE_OPAQUE(Vec<sem::SubtreePeriod>)
PYBIND11_MAKE_OPAQUE(IntSet<sem::SubtreePeriod::Kind>)
PYBIND11_MAKE_OPAQUE(std::vector<sem::SemId<sem::Cell>>)
PYBIND11_MAKE_OPAQUE(Vec<sem::SemId<sem::Cell>>)
PYBIND11_MAKE_OPAQUE(std::vector<sem::SemId<sem::Row>>)
PYBIND11_MAKE_OPAQUE(Vec<sem::SemId<sem::Row>>)
PYBIND11_MAKE_OPAQUE(std::vector<sem::SemId<sem::BigIdent>>)
PYBIND11_MAKE_OPAQUE(Vec<sem::SemId<sem::BigIdent>>)
PYBIND11_MAKE_OPAQUE(std::vector<UserTime>)
PYBIND11_MAKE_OPAQUE(Vec<UserTime>)
PYBIND11_MAKE_OPAQUE(std::vector<sem::SemId<sem::Time>>)
PYBIND11_MAKE_OPAQUE(Vec<sem::SemId<sem::Time>>)
PYBIND11_MAKE_OPAQUE(std::vector<SequenceSegment>)
PYBIND11_MAKE_OPAQUE(Vec<SequenceSegment>)
PYBIND11_MAKE_OPAQUE(std::vector<SequenceAnnotationTag>)
PYBIND11_MAKE_OPAQUE(Vec<SequenceAnnotationTag>)
PYBIND11_MAKE_OPAQUE(std::vector<SequenceAnnotation>)
PYBIND11_MAKE_OPAQUE(Vec<SequenceAnnotation>)
PYBIND11_MAKE_OPAQUE(std::vector<SequenceSegmentGroup>)
PYBIND11_MAKE_OPAQUE(Vec<SequenceSegmentGroup>)
PYBIND11_MODULE(pyhaxorg, m) {
  PyTypeRegistryGuard type_registry_guard{};
  bind_vector<sem::SemId<sem::Org>>(m, "VecOfSemIdOfOrg", type_registry_guard);
  bind_vector<sem::Tblfm::Expr>(m, "VecOfTblfmExpr", type_registry_guard);
  bind_vector<sem::Tblfm::Expr::Assign::Flag>(m, "VecOfTblfmExprAssignFlag", type_registry_guard);
  bind_vector<Str>(m, "VecOfStr", type_registry_guard);
  bind_vector<sem::BlockCodeLine::Part>(m, "VecOfBlockCodeLinePart", type_registry_guard);
  bind_vector<int>(m, "VecOfint", type_registry_guard);
  bind_unordered_map<Str, Str>(m, "UnorderedMapOfStrStr", type_registry_guard);
  bind_vector<sem::AttrValue>(m, "VecOfAttrValue", type_registry_guard);
  bind_vector<sem::SemId<sem::Attr>>(m, "VecOfSemIdOfAttr", type_registry_guard);
  bind_unordered_map<Str, sem::SemId<sem::AttrList>>(m, "UnorderedMapOfStrSemIdOfAttrList", type_registry_guard);
  bind_vector<sem::SemId<sem::ErrorItem>>(m, "VecOfSemIdOfErrorItem", type_registry_guard);
  bind_vector<sem::SemId<sem::HashTag>>(m, "VecOfSemIdOfHashTag", type_registry_guard);
  bind_vector<Vec<Str>>(m, "VecOfVecOfStr", type_registry_guard);
  bind_vector<sem::Symbol::Param>(m, "VecOfSymbolParam", type_registry_guard);
  bind_vector<sem::BlockCodeSwitch>(m, "VecOfBlockCodeSwitch", type_registry_guard);
  bind_vector<sem::BlockCodeLine>(m, "VecOfBlockCodeLine", type_registry_guard);
  bind_vector<sem::SemId<sem::SubtreeLog>>(m, "VecOfSemIdOfSubtreeLog", type_registry_guard);
  bind_vector<sem::NamedProperty>(m, "VecOfNamedProperty", type_registry_guard);
  bind_vector<sem::SubtreePeriod>(m, "VecOfSubtreePeriod", type_registry_guard);
  bind_int_set<sem::SubtreePeriod::Kind>(m, "IntSetOfSubtreePeriodKind", type_registry_guard);
  bind_vector<sem::SemId<sem::Cell>>(m, "VecOfSemIdOfCell", type_registry_guard);
  bind_vector<sem::SemId<sem::Row>>(m, "VecOfSemIdOfRow", type_registry_guard);
  bind_vector<sem::SemId<sem::BigIdent>>(m, "VecOfSemIdOfBigIdent", type_registry_guard);
  bind_vector<UserTime>(m, "VecOfUserTime", type_registry_guard);
  bind_vector<sem::SemId<sem::Time>>(m, "VecOfSemIdOfTime", type_registry_guard);
  bind_vector<SequenceSegment>(m, "VecOfSequenceSegment", type_registry_guard);
  bind_vector<SequenceAnnotationTag>(m, "VecOfSequenceAnnotationTag", type_registry_guard);
  bind_vector<SequenceAnnotation>(m, "VecOfSequenceAnnotation", type_registry_guard);
  bind_vector<SequenceSegmentGroup>(m, "VecOfSequenceSegmentGroup", type_registry_guard);
  pybind11::class_<sem::Org, sem::SemId<sem::Org>>(m, "Org")
    .def_readwrite("loc", &sem::Org::loc, R"RAW(\brief Location of the node in the original source file)RAW")
    .def_readwrite("documentId", &sem::Org::documentId, R"RAW(\brief Application specific ID of the original document)RAW")
    .def_readwrite("subnodes", &sem::Org::subnodes, R"RAW(\brief List of subnodes.

Some of the derived nodes don't make the use of subnode list
(word, punctuation etc), but it was left on the top level of the
hierarchy for conveinience purposes. It is not expected that 'any'
node can have subnodes.)RAW")
    .def("getKind", static_cast<OrgSemKind(sem::Org::*)() const>(&sem::Org::getKind), R"RAW(\brief Get kind of this sem node)RAW")
    .def("isGenerated", static_cast<bool(sem::Org::*)() const>(&sem::Org::isGenerated), R"RAW(\brief Whether original node adapter is missing)RAW")
    .def("push_back",
         static_cast<void(sem::Org::*)(sem::SemId<sem::Org>)>(&sem::Org::push_back),
         pybind11::arg("sub"))
    .def("insert",
         static_cast<void(sem::Org::*)(int, sem::SemId<sem::Org>)>(&sem::Org::insert),
         pybind11::arg("pos"),
         pybind11::arg("node"))
    .def("at",
         static_cast<sem::SemId<sem::Org>(sem::Org::*)(int) const>(&sem::Org::at),
         pybind11::arg("idx"),
         R"RAW(\brief Get subnode at specified index)RAW")
    .def("is_",
         static_cast<bool(sem::Org::*)(OrgSemKind) const>(&sem::Org::is),
         pybind11::arg("kind"))
    .def("__getitem__",
         static_cast<sem::SemId<sem::Org>(sem::Org::*)(int) const>(&sem::Org::at),
         pybind11::arg("idx"))
    .def("__iter__",
         [](sem::Org const& node) -> auto {
         return pybind11::make_iterator(node.subnodes.begin(), node.subnodes.end());
         },
         pybind11::keep_alive<0, 1>())
    ;
  pybind11::class_<LineCol>(m, "LineCol")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> LineCol {
                        LineCol result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("line", &LineCol::line)
    .def_readwrite("column", &LineCol::column)
    .def_readwrite("pos", &LineCol::pos)
    .def("__repr__", [](LineCol _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](LineCol _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::Tblfm::Expr::AxisRef>(m, "TblfmExprAxisRef")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::Tblfm::Expr::AxisRef {
                        sem::Tblfm::Expr::AxisRef result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("colIndex", &sem::Tblfm::Expr::AxisRef::colIndex)
    .def_readwrite("rowIndex", &sem::Tblfm::Expr::AxisRef::rowIndex)
    .def_readwrite("colFromTop", &sem::Tblfm::Expr::AxisRef::colFromTop)
    .def_readwrite("rowFromTop", &sem::Tblfm::Expr::AxisRef::rowFromTop)
    .def("operator==",
         static_cast<bool(sem::Tblfm::Expr::AxisRef::*)(sem::Tblfm::Expr::AxisRef const&) const>(&sem::Tblfm::Expr::AxisRef::operator==),
         pybind11::arg("other"))
    .def("__repr__", [](sem::Tblfm::Expr::AxisRef _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::Tblfm::Expr::AxisRef _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::Tblfm::Expr::RangeRef>(m, "TblfmExprRangeRef")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::Tblfm::Expr::RangeRef {
                        sem::Tblfm::Expr::RangeRef result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("first", &sem::Tblfm::Expr::RangeRef::first)
    .def_readwrite("last", &sem::Tblfm::Expr::RangeRef::last)
    .def("operator==",
         static_cast<bool(sem::Tblfm::Expr::RangeRef::*)(sem::Tblfm::Expr::RangeRef const&) const>(&sem::Tblfm::Expr::RangeRef::operator==),
         pybind11::arg("other"))
    .def("__repr__", [](sem::Tblfm::Expr::RangeRef _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::Tblfm::Expr::RangeRef _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::Tblfm::Expr::Call>(m, "TblfmExprCall")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::Tblfm::Expr::Call {
                        sem::Tblfm::Expr::Call result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("name", &sem::Tblfm::Expr::Call::name)
    .def_readwrite("args", &sem::Tblfm::Expr::Call::args)
    .def("operator==",
         static_cast<bool(sem::Tblfm::Expr::Call::*)(sem::Tblfm::Expr::Call const&) const>(&sem::Tblfm::Expr::Call::operator==),
         pybind11::arg("other"))
    .def("__repr__", [](sem::Tblfm::Expr::Call _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::Tblfm::Expr::Call _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::Tblfm::Expr::Elisp>(m, "TblfmExprElisp")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::Tblfm::Expr::Elisp {
                        sem::Tblfm::Expr::Elisp result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("value", &sem::Tblfm::Expr::Elisp::value)
    .def("operator==",
         static_cast<bool(sem::Tblfm::Expr::Elisp::*)(sem::Tblfm::Expr::Elisp const&) const>(&sem::Tblfm::Expr::Elisp::operator==),
         pybind11::arg("other"))
    .def("__repr__", [](sem::Tblfm::Expr::Elisp _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::Tblfm::Expr::Elisp _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  bind_enum_iterator<sem::Tblfm::Expr::Assign::Flag>(m, "TblfmExprAssignFlag", type_registry_guard);
  pybind11::enum_<sem::Tblfm::Expr::Assign::Flag>(m, "TblfmExprAssignFlag")
    .value("CellLeftAlign", sem::Tblfm::Expr::Assign::Flag::CellLeftAlign, R"RAW(Left-align the result)RAW")
    .value("CellRightAlign", sem::Tblfm::Expr::Assign::Flag::CellRightAlign, R"RAW(Right-align the result)RAW")
    .value("CellCenterAlign", sem::Tblfm::Expr::Assign::Flag::CellCenterAlign, R"RAW(Center-align the result)RAW")
    .value("CellNumber", sem::Tblfm::Expr::Assign::Flag::CellNumber, R"RAW(Convert result to number/currency format)RAW")
    .value("CellExponential", sem::Tblfm::Expr::Assign::Flag::CellExponential, R"RAW(Use exponential notation for numbers)RAW")
    .value("CellFloating", sem::Tblfm::Expr::Assign::Flag::CellFloating, R"RAW(Use floating point format)RAW")
    .value("CellUnformat", sem::Tblfm::Expr::Assign::Flag::CellUnformat, R"RAW(Unformat values before calculating)RAW")
    .value("CellText", sem::Tblfm::Expr::Assign::Flag::CellText, R"RAW(Convert result to text)RAW")
    .value("CellBool", sem::Tblfm::Expr::Assign::Flag::CellBool, R"RAW(Display boolean values as t/nil)RAW")
    .value("CellDecimal", sem::Tblfm::Expr::Assign::Flag::CellDecimal, R"RAW(Fixed format with specified decimal places (e.g., ;D2))RAW")
    .value("CellPercentage", sem::Tblfm::Expr::Assign::Flag::CellPercentage, R"RAW(Percentage format)RAW")
    .value("CellHours", sem::Tblfm::Expr::Assign::Flag::CellHours, R"RAW(Convert to hours/minutes (HH:MM))RAW")
    .value("CellZero", sem::Tblfm::Expr::Assign::Flag::CellZero, R"RAW(Display zero as empty cell)RAW")
    .value("CellMarkInvalid", sem::Tblfm::Expr::Assign::Flag::CellMarkInvalid, R"RAW(Mark field as invalid if conversion fails)RAW")
    .value("CellQuote", sem::Tblfm::Expr::Assign::Flag::CellQuote, R"RAW(Quote field contents)RAW")
    .def("__iter__", [](sem::Tblfm::Expr::Assign::Flag _self) -> PyEnumIterator<sem::Tblfm::Expr::Assign::Flag> {
                     return
                     PyEnumIterator<sem::Tblfm::Expr::Assign::Flag>
                     ();
                     })
    ;
  pybind11::class_<sem::Tblfm::Expr::Assign>(m, "TblfmExprAssign")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::Tblfm::Expr::Assign {
                        sem::Tblfm::Expr::Assign result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("target", &sem::Tblfm::Expr::Assign::target)
    .def_readwrite("expr", &sem::Tblfm::Expr::Assign::expr)
    .def_readwrite("flags", &sem::Tblfm::Expr::Assign::flags)
    .def("operator==",
         static_cast<bool(sem::Tblfm::Expr::Assign::*)(sem::Tblfm::Expr::Assign const&) const>(&sem::Tblfm::Expr::Assign::operator==),
         pybind11::arg("other"))
    .def("__repr__", [](sem::Tblfm::Expr::Assign _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::Tblfm::Expr::Assign _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  bind_enum_iterator<sem::Tblfm::Expr::Kind>(m, "TblfmExprKind", type_registry_guard);
  pybind11::enum_<sem::Tblfm::Expr::Kind>(m, "TblfmExprKind")
    .value("AxisRef", sem::Tblfm::Expr::Kind::AxisRef)
    .value("RangeRef", sem::Tblfm::Expr::Kind::RangeRef)
    .value("Call", sem::Tblfm::Expr::Kind::Call)
    .value("Elisp", sem::Tblfm::Expr::Kind::Elisp)
    .value("Assign", sem::Tblfm::Expr::Kind::Assign)
    .def("__iter__", [](sem::Tblfm::Expr::Kind _self) -> PyEnumIterator<sem::Tblfm::Expr::Kind> {
                     return
                     PyEnumIterator<sem::Tblfm::Expr::Kind>
                     ();
                     })
    ;
  pybind11::class_<sem::Tblfm::Expr>(m, "TblfmExpr")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::Tblfm::Expr {
                        sem::Tblfm::Expr result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("data", &sem::Tblfm::Expr::data)
    .def("operator==",
         static_cast<bool(sem::Tblfm::Expr::*)(sem::Tblfm::Expr const&) const>(&sem::Tblfm::Expr::operator==),
         pybind11::arg("other"))
    .def("isAxisRef", static_cast<bool(sem::Tblfm::Expr::*)() const>(&sem::Tblfm::Expr::isAxisRef))
    .def("getAxisRef", static_cast<sem::Tblfm::Expr::AxisRef&(sem::Tblfm::Expr::*)()>(&sem::Tblfm::Expr::getAxisRef))
    .def("isRangeRef", static_cast<bool(sem::Tblfm::Expr::*)() const>(&sem::Tblfm::Expr::isRangeRef))
    .def("getRangeRef", static_cast<sem::Tblfm::Expr::RangeRef&(sem::Tblfm::Expr::*)()>(&sem::Tblfm::Expr::getRangeRef))
    .def("isCall", static_cast<bool(sem::Tblfm::Expr::*)() const>(&sem::Tblfm::Expr::isCall))
    .def("getCall", static_cast<sem::Tblfm::Expr::Call&(sem::Tblfm::Expr::*)()>(&sem::Tblfm::Expr::getCall))
    .def("isElisp", static_cast<bool(sem::Tblfm::Expr::*)() const>(&sem::Tblfm::Expr::isElisp))
    .def("getElisp", static_cast<sem::Tblfm::Expr::Elisp&(sem::Tblfm::Expr::*)()>(&sem::Tblfm::Expr::getElisp))
    .def("isAssign", static_cast<bool(sem::Tblfm::Expr::*)() const>(&sem::Tblfm::Expr::isAssign))
    .def("getAssign", static_cast<sem::Tblfm::Expr::Assign&(sem::Tblfm::Expr::*)()>(&sem::Tblfm::Expr::getAssign))
    .def_static("getKindStatic",
                static_cast<sem::Tblfm::Expr::Kind(*)(sem::Tblfm::Expr::Data const&)>(&sem::Tblfm::Expr::getKind),
                pybind11::arg("__input"))
    .def("getKind", static_cast<sem::Tblfm::Expr::Kind(sem::Tblfm::Expr::*)() const>(&sem::Tblfm::Expr::getKind))
    .def("__repr__", [](sem::Tblfm::Expr _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::Tblfm::Expr _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::Tblfm>(m, "Tblfm")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::Tblfm {
                        sem::Tblfm result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("exprs", &sem::Tblfm::exprs)
    .def("operator==",
         static_cast<bool(sem::Tblfm::*)(sem::Tblfm const&) const>(&sem::Tblfm::operator==),
         pybind11::arg("other"))
    .def("__repr__", [](sem::Tblfm _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::Tblfm _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::AttrValue>(m, "AttrValue")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::AttrValue {
                        sem::AttrValue result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("name", &sem::AttrValue::name)
    .def_readwrite("varname", &sem::AttrValue::varname)
    .def_readwrite("value", &sem::AttrValue::value)
    .def("getBool", static_cast<Opt<bool>(sem::AttrValue::*)() const>(&sem::AttrValue::getBool))
    .def("getInt", static_cast<Opt<int>(sem::AttrValue::*)() const>(&sem::AttrValue::getInt))
    .def("getString", static_cast<Str(sem::AttrValue::*)() const>(&sem::AttrValue::getString))
    .def("operator==",
         static_cast<bool(sem::AttrValue::*)(sem::AttrValue const&) const>(&sem::AttrValue::operator==),
         pybind11::arg("other"))
    .def("__repr__", [](sem::AttrValue _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::AttrValue _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::SubtreePath>(m, "SubtreePath")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::SubtreePath {
                        sem::SubtreePath result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("path", &sem::SubtreePath::path)
    .def("operator==",
         static_cast<bool(sem::SubtreePath::*)(sem::SubtreePath const&) const>(&sem::SubtreePath::operator==),
         pybind11::arg("other"))
    .def("__repr__", [](sem::SubtreePath _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::SubtreePath _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::BlockCodeLine::Part::Raw>(m, "BlockCodeLinePartRaw")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::BlockCodeLine::Part::Raw {
                        sem::BlockCodeLine::Part::Raw result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("code", &sem::BlockCodeLine::Part::Raw::code)
    .def("operator==",
         static_cast<bool(sem::BlockCodeLine::Part::Raw::*)(sem::BlockCodeLine::Part::Raw const&) const>(&sem::BlockCodeLine::Part::Raw::operator==),
         pybind11::arg("other"))
    .def("__repr__", [](sem::BlockCodeLine::Part::Raw _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::BlockCodeLine::Part::Raw _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::BlockCodeLine::Part::Callout>(m, "BlockCodeLinePartCallout")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::BlockCodeLine::Part::Callout {
                        sem::BlockCodeLine::Part::Callout result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("name", &sem::BlockCodeLine::Part::Callout::name)
    .def("operator==",
         static_cast<bool(sem::BlockCodeLine::Part::Callout::*)(sem::BlockCodeLine::Part::Callout const&) const>(&sem::BlockCodeLine::Part::Callout::operator==),
         pybind11::arg("other"))
    .def("__repr__", [](sem::BlockCodeLine::Part::Callout _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::BlockCodeLine::Part::Callout _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::BlockCodeLine::Part::Tangle>(m, "BlockCodeLinePartTangle")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::BlockCodeLine::Part::Tangle {
                        sem::BlockCodeLine::Part::Tangle result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("target", &sem::BlockCodeLine::Part::Tangle::target)
    .def("operator==",
         static_cast<bool(sem::BlockCodeLine::Part::Tangle::*)(sem::BlockCodeLine::Part::Tangle const&) const>(&sem::BlockCodeLine::Part::Tangle::operator==),
         pybind11::arg("other"))
    .def("__repr__", [](sem::BlockCodeLine::Part::Tangle _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::BlockCodeLine::Part::Tangle _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  bind_enum_iterator<sem::BlockCodeLine::Part::Kind>(m, "BlockCodeLinePartKind", type_registry_guard);
  pybind11::enum_<sem::BlockCodeLine::Part::Kind>(m, "BlockCodeLinePartKind")
    .value("Raw", sem::BlockCodeLine::Part::Kind::Raw)
    .value("Callout", sem::BlockCodeLine::Part::Kind::Callout)
    .value("Tangle", sem::BlockCodeLine::Part::Kind::Tangle)
    .def("__iter__", [](sem::BlockCodeLine::Part::Kind _self) -> PyEnumIterator<sem::BlockCodeLine::Part::Kind> {
                     return
                     PyEnumIterator<sem::BlockCodeLine::Part::Kind>
                     ();
                     })
    ;
  pybind11::class_<sem::BlockCodeLine::Part>(m, "BlockCodeLinePart")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::BlockCodeLine::Part {
                        sem::BlockCodeLine::Part result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("data", &sem::BlockCodeLine::Part::data)
    .def("operator==",
         static_cast<bool(sem::BlockCodeLine::Part::*)(sem::BlockCodeLine::Part const&) const>(&sem::BlockCodeLine::Part::operator==),
         pybind11::arg("other"))
    .def("isRaw", static_cast<bool(sem::BlockCodeLine::Part::*)() const>(&sem::BlockCodeLine::Part::isRaw))
    .def("getRaw", static_cast<sem::BlockCodeLine::Part::Raw&(sem::BlockCodeLine::Part::*)()>(&sem::BlockCodeLine::Part::getRaw))
    .def("isCallout", static_cast<bool(sem::BlockCodeLine::Part::*)() const>(&sem::BlockCodeLine::Part::isCallout))
    .def("getCallout", static_cast<sem::BlockCodeLine::Part::Callout&(sem::BlockCodeLine::Part::*)()>(&sem::BlockCodeLine::Part::getCallout))
    .def("isTangle", static_cast<bool(sem::BlockCodeLine::Part::*)() const>(&sem::BlockCodeLine::Part::isTangle))
    .def("getTangle", static_cast<sem::BlockCodeLine::Part::Tangle&(sem::BlockCodeLine::Part::*)()>(&sem::BlockCodeLine::Part::getTangle))
    .def_static("getKindStatic",
                static_cast<sem::BlockCodeLine::Part::Kind(*)(sem::BlockCodeLine::Part::Data const&)>(&sem::BlockCodeLine::Part::getKind),
                pybind11::arg("__input"))
    .def("getKind", static_cast<sem::BlockCodeLine::Part::Kind(sem::BlockCodeLine::Part::*)() const>(&sem::BlockCodeLine::Part::getKind))
    .def("__repr__", [](sem::BlockCodeLine::Part _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::BlockCodeLine::Part _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::BlockCodeLine>(m, "BlockCodeLine")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::BlockCodeLine {
                        sem::BlockCodeLine result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("parts", &sem::BlockCodeLine::parts, R"RAW(parts of the single line)RAW")
    .def("operator==",
         static_cast<bool(sem::BlockCodeLine::*)(sem::BlockCodeLine const&) const>(&sem::BlockCodeLine::operator==),
         pybind11::arg("other"))
    .def("__repr__", [](sem::BlockCodeLine _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::BlockCodeLine _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::BlockCodeSwitch::LineStart>(m, "BlockCodeSwitchLineStart")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::BlockCodeSwitch::LineStart {
                        sem::BlockCodeSwitch::LineStart result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("start", &sem::BlockCodeSwitch::LineStart::start, R"RAW(First line number)RAW")
    .def_readwrite("extendLast", &sem::BlockCodeSwitch::LineStart::extendLast, R"RAW(Continue numbering from the previous block nstead of starting anew)RAW")
    .def("operator==",
         static_cast<bool(sem::BlockCodeSwitch::LineStart::*)(sem::BlockCodeSwitch::LineStart const&) const>(&sem::BlockCodeSwitch::LineStart::operator==),
         pybind11::arg("other"))
    .def("__repr__", [](sem::BlockCodeSwitch::LineStart _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::BlockCodeSwitch::LineStart _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::BlockCodeSwitch::CalloutFormat>(m, "BlockCodeSwitchCalloutFormat")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::BlockCodeSwitch::CalloutFormat {
                        sem::BlockCodeSwitch::CalloutFormat result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("format", &sem::BlockCodeSwitch::CalloutFormat::format)
    .def("operator==",
         static_cast<bool(sem::BlockCodeSwitch::CalloutFormat::*)(sem::BlockCodeSwitch::CalloutFormat const&) const>(&sem::BlockCodeSwitch::CalloutFormat::operator==),
         pybind11::arg("other"))
    .def("__repr__", [](sem::BlockCodeSwitch::CalloutFormat _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::BlockCodeSwitch::CalloutFormat _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::BlockCodeSwitch::RemoveCallout>(m, "BlockCodeSwitchRemoveCallout")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::BlockCodeSwitch::RemoveCallout {
                        sem::BlockCodeSwitch::RemoveCallout result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("remove", &sem::BlockCodeSwitch::RemoveCallout::remove)
    .def("operator==",
         static_cast<bool(sem::BlockCodeSwitch::RemoveCallout::*)(sem::BlockCodeSwitch::RemoveCallout const&) const>(&sem::BlockCodeSwitch::RemoveCallout::operator==),
         pybind11::arg("other"))
    .def("__repr__", [](sem::BlockCodeSwitch::RemoveCallout _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::BlockCodeSwitch::RemoveCallout _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::BlockCodeSwitch::EmphasizeLine>(m, "BlockCodeSwitchEmphasizeLine")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::BlockCodeSwitch::EmphasizeLine {
                        sem::BlockCodeSwitch::EmphasizeLine result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("line", &sem::BlockCodeSwitch::EmphasizeLine::line)
    .def("operator==",
         static_cast<bool(sem::BlockCodeSwitch::EmphasizeLine::*)(sem::BlockCodeSwitch::EmphasizeLine const&) const>(&sem::BlockCodeSwitch::EmphasizeLine::operator==),
         pybind11::arg("other"))
    .def("__repr__", [](sem::BlockCodeSwitch::EmphasizeLine _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::BlockCodeSwitch::EmphasizeLine _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::BlockCodeSwitch::Dedent>(m, "BlockCodeSwitchDedent")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::BlockCodeSwitch::Dedent {
                        sem::BlockCodeSwitch::Dedent result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("value", &sem::BlockCodeSwitch::Dedent::value)
    .def("operator==",
         static_cast<bool(sem::BlockCodeSwitch::Dedent::*)(sem::BlockCodeSwitch::Dedent const&) const>(&sem::BlockCodeSwitch::Dedent::operator==),
         pybind11::arg("other"))
    .def("__repr__", [](sem::BlockCodeSwitch::Dedent _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::BlockCodeSwitch::Dedent _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  bind_enum_iterator<sem::BlockCodeSwitch::Kind>(m, "BlockCodeSwitchKind", type_registry_guard);
  pybind11::enum_<sem::BlockCodeSwitch::Kind>(m, "BlockCodeSwitchKind")
    .value("LineStart", sem::BlockCodeSwitch::Kind::LineStart)
    .value("CalloutFormat", sem::BlockCodeSwitch::Kind::CalloutFormat)
    .value("RemoveCallout", sem::BlockCodeSwitch::Kind::RemoveCallout)
    .value("EmphasizeLine", sem::BlockCodeSwitch::Kind::EmphasizeLine)
    .value("Dedent", sem::BlockCodeSwitch::Kind::Dedent)
    .def("__iter__", [](sem::BlockCodeSwitch::Kind _self) -> PyEnumIterator<sem::BlockCodeSwitch::Kind> {
                     return
                     PyEnumIterator<sem::BlockCodeSwitch::Kind>
                     ();
                     })
    ;
  pybind11::class_<sem::BlockCodeSwitch>(m, "BlockCodeSwitch")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::BlockCodeSwitch {
                        sem::BlockCodeSwitch result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("data", &sem::BlockCodeSwitch::data)
    .def("operator==",
         static_cast<bool(sem::BlockCodeSwitch::*)(sem::BlockCodeSwitch const&) const>(&sem::BlockCodeSwitch::operator==),
         pybind11::arg("other"))
    .def("isLineStart", static_cast<bool(sem::BlockCodeSwitch::*)() const>(&sem::BlockCodeSwitch::isLineStart))
    .def("getLineStart", static_cast<sem::BlockCodeSwitch::LineStart&(sem::BlockCodeSwitch::*)()>(&sem::BlockCodeSwitch::getLineStart))
    .def("isCalloutFormat", static_cast<bool(sem::BlockCodeSwitch::*)() const>(&sem::BlockCodeSwitch::isCalloutFormat))
    .def("getCalloutFormat", static_cast<sem::BlockCodeSwitch::CalloutFormat&(sem::BlockCodeSwitch::*)()>(&sem::BlockCodeSwitch::getCalloutFormat))
    .def("isRemoveCallout", static_cast<bool(sem::BlockCodeSwitch::*)() const>(&sem::BlockCodeSwitch::isRemoveCallout))
    .def("getRemoveCallout", static_cast<sem::BlockCodeSwitch::RemoveCallout&(sem::BlockCodeSwitch::*)()>(&sem::BlockCodeSwitch::getRemoveCallout))
    .def("isEmphasizeLine", static_cast<bool(sem::BlockCodeSwitch::*)() const>(&sem::BlockCodeSwitch::isEmphasizeLine))
    .def("getEmphasizeLine", static_cast<sem::BlockCodeSwitch::EmphasizeLine&(sem::BlockCodeSwitch::*)()>(&sem::BlockCodeSwitch::getEmphasizeLine))
    .def("isDedent", static_cast<bool(sem::BlockCodeSwitch::*)() const>(&sem::BlockCodeSwitch::isDedent))
    .def("getDedent", static_cast<sem::BlockCodeSwitch::Dedent&(sem::BlockCodeSwitch::*)()>(&sem::BlockCodeSwitch::getDedent))
    .def_static("getKindStatic",
                static_cast<sem::BlockCodeSwitch::Kind(*)(sem::BlockCodeSwitch::Data const&)>(&sem::BlockCodeSwitch::getKind),
                pybind11::arg("__input"))
    .def("getKind", static_cast<sem::BlockCodeSwitch::Kind(sem::BlockCodeSwitch::*)() const>(&sem::BlockCodeSwitch::getKind))
    .def("__repr__", [](sem::BlockCodeSwitch _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::BlockCodeSwitch _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::BlockCodeEvalResult::None>(m, "BlockCodeEvalResultNone")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::BlockCodeEvalResult::None {
                        sem::BlockCodeEvalResult::None result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def("operator==",
         static_cast<bool(sem::BlockCodeEvalResult::None::*)(sem::BlockCodeEvalResult::None const&) const>(&sem::BlockCodeEvalResult::None::operator==),
         pybind11::arg("other"))
    .def("__repr__", [](sem::BlockCodeEvalResult::None _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::BlockCodeEvalResult::None _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::BlockCodeEvalResult::OrgValue>(m, "BlockCodeEvalResultOrgValue")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::BlockCodeEvalResult::OrgValue {
                        sem::BlockCodeEvalResult::OrgValue result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("value", &sem::BlockCodeEvalResult::OrgValue::value, R"RAW(Evaluation result)RAW")
    .def("operator==",
         static_cast<bool(sem::BlockCodeEvalResult::OrgValue::*)(sem::BlockCodeEvalResult::OrgValue const&) const>(&sem::BlockCodeEvalResult::OrgValue::operator==),
         pybind11::arg("other"))
    .def("__repr__", [](sem::BlockCodeEvalResult::OrgValue _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::BlockCodeEvalResult::OrgValue _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::BlockCodeEvalResult::File>(m, "BlockCodeEvalResultFile")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::BlockCodeEvalResult::File {
                        sem::BlockCodeEvalResult::File result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("path", &sem::BlockCodeEvalResult::File::path)
    .def("operator==",
         static_cast<bool(sem::BlockCodeEvalResult::File::*)(sem::BlockCodeEvalResult::File const&) const>(&sem::BlockCodeEvalResult::File::operator==),
         pybind11::arg("other"))
    .def("__repr__", [](sem::BlockCodeEvalResult::File _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::BlockCodeEvalResult::File _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::BlockCodeEvalResult::Raw>(m, "BlockCodeEvalResultRaw")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::BlockCodeEvalResult::Raw {
                        sem::BlockCodeEvalResult::Raw result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("text", &sem::BlockCodeEvalResult::Raw::text)
    .def("operator==",
         static_cast<bool(sem::BlockCodeEvalResult::Raw::*)(sem::BlockCodeEvalResult::Raw const&) const>(&sem::BlockCodeEvalResult::Raw::operator==),
         pybind11::arg("other"))
    .def("__repr__", [](sem::BlockCodeEvalResult::Raw _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::BlockCodeEvalResult::Raw _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  bind_enum_iterator<sem::BlockCodeEvalResult::Kind>(m, "BlockCodeEvalResultKind", type_registry_guard);
  pybind11::enum_<sem::BlockCodeEvalResult::Kind>(m, "BlockCodeEvalResultKind")
    .value("None", sem::BlockCodeEvalResult::Kind::None)
    .value("OrgValue", sem::BlockCodeEvalResult::Kind::OrgValue)
    .value("File", sem::BlockCodeEvalResult::Kind::File)
    .value("Raw", sem::BlockCodeEvalResult::Kind::Raw)
    .def("__iter__", [](sem::BlockCodeEvalResult::Kind _self) -> PyEnumIterator<sem::BlockCodeEvalResult::Kind> {
                     return
                     PyEnumIterator<sem::BlockCodeEvalResult::Kind>
                     ();
                     })
    ;
  pybind11::class_<sem::BlockCodeEvalResult>(m, "BlockCodeEvalResult")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::BlockCodeEvalResult {
                        sem::BlockCodeEvalResult result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("data", &sem::BlockCodeEvalResult::data)
    .def("operator==",
         static_cast<bool(sem::BlockCodeEvalResult::*)(sem::BlockCodeEvalResult const&) const>(&sem::BlockCodeEvalResult::operator==),
         pybind11::arg("other"))
    .def("isNone", static_cast<bool(sem::BlockCodeEvalResult::*)() const>(&sem::BlockCodeEvalResult::isNone))
    .def("getNone", static_cast<sem::BlockCodeEvalResult::None&(sem::BlockCodeEvalResult::*)()>(&sem::BlockCodeEvalResult::getNone))
    .def("isOrgValue", static_cast<bool(sem::BlockCodeEvalResult::*)() const>(&sem::BlockCodeEvalResult::isOrgValue))
    .def("getOrgValue", static_cast<sem::BlockCodeEvalResult::OrgValue&(sem::BlockCodeEvalResult::*)()>(&sem::BlockCodeEvalResult::getOrgValue))
    .def("isFile", static_cast<bool(sem::BlockCodeEvalResult::*)() const>(&sem::BlockCodeEvalResult::isFile))
    .def("getFile", static_cast<sem::BlockCodeEvalResult::File&(sem::BlockCodeEvalResult::*)()>(&sem::BlockCodeEvalResult::getFile))
    .def("isRaw", static_cast<bool(sem::BlockCodeEvalResult::*)() const>(&sem::BlockCodeEvalResult::isRaw))
    .def("getRaw", static_cast<sem::BlockCodeEvalResult::Raw&(sem::BlockCodeEvalResult::*)()>(&sem::BlockCodeEvalResult::getRaw))
    .def_static("getKindStatic",
                static_cast<sem::BlockCodeEvalResult::Kind(*)(sem::BlockCodeEvalResult::Data const&)>(&sem::BlockCodeEvalResult::getKind),
                pybind11::arg("__input"))
    .def("getKind", static_cast<sem::BlockCodeEvalResult::Kind(sem::BlockCodeEvalResult::*)() const>(&sem::BlockCodeEvalResult::getKind))
    .def("__repr__", [](sem::BlockCodeEvalResult _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::BlockCodeEvalResult _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::DocumentExportConfig::TaskExport>(m, "DocumentExportConfigTaskExport")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::DocumentExportConfig::TaskExport {
                        sem::DocumentExportConfig::TaskExport result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("taskWhitelist", &sem::DocumentExportConfig::TaskExport::taskWhitelist)
    .def("operator==",
         static_cast<bool(sem::DocumentExportConfig::TaskExport::*)(sem::DocumentExportConfig::TaskExport const&) const>(&sem::DocumentExportConfig::TaskExport::operator==),
         pybind11::arg("other"))
    .def("__repr__", [](sem::DocumentExportConfig::TaskExport _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::DocumentExportConfig::TaskExport _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  bind_enum_iterator<sem::DocumentExportConfig::TagExport>(m, "DocumentExportConfigTagExport", type_registry_guard);
  pybind11::enum_<sem::DocumentExportConfig::TagExport>(m, "DocumentExportConfigTagExport")
    .value("None", sem::DocumentExportConfig::TagExport::None)
    .value("All", sem::DocumentExportConfig::TagExport::All)
    .value("NotInToc", sem::DocumentExportConfig::TagExport::NotInToc, R"RAW(Expot tags in subtree titles but not in the table of content)RAW")
    .def("__iter__", [](sem::DocumentExportConfig::TagExport _self) -> PyEnumIterator<sem::DocumentExportConfig::TagExport> {
                     return
                     PyEnumIterator<sem::DocumentExportConfig::TagExport>
                     ();
                     })
    ;
  bind_enum_iterator<sem::DocumentExportConfig::TaskFiltering>(m, "DocumentExportConfigTaskFiltering", type_registry_guard);
  pybind11::enum_<sem::DocumentExportConfig::TaskFiltering>(m, "DocumentExportConfigTaskFiltering")
    .value("Whitelist", sem::DocumentExportConfig::TaskFiltering::Whitelist, R"RAW(Include tasks from the whitelist)RAW")
    .value("Done", sem::DocumentExportConfig::TaskFiltering::Done, R"RAW(Include tasks marked as done)RAW")
    .value("None", sem::DocumentExportConfig::TaskFiltering::None, R"RAW(Exclude all task subtrees from export)RAW")
    .value("All", sem::DocumentExportConfig::TaskFiltering::All, R"RAW(Add all task subtrees to export)RAW")
    .def("__iter__", [](sem::DocumentExportConfig::TaskFiltering _self) -> PyEnumIterator<sem::DocumentExportConfig::TaskFiltering> {
                     return
                     PyEnumIterator<sem::DocumentExportConfig::TaskFiltering>
                     ();
                     })
    ;
  bind_enum_iterator<sem::DocumentExportConfig::BrokenLinks>(m, "DocumentExportConfigBrokenLinks", type_registry_guard);
  pybind11::enum_<sem::DocumentExportConfig::BrokenLinks>(m, "DocumentExportConfigBrokenLinks")
    .value("Mark", sem::DocumentExportConfig::BrokenLinks::Mark)
    .value("Raise", sem::DocumentExportConfig::BrokenLinks::Raise)
    .value("Ignore", sem::DocumentExportConfig::BrokenLinks::Ignore)
    .def("__iter__", [](sem::DocumentExportConfig::BrokenLinks _self) -> PyEnumIterator<sem::DocumentExportConfig::BrokenLinks> {
                     return
                     PyEnumIterator<sem::DocumentExportConfig::BrokenLinks>
                     ();
                     })
    ;
  pybind11::class_<sem::DocumentExportConfig::DoExport>(m, "DocumentExportConfigDoExport")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::DocumentExportConfig::DoExport {
                        sem::DocumentExportConfig::DoExport result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("exportToc", &sem::DocumentExportConfig::DoExport::exportToc)
    .def("operator==",
         static_cast<bool(sem::DocumentExportConfig::DoExport::*)(sem::DocumentExportConfig::DoExport const&) const>(&sem::DocumentExportConfig::DoExport::operator==),
         pybind11::arg("other"))
    .def("__repr__", [](sem::DocumentExportConfig::DoExport _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::DocumentExportConfig::DoExport _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::DocumentExportConfig::ExportFixed>(m, "DocumentExportConfigExportFixed")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::DocumentExportConfig::ExportFixed {
                        sem::DocumentExportConfig::ExportFixed result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("exportLevels", &sem::DocumentExportConfig::ExportFixed::exportLevels)
    .def("operator==",
         static_cast<bool(sem::DocumentExportConfig::ExportFixed::*)(sem::DocumentExportConfig::ExportFixed const&) const>(&sem::DocumentExportConfig::ExportFixed::operator==),
         pybind11::arg("other"))
    .def("__repr__", [](sem::DocumentExportConfig::ExportFixed _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::DocumentExportConfig::ExportFixed _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  bind_enum_iterator<sem::DocumentExportConfig::TocExportKind>(m, "DocumentExportConfigTocExportKind", type_registry_guard);
  pybind11::enum_<sem::DocumentExportConfig::TocExportKind>(m, "DocumentExportConfigTocExportKind")
    .value("DoExport", sem::DocumentExportConfig::TocExportKind::DoExport)
    .value("ExportFixed", sem::DocumentExportConfig::TocExportKind::ExportFixed)
    .def("__iter__", [](sem::DocumentExportConfig::TocExportKind _self) -> PyEnumIterator<sem::DocumentExportConfig::TocExportKind> {
                     return
                     PyEnumIterator<sem::DocumentExportConfig::TocExportKind>
                     ();
                     })
    ;
  pybind11::class_<sem::DocumentExportConfig>(m, "DocumentExportConfig")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::DocumentExportConfig {
                        sem::DocumentExportConfig result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("inlinetasks", &sem::DocumentExportConfig::inlinetasks)
    .def_readwrite("footnotes", &sem::DocumentExportConfig::footnotes)
    .def_readwrite("clock", &sem::DocumentExportConfig::clock)
    .def_readwrite("author", &sem::DocumentExportConfig::author)
    .def_readwrite("emphasis", &sem::DocumentExportConfig::emphasis)
    .def_readwrite("specialStrings", &sem::DocumentExportConfig::specialStrings)
    .def_readwrite("propertyDrawers", &sem::DocumentExportConfig::propertyDrawers)
    .def_readwrite("statisticsCookies", &sem::DocumentExportConfig::statisticsCookies)
    .def_readwrite("todoText", &sem::DocumentExportConfig::todoText, R"RAW(Include todo keywords in export)RAW")
    .def_readwrite("brokenLinks", &sem::DocumentExportConfig::brokenLinks)
    .def_readwrite("tocExport", &sem::DocumentExportConfig::tocExport)
    .def_readwrite("tagExport", &sem::DocumentExportConfig::tagExport)
    .def_readwrite("data", &sem::DocumentExportConfig::data)
    .def("operator==",
         static_cast<bool(sem::DocumentExportConfig::*)(sem::DocumentExportConfig const&) const>(&sem::DocumentExportConfig::operator==),
         pybind11::arg("other"))
    .def("isDoExport", static_cast<bool(sem::DocumentExportConfig::*)() const>(&sem::DocumentExportConfig::isDoExport))
    .def("getDoExport", static_cast<sem::DocumentExportConfig::DoExport&(sem::DocumentExportConfig::*)()>(&sem::DocumentExportConfig::getDoExport))
    .def("isExportFixed", static_cast<bool(sem::DocumentExportConfig::*)() const>(&sem::DocumentExportConfig::isExportFixed))
    .def("getExportFixed", static_cast<sem::DocumentExportConfig::ExportFixed&(sem::DocumentExportConfig::*)()>(&sem::DocumentExportConfig::getExportFixed))
    .def_static("getTocExportKindStatic",
                static_cast<sem::DocumentExportConfig::TocExportKind(*)(sem::DocumentExportConfig::TocExport const&)>(&sem::DocumentExportConfig::getTocExportKind),
                pybind11::arg("__input"))
    .def("getTocExportKind", static_cast<sem::DocumentExportConfig::TocExportKind(sem::DocumentExportConfig::*)() const>(&sem::DocumentExportConfig::getTocExportKind))
    .def("__repr__", [](sem::DocumentExportConfig _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::DocumentExportConfig _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  bind_enum_iterator<sem::SubtreePeriod::Kind>(m, "SubtreePeriodKind", type_registry_guard);
  pybind11::enum_<sem::SubtreePeriod::Kind>(m, "SubtreePeriodKind")
    .value("Clocked", sem::SubtreePeriod::Kind::Clocked, R"RAW(Time period of the task execution.)RAW")
    .value("Closed", sem::SubtreePeriod::Kind::Closed, R"RAW(Task marked as closed)RAW")
    .value("Scheduled", sem::SubtreePeriod::Kind::Scheduled, R"RAW(Date of task execution start plus it's estimated effort duration. If the latter one is missing then only a single time point is returned)RAW")
    .value("Titled", sem::SubtreePeriod::Kind::Titled, R"RAW(Single point or time range used in title. Single point can also be a simple time, such as `12:20`)RAW")
    .value("Deadline", sem::SubtreePeriod::Kind::Deadline, R"RAW(Date of task completion. Must be a single time point)RAW")
    .value("Created", sem::SubtreePeriod::Kind::Created, R"RAW(When the subtree was created)RAW")
    .value("Repeated", sem::SubtreePeriod::Kind::Repeated, R"RAW(Last repeat time of the recurring tasks)RAW")
    .def("__iter__", [](sem::SubtreePeriod::Kind _self) -> PyEnumIterator<sem::SubtreePeriod::Kind> {
                     return
                     PyEnumIterator<sem::SubtreePeriod::Kind>
                     ();
                     })
    ;
  pybind11::class_<sem::SubtreePeriod>(m, "SubtreePeriod")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::SubtreePeriod {
                        sem::SubtreePeriod result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("kind", &sem::SubtreePeriod::kind, R"RAW(Time period kind -- not associated with point/range distinction)RAW")
    .def_readwrite("from_", &sem::SubtreePeriod::from, R"RAW(Clock start time)RAW")
    .def_readwrite("to", &sem::SubtreePeriod::to, R"RAW(Optional end of the clock)RAW")
    .def("operator==",
         static_cast<bool(sem::SubtreePeriod::*)(sem::SubtreePeriod const&) const>(&sem::SubtreePeriod::operator==),
         pybind11::arg("other"))
    .def("__repr__", [](sem::SubtreePeriod _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::SubtreePeriod _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  bind_enum_iterator<sem::NamedProperty::SetMode>(m, "NamedPropertySetMode", type_registry_guard);
  pybind11::enum_<sem::NamedProperty::SetMode>(m, "NamedPropertySetMode")
    .value("Override", sem::NamedProperty::SetMode::Override)
    .value("Add", sem::NamedProperty::SetMode::Add)
    .value("Subtract", sem::NamedProperty::SetMode::Subtract)
    .def("__iter__", [](sem::NamedProperty::SetMode _self) -> PyEnumIterator<sem::NamedProperty::SetMode> {
                     return
                     PyEnumIterator<sem::NamedProperty::SetMode>
                     ();
                     })
    ;
  bind_enum_iterator<sem::NamedProperty::InheritanceMode>(m, "NamedPropertyInheritanceMode", type_registry_guard);
  pybind11::enum_<sem::NamedProperty::InheritanceMode>(m, "NamedPropertyInheritanceMode")
    .value("ThisAndSub", sem::NamedProperty::InheritanceMode::ThisAndSub)
    .value("OnlyThis", sem::NamedProperty::InheritanceMode::OnlyThis)
    .value("OnlySub", sem::NamedProperty::InheritanceMode::OnlySub)
    .def("__iter__", [](sem::NamedProperty::InheritanceMode _self) -> PyEnumIterator<sem::NamedProperty::InheritanceMode> {
                     return
                     PyEnumIterator<sem::NamedProperty::InheritanceMode>
                     ();
                     })
    ;
  pybind11::class_<sem::NamedProperty::Nonblocking>(m, "NamedPropertyNonblocking")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::NamedProperty::Nonblocking {
                        sem::NamedProperty::Nonblocking result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("isBlocking", &sem::NamedProperty::Nonblocking::isBlocking)
    .def("operator==",
         static_cast<bool(sem::NamedProperty::Nonblocking::*)(sem::NamedProperty::Nonblocking const&) const>(&sem::NamedProperty::Nonblocking::operator==),
         pybind11::arg("other"))
    .def("__repr__", [](sem::NamedProperty::Nonblocking _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::NamedProperty::Nonblocking _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::NamedProperty::ArchiveTime>(m, "NamedPropertyArchiveTime")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::NamedProperty::ArchiveTime {
                        sem::NamedProperty::ArchiveTime result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("time", &sem::NamedProperty::ArchiveTime::time)
    .def("operator==",
         static_cast<bool(sem::NamedProperty::ArchiveTime::*)(sem::NamedProperty::ArchiveTime const&) const>(&sem::NamedProperty::ArchiveTime::operator==),
         pybind11::arg("other"))
    .def("__repr__", [](sem::NamedProperty::ArchiveTime _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::NamedProperty::ArchiveTime _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::NamedProperty::ArchiveFile>(m, "NamedPropertyArchiveFile")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::NamedProperty::ArchiveFile {
                        sem::NamedProperty::ArchiveFile result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("file", &sem::NamedProperty::ArchiveFile::file)
    .def("operator==",
         static_cast<bool(sem::NamedProperty::ArchiveFile::*)(sem::NamedProperty::ArchiveFile const&) const>(&sem::NamedProperty::ArchiveFile::operator==),
         pybind11::arg("other"))
    .def("__repr__", [](sem::NamedProperty::ArchiveFile _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::NamedProperty::ArchiveFile _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::NamedProperty::ArchiveOlpath>(m, "NamedPropertyArchiveOlpath")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::NamedProperty::ArchiveOlpath {
                        sem::NamedProperty::ArchiveOlpath result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("path", &sem::NamedProperty::ArchiveOlpath::path)
    .def("operator==",
         static_cast<bool(sem::NamedProperty::ArchiveOlpath::*)(sem::NamedProperty::ArchiveOlpath const&) const>(&sem::NamedProperty::ArchiveOlpath::operator==),
         pybind11::arg("other"))
    .def("__repr__", [](sem::NamedProperty::ArchiveOlpath _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::NamedProperty::ArchiveOlpath _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::NamedProperty::ArchiveTarget>(m, "NamedPropertyArchiveTarget")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::NamedProperty::ArchiveTarget {
                        sem::NamedProperty::ArchiveTarget result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("path", &sem::NamedProperty::ArchiveTarget::path)
    .def_readwrite("pattern", &sem::NamedProperty::ArchiveTarget::pattern)
    .def("operator==",
         static_cast<bool(sem::NamedProperty::ArchiveTarget::*)(sem::NamedProperty::ArchiveTarget const&) const>(&sem::NamedProperty::ArchiveTarget::operator==),
         pybind11::arg("other"))
    .def("__repr__", [](sem::NamedProperty::ArchiveTarget _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::NamedProperty::ArchiveTarget _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::NamedProperty::ArchiveCategory>(m, "NamedPropertyArchiveCategory")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::NamedProperty::ArchiveCategory {
                        sem::NamedProperty::ArchiveCategory result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("category", &sem::NamedProperty::ArchiveCategory::category)
    .def("operator==",
         static_cast<bool(sem::NamedProperty::ArchiveCategory::*)(sem::NamedProperty::ArchiveCategory const&) const>(&sem::NamedProperty::ArchiveCategory::operator==),
         pybind11::arg("other"))
    .def("__repr__", [](sem::NamedProperty::ArchiveCategory _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::NamedProperty::ArchiveCategory _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::NamedProperty::ArchiveTodo>(m, "NamedPropertyArchiveTodo")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::NamedProperty::ArchiveTodo {
                        sem::NamedProperty::ArchiveTodo result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("todo", &sem::NamedProperty::ArchiveTodo::todo)
    .def("operator==",
         static_cast<bool(sem::NamedProperty::ArchiveTodo::*)(sem::NamedProperty::ArchiveTodo const&) const>(&sem::NamedProperty::ArchiveTodo::operator==),
         pybind11::arg("other"))
    .def("__repr__", [](sem::NamedProperty::ArchiveTodo _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::NamedProperty::ArchiveTodo _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::NamedProperty::Trigger>(m, "NamedPropertyTrigger")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::NamedProperty::Trigger {
                        sem::NamedProperty::Trigger result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def("operator==",
         static_cast<bool(sem::NamedProperty::Trigger::*)(sem::NamedProperty::Trigger const&) const>(&sem::NamedProperty::Trigger::operator==),
         pybind11::arg("other"))
    .def("__repr__", [](sem::NamedProperty::Trigger _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::NamedProperty::Trigger _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::NamedProperty::ExportLatexClass>(m, "NamedPropertyExportLatexClass")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::NamedProperty::ExportLatexClass {
                        sem::NamedProperty::ExportLatexClass result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("latexClass", &sem::NamedProperty::ExportLatexClass::latexClass)
    .def("operator==",
         static_cast<bool(sem::NamedProperty::ExportLatexClass::*)(sem::NamedProperty::ExportLatexClass const&) const>(&sem::NamedProperty::ExportLatexClass::operator==),
         pybind11::arg("other"))
    .def("__repr__", [](sem::NamedProperty::ExportLatexClass _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::NamedProperty::ExportLatexClass _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::NamedProperty::ExportLatexClassOptions>(m, "NamedPropertyExportLatexClassOptions")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::NamedProperty::ExportLatexClassOptions {
                        sem::NamedProperty::ExportLatexClassOptions result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("options", &sem::NamedProperty::ExportLatexClassOptions::options)
    .def("operator==",
         static_cast<bool(sem::NamedProperty::ExportLatexClassOptions::*)(sem::NamedProperty::ExportLatexClassOptions const&) const>(&sem::NamedProperty::ExportLatexClassOptions::operator==),
         pybind11::arg("other"))
    .def("__repr__", [](sem::NamedProperty::ExportLatexClassOptions _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::NamedProperty::ExportLatexClassOptions _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::NamedProperty::ExportLatexHeader>(m, "NamedPropertyExportLatexHeader")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::NamedProperty::ExportLatexHeader {
                        sem::NamedProperty::ExportLatexHeader result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("header", &sem::NamedProperty::ExportLatexHeader::header)
    .def("operator==",
         static_cast<bool(sem::NamedProperty::ExportLatexHeader::*)(sem::NamedProperty::ExportLatexHeader const&) const>(&sem::NamedProperty::ExportLatexHeader::operator==),
         pybind11::arg("other"))
    .def("__repr__", [](sem::NamedProperty::ExportLatexHeader _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::NamedProperty::ExportLatexHeader _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::NamedProperty::ExportLatexCompiler>(m, "NamedPropertyExportLatexCompiler")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::NamedProperty::ExportLatexCompiler {
                        sem::NamedProperty::ExportLatexCompiler result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("compiler", &sem::NamedProperty::ExportLatexCompiler::compiler)
    .def("operator==",
         static_cast<bool(sem::NamedProperty::ExportLatexCompiler::*)(sem::NamedProperty::ExportLatexCompiler const&) const>(&sem::NamedProperty::ExportLatexCompiler::operator==),
         pybind11::arg("other"))
    .def("__repr__", [](sem::NamedProperty::ExportLatexCompiler _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::NamedProperty::ExportLatexCompiler _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::NamedProperty::Ordered>(m, "NamedPropertyOrdered")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::NamedProperty::Ordered {
                        sem::NamedProperty::Ordered result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("isOrdered", &sem::NamedProperty::Ordered::isOrdered)
    .def("operator==",
         static_cast<bool(sem::NamedProperty::Ordered::*)(sem::NamedProperty::Ordered const&) const>(&sem::NamedProperty::Ordered::operator==),
         pybind11::arg("other"))
    .def("__repr__", [](sem::NamedProperty::Ordered _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::NamedProperty::Ordered _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::NamedProperty::Effort>(m, "NamedPropertyEffort")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::NamedProperty::Effort {
                        sem::NamedProperty::Effort result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("hours", &sem::NamedProperty::Effort::hours)
    .def_readwrite("minutes", &sem::NamedProperty::Effort::minutes)
    .def("operator==",
         static_cast<bool(sem::NamedProperty::Effort::*)(sem::NamedProperty::Effort const&) const>(&sem::NamedProperty::Effort::operator==),
         pybind11::arg("other"))
    .def("__repr__", [](sem::NamedProperty::Effort _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::NamedProperty::Effort _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  bind_enum_iterator<sem::NamedProperty::Visibility::Level>(m, "NamedPropertyVisibilityLevel", type_registry_guard);
  pybind11::enum_<sem::NamedProperty::Visibility::Level>(m, "NamedPropertyVisibilityLevel")
    .value("Folded", sem::NamedProperty::Visibility::Level::Folded)
    .value("Children", sem::NamedProperty::Visibility::Level::Children)
    .value("Content", sem::NamedProperty::Visibility::Level::Content)
    .value("All", sem::NamedProperty::Visibility::Level::All)
    .def("__iter__", [](sem::NamedProperty::Visibility::Level _self) -> PyEnumIterator<sem::NamedProperty::Visibility::Level> {
                     return
                     PyEnumIterator<sem::NamedProperty::Visibility::Level>
                     ();
                     })
    ;
  pybind11::class_<sem::NamedProperty::Visibility>(m, "NamedPropertyVisibility")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::NamedProperty::Visibility {
                        sem::NamedProperty::Visibility result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("level", &sem::NamedProperty::Visibility::level)
    .def("operator==",
         static_cast<bool(sem::NamedProperty::Visibility::*)(sem::NamedProperty::Visibility const&) const>(&sem::NamedProperty::Visibility::operator==),
         pybind11::arg("other"))
    .def("__repr__", [](sem::NamedProperty::Visibility _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::NamedProperty::Visibility _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::NamedProperty::ExportOptions>(m, "NamedPropertyExportOptions")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::NamedProperty::ExportOptions {
                        sem::NamedProperty::ExportOptions result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("backend", &sem::NamedProperty::ExportOptions::backend)
    .def_readwrite("values", &sem::NamedProperty::ExportOptions::values)
    .def("operator==",
         static_cast<bool(sem::NamedProperty::ExportOptions::*)(sem::NamedProperty::ExportOptions const&) const>(&sem::NamedProperty::ExportOptions::operator==),
         pybind11::arg("other"))
    .def("__repr__", [](sem::NamedProperty::ExportOptions _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::NamedProperty::ExportOptions _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::NamedProperty::Blocker>(m, "NamedPropertyBlocker")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::NamedProperty::Blocker {
                        sem::NamedProperty::Blocker result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("blockers", &sem::NamedProperty::Blocker::blockers)
    .def("operator==",
         static_cast<bool(sem::NamedProperty::Blocker::*)(sem::NamedProperty::Blocker const&) const>(&sem::NamedProperty::Blocker::operator==),
         pybind11::arg("other"))
    .def("__repr__", [](sem::NamedProperty::Blocker _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::NamedProperty::Blocker _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::NamedProperty::Unnumbered>(m, "NamedPropertyUnnumbered")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::NamedProperty::Unnumbered {
                        sem::NamedProperty::Unnumbered result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def("operator==",
         static_cast<bool(sem::NamedProperty::Unnumbered::*)(sem::NamedProperty::Unnumbered const&) const>(&sem::NamedProperty::Unnumbered::operator==),
         pybind11::arg("other"))
    .def("__repr__", [](sem::NamedProperty::Unnumbered _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::NamedProperty::Unnumbered _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::NamedProperty::Created>(m, "NamedPropertyCreated")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::NamedProperty::Created {
                        sem::NamedProperty::Created result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("time", &sem::NamedProperty::Created::time)
    .def("operator==",
         static_cast<bool(sem::NamedProperty::Created::*)(sem::NamedProperty::Created const&) const>(&sem::NamedProperty::Created::operator==),
         pybind11::arg("other"))
    .def("__repr__", [](sem::NamedProperty::Created _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::NamedProperty::Created _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::NamedProperty::CustomArgs>(m, "NamedPropertyCustomArgs")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::NamedProperty::CustomArgs {
                        sem::NamedProperty::CustomArgs result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("name", &sem::NamedProperty::CustomArgs::name, R"RAW(Original name of the property)RAW")
    .def_readwrite("sub", &sem::NamedProperty::CustomArgs::sub, R"RAW(Property target specialization)RAW")
    .def_readwrite("attrs", &sem::NamedProperty::CustomArgs::attrs, R"RAW(Property parameters)RAW")
    .def("operator==",
         static_cast<bool(sem::NamedProperty::CustomArgs::*)(sem::NamedProperty::CustomArgs const&) const>(&sem::NamedProperty::CustomArgs::operator==),
         pybind11::arg("other"))
    .def("__repr__", [](sem::NamedProperty::CustomArgs _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::NamedProperty::CustomArgs _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::NamedProperty::CustomRaw>(m, "NamedPropertyCustomRaw")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::NamedProperty::CustomRaw {
                        sem::NamedProperty::CustomRaw result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("name", &sem::NamedProperty::CustomRaw::name, R"RAW(Original name of the property)RAW")
    .def_readwrite("value", &sem::NamedProperty::CustomRaw::value, R"RAW(Property value)RAW")
    .def("operator==",
         static_cast<bool(sem::NamedProperty::CustomRaw::*)(sem::NamedProperty::CustomRaw const&) const>(&sem::NamedProperty::CustomRaw::operator==),
         pybind11::arg("other"))
    .def("__repr__", [](sem::NamedProperty::CustomRaw _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::NamedProperty::CustomRaw _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  bind_enum_iterator<sem::NamedProperty::Kind>(m, "NamedPropertyKind", type_registry_guard);
  pybind11::enum_<sem::NamedProperty::Kind>(m, "NamedPropertyKind")
    .value("Nonblocking", sem::NamedProperty::Kind::Nonblocking)
    .value("ArchiveTime", sem::NamedProperty::Kind::ArchiveTime)
    .value("ArchiveFile", sem::NamedProperty::Kind::ArchiveFile)
    .value("ArchiveOlpath", sem::NamedProperty::Kind::ArchiveOlpath)
    .value("ArchiveTarget", sem::NamedProperty::Kind::ArchiveTarget)
    .value("ArchiveCategory", sem::NamedProperty::Kind::ArchiveCategory)
    .value("ArchiveTodo", sem::NamedProperty::Kind::ArchiveTodo)
    .value("Trigger", sem::NamedProperty::Kind::Trigger)
    .value("ExportLatexClass", sem::NamedProperty::Kind::ExportLatexClass)
    .value("ExportLatexClassOptions", sem::NamedProperty::Kind::ExportLatexClassOptions)
    .value("ExportLatexHeader", sem::NamedProperty::Kind::ExportLatexHeader)
    .value("ExportLatexCompiler", sem::NamedProperty::Kind::ExportLatexCompiler)
    .value("Ordered", sem::NamedProperty::Kind::Ordered)
    .value("Effort", sem::NamedProperty::Kind::Effort)
    .value("Visibility", sem::NamedProperty::Kind::Visibility)
    .value("ExportOptions", sem::NamedProperty::Kind::ExportOptions)
    .value("Blocker", sem::NamedProperty::Kind::Blocker)
    .value("Unnumbered", sem::NamedProperty::Kind::Unnumbered)
    .value("Created", sem::NamedProperty::Kind::Created)
    .value("CustomArgs", sem::NamedProperty::Kind::CustomArgs)
    .value("CustomRaw", sem::NamedProperty::Kind::CustomRaw)
    .def("__iter__", [](sem::NamedProperty::Kind _self) -> PyEnumIterator<sem::NamedProperty::Kind> {
                     return
                     PyEnumIterator<sem::NamedProperty::Kind>
                     ();
                     })
    ;
  pybind11::class_<sem::NamedProperty>(m, "NamedProperty")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::NamedProperty {
                        sem::NamedProperty result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("mainSetRule", &sem::NamedProperty::mainSetRule)
    .def_readwrite("subSetRule", &sem::NamedProperty::subSetRule)
    .def_readwrite("inheritanceMode", &sem::NamedProperty::inheritanceMode)
    .def_readwrite("data", &sem::NamedProperty::data)
    .def("isMatching",
         static_cast<bool(sem::NamedProperty::*)(Str const&, Opt<Str> const&) const>(&sem::NamedProperty::isMatching),
         pybind11::arg("kind"),
         pybind11::arg_v("subKind", std::nullopt),
         R"RAW(Check if property matches specified kind and optional subkind. Built-in property checking is also done with this function -- 'created' etc.)RAW")
    .def("getName", static_cast<Str(sem::NamedProperty::*)() const>(&sem::NamedProperty::getName), R"RAW(Get non-normalized name of the property (for built-in and user))RAW")
    .def("getSubKind", static_cast<Opt<Str>(sem::NamedProperty::*)() const>(&sem::NamedProperty::getSubKind), R"RAW(Get non-normalized sub-kind for the property.)RAW")
    .def("operator==",
         static_cast<bool(sem::NamedProperty::*)(sem::NamedProperty const&) const>(&sem::NamedProperty::operator==),
         pybind11::arg("other"))
    .def("isNonblocking", static_cast<bool(sem::NamedProperty::*)() const>(&sem::NamedProperty::isNonblocking))
    .def("getNonblocking", static_cast<sem::NamedProperty::Nonblocking&(sem::NamedProperty::*)()>(&sem::NamedProperty::getNonblocking))
    .def("isArchiveTime", static_cast<bool(sem::NamedProperty::*)() const>(&sem::NamedProperty::isArchiveTime))
    .def("getArchiveTime", static_cast<sem::NamedProperty::ArchiveTime&(sem::NamedProperty::*)()>(&sem::NamedProperty::getArchiveTime))
    .def("isArchiveFile", static_cast<bool(sem::NamedProperty::*)() const>(&sem::NamedProperty::isArchiveFile))
    .def("getArchiveFile", static_cast<sem::NamedProperty::ArchiveFile&(sem::NamedProperty::*)()>(&sem::NamedProperty::getArchiveFile))
    .def("isArchiveOlpath", static_cast<bool(sem::NamedProperty::*)() const>(&sem::NamedProperty::isArchiveOlpath))
    .def("getArchiveOlpath", static_cast<sem::NamedProperty::ArchiveOlpath&(sem::NamedProperty::*)()>(&sem::NamedProperty::getArchiveOlpath))
    .def("isArchiveTarget", static_cast<bool(sem::NamedProperty::*)() const>(&sem::NamedProperty::isArchiveTarget))
    .def("getArchiveTarget", static_cast<sem::NamedProperty::ArchiveTarget&(sem::NamedProperty::*)()>(&sem::NamedProperty::getArchiveTarget))
    .def("isArchiveCategory", static_cast<bool(sem::NamedProperty::*)() const>(&sem::NamedProperty::isArchiveCategory))
    .def("getArchiveCategory", static_cast<sem::NamedProperty::ArchiveCategory&(sem::NamedProperty::*)()>(&sem::NamedProperty::getArchiveCategory))
    .def("isArchiveTodo", static_cast<bool(sem::NamedProperty::*)() const>(&sem::NamedProperty::isArchiveTodo))
    .def("getArchiveTodo", static_cast<sem::NamedProperty::ArchiveTodo&(sem::NamedProperty::*)()>(&sem::NamedProperty::getArchiveTodo))
    .def("isTrigger", static_cast<bool(sem::NamedProperty::*)() const>(&sem::NamedProperty::isTrigger))
    .def("getTrigger", static_cast<sem::NamedProperty::Trigger&(sem::NamedProperty::*)()>(&sem::NamedProperty::getTrigger))
    .def("isExportLatexClass", static_cast<bool(sem::NamedProperty::*)() const>(&sem::NamedProperty::isExportLatexClass))
    .def("getExportLatexClass", static_cast<sem::NamedProperty::ExportLatexClass&(sem::NamedProperty::*)()>(&sem::NamedProperty::getExportLatexClass))
    .def("isExportLatexClassOptions", static_cast<bool(sem::NamedProperty::*)() const>(&sem::NamedProperty::isExportLatexClassOptions))
    .def("getExportLatexClassOptions", static_cast<sem::NamedProperty::ExportLatexClassOptions&(sem::NamedProperty::*)()>(&sem::NamedProperty::getExportLatexClassOptions))
    .def("isExportLatexHeader", static_cast<bool(sem::NamedProperty::*)() const>(&sem::NamedProperty::isExportLatexHeader))
    .def("getExportLatexHeader", static_cast<sem::NamedProperty::ExportLatexHeader&(sem::NamedProperty::*)()>(&sem::NamedProperty::getExportLatexHeader))
    .def("isExportLatexCompiler", static_cast<bool(sem::NamedProperty::*)() const>(&sem::NamedProperty::isExportLatexCompiler))
    .def("getExportLatexCompiler", static_cast<sem::NamedProperty::ExportLatexCompiler&(sem::NamedProperty::*)()>(&sem::NamedProperty::getExportLatexCompiler))
    .def("isOrdered", static_cast<bool(sem::NamedProperty::*)() const>(&sem::NamedProperty::isOrdered))
    .def("getOrdered", static_cast<sem::NamedProperty::Ordered&(sem::NamedProperty::*)()>(&sem::NamedProperty::getOrdered))
    .def("isEffort", static_cast<bool(sem::NamedProperty::*)() const>(&sem::NamedProperty::isEffort))
    .def("getEffort", static_cast<sem::NamedProperty::Effort&(sem::NamedProperty::*)()>(&sem::NamedProperty::getEffort))
    .def("isVisibility", static_cast<bool(sem::NamedProperty::*)() const>(&sem::NamedProperty::isVisibility))
    .def("getVisibility", static_cast<sem::NamedProperty::Visibility&(sem::NamedProperty::*)()>(&sem::NamedProperty::getVisibility))
    .def("isExportOptions", static_cast<bool(sem::NamedProperty::*)() const>(&sem::NamedProperty::isExportOptions))
    .def("getExportOptions", static_cast<sem::NamedProperty::ExportOptions&(sem::NamedProperty::*)()>(&sem::NamedProperty::getExportOptions))
    .def("isBlocker", static_cast<bool(sem::NamedProperty::*)() const>(&sem::NamedProperty::isBlocker))
    .def("getBlocker", static_cast<sem::NamedProperty::Blocker&(sem::NamedProperty::*)()>(&sem::NamedProperty::getBlocker))
    .def("isUnnumbered", static_cast<bool(sem::NamedProperty::*)() const>(&sem::NamedProperty::isUnnumbered))
    .def("getUnnumbered", static_cast<sem::NamedProperty::Unnumbered&(sem::NamedProperty::*)()>(&sem::NamedProperty::getUnnumbered))
    .def("isCreated", static_cast<bool(sem::NamedProperty::*)() const>(&sem::NamedProperty::isCreated))
    .def("getCreated", static_cast<sem::NamedProperty::Created&(sem::NamedProperty::*)()>(&sem::NamedProperty::getCreated))
    .def("isCustomArgs", static_cast<bool(sem::NamedProperty::*)() const>(&sem::NamedProperty::isCustomArgs))
    .def("getCustomArgs", static_cast<sem::NamedProperty::CustomArgs&(sem::NamedProperty::*)()>(&sem::NamedProperty::getCustomArgs))
    .def("isCustomRaw", static_cast<bool(sem::NamedProperty::*)() const>(&sem::NamedProperty::isCustomRaw))
    .def("getCustomRaw", static_cast<sem::NamedProperty::CustomRaw&(sem::NamedProperty::*)()>(&sem::NamedProperty::getCustomRaw))
    .def_static("getKindStatic",
                static_cast<sem::NamedProperty::Kind(*)(sem::NamedProperty::Data const&)>(&sem::NamedProperty::getKind),
                pybind11::arg("__input"))
    .def("getKind", static_cast<sem::NamedProperty::Kind(sem::NamedProperty::*)() const>(&sem::NamedProperty::getKind))
    .def("__repr__", [](sem::NamedProperty _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::NamedProperty _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::None, sem::SemId<sem::None>, sem::Org>(m, "None")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::None {
                        sem::None result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def("__repr__", [](sem::None _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::None _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::Attr, sem::SemId<sem::Attr>, sem::Org>(m, "Attr")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::Attr {
                        sem::Attr result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("arg", &sem::Attr::arg)
    .def("getName", static_cast<Str(sem::Attr::*)() const>(&sem::Attr::getName))
    .def("getValue", static_cast<Str(sem::Attr::*)() const>(&sem::Attr::getValue))
    .def("getVarname", static_cast<Str(sem::Attr::*)() const>(&sem::Attr::getVarname))
    .def("__repr__", [](sem::Attr _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::Attr _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::AttrList, sem::SemId<sem::AttrList>, sem::Org>(m, "AttrList")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::AttrList {
                        sem::AttrList result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("args", &sem::AttrList::args, R"RAW(List of arguments)RAW")
    .def("__repr__", [](sem::AttrList _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::AttrList _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::Attrs, sem::SemId<sem::Attrs>, sem::Org>(m, "Attrs")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::Attrs {
                        sem::Attrs result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("positional", &sem::Attrs::positional, R"RAW(Positional arguments with no keys)RAW")
    .def_readwrite("named", &sem::Attrs::named, R"RAW(Stored key-value mapping)RAW")
    .def("getAttrs",
         static_cast<Vec<sem::AttrValue>(sem::Attrs::*)(Opt<Str> const&) const>(&sem::Attrs::getAttrs),
         pybind11::arg_v("key", std::nullopt))
    .def("__repr__", [](sem::Attrs _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::Attrs _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::ErrorItem, sem::SemId<sem::ErrorItem>, sem::Org>(m, "ErrorItem")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::ErrorItem {
                        sem::ErrorItem result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("message", &sem::ErrorItem::message)
    .def_readwrite("function", &sem::ErrorItem::function, R"RAW(Conversion function name where the error was created)RAW")
    .def_readwrite("line", &sem::ErrorItem::line, R"RAW(Line number for the conversion where the error was created)RAW")
    .def("__repr__", [](sem::ErrorItem _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::ErrorItem _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::ErrorGroup, sem::SemId<sem::ErrorGroup>, sem::Org>(m, "ErrorGroup")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::ErrorGroup {
                        sem::ErrorGroup result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("diagnostics", &sem::ErrorGroup::diagnostics)
    .def_readwrite("function", &sem::ErrorGroup::function, R"RAW(Conversion function name where the error was created)RAW")
    .def_readwrite("line", &sem::ErrorGroup::line, R"RAW(Line number for the conversion where the error was created)RAW")
    .def("__repr__", [](sem::ErrorGroup _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::ErrorGroup _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::Stmt, sem::SemId<sem::Stmt>, sem::Org>(m, "Stmt")
    .def_readwrite("attached", &sem::Stmt::attached)
    .def("getAttached",
         static_cast<Vec<sem::SemId<sem::Org>>(sem::Stmt::*)(Opt<Str> const&) const>(&sem::Stmt::getAttached),
         pybind11::arg_v("kind", std::nullopt),
         R"RAW(Return attached nodes of a specific kinds or all attached (if kind is nullopt))RAW")
    .def("getCaption", static_cast<Vec<sem::SemId<sem::Org>>(sem::Stmt::*)() const>(&sem::Stmt::getCaption))
    .def("getName", static_cast<Vec<Str>(sem::Stmt::*)() const>(&sem::Stmt::getName))
    .def("getAttrs",
         static_cast<Vec<sem::AttrValue>(sem::Stmt::*)(Opt<Str> const&) const>(&sem::Stmt::getAttrs),
         pybind11::arg_v("kind", std::nullopt),
         R"RAW(Get all named arguments for the command, across all attached properties. If kind is nullopt returns all attached arguments for all properties.)RAW")
    .def("getFirstAttr",
         static_cast<Opt<sem::AttrValue>(sem::Stmt::*)(Str const&) const>(&sem::Stmt::getFirstAttr),
         pybind11::arg("kind"),
         R"RAW(Get the first parameter for the statement. In case there is a longer list of values matching given kinddifferent node kinds can implement different priorities )RAW")
    ;
  pybind11::class_<sem::Inline, sem::SemId<sem::Inline>, sem::Org>(m, "Inline")
    ;
  pybind11::class_<sem::StmtList, sem::SemId<sem::StmtList>, sem::Org>(m, "StmtList")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::StmtList {
                        sem::StmtList result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def("__repr__", [](sem::StmtList _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::StmtList _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::Empty, sem::SemId<sem::Empty>, sem::Org>(m, "Empty")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::Empty {
                        sem::Empty result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def("__repr__", [](sem::Empty _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::Empty _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::Cmd, sem::SemId<sem::Cmd>, sem::Stmt>(m, "Cmd")
    .def_readwrite("attrs", &sem::Cmd::attrs, R"RAW(Additional parameters aside from 'exporter',)RAW")
    .def_readwrite("attached", &sem::Cmd::attached)
    .def("getAttrs",
         static_cast<Vec<sem::AttrValue>(sem::Cmd::*)(Opt<Str> const&) const>(&sem::Cmd::getAttrs),
         pybind11::arg_v("key", std::nullopt),
         R"RAW(Return all parameters with keys matching name. This is an override implementation that accounts for the explicit command parameters if any.)RAW")
    .def("getFirstAttr",
         static_cast<Opt<sem::AttrValue>(sem::Cmd::*)(Str const&) const>(&sem::Cmd::getFirstAttr),
         pybind11::arg("kind"),
         R"RAW(Override of the base statement argument get, prioritizing the explicit command parameters)RAW")
    .def("getAttached",
         static_cast<Vec<sem::SemId<sem::Org>>(sem::Cmd::*)(Opt<Str> const&) const>(&sem::Cmd::getAttached),
         pybind11::arg_v("kind", std::nullopt),
         R"RAW(Return attached nodes of a specific kinds or all attached (if kind is nullopt))RAW")
    .def("getCaption", static_cast<Vec<sem::SemId<sem::Org>>(sem::Cmd::*)() const>(&sem::Cmd::getCaption))
    .def("getName", static_cast<Vec<Str>(sem::Cmd::*)() const>(&sem::Cmd::getName))
    .def("getAttrs",
         static_cast<Vec<sem::AttrValue>(sem::Cmd::*)(Opt<Str> const&) const>(&sem::Cmd::getAttrs),
         pybind11::arg_v("kind", std::nullopt),
         R"RAW(Get all named arguments for the command, across all attached properties. If kind is nullopt returns all attached arguments for all properties.)RAW")
    .def("getFirstAttr",
         static_cast<Opt<sem::AttrValue>(sem::Cmd::*)(Str const&) const>(&sem::Cmd::getFirstAttr),
         pybind11::arg("kind"),
         R"RAW(Get the first parameter for the statement. In case there is a longer list of values matching given kinddifferent node kinds can implement different priorities )RAW")
    ;
  pybind11::class_<sem::Block, sem::SemId<sem::Block>, sem::Cmd>(m, "Block")
    .def_readwrite("attrs", &sem::Block::attrs, R"RAW(Additional parameters aside from 'exporter',)RAW")
    .def_readwrite("attached", &sem::Block::attached)
    .def("getAttrs",
         static_cast<Vec<sem::AttrValue>(sem::Block::*)(Opt<Str> const&) const>(&sem::Block::getAttrs),
         pybind11::arg_v("key", std::nullopt),
         R"RAW(Return all parameters with keys matching name. This is an override implementation that accounts for the explicit command parameters if any.)RAW")
    .def("getFirstAttr",
         static_cast<Opt<sem::AttrValue>(sem::Block::*)(Str const&) const>(&sem::Block::getFirstAttr),
         pybind11::arg("kind"),
         R"RAW(Override of the base statement argument get, prioritizing the explicit command parameters)RAW")
    .def("getAttached",
         static_cast<Vec<sem::SemId<sem::Org>>(sem::Block::*)(Opt<Str> const&) const>(&sem::Block::getAttached),
         pybind11::arg_v("kind", std::nullopt),
         R"RAW(Return attached nodes of a specific kinds or all attached (if kind is nullopt))RAW")
    .def("getCaption", static_cast<Vec<sem::SemId<sem::Org>>(sem::Block::*)() const>(&sem::Block::getCaption))
    .def("getName", static_cast<Vec<Str>(sem::Block::*)() const>(&sem::Block::getName))
    .def("getAttrs",
         static_cast<Vec<sem::AttrValue>(sem::Block::*)(Opt<Str> const&) const>(&sem::Block::getAttrs),
         pybind11::arg_v("kind", std::nullopt),
         R"RAW(Get all named arguments for the command, across all attached properties. If kind is nullopt returns all attached arguments for all properties.)RAW")
    .def("getFirstAttr",
         static_cast<Opt<sem::AttrValue>(sem::Block::*)(Str const&) const>(&sem::Block::getFirstAttr),
         pybind11::arg("kind"),
         R"RAW(Get the first parameter for the statement. In case there is a longer list of values matching given kinddifferent node kinds can implement different priorities )RAW")
    ;
  pybind11::class_<sem::LineCommand, sem::SemId<sem::LineCommand>, sem::Cmd>(m, "LineCommand")
    .def_readwrite("attrs", &sem::LineCommand::attrs, R"RAW(Additional parameters aside from 'exporter',)RAW")
    .def_readwrite("attached", &sem::LineCommand::attached)
    .def("getAttrs",
         static_cast<Vec<sem::AttrValue>(sem::LineCommand::*)(Opt<Str> const&) const>(&sem::LineCommand::getAttrs),
         pybind11::arg_v("key", std::nullopt),
         R"RAW(Return all parameters with keys matching name. This is an override implementation that accounts for the explicit command parameters if any.)RAW")
    .def("getFirstAttr",
         static_cast<Opt<sem::AttrValue>(sem::LineCommand::*)(Str const&) const>(&sem::LineCommand::getFirstAttr),
         pybind11::arg("kind"),
         R"RAW(Override of the base statement argument get, prioritizing the explicit command parameters)RAW")
    .def("getAttached",
         static_cast<Vec<sem::SemId<sem::Org>>(sem::LineCommand::*)(Opt<Str> const&) const>(&sem::LineCommand::getAttached),
         pybind11::arg_v("kind", std::nullopt),
         R"RAW(Return attached nodes of a specific kinds or all attached (if kind is nullopt))RAW")
    .def("getCaption", static_cast<Vec<sem::SemId<sem::Org>>(sem::LineCommand::*)() const>(&sem::LineCommand::getCaption))
    .def("getName", static_cast<Vec<Str>(sem::LineCommand::*)() const>(&sem::LineCommand::getName))
    .def("getAttrs",
         static_cast<Vec<sem::AttrValue>(sem::LineCommand::*)(Opt<Str> const&) const>(&sem::LineCommand::getAttrs),
         pybind11::arg_v("kind", std::nullopt),
         R"RAW(Get all named arguments for the command, across all attached properties. If kind is nullopt returns all attached arguments for all properties.)RAW")
    .def("getFirstAttr",
         static_cast<Opt<sem::AttrValue>(sem::LineCommand::*)(Str const&) const>(&sem::LineCommand::getFirstAttr),
         pybind11::arg("kind"),
         R"RAW(Get the first parameter for the statement. In case there is a longer list of values matching given kinddifferent node kinds can implement different priorities )RAW")
    ;
  pybind11::class_<sem::Attached, sem::SemId<sem::Attached>, sem::LineCommand>(m, "Attached")
    .def_readwrite("attrs", &sem::Attached::attrs, R"RAW(Additional parameters aside from 'exporter',)RAW")
    .def_readwrite("attached", &sem::Attached::attached)
    .def("getAttrs",
         static_cast<Vec<sem::AttrValue>(sem::Attached::*)(Opt<Str> const&) const>(&sem::Attached::getAttrs),
         pybind11::arg_v("key", std::nullopt),
         R"RAW(Return all parameters with keys matching name. This is an override implementation that accounts for the explicit command parameters if any.)RAW")
    .def("getFirstAttr",
         static_cast<Opt<sem::AttrValue>(sem::Attached::*)(Str const&) const>(&sem::Attached::getFirstAttr),
         pybind11::arg("kind"),
         R"RAW(Override of the base statement argument get, prioritizing the explicit command parameters)RAW")
    .def("getAttached",
         static_cast<Vec<sem::SemId<sem::Org>>(sem::Attached::*)(Opt<Str> const&) const>(&sem::Attached::getAttached),
         pybind11::arg_v("kind", std::nullopt),
         R"RAW(Return attached nodes of a specific kinds or all attached (if kind is nullopt))RAW")
    .def("getCaption", static_cast<Vec<sem::SemId<sem::Org>>(sem::Attached::*)() const>(&sem::Attached::getCaption))
    .def("getName", static_cast<Vec<Str>(sem::Attached::*)() const>(&sem::Attached::getName))
    .def("getAttrs",
         static_cast<Vec<sem::AttrValue>(sem::Attached::*)(Opt<Str> const&) const>(&sem::Attached::getAttrs),
         pybind11::arg_v("kind", std::nullopt),
         R"RAW(Get all named arguments for the command, across all attached properties. If kind is nullopt returns all attached arguments for all properties.)RAW")
    .def("getFirstAttr",
         static_cast<Opt<sem::AttrValue>(sem::Attached::*)(Str const&) const>(&sem::Attached::getFirstAttr),
         pybind11::arg("kind"),
         R"RAW(Get the first parameter for the statement. In case there is a longer list of values matching given kinddifferent node kinds can implement different priorities )RAW")
    ;
  pybind11::class_<sem::Leaf, sem::SemId<sem::Leaf>, sem::Org>(m, "Leaf")
    .def_readwrite("text", &sem::Leaf::text, R"RAW(Final leaf value)RAW")
    .def("getText", static_cast<Str(sem::Leaf::*)() const>(&sem::Leaf::getText))
    ;
  pybind11::class_<sem::CmdCaption, sem::SemId<sem::CmdCaption>, sem::Attached>(m, "CmdCaption")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::CmdCaption {
                        sem::CmdCaption result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("text", &sem::CmdCaption::text, R"RAW(Content description)RAW")
    .def_readwrite("attrs", &sem::CmdCaption::attrs, R"RAW(Additional parameters aside from 'exporter',)RAW")
    .def_readwrite("attached", &sem::CmdCaption::attached)
    .def("getAttrs",
         static_cast<Vec<sem::AttrValue>(sem::CmdCaption::*)(Opt<Str> const&) const>(&sem::CmdCaption::getAttrs),
         pybind11::arg_v("key", std::nullopt),
         R"RAW(Return all parameters with keys matching name. This is an override implementation that accounts for the explicit command parameters if any.)RAW")
    .def("getFirstAttr",
         static_cast<Opt<sem::AttrValue>(sem::CmdCaption::*)(Str const&) const>(&sem::CmdCaption::getFirstAttr),
         pybind11::arg("kind"),
         R"RAW(Override of the base statement argument get, prioritizing the explicit command parameters)RAW")
    .def("getAttached",
         static_cast<Vec<sem::SemId<sem::Org>>(sem::CmdCaption::*)(Opt<Str> const&) const>(&sem::CmdCaption::getAttached),
         pybind11::arg_v("kind", std::nullopt),
         R"RAW(Return attached nodes of a specific kinds or all attached (if kind is nullopt))RAW")
    .def("getCaption", static_cast<Vec<sem::SemId<sem::Org>>(sem::CmdCaption::*)() const>(&sem::CmdCaption::getCaption))
    .def("getName", static_cast<Vec<Str>(sem::CmdCaption::*)() const>(&sem::CmdCaption::getName))
    .def("getAttrs",
         static_cast<Vec<sem::AttrValue>(sem::CmdCaption::*)(Opt<Str> const&) const>(&sem::CmdCaption::getAttrs),
         pybind11::arg_v("kind", std::nullopt),
         R"RAW(Get all named arguments for the command, across all attached properties. If kind is nullopt returns all attached arguments for all properties.)RAW")
    .def("getFirstAttr",
         static_cast<Opt<sem::AttrValue>(sem::CmdCaption::*)(Str const&) const>(&sem::CmdCaption::getFirstAttr),
         pybind11::arg("kind"),
         R"RAW(Get the first parameter for the statement. In case there is a longer list of values matching given kinddifferent node kinds can implement different priorities )RAW")
    .def("__repr__", [](sem::CmdCaption _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::CmdCaption _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::CmdName, sem::SemId<sem::CmdName>, sem::Attached>(m, "CmdName")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::CmdName {
                        sem::CmdName result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("name", &sem::CmdName::name)
    .def_readwrite("attrs", &sem::CmdName::attrs, R"RAW(Additional parameters aside from 'exporter',)RAW")
    .def_readwrite("attached", &sem::CmdName::attached)
    .def("getAttrs",
         static_cast<Vec<sem::AttrValue>(sem::CmdName::*)(Opt<Str> const&) const>(&sem::CmdName::getAttrs),
         pybind11::arg_v("key", std::nullopt),
         R"RAW(Return all parameters with keys matching name. This is an override implementation that accounts for the explicit command parameters if any.)RAW")
    .def("getFirstAttr",
         static_cast<Opt<sem::AttrValue>(sem::CmdName::*)(Str const&) const>(&sem::CmdName::getFirstAttr),
         pybind11::arg("kind"),
         R"RAW(Override of the base statement argument get, prioritizing the explicit command parameters)RAW")
    .def("getAttached",
         static_cast<Vec<sem::SemId<sem::Org>>(sem::CmdName::*)(Opt<Str> const&) const>(&sem::CmdName::getAttached),
         pybind11::arg_v("kind", std::nullopt),
         R"RAW(Return attached nodes of a specific kinds or all attached (if kind is nullopt))RAW")
    .def("getCaption", static_cast<Vec<sem::SemId<sem::Org>>(sem::CmdName::*)() const>(&sem::CmdName::getCaption))
    .def("getName", static_cast<Vec<Str>(sem::CmdName::*)() const>(&sem::CmdName::getName))
    .def("getAttrs",
         static_cast<Vec<sem::AttrValue>(sem::CmdName::*)(Opt<Str> const&) const>(&sem::CmdName::getAttrs),
         pybind11::arg_v("kind", std::nullopt),
         R"RAW(Get all named arguments for the command, across all attached properties. If kind is nullopt returns all attached arguments for all properties.)RAW")
    .def("getFirstAttr",
         static_cast<Opt<sem::AttrValue>(sem::CmdName::*)(Str const&) const>(&sem::CmdName::getFirstAttr),
         pybind11::arg("kind"),
         R"RAW(Get the first parameter for the statement. In case there is a longer list of values matching given kinddifferent node kinds can implement different priorities )RAW")
    .def("__repr__", [](sem::CmdName _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::CmdName _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::CmdCustomArgs, sem::SemId<sem::CmdCustomArgs>, sem::Cmd>(m, "CmdCustomArgs")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::CmdCustomArgs {
                        sem::CmdCustomArgs result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("name", &sem::CmdCustomArgs::name)
    .def_readwrite("isAttached", &sem::CmdCustomArgs::isAttached)
    .def_readwrite("attrs", &sem::CmdCustomArgs::attrs, R"RAW(Additional parameters aside from 'exporter',)RAW")
    .def_readwrite("attached", &sem::CmdCustomArgs::attached)
    .def("getAttrs",
         static_cast<Vec<sem::AttrValue>(sem::CmdCustomArgs::*)(Opt<Str> const&) const>(&sem::CmdCustomArgs::getAttrs),
         pybind11::arg_v("key", std::nullopt),
         R"RAW(Return all parameters with keys matching name. This is an override implementation that accounts for the explicit command parameters if any.)RAW")
    .def("getFirstAttr",
         static_cast<Opt<sem::AttrValue>(sem::CmdCustomArgs::*)(Str const&) const>(&sem::CmdCustomArgs::getFirstAttr),
         pybind11::arg("kind"),
         R"RAW(Override of the base statement argument get, prioritizing the explicit command parameters)RAW")
    .def("getAttached",
         static_cast<Vec<sem::SemId<sem::Org>>(sem::CmdCustomArgs::*)(Opt<Str> const&) const>(&sem::CmdCustomArgs::getAttached),
         pybind11::arg_v("kind", std::nullopt),
         R"RAW(Return attached nodes of a specific kinds or all attached (if kind is nullopt))RAW")
    .def("getCaption", static_cast<Vec<sem::SemId<sem::Org>>(sem::CmdCustomArgs::*)() const>(&sem::CmdCustomArgs::getCaption))
    .def("getName", static_cast<Vec<Str>(sem::CmdCustomArgs::*)() const>(&sem::CmdCustomArgs::getName))
    .def("getAttrs",
         static_cast<Vec<sem::AttrValue>(sem::CmdCustomArgs::*)(Opt<Str> const&) const>(&sem::CmdCustomArgs::getAttrs),
         pybind11::arg_v("kind", std::nullopt),
         R"RAW(Get all named arguments for the command, across all attached properties. If kind is nullopt returns all attached arguments for all properties.)RAW")
    .def("getFirstAttr",
         static_cast<Opt<sem::AttrValue>(sem::CmdCustomArgs::*)(Str const&) const>(&sem::CmdCustomArgs::getFirstAttr),
         pybind11::arg("kind"),
         R"RAW(Get the first parameter for the statement. In case there is a longer list of values matching given kinddifferent node kinds can implement different priorities )RAW")
    .def("__repr__", [](sem::CmdCustomArgs _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::CmdCustomArgs _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::CmdCustomRaw, sem::SemId<sem::CmdCustomRaw>, sem::Stmt>(m, "CmdCustomRaw")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::CmdCustomRaw {
                        sem::CmdCustomRaw result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("name", &sem::CmdCustomRaw::name)
    .def_readwrite("isAttached", &sem::CmdCustomRaw::isAttached)
    .def_readwrite("text", &sem::CmdCustomRaw::text)
    .def_readwrite("attached", &sem::CmdCustomRaw::attached)
    .def("getAttached",
         static_cast<Vec<sem::SemId<sem::Org>>(sem::CmdCustomRaw::*)(Opt<Str> const&) const>(&sem::CmdCustomRaw::getAttached),
         pybind11::arg_v("kind", std::nullopt),
         R"RAW(Return attached nodes of a specific kinds or all attached (if kind is nullopt))RAW")
    .def("getCaption", static_cast<Vec<sem::SemId<sem::Org>>(sem::CmdCustomRaw::*)() const>(&sem::CmdCustomRaw::getCaption))
    .def("getName", static_cast<Vec<Str>(sem::CmdCustomRaw::*)() const>(&sem::CmdCustomRaw::getName))
    .def("getAttrs",
         static_cast<Vec<sem::AttrValue>(sem::CmdCustomRaw::*)(Opt<Str> const&) const>(&sem::CmdCustomRaw::getAttrs),
         pybind11::arg_v("kind", std::nullopt),
         R"RAW(Get all named arguments for the command, across all attached properties. If kind is nullopt returns all attached arguments for all properties.)RAW")
    .def("getFirstAttr",
         static_cast<Opt<sem::AttrValue>(sem::CmdCustomRaw::*)(Str const&) const>(&sem::CmdCustomRaw::getFirstAttr),
         pybind11::arg("kind"),
         R"RAW(Get the first parameter for the statement. In case there is a longer list of values matching given kinddifferent node kinds can implement different priorities )RAW")
    .def("__repr__", [](sem::CmdCustomRaw _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::CmdCustomRaw _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::CmdCustomText, sem::SemId<sem::CmdCustomText>, sem::Stmt>(m, "CmdCustomText")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::CmdCustomText {
                        sem::CmdCustomText result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("name", &sem::CmdCustomText::name)
    .def_readwrite("isAttached", &sem::CmdCustomText::isAttached)
    .def_readwrite("text", &sem::CmdCustomText::text)
    .def_readwrite("attached", &sem::CmdCustomText::attached)
    .def("getAttached",
         static_cast<Vec<sem::SemId<sem::Org>>(sem::CmdCustomText::*)(Opt<Str> const&) const>(&sem::CmdCustomText::getAttached),
         pybind11::arg_v("kind", std::nullopt),
         R"RAW(Return attached nodes of a specific kinds or all attached (if kind is nullopt))RAW")
    .def("getCaption", static_cast<Vec<sem::SemId<sem::Org>>(sem::CmdCustomText::*)() const>(&sem::CmdCustomText::getCaption))
    .def("getName", static_cast<Vec<Str>(sem::CmdCustomText::*)() const>(&sem::CmdCustomText::getName))
    .def("getAttrs",
         static_cast<Vec<sem::AttrValue>(sem::CmdCustomText::*)(Opt<Str> const&) const>(&sem::CmdCustomText::getAttrs),
         pybind11::arg_v("kind", std::nullopt),
         R"RAW(Get all named arguments for the command, across all attached properties. If kind is nullopt returns all attached arguments for all properties.)RAW")
    .def("getFirstAttr",
         static_cast<Opt<sem::AttrValue>(sem::CmdCustomText::*)(Str const&) const>(&sem::CmdCustomText::getFirstAttr),
         pybind11::arg("kind"),
         R"RAW(Get the first parameter for the statement. In case there is a longer list of values matching given kinddifferent node kinds can implement different priorities )RAW")
    .def("__repr__", [](sem::CmdCustomText _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::CmdCustomText _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::CmdResults, sem::SemId<sem::CmdResults>, sem::Attached>(m, "CmdResults")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::CmdResults {
                        sem::CmdResults result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("attrs", &sem::CmdResults::attrs, R"RAW(Additional parameters aside from 'exporter',)RAW")
    .def_readwrite("attached", &sem::CmdResults::attached)
    .def("getAttrs",
         static_cast<Vec<sem::AttrValue>(sem::CmdResults::*)(Opt<Str> const&) const>(&sem::CmdResults::getAttrs),
         pybind11::arg_v("key", std::nullopt),
         R"RAW(Return all parameters with keys matching name. This is an override implementation that accounts for the explicit command parameters if any.)RAW")
    .def("getFirstAttr",
         static_cast<Opt<sem::AttrValue>(sem::CmdResults::*)(Str const&) const>(&sem::CmdResults::getFirstAttr),
         pybind11::arg("kind"),
         R"RAW(Override of the base statement argument get, prioritizing the explicit command parameters)RAW")
    .def("getAttached",
         static_cast<Vec<sem::SemId<sem::Org>>(sem::CmdResults::*)(Opt<Str> const&) const>(&sem::CmdResults::getAttached),
         pybind11::arg_v("kind", std::nullopt),
         R"RAW(Return attached nodes of a specific kinds or all attached (if kind is nullopt))RAW")
    .def("getCaption", static_cast<Vec<sem::SemId<sem::Org>>(sem::CmdResults::*)() const>(&sem::CmdResults::getCaption))
    .def("getName", static_cast<Vec<Str>(sem::CmdResults::*)() const>(&sem::CmdResults::getName))
    .def("getAttrs",
         static_cast<Vec<sem::AttrValue>(sem::CmdResults::*)(Opt<Str> const&) const>(&sem::CmdResults::getAttrs),
         pybind11::arg_v("kind", std::nullopt),
         R"RAW(Get all named arguments for the command, across all attached properties. If kind is nullopt returns all attached arguments for all properties.)RAW")
    .def("getFirstAttr",
         static_cast<Opt<sem::AttrValue>(sem::CmdResults::*)(Str const&) const>(&sem::CmdResults::getFirstAttr),
         pybind11::arg("kind"),
         R"RAW(Get the first parameter for the statement. In case there is a longer list of values matching given kinddifferent node kinds can implement different priorities )RAW")
    .def("__repr__", [](sem::CmdResults _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::CmdResults _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::CmdTblfm, sem::SemId<sem::CmdTblfm>, sem::Cmd>(m, "CmdTblfm")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::CmdTblfm {
                        sem::CmdTblfm result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("expr", &sem::CmdTblfm::expr)
    .def_readwrite("attrs", &sem::CmdTblfm::attrs, R"RAW(Additional parameters aside from 'exporter',)RAW")
    .def_readwrite("attached", &sem::CmdTblfm::attached)
    .def("getAttrs",
         static_cast<Vec<sem::AttrValue>(sem::CmdTblfm::*)(Opt<Str> const&) const>(&sem::CmdTblfm::getAttrs),
         pybind11::arg_v("key", std::nullopt),
         R"RAW(Return all parameters with keys matching name. This is an override implementation that accounts for the explicit command parameters if any.)RAW")
    .def("getFirstAttr",
         static_cast<Opt<sem::AttrValue>(sem::CmdTblfm::*)(Str const&) const>(&sem::CmdTblfm::getFirstAttr),
         pybind11::arg("kind"),
         R"RAW(Override of the base statement argument get, prioritizing the explicit command parameters)RAW")
    .def("getAttached",
         static_cast<Vec<sem::SemId<sem::Org>>(sem::CmdTblfm::*)(Opt<Str> const&) const>(&sem::CmdTblfm::getAttached),
         pybind11::arg_v("kind", std::nullopt),
         R"RAW(Return attached nodes of a specific kinds or all attached (if kind is nullopt))RAW")
    .def("getCaption", static_cast<Vec<sem::SemId<sem::Org>>(sem::CmdTblfm::*)() const>(&sem::CmdTblfm::getCaption))
    .def("getName", static_cast<Vec<Str>(sem::CmdTblfm::*)() const>(&sem::CmdTblfm::getName))
    .def("getAttrs",
         static_cast<Vec<sem::AttrValue>(sem::CmdTblfm::*)(Opt<Str> const&) const>(&sem::CmdTblfm::getAttrs),
         pybind11::arg_v("kind", std::nullopt),
         R"RAW(Get all named arguments for the command, across all attached properties. If kind is nullopt returns all attached arguments for all properties.)RAW")
    .def("getFirstAttr",
         static_cast<Opt<sem::AttrValue>(sem::CmdTblfm::*)(Str const&) const>(&sem::CmdTblfm::getFirstAttr),
         pybind11::arg("kind"),
         R"RAW(Get the first parameter for the statement. In case there is a longer list of values matching given kinddifferent node kinds can implement different priorities )RAW")
    .def("__repr__", [](sem::CmdTblfm _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::CmdTblfm _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::HashTag, sem::SemId<sem::HashTag>, sem::Inline>(m, "HashTag")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::HashTag {
                        sem::HashTag result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("head", &sem::HashTag::head, R"RAW(Main part of the tag)RAW")
    .def_readwrite("subtags", &sem::HashTag::subtags, R"RAW(List of nested tags)RAW")
    .def("prefixMatch",
         static_cast<bool(sem::HashTag::*)(Vec<Str> const&) const>(&sem::HashTag::prefixMatch),
         pybind11::arg("prefix"),
         R"RAW(Check if list of tag names is a prefix for either of the nested hash tags in this one)RAW")
    .def("getFlatHashes",
         static_cast<Vec<Vec<Str>>(sem::HashTag::*)(bool) const>(&sem::HashTag::getFlatHashes),
         pybind11::arg_v("withIntermediate", true),
         R"RAW(Get flat list of expanded hashtags)RAW")
    .def("__repr__", [](sem::HashTag _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::HashTag _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::InlineFootnote, sem::SemId<sem::InlineFootnote>, sem::Inline>(m, "InlineFootnote")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::InlineFootnote {
                        sem::InlineFootnote result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("tag", &sem::InlineFootnote::tag, R"RAW(Footnote text target name)RAW")
    .def_readwrite("definition", &sem::InlineFootnote::definition, R"RAW(Link to possibly resolved definition)RAW")
    .def("__repr__", [](sem::InlineFootnote _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::InlineFootnote _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  bind_enum_iterator<sem::Time::Repeat::Mode>(m, "TimeRepeatMode", type_registry_guard);
  pybind11::enum_<sem::Time::Repeat::Mode>(m, "TimeRepeatMode")
    .value("None", sem::Time::Repeat::Mode::None, R"RAW(Do not repeat task on completion)RAW")
    .value("Exact", sem::Time::Repeat::Mode::Exact, R"RAW(?)RAW")
    .value("FirstMatch", sem::Time::Repeat::Mode::FirstMatch, R"RAW(Repeat on the first matching day in the future)RAW")
    .value("SameDay", sem::Time::Repeat::Mode::SameDay, R"RAW(Repeat task on the same day next week/month/year)RAW")
    .def("__iter__", [](sem::Time::Repeat::Mode _self) -> PyEnumIterator<sem::Time::Repeat::Mode> {
                     return
                     PyEnumIterator<sem::Time::Repeat::Mode>
                     ();
                     })
    ;
  bind_enum_iterator<sem::Time::Repeat::Period>(m, "TimeRepeatPeriod", type_registry_guard);
  pybind11::enum_<sem::Time::Repeat::Period>(m, "TimeRepeatPeriod")
    .value("Year", sem::Time::Repeat::Period::Year)
    .value("Month", sem::Time::Repeat::Period::Month)
    .value("Week", sem::Time::Repeat::Period::Week)
    .value("Day", sem::Time::Repeat::Period::Day)
    .value("Hour", sem::Time::Repeat::Period::Hour)
    .value("Minute", sem::Time::Repeat::Period::Minute)
    .def("__iter__", [](sem::Time::Repeat::Period _self) -> PyEnumIterator<sem::Time::Repeat::Period> {
                     return
                     PyEnumIterator<sem::Time::Repeat::Period>
                     ();
                     })
    ;
  pybind11::class_<sem::Time::Repeat>(m, "TimeRepeat")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::Time::Repeat {
                        sem::Time::Repeat result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("mode", &sem::Time::Repeat::mode, R"RAW(mode)RAW")
    .def_readwrite("period", &sem::Time::Repeat::period, R"RAW(period)RAW")
    .def_readwrite("count", &sem::Time::Repeat::count, R"RAW(count)RAW")
    .def("__repr__", [](sem::Time::Repeat _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::Time::Repeat _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::Time::Static>(m, "TimeStatic")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::Time::Static {
                        sem::Time::Static result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("repeat", &sem::Time::Static::repeat)
    .def_readwrite("time", &sem::Time::Static::time)
    .def("__repr__", [](sem::Time::Static _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::Time::Static _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::Time::Dynamic>(m, "TimeDynamic")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::Time::Dynamic {
                        sem::Time::Dynamic result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("expr", &sem::Time::Dynamic::expr)
    .def("__repr__", [](sem::Time::Dynamic _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::Time::Dynamic _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  bind_enum_iterator<sem::Time::TimeKind>(m, "TimeTimeKind", type_registry_guard);
  pybind11::enum_<sem::Time::TimeKind>(m, "TimeTimeKind")
    .value("Static", sem::Time::TimeKind::Static)
    .value("Dynamic", sem::Time::TimeKind::Dynamic)
    .def("__iter__", [](sem::Time::TimeKind _self) -> PyEnumIterator<sem::Time::TimeKind> {
                     return
                     PyEnumIterator<sem::Time::TimeKind>
                     ();
                     })
    ;
  pybind11::class_<sem::Time, sem::SemId<sem::Time>, sem::Org>(m, "Time")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::Time {
                        sem::Time result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("isActive", &sem::Time::isActive, R"RAW(<active> vs [inactive])RAW")
    .def_readwrite("time", &sem::Time::time)
    .def("getYear", static_cast<Opt<int>(sem::Time::*)() const>(&sem::Time::getYear))
    .def("getMonth", static_cast<Opt<int>(sem::Time::*)() const>(&sem::Time::getMonth))
    .def("getDay", static_cast<Opt<int>(sem::Time::*)() const>(&sem::Time::getDay))
    .def("getHour", static_cast<Opt<int>(sem::Time::*)() const>(&sem::Time::getHour))
    .def("getMinute", static_cast<Opt<int>(sem::Time::*)() const>(&sem::Time::getMinute))
    .def("getSecond", static_cast<Opt<int>(sem::Time::*)() const>(&sem::Time::getSecond))
    .def("getStaticTime", static_cast<UserTime(sem::Time::*)() const>(&sem::Time::getStaticTime))
    .def("isStatic", static_cast<bool(sem::Time::*)() const>(&sem::Time::isStatic))
    .def("getStatic", static_cast<sem::Time::Static&(sem::Time::*)()>(&sem::Time::getStatic))
    .def("isDynamic", static_cast<bool(sem::Time::*)() const>(&sem::Time::isDynamic))
    .def("getDynamic", static_cast<sem::Time::Dynamic&(sem::Time::*)()>(&sem::Time::getDynamic))
    .def_static("getTimeKindStatic",
                static_cast<sem::Time::TimeKind(*)(sem::Time::TimeVariant const&)>(&sem::Time::getTimeKind),
                pybind11::arg("__input"))
    .def("getTimeKind", static_cast<sem::Time::TimeKind(sem::Time::*)() const>(&sem::Time::getTimeKind))
    .def("__repr__", [](sem::Time _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::Time _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::TimeRange, sem::SemId<sem::TimeRange>, sem::Org>(m, "TimeRange")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::TimeRange {
                        sem::TimeRange result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("from_", &sem::TimeRange::from, R"RAW(Starting time)RAW")
    .def_readwrite("to", &sem::TimeRange::to, R"RAW(Finishing time)RAW")
    .def("__repr__", [](sem::TimeRange _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::TimeRange _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::Macro, sem::SemId<sem::Macro>, sem::Org>(m, "Macro")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::Macro {
                        sem::Macro result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("name", &sem::Macro::name, R"RAW(Macro name)RAW")
    .def_readwrite("attrs", &sem::Macro::attrs, R"RAW(Additional parameters aside from 'exporter',)RAW")
    .def("__repr__", [](sem::Macro _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::Macro _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::Symbol::Param>(m, "SymbolParam")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::Symbol::Param {
                        sem::Symbol::Param result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("key", &sem::Symbol::Param::key, R"RAW(Key -- for non-positional)RAW")
    .def_readwrite("value", &sem::Symbol::Param::value, R"RAW(Uninterpreted value)RAW")
    .def("__repr__", [](sem::Symbol::Param _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::Symbol::Param _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::Symbol, sem::SemId<sem::Symbol>, sem::Org>(m, "Symbol")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::Symbol {
                        sem::Symbol result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("name", &sem::Symbol::name, R"RAW(Name of the symbol)RAW")
    .def_readwrite("parameters", &sem::Symbol::parameters, R"RAW(Optional list of parameters)RAW")
    .def_readwrite("positional", &sem::Symbol::positional, R"RAW(Positional parameters)RAW")
    .def("__repr__", [](sem::Symbol _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::Symbol _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::Escaped, sem::SemId<sem::Escaped>, sem::Leaf>(m, "Escaped")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::Escaped {
                        sem::Escaped result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("text", &sem::Escaped::text, R"RAW(Final leaf value)RAW")
    .def("getText", static_cast<Str(sem::Escaped::*)() const>(&sem::Escaped::getText))
    .def("__repr__", [](sem::Escaped _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::Escaped _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::Newline, sem::SemId<sem::Newline>, sem::Leaf>(m, "Newline")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::Newline {
                        sem::Newline result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("text", &sem::Newline::text, R"RAW(Final leaf value)RAW")
    .def("getText", static_cast<Str(sem::Newline::*)() const>(&sem::Newline::getText))
    .def("__repr__", [](sem::Newline _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::Newline _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::Space, sem::SemId<sem::Space>, sem::Leaf>(m, "Space")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::Space {
                        sem::Space result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("text", &sem::Space::text, R"RAW(Final leaf value)RAW")
    .def("getText", static_cast<Str(sem::Space::*)() const>(&sem::Space::getText))
    .def("__repr__", [](sem::Space _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::Space _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::Word, sem::SemId<sem::Word>, sem::Leaf>(m, "Word")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::Word {
                        sem::Word result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("text", &sem::Word::text, R"RAW(Final leaf value)RAW")
    .def("getText", static_cast<Str(sem::Word::*)() const>(&sem::Word::getText))
    .def("__repr__", [](sem::Word _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::Word _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::AtMention, sem::SemId<sem::AtMention>, sem::Leaf>(m, "AtMention")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::AtMention {
                        sem::AtMention result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("text", &sem::AtMention::text, R"RAW(Final leaf value)RAW")
    .def("getText", static_cast<Str(sem::AtMention::*)() const>(&sem::AtMention::getText))
    .def("__repr__", [](sem::AtMention _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::AtMention _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::RawText, sem::SemId<sem::RawText>, sem::Leaf>(m, "RawText")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::RawText {
                        sem::RawText result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("text", &sem::RawText::text, R"RAW(Final leaf value)RAW")
    .def("getText", static_cast<Str(sem::RawText::*)() const>(&sem::RawText::getText))
    .def("__repr__", [](sem::RawText _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::RawText _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::Punctuation, sem::SemId<sem::Punctuation>, sem::Leaf>(m, "Punctuation")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::Punctuation {
                        sem::Punctuation result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("text", &sem::Punctuation::text, R"RAW(Final leaf value)RAW")
    .def("getText", static_cast<Str(sem::Punctuation::*)() const>(&sem::Punctuation::getText))
    .def("__repr__", [](sem::Punctuation _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::Punctuation _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::Placeholder, sem::SemId<sem::Placeholder>, sem::Leaf>(m, "Placeholder")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::Placeholder {
                        sem::Placeholder result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("text", &sem::Placeholder::text, R"RAW(Final leaf value)RAW")
    .def("getText", static_cast<Str(sem::Placeholder::*)() const>(&sem::Placeholder::getText))
    .def("__repr__", [](sem::Placeholder _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::Placeholder _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::BigIdent, sem::SemId<sem::BigIdent>, sem::Leaf>(m, "BigIdent")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::BigIdent {
                        sem::BigIdent result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("text", &sem::BigIdent::text, R"RAW(Final leaf value)RAW")
    .def("getText", static_cast<Str(sem::BigIdent::*)() const>(&sem::BigIdent::getText))
    .def("__repr__", [](sem::BigIdent _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::BigIdent _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::RadioTarget, sem::SemId<sem::RadioTarget>, sem::Leaf>(m, "RadioTarget")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::RadioTarget {
                        sem::RadioTarget result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("text", &sem::RadioTarget::text, R"RAW(Final leaf value)RAW")
    .def("getText", static_cast<Str(sem::RadioTarget::*)() const>(&sem::RadioTarget::getText))
    .def("__repr__", [](sem::RadioTarget _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::RadioTarget _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::TextTarget, sem::SemId<sem::TextTarget>, sem::Leaf>(m, "TextTarget")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::TextTarget {
                        sem::TextTarget result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("text", &sem::TextTarget::text, R"RAW(Final leaf value)RAW")
    .def("getText", static_cast<Str(sem::TextTarget::*)() const>(&sem::TextTarget::getText))
    .def("__repr__", [](sem::TextTarget _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::TextTarget _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::Markup, sem::SemId<sem::Markup>, sem::Org>(m, "Markup")
    ;
  pybind11::class_<sem::Bold, sem::SemId<sem::Bold>, sem::Markup>(m, "Bold")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::Bold {
                        sem::Bold result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def("__repr__", [](sem::Bold _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::Bold _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::Underline, sem::SemId<sem::Underline>, sem::Markup>(m, "Underline")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::Underline {
                        sem::Underline result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def("__repr__", [](sem::Underline _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::Underline _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::Monospace, sem::SemId<sem::Monospace>, sem::Markup>(m, "Monospace")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::Monospace {
                        sem::Monospace result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def("__repr__", [](sem::Monospace _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::Monospace _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::MarkQuote, sem::SemId<sem::MarkQuote>, sem::Markup>(m, "MarkQuote")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::MarkQuote {
                        sem::MarkQuote result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def("__repr__", [](sem::MarkQuote _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::MarkQuote _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::Verbatim, sem::SemId<sem::Verbatim>, sem::Markup>(m, "Verbatim")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::Verbatim {
                        sem::Verbatim result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def("__repr__", [](sem::Verbatim _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::Verbatim _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::Italic, sem::SemId<sem::Italic>, sem::Markup>(m, "Italic")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::Italic {
                        sem::Italic result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def("__repr__", [](sem::Italic _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::Italic _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::Strike, sem::SemId<sem::Strike>, sem::Markup>(m, "Strike")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::Strike {
                        sem::Strike result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def("__repr__", [](sem::Strike _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::Strike _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::Par, sem::SemId<sem::Par>, sem::Markup>(m, "Par")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::Par {
                        sem::Par result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def("__repr__", [](sem::Par _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::Par _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::Latex, sem::SemId<sem::Latex>, sem::Org>(m, "Latex")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::Latex {
                        sem::Latex result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def("__repr__", [](sem::Latex _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::Latex _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::Link::Raw>(m, "LinkRaw")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::Link::Raw {
                        sem::Link::Raw result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("text", &sem::Link::Raw::text)
    .def("__repr__", [](sem::Link::Raw _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::Link::Raw _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::Link::Id>(m, "LinkId")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::Link::Id {
                        sem::Link::Id result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("text", &sem::Link::Id::text)
    .def("__repr__", [](sem::Link::Id _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::Link::Id _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::Link::Person>(m, "LinkPerson")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::Link::Person {
                        sem::Link::Person result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("name", &sem::Link::Person::name)
    .def("__repr__", [](sem::Link::Person _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::Link::Person _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::Link::UserProtocol>(m, "LinkUserProtocol")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::Link::UserProtocol {
                        sem::Link::UserProtocol result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("protocol", &sem::Link::UserProtocol::protocol)
    .def_readwrite("target", &sem::Link::UserProtocol::target)
    .def("__repr__", [](sem::Link::UserProtocol _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::Link::UserProtocol _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::Link::Internal>(m, "LinkInternal")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::Link::Internal {
                        sem::Link::Internal result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("target", &sem::Link::Internal::target)
    .def("__repr__", [](sem::Link::Internal _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::Link::Internal _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::Link::Footnote>(m, "LinkFootnote")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::Link::Footnote {
                        sem::Link::Footnote result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("target", &sem::Link::Footnote::target)
    .def("__repr__", [](sem::Link::Footnote _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::Link::Footnote _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::Link::File>(m, "LinkFile")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::Link::File {
                        sem::Link::File result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("file", &sem::Link::File::file)
    .def("__repr__", [](sem::Link::File _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::Link::File _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::Link::Attachment>(m, "LinkAttachment")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::Link::Attachment {
                        sem::Link::Attachment result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("file", &sem::Link::Attachment::file)
    .def("__repr__", [](sem::Link::Attachment _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::Link::Attachment _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  bind_enum_iterator<sem::Link::Kind>(m, "LinkKind", type_registry_guard);
  pybind11::enum_<sem::Link::Kind>(m, "LinkKind")
    .value("Raw", sem::Link::Kind::Raw)
    .value("Id", sem::Link::Kind::Id)
    .value("Person", sem::Link::Kind::Person)
    .value("UserProtocol", sem::Link::Kind::UserProtocol)
    .value("Internal", sem::Link::Kind::Internal)
    .value("Footnote", sem::Link::Kind::Footnote)
    .value("File", sem::Link::Kind::File)
    .value("Attachment", sem::Link::Kind::Attachment)
    .def("__iter__", [](sem::Link::Kind _self) -> PyEnumIterator<sem::Link::Kind> {
                     return
                     PyEnumIterator<sem::Link::Kind>
                     ();
                     })
    ;
  pybind11::class_<sem::Link, sem::SemId<sem::Link>, sem::Stmt>(m, "Link")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::Link {
                        sem::Link result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("description", &sem::Link::description)
    .def_readwrite("data", &sem::Link::data)
    .def_readwrite("attached", &sem::Link::attached)
    .def("isRaw", static_cast<bool(sem::Link::*)() const>(&sem::Link::isRaw))
    .def("getRaw", static_cast<sem::Link::Raw&(sem::Link::*)()>(&sem::Link::getRaw))
    .def("isId", static_cast<bool(sem::Link::*)() const>(&sem::Link::isId))
    .def("getId", static_cast<sem::Link::Id&(sem::Link::*)()>(&sem::Link::getId))
    .def("isPerson", static_cast<bool(sem::Link::*)() const>(&sem::Link::isPerson))
    .def("getPerson", static_cast<sem::Link::Person&(sem::Link::*)()>(&sem::Link::getPerson))
    .def("isUserProtocol", static_cast<bool(sem::Link::*)() const>(&sem::Link::isUserProtocol))
    .def("getUserProtocol", static_cast<sem::Link::UserProtocol&(sem::Link::*)()>(&sem::Link::getUserProtocol))
    .def("isInternal", static_cast<bool(sem::Link::*)() const>(&sem::Link::isInternal))
    .def("getInternal", static_cast<sem::Link::Internal&(sem::Link::*)()>(&sem::Link::getInternal))
    .def("isFootnote", static_cast<bool(sem::Link::*)() const>(&sem::Link::isFootnote))
    .def("getFootnote", static_cast<sem::Link::Footnote&(sem::Link::*)()>(&sem::Link::getFootnote))
    .def("isFile", static_cast<bool(sem::Link::*)() const>(&sem::Link::isFile))
    .def("getFile", static_cast<sem::Link::File&(sem::Link::*)()>(&sem::Link::getFile))
    .def("isAttachment", static_cast<bool(sem::Link::*)() const>(&sem::Link::isAttachment))
    .def("getAttachment", static_cast<sem::Link::Attachment&(sem::Link::*)()>(&sem::Link::getAttachment))
    .def_static("getLinkKindStatic",
                static_cast<sem::Link::Kind(*)(sem::Link::Data const&)>(&sem::Link::getLinkKind),
                pybind11::arg("__input"))
    .def("getLinkKind", static_cast<sem::Link::Kind(sem::Link::*)() const>(&sem::Link::getLinkKind))
    .def("getAttached",
         static_cast<Vec<sem::SemId<sem::Org>>(sem::Link::*)(Opt<Str> const&) const>(&sem::Link::getAttached),
         pybind11::arg_v("kind", std::nullopt),
         R"RAW(Return attached nodes of a specific kinds or all attached (if kind is nullopt))RAW")
    .def("getCaption", static_cast<Vec<sem::SemId<sem::Org>>(sem::Link::*)() const>(&sem::Link::getCaption))
    .def("getName", static_cast<Vec<Str>(sem::Link::*)() const>(&sem::Link::getName))
    .def("getAttrs",
         static_cast<Vec<sem::AttrValue>(sem::Link::*)(Opt<Str> const&) const>(&sem::Link::getAttrs),
         pybind11::arg_v("kind", std::nullopt),
         R"RAW(Get all named arguments for the command, across all attached properties. If kind is nullopt returns all attached arguments for all properties.)RAW")
    .def("getFirstAttr",
         static_cast<Opt<sem::AttrValue>(sem::Link::*)(Str const&) const>(&sem::Link::getFirstAttr),
         pybind11::arg("kind"),
         R"RAW(Get the first parameter for the statement. In case there is a longer list of values matching given kinddifferent node kinds can implement different priorities )RAW")
    .def("__repr__", [](sem::Link _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::Link _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::BlockCenter, sem::SemId<sem::BlockCenter>, sem::Block>(m, "BlockCenter")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::BlockCenter {
                        sem::BlockCenter result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("attrs", &sem::BlockCenter::attrs, R"RAW(Additional parameters aside from 'exporter',)RAW")
    .def_readwrite("attached", &sem::BlockCenter::attached)
    .def("getAttrs",
         static_cast<Vec<sem::AttrValue>(sem::BlockCenter::*)(Opt<Str> const&) const>(&sem::BlockCenter::getAttrs),
         pybind11::arg_v("key", std::nullopt),
         R"RAW(Return all parameters with keys matching name. This is an override implementation that accounts for the explicit command parameters if any.)RAW")
    .def("getFirstAttr",
         static_cast<Opt<sem::AttrValue>(sem::BlockCenter::*)(Str const&) const>(&sem::BlockCenter::getFirstAttr),
         pybind11::arg("kind"),
         R"RAW(Override of the base statement argument get, prioritizing the explicit command parameters)RAW")
    .def("getAttached",
         static_cast<Vec<sem::SemId<sem::Org>>(sem::BlockCenter::*)(Opt<Str> const&) const>(&sem::BlockCenter::getAttached),
         pybind11::arg_v("kind", std::nullopt),
         R"RAW(Return attached nodes of a specific kinds or all attached (if kind is nullopt))RAW")
    .def("getCaption", static_cast<Vec<sem::SemId<sem::Org>>(sem::BlockCenter::*)() const>(&sem::BlockCenter::getCaption))
    .def("getName", static_cast<Vec<Str>(sem::BlockCenter::*)() const>(&sem::BlockCenter::getName))
    .def("getAttrs",
         static_cast<Vec<sem::AttrValue>(sem::BlockCenter::*)(Opt<Str> const&) const>(&sem::BlockCenter::getAttrs),
         pybind11::arg_v("kind", std::nullopt),
         R"RAW(Get all named arguments for the command, across all attached properties. If kind is nullopt returns all attached arguments for all properties.)RAW")
    .def("getFirstAttr",
         static_cast<Opt<sem::AttrValue>(sem::BlockCenter::*)(Str const&) const>(&sem::BlockCenter::getFirstAttr),
         pybind11::arg("kind"),
         R"RAW(Get the first parameter for the statement. In case there is a longer list of values matching given kinddifferent node kinds can implement different priorities )RAW")
    .def("__repr__", [](sem::BlockCenter _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::BlockCenter _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::BlockQuote, sem::SemId<sem::BlockQuote>, sem::Block>(m, "BlockQuote")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::BlockQuote {
                        sem::BlockQuote result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("attrs", &sem::BlockQuote::attrs, R"RAW(Additional parameters aside from 'exporter',)RAW")
    .def_readwrite("attached", &sem::BlockQuote::attached)
    .def("getAttrs",
         static_cast<Vec<sem::AttrValue>(sem::BlockQuote::*)(Opt<Str> const&) const>(&sem::BlockQuote::getAttrs),
         pybind11::arg_v("key", std::nullopt),
         R"RAW(Return all parameters with keys matching name. This is an override implementation that accounts for the explicit command parameters if any.)RAW")
    .def("getFirstAttr",
         static_cast<Opt<sem::AttrValue>(sem::BlockQuote::*)(Str const&) const>(&sem::BlockQuote::getFirstAttr),
         pybind11::arg("kind"),
         R"RAW(Override of the base statement argument get, prioritizing the explicit command parameters)RAW")
    .def("getAttached",
         static_cast<Vec<sem::SemId<sem::Org>>(sem::BlockQuote::*)(Opt<Str> const&) const>(&sem::BlockQuote::getAttached),
         pybind11::arg_v("kind", std::nullopt),
         R"RAW(Return attached nodes of a specific kinds or all attached (if kind is nullopt))RAW")
    .def("getCaption", static_cast<Vec<sem::SemId<sem::Org>>(sem::BlockQuote::*)() const>(&sem::BlockQuote::getCaption))
    .def("getName", static_cast<Vec<Str>(sem::BlockQuote::*)() const>(&sem::BlockQuote::getName))
    .def("getAttrs",
         static_cast<Vec<sem::AttrValue>(sem::BlockQuote::*)(Opt<Str> const&) const>(&sem::BlockQuote::getAttrs),
         pybind11::arg_v("kind", std::nullopt),
         R"RAW(Get all named arguments for the command, across all attached properties. If kind is nullopt returns all attached arguments for all properties.)RAW")
    .def("getFirstAttr",
         static_cast<Opt<sem::AttrValue>(sem::BlockQuote::*)(Str const&) const>(&sem::BlockQuote::getFirstAttr),
         pybind11::arg("kind"),
         R"RAW(Get the first parameter for the statement. In case there is a longer list of values matching given kinddifferent node kinds can implement different priorities )RAW")
    .def("__repr__", [](sem::BlockQuote _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::BlockQuote _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::BlockComment, sem::SemId<sem::BlockComment>, sem::Stmt>(m, "BlockComment")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::BlockComment {
                        sem::BlockComment result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("attached", &sem::BlockComment::attached)
    .def("getAttached",
         static_cast<Vec<sem::SemId<sem::Org>>(sem::BlockComment::*)(Opt<Str> const&) const>(&sem::BlockComment::getAttached),
         pybind11::arg_v("kind", std::nullopt),
         R"RAW(Return attached nodes of a specific kinds or all attached (if kind is nullopt))RAW")
    .def("getCaption", static_cast<Vec<sem::SemId<sem::Org>>(sem::BlockComment::*)() const>(&sem::BlockComment::getCaption))
    .def("getName", static_cast<Vec<Str>(sem::BlockComment::*)() const>(&sem::BlockComment::getName))
    .def("getAttrs",
         static_cast<Vec<sem::AttrValue>(sem::BlockComment::*)(Opt<Str> const&) const>(&sem::BlockComment::getAttrs),
         pybind11::arg_v("kind", std::nullopt),
         R"RAW(Get all named arguments for the command, across all attached properties. If kind is nullopt returns all attached arguments for all properties.)RAW")
    .def("getFirstAttr",
         static_cast<Opt<sem::AttrValue>(sem::BlockComment::*)(Str const&) const>(&sem::BlockComment::getFirstAttr),
         pybind11::arg("kind"),
         R"RAW(Get the first parameter for the statement. In case there is a longer list of values matching given kinddifferent node kinds can implement different priorities )RAW")
    .def("__repr__", [](sem::BlockComment _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::BlockComment _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::BlockVerse, sem::SemId<sem::BlockVerse>, sem::Block>(m, "BlockVerse")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::BlockVerse {
                        sem::BlockVerse result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("attrs", &sem::BlockVerse::attrs, R"RAW(Additional parameters aside from 'exporter',)RAW")
    .def_readwrite("attached", &sem::BlockVerse::attached)
    .def("getAttrs",
         static_cast<Vec<sem::AttrValue>(sem::BlockVerse::*)(Opt<Str> const&) const>(&sem::BlockVerse::getAttrs),
         pybind11::arg_v("key", std::nullopt),
         R"RAW(Return all parameters with keys matching name. This is an override implementation that accounts for the explicit command parameters if any.)RAW")
    .def("getFirstAttr",
         static_cast<Opt<sem::AttrValue>(sem::BlockVerse::*)(Str const&) const>(&sem::BlockVerse::getFirstAttr),
         pybind11::arg("kind"),
         R"RAW(Override of the base statement argument get, prioritizing the explicit command parameters)RAW")
    .def("getAttached",
         static_cast<Vec<sem::SemId<sem::Org>>(sem::BlockVerse::*)(Opt<Str> const&) const>(&sem::BlockVerse::getAttached),
         pybind11::arg_v("kind", std::nullopt),
         R"RAW(Return attached nodes of a specific kinds or all attached (if kind is nullopt))RAW")
    .def("getCaption", static_cast<Vec<sem::SemId<sem::Org>>(sem::BlockVerse::*)() const>(&sem::BlockVerse::getCaption))
    .def("getName", static_cast<Vec<Str>(sem::BlockVerse::*)() const>(&sem::BlockVerse::getName))
    .def("getAttrs",
         static_cast<Vec<sem::AttrValue>(sem::BlockVerse::*)(Opt<Str> const&) const>(&sem::BlockVerse::getAttrs),
         pybind11::arg_v("kind", std::nullopt),
         R"RAW(Get all named arguments for the command, across all attached properties. If kind is nullopt returns all attached arguments for all properties.)RAW")
    .def("getFirstAttr",
         static_cast<Opt<sem::AttrValue>(sem::BlockVerse::*)(Str const&) const>(&sem::BlockVerse::getFirstAttr),
         pybind11::arg("kind"),
         R"RAW(Get the first parameter for the statement. In case there is a longer list of values matching given kinddifferent node kinds can implement different priorities )RAW")
    .def("__repr__", [](sem::BlockVerse _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::BlockVerse _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::BlockDynamicFallback, sem::SemId<sem::BlockDynamicFallback>, sem::Block>(m, "BlockDynamicFallback")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::BlockDynamicFallback {
                        sem::BlockDynamicFallback result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("name", &sem::BlockDynamicFallback::name)
    .def_readwrite("attrs", &sem::BlockDynamicFallback::attrs, R"RAW(Additional parameters aside from 'exporter',)RAW")
    .def_readwrite("attached", &sem::BlockDynamicFallback::attached)
    .def("getAttrs",
         static_cast<Vec<sem::AttrValue>(sem::BlockDynamicFallback::*)(Opt<Str> const&) const>(&sem::BlockDynamicFallback::getAttrs),
         pybind11::arg_v("key", std::nullopt),
         R"RAW(Return all parameters with keys matching name. This is an override implementation that accounts for the explicit command parameters if any.)RAW")
    .def("getFirstAttr",
         static_cast<Opt<sem::AttrValue>(sem::BlockDynamicFallback::*)(Str const&) const>(&sem::BlockDynamicFallback::getFirstAttr),
         pybind11::arg("kind"),
         R"RAW(Override of the base statement argument get, prioritizing the explicit command parameters)RAW")
    .def("getAttached",
         static_cast<Vec<sem::SemId<sem::Org>>(sem::BlockDynamicFallback::*)(Opt<Str> const&) const>(&sem::BlockDynamicFallback::getAttached),
         pybind11::arg_v("kind", std::nullopt),
         R"RAW(Return attached nodes of a specific kinds or all attached (if kind is nullopt))RAW")
    .def("getCaption", static_cast<Vec<sem::SemId<sem::Org>>(sem::BlockDynamicFallback::*)() const>(&sem::BlockDynamicFallback::getCaption))
    .def("getName", static_cast<Vec<Str>(sem::BlockDynamicFallback::*)() const>(&sem::BlockDynamicFallback::getName))
    .def("getAttrs",
         static_cast<Vec<sem::AttrValue>(sem::BlockDynamicFallback::*)(Opt<Str> const&) const>(&sem::BlockDynamicFallback::getAttrs),
         pybind11::arg_v("kind", std::nullopt),
         R"RAW(Get all named arguments for the command, across all attached properties. If kind is nullopt returns all attached arguments for all properties.)RAW")
    .def("getFirstAttr",
         static_cast<Opt<sem::AttrValue>(sem::BlockDynamicFallback::*)(Str const&) const>(&sem::BlockDynamicFallback::getFirstAttr),
         pybind11::arg("kind"),
         R"RAW(Get the first parameter for the statement. In case there is a longer list of values matching given kinddifferent node kinds can implement different priorities )RAW")
    .def("__repr__", [](sem::BlockDynamicFallback _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::BlockDynamicFallback _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::BlockExample, sem::SemId<sem::BlockExample>, sem::Block>(m, "BlockExample")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::BlockExample {
                        sem::BlockExample result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("attrs", &sem::BlockExample::attrs, R"RAW(Additional parameters aside from 'exporter',)RAW")
    .def_readwrite("attached", &sem::BlockExample::attached)
    .def("getAttrs",
         static_cast<Vec<sem::AttrValue>(sem::BlockExample::*)(Opt<Str> const&) const>(&sem::BlockExample::getAttrs),
         pybind11::arg_v("key", std::nullopt),
         R"RAW(Return all parameters with keys matching name. This is an override implementation that accounts for the explicit command parameters if any.)RAW")
    .def("getFirstAttr",
         static_cast<Opt<sem::AttrValue>(sem::BlockExample::*)(Str const&) const>(&sem::BlockExample::getFirstAttr),
         pybind11::arg("kind"),
         R"RAW(Override of the base statement argument get, prioritizing the explicit command parameters)RAW")
    .def("getAttached",
         static_cast<Vec<sem::SemId<sem::Org>>(sem::BlockExample::*)(Opt<Str> const&) const>(&sem::BlockExample::getAttached),
         pybind11::arg_v("kind", std::nullopt),
         R"RAW(Return attached nodes of a specific kinds or all attached (if kind is nullopt))RAW")
    .def("getCaption", static_cast<Vec<sem::SemId<sem::Org>>(sem::BlockExample::*)() const>(&sem::BlockExample::getCaption))
    .def("getName", static_cast<Vec<Str>(sem::BlockExample::*)() const>(&sem::BlockExample::getName))
    .def("getAttrs",
         static_cast<Vec<sem::AttrValue>(sem::BlockExample::*)(Opt<Str> const&) const>(&sem::BlockExample::getAttrs),
         pybind11::arg_v("kind", std::nullopt),
         R"RAW(Get all named arguments for the command, across all attached properties. If kind is nullopt returns all attached arguments for all properties.)RAW")
    .def("getFirstAttr",
         static_cast<Opt<sem::AttrValue>(sem::BlockExample::*)(Str const&) const>(&sem::BlockExample::getFirstAttr),
         pybind11::arg("kind"),
         R"RAW(Get the first parameter for the statement. In case there is a longer list of values matching given kinddifferent node kinds can implement different priorities )RAW")
    .def("__repr__", [](sem::BlockExample _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::BlockExample _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  bind_enum_iterator<sem::BlockExport::Format>(m, "BlockExportFormat", type_registry_guard);
  pybind11::enum_<sem::BlockExport::Format>(m, "BlockExportFormat")
    .value("Inline", sem::BlockExport::Format::Inline, R"RAW(Export directly in the paragraph)RAW")
    .value("Line", sem::BlockExport::Format::Line, R"RAW(Single line of export)RAW")
    .value("Block", sem::BlockExport::Format::Block, R"RAW(Multiple lines of export)RAW")
    .def("__iter__", [](sem::BlockExport::Format _self) -> PyEnumIterator<sem::BlockExport::Format> {
                     return
                     PyEnumIterator<sem::BlockExport::Format>
                     ();
                     })
    ;
  pybind11::class_<sem::BlockExport, sem::SemId<sem::BlockExport>, sem::Block>(m, "BlockExport")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::BlockExport {
                        sem::BlockExport result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("format", &sem::BlockExport::format, R"RAW(Export block type)RAW")
    .def_readwrite("exporter", &sem::BlockExport::exporter, R"RAW(Exporter backend name)RAW")
    .def_readwrite("placement", &sem::BlockExport::placement, R"RAW(Customized position of the text in the final exporting document.)RAW")
    .def_readwrite("content", &sem::BlockExport::content, R"RAW(Raw exporter content string)RAW")
    .def_readwrite("attrs", &sem::BlockExport::attrs, R"RAW(Additional parameters aside from 'exporter',)RAW")
    .def_readwrite("attached", &sem::BlockExport::attached)
    .def("getAttrs",
         static_cast<Vec<sem::AttrValue>(sem::BlockExport::*)(Opt<Str> const&) const>(&sem::BlockExport::getAttrs),
         pybind11::arg_v("key", std::nullopt),
         R"RAW(Return all parameters with keys matching name. This is an override implementation that accounts for the explicit command parameters if any.)RAW")
    .def("getFirstAttr",
         static_cast<Opt<sem::AttrValue>(sem::BlockExport::*)(Str const&) const>(&sem::BlockExport::getFirstAttr),
         pybind11::arg("kind"),
         R"RAW(Override of the base statement argument get, prioritizing the explicit command parameters)RAW")
    .def("getAttached",
         static_cast<Vec<sem::SemId<sem::Org>>(sem::BlockExport::*)(Opt<Str> const&) const>(&sem::BlockExport::getAttached),
         pybind11::arg_v("kind", std::nullopt),
         R"RAW(Return attached nodes of a specific kinds or all attached (if kind is nullopt))RAW")
    .def("getCaption", static_cast<Vec<sem::SemId<sem::Org>>(sem::BlockExport::*)() const>(&sem::BlockExport::getCaption))
    .def("getName", static_cast<Vec<Str>(sem::BlockExport::*)() const>(&sem::BlockExport::getName))
    .def("getAttrs",
         static_cast<Vec<sem::AttrValue>(sem::BlockExport::*)(Opt<Str> const&) const>(&sem::BlockExport::getAttrs),
         pybind11::arg_v("kind", std::nullopt),
         R"RAW(Get all named arguments for the command, across all attached properties. If kind is nullopt returns all attached arguments for all properties.)RAW")
    .def("getFirstAttr",
         static_cast<Opt<sem::AttrValue>(sem::BlockExport::*)(Str const&) const>(&sem::BlockExport::getFirstAttr),
         pybind11::arg("kind"),
         R"RAW(Get the first parameter for the statement. In case there is a longer list of values matching given kinddifferent node kinds can implement different priorities )RAW")
    .def("__repr__", [](sem::BlockExport _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::BlockExport _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::BlockAdmonition, sem::SemId<sem::BlockAdmonition>, sem::Block>(m, "BlockAdmonition")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::BlockAdmonition {
                        sem::BlockAdmonition result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("attrs", &sem::BlockAdmonition::attrs, R"RAW(Additional parameters aside from 'exporter',)RAW")
    .def_readwrite("attached", &sem::BlockAdmonition::attached)
    .def("getAttrs",
         static_cast<Vec<sem::AttrValue>(sem::BlockAdmonition::*)(Opt<Str> const&) const>(&sem::BlockAdmonition::getAttrs),
         pybind11::arg_v("key", std::nullopt),
         R"RAW(Return all parameters with keys matching name. This is an override implementation that accounts for the explicit command parameters if any.)RAW")
    .def("getFirstAttr",
         static_cast<Opt<sem::AttrValue>(sem::BlockAdmonition::*)(Str const&) const>(&sem::BlockAdmonition::getFirstAttr),
         pybind11::arg("kind"),
         R"RAW(Override of the base statement argument get, prioritizing the explicit command parameters)RAW")
    .def("getAttached",
         static_cast<Vec<sem::SemId<sem::Org>>(sem::BlockAdmonition::*)(Opt<Str> const&) const>(&sem::BlockAdmonition::getAttached),
         pybind11::arg_v("kind", std::nullopt),
         R"RAW(Return attached nodes of a specific kinds or all attached (if kind is nullopt))RAW")
    .def("getCaption", static_cast<Vec<sem::SemId<sem::Org>>(sem::BlockAdmonition::*)() const>(&sem::BlockAdmonition::getCaption))
    .def("getName", static_cast<Vec<Str>(sem::BlockAdmonition::*)() const>(&sem::BlockAdmonition::getName))
    .def("getAttrs",
         static_cast<Vec<sem::AttrValue>(sem::BlockAdmonition::*)(Opt<Str> const&) const>(&sem::BlockAdmonition::getAttrs),
         pybind11::arg_v("kind", std::nullopt),
         R"RAW(Get all named arguments for the command, across all attached properties. If kind is nullopt returns all attached arguments for all properties.)RAW")
    .def("getFirstAttr",
         static_cast<Opt<sem::AttrValue>(sem::BlockAdmonition::*)(Str const&) const>(&sem::BlockAdmonition::getFirstAttr),
         pybind11::arg("kind"),
         R"RAW(Get the first parameter for the statement. In case there is a longer list of values matching given kinddifferent node kinds can implement different priorities )RAW")
    .def("__repr__", [](sem::BlockAdmonition _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::BlockAdmonition _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::BlockCode, sem::SemId<sem::BlockCode>, sem::Block>(m, "BlockCode")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::BlockCode {
                        sem::BlockCode result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("lang", &sem::BlockCode::lang, R"RAW(Code block language name)RAW")
    .def_readwrite("switches", &sem::BlockCode::switches, R"RAW(Switch options for block)RAW")
    .def_readwrite("exports", &sem::BlockCode::exports, R"RAW(What to export)RAW")
    .def_readwrite("result", &sem::BlockCode::result, R"RAW(Code evaluation results)RAW")
    .def_readwrite("lines", &sem::BlockCode::lines, R"RAW(Collected code lines)RAW")
    .def_readwrite("cache", &sem::BlockCode::cache, R"RAW(Do cache values?)RAW")
    .def_readwrite("eval", &sem::BlockCode::eval, R"RAW(Eval on export?)RAW")
    .def_readwrite("noweb", &sem::BlockCode::noweb, R"RAW(Web-tangle code on export/run)RAW")
    .def_readwrite("hlines", &sem::BlockCode::hlines, R"RAW(?)RAW")
    .def_readwrite("tangle", &sem::BlockCode::tangle, R"RAW(?)RAW")
    .def_readwrite("attrs", &sem::BlockCode::attrs, R"RAW(Additional parameters aside from 'exporter',)RAW")
    .def_readwrite("attached", &sem::BlockCode::attached)
    .def("getAttrs",
         static_cast<Vec<sem::AttrValue>(sem::BlockCode::*)(Opt<Str> const&) const>(&sem::BlockCode::getAttrs),
         pybind11::arg_v("key", std::nullopt),
         R"RAW(Return all parameters with keys matching name. This is an override implementation that accounts for the explicit command parameters if any.)RAW")
    .def("getFirstAttr",
         static_cast<Opt<sem::AttrValue>(sem::BlockCode::*)(Str const&) const>(&sem::BlockCode::getFirstAttr),
         pybind11::arg("kind"),
         R"RAW(Override of the base statement argument get, prioritizing the explicit command parameters)RAW")
    .def("getAttached",
         static_cast<Vec<sem::SemId<sem::Org>>(sem::BlockCode::*)(Opt<Str> const&) const>(&sem::BlockCode::getAttached),
         pybind11::arg_v("kind", std::nullopt),
         R"RAW(Return attached nodes of a specific kinds or all attached (if kind is nullopt))RAW")
    .def("getCaption", static_cast<Vec<sem::SemId<sem::Org>>(sem::BlockCode::*)() const>(&sem::BlockCode::getCaption))
    .def("getName", static_cast<Vec<Str>(sem::BlockCode::*)() const>(&sem::BlockCode::getName))
    .def("getAttrs",
         static_cast<Vec<sem::AttrValue>(sem::BlockCode::*)(Opt<Str> const&) const>(&sem::BlockCode::getAttrs),
         pybind11::arg_v("kind", std::nullopt),
         R"RAW(Get all named arguments for the command, across all attached properties. If kind is nullopt returns all attached arguments for all properties.)RAW")
    .def("getFirstAttr",
         static_cast<Opt<sem::AttrValue>(sem::BlockCode::*)(Str const&) const>(&sem::BlockCode::getFirstAttr),
         pybind11::arg("kind"),
         R"RAW(Get the first parameter for the statement. In case there is a longer list of values matching given kinddifferent node kinds can implement different priorities )RAW")
    .def("__repr__", [](sem::BlockCode _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::BlockCode _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::SubtreeLog::DescribedLog>(m, "SubtreeLogDescribedLog")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::SubtreeLog::DescribedLog {
                        sem::SubtreeLog::DescribedLog result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("desc", &sem::SubtreeLog::DescribedLog::desc, R"RAW(Optional description of the log entry)RAW")
    .def("__repr__", [](sem::SubtreeLog::DescribedLog _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::SubtreeLog::DescribedLog _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  bind_enum_iterator<sem::SubtreeLog::Priority::Action>(m, "SubtreeLogPriorityAction", type_registry_guard);
  pybind11::enum_<sem::SubtreeLog::Priority::Action>(m, "SubtreeLogPriorityAction")
    .value("Added", sem::SubtreeLog::Priority::Action::Added, R"RAW(`Priority B added on [timestamp]`)RAW")
    .value("Removed", sem::SubtreeLog::Priority::Action::Removed, R"RAW(`Priority C removed on [timestamp]`)RAW")
    .value("Changed", sem::SubtreeLog::Priority::Action::Changed, R"RAW(`Priority B changed from C on [timestamp]`)RAW")
    .def("__iter__", [](sem::SubtreeLog::Priority::Action _self) -> PyEnumIterator<sem::SubtreeLog::Priority::Action> {
                     return
                     PyEnumIterator<sem::SubtreeLog::Priority::Action>
                     ();
                     })
    ;
  pybind11::class_<sem::SubtreeLog::Priority, sem::SubtreeLog::DescribedLog>(m, "SubtreeLogPriority")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::SubtreeLog::Priority {
                        sem::SubtreeLog::Priority result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("oldPriority", &sem::SubtreeLog::Priority::oldPriority, R"RAW(Previous priority for change and removal)RAW")
    .def_readwrite("newPriority", &sem::SubtreeLog::Priority::newPriority, R"RAW(New priority for change and addition)RAW")
    .def_readwrite("on", &sem::SubtreeLog::Priority::on, R"RAW(When priority was changed)RAW")
    .def_readwrite("action", &sem::SubtreeLog::Priority::action, R"RAW(Which action taken)RAW")
    .def("__repr__", [](sem::SubtreeLog::Priority _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::SubtreeLog::Priority _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::SubtreeLog::Note, sem::SubtreeLog::DescribedLog>(m, "SubtreeLogNote")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::SubtreeLog::Note {
                        sem::SubtreeLog::Note result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("on", &sem::SubtreeLog::Note::on, R"RAW(Where log was taken)RAW")
    .def("__repr__", [](sem::SubtreeLog::Note _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::SubtreeLog::Note _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::SubtreeLog::Refile, sem::SubtreeLog::DescribedLog>(m, "SubtreeLogRefile")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::SubtreeLog::Refile {
                        sem::SubtreeLog::Refile result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("on", &sem::SubtreeLog::Refile::on, R"RAW(When the refiling happened)RAW")
    .def_readwrite("from_", &sem::SubtreeLog::Refile::from, R"RAW(Link to the original subtree)RAW")
    .def("__repr__", [](sem::SubtreeLog::Refile _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::SubtreeLog::Refile _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::SubtreeLog::Clock, sem::SubtreeLog::DescribedLog>(m, "SubtreeLogClock")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::SubtreeLog::Clock {
                        sem::SubtreeLog::Clock result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("from_", &sem::SubtreeLog::Clock::from, R"RAW(Clock start time)RAW")
    .def_readwrite("to", &sem::SubtreeLog::Clock::to, R"RAW(Optional end of the clock)RAW")
    .def("__repr__", [](sem::SubtreeLog::Clock _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::SubtreeLog::Clock _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::SubtreeLog::State, sem::SubtreeLog::DescribedLog>(m, "SubtreeLogState")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::SubtreeLog::State {
                        sem::SubtreeLog::State result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("from_", &sem::SubtreeLog::State::from)
    .def_readwrite("to", &sem::SubtreeLog::State::to)
    .def_readwrite("on", &sem::SubtreeLog::State::on)
    .def("__repr__", [](sem::SubtreeLog::State _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::SubtreeLog::State _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::SubtreeLog::Tag, sem::SubtreeLog::DescribedLog>(m, "SubtreeLogTag")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::SubtreeLog::Tag {
                        sem::SubtreeLog::Tag result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("on", &sem::SubtreeLog::Tag::on, R"RAW(When the log was assigned)RAW")
    .def_readwrite("tag", &sem::SubtreeLog::Tag::tag, R"RAW(Tag in question)RAW")
    .def_readwrite("added", &sem::SubtreeLog::Tag::added, R"RAW(Added/removed?)RAW")
    .def("__repr__", [](sem::SubtreeLog::Tag _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::SubtreeLog::Tag _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::SubtreeLog::Unknown, sem::SubtreeLog::DescribedLog>(m, "SubtreeLogUnknown")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::SubtreeLog::Unknown {
                        sem::SubtreeLog::Unknown result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def("__repr__", [](sem::SubtreeLog::Unknown _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::SubtreeLog::Unknown _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  bind_enum_iterator<sem::SubtreeLog::Kind>(m, "SubtreeLogKind", type_registry_guard);
  pybind11::enum_<sem::SubtreeLog::Kind>(m, "SubtreeLogKind")
    .value("Priority", sem::SubtreeLog::Kind::Priority)
    .value("Note", sem::SubtreeLog::Kind::Note)
    .value("Refile", sem::SubtreeLog::Kind::Refile)
    .value("Clock", sem::SubtreeLog::Kind::Clock)
    .value("State", sem::SubtreeLog::Kind::State)
    .value("Tag", sem::SubtreeLog::Kind::Tag)
    .value("Unknown", sem::SubtreeLog::Kind::Unknown)
    .def("__iter__", [](sem::SubtreeLog::Kind _self) -> PyEnumIterator<sem::SubtreeLog::Kind> {
                     return
                     PyEnumIterator<sem::SubtreeLog::Kind>
                     ();
                     })
    ;
  pybind11::class_<sem::SubtreeLog, sem::SemId<sem::SubtreeLog>, sem::Org>(m, "SubtreeLog")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::SubtreeLog {
                        sem::SubtreeLog result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("log", &sem::SubtreeLog::log)
    .def("setDescription",
         static_cast<void(sem::SubtreeLog::*)(sem::SemId<sem::StmtList>)>(&sem::SubtreeLog::setDescription),
         pybind11::arg("desc"))
    .def("isPriority", static_cast<bool(sem::SubtreeLog::*)() const>(&sem::SubtreeLog::isPriority))
    .def("getPriority", static_cast<sem::SubtreeLog::Priority&(sem::SubtreeLog::*)()>(&sem::SubtreeLog::getPriority))
    .def("isNote", static_cast<bool(sem::SubtreeLog::*)() const>(&sem::SubtreeLog::isNote))
    .def("getNote", static_cast<sem::SubtreeLog::Note&(sem::SubtreeLog::*)()>(&sem::SubtreeLog::getNote))
    .def("isRefile", static_cast<bool(sem::SubtreeLog::*)() const>(&sem::SubtreeLog::isRefile))
    .def("getRefile", static_cast<sem::SubtreeLog::Refile&(sem::SubtreeLog::*)()>(&sem::SubtreeLog::getRefile))
    .def("isClock", static_cast<bool(sem::SubtreeLog::*)() const>(&sem::SubtreeLog::isClock))
    .def("getClock", static_cast<sem::SubtreeLog::Clock&(sem::SubtreeLog::*)()>(&sem::SubtreeLog::getClock))
    .def("isState", static_cast<bool(sem::SubtreeLog::*)() const>(&sem::SubtreeLog::isState))
    .def("getState", static_cast<sem::SubtreeLog::State&(sem::SubtreeLog::*)()>(&sem::SubtreeLog::getState))
    .def("isTag", static_cast<bool(sem::SubtreeLog::*)() const>(&sem::SubtreeLog::isTag))
    .def("getTag", static_cast<sem::SubtreeLog::Tag&(sem::SubtreeLog::*)()>(&sem::SubtreeLog::getTag))
    .def("isUnknown", static_cast<bool(sem::SubtreeLog::*)() const>(&sem::SubtreeLog::isUnknown))
    .def("getUnknown", static_cast<sem::SubtreeLog::Unknown&(sem::SubtreeLog::*)()>(&sem::SubtreeLog::getUnknown))
    .def_static("getLogKindStatic",
                static_cast<sem::SubtreeLog::Kind(*)(sem::SubtreeLog::LogEntry const&)>(&sem::SubtreeLog::getLogKind),
                pybind11::arg("__input"))
    .def("getLogKind", static_cast<sem::SubtreeLog::Kind(sem::SubtreeLog::*)() const>(&sem::SubtreeLog::getLogKind))
    .def("__repr__", [](sem::SubtreeLog _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::SubtreeLog _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::Subtree, sem::SemId<sem::Subtree>, sem::Org>(m, "Subtree")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::Subtree {
                        sem::Subtree result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("level", &sem::Subtree::level, R"RAW(Subtree level)RAW")
    .def_readwrite("treeId", &sem::Subtree::treeId, R"RAW(:ID: property)RAW")
    .def_readwrite("todo", &sem::Subtree::todo, R"RAW(Todo state of the tree)RAW")
    .def_readwrite("completion", &sem::Subtree::completion, R"RAW(Task completion state)RAW")
    .def_readwrite("description", &sem::Subtree::description)
    .def_readwrite("tags", &sem::Subtree::tags, R"RAW(Trailing tags)RAW")
    .def_readwrite("title", &sem::Subtree::title, R"RAW(Main title)RAW")
    .def_readwrite("logbook", &sem::Subtree::logbook, R"RAW(Associated subtree log)RAW")
    .def_readwrite("properties", &sem::Subtree::properties, R"RAW(Immediate properties)RAW")
    .def_readwrite("closed", &sem::Subtree::closed, R"RAW(When subtree was marked as closed)RAW")
    .def_readwrite("deadline", &sem::Subtree::deadline, R"RAW(When is the deadline)RAW")
    .def_readwrite("scheduled", &sem::Subtree::scheduled, R"RAW(When the event is scheduled)RAW")
    .def_readwrite("isComment", &sem::Subtree::isComment, R"RAW(Subtree is annotated with the COMMENT keyword)RAW")
    .def_readwrite("isArchived", &sem::Subtree::isArchived, R"RAW(Subtree is tagged with `:ARCHIVE:` tag)RAW")
    .def_readwrite("priority", &sem::Subtree::priority)
    .def("getTimePeriods",
         static_cast<Vec<sem::SubtreePeriod>(sem::Subtree::*)(IntSet<sem::SubtreePeriod::Kind>) const>(&sem::Subtree::getTimePeriods),
         pybind11::arg("kinds"))
    .def("getProperties",
         static_cast<Vec<sem::NamedProperty>(sem::Subtree::*)(Str const&, Opt<Str> const&) const>(&sem::Subtree::getProperties),
         pybind11::arg("kind"),
         pybind11::arg_v("subkind", std::nullopt))
    .def("getProperty",
         static_cast<Opt<sem::NamedProperty>(sem::Subtree::*)(Str const&, Opt<Str> const&) const>(&sem::Subtree::getProperty),
         pybind11::arg("kind"),
         pybind11::arg_v("subkind", std::nullopt))
    .def("removeProperty",
         static_cast<void(sem::Subtree::*)(Str const&, Opt<Str> const&)>(&sem::Subtree::removeProperty),
         pybind11::arg("kind"),
         pybind11::arg_v("subkind", std::nullopt),
         R"RAW(Remove all instances of the property with matching kind/subkind from the property list)RAW")
    .def("setProperty",
         static_cast<void(sem::Subtree::*)(sem::NamedProperty const&)>(&sem::Subtree::setProperty),
         pybind11::arg("value"),
         R"RAW(Create or override existing property value in the subtree property list)RAW")
    .def("setPropertyStrValue",
         static_cast<void(sem::Subtree::*)(Str const&, Str const&, Opt<Str> const&)>(&sem::Subtree::setPropertyStrValue),
         pybind11::arg("value"),
         pybind11::arg("kind"),
         pybind11::arg_v("subkind", std::nullopt),
         R"RAW(Assign a raw string literal to a property.)RAW")
    .def("__repr__", [](sem::Subtree _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::Subtree _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::SubtreeCompletion, sem::SemId<sem::SubtreeCompletion>, sem::Inline>(m, "SubtreeCompletion")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::SubtreeCompletion {
                        sem::SubtreeCompletion result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("done", &sem::SubtreeCompletion::done, R"RAW(Number of completed tasks)RAW")
    .def_readwrite("full", &sem::SubtreeCompletion::full, R"RAW(Full number of tasks)RAW")
    .def_readwrite("isPercent", &sem::SubtreeCompletion::isPercent, R"RAW(Use fraction or percent to display completion)RAW")
    .def("__repr__", [](sem::SubtreeCompletion _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::SubtreeCompletion _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::Cell, sem::SemId<sem::Cell>, sem::Cmd>(m, "Cell")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::Cell {
                        sem::Cell result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("isBlock", &sem::Cell::isBlock, R"RAW(Single-line pipe cell or `#+cell:` command)RAW")
    .def_readwrite("attrs", &sem::Cell::attrs, R"RAW(Additional parameters aside from 'exporter',)RAW")
    .def_readwrite("attached", &sem::Cell::attached)
    .def("getAttrs",
         static_cast<Vec<sem::AttrValue>(sem::Cell::*)(Opt<Str> const&) const>(&sem::Cell::getAttrs),
         pybind11::arg_v("key", std::nullopt),
         R"RAW(Return all parameters with keys matching name. This is an override implementation that accounts for the explicit command parameters if any.)RAW")
    .def("getFirstAttr",
         static_cast<Opt<sem::AttrValue>(sem::Cell::*)(Str const&) const>(&sem::Cell::getFirstAttr),
         pybind11::arg("kind"),
         R"RAW(Override of the base statement argument get, prioritizing the explicit command parameters)RAW")
    .def("getAttached",
         static_cast<Vec<sem::SemId<sem::Org>>(sem::Cell::*)(Opt<Str> const&) const>(&sem::Cell::getAttached),
         pybind11::arg_v("kind", std::nullopt),
         R"RAW(Return attached nodes of a specific kinds or all attached (if kind is nullopt))RAW")
    .def("getCaption", static_cast<Vec<sem::SemId<sem::Org>>(sem::Cell::*)() const>(&sem::Cell::getCaption))
    .def("getName", static_cast<Vec<Str>(sem::Cell::*)() const>(&sem::Cell::getName))
    .def("getAttrs",
         static_cast<Vec<sem::AttrValue>(sem::Cell::*)(Opt<Str> const&) const>(&sem::Cell::getAttrs),
         pybind11::arg_v("kind", std::nullopt),
         R"RAW(Get all named arguments for the command, across all attached properties. If kind is nullopt returns all attached arguments for all properties.)RAW")
    .def("getFirstAttr",
         static_cast<Opt<sem::AttrValue>(sem::Cell::*)(Str const&) const>(&sem::Cell::getFirstAttr),
         pybind11::arg("kind"),
         R"RAW(Get the first parameter for the statement. In case there is a longer list of values matching given kinddifferent node kinds can implement different priorities )RAW")
    .def("__repr__", [](sem::Cell _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::Cell _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::Row, sem::SemId<sem::Row>, sem::Cmd>(m, "Row")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::Row {
                        sem::Row result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("cells", &sem::Row::cells, R"RAW(List of cells on the row)RAW")
    .def_readwrite("isBlock", &sem::Row::isBlock, R"RAW(Single-line pipe cell or `#+cell:` command)RAW")
    .def_readwrite("attrs", &sem::Row::attrs, R"RAW(Additional parameters aside from 'exporter',)RAW")
    .def_readwrite("attached", &sem::Row::attached)
    .def("getAttrs",
         static_cast<Vec<sem::AttrValue>(sem::Row::*)(Opt<Str> const&) const>(&sem::Row::getAttrs),
         pybind11::arg_v("key", std::nullopt),
         R"RAW(Return all parameters with keys matching name. This is an override implementation that accounts for the explicit command parameters if any.)RAW")
    .def("getFirstAttr",
         static_cast<Opt<sem::AttrValue>(sem::Row::*)(Str const&) const>(&sem::Row::getFirstAttr),
         pybind11::arg("kind"),
         R"RAW(Override of the base statement argument get, prioritizing the explicit command parameters)RAW")
    .def("getAttached",
         static_cast<Vec<sem::SemId<sem::Org>>(sem::Row::*)(Opt<Str> const&) const>(&sem::Row::getAttached),
         pybind11::arg_v("kind", std::nullopt),
         R"RAW(Return attached nodes of a specific kinds or all attached (if kind is nullopt))RAW")
    .def("getCaption", static_cast<Vec<sem::SemId<sem::Org>>(sem::Row::*)() const>(&sem::Row::getCaption))
    .def("getName", static_cast<Vec<Str>(sem::Row::*)() const>(&sem::Row::getName))
    .def("getAttrs",
         static_cast<Vec<sem::AttrValue>(sem::Row::*)(Opt<Str> const&) const>(&sem::Row::getAttrs),
         pybind11::arg_v("kind", std::nullopt),
         R"RAW(Get all named arguments for the command, across all attached properties. If kind is nullopt returns all attached arguments for all properties.)RAW")
    .def("getFirstAttr",
         static_cast<Opt<sem::AttrValue>(sem::Row::*)(Str const&) const>(&sem::Row::getFirstAttr),
         pybind11::arg("kind"),
         R"RAW(Get the first parameter for the statement. In case there is a longer list of values matching given kinddifferent node kinds can implement different priorities )RAW")
    .def("__repr__", [](sem::Row _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::Row _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::Table, sem::SemId<sem::Table>, sem::Block>(m, "Table")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::Table {
                        sem::Table result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("rows", &sem::Table::rows, R"RAW(List of rows for the table)RAW")
    .def_readwrite("isBlock", &sem::Table::isBlock, R"RAW(Single-line pipe cell or `#+cell:` command)RAW")
    .def_readwrite("attrs", &sem::Table::attrs, R"RAW(Additional parameters aside from 'exporter',)RAW")
    .def_readwrite("attached", &sem::Table::attached)
    .def("getAttrs",
         static_cast<Vec<sem::AttrValue>(sem::Table::*)(Opt<Str> const&) const>(&sem::Table::getAttrs),
         pybind11::arg_v("key", std::nullopt),
         R"RAW(Return all parameters with keys matching name. This is an override implementation that accounts for the explicit command parameters if any.)RAW")
    .def("getFirstAttr",
         static_cast<Opt<sem::AttrValue>(sem::Table::*)(Str const&) const>(&sem::Table::getFirstAttr),
         pybind11::arg("kind"),
         R"RAW(Override of the base statement argument get, prioritizing the explicit command parameters)RAW")
    .def("getAttached",
         static_cast<Vec<sem::SemId<sem::Org>>(sem::Table::*)(Opt<Str> const&) const>(&sem::Table::getAttached),
         pybind11::arg_v("kind", std::nullopt),
         R"RAW(Return attached nodes of a specific kinds or all attached (if kind is nullopt))RAW")
    .def("getCaption", static_cast<Vec<sem::SemId<sem::Org>>(sem::Table::*)() const>(&sem::Table::getCaption))
    .def("getName", static_cast<Vec<Str>(sem::Table::*)() const>(&sem::Table::getName))
    .def("getAttrs",
         static_cast<Vec<sem::AttrValue>(sem::Table::*)(Opt<Str> const&) const>(&sem::Table::getAttrs),
         pybind11::arg_v("kind", std::nullopt),
         R"RAW(Get all named arguments for the command, across all attached properties. If kind is nullopt returns all attached arguments for all properties.)RAW")
    .def("getFirstAttr",
         static_cast<Opt<sem::AttrValue>(sem::Table::*)(Str const&) const>(&sem::Table::getFirstAttr),
         pybind11::arg("kind"),
         R"RAW(Get the first parameter for the statement. In case there is a longer list of values matching given kinddifferent node kinds can implement different priorities )RAW")
    .def("__repr__", [](sem::Table _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::Table _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::Paragraph, sem::SemId<sem::Paragraph>, sem::Stmt>(m, "Paragraph")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::Paragraph {
                        sem::Paragraph result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("attached", &sem::Paragraph::attached)
    .def("isFootnoteDefinition", static_cast<bool(sem::Paragraph::*)() const>(&sem::Paragraph::isFootnoteDefinition))
    .def("getFootnoteName", static_cast<Opt<Str>(sem::Paragraph::*)() const>(&sem::Paragraph::getFootnoteName))
    .def("hasAdmonition", static_cast<bool(sem::Paragraph::*)() const>(&sem::Paragraph::hasAdmonition))
    .def("getAdmonitions", static_cast<Vec<Str>(sem::Paragraph::*)() const>(&sem::Paragraph::getAdmonitions))
    .def("getAdmonitionNodes", static_cast<Vec<sem::SemId<sem::BigIdent>>(sem::Paragraph::*)() const>(&sem::Paragraph::getAdmonitionNodes))
    .def("hasTimestamp", static_cast<bool(sem::Paragraph::*)() const>(&sem::Paragraph::hasTimestamp))
    .def("getTimestamps", static_cast<Vec<UserTime>(sem::Paragraph::*)() const>(&sem::Paragraph::getTimestamps))
    .def("getTimestampNodes", static_cast<Vec<sem::SemId<sem::Time>>(sem::Paragraph::*)() const>(&sem::Paragraph::getTimestampNodes))
    .def("hasLeadHashtags", static_cast<bool(sem::Paragraph::*)() const>(&sem::Paragraph::hasLeadHashtags))
    .def("getLeadHashtags", static_cast<Vec<sem::SemId<sem::HashTag>>(sem::Paragraph::*)() const>(&sem::Paragraph::getLeadHashtags))
    .def("getBody", static_cast<Vec<sem::SemId<sem::Org>>(sem::Paragraph::*)() const>(&sem::Paragraph::getBody), R"RAW(Return content of the paragraph, without prefix idents, hashtags, footnotes etc. )RAW")
    .def("getAttached",
         static_cast<Vec<sem::SemId<sem::Org>>(sem::Paragraph::*)(Opt<Str> const&) const>(&sem::Paragraph::getAttached),
         pybind11::arg_v("kind", std::nullopt),
         R"RAW(Return attached nodes of a specific kinds or all attached (if kind is nullopt))RAW")
    .def("getCaption", static_cast<Vec<sem::SemId<sem::Org>>(sem::Paragraph::*)() const>(&sem::Paragraph::getCaption))
    .def("getName", static_cast<Vec<Str>(sem::Paragraph::*)() const>(&sem::Paragraph::getName))
    .def("getAttrs",
         static_cast<Vec<sem::AttrValue>(sem::Paragraph::*)(Opt<Str> const&) const>(&sem::Paragraph::getAttrs),
         pybind11::arg_v("kind", std::nullopt),
         R"RAW(Get all named arguments for the command, across all attached properties. If kind is nullopt returns all attached arguments for all properties.)RAW")
    .def("getFirstAttr",
         static_cast<Opt<sem::AttrValue>(sem::Paragraph::*)(Str const&) const>(&sem::Paragraph::getFirstAttr),
         pybind11::arg("kind"),
         R"RAW(Get the first parameter for the statement. In case there is a longer list of values matching given kinddifferent node kinds can implement different priorities )RAW")
    .def("__repr__", [](sem::Paragraph _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::Paragraph _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::ColonExample, sem::SemId<sem::ColonExample>, sem::Org>(m, "ColonExample")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::ColonExample {
                        sem::ColonExample result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def("__repr__", [](sem::ColonExample _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::ColonExample _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::CmdAttr, sem::SemId<sem::CmdAttr>, sem::Attached>(m, "CmdAttr")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::CmdAttr {
                        sem::CmdAttr result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("target", &sem::CmdAttr::target)
    .def_readwrite("attrs", &sem::CmdAttr::attrs, R"RAW(Additional parameters aside from 'exporter',)RAW")
    .def_readwrite("attached", &sem::CmdAttr::attached)
    .def("getAttrs",
         static_cast<Vec<sem::AttrValue>(sem::CmdAttr::*)(Opt<Str> const&) const>(&sem::CmdAttr::getAttrs),
         pybind11::arg_v("key", std::nullopt),
         R"RAW(Return all parameters with keys matching name. This is an override implementation that accounts for the explicit command parameters if any.)RAW")
    .def("getFirstAttr",
         static_cast<Opt<sem::AttrValue>(sem::CmdAttr::*)(Str const&) const>(&sem::CmdAttr::getFirstAttr),
         pybind11::arg("kind"),
         R"RAW(Override of the base statement argument get, prioritizing the explicit command parameters)RAW")
    .def("getAttached",
         static_cast<Vec<sem::SemId<sem::Org>>(sem::CmdAttr::*)(Opt<Str> const&) const>(&sem::CmdAttr::getAttached),
         pybind11::arg_v("kind", std::nullopt),
         R"RAW(Return attached nodes of a specific kinds or all attached (if kind is nullopt))RAW")
    .def("getCaption", static_cast<Vec<sem::SemId<sem::Org>>(sem::CmdAttr::*)() const>(&sem::CmdAttr::getCaption))
    .def("getName", static_cast<Vec<Str>(sem::CmdAttr::*)() const>(&sem::CmdAttr::getName))
    .def("getAttrs",
         static_cast<Vec<sem::AttrValue>(sem::CmdAttr::*)(Opt<Str> const&) const>(&sem::CmdAttr::getAttrs),
         pybind11::arg_v("kind", std::nullopt),
         R"RAW(Get all named arguments for the command, across all attached properties. If kind is nullopt returns all attached arguments for all properties.)RAW")
    .def("getFirstAttr",
         static_cast<Opt<sem::AttrValue>(sem::CmdAttr::*)(Str const&) const>(&sem::CmdAttr::getFirstAttr),
         pybind11::arg("kind"),
         R"RAW(Get the first parameter for the statement. In case there is a longer list of values matching given kinddifferent node kinds can implement different priorities )RAW")
    .def("__repr__", [](sem::CmdAttr _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::CmdAttr _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::Call, sem::SemId<sem::Call>, sem::Org>(m, "Call")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::Call {
                        sem::Call result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("name", &sem::Call::name, R"RAW(Call target name)RAW")
    .def_readwrite("attrs", &sem::Call::attrs, R"RAW(Additional parameters aside from 'exporter',)RAW")
    .def_readwrite("isCommand", &sem::Call::isCommand)
    .def("__repr__", [](sem::Call _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::Call _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::List, sem::SemId<sem::List>, sem::Stmt>(m, "List")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::List {
                        sem::List result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("attached", &sem::List::attached)
    .def("getListAttrs",
         static_cast<Vec<sem::AttrValue>(sem::List::*)(Str const&) const>(&sem::List::getListAttrs),
         pybind11::arg("key"))
    .def("isDescriptionList", static_cast<bool(sem::List::*)() const>(&sem::List::isDescriptionList), R"RAW(List is marked as description if any list item has a header)RAW")
    .def("isNumberedList", static_cast<bool(sem::List::*)() const>(&sem::List::isNumberedList), R"RAW(List is marked as numbered if any list item has bullet text set)RAW")
    .def("getAttached",
         static_cast<Vec<sem::SemId<sem::Org>>(sem::List::*)(Opt<Str> const&) const>(&sem::List::getAttached),
         pybind11::arg_v("kind", std::nullopt),
         R"RAW(Return attached nodes of a specific kinds or all attached (if kind is nullopt))RAW")
    .def("getCaption", static_cast<Vec<sem::SemId<sem::Org>>(sem::List::*)() const>(&sem::List::getCaption))
    .def("getName", static_cast<Vec<Str>(sem::List::*)() const>(&sem::List::getName))
    .def("getAttrs",
         static_cast<Vec<sem::AttrValue>(sem::List::*)(Opt<Str> const&) const>(&sem::List::getAttrs),
         pybind11::arg_v("kind", std::nullopt),
         R"RAW(Get all named arguments for the command, across all attached properties. If kind is nullopt returns all attached arguments for all properties.)RAW")
    .def("getFirstAttr",
         static_cast<Opt<sem::AttrValue>(sem::List::*)(Str const&) const>(&sem::List::getFirstAttr),
         pybind11::arg("kind"),
         R"RAW(Get the first parameter for the statement. In case there is a longer list of values matching given kinddifferent node kinds can implement different priorities )RAW")
    .def("__repr__", [](sem::List _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::List _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  bind_enum_iterator<sem::ListItem::Checkbox>(m, "ListItemCheckbox", type_registry_guard);
  pybind11::enum_<sem::ListItem::Checkbox>(m, "ListItemCheckbox")
    .value("None", sem::ListItem::Checkbox::None)
    .value("Done", sem::ListItem::Checkbox::Done)
    .value("Empty", sem::ListItem::Checkbox::Empty)
    .value("Partial", sem::ListItem::Checkbox::Partial)
    .def("__iter__", [](sem::ListItem::Checkbox _self) -> PyEnumIterator<sem::ListItem::Checkbox> {
                     return
                     PyEnumIterator<sem::ListItem::Checkbox>
                     ();
                     })
    ;
  pybind11::class_<sem::ListItem, sem::SemId<sem::ListItem>, sem::Org>(m, "ListItem")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::ListItem {
                        sem::ListItem result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("checkbox", &sem::ListItem::checkbox)
    .def_readwrite("header", &sem::ListItem::header, R"RAW(Description list item header)RAW")
    .def_readwrite("bullet", &sem::ListItem::bullet, R"RAW(Full text of the numbered list item, e.g. `a)`, `a.`)RAW")
    .def("isDescriptionItem", static_cast<bool(sem::ListItem::*)() const>(&sem::ListItem::isDescriptionItem))
    .def("__repr__", [](sem::ListItem _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::ListItem _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::DocumentOptions, sem::SemId<sem::DocumentOptions>, sem::Org>(m, "DocumentOptions")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::DocumentOptions {
                        sem::DocumentOptions result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("initialVisibility", &sem::DocumentOptions::initialVisibility)
    .def_readwrite("properties", &sem::DocumentOptions::properties)
    .def_readwrite("exportConfig", &sem::DocumentOptions::exportConfig)
    .def_readwrite("fixedWidthSections", &sem::DocumentOptions::fixedWidthSections)
    .def_readwrite("startupIndented", &sem::DocumentOptions::startupIndented)
    .def_readwrite("category", &sem::DocumentOptions::category)
    .def_readwrite("setupfile", &sem::DocumentOptions::setupfile)
    .def_readwrite("maxSubtreeLevelExport", &sem::DocumentOptions::maxSubtreeLevelExport)
    .def("getProperties",
         static_cast<Vec<sem::NamedProperty>(sem::DocumentOptions::*)(Str const&, Opt<Str> const&) const>(&sem::DocumentOptions::getProperties),
         pybind11::arg("kind"),
         pybind11::arg_v("subKind", std::nullopt))
    .def("getProperty",
         static_cast<Opt<sem::NamedProperty>(sem::DocumentOptions::*)(Str const&, Opt<Str> const&) const>(&sem::DocumentOptions::getProperty),
         pybind11::arg("kind"),
         pybind11::arg_v("subKind", std::nullopt))
    .def("__repr__", [](sem::DocumentOptions _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::DocumentOptions _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::Document, sem::SemId<sem::Document>, sem::Org>(m, "Document")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::Document {
                        sem::Document result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("title", &sem::Document::title)
    .def_readwrite("author", &sem::Document::author)
    .def_readwrite("creator", &sem::Document::creator)
    .def_readwrite("filetags", &sem::Document::filetags)
    .def_readwrite("email", &sem::Document::email)
    .def_readwrite("language", &sem::Document::language)
    .def_readwrite("options", &sem::Document::options)
    .def_readwrite("exportFileName", &sem::Document::exportFileName)
    .def("getProperties",
         static_cast<Vec<sem::NamedProperty>(sem::Document::*)(Str const&, Opt<Str> const&) const>(&sem::Document::getProperties),
         pybind11::arg("kind"),
         pybind11::arg_v("subKind", std::nullopt))
    .def("getProperty",
         static_cast<Opt<sem::NamedProperty>(sem::Document::*)(Str const&, Opt<Str> const&) const>(&sem::Document::getProperty),
         pybind11::arg("kind"),
         pybind11::arg_v("subKind", std::nullopt))
    .def("__repr__", [](sem::Document _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::Document _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::FileTarget, sem::SemId<sem::FileTarget>, sem::Org>(m, "FileTarget")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::FileTarget {
                        sem::FileTarget result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("path", &sem::FileTarget::path)
    .def_readwrite("line", &sem::FileTarget::line)
    .def_readwrite("searchTarget", &sem::FileTarget::searchTarget)
    .def_readwrite("restrictToHeadlines", &sem::FileTarget::restrictToHeadlines)
    .def_readwrite("targetId", &sem::FileTarget::targetId)
    .def_readwrite("regexp", &sem::FileTarget::regexp)
    .def("__repr__", [](sem::FileTarget _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::FileTarget _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::TextSeparator, sem::SemId<sem::TextSeparator>, sem::Org>(m, "TextSeparator")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::TextSeparator {
                        sem::TextSeparator result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def("__repr__", [](sem::TextSeparator _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::TextSeparator _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::Include::Example>(m, "IncludeExample")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::Include::Example {
                        sem::Include::Example result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def("__repr__", [](sem::Include::Example _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::Include::Example _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::Include::Export>(m, "IncludeExport")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::Include::Export {
                        sem::Include::Export result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def("__repr__", [](sem::Include::Export _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::Include::Export _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::Include::Src>(m, "IncludeSrc")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::Include::Src {
                        sem::Include::Src result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def("__repr__", [](sem::Include::Src _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::Include::Src _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::Include::OrgDocument>(m, "IncludeOrgDocument")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::Include::OrgDocument {
                        sem::Include::OrgDocument result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("minLevel", &sem::Include::OrgDocument::minLevel, R"RAW(The minimum level of headlines to include. Headlines with a level smaller than this value will be demoted to this level.)RAW")
    .def("__repr__", [](sem::Include::OrgDocument _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::Include::OrgDocument _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  bind_enum_iterator<sem::Include::Kind>(m, "IncludeKind", type_registry_guard);
  pybind11::enum_<sem::Include::Kind>(m, "IncludeKind")
    .value("Example", sem::Include::Kind::Example)
    .value("Export", sem::Include::Kind::Export)
    .value("Src", sem::Include::Kind::Src)
    .value("OrgDocument", sem::Include::Kind::OrgDocument)
    .def("__iter__", [](sem::Include::Kind _self) -> PyEnumIterator<sem::Include::Kind> {
                     return
                     PyEnumIterator<sem::Include::Kind>
                     ();
                     })
    ;
  pybind11::class_<sem::Include, sem::SemId<sem::Include>, sem::Org>(m, "Include")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::Include {
                        sem::Include result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("path", &sem::Include::path, R"RAW(Path to include)RAW")
    .def_readwrite("firstLine", &sem::Include::firstLine, R"RAW(0-based index of the first line to include. NOTE: Org-mode syntax uses 1-based half-open range in the text)RAW")
    .def_readwrite("lastLine", &sem::Include::lastLine, R"RAW(0-based index of the last line to include)RAW")
    .def_readwrite("data", &sem::Include::data)
    .def("isExample", static_cast<bool(sem::Include::*)() const>(&sem::Include::isExample))
    .def("getExample", static_cast<sem::Include::Example&(sem::Include::*)()>(&sem::Include::getExample))
    .def("isExport", static_cast<bool(sem::Include::*)() const>(&sem::Include::isExport))
    .def("getExport", static_cast<sem::Include::Export&(sem::Include::*)()>(&sem::Include::getExport))
    .def("isSrc", static_cast<bool(sem::Include::*)() const>(&sem::Include::isSrc))
    .def("getSrc", static_cast<sem::Include::Src&(sem::Include::*)()>(&sem::Include::getSrc))
    .def("isOrgDocument", static_cast<bool(sem::Include::*)() const>(&sem::Include::isOrgDocument))
    .def("getOrgDocument", static_cast<sem::Include::OrgDocument&(sem::Include::*)()>(&sem::Include::getOrgDocument))
    .def_static("getIncludeKindStatic",
                static_cast<sem::Include::Kind(*)(sem::Include::Data const&)>(&sem::Include::getIncludeKind),
                pybind11::arg("__input"))
    .def("getIncludeKind", static_cast<sem::Include::Kind(sem::Include::*)() const>(&sem::Include::getIncludeKind))
    .def("__repr__", [](sem::Include _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::Include _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::DocumentGroup, sem::SemId<sem::DocumentGroup>, sem::Org>(m, "DocumentGroup")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::DocumentGroup {
                        sem::DocumentGroup result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def("__repr__", [](sem::DocumentGroup _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::DocumentGroup _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  bind_enum_iterator<ListFormattingMode>(m, "ListFormattingMode", type_registry_guard);
  pybind11::enum_<ListFormattingMode>(m, "ListFormattingMode")
    .value("None", ListFormattingMode::None)
    .value("Table1D1Col", ListFormattingMode::Table1D1Col)
    .value("Table1D2Col", ListFormattingMode::Table1D2Col)
    .value("Table2DColFirst", ListFormattingMode::Table2DColFirst)
    .def("__iter__", [](ListFormattingMode _self) -> PyEnumIterator<ListFormattingMode> {
                     return
                     PyEnumIterator<ListFormattingMode>
                     ();
                     })
    ;
  bind_enum_iterator<NodeAttachMode>(m, "NodeAttachMode", type_registry_guard);
  pybind11::enum_<NodeAttachMode>(m, "NodeAttachMode")
    .value("None", NodeAttachMode::None)
    .value("Subtree", NodeAttachMode::Subtree)
    .def("__iter__", [](NodeAttachMode _self) -> PyEnumIterator<NodeAttachMode> {
                     return
                     PyEnumIterator<NodeAttachMode>
                     ();
                     })
    ;
  bind_enum_iterator<InitialSubtreeVisibility>(m, "InitialSubtreeVisibility", type_registry_guard);
  pybind11::enum_<InitialSubtreeVisibility>(m, "InitialSubtreeVisibility")
    .value("Overview", InitialSubtreeVisibility::Overview)
    .value("Content", InitialSubtreeVisibility::Content)
    .value("ShowAll", InitialSubtreeVisibility::ShowAll)
    .value("Show2Levels", InitialSubtreeVisibility::Show2Levels)
    .value("Show3Levels", InitialSubtreeVisibility::Show3Levels)
    .value("Show4Levels", InitialSubtreeVisibility::Show4Levels)
    .value("Show5Levels", InitialSubtreeVisibility::Show5Levels)
    .value("ShowEverything", InitialSubtreeVisibility::ShowEverything)
    .def("__iter__", [](InitialSubtreeVisibility _self) -> PyEnumIterator<InitialSubtreeVisibility> {
                     return
                     PyEnumIterator<InitialSubtreeVisibility>
                     ();
                     })
    ;
  bind_enum_iterator<BlockCodeResults>(m, "BlockCodeResults", type_registry_guard);
  pybind11::enum_<BlockCodeResults>(m, "BlockCodeResults")
    .value("Replace", BlockCodeResults::Replace, R"RAW(Remove old result, replace with new value)RAW")
    .def("__iter__", [](BlockCodeResults _self) -> PyEnumIterator<BlockCodeResults> {
                     return
                     PyEnumIterator<BlockCodeResults>
                     ();
                     })
    ;
  bind_enum_iterator<BlockCodeExports>(m, "BlockCodeExports", type_registry_guard);
  pybind11::enum_<BlockCodeExports>(m, "BlockCodeExports")
    .value("None", BlockCodeExports::None, R"RAW(Hide both original code and run result)RAW")
    .value("Both", BlockCodeExports::Both, R"RAW(Show output and code)RAW")
    .value("Code", BlockCodeExports::Code, R"RAW(Show only code)RAW")
    .value("Results", BlockCodeExports::Results, R"RAW(Show only evaluation results)RAW")
    .def("__iter__", [](BlockCodeExports _self) -> PyEnumIterator<BlockCodeExports> {
                     return
                     PyEnumIterator<BlockCodeExports>
                     ();
                     })
    ;
  bind_enum_iterator<OrgSpecName>(m, "OrgSpecName", type_registry_guard);
  pybind11::enum_<OrgSpecName>(m, "OrgSpecName")
    .value("Unnamed", OrgSpecName::Unnamed)
    .value("Result", OrgSpecName::Result)
    .value("Year", OrgSpecName::Year)
    .value("Day", OrgSpecName::Day)
    .value("Clock", OrgSpecName::Clock)
    .value("Repeater", OrgSpecName::Repeater)
    .value("Zone", OrgSpecName::Zone)
    .value("Link", OrgSpecName::Link)
    .value("Tags", OrgSpecName::Tags)
    .value("Tag", OrgSpecName::Tag)
    .value("State", OrgSpecName::State)
    .value("Protocol", OrgSpecName::Protocol)
    .value("Desc", OrgSpecName::Desc)
    .value("Times", OrgSpecName::Times)
    .value("Drawer", OrgSpecName::Drawer)
    .value("Args", OrgSpecName::Args)
    .value("Name", OrgSpecName::Name)
    .value("Definition", OrgSpecName::Definition)
    .value("Body", OrgSpecName::Body)
    .value("HeaderArgs", OrgSpecName::HeaderArgs)
    .value("File", OrgSpecName::File)
    .value("Kind", OrgSpecName::Kind)
    .value("Lang", OrgSpecName::Lang)
    .value("Prefix", OrgSpecName::Prefix)
    .value("Text", OrgSpecName::Text)
    .value("Todo", OrgSpecName::Todo)
    .value("Importance", OrgSpecName::Importance)
    .value("Title", OrgSpecName::Title)
    .value("Completion", OrgSpecName::Completion)
    .value("Head", OrgSpecName::Head)
    .value("Subnodes", OrgSpecName::Subnodes)
    .value("Properties", OrgSpecName::Properties)
    .value("Logbook", OrgSpecName::Logbook)
    .value("Description", OrgSpecName::Description)
    .value("Logs", OrgSpecName::Logs)
    .value("Newstate", OrgSpecName::Newstate)
    .value("Oldstate", OrgSpecName::Oldstate)
    .value("Time", OrgSpecName::Time)
    .value("From", OrgSpecName::From)
    .value("EndArgs", OrgSpecName::EndArgs)
    .value("Flags", OrgSpecName::Flags)
    .value("Value", OrgSpecName::Value)
    .value("Assoc", OrgSpecName::Assoc)
    .value("Main", OrgSpecName::Main)
    .value("Hash", OrgSpecName::Hash)
    .value("Bullet", OrgSpecName::Bullet)
    .value("Counter", OrgSpecName::Counter)
    .value("Checkbox", OrgSpecName::Checkbox)
    .value("Header", OrgSpecName::Header)
    .value("To", OrgSpecName::To)
    .value("Diff", OrgSpecName::Diff)
    .value("Property", OrgSpecName::Property)
    .value("Subname", OrgSpecName::Subname)
    .value("Values", OrgSpecName::Values)
    .value("Cells", OrgSpecName::Cells)
    .value("Rows", OrgSpecName::Rows)
    .value("Lines", OrgSpecName::Lines)
    .value("Chunks", OrgSpecName::Chunks)
    .value("InheritanceMode", OrgSpecName::InheritanceMode)
    .value("MainSetRule", OrgSpecName::MainSetRule)
    .value("SubSetRule", OrgSpecName::SubSetRule)
    .def("__iter__", [](OrgSpecName _self) -> PyEnumIterator<OrgSpecName> {
                     return
                     PyEnumIterator<OrgSpecName>
                     ();
                     })
    ;
  bind_enum_iterator<OrgNodeKind>(m, "OrgNodeKind", type_registry_guard);
  pybind11::enum_<OrgNodeKind>(m, "OrgNodeKind")
    .value("None", OrgNodeKind::None, R"RAW(Default valye for node - invalid state)RAW")
    .value("Document", OrgNodeKind::Document, R"RAW(Toplevel part of the ast, not created by parser, and only used in `semorg` stage)RAW")
    .value("Empty", OrgNodeKind::Empty, R"RAW(Empty node - valid state that does not contain any value)RAW")
    .value("InlineStmtList", OrgNodeKind::InlineStmtList)
    .value("StmtList", OrgNodeKind::StmtList, R"RAW(List of statements, possibly recursive. Used as toplevel part of the document, in recursive parsing of subtrees, or as regular list, in cases where multiple subnodes have to be grouped together.)RAW")
    .value("Checkbox", OrgNodeKind::Checkbox, R"RAW(Single checkbox item like `[X]` or `[-]`)RAW")
    .value("List", OrgNodeKind::List)
    .value("Bullet", OrgNodeKind::Bullet, R"RAW(List item prefix)RAW")
    .value("ListItem", OrgNodeKind::ListItem)
    .value("ListTag", OrgNodeKind::ListTag, R"RAW(Auxilliary wrapper for the paragraph placed at the start of the description list.)RAW")
    .value("Counter", OrgNodeKind::Counter)
    .value("File", OrgNodeKind::File)
    .value("ColonExample", OrgNodeKind::ColonExample, R"RAW(Colon example block)RAW")
    .value("TextSeparator", OrgNodeKind::TextSeparator, R"RAW(Long horizontal line `----`)RAW")
    .value("Paragraph", OrgNodeKind::Paragraph, R"RAW(Single 'paragraph' of text. Used as generic container for any place in AST where unordered sentence might be encountered (e.g. caption, link description) - not limited to actual paragraph)RAW")
    .value("TableRow", OrgNodeKind::TableRow, R"RAW(Horizontal table row)RAW")
    .value("TableCell", OrgNodeKind::TableCell, R"RAW(Single cell in row. Might contain anyting, including other tables, simple text paragraph etc.)RAW")
    .value("Table", OrgNodeKind::Table, R"RAW(Org-mode table)RAW")
    .value("InlineFootnote", OrgNodeKind::InlineFootnote, R"RAW(Inline footnote with text placed directly in the node body.)RAW")
    .value("Footnote", OrgNodeKind::Footnote, R"RAW(Footnote entry. Just as regular links - internal content is not parsed, and instead just cut out verbatim into target AST node.)RAW")
    .value("Cmd", OrgNodeKind::Cmd, R"RAW(Undefined single-line command -- most likely custom user-provided oe)RAW")
    .value("Attrs", OrgNodeKind::Attrs, R"RAW(Arguments for the command block)RAW")
    .value("CmdTitle", OrgNodeKind::CmdTitle, R"RAW(`#+title:` - full document title)RAW")
    .value("CmdAuthor", OrgNodeKind::CmdAuthor, R"RAW(`#+author:` Document author)RAW")
    .value("CmdCreator", OrgNodeKind::CmdCreator, R"RAW(`#+creator:` Document creator)RAW")
    .value("CmdInclude", OrgNodeKind::CmdInclude, R"RAW(`#+include:` - include other org-mode document (or subsection of it), source code or backend-specific chunk.)RAW")
    .value("CmdLanguage", OrgNodeKind::CmdLanguage, R"RAW(`#+language:`)RAW")
    .value("CmdAttr", OrgNodeKind::CmdAttr, R"RAW(`#+attr_html:`, `#+attr_image` etc.)RAW")
    .value("CmdStartup", OrgNodeKind::CmdStartup, R"RAW(`#+startup:`)RAW")
    .value("CmdName", OrgNodeKind::CmdName, R"RAW(`#+name:` - name of the associated entry)RAW")
    .value("CmdCustomTextCommand", OrgNodeKind::CmdCustomTextCommand, R"RAW(Line command with parsed text value)RAW")
    .value("CmdCustomArgsCommand", OrgNodeKind::CmdCustomArgsCommand, R"RAW(Line command with parsed argument list)RAW")
    .value("CmdCustomRawCommand", OrgNodeKind::CmdCustomRawCommand, R"RAW(Line command with raw text argument)RAW")
    .value("CmdResults", OrgNodeKind::CmdResults, R"RAW(`#+results:` - source code block evaluation results)RAW")
    .value("CmdHeader", OrgNodeKind::CmdHeader, R"RAW(`#+header:` - extended list of parameters passed to associated block)RAW")
    .value("CmdOptions", OrgNodeKind::CmdOptions, R"RAW(`#+options:` - document-wide formatting options)RAW")
    .value("CmdTblfm", OrgNodeKind::CmdTblfm)
    .value("CmdCaption", OrgNodeKind::CmdCaption, R"RAW(`#+caption:` command)RAW")
    .value("CmdResult", OrgNodeKind::CmdResult, R"RAW(Command evaluation result)RAW")
    .value("CmdCallCode", OrgNodeKind::CmdCallCode, R"RAW(Call to named source code block.)RAW")
    .value("CmdFlag", OrgNodeKind::CmdFlag, R"RAW(Flag for source code block. For example `-n`, which is used to to make source code block export with lines)RAW")
    .value("CmdKey", OrgNodeKind::CmdKey)
    .value("CmdValue", OrgNodeKind::CmdValue)
    .value("CmdNamedValue", OrgNodeKind::CmdNamedValue, R"RAW(Key-value pair for source code block call.)RAW")
    .value("CmdLatexClass", OrgNodeKind::CmdLatexClass)
    .value("CmdLatexHeader", OrgNodeKind::CmdLatexHeader)
    .value("CmdLatexCompiler", OrgNodeKind::CmdLatexCompiler)
    .value("CmdLatexClassOptions", OrgNodeKind::CmdLatexClassOptions)
    .value("CmdHtmlHead", OrgNodeKind::CmdHtmlHead)
    .value("CmdColumns", OrgNodeKind::CmdColumns, R"RAW(`#+columns:` line command for specifying formatting of the org-mode clock table visualization on per-file basis.)RAW")
    .value("CmdPropertyArgs", OrgNodeKind::CmdPropertyArgs, R"RAW(`#+property:` command)RAW")
    .value("CmdPropertyText", OrgNodeKind::CmdPropertyText, R"RAW(`#+property:` command)RAW")
    .value("CmdPropertyRaw", OrgNodeKind::CmdPropertyRaw, R"RAW(`#+property:` command)RAW")
    .value("CmdFiletags", OrgNodeKind::CmdFiletags, R"RAW(`#+filetags:` line command)RAW")
    .value("BlockVerbatimMultiline", OrgNodeKind::BlockVerbatimMultiline, R"RAW(Verbatim mulitiline block that *might* be a part of `orgMultilineCommand` (in case of `#+begin-src`), but not necessarily. Can also be a part of =quote= and =example= multiline blocks.)RAW")
    .value("CodeLine", OrgNodeKind::CodeLine, R"RAW(Single line of source code)RAW")
    .value("CodeText", OrgNodeKind::CodeText, R"RAW(Block of source code text)RAW")
    .value("CodeTangle", OrgNodeKind::CodeTangle, R"RAW(Single tangle target in the code block)RAW")
    .value("CodeCallout", OrgNodeKind::CodeCallout, R"RAW(`(refs:` callout in the source code)RAW")
    .value("BlockCode", OrgNodeKind::BlockCode)
    .value("BlockQuote", OrgNodeKind::BlockQuote, R"RAW(`#+begin_quote:` block in code)RAW")
    .value("BlockComment", OrgNodeKind::BlockComment, R"RAW(`#+begin_comment:` block in code)RAW")
    .value("BlockCenter", OrgNodeKind::BlockCenter)
    .value("BlockVerse", OrgNodeKind::BlockVerse)
    .value("BlockExample", OrgNodeKind::BlockExample, R"RAW(Verbatim example text block)RAW")
    .value("BlockExport", OrgNodeKind::BlockExport)
    .value("BlockDetails", OrgNodeKind::BlockDetails, R"RAW(`#+begin_details`  section)RAW")
    .value("BlockSummary", OrgNodeKind::BlockSummary, R"RAW(`#+begin_summary` section)RAW")
    .value("BlockDynamicFallback", OrgNodeKind::BlockDynamicFallback, R"RAW(#+begin_<any> section)RAW")
    .value("BigIdent", OrgNodeKind::BigIdent, R"RAW(full-uppsercase identifier such as `MUST` or `TODO`)RAW")
    .value("Bold", OrgNodeKind::Bold, R"RAW(Region of text with formatting, which contains standalone words -
     can itself contain subnodes, which allows to represent nested
     formatting regions, such as `*bold /italic/*` text. Particular type
     of identifier is stored in string form in `str` field for `OrgNode`
     -- bold is represented as `"*"`, italic as `/` and so on. In case
     of explicit open/close pairs only opening one is stored.

     NOTE: when structured sentences are enabled, regular punctuation
     elements like `some text (notes)` are also represented as `Word,
     Word, Markup(str: "(", [Word])` - e.g. structure is not fully flat.)RAW")
    .value("Italic", OrgNodeKind::Italic)
    .value("Verbatim", OrgNodeKind::Verbatim)
    .value("Backtick", OrgNodeKind::Backtick)
    .value("Underline", OrgNodeKind::Underline)
    .value("Strike", OrgNodeKind::Strike)
    .value("Quote", OrgNodeKind::Quote)
    .value("Angle", OrgNodeKind::Angle)
    .value("Monospace", OrgNodeKind::Monospace)
    .value("Par", OrgNodeKind::Par)
    .value("InlineMath", OrgNodeKind::InlineMath, R"RAW(Inline latex math. Contains latex math body - either from `$dollar-wrapped$` or `\(paren-wrapped\)` inline text.)RAW")
    .value("DisplayMath", OrgNodeKind::DisplayMath, R"RAW(Inline display latex math from `$$double-dollar$$` or `\[bracket-wrapped\]` code.)RAW")
    .value("Space", OrgNodeKind::Space, R"RAW(Space or tab character in regular text)RAW")
    .value("Punctuation", OrgNodeKind::Punctuation)
    .value("Colon", OrgNodeKind::Colon)
    .value("Word", OrgNodeKind::Word, R"RAW(Regular word - technically not different from `orgIdent`, but defined separately to disiguish between places where special syntax is required and free-form text.)RAW")
    .value("Escaped", OrgNodeKind::Escaped, R"RAW(Escaped formatting character in the text)RAW")
    .value("Newline", OrgNodeKind::Newline)
    .value("RawLink", OrgNodeKind::RawLink, R"RAW(Raw unwrapped link that was pasted in text)RAW")
    .value("Link", OrgNodeKind::Link, R"RAW(External or internal link. Consists of one or two elements - target
     (url, file location etc.) and description (`orgParagraph` of text).
     Description might be empty, and represented as empty node in this
     case. For external links particular formatting of the address is
     not handled by parser and instead contains raw string from input
     text.)RAW")
    .value("Macro", OrgNodeKind::Macro, R"RAW(Org-mode macro replacement - during export each macro is expanded
     and evaluated according to it's environment. Body of the macro is
     not parsed fully during org-mode evaluation, but is checked for
     correct parenthesis balance (as macro might contain elisp code))RAW")
    .value("Symbol", OrgNodeKind::Symbol, R"RAW(Special symbol that should be exported differently to various backends - greek letters (`lpha`), mathematical notations and so on.)RAW")
    .value("StaticActiveTime", OrgNodeKind::StaticActiveTime)
    .value("StaticInactiveTime", OrgNodeKind::StaticInactiveTime)
    .value("DynamicActiveTime", OrgNodeKind::DynamicActiveTime)
    .value("DynamicInactiveTime", OrgNodeKind::DynamicInactiveTime, R"RAW(Single date and time entry (active or inactive),, possibly with repeater interval. Is not parsed directly, and instead contains `orgRawText` that can be parsed later)RAW")
    .value("TimeRange", OrgNodeKind::TimeRange, R"RAW(Date and time range format - two `orgDateTime` entries)RAW")
    .value("SimpleTime", OrgNodeKind::SimpleTime, R"RAW(Result of the time range evaluation or trailing annotation a subtree)RAW")
    .value("HashTag", OrgNodeKind::HashTag)
    .value("MetaSymbol", OrgNodeKind::MetaSymbol, R"RAW(`\sym{}` with explicit arguments)RAW")
    .value("AtMention", OrgNodeKind::AtMention, R"RAW(`@user`)RAW")
    .value("Placeholder", OrgNodeKind::Placeholder, R"RAW(Placeholder entry in text, usually writte like `<text to replace>`)RAW")
    .value("RadioTarget", OrgNodeKind::RadioTarget, R"RAW(`<<<RADIO>>>`)RAW")
    .value("Target", OrgNodeKind::Target, R"RAW(`<<TARGET>>`)RAW")
    .value("SrcInlineCode", OrgNodeKind::SrcInlineCode, R"RAW(inline piece of code (such as `src_nim`),. Latter is different from regular monospaced text inside of `~~` pair as it contains additional internal structure, optional parameter for code evaluation etc.)RAW")
    .value("InlineCallCode", OrgNodeKind::InlineCallCode, R"RAW(Call to named source code block.)RAW")
    .value("InlineExport", OrgNodeKind::InlineExport, R"RAW(Passthrough block. Inline, multiline, or single-line. Syntax is `@@<backend-name>:<any-body>@@`. Has line and block syntax respectively)RAW")
    .value("InlineComment", OrgNodeKind::InlineComment)
    .value("RawText", OrgNodeKind::RawText, R"RAW(Raw string of text from input buffer. Things like particular syntax details of every single command, link formats are not handled in parser, deferring formatting to future processing layers )RAW")
    .value("SubtreeDescription", OrgNodeKind::SubtreeDescription, R"RAW(`:description:` entry)RAW")
    .value("SubtreeUrgency", OrgNodeKind::SubtreeUrgency)
    .value("DrawerLogbook", OrgNodeKind::DrawerLogbook, R"RAW(`:logbook:` entry storing note information)RAW")
    .value("Drawer", OrgNodeKind::Drawer, R"RAW(Single enclosed drawer like `:properties: ... :end:` or `:logbook: ... :end:`)RAW")
    .value("DrawerPropertyList", OrgNodeKind::DrawerPropertyList)
    .value("DrawerProperty", OrgNodeKind::DrawerProperty, R"RAW(`:property:` drawer)RAW")
    .value("Subtree", OrgNodeKind::Subtree, R"RAW(Section subtree)RAW")
    .value("SubtreeTimes", OrgNodeKind::SubtreeTimes, R"RAW(Time? associated with subtree entry)RAW")
    .value("SubtreeStars", OrgNodeKind::SubtreeStars)
    .value("SubtreeCompletion", OrgNodeKind::SubtreeCompletion, R"RAW(Task compleation cookie, indicated either in percents of completion, or as `<done>/<todo>` ratio.)RAW")
    .value("SubtreeImportance", OrgNodeKind::SubtreeImportance, R"RAW(Subtree importance level, such as `[#A]` or `[#B]`. Default org-mode only allows single character for contents inside of `[]`, but this parser makes it possible to use any regular identifier, such as `[#urgent]`.)RAW")
    .def("__iter__", [](OrgNodeKind _self) -> PyEnumIterator<OrgNodeKind> {
                     return
                     PyEnumIterator<OrgNodeKind>
                     ();
                     })
    ;
  bind_enum_iterator<OrgSemKind>(m, "OrgSemKind", type_registry_guard);
  pybind11::enum_<OrgSemKind>(m, "OrgSemKind")
    .value("None", OrgSemKind::None)
    .value("Attr", OrgSemKind::Attr)
    .value("AttrList", OrgSemKind::AttrList)
    .value("Attrs", OrgSemKind::Attrs)
    .value("ErrorItem", OrgSemKind::ErrorItem)
    .value("ErrorGroup", OrgSemKind::ErrorGroup)
    .value("StmtList", OrgSemKind::StmtList)
    .value("Empty", OrgSemKind::Empty)
    .value("CmdCaption", OrgSemKind::CmdCaption)
    .value("CmdName", OrgSemKind::CmdName)
    .value("CmdCustomArgs", OrgSemKind::CmdCustomArgs)
    .value("CmdCustomRaw", OrgSemKind::CmdCustomRaw)
    .value("CmdCustomText", OrgSemKind::CmdCustomText)
    .value("CmdResults", OrgSemKind::CmdResults)
    .value("CmdTblfm", OrgSemKind::CmdTblfm)
    .value("HashTag", OrgSemKind::HashTag)
    .value("InlineFootnote", OrgSemKind::InlineFootnote)
    .value("Time", OrgSemKind::Time)
    .value("TimeRange", OrgSemKind::TimeRange)
    .value("Macro", OrgSemKind::Macro)
    .value("Symbol", OrgSemKind::Symbol)
    .value("Escaped", OrgSemKind::Escaped)
    .value("Newline", OrgSemKind::Newline)
    .value("Space", OrgSemKind::Space)
    .value("Word", OrgSemKind::Word)
    .value("AtMention", OrgSemKind::AtMention)
    .value("RawText", OrgSemKind::RawText)
    .value("Punctuation", OrgSemKind::Punctuation)
    .value("Placeholder", OrgSemKind::Placeholder)
    .value("BigIdent", OrgSemKind::BigIdent)
    .value("RadioTarget", OrgSemKind::RadioTarget)
    .value("TextTarget", OrgSemKind::TextTarget)
    .value("Bold", OrgSemKind::Bold)
    .value("Underline", OrgSemKind::Underline)
    .value("Monospace", OrgSemKind::Monospace)
    .value("MarkQuote", OrgSemKind::MarkQuote)
    .value("Verbatim", OrgSemKind::Verbatim)
    .value("Italic", OrgSemKind::Italic)
    .value("Strike", OrgSemKind::Strike)
    .value("Par", OrgSemKind::Par)
    .value("Latex", OrgSemKind::Latex)
    .value("Link", OrgSemKind::Link)
    .value("BlockCenter", OrgSemKind::BlockCenter)
    .value("BlockQuote", OrgSemKind::BlockQuote)
    .value("BlockComment", OrgSemKind::BlockComment)
    .value("BlockVerse", OrgSemKind::BlockVerse)
    .value("BlockDynamicFallback", OrgSemKind::BlockDynamicFallback)
    .value("BlockExample", OrgSemKind::BlockExample)
    .value("BlockExport", OrgSemKind::BlockExport)
    .value("BlockAdmonition", OrgSemKind::BlockAdmonition)
    .value("BlockCode", OrgSemKind::BlockCode)
    .value("SubtreeLog", OrgSemKind::SubtreeLog)
    .value("Subtree", OrgSemKind::Subtree)
    .value("SubtreeCompletion", OrgSemKind::SubtreeCompletion)
    .value("Cell", OrgSemKind::Cell)
    .value("Row", OrgSemKind::Row)
    .value("Table", OrgSemKind::Table)
    .value("Paragraph", OrgSemKind::Paragraph)
    .value("ColonExample", OrgSemKind::ColonExample)
    .value("CmdAttr", OrgSemKind::CmdAttr)
    .value("Call", OrgSemKind::Call)
    .value("List", OrgSemKind::List)
    .value("ListItem", OrgSemKind::ListItem)
    .value("DocumentOptions", OrgSemKind::DocumentOptions)
    .value("Document", OrgSemKind::Document)
    .value("FileTarget", OrgSemKind::FileTarget)
    .value("TextSeparator", OrgSemKind::TextSeparator)
    .value("Include", OrgSemKind::Include)
    .value("DocumentGroup", OrgSemKind::DocumentGroup)
    .def("__iter__", [](OrgSemKind _self) -> PyEnumIterator<OrgSemKind> {
                     return
                     PyEnumIterator<OrgSemKind>
                     ();
                     })
    ;
  pybind11::class_<UserTimeBreakdown>(m, "UserTimeBreakdown")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> UserTimeBreakdown {
                        UserTimeBreakdown result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("year", &UserTimeBreakdown::year)
    .def_readwrite("month", &UserTimeBreakdown::month)
    .def_readwrite("day", &UserTimeBreakdown::day)
    .def_readwrite("hour", &UserTimeBreakdown::hour)
    .def_readwrite("minute", &UserTimeBreakdown::minute)
    .def_readwrite("second", &UserTimeBreakdown::second)
    .def_readwrite("zone", &UserTimeBreakdown::zone)
    .def("__repr__", [](UserTimeBreakdown _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](UserTimeBreakdown _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<UserTime>(m, "UserTime")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> UserTime {
                        UserTime result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def("getBreakdown", static_cast<UserTimeBreakdown(UserTime::*)() const>(&UserTime::getBreakdown))
    .def("format", static_cast<std::string(UserTime::*)() const>(&UserTime::format))
    .def("__repr__", [](UserTime _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](UserTime _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::OrgParseParameters>(m, "OrgParseParameters")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::OrgParseParameters {
                        sem::OrgParseParameters result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("baseTokenTracePath", &sem::OrgParseParameters::baseTokenTracePath)
    .def_readwrite("tokenTracePath", &sem::OrgParseParameters::tokenTracePath)
    .def_readwrite("parseTracePath", &sem::OrgParseParameters::parseTracePath)
    .def_readwrite("semTracePath", &sem::OrgParseParameters::semTracePath)
    .def("__repr__", [](sem::OrgParseParameters _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::OrgParseParameters _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::OrgYamlExportOpts>(m, "OrgYamlExportOpts")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::OrgYamlExportOpts {
                        sem::OrgYamlExportOpts result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("skipNullFields", &sem::OrgYamlExportOpts::skipNullFields)
    .def_readwrite("skipFalseFields", &sem::OrgYamlExportOpts::skipFalseFields)
    .def_readwrite("skipZeroFields", &sem::OrgYamlExportOpts::skipZeroFields)
    .def_readwrite("skipLocation", &sem::OrgYamlExportOpts::skipLocation)
    .def_readwrite("skipId", &sem::OrgYamlExportOpts::skipId)
    .def("__repr__", [](sem::OrgYamlExportOpts _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::OrgYamlExportOpts _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<sem::OrgTreeExportOpts>(m, "OrgTreeExportOpts")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> sem::OrgTreeExportOpts {
                        sem::OrgTreeExportOpts result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("withLineCol", &sem::OrgTreeExportOpts::withLineCol)
    .def_readwrite("withOriginalId", &sem::OrgTreeExportOpts::withOriginalId)
    .def_readwrite("withSubnodeIdx", &sem::OrgTreeExportOpts::withSubnodeIdx)
    .def_readwrite("skipEmptyFields", &sem::OrgTreeExportOpts::skipEmptyFields)
    .def_readwrite("startLevel", &sem::OrgTreeExportOpts::startLevel)
    .def_readwrite("withColor", &sem::OrgTreeExportOpts::withColor)
    .def_readwrite("maxDepth", &sem::OrgTreeExportOpts::maxDepth)
    .def("__repr__", [](sem::OrgTreeExportOpts _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](sem::OrgTreeExportOpts _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<SequenceSegment>(m, "SequenceSegment")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> SequenceSegment {
                        SequenceSegment result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("kind", &SequenceSegment::kind, R"RAW(\brief Kind of the segment, does not have to be unique for all
segments, and different sequence segment groups can have segments
with identical kinds.)RAW")
    .def_readwrite("first", &SequenceSegment::first, R"RAW(\brief Inclusive left boundary of the segment. Mustnot overlap with
other segments' boundaries,but can be identical to the `last`,
to create a point segment (spans 1 element).)RAW")
    .def_readwrite("last", &SequenceSegment::last, R"RAW(\brief Inclusive right boundary for the segment)RAW")
    .def("__repr__", [](SequenceSegment _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](SequenceSegment _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<SequenceSegmentGroup>(m, "SequenceSegmentGroup")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> SequenceSegmentGroup {
                        SequenceSegmentGroup result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("kind", &SequenceSegmentGroup::kind, R"RAW(\brief An kind of the segment group, does not have to be unique)RAW")
    .def_readwrite("segments", &SequenceSegmentGroup::segments, R"RAW(\brief List of input segments for grouping)RAW")
    .def("__repr__", [](SequenceSegmentGroup _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](SequenceSegmentGroup _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<SequenceAnnotationTag>(m, "SequenceAnnotationTag")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> SequenceAnnotationTag {
                        SequenceAnnotationTag result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("groupKind", &SequenceAnnotationTag::groupKind, R"RAW(\brief ID of the original group this segment came from)RAW")
    .def_readwrite("segmentKinds", &SequenceAnnotationTag::segmentKinds, R"RAW(\brief ID of the segment in this group.

Segment kinds are constructed from all ranges
that overlap points in the segment.
In the example below, there are 3 separate slices, `[2,3]`, `[1,4]`
and finally `[6,7]`. The resulting segmentation will have 4
different sequence segments from these ranges. The first one is
`[1,1]`, then `[2,3]`, `[4]`, and `[6,7]`.
```
0
1   |
2 | |
3 | |
4   |
5
6   |
7   |
```)RAW")
    .def("__repr__", [](SequenceAnnotationTag _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](SequenceAnnotationTag _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<SequenceAnnotation>(m, "SequenceAnnotation")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> SequenceAnnotation {
                        SequenceAnnotation result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def_readwrite("first", &SequenceAnnotation::first, R"RAW(\brief Inclusive left boundary for the sequence segment annotation)RAW")
    .def_readwrite("last", &SequenceAnnotation::last, R"RAW(\brief Inclusive right boundary for the sequence segment)RAW")
    .def_readwrite("annotations", &SequenceAnnotation::annotations, R"RAW(\brief Full list of all annotated segments.)RAW")
    .def("isAnnotatedWith",
         static_cast<bool(SequenceAnnotation::*)(int, int) const>(&SequenceAnnotation::isAnnotatedWith),
         pybind11::arg("groupKind"),
         pybind11::arg("segmentKind"),
         R"RAW(\brief Check if the segment is annotated with a given group kind
and a segment kind.)RAW")
    .def("__repr__", [](SequenceAnnotation _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](SequenceAnnotation _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  pybind11::class_<ExporterPython>(m, "ExporterPython")
    .def(pybind11::init([](pybind11::kwargs const& kwargs) -> ExporterPython {
                        ExporterPython result{};
                        init_fields_from_kwargs(result, kwargs);
                        return result;
                        }))
    .def("enableBufferTrace", static_cast<void(ExporterPython::*)()>(&ExporterPython::enableBufferTrace))
    .def("getTraceBuffer", static_cast<std::string(ExporterPython::*)() const>(&ExporterPython::getTraceBuffer))
    .def("enableFileTrace",
         static_cast<void(ExporterPython::*)(std::string const&, bool)>(&ExporterPython::enableFileTrace),
         pybind11::arg("path"),
         pybind11::arg("colored"))
    .def("setVisitAnyIdAround",
         static_cast<void(ExporterPython::*)(ExporterPython::PyFunc)>(&ExporterPython::setVisitAnyIdAround),
         pybind11::arg("cb"))
    .def("setVisitAnyIdIn",
         static_cast<void(ExporterPython::*)(ExporterPython::PyFunc)>(&ExporterPython::setVisitAnyIdIn),
         pybind11::arg("cb"))
    .def("setVisitAnyField",
         static_cast<void(ExporterPython::*)(ExporterPython::PyFunc)>(&ExporterPython::setVisitAnyField),
         pybind11::arg("cb"))
    .def("setEvalTopCb",
         static_cast<void(ExporterPython::*)(ExporterPython::PyFunc)>(&ExporterPython::setEvalTopCb),
         pybind11::arg("cb"))
    .def("setVisitIdAround",
         static_cast<void(ExporterPython::*)(OrgSemKind, ExporterPython::PyFunc)>(&ExporterPython::setVisitIdAround),
         pybind11::arg("kind"),
         pybind11::arg("cb"))
    .def("setEvalIdAround",
         static_cast<void(ExporterPython::*)(OrgSemKind, ExporterPython::PyFunc)>(&ExporterPython::setEvalIdAround),
         pybind11::arg("kind"),
         pybind11::arg("cb"))
    .def("setVisitIdInCb",
         static_cast<void(ExporterPython::*)(OrgSemKind, ExporterPython::PyFunc)>(&ExporterPython::setVisitIdInCb),
         pybind11::arg("kind"),
         pybind11::arg("cb"))
    .def("setEvalIdIn",
         static_cast<void(ExporterPython::*)(OrgSemKind, ExporterPython::PyFunc)>(&ExporterPython::setEvalIdIn),
         pybind11::arg("kind"),
         pybind11::arg("cb"))
    .def("setVisitLeafField",
         static_cast<void(ExporterPython::*)(LeafFieldType, ExporterPython::PyFunc)>(&ExporterPython::setVisitLeafField),
         pybind11::arg("kind"),
         pybind11::arg("cb"))
    .def("setEvalLeafField",
         static_cast<void(ExporterPython::*)(LeafFieldType, ExporterPython::PyFunc)>(&ExporterPython::setEvalLeafField),
         pybind11::arg("kind"),
         pybind11::arg("cb"))
    .def("setVisitOrgField",
         static_cast<void(ExporterPython::*)(OrgSemKind, ExporterPython::PyFunc)>(&ExporterPython::setVisitOrgField),
         pybind11::arg("kind"),
         pybind11::arg("cb"))
    .def("setEvalOrgField",
         static_cast<void(ExporterPython::*)(OrgSemKind, ExporterPython::PyFunc)>(&ExporterPython::setEvalOrgField),
         pybind11::arg("kind"),
         pybind11::arg("cb"))
    .def("setSelf",
         static_cast<void(ExporterPython::*)(pybind11::object)>(&ExporterPython::setSelf),
         pybind11::arg("val"))
    .def("setNewOrgRes",
         static_cast<void(ExporterPython::*)(OrgSemKind, ExporterPython::PyFunc)>(&ExporterPython::setNewOrgRes),
         pybind11::arg("kind"),
         pybind11::arg("cb"))
    .def("setNewAnyOrgRes",
         static_cast<void(ExporterPython::*)(ExporterPython::PyFunc)>(&ExporterPython::setNewAnyOrgRes),
         pybind11::arg("cb"))
    .def("setNewLeafRes",
         static_cast<void(ExporterPython::*)(LeafFieldType, ExporterPython::PyFunc)>(&ExporterPython::setNewLeafRes),
         pybind11::arg("kind"),
         pybind11::arg("cb"))
    .def("setNewAnyLeafRes",
         static_cast<void(ExporterPython::*)(ExporterPython::PyFunc)>(&ExporterPython::setNewAnyLeafRes),
         pybind11::arg("cb"))
    .def("setPushVisitAnyId",
         static_cast<void(ExporterPython::*)(ExporterPython::PyFunc)>(&ExporterPython::setPushVisitAnyId),
         pybind11::arg("cb"))
    .def("setPopVisitAnyId",
         static_cast<void(ExporterPython::*)(ExporterPython::PyFunc)>(&ExporterPython::setPopVisitAnyId),
         pybind11::arg("cb"))
    .def("setPushVisitId",
         static_cast<void(ExporterPython::*)(OrgSemKind, ExporterPython::PyFunc)>(&ExporterPython::setPushVisitId),
         pybind11::arg("kind"),
         pybind11::arg("cb"))
    .def("setPopVisitIdCb",
         static_cast<void(ExporterPython::*)(OrgSemKind, ExporterPython::PyFunc)>(&ExporterPython::setPopVisitIdCb),
         pybind11::arg("kind"),
         pybind11::arg("cb"))
    .def("setVisitAnyHookCb",
         static_cast<void(ExporterPython::*)(ExporterPython::PyFunc)>(&ExporterPython::setVisitAnyHookCb),
         pybind11::arg("cb"))
    .def("setVisitIdHook",
         static_cast<void(ExporterPython::*)(OrgSemKind, ExporterPython::PyFunc)>(&ExporterPython::setVisitIdHook),
         pybind11::arg("kind"),
         pybind11::arg("cb"))
    .def("evalTop",
         static_cast<ExporterPython::Res(ExporterPython::*)(sem::SemId<sem::Org>)>(&ExporterPython::evalTop),
         pybind11::arg("org"))
    .def("eval",
         static_cast<ExporterPython::Res(ExporterPython::*)(sem::SemId<sem::Org>)>(&ExporterPython::eval),
         pybind11::arg("org"))
    .def("__repr__", [](ExporterPython _self) -> std::string {
                     return py_repr_impl(_self);
                     })
    .def("__getattr__",
         [](ExporterPython _self, std::string name) -> pybind11::object {
         return py_getattr_impl(_self, name);
         },
         pybind11::arg("name"))
    ;
  bind_enum_iterator<LeafFieldType>(m, "LeafFieldType", type_registry_guard);
  pybind11::enum_<LeafFieldType>(m, "LeafFieldType")
    .value("Int", LeafFieldType::Int)
    .value("UserTimeKind", LeafFieldType::UserTimeKind)
    .value("QDate", LeafFieldType::QDate)
    .value("Bool", LeafFieldType::Bool)
    .value("FixedIdVec", LeafFieldType::FixedIdVec)
    .value("TopIdVec", LeafFieldType::TopIdVec)
    .value("QDateTime", LeafFieldType::QDateTime)
    .value("Str", LeafFieldType::Str)
    .value("Any", LeafFieldType::Any)
    .def("__iter__", [](LeafFieldType _self) -> PyEnumIterator<LeafFieldType> {
                     return
                     PyEnumIterator<LeafFieldType>
                     ();
                     })
    ;
  m.def("newSemTimeStatic",
        static_cast<sem::SemId<sem::Time>(*)(UserTimeBreakdown const&, bool)>(&sem::newSemTimeStatic),
        pybind11::arg("breakdown"),
        pybind11::arg_v("isActive", 0));
  m.def("parseFile",
        static_cast<sem::SemId<sem::Document>(*)(std::string, sem::OrgParseParameters const&)>(&sem::parseFile),
        pybind11::arg("file"),
        pybind11::arg("opts"));
  m.def("parseString",
        static_cast<sem::SemId<sem::Document>(*)(std::string const)>(&sem::parseString),
        pybind11::arg("text"));
  m.def("parseStringOpts",
        static_cast<sem::SemId<sem::Document>(*)(std::string const, sem::OrgParseParameters const&)>(&sem::parseStringOpts),
        pybind11::arg("text"),
        pybind11::arg("opts"));
  m.def("asOneNode",
        static_cast<sem::SemId<sem::Org>(*)(sem::OrgArg)>(&sem::asOneNode),
        pybind11::arg("arg"));
  m.def("formatToString",
        static_cast<std::string(*)(sem::SemId<sem::Org>)>(&sem::formatToString),
        pybind11::arg("arg"));
  m.def("exportToYamlString",
        static_cast<std::string(*)(sem::SemId<sem::Org> const&, sem::OrgYamlExportOpts const&)>(&sem::exportToYamlString),
        pybind11::arg("node"),
        pybind11::arg("opts"));
  m.def("exportToYamlFile",
        static_cast<void(*)(sem::SemId<sem::Org> const&, std::string, sem::OrgYamlExportOpts const&)>(&sem::exportToYamlFile),
        pybind11::arg("node"),
        pybind11::arg("path"),
        pybind11::arg("opts"));
  m.def("exportToJsonString",
        static_cast<std::string(*)(sem::SemId<sem::Org> const&)>(&sem::exportToJsonString),
        pybind11::arg("node"));
  m.def("exportToJsonFile",
        static_cast<void(*)(sem::SemId<sem::Org> const&, std::string)>(&sem::exportToJsonFile),
        pybind11::arg("node"),
        pybind11::arg("path"));
  m.def("readProtobufFile",
        static_cast<sem::SemId<sem::Document>(*)(std::string const&)>(&sem::readProtobufFile),
        pybind11::arg("file"));
  m.def("exportToProtobufFile",
        static_cast<void(*)(sem::SemId<sem::Document>, std::string const&)>(&sem::exportToProtobufFile),
        pybind11::arg("doc"),
        pybind11::arg("file"));
  m.def("exportToTreeString",
        static_cast<std::string(*)(sem::SemId<sem::Org> const&, sem::OrgTreeExportOpts const&)>(&sem::exportToTreeString),
        pybind11::arg("node"),
        pybind11::arg("opts"));
  m.def("exportToTreeFile",
        static_cast<void(*)(sem::SemId<sem::Org> const&, std::string, sem::OrgTreeExportOpts const&)>(&sem::exportToTreeFile),
        pybind11::arg("node"),
        pybind11::arg("path"),
        pybind11::arg("opts"));
  m.def("annotateSequence",
        static_cast<Vec<SequenceAnnotation>(*)(Vec<SequenceSegmentGroup> const&, int, int)>(&annotateSequence),
        pybind11::arg("groups"),
        pybind11::arg("first"),
        pybind11::arg("last"));
  m.def("eachSubnodeRec",
        static_cast<void(*)(sem::SemId<sem::Org>, pybind11::function)>(&eachSubnodeRec),
        pybind11::arg("node"),
        pybind11::arg("callback"));
}
/* clang-format on */