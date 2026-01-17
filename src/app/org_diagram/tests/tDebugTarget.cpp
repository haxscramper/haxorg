#include <org_diagram/src/model/DiaNodeTreeModel.hpp>
#include <QTest>
#include <org_diagram/src/model/DiaVersionStore.hpp>
#include <org_diagram/src/utils/common.hpp>
#include <org_diagram/src/utils/test_utils.hpp>
#include <QTimer>
#include <QSignalSpy>
#include <haxorg/sem/SemBaseApi.hpp>
#include <haxorg/exporters/exportertree.hpp>
#include <org_diagram/src/model/layout/ElkLayoutManager.hpp>

#include <haxorg/sem/perfetto_org.hpp>
#include <hstd/ext/perfetto_aux_impl_template.hpp>

#pragma clang diagnostic ignored "-Wmacro-redefined"

using namespace test;

using S  = DiaVersionStore;
using EC = S::EditCmd;

using namespace dia::layout;

class DebugTarget : public QObject {
  public slots:

    void testDirectStringLayout() {
        auto             __scope = trackTestExecution(this);
        ElkLayoutManager layoutManager{JNI_ELK_LIB_JAR_PATH};

        // Example JSON input (you would construct this based on your
        // diagram data)
        std::string inputJson = R"({
        "id": "root",
        "children": [
            {"id": "node1", "width": 100, "height": 50},
            {"id": "node2", "width": 100, "height": 50}
        ],
        "edges": [
            {"id": "edge1", "sources": ["node1"], "targets": ["node2"]}
        ]
    })";

        // Perform multiple layouts
        for (int i = 0; i < 5; ++i) {
            std::string result = layoutManager.layoutDiagram(inputJson);
        }
    }

    void testSerializedGraphLayout() {
        auto             __scope = trackTestExecution(this);
        ElkLayoutManager layoutManager{JNI_ELK_LIB_JAR_PATH};

        layoutManager.layoutDiagram(
            elk::Graph{
                .id       = "root",
                .children = hstd::Vec<
                    elk::
                        Node>{elk::Node{.id = "node1", .width = 100, .height = 100}, elk::Node{.id = "node2", .width = 100, .height = 100}},
                .edges = hstd::Vec<elk::Edge>{elk::Edge{
                    .id      = "edge1",
                    .sources = hstd::Vec<hstd::Str>{"node1"},
                    .targets = hstd::Vec<hstd::Str>{"node2"} //
                }}});
    }

    void run_thing() {
        testDirectStringLayout();
        testSerializedGraphLayout();
        QApplication::quit();
    }
};

int main(int argc, char** argv) {
    QApplication app(argc, argv);
    DebugTarget  dt;
    hstd::log::push_sink(
        hstd::log::init_file_sink(getDebugFile(&dt, "main.log").native()));
    QTimer::singleShot(0, &dt, &DebugTarget::run_thing);
    return app.exec();
}
