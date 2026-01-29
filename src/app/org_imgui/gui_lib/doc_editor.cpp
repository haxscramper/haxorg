// #define NDEBUG ORG_LIB_DEBUG_BUILD
#include <haxorg/imm/ImmOrgGraph.hpp>

#include "doc_editor.hpp"
#include "block_graph.hpp"
#include "node_grid_graph.hpp"
#include <hstd/stdlib/PtrsFormatter.hpp>

using namespace hstd;

#define CTX_MSG(...)                                                      \
    if (ctx.OperationsTracer::TraceState) { ctx.message(__VA_ARGS__); }

#define CTX_MSG_ALL(...) ctx.message(__VA_ARGS__);


Opt<DocBlock::Ptr> to_doc_block(
    const org::imm::ImmAdapter& it,
    const DocBlockConfig&       conf,
    DocBlockContext&            ctx) {

    struct AuxCtx {
        int depth = 0;
        int lane  = 0;

        AuxCtx inLane(int l) const {
            auto r = *this;
            r.lane = l;
            return r;
        }

        int getThisWidth(const DocBlockConfig& conf) const {
            if (lane == 0) {
                return conf.editLaneWidth
                     - (conf.nestingBlockOffset * depth);
                ;
            } else {
                return conf.annotationLanesWidth.at(lane - 1);
            }
        }

        AuxCtx withIncDepth() const {
            auto r = *this;
            r.depth += 1;
            return r;
        }
    };

    Func<Opt<DocBlock::Ptr>(org::imm::ImmAdapter const&, CR<AuxCtx> actx)>
        auxAnnotation;
    Func<Opt<DocBlock::Ptr>(org::imm::ImmAdapter const&, CR<AuxCtx> actx)>
        auxNode;

    auxAnnotation = [&](org::imm::ImmAdapter const& it,
                        CR<AuxCtx> actx) -> Opt<DocBlock::Ptr> {
        CTX_MSG(fmt("Aux annotation from {}", it));
        auto __scope = ctx.scopeLevel();
        auto tmp     = std::make_shared<DocBlockAnnotation>();
        if (auto item = it.asOpt<org::imm::ImmListItem>()) {
            if (auto header = item->getHeader()) {
                tmp->name = EditableOrgTextEntry::from_adapter(
                    header.value(),
                    conf.annotationLanesWidth.at(0),
                    EditableOrgText::Mode::SingleLine);
            }

            for (auto const& sub : item->sub()) {
                auto subdoc = auxNode(sub, actx.withIncDepth());
                if (subdoc) { tmp->addNested(subdoc.value()); }
            }
        }

        return tmp;
    };

    auxNode = [&](org::imm::ImmAdapter const& it,
                  CR<AuxCtx>                  actx) -> Opt<DocBlock::Ptr> {
        if (it.is(OrgSemKind::Newline)) {
            return std::nullopt;
        } else {
            CTX_MSG(fmt("Aux node from {}", it));
            auto           __scope = ctx.scopeLevel();
            SPtr<DocBlock> result;
            auto           add_subnodes = [&]() {
                for (auto const& sub : it.sub()) {
                    auto subdoc = auxNode(sub, actx.withIncDepth());
                    if (subdoc) { result->addNested(subdoc.value()); }
                }
            };

            if (auto d = it.asOpt<org::imm::ImmDocument>()) {
                auto tmp    = std::make_shared<DocBlockDocument>();
                tmp->origin = d.value();
                result      = tmp;
                add_subnodes();
            } else if (auto d = it.asOpt<org::imm::ImmParagraph>()) {
                auto tmp  = std::make_shared<DocBlockParagraph>();
                tmp->text = EditableOrgTextEntry::from_adapter(
                    d.value(), actx.getThisWidth(conf));
                result = tmp;
            } else if (auto d = it.asOpt<org::imm::ImmSubtree>()) {
                auto tmp    = std::make_shared<DocBlockSubtree>();
                tmp->origin = d.value();
                tmp->title  = EditableOrgTextEntry::from_adapter(
                    d->getTitle(), actx.getThisWidth(conf));
                result = tmp;
                for (auto const& sub : it.sub()) {
                    if (org::graph::isAttachedDescriptionList(sub)) {
                        auto annotation = auxAnnotation(
                            sub, actx.withIncDepth());
                        if (annotation) {
                            result->addAnnotation(annotation.value());
                        }
                    } else {
                        auto subdoc = auxNode(sub, actx.withIncDepth());
                        if (subdoc) { result->addNested(subdoc.value()); }
                    }
                }
            } else if (auto e = it.asOpt<org::imm::ImmBlockExport>()) {
                auto tmp    = std::make_shared<DocBlockExport>();
                tmp->origin = e.value();
                result      = tmp;
            } else {
                auto tmp    = std::make_shared<DocBlockFallback>();
                tmp->origin = it;
                result      = tmp;
                add_subnodes();
            }

            ImVec2 size = result->getSize();
            LOGIC_ASSERTION_CHECK_FMT(
                size.x != 0 && size.y != 0,
                "Cannot create block with no size from {}",
                it);

            return result;
        }
    };

    return auxNode(it, AuxCtx{});
}

void render_doc_block(DocBlockModel& model, const DocBlockConfig& conf) {
    DocBlock::RenderContext renderContext{};
    renderContext.start = ImGui::GetCursorScreenPos();
    model.root->render(model, conf, renderContext);


    ImGuiIO& io  = ImGui::GetIO();
    auto&    ctx = model.ctx;
    if (io.MouseWheel != 0.0f) {
        model.ctx.action(
            DocBlockAction::Scroll{
                .pos       = io.MousePos - renderContext.start,
                .direction = io.MouseWheel * conf.mouseScrollMultiplier,
            });
    }

    if (ImGui::IsKeyPressed(ImGuiKey_PageUp)) {
        model.ctx.action(
            DocBlockAction::Scroll{
                .pos       = io.MousePos - renderContext.start,
                .direction = static_cast<float>(conf.pageUpScrollStep),
            });
    }

    if (ImGui::IsKeyPressed(ImGuiKey_PageDown)) {
        model.ctx.action(
            DocBlockAction::Scroll{
                .pos       = io.MousePos - renderContext.start,
                .direction = static_cast<float>(conf.pageDownScrollStep),
            });
    }
}

void apply_doc_block_actions(
    EditableOrgDocGroup&  history,
    DocBlockModel&        model,
    const DocBlockConfig& conf) {
    if (model.ctx.actions.empty()) { return; }

    auto __log_scoped = HSLOG_SINK_FACTORY_SCOPED([]() {
        return ::hstd::log::init_file_sink(
            "/tmp/apply_doc_block_actions.log");
    });

    auto& ctx = model.ctx;

    CTX_MSG("Apply doc block edit actions");
    auto __scope = ctx.scopeLevel();
    for (auto const& act : model.ctx.actions) {
        switch (act.getKind()) {
            case DocBlockAction::Kind::NodeEditChanged: {
                model.syncBlockGraph(conf);
                model.syncLayout(conf);
                break;
            }

            case DocBlockAction::Kind::NodeTextChanged: {
                CTX_MSG("Node text changed, applying changes");
                auto        __scope = ctx.scopeLevel();
                auto const& t       = act.getNodeTextChanged();
                CTX_MSG("Replacing history node");
                auto upd = history.replaceNode(
                    t.edit.origin, t.edit.value.value());
                CTX_MSG("Extending history");
                history.extendHistory(upd);
                CTX_MSG("Sync root for new adapter");
                model.syncRoot(
                    history.getCurrentHistory().getNewRoot(
                        model.root->ptr_as<DocBlockDocument>()
                            ->getRootOrigin()),
                    conf);
                CTX_MSG("Sync positions for new adapter");
                model.syncBlockGraph(conf);
                model.syncLayout(conf);
                break;
            }

            case DocBlockAction::Kind::Scroll: {
                auto const& scr = act.getScroll();
                model.g.addScrolling(scr.pos, scr.direction);
                model.syncLayout(conf);
                break;
            }
        }
    }

    model.ctx.actions.clear();
}

Vec<DocBlock::Ptr> DocBlock::getFlatBlocks() {
    Vec<DocBlock::Ptr>        res;
    Func<void(DocBlock::Ptr)> aux;
    aux = [&](DocBlock::Ptr ptr) {
        res.push_back(ptr);
        for (auto const& sub : ptr->nested) { aux(sub); }
    };

    aux(shared_from_this());

    return res;
}

Vec<DocBlock::Ptr> DocBlock::getFlatAnnotations() {
    Vec<DocBlock::Ptr>        res;
    Func<void(DocBlock::Ptr)> aux;
    aux = [&](DocBlock::Ptr ptr) {
        if (ptr->dyn_cast<DocBlockAnnotation>()) { res.push_back(ptr); }
        for (auto const& sub : ptr->annotations) { aux(sub); }
        for (auto const& sub : ptr->nested) { aux(sub); }
    };

    aux(shared_from_this());

    return res;
}


void DocBlockModel::syncRoot(
    const org::imm::ImmAdapter& root,
    const DocBlockConfig&       conf) {
    this->root = std::dynamic_pointer_cast<DocBlockDocument>(
        to_doc_block(root, conf, ctx).value());
}

void DocBlockModel::syncBlockGraph(const DocBlockConfig& conf) {
    CTX_MSG("Sync block graph");
    auto __scope = ctx.scopeLevel();

    Func<void(DocBlock::Ptr const& block)> aux;

    g.setVisible(conf.gridViewport);

    auto add_graph_rect = [&](DocBlock::Ptr block) -> BlockNodeId {
        auto flatPos = BlockNodeId ::FromIndex(
            flatGrid.push_back_idx(block));
        int         lane    = block->getLane();
        LaneNodePos lanePos = g.addNode(
            lane, flatPos, block->getSize(), conf.laneConf);
        return flatPos;
    };

    for (auto const& block : root->getFlatBlocks()) {
        if (block->dyn_cast<DocBlockDocument>()) { continue; }
        BlockNodeId flatPos                  = add_graph_rect(block);
        g.at(flatPos).horizontalCenterOffset = conf.nestingBlockOffset
                                             * block->getDepth();
        flatGrid.resize_at(flatPos.getIndex()) = block;

        Func<void(DocBlock::Ptr annotation)> aux;
        aux = [&](DocBlock::Ptr annotation) {
            add_graph_rect(annotation);
            for (auto const& sub : annotation->annotations) { aux(sub); }
        };
    }
}

void DocBlockModel::syncLayout(const DocBlockConfig& conf) {
    CTX_MSG("Sync layout graph");
    auto __scope = ctx.scopeLevel();
    lyt          = g.getLayout();
    for (LaneBlockLayout::RectSpec const& rect : lyt.getRectangles(g)) {
        DocBlock::Ptr node = flatGrid.at(rect.blockId.getIndex());
        if (rect.isVisible) {
            LOGIC_ASSERTION_CHECK_FMT(
                rect.size.x != 0 && rect.size.y != 0,
                "Rect is visible but has no size {}. Size of the "
                "original rectangle at position {} is {}",
                rect,
                rect.blockId,
                node->getSize());

            // CTX_MSG(fmt("Rect {}", rect));
            node->isVisible = true;
            node->setPos(rect.pos);
        } else {
            node->isVisible = false;
        }
    }
}


void DocBlockContext::message(
    const std::string& value,
    int                line,
    const char*        function,
    const char*        file) const {
    HSLOG_BUILDER()
        .set_callsite(line, function, file)
        .message(value)
        .depth(activeLevel)
        .severity(hstd::log::l_info)
        .source_scope({"gui", "feature", "doc_edit"});

    OperationsTracer::message(value, function, line, file);
}

void DocBlock::treeRepr(ColStream& os) {
    Func<void(DocBlock::Ptr const&, int)> aux;
    aux = [&](DocBlock::Ptr const& b, int depth) {
        os.indent(depth * 2);
        os << fmt1(b->getKind());

        os << fmt(
            " {}@{} ({})", isVisible ? "Y" : "N", getPos(), getSize());

        os << " ";
        using K = DocBlock::Kind;

#define __case(_Kind)                                                     \
    case K::_Kind:                                                        \
        os << escape_literal(fmt1(*b->dyn_cast<DocBlock##_Kind>()));      \
        break;

        switch (b->getKind()) {
            __case(Annotation);
            __case(Document);
            __case(Export);
            __case(Paragraph);
            __case(Subtree);
            __case(ListHeader);
            __case(Fallback);
        }

        for (auto const& a : b->annotations) {
            os << "\n";
            aux(a, depth + 1);
        }

        for (auto const& a : b->nested) {
            os << "\n";
            aux(a, depth + 1);
        }
    };

    aux(shared_from_this(), 0);
}

int DocBlock::getDepth() const {
    if (parent.expired()) {
        return 0;
    } else if (dyn_cast<DocBlockAnnotation>()) {
        return parent.lock()->getDepth();
    } else {
        return parent.lock()->getDepth() + 1;
    }
}

void doc_editor_loop(
    GLFWwindow*                    window,
    org::sem::SemId<org::sem::Org> node,
    org::parse::ParseContext::Ptr  parse_context) {
    auto          ast_ctx = org::imm::ImmAstContext::init_start_context();
    DocBlockModel model;
    EditableOrgDocGroup docs{ast_ctx, parse_context};
    DocBlockConfig      conf;

    conf.laneConf.getDefaultBlockMargin =
        [](LaneNodePos const&) -> Pair<int, int> { return {0, 0}; };

    model.ctx.setTraceFile("/tmp/doc_editor_trace.log");

    DocRootId root_idx = docs.addRoot(node);

    bool first = true;

    while (!glfwWindowShouldClose(window)) {
        frame_start();
        if (first) {
            conf.gridViewport = ImGui::GetMainViewport()->Size;
            model.syncFull(docs.getCurrentRoot(root_idx), conf);
            writeFile(
                "/tmp/doc_editor_tree.txt",
                model.root->treeRepr().toString(false));
            first = false;
        }

        {
            fullscreen_window_begin();
            { render_doc_block(model, conf); }
            ImGui::End();
        }
        frame_end(window);
        apply_doc_block_actions(docs, model, conf);
        quit_on_q(window);
    }
}

int DocBlock::getLane() const {
    if (parent.expired()) {
        return 0;
    } else if (dyn_cast<DocBlockAnnotation>()) {
        return parent.lock()->getLane() + 1;
    } else {
        return 0;
    }
}

void DocBlock::syncSize(int thisLane, const DocBlockConfig& conf) {
    int depth           = getDepth();
    int widthWithOffset = conf.editLaneWidth
                        - (conf.nestingBlockOffset * depth);

    setWidth(widthWithOffset);
}

namespace {
using ER = EditableOrgText::Result;


void handle_text_edit_result(
    DocBlockModel&        model,
    EditableOrgTextEntry& text,
    DocBlock*             block,
    std::string const&    id) {
    auto result = text.render(id.c_str());

    if (result && result->isChanged()) {
        model.ctx.action(
            DocBlockAction::NodeTextChanged{
                .block = block->shared_from_this(),
                .edit  = result.value(),
            });
    }

    if (result) {
        model.ctx.action(
            DocBlockAction::NodeEditChanged{
                .block = block->shared_from_this()});
    }
};

void configure_window_render(
    DocBlockModel&           model,
    DocBlock*                block,
    DocBlock::RenderContext& renderContext,
    const DocBlockConfig&    conf) {

    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 1);
    ImGui::PushStyleVar(ImGuiStyleVar_ChildBorderSize, 0);
    ImGui::PushStyleColor(ImGuiCol_Border, IM_COL32(255, 0, 0, 255));
    ImGui::PushStyleColor(ImGuiCol_WindowBg, conf.annotationNodeWindowBg);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));

    ImGui::SetNextWindowPos(renderContext.getWindowPos(block));
    ImGui::SetNextWindowSize(block->getSize());
}

void pop_window_render() {
    ImGui::PopStyleVar(3);
    ImGui::PopStyleColor(2);
}

void post_render(DocBlock::RenderContext& renderContext) {
    ++renderContext.dfsIndex;
}

void render_sub_entries(
    DocBlockModel&           model,
    DocBlock*                block,
    const DocBlockConfig&    conf,
    DocBlock::RenderContext& renderContext) {
    for (auto& sub : block->nested) {
        sub->render(model, conf, renderContext);
    }

    for (auto& sub : block->annotations) {
        sub->render(model, conf, renderContext);
    }
}

void debug_render(
    DocBlock*                block,
    DocBlock::RenderContext& renderContext) {
    auto pos = renderContext.getWindowPos(block);
    ImGui::GetForegroundDrawList()->AddRect(
        pos, pos + block->getSize(), IM_COL32(0, 255, 255, 255));

    AddText(
        ImGui::GetForegroundDrawList(),
        pos + ImVec2{600, 0},
        IM_COL32(0, 255, 0, 255),
        fmt("{} @{} {}",
            block->getKind(),
            block->getPos(),
            block->getSize()));
}

} // namespace

void DocBlockDocument::render(
    DocBlockModel&        model,
    const DocBlockConfig& conf,
    RenderContext&        renderContext) {
    debug_render(this, renderContext);
    post_render(renderContext);
    render_sub_entries(model, this, conf, renderContext);
}

void DocBlockParagraph::render(
    DocBlockModel&        model,
    const DocBlockConfig& conf,
    RenderContext&        renderContext) {
    if (!isVisible) { return; }
    configure_window_render(model, this, renderContext, conf);
    if (IM_FN_BEGIN(
            BeginChild, renderContext.getId("##doc_block").c_str())) {
        handle_text_edit_result(
            model, text, this, renderContext.getId("text"));
    }
    IM_FN_END(EndChild);
    pop_window_render();
    debug_render(this, renderContext);
    post_render(renderContext);
}

void DocBlockAnnotation::render(
    DocBlockModel&        model,
    const DocBlockConfig& conf,
    RenderContext&        renderContext) {
    if (!isVisible) { return; }
    configure_window_render(model, this, renderContext, conf);
    if (IM_FN_BEGIN(
            BeginChild, renderContext.getId("##doc_block").c_str())) {
        handle_text_edit_result(
            model, name, this, renderContext.getId("annotation"));
    }
    IM_FN_END(EndChild);

    pop_window_render();
    debug_render(this, renderContext);
    post_render(renderContext);
    render_sub_entries(model, this, conf, renderContext);
}

void DocBlockExport::render(
    DocBlockModel&        model,
    const DocBlockConfig& conf,
    RenderContext&        renderContext) {
    if (!isVisible) { return; }
}

void DocBlockSubtree::render(
    DocBlockModel&        model,
    const DocBlockConfig& conf,
    RenderContext&        renderContext) {
    if (isVisible) {
        configure_window_render(model, this, renderContext, conf);
        if (IM_FN_BEGIN(
                BeginChild, renderContext.getId("##doc_block").c_str())) {
            handle_text_edit_result(
                model, title, this, renderContext.getId("title"));
        }
        IM_FN_END(EndChild);
        pop_window_render();
    }

    post_render(renderContext);
    debug_render(this, renderContext);
    render_sub_entries(model, this, conf, renderContext);
}

void DocBlockListHeader::render(
    DocBlockModel&        model,
    const DocBlockConfig& conf,
    RenderContext&        renderContext) {
    post_render(renderContext);
    debug_render(this, renderContext);
    render_sub_entries(model, this, conf, renderContext);
}

void DocBlockFallback::render(
    DocBlockModel&        model,
    const DocBlockConfig& conf,
    RenderContext&        renderContext) {
    if (isVisible) {
        configure_window_render(model, this, renderContext, conf);
        if (IM_FN_BEGIN(
                BeginChild, renderContext.getId("##doc_block").c_str())) {
            auto pos = getCurrentWindowContentPos();

            AddText(
                dl(),
                pos,
                IM_COL32(255, 0, 0, 255),
                fmt("Fallback for {}", origin.getKind()));
        }
        IM_FN_END(EndChild);
        pop_window_render();
    }

    debug_render(this, renderContext);
    post_render(renderContext);
    render_sub_entries(model, this, conf, renderContext);
}
