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
struct PtrAstApi : public CRTP_this_method<T> {
    using CRTP_this_method<T>::_this;
    template <typename Other>
    Other* dyn_cast() {
        return dynamic_cast<Other*>(_this());
    }

    template <typename Other>
    Other const* dyn_cast() const {
        return dynamic_cast<Other const*>(_this());
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

    template <typename Other>
    SPtr<Other> ptr_as() {
        auto tmp = std::dynamic_pointer_cast<Other>(shared_from_this());
        LOGIC_ASSERTION_CHECK(tmp.get() != nullptr, "Ptr get failed");
        return tmp;
    }

    DECL_DESCRIBED_ENUM(
        Kind,
        Annotation,
        Document,
        Export,
        Paragraph,
        Subtree,
        ListHeader);

#define __kind_methods(_Kind)                                             \
    bool is##_Kind() const { return getKind() == Kind::_Kind; }

    __kind_methods(Annotation);
    __kind_methods(Document);
    __kind_methods(Export);
    __kind_methods(Paragraph);
    __kind_methods(Subtree);
    __kind_methods(ListHeader);

#undef __kind_methods

    Vec<DocBlock::Ptr>      nested;
    Vec<DocBlock::Ptr>      annotations;
    std::weak_ptr<DocBlock> parent;
    bool                    isVisible = true;

    DESC_FIELDS(DocBlock, (nested, annotations, isVisible));

    ImVec2         pos;
    virtual Kind   getKind() const     = 0;
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

    virtual void syncSize(int thisLane, DocBlockConfig const& conf);

    virtual void syncSizeRec(int thisLane, DocBlockConfig const& conf) {
        syncSize(thisLane, conf);
        for (auto& sub : nested) { sub->syncSizeRec(thisLane, conf); }
        for (auto& a : annotations) { a->syncSizeRec(thisLane + 1, conf); }
    }

    Vec<DocBlock::Ptr> getFlatBlocks();
    Vec<DocBlock::Ptr> getFlatAnnotations();
};

struct DocBlockDocument : public DocBlock {
    org::ImmAdapterT<org::ImmDocument> origin;

    Kind   getKind() const override { return Kind::Document; }
    ImVec2 getSize() const override { return ImVec2(); }
    void   setWidth(int w) override {}

    BOOST_DESCRIBE_CLASS(DocBlockDocument, (DocBlock), (origin), (), ());

    org::ImmAdapter getRootOrigin() const { return origin; }
};

struct DocBlockAnnotation : public DocBlock {
    EditableOrgTextEntry text;
    Str                  name;
    ImVec2               pos;

    ImVec2 const& getPos() const { return pos; }
    ImVec2        getSize() const override { return text.getSize(); }
    Kind          getKind() const override { return Kind::Annotation; }

    BOOST_DESCRIBE_CLASS(
        DocBlockAnnotation,
        (DocBlock),
        (text, name, pos),
        (),
        ());

    void setWidth(int width) override { text.setWidth(width); }

    void syncSize(int thisLane, DocBlockConfig const& conf) override {
        text.setWidth(conf.annotationLanesWidth.at(thisLane));
    }
};

struct DocBlockExport : public DocBlock {
    org::ImmAdapterT<org::ImmBlockExport> origin;
    ImVec2 getSize() const override { return ImVec2{100, 20}; }
    void   setWidth(int width) override {}
    Kind   getKind() const override { return Kind::Export; }
    BOOST_DESCRIBE_CLASS(DocBlockExport, (DocBlock), (origin), (), ());
};

struct DocBlockParagraph : public DocBlock {
    org::ImmAdapterT<org::ImmParagraph> origin;
    EditableOrgTextEntry                text;
    void   setWidth(int width) override { text.setWidth(width); }
    ImVec2 getSize() const override { return text.getSize(); }
    Kind   getKind() const override { return Kind::Paragraph; }
    BOOST_DESCRIBE_CLASS(DocBlockParagraph, (), (text, origin), (), ());
};

struct DocBlockSubtree : public DocBlock {
    org::ImmAdapterT<org::ImmSubtree> origin;
    EditableOrgTextEntry              title;

    void   setWidth(int width) override { title.setWidth(width); }
    ImVec2 getSize() const override { return title.getSize(); }
    Kind   getKind() const override { return Kind::Subtree; }

    BOOST_DESCRIBE_CLASS(DocBlockSubtree, (), (title, origin), (), ());
};

struct DocBlockListHeader : public DocBlock {
    org::ImmAdapterT<org::ImmList> origin;
    Kind   getKind() const override { return Kind::ListHeader; }
    void   setWidth(int width) override {}
    ImVec2 getSize() const override { return ImVec2{100, 20}; }
    BOOST_DESCRIBE_CLASS(DocBlockListHeader, (DocBlock), (origin), (), ());
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
    DocBlockDocument::Ptr root;
    DocBlockContext       ctx;

    int      docLaneScrollOffset = 0;
    Vec<int> annotationLaneScrollOffsets;

    DESC_FIELDS(DocBlockModel, (root, ctx));

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

Opt<DocBlock::Ptr> to_doc_block(
    org::ImmAdapter const& it,
    DocBlockConfig const&  conf);
void render_doc_block(DocBlockModel& model, DocBlockConfig const& conf);

void apply_doc_block_actions(
    EditableOrgDocGroup&  history,
    DocBlockModel&        model,
    DocBlockConfig const& conf);

void doc_editor_loop(GLFWwindow* window, sem::SemId<sem::Org> node);
