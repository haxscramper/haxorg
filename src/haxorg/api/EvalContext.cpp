#include "EvalContext.hpp"
#include <haxorg/imm/ImmOrg.hpp>
#include <hstd/stdlib/Map.hpp>
#include <hstd/stdlib/JsonUse.hpp>
#include <hstd/stdlib/JsonSerde.hpp>
#include <haxorg/api/SemBaseApi.hpp>
#include <hstd/stdlib/OptSerde.hpp>
#include <hstd/stdlib/OptFormatter.hpp>
#include <hstd/stdlib/VecFormatter.hpp>
#include <hstd/stdlib/VariantFormatter.hpp>
#include <haxorg/exporters/ExporterJson.hpp>
#include <deque>

using namespace org;
using namespace hstd;
namespace {

json sliceJson(
    const json&                                    input,
    const Vec<org::sem::AttrValue::DimensionSpan>& spans) {
    if (!input.is_array()) {
        throw std::invalid_argument("Input JSON must be an array");
    }

    if (spans.empty()) { return input; }

    std::vector<size_t> dimensions;
    auto                current = &input;
    while (current->is_array() && !current->empty()) {
        dimensions.push_back(current->size());
        current = &(*current)[0];
    }

    if (spans.size() > dimensions.size()) {
        throw std::invalid_argument(
            "More spans provided than dimensions in input");
    }

    std::vector<std::vector<int>> indices(spans.size());
    for (size_t i = 0; i < spans.size(); ++i) {
        const auto& span     = spans[i];
        int         dim_size = static_cast<int>(dimensions[i]);

        int first = span.first;
        if (first < 0) { first = dim_size + first; }
        if (first < 0 || first >= dim_size) {
            throw std::out_of_range("Span first index out of bounds");
        }

        int last = span.last.has_value() ? span.last.value() : first;
        if (last < 0) { last = dim_size + last; }
        if (last < 0 || last >= dim_size || last < first) {
            throw std::out_of_range("Span last index out of bounds");
        }

        for (int idx = first; idx <= last; ++idx) {
            indices[i].push_back(idx);
        }
    }

    std::function<json(const json&, size_t, const std::vector<int>&)>
        sliceRecursive;
    sliceRecursive = [&](const json&             arr,
                         size_t                  dim,
                         const std::vector<int>& path) -> json {
        if (dim == indices.size()) {
            const json* value = &arr;
            for (int idx : path) { value = &(*value)[idx]; }
            return *value;
        }

        json result = json::array();
        for (int idx : indices[dim]) {
            std::vector<int> newPath = path;
            newPath.push_back(idx);

            if (dim == indices.size() - 1) {
                result.push_back(sliceRecursive(arr, dim + 1, newPath));
            } else {
                json subArray = sliceRecursive(arr, dim + 1, newPath);
                result.push_back(subArray);
            }
        }
        return result;
    };

    return sliceRecursive(input, 0, {});
}

} // namespace


struct EvalContext {
    OrgCodeEvalParameters const& conf;
    imm::ImmAstVersion           version;
    Vec<imm::ImmAstVersion>      history;
    UnorderedMap<Str, json>      namedResults;
    UnorderedMap<Str, Str>       evalResults;
    /// \brief Original name that is currently being evaluated.
    hstd::Str currentFile;
    /// \brief Count number of evaluations in the context in order to
    /// assign unique names to the source file names for evaluation result
    /// parsing.
    int evalCounter = 0;

    imm::ImmAstContext::Ptr getContext() const { return version.context; }
    hstd::SPtr<imm::ImmAstTrackingMap> getTrack() const {
        return getContext()->currentTrack;
    }

    bool isTraceEnabled() const {
        return conf.debug && conf.debug->TraceState;
    }


#define EVAL_TRACE(msg)                                                   \
    if (isTraceEnabled()) { conf.debug->message(msg); }


#define EVAL_SCOPE()                                                      \
    auto CONCAT(__scope, __COUNTER__) = isTraceEnabled()                  \
                                          ? conf.debug->scopeLevel()      \
                                          : finally_std::nop();

    Opt<json> getTargetValue(imm::ImmId const& target_id, bool asFlatText)
        const {
        auto target = getContext()->adaptUnrooted(target_id);
        EVAL_TRACE(fmt("Target node is {}", target));
        EVAL_SCOPE();
        Opt<json> result;

        target.visitNodeValue(
            overloaded{
                [&](imm::ImmStmtList const& list) {
                    json out = json::array();
                    for (auto const& it : list) {
                        auto nested = getTargetValue(it, asFlatText);
                        if (nested) { out.push_back(nested.value()); }
                    }

                    if (out.size() == 0) {
                        result = std::nullopt;
                    } else if (out.size() == 1) {
                        result = out.at(0);
                    } else {
                        result = out;
                    }
                },
                [&](imm::ImmTable const& t) {
                    json out_table = json::array();
                    for (auto const& row : t.rows) {
                        json out_row = json::array();
                        EVAL_TRACE(fmt("Row {}", row));
                        EVAL_SCOPE();
                        for (auto const& cell : getContext()
                                                    ->adaptUnrooted(row)
                                                    .as<imm::ImmRow>()
                                                    ->cells) {
                            EVAL_TRACE(fmt("Cell {}", cell));
                            if (asFlatText) {
                                out_row.push_back(getCleanText(
                                    getContext()->adaptUnrooted(cell)));
                            } else {
                                auto cell_sem = org::imm::sem_from_immer(
                                    cell, *getContext());
                                auto json_res = algo::ExporterJson::toJson(
                                    cell_sem);
                                out_row.push_back(json_res);
                            }
                        }
                        out_table.push_back(out_row);
                    }
                    result = out_table;
                },
                [&](imm::ImmBlockCode const& code) {
                    if (code.result.empty()) {
                        EVAL_TRACE(
                            "Target code block was not evaluated, no "
                            "result "
                            "field");
                    } else {
                        auto value = getContext()
                                         ->adaptUnrooted(
                                             code.result.back())
                                         .as<imm::
                                                 ImmBlockCodeEvalResult>();
                        EVAL_TRACE(fmt(
                            "Target code block evaluated to {}", value));
                        // EVAL_TRACE()
                        result = getTargetValue(value->node, asFlatText);
                    }
                },
                [&](auto const&) {},
            });

        return result;
    }

    Opt<json> getAttrValue(sem::AttrValue const& attr) const {
        EVAL_TRACE(fmt("Resolving attribute value to state {}", attr));
        EVAL_SCOPE();
        Str  name = attr.getString();
        auto node = getTrack()->names.get(name);
        if (!node) {
            EVAL_TRACE("No named nodes with the value");
            return std::nullopt;
        }
        auto paths = getContext()->getPathsFor(node.value());
        LOGIC_ASSERTION_CHECK_FMT(
            !paths.empty(), "Logic block {} has no paths", node.value());
        Opt<json> result = getTargetValue(paths.front().id, true);


        if (result) { result = sliceJson(result.value(), attr.span); }

        return result;
    }


    struct CallParams {
        imm::ImmAdapterT<imm::ImmBlockCode> block;
        Opt<org::sem::AttrGroup>            callsiteVars;
        Opt<org::sem::AttrGroup>            callsiteHeaderArgs;
    };

    CallParams getTargetBlock(imm::ImmAdapter const& adapter) {
        EVAL_SCOPE();
        CallParams res;
        if (adapter.is(OrgSemKind::BlockCode)) {
            res.block = adapter.as<imm::ImmBlockCode>();
        } else {
            auto command = adapter.as<imm::ImmCmdCall>();
            EVAL_TRACE(fmt(
                "Getting target code block for name '{}'", command->name));
            res.callsiteVars       = command->callAttrs;
            res.callsiteHeaderArgs = command->insideHeaderAttrs;
            if (auto opt_block = getTrack()->names.get(command->name)) {
                if (!opt_block->is(OrgSemKind::BlockCode)) {
                    EVAL_TRACE(
                        fmt("Name '{}' does not refer to a code block",
                            command->name));
                }

                auto paths = getContext()->getPathsFor(opt_block.value());
                LOGIC_ASSERTION_CHECK_FMT(
                    !paths.empty(),
                    "Logic block {} has no paths",
                    opt_block.value());
                res.block = getContext()
                                ->adapt(paths.front())
                                .as<imm::ImmBlockCode>();
            } else {
                EVAL_TRACE(
                    fmt("Name '{}' does not refer to a known document "
                        "entry",
                        command->name));
            }
        }


        return res;
    }

    sem::SemId<sem::Org> convertOutput(
        sem::OrgCodeEvalOutput const& out,
        sem::OrgCodeEvalInput const&  in,
        const OrgCodeEvalParameters&  conf) {
        EVAL_SCOPE();
        EVAL_TRACE(fmt("Parsing stdout"));
        std::string activeName = hstd::fmt(
            "{}-output-{}", currentFile, evalCounter);
        auto doc = conf.parseContext->parseString(
            activeName, out.stdoutText);
        auto stmt = sem::SemId<sem::StmtList>::New();
        for (auto const& node : doc) {
            EVAL_TRACE(fmt("Result node {}", node->getKind()));
            stmt->subnodes.push_back(node);
        }
        ++evalCounter;
        return stmt;
    }

    sem::OrgCodeEvalInput convertInput(CallParams const& res) {
        EVAL_SCOPE();
        sem::OrgCodeEvalInput input;
        if (res.block->lang->has_value()) {
            input.language = res.block->lang.get().value();
        }

        using I = sem::OrgCodeEvalInput;

        input.resultHandling = I::ResultHandling::Replace;
        input.resultType     = I::ResultType::Scalar;


        Vec<Str> buf;
        for (auto const& line : res.block->lines) {
            buf.push_back("");
            for (auto const& part : line.parts) {
                using K = sem::BlockCodeLine::Part::Kind;
                switch (part.getKind()) {
                    case K::Raw: {
                        buf.back().append(part.getRaw().code);
                        break;
                    }
                    case K::Callout: {
                        // callouts are explicitly skipped
                        break;
                    }
                    case K::Tangle: {
                        logic_todo_impl();
                        break;
                    }
                }
            }
        }

        input.tangledCode = join("\n", buf);

        for (auto const& res : res.block.getAttrs("results")) {
            auto norm = normalize(res.getString());
            if (norm == "table" || norm == "vector") {
                input.resultType = I::ResultType::Table;
            } else if (norm == "list") {
                input.resultType = I::ResultType::List;
            } else if (norm == "scalar" || norm == "verbatim") {
                input.resultType = I::ResultType::Scalar;
            } else if (norm == "file") {
                input.resultType = I ::ResultType::SaveFile;
            } else if (norm == "raw") {
                input.resultFormat = I::ResultFormat::Raw;
            } else if (norm == "code") {
                input.resultFormat = I::ResultFormat::Code;
            } else if (norm == "drawer") {
                input.resultFormat = I::ResultFormat::Drawer;
            } else if (norm == "html") {
                input.resultFormat = I::ResultFormat::ExportType;
                input.exportType   = "html";
            } else if (norm == "latex") {
                input.resultFormat = I::ResultFormat::ExportType;
                input.exportType   = "latex";
            } else if (norm == "link" || norm == "graphics") {
                input.resultFormat = I::ResultFormat::Link;
            } else if (norm == "org") {
                input.resultFormat = I::ResultFormat::Code;
                input.exportType   = "org";
            } else if (norm == "pp") {
                input.resultFormat = I::ResultFormat::Code;
            } else if (norm == "replace") {
                input.resultHandling = I::ResultHandling::Replace;
            } else if (norm == "silent") {
                input.resultHandling = I::ResultHandling::Silent;
            } else if (norm == "none") {
                input.resultHandling = I::ResultHandling::None;
            } else if (norm == "discard") {
                input.resultHandling = I::ResultHandling::Discard;
            } else if (norm == "append") {
                input.resultHandling = I::ResultHandling::Append;
            } else if (norm == "prepend") {
                input.resultHandling = I::ResultHandling::Prepend;
            }
        }

        if (auto attr = res.block.getFirstAttr("result-export-language")) {
            input.exportType = attr->getString();
        }

        if (auto attr = res.block.getFirstAttr("result-code-language")) {
            input.exportType = attr->getString();
        }

        UnorderedMap<Str, sem::AttrValue> byVarname;
        if (auto default_vars = res.block->attrs.getNamed("var")) {
            for (auto const& var : default_vars->items) {
                EVAL_TRACE(fmt("Default variable {}", var));
                byVarname.insert_or_assign(var.varname.value(), var);
            }
        }

        if (res.callsiteVars) {
            for (auto const& var : res.callsiteVars->positional.items) {
                EVAL_TRACE(fmt("Callsite variable {}", var));
                if (var.varname) {
                    byVarname.insert_or_assign(var.varname.value(), var);
                }
            }
        }

        for (auto const& key : sorted(byVarname.keys())) {
            sem::OrgCodeEvalInput::Var var;
            auto const&                attr = byVarname.at(key);

            var.name = attr.varname.value();
            json value;
            if (auto named_value = getAttrValue(attr)) {
                value = named_value.value();
            } else {
                value = attr.getString();
            }
            EVAL_TRACE(
                fmt("Var '{}' value is '{}'", var.name, value.dump()));
            var.value = value;
            input.argList.push_back(var);
        }


        return input;
    }


    void setOutput(
        Vec<sem::OrgCodeEvalOutput> const& out,
        sem::OrgCodeEvalInput const&       input,
        imm::ImmUniqId const&              block,
        sem::SemId<sem::Org>               node) {
        EVAL_SCOPE();
        auto target_id = block.update(version.context->at(block.path));
        auto target    = version.context->adapt(target_id);
        auto result    = sem::SemId<sem::BlockCodeEvalResult>::New();

        result->raw  = out;
        result->node = node;

        version = version.getEditVersion(
            [&](imm::ImmAstContext::Ptr ast,
                imm::ImmAstEditContext& ctx) -> imm::ImmAstReplaceGroup {
                auto id = ast->add(result, ctx)
                              .as<imm::ImmBlockCodeEvalResult>();

                if (id == target_id.id) {
                    EVAL_TRACE("No changes in the code eval");
                    return imm::ImmAstReplaceGroup{};
                } else {
                    EVAL_TRACE(
                        fmt("Updating AST with new eval result, target "
                            "{}, result handling {} result format {} new "
                            "node {}",
                            target.uniq(),
                            input.resultHandling,
                            input.resultFormat,
                            id));

                    auto assign_result = [&]<typename T>(T code) -> T {
                        using RH = sem::OrgCodeEvalInput::ResultHandling;
                        switch (input.resultHandling) {
                            case RH::Append:
                                code.result = code.result.push_back(id);
                                break;
                            case RH::Prepend:
                                code.result = code.result.insert(0, id);
                                break;
                            case RH::Replace: code.result = {id}; break;
                            case RH::Discard: break;
                            case RH::Silent:
                            case RH::None:
                                // TODO
                                break;
                        }

                        return code;
                    };

                    if (target.is(OrgSemKind::BlockCode)) {
                        return ctx.store().updateNode<imm::ImmBlockCode>(
                            target, ctx, [&](imm::ImmBlockCode code) {
                                return assign_result(code);
                            });
                    } else {
                        return ctx.store().updateNode<imm::ImmCmdCall>(
                            target, ctx, [&](imm::ImmCmdCall code) {
                                return assign_result(code);
                            });
                    }
                }
            });

        if (conf.isTraceEnabled()) { history.push_back(version); }
    };

    sem::SemId<sem::Org> evalAll(sem::SemId<sem::Org> document) {
        auto imm_context = imm::ImmAstContext::init_start_context();
        // imm_context->debug->setTraceFile("/tmp/evaluateCodeBlocks.log");
        version = imm_context->init(document);

        auto collect_code_blocks =
            [](imm::ImmAdapter const& ad) -> Vec<imm::ImmUniqId> {
            Vec<imm::ImmUniqId> res;
            org::eachSubnodeRec(
                ad, true, [&](imm::ImmAdapter const& adapter) {
                    if (adapter.is(OrgSemKind::BlockCode)
                        || adapter.is(OrgSemKind::CmdCall)) {
                        res.push_back(adapter.uniq());
                    }
                });

            return res;
        };


        if (isTraceEnabled()) { history.push_back(version); }


        auto init_buffer = collect_code_blocks(version.getRootAdapter());
        std::deque<imm::ImmUniqId> codeBlockPaths{
            init_buffer.begin(), init_buffer.end()};

        while (!codeBlockPaths.empty()) {
            auto block = codeBlockPaths.front();
            codeBlockPaths.pop_front();
            imm::ImmAdapter adapter = version.context->adapt(block);

            CallParams call = getTargetBlock(adapter);

            if (!call.block.isNil()) {
                EVAL_TRACE(
                    fmt("Evaluating language '{}' at {}",
                        call.block->lang,
                        call.block->loc));
                EVAL_SCOPE();

                auto input  = convertInput(call);
                auto output = conf.evalBlock(input);

                for (auto const& it : output) {
                    if (!it.cmd) { EVAL_TRACE(fmt("cmd: {}", it.cmd)); }
                    if (!it.args.empty()) {
                        EVAL_TRACE(fmt("args: {}", it.args));
                    }
                    EVAL_TRACE(fmt("code: {}", it.code));
                    if (!it.cwd.empty()) {
                        EVAL_TRACE(fmt("cwd: {}", it.cwd));
                    }

                    if (!it.stderrText.empty()) {
                        EVAL_TRACE(fmt("stderr:\n{}", it.stderrText));
                    }

                    if (!it.stdoutText.empty()) {
                        EVAL_TRACE(fmt("stdout:\n{}", it.stdoutText));
                    }
                }

                if (!output.empty()) {
                    setOutput(
                        output,
                        input,
                        block,
                        convertOutput(output.back(), input, conf));
                }
            }
        }

        if (isTraceEnabled()) {
#if !ORG_EMCC_BUILD
            auto graph = org::imm::toGraphviz(history);
            graph.render("/tmp/CodeBlockEvalGraph.png");
#endif
        }

        imm::ImmAdapter::TreeReprConf repr_conf;
        repr_conf.withAuxFields  = true;
        repr_conf.withReflFields = true;
        writeFile(
            "/tmp/codeblock_eval_final.txt",
            version.getRootAdapter().treeRepr(repr_conf).toString(false));

        EVAL_TRACE(
            fmt("Converting final root result {} back to sem",
                version.getRoot()));
        return org::imm::sem_from_immer(
            version.getRoot(), *version.context);
    }
};


sem::SemId<sem::Org> org::evaluateCodeBlocks(
    sem::SemId<sem::Org>         document,
    const OrgCodeEvalParameters& conf) {
    EvalContext ctx{.conf = conf};
    return ctx.evalAll(document);
}
