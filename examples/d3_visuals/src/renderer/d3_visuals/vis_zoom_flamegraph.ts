import * as d3 from "d3";
import {array, Schema, string, z} from "zod";

import * as org from "../org_data.ts";

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

class OrgSubtreeEvent {
  public self_size: number         = 0;
  public nested: OrgSubtreeEvent[] = Array();
  public title: string;

  get_full_size(): number {
    var res = this.self_size;
    for (var sub of this.nested) {
      res += sub.get_full_size();
    }
    return res;
  }

  static async from_id(client: org.OrgClient,
                       id: org.ImmUniqId): Promise<OrgSubtreeEvent> {
    var               res = new OrgSubtreeEvent();
    res.title             = await client.getCleanSubtreeTitle({id : id});
    res.self_size         = 1;

    const subnodes: org.ImmUniqId[] = await client.getAllSubnodes({id : id});

    for (var subnode of subnodes) {
      if ((subnode as org.ImmUniqId).id.format.startsWith("Subtree")) {
        res.nested.push(await this.from_id(client, subnode));
      }
    }

    return res;
  }
}

class Event {
  public static readonly Schema = z.object({
    name : z.string(),
    start: EventPoint.Schema,
    end: EventPoint.Schema,
    layer: z.number(),
  });

  constructor(
      public name: string,
      public start: EventPoint,
      public end: EventPoint,
      public layer: number,
      public type: string    = "one",
      public nested: Event[] = Array(),
  ) {
    assert_zod(start, EventPoint.Schema);
    assert_zod(end, EventPoint.Schema);
    assert_zod(nested, z.array(Event.Schema));
    assert_zod(layer, z.number());
  }

  static from_org_subtree(tree: OrgSubtreeEvent[]): Event[] {
    var      res: Event[] = Array();
    var      start        = 0;
    function aux(event: OrgSubtreeEvent, event_layer: number) {
      const this_start = start;
      start += event.self_size;
      for (var sub of event.nested) {
        aux(sub, event_layer + 1);
      }

      res.push(new Event(
          event.title,
          new EventPoint(this_start),
          new EventPoint(start),
          event_layer,
          "one",
          ));
    }

    for (var t of tree) {
      aux(t, 0);
    }

    return res;
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
      public layer: number,
  ) {
    assert_zod(start, EventPoint.Schema);
    assert_zod(end, EventPoint.Schema);
    assert_zod(type, z.string());
    assert_zod(name, z.string());
    assert_zod(layer, z.number());
  }

  public static readonly Schema = z.object({
    start : EventPoint.Schema,
    end: EventPoint.Schema,
    type: z.string(),
    name: z.string(),
    layer: z.number(),
  });
}

export class ZoomFlamegraphVisualizationConfig {
  height: number                      = 900;
  width: number                       = 900;
  rect_height: number                 = 20;
  brush_height: number                = 70;
  top_margin: number                  = 40;
  right_margin: number                = 20;
  bottom_margin: number               = 20;
  left_margin: number                 = 20;
  left_brush_margin: number           = 10;
  right_brush_margin: number          = 10;
  bottom_brush_margin: number         = 10;
  horizontal_event_placement: boolean = true;
  horizontal_brush_placement: boolean = true;
  event_domain_rect_padding: number   = 4;
  layer_domain_rect_padding: number   = 4;

  get_zoom_area_offset_left(): number {
    if (this.horizontal_brush_placement) {
      return this.left_margin;
    } else {
      return this.left_margin + this.brush_height;
    }
  }

  get_event_domain_size_attr_name(): string {
    return this.horizontal_event_placement ? "width" : "height";
  }

  get_layer_domain_size_attr_name(): string {
    return this.horizontal_event_placement ? "height" : "width";
  }

  get_brush_left_pos(): number {
    if (this.horizontal_brush_placement) {
      return this.left_margin + this.left_brush_margin;
    } else {
      return this.left_margin;
    }
  }

  get_brush_horizontal_size(): number {
    if (this.horizontal_brush_placement) {
      return this.get_content_event_extent() - this.left_brush_margin
             - this.right_brush_margin;
    } else {
      return this.brush_height;
    }
  }

  get_brush_event_domain_size(): number {
    if (this.horizontal_brush_placement) {
      return this.get_brush_horizontal_size();
    } else {
      return this.get_brush_vertical_size();
    }
  }

  get_brush_vertical_size(): number {
    if (this.horizontal_brush_placement) {
      return this.brush_height;
    } else {
      return this.get_content_event_extent();
    }
  }

  get_brush_top_pos(): number {
    if (this.horizontal_brush_placement) {
      return this.height - this.top_margin - this.brush_height;
    } else {
      return this.top_margin;
    }
  }

  get_content_event_extent(): number {
    return this.width - this.left_margin - this.right_margin;
  }

  get_content_layer_extent(): number {
    return this.height - this.top_margin - this.bottom_margin;
  }
}

type EventDomain
    = d3.ScaleTime<number, number, never>|d3.ScaleLinear<number, number>;

class ZoomUpdateState {
  event_domain: EventDomain;
  brush_event_domain: EventDomain;
  brush_layer_domain: d3.ScaleLinear<number, number, never>;
  layer_domain: d3.ScaleBand<string>;
  area: d3.Selection<SVGGElement, ZoomDatum, HTMLElement, any>;
  zoom: d3.ZoomBehavior<Element, ZoomDatum>;
  context: d3.Selection<SVGGElement, ZoomDatum, HTMLElement, any>;
  focus: d3.Selection<SVGGElement, ZoomDatum, HTMLElement, any>;
  event_axis: d3.Axis<Date|d3.NumberValue>;
  brush: d3.BrushBehavior<ZoomDatum>;
  event_color: d3.ScaleOrdinal<string, string>;
}

export class ZoomFlamegraphVisualization {
  svg: d3.Selection<SVGSVGElement, ZoomDatum, HTMLElement, any>;

  programmaticZoom: boolean  = false;
  programmaticBrush: boolean = false;

  event_selector: string = ".event_rectangle";
  gantt?: Gantt;
  conf: ZoomFlamegraphVisualizationConfig

  state: ZoomUpdateState;

  get_event_color(d: ZoomDatum): string {
    return this.state.event_color(`${d.layer}`);
  }

  convertTimeline(data: Gantt): ZoomDatum[] {
    function flatten(data: Event) {
      assert_zod(data, Event.Schema);
      return [ data ].concat(data.nested.map(d => flatten(d)).flat(1));
    }

    var   flat     = data.events.map(d => flatten(d));
    const timeline = flat.flat(1).map(function(d: Event): ZoomDatum {
      return new ZoomDatum(
          d.start,
          d.end,
          d.type!,
          d.name,
          d.layer,
      );
    });

    return timeline;
  }

  constructor(svg_element: string, conf: ZoomFlamegraphVisualizationConfig) {
    this.conf = conf;
    this.svg  = d3.select<SVGGElement, ZoomDatum>(`#${svg_element}`)
                    .append("svg")
                    .attr("class", "flame-graph")
                    .attr("height", this.conf.height)
                    .attr("width", this.conf.width);
  }

  get_datum_event_domain_length(d: ZoomDatum): number {
    return (this.state.event_domain(d.end.point)
            - this.state.event_domain(d.start.point));
  }

  rescaleForTransform() {
    this.state.area
        .selectAll(this.event_selector)
        // @ts-ignore
        .attr("transform", (d: ZoomDatum) => this.rectTransform(d));
    this.state.area.selectAll(this.event_selector + ",.body")
        .attr("overflow",
              this.conf.horizontal_event_placement ? "hidden" : "visible")
        .attr(this.conf.get_layer_domain_size_attr_name(),
              // @ts-ignore
              (d: ZoomDatum) => this.conf.rect_height)
        .attr(this.conf.get_event_domain_size_attr_name(),
              // @ts-ignore
              (d: ZoomDatum) => this.get_datum_event_domain_length(d));

    this.state.area.selectAll(this.event_selector + ",.rect-visual")
        .attr(this.conf.get_event_domain_size_attr_name(),
              // @ts-ignore
              (d: ZoomDatum) => {
                return this.get_datum_event_domain_length(d)
                       - this.conf.event_domain_rect_padding;
              });
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

    this.state.event_domain.domain(
        t.rescaleX(this.state.brush_event_domain).domain());
    this.rescaleForTransform();

    // @ts-ignore
    this.state.focus.select(".axis--event").call(this.state.event_axis);
    this.programmaticBrush = true;
    this.state.context.select(".brush").call(
        // @ts-ignore
        this.state.brush.move,
        this.state.event_domain.range().map(t.invertX, t));
  }

  async get_gantt(client: org.OrgClient, root: org.ImmUniqId): Promise<Gantt> {
    var res                            = new Gantt();
    var root_subtrees: org.ImmUniqId[] = Array();
    for (var subnode of await client.getAllSubnodes({id : root})) {
      if ((subnode as org.ImmUniqId).id.format.startsWith("Subtree")) {
        root_subtrees.push(subnode as org.ImmUniqId);
      }
    }
    const root_subtrees_list = await Promise.all(root_subtrees.map(
        async (id: org.ImmUniqId) => await OrgSubtreeEvent.from_id(client,
                                                                   id)));
    res.events               = Event.from_org_subtree(root_subtrees_list);
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

  rectTransform(d: ZoomDatum) {
    const layer_offset = get_defined(this.state.layer_domain(d.type))
                         + (this.conf.rect_height * d.layer);
    const event_offset = this.state.event_domain(d.start.point).toFixed(3);

    if (this.conf.horizontal_event_placement) {
      return `translate(${event_offset},${layer_offset})`;
    } else {
      return `translate(${layer_offset},${event_offset})`;
    }
  };

  brushed(event: any) {
    if (this.programmaticBrush) {
      this.programmaticBrush = false;
      return;
    } else {
      var s = event.selection || this.state.brush_event_domain.range();

      this.state.event_domain.domain(s.map(this.state.brush_event_domain.invert,
                                           this.state.brush_event_domain));
      this.rescaleForTransform();

      // focus.select(".focus").attr("d", focus);
      // @ts-ignore
      this.state.focus.select(".axis--event").call(this.state.event_axis);
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
                              this.conf.get_content_event_extent(),
                              this.conf.get_content_layer_extent(),
                            ]
                          ])
                          .extent([
                            [ 0, 0 ],
                            [
                              this.conf.get_content_event_extent(),
                              this.conf.get_content_layer_extent(),
                            ]
                          ])
                          .on("zoom", (e: any) => this.zoomed(e));

    this.svg.selectAll(".zoom")
        .data([ this.conf ])
        .join(enter => enter.append("rect")
                           .attr("class", "zoom")
                           .attr("width", this.conf.get_content_event_extent())
                           .attr("height", this.conf.get_content_layer_extent())
                           .style("fill", "white")
                           .attr(
                               "transform",
                               "translate("
                                   + this.conf.get_zoom_area_offset_left() + ","
                                   + this.conf.top_margin + ")",
                               )
                           // @ts-ignore
                           .call(this.state.zoom));
  }

  update_brush_context_event_rectangles(timeline: ZoomDatum[]) {
    var brush_rectangles
        = this.svg.selectAll(".brush-rectangles")
              .data([ this.conf ])
              .join(enter => enter.append("g")
                                 .attr("width",
                                       this.conf.get_brush_horizontal_size())
                                 .attr("height",
                                       this.conf.get_brush_vertical_size())
                                 .attr("class", "brush-rectangles")
                                 .attr("transform",
                                       `translate(${
                                           this.conf.get_brush_left_pos()}, ${
                                           this.conf.get_brush_top_pos()})`));

    const conf  = this.conf;
    const state = this.state;
    var   context_layer_domain
        = d3.scaleBand()
              .domain(timeline.map(function(entry) { return entry.type; }))
              .rangeRound([ conf.brush_height, 0 ]);

    const event_height       = 2;
    const event_layer_height = 4;

    function get_event_context_x(d: ZoomDatum): number {
      if (conf.horizontal_brush_placement) {
        return state.brush_event_domain(d.start.point);
      } else {
        return context_layer_domain(d.type) as
               number + d.layer * event_layer_height;
      }
    }

    function get_event_context_y(d: ZoomDatum): number {
      if (conf.horizontal_brush_placement) {
        return context_layer_domain(d.type) as
               number + d.layer * event_layer_height;
      } else {
        return state.brush_event_domain(d.start.point);
      }
    }

    function get_event_context_extent(d: ZoomDatum): number {
      return state.brush_event_domain(d.end.point)
             - state.brush_event_domain(d.start.point);
    }

    brush_rectangles.selectAll("rect")
        .data(timeline)
        .enter()
        .append("rect")
        .attr("fill", (d: ZoomDatum) => this.get_event_color(d))
        .attr("x", (d: ZoomDatum) => get_event_context_x(d))
        .attr("y", (d: ZoomDatum) => get_event_context_y(d))
        .attr("width", (d: ZoomDatum) => conf.horizontal_brush_placement
                                             ? get_event_context_extent(d)
                                             : event_height)
        .attr("height", (d: ZoomDatum) => conf.horizontal_brush_placement
                                              ? event_height
                                              : get_event_context_extent(d));
  }

  update_event_rectangles(timeline: ZoomDatum[]) {
    const c           = this.conf;
    var   keyFunction = function(d: ZoomDatum) {
      const res = `${d.start.point}-${d.end.point}-${d.layer}-${d.type}-${
          c.horizontal_event_placement}`;
      return res;
    };

    var event_rectangles = this.state.area
                               .selectAll(".event_rectangle")
                               // @ts-ignore
                               .data(timeline, keyFunction);

    const get_overflow_state
        = () => this.conf.horizontal_event_placement ? "hidden" : "visible";

    var event_repr = event_rectangles.join(
        enter => enter.append("g")
                     .attr("class", "event_rectangle")
                     .attr("debug", keyFunction)
                     .attr("overflow", get_overflow_state)
                     .append("svg")
                     .attr("class", "body")
                     .attr("overflow", get_overflow_state),
        update => update.attr("overflow", get_overflow_state))
        // .attr(this.conf.get_layer_domain_size_attr_name(),
        //       (d: ZoomDatum) => { return this.conf.rect_height; })
        // .attr(this.conf.get_event_domain_size_attr_name(),
        //       (d: ZoomDatum) => {
        //         return this.get_datum_event_domain_length(d);
        //       })
        // .attr("transform", (d: ZoomDatum) => this.rectTransform(d))
        ;

    // if (!this.conf.horizontal_event_placement) {
    //   event_repr.attr("overflow", "visible");
    // }

    this.state.event_color
        = d3.scaleOrdinal<string, string>()
              .domain(
                  [...new Set(timeline.map((d: ZoomDatum) => `${d.layer}`)) ])
              .range(d3.schemeSet3);

    event_repr.selectAll(".rect-visual")
        .data((d: ZoomDatum) => [d])
        .join(enter => enter.append("rect"))
        .attr("rx", "2px")
        .attr("ry", "2px")
        .attr(this.conf.horizontal_event_placement ? "x" : "y",
              this.conf.event_domain_rect_padding / 2)
        .attr(this.conf.horizontal_brush_placement ? "y" : "x",
              this.conf.layer_domain_rect_padding / 2)
        .attr("class", "rect-visual")
        .style("fill", (d: ZoomDatum) => this.get_event_color(d))
        .style("stroke", "black")
        .style("stroke-width", "1px")
        .on("mouseover",
            (event: any, d: ZoomDatum) => {
              const f_from: string
                  = d.start.point instanceof Date
                        ? d.start.point.toISOString().slice(0, 19)
                        : d.start.point.toString();

              const f_to: string = d.end.point instanceof Date
                                       ? d.end.point.toISOString().slice(0, 19)
                                       : d.end.point.toString();

              // console.log(`Focused from ${f_from} to
              // ${f_to}`);
            })
        .on("mouseout", (d: ZoomDatum) => {})
        .attr(this.conf.get_layer_domain_size_attr_name(),
              this.conf.rect_height - this.conf.layer_domain_rect_padding);

    var text_repr = event_repr.selectAll(".text")
                        .data((d: ZoomDatum) => [d])
                        .join(
                            enter => enter.append("text").attr("class", "text"),
                            update => update,
                            )
                        .text((d: ZoomDatum) => d.name)
                        .attr("font-family", "Verdana, sans-serif")
                        .attr("font-size", "12px")
                        .attr("fill", "black");

    if (this.conf.horizontal_event_placement) {
      text_repr //
          .attr("x", "50%")
          .attr("y", "50%")
          .attr("text-anchor", "middle")
          .attr("alignment-baseline", "middle");
    } else {
      text_repr //
          .attr("x", this.conf.event_domain_rect_padding / 2)
          .attr("y", this.conf.layer_domain_rect_padding / 2)
          .attr("text-anchor", "start")
          .attr("alignment-baseline", "hanging");
    }

    // event_rectangles.exit();
  }

  restore_brush_selection() {
    var storedBrushSelection
        = localStorage.getItem("brushSelection")
              ? JSON.parse(localStorage.getItem("brushSelection")!) as number[]
              : this.state.brush_event_domain.range();

    this.state.context.selectAll(".brush")
        .data([ this.conf ])
        .join(enter => enter.append("g")
                           .attr("class", "brush")
                           .call(this.state.brush)
                           // @ts-ignore
                           .call(this.state.brush.move,
                                 // @ts-ignore
                                 this.state.brush_event_domain.range()));

    // Get stored zoom and pan values
    var storedZoom       = +localStorage.getItem("zoom")!;
    var storedTranslateX = +localStorage.getItem("translateX")!;
    var storedTranslateY = +localStorage.getItem("translateY")!;

    // If stored values exist, apply them to the SVG
    if (storedZoom && storedTranslateX && storedTranslateY && false) {
      console.log("Restoring zoom transform");
      this.svg.call(
          // @ts-ignore
          this.state.zoom.transform,
          d3.zoomIdentity.translate(storedTranslateX, storedTranslateY)
              .scale(storedZoom));
    }

    // If stored brush selection exists, apply it
    if (storedBrushSelection) {
      function clamp(domain: d3.ScaleTime<number, number>, value) {
        return Math.max(domain.range()[0], Math.min(domain.range()[1], value));
      }

      const clamped_selection = [
        // @ts-ignore
        clamp(this.state.brush_event_domain, storedBrushSelection[0]),
        // @ts-ignore
        clamp(this.state.brush_event_domain, storedBrushSelection[1])
      ];

      // @ts-ignore
      // brushG.call(this.state.brush.move, clamped_selection);
    }
  }

  update() {
    console.log("Triggering update");
    this.state     = new ZoomUpdateState();
    const timeline = this.convertTimeline(this.gantt!);

    if (!(timeline.every(d => d.start.isDate())
          || timeline.every(d => d.start.isNumber()))) {
      throw new Error(
          "Either every timeline event must be a date, or every event must be a number");
    }

    const isTimeXDomain = timeline[0].start.isDate();

    const event_domain_range = [
      get_defined(d3.min(
          timeline, (d: ZoomDatum): Date|number => { return d.start.point; })),
      get_defined(d3.max(
          timeline, (d: ZoomDatum): Date|number => { return d.end.point; })),
    ];

    if (isTimeXDomain) {
      this.state.event_domain
          = d3.scaleTime().domain(event_domain_range).range([
              0, this.conf.get_content_event_extent()
            ]);
    } else {
      this.state.event_domain
          = d3.scaleLinear().domain(event_domain_range).range([
              0, this.conf.get_content_event_extent()
            ]);
    }

    if (isTimeXDomain) {
      this.state.brush_event_domain
          = d3.scaleTime().domain(event_domain_range).range([
              0, this.conf.get_brush_event_domain_size()
            ]);
    } else {
      this.state.brush_event_domain
          = d3.scaleLinear().domain(event_domain_range).range([
              0, this.conf.get_brush_event_domain_size()
            ]);
    }

    this.state.brush_layer_domain = d3.scaleLinear().range(
        [ this.conf.get_brush_event_domain_size(), 0 ]);

    this.state.layer_domain
        = d3.scaleBand()
              .domain(timeline.map(function(entry) { return entry.type; }))
              .rangeRound([ this.conf.get_content_layer_extent(), 0 ]);

    this.state.focus
        = this.svg.selectAll(".focus")
              .data([ this.conf ])
              .join(enter => enter.append("g")
                                 .attr("class", "focus")
                                 .attr("transform",
                                       "translate(" + this.conf.left_margin
                                           + "," + this.conf.top_margin + ")"));

    this.state.event_axis = this.conf.horizontal_event_placement
                                ? d3.axisBottom(this.state.event_domain)
                                : d3.axisLeft(this.state.event_domain);
    var brush_event_axis  = this.conf.horizontal_brush_placement
                                ? d3.axisBottom(this.state.brush_event_domain)
                                : d3.axisLeft(this.state.brush_event_domain);
    var layer_axis        = this.conf.horizontal_event_placement
                                ? d3.axisLeft(this.state.layer_domain).tickSize(0)
                                : d3.axisBottom(this.state.layer_domain).tickSize(0);

    if (this.conf.horizontal_brush_placement) {
      this.state.brush
          = d3.brushX<ZoomDatum>()
                .extent([
                  [ 0, 0 ],
                  [
                    this.conf.get_brush_horizontal_size(),
                    this.conf.get_brush_vertical_size(),
                  ]
                ])
                .on("brush end", (e: any, d: ZoomDatum) => this.brushed(e));
    } else {
      this.state.brush
          = d3.brushY<ZoomDatum>()
                .extent([
                  [ 0, 0 ],
                  [
                    this.conf.get_brush_horizontal_size(),
                    this.conf.get_brush_vertical_size(),
                  ]
                ])
                .on("brush end", (e: any, d: ZoomDatum) => this.brushed(e));
    }

    this.update_zoom_selector();

    this.state.area
        = this.svg.selectAll(".clipped.event-rect-area")
              .data([ this.conf ])
              .join(
                  (enter) => {
                      return enter.append("g")
                          .attr("class", "clipped event-rect-area")
                          .attr("width", this.conf.get_content_event_extent())
                          .attr("height", this.conf.get_content_layer_extent())
                          .attr("transform",
                                `translate(${
                                    this.conf.get_zoom_area_offset_left()},${
                                    this.conf.top_margin})`)});

    this.update_event_rectangles(timeline);

    var brush_area
        = d3.area<ZoomDatum>()
              .curve(this.conf.horizontal_brush_placement ? d3.curveMonotoneX
                                                          : d3.curveMonotoneY)
              .x((d: ZoomDatum) => {
                return this.state.brush_event_domain(d.start.point);
              })
              .y0(this.conf.get_brush_horizontal_size())
              .y1((d: ZoomDatum) => {
                // @ts-ignore
                return this.state.brush_layer_domain(d.name);
              });

    this.state.context
        = this.svg.selectAll(".context")
              .data([ this.conf ])
              .join(enter => enter.append("g")
                                 .attr("class", "context")
                                 .attr("transform",
                                       "translate("
                                           + this.conf.get_brush_left_pos()
                                           + "," + this.conf.get_brush_top_pos()
                                           + ")"));

    this.state.brush_event_domain.domain(this.state.event_domain.domain());
    // @ts-ignore
    this.state.brush_layer_domain.domain(this.state.layer_domain.domain());

    this.state.focus.selectAll(".axis--event")
        .data([ this.conf ])
        .join(
            enter => enter.append("g")
                         .attr("class", "axis axis--event")
                         .attr("transform",
                               "translate("
                                   + (this.conf.horizontal_brush_placement
                                          ? 0
                                          : this.conf.brush_height)
                                   + ","
                                   + (this.conf.horizontal_event_placement
                                          ? this.conf.get_content_layer_extent()
                                          : 0)
                                   + ")")
                         .call(this.state.event_axis));

    this.state.focus.selectAll(".axis--layer")
        .data([ this.conf ])
        .join(enter => enter.append("g")
                           .attr("class", "axis axis--layer")
                           .call(layer_axis));

    this.state.context.selectAll(".axis--event")
        .data([ this.conf ])
        .join(enter => enter.append("g")
                           .attr("class", "axis axis--event")
                           .attr("transform",
                                 "translate(0,"
                                     + (this.conf.horizontal_brush_placement
                                            ? this.conf.brush_height
                                            : 0)
                                     + ")")
                           .call(brush_event_axis));

    this.restore_brush_selection();
    this.update_brush_context_event_rectangles(timeline);

    this.rescaleForTransform();
  }
}
