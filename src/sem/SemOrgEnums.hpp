#pragma once
enum class OrgSemKind {
  StmtList,
  Empty,
  Row,
  Table,
  HashTag,
  Footnote,
  Completion,
  Paragraph,
  Center,
  Caption,
  Quote,
  Example,
  Export,
  AdmonitionBlock,
  Code,
  Time,
  TimeRange,
  Macro,
  Symbol,
  SubtreeLog,
  Subtree,
  InlineMath,
  Escaped,
  Newline,
  Space,
  Word,
  AtMention,
  RawText,
  Punctuation,
  Placeholder,
  BigIdent,
  Bold,
  Underline,
  Monospace,
  MarkQuote,
  Verbatim,
  Italic,
  Strike,
  Par,
  List,
  ListItem,
  Link,
};

#define EACH_ORG_SEM_KIND(__IMPL) \
    __IMPL(StmtList) \
    __IMPL(Empty) \
    __IMPL(Row) \
    __IMPL(Table) \
    __IMPL(HashTag) \
    __IMPL(Footnote) \
    __IMPL(Completion) \
    __IMPL(Paragraph) \
    __IMPL(Center) \
    __IMPL(Caption) \
    __IMPL(Quote) \
    __IMPL(Example) \
    __IMPL(Export) \
    __IMPL(AdmonitionBlock) \
    __IMPL(Code) \
    __IMPL(Time) \
    __IMPL(TimeRange) \
    __IMPL(Macro) \
    __IMPL(Symbol) \
    __IMPL(SubtreeLog) \
    __IMPL(Subtree) \
    __IMPL(InlineMath) \
    __IMPL(Escaped) \
    __IMPL(Newline) \
    __IMPL(Space) \
    __IMPL(Word) \
    __IMPL(AtMention) \
    __IMPL(RawText) \
    __IMPL(Punctuation) \
    __IMPL(Placeholder) \
    __IMPL(BigIdent) \
    __IMPL(Bold) \
    __IMPL(Underline) \
    __IMPL(Monospace) \
    __IMPL(MarkQuote) \
    __IMPL(Verbatim) \
    __IMPL(Italic) \
    __IMPL(Strike) \
    __IMPL(Par) \
    __IMPL(List) \
    __IMPL(ListItem) \
    __IMPL(Link) \

