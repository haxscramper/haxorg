#pragma once

#include <org_imgui/gui_lib/block_graph.hpp>
#include <org_imgui/gui_lib/node_grid_graph.hpp>
#include <org_imgui/gui_lib/imgui_utils.hpp>
#include <haxorg/sem/ImmOrg.hpp>
#include <org_imgui/gui_lib/im_org_ui_common.hpp>
#include <hstd/stdlib/Ptrs.hpp>

struct DocBlockConfig {
    int            editLaneWidth      = 600;
    int            nestingBlockOffset = 40;
    hstd::Vec<int> annotationLanesWidth{200};
    ImU32          annotationNodeWindowBg = IM_COL32(128, 128, 128, 128);
    int            pageUpScrollStep       = 20;
    int            pageDownScrollStep     = -20;
    int            mouseScrollMultiplier  = 10;
    ImVec2         gridViewport;

    LaneBlockGraphConfig laneConf;

    DESC_FIELDS(
        DocBlockConfig,
        (editLaneWidth,
         nestingBlockOffset,
         annotationLanesWidth,
         laneConf,
         gridViewport,
         pageUpScrollStep,
         pageDownScrollStep,
         mouseScrollMultiplier,
         annotationNodeWindowBg));
};

struct DocBlockModel;
struct DocBlockContext;

struct DocBlock : hstd::SharedPtrApi<DocBlock> {
    virtual ~DocBlock() = default;

    ImDrawList* dl() const { return ImGui::GetWindowDrawList(); }

    template <typename Other>
    hstd::SPtr<Other> ptr_as() {
        auto tmp = std::dynamic_pointer_cast<Other>(shared_from_this());
        LOGIC_ASSERTION_CHECK(tmp.get() != nullptr, "Ptr get failed");
        return tmp;
    }

    template <typename Other>
    Other* dyn_cast() {
        return dynamic_cast<Other*>(this);
    }

    template <typename Other>
    Other const* dyn_cast() const {
        return dynamic_cast<Other const*>(this);
    }

    DECL_DESCRIBED_ENUM(
        Kind,
        Annotation,
        Document,
        Export,
        Paragraph,
        Subtree,
        ListHeader,
        Fallback);

#define __kind_methods(_Kind)                                             \
    bool is##_Kind() const { return getKind() == Kind::_Kind; }

    __kind_methods(Annotation);
    __kind_methods(Document);
    __kind_methods(Export);
    __kind_methods(Paragraph);
    __kind_methods(Subtree);
    __kind_methods(ListHeader);

#undef __kind_methods

    hstd::Vec<DocBlock::Ptr> nested;
    hstd::Vec<DocBlock::Ptr> annotations;
    std::weak_ptr<DocBlock>  parent;
    bool                     isVisible = true;

    DESC_FIELDS(DocBlock, (nested, annotations, isVisible));

    ImVec2         pos;
    virtual Kind   getKind() const     = 0;
    virtual ImVec2 getSize() const     = 0;
    virtual void   setWidth(int width) = 0;
    ImVec2         getPos() const { return pos; }
    virtual void   setPos(ImVec2 const& p) { pos = p; }

    struct RenderContext {
        ImVec2 start;
        int    dfsIndex = 0;
        DESC_FIELDS(RenderContext, (start));

        int getIndex() { return dfsIndex++; }

        ImVec2 getThisWindowPos() const { return start; }
        ImVec2 getWindowPos(DocBlock* block) const {
            return block->getPos() + start;
        }

        std::string getId(std::string prefix = "") const {
            return hstd::fmt("{}_{}", prefix, dfsIndex);
        }
    };

    virtual void render(DocBlockModel& model, DocBlockConfig const& conf, RenderContext& renderContext) = 0;

    DocBlock::Ptr at(int pos) const { return nested.at(pos); }
    DocBlock::Ptr at(hstd::Vec<int> path) const {
        auto res = nested.at(path.front());
        for (int i : path.at(slice(1, hstd::BackwardsIndex(1)))) {
            res = res->at(i);
        }
        return res;
    }

    void          treeRepr(hstd::ColStream& os);
    hstd::ColText treeRepr() {
        hstd::ColStream os;
        treeRepr(os);
        return os.getBuffer();
    }

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

    hstd::Vec<DocBlock::Ptr> getFlatBlocks();
    hstd::Vec<DocBlock::Ptr> getFlatAnnotations();
};

struct DocBlockDocument : public DocBlock {
    org::imm::ImmAdapterT<org::imm::ImmDocument> origin;

    Kind   getKind() const override { return Kind::Document; }
    ImVec2 getSize() const override { return ImVec2(10, 10); }
    void   setWidth(int w) override {}

    BOOST_DESCRIBE_CLASS(DocBlockDocument, (DocBlock), (origin), (), ());

    org::imm::ImmAdapter getRootOrigin() const { return origin; }

    virtual void render(
        DocBlockModel&        model,
        const DocBlockConfig& conf,
        RenderContext&        renderContext) override;
};

struct DocBlockAnnotation : public DocBlock {
    EditableOrgTextEntry name;
    ImVec2               pos;

    ImVec2 const& getPos() const { return pos; }
    ImVec2        getSize() const override { return name.getSize(); }
    Kind          getKind() const override { return Kind::Annotation; }

    BOOST_DESCRIBE_CLASS(
        DocBlockAnnotation,
        (DocBlock),
        (name, pos),
        (),
        ());

    void setWidth(int width) override {}
    void syncSize(int thisLane, DocBlockConfig const& conf) override {}

    virtual void render(
        DocBlockModel&        model,
        const DocBlockConfig& conf,
        RenderContext&        renderContext) override;
};

struct DocBlockExport : public DocBlock {
    org::imm::ImmAdapterT<org::imm::ImmBlockExport> origin;
    ImVec2 getSize() const override { return ImVec2{100, 20}; }
    void   setWidth(int width) override {}
    Kind   getKind() const override { return Kind::Export; }
    BOOST_DESCRIBE_CLASS(DocBlockExport, (DocBlock), (origin), (), ());

    virtual void render(
        DocBlockModel&        model,
        const DocBlockConfig& conf,
        RenderContext&        renderContext) override;
};

struct DocBlockFallback : public DocBlock {
    org::imm::ImmAdapter origin;
    ImVec2 getSize() const override { return ImVec2{200, 20}; }
    void   setWidth(int width) override {}
    Kind   getKind() const override { return Kind::Fallback; }
    BOOST_DESCRIBE_CLASS(DocBlockFallback, (DocBlock), (origin), (), ());

    virtual void render(
        DocBlockModel&        model,
        const DocBlockConfig& conf,
        RenderContext&        renderContext) override;
};


struct DocBlockParagraph : public DocBlock {
    org::imm::ImmAdapterT<org::imm::ImmParagraph> origin;
    EditableOrgTextEntry                          text;
    void   setWidth(int width) override { text.setWidth(width); }
    ImVec2 getSize() const override { return text.getSize(); }
    Kind   getKind() const override { return Kind::Paragraph; }
    BOOST_DESCRIBE_CLASS(DocBlockParagraph, (), (text, origin), (), ());

    virtual void render(
        DocBlockModel&        model,
        const DocBlockConfig& conf,
        RenderContext&        renderContext) override;
};

struct DocBlockSubtree : public DocBlock {
    org::imm::ImmAdapterT<org::imm::ImmSubtree> origin;
    EditableOrgTextEntry                        title;

    void   setWidth(int width) override { title.setWidth(width); }
    ImVec2 getSize() const override { return title.getSize(); }
    Kind   getKind() const override { return Kind::Subtree; }

    BOOST_DESCRIBE_CLASS(DocBlockSubtree, (), (title, origin), (), ());

    virtual void render(
        DocBlockModel&        model,
        const DocBlockConfig& conf,
        RenderContext&        renderContext) override;
};

struct DocBlockListHeader : public DocBlock {
    org::imm::ImmAdapterT<org::imm::ImmList> origin;
    Kind   getKind() const override { return Kind::ListHeader; }
    void   setWidth(int width) override {}
    ImVec2 getSize() const override { return ImVec2{100, 20}; }
    BOOST_DESCRIBE_CLASS(DocBlockListHeader, (DocBlock), (origin), (), ());

    virtual void render(
        DocBlockModel&        model,
        const DocBlockConfig& conf,
        RenderContext&        renderContext) override;
};

template <>
struct std::formatter<DocBlock*>
    : hstd::std_format_ptr_as_hex<DocBlock> {};
template <>
struct std::formatter<DocBlock const*>
    : hstd::std_format_ptr_as_hex<DocBlock> {};

struct DocBlockAction {
    struct NodeEditChanged {
        DocBlock::Ptr block;
        DESC_FIELDS(NodeEditChanged, (block));
    };

    struct NodeTextChanged {
        DocBlock::Ptr           block;
        EditableOrgText::Result edit;
        DESC_FIELDS(NodeTextChanged, (block, edit));
    };

    struct Scroll {
        ImVec2 pos;
        float  direction;
        DESC_FIELDS(Scroll, (pos, direction));
    };

    SUB_VARIANTS(
        Kind,
        Data,
        data,
        getKind,
        NodeEditChanged,
        NodeTextChanged,
        Scroll);

    Data data;

    DESC_FIELDS(DocBlockAction, (data));
};

struct DocBlockContext : hstd::OperationsTracer {
    hstd::Vec<DocBlockAction> actions;

    void action(
        DocBlockAction::Data const& act,
        int                         line     = __builtin_LINE(),
        char const*                 function = __builtin_FUNCTION(),
        char const*                 file     = __builtin_FILE()) {
        DocBlockAction ga{act};
        message(hstd::fmt("Action {}", ga), line, function, file);
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

    LaneBlockGraph           g;
    LaneBlockLayout          lyt;
    hstd::Vec<DocBlock::Ptr> flatGrid;

    DESC_FIELDS(DocBlockModel, (root, ctx, g));

    void syncFull(
        org::imm::ImmAdapter const& root,
        DocBlockConfig const&       conf) {
        syncRoot(root, conf);
        syncBlockGraph(conf);
        syncLayout(conf);
    }

    void syncRoot(
        org::imm::ImmAdapter const& root,
        DocBlockConfig const&       conf);
    void syncBlockGraph(DocBlockConfig const& conf);
    void syncLayout(DocBlockConfig const& conf);

    int getLaneScroll(int lane) {
        return g.getExistingLane(lane).scrollOffset;
    }
};

hstd::Opt<DocBlock::Ptr> to_doc_block(
    org::imm::ImmAdapter const& it,
    DocBlockConfig const&       conf,
    DocBlockContext&            ctx);
void render_doc_block(DocBlockModel& model, DocBlockConfig const& conf);

void apply_doc_block_actions(
    EditableOrgDocGroup&  history,
    DocBlockModel&        model,
    DocBlockConfig const& conf);

void doc_editor_loop(
    GLFWwindow*                    window,
    org::sem::SemId<org::sem::Org> node);
