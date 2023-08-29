#include "exporternlp_enums.hpp"
using namespace NLP;

Opt<PosTag> enum_serde<PosTag>::from_string(QString value) {
  if (value == "ADJP") { return PosTag::ADJP; } else
  if (value == "ADVP") { return PosTag::ADVP; } else
  if (value == "CC") { return PosTag::CC; } else
  if (value == "CD") { return PosTag::CD; } else
  if (value == "CONJP") { return PosTag::CONJP; } else
  if (value == "DT") { return PosTag::DT; } else
  if (value == "EX") { return PosTag::EX; } else
  if (value == "FRAG") { return PosTag::FRAG; } else
  if (value == "FW") { return PosTag::FW; } else
  if (value == "HYPH") { return PosTag::HYPH; } else
  if (value == "IN") { return PosTag::IN; } else
  if (value == "INTJ") { return PosTag::INTJ; } else
  if (value == "JJ") { return PosTag::JJ; } else
  if (value == "JJR") { return PosTag::JJR; } else
  if (value == "JJS") { return PosTag::JJS; } else
  if (value == "LS") { return PosTag::LS; } else
  if (value == "LST") { return PosTag::LST; } else
  if (value == "MD") { return PosTag::MD; } else
  if (value == "META") { return PosTag::META; } else
  if (value == "NAC") { return PosTag::NAC; } else
  if (value == "NFP") { return PosTag::NFP; } else
  if (value == "NML") { return PosTag::NML; } else
  if (value == "NN") { return PosTag::NN; } else
  if (value == "NNP") { return PosTag::NNP; } else
  if (value == "NNPS") { return PosTag::NNPS; } else
  if (value == "NNS") { return PosTag::NNS; } else
  if (value == "NP") { return PosTag::NP; } else
  if (value == "NPS") { return PosTag::NPS; } else
  if (value == "NP_TMP") { return PosTag::NP_TMP; } else
  if (value == "PDT") { return PosTag::PDT; } else
  if (value == "POS") { return PosTag::POS; } else
  if (value == "PP") { return PosTag::PP; } else
  if (value == "PPZ") { return PosTag::PPZ; } else
  if (value == "PRN") { return PosTag::PRN; } else
  if (value == "PRP") { return PosTag::PRP; } else
  if (value == "PRT") { return PosTag::PRT; } else
  if (value == "PUNCT_COLON") { return PosTag::PUNCT_COLON; } else
  if (value == "PUNCT_COMMA") { return PosTag::PUNCT_COMMA; } else
  if (value == "PUNCT_PERIOD") { return PosTag::PUNCT_PERIOD; } else
  if (value == "PUNCT_QUOTE_CLOSE") { return PosTag::PUNCT_QUOTE_CLOSE; } else
  if (value == "PUNCT_QUOTE_OPEN") { return PosTag::PUNCT_QUOTE_OPEN; } else
  if (value == "QP") { return PosTag::QP; } else
  if (value == "RB") { return PosTag::RB; } else
  if (value == "RBR") { return PosTag::RBR; } else
  if (value == "RBS") { return PosTag::RBS; } else
  if (value == "ROOT") { return PosTag::ROOT; } else
  if (value == "RP") { return PosTag::RP; } else
  if (value == "RRC") { return PosTag::RRC; } else
  if (value == "S") { return PosTag::S; } else
  if (value == "SBAR") { return PosTag::SBAR; } else
  if (value == "SBARQ") { return PosTag::SBARQ; } else
  if (value == "SENT") { return PosTag::SENT; } else
  if (value == "SINV") { return PosTag::SINV; } else
  if (value == "SQ") { return PosTag::SQ; } else
  if (value == "SYM") { return PosTag::SYM; } else
  if (value == "TO") { return PosTag::TO; } else
  if (value == "UCP") { return PosTag::UCP; } else
  if (value == "UH") { return PosTag::UH; } else
  if (value == "VB") { return PosTag::VB; } else
  if (value == "VBD") { return PosTag::VBD; } else
  if (value == "VBG") { return PosTag::VBG; } else
  if (value == "VBN") { return PosTag::VBN; } else
  if (value == "VBP") { return PosTag::VBP; } else
  if (value == "VBZ") { return PosTag::VBZ; } else
  if (value == "VH") { return PosTag::VH; } else
  if (value == "VHD") { return PosTag::VHD; } else
  if (value == "VHG") { return PosTag::VHG; } else
  if (value == "VHN") { return PosTag::VHN; } else
  if (value == "VHP") { return PosTag::VHP; } else
  if (value == "VHZ") { return PosTag::VHZ; } else
  if (value == "VP") { return PosTag::VP; } else
  if (value == "VV") { return PosTag::VV; } else
  if (value == "VVD") { return PosTag::VVD; } else
  if (value == "VVG") { return PosTag::VVG; } else
  if (value == "VVN") { return PosTag::VVN; } else
  if (value == "VVP") { return PosTag::VVP; } else
  if (value == "VVZ") { return PosTag::VVZ; } else
  if (value == "WDT") { return PosTag::WDT; } else
  if (value == "WHADJP") { return PosTag::WHADJP; } else
  if (value == "WHADVP") { return PosTag::WHADVP; } else
  if (value == "WHNP") { return PosTag::WHNP; } else
  if (value == "WHPP") { return PosTag::WHPP; } else
  if (value == "WP") { return PosTag::WP; } else
  if (value == "WRB") { return PosTag::WRB; } else
  if (value == "X") { return PosTag::X; } else
  { return std::nullopt; }
}
QString enum_serde<PosTag>::to_string(PosTag value) {
  switch (value) {
    case PosTag::ADJP: return "ADJP";
    case PosTag::ADVP: return "ADVP";
    case PosTag::CC: return "CC";
    case PosTag::CD: return "CD";
    case PosTag::CONJP: return "CONJP";
    case PosTag::DT: return "DT";
    case PosTag::EX: return "EX";
    case PosTag::FRAG: return "FRAG";
    case PosTag::FW: return "FW";
    case PosTag::HYPH: return "HYPH";
    case PosTag::IN: return "IN";
    case PosTag::INTJ: return "INTJ";
    case PosTag::JJ: return "JJ";
    case PosTag::JJR: return "JJR";
    case PosTag::JJS: return "JJS";
    case PosTag::LS: return "LS";
    case PosTag::LST: return "LST";
    case PosTag::MD: return "MD";
    case PosTag::META: return "META";
    case PosTag::NAC: return "NAC";
    case PosTag::NFP: return "NFP";
    case PosTag::NML: return "NML";
    case PosTag::NN: return "NN";
    case PosTag::NNP: return "NNP";
    case PosTag::NNPS: return "NNPS";
    case PosTag::NNS: return "NNS";
    case PosTag::NP: return "NP";
    case PosTag::NPS: return "NPS";
    case PosTag::NP_TMP: return "NP_TMP";
    case PosTag::PDT: return "PDT";
    case PosTag::POS: return "POS";
    case PosTag::PP: return "PP";
    case PosTag::PPZ: return "PPZ";
    case PosTag::PRN: return "PRN";
    case PosTag::PRP: return "PRP";
    case PosTag::PRT: return "PRT";
    case PosTag::PUNCT_COLON: return "PUNCT_COLON";
    case PosTag::PUNCT_COMMA: return "PUNCT_COMMA";
    case PosTag::PUNCT_PERIOD: return "PUNCT_PERIOD";
    case PosTag::PUNCT_QUOTE_CLOSE: return "PUNCT_QUOTE_CLOSE";
    case PosTag::PUNCT_QUOTE_OPEN: return "PUNCT_QUOTE_OPEN";
    case PosTag::QP: return "QP";
    case PosTag::RB: return "RB";
    case PosTag::RBR: return "RBR";
    case PosTag::RBS: return "RBS";
    case PosTag::ROOT: return "ROOT";
    case PosTag::RP: return "RP";
    case PosTag::RRC: return "RRC";
    case PosTag::S: return "S";
    case PosTag::SBAR: return "SBAR";
    case PosTag::SBARQ: return "SBARQ";
    case PosTag::SENT: return "SENT";
    case PosTag::SINV: return "SINV";
    case PosTag::SQ: return "SQ";
    case PosTag::SYM: return "SYM";
    case PosTag::TO: return "TO";
    case PosTag::UCP: return "UCP";
    case PosTag::UH: return "UH";
    case PosTag::VB: return "VB";
    case PosTag::VBD: return "VBD";
    case PosTag::VBG: return "VBG";
    case PosTag::VBN: return "VBN";
    case PosTag::VBP: return "VBP";
    case PosTag::VBZ: return "VBZ";
    case PosTag::VH: return "VH";
    case PosTag::VHD: return "VHD";
    case PosTag::VHG: return "VHG";
    case PosTag::VHN: return "VHN";
    case PosTag::VHP: return "VHP";
    case PosTag::VHZ: return "VHZ";
    case PosTag::VP: return "VP";
    case PosTag::VV: return "VV";
    case PosTag::VVD: return "VVD";
    case PosTag::VVG: return "VVG";
    case PosTag::VVN: return "VVN";
    case PosTag::VVP: return "VVP";
    case PosTag::VVZ: return "VVZ";
    case PosTag::WDT: return "WDT";
    case PosTag::WHADJP: return "WHADJP";
    case PosTag::WHADVP: return "WHADVP";
    case PosTag::WHNP: return "WHNP";
    case PosTag::WHPP: return "WHPP";
    case PosTag::WP: return "WP";
    case PosTag::WRB: return "WRB";
    case PosTag::X: return "X";
    default: throw std::domain_error("Unexpected enum value -- cannot be converted to string");
  }
}