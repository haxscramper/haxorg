import * as d3 from "d3";

import * as org from "./org_data.ts";
import {dump_html} from "./utils.ts";

class RangeClose {
  constructor(public start: Date, public end: Date) {}
}

function get_defined<T>(value: T|undefined|null,
                        errorMessage = "Value is not defined"): T {
  if (value === undefined || value === null) {
    throw new Error(errorMessage);
  }
  return value;
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

class Event {
  constructor(
      public start: Date,
      public end: Date,
      public name: string,
      public completion?: number,
      public type: string        = "one",
      public nested: Event[]     = Array(),
      public hasHours: boolean   = true,
      public hasMinute: boolean  = true,
      public hasSeconds: boolean = true,
  ) {}
}

class Gantt {
  constructor(
      public title?: string,
      public dateFormat?: string,
      public today?: Date,
      public printScale?: string,
      public projectStart?: Date,
      public projectEnd?: Date,
      public legend?: string,
      public events: Event[] = Array(),
  ) {}
}

class ZoomDatum {
  constructor(
      public startdate: Date,
      public enddate: Date,
      public type: string,
      public name: string,
      public index?: number,
  ) {}
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

export class ZoomFlamegraphVisualization {
  svg: d3.Selection<SVGSVGElement, ZoomDatum, HTMLElement, any>;

  programmaticZoom: boolean  = false;
  programmaticBrush: boolean = false;

  event_selector: string    = ".event_rectangle";
  scalable_selector: string = this.event_selector + ",.data_overlay";
  gantt?: Gantt;
  conf: ZoomFlamegraphVisualizationConfig

  convertTimeline(data: Gantt): ZoomDatum[] {
    function flatten(data) {
      return [ data ].concat(data.nested.map(d => flatten(d)).flat(1));
    }

    var   flat     = data.events.map(d => flatten(d));
    const timeline = flat.flat(1).map(function(d: Event): ZoomDatum {
      var result = new ZoomDatum(
          new Date(d.start),
          new Date(d.end),
          d.type,
          d.name,
      );

      if (d.start_date_only && d.stop_date_only) {
        result.enddate.setHours(23, 59, 59);
      }

      return result;
    });

    var idx = 0;
    return timeline.sort((lhs, rhs) => gt_cmp(lhs.startdate, rhs.startdate))
        .map(d => ({...d, index : idx++}));
  }

  constructor(svg_element: string, conf: ZoomFlamegraphVisualizationConfig) {
    this.conf = conf;
    this.svg  = d3.select<SVGGElement, ZoomDatum>(`#${svg_element}`)
                    .append("svg")
                    .attr("height", this.conf.height)
                    .attr("width", this.conf.width);
  }

  rescaleForTransform(
      x: d3.ScaleTime<number, number, never>,
      y: d3.ScaleBand<string>,
      area: d3.Selection<SVGGElement, ZoomDatum, HTMLElement, any>,
  ) {
    area.selectAll(this.scalable_selector)
        // @ts-ignore
        .attr("transform", (d: ZoomDatum) => this.rectTransform(d, x, y));
    area.selectAll(this.event_selector)
        .attr("width",
              // @ts-ignore
              (d: ZoomDatum) => {return (x(d.enddate) - x(d.startdate))})
  }

  zoomed(
      e: any,
      x: d3.ScaleTime<number, number, never>,
      y: d3.ScaleBand<string>,
      brush_x_domain: d3.ScaleTime<number, number, never>,
      area: d3.Selection<SVGGElement, ZoomDatum, HTMLElement, any>,
      focus: d3.Selection<SVGGElement, ZoomDatum, HTMLElement, any>,
      xAxis: any,
      context: d3.Selection<SVGGElement, ZoomDatum, HTMLElement, any>,
      brush: d3.BrushBehavior<ZoomDatum>,
  ) {
    if (this.programmaticZoom) {
      this.programmaticZoom = false;
      return;
    }

    var t = e.transform;

    // Store the current zoom level and translation in local storage.
    localStorage.setItem("zoom", t.k);
    localStorage.setItem("translateX", t.x);
    localStorage.setItem("translateY", t.y);

    x.domain(t.rescaleX(brush_x_domain).domain());
    this.rescaleForTransform(x, y, area);

    focus.select(".axis--x").call(xAxis);
    this.programmaticBrush = true;
    // @ts-ignore
    context.select(".brush").call(brush.move, x.range().map(t.invertX, t));
  }

  async get_gantt(client: org.OrgClient, root: org.ImmUniqId): Promise<Gantt> {
    var res = new Gantt();
    res.events.push(new Event(new Date("2025-01-26T16:00:00"),
                              new Date("2025-01-26T16:30:00"), "test1-1",
                              undefined, "one"));

    res.events.push(new Event(new Date("2025-01-26T17:00:00"),
                              new Date("2025-01-26T17:30:00"), "test1-2",
                              undefined, "one"));

    res.events.push(new Event(new Date("2025-01-26T17:00:00"),
                              new Date("2025-01-26T17:30:00"), "test2-1",
                              undefined, "two"));

    res.events.push(new Event(new Date("2025-01-26T18:00:00"),
                              new Date("2025-01-26T18:30:00"), "test2-2",
                              undefined, "two"));

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
      x: d3.ScaleTime<number, number, never>,
      y: d3.ScaleBand<string>,
  ) {
    return "translate(" + x(d.startdate).toFixed(3) + "," + y(d.type) + ")";
  };

  brushed(
      event: any,
      x_domain: d3.ScaleTime<number, number, never>,
      y_domain: d3.ScaleBand<string>,
      area: d3.Selection<SVGGElement, ZoomDatum, HTMLElement, any>,
      brush_x_domain: d3.ScaleTime<number, number, never>,
      zoom: d3.ZoomBehavior<Element, ZoomDatum>,
      xAxis: d3.Axis<Date|d3.NumberValue>,
      focus: d3.Selection<SVGGElement, ZoomDatum, HTMLElement, any>,
  ) {
    if (this.programmaticBrush) {
      this.programmaticBrush = false;
      return;
    } else {
      var s = event.selection || brush_x_domain.range();

      x_domain.domain(s.map(brush_x_domain.invert, brush_x_domain));
      this.rescaleForTransform(x_domain, y_domain, area);

      // focus.select(".focus").attr("d", focus);
      // @ts-ignore
      focus.select(".axis--x").call(xAxis);
      this.programmaticZoom = true;
      this.svg.select(".zoom").call(
          // @ts-ignore
          zoom.transform,
          d3.zoomIdentity.scale(this.conf.width / (s[1] - s[0]))
              .translate(-s[0], 0),
      );

      localStorage.setItem("brushSelection", JSON.stringify(s));
    }
  }

  update() {
    const timeline = this.convertTimeline(this.gantt!);
    // To get the event positio05
    var keyFunction = function(d) { return d.startdate + d.type; };
    // Define the div for the tooltip
    var tooltip = d3.select("body").append("div").attr("class", "tooltip")

    var x_domain
        = d3.scaleTime()
              .domain([
                get_defined(d3.min(
                    timeline, (d: ZoomDatum): Date => { return d.startdate; })),
                get_defined(d3.max(
                    timeline, (d: ZoomDatum): Date => { return d.enddate; })),
              ])
              .range([ 0, this.conf.get_content_width() ]);

    var brush_x_domain
        = d3.scaleTime().range([ 0, this.conf.get_brush_width() ]);
    // y = d3.scaleOrdinal().range([height, 0]),
    var brush_y_domain = d3.scaleLinear().range([ this.conf.brush_height, 0 ]);

    var y_domain
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

    var focus = this.svg.append("g")
                    .attr("class", "focus")
                    .attr("transform", "translate(" + this.conf.left_margin
                                           + "," + this.conf.top_margin + ")");

    var xAxis  = d3.axisBottom(x_domain);
    var xAxis2 = d3.axisBottom(brush_x_domain);
    var yAxis  = d3.axisLeft(y_domain).tickSize(0);
    var brush  = d3.brushX<ZoomDatum>()
                    .extent([
                      [ 0, 0 ],
                      [ this.conf.get_brush_width(), this.conf.brush_height ]
                    ])
                    .on("brush end", (e: any, d: ZoomDatum) => this.brushed(
                                         e,
                                         x_domain,
                                         y_domain,
                                         area,
                                         brush_x_domain,
                                         zoom,
                                         xAxis,
                                         focus,
                                         ));
    var zoom
        = d3.zoom<Element, ZoomDatum>()
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
              .on("zoom",
                  (e: any) => this.zoomed(e, x_domain, y_domain, brush_x_domain,
                                          area, focus, xAxis, context, brush));

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
        .call(zoom);

    this.svg.append("defs")
        .append("clipPath")
        .attr("id", "clip")
        .append("rect")
        .attr("width", this.conf.get_content_width())
        .attr("height", this.conf.get_content_height())

    var area = this.svg.append("g")
                   .attr("class", "clipped")
                   .attr("width", this.conf.get_content_width())
                   .attr("height", this.conf.get_content_height())
                   .attr(
                       "transform",
                       "translate(" + this.conf.left_margin + ","
                           + this.conf.top_margin + ")",
                   );

    var event_rectangles
        = area.selectAll(".event_rectangle")
              .data(timeline, keyFunction)
              .attr("class", "event_rectangle")
              .enter()
              .append("g")
              .attr("transform", (d: ZoomDatum) => this.rectTransform(
                                     d, x_domain, y_domain));

    const rectOffset = (d) => { return d.index * this.conf.rect_size; }

    const colorScale
        = d3.scaleOrdinal(d3.schemeCategory10);
    const randomColor
        = () => colorScale(Math.floor(Math.random() * 20).toString());

    event_rectangles
        .append("rect")

        .attr("y", d => rectOffset(d))
        .attr("height", function(d) { return 10; })
        .attr("width", (d: ZoomDatum) => {return (x_domain(d.enddate)
                                                  - x_domain(d.startdate))})
        .style("fill", d => randomColor())
        .on("mouseover",
            (event: any, d: ZoomDatum) => {
              tooltip.style("left", event.pageX + "px")
                  .style("top", event.pageY + "px")
                  .style("display", "inline-block")
                  .html((d.name)
                        + "<br> from :" + d.startdate.toISOString().slice(0, 19)
                        + "<br> to :" + d.enddate.toISOString().slice(0, 19));
            })
        .on("mouseout",
            function(d: ZoomDatum) { tooltip.style("display", "none") });

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

    var area2
        = d3.area<ZoomDatum>()
              .curve(d3.curveMonotoneX)
              .x((d: ZoomDatum) => { return brush_x_domain(d.startdate); })
              .y0(this.conf.brush_height)
              // @ts-ignore
              .y1((d: ZoomDatum) => { return brush_y_domain(d.name); });

    var context = this.svg.append("g")
                      .attr("class", "context")
                      .attr("transform",
                            "translate(" + this.conf.get_brush_left_pos() + ","
                                + this.conf.get_brush_top_pos() + ")");

    brush_x_domain.domain(x_domain.domain());
    brush_y_domain.domain(y_domain.domain());

    focus.append("g")
        .attr("class", "axis axis--x")
        .attr("transform",
              "translate(0," + this.conf.get_content_height() + ")")
        .call(xAxis);

    focus.append("g").attr("class", "axis axis--y").call(yAxis);

    context.append("path")
        .datum(timeline)
        .attr("class", "area")
        .attr("d", area2);

    context.append("g")
        .attr("class", "axis axis--x")
        .attr("transform", "translate(0," + this.conf.brush_height + ")")
        .call(xAxis2);

    var storedBrushSelection
        = localStorage.getItem("brushSelection")
              ? JSON.parse(localStorage.getItem("brushSelection")!) as number[]
              : brush_x_domain.range();

    var brushG = context.append("g")
                     .attr("class", "brush")
                     .call(brush)
                     // @ts-ignore
                     .call(brush.move, brush_x_domain.range());

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
        clamp(brush_x_domain, storedBrushSelection[0]),
        clamp(brush_x_domain, storedBrushSelection[1])
      ];

      console.log("Restore brush selection", clamped_selection);
      // @ts-ignore
      brushG.call(brush.move, clamped_selection);
    }

    dump_html();
  }
}
