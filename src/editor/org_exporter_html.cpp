#include "org_exporter_html.hpp"

#include <exporters/Exporter.cpp>

template class Exporter<ExporterHtml, layout::BlockId>;

void ExporterHtml::visitDocument(Res& res, In<sem::Document> doc) {
    res = b.stack();
    b.add_at(res, multiString(R"(
<!DOCTYPE html>
<html>
<head>
<style>
)"));

    b.add_at(res, multiString(R"(
</style>
</head>
<body>
)"));

    b.add_at(res, string(R"(<article class="content">)"));
    for (const auto& item : doc->subnodes) { b.add_at(res, eval(item)); }
    b.add_at(res, string("</article>"));

    b.add_at(res, multiString(R"(
</body>
</html>
)"));
}

void ExporterHtml::visitSubtree(Res& res, In<sem::Subtree> tree) {
    res = b.stack({
        string("<section id=\""_ss + tree->treeId.value_or("") + "\">"_ss),
        lineWrap("h" + fmt1(tree->level), {eval(tree->title)}),
        stackSubnodes(tree),
        string("</section>"),
    });
}
