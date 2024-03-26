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
                      console.log(result);
                      return result;
                    });

  return [ nodes, links ];
}
