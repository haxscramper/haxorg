import {
  CollapsibleTreeVisualization,
  CollapsibleTreeVisualizationConfig
} from "./visualization";

window.addEventListener("DOMContentLoaded", () => {
  var conf = new CollapsibleTreeVisualizationConfig();
  conf.circle_vertical_spacing = 30;
  const viz = new CollapsibleTreeVisualization("visualization", conf);
  viz.render_tree_repr();
});
