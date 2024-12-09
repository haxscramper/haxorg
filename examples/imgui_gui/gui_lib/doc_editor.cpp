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
        result.data = DocBlock::Subtree{.origin = d.value()};
        result.getSubtree().title =
    } else {
        throw std::domain_error(
            fmt("No known conversion of node {} to doc block", it));
    }


    return result;
}

EditableOrgText to_editable_text(const org::ImmAdapter it) {
    EditableOrgText res;


    return res;
}
