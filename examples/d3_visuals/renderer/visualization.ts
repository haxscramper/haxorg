// src/renderer/visualization.ts
import * as d3 from "d3";

import * as org from "./org_data.ts";
import {log} from "./org_logger.ts";

interface OrgTreeNode {
  id: org.ImmUniqId;
  subtrees: OrgTreeNode[];
  visibility: string;
  tmp_children?: OrgHierarchyNode[];
  name: string;
  idx: number;
}

interface OrgHierarchyNode extends d3.HierarchyNode<OrgTreeNode> {
  // d3.hierarchy returns hierarchy node type, but there are extra fields not
  // described in the shipped interface.
  x0: number|undefined;
  y0: number|undefined;
}

type OrgHierarchyPointNode = d3.HierarchyPointNode<OrgTreeNode>;

// Set the dimensions and margins of the diagram

// export class CircleVisualization {
//   private svg: d3.Selection<SVGSVGElement, OrgTreeNode, HTMLElement, any>;
//   private data: number[];

//   constructor(containerId: string, width: number = 400, height: number =
//   200) {
//     this.data = Array.from({length : 5}, () => Math.random() * 100);

//     this.svg = d3.select<SVGSVGElement, OrgTreeNode>(`#${containerId}`)
//                    .append("svg")
//                    .attr("width", width)
//                    .attr("height", height);
//   }

//   render(): void {
//     log.info("Render");
//     tree_repr_test();
//   }
// }

export class CollapsibleTreeVisualizationConfig {
  width: number = 1400;
  height: number = 1600;
  circle_radius: number = 5;
  circle_label_spacing: number = 13;
  layer_horizontal_spacing: number = 250;
  circle_vertical_spacing: number = 12;
  x_offset: number = 0;
  y_offset: number = 0;
};

export class CollapsibleTreeVisualization {
  svg: d3.Selection<SVGGElement, OrgTreeNode, HTMLElement, any>;
  treemap: d3.TreeLayout<OrgTreeNode>;
  root: OrgHierarchyNode;
  conf: CollapsibleTreeVisualizationConfig;

  onLoadAll(treeData: OrgTreeNode) {
    // Assigns parent, children, height, depth
    this.root = d3.hierarchy(treeData,
                             function(d: OrgTreeNode) { return d.subtrees; }) as
                OrgHierarchyNode;
    console.log(this.root);
    this.root.each(CollapsibleTreeVisualization.initialDocumentVisibility);
    this.root.each(CollapsibleTreeVisualization.initialNodeVisibility);
    this.update(this.root);
  }

  async toTreeHierarchy(client: org.OrgClient,
                        id: org.ImmUniqId): Promise<OrgTreeNode|null> {
    if (id.id.format.startsWith("Subtree") ||
        id.id.format.startsWith("Document")) {
      var result: OrgTreeNode = {
        id : id,
        subtrees : Array(),
        visibility : "all",
        name : await client.getCleanSubtreeTitle({id : id}),
        idx : 0,
      };

      const size: number = await client.getSize({id : id});

      for (var idx = 0; idx < size; ++idx) {
        const subnode = await client.getSubnodeAt({id : id, index : idx});
        const sub_hierarchy = await this.toTreeHierarchy(client, subnode);
        if (sub_hierarchy) {
          result.subtrees.push(sub_hierarchy);
        }
      }

      return result;
    } else {
      return null;
    }
  }

  async render_tree_repr() {
    const ws = new WebSocket("ws://localhost:8089");

    // Wait for connection
    await new Promise<void>(resolve =>
                                ws.addEventListener("open", () => resolve()));

    const client = org.createWebSocketClient(ws);
    client.setExceptionHandler({handler : true});

    await client.setRootFile({path : "/home/haxscramper/tmp/org_trivial.org"});

    const root = await client.getRoot({});
    log.info(`root: ${JSON.stringify(root)}`);

    // await treeRepr(client, root, 0);
    log.info("done");

    const hierarchy = await this.toTreeHierarchy(client, root);

    if (hierarchy) {
      console.log(hierarchy);
      this.onLoadAll(hierarchy);
    }
  }

  constructor(containerId: string, conf: CollapsibleTreeVisualizationConfig) {
    this.conf = conf;
    // append the svg object to the body of the page
    // appends a 'group' element to 'svg'
    // moves the 'group' element to the top left margin
    this.svg = d3.select<SVGSVGElement, OrgTreeNode>(`#${containerId}`)
                   .append("svg")
                   .attr("width", this.conf.width)
                   .attr("height", this.conf.height)
                   .append("g");

    // declares a tree layout and assigns the size
    this.treemap = d3.tree<OrgTreeNode>()
                       .size([
                         this.conf.height,
                         this.conf.width,
                       ])
                       .nodeSize([
                         this.conf.circle_vertical_spacing,
                         this.conf.layer_horizontal_spacing,
                       ]);
  }

  // Collapse the node and all it's children
  collapse(d: OrgHierarchyNode) {
    if (d.children) {
      d.data.tmp_children = d.children;
      d.data.tmp_children.forEach(this.collapse);
      d.children = undefined;
    }
  }

  // Creates a curved (diagonal) path from parent to the child nodes
  diagonal(s, d: OrgHierarchyNode) {
    var path = `M ${s.y} ${s.x} C ${(s.y + d.y) / 2} ${s.x}, ${
        (s.y + d.y) / 2} ${d.x}, ${d.y} ${d.x}`;
    return path
  }

  static hideDirectSubnodes(d) {
    d._children = d.children;
    d.children = null;
  }

  static showDirectSubnodes(d) {
    d.children = d._children;
    d._children = null;
  }

  toggleNode(d) {
    if (d.children) {
      CollapsibleTreeVisualization.hideDirectSubnodes(d);
    } else {
      CollapsibleTreeVisualization.showDirectSubnodes(d);
    }
  }

  closeSameLevelNodes(targetNode) {
    this.root.each(function(d) {
      if (d.depth === targetNode.depth && d !== targetNode) {
        CollapsibleTreeVisualization.hideDirectSubnodes(d);
      }
    });
  }

  static initialNodeVisibility(d: OrgHierarchyNode) {
    switch (d.data.visibility) {
    case "folded":
      CollapsibleTreeVisualization.hideDirectSubnodes(d);
      break;
    case "children":
      // No-op, since direct children are initially visible
      break;
    case "content":
      // Hide grandchildren
      d.children &&
          d.children.forEach(CollapsibleTreeVisualization.hideDirectSubnodes);
      break;
    case "all":
      // No-op, since all nodes are initially visible
      break;
    case undefined:
      break;
    default:
      console.warn(`Unknown visibility option "${d.data.visibility}"`);
      break;
    }
  }

  static initialDocumentVisibility(d: OrgHierarchyNode) {
    switch (d.data.visibility) {
    case "overview":
      // Show only the root (first-level nodes)
      if (d.depth > 1)
        CollapsibleTreeVisualization.hideDirectSubnodes(d);
      break;
    case "content":
      // Show the root and its direct children
      if (d.depth > 2)
        CollapsibleTreeVisualization.hideDirectSubnodes(d);
      break;
    case "showall":
      // No-op, since all nodes are initially visible
      break;
    case "show2levels":
      if (d.depth > 2)
        CollapsibleTreeVisualization.hideDirectSubnodes(d);
      break;
    case "show3levels":
      if (d.depth > 3)
        CollapsibleTreeVisualization.hideDirectSubnodes(d);
      break;
    case "show4levels":
      if (d.depth > 4)
        CollapsibleTreeVisualization.hideDirectSubnodes(d);
      break;
    case "show5levels":
      if (d.depth > 5)
        CollapsibleTreeVisualization.hideDirectSubnodes(d);
      break;
    case "showeverything":
      // No-op, since all nodes are initially visible
      break;
    case undefined:
      break;
    default:
      console.warn(`Unknown visibility option "${d.data.visibility}"`);
      break;
    }
  }

  // Toggle children on click.
  click(d: OrgHierarchyNode) {
    log.info(`Click on node ${d.data.id}`)
        // if (d3.event.shiftKey) {
        // closeSameLevelNodes(d);
        // } else {
        this.toggleNode(d);
    // }
    this.update(d);
  }

  update(source: OrgHierarchyNode) {
    // Assigns the x and y position for the nodes
    var treeData = this.treemap(this.root);
    // Compute the new tree layout.
    var nodes = treeData.descendants();
    var links = treeData.descendants().slice(1);

    // Normalize for fixed-depth.
    nodes.forEach((d) => {d.y = d.depth * this.conf.layer_horizontal_spacing});

    // ****************** Nodes section ***************************

    var i = 0;
    // Update the nodes...
    var node =
        this.svg.selectAll<d3.BaseType, OrgHierarchyPointNode>("g.node").data(
            nodes, function(this: d3.BaseType, d: OrgHierarchyPointNode) {
              return d.data.idx || (d.data.idx = ++i);
            });

    console.log(nodes);

    // Enter any new modes at the parent's previous position.
    var nodeEnter //
        = node.enter()
              .append("g")
              .attr("class", "node")
              .attr("transform",
                    (d: OrgHierarchyPointNode) => {
                      return "translate(" + this.conf.x_offset + "," +
                             this.conf.y_offset + ")";
                    })
              .on("click", this.click);

    // Add Circle for the nodes
    nodeEnter.append("circle")
        .attr("class", "node")
        .attr("r", 1e-6)
        .style("fill", function(d: OrgHierarchyPointNode) {
          return d.data.tmp_children ? "lightsteelblue" : "#fff";
        });

    // Add labels for the nodes
    nodeEnter.append("text")
        .attr("dy", ".35em")
        .attr("x",
              (d: OrgHierarchyPointNode) => {
                return this.conf.circle_label_spacing;
              })
        .attr("text-anchor", function(d) { return "start"; })
        .text(function(this: SVGTextElement,
                       d: OrgHierarchyPointNode) { return d.data.name; });

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
        .attr("r", this.conf.circle_radius)
        .style("fill", function(this: d3.BaseType, d: OrgHierarchyPointNode):
                           string {
                             return d.data.tmp_children ? "lightsteelblue"
                                                        : "#fff";
                           })
        .attr("cursor", "pointer");

    // Remove any exiting nodes
    var nodeExit //
        = node.exit()
              .transition()
              // .duration(duration)
              .attr("transform",
                    function(this: d3.BaseType, d: OrgHierarchyPointNode):
                        string {
                          return "translate(" + source.y + "," + source.x + ")";
                        })
              .remove();

    // On exit reduce the node circles size to 0
    nodeExit.select("circle").attr("r", 1e-6);

    // On exit reduce the opacity of text labels
    nodeExit.select("text").style("fill-opacity", 1e-6);

    // ****************** links section ***************************

    // Update the links...
    var link = this.svg.selectAll("path.link")
                   .data(links, function(d: OrgHierarchyNode) { return d.id; });

    // Enter any new links at the parent's previous position.
    var linkEnter =
        link.enter()
            .insert("path", "g")
            .attr("class", "link")
            .attr("d", (d: OrgHierarchyNode) => {
              var o = {x : this.conf.x_offset, y : this.conf.y_offset};
              return this.diagonal(o, o);
            });

    // UPDATE
    var linkUpdate = linkEnter.merge(link);

    // Transition back to the parent element position
    linkUpdate
        .transition()
        // .duration(duration)
        .attr("d",
              (d: OrgHierarchyNode) => {return this.diagonal(d, d.parent)});

    // Remove any exiting links
    var linkExit = link.exit()
                       .transition()
                       //  .duration(duration)
                       .attr("d",
                             (d: OrgHierarchyNode) => {
                               var o = {x : source.x, y : source.y};
                               return this.diagonal(o, o);
                             })
                       .remove();

    // Store the old positions for transition.
    nodes.forEach(function(d: OrgHierarchyNode) {
      d.x0 = d.x;
      d.y0 = d.y;
    });
  }
}

async function treeRepr(client: org.OrgClient, id: org.ImmUniqId,
                        depth: number = 0) {
  log.info(" ".repeat(depth * 2) + `[${depth}] ${id.id.format}`)

  const size: number = await client.getSize({id : id});
  for (var idx = 0; idx < size; ++idx) {
    const subnode = await client.getSubnodeAt({id : id, index : idx});
    await treeRepr(client, subnode, depth + 1);
  }
}
