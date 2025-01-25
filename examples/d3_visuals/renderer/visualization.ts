// src/renderer/visualization.ts
import {execSync} from "child_process";
import * as d3 from "d3";
import * as fs from "fs";
import SVGPathCommander from "svg-path-commander";
import {BaseLogger} from "tslog";

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

type OrgHierarchyNode      = d3.HierarchyNode<OrgTreeNode>;
type OrgHierarchyPointNode = d3.HierarchyPointNode<OrgTreeNode>;

function dump_html() {
  const html: string = document.documentElement.outerHTML;
  const fileName     = "/tmp/d3_js_output.html"
  fs.writeFileSync(fileName, html, "utf-8");
  try {
    execSync(`tidy -q -m -i -w 120 --show-warnings no ${fileName}`);
  } catch (e) {
  }
}

interface XYPoint {
  x: number;
  y: number;
}

export class CollapsibleTreeVisualizationConfig {
  width: number                    = 1400;
  height: number                   = 1600;
  circle_radius: number            = 5;
  circle_label_spacing: number     = 13;
  layer_horizontal_spacing: number = 250;
  circle_vertical_spacing: number  = 12;
  x_offset: number                 = 0;
  y_offset?: number                = undefined;
  link_width: number               = 2;
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
    this.root.each(CollapsibleTreeVisualization.initialDocumentVisibility);
    this.root.each(CollapsibleTreeVisualization.initialNodeVisibility);
    this.update();
  }

  async toTreeHierarchy(client: org.OrgClient,
                        id: org.ImmUniqId): Promise<OrgTreeNode|null> {
    if (id.id.format.startsWith("Subtree")
        || id.id.format.startsWith("Document")) {
      var result: OrgTreeNode = {
        id : id,
        subtrees : Array(),
        visibility : "showall",
        name : await client.getCleanSubtreeTitle({id : id}),
        idx : 0,
      };

      const size: number = await client.getSize({id : id});

      for (var idx = 0; idx < size; ++idx) {
        const subnode       = await client.getSubnodeAt({id : id, index : idx});
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
    await new Promise<void>(
        resolve => ws.addEventListener("open", () => resolve()));

    const client = org.createWebSocketClient(ws);
    client.setExceptionHandler({handler : true});

    await client.setRootFile({path : "/home/haxscramper/tmp/org_trivial.org"});

    const root                   = await client.getRoot({});
    const              hierarchy = await this.toTreeHierarchy(client, root);

    if (hierarchy) {
      this.onLoadAll(hierarchy);
    }
  }

  constructor(containerId: string, conf: CollapsibleTreeVisualizationConfig) {
    this.conf = conf;
    if (!this.conf.y_offset) {
      this.conf.y_offset = this.conf.height / 2;
    }
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
  diagonal(s: XYPoint, d: XYPoint): string {
    const path = d3.path();

    // Control points for the bezier curve
    const controlPointX1 = s.y + (d.y - s.y) / 3;
    const controlPointX2 = d.y - (d.y - s.y) / 3;

    // Calculate the direction of the curve (vector from start to end)
    const deltaX = d.x - s.x;
    const deltaY = d.y - s.y;
    const length = Math.sqrt(deltaX * deltaX + deltaY * deltaY);

    if (length === 0) {
      return "";
    } else {
      // Calculate unit normal vector (perpendicular to the direction vector)
      const normalX = (this.conf.link_width / 2) * (deltaY / length);
      const normalY = (this.conf.link_width / 2) * (-deltaX / length);

      // Move to the starting point, offset by the normal vector
      path.moveTo(s.y + normalY, s.x + normalX);

      // Draw upper part of the bezier curve with offset
      path.bezierCurveTo(controlPointX1 + normalY, s.x + normalX,
                         controlPointX2 + normalY, d.x + normalX, d.y + normalY,
                         d.x + normalX);

      // Draw the lower part of the bezier curve (reverse normal direction)
      path.lineTo(d.y - normalY, d.x - normalX);
      path.bezierCurveTo(controlPointX2 - normalY, d.x - normalX,
                         controlPointX1 - normalY, s.x - normalX, s.y - normalY,
                         s.x - normalX);

      // Close the path
      path.closePath();

      return path.toString();
    }
  }

  static hideDirectSubnodes(d) {
    d._children = d.children;
    d.children  = null;
  }

  static showDirectSubnodes(d) {
    d.children  = d._children;
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
    const v = d.data.visibility;
    if (v === "folded") {
      CollapsibleTreeVisualization.hideDirectSubnodes(d);
    } else if (v === "content") {
      d.children
          && d.children.forEach(
              CollapsibleTreeVisualization.hideDirectSubnodes);
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
  click(d: OrgHierarchyPointNode) {
    // if (d3.event.shiftKey) {
    // closeSameLevelNodes(d);
    // } else {
    this.toggleNode(d);
    // }
    this.update();
  }

  update() {
    // Assigns the x and y position for the nodes
    var treeData = this.treemap(this.root);
    // Compute the new tree layout.
    var nodes = treeData.descendants();
    var links = treeData.descendants().slice(1);
    {
      const minY       = d3.min(treeData.descendants(), d => d.y) ?? 0;
      const maxY       = d3.max(treeData.descendants(), d => d.y) ?? 0;
      const treeHeight = maxY - minY;
      const yOffset    = (this.conf.height - treeHeight) / 2 - minY;
      treeData.descendants().forEach(node => { node.y += yOffset; });
    }

    // Normalize for fixed-depth.
    nodes.forEach((d) => {d.y = d.depth * this.conf.layer_horizontal_spacing});

    // ****************** Nodes section ***************************

    var i = 0;
    // Update the nodes...
    var node
        = this.svg.selectAll<d3.BaseType, OrgHierarchyPointNode>("g.node").data(
            nodes, function(this: d3.BaseType, d: OrgHierarchyPointNode) {
              return d.data.idx || (d.data.idx = ++i);
            });

    // Enter any new modes at the parent's previous position.
    var nodeEnter //
        = node.enter()
              .append("g")
              .attr("class", "node")
              .attr("transform",
                    (d: OrgHierarchyPointNode) => {
                      return "translate(" + d.y + "," + d.x + ")";
                    })
              .on("click",
                  (event: any, d: OrgHierarchyPointNode) => { this.click(d); });

    // Add Circle for the nodes
    nodeEnter.append("circle")
        .attr("class", "node")
        .attr("r", 1e-6)
        .style("fill", function(d: OrgHierarchyPointNode) {
          return d.data.tmp_children ? "lightsteelblue" : "cyan";
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
    nodeUpdate.transition()
        .on("end", dump_html)
        // .duration(duration)
        .attr("transform", (d: OrgHierarchyPointNode) => {
          return "translate(" + d.y + "," + d.x + ")";
        });

    // Update the node attributes and style
    nodeUpdate.select("circle.node")
        .attr("r", this.conf.circle_radius)
        .style("fill", function(this: d3.BaseType, d: OrgHierarchyPointNode):
                           string {
                             return d.data.tmp_children ? "lightsteelblue"
                                                        : "cyan";
                           })
        .attr("cursor", "pointer");

    // Remove any exiting nodes
    var nodeExit //
        = node.exit<OrgHierarchyPointNode>()
              .transition()
              .on("end", dump_html)
              // .duration(duration)
              .attr("transform", (d: OrgHierarchyPointNode):
                                     string => {
                                       return "translate(" + this.conf.y_offset
                                              + "," + this.conf.x_offset + ")";
                                     })
              .remove();

    // On exit reduce the node circles size to 0
    nodeExit.select("circle").attr("r", 1e-6);

    // On exit reduce the opacity of text labels
    nodeExit.select("text").style("fill-opacity", 1e-6);

    // ****************** links section ***************************

    // Update the links...
    var link
        = this.svg.selectAll<d3.BaseType, OrgHierarchyPointNode>("path.link")
              .data(links, function(this: d3.BaseType,
                                    d: OrgHierarchyNode) { return d.id; });

    // Enter any new links at the parent's previous position.
    var linkEnter
        = link.enter()
              .insert("path", "g")
              .attr("class", "link")
              .attr("d", (d: OrgHierarchyNode) => {
                var o = {x : this.conf.x_offset, y : this.conf.y_offset!};
                return this.diagonal(o, o);
              });

    // UPDATE
    var linkUpdate = linkEnter.merge(link);

    // Transition back to the parent element position
    linkUpdate.transition()
        .on("end", dump_html)
        // .duration(duration)
        .attr("d", (d: OrgHierarchyNode) => {return this.diagonal(
                       d as XYPoint, d.parent as XYPoint)});

    // Remove any exiting links
    var linkExit
        = link.exit()
              .transition()
              .on("end", dump_html)
              //  .duration(duration)
              .attr("d",
                    (d: OrgHierarchyNode) => {
                      var o = {x : this.conf.x_offset, y : this.conf.y_offset!};
                      return this.diagonal(o, o);
                    })
              .remove();

    // // Store the old positions for transition.
    // nodes.forEach(function(d: OrgHierarchyNode) {
    //   d.x0 = d.x;
    //   d.y0 = d.y;
    // });

    dump_html();
  }
}

async function treeRepr(client: org.OrgClient, id: org.ImmUniqId,
                        depth: number = 0) {
  log.info(" ".repeat(depth * 2) + `[${depth}] ${id.id.format}`)

  const size: number = await client.getSize({id : id});
  for (var idx = 0; idx < size; ++idx) {
    const subnode = await client.getSubnodeAt({id : id, index : idx});
    await                 treeRepr(client, subnode, depth + 1);
  }
}
