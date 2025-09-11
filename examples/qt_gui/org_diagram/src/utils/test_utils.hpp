#pragma once

#include <haxorg/sem/SemBaseApi.hpp>
#include <src/model/HistoryManager.hpp>
#include <src/model/nodes/DiagramTreeNode.hpp>

namespace test {
struct ScopeV12 {
    org::imm::ImmAstContext::Ptr context;
    HistoryManager               manager;
    hstd::SPtr<DiaContext>       tree_context;
    ScopeV12()
        : context{org::imm::ImmAstContext::init_start_context()}
        , manager{context}
        , tree_context{DiaContext::shared()} //
    {}

    org::imm::ImmAdapter getRootV1() const { return manager.getRoot(0); }
    org::imm::ImmAdapter getRootV2() const { return manager.getRoot(1); }
};

struct ScopeV12DiagramDiff : ScopeV12 {
    DiaAdapter           srcAdapter;
    DiaAdapter           dstAdapter;
    std::vector<DiaEdit> edits;
    ScopeV12DiagramDiff(std::string const& src, std::string const& dst) {
        HSLOG_INFO("test", "src:\n", src);
        HSLOG_INFO("test", "dst:\n", dst);

        manager.addDocument(src);
        manager.addDocument(dst);
        srcAdapter = FromDocument(tree_context, getRootV1());
        dstAdapter = FromDocument(tree_context, getRootV2());
        edits      = getEdits(srcAdapter, dstAdapter, DiaEditConf{});

        HSLOG_INFO(
            "test", "srcAdapter:\n", srcAdapter.format().toString(false));

        HSLOG_INFO(
            "test", "dstAdapter:\n", dstAdapter.format().toString(false));

        log_collection("test", hstd::log::severity_level::trace, edits)
            .end();
    }
};

struct ScopeDiagramTree {
    org::imm::ImmAstContext::Ptr context;
    hstd::SPtr<DiaContext>       tree_context;

    org::imm::ImmAstVersion getAdapter(std::string const& text) {
        auto parsed = org::parseString(text);
        return context->addRoot(parsed);
    }

    ScopeDiagramTree()
        : context{org::imm::ImmAstContext::init_start_context()}
        , tree_context{DiaContext::shared()} //
    {}
};

struct DiaNodeItemParams {
    int              level    = 2;
    std::string      itemName = "item N";
    DiaNodeItem::Pos pos;
};

struct DiaNodeLayerParams {
    std::string layerName = "layer N";
};

std::string makeItemText(DiaNodeItemParams const& conf);
std::string makeLayerText(
    DiaNodeLayerParams const&           layer,
    hstd::Vec<DiaNodeItemParams> const& items);

inline DiaNodeItemParams ditem(
    std::string const&      itemName,
    DiaNodeItem::Pos const& pos = DiaNodeItem::Pos{}) {
    return DiaNodeItemParams{.itemName = itemName, .pos = pos};
}

inline DiaNodeItemParams ditem(
    int                     level,
    std::string const&      itemName,
    DiaNodeItem::Pos const& pos = DiaNodeItem::Pos{}) {
    return DiaNodeItemParams{
        .level = level, .itemName = itemName, .pos = pos};
}

} // namespace test
