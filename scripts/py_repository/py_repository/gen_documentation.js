function add_coverage_annotation_handler() {
  console.log("Dom content loaded")
  document.querySelectorAll(".segment-cov-executed").forEach(function(elem) {
    console.log("Adding event listener to element")
    elem.addEventListener("mouseover", function(event) {
      const covIdx = this.dataset.covIdx;
      console.log(`Triggered mouseover for the executed segment coverage ${covIdx}`)
      const tooltip = document.createElement("div");
      tooltip.className = "tooltip";
      tooltip.style.position = "absolute";
      tooltip.style.backgroundColor = "#f9f9f9";
      tooltip.style.border = "1px solid #ccc";
      tooltip.style.padding = "10px";
      tooltip.style.zIndex = "1000";

      const covContextElem = document.getElementById(`cov-context-${covIdx}`);
      if (covContextElem) {
        const clonedElem = covContextElem.cloneNode(true);
        clonedElem.style.display = "block";
        tooltip.appendChild(clonedElem);
      }

      document.body.appendChild(tooltip);

      function moveTooltip(event) {
        tooltip.style.left = event.pageX + "px";
        tooltip.style.top = event.pageY + "px";
      }

      document.addEventListener("mousemove", moveTooltip);

      elem.addEventListener("mouseout", function() {
        document.removeEventListener("mousemove", moveTooltip);
        tooltip.remove();
      }, {once : true});
    });
  });
}

window.onload = function() { add_coverage_annotation_handler(); }
