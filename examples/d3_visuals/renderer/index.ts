import {
  CollapsibleTreeVisualization,
  CollapsibleTreeVisualizationConfig
} from "./vis_collapsible_tree.ts";
import {ZoomFlamegraphVisualization} from "./vis_zoom_flamegraph.ts"

window.addEventListener("DOMContentLoaded", () => {
  if (true) {
    const viz = new ZoomFlamegraphVisualization("visualization");
    viz.render();
  } else {
    var conf                     = new CollapsibleTreeVisualizationConfig();
    conf.circle_vertical_spacing = 30;
    const viz = new CollapsibleTreeVisualization("visualization", conf);
    viz.render_tree_repr();
  }
});
