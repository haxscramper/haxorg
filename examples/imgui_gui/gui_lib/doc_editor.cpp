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
            auto result = DocBlock::shared();

            auto thisWidth = conf.editLaneWidth
                           - (conf.nestingBlockOffset * depth);

            auto add_subnodes = [&]() {
                for (auto const& sub : it.sub()) {
                    auto subdoc = aux(sub, depth + 1);
                    if (subdoc) { result->addNested(subdoc.value()); }
                }
            };

            if (auto d = it.asOpt<org::ImmDocument>()) {
                result->data = DocBlock::Document{.origin = d.value()};
                add_subnodes();
            } else if (auto d = it.asOpt<org::ImmParagraph>()) {
                result->data = DocBlock::Paragraph{.origin = d.value()};
                result->getParagraph().text = EditableOrgTextEntry::
                    from_adapter(d.value(), thisWidth);
            } else if (auto d = it.asOpt<org::ImmSubtree>()) {
                result->data = DocBlock::Subtree{.origin = d.value()};
                result->getSubtree().title = EditableOrgTextEntry::
                    from_adapter(d->getTitle(), thisWidth);
                add_subnodes();
            } else {
                throw std::domain_error(fmt(
                    "No known conversion of node {} to doc block", it));
            }


            return result;
        }
    };

    return aux(it, 0);
}

namespace {

struct DocBlockRenderContext {
    ImVec2 start;
    int    dfsIndex = 0;
    DESC_FIELDS(DocBlockRenderContext, (start));

    int getIndex() { return dfsIndex++; }

    ImVec2 getThisWindowPos() const { return start; }
    ImVec2 getWindowPos(DocBlock::Ptr const& block) const {
        return block->getPos() + start;
    }
};

void render_doc_annotation() {}

void render_doc_block(
    DocBlockModel&         model,
    DocBlock::Ptr&         block,
    const DocBlockConfig&  conf,
    DocBlockRenderContext& renderContext) {
    auto __scope = IM_SCOPE_BEGIN(
        "Doc block rendering",
        fmt("Index {} kind {}", renderContext.dfsIndex, block->getKind()));

    auto frameless_vars = push_frameless_window_vars();
    ImGui::SetNextWindowPos(renderContext.getWindowPos(block));
    ImGui::SetNextWindowSize(block->getSize());

    int selfIndex = renderContext.getIndex();

    using ER = EditableOrgText::Result;

    auto handle_edit_result = [&](ER result) {
        if (result == ER::CancelledEditing || result == ER::StartedEditing
            || result == ER::Changed) {
            model.ctx.action(
                DocBlockAction::NodeEditChanged{.block = block});
        }
    };

    if (IM_FN_BEGIN(BeginChild, c_fmt("##doc_block_{}", selfIndex))) {
        if (block->isSubtree()) {
            auto& t = block->getSubtree();
            handle_edit_result(
                t.title.render(c_fmt("title_{}", selfIndex)));
        } else if (block->isParagraph()) {
            auto& p = block->getParagraph();
            handle_edit_result(
                p.text.render(c_fmt("paragraph_{}", selfIndex)));
        } else if (block->isDocument()) {
            // pass
        } else {
            logic_todo_impl();
        }
    }

    IM_FN_END(EndChild);
    ImGui::PopStyleVar(frameless_vars);

    ++renderContext.dfsIndex;
    for (auto& sub : block->nested) {
        render_doc_block(model, sub, conf, renderContext);
    }
}
} // namespace

void render_doc_block(DocBlockModel& model, const DocBlockConfig& conf) {
    DocBlockRenderContext renderContext{};
    renderContext.start = ImGui::GetCursorScreenPos();
    render_doc_block(model, model.root.root, conf, renderContext);
}

void apply_doc_block_actions(
    EditableOrgDocGroup&  history,
    DocBlockModel&        model,
    const DocBlockConfig& conf) {
    auto& ctx = model.ctx;
    CTX_MSG("Apply doc block edit actions");
    auto __scope = ctx.scopeLevel();
    for (auto const& act : model.ctx.actions) {
        switch (act.getKind()) {
            case DocBlockAction::Kind::NodeEditChanged: {
                model.root.syncPositions(model.ctx, conf);
                break;
            }
        }
    }
}

void DocBlockDocument::syncPositions(
    DocBlockContext&      ctx,
    const DocBlockConfig& conf) {
    CTX_MSG("Sync positions");
    auto __scope = ctx.scopeLevel();

    NodeGridGraph                          g;
    Func<void(DocBlock::Ptr const& block)> aux;

    g.setVisible(conf.gridViewport);

    int const mainLane       = 0;
    int const annotationLane = 1;

    g.ir.lane(mainLane, conf.laneConf).scrollOffset = docLaneScrollOffset;
    for (int i = annotationLane;
         i < annotationLaneScrollOffsets.size() + 1;
         ++i) {
        g.ir.lane(i, conf.laneConf).scrollOffset = getLaneScroll(i);
    }

    Vec<DocBlock::Ptr> flatGrid;

    auto add_graph_rect = [&](DocBlock::Ptr block) -> int {
        int         flatPos = flatGrid.push_back_idx(block);
        int         lane    = block->getLane();
        LaneNodePos lanePos = g.ir.addNode(
            lane, block->getSize(), conf.laneConf);

        g.add(flatPos, lanePos);
        return flatPos;
    };

    for (auto const& block : getFlatBlocks()) {
        if (block->isDocument()) { continue; }
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

    g.syncLayout();


    {
        CTX_MSG("Rectangle positions");
        auto __scope = ctx.scopeLevel();
        for (NodeGridGraph::RectSpec const& rect : g.getRectangles()) {
            CTX_MSG(fmt("Rect {}", rect));
            DocBlock::Ptr node = flatGrid.at(rect.flatPos);
            if (rect.isVisible) {
                node->isVisible = true;
                node->setPos(rect.pos);
            } else {
                node->isVisible = false;
            }
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

        std::visit([&](auto const& d) { os << " " << fmt1(d); }, b->data);

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
