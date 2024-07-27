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

void ExporterPython::enableBufferTrace() {
    TraceState    = true;
    traceToBuffer = true;
}

std::string ExporterPython::getTraceBuffer() const {
    return this->traceBuffer;
}

void ExporterPython::enableFileTrace(
    const std::string& path,
    bool               colored) {
    this->setTraceFile(path);
    this->traceColored = colored;
}

void ExporterPython::visitDispatch(Res& res, sem::SemId<sem::Org> arg) {
    auto __scope = trace_scope(
        trace(VisitReport::Kind::VisitDispatch).with_node(arg));

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
    auto __scope = trace_scope(
        trace(VisitReport::Kind::VisitTop).with_node(org));

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
