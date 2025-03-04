#include "pyhaxorg_manual_impl.hpp"
#include <haxorg/sem/SemOrgSerde.hpp>

#include <haxorg/sem/SemOrgFormat.hpp>
#include <haxorg/exporters/ExporterJson.hpp>
#include <hstd/stdlib/Filesystem.hpp>
#include <haxorg/exporters/exporteryaml.hpp>
#include <haxorg/exporters/exportertree.hpp>
#include <datetime.h>

#include <haxorg/exporters/Exporter.cpp>
#include <haxorg/sem/perfetto_org.hpp>
#include <hstd/ext/perfetto_aux_impl_template.hpp>

using namespace org;
using namespace hstd;
using namespace org::bind::python;

template class org::algo::Exporter<ExporterPython, py::object>;


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

std::string format_function_definition(const pybind11::function& func) {
    auto obj  = func.attr("__code__");
    auto name = std::string{pybind11::str(func.attr("__name__"))};
    auto file = std::string{pybind11::str(obj.attr("co_filename"))};
    auto line = obj.attr("co_firstlineno").cast<int>();

    return std::format(
        "{}:{}@{}",
        name,
        line,
        std::filesystem::path(file).stem().string());
}

std::string ExporterPython::describe(const PyFunc& func) const {
    return format_function_definition(func);
}

std::string ExporterPython::describe_use(
    const std::string& msg,
    const PyFunc&      usage) const {
    return std::format("{} {}", msg, describe(usage));
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

void ExporterPython::print_trace(
    const std::string& trace,
    const std::string& file,
    const std::string& function,
    int                line) {
    auto rep     = this->trace(VisitReport::Kind::Print);
    rep.line     = line;
    rep.function = function.c_str();
    rep.file     = file.c_str();
    rep.msg      = trace;
    trace_instant(rep);
}

ExporterPython::Res ExporterPython::newResImpl(sem::OrgArg node) {
    if (newAnyOrgResCb) {
        trace_leaf(VK::NewRes, node, "universal CB", *newAnyOrgResCb);
        return newAnyOrgResCb->operator()(_self, node);
    } else if (auto cb = newOrgResCb.get(node->getKind())) {
        trace_leaf(VK::NewRes, node, "callback for kind", *cb);
        return cb.value()(_self, node);
    } else {
        // trace_instant(
        //     trace(VK::NewRes)
        //         .with_node(node)
        //         .with_msg(fmt("no callback for {}", node->getKind())));
        return py::none();
    }
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

void ExporterPython::pushVisitImpl(Res& res, sem::OrgArg id) {
    if (pushVisitAnyIdCb) {
        trace_leaf(VK::PushVisit, id, "universal", *pushVisitAnyIdCb);
        pushVisitAnyIdCb->operator()(_self, res, id);
    } else if (auto cb = pushVisitIdCb.get(id->getKind())) {
        trace_leaf(VK::PushVisit, id, "kind", *cb);
        cb.value()(_self, res, id);
    } else {
        // trace_no_cb(VK::PushVisit, id);
    }
}

void ExporterPython::popVisitImpl(Res& res, sem::OrgArg id) {
    if (popVisitAnyIdCb) {
        trace_leaf(VK::PopVisit, id, "universal", *popVisitAnyIdCb);
        popVisitAnyIdCb->operator()(_self, res, id);
    } else if (auto cb = popVisitIdCb.get(id->getKind())) {
        trace_leaf(VK::PopVisit, id, "kind", *cb);
        cb.value()(_self, res, id);
    } else {
        // trace_no_cb(VK::PopVisit, id);
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


void org::bind::python::eachSubnodeRec(
    sem::SemId<sem::Org> node,
    py::function         callback) {
    org::eachSubnodeRec(
        node, [&](sem::SemId<sem::Org> arg) { callback(arg); });
}

void org::bind::python::eachSubnodeRecSimplePath(
    sem::SemId<sem::Org> node,
    py::function         callback) {
    org::eachSubnodeRecSimplePath(
        node, [&](sem::OrgArg arg, sem::OrgVecArg path) {
            callback(arg, path);
        });
}

org::sem::SemId<sem::Org> org::bind::python::evaluateCodeBlocks(
    org::sem::SemId<sem::Org>   node,
    const PyCodeEvalParameters& conf) {
    OrgCodeEvalParameters eval_conf{conf.debug};

    eval_conf.evalBlock = [&](org::sem::OrgCodeEvalInput const& input)
        -> Vec<org::sem::OrgCodeEvalOutput> {
        return conf.evalBlock(input)
            .cast<Vec<org::sem::OrgCodeEvalOutput>>();
    };

    return org::evaluateCodeBlocks(node, eval_conf);
}
