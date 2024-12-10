#include "doc_editor.hpp"


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
                    if (subdoc) {
                        result->nested.push_back(subdoc.value());
                    }
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
    ImVec2 offset;
    int    dfsIndex = 0;
    DESC_FIELDS(DocBlockRenderContext, (start, offset));

    ImVec2 getThisWindowPos() const { return start + offset; }
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
    ImGui::SetNextWindowPos(block->getPos());
    ImGui::SetNextWindowSize(block->getSize());

    if (IM_FN_BEGIN(
            BeginChild, c_fmt("##doc_block_{}", block->selfIndex))) {
        if (block->isSubtree()) {
            auto& t = block->getSubtree();
            t.title.render(c_fmt("title_{}", block->selfIndex));
        } else if (block->isParagraph()) {
            auto& p = block->getParagraph();
            p.text.render(c_fmt("paragraph_{}", block->selfIndex));
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
    render_doc_block(model, model.root, conf, renderContext);
}

void apply_doc_block_actions(
    EditableOrgDocGroup&  history,
    DocBlockModel&        model,
    const DocBlockConfig& config) {}

void DocBlockDocument::syncPositions(const DocBlockConfig& conf) {

}
