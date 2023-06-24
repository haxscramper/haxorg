function convertTimeline(data) {
  function flatten(data) {
    return [ data ].concat(data.nested.map(d => flatten(d)).flat(1));
  }

  var flat = data.events.map(d => flatten(d));
  const timeline = flat.flat(1).map(function(d) {
    var result = ({
      startdate : new Date(d.start),
      enddate : new Date(d.stop),
      type : "one",
      name : d.name
    });

    if (d.start_date_only && d.stop_date_only) {
      result.enddate.setHours(23, 59, 59);
    }

    return result;
  });

  console.log(timeline);
  var idx = 0;
  return timeline.filter(d => 2004 < d.enddate.getFullYear())
      .map(d => ({...d, index : idx++}));
}

function update(timeline) {
  // To get the event positio05
  var keyFunction = function(d) { return d.startdate + d.type; }

  var svg = d3.select("svg")

  const margin = {top : 20, right : 20, bottom : 110, left : 50};
  const margin2 = {top : 430, right : 20, bottom : 30, left : 50};
  const width = +svg.attr("width") - margin.left - margin.right;
  const height = +svg.attr("height") - margin.top - margin.bottom;
  const height2 = +svg.attr("height") - margin2.top - margin2.bottom;

  // Define the div for the tooltip
  var tooltip = d3.select("body").append("div").attr("class", "tooltip")

  var parseDate = d3.timeParse("%b %Y");

  var x = d3.scaleTime()
              .domain([
                d3.min(timeline, function(d) { return d.startdate; }),
                d3.max(timeline, function(d) { return d.enddate; })
              ])
              .range([ 0, width ]),
      x2 = d3.scaleTime().range([ 0, width ]),
      // y = d3.scaleOrdinal().range([height, 0]),
      y2 = d3.scaleLinear().range([ height2, 0 ]);

  var y = d3.scaleBand()
              .domain(timeline.map(function(entry) { return entry.type; }))
              .rangeRound([ height, 0 ])

  let programmaticZoom = false;
  let programmaticBrush = false;

  const scalable_selector = ".event_rectangle,.data_overlay";

  function zoomed(e) {
    if (programmaticZoom) {
      programmaticZoom = false;
      return;
    }

    var t = e.transform;
    x.domain(t.rescaleX(x2).domain());
    area.selectAll(scalable_selector)
        .attr("transform", rectTransform)
        .attr("width", function(d) { return (x(d.enddate) - x(d.startdate)) })
    focus.select(".axis--x").call(xAxis);
    programmaticBrush = true;
    context.select(".brush").call(brush.move, x.range().map(t.invertX, t));
  }

  function brushed(event, d) {
    if (programmaticBrush) {
      programmaticBrush = false;
      return;
    }

    var s = event.selection || x2.range();
    x.domain(s.map(x2.invert, x2));
    area.selectAll(scalable_selector)
        .attr("transform", rectTransform)
        .attr("width", function(d) { return (x(d.enddate) - x(d.startdate)) })
    //   focus.select(".focus").attr("d", focus);
    focus.select(".axis--x").call(xAxis);
    programmaticZoom = true;
    svg.select(".zoom").call(
        zoom.transform,
        d3.zoomIdentity.scale(width / (s[1] - s[0])).translate(-s[0], 0));
  }

  // colors for each type
  var types = [...new Set(timeline.map(item => item.type)) ];
  var colors = chroma.scale('Spectral').colors(types.length)
  var type2color = {};
  types.forEach(function(element,
                         index) { type2color[element] = colors[index] });

  var rectTransform = function(
      d) { return "translate(" + x(d.startdate) + "," + y(d.type) + ")"; };

  var xAxis = d3.axisBottom(x), xAxis2 = d3.axisBottom(x2),
      yAxis = d3.axisLeft(y).tickSize(0);

  var brush = d3.brushX()
                  .extent([ [ 0, 0 ], [ width, height2 ] ])
                  .on("brush end", brushed);

  var zoom = d3.zoom()
                 .scaleExtent([ 1, Infinity ])
                 .translateExtent([ [ 0, 0 ], [ width, height ] ])
                 .extent([ [ 0, 0 ], [ width, height ] ])
                 .on("zoom", zoomed);

  svg.append("rect")
      .attr("class", "zoom")
      .attr("width", width)
      .attr("height", height)
      .attr("transform", "translate(" + margin.left + "," + margin.top + ")")
      .call(zoom);

  svg.append("defs")
      .append("clipPath")
      .attr("id", "clip")
      .append("rect")
      .attr("width", width)
      .attr("height", height)

  var area = svg.append("g")
                 .attr('class', 'clipped')
                 .attr("width", width)
                 .attr("height", height)
                 .attr("transform",
                       "translate(" + margin.left + "," + margin.top + ")");

  var focus = svg.append("g")
                  .attr("class", "focus")
                  .attr("transform",
                        "translate(" + margin.left + "," + margin.top + ")");

  var event_rectangles = area.selectAll(".event_rectangle")
                             .data(timeline, keyFunction)
                             .enter()
                             .append("g");

  event_rectangles.append("rect")
      .attr("rx", 5)
      .attr("ry", 5)
      .attr("class", "event_rectangle")
      .attr("y", 0)
      .attr("transform", rectTransform)
      .attr("height", function(d) { return y.bandwidth(); })
      .attr("width", function(d) { return (x(d.enddate) - x(d.startdate)) })
      .style("fill", function(d) { return type2color[d.type] })
      .on("mouseover",
          function(event, d) {
            tooltip.style("left", event.pageX + "px")
                .style("top", event.pageY + "px")
                .style("display", "inline-block")
                .html((d.name) +
                      "<br> from :" + d.startdate.toISOString().slice(0, 19) +
                      "<br> to :" + d.enddate.toISOString().slice(0, 19));
          })
      .on("mouseout", function(d) { tooltip.style("display", "none") });

  var data_overlay = area.selectAll(".data_overlay")
                         .data(timeline, keyFunction)
                         .enter()
                         .append("g");

  function rectOffset(d) { return d.index * 20; }

  data_overlay.append('text')
      .attr('y', d => rectOffset(d))
      .text(d => d.name)
      .attr("class", "data_overlay")
      .attr('text-anchor', 'start')
      .attr('alignment-baseline', 'middle')
      .attr('font-family', 'Verdana, sans-serif')
      .attr("font-size", '14px')
      .attr("transform", rectTransform)
      .attr("fill", 'black');

  data_overlay.append('rect')
      .attr('x', -0.5)
      .attr('y', 0)
      .attr('width', 1)
      .attr('height', height)
      .attr('stroke', 'black')
      .attr('stroke-width', 0)
      .attr('fill', 'black')

  var area2 = d3.area()
                  .curve(d3.curveMonotoneX)
                  .x(function(d) { return x2(d.startdate); })
                  .y0(height2)
                  .y1(function(d) { return y2(d.name); });

  var context = svg.append("g")
                    .attr("class", "context")
                    .attr("transform", "translate(" + margin2.left + "," +
                                           margin2.top + ")");

  var data = timeline

  x2.domain(x.domain());
  y2.domain(y.domain());

  focus.append("g")
      .attr("class", "axis axis--x")
      .attr("transform", "translate(0," + height + ")")
      .call(xAxis);

  focus.append("g").attr("class", "axis axis--y").call(yAxis);

  context.append("path").datum(data).attr("class", "area").attr("d", area2);

  context.append("g")
      .attr("class", "axis axis--x")
      .attr("transform", "translate(0," + height2 + ")")
      .call(xAxis2);

  context.append("g")
      .attr("class", "brush")
      .call(brush)
      .call(brush.move, x.range());
}

d3.json("/tmp/gantt.json")
    .then(function(data) { update(convertTimeline(data)); },
          function(err) { throw err; })
