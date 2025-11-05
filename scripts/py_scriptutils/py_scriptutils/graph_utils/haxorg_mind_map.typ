
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
  debug_text(repr((x, y)), color)
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

  let port_width = 8
  let port_height = 8
  let rect_x = 0
  let rect_y = 0

  // If the port has explicit width and height it is going to be properly offset
  // relative to the parent node. But if the port originally had no dimensions,
  // the ELK layout treats it as a zero-sized point.
  if "width" in port and "height" in port {
    port_width = port.at("width")
    port_height = port.at("height")
    rect_x = port_x - port_width / 2
    rect_y = port_y - port_height / 2
  } else {
    // Determine the placement of the port rectangle based on the port side
    if port_side == "WEST" {
      rect_x = port_x - port_width
      rect_y = port_y - port_height / 2
    } else if port_side == "EAST" {
      rect_x = port_x
      rect_y = port_y - port_height / 2
    } else if port_side == "NORTH" {
      rect_x = port_x - port_width / 2
      rect_y = port_y - port_height
    } else if port_side == "SOUTH" {
      rect_x = port_x - port_width / 2
      rect_y = port_y
    } else {
      // Default: center the rectangle
      rect_x = port_x - port_width / 2
      rect_y = port_y - port_height / 2
    }
  }

  // Draw the port rectangle
  place(
    dx: rect_x * 1pt - 1pt,
    dy: rect_y * 1pt - 1pt,
    stack(
      rect(
        width: port_width * 1pt,
        height: port_height * 1pt,
        stroke: black + 1pt,
        fill: white,
        // draw_arrow(direction, port_width, port_height),
      ),
      // Draw direction arrow inside the rectangle
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
    stack(node.subnodes.map(render_org).join(), dir: ltr)
  } else if kind == "Paragraph" {
    stack(render_subnodes(), dir: ltr)
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
  let label_text = if "text" in label { label.text } else { "" }

  let breakable-text(str) = str.clusters().join("\u{200B}")

  let fill-res = rgb("#F5F5DC")

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
          size: label.extra.font_size * 1pt,
          fill: black,
          breakable-text(label_text),
        ),
      ),
    ),
  )

  // Handle nested labels if they exist
  if "labels" in label and label.labels != none {
    for nested_label in label.labels {
      draw_label(nested_label)
    }
  }
}

#let draw_node_base(node, fill_color) = {
  rect(
    width: 100%,
    height: 100%,
    stroke: black + 2pt,
    fill: fill_color,
    radius: 5pt,
    stack(
      // Place ports inside this rectangle
      if "ports" in node {
        for port in node.ports {
          draw_port(port)
        }
      },
      if "labels" in node {
        for label in node.labels {
          draw_label(label)
        }
      },
    ),
  )
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
    dx: (node.x + x_offset) * 1pt,
    dy: (node.y + y_offset) * 1pt,
    box(
      width: node.width * 1pt,
      height: node.height * 1pt,
      body,
    ),
  )
}


#let draw_edge_with_polygon(edge_data) = {
  let polygon_points = edge_data.extra.data.data.polygon
  let typst_points = ()

  for point in polygon_points {
    typst_points.push((point.at(0) * 1pt, point.at(1) * 1pt))
  }

  let fill_style = gray.lighten(80%)

  if "pattern" in edge_data.extra.data.data {
    let palette = edge_data.extra.data.data.pattern.palette
    if palette.len() > 0 {
      let colors = palette.map(c => rgb(c.r, c.g, c.b))
      fill_style = if colors.len() == 1 {
        colors.at(0)
      } else {
        gradient.linear(..colors)
      }
    }
  }

  place(
    polygon(
      fill: fill_style,
      stroke: black + 1pt,
      ..typst_points,
    ),
  )
}

#let draw_edge_with_sections(edge_data) = {
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
        stroke: black + 1pt,
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
      and "data" in edge_data.extra
      and "data" in edge_data.extra.data
      and "polygon" in edge_data.extra.data.data
  ) {
    draw_edge_with_polygon(edge_data)
  } else if "sections" in edge_data {
    draw_edge_with_sections(edge_data)
  }
}



#let draw_node(node) = {
  node_box(node, draw_node_base(node, blue.lighten(80%)), 0, 0)
  // node.extra.data is `DiaGraph::SerialSchema`
  let data = node.extra.data
  let extra = data.extra
  if (
    "structuredDescription" in extra and extra.structuredDescription != none
  ) {
    node_box(
      node,
      box(width: 100%, height: 100%, inset: 4pt, text(size: 8pt, render_org(
        extra.structuredDescription,
      ))),
      0,
      0,
    )
  } else if "vertexDescription" in data {
    node_box(
      node,
      box(width: 100%, height: 100%, inset: 4pt, text(
        size: 8pt,
        data.vertexDescription,
      )),
      0,
      0,
    )
  } else if "vertexName" in data {
    node_box(
      node,
      box(width: 100%, height: 100%, inset: 4pt, text(
        size: 8pt,
        data.vertexName,
      )),
      0,
      0,
    )
  }

  if "children" in node {
    for subnode in node.children {
      node_box(node, draw_node(subnode), 0, 0)
    }
  }

  if "edges" in node {
    for edge in node.edges {
      node_box(node, draw_edge(edge), 0, 0)
    }
  }
}


