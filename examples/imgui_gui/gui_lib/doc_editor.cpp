#include "doc_editor.hpp"


Opt<DocBlock> to_doc_block(const org::ImmAdapter& it) {
    if (it.is(OrgSemKind::Newline)) {
        return std::nullopt;
    } else {
        DocBlock result;

        auto add_subnodes = [&]() {
            for (auto const& sub : it.sub()) {
                auto subdoc = to_doc_block(sub);
                if (subdoc) { result.nested.push_back(subdoc.value()); }
            }
        };

        if (auto d = it.asOpt<org::ImmDocument>()) {
            result.data = DocBlock::Document{.origin = d.value()};
            add_subnodes();
        } else if (auto d = it.asOpt<org::ImmParagraph>()) {
            result.data = DocBlock::Paragraph{.origin = d.value()};
        } else if (auto d = it.asOpt<org::ImmSubtree>()) {
            result.data = DocBlock::Subtree{.origin = d.value()};
            result.getSubtree().title.text = EditableOrgText::from_adapter(
                d->getTitle());
            result.getSubtree().title.setWidth(120);
            add_subnodes();
        } else {
            throw std::domain_error(
                fmt("No known conversion of node {} to doc block", it));
        }


        return result;
    }
}

namespace {

struct DocBlockRenderContext {
    ImVec2 start;
    ImVec2 offset;
    DESC_FIELDS(DocBlockRenderContext, (start, offset));

    ImVec2 getThisWindowPos() const { return start + offset; }

    DocBlockRenderContext withExtraOffset(ImVec2 const& diff) const {
        DocBlockRenderContext result = *this;
        result.offset += diff;
        return result;
    }
};

void render_doc_block(
    DocBlockModel&               model,
    DocBlock&                    block,
    const DocBlockConfig&        conf,
    int&                         dfsIndex,
    DocBlockRenderContext const& renderContext) {

    auto   frameless_vars = push_frameless_window_vars();
    ImVec2 thisSize;
    if (block.isSubtree()) {
        auto const& t = block.getSubtree();
        thisSize      = t.title.getSize();
    } else if (block.isParagraph()) {
        auto const& p = block.getParagraph();
        thisSize      = p.text.getSize();
    } else {
        logic_todo_impl();
    }

    ImGui::SetNextWindowPos(renderContext.getThisWindowPos());


    if (IM_FN_BEGIN(BeginChild, c_fmt("##doc_block_{}", dfsIndex))) {
        if (block.isSubtree()) {
            auto& t = block.getSubtree();
            t.title.render(c_fmt("title_{}", dfsIndex));
        } else if (block.isParagraph()) {
            auto& p = block.getParagraph();
            p.text.render(c_fmt("paragraph_{}", dfsIndex));
        } else {
            logic_todo_impl();
        }
    }

    IM_FN_END(EndChild);
    ImGui::PopStyleVar(frameless_vars);

    ++dfsIndex;
    for (auto& sub : block.nested) {
        render_doc_block(
            model,
            sub,
            conf,
            dfsIndex,
            renderContext.withExtraOffset(thisSize));
    }
}
} // namespace

void render_doc_block(DocBlockModel& model, const DocBlockConfig& conf) {
    int                   dfsIndex = 0;
    DocBlockRenderContext renderContext{};
    render_doc_block(model, model.root, conf, dfsIndex, renderContext);
}

void apply_doc_block_actions(
    EditableOrgDocGroup&  history,
    DocBlockModel&        model,
    const DocBlockConfig& config) {}
