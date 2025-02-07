import { useState, useEffect, useRef } from 'react';
import React from "react";
import * as d3 from 'd3';
import { ZoomFlamegraphVisualization, ZoomFlamegraphVisualizationConfig } from "../../renderer/vis_zoom_flamegraph.ts";

export function FlameGraph() {
  const [horizontalEventPlacement, setHorizontalEventPlacement] = useState(true);
  const [horizontalBrushPlacement, setHorizontalBrushPlacement] = useState(true);
  const containerRef = useRef<HTMLDivElement>(null);
  const vizRef = useRef<ZoomFlamegraphVisualization | null>(null);

  useEffect(() => {
    if (!containerRef.current) return;

    const config = new ZoomFlamegraphVisualizationConfig();
    config.horizontal_event_placement = horizontalEventPlacement;
    config.horizontal_brush_placement = horizontalBrushPlacement;
    d3.select(containerRef.current).selectAll('svg').remove();
    vizRef.current = new ZoomFlamegraphVisualization(containerRef.current.id, config);
    vizRef.current.render();
  }, []);

  useEffect(() => {
    if (!vizRef.current) return;
    vizRef.current.conf.horizontal_event_placement = horizontalEventPlacement;
    vizRef.current.conf.horizontal_brush_placement = horizontalBrushPlacement;
    vizRef.current.render();
  }, [horizontalEventPlacement, horizontalBrushPlacement]);

  return (
    <div>
      <label>
        <input
          type="checkbox"
          checked={horizontalEventPlacement}
          onChange={(e) => setHorizontalEventPlacement(e.target.checked)}
        />
        Horizontal Event Placement
      </label>
      <label>
        <input
          type="checkbox"
          checked={horizontalBrushPlacement}
          onChange={(e) => setHorizontalBrushPlacement(e.target.checked)}
        />
        Horizontal Brush Placement
      </label>
      <div id="visualization" ref={containerRef} />
    </div>
  );
};
