#pragma once

#include <gui_lib/imgui_utils.hpp>
#include <haxorg/sem/ImmOrg.hpp>
#include <gui_lib/im_org_ui_common.hpp>


struct DocBlock {
    struct Document {
        org::ImmAdapterT<org::ImmDocument> origin;
    };

    struct Paragraph {
        struct Annotation {
            EditableOrgText text;
            Str             name;
            DESC_FIELDS(Annotation, (text, name));
        };

        org::ImmAdapterT<org::ImmParagraph> origin;
        EditableOrgText                     text;
        Vec<Annotation>                     annotations;


        DESC_FIELDS(Paragraph, (text, origin, annotations));
    };

    struct Subtree {
        struct Annotation {
            EditableOrgText text;
            Str             name;
            DESC_FIELDS(Annotation, (text, name));
        };

        org::ImmAdapterT<org::ImmSubtree> origin;
        EditableOrgText                   title;
        Vec<Annotation>                   annotations;

        DESC_FIELDS(Subtree, (title, origin, annotations));
    };


    SUB_VARIANTS(Kind, Data, data, getKind, Paragraph, Subtree, Document);

    Data          data;
    Vec<DocBlock> nested;

    DESC_FIELDS(DocBlock, (data, nested));
};

DocBlock to_doc_block(org::ImmAdapter const& it);
