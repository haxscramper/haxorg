#include "exportergantt.hpp"

#include <hstd/stdlib/Debug.hpp>
#include <exporters/ExporterUltraplain.hpp>
#include <exporters/exportertree.hpp>
#include <hstd/stdlib/strutils.hpp>


#include <exporters/Exporter.cpp>

template class Exporter<ExporterGantt, int>;


using osk = OrgSemKind;

void treeRepr(sem::SemIdT<sem::Org> org) {
    ColStream os{qcout};
    ExporterTree(os).visitTop(org);
}

void ExporterGantt::pushVisit(int&, sem::SemIdT<sem::Subtree> tree) {
    using Period = sem::Subtree::Period;
    stack.push_back({});
    for (sem::Subtree::Period const& period : tree->getTimePeriods(
             IntSet<Period::Kind>(Period::Kind::Titled))) {
        UserTime start, end;
        if (period.period.index() == 0) {
            UserTime const& time = swl::get<0>(period.period)
                                       ->getStatic()
                                       .time;
            start = time;
            end   = time;
        } else {
            start = swl::get<1>(period.period)->from->getStatic().time;
            end   = swl::get<1>(period.period)->to->getStatic().time;
        }

        stack.back().event.name  = ExporterUltraplain::toStr(tree->title);
        stack.back().event.start = start;
        stack.back().event.stop  = end;
        stack.back().filled      = true;
        break;
    }
}

void ExporterGantt::popVisit(int&, sem::SemIdT<sem::Subtree> tree) {
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
