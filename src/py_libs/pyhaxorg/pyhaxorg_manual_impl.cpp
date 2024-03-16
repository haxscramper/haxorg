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

std::string exportToJsonString(sem::SemId<sem::Org> const& node) {
    return to_string(ExporterJson{}.evalTop(node));
}

void exportToJsonFile(sem::SemId<sem::Org> const& node, std::string path) {
    writeFile(fs::path{path}, exportToJsonString(node));
}

std::string exportToYamlString(sem::SemId<sem::Org> const& node) {
    std::stringstream os;
    os << ExporterYaml{}.evalTop(node);
    return os.str();
}

void exportToYamlFile(sem::SemId<sem::Org> const& node, std::string path) {
    writeFile(fs::path{path}, exportToYamlString(node));
}


std::string exportToTreeString(
    sem::SemId<sem::Org> const& node,
    OrgTreeExportOpts const&    opts) {
    ColStream    os{};
    ExporterTree tree{os};

    tree.conf.withLineCol     = opts.withLineCol;
    tree.conf.withOriginalId  = opts.withOriginalId;
    tree.conf.skipEmptyFields = opts.skipEmptyFields;
    tree.conf.startLevel      = opts.startLevel;
    tree.evalTop(node);

    std::string result = os.toString(opts.withColor);
    return result;
}

void exportToTreeFile(
    sem::SemId<sem::Org> const& node,
    std::string                 path,
    OrgTreeExportOpts const&    opts) {

    ColStream    os{};
    ExporterTree tree{os};

    tree.conf.withLineCol     = opts.withLineCol;
    tree.conf.withOriginalId  = opts.withOriginalId;
    tree.conf.skipEmptyFields = opts.skipEmptyFields;
    tree.conf.startLevel      = opts.startLevel;
    tree.evalTop(node);

    std::ofstream file{path};
    file << os.toString(opts.withColor);
}

sem::SemId<sem::Document> parseFile(
    std::string               file,
    const OrgParseParameters& opts) {
    return parseStringOpts(readFile(fs::path{file}), opts);
}

sem::SemId<sem::Document> parseString(std::string file) {
    return parseStringOpts(readFile(fs::path{file}), OrgParseParameters{});
}

sem::SemId<sem::Document> parseStringOpts(
    const std::string         text,
    OrgParseParameters const& opts) {
    LexerParams         p;
    SPtr<std::ofstream> fileTrace;
    if (opts.baseTokenTracePath) {
        fileTrace = std::make_shared<std::ofstream>(
            *opts.baseTokenTracePath);
    }
    p.traceStream            = fileTrace.get();
    OrgTokenGroup baseTokens = ::tokenize(text.data(), text.size(), p);
    OrgTokenGroup tokens;
    OrgTokenizer  tokenizer{&tokens};

    if (opts.tokenTracePath) {
        tokenizer.setTraceFile(*opts.tokenTracePath);
    }

    tokenizer.convert(baseTokens);
    Lexer<OrgTokenKind, OrgFill> lex{&tokens};

    OrgNodeGroup nodes{&tokens};
    OrgParser    parser{&nodes};
    if (opts.parseTracePath) { parser.setTraceFile(*opts.parseTracePath); }

    (void)parser.parseFull(lex);

    sem::OrgConverter converter{};
    if (opts.semTracePath) { converter.setTraceFile(*opts.semTracePath); }

    return converter.toDocument(OrgAdapter(&nodes, OrgId(0)));
}

sem::SemId<sem::Document> readProtobufFile(const std::string& file) {
    sem::SemId        read_node = sem::SemId<sem::Org>::Nil();
    std::ifstream     stream{file};
    orgproto::AnyNode result;
    result.ParseFromIstream(&stream);
    proto_serde<orgproto::AnyNode, sem::SemId<sem::Org>>::read(
        result,
        proto_write_accessor<sem::SemId<sem::Org>>::for_ref(read_node));
    return read_node.as<sem::Document>();
}

void exportToProtobufFile(
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

void init_py_manual_api(pybind11::module& m) {
    PyDateTime_IMPORT;
    assert(PyDateTimeAPI);
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
std::string formatToString(sem::SemId<sem::Org> arg) {
    return sem::Formatter::format(arg);
}

void eachSubnodeRec(sem::SemId<sem::Org> node, py::function callback) {
    sem::eachSubnodeRec(
        node, [&](sem::SemId<sem::Org> arg) { callback(arg); });
}
