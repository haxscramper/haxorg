// Set the dimensions and margins of the diagram
const margin = {
  top : 1200,
  right : 90,
  bottom : 30,
  left : 90
};

const width = 1400 - margin.left - margin.right;
const height = 1600 - margin.top - margin.bottom;
const circle_radius = 5;
const circle_label_spacing = 13;
const layer_horizontal_spacing = 250;
const circle_vertical_spacing = 12;

import {flushAllD3Transitions} from "../utils.mjs";

var i = 0;
var duration = 750;
var root;

function initialNodeVisibility(d) {
  switch (d.visibility) {
  case "folded":
    hideDirectSubnodes(d);
    break;
  case "children":
    // No-op, since direct children are initially visible
    break;
  case "content":
    // Hide grandchildren
    d.children && d.children.forEach(hideDirectSubnodes);
    break;
  case "all":
    // No-op, since all nodes are initially visible
    break;
  case undefined:
    break;
  default:
    console.warn(`Unknown visibility option "${d.visibility}"`);
    break;
  }
}

function initialDocumentVisibility(d) {
  switch (d.visibility) {
  case "overview":
    // Show only the root (first-level nodes)
    if (d.depth > 1)
      hideDirectSubnodes(d);
    break;
  case "content":
    // Show the root and its direct children
    if (d.depth > 2)
      hideDirectSubnodes(d);
    break;
  case "showall":
    // No-op, since all nodes are initially visible
    break;
  case "show2levels":
    if (d.depth > 2)
      hideDirectSubnodes(d);
    break;
  case "show3levels":
    if (d.depth > 3)
      hideDirectSubnodes(d);
    break;
  case "show4levels":
    if (d.depth > 4)
      hideDirectSubnodes(d);
    break;
  case "show5levels":
    if (d.depth > 5)
      hideDirectSubnodes(d);
    break;
  case "showeverything":
    // No-op, since all nodes are initially visible
    break;
  case undefined:
    break;
  default:
    console.warn(`Unknown visibility option "${d.visibility}"`);
    break;
  }
}

// Collapse the node and all it's children
function collapse(d) {
  if (d.children) {
    d._children = d.children
    d._children.forEach(collapse)
    d.children = null
  }
}

// Creates a curved (diagonal) path from parent to the child nodes
function diagonal(s, d) {
  var path = `M ${s.y} ${s.x} C ${(s.y + d.y) / 2} ${s.x}, ${(s.y + d.y) / 2} ${
      d.x}, ${d.y} ${d.x}`;
  return path
}

function hideDirectSubnodes(d) {
  d._children = d.children;
  d.children = null;
}

function showDirectSubnodes(d) {
  d.children = d._children;
  d._children = null;
}

function toggleNode(d) {
  if (d.children) {
    hideDirectSubnodes(d);
  } else {
    showDirectSubnodes(d);
  }
}

function closeSameLevelNodes(targetNode) {
  root.each(function(d) {
    if (d.depth === targetNode.depth && d !== targetNode) {
      hideDirectSubnodes(d);
    }
  });
}

// Toggle children on click.
function click(d) {
  if (d3.event.shiftKey) {
    closeSameLevelNodes(d);
  } else {
    toggleNode(d);
  }
  update(d);
}

function update(source) {
  // Assigns the x and y position for the nodes
  var treeData = treemap(root);

  // Compute the new tree layout.
  var nodes = treeData.descendants();
  var links = treeData.descendants().slice(1);

  // Normalize for fixed-depth.
  nodes.forEach(function(d) { d.y = d.depth * layer_horizontal_spacing });

  // ****************** Nodes section ***************************

  // Update the nodes...
  var node = svg.selectAll("g.node").data(
      nodes, function(d) { return d.id || (d.id = ++i); });

  // Enter any new modes at the parent's previous position.
  var nodeEnter =
      node.enter()
          .append("g")
          .attr("class", "node")
          .attr("transform",
                function(d) {
                  return "translate(" + source.y0 + "," + source.x0 + ")";
                })
          .on("click", click);

  // Add Circle for the nodes
  nodeEnter.append("circle")
      .attr("class", "node")
      .attr("r", 1e-6)
      .style("fill",
             function(d) { return d._children ? "lightsteelblue" : "#fff"; });

  // Add labels for the nodes
  nodeEnter.append("text")
      .attr("dy", ".35em")
      .attr("x", function(d) { return circle_label_spacing; })
      .attr("text-anchor", function(d) { return "start"; })
      .text(function(d) { return d.data.name; });

  // UPDATE
  var nodeUpdate = nodeEnter.merge(node);

  // Transition to the proper position for the node
  nodeUpdate
      .transition()
      // .duration(duration)
      .attr("transform",
            function(d) { return "translate(" + d.y + "," + d.x + ")"; });

  // Update the node attributes and style
  nodeUpdate.select("circle.node")
      .attr("r", circle_radius)
      .style("fill",
             function(d) { return d._children ? "lightsteelblue" : "#fff"; })
      .attr("cursor", "pointer");

  // Remove any exiting nodes
  var nodeExit =
      node.exit()
          .transition()
          // .duration(duration)
          .attr(
              "transform",
              function(
                  d) { return "translate(" + source.y + "," + source.x + ")"; })
          .remove();

  // On exit reduce the node circles size to 0
  nodeExit.select("circle").attr("r", 1e-6);

  // On exit reduce the opacity of text labels
  nodeExit.select("text").style("fill-opacity", 1e-6);

  // ****************** links section ***************************

  // Update the links...
  var link =
      svg.selectAll("path.link").data(links, function(d) { return d.id; });

  // Enter any new links at the parent's previous position.
  var linkEnter = link.enter()
                      .insert("path", "g")
                      .attr("class", "link")
                      .attr("d", function(d) {
                        var o = {x : source.x0, y : source.y0};
                        return diagonal(o, o);
                      });

  // UPDATE
  var linkUpdate = linkEnter.merge(link);

  // Transition back to the parent element position
  linkUpdate
      .transition()
      // .duration(duration)
      .attr("d", function(d) { return diagonal(d, d.parent) });

  // Remove any exiting links
  var linkExit = link.exit()
                     .transition()
                     //  .duration(duration)
                     .attr("d",
                           function(d) {
                             var o = {x : source.x, y : source.y};
                             return diagonal(o, o);
                           })
                     .remove();

  // Store the old positions for transition.
  nodes.forEach(function(d) {
    d.x0 = d.x;
    d.y0 = d.y;
  });
}

// append the svg object to the body of the page
// appends a 'group' element to 'svg'
// moves the 'group' element to the top left margin
var svg =
    d3.select("body")
        .append("svg")
        .attr("width", width + margin.right + margin.left)
        .attr("height", height + margin.top + margin.bottom)
        .append("g")
        .attr("transform", "translate(" + margin.left + "," + margin.top + ")");

// declares a tree layout and assigns the size
var treemap = d3.tree()
                  .size([
                    height,
                    width,
                  ])
                  .nodeSize([
                    circle_vertical_spacing,
                    layer_horizontal_spacing,
                  ]);

function onLoadAll(treeData) {
  // Assigns parent, children, height, depth
  root = d3.hierarchy(treeData, function(d) { return d.subtrees; });
  root.x0 = height / 2;
  root.y0 = 0;

  root.each(initialDocumentVisibility);
  root.each(initialNodeVisibility);
  update(root);
}

export function evalTest(data) {
  onLoadAll(data.treeData);
  flushAllD3Transitions();
}

export function onLoadFromLocalhost(filename, port) {
  d3.json(`http://localhost:${port}/tree_structure/${filename}`)
      .then(function(treeData) { onLoadAll(treeData); },
            function(err) { throw err; });
}
