#include <editor/editor_lib/org_graph_model.hpp>
#include <editor/editor_lib/app_utils.hpp>


void OrgGraph::addBox(CR<OrgBoxId> box) {
    sem::SemId<sem::Org> n = store->node(box);
    if (n->is(osk::Subtree)) {
        sem::SemId<sem::Subtree> tree = n.as<sem::Subtree>();
        if (tree->treeId) {
            this->subtreeIds[tree->treeId.value()].push_back(box);
        }
    } else if (n->is(osk::AnnotatedParagraph)) {
        sem::SemId<sem::AnnotatedParagraph>
            par = n.as<sem::AnnotatedParagraph>();
        if (par->getAnnotationKind()
            == sem::AnnotatedParagraph::AnnotationKind::Footnote) {
            this->footnoteTargets[par->getFootnote().name].push_back(box);
        }
    }

    if (!NestedNodes.contains(n->getKind())) {
        sem::eachSubnodeRec(n, [&](sem::OrgArg arg) {
            //
        });
    }

    VDesc v          = boost::add_vertex(g);
    boxToVertex[box] = v;
}
