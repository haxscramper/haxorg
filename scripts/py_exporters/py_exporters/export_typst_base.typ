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
  items: (),
  isDescription: false,
) = {
  if isDescription {
    terms(..items);
  } else {
    list(..items)
  }
}

#let orgListItem(
  header: none,
  content: [],
  isDescription: false,
) = {
  if isDescription {
    terms.item(header, content)
  } else {
    list.item(content)
  }
}

#let orgParagraph(
  admonition: "",
  timestamp: "",
  footnote: "",
  kind: "none",
  body
) = {
  if kind == "none" {
    body
  } else if kind == "admonition" {
    [#box(radius: 2pt, stroke: red, inset: 4pt)[#admonition]]
    body
  }
}


#let orgPlaceholder(text: "") = {
  [#text]
}

#let orgBigIdent(text: "") = {
  [#text]
}

#let orgMention(text: "") = {
  [#text]
}

#let orgQuote(body) = {
  quote(body, block: true)
}

#let orgExample(body) = {
  body
}

#let orgCenter(body) = {
  align(center)[
    body
  ]
}

#let orgCode(lang: "", text: "") = {
  raw(lang: lang, block: true, text)
}
