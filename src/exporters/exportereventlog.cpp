#include "exportereventlog.hpp"
#include <exporters/exportertree.hpp>
#include <QFileInfo>

using namespace sem;
using osk = OrgSemKind;

void ExporterEventLog::visitSubtree(int& _, In<Subtree> tree) {
    qDebug() << "Visit subtree";
    using PK = Subtree::Property::Kind;
    using D  = Event::Data;

    if (auto created = tree->getProperty(PK::Created);
        created.has_value()) {
        log(Event::SubtreeCreated{
            {.original = tree, .time = created->getCreated().time}});
    }


    for (auto const& entry : tree->logbook) {
        using Log = SubtreeLog;
        switch (entry->getLogKind()) {
            case Log::Kind::Clock: {
                auto range = entry->getClock().range;
                if (std::holds_alternative<SemIdT<Time>>(range)) {
                    log(Event::ClockStarted{
                        {.original = entry,
                         .time     = std::get<SemIdT<Time>>(range)},
                    });
                } else {
                    log(Event::ClockStarted{
                        {.original = entry,
                         .time = std::get<SemIdT<TimeRange>>(range)->from},
                    });
                    log(Event::ClockCompleted{
                        {.original = entry,
                         .time = std::get<SemIdT<TimeRange>>(range)->from},
                        .at = std::get<SemIdT<TimeRange>>(range)->to,
                    });
                }
                break;
            }

            case Log::Kind::State: {
                log(Event::SubtreeStateAssigned{{
                    .original = entry,
                    .time     = entry->getState().on,
                }});

                break;
            }

            case Log::Kind::Tag: {
                auto const& tag = entry->getTag();
                if (tag.added) {
                    log(Event::TagAssigned{{
                        .original = entry,
                        .time     = tag.on,
                    }});
                } else {
                    log(Event::TagRemoved{{
                        .original = entry,
                        .time     = tag.on,
                    }});
                }
                break;
            }

            default: {
                qWarning() << "Unhandled exporter subtree log entry kind"
                           << entry->getLogKind();
            }
        }
    }

    ExporterTree::treeRepr(tree, QFileInfo("/tmp/tree-repr"));
    visitSubnodes(tree->subnodes);
}

void ExporterEventLog::visitListItem(int& _, In<ListItem> item) {
    auto const& nodes = item->subnodes;

    if (nodes.at(0).is(osk::Paragraph)
        && nodes.at(0)->at(0).is(osk::Time)) {
        auto time = nodes.at(0)->at(0).as<Time>();
        log(Event::ListLogWritten({
            {.original = item, .time = nodes.at(0)->at(0).as<Time>()},
            .item = item,
        }));
    }

    if (1 < nodes.size()) {
        for (auto const& sub : nodes[slice(1, 1_B)]) {
            visit(_, sub);
        }
    }
}

void ExporterEventLog::visitSubnodes(CR<Vec<SemId>> ids) {
    int i = 0;
    for (auto const& id : ids) {
        visit(i, id);
    }
}

void ExporterEventLog::log(const Event& event) {
    if (logConsumer) {
        logConsumer(event);
    }
}
