#include "org_exporter_html.hpp"

#include <haxorg/exporters/Exporter.cpp>

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

void ExporterHtml::visitLink(Res& res, In<sem::Link> link) {
    if (link->description) {
        res = eval(link->description.value());
    } else {
        switch (link->getLinkKind()) {
            case sem::Link::Kind::Footnote: {
                res = lineWrap(
                    "sup",
                    {string(
                        "["_ss + link->getFootnote().target + "]"_ss)});
                break;
            }
            default: {
                res = string("");
            }
        }
    }
}
