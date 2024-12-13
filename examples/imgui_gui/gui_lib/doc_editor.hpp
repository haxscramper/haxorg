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
    ImVec2               gridViewport;

    DESC_FIELDS(
        DocBlockConfig,
        (editLaneWidth,
         nestingBlockOffset,
         annotationLanesWidth,
         laneConf,
         gridViewport));
};


struct DocBlock : SharedPtrApi<DocBlock> {
    struct Document {
        org::ImmAdapterT<org::ImmDocument> origin;
        ImVec2 getSize() const { return ImVec2(); }
        DESC_FIELDS(Document, (origin));
    };

    struct Annotation {
        EditableOrgTextEntry text;
        Str                  name;
        ImVec2               pos;
        ImVec2 const&        getPos() const { return pos; }
        ImVec2               getSize() const { return text.getSize(); }

        DESC_FIELDS(Annotation, (text, name, pos));

        void setWidth(int width) { text.setWidth(width); }

        void syncSize(int thisLane, DocBlockConfig const& conf) {
            text.setWidth(conf.annotationLanesWidth.at(thisLane));
        }
    };

    struct Paragraph {
        org::ImmAdapterT<org::ImmParagraph> origin;
        EditableOrgTextEntry                text;
        void   setWidth(int width) { text.setWidth(width); }
        ImVec2 getSize() const { return text.getSize(); }
        DESC_FIELDS(Paragraph, (text, origin));
    };

    struct Subtree {
        org::ImmAdapterT<org::ImmSubtree> origin;
        EditableOrgTextEntry              title;

        void   setWidth(int width) { title.setWidth(width); }
        ImVec2 getSize() const { return title.getSize(); }

        DESC_FIELDS(Subtree, (title, origin));
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
    Vec<DocBlock::Ptr>      annotations;
    std::weak_ptr<DocBlock> parent;
    ImVec2                  pos;
    bool                    isVisible = true;

    DESC_FIELDS(
        DocBlock,
        (data, nested, annotations, parent, pos, isVisible));

    ImVec2 const& getPos() const { return pos; }
    void          setPos(ImVec2 const& p) { pos = p; }

    DocBlock::Ptr at(int pos) const { return nested.at(pos); }
    DocBlock::Ptr at(Vec<int> path) const {
        auto res = nested.at(path.front());
        for (int i : path.at(slice(1, 1_B))) { res = res->at(i); }
        return res;
    }

    ImVec2 getSize() {
        return std::visit(
            [](const auto& it) { return it.getSize(); }, data);
    }

    void treeRepr(ColStream& os);

    void setWidth(int width) {
        std::visit(
            overloaded{
                [&](Subtree& st) { st.setWidth(width); },
                [&](Paragraph& par) { par.setWidth(width); },
                [&](Document& d) {},
                [&](Annotation& a) { a.setWidth(width); },
            },
            data);
    }


    void addNested(DocBlock::Ptr block) {
        block->parent = weak_from_this();
        nested.push_back(block);
    }

    void addAnnotation(DocBlock::Ptr block) {
        block->parent = weak_from_this();
        annotations.push_back(block);
    }

    int getDepth() const {
        if (parent.expired()) {
            return 0;
        } else if (isAnnotation()) {
            return parent.lock()->getDepth();
        } else {
            return parent.lock()->getDepth() + 1;
        }
    }

    int getLane() const {
        if (parent.expired()) {
            return 0;
        } else if (isAnnotation()) {
            return parent.lock()->getLane() + 1;
        } else {
            return 0;
        }
    }


    void syncSize(int thisLane, DocBlockConfig const& conf) {
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
                [&](Annotation& a) { a.syncSize(thisLane, conf); },
                [](Document const& d) {},
            },
            data);
    }

    void syncSizeRec(int thisLane, DocBlockConfig const& conf) {
        syncSize(thisLane, conf);
        for (auto& sub : nested) { sub->syncSizeRec(thisLane, conf); }
        for (auto& a : annotations) { a->syncSizeRec(thisLane + 1, conf); }
    }
};

template <>
struct std::formatter<DocBlock*> : std_format_ptr_as_hex<DocBlock> {};
template <>
struct std::formatter<DocBlock const*>
    : std_format_ptr_as_hex<DocBlock> {};

struct DocBlockAction {
    struct NodeEditChanged {
        DocBlock::Ptr block;
        DESC_FIELDS(NodeEditChanged, (block));
    };

    struct NodeTextChanged {
        DocBlock::Ptr   block;
        std::string     updated;
        org::ImmAdapter origin;
        DESC_FIELDS(NodeTextChanged, (block, updated, origin));
    };

    SUB_VARIANTS(
        Kind,
        Data,
        data,
        getKind,
        NodeEditChanged,
        NodeTextChanged);

    Data data;

    DESC_FIELDS(DocBlockAction, (data));
};

struct DocBlockContext
    : OperationsTracer
    , OperationsScope {
    Vec<DocBlockAction> actions;

    void action(
        DocBlockAction::Data const& act,
        int                         line     = __builtin_LINE(),
        char const*                 function = __builtin_FUNCTION(),
        char const*                 file     = __builtin_FILE()) {
        DocBlockAction ga{act};
        message(fmt("Action {}", ga), line, function, file);
        actions.push_back({ga});
    }


    void message(
        std::string const& value,
        int                line     = __builtin_LINE(),
        char const*        function = __builtin_FUNCTION(),
        char const*        file     = __builtin_FILE()) const;
};


struct DocBlockDocument {
    DocBlock::Ptr root;

    DocBlock::Ptr at(int idx) const { return root->at(idx); }
    DocBlock::Ptr at(Vec<int> const& path) const { return root->at(path); }

    org::ImmAdapter getRootOrigin() const {
        return root->getDocument().origin;
    }

    Vec<DocBlock::Ptr> getFlatBlocks() {
        Vec<DocBlock::Ptr>        res;
        Func<void(DocBlock::Ptr)> aux;
        aux = [&](DocBlock::Ptr ptr) {
            res.push_back(ptr);
            for (auto const& sub : ptr->nested) { aux(sub); }
        };

        aux(root);

        return res;
    }

    Vec<DocBlock::Ptr> getFlatAnnotations() {
        Vec<DocBlock::Ptr>        res;
        Func<void(DocBlock::Ptr)> aux;
        aux = [&](DocBlock::Ptr ptr) {
            if (ptr->isAnnotation()) { res.push_back(ptr); }
            for (auto const& sub : ptr->annotations) { aux(sub); }
            for (auto const& sub : ptr->nested) { aux(sub); }
        };

        aux(root);

        return res;
    }

    int      docLaneScrollOffset = 0;
    Vec<int> annotationLaneScrollOffsets;
    void     syncSize(DocBlockConfig const& conf) {
        root->syncSizeRec(0, conf);
    }

    void syncPositions(DocBlockContext& ctx, DocBlockConfig const& conf);
    void syncRoot(org::ImmAdapter const& root, DocBlockConfig const& conf);


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
    DocBlockDocument root;
    DocBlockContext  ctx;
    DESC_FIELDS(DocBlockModel, (root, ctx));
};

Opt<DocBlock::Ptr> to_doc_block(
    org::ImmAdapter const& it,
    DocBlockConfig const&  conf);
void render_doc_block(DocBlockModel& model, DocBlockConfig const& conf);

void apply_doc_block_actions(
    EditableOrgDocGroup&  history,
    DocBlockModel&        model,
    DocBlockConfig const& conf);
