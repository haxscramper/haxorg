#pragma once
// Separate reflection tool will collect the attributes, regular clang
// process does not need to run with a plugin enabled
#pragma clang diagnostic ignored "-Wunknown-attributes"

#undef slots
#include <pybind11/pybind11.h>
#include <haxorg/sem/SemOrg.hpp>
#include <pybind11/stl.h>
#include <hstd/stdlib/Yaml.hpp>
#include <hstd/stdlib/Json.hpp>

#include <haxorg/sem/SemConvert.hpp>
#include <haxorg/parse/OrgParser.hpp>
#include <haxorg/parse/OrgTokenizer.hpp>
#include <haxorg/parse/OrgTypes.hpp>
#include <haxorg/exporters/Exporter.hpp>


#include <SemOrgProto.pb.h>
#include <py_libs/py_type_casters.hpp>
#include <py_libs/pybind11_utils.hpp>

#include <frameobject.h>
#include <haxorg/sem/SemBaseApi.hpp>
#include <hstd/stdlib/RangeSegmentation.hpp>


PYBIND11_DECLARE_HOLDER_TYPE(T, org::sem::SemId<T>);

namespace py = pybind11;

namespace org::bind::python {

std::vector<org::sem::SemId<org::sem::Org>> getSubnodeRange(
    org::sem::SemId<org::sem::Org> id,
    pybind11::slice                slice);
org::sem::SemId<org::sem::Org> getSingleSubnode(
    org::sem::SemId<org::sem::Org> id,
    int                            index);

[[refl]] void eachSubnodeRec(
    org::sem::SemId<org::sem::Org> node,
    py::function                   callback);

[[refl]] void eachSubnodeRecSimplePath(
    org::sem::SemId<org::sem::Org> node,
    py::function                   callback);

enum class [[refl]] LeafFieldType
{
    Int,
    UserTimeKind,
    QDate,
    Bool,
    FixedIdVec,
    TopIdVec,
    QDateTime,
    Str,
    Any
};

} // namespace org::bind::python

template <>
struct hstd::value_domain<org::bind::python::LeafFieldType>
    : value_domain_ungapped<
          org::bind::python::LeafFieldType,
          org::bind::python::LeafFieldType::Int,
          org::bind::python::LeafFieldType::Any> {};


namespace org::bind::python {
template <typename T>
struct LeafKindForT;

template <typename T, LeafFieldType kind>
struct LeafKindForBase {
    static const LeafFieldType value = kind;
};

template <>
struct LeafKindForT<int> : LeafKindForBase<int, LeafFieldType::Int> {};


template <>
struct LeafKindForT<hstd::Str>
    : LeafKindForBase<hstd::Str, LeafFieldType::Str> {};

template <>
struct LeafKindForT<bool> : LeafKindForBase<bool, LeafFieldType::Bool> {};

template <>
struct LeafKindForT<hstd::Vec<org::sem::SemId<org::sem::Org>>>
    : LeafKindForBase<
          hstd::Vec<org::sem::SemId<org::sem::Org>>,
          LeafFieldType::TopIdVec> {};

template <org::sem::IsOrg T>
struct LeafKindForT<hstd::Vec<org::sem::SemId<T>>>
    : LeafKindForBase<
          hstd::Vec<org::sem::SemId<T>>,
          LeafFieldType::FixedIdVec> {};

template <typename T>
struct LeafKindForT : LeafKindForBase<T, LeafFieldType::Any> {};


class PythonStreamDevice {
  public:
    PythonStreamDevice(py::object py_stream) : stream(py_stream) {
        write = stream.attr("write");
    }

  private:
    py::function write;
    py::object   stream;
};

template <typename... Ts>
struct FixedTypeUnion {
    template <typename T>
    static constexpr bool contains = (std::same_as<T, Ts> || ...);
};

template <typename T, typename... Ts>
concept IsOneOf = FixedTypeUnion<Ts...>::template contains<
    std::remove_cvref_t<T>>;

struct [[refl]] ExporterPython
    : org::algo::Exporter<ExporterPython, py::object> {
    using Base = org::algo::Exporter<ExporterPython, py::object>;
#define __ExporterBase Base
    EXPORTER_USING()
#undef __ExporterBase

    BOOST_DESCRIBE_CLASS(ExporterPython, (), (), (), ());

    using PyFunc     = py::function;
    using Res        = py::object;
    using SemCbMap   = hstd::UnorderedMap<OrgSemKind, PyFunc>;
    using FieldCbMap = hstd::UnorderedMap<LeafFieldType, PyFunc>;

    std::string describe(PyFunc const& func) const;
    std::string describe_use(std::string const& msg, PyFunc const& usage)
        const;


    using VK = VisitReport::Kind;

    void trace_no_cb(
        VK               kind,
        org::sem::OrgArg node,
        int              line     = __builtin_LINE(),
        char const*      function = __builtin_FUNCTION()) {
        trace_instant(
            trace(kind)
                .with_node(node)
                .with_loc(line, function)
                .with_msg(hstd::fmt(
                    "no callback for node kind {}", node->getKind())));
    }

    VisitScope trace_leaf(
        VK                 kind,
        org::sem::OrgArg   node,
        std::string const& msg,
        PyFunc const&      cb,
        int                line     = __builtin_LINE(),
        char const*        function = __builtin_FUNCTION()) {
        return trace_instant(trace(kind)
                                 .with_node(node)
                                 .with_msg(describe_use(msg, cb))
                                 .with_loc(line, function));
    }

    VisitScope trace_scoped(
        VK                 kind,
        org::sem::OrgArg   node,
        std::string const& msg,
        PyFunc const&      cb,
        int                line     = __builtin_LINE(),
        char const*        function = __builtin_FUNCTION()) {
        return trace_scope(trace(kind)
                               .with_node(node)
                               .with_msg(describe_use(msg, cb))
                               .with_loc(line, function));
    }

    [[refl]] void        enableBufferTrace();
    [[refl]] std::string getTraceBuffer() const;
    [[refl]] void enableFileTrace(std::string const& path, bool colored);

    hstd::Opt<PyFunc> visitAnyNodeAround;
    [[refl]] void     setVisitAnyIdAround(PyFunc cb) {
        visitAnyNodeAround = cb;
    }

    hstd::Opt<PyFunc> visitAnyNodeIn;
    [[refl]] void     setVisitAnyIdIn(PyFunc cb) { visitAnyNodeIn = cb; }

    hstd::Opt<PyFunc> visitAnyField;
    [[refl]] void     setVisitAnyField(PyFunc cb) { visitAnyField = cb; }

    hstd::Opt<PyFunc> evalTopCb;
    [[refl]] void     setEvalTopCb(PyFunc cb) { evalTopCb = cb; }

    SemCbMap      visitIdAroundCb;
    [[refl]] void setVisitIdAround(OrgSemKind kind, PyFunc cb) {
        visitIdAroundCb[kind] = cb;
    }

    SemCbMap      evalIdAroundCb;
    [[refl]] void setEvalIdAround(OrgSemKind kind, PyFunc cb) {
        evalIdAroundCb[kind] = cb;
    }

    SemCbMap      visitIdInCb;
    [[refl]] void setVisitIdInCb(OrgSemKind kind, PyFunc cb) {
        visitIdInCb[kind] = cb;
    }

    SemCbMap      evalIdInCb;
    [[refl]] void setEvalIdIn(OrgSemKind kind, PyFunc cb) {
        evalIdInCb[kind] = cb;
    }

    FieldCbMap    visitLeafFieldCb;
    [[refl]] void setVisitLeafField(
        org::bind::python::LeafFieldType kind,
        PyFunc                           cb) {
        visitLeafFieldCb[kind] = cb;
    }

    FieldCbMap    evalLeafFieldCb;
    [[refl]] void setEvalLeafField(
        org::bind::python::LeafFieldType kind,
        PyFunc                           cb) {
        evalLeafFieldCb[kind] = cb;
    }

    SemCbMap      visitOrgFieldCb;
    [[refl]] void setVisitOrgField(OrgSemKind kind, PyFunc cb) {
        visitOrgFieldCb[kind] = cb;
    }

    SemCbMap      evalOrgFieldCb;
    [[refl]] void setEvalOrgField(OrgSemKind kind, PyFunc cb) {
        evalOrgFieldCb[kind] = cb;
    }

    py::object    _self;
    [[refl]] void setSelf(py::object val) { _self = val; }


    SemCbMap      newOrgResCb;
    [[refl]] void setNewOrgRes(OrgSemKind kind, PyFunc cb) {
        newOrgResCb[kind] = cb;
    }

    hstd::Opt<PyFunc> newAnyOrgResCb;
    [[refl]] void     setNewAnyOrgRes(PyFunc cb) { newAnyOrgResCb = cb; }

    FieldCbMap    newLeafResCb;
    [[refl]] void setNewLeafRes(
        org::bind::python::LeafFieldType kind,
        PyFunc                           cb) {
        newLeafResCb[kind] = cb;
    }

    hstd::Opt<PyFunc> newAnyLeafResCb;
    [[refl]] void     setNewAnyLeafRes(PyFunc cb) { newAnyLeafResCb = cb; }

    hstd::Opt<PyFunc> pushVisitAnyIdCb;
    [[refl]] void setPushVisitAnyId(PyFunc cb) { pushVisitAnyIdCb = cb; }

    hstd::Opt<PyFunc> popVisitAnyIdCb;
    [[refl]] void     setPopVisitAnyId(PyFunc cb) { popVisitAnyIdCb = cb; }

    SemCbMap      pushVisitIdCb;
    [[refl]] void setPushVisitId(OrgSemKind kind, PyFunc cb) {
        pushVisitIdCb[kind] = cb;
    }

    SemCbMap      popVisitIdCb;
    [[refl]] void setPopVisitIdCb(OrgSemKind kind, PyFunc cb) {
        popVisitIdCb[kind] = cb;
    }

    hstd::Opt<PyFunc> visitAnyHookCb;
    [[refl]] void     setVisitAnyHookCb(PyFunc cb) { visitAnyHookCb = cb; }

    SemCbMap      visitIdHookCb;
    [[refl]] void setVisitIdHook(OrgSemKind kind, PyFunc cb) {
        visitIdHookCb[kind] = cb;
    }

    [[refl]] void print_trace(
        std::string const& trace,
        std::string const& file,
        std::string const& function,
        int                line);

    Res newResImpl(org::sem::OrgArg node);

    Res newRes(org::sem::SemId<org::sem::Org> const& node) {
        return newResImpl(node);
    }

    template <org::sem::IsOrg T>
    Res newRes(org::sem::SemId<T> const& node) {
        return newResImpl(node.asOrg());
    }

    template <org::sem::NotOrg T>
    Res newRes(T const& node) {
        if (newAnyOrgResCb) {
            return newAnyLeafResCb->operator()(_self, node);
        } else if (newLeafResCb.contains(LeafKindForT<T>::value)) {
            trace_instant(
                trace(VK::NewRes)
                    .with_node(node)
                    .with_msg(describe_use(
                        "has callback for kind",
                        newLeafResCb.at(LeafKindForT<T>::value))));
            return newLeafResCb.at(LeafKindForT<T>::value)(_self, node);
        } else {
            trace_instant(
                trace(VK::NewRes)
                    .with_node(node)
                    .with_msg(fmt("no callback for {}", T::staticKind)));
            return py::none();
        }
    }

    template <org::sem::IsOrg T>
    void visitOrgNodeAround(Res& res, org::sem::SemId<T> node) {
        OrgSemKind kind = T::staticKind;
        auto       ev   = trace(VK::VisitValue).with_node(node);
        if (visitAnyNodeAround) {
            trace_instant(ev.with_loc().with_msg(describe_use(
                "has generic around visitor callback",
                *visitAnyNodeAround)));
            visitAnyNodeAround->operator()(_self, res, node);
        } else if (visitIdAroundCb.contains(kind)) {
            trace_instant(ev.with_loc().with_msg(describe_use(
                "has specific around visitor callback",
                visitIdAroundCb.at(kind))));
            visitIdAroundCb.at(kind)(_self, res, node);
        } else if (evalIdAroundCb.contains(kind)) {
            trace_instant(ev.with_loc().with_msg(describe_use(
                "has specific around eval callback",
                evalIdAroundCb.at(kind))));
            res = evalIdAroundCb.at(kind)(_self, node);
        } else {
            trace_instant(ev.with_loc().with_msg("going to dispatched"));
            _this()->visitDispatch(res, node);
        }
    }

    void visitDispatch(Res& res, org::sem::SemId<org::sem::Org> arg);

    template <org::sem::IsOrg T>
    void visitOrgNodeIn(Res& res, org::sem::SemId<T> node) {
        OrgSemKind kind = T::staticKind;
        auto       ev   = trace(VK::VisitSpecificKind).with_node(node);
        if (visitAnyNodeIn) {
            auto __scope = trace_scope(ev.with_loc().with_msg(describe_use(
                "has generic visitor callback", *visitAnyNodeIn)));
            visitAnyNodeIn->operator()(_self, res, node);
        } else if (visitIdInCb.contains(kind)) {
            auto __scope = trace_scope(ev.with_loc().with_msg(describe_use(
                "has specifid visitor callback", visitIdInCb.at(kind))));
            visitIdInCb.at(kind)(_self, res, node);
        } else if (evalIdInCb.contains(kind)) {
            auto __scope = trace_scope(ev.with_loc().with_msg(describe_use(
                "has specifid eval callback", evalIdInCb.at(kind))));

            res = evalIdInCb.at(kind)(_self, node);
        } else {
            auto __scope = trace_scope(
                ev.with_loc().with_msg("deferring to default visitor"));
            switch (kind) {
#define __case(__Kind)                                                    \
    case OrgSemKind::__Kind: {                                            \
        _this()->visit##__Kind(                                           \
            res, node.template as<org::sem::__Kind>());                   \
        break;                                                            \
    }

                EACH_SEM_ORG_KIND(__case)

#undef __case
            }
        }
    }

    template <org::sem::IsOrg T>
    void visitOrgField(
        Res&                      res,
        const char*               name,
        org::sem::SemId<T> const& value) {
        OrgSemKind kind = T::staticKind;
        auto       ev   = trace(VK::VisitField)
                      .with_node(value.asOrg())
                      .with_field(name);

        if (visitAnyField) {
            auto __scope = trace_scope(ev.with_loc().with_msg(
                describe_use("has universal CB", *visitAnyField)));
            visitAnyField->operator()(_self, res, name, value);
        } else if (visitOrgFieldCb.contains(kind)) {
            auto __scope = trace_scope(ev.with_loc().with_msg(describe_use(
                "has specific visitor CB", visitOrgFieldCb.at(kind))));
            visitOrgFieldCb.at(kind)(_self, res, name, value);
        } else if (evalOrgFieldCb.contains(kind)) {
            auto __scope = trace_scope(ev.with_loc().with_msg(describe_use(
                "has specific eval CB", evalOrgFieldCb.at(kind))));

            res = evalOrgFieldCb.at(kind)(_self, name, value);
        } else {
            auto __scope = trace_scope(
                ev.with_loc().with_msg("using default visit"));
            visit(res, value);
        }
    }

#define __fallback_visit(__msg)                                           \
    auto __scope = trace_scope(                                           \
        trace(VK::VisitField).with_field(name).with_msg(__msg));


    template <typename T>
    void fallbackFieldVisitor(
        Res&          res,
        const char*   name,
        hstd::CVec<T> value) {
        __fallback_visit("using fallback field visitor for vector");
        for (T const& it : value) { _this()->visit(res, it); }
    }

    template <typename T>
    void fallbackFieldVisitor(
        Res&         res,
        const char*  name,
        hstd::Opt<T> value) {
        __fallback_visit("using fallback field visitor for vector");
        if (value) { _this()->visit(res, value.value()); }
    }


    template <typename T>
    void fallbackFieldVisitor(Res& res, const char* name, T const& value) {
        __fallback_visit("using empty leaf field visitor callback");
    }


    template <org::sem::NotOrg T>
    void visitOrgField(Res& res, const char* name, T const& value) {
        auto ev = trace(VK::VisitField).with_value(value).with_field(name);

        LeafFieldType kind = LeafKindForT<T>::value;
        if (visitAnyField) {
            auto __scope = trace_scope(ev.with_loc().with_msg(
                describe_use("has universal CB", *visitAnyField)));
            visitAnyField->operator()(_self, res, name, value);
        } else if (visitLeafFieldCb.contains(kind)) {
            auto __scope = trace_scope(ev.with_loc().with_msg(describe_use(
                "has specific visitor CB", visitLeafFieldCb.at(kind))));

            visitLeafFieldCb.at(kind)(_self, res, name, value);
        } else if (evalLeafFieldCb.contains(kind)) {
            auto __scope = trace_scope(ev.with_loc().with_msg(describe_use(
                "has specific eval CB", evalLeafFieldCb.at(kind))));

            res = evalLeafFieldCb.at(kind)(_self, name, value);
        } else {
            _this()->fallbackFieldVisitor(res, name, value);
        }
    }

    template <org::sem::IsOrg T>
    void visitDispatchHook(Res& res, org::sem::SemId<T> id) {
        if (visitAnyHookCb) {
            auto __scope = trace_scoped(
                VK::VisitDispatchHook, id, "universal", *visitAnyHookCb);
            visitAnyHookCb->operator()(_self, res, id);
        } else if (auto cb = visitIdHookCb.get(T::staticKind)) {
            auto __scope = trace_scoped(
                VK::VisitDispatchHook, id, "cb for kind", *cb);
            cb.value()(_self, res, id);
        } else {
            // trace_no_cb(VK::VisitDispatchHook, id);
        }
    }

    void pushVisitImpl(Res& res, org::sem::OrgArg id);

    template <org::sem::IsOrg T>
    void pushVisit(Res& res, org::sem::SemId<T> id) {
        pushVisitImpl(res, id);
    }

    void popVisitImpl(Res& res, org::sem::OrgArg id);

    template <org::sem::IsOrg T>
    void popVisit(Res& res, org::sem::SemId<T> id) {
        popVisitImpl(res, id);
    }

    template <org::sem::IsOrg T>
    void visit(Res& res, org::sem::SemId<T> node) {
        visitOrgNodeAround(res, node);
    }

    void visit(Res& res, org::sem::SemId<org::sem::Org> node) {
        _this()->visitDispatch(res, node);
    }

    void visit(Res& res, org::sem::BlockCodeSwitch const&) {}
    void visit(Res& res, org::sem::Symbol::Param const&) {}
    void visit(Res& res, org::sem::NamedProperty const&) {}
    void visit(Res& res, hstd::Str const&) {}
    void visit(Res& res, hstd::Vec<hstd::Str> const&) {}
    void visit(
        Res& res,
        org::sem::DocumentExportConfig::TocExport const&) {}
    void visit(Res& res, org::sem::Tblfm const&) {}
    void visit(Res& res, org::sem::Tblfm::Assign::Flag const&) {}
    void visit(Res& res, int const&) {}

    template <org::sem::IsOrg T>
    void visitField(Res& res, char const* name, org::sem::SemId<T> value) {
        visitOrgField(res, name, value);
    }

    template <org::sem::NotOrg T>
    void visitField(Res& res, char const* name, T const& value) {
        visitOrgField(res, name, value);
    }

    void visitField(
        Res&                           res,
        char const*                    name,
        org::sem::SemId<org::sem::Org> value);

    [[refl]] Res evalTop(org::sem::SemId<org::sem::Org> org);

    [[refl]] Res eval(org::sem::SemId<org::sem::Org> org) {
        Res tmp = _this()->newRes(org);
        _this()->visit(tmp, org);
        return tmp;
    }
};

void init_py_manual_api(py::module& m);

} // namespace org::bind::python
