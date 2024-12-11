#pragma once

#include "gui_lib/block_graph.hpp"
#include <gui_lib/imgui_utils.hpp>
#include <haxorg/sem/ImmOrg.hpp>
#include <gui_lib/im_org_ui_common.hpp>
#include <hstd/stdlib/Ptrs.hpp>

struct DocBlockConfig {
    int                  editLaneWidth      = 600;
    int                  nestingBlockOffset = 40;
    Vec<int>             annotationLanesWidth{200};
    LaneBlockGraphConfig laneConf;

    DESC_FIELDS(
        DocBlockConfig,
        (editLaneWidth,
         nestingBlockOffset,
         annotationLanesWidth,
         laneConf));
};


struct DocBlock : SharedPtrApi<DocBlock> {
    struct Document {
        org::ImmAdapterT<org::ImmDocument> origin;
        ImVec2 getSize() const { return ImVec2(); }
    };

    struct Annotation {
        EditableOrgTextEntry text;
        Str                  name;
        ImVec2               pos;
        ImVec2 const&        getPos() const { return pos; }
        DESC_FIELDS(Annotation, (text, name, pos));

        void syncSize(int thisLane, DocBlockConfig const& conf) {
            text.setWidth(conf.annotationLanesWidth.at(thisLane));
        }
    };


    struct Paragraph {
        org::ImmAdapterT<org::ImmParagraph> origin;
        EditableOrgTextEntry                text;
        Vec<Annotation>                     annotations;
        void   setWidth(int width) { text.setWidth(width); }
        ImVec2 getSize() const { return text.getSize(); }
        DESC_FIELDS(Paragraph, (text, origin, annotations));
    };

    struct Subtree {
        org::ImmAdapterT<org::ImmSubtree> origin;
        EditableOrgTextEntry              title;
        Vec<Annotation>                   annotations;

        void   setWidth(int width) { title.setWidth(width); }
        ImVec2 getSize() const { return title.getSize(); }

        DESC_FIELDS(Subtree, (title, origin, annotations));
    };


    SUB_VARIANTS(
        Kind,
        Data,
        data,
        getKind,
        Paragraph,
        Subtree,
        Document,
        Annotation);

    Data                    data;
    Vec<DocBlock::Ptr>      nested;
    std::weak_ptr<DocBlock> parent;
    ImVec2                  pos;
    int                     selfIndex = 0;

    ImVec2 const& getPos() const { return pos; }

    ImVec2 getSize() {
        return std::visit(
            [](const auto& it) { return it.getSize(); }, data);
    }

    void setWidth(int width) {
        std::visit(
            overloaded{
                [&](Subtree& st) { st.setWidth(width); },
                [&](Paragraph& par) { par.setWidth(width); },
                [&](Document& d) {},
            },
            data);
    }


    void add_nested(DocBlock::Ptr block) {
        block->parent = weak_from_this();
        nested.push_back(block);
    }

    int getDepth() const {
        if (parent.expired()) {
            return 0;
        } else {
            return parent.lock()->getDepth() + 1;
        }
    }

    DESC_FIELDS(DocBlock, (data, nested, parent, pos, selfIndex));

    void syncSize(DocBlockConfig const& conf) {
        int depth = getDepth();
        std::visit(
            overloaded{
                [&](Subtree& p) {
                    p.title.setWidth(
                        conf.editLaneWidth
                        - (conf.nestingBlockOffset * depth));
                },
                [&](Paragraph& p) {
                    p.text.setWidth(
                        conf.editLaneWidth
                        - (conf.nestingBlockOffset * depth));
                },
                [](Document const& d) {},
            },
            data);
    }

    void syncSizeRec(DocBlockConfig const& conf) {
        syncSize(conf);
        for (auto& sub : nested) { sub->syncSizeRec(conf); }
    }
};

struct DocBlockAction {};

struct DocBlockContext
    : OperationsTracer
    , OperationsScope {
    Vec<DocBlockAction> actions;
};


struct DocBlockDocument {
    DocBlock::Ptr      root;
    Vec<DocBlock::Ptr> getFlatBlocks() {
        Vec<DocBlock::Ptr>        res;
        Func<void(DocBlock::Ptr)> aux;
        aux = [&](DocBlock::Ptr ptr) {
            res.push_back(ptr);
            for (auto const& sub : ptr->nested) { aux(sub); }
        };

        return res;
    }
    int      docLaneScrollOffset = 0;
    Vec<int> annotationLaneScrollOffsets;
    void syncSize(DocBlockConfig const& conf) { root->syncSizeRec(conf); }
    void syncPositions(DocBlockConfig const& conf);
    DESC_FIELDS(
        DocBlockDocument,
        (root, docLaneScrollOffset, annotationLaneScrollOffsets));

    int getLaneScroll(int lane) {
        if (lane == 0) {
            return docLaneScrollOffset;
        } else {
            return docLaneScrollOffset
                 + annotationLaneScrollOffsets.at_or(lane - 1, 0);
        }
    }
};

struct DocBlockModel {
    DocBlock::Ptr   root;
    DocBlockContext ctx;
    DESC_FIELDS(DocBlockModel, (root, ctx));
};

Opt<DocBlock::Ptr> to_doc_block(
    org::ImmAdapter const& it,
    DocBlockConfig const&  conf);
void render_doc_block(DocBlockModel& model, DocBlockConfig const& conf);

void apply_doc_block_actions(
    EditableOrgDocGroup&  history,
    DocBlockModel&        model,
    DocBlockConfig const& config);
