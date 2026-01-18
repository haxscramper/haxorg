#pragma once

#include <hstd/stdlib/TraceBase.hpp>
#include <hstd/stdlib/Func.hpp>
#include <hstd/stdlib/Vec.hpp>
#include <haxorg/sem/SemOrg.hpp>
#include <haxorg/api/ParseContext.hpp>


namespace org {
struct OrgCodeEvalParameters {
    hstd::Func<hstd::Vec<sem::OrgCodeEvalOutput>(
        sem::OrgCodeEvalInput const&)>
                                              evalBlock;
    hstd::SPtr<hstd::OperationsTracer>        debug;
    std::string                               currentFile;
    std::shared_ptr<org::parse::ParseContext> parseContext;

    bool isTraceEnabled() const { return debug && debug->TraceState; }

    OrgCodeEvalParameters(
        std::shared_ptr<org::parse::ParseContext> parseContext)
        : parseContext{parseContext}
        , debug{std::make_shared<hstd::OperationsTracer>()} {}
    OrgCodeEvalParameters(
        std::shared_ptr<org::parse::ParseContext> parseContext,
        hstd::SPtr<hstd::OperationsTracer>        debug)
        : parseContext{parseContext}, debug{debug} {}
};

sem::SemId<sem::Org> evaluateCodeBlocks(
    sem::SemId<sem::Org>         document,
    OrgCodeEvalParameters const& conf);

} // namespace org
