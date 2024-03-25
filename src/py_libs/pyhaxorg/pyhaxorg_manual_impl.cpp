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


void eachSubnodeRec(sem::SemId<sem::Org> node, py::function callback) {
    sem::eachSubnodeRec(
        node, [&](sem::SemId<sem::Org> arg) { callback(arg); });
}
