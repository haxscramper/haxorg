#include "pyhaxorg_manual_impl.hpp"

#include <exporters/ExporterJson.hpp>
#include <hstd/stdlib/Filesystem.hpp>
#include <exporters/exporteryaml.hpp>
#include <exporters/exportertree.hpp>

#include <memory>

#include <exporters/Exporter.cpp>

template class Exporter<ExporterPython, py::object>;

QTextStream qcout;

OrgExporterJson::OrgExporterJson() {
    impl = std::make_shared<ExporterJson>();
}

QString OrgExporterJson::exportToString() { return to_string(result); }

void OrgExporterJson::exportToFile(QString path) {
    writeFile(QFileInfo(path), exportToString());
}

void OrgExporterJson::visitNode(sem::SemId node) {
    result = impl->evalTop(node);
}

OrgExporterYaml::OrgExporterYaml() {
    impl = std::make_shared<ExporterYaml>();
}

QString OrgExporterYaml::exportToString() { return to_string(result); }

void OrgExporterYaml::exportToFile(QString path) {
    writeFile(QFileInfo(path), exportToString());
}

void OrgExporterYaml::visitNode(sem::SemId node) {
    result = impl->evalTop(node);
}

OrgExporterTree::OrgExporterTree() {
    impl = std::make_shared<ExporterTree>(os);
}

QString OrgExporterTree::toString(sem::SemId node, ExporterTreeOpts opts) {
    QString     buf;
    QTextStream os{&buf};
    stream(os, node, opts);
}

void OrgExporterTree::toFile(
    sem::SemId       node,
    QString          path,
    ExporterTreeOpts opts) {
    auto ctx = openFileOrStream(QFileInfo(path), true);
    stream(*ctx->stream, node, opts);
}

void OrgExporterTree::stream(
    QTextStream&     stream,
    sem::SemId       node,
    ExporterTreeOpts opts) {
    os                         = ColStream{stream};
    os.colored                 = opts.withColor;
    impl->conf.withLineCol     = opts.withLineCol;
    impl->conf.withOriginalId  = opts.withOriginalId;
    impl->conf.skipEmptyFields = opts.skipEmptyFields;
    impl->conf.startLevel      = opts.startLevel;
    impl->evalTop(node);
}

void OrgContext::run() {
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

std::vector<sem::SemId> getSubnodeRange(
    sem::SemId      id,
    pybind11::slice slice) {

    size_t start;
    size_t stop;
    size_t step;
    size_t slicelength;

    Vec<sem::SemId> const& data = id->subnodes;
    if (!slice.compute(data.size(), &start, &stop, &step, &slicelength)) {
        throw py::error_already_set();
    }

    std::vector<sem::SemId> result{slicelength, sem::SemId::Nil()};
    for (size_t i = 0; i < slicelength; ++i) {
        result[i] = data[start];
        start += step;
    }
    return result;
}

sem::SemId getSingleSubnode(sem::SemId id, int index) {
    return id->at(index);
}

OrgIdVariant castAs(sem::SemId id) {
    switch (id->getKind()) {

#define _case(__Kind)                                                     \
    case OrgSemKind::__Kind: {                                            \
        return id.as<sem::__Kind>();                                      \
    }
        EACH_SEM_ORG_KIND(_case)
#undef _case
    }
}

void init_py_manual_api(pybind11::module& m) {
    pybind11::class_<sem::SemId>(m, "SemId")
        .def(pybind11::init(
            []() -> sem::SemId { return sem::SemId::Nil(); }))
        .def("getKind", &sem::SemId::getKind)
        .def(
            "__len__",
            [](sem::SemId const& id) -> int {
                return id->subnodes.size();
            })
        .def(
            "__iter__",
            [](sem::SemId const& id) {
                return py::make_iterator(
                    id->subnodes.begin(), id->subnodes.end());
            })
        .def(
            "__getitem__",
            [](sem::SemId _self, int index) {
                return getSingleSubnode(_self, index);
            })
        .def("__getitem__", [](sem::SemId _self, py::slice slice) {
            return getSubnodeRange(_self, slice);
        });

    ;
}

void ExporterPython::enablePyStreamTrace(pybind11::object stream) {
    pyStreamDevice     = std::make_shared<PythonStreamDevice>(stream);
    writeStreamContext = std::make_shared<IoContext>();
    writeStreamContext->stream      = std::make_shared<QTextStream>();
    this->exportTracer              = OperationsTracer{};
    this->exportTracer->stream      = writeStreamContext->stream;
    this->exportTracer->traceToFile = true;
    writeStreamContext->stream->setDevice(&(*pyStreamDevice));
    this->visitEventCb = [this](ExporterPython::VisitEvent const& ev) {
        this->traceVisit(ev);
    };
}

void ExporterPython::enableBufferTrace() {
    writeStreamContext              = std::make_shared<IoContext>();
    writeStreamContext->stream      = std::make_shared<QTextStream>();
    this->exportTracer->stream      = writeStreamContext->stream;
    this->exportTracer->traceToFile = true;
    writeStreamContext->stream->setString(&traceBuffer);
    this->visitEventCb = [this](ExporterPython::VisitEvent const& ev) {
        this->traceVisit(ev);
    };
}

QString ExporterPython::getTraceBuffer() const { return traceBuffer; }

void ExporterPython::enableFileTrace(const QString& path) {
    writeStreamContext         = openFileOrStream(QFileInfo(path), true);
    traceStream.ostream        = writeStreamContext->stream.get();
    traceStream.colored        = false;
    this->exportTracer         = OperationsTracer{};
    this->exportTracer->stream = writeStreamContext->stream;
    this->exportTracer->traceToFile = true;
    this->visitEventCb = [this](ExporterPython::VisitEvent const& ev) {
        this->traceVisit(ev);
    };
}

void ExporterPython::visitDispatch(Res& res, sem::SemId arg) {
    __visit_scope(
        VisitEvent::Kind::VisitDispatch,
        .visitedValue = &res,
        .visitedNode  = arg);

    if (arg.isNil()) {
        return;
    }

    auto kind = arg->getKind();
    switch (kind) {
#define __case(__Kind)                                                    \
    case OrgSemKind::__Kind: {                                            \
        In<sem::__Kind> tmp = arg.as<sem::__Kind>();                      \
        _this()->pushVisit(res, tmp);                                     \
        _this()->visitDispatchHook(res, tmp);                             \
        _this()->visitOrgNodeIn(res, tmp);                                \
        _this()->popVisit(res, tmp);                                      \
        break;                                                            \
    }


        EACH_SEM_ORG_KIND(__case)

#undef __case
    }
}

void ExporterPython::traceVisit(const VisitEvent& ev) {
    using K = typename VisitEvent::Kind;
    if (((ev.kind == K::PushVisit || ev.kind == K::VisitStart)
         && !ev.isStart)
        || ((ev.kind == K::PopVisit || ev.kind == K::VisitEnd)
            && ev.isStart)) {
        return;
    }

    auto os = exportTracer->getStream();


    os << os.indent(ev.level * 2) << (ev.isStart ? ">" : "<") << " "
       << to_string(ev.kind);

    if (ev.visitedNode) {
        os << " node:" << to_string(ev.visitedNode->getKind());
    }

    if (0 < ev.field.length()) {
        os << " field:" << ev.field;
    }

    if (!ev.msg.isEmpty()) {
        os << " msg:" << ev.msg;
    }

    os << " on " << QFileInfo(ev.file).fileName() << ":" << ev.line << " "
       << ev.function << " " << os.end();

    if (0 < ev.type.length()) {
        os << " type:" << demangle(ev.type.toLatin1());
    }

    exportTracer->endStream(os);
}

void ExporterPython::visitField(
    Res&        res,
    const char* name,
    sem::SemId  value) {
    switch (value->getKind()) {
#define __case(__Kind)                                                    \
    case OrgSemKind::__Kind: {                                            \
        In<sem::__Kind> tmp = value.as<sem::__Kind>();                    \
        visitOrgField(res, name, tmp);                                    \
        break;                                                            \
    }

        EACH_SEM_ORG_KIND(__case)

#undef __case
    }
}

ExporterPython::Res ExporterPython::evalTop(sem::SemId org) {
    __visit_scope(VisitEvent::Kind::VisitTop, .visitedNode = org);
    if (evalTopCb) {
        return evalTopCb->operator()(_self, org);
    } else {
        _this()->visitStart(org);
        Res tmp = _this()->newRes(org);
        _this()->visit(tmp, org);
        _this()->visitEnd(org);
        return tmp;
    }
}
