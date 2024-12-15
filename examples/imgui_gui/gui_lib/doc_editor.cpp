#define NDEBUG 0

#include "doc_editor.hpp"
#include "block_graph.hpp"
#include "node_grid_graph.hpp"

#define CTX_MSG(...)                                                      \
    if (ctx.OperationsTracer::TraceState) { ctx.message(__VA_ARGS__); }

#define CTX_MSG_ALL(...) ctx.message(__VA_ARGS__);


Opt<DocBlock::Ptr> to_doc_block(
    const org::ImmAdapter& it,
    const DocBlockConfig&  conf) {

    Func<Opt<DocBlock::Ptr>(org::ImmAdapter const&, int)> aux;
    aux = [&](org::ImmAdapter const& it, int depth) -> Opt<DocBlock::Ptr> {
        if (it.is(OrgSemKind::Newline)) {
            return std::nullopt;
        } else {
            SPtr<DocBlock> result;

            auto thisWidth = conf.editLaneWidth
                           - (conf.nestingBlockOffset * depth);

            auto add_subnodes = [&]() {
                for (auto const& sub : it.sub()) {
                    auto subdoc = aux(sub, depth + 1);
                    if (subdoc) { result->addNested(subdoc.value()); }
                }
            };

            if (auto d = it.asOpt<org::ImmDocument>()) {
                auto tmp    = std::make_shared<DocBlockDocument>();
                tmp->origin = d.value();
                result      = tmp;
                add_subnodes();
            } else if (auto d = it.asOpt<org::ImmParagraph>()) {
                auto tmp  = std::make_shared<DocBlockParagraph>();
                tmp->text = EditableOrgTextEntry::from_adapter(
                    d.value(), thisWidth);
                result = tmp;
            } else if (auto d = it.asOpt<org::ImmSubtree>()) {
                auto tmp    = std::make_shared<DocBlockSubtree>();
                tmp->origin = d.value();
                tmp->title  = EditableOrgTextEntry::from_adapter(
                    d->getTitle(), thisWidth);
                result = tmp;
                add_subnodes();
            } else if (auto e = it.asOpt<org::ImmBlockExport>()) {
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
            LOGIC_ASSERTION_CHECK(
                size.x != 0 && size.y != 0,
                "Cannot create block with no size from {}",
                it);

            return result;
        }
    };

    return aux(it, 0);
}

void render_doc_block(DocBlockModel& model, const DocBlockConfig& conf) {
    DocBlock::RenderContext renderContext{};
    renderContext.start = ImGui::GetCursorScreenPos();
    model.root->render(model, conf, renderContext);


    ImGuiIO& io  = ImGui::GetIO();
    auto&    ctx = model.ctx;
    if (io.MouseWheel != 0.0f) {
        model.ctx.action(DocBlockAction::Scroll{
            .pos       = io.MousePos - renderContext.start,
            .direction = io.MouseWheel * conf.mouseScrollMultiplier,
        });
    }

    if (ImGui::IsKeyPressed(ImGuiKey_PageUp)) {
        model.ctx.action(DocBlockAction::Scroll{
            .pos       = io.MousePos - renderContext.start,
            .direction = static_cast<float>(conf.pageUpScrollStep),
        });
    }

    if (ImGui::IsKeyPressed(ImGuiKey_PageDown)) {
        model.ctx.action(DocBlockAction::Scroll{
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

    auto __log_scoped = OLOG_SINK_FACTORY_SCOPED([]() {
        return ::org_logging::init_file_sink(
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
                auto upd = history.replace_node(t.origin, t.updated);
                CTX_MSG("Extending history");
                history.extend_history(upd);
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
                model.g.ir.addScrolling(scr.pos, scr.direction);
                model.g.ir.resetVisibility();
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
    const org::ImmAdapter& root,
    const DocBlockConfig&  conf) {
    this->root = std::dynamic_pointer_cast<DocBlockDocument>(
        to_doc_block(root, conf).value());
}

void DocBlockModel::syncBlockGraph(const DocBlockConfig& conf) {
    CTX_MSG("Sync block graph");
    auto __scope = ctx.scopeLevel();

    Func<void(DocBlock::Ptr const& block)> aux;

    g.setVisible(conf.gridViewport);

    auto add_graph_rect = [&](DocBlock::Ptr block) -> int {
        int         flatPos = flatGrid.push_back_idx(block);
        int         lane    = block->getLane();
        LaneNodePos lanePos = g.ir.addNode(
            lane, block->getSize(), conf.laneConf);

        g.add(flatPos, lanePos);
        return flatPos;
    };

    for (auto const& block : root->getFlatBlocks()) {
        if (block->dyn_cast<DocBlockDocument>()) { continue; }
        int flatPos                               = add_graph_rect(block);
        g.getNode(flatPos).horizontalCenterOffset = conf.nestingBlockOffset
                                                  * block->getDepth();
        flatGrid.resize_at(flatPos) = block;

        Func<void(DocBlock::Ptr annotation)> aux;
        aux = [&](DocBlock::Ptr annotation) {
            int flatPos = add_graph_rect(annotation);
            for (auto const& sub : annotation->annotations) { aux(sub); }
        };
    }
}

void DocBlockModel::syncLayout(const DocBlockConfig& conf) {
    CTX_MSG("Sync layout graph");
    auto __scope = ctx.scopeLevel();
    g.syncLayout();
    for (NodeGridGraph::RectSpec const& rect : g.getRectangles()) {
        DocBlock::Ptr node = flatGrid.at(rect.flatPos);
        if (rect.isVisible) {
            LOGIC_ASSERTION_CHECK(
                rect.size.x != 0 && rect.size.y != 0,
                "Rect is visible but has no size {}. Size of the "
                "original rectangle at position {} is {}",
                rect,
                rect.flatPos,
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
    OLOG_BUILDER()
        .set_callsite(line, function, file)
        .message(value)
        .depth(activeLevel)
        .category("doc-edit")
        .severity(ol_info)
        .source_scope({"gui", "feature", "doc_edit"});

    OperationsTracer::message(value, activeLevel, line, function, file);
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

void doc_editor_loop(GLFWwindow* window, sem::SemId<sem::Org> node) {
    auto                ast_ctx = org::ImmAstContext::init_start_context();
    DocBlockModel       model;
    EditableOrgDocGroup docs{ast_ctx};
    DocBlockConfig      conf;

    conf.laneConf.getDefaultBlockMargin =
        [](LaneNodePos const&) -> Pair<int, int> { return {0, 0}; };

    model.ctx.setTraceFile("/tmp/doc_editor_trace.log");

    int root_idx = docs.init_root(node);

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

    if (result == ER::Changed) {
        model.ctx.action(DocBlockAction::NodeTextChanged{
            .block   = block->shared_from_this(),
            .updated = text.text.value,
            .origin  = text.text.origin,
        });
    }

    if (result == ER::CancelledEditing || result == ER::StartedEditing
        || result == ER::Changed) {
        model.ctx.action(DocBlockAction::NodeEditChanged{
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

void render_nested(
    DocBlockModel&           model,
    DocBlock*                block,
    const DocBlockConfig&    conf,
    DocBlock::RenderContext& renderContext) {
    for (auto& sub : block->nested) {
        sub->render(model, conf, renderContext);
    }
}

void debug_render(
    DocBlock*                block,
    DocBlock::RenderContext& renderContext) {
    AddText(
        ImGui::GetForegroundDrawList(),
        renderContext.getWindowPos(block) + ImVec2{600, 0},
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
    render_nested(model, this, conf, renderContext);
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
            model, text, this, renderContext.getId("annotation"));
    }
    IM_FN_END(EndChild);

    pop_window_render();
    debug_render(this, renderContext);
    post_render(renderContext);
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
    render_nested(model, this, conf, renderContext);
}

void DocBlockListHeader::render(
    DocBlockModel&        model,
    const DocBlockConfig& conf,
    RenderContext&        renderContext) {
    post_render(renderContext);
    debug_render(this, renderContext);
    render_nested(model, this, conf, renderContext);
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
    render_nested(model, this, conf, renderContext);
}
