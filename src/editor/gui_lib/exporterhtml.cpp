#include "exporterhtml.hpp"

#include <exporters/Exporter.cpp>
template class Exporter<ExporterHtml, layout::BlockId>;

const char* sidebarSync = R"html(
    var toc = document.querySelector('.toc');
    var tocPath = document.querySelector('.toc-marker path');
    var tocItems;

    // Factor of screen size that the element must cross
    // before it's considered visible
    var TOP_MARGIN = 0.1;
    var BOTTOM_MARGIN = 0.2;
    var pathLength;
    var lastPathStart;
    var lastPathEnd;

    window.addEventListener('resize', drawPath, false);
    window.addEventListener('scroll', sync, false);

    drawPath();

    function drawPath() {

      tocItems = [].slice.call(toc.querySelectorAll('li'));

      // Cache element references and measurements
      tocItems = tocItems.map(function (item) {
        var anchor = item.querySelector('a');
        var target = document.getElementById(anchor.getAttribute('href').slice(1));

        return {
          listItem: item,
          anchor: anchor,
          target: target
        };
      });

      // Remove missing targets
      tocItems = tocItems.filter(function (item) {
        return !!item.target;
      });

      var path = [];
      var pathIndent;

      tocItems.forEach(function (item, i) {

        var x = item.anchor.offsetLeft - 5,
          y = item.anchor.offsetTop,
          height = item.anchor.offsetHeight;

        if (i === 0) {
          path.push('M', x, y, 'L', x, y + height);
          item.pathStart = 0;
        } else {
          // Draw an additional line when there's a change in
          // indent levels
          if (pathIndent !== x) path.push('L', pathIndent, y);

          path.push('L', x, y);

          // Set the current path so that we can measure it
          tocPath.setAttribute('d', path.join(' '));
          item.pathStart = tocPath.getTotalLength() || 0;

          path.push('L', x, y + height);
        }

        pathIndent = x;

        tocPath.setAttribute('d', path.join(' '));
        item.pathEnd = tocPath.getTotalLength();

      });

      pathLength = tocPath.getTotalLength();

      sync();

    }

    function sync() {
      var windowHeight = window.innerHeight;
      var pathStart = pathLength;
      var pathEnd = 0;
      var visibleItems = 0;

      tocItems.forEach(function (item) {
        var targetBounds = item.target.getBoundingClientRect();

        if (targetBounds.bottom > windowHeight * TOP_MARGIN && targetBounds.top < windowHeight * (1 - BOTTOM_MARGIN)) {
          pathStart = Math.min(item.pathStart, pathStart);
          pathEnd = Math.max(item.pathEnd, pathEnd);
          visibleItems += 1;

          item.listItem.classList.add('visible');
        }
        else {
          item.listItem.classList.remove('visible');
        }

      });

      // Specify the visible path or hide the path altogether
      // if there are no visible items
      if (visibleItems > 0 && pathStart < pathEnd) {
        if (pathStart !== lastPathStart || pathEnd !== lastPathEnd) {
          tocPath.setAttribute('stroke-dashoffset', '1');
          tocPath.setAttribute('stroke-dasharray', '1, ' + pathStart + ', ' + (pathEnd - pathStart) + ', ' + pathLength);
          tocPath.setAttribute('opacity', 1);
        }
      } else {
        tocPath.setAttribute('opacity', 0);
      }

      lastPathStart = pathStart;
      lastPathEnd = pathEnd;

    }
)html";

const char* sidebarStyle = R"html(
    * {
      box-sizing: border-box;
    }

    body {
      width: 100vw;
      height: 100vh;
      overflow: auto;
    }

    body {
      padding: 2em 2em 2em 20em;
    }

    .toc {
      overflow-y: scroll;
      overflow-x: scroll;
      position: fixed;
      height: 100%;
      left: 0em;
      padding: 1em;
      width: 20em;
    }

    .toc ul {
      list-style: none;
      padding: 0;
      margin: 0;
    }

    .toc ul ul {
      padding-left: 2em;
    }

    .toc li a {
      display: inline-block;
      color: #aaa;
      text-decoration: none;
      transition: all 0.3s cubic-bezier(0.23, 1, 0.32, 1);
    }

    .toc li.visible>a {
      color: #111;
      transform: translate(5px);
    }

    .toc-marker {
      position: absolute;
      top: 0;
      left: 0;
      width: 100%;
      height: 4000%;
      z-index: -1;
    }

    .toc-marker path {
      transition: all 0.3s ease;
    }

)html";

void ExporterHtml::visitDocument(Res& res, In<sem::Document> doc) {
    res = b.stack();
    b.add_at(res, multiString(R"(
<!DOCTYPE html>
<html>
<head>
<style>
)"));

    b.add_at(res, multiString(sidebarStyle));

    b.add_at(res, multiString(R"(
</style>
</head>
<body>
)"));

    b.add_at(
        res,
        b.stack({
            string(R"(<nav class="toc">)"),
            stackWrap("ul", {b.indent(2, createTocList(doc))}),
            string(R"html(
    <svg class="toc-marker" width="200" height="200" xmlns="http://www.w3.org/2000/svg">
      <path stroke="#444" stroke-width="3" fill="transparent" stroke-dasharray="0, 0, 0, 1000" stroke-linecap="round"
        stroke-linejoin="round" transform="translate(-0.5, -0.5)" />
    </svg>
  </nav>
)html"),
        }));

    b.add_at(res, string(R"(<article class="content">)"));

    for (const auto& item : doc->subnodes) { b.add_at(res, eval(item)); }

    b.add_at(res, string("</article>"));

    b.add_at(res, stackWrap("script", {multiString(sidebarSync)}));
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

ExporterHtml::Res ExporterHtml::createTocList(sem::SemId<sem::Org> node) {
    Vec<Res> subItems;
    for (const auto& it : node->subnodes) {
        Res tocEntry = createTocList(it);
        if (!tocEntry.isNil()) { subItems.push_back(tocEntry); }
    }

    if (node->getKind() == OrgSemKind::Subtree) {
        Res stack = b.stack();
        b.add_at(stack, lineSubnodes(node.as<sem::Subtree>()->title));

        if (!subItems.empty()) {
            b.add_at(
                stack,
                stackWrap("ul", {b.indent(2, {b.stack(subItems)})}));
        }

        bool isStack = !subItems.empty();
        return directionWrap(
            isStack, "li", {b.indent(isStack ? 2 : 0, {stack})});

    } else {
        if (subItems.empty()) {
            return Res::Nil();
        } else {
            return b.stack(subItems);
        }
    }
}
