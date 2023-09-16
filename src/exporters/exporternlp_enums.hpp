#pragma once
#include <hstd/system/basic_templates.hpp>
#include <hstd/system/reflection.hpp>
#include <hstd/stdlib/Opt.hpp>
/// \brief Dependency kind
enum class NlpDepKind : short int {
  ROOT,
  acl,
  advcl,
  advmod,
  amod,
  appos,
  aux,
  _case,
  cc,
  ccomp,
  compound,
  conj,
  cop,
  csubj,
  dep,
  det,
  discourse,
  expl,
  fixed,
  iobj,
  mark,
  nmod,
  nsubj,
  nummod,
  obj,
  obl,
  parataxis,
  punct,
  ref,
  xcomp,
};

template <>
struct enum_serde<NlpDepKind> {
  static Opt<NlpDepKind> from_string(QString value);
  static QString to_string(NlpDepKind value);
};

template <>
struct value_domain<NlpDepKind> : public value_domain_ungapped<NlpDepKind,
                                                               NlpDepKind::ROOT,
                                                               NlpDepKind::xcomp> {};

/// \brief Part of speech tag
enum class NlpPosTag : short int {
  ADJP,
  ADVP,
  ADD,
  AFX,
  CC,
  CD,
  CONJP,
  DT,
  EX,
  FRAG,
  FW,
  HYPH,
  IN,
  INTJ,
  JJ,
  JJR,
  JJS,
  LRB,
  LS,
  LST,
  MD,
  META,
  NAC,
  NFP,
  NML,
  NN,
  NNP,
  NNPS,
  NNS,
  NP,
  NPS,
  NP_TMP,
  PDT,
  POS,
  PP,
  PPZ,
  PRN,
  PRP,
  PRT,
  PUNCT_COLON,
  PUNCT_COMMA,
  PUNCT_PERIOD,
  PUNCT_QUOTE_CLOSE,
  PUNCT_QUOTE_OPEN,
  QP,
  RB,
  RBR,
  RBS,
  ROOT,
  RP,
  RRB,
  RRC,
  S,
  SBAR,
  SBARQ,
  SENT,
  SINV,
  SQ,
  SYM,
  TO,
  UCP,
  UH,
  VB,
  VBD,
  VBG,
  VBN,
  VBP,
  VBZ,
  VH,
  VHD,
  VHG,
  VHN,
  VHP,
  VHZ,
  VP,
  VV,
  VVD,
  VVG,
  VVN,
  VVP,
  VVZ,
  WDT,
  WHADJP,
  WHADVP,
  WHNP,
  WHPP,
  WP,
  /// \brief Possessive wh-pronoun
  WP_POS,
  WRB,
  X,
};

template <>
struct enum_serde<NlpPosTag> {
  static Opt<NlpPosTag> from_string(QString value);
  static QString to_string(NlpPosTag value);
};

template <>
struct value_domain<NlpPosTag> : public value_domain_ungapped<NlpPosTag,
                                                              NlpPosTag::ADJP,
                                                              NlpPosTag::X> {};