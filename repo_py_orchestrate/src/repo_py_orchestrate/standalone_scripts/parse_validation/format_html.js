"use strict";

const results       = document.getElementById("results");
const detailContent = document.getElementById("detail-content");

results.addEventListener("click", (event) => {
  if (!(event.target instanceof Element)) {
    return;
  }

  const button = event.target.closest("button[data-template]");

  if (!button) {
    return;
  }

  const template = document.getElementById(button.dataset.template);

  if (!(template instanceof HTMLTemplateElement)) {
    throw new Error("Missing detail template: " + button.dataset.template);
  }

  for (const active of results.querySelectorAll(
           "button[aria-pressed=\"true\"]")) {
    active.setAttribute("aria-pressed", "false");
  }

  for (const row of results.querySelectorAll("tr.selected")) {
    row.classList.remove("selected");
  }

  button.setAttribute("aria-pressed", "true");
  button.closest("tr").classList.add("selected");

  detailContent.replaceChildren(template.content.cloneNode(true));
  detailContent.parentElement.scrollTop = 0;
});
