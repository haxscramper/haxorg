#include "src/model/QtOrgAstModel.hpp"
#include <QTest>
#include <src/model/HistoryManager.hpp>
#include <src/utils/common.hpp>
#include <src/utils/test_utils.hpp>

#pragma clang diagnostic ignored "-Wmacro-redefined"
#define _cat "test.history"

using namespace test;

class DebugTarget : public QObject {
  public:
    void run_thing() {
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
        visualizeTestDiff(this, scope);
    }
};

int main() {
    DebugTarget dt;
    dt.run_thing();
}
