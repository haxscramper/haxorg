#include "exportergantt.hpp"

#include <hstd/stdlib/Debug.hpp>
#include <exporters/ExporterUltraplain.hpp>
#include <exporters/exportertree.hpp>
#include <hstd/stdlib/strutils.hpp>

using osk = OrgSemKind;

void treeRepr(sem::Wrap<sem::Org> org) {
    ColStream os{qcout};
    ExporterTree(os).visitTop(org);
}

void ExporterGantt::pushVisit(int&, sem::Wrap<sem::Subtree> tree) {
    using Period = sem::Subtree::Period;
    stack.push_back({});
    for (sem::Subtree::Period const& period : tree->getTimePeriods(
             IntSet<Period::Kind>(Period::Kind::Titled))) {
        QDateTime start, end;
        if (period.period.index() == 0) {
            QDateTime const& time = std::get<0>(period.period)
                                        ->getStatic()
                                        .time;
            start = time;
            end   = time;
        } else {
            start = std::get<1>(period.period)->from->getStatic().time;
            end   = std::get<1>(period.period)->to->getStatic().time;
        }

        stack.back().event.name  = ExporterUltraplain::toStr(tree->title);
        stack.back().event.start = start.date();
        stack.back().event.stop  = end.date();
        stack.back().filled      = true;
        break;
    }
}

void ExporterGantt::popVisit(int&, sem::Wrap<sem::Subtree> tree) {
    auto last = stack.pop_back_v();
    if (stack.empty()) {
        if (last.filled) {
            gantt.events.push_back(last.event);
        }
    } else {
        if (last.filled) {
            stack.back().event.nested.push_back(last.event);
        }
    }
}
