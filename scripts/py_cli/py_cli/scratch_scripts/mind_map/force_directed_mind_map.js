import {convertMindMapGraph} from "http://localhost:9555/js_source/utils.js";

// Define color scale
const colorScale =
    d3.scaleSequential()
        .domain([ 0, 10 ]) // input domain: levels range from 0 to 10
        .interpolator(
            d3.interpolateCool); // output range: color from warm to cool

// Define radius scale
const radiusScale =
    d3.scaleLinear()
        .domain([ 0, 10 ]) // input domain: levels range from 0 to 10
        .range([ 20, 2 ]); // output range: radius size from 20 to 2

d3.json("http://localhost:9555/get_mind_map/mind_map.org")
    .then(
        function(data) {
          // Specify the dimensions of the chart.
          const width = 1400;
          const height = 1400;

          var [nodes, links] = convertMindMapGraph(data);

          // Create the SVG container.
          const svg = d3.select("body")
                          .append("svg")
                          .attr("height", height)
                          .attr("width", width);

          // Add a line for each link, and a circle for each node.
          const link = svg.append("g")
                           .attr("stroke", "#999")
                           .attr("stroke-opacity", 0.6)
                           .selectAll("line")
                           .data(links)
                           .join("line")
                           .attr("stroke-width", d => Math.sqrt(d.value));

          const node = svg.append("g")
                           .attr("stroke", "#fff")
                           .attr("stroke-width", 1.5)
                           .selectAll("g")
                           .data(nodes)
                           .join("g");

          function clampStr(str, size) {
            if (!str) {
              return str;
            } else if (str.length < size) {
              return str;
            } else {
              return str.slice(0, size);
            }
          }

          node.append("circle")
              .attr("r", d => radiusScale(d.metadata.level))
              .attr("fill", d => colorScale(d.metadata.level))
              .append("title")
              .text(d => d.metadata.title);

          node.append("text")
              .attr("dx", d => d.metadata.isSubtree
                                   ? radiusScale(d.metadata.level) / 2 + 8
                                   : 40)
              .attr("dy", "0.35em") // Center text vertically
              .attr("stroke", "black")
              .attr("stroke-width", 0.7)
              .attr("font-weight", 10)
              .attr("font-size", "12px")
              .text(d => clampStr(d.metadata.title, 12));

          // Add a drag behavior.
          node.call(d3.drag()
                        .on("start", dragstarted)
                        .on("drag", dragged)
                        .on("end", dragended));

          var maxNodeWidth = 0;
          node.each(function() {
            const bbox = this.getBBox();
            if (bbox.width > maxNodeWidth) {
              maxNodeWidth = bbox.width;
            }
          });

          // Create a simulation with several forces.
          const simulation =
              d3.forceSimulation(nodes)
                  .force("link",
                         d3.forceLink(links).id(d => d.id).distance(300))
                  .force("center", d3.forceCenter(width / 2, height / 2))
                  .force("charge", d3.forceManyBody().strength(-maxNodeWidth))
                  .force("x", d3.forceX())
                  .force("y", d3.forceY());

          // Set the position attributes of links and nodes each time the
          // simulation ticks.
          simulation.on("tick", () => {
            link.attr("x1", d => d.source.x)
                .attr("y1", d => d.source.y)
                .attr("x2", d => d.target.x)
                .attr("y2", d => d.target.y);

            node.attr("transform", d => `translate(${d.x},${d.y})`);
          });

          // Reheat the simulation when drag starts, and fix the subject
          // position.
          function dragstarted(event) {
            if (!event.active)
              simulation.alphaTarget(0.3).restart();
            event.subject.fx = event.subject.x;
            event.subject.fy = event.subject.y;
          }

          // Update the subject (dragged node) position during drag.
          function dragged(event) {
            event.subject.fx = event.x;
            event.subject.fy = event.y;
          }

          // Restore the target alpha so the simulation cools after dragging
          // ends. Unfix the subject position now that it’s no longer being
          // dragged.
          function dragended(event) {
            if (!event.active)
              simulation.alphaTarget(0);
            event.subject.fx = null;
            event.subject.fy = null;
          }
        },
        function(err) { throw err; });
