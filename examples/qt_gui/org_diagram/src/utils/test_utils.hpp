#pragma once

#include <haxorg/sem/SemBaseApi.hpp>
#include <src/model/HistoryManager.hpp>
#include <src/model/nodes/DiagramTreeNode.hpp>
#include <src/model/DiaNodeTreeModel.hpp>
#include <src/gui/DiaScene.hpp>

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
    ScopeV12DiagramDiff(std::string const& src, std::string const& dst);
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

struct ScopeV12ItemModel : ScopeV12DiagramDiff {
    DiaSceneItemModel model;
    DiaScene          scene;
    ScopeV12ItemModel(std::string const& src, std::string const& dst)
        : ScopeV12DiagramDiff{src, dst}, scene{&model} {}

    void logModel() {
        HSLOG_INFO(_cat, printModelTree(&model).toString(false));
    }
};

struct ScopeV12UpdateTest : ScopeV12ItemModel {
    hstd::log::SignalDebugger signalCatcher;
    ScopeV12UpdateTest(std::string const& src, std::string const& dst)
        : ScopeV12ItemModel{src, dst}
        , signalCatcher{get_tracker(), &model} {}

    void setV1() {
        HSLOG_TRACE(_cat, "Scene root before setting the adapter");
        scene.logSceneRoot();
        scene.setRootAdapter(srcAdapter);
        HSLOG_TRACE(_cat, "Scene root after setting the adapter");
        scene.logSceneRoot();
    }
    void setV2() {
        scene.resetRootAdapter(dstAdapter, edits);
        HSLOG_TRACE(_cat, "Scene root after updating the adapter");
        scene.logSceneRoot();
    }
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

void visualizeTestDiff(QObject* obj, ScopeV12DiagramDiff const& scope);

} // namespace test
