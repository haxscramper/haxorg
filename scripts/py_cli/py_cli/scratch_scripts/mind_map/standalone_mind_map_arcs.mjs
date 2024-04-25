import {convertMindMapGraph} from "/utils.mjs";

const margin = ({top : 20, right : 20, bottom : 20, left : 1000});

function arc(d) {
  const y1 = d.source.y;
  const y2 = d.target.y;
  const r = Math.abs(y2 - y1) / 2;
  return `M${margin.left},${y1}A${r},${r} 0,0,${y1 < y2 ? 0 : 1} ${
      margin.left},${y2}`;
}

const svgStyle = `

.hover path {
  stroke: #ccc;
}

.hover text {
  fill: #ccc;
}

.hover g.primary text {
  fill: black;
  font-weight: bold;
}

.hover g.secondary text {
  fill: #333;
}

.hover path.primary {
  stroke: #333;
  stroke-opacity: 1;
}

`;

function convertToArcMap(data) {
  var [base_nodes, base_links] = convertMindMapGraph(data);

  const nodes = base_nodes.map((d) => ({
                                 id : d.id,
                                 sourceLinks : [],
                                 targetLinks : [],
                                 metadata : d.metadata,
                                 group : 1
                               }));

  console.log(base_nodes);

  const nodeById = new Map(nodes.map(d => [d.id, d]));

  const links = base_links.map(({source, target, value}) => ({
                                 source : nodeById.get(source),
                                 target : nodeById.get(target),
                                 value
                               }));

  for (const link of links) {
    const {source, target, value} = link;
    source.sourceLinks.push(link);
    target.targetLinks.push(link);
  }

  return [ nodes, links ];
}

function impl(data) {
  // Specify the dimensions of the chart.
  const width = 1400;

  var [nodes, links] = convertToArcMap(data);

  const step = 14;
  const height = (nodes.length - 1) * step + margin.top + margin.bottom;

  const svg = d3.select("body")
                  .append("svg")
                  .attr("height", height)
                  .attr("width", width);

  svg.append("style").text(svgStyle);

  const y = d3.scalePoint(nodes.map(d => Number(d.id)).sort(d3.ascending),
                          [ margin.top, height - margin.bottom ]);
  const color = d3.scaleOrdinal(nodes.map(d => d.group).sort(d3.ascending),
                                d3.schemeCategory10)

  const label =
      svg.append("g")
          .attr("font-family", "sans-serif")
          .attr("font-size", 10)
          .selectAll("g")
          .data(nodes)
          .join("g")
          .attr("transform",
                d => `translate(${margin.left},${d.y = y(Number(d.id))})`)
          .call(g => g.append("text")
                         .attr("x", 15)
                         .attr("dy", "0.35em")
                         .attr("fill", d => d3.lab(color(d.group)).darker(2))
                         .text(d => d.metadata.title))
          .call(g => g.append("circle").attr("r", 3).attr("fill",
                                                          d => color(d.group)));

  const path = svg.insert("g", "*")
                   .attr("fill", "none")
                   .attr("stroke-opacity", 0.6)
                   .attr("stroke-width", 1.5)
                   .selectAll("path")
                   .data(links)
                   .join("path")
                   .attr("stroke", d => d.source.group === d.target.group
                                            ? color(d.source.group)
                                            : "#aaa")
                   .attr("d", arc);
}

export function onLoadFromLocalhost(filename, port) {
  d3.json(`http://localhost:${port}/get_mind_map/${filename}`)
      .then(function(data) { impl(data); }, function(err) { throw err; });
}
