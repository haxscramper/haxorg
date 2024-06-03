

function show_coverage_segment_idx(index) {
  document.querySelectorAll(".cov-context")
      .forEach(function(div) { div.style.display = "none"; });

  const contextDiv = document.getElementById("cov-context-" + index);
  if (contextDiv) {
    contextDiv.style.display = "block";
  }
}

window.onload = function() {
  //
}
