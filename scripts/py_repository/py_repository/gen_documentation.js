var data = {};

function show_coverage_segment_idx(index) {
  const existingContainer = document.querySelector(".cov-context");
  if (existingContainer) {
    existingContainer.remove();
  }

  const container = document.createElement("div");
  container.className = "cov-context";

  const contextGroup = data.SegmentContexts[index];
  if (!contextGroup) {
    container.textContent = "<no-coverage>";
    document.body.appendChild(container);
    return;
  }

  let hasContent = false;

  contextGroup.Grouped.forEach(group => {
    const contextName = group.Context.Name;
    const functionSegments = group.FunctionSegments;

    const validSegments =
        functionSegments.filter(seg => seg.ExecutionCount > 0);
    if (validSegments.length === 0)
      return;

    const contextHeader = document.createElement("div");
    const functionHeader =
        validSegments.length === 1
            ? `${contextName}, #${validSegments[0].ExecutionCount}`
            : `${contextName}:`;
    contextHeader.textContent = functionHeader;
    container.appendChild(contextHeader);

    if (validSegments.length > 1) {
      const ul = document.createElement("ul");
      validSegments.forEach(seg => {
        const li = document.createElement("li");
        const functionName = data.Functions[seg.Function].SimplifiedDemangled;
        li.textContent =
            `#${seg.ExecutionCount}, ${functionName}`;
        ul.appendChild(li);
      });
      container.appendChild(ul);
    }

    hasContent = true;
  });

  if (!hasContent) {
    container.textContent = "<no-coverage>";
  }

  document.body.appendChild(container);
}

window.onload = function() {
  data = JSON.parse(document.getElementById("segment-coverage").textContent);
}
