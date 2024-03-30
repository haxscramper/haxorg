export function convertMindMapGraph(data) {
  var idMap = new Map();
  const nodes = Array();
  for (const [key, value] of Object.entries(data.nodes)) {
    if (value.metadata.kind == "Subtree") {
      value.id = value.metadata.id;
      idMap.set(key, value.id);
      nodes.push(value)
    }
  }

  // The force simulation mutates links and nodes, so create a copy
  // so that re-evaluating this cell produces the same result.
  const links = data.edges.filter(d => d.metadata.kind == "InternallyRefers")
                    .map(function(d) {
                      var result = ({
                        ...d,
                        source : idMap.get(d.source),
                        target : idMap.get(d.target)
                      });
                      return result;
                    });

  return [ nodes, links ];
}

export function flushAllD3Transitions() {
  const now = performance.now;
  performance.now = function() { return Infinity; };
  d3.timerFlush();
  performance.now = now;
}

export function console_log_stack(message, traceLines = 1) {
  const error = new Error();
  const stackLines = error.stack.split("\n").slice(2, 2 + traceLines);
  const formattedStack = stackLines.map(line => `  ${line.trim()}`).join("\n");
  console.log(`${message}\n${formattedStack}`);
}
