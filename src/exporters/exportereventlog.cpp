#include "exportereventlog.hpp"
#include <exporters/exportertree.hpp>
#include <QFileInfo>

using namespace sem;
using osk = OrgSemKind;

void ExporterEventLog::visitSubtree(int& _, In<sem::Subtree> tree) {
    qDebug() << "Visit subtree";
    using PK = sem::Subtree::Property::Kind;
    using D  = Event::Data;

    if (auto created = tree->getProperty(PK::Created);
        created.has_value()) {
        log(Event::SubtreeCreated{{.time = created->getCreated().time}});
    }


    ExporterTree::treeRepr(tree, QFileInfo("/tmp/tree-repr"));
    visitSubnodes(tree->subnodes);
}

void ExporterEventLog::visitListItem(int& _, In<sem::ListItem> item) {
    auto const& nodes = item->subnodes;

    if (nodes.at(0).is(osk::Paragraph)
        && nodes.at(0)->at(0).is(osk::Time)) {
        auto time = nodes.at(0)->at(0).as<sem::Time>();
        log(Event::ListLogWritten({
            {.time = nodes.at(0)->at(0).as<sem::Time>()},
            .item = item,
        }));
    }

    if (1 < nodes.size()) {
        for (auto const& sub : nodes[slice(1, 1_B)]) {
            visit(_, sub);
        }
    }
}

void ExporterEventLog::visitSubnodes(CR<Vec<sem::SemId>> ids) {
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
