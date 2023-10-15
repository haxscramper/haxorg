#include "exporternlp_enums.hpp"

Opt<NlpDepKind> enum_serde<NlpDepKind>::from_string(QString value) {
  if (value == "ROOT") { return NlpDepKind::ROOT; } else
  if (value == "acl") { return NlpDepKind::acl; } else
  if (value == "advcl") { return NlpDepKind::advcl; } else
  if (value == "advmod") { return NlpDepKind::advmod; } else
  if (value == "amod") { return NlpDepKind::amod; } else
  if (value == "appos") { return NlpDepKind::appos; } else
  if (value == "aux") { return NlpDepKind::aux; } else
  if (value == "_case") { return NlpDepKind::_case; } else
  if (value == "cc") { return NlpDepKind::cc; } else
  if (value == "ccomp") { return NlpDepKind::ccomp; } else
  if (value == "compound") { return NlpDepKind::compound; } else
  if (value == "conj") { return NlpDepKind::conj; } else
  if (value == "cop") { return NlpDepKind::cop; } else
  if (value == "csubj") { return NlpDepKind::csubj; } else
  if (value == "dep") { return NlpDepKind::dep; } else
  if (value == "det") { return NlpDepKind::det; } else
  if (value == "discourse") { return NlpDepKind::discourse; } else
  if (value == "expl") { return NlpDepKind::expl; } else
  if (value == "fixed") { return NlpDepKind::fixed; } else
  if (value == "iobj") { return NlpDepKind::iobj; } else
  if (value == "mark") { return NlpDepKind::mark; } else
  if (value == "nmod") { return NlpDepKind::nmod; } else
  if (value == "nsubj") { return NlpDepKind::nsubj; } else
  if (value == "nummod") { return NlpDepKind::nummod; } else
  if (value == "obj") { return NlpDepKind::obj; } else
  if (value == "obl") { return NlpDepKind::obl; } else
  if (value == "parataxis") { return NlpDepKind::parataxis; } else
  if (value == "punct") { return NlpDepKind::punct; } else
  if (value == "ref") { return NlpDepKind::ref; } else
  if (value == "xcomp") { return NlpDepKind::xcomp; } else
  { return std::nullopt; }
}
QString enum_serde<NlpDepKind>::to_string(NlpDepKind value) {
  switch (value) {
    case NlpDepKind::ROOT: return "ROOT";
    case NlpDepKind::acl: return "acl";
    case NlpDepKind::advcl: return "advcl";
    case NlpDepKind::advmod: return "advmod";
    case NlpDepKind::amod: return "amod";
    case NlpDepKind::appos: return "appos";
    case NlpDepKind::aux: return "aux";
    case NlpDepKind::_case: return "_case";
    case NlpDepKind::cc: return "cc";
    case NlpDepKind::ccomp: return "ccomp";
    case NlpDepKind::compound: return "compound";
    case NlpDepKind::conj: return "conj";
    case NlpDepKind::cop: return "cop";
    case NlpDepKind::csubj: return "csubj";
    case NlpDepKind::dep: return "dep";
    case NlpDepKind::det: return "det";
    case NlpDepKind::discourse: return "discourse";
    case NlpDepKind::expl: return "expl";
    case NlpDepKind::fixed: return "fixed";
    case NlpDepKind::iobj: return "iobj";
    case NlpDepKind::mark: return "mark";
    case NlpDepKind::nmod: return "nmod";
    case NlpDepKind::nsubj: return "nsubj";
    case NlpDepKind::nummod: return "nummod";
    case NlpDepKind::obj: return "obj";
    case NlpDepKind::obl: return "obl";
    case NlpDepKind::parataxis: return "parataxis";
    case NlpDepKind::punct: return "punct";
    case NlpDepKind::ref: return "ref";
    case NlpDepKind::xcomp: return "xcomp";
    default: throw std::domain_error("Unexpected enum value -- cannot be converted to string");
  }
}

Opt<NlpPosTag> enum_serde<NlpPosTag>::from_string(QString value) {
  if (value == "ADJP") { return NlpPosTag::ADJP; } else
  if (value == "ADVP") { return NlpPosTag::ADVP; } else
  if (value == "ADD") { return NlpPosTag::ADD; } else
  if (value == "AFX") { return NlpPosTag::AFX; } else
  if (value == "CC") { return NlpPosTag::CC; } else
  if (value == "CD") { return NlpPosTag::CD; } else
  if (value == "CONJP") { return NlpPosTag::CONJP; } else
  if (value == "DT") { return NlpPosTag::DT; } else
  if (value == "EX") { return NlpPosTag::EX; } else
  if (value == "FRAG") { return NlpPosTag::FRAG; } else
  if (value == "FW") { return NlpPosTag::FW; } else
  if (value == "HYPH") { return NlpPosTag::HYPH; } else
  if (value == "IN") { return NlpPosTag::IN; } else
  if (value == "INTJ") { return NlpPosTag::INTJ; } else
  if (value == "JJ") { return NlpPosTag::JJ; } else
  if (value == "JJR") { return NlpPosTag::JJR; } else
  if (value == "JJS") { return NlpPosTag::JJS; } else
  if (value == "LRB") { return NlpPosTag::LRB; } else
  if (value == "LS") { return NlpPosTag::LS; } else
  if (value == "LST") { return NlpPosTag::LST; } else
  if (value == "MD") { return NlpPosTag::MD; } else
  if (value == "META") { return NlpPosTag::META; } else
  if (value == "NAC") { return NlpPosTag::NAC; } else
  if (value == "NFP") { return NlpPosTag::NFP; } else
  if (value == "NML") { return NlpPosTag::NML; } else
  if (value == "NN") { return NlpPosTag::NN; } else
  if (value == "NNP") { return NlpPosTag::NNP; } else
  if (value == "NNPS") { return NlpPosTag::NNPS; } else
  if (value == "NNS") { return NlpPosTag::NNS; } else
  if (value == "NP") { return NlpPosTag::NP; } else
  if (value == "NPS") { return NlpPosTag::NPS; } else
  if (value == "NP_TMP") { return NlpPosTag::NP_TMP; } else
  if (value == "PDT") { return NlpPosTag::PDT; } else
  if (value == "POS") { return NlpPosTag::POS; } else
  if (value == "PP") { return NlpPosTag::PP; } else
  if (value == "PPZ") { return NlpPosTag::PPZ; } else
  if (value == "PRN") { return NlpPosTag::PRN; } else
  if (value == "PRP") { return NlpPosTag::PRP; } else
  if (value == "PRT") { return NlpPosTag::PRT; } else
  if (value == "PUNCT_COLON") { return NlpPosTag::PUNCT_COLON; } else
  if (value == "PUNCT_COMMA") { return NlpPosTag::PUNCT_COMMA; } else
  if (value == "PUNCT_PERIOD") { return NlpPosTag::PUNCT_PERIOD; } else
  if (value == "PUNCT_QUOTE_CLOSE") { return NlpPosTag::PUNCT_QUOTE_CLOSE; } else
  if (value == "PUNCT_QUOTE_OPEN") { return NlpPosTag::PUNCT_QUOTE_OPEN; } else
  if (value == "QP") { return NlpPosTag::QP; } else
  if (value == "RB") { return NlpPosTag::RB; } else
  if (value == "RBR") { return NlpPosTag::RBR; } else
  if (value == "RBS") { return NlpPosTag::RBS; } else
  if (value == "ROOT") { return NlpPosTag::ROOT; } else
  if (value == "RP") { return NlpPosTag::RP; } else
  if (value == "RRB") { return NlpPosTag::RRB; } else
  if (value == "RRC") { return NlpPosTag::RRC; } else
  if (value == "S") { return NlpPosTag::S; } else
  if (value == "SBAR") { return NlpPosTag::SBAR; } else
  if (value == "SBARQ") { return NlpPosTag::SBARQ; } else
  if (value == "SENT") { return NlpPosTag::SENT; } else
  if (value == "SINV") { return NlpPosTag::SINV; } else
  if (value == "SQ") { return NlpPosTag::SQ; } else
  if (value == "SYM") { return NlpPosTag::SYM; } else
  if (value == "TO") { return NlpPosTag::TO; } else
  if (value == "UCP") { return NlpPosTag::UCP; } else
  if (value == "UH") { return NlpPosTag::UH; } else
  if (value == "VB") { return NlpPosTag::VB; } else
  if (value == "VBD") { return NlpPosTag::VBD; } else
  if (value == "VBG") { return NlpPosTag::VBG; } else
  if (value == "VBN") { return NlpPosTag::VBN; } else
  if (value == "VBP") { return NlpPosTag::VBP; } else
  if (value == "VBZ") { return NlpPosTag::VBZ; } else
  if (value == "VH") { return NlpPosTag::VH; } else
  if (value == "VHD") { return NlpPosTag::VHD; } else
  if (value == "VHG") { return NlpPosTag::VHG; } else
  if (value == "VHN") { return NlpPosTag::VHN; } else
  if (value == "VHP") { return NlpPosTag::VHP; } else
  if (value == "VHZ") { return NlpPosTag::VHZ; } else
  if (value == "VP") { return NlpPosTag::VP; } else
  if (value == "VV") { return NlpPosTag::VV; } else
  if (value == "VVD") { return NlpPosTag::VVD; } else
  if (value == "VVG") { return NlpPosTag::VVG; } else
  if (value == "VVN") { return NlpPosTag::VVN; } else
  if (value == "VVP") { return NlpPosTag::VVP; } else
  if (value == "VVZ") { return NlpPosTag::VVZ; } else
  if (value == "WDT") { return NlpPosTag::WDT; } else
  if (value == "WHADJP") { return NlpPosTag::WHADJP; } else
  if (value == "WHADVP") { return NlpPosTag::WHADVP; } else
  if (value == "WHNP") { return NlpPosTag::WHNP; } else
  if (value == "WHPP") { return NlpPosTag::WHPP; } else
  if (value == "WP") { return NlpPosTag::WP; } else
  if (value == "WP_POS") { return NlpPosTag::WP_POS; } else
  if (value == "WRB") { return NlpPosTag::WRB; } else
  if (value == "X") { return NlpPosTag::X; } else
  { return std::nullopt; }
}
QString enum_serde<NlpPosTag>::to_string(NlpPosTag value) {
  switch (value) {
    case NlpPosTag::ADJP: return "ADJP";
    case NlpPosTag::ADVP: return "ADVP";
    case NlpPosTag::ADD: return "ADD";
    case NlpPosTag::AFX: return "AFX";
    case NlpPosTag::CC: return "CC";
    case NlpPosTag::CD: return "CD";
    case NlpPosTag::CONJP: return "CONJP";
    case NlpPosTag::DT: return "DT";
    case NlpPosTag::EX: return "EX";
    case NlpPosTag::FRAG: return "FRAG";
    case NlpPosTag::FW: return "FW";
    case NlpPosTag::HYPH: return "HYPH";
    case NlpPosTag::IN: return "IN";
    case NlpPosTag::INTJ: return "INTJ";
    case NlpPosTag::JJ: return "JJ";
    case NlpPosTag::JJR: return "JJR";
    case NlpPosTag::JJS: return "JJS";
    case NlpPosTag::LRB: return "LRB";
    case NlpPosTag::LS: return "LS";
    case NlpPosTag::LST: return "LST";
    case NlpPosTag::MD: return "MD";
    case NlpPosTag::META: return "META";
    case NlpPosTag::NAC: return "NAC";
    case NlpPosTag::NFP: return "NFP";
    case NlpPosTag::NML: return "NML";
    case NlpPosTag::NN: return "NN";
    case NlpPosTag::NNP: return "NNP";
    case NlpPosTag::NNPS: return "NNPS";
    case NlpPosTag::NNS: return "NNS";
    case NlpPosTag::NP: return "NP";
    case NlpPosTag::NPS: return "NPS";
    case NlpPosTag::NP_TMP: return "NP_TMP";
    case NlpPosTag::PDT: return "PDT";
    case NlpPosTag::POS: return "POS";
    case NlpPosTag::PP: return "PP";
    case NlpPosTag::PPZ: return "PPZ";
    case NlpPosTag::PRN: return "PRN";
    case NlpPosTag::PRP: return "PRP";
    case NlpPosTag::PRT: return "PRT";
    case NlpPosTag::PUNCT_COLON: return "PUNCT_COLON";
    case NlpPosTag::PUNCT_COMMA: return "PUNCT_COMMA";
    case NlpPosTag::PUNCT_PERIOD: return "PUNCT_PERIOD";
    case NlpPosTag::PUNCT_QUOTE_CLOSE: return "PUNCT_QUOTE_CLOSE";
    case NlpPosTag::PUNCT_QUOTE_OPEN: return "PUNCT_QUOTE_OPEN";
    case NlpPosTag::QP: return "QP";
    case NlpPosTag::RB: return "RB";
    case NlpPosTag::RBR: return "RBR";
    case NlpPosTag::RBS: return "RBS";
    case NlpPosTag::ROOT: return "ROOT";
    case NlpPosTag::RP: return "RP";
    case NlpPosTag::RRB: return "RRB";
    case NlpPosTag::RRC: return "RRC";
    case NlpPosTag::S: return "S";
    case NlpPosTag::SBAR: return "SBAR";
    case NlpPosTag::SBARQ: return "SBARQ";
    case NlpPosTag::SENT: return "SENT";
    case NlpPosTag::SINV: return "SINV";
    case NlpPosTag::SQ: return "SQ";
    case NlpPosTag::SYM: return "SYM";
    case NlpPosTag::TO: return "TO";
    case NlpPosTag::UCP: return "UCP";
    case NlpPosTag::UH: return "UH";
    case NlpPosTag::VB: return "VB";
    case NlpPosTag::VBD: return "VBD";
    case NlpPosTag::VBG: return "VBG";
    case NlpPosTag::VBN: return "VBN";
    case NlpPosTag::VBP: return "VBP";
    case NlpPosTag::VBZ: return "VBZ";
    case NlpPosTag::VH: return "VH";
    case NlpPosTag::VHD: return "VHD";
    case NlpPosTag::VHG: return "VHG";
    case NlpPosTag::VHN: return "VHN";
    case NlpPosTag::VHP: return "VHP";
    case NlpPosTag::VHZ: return "VHZ";
    case NlpPosTag::VP: return "VP";
    case NlpPosTag::VV: return "VV";
    case NlpPosTag::VVD: return "VVD";
    case NlpPosTag::VVG: return "VVG";
    case NlpPosTag::VVN: return "VVN";
    case NlpPosTag::VVP: return "VVP";
    case NlpPosTag::VVZ: return "VVZ";
    case NlpPosTag::WDT: return "WDT";
    case NlpPosTag::WHADJP: return "WHADJP";
    case NlpPosTag::WHADVP: return "WHADVP";
    case NlpPosTag::WHNP: return "WHNP";
    case NlpPosTag::WHPP: return "WHPP";
    case NlpPosTag::WP: return "WP";
    case NlpPosTag::WP_POS: return "WP_POS";
    case NlpPosTag::WRB: return "WRB";
    case NlpPosTag::X: return "X";
    default: throw std::domain_error("Unexpected enum value -- cannot be converted to string");
  }
}