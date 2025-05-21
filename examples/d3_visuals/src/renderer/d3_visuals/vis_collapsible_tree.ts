import * as d3 from "d3";

import {org} from "../org_data.ts";
import {log} from "../org_logger.ts";
import {dump_html} from "../utils.ts";
import {initWasmModule, osk} from "../wasm_client";

interface OrgTreeNode {
  node: org.Org;
  subtrees: OrgTreeNode[];
  visibility: string;
  tmp_children?: OrgHierarchyNode[];
  name: string;
  idx: number;
}

type OrgHierarchyNode      = d3.HierarchyNode<OrgTreeNode>;
type OrgHierarchyPointNode = d3.HierarchyPointNode<OrgTreeNode>;

interface XYPoint {
  x: number;
  y: number;
}

export class CollapsibleTreeVisualizationConfig {
  width: number                    = 1400;
  height: number                   = 800;
  circle_radius: number            = 5;
  circle_label_spacing: number     = 13;
  layer_horizontal_spacing: number = 250;
  circle_vertical_spacing: number  = 12;
  x_offset: number                 = 0;
  y_offset?: number                = undefined;
  link_width: number               = 2;
  path: string;
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

  toTreeHierarchy(node: org.Org): OrgTreeNode|null {
    if (node.getKind() == osk().Subtree || node.getKind() == osk().Document) {
      var   result: OrgTreeNode = {
        node : node,
        subtrees : Array(),
        visibility : "showall",
        name : "",
        idx : 0,
      };

      if (node.is(osk().Subtree)) {
        result.name = window.module.cast_to_Subtree(node).getCleanTitle().toString();
      } else if (node.is(osk().Document)) {
        // result.name = window.module.cast_to_Document(node).getCleanTitle().toString(); 
      }

      for (var sub of node.subnodes.toArray()) {
        const sub_hierarchy = this.toTreeHierarchy(sub);
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
    await initWasmModule();
    const result = await window.electronAPI.readFile(this.conf.path);
    if (result.success) {
      console.log("Rendering tree hierarchy");
      const node      = window.module.parseString(result.data!);
      const hierarchy = this.toTreeHierarchy(node);
      console.log("Constructed tree hierarchy");
      if (hierarchy) {
        this.onLoadAll(hierarchy);
      }
    } else {
      console.log("Failed to construct");
      throw new Error(result.error);
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
                         this.conf.width,
                         this.conf.height,
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
    // console.log(`diagonal ${s.x} / ${s.y} ... ${d.x} / ${d.y}`)
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
    var   treeData          = this.treemap(this.root);
    var   nodes             = treeData.descendants();
    var   links             = treeData.descendants().slice(1);
    const minY              = d3.min(treeData.descendants(), d => d.x) ?? 0;
    const maxY              = d3.max(treeData.descendants(), d => d.x) ?? 0;
    const vertical_offset   = -minY + this.conf.height / 2;
    const horizontal_offset = 20;

    function fix_point(p: XYPoint): XYPoint {
      return {x : p.x + vertical_offset, y : p.y + horizontal_offset};
    }

    function format_point(p: XYPoint): string {
      const p1 = fix_point(p);
      // for unkown reasons `treeData` nodes layout layers are spaced out
      // vertically (several lanes with identical y, so I need to format the
      // nodes using this random code where y goes to x and vice versa).
      return `${(p1.y).toFixed(3)},${(p1.x).toFixed(3)}`;
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
                      return "translate(" + format_point(d) + ")";
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
          return "translate(" + format_point(d) + ")";
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
                                       return "translate(" + format_point({
                                                y : this.conf.y_offset!,
                                                x : this.conf.x_offset,
                                              })
                                              + ")";
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
                return this.diagonal(fix_point(o), fix_point(o));
              });

    // UPDATE
    var linkUpdate = linkEnter.merge(link);

    // Transition back to the parent element position
    linkUpdate.transition()
        .on("end", dump_html)
        // .duration(duration)
        .attr("d",
              (d: OrgHierarchyNode) => {return this.diagonal(
                  fix_point(d as XYPoint), fix_point(d.parent as XYPoint))});

    // Remove any exiting links
    var linkExit
        = link.exit()
              .transition()
              .on("end", dump_html)
              //  .duration(duration)
              .attr("d",
                    (d: OrgHierarchyNode) => {
                      var o = {x : this.conf.x_offset, y : this.conf.y_offset!};
                      return this.diagonal(fix_point(o), fix_point(o));
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
