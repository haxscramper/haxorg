#pragma once

#include <haxorg/sem/SemBaseApi.hpp>
#include <src/model/DiaVersionStore.hpp>
#include <src/model/nodes/DiagramTreeNode.hpp>
#include <src/model/DiaNodeTreeModel.hpp>
#include <src/gui/DiaScene.hpp>

namespace test {
struct ScopeManaged {
    org::imm::ImmAstContext::Ptr imm_context;
    DiaContext::Ptr              dia_context;
    DiaVersionStore::Ptr         version_store;
    ScopeManaged()
        : imm_context{org::imm::ImmAstContext::init_start_context()}
        , dia_context{DiaContext::shared()}
        , version_store{DiaVersionStore::shared(imm_context, dia_context)}
    //
    {}
};

struct ScopeV12 : public ScopeManaged {
    org::imm::ImmAdapter getRootV1() const {
        return version_store->getImmRoot(0);
    }
    org::imm::ImmAdapter getRootV2() const {
        return version_store->getImmRoot(1);
    }
};


struct ScopeV12DiagramDiff : ScopeV12 {
    DiaAdapter         srcAdapter;
    DiaAdapter         dstAdapter;
    hstd::Vec<DiaEdit> edits;
    ScopeV12DiagramDiff(std::string const& src, std::string const& dst);
};

struct ScopeDiagramTree {
    org::imm::ImmAstContext::Ptr imm_context;
    hstd::SPtr<DiaContext>       dia_context;

    org::imm::ImmAstVersion getAdapter(std::string const& text) {
        auto parsed = org::parseString(text);
        return imm_context->addRoot(parsed);
    }

    ScopeDiagramTree()
        : imm_context{org::imm::ImmAstContext::init_start_context()}
        , dia_context{DiaContext::shared()} //
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
        : ScopeV12DiagramDiff{src, dst}, scene{&model, version_store} {}

    void logModel() {
        HSLOG_INFO(_cat, printModelTree(&model).toString(false));
    }
};

struct ScopeV12UpdateTest : ScopeV12ItemModel {
    hstd::log::SignalDebugger signalCatcher;
    ScopeV12UpdateTest(std::string const& src, std::string const& dst)
        : ScopeV12ItemModel{src, dst}
        , signalCatcher{get_tracker(), &model} {}

    QModelIndex indexAt(hstd::Vec<int> const& path) {
        return model.indexAtPath(path).value();
    }

    DiaSceneItem* itemViaIndexAt(hstd::Vec<int> const& path) {
        return static_cast<DiaSceneItem*>(indexAt(path).internalPointer());
    }

    void setV1() {
        HSLOG_TRACE(_cat, "Scene root before setting the adapter");
        scene.logSceneRoot();
        scene.setRootAdapter(srcAdapter);
        HSLOG_TRACE(_cat, "Scene root after setting the adapter");
        scene.logSceneRoot();
        HSLOG_TRACE(_cat, "Tree model after setting the adapter");
        HSLOG_TRACE(_cat, model.format().toString(false));
    }

    void setV2() {
        scene.resetRootAdapter(edits);
        HSLOG_TRACE(_cat, "Scene root after updating the adapter");
        scene.logSceneRoot();
        HSLOG_TRACE(_cat, "Tree model after updating the adapter");
        HSLOG_TRACE(_cat, model.format().toString(false));
    }
};

struct ScopeDiaContextEdits : public ScopeManaged {
    DiaSceneItemModel model;
    DiaScene          scene;
    ScopeDiaContextEdits() : scene{&model, version_store} {
        QObject::connect(
            version_store.get(),
            &DiaVersionStore::diaRootChanged,
            &scene,
            &DiaScene::diaRootChanged);
    }

    DiaAdapter getRoot() {
        return this->version_store->getActiveDiaRoot();
    }

    struct TextSetResult {
        DiaAdapter           dia;
        org::imm::ImmAdapter imm;
        int                  rootIndex;
    };

    TextSetResult setText(std::string const& text);
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
