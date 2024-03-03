#include "pyhaxorg_manual_impl.hpp"
#include "sem/SemOrgSerde.hpp"

#include <sem/SemOrgFormat.hpp>
#include <exporters/ExporterJson.hpp>
#include <hstd/stdlib/Filesystem.hpp>
#include <exporters/exporteryaml.hpp>
#include <exporters/exportertree.hpp>
#include <datetime.h>
#include <fstream>

#include <memory>

#include <exporters/Exporter.cpp>
#include <sem/perfetto_org.hpp>
#include <hstd/wrappers/perfetto_aux_impl_template.hpp>


template class Exporter<ExporterPython, py::object>;

OrgExporterJson::OrgExporterJson() {
    impl = std::make_shared<ExporterJson>();
}

std::string OrgExporterJson::exportToString() { return to_string(result); }

void OrgExporterJson::exportToFile(std::string path) {
    writeFile(fs::path{path}, exportToString());
}

void OrgExporterJson::visitNode(sem::SemId<sem::Org> node) {
    result = impl->evalTop(node);
}

OrgExporterYaml::OrgExporterYaml() {
    impl = std::make_shared<ExporterYaml>();
}

std::string OrgExporterYaml::exportToString() {
    std::stringstream os;
    os << result;
    return os.str();
}

void OrgExporterYaml::exportToFile(std::string path) {
    writeFile(fs::path{path}, exportToString());
}

void OrgExporterYaml::visitNode(sem::SemId<sem::Org> node) {
    result = impl->evalTop(node);
}

std::string OrgExporterTree::toString(
    sem::SemId<sem::Org> node,
    ExporterTreeOpts     opts) {
    std::string       buf;
    std::stringstream os{buf};
    stream(os, node, opts);
    return buf;
}

void OrgExporterTree::toFile(
    sem::SemId<sem::Org> node,
    std::string          path,
    ExporterTreeOpts     opts) {
    std::ofstream file{path};
    stream(file, node, opts);
}

void OrgExporterTree::stream(
    std::ostream&        stream,
    sem::SemId<sem::Org> node,
    ExporterTreeOpts     opts) {
    ColStream os{stream};
    os.colored = opts.withColor;
    os.ostream = &stream;

    ExporterTree tree{os};

    tree.conf.withLineCol     = opts.withLineCol;
    tree.conf.withOriginalId  = opts.withOriginalId;
    tree.conf.skipEmptyFields = opts.skipEmptyFields;
    tree.conf.startLevel      = opts.startLevel;
    tree.evalTop(node);
}

sem::SemId<sem::Document> OrgContext::parseFile(std::string file) {
    return parseString(readFile(fs::path{file}));
}

sem::SemId<sem::Document> OrgContext::parseString(const std::string text) {
    LexerParams   p;
    OrgTokenGroup baseTokens = ::tokenize(text.data(), text.size(), p);
    OrgTokenGroup tokens;
    OrgTokenizer  tokenizer{&tokens};

    tokenizer.convert(baseTokens);
    Lexer<OrgTokenKind, OrgFill> lex{&tokens};

    OrgNodeGroup nodes{&tokens};
    OrgParser    parser{&nodes};
    (void)parser.parseFull(lex);

    sem::OrgConverter converter{};

    return converter.toDocument(OrgAdapter(&nodes, OrgId(0)));
}

sem::SemId<sem::Document> OrgContext::parseProtobuf(
    const std::string& file) {
    sem::SemId        read_node = sem::SemId<sem::Org>::Nil();
    std::ifstream     stream{file};
    orgproto::AnyNode result;
    result.ParseFromIstream(&stream);
    proto_serde<orgproto::AnyNode, sem::SemId<sem::Org>>::read(
        result,
        proto_write_accessor<sem::SemId<sem::Org>>::for_ref(read_node));
    return read_node.as<sem::Document>();
}

void OrgContext::saveProtobuf(
    sem::SemId<sem::Document> doc,
    const std::string&        file) {
    std::ofstream     stream{file};
    orgproto::AnyNode result;
    proto_serde<orgproto::AnyNode, sem::SemId<sem::Org>>::write(
        &result, doc.asOrg());
    result.SerializeToOstream(&stream);
}


std::vector<sem::SemId<sem::Org>> getSubnodeRange(
    sem::SemId<sem::Org> id,
    pybind11::slice      slice) {

    size_t start;
    size_t stop;
    size_t step;
    size_t slicelength;

    Vec<sem::SemId<sem::Org>> const& data = id->subnodes;
    if (!slice.compute(data.size(), &start, &stop, &step, &slicelength)) {
        throw py::error_already_set();
    }

    std::vector<sem::SemId<sem::Org>> result{
        slicelength, sem::SemId<sem::Org>::Nil()};
    for (size_t i = 0; i < slicelength; ++i) {
        result[i] = data[start];
        start += step;
    }
    return result;
}

sem::SemId<sem::Org> getSingleSubnode(sem::SemId<sem::Org> id, int index) {
    return id->at(index);
}

sem::OrgVariant castAs(sem::SemId<sem::Org> id) {
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
    PyDateTime_IMPORT;
    assert(PyDateTimeAPI);
    bind_int_set<sem::Subtree::Period::Kind>(m, "SubtreePeriodKind");
}

void ExporterPython::enablePyStreamTrace(pybind11::object stream) {
    pyStreamDevice     = std::make_shared<PythonStreamDevice>(stream);
    writeStreamContext = std::make_shared<IoContext>();
    // TODO fixme the constructor
    // writeStreamContext->stream      = std::make_shared<std::ostream>();
    this->exportTracer              = OperationsTracer{};
    this->exportTracer->stream      = writeStreamContext->stream;
    this->exportTracer->traceToFile = true;
    assert(false);
    // writeStreamContext->stream->setDevice(&(*pyStreamDevice));
    this->visitEventCb = [this](ExporterPython::VisitEvent const& ev) {
        this->traceVisit(ev);
    };
}

void ExporterPython::enableBufferTrace() {
    writeStreamContext = std::make_shared<IoContext>();
    // TODO fixme create tracer
    // writeStreamContext->stream      = std::make_shared<std::ostream>();
    this->exportTracer->stream      = writeStreamContext->stream;
    this->exportTracer->traceToFile = true;
    assert(false);
    // writeStreamContext->stream->setString(&traceBuffer);
    this->visitEventCb = [this](ExporterPython::VisitEvent const& ev) {
        this->traceVisit(ev);
    };
}

std::string ExporterPython::getTraceBuffer() const { return traceBuffer; }

void ExporterPython::enableFileTrace(
    const std::string& path,
    bool               colored) {
    writeStreamContext         = std::make_shared<IoContext>();
    writeStreamContext->stream = std::make_shared<std::ofstream>(path);
    traceStream.ostream        = writeStreamContext->stream.get();
    traceStream.colored        = colored;
    this->exportTracer         = OperationsTracer{};
    this->exportTracer->stream = writeStreamContext->stream;
    this->exportTracer->traceToFile = true;
    this->visitEventCb = [this](ExporterPython::VisitEvent const& ev) {
        this->traceVisit(ev);
    };
}

void ExporterPython::visitDispatch(Res& res, sem::SemId<sem::Org> arg) {
    __visit_scope(
        VisitEvent::Kind::VisitDispatch,
        .visitedValue = &res,
        .visitedNode  = arg);

    if (arg.isNil()) { return; }

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
       << fmt1(ev.kind);

    if (ev.visitedNode) {
        os << " node:" << fmt1((*ev.visitedNode)->getKind());
    }

    if (0 < ev.field.length()) { os << " field:" << ev.field; }

    if (!ev.msg.empty()) {
        os << " msg:" << os.yellow() << ev.msg << os.end();
    }

    os << " on " << fs::path(ev.file).stem() << ":" << fmt1(ev.line) << " "
       << " " << os.end();

    exportTracer->endStream(os);
}

void ExporterPython::visitField(
    Res&                 res,
    const char*          name,
    sem::SemId<sem::Org> value) {
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

ExporterPython::Res ExporterPython::evalTop(sem::SemId<sem::Org> org) {
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
std::string OrgContext::formatToString(sem::SemId<sem::Org> arg) {
    return sem::Formatter::format(arg);
}
