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

struct DocBlockModel;
struct DocBlockContext;

template <typename T>
struct PtrAstApi {
    template <typename Other>
    Other* dyn_cast() {
        return dynamic_cast<Other*>(this);
    }

    template <typename Other>
    Other const* dyn_cast() const {
        return dynamic_cast<Other const*>(this);
    }
};

struct DocBlock
    : SharedPtrApi<DocBlock>
    , PtrAstApi<DocBlock> {
    struct RenderContext {
        ImVec2 start;
        int    dfsIndex = 0;
        DESC_FIELDS(RenderContext, (start));

        int getIndex() { return dfsIndex++; }

        ImVec2 getThisWindowPos() const { return start; }
        ImVec2 getWindowPos(DocBlock* block) const {
            return block->getPos() + start;
        }
    };

    Vec<DocBlock::Ptr>      nested;
    Vec<DocBlock::Ptr>      annotations;
    std::weak_ptr<DocBlock> parent;
    bool                    isVisible = true;

    ImVec2         pos;
    virtual ImVec2 getSize() const     = 0;
    virtual void   setWidth(int width) = 0;
    ImVec2         getPos() const { return pos; }
    virtual void   setPos(ImVec2 const& p) { pos = p; }

    virtual void render(DocBlockModel& model, DocBlockConfig const& conf);


    DocBlock::Ptr at(int pos) const { return nested.at(pos); }
    DocBlock::Ptr at(Vec<int> path) const {
        auto res = nested.at(path.front());
        for (int i : path.at(slice(1, 1_B))) { res = res->at(i); }
        return res;
    }

    void treeRepr(ColStream& os);

    void addNested(DocBlock::Ptr block) {
        block->parent = weak_from_this();
        nested.push_back(block);
    }

    void addAnnotation(DocBlock::Ptr block) {
        block->parent = weak_from_this();
        annotations.push_back(block);
    }

    int getDepth() const;

    int getLane() const;

    virtual void syncSize(int thisLane, DocBlockConfig const& conf) {
        int depth           = getDepth();
        int widthWithOffset = conf.editLaneWidth
                            - (conf.nestingBlockOffset * depth);

        setWidth(widthWithOffset);
    }

    virtual void syncSizeRec(int thisLane, DocBlockConfig const& conf) {
        syncSize(thisLane, conf);
        for (auto& sub : nested) { sub->syncSizeRec(thisLane, conf); }
        for (auto& a : annotations) { a->syncSizeRec(thisLane + 1, conf); }
    }
};

struct DocBlockDocument : public DocBlock {
    org::ImmAdapterT<org::ImmDocument> origin;
    ImVec2                             getSize() const { return ImVec2(); }
    void                               setWidth(int w) {}
    DESC_FIELDS(DocBlockDocument, (origin));

    org::ImmAdapter getRootOrigin() const { return origin; }

    Vec<DocBlock::Ptr> getFlatBlocks() {
        Vec<DocBlock::Ptr>        res;
        Func<void(DocBlock::Ptr)> aux;
        aux = [&](DocBlock::Ptr ptr) {
            res.push_back(ptr);
            for (auto const& sub : ptr->nested) { aux(sub); }
        };

        aux(shared_from_this());

        return res;
    }

    Vec<DocBlock::Ptr> getFlatAnnotations();

    int      docLaneScrollOffset = 0;
    Vec<int> annotationLaneScrollOffsets;
    void syncPositions(DocBlockContext& ctx, DocBlockConfig const& conf);
    void syncRoot(org::ImmAdapter const& root, DocBlockConfig const& conf);


    int getLaneScroll(int lane) {
        if (lane == 0) {
            return docLaneScrollOffset;
        } else {
            return docLaneScrollOffset
                 + annotationLaneScrollOffsets.at_or(lane - 1, 0);
        }
    }
};

struct DocBlockAnnotation : public DocBlock {
    EditableOrgTextEntry text;
    Str                  name;
    ImVec2               pos;
    ImVec2 const&        getPos() const { return pos; }
    ImVec2               getSize() const { return text.getSize(); }

    DESC_FIELDS(DocBlockAnnotation, (text, name, pos));

    void setWidth(int width) { text.setWidth(width); }

    void syncSize(int thisLane, DocBlockConfig const& conf) {
        text.setWidth(conf.annotationLanesWidth.at(thisLane));
    }
};

struct DocBlockExport : public DocBlock {
    org::ImmAdapterT<org::ImmBlockExport> origin;
    ImVec2 getSize() const { return ImVec2{100, 20}; }
    void   setWidth(int width) {}
    DESC_FIELDS(DocBlockExport, (origin));
};

struct DocBlockParagraph : public DocBlock {
    org::ImmAdapterT<org::ImmParagraph> origin;
    EditableOrgTextEntry                text;
    void   setWidth(int width) { text.setWidth(width); }
    ImVec2 getSize() const { return text.getSize(); }
    DESC_FIELDS(DocBlockParagraph, (text, origin));
};

struct DocBlockSubtree : public DocBlock {
    org::ImmAdapterT<org::ImmSubtree> origin;
    EditableOrgTextEntry              title;

    void   setWidth(int width) { title.setWidth(width); }
    ImVec2 getSize() const { return title.getSize(); }

    DESC_FIELDS(DocBlockSubtree, (title, origin));
};

struct DocBlockListHeader : public DocBlock {
    org::ImmAdapterT<org::ImmList> origin;

    void   setWidth(int width) {}
    ImVec2 getSize() const { return ImVec2{100, 20}; }
    DESC_FIELDS(DocBlockListHeader, (origin));
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

void doc_editor_loop(GLFWwindow* window, sem::SemId<sem::Org> node);
