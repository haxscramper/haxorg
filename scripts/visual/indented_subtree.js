const nodeSize = 17;
const format = d3.format(",");
const width = 900;

var root;
var i = 0;

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
  d.children = null;
}

function showDirectSubnodes(d) {
  d.children = d._children;
  d._children = null;
}

// Toggle children on click.
function click(d) {
  toggleNode(d);
  update(d);
}

function toggleNode(d) {
  if (d.children) {
    hideDirectSubnodes(d);
  } else {
    showDirectSubnodes(d);
  }
}

function update(root) {
  console.log("Updating tree for new root")
  const link = svg.append("g")
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

  const node = svg.append("g")
    .selectAll("g")
    .data(nodes)
    .join("g")
    .on('click', click)
    .attr("transform", d => `translate(0,${d.index * nodeSize})`);

  node.append("circle")
    .attr("cx", d => d.depth * nodeSize)
    .attr("r", 2.5)
    .attr("fill", d => d.children ? null : "#999");

  node.append("text")
    .attr("dy", "0.32em")
    .attr("x", d => d.depth * nodeSize + 6)
    .text(d => d.data.name);

  node.append("title")
    .text(d => d.ancestors().reverse().map(d => d.data.name).join("/"));

  for (const { label, value, format, x } of columns) {
    svg.append("text")
      .attr("dy", "0.32em")
      .attr("y", -nodeSize)
      .attr("x", x)
      .attr("text-anchor", "end")
      .attr("font-weight", "bold")
      .text(label);

    node.append("text")
      .attr("dy", "0.32em")
      .attr("x", x)
      .attr("text-anchor", "end")
      .attr("fill", d => d.children ? null : "#555")
      .data(root.copy().sum(value).descendants())
      .text(d => format(d.value, d));
  }
}

const svg = d3.select("body").append("svg")
  .attr("width", 1200)
  .attr("height", 2300)
  .attr("font-family", "sans-serif")
  .attr("font-size", 10)
  .style("overflow", "visible");


d3.json("/tmp/subtree-hierarhcy.json").then(
  function (treeData) {
    root = d3.hierarchy(treeData, d => d.subtrees).eachBefore(d => d.index = i++);
    update(root);
  },
  function (err) {
    throw err;
  }
);
