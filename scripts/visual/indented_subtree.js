const nodeSize = 10;
const format = d3.format(",");
const width = 900;

var root;

columns = [
  {
    label: "Size",
    value: d => d.value,
    format,
    x: 500
  },
  {
    label: "Count",
    value: d => d.children ? 0 : 1,
    format: (value, d) => d.children ? format(value) : "-",
    x: 500 + 120
  }
]

function hideDirectSubnodes(d) {
  d._children = d.children;
  for (const sub of d.children) {
    sub.visible = false;
  }
  d.children = null;
}

function showDirectSubnodes(d) {
  d.children = d._children;
  d._children = null;
  for (const sub of d.children) {
    sub.visible = true;
  }
}

// Toggle children on click.
function click(d) {
  toggleNode(d);
  update(d);
}

function toggleNode(d) {
  if (d.children) {
    console.log("Hide direct subnodes");
    hideDirectSubnodes(d);
  } else {
    showDirectSubnodes(d);
  }
}

function update() {
  i = 0;
  root = root.eachBefore(d => d.visible && (d.index = i++));
  console.log("Updating tree for new root")
  // Add links between nodes
  svg.select("g.paths")
    .attr("fill", "none")
    .attr("stroke", "#999")
    .selectAll("path")
    .data(root.links())
    .join("path")
    .attr("d", d => `
M${d.source.depth * nodeSize},${d.source.index * nodeSize}
V${d.target.index * nodeSize}
h${nodeSize}
`);

  const nodes = root.descendants();

  const node = svg.select("g.nodes")
    .selectAll("g")
    .data(nodes, d => d.d);

  var nodeEnter = node.enter().append("g")
    .on('click', click)
    .attr("transform", d => `translate(0,${d.index * nodeSize})`);

  nodeEnter.append("circle")
    .attr("cx", d => d.depth * nodeSize)
    .attr("r", 2.5)
    .style("display", d => d.visible ? "inline" : "none")
    .attr("fill", d => d.children ? null : "#999");

  nodeEnter.append("text")
    .attr("dy", "0.32em")
    .attr("x", d => d.depth * nodeSize + 6)
    .style("display", d => d.visible ? "inline" : "none")
    .text(d => d.data.name);

  nodeEnter.append("title")
    .text(d => d.ancestors().reverse().map(d => d.data.name).join("/"));

  for (const { label, value, format, x } of columns) {
    svg.append("text")
      .attr("dy", "0.32em")
      .attr("y", -nodeSize)
      .attr("x", x)
      .attr("text-anchor", "end")
      .attr("font-weight", "bold")
      .text(label);

    nodeEnter.append("text")
      .attr("dy", "0.32em")
      .attr("x", x)
      .attr("text-anchor", "end")
      .attr("fill", d => d.children ? null : "#555")
      .data(root.copy().sum(value).descendants())
      .text(d => format(d.value, d));
  }

  node.exit().remove()
}

const svg = d3.select("body").append("svg")
  .attr("width", 1200)
  .attr("height", 2300)
  .attr("font-family", "sans-serif")
  .attr("font-size", 10)
  .style("overflow", "visible");

svg.append("g").attr("class", "paths");
svg.append("g").attr("class", "nodes");

function getInitialVisibility(d) {
  visible = true;
  if (d.data.isSubtree && 0 < d.ancestors().length) {
    search_loop:
    for (parent of d.ancestors()) {
      if (parent.data.isSubtree && parent != d) {
        for (prop of parent.data.properties) {
          if (prop.data.kind == "Visibility") {
            if (prop.data.level == "Folded") {
              visible = false;
              break search_loop;
            }
          }
        }
      }

    }
  }

  return visible;
}

d3.json("/tmp/subtree-hierarhcy.json").then(
  function (treeData) {
    counter = 0;
    idx = 0;
    root = d3.hierarchy(treeData, d => d.subtrees).eachBefore(function (d) {
      d.visible = getInitialVisibility(d);
      d.id = counter++;
    });
    update();
  },
  function (err) {
    throw err;
  }
);
