// src/renderer/visualization.ts
import * as d3 from "d3";

import * as org from "./org_data.ts";
import {log} from "./org_logger.ts";

async function treeRepr(client: org.OrgClient, id: org.ImmUniqId, depth: number = 0) {
  log.info(" ".repeat(depth * 2) + `[${depth}] ${id.id.format}`)

  const size: number = await client.getSize({id : id});
  for (var idx = 0; idx < size; ++idx) {
    const subnode = await client.getSubnodeAt({id : id, index : idx})
                        await treeRepr(client, subnode, depth + 1);
  }
}

async function tree_repr_test() {
  const ws = new WebSocket("ws://localhost:8089");

  // Wait for connection
  await new Promise<void>(resolve =>
                              ws.addEventListener("open", () => resolve()));

  const client = org.createWebSocketClient(ws);
  client.setExceptionHandler({handler : true});

  await client.setRootFile({path : "/home/haxscramper/tmp/org_trivial.org"});

  const root = await client.getRoot({});
  log.info(`root: ${JSON.stringify(root)}`);

  await treeRepr(client, root, 0);
  log.info("done");
}

export class CircleVisualization {
  private svg: d3.Selection<SVGSVGElement, unknown, HTMLElement, any>;
  private data: number[];

  constructor(containerId: string, width: number = 400, height: number = 200) {
    this.data = Array.from({length : 5}, () => Math.random() * 100);

    this.svg = d3.select(`#${containerId}`)
                   .append("svg")
                   .attr("width", width)
                   .attr("height", height);
  }

  render(): void {
    log.info("Render");
    tree_repr_test();
    this.svg.selectAll("circle")
        .data(this.data)
        .join("circle")
        .attr("cx", (d: number, i: number) => i * 80 + 40)
        .attr("cy", 100)
        .attr("r", (d: number) => d / 4)
        .style("fill", "steelblue")
        .on("mouseover",
            function(this: SVGCircleElement) {
              d3.select(this).transition().duration(200).style("fill", "red");
            })
        .on("mouseout", function(this: SVGCircleElement) {
          d3.select(this).transition().duration(200).style("fill", "steelblue");
        });
  }
}
