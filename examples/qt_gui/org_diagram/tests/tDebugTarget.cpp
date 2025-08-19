#include <QTest>
#include <src/model/HistoryManager.hpp>
#include <src/utils/common.hpp>

#pragma clang diagnostic ignored "-Wmacro-redefined"
#define _cat "test.history"


class DebugTarget : public QObject {
  public:
    void run_thing() {
        HistoryManager manager;
        manager.setDocument("word");
        manager.setDocument("word second");

        auto diff = manager.getDifference(0, 1);
        for (auto const& it : diff) { HSLOG_TRACE(_cat, hstd::fmt1(it)); }
    }
};

int main() {
    DebugTarget dt;
    dt.run_thing();
}
