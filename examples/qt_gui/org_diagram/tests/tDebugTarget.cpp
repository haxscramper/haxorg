#include <src/model/DiaNodeTreeModel.hpp>
#include <QTest>
#include <src/model/DiaVersionStore.hpp>
#include <src/utils/common.hpp>
#include <src/utils/test_utils.hpp>
#include <QTimer>
#include <QSignalSpy>
#include <haxorg/sem/SemBaseApi.hpp>
#include <haxorg/exporters/exportertree.hpp>
#include <src/model/layout/ElkLayoutManager.hpp>

#pragma clang diagnostic ignored "-Wmacro-redefined"

using namespace test;

using S  = DiaVersionStore;
using EC = S::EditCmd;

class DebugTarget : public QObject {
  public slots:
    void run_thing() {
        auto             __scope = trackTestExecution(this);
        ElkLayoutManager layoutManager{"jni_elk/lib/elk-wrapper.jar"};

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
            if (result.find("ERROR:") == 0) {
                std::cerr << "Layout failed: " << result << std::endl;
            } else {
                std::cout << "Layout " << i << " completed successfully "
                          << result << std::endl;
                // Process the result JSON...
            }
        }
        QApplication::quit();
    }
};

int main(int argc, char** argv) {
    QApplication app(argc, argv);
    DebugTarget  dt;
    QTimer::singleShot(0, &dt, &DebugTarget::run_thing);
    return app.exec();
}
