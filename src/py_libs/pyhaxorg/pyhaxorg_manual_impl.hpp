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
#include <exporters/Exporter.hpp>

#include <py_type_casters.hpp>

#include <frameobject.h>


namespace py = pybind11;

struct ExporterJson;
struct ExporterYaml;
struct ExporterTree;

#define __id(I) , sem::SemIdT<sem::I>
/// \brief Global variant of all sem node derivations
using OrgIdVariant = std::variant<EACH_SEM_ORG_KIND_CSV(__id)>;
#undef __id

OrgIdVariant castAs(sem::SemId id);

std::vector<sem::SemId> getSubnodeRange(
    sem::SemId      id,
    pybind11::slice slice);
sem::SemId getSingleSubnode(sem::SemId id, int index);

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

    [[refl]] void initLocationResolvers();

    void run();


    [[refl]] void parseFile(std::string file) {
        source = readFile(QFileInfo(QString::fromStdString(file)));
        run();
    }

    [[refl]] void loadStore(QString path);

    [[refl]] void writeStore(QString path);

    [[refl]] void parseString(QString text) {
        source = text;
        run();
    }


    [[refl]] sem::SemIdT<sem::Document> getNode() { return node; }
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
struct LeafKindForT<UserTime::Kind>
    : LeafKindForBase<UserTime::Kind, LeafFieldType::UserTimeKind> {};

template <>
struct LeafKindForT<QDate>
    : LeafKindForBase<QDate, LeafFieldType::QDate> {};

template <>
struct LeafKindForT<QDateTime>
    : LeafKindForBase<QDateTime, LeafFieldType::QDateTime> {};

template <>
struct LeafKindForT<Str> : LeafKindForBase<Str, LeafFieldType::Str> {};

template <>
struct LeafKindForT<bool> : LeafKindForBase<bool, LeafFieldType::Bool> {};

template <>
struct LeafKindForT<Vec<sem::SemId>>
    : LeafKindForBase<Vec<sem::SemId>, LeafFieldType::TopIdVec> {};

template <sem::IsOrg T>
struct LeafKindForT<Vec<sem::SemIdT<T>>>
    : LeafKindForBase<Vec<sem::SemIdT<T>>, LeafFieldType::FixedIdVec> {};

template <typename T>
struct LeafKindForT : LeafKindForBase<T, LeafFieldType::Any> {};


class PythonStreamDevice : public QIODevice {
  public:
    PythonStreamDevice(py::object py_stream, QObject* parent = nullptr)
        : QIODevice(parent), stream(py_stream) {
        open(QIODevice::WriteOnly);
        write = stream.attr("write");
    }

  protected:
    qint64 writeData(const char* data, qint64 len) override {
        write(std::string(data, len));
        return len;
    }

    qint64 readData(char* /*data*/, qint64 /*len*/) override { return -1; }

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
    QString                  traceBuffer;
    SPtr<PythonStreamDevice> pyStreamDevice;
    SPtr<IoContext>          writeStreamContext;

    [[refl]] void    enablePyStreamTrace(py::object stream);
    [[refl]] void    enableBufferTrace();
    [[refl]] QString getTraceBuffer() const;
    [[refl]] void    enableFileTrace(QString const& path);

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

    Res newRes(sem::SemId const& node) {
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
                .msg = ("no callback for " + to_string(node->getKind())));
            return py::none();
        }
    }

    template <sem::IsOrg T>
    Res newRes(sem::SemIdT<T> const& node) {
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
    void visitOrgNodeAround(Res& res, sem::SemIdT<T> node) {
        OrgSemKind kind = T::staticKind;
        if (visitAnyNodeAround) {
            visitAnyNodeAround->operator()(_self, res, node);
        } else if (visitIdAroundCb.contains(kind)) {
            visitIdAroundCb.at(kind)(_self, res, node);
        } else if (evalIdAroundCb.contains(kind)) {
            res = evalIdAroundCb.at(kind)(_self, node);
        } else {
            _this()->visitDispatch(res, node);
        }
    }

    void visitDispatch(Res& res, sem::SemId arg);

    template <sem::IsOrg T>
    void visitOrgNodeIn(Res& res, sem::SemIdT<T> node) {
        OrgSemKind kind = T::staticKind;
        if (visitAnyNodeIn) {
            visitAnyNodeIn->operator()(_self, res, node);
        } else if (visitIdInCb.contains(kind)) {
            visitIdInCb.at(kind)(_self, res, node);
        } else if (evalIdInCb.contains(kind)) {
            res = evalIdInCb.at(kind)(_self, node);
        } else {
            switch (kind) {
#define __case(__Kind)                                                    \
    case OrgSemKind::__Kind: {                                            \
        _this()->visit##__Kind(res, node);                                \
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
        Res&                  res,
        const char*           name,
        sem::SemIdT<T> const& value) {
        OrgSemKind kind = T::staticKind;
        if (visitAnyField) {
            visitAnyField->operator()(_self, res, name, value);
        } else if (visitOrgFieldCb.contains(kind)) {
            visitOrgFieldCb.at(kind)(_self, res, name, value);
        } else if (evalOrgFieldCb.contains(kind)) {
            res = evalOrgFieldCb.at(kind)(_self, name, value);
        } else {
            visit(res, value);
        }
    }

    template <sem::NotOrg T>
    void visitOrgField(Res& res, const char* name, T const& value) {
        LeafFieldType kind = LeafKindForT<T>::value;
        if (visitAnyField) {
            visitAnyField->operator()(_self, res, name, value);
        } else if (visitLeafFieldCb.contains(kind)) {
            visitLeafFieldCb.at(kind)(_self, res, name, value);
        } else if (evalLeafFieldCb.contains(kind)) {
            res = evalLeafFieldCb.at(kind)(_self, name, value);
        }
    }

    template <sem::IsOrg T>
    void visitDispatchHook(Res& res, sem::SemIdT<T> id) {
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
                .msg = ("no callback for " + to_string(T::staticKind)));
        }
    }

    template <sem::IsOrg T>
    void pushVisit(Res& res, sem::SemIdT<T> id) {
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
    void popVisit(Res& res, sem::SemIdT<T> id) {
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
                .msg = ("no callback for " + to_string(T::staticKind)));
        }
    }

    template <sem::IsOrg T>
    void visit(Res& res, sem::SemIdT<T> node) {
        visitOrgNodeAround(res, node);
    }

    void visit(Res& res, sem::SemId node) {
        _this()->visitDispatch(res, node);
    }


    template <sem::IsOrg T>
    void visitField(Res& res, char const* name, sem::SemIdT<T> value) {
        visitOrgField(res, name, value);
    }

    template <sem::NotOrg T>
    void visitField(Res& res, char const* name, T const& value) {
        visitOrgField(res, name, value);
    }

    void visitField(Res& res, char const* name, sem::SemId value);

    [[refl]] Res evalTop(sem::SemId org);

    [[refl]] Res eval(sem::SemId org) {
        Res tmp = _this()->newRes(org);
        _this()->visit(tmp, org);
        return tmp;
    }
};

void init_py_manual_api(py::module& m);
