
#let debug_text(text_in, color) = {
  place(
    top + left,
    dx: 0pt,
    dy: 0pt,
    text(
      size: 2pt,
      fill: color,
      weight: "bold",
      text_in,
    ),
  )
}

#let debug_point(x, y, color) = {
  place(
    top + left,
    dx: 0pt,
    dy: 0pt,
    circle(radius: 0.5pt, fill: color),
  )
  debug_text(repr((x, y)), blue)
}

#let debug_abs_point(x, y, color) = {
  place(
    dx: x * 1pt,
    dy: y * 1pt,
    debug_point(x, y, color),
  )
}

#let draw_port(port) = {
  let port_x = port.at("x", default: 0)
  let port_y = port.at("y", default: 0)
  let direction = port
    .at("extra", default: (:))
    .at("data", default: (:))
    .at("data", default: (:))
    .at("direction", default: "")
  let port_side = port
    .at("properties", default: (:))
    .at("port_side", default: "")

  let port_width = port.at("width", default: 8)
  let port_height = port.at("height", default: 8)
  let rect_x = port_x
  let rect_y = port_y

  place(
    dx: port_x * 1pt,
    dy: port_y * 1pt,
    stack(
      rect(
        width: port_width * 1pt,
        height: port_height * 1pt,
        // stroke: black + 1pt,
        fill: gray.lighten(50%),
      ),
    ),
  )

  if "labels" in port {
    for label in port.labels {
      place(
        dx: port_x * 1pt,
        dy: port_y * 1pt,
        draw_label(label),
      )
    }
  }
}

#let render_org(node) = {
  let kind = node.kind

  let subnodes = node.at("subnodes", default: ())

  // Helper function to render all subnodes
  let render_subnodes() = {
    if subnodes != () {
      subnodes.map(subnode => render_org(subnode)).join()
    }
  }

  let render_subnodes_wo_newlines() = {
    if subnodes != () {
      subnodes
        .filter(subnode => subnode.kind != "Newline")
        .map(subnode => render_org(subnode))
        .join()
    }
  }

  if (
    kind == "Space"
      or kind == "BigIdent"
      or kind == "Word"
      or kind == "Newline"
      or kind == "Punctuation"
      or kind == "RawText"
  ) {
    node.text
  } else if kind == "Bold" {
    strong(node.subnodes.map(render_org).join())
  } else if kind == "Verbatim" {
    raw(node.subnodes.map(it => it.text).join())
  } else if kind == "Monospace" {
    raw(node.subnodes.map(it => it.text).join())
  } else if kind == "Paragraph" {
    par(render_subnodes())
  } else if kind == "Italic" {
    emph(node.subnodes.map(render_org).join())
  } else if kind == "Underline" {
    underline(node.subnodes.map(render_org).join())
  } else if kind == "List" {
    list(..node.subnodes.map(render_org))
  } else if kind == "BlockDynamicFallback" {
    if (node.name == "description") {
      stack(render_subnodes_wo_newlines())
    }
  } else {
    // Fallback for unknown node types
    [Unknown node type: #kind, #debug_text(repr(node), red)]
  }
}

#let draw_label(label) = {
  let label_x = if "x" in label { label.x * 1pt } else { 0pt }
  let label_y = if "y" in label { label.y * 1pt } else { 0pt }
  let label_width = if "width" in label { label.width * 1pt } else { auto }
  let label_height = if "height" in label { label.height * 1pt } else { auto }

  let breakable-text(str) = str.clusters().join("\u{200B}")

  let draw_label(fill-res, body) = {
    place(
      dx: label_x,
      dy: label_y,
      rect(
        width: label_width,
        height: label_height,
        fill: fill-res,
        radius: 2pt,
        inset: 2pt,
        place(
          center + horizon,
          text(
            size: label.extra.label_geometry.font_size * 1pt,
            fill: black,
            body,
          ),
        ),
      ),
    )
  }

  if "haxorg_edge_extra" in label.extra {
    let extra = label.extra.haxorg_edge_extra
    draw_label(red.lighten(60%), stack(
      if "structuredEdgeDetailed" in extra {
        render_org(extra.structuredEdgeDetailed)
      } else if "edgeDetailed" in extra {
        text(extra.edgeDetailed)
      },
      if "structuredEdgeBrief" in extra {
        render_org(extra.structuredEdgeBrief)
      } else if "edgeBrief" in extra {
        text(extra.edgeBrief)
      },
    ))
  } else if "text" in label {
    draw_label(rgb("#F5F5DC"), breakable-text(label.text))
  }

  // Handle nested labels if they exist
  if "labels" in label and label.labels != none {
    for nested_label in label.labels {
      draw_label(nested_label)
    }
  }
}


#let box_at(..args) = {
  place(
    dx: args.at("x") * 1pt,
    dy: args.at("y") * 1pt,
    box(
      inset: args.at("inset", default: 0pt),
      width: args.at("width") * 1pt,
      height: args.at("height") * 1pt,
      place(
        args.at("body"),
      ),
    ),
  )
}


#let node_box(node, body, x_offset, y_offset) = {
  place(
    dx: (node.at("x", default: 0) + x_offset) * 1pt,
    dy: (node.at("y", default: 0) + y_offset) * 1pt,
    box(
      width: node.width * 1pt,
      height: node.height * 1pt,
      body,
    ),
  )
}

#let node_place(node, body, x_offset, y_offset) = {
  place(
    dx: (node.at("x", default: 0) + x_offset) * 1pt,
    dy: (node.at("y", default: 0) + y_offset) * 1pt,
    body,
  )
}

#let draw_node_ports(node) = {
  if "ports" in node {
    for port in node.ports {
      node_place(node, draw_port(port), 0, 0)
    }
  }
}


#let map_draw_command(cmd) = {
  if cmd.type == "line" {
    curve.line((cmd.x * 1pt, cmd.y * 1pt))
  } else if cmd.type == "move" {
    curve.move((cmd.x * 1pt, cmd.y * 1pt))
  } else if cmd.type == "close" {
    curve.close()
  } else if cmd.type == "quad" {
    curve.quad(
      (cmd.control_x * 1pt, cmd.control_y * 1pt),
      (cmd.x * 1pt, cmd.y * 1pt),
    )
  } else {
    curve.cubic(
      (cmd.control_start_x * 1pt, cmd.control_start_y * 1pt),
      (cmd.control_end_x * 1pt, cmd.control_end_y * 1pt),
      (cmd.x * 1pt, cmd.y * 1pt),
    )
  }
}

#let draw_edge_with_polygon(edge_data) = {
  let hyperedge = edge_data.extra.elk_extra.hyperedge
  let fill_style = gray.lighten(50%)

  place(
    curve(
      fill: fill_style,
      // stroke: black + 1pt,
      ..hyperedge.drawing.map(p => map_draw_command(p)),
    ),
  )
}

#let draw_edge_with_sections(edge_data) = {
  if "labels" in edge_data {
    let section0 = edge_data.sections.at(0)
    for label in edge_data.labels {
      place(
        dx: section0.startPoint.x * 1pt,
        dy: section0.startPoint.y * 1pt,
        draw_label(label),
      )
    }
  }


  for section in edge_data.sections {
    let start = section.at("startPoint")
    let end = section.at("endPoint")

    let curve_elements = ()

    if "bendPoints" in section {
      let points = (start,) + section.at("bendPoints") + (end,)

      curve_elements.push(curve.line((
        points.at(0).at("x") * 1pt,
        points.at(0).at("y") * 1pt,
      )))

      for i in range(1, points.len()) {
        let point = points.at(i)
        curve_elements.push(curve.line((
          point.at("x") * 1pt,
          point.at("y") * 1pt,
        )))
      }
    } else {
      curve_elements.push(curve.line((
        start.at("x") * 1pt,
        start.at("y") * 1pt,
      )))
      curve_elements.push(curve.line((end.at("x") * 1pt, end.at("y") * 1pt)))
    }

    place(
      curve(
        stroke: black + 0.5pt,
        curve.move((start.x * 1pt, start.y * 1pt)),
        ..curve_elements,
      ),
    )
  }
}

#let draw_edge(edge_data) = {
  // Check if hyperedge polygon is specified
  if (
    "extra" in edge_data
      and "elk_extra" in edge_data.extra
      and "hyperedge" in edge_data.extra.elk_extra
  ) {
    draw_edge_with_polygon(edge_data)
  } else if "sections" in edge_data {
    draw_edge_with_sections(edge_data)
  }
}


#let draw_node_description_body(node, body) = {
  node_box(
    node,
    box(width: 100%, height: 100%, inset: 4pt, box(
      width: 100%,
      height: 100%,
      clip: true,
      text(
        size: 8pt,
        body,
      ),
    )),
    0,
    0,
  )
}

#let get_node_color(node) = {
  if "haxorg_vertex" in node.extra {
    if "todoState" in node.extra.haxorg_vertex.extra {
      let state = node.extra.haxorg_vertex.extra.todoState
      if state == "TODO" {
        yellow
      } else if state == "DONE" or state == "COMPLETED" {
        green
      } else if state == "WIP" {
        orange
      } else if state == "FAILED" {
        red
      } else {
        blue
      }
    } else {
      blue
    }
  } else if "haxorg_label_edge" in node.extra {
    purple
  } else {
    blue
  }
}

#let get_depth_lighten_percent(node) = {
  if "haxorg_vertex" in node.extra {
    if "nestingLevel" in node.extra.haxorg_vertex.extra {
      90% - node.extra.haxorg_vertex.extra.nestingLevel * 10%
    } else {
      80%
    }
  } else {
    90%
  }
}

#let draw_nested_subtrees(nested_subtrees) = {
  if nested_subtrees.len() == 0 {
    return none
  }

  let process_subtree(subtree) = {
    let rows = ()

    // First column: just asterisk (no indentation)
    let col1 = "*"

    // Second column: todo state or empty
    let col2 = if subtree.at("todoState", default: none) != none {
      subtree.todoState
    } else {
      ""
    }

    // Third column: structured name or regular name
    let col3 = if subtree.at("structuredName", default: none) != none {
      render_org(subtree.structuredName)
    } else {
      text(size: 8pt, subtree.name)
    }

    rows.push((col1, col2, col3))

    // Process nested subtrees recursively
    if subtree.at("nested", default: ()).len() > 0 {
      for nested in subtree.nested {
        rows = rows + process_subtree(nested)
      }
    }

    return rows
  }

  // Collect all rows
  let all_rows = ()
  for subtree in nested_subtrees {
    all_rows = all_rows + process_subtree(subtree)
  }

  // Create and return the table
  table(
    columns: 3,
    stroke: none,
    align: (left, center, left),
    ..all_rows.flatten()
  )
}

#let draw_node_base(node, fill_color) = {
  node_box(
    node,
    rect(
      width: 100%,
      height: 100%,
      stroke: (paint: gray.lighten(50%), thickness: 1.5pt, dash: "dashed"),
      fill: fill_color,
      radius: 5pt,
    ),
    0,
    0,
  )

  if "labels" in node {
    for label in node.labels {
      node_place(node, draw_label(label), 0, 0)
    }
  }
}

#let draw_node_description(node) = {
  if "haxorg_vertex" in node.extra {
    // node.extra.data is `DiaGraph::SerialSchema`
    let data = node.extra.haxorg_vertex
    let extra = data.extra


    draw_node_description_body(node, stack(
      if (
        "structuredDescription" in extra and extra.structuredDescription != none
      ) {
        render_org(
          extra.structuredDescription,
        )
      } else if "vertexDescription" in data {
        text(
          size: 8pt,
          data.vertexDescription,
        )
      } else if "structuredName" in extra and extra.structuredName != none {
        render_org(
          extra.structuredName,
        )
      } else if "vertexName" in data {
        text(
          size: 8pt,
          data.vertexName,
        )
      },
      if "nestedSubtrees" in extra {
        pad(top: 2pt, draw_nested_subtrees(extra.nestedSubtrees))
      },
    ))
  } else if "haxorg_label_edge" in node.extra {
    let original_edge_data = node.extra.haxorg_label_edge
    let edge_extra = original_edge_data.extra
    text(size: 8pt, draw_node_description_body(node, stack(
      if "structuredEdgeBrief" in edge_extra {
        render_org(edge_extra.structuredEdgeBrief)
      } else if "edgeBrief" in edge_extra {
        text(edge_extra.edgeBrief)
      },
      if "structuredEdgeDetailed" in edge_extra {
        render_org(edge_extra.structuredEdgeDetailed)
      } else if "edgeDetailed" in edge_extra {
        text(edge_extra.edgeDetailed)
      },
    )))
  }
}

#let draw_node_nested_edges(node) = {
  if "edges" in node {
    for edge in node.edges {
      node_place(node, draw_edge(edge), 0, 0)
    }
  }
}

#let draw_node(node) = {
  draw_node_base(
    node,
    get_node_color(node).lighten(get_depth_lighten_percent(node)),
  )

  draw_node_description(node)

  if "children" in node {
    for subnode in node.children {
      node_place(node, draw_node(subnode), 0, 0)
    }
  }

  draw_node_nested_edges(node)
  draw_node_ports(node)
}


