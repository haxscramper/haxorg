#import "@preview/gentle-clues:1.1.0": *

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
    if admonition == "INFO" {
      info[#body]
    } else if admonition == "IDEA" {
      idea[#body]
    } else if admonition == "QUESTION" {
      question[#body]
    } else if admonition == "EXAMPLE" {
      example[#body]
    } else if admonition == "NOTE" {
      clue(
        title: "Note",
        icon: emoji.notepad,
      )[#body]
    } else {
      clue(
        title: admonition,
        icon: emoji.unknown,
      )[#body]
    }
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
