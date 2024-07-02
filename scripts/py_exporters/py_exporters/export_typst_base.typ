#let orgSubtree(
    level: 1, 
    tags: (),
    title,
  ) = {
  heading(
    level: level
  )[#title]
}

#let orgList(
  items: ()
) = {
  list(..items)
}

#let orgListItem(
  header: none,
  content: [],
  isDescription: false,
) = {
  list.item(content)
}

#let orgParagraph(
  admonition: "",
  body
) = {
  body
}
