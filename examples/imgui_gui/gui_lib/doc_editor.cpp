#include "doc_editor.hpp"


DocBlock to_doc_block(const org::ImmAdapter& it) {
    DocBlock result;

    if (auto d = it.asOpt<org::ImmDocument>()) {
        result.data = DocBlock::Document{.origin = d.value()};
        for (auto const& sub : it.sub()) {
            result.nested.push_back(to_doc_block(sub));
        }
    } else if (auto d = it.asOpt<org::ImmParagraph>()) {
        result.data = DocBlock::Paragraph{.origin = d.value()};
    } else if (auto d = it.asOpt<org::ImmSubtree>()) {
        result.data               = DocBlock::Subtree{.origin = d.value()};
        result.getSubtree().title = EditableOrgText::from_adapter(
            d->getTitle());
    } else {
        throw std::domain_error(
            fmt("No known conversion of node {} to doc block", it));
    }


    return result;
}

void render_doc_block(DocBlockModel& model, const DocBlockConfig& conf) {}

void apply_doc_block_actions(
    EditableOrgDocGroup&  history,
    DocBlockModel&        model,
    const DocBlockConfig& config) {}
