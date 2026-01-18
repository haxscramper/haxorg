#include <QTest>
#include <haxorg/api/SemBaseApi.hpp>
#include <org_diagram/src/model/DiaVersionStore.hpp>
#include <org_diagram/src/utils/common.hpp>
#include <org_diagram/src/utils/test_utils.hpp>
#include <org_diagram/src/model/nodes/DiagramTreeNode.hpp>
#include <hstd/stdlib/VariantFormatter.hpp>

#include <haxorg/sem/perfetto_org.hpp>
#include <hstd/ext/perfetto_aux_impl_template.hpp>

#pragma clang diagnostic ignored "-Wmacro-redefined"
#define _cat "test.history"

using namespace test;

class DiaContextStoreTreeSwitchingTest : public QObject {
    Q_OBJECT


    hstd::Vec<DiaNodeItemParams> simplePrefix5_level2 = hstd::Vec{
        ditem("prefix 1"),
        ditem("prefix 2"),
        ditem("prefix 3"),
        ditem("prefix 4"),
        ditem("prefix 5"),
    };

    hstd::Vec<DiaNodeItemParams> simpleSuffix5_level2 = hstd::Vec{
        ditem("suffix 1"),
        ditem("suffix 2"),
        ditem("suffix 3"),
        ditem("suffix 4"),
        ditem("suffix 5"),
    };

    void verifyTransition(ScopeV12DiagramDiff const& diff) {
        visualizeTestDiff(this, diff);

        DiaSceneItemModel srcModel;
        DiaScene          srcScene{&srcModel, diff.version_store};
        srcScene.setRootAdapter(diff.srcAdapter);
        srcScene.resetRootAdapter(diff.edits);
        DiaSceneItemModel dstModel;
        DiaScene          dstScene{&dstModel, diff.version_store};
        dstScene.setRootAdapter(diff.dstAdapter);

        auto compare = test::compareModels<std::string, DiaSceneItemModel>(
            &srcModel,
            &dstModel,
            [](QModelIndex const&       index,
               DiaSceneItemModel const* model) -> std::string {
                return model->getNode(index)->name.toStdString();
            });

        if (!compare.empty()) {
            std::string message;
            message = "model switch failed";
            for (auto const& it : compare) {
                message += hstd::fmt("\n{}", it.description);
            }


            HSLOG_ERROR("{}", message);
            HSLOG_ERROR(
                "src model:\n{}", srcModel.format().toString(false));
            HSLOG_ERROR(
                "dst model:\n{}", dstModel.format().toString(false));

            QFAIL(message.c_str());
        }
    }

  private slots:
    void testFromRegularText() {
        DiaVersionStore manager{
            org::imm::ImmAstContext::init_start_context(),
            DiaContext::shared()};
        manager.addDocument("*bold*");
        manager.addDocument("/italic/");
    }

    void testGetSimpleDifference() {
        DiaVersionStore manager{
            org::imm::ImmAstContext::init_start_context(),
            DiaContext::shared()};
        manager.addDocument("word");
        manager.addDocument("word second");
    }

    void testTreeEdits() {
        auto     __scope = trackTestExecution(this);
        ScopeV12 scope;
        scope.version_store->addDocument(R"(
* layer 1
** item 1
    :properties:
    :prop_json:haxorg_diagram_position: {"x": 12, "y": 90}
    :prop_args:haxorg_diagram_node: :some-value t
    :end:
)");
        scope.version_store->addDocument(R"(
* layer 1
** item 1
    :properties:
    :prop_json:haxorg_diagram_position: {"x": 142, "y": 900}
    :prop_args:haxorg_diagram_node: :some-value t
    :end:
)");
        auto treeV1 = FromDocument(scope.dia_context, scope.getRootV1());

        HSLOG_INFO(
            "treeV1 adapter repr\n{}", scope.getRootV1().treeReprString());

        HSLOG_INFO(
            "treeV2 adapter repr\n{}", scope.getRootV2().treeReprString());

        HSLOG_INFO(
            "treeV1 before edit\n{}", treeV1.format().toString(false));
    }

    void testDepletedEdits() {
        auto                __scope = trackTestExecution(this);
        ScopeV12DiagramDiff scope{
            R"(
* layer
)",
            R"(
* layer
)"};
        QCOMPARE_EQ(scope.edits.size(), 0);
        hstd::log::log_sequential_collection(scope.edits).as_trace().end();
    }

    void testLeafChange() {
        auto                __scope = trackTestExecution(this);
        ScopeV12DiagramDiff scope{
            R"(
* layer
** item 1
    :properties:
    :prop_json:haxorg_diagram_position: {"x": 12, "y": 90}
    :prop_args:haxorg_diagram_node: :some-value t
    :end:
)",
            R"(
* layer
** item 1
    :properties:
    :prop_json:haxorg_diagram_position: {"x": 142, "y": 900}
    :prop_args:haxorg_diagram_node: :some-value t
    :end:
)"};
        QCOMPARE_EQ(scope.edits.size(), 3);
    }

    void testInsertDuplicateSubnode() {
        auto                __scope = trackTestExecution(this);
        ScopeV12DiagramDiff scope{
            R"(
* layer
** item 1
    :properties:
    :prop_json:haxorg_diagram_position: {"x": 12, "y": 90}
    :prop_args:haxorg_diagram_node: :some-value t
    :end:
** item 2
    :properties:
    :prop_json:haxorg_diagram_position: {"x": 44, "y": 900}
    :prop_args:haxorg_diagram_node: :some-value nil
    :end:
)",
            R"(
* layer
** item 1
    :properties:
    :prop_json:haxorg_diagram_position: {"x": 12, "y": 90}
    :prop_args:haxorg_diagram_node: :some-value t
    :end:
** item 2
    :properties:
    :prop_json:haxorg_diagram_position: {"x": 44, "y": 900}
    :prop_args:haxorg_diagram_node: :some-value nil
    :end:
** item 1
    :properties:
    :prop_json:haxorg_diagram_position: {"x": 12, "y": 90}
    :prop_args:haxorg_diagram_node: :some-value t
    :end:
)"};

        verifyTransition(scope);
    }

    void testSubnodeMove() {
        auto                __scope = trackTestExecution(this);
        ScopeV12DiagramDiff scope{
            R"(
* layer
** item 1
    :properties:
    :prop_json:haxorg_diagram_position: {"x": 12, "y": 90}
    :prop_args:haxorg_diagram_node: :some-value t
    :end:
** item 2
    :properties:
    :prop_json:haxorg_diagram_position: {"x": 44, "y": 900}
    :prop_args:haxorg_diagram_node: :some-value nil
    :end:
)",
            R"(
* layer
** item 2
    :properties:
    :prop_json:haxorg_diagram_position: {"x": 44, "y": 900}
    :prop_args:haxorg_diagram_node: :some-value nil
    :end:
** item 1
    :properties:
    :prop_json:haxorg_diagram_position: {"x": 12, "y": 90}
    :prop_args:haxorg_diagram_node: :some-value t
    :end:
)"};

        verifyTransition(scope);
    }


    void testSubnodeMoveWithManyAdjacent() {
        auto __scope = trackTestExecution(this);

        ScopeV12DiagramDiff scope{
            makeLayerText(
                DiaNodeLayerParams{},
                simplePrefix5_level2
                    + hstd::Vec{ditem("item 1"), ditem("item 2")}
                    + simpleSuffix5_level2),
            makeLayerText(
                DiaNodeLayerParams{},
                simplePrefix5_level2
                    + hstd::Vec{ditem("item 2"), ditem("item 1")}
                    + simpleSuffix5_level2),
        };

        verifyTransition(scope);
    }

    void testSubnodeUpdateInPlace() {
        auto __scope = trackTestExecution(this);

        ScopeV12DiagramDiff scope{
            makeLayerText(
                DiaNodeLayerParams{},
                simplePrefix5_level2 + hstd::Vec{ditem("item 1", {10, 10})}
                    + simpleSuffix5_level2),
            makeLayerText(
                DiaNodeLayerParams{},
                simplePrefix5_level2 + hstd::Vec{ditem("item 1", {10, 20})}
                    + simpleSuffix5_level2),
        };

        verifyTransition(scope);
    }

    void testSubnodeUpdateDeepNode() {
        auto                __scope = trackTestExecution(this);
        ScopeV12DiagramDiff scope{
            makeLayerText(
                DiaNodeLayerParams{},
                hstd::Vec{
                    ditem(2, "item 1"),
                    ditem(3, "item 2"),
                    ditem(4, "item 3"),
                    ditem(5, "item 4"),
                    ditem(6, "item 5", {10, 10})}),
            makeLayerText(
                DiaNodeLayerParams{},
                hstd::Vec{
                    ditem(2, "item 1"),
                    ditem(3, "item 2"),
                    ditem(4, "item 3"),
                    ditem(5, "item 4"),
                    ditem(6, "item 5", {10, 20})}),
        };

        verifyTransition(scope);
    }

    void testSubnodeSwapDeepNode() {
        auto                __scope = trackTestExecution(this);
        ScopeV12DiagramDiff scope{
            makeLayerText(
                DiaNodeLayerParams{},
                hstd::Vec{
                    ditem(2, "item 1"),
                    ditem(3, "item 2"),
                    ditem(4, "item 3"),
                    ditem(5, "item 4"),
                    ditem(6, "item 5", {10, 10})}),
            makeLayerText(
                DiaNodeLayerParams{},
                hstd::Vec{
                    ditem(2, "item 1"),
                    ditem(3, "item 2"),
                    ditem(4, "item 3"),
                    ditem(5, "item 4"),
                    ditem(6, "item 5", {10, 20})}),
        };

        verifyTransition(scope);
    }

    void testSubnodeMoveToOtherSubtree() {
        auto                __scope = trackTestExecution(this);
        ScopeV12DiagramDiff scope{
            makeLayerText(
                DiaNodeLayerParams{},
                hstd::Vec{
                    ditem(2, "item 1"),
                    ditem(2, "item 2"),
                    ditem(3, "item 2-1"),
                    ditem(3, "item 2-2"),
                }),
            makeLayerText(
                DiaNodeLayerParams{},
                hstd::Vec{
                    ditem(2, "item 1"),
                    ditem(3, "item 2-1"),
                    ditem(3, "item 2-2"),
                    ditem(2, "item 2"),
                }),
        };

        verifyTransition(scope);
    }

    void testWideTreeMultipleEdits() {
        auto                __scope = trackTestExecution(this);
        ScopeV12DiagramDiff scope{
            makeLayerText(
                DiaNodeLayerParams{},
                hstd::Vec{
                    ditem("item A", {10, 10}),
                    ditem("item B", {20, 10}),
                    ditem("item C", {30, 10}),
                    ditem("item D", {40, 10}),
                    ditem("item E", {50, 10})}),
            makeLayerText(
                DiaNodeLayerParams{},
                hstd::Vec{
                    ditem("item A", {15, 15}),
                    ditem("item D", {20, 10}),
                    ditem("item C", {30, 10}),
                    ditem("item B", {40, 10}),
                    ditem("item F", {60, 10})}),
        };

        verifyTransition(scope);
    }

    void testSwapFollowedByInsert_TwoItems() {
        auto                __scope = trackTestExecution(this);
        ScopeV12DiagramDiff scope{
            makeLayerText(
                DiaNodeLayerParams{},
                hstd::Vec{
                    ditem("item A", {10, 10}), ditem("item B", {20, 10})}),
            makeLayerText(
                DiaNodeLayerParams{},
                hstd::Vec{
                    ditem("item B", {20, 10}),
                    ditem("item A", {10, 10}),
                    ditem("item C", {30, 10})}),
        };

        verifyTransition(scope);
    }

    void testSwapFollowedByInsert_WithPrefix() {
        auto                __scope = trackTestExecution(this);
        ScopeV12DiagramDiff scope{
            makeLayerText(
                DiaNodeLayerParams{},
                hstd::Vec{
                    ditem("item X", {5, 10}),
                    ditem("item Y", {7, 10}),
                    ditem("item A", {10, 10}),
                    ditem("item B", {20, 10})}),
            makeLayerText(
                DiaNodeLayerParams{},
                hstd::Vec{
                    ditem("item X", {5, 10}),
                    ditem("item Y", {7, 10}),
                    ditem("item B", {20, 10}),
                    ditem("item A", {10, 10}),
                    ditem("item C", {30, 10})}),
        };

        verifyTransition(scope);
    }

    void testSwapFollowedByInsert_WithPrefixAndSuffix() {
        auto                __scope = trackTestExecution(this);
        ScopeV12DiagramDiff scope{
            makeLayerText(
                DiaNodeLayerParams{},
                hstd::Vec{
                    ditem("item X", {5, 10}),
                    ditem("item Y", {7, 10}),
                    ditem("item A", {10, 10}),
                    ditem("item B", {20, 10}),
                    ditem("item Z", {50, 10}),
                    ditem("item W", {60, 10})}),
            makeLayerText(
                DiaNodeLayerParams{},
                hstd::Vec{
                    ditem("item X", {5, 10}),
                    ditem("item Y", {7, 10}),
                    ditem("item B", {20, 10}),
                    ditem("item A", {10, 10}),
                    ditem("item C", {30, 10}),
                    ditem("item Z", {50, 10}),
                    ditem("item W", {60, 10})}),
        };

        verifyTransition(scope);
    }

    void testWideNodeAllLeavesChanged() {
        auto                __scope = trackTestExecution(this);
        ScopeV12DiagramDiff scope{
            makeLayerText(
                DiaNodeLayerParams{},
                hstd::Vec{
                    ditem("root"),
                    ditem(3, "leaf A", {10, 10}),
                    ditem(3, "leaf B", {20, 10}),
                    ditem(3, "leaf C", {30, 10}),
                    ditem(3, "leaf D", {40, 10}),
                    ditem(3, "leaf E", {50, 10}),
                    ditem(3, "leaf F", {60, 10}),
                    ditem(3, "leaf G", {70, 10}),
                    ditem(3, "leaf H", {80, 10})}),
            makeLayerText(
                DiaNodeLayerParams{},
                hstd::Vec{
                    ditem("root"),
                    ditem(3, "leaf A", {15, 15}),
                    ditem(3, "leaf B", {25, 15}),
                    ditem(3, "leaf C", {35, 15}),
                    ditem(3, "leaf D", {45, 15}),
                    ditem(3, "leaf E", {55, 15}),
                    ditem(3, "leaf F", {65, 15}),
                    ditem(3, "leaf G", {75, 15}),
                    ditem(3, "leaf H", {85, 15})}),
        };

        verifyTransition(scope);
    }

    void testWideNodeSubnodesChanged() {
        auto                __scope = trackTestExecution(this);
        ScopeV12DiagramDiff scope{
            makeLayerText(
                DiaNodeLayerParams{},
                hstd::Vec{
                    ditem("root"),
                    ditem(3, "a", {10, 10}),
                    ditem(4, "a1", {11, 11}),
                    ditem(4, "a2", {12, 12}),
                    ditem(4, "a3", {13, 13}),
                    ditem(3, "b", {20, 10}),
                    ditem(4, "b1", {21, 11}),
                    ditem(4, "b2", {22, 12}),
                    ditem(4, "b3", {23, 13}),
                    ditem(3, "c", {30, 10}),
                    ditem(4, "c1", {31, 11}),
                    ditem(4, "c2", {32, 12}),
                    ditem(4, "c3", {33, 13})}),
            makeLayerText(
                DiaNodeLayerParams{},
                hstd::Vec{
                    ditem("root"),
                    ditem(3, "a-dash", {15, 15}),
                    ditem(4, "a1", {11, 11}),
                    ditem(4, "a2", {12, 12}),
                    ditem(4, "a3", {13, 13}),
                    ditem(3, "b-dash", {25, 15}),
                    ditem(4, "b1", {21, 11}),
                    ditem(4, "b2", {22, 12}),
                    ditem(4, "b3", {23, 13}),
                    ditem(3, "c-dash", {35, 15}),
                    ditem(4, "c1", {31, 11}),
                    ditem(4, "c2", {32, 12}),
                    ditem(4, "c3", {33, 13})}),
        };


        verifyTransition(scope);
    }

    void testMultiWideTreeLeafMovesInserts_UniqueLeaves() {
        auto                __scope = trackTestExecution(this);
        ScopeV12DiagramDiff scope{
            makeLayerText(
                DiaNodeLayerParams{},
                hstd::Vec{
                    ditem("root"),
                    ditem(3, "group A", {10, 10}),
                    ditem(4, "leaf A1", {11, 11}),
                    ditem(4, "leaf A2", {12, 12}),
                    ditem(4, "leaf A3", {13, 13}),
                    ditem(3, "group B", {20, 10}),
                    ditem(4, "leaf B1", {21, 11}),
                    ditem(4, "leaf B2", {22, 12}),
                    ditem(3, "group C", {30, 10}),
                    ditem(4, "leaf C1", {31, 11}),
                    ditem(4, "leaf C2", {32, 12}),
                    ditem(4, "leaf C3", {33, 13})}),
            makeLayerText(
                DiaNodeLayerParams{},
                hstd::Vec{
                    ditem("root"),
                    ditem(3, "group pre-A", {10, 10}),
                    ditem(3, "group A", {10, 10}),
                    ditem(4, "leaf A1", {11, 11}),
                    ditem(4, "leaf B1", {21, 11}),
                    ditem(3, "group B", {20, 10}),
                    ditem(4, "leaf A2", {12, 12}),
                    ditem(4, "leaf C1", {31, 11}),
                    ditem(3, "group C", {30, 10}),
                    ditem(4, "leaf A3", {13, 13}),
                    ditem(4, "leaf B2", {22, 12}),
                    ditem(4, "leaf C2", {32, 12})}),
        };

        verifyTransition(scope);
    }

    void testMultiWideTreeLeafMoves_UniqueLeaves() {
        auto                __scope = trackTestExecution(this);
        ScopeV12DiagramDiff scope{
            makeLayerText(
                DiaNodeLayerParams{},
                hstd::Vec{
                    ditem("root"),
                    ditem(3, "group A", {10, 10}),
                    ditem(4, "leaf A1", {11, 11}),
                    ditem(4, "leaf A2", {12, 12}),
                    ditem(4, "leaf A3", {13, 13}),
                    ditem(3, "group B", {20, 10}),
                    ditem(4, "leaf B1", {21, 11}),
                    ditem(4, "leaf B2", {22, 12}),
                    ditem(3, "group C", {30, 10}),
                    ditem(4, "leaf C1", {31, 11}),
                    ditem(4, "leaf C2", {32, 12}),
                    ditem(4, "leaf C3", {33, 13})}),
            makeLayerText(
                DiaNodeLayerParams{},
                hstd::Vec{
                    ditem("root"),
                    ditem(3, "group A", {10, 10}),
                    ditem(4, "leaf A1", {11, 11}),
                    ditem(4, "leaf B1", {21, 11}),
                    ditem(3, "group B", {20, 10}),
                    ditem(4, "leaf A2", {12, 12}),
                    ditem(4, "leaf C1", {31, 11}),
                    ditem(3, "group C", {30, 10}),
                    ditem(4, "leaf A3", {13, 13}),
                    ditem(4, "leaf B2", {22, 12}),
                    ditem(4, "leaf C2", {32, 12})}),
        };

        verifyTransition(scope);
    }

    void testMultiWideTreeLeafMoves_DuplicateLeaves() {
        auto                __scope = trackTestExecution(this);
        ScopeV12DiagramDiff scope{
            makeLayerText(
                DiaNodeLayerParams{},
                hstd::Vec{
                    ditem("root"),
                    ditem(3, "group A", {10, 10}),
                    ditem(4, "common leaf", {11, 11}),
                    ditem(4, "leaf A2", {12, 12}),
                    ditem(4, "shared item", {13, 13}),
                    ditem(3, "group B", {20, 10}),
                    ditem(4, "common leaf", {21, 11}),
                    ditem(4, "leaf B2", {22, 12}),
                    ditem(3, "group C", {30, 10}),
                    ditem(4, "shared item", {31, 11}),
                    ditem(4, "leaf C2", {32, 12})}),
            makeLayerText(
                DiaNodeLayerParams{},
                hstd::Vec{
                    ditem("root"),
                    ditem(3, "group A", {10, 10}),
                    ditem(4, "shared item", {13, 13}),
                    ditem(4, "common leaf", {21, 11}),
                    ditem(3, "group B", {20, 10}),
                    ditem(4, "leaf A2", {12, 12}),
                    ditem(4, "common leaf", {11, 11}),
                    ditem(3, "group C", {30, 10}),
                    ditem(4, "leaf B2", {22, 12}),
                    ditem(4, "shared item", {31, 11})}),
        };

        verifyTransition(scope);
    }

    void testMultiWideTreeLeafDeleteInsert_UniqueLeaves() {
        auto                __scope = trackTestExecution(this);
        ScopeV12DiagramDiff scope{
            makeLayerText(
                DiaNodeLayerParams{},
                hstd::Vec{
                    ditem("root"),
                    ditem(3, "group A", {10, 10}),
                    ditem(4, "leaf A1", {11, 11}),
                    ditem(4, "leaf A2", {12, 12}),
                    ditem(4, "leaf A3", {13, 13}),
                    ditem(3, "group B", {20, 10}),
                    ditem(4, "leaf B1", {21, 11}),
                    ditem(4, "leaf B2", {22, 12}),
                    ditem(3, "group C", {30, 10}),
                    ditem(4, "leaf C1", {31, 11})}),
            makeLayerText(
                DiaNodeLayerParams{},
                hstd::Vec{
                    ditem("root"),
                    ditem(3, "group A", {10, 10}),
                    ditem(4, "leaf A1", {11, 11}),
                    ditem(4, "new leaf A4", {14, 14}),
                    ditem(3, "group B", {20, 10}),
                    ditem(4, "leaf B2", {22, 12}),
                    ditem(4, "new leaf B3", {23, 13}),
                    ditem(3, "group C", {30, 10}),
                    ditem(4, "new leaf C2", {32, 12}),
                    ditem(4, "new leaf C3", {33, 13})}),
        };

        verifyTransition(scope);
    }

    void testMultiWideTreeLeafDeleteInsert_DuplicateLeaves() {
        auto                __scope = trackTestExecution(this);
        ScopeV12DiagramDiff scope{
            makeLayerText(
                DiaNodeLayerParams{},
                hstd::Vec{
                    ditem("root"),
                    ditem(3, "group A", {10, 10}),
                    ditem(4, "common leaf", {11, 11}),
                    ditem(4, "leaf A2", {12, 12}),
                    ditem(4, "shared item", {13, 13}),
                    ditem(3, "group B", {20, 10}),
                    ditem(4, "common leaf", {21, 11}),
                    ditem(4, "leaf B2", {22, 12}),
                    ditem(3, "group C", {30, 10}),
                    ditem(4, "shared item", {31, 11})}),
            makeLayerText(
                DiaNodeLayerParams{},
                hstd::Vec{
                    ditem("root"),
                    ditem(3, "group A", {10, 10}),
                    ditem(4, "common leaf", {11, 11}),
                    ditem(4, "new shared", {14, 14}),
                    ditem(3, "group B", {20, 10}),
                    ditem(4, "leaf B2", {22, 12}),
                    ditem(4, "new shared", {23, 13}),
                    ditem(3, "group C", {30, 10}),
                    ditem(4, "common leaf", {32, 12}),
                    ditem(4, "shared item", {31, 11})}),
        };

        verifyTransition(scope);
    }

    void testMultiWideTreeComplexEdits_UniqueLeaves() {
        auto                __scope = trackTestExecution(this);
        ScopeV12DiagramDiff scope{
            makeLayerText(
                DiaNodeLayerParams{},
                hstd::Vec{
                    ditem("root"),
                    ditem(3, "group A", {10, 10}),
                    ditem(4, "leaf A1", {11, 11}),
                    ditem(4, "leaf A2", {12, 12}),
                    ditem(4, "leaf A3", {13, 13}),
                    ditem(3, "group B", {20, 10}),
                    ditem(4, "leaf B1", {21, 11}),
                    ditem(4, "leaf B2", {22, 12}),
                    ditem(4, "leaf B3", {23, 13}),
                    ditem(3, "group C", {30, 10}),
                    ditem(4, "leaf C1", {31, 11}),
                    ditem(4, "leaf C2", {32, 12})}),
            makeLayerText(
                DiaNodeLayerParams{},
                hstd::Vec{
                    ditem("root"),
                    ditem(3, "group A", {10, 10}),
                    ditem(4, "leaf B1", {21, 11}),
                    ditem(4, "new leaf A4", {14, 14}),
                    ditem(3, "group B", {20, 10}),
                    ditem(4, "leaf A2", {12, 12}),
                    ditem(4, "leaf C1", {31, 11}),
                    ditem(4, "new leaf B4", {24, 14}),
                    ditem(3, "group C", {30, 10}),
                    ditem(4, "leaf A3", {13, 13}),
                    ditem(4, "new leaf C3", {33, 13})}),
        };

        verifyTransition(scope);
    }

    void testMultiWideTreeComplexEdits_DuplicateLeaves() {
        auto                __scope = trackTestExecution(this);
        ScopeV12DiagramDiff scope{
            makeLayerText(
                DiaNodeLayerParams{},
                hstd::Vec{
                    ditem("root"),
                    ditem(3, "group A", {10, 10}),
                    ditem(4, "common leaf", {11, 11}),
                    ditem(4, "leaf A2", {12, 12}),
                    ditem(4, "shared item", {13, 13}),
                    ditem(3, "group B", {20, 10}),
                    ditem(4, "common leaf", {21, 11}),
                    ditem(4, "leaf B2", {22, 12}),
                    ditem(4, "shared item", {23, 13}),
                    ditem(3, "group C", {30, 10}),
                    ditem(4, "leaf C1", {31, 11}),
                    ditem(4, "common leaf", {32, 12})}),
            makeLayerText(
                DiaNodeLayerParams{},
                hstd::Vec{
                    ditem("root"),
                    ditem(3, "group A", {10, 10}),
                    ditem(4, "leaf B2", {22, 12}),
                    ditem(4, "new common", {14, 14}),
                    ditem(3, "group B", {20, 10}),
                    ditem(4, "shared item", {13, 13}),
                    ditem(4, "common leaf", {32, 12}),
                    ditem(4, "new common", {24, 14}),
                    ditem(3, "group C", {30, 10}),
                    ditem(4, "leaf A2", {12, 12}),
                    ditem(4, "common leaf", {11, 11})}),
        };

        verifyTransition(scope);
    }

    void testDeleteLevel3NodeWithLeaves() {
        auto                __scope = trackTestExecution(this);
        ScopeV12DiagramDiff scope{
            makeLayerText(
                DiaNodeLayerParams{},
                hstd::Vec{
                    ditem("group A", {10, 10}),
                    ditem(3, "subgroup A1", {11, 11}),
                    ditem(4, "leaf A1-1", {12, 12}),
                    ditem(4, "leaf A1-2", {13, 13}),
                    ditem(3, "subgroup A2", {14, 14}),
                    ditem(4, "leaf A2-1", {15, 15}),
                    ditem(4, "leaf A2-2", {16, 16}),
                    ditem("group B", {20, 10}),
                    ditem(3, "subgroup B1", {21, 11}),
                    ditem(4, "leaf B1-1", {22, 12})}),
            makeLayerText(
                DiaNodeLayerParams{},
                hstd::Vec{
                    ditem("group A", {10, 10}),
                    ditem(3, "subgroup A1", {11, 11}),
                    ditem(4, "leaf A1-1", {12, 12}),
                    ditem(4, "leaf A1-2", {13, 13}),
                    ditem("group B", {20, 10}),
                    ditem(3, "subgroup B1", {21, 11}),
                    ditem(4, "leaf B1-1", {22, 12})}),
        };

        verifyTransition(scope);
    }

    void testDeleteLevel2NodeWithSubtree() {
        auto                __scope = trackTestExecution(this);
        ScopeV12DiagramDiff scope{
            makeLayerText(
                DiaNodeLayerParams{},
                hstd::Vec{
                    ditem("group A", {10, 10}),
                    ditem(3, "subgroup A1", {11, 11}),
                    ditem(4, "leaf A1-1", {12, 12}),
                    ditem(4, "leaf A1-2", {13, 13}),
                    ditem(3, "subgroup A2", {14, 14}),
                    ditem(4, "leaf A2-1", {15, 15}),
                    ditem("group B", {20, 10}),
                    ditem(3, "subgroup B1", {21, 11}),
                    ditem(4, "leaf B1-1", {22, 12}),
                    ditem(4, "leaf B1-2", {23, 13}),
                    ditem(3, "subgroup B2", {24, 14}),
                    ditem(4, "leaf B2-1", {25, 15}),
                    ditem("group C", {30, 10})}),
            makeLayerText(
                DiaNodeLayerParams{},
                hstd::Vec{
                    ditem("group A", {10, 10}),
                    ditem(3, "subgroup A1", {11, 11}),
                    ditem(4, "leaf A1-1", {12, 12}),
                    ditem(4, "leaf A1-2", {13, 13}),
                    ditem(3, "subgroup A2", {14, 14}),
                    ditem(4, "leaf A2-1", {15, 15}),
                    ditem("group C", {30, 10})}),
        };

        verifyTransition(scope);
    }

    void testInsertLevel3NodeWithLeaves() {
        auto                __scope = trackTestExecution(this);
        ScopeV12DiagramDiff scope{
            makeLayerText(
                DiaNodeLayerParams{},
                hstd::Vec{
                    ditem("group A", {10, 10}),
                    ditem(3, "subgroup A1", {11, 11}),
                    ditem(4, "leaf A1-1", {12, 12}),
                    ditem(4, "leaf A1-2", {13, 13}),
                    ditem("group B", {20, 10}),
                    ditem(3, "subgroup B1", {21, 11}),
                    ditem(4, "leaf B1-1", {22, 12})}),
            makeLayerText(
                DiaNodeLayerParams{},
                hstd::Vec{
                    ditem("group A", {10, 10}),
                    ditem(3, "subgroup A1", {11, 11}),
                    ditem(4, "leaf A1-1", {12, 12}),
                    ditem(4, "leaf A1-2", {13, 13}),
                    ditem(3, "subgroup A2", {14, 14}),
                    ditem(4, "leaf A2-1", {15, 15}),
                    ditem(4, "leaf A2-2", {16, 16}),
                    ditem("group B", {20, 10}),
                    ditem(3, "subgroup B1", {21, 11}),
                    ditem(4, "leaf B1-1", {22, 12})}),
        };


        verifyTransition(scope);
    }

    void testInsertLevel2NodeWithSubtree() {
        auto                __scope = trackTestExecution(this);
        ScopeV12DiagramDiff scope{
            makeLayerText(
                DiaNodeLayerParams{},
                hstd::Vec{
                    ditem("group A", {10, 10}),
                    ditem(3, "subgroup A1", {11, 11}),
                    ditem(4, "leaf A1-1", {12, 12}),
                    ditem(4, "leaf A1-2", {13, 13}),
                    ditem(3, "subgroup A2", {14, 14}),
                    ditem(4, "leaf A2-1", {15, 15}),
                    ditem("group C", {30, 10})}),
            makeLayerText(
                DiaNodeLayerParams{},
                hstd::Vec{
                    ditem("group A", {10, 10}),
                    ditem(3, "subgroup A1", {11, 11}),
                    ditem(4, "leaf A1-1", {12, 12}),
                    ditem(4, "leaf A1-2", {13, 13}),
                    ditem(3, "subgroup A2", {14, 14}),
                    ditem(4, "leaf A2-1", {15, 15}),
                    ditem("group B", {20, 10}),
                    ditem(3, "subgroup B1", {21, 11}),
                    ditem(4, "leaf B1-1", {22, 12}),
                    ditem(4, "leaf B1-2", {23, 13}),
                    ditem(3, "subgroup B2", {24, 14}),
                    ditem(4, "leaf B2-1", {25, 15}),
                    ditem("group C", {30, 10})}),
        };


        verifyTransition(scope);
    }

    void testSwapLevel2ItemsWithLevel3Leaves() {
        auto                __scope = trackTestExecution(this);
        ScopeV12DiagramDiff scope{
            makeLayerText(
                DiaNodeLayerParams{},
                hstd::Vec{
                    ditem("group A", {10, 10}),
                    ditem(3, "leaf A1", {11, 11}),
                    ditem(3, "leaf A2", {12, 12}),
                    ditem(3, "leaf A3", {13, 13}),
                    ditem("group B", {20, 10}),
                    ditem(3, "leaf B1", {21, 11}),
                    ditem(3, "leaf B2", {22, 12}),
                    ditem("group C", {30, 10}),
                    ditem(3, "leaf C1", {31, 11})}),
            makeLayerText(
                DiaNodeLayerParams{},
                hstd::Vec{
                    ditem("group B", {20, 10}),
                    ditem(3, "leaf B1", {21, 11}),
                    ditem(3, "leaf B2", {22, 12}),
                    ditem("group A", {10, 10}),
                    ditem(3, "leaf A1", {11, 11}),
                    ditem(3, "leaf A2", {12, 12}),
                    ditem(3, "leaf A3", {13, 13}),
                    ditem("group C", {30, 10}),
                    ditem(3, "leaf C1", {31, 11})}),
        };

        verifyTransition(scope);
    }

    void testSwapLevel2ItemsWithNestedSubtrees() {
        auto                __scope = trackTestExecution(this);
        ScopeV12DiagramDiff scope{
            makeLayerText(
                DiaNodeLayerParams{},
                hstd::Vec{
                    ditem("group A", {10, 10}),
                    ditem(3, "subgroup A1", {11, 11}),
                    ditem(4, "leaf A1-1", {12, 12}),
                    ditem(4, "leaf A1-2", {13, 13}),
                    ditem(3, "subgroup A2", {14, 14}),
                    ditem(4, "leaf A2-1", {15, 15}),
                    ditem("group B", {20, 10}),
                    ditem(3, "subgroup B1", {21, 11}),
                    ditem(4, "leaf B1-1", {22, 12}),
                    ditem(3, "subgroup B2", {24, 14}),
                    ditem(4, "leaf B2-1", {25, 15}),
                    ditem(4, "leaf B2-2", {26, 16}),
                    ditem("group C", {30, 10}),
                    ditem(3, "leaf C1", {31, 11})}),
            makeLayerText(
                DiaNodeLayerParams{},
                hstd::Vec{
                    ditem("group B", {20, 10}),
                    ditem(3, "subgroup B1", {21, 11}),
                    ditem(4, "leaf B1-1", {22, 12}),
                    ditem(3, "subgroup B2", {24, 14}),
                    ditem(4, "leaf B2-1", {25, 15}),
                    ditem(4, "leaf B2-2", {26, 16}),
                    ditem("group A", {10, 10}),
                    ditem(3, "subgroup A1", {11, 11}),
                    ditem(4, "leaf A1-1", {12, 12}),
                    ditem(4, "leaf A1-2", {13, 13}),
                    ditem(3, "subgroup A2", {14, 14}),
                    ditem(4, "leaf A2-1", {15, 15}),
                    ditem("group C", {30, 10}),
                    ditem(3, "leaf C1", {31, 11})}),
        };

        verifyTransition(scope);
    }
};

HAXORG_QT_TEST_MAIN(DiaContextStoreTreeSwitchingTest)
#include "tDiaContextStoreTreeSwitchingTest.moc"
