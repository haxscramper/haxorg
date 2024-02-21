#pragma once
// Separate reflection tool will collect the attributes, regular clang
// process does not need to run with a plugin enabled
#pragma clang diagnostic ignored "-Wunknown-attributes"

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
#include <exporters/Exporter.hpp>
#include <pybind11/stl_bind.h>

#include <SemOrgProto.pb.h>
#include <py_type_casters.hpp>

#include <frameobject.h>

namespace py = pybind11;

PYBIND11_DECLARE_HOLDER_TYPE(T, sem::SemId<T>);

template <typename T>
void bind_int_set(py::module& m, const char* PyNameType) {
    py::class_<IntSet<T>>(m, (std::string(PyNameType) + "IntVec").c_str())
        .def(py::init([](py::list list) -> IntSet<T> {
            IntSet<T> result;
            for (auto const& it : list) { result.incl(it.cast<T>()); }

            return result;
        }));
}

template <typename T>
void bind_vector(py::module& m, const char* PyNameType) {
    py::bind_vector<std::vector<T>>(
        m, (std::string(PyNameType) + "StdVector").c_str());
    pybind11::class_<Vec<T>, std::vector<T>>(
        m, (std::string(PyNameType) + "Vec").c_str())
        .def(pybind11::init<>())
        .def(pybind11::init<int, const T&>())
        .def(pybind11::init<std::initializer_list<T>>())
        .def(pybind11::init<const Vec<T>&>())
        .def("FromValue", &Vec<T>::FromValue)
        .def("append", (void(Vec<T>::*)(const Vec<T>&)) & Vec<T>::append);
}

template <typename K, typename V>
void bind_mapping(py::module& m, const char* PyNameType) {
    using M = UnorderedMap<K, V>;

    py::bind_map<std::unordered_map<K, V>>(
        m, (std::string(PyNameType) + "StdUnorderedMap").c_str());

    py::class_<UnorderedMap<K, V>, std::unordered_map<K, V>>(
        m, (std::string(PyNameType) + "UnorderedMap").c_str())
        .def(py::init<>())
        .def("contains", &M::contains)
        .def("get", &M::get)
        .def("keys", &M::keys);
}

struct ExporterJson;
struct ExporterYaml;
struct ExporterTree;

std::vector<sem::SemId<sem::Org>> getSubnodeRange(
    sem::SemId<sem::Org> id,
    pybind11::slice      slice);
sem::SemId<sem::Org> getSingleSubnode(sem::SemId<sem::Org> id, int index);

struct [[refl]] OrgExporterJson {
    SPtr<ExporterJson> impl;
    json               result;

    OrgExporterJson();
    /// Visit top-level node of the exporter, filling in the internal
    /// return state.
    [[refl]] void visitNode(sem::SemId<sem::Org> node /*! Input node */);
    [[refl]] std::string exportToString();
    [[refl]] void        exportToFile(std::string path);
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
    ColStream            os;
    [[refl]] std::string toString(
        sem::SemId<sem::Org> node,
        ExporterTreeOpts     opts);
    [[refl]] void toFile(
        sem::SemId<sem::Org> node,
        std::string          path,
        ExporterTreeOpts     opts);

    void stream(
        std::ostream&        stream,
        sem::SemId<sem::Org> node,
        ExporterTreeOpts     opts);
};


struct [[refl]] OrgExporterYaml {
    SPtr<ExporterYaml> impl;
    yaml               result;

    OrgExporterYaml();
    /// Visit top-level node of the exporter, filling in the internal
    /// return state.
    [[refl]] void        visitNode(sem::SemId<sem::Org> node);
    [[refl]] std::string exportToString();
    [[refl]] void        exportToFile(std::string path);
};

struct [[refl]] OrgContext {
    sem::SemId<sem::Document> node = sem::SemId<sem::Document>::Nil();

    OrgContext() {}

    [[refl]] sem::SemId<sem::Document> parseFile(std::string file);
    [[refl]] sem::SemId<sem::Document> parseString(std::string const text);
    [[refl]] sem::SemId<sem::Document> parseProtobuf(
        std::string const& file);
    [[refl]] void saveProtobuf(
        sem::SemId<sem::Document> doc,
        std::string const&        file);
};


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

template <typename T>
struct LeafKindForT;

template <typename T, LeafFieldType kind>
struct LeafKindForBase {
    static const LeafFieldType value = kind;
};

template <>
struct LeafKindForT<int> : LeafKindForBase<int, LeafFieldType::Int> {};


template <>
struct LeafKindForT<Str> : LeafKindForBase<Str, LeafFieldType::Str> {};

template <>
struct LeafKindForT<bool> : LeafKindForBase<bool, LeafFieldType::Bool> {};

template <>
struct LeafKindForT<Vec<sem::SemId<sem::Org>>>
    : LeafKindForBase<Vec<sem::SemId<sem::Org>>, LeafFieldType::TopIdVec> {
};

template <sem::IsOrg T>
struct LeafKindForT<Vec<sem::SemId<T>>>
    : LeafKindForBase<Vec<sem::SemId<T>>, LeafFieldType::FixedIdVec> {};

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

struct [[refl]] ExporterPython : Exporter<ExporterPython, py::object> {
    using Base = Exporter<ExporterPython, py::object>;
#define __ExporterBase Base
    EXPORTER_USING()
#undef __ExporterBase

    using PyFunc     = py::function;
    using Res        = py::object;
    using SemCbMap   = UnorderedMap<OrgSemKind, PyFunc>;
    using FieldCbMap = UnorderedMap<LeafFieldType, PyFunc>;

    Opt<OperationsTracer> exportTracer;

    ColStream                traceStream;
    std::string              traceBuffer;
    SPtr<PythonStreamDevice> pyStreamDevice;
    SPtr<IoContext>          writeStreamContext;

    [[refl]] void        enablePyStreamTrace(py::object stream);
    [[refl]] void        enableBufferTrace();
    [[refl]] std::string getTraceBuffer() const;
    [[refl]] void enableFileTrace(std::string const& path, bool colored);

    Opt<PyFunc>   visitAnyNodeAround;
    [[refl]] void setVisitAnyIdAround(PyFunc cb) {
        visitAnyNodeAround = cb;
    }

    Opt<PyFunc>   visitAnyNodeIn;
    [[refl]] void setVisitAnyIdIn(PyFunc cb) { visitAnyNodeIn = cb; }

    Opt<PyFunc>   visitAnyField;
    [[refl]] void setVisitAnyField(PyFunc cb) { visitAnyField = cb; }

    Opt<PyFunc>   evalTopCb;
    [[refl]] void setEvalTopCb(PyFunc cb) { evalTopCb = cb; }

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
    [[refl]] void setVisitLeafField(LeafFieldType kind, PyFunc cb) {
        visitLeafFieldCb[kind] = cb;
    }

    FieldCbMap    evalLeafFieldCb;
    [[refl]] void setEvalLeafField(LeafFieldType kind, PyFunc cb) {
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

    Opt<PyFunc>   newAnyOrgResCb;
    [[refl]] void setNewAnyOrgRes(PyFunc cb) { newAnyOrgResCb = cb; }

    FieldCbMap    newLeafResCb;
    [[refl]] void setNewLeafRes(LeafFieldType kind, PyFunc cb) {
        newLeafResCb[kind] = cb;
    }

    Opt<PyFunc>   newAnyLeafResCb;
    [[refl]] void setNewAnyLeafRes(PyFunc cb) { newAnyLeafResCb = cb; }

    Opt<PyFunc>   pushVisitAnyIdCb;
    [[refl]] void setPushVisitAnyId(PyFunc cb) { pushVisitAnyIdCb = cb; }

    Opt<PyFunc>   popVisitAnyIdCb;
    [[refl]] void setPopVisitAnyId(PyFunc cb) { popVisitAnyIdCb = cb; }

    SemCbMap      pushVisitIdCb;
    [[refl]] void setPushVisitId(OrgSemKind kind, PyFunc cb) {
        pushVisitIdCb[kind] = cb;
    }

    SemCbMap      popVisitIdCb;
    [[refl]] void setPopVisitIdCb(OrgSemKind kind, PyFunc cb) {
        popVisitIdCb[kind] = cb;
    }

    Opt<PyFunc>   visitAnyHookCb;
    [[refl]] void setVisitAnyHookCb(PyFunc cb) { visitAnyHookCb = cb; }

    SemCbMap      visitIdHookCb;
    [[refl]] void setVisitIdHook(OrgSemKind kind, PyFunc cb) {
        visitIdHookCb[kind] = cb;
    }

    Res newRes(sem::SemId<sem::Org> const& node) {
        if (newAnyOrgResCb) {
            __visit_scope(
                VisitEvent::Kind::NewRes,
                .visitedNode = node,
                .msg         = "has universal CB");
            return newAnyOrgResCb->operator()(_self, node);
        } else if (newOrgResCb.contains(node->getKind())) {
            __visit_scope(
                VisitEvent::Kind::NewRes,
                .visitedNode = node,
                .msg         = "has callback for kind");
            return newOrgResCb.at(node->getKind())(_self, node);
        } else {
            __visit_scope(
                VisitEvent::Kind::NewRes,
                .visitedNode = node,
                .msg = ("no callback for " + fmt1(node->getKind())));
            return py::none();
        }
    }

    template <sem::IsOrg T>
    Res newRes(sem::SemId<T> const& node) {
        if (newAnyOrgResCb) {
            __visit_scope(
                VisitEvent::Kind::NewRes,
                .visitedNode = node,
                .msg         = "has universal CB");
            return newAnyOrgResCb->operator()(_self, node);
        } else if (newOrgResCb.contains(T::staticKind)) {
            __visit_scope(
                VisitEvent::Kind::NewRes,
                .visitedNode = node,
                .msg         = "has callback for kind");
            return newOrgResCb.at(T::staticKind)(_self, node);
        } else {
            __visit_scope(
                VisitEvent::Kind::NewRes,
                .visitedNode = node,
                .msg = ("no callback for " + to_string(T::staticKind)));
            return py::none();
        }
    }

    template <sem::NotOrg T>
    Res newRes(T const& node) {
        if (newAnyOrgResCb) {
            return newAnyLeafResCb->operator()(_self, node);
        } else if (newLeafResCb.contains(LeafKindForT<T>::value)) {
            __visit_scope(
                VisitEvent::Kind::NewRes,
                .visitedNode = node,
                .msg         = "has callback for kind");
            return newLeafResCb.at(LeafKindForT<T>::value)(_self, node);
        } else {
            __visit_scope(
                VisitEvent::Kind::NewRes,
                .visitedNode = node,
                .msg = ("no callback for " + to_string(T::staticKind)));
            return py::none();
        }
    }

    template <sem::IsOrg T>
    void visitOrgNodeAround(Res& res, sem::SemId<T> node) {
        OrgSemKind kind = T::staticKind;
        if (visitAnyNodeAround) {
            __visit_scope(
                VisitEvent::Kind::VisitValue,
                .visitedNode = node,
                .msg         = "has generic around visitor callback");
            visitAnyNodeAround->operator()(_self, res, node);
        } else if (visitIdAroundCb.contains(kind)) {
            __visit_scope(
                VisitEvent::Kind::VisitValue,
                .visitedNode = node,
                .msg         = "has specific around visitor callback");
            visitIdAroundCb.at(kind)(_self, res, node);
        } else if (evalIdAroundCb.contains(kind)) {
            __visit_scope(
                VisitEvent::Kind::VisitValue,
                .visitedNode = node,
                .msg         = "has specific around eval callback");
            res = evalIdAroundCb.at(kind)(_self, node);
        } else {
            __visit_scope(
                VisitEvent::Kind::VisitValue,
                .visitedNode = node,
                .msg         = "going to dispatched");
            _this()->visitDispatch(res, node);
        }
    }

    void visitDispatch(Res& res, sem::SemId<sem::Org> arg);

    template <sem::IsOrg T>
    void visitOrgNodeIn(Res& res, sem::SemId<T> node) {
        OrgSemKind kind = T::staticKind;
        if (visitAnyNodeIn) {
            __visit_scope(
                VisitEvent::Kind::VisitSpecificKind,
                .visitedNode = node,
                .msg         = "has generic visitor callback");
            visitAnyNodeIn->operator()(_self, res, node);
        } else if (visitIdInCb.contains(kind)) {
            __visit_scope(
                VisitEvent::Kind::VisitSpecificKind,
                .visitedNode = node,
                .msg         = "has specifid visitor callback");
            visitIdInCb.at(kind)(_self, res, node);
        } else if (evalIdInCb.contains(kind)) {
            __visit_scope(
                VisitEvent::Kind::VisitSpecificKind,
                .visitedNode = node,
                .msg         = "has specifid eval callback");
            res = evalIdInCb.at(kind)(_self, node);
        } else {
            __visit_scope(
                VisitEvent::Kind::VisitSpecificKind,
                .visitedNode = node,
                .msg         = "deferring to default visitor");
            switch (kind) {
#define __case(__Kind)                                                    \
    case OrgSemKind::__Kind: {                                            \
        _this()->visit##__Kind(res, node.template as<sem::__Kind>());     \
        break;                                                            \
    }

                EACH_SEM_ORG_KIND(__case)

#undef __case
            }
        }
    }

    void traceVisit(ExporterPython::VisitEvent const& ev);

    template <sem::IsOrg T>
    void visitOrgField(
        Res&                 res,
        const char*          name,
        sem::SemId<T> const& value) {
        OrgSemKind kind = T::staticKind;
        if (visitAnyField) {
            __visit_scope(
                VisitEvent::Kind::VisitField,
                .visitedValue = &res,
                .field        = std::string(name),
                .visitedNode  = value.asOrg(),
                .msg          = "has universal CB");

            visitAnyField->operator()(_self, res, name, value);
        } else if (visitOrgFieldCb.contains(kind)) {
            __visit_scope(
                VisitEvent::Kind::VisitField,
                .visitedValue = &res,
                .field        = std::string(name),
                .visitedNode  = value.asOrg(),
                .msg          = "has specific visitor CB");

            visitOrgFieldCb.at(kind)(_self, res, name, value);
        } else if (evalOrgFieldCb.contains(kind)) {
            __visit_scope(
                VisitEvent::Kind::VisitField,
                .visitedValue = &res,
                .field        = std::string(name),
                .visitedNode  = value.asOrg(),
                .msg          = "has specific eval CB");

            res = evalOrgFieldCb.at(kind)(_self, name, value);
        } else {
            __visit_scope(
                VisitEvent::Kind::VisitField,
                .visitedValue = &res,
                .field        = std::string(name),
                .visitedNode  = value.asOrg(),
                .msg          = "using default visit");

            visit(res, value);
        }
    }

#define __fallback_visit(__msg)                                           \
    __visit_scope(                                                        \
        VisitEvent::Kind::VisitField,                                     \
        .visitedValue = &res,                                             \
        .field        = std::string(name),                                \
        .msg          = __msg);


    template <typename T>
    void fallbackFieldVisitor(Res& res, const char* name, CVec<T> value) {
        __fallback_visit("using fallback field visitor for vector");
        for (T const& it : value) { _this()->visit(res, it); }
    }

    template <typename T>
    void fallbackFieldVisitor(Res& res, const char* name, Opt<T> value) {
        __fallback_visit("using fallback field visitor for vector");
        if (value) { _this()->visit(res, value.value()); }
    }


    template <typename T>
    void fallbackFieldVisitor(Res& res, const char* name, T const& value) {
        __fallback_visit("using empty leaf field visitor callback");
    }


    template <sem::NotOrg T>
    void visitOrgField(Res& res, const char* name, T const& value) {
        LeafFieldType kind = LeafKindForT<T>::value;
        if (visitAnyField) {
            __visit_scope(
                VisitEvent::Kind::VisitField,
                .visitedValue = &res,
                .field        = std::string(name),
                .msg          = "has universal CB");

            visitAnyField->operator()(_self, res, name, value);
        } else if (visitLeafFieldCb.contains(kind)) {
            __visit_scope(
                VisitEvent::Kind::VisitField,
                .visitedValue = &res,
                .field        = std::string(name),
                .msg          = "has specific visitor CB");

            visitLeafFieldCb.at(kind)(_self, res, name, value);
        } else if (evalLeafFieldCb.contains(kind)) {
            __visit_scope(
                VisitEvent::Kind::VisitField,
                .visitedValue = &res,
                .field        = std::string(name),
                .msg          = "has specific eval CB");

            res = evalLeafFieldCb.at(kind)(_self, name, value);
        } else {
            _this()->fallbackFieldVisitor(res, name, value);
        }
    }

    template <sem::IsOrg T>
    void visitDispatchHook(Res& res, sem::SemId<T> id) {
        if (visitAnyHookCb) {
            __visit_scope(
                VisitEvent::Kind::VisitDispatchHook,
                .visitedValue = &res,
                .visitedNode  = id,
                .msg          = "has universal CB");


            visitAnyHookCb->operator()(_self, res, id);
        } else if (visitIdHookCb.contains(T::staticKind)) {
            __visit_scope(
                VisitEvent::Kind::VisitDispatchHook,
                .visitedValue = &res,
                .visitedNode  = id,
                .msg          = "has fixed CB");


            visitIdHookCb.at(T::staticKind)(_self, res, id);
        } else {
            __visit_scope(
                VisitEvent::Kind::VisitDispatchHook,
                .visitedValue = &res,
                .visitedNode  = id,
                .msg = ("no callback for " + fmt1(T::staticKind)));
        }
    }

    template <sem::IsOrg T>
    void pushVisit(Res& res, sem::SemId<T> id) {
        __visit_scope(
            VisitEvent::Kind::PushVisit,
            .visitedValue = &res,
            .visitedNode  = id);
        if (pushVisitAnyIdCb) {
            pushVisitAnyIdCb->operator()(_self, res, id);
        } else if (pushVisitIdCb.contains(T::staticKind)) {
            pushVisitIdCb.at(T::staticKind)(_self, res, id);
        }
    }

    template <sem::IsOrg T>
    void popVisit(Res& res, sem::SemId<T> id) {
        if (popVisitAnyIdCb) {
            __visit_scope(
                VisitEvent::Kind::PopVisit,
                .visitedValue = &res,
                .visitedNode  = id,
                .msg          = "has universal CB");

            popVisitAnyIdCb->operator()(_self, res, id);
        } else if (popVisitIdCb.contains(T::staticKind)) {
            __visit_scope(
                VisitEvent::Kind::PopVisit,
                .visitedValue = &res,
                .visitedNode  = id,
                .msg          = "has fixed CB");

            popVisitIdCb.at(T::staticKind)(_self, res, id);
        } else {
            __visit_scope(
                VisitEvent::Kind::PopVisit,
                .visitedValue = &res,
                .visitedNode  = id,
                .msg = ("no callback for " + fmt1(T::staticKind)));
        }
    }

    template <sem::IsOrg T>
    void visit(Res& res, sem::SemId<T> node) {
        visitOrgNodeAround(res, node);
    }

    void visit(Res& res, sem::SemId<sem::Org> node) {
        _this()->visitDispatch(res, node);
    }

    void visit(Res& res, sem::Code::Switch const&) {}
    void visit(Res& res, sem::Symbol::Param const&) {}
    void visit(Res& res, sem::Subtree::Property const&) {}
    void visit(Res& res, Str const&) {}
    void visit(Res& res, Vec<Str> const&) {}
    void visit(Res& res, sem::DocumentOptions::TocExport const&) {}
    void visit(Res& res, int const&) {}

    template <sem::IsOrg T>
    void visitField(Res& res, char const* name, sem::SemId<T> value) {
        visitOrgField(res, name, value);
    }

    template <sem::NotOrg T>
    void visitField(Res& res, char const* name, T const& value) {
        visitOrgField(res, name, value);
    }

    void visitField(
        Res&                 res,
        char const*          name,
        sem::SemId<sem::Org> value);

    [[refl]] Res evalTop(sem::SemId<sem::Org> org);

    [[refl]] Res eval(sem::SemId<sem::Org> org) {
        Res tmp = _this()->newRes(org);
        _this()->visit(tmp, org);
        return tmp;
    }
};

void init_py_manual_api(py::module& m);
