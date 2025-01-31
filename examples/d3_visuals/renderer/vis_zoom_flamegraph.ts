import * as d3 from "d3";
import {Schema, string, z} from "zod";

import * as org from "./org_data.ts";
import {dump_html} from "./utils.ts";

class RangeClose {
  constructor(public start: Date, public end: Date) {}
}

export function lt_cmp(lhs, rhs): number {
  if (lhs < rhs) {
    return -1;
  } else {
    return 1;
  }
}

export function gt_cmp(lhs, rhs): number {
  if (lhs < rhs) {
    return -1;
  } else {
    return 1;
  }
}

class EventPoint {
  public point: Date|number;
  constructor(date: Date|number) { this.point = date; }

  isDate(): boolean { return this.point instanceof Date; }
  isNumber(): boolean { return typeof this.point == "number"; }

  public static readonly Schema = z.object({
    point : z.union([ z.date(), z.number() ]),
  });
}

function assert_zod<T>(value: T, schema) { schema.parse(value); }

function get_defined<T>(value: T|undefined|null,
                        errorMessage = "Value is not defined"): T {
  if (value === undefined || value === null) {
    throw new Error(errorMessage);
  }
  return value;
}

class Event {
  public static readonly Schema = z.object({
    name : z.string(),
    start: EventPoint.Schema,
    end: EventPoint.Schema,
  });

  constructor(
      public name: string,
      public start: EventPoint,
      public end: EventPoint,
      public completion: number|null = null,
      public type: string            = "one",
      public nested: Event[]         = Array(),
  ) {
    assert_zod(start, EventPoint.Schema);
    assert_zod(end, EventPoint.Schema);
    assert_zod(nested, z.array(Event.Schema));
  }
}

class Gantt {
  constructor(
      public events: Event[] = Array(),
  ) {}
}

class ZoomDatum {
  constructor(
      public start: EventPoint,
      public end: EventPoint,
      public type: string,
      public name: string,
      public index?: number,
  ) {
    assert_zod(start, EventPoint.Schema);
    assert_zod(end, EventPoint.Schema);
    assert_zod(type, z.string());
    assert_zod(name, z.string());
  }

  public static readonly Schema = z.object({
    start : EventPoint.Schema,
    end: EventPoint.Schema,
    type: z.string(),
    name: z.string(),
  });
}

export class ZoomFlamegraphVisualizationConfig {
  height: number              = 600;
  width: number               = 900;
  rect_size: number           = 10;
  brush_height: number        = 70;
  top_margin: number          = 40;
  right_margin: number        = 20;
  bottom_margin: number       = 20;
  left_margin: number         = 20;
  left_brush_margin: number   = 10;
  right_brush_margin: number  = 10;
  bottom_brush_margin: number = 10;

  get_brush_left_pos(): number {
    return this.left_margin + this.left_brush_margin;
  }

  get_brush_width(): number {
    return this.get_content_width() - this.left_brush_margin
           - this.right_brush_margin;
  }

  get_brush_top_pos(): number {
    return this.height - this.top_margin - this.brush_height;
  }

  get_content_width(): number {
    return this.width - this.left_margin - this.right_margin;
  }

  get_content_height(): number {
    return this.height - this.top_margin - this.bottom_margin;
  }
}

type XDomain
    = d3.ScaleTime<number, number, never>|d3.ScaleLinear<number, number>;

class ZoomUpdateState {
  tooltip: d3.Selection<HTMLDivElement, unknown, HTMLElement, any>;
  x_domain: XDomain;
  brush_x_domain: XDomain;
  brush_y_domain: d3.ScaleLinear<number, number, never>;
  y_domain: d3.ScaleBand<string>;
  area: d3.Selection<SVGGElement, ZoomDatum, HTMLElement, any>;
  zoom: d3.ZoomBehavior<Element, ZoomDatum>;
  context: d3.Selection<SVGGElement, ZoomDatum, HTMLElement, any>;
  focus: d3.Selection<SVGGElement, ZoomDatum, HTMLElement, any>;
  xAxis: d3.Axis<Date|d3.NumberValue>;
  brush: d3.BrushBehavior<ZoomDatum>;
}

export class ZoomFlamegraphVisualization {
  svg: d3.Selection<SVGSVGElement, ZoomDatum, HTMLElement, any>;

  programmaticZoom: boolean  = false;
  programmaticBrush: boolean = false;

  event_selector: string = ".event_rectangle";
  gantt?: Gantt;
  conf: ZoomFlamegraphVisualizationConfig

  state: ZoomUpdateState;

  convertTimeline(data: Gantt): ZoomDatum[] {
    function flatten(data: Event) {
      return [ data ].concat(data.nested.map(d => flatten(d)).flat(1));
    }

    var   flat     = data.events.map(d => flatten(d));
    const timeline = flat.flat(1).map(function(d: Event): ZoomDatum {
      var result = new ZoomDatum(
          d.start,
          d.end,
          d.type!,
          d.name,
      );

      return result;
    });

    var idx = 0;
    return timeline.sort((lhs, rhs) => gt_cmp(lhs.start.point, rhs.start.point))
        .map(d => ({...d, index : idx++}));
  }

  constructor(svg_element: string, conf: ZoomFlamegraphVisualizationConfig) {
    this.conf = conf;
    this.svg  = d3.select<SVGGElement, ZoomDatum>(`#${svg_element}`)
                    .append("svg")
                    .attr("height", this.conf.height)
                    .attr("width", this.conf.width);
  }

  rescaleForTransform() {
    this.state.area
        .selectAll(this.event_selector)
        // @ts-ignore
        .attr("transform", (d: ZoomDatum) => this.rectTransform(d));
    this.state.area.selectAll(this.event_selector)
        .attr("width",
              // @ts-ignore
              (d: ZoomDatum) => {return (this.state.x_domain(d.end.point)
                                         - this.state.x_domain(d.start.point))})
  }

  zoomed(e: any) {
    if (this.programmaticZoom) {
      this.programmaticZoom = false;
      return;
    }

    var t = e.transform;

    // Store the current zoom level and translation in local storage.
    localStorage.setItem("zoom", t.k);
    localStorage.setItem("translateX", t.x);
    localStorage.setItem("translateY", t.y);

    this.state.x_domain.domain(t.rescaleX(this.state.brush_x_domain).domain());
    this.rescaleForTransform();

    // @ts-ignore
    this.state.focus.select(".axis--x").call(this.state.xAxis);
    this.programmaticBrush = true;
    this.state.context.select(".brush").call(
        // @ts-ignore
        this.state.brush.move, this.state.x_domain.range().map(t.invertX, t));
  }

  async get_gantt(client: org.OrgClient, root: org.ImmUniqId): Promise<Gantt> {
    var res = new Gantt();
    var idx = 0;

    async function to_event(tree: org.ImmUniqId): Promise<Event> {
      var res = new Event(
          await client.getCleanSubtreeTitle({id : tree}),
          new EventPoint(idx),
          new EventPoint(idx + 1),
      );

      idx += 2;

      return res;
    }

    const size: number = await client.getSize({id : root});
    for (var idx = 0; idx < size; ++idx) {
      const subnode = await client.getSubnodeAt({id : root, index : idx});
      res.events.push(await to_event(subnode));
    }

    return res;
  }

  async render() {
    const client = await org.openClient(
        8089,
        "/home/haxscramper/tmp/org_trivial.org",
    );

    this.gantt = await this.get_gantt(client, await client.getRoot({}));
    this.update();
  }

  rectTransform(
      d: ZoomDatum,
  ) {
    return "translate(" + this.state.x_domain(d.start.point).toFixed(3) + ","
           + this.state.y_domain(d.type) + ")";
  };

  brushed(event: any) {
    if (this.programmaticBrush) {
      this.programmaticBrush = false;
      return;
    } else {
      var s = event.selection || this.state.brush_x_domain.range();

      this.state.x_domain.domain(
          s.map(this.state.brush_x_domain.invert, this.state.brush_x_domain));
      this.rescaleForTransform();

      // focus.select(".focus").attr("d", focus);
      // @ts-ignore
      this.state.focus.select(".axis--x").call(this.state.xAxis);
      this.programmaticZoom = true;
      this.svg.select(".zoom").call(
          // @ts-ignore
          this.state.zoom.transform,
          d3.zoomIdentity.scale(this.conf.width / (s[1] - s[0]))
              .translate(-s[0], 0),
      );

      localStorage.setItem("brushSelection", JSON.stringify(s));
    }
  }

  update_zoom_selector() {
    this.state.zoom = d3.zoom<Element, ZoomDatum>()
                          .scaleExtent([ 1, Infinity ])
                          .translateExtent([
                            [ 0, 0 ],
                            [
                              this.conf.get_content_width(),
                              this.conf.get_content_height(),
                            ]
                          ])
                          .extent([
                            [ 0, 0 ],
                            [
                              this.conf.get_content_width(),
                              this.conf.get_content_height(),
                            ]
                          ])
                          .on("zoom", (e: any) => this.zoomed(e));

    this.svg.append("rect")
        .attr("class", "zoom")
        .attr("width", this.conf.get_content_width())
        .attr("height", this.conf.get_content_height())
        .style("fill", "white")
        .attr(
            "transform",
            "translate(" + this.conf.left_margin + "," + this.conf.top_margin
                + ")",
            )
        // @ts-ignore
        .call(this.state.zoom);
  }

  update_event_rectangles(timeline: ZoomDatum[]) {

    var keyFunction = function(d: ZoomDatum) { return d.start.point + d.type; };

    var event_rectangles
        = this.state.area.selectAll(".event_rectangle")
              .data(timeline, keyFunction)
              .enter()
              .append("g")
              .attr("class", "event_rectangle")
              .attr("transform", (d: ZoomDatum) => this.rectTransform(d));

    const rectOffset = (d) => { return d.index * this.conf.rect_size; }

    const colorScale
        = d3.scaleOrdinal(d3.schemeCategory10);
    const randomColor
        = () => colorScale(Math.floor(Math.random() * 20).toString());

    event_rectangles
        .append("rect")

        .attr("y", d => rectOffset(d))
        .attr("height", function(d) { return 10; })
        .attr("width",
              (d: ZoomDatum) => {return (this.state.x_domain(d.end.point)
                                         - this.state.x_domain(d.start.point))})
        .style("fill", d => randomColor())
        .on("mouseover",
            (event: any, d: ZoomDatum) => {
              this.state.tooltip.style("left", event.pageX + "px")
                  .style("top", event.pageY + "px")
                  .style("display", "inline-block")
                  .html(
                      (d.name) + "<br> from :" + d.start.isDate()
                          ? ((d.start.point as Date).toISOString().slice(0, 19)
                             + "<br> to :"
                             + (d.end.point as Date).toISOString().slice(0, 19))
                          : (d.start.point.toString().slice(0, 19) + "<br> to :"
                             + d.end.point.toString().slice(0, 19)));
            })
        .on("mouseout",
            (d: ZoomDatum) => {this.state.tooltip.style("display", "none")});

    const tail_offset = 3;

    event_rectangles.append("text")
        .attr("y", d => rectOffset(d) - this.conf.rect_size * tail_offset)
        .text(d => d.name)
        .attr("text-anchor", "start")
        .attr("alignment-baseline", "middle")
        .attr("font-family", "Verdana, sans-serif")
        .attr("font-size", "14px")
        .attr("fill", "black");

    // Timeline annotation ticks
    event_rectangles.append("rect")
        .attr("x", -0.5)
        .attr("y", d => rectOffset(d) - this.conf.rect_size * tail_offset)
        .attr("height", d => this.conf.rect_size * tail_offset)
        .attr("stroke", "black")
        .attr("stroke-width", 0)
        .attr("width", 1)
        .attr("fill", "black");
  }

  restore_brush_selection() {
    var storedBrushSelection
        = localStorage.getItem("brushSelection")
              ? JSON.parse(localStorage.getItem("brushSelection")!) as number[]
              : this.state.brush_x_domain.range();

    var brushG
        = this.state.context.append("g")
              .attr("class", "brush")
              .call(this.state.brush)
              // @ts-ignore
              .call(this.state.brush.move, this.state.brush_x_domain.range());

    // Get stored zoom and pan values
    var storedZoom       = +localStorage.getItem("zoom")!;
    var storedTranslateX = +localStorage.getItem("translateX")!;
    var storedTranslateY = +localStorage.getItem("translateY")!;

    // If stored values exist, apply them to the SVG
    if (storedZoom && storedTranslateX && storedTranslateY) {
      console.log("Restoring zoom transform");
      this.svg.call(
          // @ts-ignore
          zoom.transform,
          d3.zoomIdentity.translate(storedTranslateX, storedTranslateY)
              .scale(storedZoom));
    }

    // If stored brush selection exists, apply it
    if (storedBrushSelection) {
      function clamp(domain: d3.ScaleTime<number, number>, value) {
        return Math.max(domain.range()[0], Math.min(domain.range()[1], value));
      }

      const clamped_selection = [
        clamp(this.state.brush_x_domain, storedBrushSelection[0]),
        clamp(this.state.brush_x_domain, storedBrushSelection[1])
      ];

      console.log("Restore brush selection", clamped_selection);
      // @ts-ignore
      // brushG.call(this.state.brush.move, clamped_selection);
    }
  }

  update() {
    this.state     = new ZoomUpdateState();
    const timeline = this.convertTimeline(this.gantt!);

    if (!(timeline.every(d => d.start.isDate())
          || timeline.every(d => d.start.isNumber()))) {
      throw new Error(
          "Either every timeline event must be a date, or every event must be a number");
    }

    const isTimeXDomain = timeline[0].start.isDate();

    // Define the div for the tooltip
    this.state.tooltip
        = d3.select("body").append("div").attr("class", "tooltip");

    const x_domain_range = [
      get_defined(d3.min(
          timeline, (d: ZoomDatum): Date|number => { return d.start.point; })),
      get_defined(d3.max(
          timeline, (d: ZoomDatum): Date|number => { return d.end.point; })),
    ];

    if (isTimeXDomain) {
      this.state.x_domain = d3.scaleTime().domain(x_domain_range).range([
        0, this.conf.get_content_width()
      ]);
    } else {
      this.state.x_domain = d3.scaleLinear().domain(x_domain_range).range([
        0, this.conf.get_content_width()
      ]);
    }

    if (isTimeXDomain) {
      this.state.brush_x_domain = d3.scaleTime().domain(x_domain_range).range([
        0, this.conf.get_brush_width()
      ]);
    } else {
      this.state.brush_x_domain
          = d3.scaleLinear().domain(x_domain_range).range([
              0, this.conf.get_brush_width()
            ]);
    }

    this.state.brush_y_domain
        = d3.scaleLinear().range([ this.conf.brush_height, 0 ]);

    this.state.y_domain
        = d3.scaleBand()
              .domain(timeline.map(function(entry) { return entry.type; }))
              .rangeRound([ this.conf.get_content_height(), 0 ]);

    // colors for each type
    var types      = [...new Set(timeline.map(item => item.type)) ];
    var colors     = d3.quantize(d3.interpolateSpectral, types.length);
    var type2color = {};
    types.forEach(function(
        element: string,
        index: number) { type2color[element] = colors[index] });

    this.state.focus
        = this.svg.append("g")
              .attr("class", "focus")
              .attr("transform", "translate(" + this.conf.left_margin + ","
                                     + this.conf.top_margin + ")");

    this.state.xAxis = d3.axisBottom(this.state.x_domain);
    var xAxis2       = d3.axisBottom(this.state.brush_x_domain);
    var yAxis        = d3.axisLeft(this.state.y_domain).tickSize(0);
    this.state.brush
        = d3.brushX<ZoomDatum>()
              .extent([
                [ 0, 0 ],
                [ this.conf.get_brush_width(), this.conf.brush_height ]
              ])
              .on("brush end", (e: any, d: ZoomDatum) => this.brushed(e));

    this.update_zoom_selector();
    this.svg.append("defs")
        .append("clipPath")
        .attr("id", "clip")
        .append("rect")
        .attr("width", this.conf.get_content_width())
        .attr("height", this.conf.get_content_height())

            this.state.area
        = this.svg.append("g")
              .attr("class", "clipped")
              .attr("width", this.conf.get_content_width())
              .attr("height", this.conf.get_content_height())
              .attr(
                  "transform",
                  "translate(" + this.conf.left_margin + ","
                      + this.conf.top_margin + ")",
              );

    this.update_event_rectangles(timeline);

    var brush_area = d3.area<ZoomDatum>()
                         .curve(d3.curveMonotoneX)
                         .x((d: ZoomDatum) => {
                           return this.state.brush_x_domain(d.start.point);
                         })
                         .y0(this.conf.brush_height)
                         .y1((d: ZoomDatum) => {
                           // @ts-ignore
                           return this.state.brush_y_domain(d.name);
                         });

    this.state.context
        = this.svg.append("g")
              .attr("class", "context")
              .attr("transform", "translate(" + this.conf.get_brush_left_pos()
                                     + "," + this.conf.get_brush_top_pos()
                                     + ")");

    this.state.brush_x_domain.domain(this.state.x_domain.domain());
    // @ts-ignore
    this.state.brush_y_domain.domain(this.state.y_domain.domain());

    this.state.focus.append("g")
        .attr("class", "axis axis--x")
        .attr("transform",
              "translate(0," + this.conf.get_content_height() + ")")
        .call(this.state.xAxis);

    this.state.focus.append("g").attr("class", "axis axis--y").call(yAxis);

    this.state.context.append("path")
        .datum(timeline)
        .attr("class", "area")
        .attr("d", brush_area);

    this.state.context.append("g")
        .attr("class", "axis axis--x")
        .attr("transform", "translate(0," + this.conf.brush_height + ")")
        .call(xAxis2);

    this.restore_brush_selection();

    dump_html();
  }
}
