import {
  CollapsibleTreeVisualization,
  CollapsibleTreeVisualizationConfig,
} from "../renderer/d3_visuals/vis_collapsible_tree.ts";
import {
  ZoomFlamegraphVisualization,
  ZoomFlamegraphVisualizationConfig,
} from "../renderer/d3_visuals/vis_zoom_flamegraph.ts"

if (false) {
  window.addEventListener("DOMContentLoaded", () => {
    if (true) {
      var conf1 = new ZoomFlamegraphVisualizationConfig();
      conf1.horizontal_event_placement = true;
      conf1.horizontal_brush_placement = true;
      const viz = new ZoomFlamegraphVisualization("visualization", conf1);
      viz.render();
    } else {
      var conf                     = new CollapsibleTreeVisualizationConfig();
      conf.circle_vertical_spacing = 30;
      const viz = new CollapsibleTreeVisualization("visualization", conf);
      viz.render_tree_repr();
    }
  });
}
