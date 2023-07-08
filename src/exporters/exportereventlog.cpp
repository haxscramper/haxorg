#include "exportereventlog.hpp"
#include <exporters/exportertree.hpp>
#include <QFileInfo>

#include <exporters/Exporter.cpp>

template class Exporter<ExporterEventLog, int>;

using namespace sem;
using osk = OrgSemKind;

void ExporterEventLog::visitSubtree(int& _, In<Subtree> tree) {
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
                        {.time     = std::get<SemIdT<Time>>(range),
                         .original = entry},
                    });
                } else {
                    log(Event::ClockStarted{
                        {.time = std::get<SemIdT<TimeRange>>(range)->from,
                         .original = entry},
                    });
                    log(Event::ClockCompleted{
                        {.time = std::get<SemIdT<TimeRange>>(range)->from,
                         .original = entry},
                        .at = std::get<SemIdT<TimeRange>>(range)->to,
                    });
                }
                break;
            }

            case Log::Kind::State: {
                log(Event::SubtreeStateAssigned{{
                    .time     = entry->getState().on,
                    .original = entry,
                }});

                break;
            }

            case Log::Kind::Tag: {
                auto const& tag = entry->getTag();
                if (tag.added) {
                    log(Event::TagAssigned{{
                        .time     = tag.on,
                        .original = entry,
                    }});
                } else {
                    log(Event::TagRemoved{{
                        .time     = tag.on,
                        .original = entry,
                    }});
                }
                break;
            }

            case Log::Kind::Note: {
                auto const& note = entry->getNote();

                log(Event::SubtreeLogWritten{{
                    .time     = note.on,
                    .original = entry,
                }});

                break;
            }

            case Log::Kind::Refile: {
                auto const& refile = entry->getRefile();

                log(Event::SubtreeRefiled{{
                    .time     = refile.on,
                    .original = entry,
                }});

                break;
            }

            default: {
                qWarning() << "Unhandled exporter subtree log entry kind"
                           << entry->getLogKind();
            }
        }
    }

    visitSubnodes(tree->subnodes);
}

void ExporterEventLog::visitListItem(int& _, In<ListItem> item) {
    auto const& nodes = item->subnodes;

    if (nodes.at(0).is(osk::Paragraph)
        && nodes.at(0)->at(0).is(osk::Time)) {
        auto time = nodes.at(0)->at(0).as<Time>();
        log(Event::ListLogWritten({
            {.time = nodes.at(0)->at(0).as<Time>(), .original = item},
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
