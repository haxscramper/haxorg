#include "exporterlatex.hpp"
#include <exporters/ExporterUltraplain.hpp>
#include <hstd/stdlib/algorithms.hpp>

#pragma clang diagnostic ignored "-Wreorder-init-list"

using namespace sem;
using osk  = OrgSemKind;
using Prop = Subtree::Property;

struct SymDef {
    QString latex;
    QString html;
    QString ascii;
    QString latin1;
    QString utf8;
};

#include <exporters/Exporter.cpp>

template class Exporter<ExporterLatex, layout::Block::Ptr>;


UnorderedMap<QString, SymDef> definitions{
    // clang-format off
    {"Agrave", SymDef{"\\`{A}",  "&Agrave;", "A",  "À",  "À"}},
    {"agrave", SymDef{"\\`{a}",  "&agrave;", "a",  "à",  "à"}},
    {"Aacute", SymDef{"\\'{A}",  "&Aacute;", "A",  "Á",  "Á"}},
    {"aacute", SymDef{"\\'{a}",  "&aacute;", "a",  "á",  "á"}},
    {"Acirc",  SymDef{"\\^{A}",  "&Acirc;",  "A",  "Â",  "Â"}},
    {"acirc",  SymDef{"\\^{a}",  "&acirc;",  "a",  "â",  "â"}},
    {"Amacr",  SymDef{"\\={A}",  "&Amacr;",  "A",  "Ã",  "Ã"}},
    {"amacr",  SymDef{"\\={a}",  "&amacr;",  "a",  "ã",  "ã"}},
    {"Atilde", SymDef{"\\~{A}",  "&Atilde;", "A",  "Ã",  "Ã"}},
    {"atilde", SymDef{"\\~{a}",  "&atilde;", "a",  "ã",  "ã"}},
    {"Auml",   SymDef{"\\\"{A}", "&Auml;",   "Ae", "Ä",  "Ä"}},
    {"auml",   SymDef{"\\\"{a}", "&auml;",   "ae", "ä",  "ä"}},
    {"Aring",  SymDef{"\\AA{}",  "&Aring;",  "A",  "Å",  "Å"}},
    {"AA",     SymDef{"\\AA{}",  "&Aring;",  "A",  "Å",  "Å"}},
    {"aring",  SymDef{"\\aa{}",  "&aring;",  "a",  "å",  "å"}},
    {"AElig",  SymDef{"\\AE{}",  "&AElig;",  "AE", "Æ",  "Æ"}},
    {"aelig",  SymDef{"\\ae{}",  "&aelig;",  "ae", "æ",  "æ"}},
    {"Ccedil", SymDef{"\\c{C}",  "&Ccedil;", "C",  "Ç",  "Ç"}},
    {"ccedil", SymDef{"\\c{c}",  "&ccedil;", "c",  "ç",  "ç"}},
    {"Egrave", SymDef{"\\`{E}",  "&Egrave;", "E",  "È",  "È"}},
    {"egrave", SymDef{"\\`{e}",  "&egrave;", "e",  "è",  "è"}},
    {"Eacute", SymDef{"\\'{E}",  "&Eacute;", "E",  "É",  "É"}},
    {"eacute", SymDef{"\\'{e}",  "&eacute;", "e",  "é",  "é"}},
    {"Ecirc",  SymDef{"\\^{E}",  "&Ecirc;",  "E",  "Ê",  "Ê"}},
    {"ecirc",  SymDef{"\\^{e}",  "&ecirc;",  "e",  "ê",  "ê"}},
    {"Euml",   SymDef{"\\\"{E}", "&Euml;",   "E",  "Ë",  "Ë"}},
    {"euml",   SymDef{"\\\"{e}", "&euml;",   "e",  "ë",  "ë"}},
    {"Igrave", SymDef{"\\`{I}",  "&Igrave;", "I",  "Ì",  "Ì"}},
    {"igrave", SymDef{"\\`{i}",  "&igrave;", "i",  "ì",  "ì"}},
    {"Iacute", SymDef{"\\'{I}",  "&Iacute;", "I",  "Í",  "Í"}},
    {"iacute", SymDef{"\\'{i}",  "&iacute;", "i",  "í",  "í"}},
    {"Idot",   SymDef{"\\.{I}",  "&idot;",   "I",  "İ",  "İ"}},
    {"inodot", SymDef{"\\i",     "&inodot;", "i",  "ı",  "ı"}},
    {"Icirc",  SymDef{"\\^{I}",  "&Icirc;",  "I",  "Î",  "Î"}},
    {"icirc",  SymDef{"\\^{i}",  "&icirc;",  "i",  "î",  "î"}},
    {"Iuml",   SymDef{"\\\"{I}", "&Iuml;",   "I",  "Ï",  "Ï"}},
    {"iuml",   SymDef{"\\\"{i}", "&iuml;",   "i",  "ï",  "ï"}},
    {"Ntilde", SymDef{"\\~{N}",  "&Ntilde;", "N",  "Ñ",  "Ñ"}},
    {"ntilde", SymDef{"\\~{n}",  "&ntilde;", "n",  "ñ",  "ñ"}},
    {"Ograve", SymDef{"\\`{O}",  "&Ograve;", "O",  "Ò",  "Ò"}},
    {"ograve", SymDef{"\\`{o}",  "&ograve;", "o",  "ò",  "ò"}},
    {"Oacute", SymDef{"\\'{O}",  "&Oacute;", "O",  "Ó",  "Ó"}},
    {"oacute", SymDef{"\\'{o}",  "&oacute;", "o",  "ó",  "ó"}},
    {"Ocirc",  SymDef{"\\^{O}",  "&Ocirc;",  "O",  "Ô",  "Ô"}},
    {"ocirc",  SymDef{"\\^{o}",  "&ocirc;",  "o",  "ô",  "ô"}},
    {"Otilde", SymDef{"\\~{O}",  "&Otilde;", "O",  "Õ",  "Õ"}},
    {"otilde", SymDef{"\\~{o}",  "&otilde;", "o",  "õ",  "õ"}},
    {"Ouml",   SymDef{"\\\"{O}", "&Ouml;",   "Oe", "Ö",  "Ö"}},
    {"ouml",   SymDef{"\\\"{o}", "&ouml;",   "oe", "ö",  "ö"}},
    {"Oslash", SymDef{"\\O",     "&Oslash;", "O",  "Ø",  "Ø"}},
    {"oslash", SymDef{"\\o{}",   "&oslash;", "o",  "ø",  "ø"}},
    {"OElig",  SymDef{"\\OE{}",  "&OElig;",  "OE", "OE", "Œ"}},
    {"oelig",  SymDef{"\\oe{}",  "&oelig;",  "oe", "oe", "œ"}},
    {"Scaron", SymDef{"\\v{S}",  "&Scaron;", "S",  "S",  "Š"}},
    {"scaron", SymDef{"\\v{s}",  "&scaron;", "s",  "s",  "š"}},
    {"szlig",  SymDef{"\\ss{}",  "&szlig;",  "ss", "ß",  "ß"}},
    {"Ugrave", SymDef{"\\`{U}",  "&Ugrave;", "U",  "Ù",  "Ù"}},
    {"ugrave", SymDef{"\\`{u}",  "&ugrave;", "u",  "ù",  "ù"}},
    {"Uacute", SymDef{"\\'{U}",  "&Uacute;", "U",  "Ú",  "Ú"}},
    {"uacute", SymDef{"\\'{u}",  "&uacute;", "u",  "ú",  "ú"}},
    {"Ucirc",  SymDef{"\\^{U}",  "&Ucirc;",  "U",  "Û",  "Û"}},
    {"ucirc",  SymDef{"\\^{u}",  "&ucirc;",  "u",  "û",  "û"}},
    {"Uuml",   SymDef{"\\\"{U}", "&Uuml;",   "Ue", "Ü",  "Ü"}},
    {"uuml",   SymDef{"\\\"{u}", "&uuml;",   "ue", "ü",  "ü"}},
    {"Yacute", SymDef{"\\'{Y}",  "&Yacute;", "Y",  "Ý",  "Ý"}},
    {"yacute", SymDef{"\\'{y}",  "&yacute;", "y",  "ý",  "ý"}},
    {"Yuml",   SymDef{"\\\"{Y}", "&Yuml;",   "Y",  "Y",  "Ÿ"}},
    {"yuml",   SymDef{"\\\"{y}", "&yuml;",   "y",  "ÿ",  "ÿ"}},

    {"fnof",   SymDef{"\\textit{f}", "&fnof;",   "f",           "f",         "ƒ"}},
    {"real",   SymDef{"\\Re",        "&real;",   "R",           "R",         "ℜ"}},
    {"image",  SymDef{"\\Im",        "&image;",  "I",           "I",         "ℑ"}},
    {"weierp", SymDef{"\\wp",        "&weierp;", "P",           "P",         "℘"}},
    {"ell",    SymDef{"\\ell",       "&ell;",    "ell",         "ell",       "ℓ"}},
    {"imath",  SymDef{"\\imath",     "&imath;",  "[dotless i]", "dotless i", "ı"}},
    {"jmath",  SymDef{"\\jmath",     "&jmath;",  "[dotless j]", "dotless j", "ȷ"}},

    {"Alpha",      SymDef{"A",            "&Alpha;",    "Alpha",                  "Alpha",                  "Α"}},
    {"alpha",      SymDef{"\\alpha",      "&alpha;",    "alpha",                  "alpha",                  "α"}},
    {"Beta",       SymDef{"B",            "&Beta;",     "Beta",                   "Beta",                   "Β"}},
    {"beta",       SymDef{"\\beta",       "&beta;",     "beta",                   "beta",                   "β"}},
    {"Gamma",      SymDef{"\\Gamma",      "&Gamma;",    "Gamma",                  "Gamma",                  "Γ"}},
    {"gamma",      SymDef{"\\gamma",      "&gamma;",    "gamma",                  "gamma",                  "γ"}},
    {"Delta",      SymDef{"\\Delta",      "&Delta;",    "Delta",                  "Delta",                  "Δ"}},
    {"delta",      SymDef{"\\delta",      "&delta;",    "delta",                  "delta",                  "δ"}},
    {"Epsilon",    SymDef{"E",            "&Epsilon;",  "Epsilon",                "Epsilon",                "Ε"}},
    {"epsilon",    SymDef{"\\epsilon",    "&epsilon;",  "epsilon",                "epsilon",                "ε"}},
    {"varepsilon", SymDef{"\\varepsilon", "&epsilon;",  "varepsilon",             "varepsilon",             "ε"}},
    {"Zeta",       SymDef{"Z",            "&Zeta;",     "Zeta",                   "Zeta",                   "Ζ"}},
    {"zeta",       SymDef{"\\zeta",       "&zeta;",     "zeta",                   "zeta",                   "ζ"}},
    {"Eta",        SymDef{"H",            "&Eta;",      "Eta",                    "Eta",                    "Η"}},
    {"eta",        SymDef{"\\eta",        "&eta;",      "eta",                    "eta",                    "η"}},
    {"Theta",      SymDef{"\\Theta",      "&Theta;",    "Theta",                  "Theta",                  "Θ"}},
    {"theta",      SymDef{"\\theta",      "&theta;",    "theta",                  "theta",                  "θ"}},
    {"thetasym",   SymDef{"\\vartheta",   "&thetasym;", "theta",                  "theta",                  "ϑ"}},
    {"vartheta",   SymDef{"\\vartheta",   "&thetasym;", "theta",                  "theta",                  "ϑ"}},
    {"Iota",       SymDef{"I",            "&Iota;",     "Iota",                   "Iota",                   "Ι"}},
    {"iota",       SymDef{"\\iota",       "&iota;",     "iota",                   "iota",                   "ι"}},
    {"Kappa",      SymDef{"K",            "&Kappa;",    "Kappa",                  "Kappa",                  "Κ"}},
    {"kappa",      SymDef{"\\kappa",      "&kappa;",    "kappa",                  "kappa",                  "κ"}},
    {"Lambda",     SymDef{"\\Lambda",     "&Lambda;",   "Lambda",                 "Lambda",                 "Λ"}},
    {"lambda",     SymDef{"\\lambda",     "&lambda;",   "lambda",                 "lambda",                 "λ"}},
    {"Mu",         SymDef{"M",            "&Mu;",       "Mu",                     "Mu",                     "Μ"}},
    {"mu",         SymDef{"\\mu",         "&mu;",       "mu",                     "mu",                     "μ"}},
    {"nu",         SymDef{"\\nu",         "&nu;",       "nu",                     "nu",                     "ν"}},
    {"Nu",         SymDef{"N",            "&Nu;",       "Nu",                     "Nu",                     "Ν"}},
    {"Xi",         SymDef{"\\Xi",         "&Xi;",       "Xi",                     "Xi",                     "Ξ"}},
    {"xi",         SymDef{"\\xi",         "&xi;",       "xi",                     "xi",                     "ξ"}},
    {"Omicron",    SymDef{"O",            "&Omicron;",  "Omicron",                "Omicron",                "Ο"}},
    {"omicron",    SymDef{"\\textit{o}",  "&omicron;",  "omicron",                "omicron",                "ο"}},
    {"Pi",         SymDef{"\\Pi",         "&Pi;",       "Pi",                     "Pi",                     "Π"}},
    {"pi",         SymDef{"\\pi",         "&pi;",       "pi",                     "pi",                     "π"}},
    {"Rho",        SymDef{"P",            "&Rho;",      "Rho",                    "Rho",                    "Ρ"}},
    {"rho",        SymDef{"\\rho",        "&rho;",      "rho",                    "rho",                    "ρ"}},
    {"Sigma",      SymDef{"\\Sigma",      "&Sigma;",    "Sigma",                  "Sigma",                  "Σ"}},
    {"sigma",      SymDef{"\\sigma",      "&sigma;",    "sigma",                  "sigma",                  "σ"}},
    {"sigmaf",     SymDef{"\\varsigma",   "&sigmaf;",   "sigmaf",                 "sigmaf",                 "ς"}},
    {"varsigma",   SymDef{"\\varsigma",   "&sigmaf;",   "varsigma",               "varsigma",               "ς"}},
    {"Tau",        SymDef{"T",            "&Tau;",      "Tau",                    "Tau",                    "Τ"}},
    {"Upsilon",    SymDef{"\\Upsilon",    "&Upsilon;",  "Upsilon",                "Upsilon",                "Υ"}},
    {"upsih",      SymDef{"\\Upsilon",    "&upsih;",    "upsilon",                "upsilon",                "ϒ"}},
    {"upsilon",    SymDef{"\\upsilon",    "&upsilon;",  "upsilon",                "upsilon",                "υ"}},
    {"Phi",        SymDef{"\\Phi",        "&Phi;",      "Phi",                    "Phi",                    "Φ"}},
    {"phi",        SymDef{"\\phi",        "&phi;",      "phi",                    "phi",                    "ɸ"}},
    {"varphi",     SymDef{"\\varphi",     "&varphi;",   "varphi",                 "varphi",                 "φ"}},
    {"Chi",        SymDef{"X",            "&Chi;",      "Chi",                    "Chi",                    "Χ"}},
    {"chi",        SymDef{"\\chi",        "&chi;",      "chi",                    "chi",                    "χ"}},
    {"acutex",     SymDef{"\\acute x",    "&acute;x",   "'x",                     "'x",                     "𝑥́"}},
    {"Psi",        SymDef{"\\Psi",        "&Psi;",      "Psi",                    "Psi",                    "Ψ"}},
    {"psi",        SymDef{"\\psi",        "&psi;",      "psi",                    "psi",                    "ψ"}},
    {"tau",        SymDef{"\\tau",        "&tau;",      "tau",                    "tau",                    "τ"}},
    {"Omega",      SymDef{"\\Omega",      "&Omega;",    "Omega",                  "Omega",                  "Ω"}},
    {"omega",      SymDef{"\\omega",      "&omega;",    "omega",                  "omega",                  "ω"}},
    {"piv",        SymDef{"\\varpi",      "&piv;",      "omega-pi",               "omega-pi",               "ϖ"}},
    {"varpi",      SymDef{"\\varpi",      "&piv;",      "omega-pi",               "omega-pi",               "ϖ"}},
    {"partial",    SymDef{"\\partial",     "&part;",     "[partial differential]", "[partial differential]", "∂"}},

    {"aleph", SymDef{"\\aleph",  "&aleph;",  "aleph", "aleph", "ℵ"}},
    {"gimel", SymDef{"\\gimel",  "&gimel;",  "gimel", "gimel", "ℷ"}},
    {"beth",  SymDef{"\\beth",   "&beth;",   "beth",  "beth",  "ב"}},
    {"dalet", SymDef{"\\daleth", "&daleth;", "dalet", "dalet", "ד"}},

    {"ETH",   SymDef{"\\DH{}", "&ETH;",   "D",  "Ð", "Ð"}},
    {"eth",   SymDef{"\\dh{}", "&eth;",   "dh", "ð", "ð"}},
    {"THORN", SymDef{"\\TH{}", "&THORN;", "TH", "Þ", "Þ"}},
    {"thorn", SymDef{"\\th{}", "&thorn;", "th", "þ", "þ"}},

    {"dots",   SymDef{"\\dots{}",               "&hellip;", "...", "...", "…"}},
    {"cdots",  SymDef{"\\cdots{}",               "&ctdot;",  "...", "...", "⋯"}},
    {"hellip", SymDef{"\\dots{}",               "&hellip;", "...", "...", "…"}},
    {"middot", SymDef{"\\textperiodcentered{}", "&middot;", ".",   "·",   "·"}},
    {"iexcl",  SymDef{"!`",                     "&iexcl;",  "!",   "¡",   "¡"}},
    {"iquest", SymDef{"?`",                     "&iquest;", "?",   "¿",   "¿"}},

    {"shy",   SymDef{"\\-", "&shy;",   "",   "",   ""}},
    {"ndash", SymDef{"--",  "&ndash;", "-",  "-",  "–"}},
    {"mdash", SymDef{"---", "&mdash;", "--", "--", "—"}},

    {"quot",   SymDef{"\\textquotedbl{}",      "&quot;",   "\"", "\"", "\""}},
    {"acute",  SymDef{"\\textasciiacute{}",    "&acute;",  "'",  "´",  "´"}},
    {"ldquo",  SymDef{"\\textquotedblleft{}",  "&ldquo;",  "\"", "\"", "“"}},
    {"rdquo",  SymDef{"\\textquotedblright{}", "&rdquo;",  "\"", "\"", "”"}},
    {"bdquo",  SymDef{"\\quotedblbase{}",      "&bdquo;",  "\"", "\"", "„"}},
    {"lsquo",  SymDef{"\\textquoteleft{}",     "&lsquo;",  "`",  "`",  "‘"}},
    {"rsquo",  SymDef{"\\textquoteright{}",    "&rsquo;",  "'",  "'",  "’"}},
    {"sbquo",  SymDef{"\\quotesinglbase{}",    "&sbquo;",  ",",  ",",  "‚"}},
    {"laquo",  SymDef{"\\guillemotleft{}",     "&laquo;",  "<<", "«",  "«"}},
    {"raquo",  SymDef{"\\guillemotright{}",    "&raquo;",  ">>", "»",  "»"}},
    {"lsaquo", SymDef{"\\guilsinglleft{}",     "&lsaquo;", "<",  "<",  "‹"}},
    {"rsaquo", SymDef{"\\guilsinglright{}",    "&rsaquo;", ">",  ">",  "›"}},

    {"circ",      SymDef{"\\^{}",               "&circ;",   "^",              "^",              "∘"}},
    {"vert",      SymDef{"\\vert{}",             "&vert;",   "|",              "|",              "|"}},
    {"vbar",      SymDef{"|",                   "|",        "|",              "|",              "|"}},
    {"brvbar",    SymDef{"\\textbrokenbar{}",   "&brvbar;", "|",              "¦",              "¦"}},
    {"S",         SymDef{"\\S",                 "&sect;",   "paragraph",      "§",              "§"}},
    {"sect",      SymDef{"\\S",                 "&sect;",   "paragraph",      "§",              "§"}},
    {"amp",       SymDef{"\\&",                 "&amp;",    "&",              "&",              "&"}},
    {"lt",        SymDef{"\\textless{}",        "&lt;",     "<",              "<",              "<"}},
    {"gt",        SymDef{"\\textgreater{}",     "&gt;",     ">",              ">",              ">"}},
    {"tilde",     SymDef{"\\textasciitilde{}",  "~",        "~",              "~",              "~"}},
    {"slash",     SymDef{"/",                   "/",        "/",              "/",              "/"}},
    {"plus",      SymDef{"+",                   "+",        "+",              "+",              "+"}},
    {"under",     SymDef{"\\_",                 "_",        "_",              "_",              "_"}},
    {"equal",     SymDef{"=",                   "=",        "=",              "=",              "="}},
    {"asciicirc", SymDef{"\\textasciicircum{}", "^",        "^",              "^",              "^"}},
    {"dagger",    SymDef{"\\textdagger{}",      "&dagger;", "[dagger]",       "[dagger]",       "†"}},
    {"dag",       SymDef{"\\dag{}",             "&dagger;", "[dagger]",       "[dagger]",       "†"}},
    {"Dagger",    SymDef{"\\textdaggerdbl{}",   "&Dagger;", "[doubledagger]", "[doubledagger]", "‡"}},
    {"ddag",      SymDef{"\\ddag{}",            "&Dagger;", "[doubledagger]", "[doubledagger]", "‡"}},

    {"nbsp",   SymDef{"~",               "&nbsp;",   " ", "\x00A0", "\x00A0"}},
    {"ensp",   SymDef{"\\hspace*{.5em}", "&ensp;",   " ", " ",      " "}},
    {"emsp",   SymDef{"\\hspace*{1em}",  "&emsp;",   " ", " ",      " "}},
    {"thinsp", SymDef{"\\hspace*{.2em}", "&thinsp;", " ", " ",      " "}},

    {"curren", SymDef{"\\textcurrency{}", "&curren;", "curr.", "¤",   "¤"}},
    {"cent",   SymDef{"\\textcent{}",     "&cent;",   "cent",  "¢",   "¢"}},
    {"pound",  SymDef{"\\pounds{}",       "&pound;",  "pound", "£",   "£"}},
    {"yen",    SymDef{"\\textyen{}",      "&yen;",    "yen",   "¥",   "¥"}},
    {"euro",   SymDef{"\\texteuro{}",     "&euro;",   "EUR",   "EUR", "€"}},
    {"EUR",    SymDef{"\\texteuro{}",     "&euro;",   "EUR",   "EUR", "€"}},
    {"dollar", SymDef{"\\$",              "$",        "$",     "$",   "$"}},
    {"USD",    SymDef{"\\$",              "$",        "$",     "$",   "$"}},

    {"copy",  SymDef{"\\textcopyright{}",  "&copy;",  "(c)", "©",  "©"}},
    {"reg",   SymDef{"\\textregistered{}", "&reg;",   "(r)", "®",  "®"}},
    {"trade", SymDef{"\\texttrademark{}",  "&trade;", "TM",  "TM", "™"}},

    {"minus",     SymDef{"-",                      "&minus;",  "-",                  "-",                  "−"}},
    {"pm",        SymDef{"\\textpm{}",            "&plusmn;", "+-",                 "±",                  "±"}},
    {"plusmn",    SymDef{"\\textpm{}",            "&plusmn;", "+-",                 "±",                  "±"}},
    {"times",     SymDef{"\\texttimes{}",         "&times;",  "*",                  "×",                  "×"}},
    {"frasl",     SymDef{"/",                     "&frasl;",  "/",                  "/",                  "⁄"}},
    {"colon",     SymDef{"\\colon",                ":",        ":",                  ":",                  ":"}},
    {"div",       SymDef{"\\textdiv{}",           "&divide;", "/",                  "÷",                  "÷"}},
    {"frac12",    SymDef{"\\textonehalf{}",       "&frac12;", "1/2",                "½",                  "½"}},
    {"frac14",    SymDef{"\\textonequarter{}",    "&frac14;", "1/4",                "¼",                  "¼"}},
    {"frac34",    SymDef{"\\textthreequarters{}", "&frac34;", "3/4",                "¾",                  "¾"}},
    {"permil",    SymDef{"\\textperthousand{}",   "&permil;", "per thousand",       "per thousand",       "‰"}},
    {"sup1",      SymDef{"\\textonesuperior{}",   "&sup1;",   "^1",                 "¹",                  "¹"}},
    {"sup2",      SymDef{"\\texttwosuperior{}",   "&sup2;",   "^2",                 "²",                  "²"}},
    {"sup3",      SymDef{"\\textthreesuperior{}", "&sup3;",   "^3",                 "³",                  "³"}},
    {"radic",     SymDef{"\\sqrt{\\,}",            "&radic;",  "[square root]",      "[square root]",      "√"}},
    {"sum",       SymDef{"\\sum",                  "&sum;",    "[sum]",              "[sum]",              "∑"}},
    {"prod",      SymDef{"\\prod",                 "&prod;",   "[product]",          "[n-ary product]",    "∏"}},
    {"micro",     SymDef{"\\textmu{}",            "&micro;",  "micro",              "µ",                  "µ"}},
    {"macr",      SymDef{"\\textasciimacron{}",   "&macr;",   "[macron]",           "¯",                  "¯"}},
    {"deg",       SymDef{"\\textdegree{}",        "&deg;",    "degree",             "°",                  "°"}},
    {"prime",     SymDef{"\\prime",                "&prime;",  "'",                  "'",                  "′"}},
    {"Prime",     SymDef{"\\prime{}\\prime",       "&Prime;",  "''",                 "''",                 "″"}},
    {"infin",     SymDef{"\\infty",                "&infin;",  "[infinity]",         "[infinity]",         "∞"}},
    {"infty",     SymDef{"\\infty",                "&infin;",  "[infinity]",         "[infinity]",         "∞"}},
    {"prop",      SymDef{"\\propto",               "&prop;",   "[proportional to]",  "[proportional to]",  "∝"}},
    {"propto",    SymDef{"\\propto",               "&prop;",   "[proportional to]",  "[proportional to]",  "∝"}},
    {"not",       SymDef{"\\textlnot{}",          "&not;",    "[angled dash]",      "¬",                  "¬"}},
    {"neg",       SymDef{"\\neg{}",                "&not;",    "[angled dash]",      "¬",                  "¬"}},
    {"land",      SymDef{"\\land",                 "&and;",    "[logical and]",      "[logical and]",      "∧"}},
    {"wedge",     SymDef{"\\wedge",                "&and;",    "[logical and]",      "[logical and]",      "∧"}},
    {"lor",       SymDef{"\\lor",                  "&or;",     "[logical or]",       "[logical or]",       "∨"}},
    {"vee",       SymDef{"\\vee",                  "&or;",     "[logical or]",       "[logical or]",       "∨"}},
    {"cap",       SymDef{"\\cap",                  "&cap;",    "[intersection]",     "[intersection]",     "∩"}},
    {"cup",       SymDef{"\\cup",                  "&cup;",    "[union]",            "[union]",            "∪"}},
    {"smile",     SymDef{"\\smile",                "&smile;",  "[cup product]",      "[cup product]",      "⌣"}},
    {"frown",     SymDef{"\\frown",                "&frown;",  "[Cap product]",      "[cap product]",      "⌢"}},
    {"int",       SymDef{"\\int",                  "&int;",    "[integral]",         "[integral]",         "∫"}},
    {"therefore", SymDef{"\\therefore",            "&there4;", "[therefore]",        "[therefore]",        "∴"}},
    {"there4",    SymDef{"\\therefore",            "&there4;", "[therefore]",        "[therefore]",        "∴"}},
    {"because",   SymDef{"\\because",              "&because;","[because]",          "[because]",          "∵"}},
    {"sim",       SymDef{"\\sim",                  "&sim;",    "~",                  "~",                  "∼"}},
    {"cong",      SymDef{"\\cong",                 "&cong;",   "[approx. equal to]", "[approx. equal to]", "≅"}},
    {"simeq",     SymDef{"\\simeq",                "&cong;",   "[approx. equal to]", "[approx. equal to]", "≅"}},
    {"asymp",     SymDef{"\\asymp",                "&asymp;",  "[almost equal to]",  "[almost equal to]",  "≈"}},
    {"approx",    SymDef{"\\approx",               "&asymp;",  "[almost equal to]",  "[almost equal to]",  "≈"}},
    {"ne",        SymDef{"\\ne",                   "&ne;",     "[not equal to]",     "[not equal to]",     "≠"}},
    {"neq",       SymDef{"\\neq",                  "&ne;",     "[not equal to]",     "[not equal to]",     "≠"}},
    {"equiv",     SymDef{"\\equiv",                "&equiv;",  "[identical to]",     "[identical to]",     "≡"}},

    {"triangleq",   SymDef{"\\triangleq",   "&triangleq;", "[defined to]",                                  "[defined to]",                                  "≜"}},
    {"le",          SymDef{"\\le",          "&le;",        "<=",                                            "<=",                                            "≤"}},
    {"leq",         SymDef{"\\le",          "&le;",        "<=",                                            "<=",                                            "≤"}},
    {"ge",          SymDef{"\\ge",          "&ge;",        ">=",                                            ">=",                                            "≥"}},
    {"geq",         SymDef{"\\ge",          "&ge;",        ">=",                                            ">=",                                            "≥"}},
    {"lessgtr",     SymDef{"\\lessgtr",     "&lessgtr;",   "[less than or greater than]",                   "[less than or greater than]",                   "≶"}},
    {"lesseqgtr",   SymDef{"\\lesseqgtr",   "&lesseqgtr;", "[less than or equal or greater than or equal]", "[less than or equal or greater than or equal]", "⋚"}},
    {"ll",          SymDef{"\\ll",          "&Lt;",        "<<",                                            "<<",                                            "≪"}},
    {"Ll",          SymDef{"\\lll",         "&Ll;",        "<<<",                                           "<<<",                                           "⋘"}},
    {"lll",         SymDef{"\\lll",         "&Ll;",        "<<<",                                           "<<<",                                           "⋘"}},
    {"gg",          SymDef{"\\gg",          "&Gt;",        ">>",                                            ">>",                                            "≫"}},
    {"Gg",          SymDef{"\\ggg",         "&Gg;",        ">>>",                                           ">>>",                                           "⋙"}},
    {"ggg",         SymDef{"\\ggg",         "&Gg;",        ">>>",                                           ">>>",                                           "⋙"}},
    {"prec",        SymDef{"\\prec",        "&pr;",        "[precedes]",                                    "[precedes]",                                    "≺"}},
    {"preceq",      SymDef{"\\preceq",      "&prcue;",     "[precedes or equal]",                           "[precedes or equal]",                           "≼"}},
    {"preccurlyeq", SymDef{"\\preccurlyeq", "&prcue;",     "[precedes or equal]",                           "[precedes or equal]",                           "≼"}},
    {"succ",        SymDef{"\\succ",        "&sc;",        "[succeeds]",                                    "[succeeds]",                                    "≻"}},
    {"succeq",      SymDef{"\\succeq",      "&sccue;",     "[succeeds or equal]",                           "[succeeds or equal]",                           "≽"}},
    {"succcurlyeq", SymDef{"\\succcurlyeq", "&sccue;",     "[succeeds or equal]",                           "[succeeds or equal]",                           "≽"}},
    {"sub",         SymDef{"\\subset",      "&sub;",       "[subset of]",                                   "[subset of]",                                   "⊂"}},
    {"subset",      SymDef{"\\subset",      "&sub;",       "[subset of]",                                   "[subset of]",                                   "⊂"}},
    {"sup",         SymDef{"\\supset",      "&sup;",       "[superset of]",                                 "[superset of]",                                 "⊃"}},
    {"supset",      SymDef{"\\supset",      "&sup;",       "[superset of]",                                 "[superset of]",                                 "⊃"}},
    {"nsub",        SymDef{"\\not\\subset", "&nsub;",      "[not a subset of]",                             "[not a subset of",                              "⊄"}},
    {"sube",        SymDef{"\\subseteq",    "&sube;",      "[subset of or equal to]",                       "[subset of or equal to]",                       "⊆"}},
    {"nsup",        SymDef{"\\not\\supset", "&nsup;",      "[not a superset of]",                           "[not a superset of]",                           "⊅"}},
    {"supe",        SymDef{"\\supseteq",    "&supe;",      "[superset of or equal to]",                     "[superset of or equal to]",                     "⊇"}},
    {"setminus",    SymDef{"\\setminus",    "&setminus;",  "\\",                                            "\\",                                            "⧵"}},
    {"forall",      SymDef{"\\forall",      "&forall;",    "[for all]",                                     "[for all]",                                     "∀"}},
    {"exist",       SymDef{"\\exists",      "&exist;",     "[there exists]",                                "[there exists]",                                "∃"}},
    {"exists",      SymDef{"\\exists",      "&exist;",     "[there exists]",                                "[there exists]",                                "∃"}},
    {"nexist",      SymDef{"\\nexists",     "&exist;",     "[there does not exists]",                       "[there does not  exists]",                      "∄"}},
    {"nexists",     SymDef{"\\nexists",     "&exist;",     "[there does not exists]",                       "[there does not  exists]",                      "∄"}},
    {"empty",       SymDef{"\\emptyset",    "&empty;",     "[empty set]",                                   "[empty set]",                                   "∅"}},
    {"emptyset",    SymDef{"\\emptyset",    "&empty;",     "[empty set]",                                   "[empty set]",                                   "∅"}},
    {"isin",        SymDef{"\\in",          "&isin;",      "[element of]",                                  "[element of]",                                  "∈"}},
    {"in",          SymDef{"\\in",          "&isin;",      "[element of]",                                  "[element of]",                                  "∈"}},
    {"notin",       SymDef{"\\notin",       "&notin;",     "[not an element of]",                           "[not an element of]",                           "∉"}},
    {"ni",          SymDef{"\\ni",          "&ni;",        "[contains as member]",                          "[contains as member]",                          "∋"}},
    {"nabla",       SymDef{"\\nabla",       "&nabla;",     "[nabla]",                                       "[nabla]",                                       "∇"}},
    {"ang",         SymDef{"\\angle",       "&ang;",       "[angle]",                                       "[angle]",                                       "∠"}},
    {"angle",       SymDef{"\\angle",       "&ang;",       "[angle]",                                       "[angle]",                                       "∠"}},
    {"perp",        SymDef{"\\perp",        "&perp;",      "[up tack]",                                     "[up tack]",                                     "⊥"}},
    {"parallel",    SymDef{"\\parallel",    "&parallel;",  "||",                                            "||",                                            "∥"}},
    {"sdot",        SymDef{"\\cdot",        "&sdot;",      "[dot]",                                         "[dot]",                                         "⋅"}},
    {"cdot",        SymDef{"\\cdot",        "&sdot;",      "[dot]",                                         "[dot]",                                         "⋅"}},
    {"lceil",       SymDef{"\\lceil",       "&lceil;",     "[left ceiling]",                                "[left ceiling]",                                "⌈"}},
    {"rceil",       SymDef{"\\rceil",       "&rceil;",     "[right ceiling]",                               "[right ceiling]",                               "⌉"}},
    {"lfloor",      SymDef{"\\lfloor",      "&lfloor;",    "[left floor]",                                  "[left floor]",                                  "⌊"}},
    {"rfloor",      SymDef{"\\rfloor",      "&rfloor;",    "[right floor]",                                 "[right floor]",                                 "⌋"}},
    {"lang",        SymDef{"\\langle",      "&lang;",      "<",                                             "<",                                             "⟨"}},
    {"rang",        SymDef{"\\rangle",      "&rang;",      ">",                                             ">",                                             "⟩"}},
    {"langle",      SymDef{"\\langle",      "&lang;",      "<",                                             "<",                                             "⟨"}},
    {"rangle",      SymDef{"\\rangle",      "&rang;",      ">",                                             ">",                                             "⟩"}},
    {"hbar",        SymDef{"\\hbar",        "&hbar;",      "hbar",                                          "hbar",                                          "ℏ"}},
    {"mho",         SymDef{"\\mho",         "&mho;",       "mho",                                           "mho",                                           "℧"}},

    {"larr",           SymDef{"\\leftarrow",      "&larr;",  "<-",             "<-",             "←"}},
    {"leftarrow",      SymDef{"\\leftarrow",      "&larr;",  "<-",             "<-",             "←"}},
    {"gets",           SymDef{"\\gets",           "&larr;",  "<-",             "<-",             "←"}},
    {"lArr",           SymDef{"\\Leftarrow",      "&lArr;",  "<=",             "<=",             "⇐"}},
    {"Leftarrow",      SymDef{"\\Leftarrow",      "&lArr;",  "<=",             "<=",             "⇐"}},
    {"uarr",           SymDef{"\\uparrow",        "&uarr;",  "[uparrow]",      "[uparrow]",      "↑"}},
    {"uparrow",        SymDef{"\\uparrow",        "&uarr;",  "[uparrow]",      "[uparrow]",      "↑"}},
    {"uArr",           SymDef{"\\Uparrow",        "&uArr;",  "[dbluparrow]",   "[dbluparrow]",   "⇑"}},
    {"Uparrow",        SymDef{"\\Uparrow",        "&uArr;",  "[dbluparrow]",   "[dbluparrow]",   "⇑"}},
    {"rarr",           SymDef{"\\rightarrow",     "&rarr;",  "->",             "->",             "→"}},
    {"to",             SymDef{"\\to",             "&rarr;",  "->",             "->",             "→"}},
    {"rightarrow",     SymDef{"\\rightarrow",     "&rarr;"   "->",             "->",             "→"}},
    {"rArr",           SymDef{"\\Rightarrow",     "&rArr;",  "=>",             "=>",             "⇒"}},
    {"Rightarrow",     SymDef{"\\Rightarrow",     "&rArr;",  "=>",             "=>",             "⇒"}},
    {"darr",           SymDef{"\\downarrow",      "&darr;",  "[downarrow]",    "[downarrow]",    "↓"}},
    {"downarrow",      SymDef{"\\downarrow",      "&darr;",  "[downarrow]",    "[downarrow]",    "↓"}},
    {"dArr",           SymDef{"\\Downarrow",      "&dArr;",  "[dbldownarrow]", "[dbldownarrow]", "⇓"}},
    {"Downarrow",      SymDef{"\\Downarrow",      "&dArr;",  "[dbldownarrow]", "[dbldownarrow]", "⇓"}},
    {"harr",           SymDef{"\\leftrightarrow", "&harr;",  "<->",            "<->",            "↔"}},
    {"leftrightarrow", SymDef{"\\leftrightarrow", "&harr;"   "<->",            "<->",            "↔"}},
    {"hArr",           SymDef{"\\Leftrightarrow", "&hArr;",  "<=>",            "<=>",            "⇔"}},
    {"Leftrightarrow", SymDef{"\\Leftrightarrow", "&hArr;",  "<=>",            "<=>",            "⇔"}},
    {"crarr",          SymDef{"\\hookleftarrow",  "&crarr;", "<-'",            "<-'",            "↵"}},
    {"hookleftarrow",  SymDef{"\\hookleftarrow",  "&crarr;"  "<-'",            "<-'",            "↵"}},

    {"arccos", SymDef{"\\arccos", "arccos", "arccos", "arccos", "arccos"}},
    {"arcsin", SymDef{"\\arcsin", "arcsin", "arcsin", "arcsin", "arcsin"}},
    {"arctan", SymDef{"\\arctan", "arctan", "arctan", "arctan", "arctan"}},
    {"arg",    SymDef{"\\arg",    "arg",    "arg",    "arg",    "arg"}},
    {"cos",    SymDef{"\\cos",    "cos",    "cos",    "cos",    "cos"}},
    {"cosh",   SymDef{"\\cosh",   "cosh",   "cosh",   "cosh",   "cosh"}},
    {"cot",    SymDef{"\\cot",    "cot",    "cot",    "cot",    "cot"}},
    {"coth",   SymDef{"\\coth",   "coth",   "coth",   "coth",   "coth"}},
    {"csc",    SymDef{"\\csc",    "csc",    "csc",    "csc",    "csc"}},
    {"deg",    SymDef{"\\deg",    "&deg;",  "deg",    "deg",    "deg"}},
    {"det",    SymDef{"\\det",    "det",    "det",    "det",    "det"}},
    {"dim",    SymDef{"\\dim",    "dim",    "dim",    "dim",    "dim"}},
    {"exp",    SymDef{"\\exp",    "exp",    "exp",    "exp",    "exp"}},
    {"gcd",    SymDef{"\\gcd",    "gcd",    "gcd",    "gcd",    "gcd"}},
    {"hom",    SymDef{"\\hom",    "hom",    "hom",    "hom",    "hom"}},
    {"inf",    SymDef{"\\inf",    "inf",    "inf",    "inf",    "inf"}},
    {"ker",    SymDef{"\\ker",    "ker",    "ker",    "ker",    "ker"}},
    {"lg",     SymDef{"\\lg",     "lg",     "lg",     "lg",     "lg"}},
    {"lim",    SymDef{"\\lim",    "lim",    "lim",    "lim",    "lim"}},
    {"liminf", SymDef{"\\liminf", "liminf", "liminf", "liminf", "liminf"}},
    {"limsup", SymDef{"\\limsup", "limsup", "limsup", "limsup", "limsup"}},
    {"ln",     SymDef{"\\ln",     "ln",     "ln",     "ln",     "ln"}},
    {"log",    SymDef{"\\log",    "log",    "log",    "log",    "log"}},
    {"max",    SymDef{"\\max",    "max",    "max",    "max",    "max"}},
    {"min",    SymDef{"\\min",    "min",    "min",    "min",    "min"}},
    {"Pr",     SymDef{"\\Pr",     "Pr",     "Pr",     "Pr",     "Pr"}},
    {"sec",    SymDef{"\\sec",    "sec",    "sec",    "sec",    "sec"}},
    {"sin",    SymDef{"\\sin",    "sin",    "sin",    "sin",    "sin"}},
    {"sinh",   SymDef{"\\sinh",   "sinh",   "sinh",   "sinh",   "sinh"}},
    {"sup",    SymDef{"\\sup",    "&sup;",  "sup",    "sup",    "sup"}},
    {"tan",    SymDef{"\\tan",    "tan",    "tan",    "tan",    "tan"}},
    {"tanh",   SymDef{"\\tanh",   "tanh",   "tanh",   "tanh",   "tanh"}},

    {"bull",      SymDef{"\\textbullet{}", "&bull;",      "*",               "*",               "•"}},
    {"bullet",    SymDef{"\\textbullet{}", "&bull;",      "*",               "*",               "•"}},
    {"star",      SymDef{"\\star",          "*",           "*",               "*",               "⋆"}},
    {"lowast",    SymDef{"\\ast",           "&lowast;",    "*",               "*",               "∗"}},
    {"ast",       SymDef{"\\ast",           "&lowast;",    "*",               "*",               "*"}},
    {"odot",      SymDef{"\\odot",          "o",           "[circled dot]",   "[circled dot]",   "ʘ"}},
    {"oplus",     SymDef{"\\oplus",         "&oplus;",     "[circled plus]",  "[circled plus]",  "⊕"}},
    {"otimes",    SymDef{"\\otimes",        "&otimes;",    "[circled times]", "[circled times]", "⊗"}},
    {"check",     SymDef{"\\checkmark",     "&checkmark;", "[checkmark]",     "[checkmark]",     "✓"}},
    {"checkmark", SymDef{"\\checkmark",     "&check;",     "[checkmark]",     "[checkmark]",     "✓"}},

    {"para",  SymDef{"\\P{}",                 "&para;",  "[pilcrow]",   "¶", "¶"}},
    {"ordf",  SymDef{"\\textordfeminine{}",   "&ordf;",  "_a_",         "ª", "ª"}},
    {"ordm",  SymDef{"\\textordmasculine{}",  "&ordm;",  "_o_",         "º", "º"}},
    {"cedil", SymDef{"\\c{}",                 "&cedil;", "[cedilla]",   "¸", "¸"}},
    {"oline", SymDef{"\\overline{~}",         "&oline;", "[overline]",  "¯", "‾"}},
    {"uml",   SymDef{"\\textasciidieresis{}", "&uml;",   "[diaeresis]", "¨", "¨"}},
    {"zwnj",  SymDef{"\\/{}",                 "&zwnj;",  "",            "",  "‌"}},
    {"zwj",   SymDef{"",                      "&zwj;",   "",            "",  "‍"}},
    {"lrm",   SymDef{"",                      "&lrm;",   "",            "",  "‎"}},
    {"rlm",   SymDef{"",                      "&rlm;",   "",            "",  "‏"}},

    {"smiley",     SymDef{"\\ddot\\smile", "&#9786;", ":-)", ":-)", "☺"}},
    {"blacksmile", SymDef{"\\ddot\\smile", "&#9787;", ":-)", ":-)", "☻"}},
    {"sad",        SymDef{"\\ddot\\frown", "&#9785;", ":-(", ":-(", "☹"}},
    {"frowny",     SymDef{"\\ddot\\frown", "&#9785;", ":-(", ":-(", "☹"}},

    {"clubs",       SymDef{"\\clubsuit",    "&clubs;",     "[clubs]",    "[clubs]",    "♣"}},
    {"clubsuit",    SymDef{"\\clubsuit",    "&clubs;",     "[clubs]",    "[clubs]",    "♣"}},
    {"spades",      SymDef{"\\spadesuit",   "&spades;",    "[spades]",   "[spades]",   "♠"}},
    {"spadesuit",   SymDef{"\\spadesuit",   "&spades;",    "[spades]",   "[spades]",   "♠"}},
    {"hearts",      SymDef{"\\heartsuit",   "&hearts;",    "[hearts]",   "[hearts]",   "♥"}},
    {"heartsuit",   SymDef{"\\heartsuit",   "&heartsuit;", "[hearts]",   "[hearts]",   "♥"}},
    {"diams",       SymDef{"\\diamondsuit", "&diams;",     "[diamonds]", "[diamonds]", "◆"}},
    {"diamondsuit", SymDef{"\\diamondsuit", "&diams;",     "[diamonds]", "[diamonds]", "◆"}},
    {"diamond",     SymDef{"\\diamondsuit", "&diamond;",   "[diamond]",  "[diamond]",  "◆"}},
    {"Diamond",     SymDef{"\\diamondsuit", "&diamond;",   "[diamond]",  "[diamond]",  "◆"}},
    {"loz",         SymDef{"\\lozenge",     "&loz;",       "[lozenge]",  "[lozenge]",  "⧫" }},
    // clang-format on
};


void ExporterLatex::addWrap(
    Res&           res,
    const QString& open,
    const QString& close,
    const QString& arg) {
    res->add(string(open + arg + close));
}

void ExporterLatex::addWrap(
    Res&           res,
    const QString& open,
    const QString& close,
    const Res&     arg) {
    res->add(string(open));
    res->add(arg);
    res->add(string(close));
}

ExporterLatex::Res ExporterLatex::command(
    const QString&      name,
    const Vec<QString>& args) {
    Res res = b::line();
    res->add(string("\\" + name));
    for (auto const& arg : args) {
        addWrap(res, "{", "}", arg);
    }
    return res;
}

ExporterLatex::Res ExporterLatex::command(
    const QString&  name,
    const Vec<Res>& opts,
    const Vec<Res>& args) {
    Res res = b::line();
    res->add(string("\\" + name));
    // FIXME join on comma, wrap on brackets
    for (auto const& opt : opts) {
        addWrap(res, "[", "]", opt);
    }

    for (auto const& arg : args) {
        addWrap(res, "{", "}", arg);
    }
    return res;
}

ExporterLatex::Res ExporterLatex::command(
    const QString&  name,
    const Vec<Res>& args) {
    Res res = b::line();
    res->add(string("\\" + name));
    for (auto const& arg : args) {
        addWrap(res, "{", "}", arg);
    }
    return res;
}

ExporterLatex::Res ExporterLatex::command(
    const QString&      name,
    const Vec<QString>& opts,
    const Vec<QString>& args) {
    Res res = b::line();
    res->add(string("\\" + name));
    // FIXME join on comma, wrap on brackets
    for (auto const& opt : opts) {
        addWrap(res, "[", "]", opt);
    }

    for (auto const& arg : args) {
        addWrap(res, "{", "}", arg);
    }
    return res;
}

void ExporterLatex::visitNewline(Res& res, In<sem::Newline> item) {
    __visit_specific_kind(res, item);
    res = string(escape(item->text));
}

void ExporterLatex::visitSpace(Res& res, In<sem::Space> item) {
    __visit_specific_kind(res, item);
    res = string(escape(item->text));
}

void ExporterLatex::visitWord(Res& res, In<sem::Word> item) {
    __visit_specific_kind(res, item);
    res = string(escape(item->text));
}

void ExporterLatex::visitRawText(Res& res, In<sem::RawText> item) {
    __visit_specific_kind(res, item);
    res = string(escape(item->text));
}

void ExporterLatex::visitPunctuation(Res& res, In<sem::Punctuation> item) {
    __visit_specific_kind(res, item);
    res = string(escape(item->text));
}

void ExporterLatex::visitPlaceholder(Res& res, In<sem::Placeholder> item) {
    __visit_specific_kind(res, item);
    res = command(
        "textsc",
        {command("texttt", {string("<" + escape(item->text) + ">")})});
}


void ExporterLatex::visitBigIdent(Res& res, In<sem::BigIdent> item) {
    __visit_specific_kind(res, item);
    QString specialColor;

    auto s = item->text;

    // TOOD use `parseBigIdent` from the sem convert
    if (s == "TODO") {
        specialColor = "green";
    } else if (s == "WIP") {
        specialColor = "brown";
    }

    if (0 < specialColor.size()) {
        res = command(
            "fbox",
            {command(
                "colorbox",
                {string(specialColor), string(escape(item->text))})});
    } else {
        res = string(escape(item->text));
    }
}

void ExporterLatex::visitFootnote(Res& res, In<sem::Footnote> footnote) {
    if (footnote->tag.empty() && footnote->definition.has_value()) {
        res = command("footnote", {visit(footnote->definition.value())});
    } else {
        res = string("");
    }
}


ExporterLatex::Res ExporterLatex::visit(SemId org) {
    __visit_eval_scope(org);
    Res tmp = nullptr;
    visit(tmp, org);
    if (tmp == nullptr) {
        tmp = string("TODO" + to_string(org->getKind()));
    }
    return tmp;
}

void ExporterLatex::subTocForAndAbove(SubtreeCmd mode) {
    switch (mode) {
        case SubtreeCmd::subparagraph:
            subTocMode.incl(SubtreeCmd::subparagraph);
        case SubtreeCmd::paragraph: subTocMode.incl(SubtreeCmd::paragraph);
        case SubtreeCmd::subsubsection:
            subTocMode.incl(SubtreeCmd::subsubsection);
        case SubtreeCmd::subsection:
            subTocMode.incl(SubtreeCmd::subsection);
        case SubtreeCmd::section: subTocMode.incl(SubtreeCmd::section);
        case SubtreeCmd::chapter: subTocMode.incl(SubtreeCmd::chapter);
        case SubtreeCmd::part: subTocMode.incl(SubtreeCmd::part);
    }
}

QString ExporterLatex::getLatexClass(
    Opt<ExporterLatex::In<Document>> doc) {
    QString baseClass = "extarticle";

    if (doc) {
        auto lclass = (*doc)->getProperty(Prop::Kind::ExportLatexClass);
        return lclass ? lclass->getExportLatexClass().latexClass
                      : baseClass;
    } else {
        return baseClass;
    }
}

Opt<ExporterLatex::SubtreeCmd> ExporterLatex::getSubtreeCommand(
    ExporterLatex::In<sem::Subtree> tree) {
    auto lclass = getLatexClass(tree->getDocument());
    if (lclass == "book" || lclass == "extbook") {
        switch (tree->level) {
            case 1: return SubtreeCmd::part;
            case 2: return SubtreeCmd::chapter;
            case 3: return SubtreeCmd::section;
            case 4: return SubtreeCmd::subsection;
            case 5: return SubtreeCmd::subsubsection;
            case 6: return SubtreeCmd::paragraph;
            case 7: return SubtreeCmd::subparagraph;
            default: return std::nullopt;
        }
    } else {
        switch (tree->level) {
            case 1: return SubtreeCmd::section;
            case 2: return SubtreeCmd::subsection;
            case 3: return SubtreeCmd::subsubsection;
            case 4: return SubtreeCmd::paragraph;
            case 5: return SubtreeCmd::subparagraph;
            default: return std::nullopt;
        }
    }
}

Opt<QString> ExporterLatex::getRefKind(SemId id) {
    switch (id->getKind()) {
        case osk::Subtree: {
            auto command = getSubtreeCommand(id.as<sem::Subtree>());
            if (command) {
                switch (command.value()) {
                    case SubtreeCmd::chapter: return "chap:";
                    case SubtreeCmd::section: return "sec:";
                    case SubtreeCmd::part: return "part:";
                }
            } else {
                return std::nullopt;
            }
        }
        default: {
            return std::nullopt;
        }
    }
}

void ExporterLatex::visitDocument(Res& res, In<Document> value) {
    __visit_specific_kind(res, value);
    res = b::stack();

    // TODO replace hardcoded default value for the font size with call to
    // `getLatexClassOptions` provided in the org document.
    res->add(command("documentclass", {"14pt"}, {getLatexClass(value)}));

    for (const auto& hdr :
         value->getProperties(Prop::Kind::ExportLatexHeader)) {
        res->add(string(hdr.getExportLatexHeader().header));
    }

    res->add(command("usepackage", {"csquotes"}));
    res->add(command("usepackage", {"bookmarks"}, {"hyperref"}));
    res->add(command("usepackage", {"xcolor"}));

    if (!subTocMode.empty()) {
        res->add(command("usepackage", {"minitoc"}));
    }

    res->add(string(R"(
\newcommand*\sepline{%
  \begin{center}
    \rule[1ex]{\textwidth}{1pt}
  \end{center}}
)"));

    res->add(string(R"(
\newcommand{\quot}[1]{\textcolor{brown}{#1}}
)"));

    Vec<sem::SemIdT<sem::Export>> headerExports;
    value.eachSubnodeRec([&](sem::SemId id) {
        if (id->is(osk::Export)) {
            sem::SemIdT<sem::Export> exp = id.as<sem::Export>();
            if (exp->placement.has_value()
                && exp->placement.value() == "header") {
                headerExports.push_back(exp);
            }
        }
    });

    for (auto const& exp : headerExports) {
        res->add(string(exp->content));
    }


    res->add(command("begin", {"document"}));
    if (!subTocMode.empty()) {
        res->add(command("dominitoc"));
        if (subTocMode.contains(SubtreeCmd::part)) {
            res->add(command("doparttoc"));
        }
    }

    if (value->options) {
        auto exp = value->options->tocExport;
        if (std::holds_alternative<bool>(exp)) {
            if (std::get<bool>(exp)) {
                res->add(command("tableofcontents"));
            }
        } else {
            int level = std::get<int>(exp);
            res->add(command("tableofcontents"));
            res->add(
                command("setcounter", {"tocdepth", to_string(level)}));
        }
    }

    for (const auto& it : value->subnodes) {
        res->add(visit(it));
    }
    res->add(command("end", {"document"}));
}

void ExporterLatex::visitSubtree(Res& res, In<Subtree> tree) {
    __visit_specific_kind(res, tree);
    res = b::stack();

    auto titleText = b::line();
    for (const auto& item : tree->title->subnodes) {
        switch (item->getKind()) {
#define _direct(__Kind)                                                   \
    case osk::__Kind: titleText->add(visit(item)); break;
            EACH_SEM_ORG_LEAF_KIND(_direct)
#undef _direct

            default: {
                titleText->add(command(
                    "texorpdfstring",
                    {visit(item),
                     // FIXME latex exporter is broken because of sem ID
                     // overloads, need to be fixed to get the right output
                     // here.
                     string(ExporterUltraplain::toStr(item))}));
            }
        }
    }

    Opt<SubtreeCmd> cmd = getSubtreeCommand(tree);


    res->add(command(
        map(cmd, [](SubtreeCmd cmd) { return to_string(cmd); })
            .value_or("textbf"),
        {titleText}));

    res->add(command(
        "label",
        {getRefKind(tree).value_or("") + tree.toId().getReadableId()}));

    if (cmd && subTocMode.contains(cmd.value())) {
        res->add(command("minitoc"));
    }

    for (const auto& it : tree->subnodes) {
        res->add(visit(it));
    }
}

void ExporterLatex::visitParagraph(Res& res, In<Paragraph> par) {
    __visit_specific_kind(res, par);
    res = b::line();
    for (auto const& sub : par->subnodes) {
        res->add(visit(sub));
    }

    if (res->size() == 0) {
        res->add(string(" "));
    }
}

void ExporterLatex::visitTime(Res& res, In<Time> time) {
    if (time->isStatic()) {
        res = command(
            "fbox",
            {command("texttt", {time->getStatic().time.toString()})});
    } else {
        res = string("TODO dynamic time");
    }
}

void ExporterLatex::visitTimeRange(Res& res, In<sem::TimeRange> range) {
    res = b::line({visit(range->from), string("--"), visit(range->to)});
}

void ExporterLatex::visitBold(Res& res, In<sem::Bold> bold) {
    res = command("textbf", {b::line(subnodes(bold))});
}


void ExporterLatex::visitUnderline(Res& res, In<sem::Underline> under) {
    res = command("underline", {b::line(subnodes(under))});
}

void ExporterLatex::visitSymbol(Res& res, In<sem::Symbol> sym) {
    if (definitions.contains(sym->name)) {
        res = string(definitions.at(sym->name).latex);
    } else if (sym->name == "q") {
        auto     arg = sym->positional.at(1_B);
        Vec<Res> items;
        items.push_back(string("\""));
        for (const auto& sub : arg->subnodes) {
            if (sub.is(osk::Punctuation)
                && sub.as<sem::Punctuation>()->text == "\"") {
                continue;
            } else {
                items.push_back(visit(sub));
            }
        }

        items.push_back(string("\""));

        res = command("quot", {b::line(items)});
    } else {

        Vec<Res> positional;

        for (auto const& arg : sym->positional) {
            positional.push_back(visit(arg));
        }

        res = command(sym->name, positional);
    }
}

void ExporterLatex::visitCenter(Res& res, In<sem::Center> center) {
    res = b::stack();
    res->add(command("begin", {"center"}));
    for (auto const& sub : center->subnodes) {
        res->add(visit(sub));
    }
    res->add(command("end", {"center"}));
}

void ExporterLatex::visitExport(Res& res, In<sem::Export> exp) {
    if (exp->exporter == "latex") {
        if (!exp->placement) {
            res = string(exp->content);
        }
    } else {
        res = string("");
    }
}

void ExporterLatex::visitMonospace(Res& res, In<sem::Monospace> mono) {
    res = command("texttt", {b::line(subnodes(mono))});
}

void ExporterLatex::visitItalic(Res& res, In<sem::Italic> italic) {
    res = command("textit", {b::line(subnodes(italic))});
}

void ExporterLatex::visitVerbatim(Res& res, In<sem::Verbatim> verb) {
    res = command("textsc", {b::line(subnodes(verb))});
}

void ExporterLatex::visitQuote(Res& res, In<sem::Quote> quote) {
    res = b::stack();
    res->add(command("begin", {"displayquote"}));
    res->add(b::stack(subnodes(quote)));
    res->add(command("end", {"displayquote"}));
}

void ExporterLatex::visitLink(Res& res, In<sem::Link> link) {
    switch (link->getLinkKind()) {
        case sem::Link::Kind::Id: {
            auto target = link->resolve();
            if (target) {
                res = b::line({command(
                    "ref",
                    {string(
                        getRefKind(*target).value_or("")
                        + target.value().getReadableId())})});

                if (link->description) {
                    res->add(visit(link->description.value()));
                }

            } else {
                if (link->description) {
                    res = visit(link->description.value());
                } else {
                    res = string("UNRESOLVED LINK");
                }
            }

            break;
        }

        case sem::Link::Kind::Footnote: {
            auto target = link->resolve();
            if (target) {
                res = command("footnote", {visit(target.value())});
            } else {
                res = string("fn:" + link->getFootnote().target);
            }
            break;
        }

        case sem::Link::Kind::Raw: {
            res = command(
                "href",
                {string(link->getRaw().text)},
                {link->description ? visit(link->description.value())
                                   : string("link")});
            res = string("href");
            break;
        }

        default: {
            res = string("LINK KIND" + to_string(link->getLinkKind()));
        }
    }
}

void ExporterLatex::visitList(Res& res, In<sem::List> list) {
    res = b::stack();
    res->add(command("begin", {"itemize"}));
    res->add(subnodes(list));
    res->add(command("end", {"itemize"}));
}

void ExporterLatex::visitListItem(Res& res, In<sem::ListItem> item) {
    res = b::line();
    if (item->isDescriptionItem()) {
        res->add(command("item", {visit(item->header.value())}));
    } else {
        res->add(command("item"));
    }
    res->add(string(" "));
    res->add(subnodes(item));
}

void ExporterLatex::visitTextSeparator(
    Res&                   res,
    In<sem::TextSeparator> sep) {
    res = command("sepline");
}

void ExporterLatex::visitHashTag(Res& res, In<sem::HashTag> tag) {
    QString join;

    Func<void(In<sem::HashTag> const& tag)> aux;
    aux = [&](In<sem::HashTag> const& tag) {
        join += tag->head;
        if (tag->subtags.size() == 1) {
            join += "##";
            aux(tag->subtags.at(0));
        } else if (1 < tag->subtags.size()) {
            join += "##[";
            bool first = true;
            for (auto const& sub : tag->subtags) {
                if (!first) {
                    join += ",";
                }
                first = false;
                aux(sub);
            }

            join += "]";
        }
    };
    join = "#";
    aux(tag);
    res = command("texttt", {string(escape(join))});
}

void ExporterLatex::visitEscaped(Res& res, In<sem::Escaped> escaped) {
    res = string(escape(escaped->text.mid(1)));
}


QString ExporterLatex::escape(const QString& value) {
    QString res;
    res.reserve(value.size());
    for (QChar const& ch : value) {
        switch (ch.toLatin1()) {
            case '&':
            case '_':
            case '}':
            case '{':
            case '#':
            case '%': res.append('\\' + ch); break;
            default: res.append(ch);
        }
    }
    return res;
}
