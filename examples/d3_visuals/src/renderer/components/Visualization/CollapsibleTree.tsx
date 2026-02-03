import React from "react";
import { useState, useEffect, useRef } from 'react';
import * as d3 from 'd3';

import {
  CollapsibleTreeVisualization,
  CollapsibleTreeVisualizationConfig,
} from "../../d3_visuals/vis_collapsible_tree.ts";

export function CollapsibleTree() {
  const containerRef = useRef<HTMLDivElement>(null);
  const vizRef = useRef<CollapsibleTreeVisualization | null>(null);

  useEffect(() => {
    if (!containerRef.current) return;

    const config = new CollapsibleTreeVisualizationConfig();
    config.path = "/home/haxscramper/tmp/org_trivial.org";
    d3.select(containerRef.current).selectAll('svg').remove();
    vizRef.current = new CollapsibleTreeVisualization(containerRef.current.id, config);
    vizRef.current.render_tree_repr();
  }, []);

  return (
    <div>
      <div id="visualization" ref={containerRef} />
    </div>
  )
}
