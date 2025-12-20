#include <hstd/stdlib/strutils.hpp>
#include <numeric>

using namespace hstd;

Str unicodeCharMappings[256][15] = {
    [(int)'A']
    = {Str("A"),
       Str("Ɐ"),
       Str("𝔄"),
       Str("𝕬"),
       Str("𝔸"),
       Str("𝐀"),
       Str("𝐴"),
       Str("𝑨"),
       Str("𝒜"),
       Str("𝓐"),
       Str("𝖠"),
       Str("𝗔"),
       Str("𝘈"),
       Str("𝘼"),
       Str("𝙰")},
    [(int)'B']
    = {Str("B"),
       Str("B"),
       Str("𝔅"),
       Str("𝕭"),
       Str("𝔹"),
       Str("𝐁"),
       Str("𝐵"),
       Str("𝑩"),
       Str("ℬ"),
       Str("𝓑"),
       Str("𝖡"),
       Str("𝗕"),
       Str("𝘉"),
       Str("𝘽"),
       Str("𝙱")},
    [(int)'C']
    = {Str("C"),
       Str("Ɔ"),
       Str("ℭ"),
       Str("𝕮"),
       Str("ℂ"),
       Str("𝐂"),
       Str("𝐶"),
       Str("𝑪"),
       Str("𝒞"),
       Str("𝓒"),
       Str("𝖢"),
       Str("𝗖"),
       Str("𝘊"),
       Str("𝘾"),
       Str("𝙲")},
    [(int)'D']
    = {Str("D"),
       Str("D"),
       Str("𝔇"),
       Str("𝕯"),
       Str("𝔻"),
       Str("𝐃"),
       Str("𝐷"),
       Str("𝑫"),
       Str("𝒟"),
       Str("𝓓"),
       Str("𝖣"),
       Str("𝗗"),
       Str("𝘋"),
       Str("𝘿"),
       Str("𝙳")},
    [(int)'E']
    = {Str("E"),
       Str("Ǝ"),
       Str("𝔈"),
       Str("𝕰"),
       Str("𝔼"),
       Str("𝐄"),
       Str("𝐸"),
       Str("𝑬"),
       Str("ℰ"),
       Str("𝓔"),
       Str("𝖤"),
       Str("𝗘"),
       Str("𝘌"),
       Str("𝙀"),
       Str("𝙴")},
    [(int)'F']
    = {Str("F"),
       Str("Ⅎ"),
       Str("𝔉"),
       Str("𝕱"),
       Str("𝔽"),
       Str("𝐅"),
       Str("𝐹"),
       Str("𝑭"),
       Str("ℱ"),
       Str("𝓕"),
       Str("𝖥"),
       Str("𝗙"),
       Str("𝘍"),
       Str("𝙁"),
       Str("𝙵")},
    [(int)'G']
    = {Str("G"),
       Str("⅁"),
       Str("𝔊"),
       Str("𝕲"),
       Str("𝔾"),
       Str("𝐆"),
       Str("𝐺"),
       Str("𝑮"),
       Str("𝒢"),
       Str("𝓖"),
       Str("𝖦"),
       Str("𝗚"),
       Str("𝘎"),
       Str("𝙂"),
       Str("𝙶")},
    [(int)'H']
    = {Str("H"),
       Str("H"),
       Str("ℌ"),
       Str("𝕳"),
       Str("ℍ"),
       Str("𝐇"),
       Str("𝐻"),
       Str("𝑯"),
       Str("ℋ"),
       Str("𝓗"),
       Str("𝖧"),
       Str("𝗛"),
       Str("𝘏"),
       Str("𝙃"),
       Str("𝙷")},
    [(int)'I']
    = {Str("I"),
       Str("I"),
       Str("ℑ"),
       Str("𝕴"),
       Str("𝕀"),
       Str("𝐈"),
       Str("𝐼"),
       Str("𝑰"),
       Str("ℐ"),
       Str("𝓘"),
       Str("𝖨"),
       Str("𝗜"),
       Str("𝘐"),
       Str("𝙄"),
       Str("𝙸")},
    [(int)'J']
    = {Str("J"),
       Str("ſ"),
       Str("𝔍"),
       Str("𝕵"),
       Str("𝕁"),
       Str("𝐉"),
       Str("𝐽"),
       Str("𝑱"),
       Str("𝒥"),
       Str("𝓙"),
       Str("𝖩"),
       Str("𝗝"),
       Str("𝘑"),
       Str("𝙅"),
       Str("𝙹")},
    [(int)'K']
    = {Str("K"),
       Str("Ʞ"),
       Str("𝔎"),
       Str("𝕶"),
       Str("𝕂"),
       Str("𝐊"),
       Str("𝐾"),
       Str("𝑲"),
       Str("𝒦"),
       Str("𝓚"),
       Str("𝖪"),
       Str("𝗞"),
       Str("𝘒"),
       Str("𝙆"),
       Str("𝙺")},
    [(int)'L']
    = {Str("L"),
       Str("Ꞁ"),
       Str("𝔏"),
       Str("𝕷"),
       Str("𝕃"),
       Str("𝐋"),
       Str("𝐿"),
       Str("𝑳"),
       Str("ℒ"),
       Str("𝓛"),
       Str("𝖫"),
       Str("𝗟"),
       Str("𝘓"),
       Str("𝙇"),
       Str("𝙻")},
    [(int)'M']
    = {Str("M"),
       Str("Ɯ"),
       Str("𝔐"),
       Str("𝕸"),
       Str("𝕄"),
       Str("𝐌"),
       Str("𝑀"),
       Str("𝑴"),
       Str("ℳ"),
       Str("𝓜"),
       Str("𝖬"),
       Str("𝗠"),
       Str("𝘔"),
       Str("𝙈"),
       Str("𝙼")},
    [(int)'N']
    = {Str("N"),
       Str("N"),
       Str("𝔑"),
       Str("𝕹"),
       Str("ℕ"),
       Str("𝐍"),
       Str("𝑁"),
       Str("𝑵"),
       Str("𝒩"),
       Str("𝓝"),
       Str("𝖭"),
       Str("𝗡"),
       Str("𝘕"),
       Str("𝙉"),
       Str("𝙽")},
    [(int)'O']
    = {Str("O"),
       Str("O"),
       Str("𝔒"),
       Str("𝕺"),
       Str("𝕆"),
       Str("𝐎"),
       Str("𝑂"),
       Str("𝑶"),
       Str("𝒪"),
       Str("𝓞"),
       Str("𝖮"),
       Str("𝗢"),
       Str("𝘖"),
       Str("𝙊"),
       Str("𝙾")},
    [(int)'P']
    = {Str("P"),
       Str("Ԁ"),
       Str("𝔓"),
       Str("𝕻"),
       Str("ℙ"),
       Str("𝐏"),
       Str("𝑃"),
       Str("𝑷"),
       Str("𝒫"),
       Str("𝓟"),
       Str("𝖯"),
       Str("𝗣"),
       Str("𝘗"),
       Str("𝙋"),
       Str("𝙿")},
    [(int)'Q']
    = {Str("Q"),
       Str("Ò"),
       Str("𝔔"),
       Str("𝕼"),
       Str("ℚ"),
       Str("𝐐"),
       Str("𝑄"),
       Str("𝑸"),
       Str("𝒬"),
       Str("𝓠"),
       Str("𝖰"),
       Str("𝗤"),
       Str("𝘘"),
       Str("𝙌"),
       Str("𝚀")},
    [(int)'R']
    = {Str("R"),
       Str("ᴚ"),
       Str("ℜ"),
       Str("𝕽"),
       Str("ℝ"),
       Str("𝐑"),
       Str("𝑅"),
       Str("𝑹"),
       Str("ℛ"),
       Str("𝓡"),
       Str("𝖱"),
       Str("𝗥"),
       Str("𝘙"),
       Str("𝙍"),
       Str("𝚁")},
    [(int)'S']
    = {Str("S"),
       Str("S"),
       Str("𝔖"),
       Str("𝕾"),
       Str("𝕊"),
       Str("𝐒"),
       Str("𝑆"),
       Str("𝑺"),
       Str("𝒮"),
       Str("𝓢"),
       Str("𝖲"),
       Str("𝗦"),
       Str("𝘚"),
       Str("𝙎"),
       Str("𝚂")},
    [(int)'T']
    = {Str("T"),
       Str("Ʇ"),
       Str("𝔗"),
       Str("𝕿"),
       Str("𝕋"),
       Str("𝐓"),
       Str("𝑇"),
       Str("𝑻"),
       Str("𝒯"),
       Str("𝓣"),
       Str("𝖳"),
       Str("𝗧"),
       Str("𝘛"),
       Str("𝙏"),
       Str("𝚃")},
    [(int)'U']
    = {Str("U"),
       Str("∩"),
       Str("𝔘"),
       Str("𝖀"),
       Str("𝕌"),
       Str("𝐔"),
       Str("𝑈"),
       Str("𝑼"),
       Str("𝒰"),
       Str("𝓤"),
       Str("𝖴"),
       Str("𝗨"),
       Str("𝘜"),
       Str("𝙐"),
       Str("𝚄")},
    [(int)'V']
    = {Str("V"),
       Str("Ʌ"),
       Str("𝔙"),
       Str("𝖁"),
       Str("𝕍"),
       Str("𝐕"),
       Str("𝑉"),
       Str("𝑽"),
       Str("𝒱"),
       Str("𝓥"),
       Str("𝖵"),
       Str("𝗩"),
       Str("𝘝"),
       Str("𝙑"),
       Str("𝚅")},
    [(int)'W']
    = {Str("W"),
       Str("ʍ"),
       Str("𝔚"),
       Str("𝖂"),
       Str("𝕎"),
       Str("𝐖"),
       Str("𝑊"),
       Str("𝑾"),
       Str("𝒲"),
       Str("𝓦"),
       Str("𝖶"),
       Str("𝗪"),
       Str("𝘞"),
       Str("𝙒"),
       Str("𝚆")},
    [(int)'X']
    = {Str("X"),
       Str("X"),
       Str("𝔛"),
       Str("𝖃"),
       Str("𝕏"),
       Str("𝐗"),
       Str("𝑋"),
       Str("𝑿"),
       Str("𝒳"),
       Str("𝓧"),
       Str("𝖷"),
       Str("𝗫"),
       Str("𝘟"),
       Str("𝙓"),
       Str("𝚇")},
    [(int)'Y']
    = {Str("Y"),
       Str("⅄"),
       Str("𝔜"),
       Str("𝖄"),
       Str("𝕐"),
       Str("𝐘"),
       Str("𝑌"),
       Str("𝒀"),
       Str("𝒴"),
       Str("𝓨"),
       Str("𝖸"),
       Str("𝗬"),
       Str("𝘠"),
       Str("𝙔"),
       Str("𝚈")},
    [(int)'Z']
    = {Str("Z"),
       Str("Z"),
       Str("ℨ"),
       Str("𝖅"),
       Str("ℤ"),
       Str("𝐙"),
       Str("𝑍"),
       Str("𝒁"),
       Str("𝒵"),
       Str("𝓩"),
       Str("𝖹"),
       Str("𝗭"),
       Str("𝘡"),
       Str("𝙕"),
       Str("𝚉")},
    [(int)'a']
    = {Str("a"),
       Str("ɐ"),
       Str("𝔞"),
       Str("𝖆"),
       Str("𝕒"),
       Str("𝐚"),
       Str("𝑎"),
       Str("𝒂"),
       Str("𝒶"),
       Str("𝓪"),
       Str("𝖺"),
       Str("𝗮"),
       Str("𝘢"),
       Str("𝙖"),
       Str("𝚊")},
    [(int)'b']
    = {Str("b"),
       Str("q"),
       Str("𝔟"),
       Str("𝖇"),
       Str("𝕓"),
       Str("𝐛"),
       Str("𝑏"),
       Str("𝒃"),
       Str("𝒷"),
       Str("𝓫"),
       Str("𝖻"),
       Str("𝗯"),
       Str("𝘣"),
       Str("𝙗"),
       Str("𝚋")},
    [(int)'c']
    = {Str("c"),
       Str("ɔ"),
       Str("𝔠"),
       Str("𝖈"),
       Str("𝕔"),
       Str("𝐜"),
       Str("𝑐"),
       Str("𝒄"),
       Str("𝒸"),
       Str("𝓬"),
       Str("𝖼"),
       Str("𝗰"),
       Str("𝘤"),
       Str("𝙘"),
       Str("𝚌")},
    [(int)'d']
    = {Str("d"),
       Str("p"),
       Str("𝔡"),
       Str("𝖉"),
       Str("𝕕"),
       Str("𝐝"),
       Str("𝑑"),
       Str("𝒅"),
       Str("𝒹"),
       Str("𝓭"),
       Str("𝖽"),
       Str("𝗱"),
       Str("𝘥"),
       Str("𝙙"),
       Str("𝚍")},
    [(int)'e']
    = {Str("e"),
       Str("ǝ"),
       Str("𝔢"),
       Str("𝖊"),
       Str("𝕖"),
       Str("𝐞"),
       Str("𝑒"),
       Str("𝒆"),
       Str("ℯ"),
       Str("𝓮"),
       Str("𝖾"),
       Str("𝗲"),
       Str("𝘦"),
       Str("𝙚"),
       Str("𝚎")},
    [(int)'f']
    = {Str("f"),
       Str("ɟ"),
       Str("𝔣"),
       Str("𝖋"),
       Str("𝕗"),
       Str("𝐟"),
       Str("𝑓"),
       Str("𝒇"),
       Str("𝒻"),
       Str("𝓯"),
       Str("𝖿"),
       Str("𝗳"),
       Str("𝘧"),
       Str("𝙛"),
       Str("𝚏")},
    [(int)'g']
    = {Str("g"),
       Str("ᵷ"),
       Str("𝔤"),
       Str("𝖌"),
       Str("𝕘"),
       Str("𝐠"),
       Str("𝑔"),
       Str("𝒈"),
       Str("ℊ"),
       Str("𝓰"),
       Str("𝗀"),
       Str("𝗴"),
       Str("𝘨"),
       Str("𝙜"),
       Str("𝚐")},
    [(int)'h']
    = {Str("h"),
       Str("ɥ"),
       Str("𝔥"),
       Str("𝖍"),
       Str("𝕙"),
       Str("𝐡"),
       Str("ℎ"),
       Str("𝒉"),
       Str("𝒽"),
       Str("𝓱"),
       Str("𝗁"),
       Str("𝗵"),
       Str("𝘩"),
       Str("𝙝"),
       Str("𝚑")},
    [(int)'i']
    = {Str("i"),
       Str("ᴉ"),
       Str("𝔦"),
       Str("𝖎"),
       Str("𝕚"),
       Str("𝐢"),
       Str("𝑖"),
       Str("𝒊"),
       Str("𝒾"),
       Str("𝓲"),
       Str("𝗂"),
       Str("𝗶"),
       Str("𝘪"),
       Str("𝙞"),
       Str("𝚒")},
    [(int)'j']
    = {Str("j"),
       Str("f"),
       Str("𝔧"),
       Str("𝖏"),
       Str("𝕛"),
       Str("𝐣"),
       Str("𝑗"),
       Str("𝒋"),
       Str("𝒿"),
       Str("𝓳"),
       Str("𝗃"),
       Str("𝗷"),
       Str("𝘫"),
       Str("𝙟"),
       Str("𝚓")},
    [(int)'k']
    = {Str("k"),
       Str("ʞ"),
       Str("𝔨"),
       Str("𝖐"),
       Str("𝕜"),
       Str("𝐤"),
       Str("𝑘"),
       Str("𝒌"),
       Str("𝓀"),
       Str("𝓴"),
       Str("𝗄"),
       Str("𝗸"),
       Str("𝘬"),
       Str("𝙠"),
       Str("𝚔")},
    [(int)'l']
    = {Str("l"),
       Str("ꞁ"),
       Str("𝔩"),
       Str("𝖑"),
       Str("𝕝"),
       Str("𝐥"),
       Str("𝑙"),
       Str("𝒍"),
       Str("𝓁"),
       Str("𝓵"),
       Str("𝗅"),
       Str("𝗹"),
       Str("𝘭"),
       Str("𝙡"),
       Str("𝚕")},
    [(int)'m']
    = {Str("m"),
       Str("ɯ"),
       Str("𝔪"),
       Str("𝖒"),
       Str("𝕞"),
       Str("𝐦"),
       Str("𝑚"),
       Str("𝒎"),
       Str("𝓂"),
       Str("𝓶"),
       Str("𝗆"),
       Str("𝗺"),
       Str("𝘮"),
       Str("𝙢"),
       Str("𝚖")},
    [(int)'n']
    = {Str("n"),
       Str("u"),
       Str("𝔫"),
       Str("𝖓"),
       Str("𝕟"),
       Str("𝐧"),
       Str("𝑛"),
       Str("𝒏"),
       Str("𝓃"),
       Str("𝓷"),
       Str("𝗇"),
       Str("𝗻"),
       Str("𝘯"),
       Str("𝙣"),
       Str("𝚗")},
    [(int)'o']
    = {Str("o"),
       Str("o"),
       Str("𝔬"),
       Str("𝖔"),
       Str("𝕠"),
       Str("𝐨"),
       Str("𝑜"),
       Str("𝒐"),
       Str("ℴ"),
       Str("𝓸"),
       Str("𝗈"),
       Str("𝗼"),
       Str("𝘰"),
       Str("𝙤"),
       Str("𝚘")},
    [(int)'p']
    = {Str("p"),
       Str("d"),
       Str("𝔭"),
       Str("𝖕"),
       Str("𝕡"),
       Str("𝐩"),
       Str("𝑝"),
       Str("𝒑"),
       Str("𝓅"),
       Str("𝓹"),
       Str("𝗉"),
       Str("𝗽"),
       Str("𝘱"),
       Str("𝙥"),
       Str("𝚙")},
    [(int)'q']
    = {Str("q"),
       Str("b"),
       Str("𝔮"),
       Str("𝖖"),
       Str("𝕢"),
       Str("𝐪"),
       Str("𝑞"),
       Str("𝒒"),
       Str("𝓆"),
       Str("𝓺"),
       Str("𝗊"),
       Str("𝗾"),
       Str("𝘲"),
       Str("𝙦"),
       Str("𝚚")},
    [(int)'r']
    = {Str("r"),
       Str("ɹ"),
       Str("𝔯"),
       Str("𝖗"),
       Str("𝕣"),
       Str("𝐫"),
       Str("𝑟"),
       Str("𝒓"),
       Str("𝓇"),
       Str("𝓻"),
       Str("𝗋"),
       Str("𝗿"),
       Str("𝘳"),
       Str("𝙧"),
       Str("𝚛")},
    [(int)'s']
    = {Str("s"),
       Str("s"),
       Str("𝔰"),
       Str("𝖘"),
       Str("𝕤"),
       Str("𝐬"),
       Str("𝑠"),
       Str("𝒔"),
       Str("𝓈"),
       Str("𝓼"),
       Str("𝗌"),
       Str("𝘀"),
       Str("𝘴"),
       Str("𝙨"),
       Str("𝚜")},
    [(int)'t']
    = {Str("t"),
       Str("ʇ"),
       Str("𝔱"),
       Str("𝖙"),
       Str("𝕥"),
       Str("𝐭"),
       Str("𝑡"),
       Str("𝒕"),
       Str("𝓉"),
       Str("𝓽"),
       Str("𝗍"),
       Str("𝘁"),
       Str("𝘵"),
       Str("𝙩"),
       Str("𝚝")},
    [(int)'u']
    = {Str("u"),
       Str("n"),
       Str("𝔲"),
       Str("𝖚"),
       Str("𝕦"),
       Str("𝐮"),
       Str("𝑢"),
       Str("𝒖"),
       Str("𝓊"),
       Str("𝓾"),
       Str("𝗎"),
       Str("𝘂"),
       Str("𝘶"),
       Str("𝙪"),
       Str("𝚞")},
    [(int)'v']
    = {Str("v"),
       Str("ʌ"),
       Str("𝔳"),
       Str("𝖛"),
       Str("𝕧"),
       Str("𝐯"),
       Str("𝑣"),
       Str("𝒗"),
       Str("𝓋"),
       Str("𝓿"),
       Str("𝗏"),
       Str("𝘃"),
       Str("𝘷"),
       Str("𝙫"),
       Str("𝚟")},
    [(int)'w']
    = {Str("w"),
       Str("ʍ"),
       Str("𝔴"),
       Str("𝖜"),
       Str("𝕨"),
       Str("𝐰"),
       Str("𝑤"),
       Str("𝒘"),
       Str("𝓌"),
       Str("𝔀"),
       Str("𝗐"),
       Str("𝘄"),
       Str("𝘸"),
       Str("𝙬"),
       Str("𝚠")},
    [(int)'x']
    = {std::string("x"),
       Str("x"),
       Str("𝔵"),
       Str("𝖝"),
       Str("𝕩"),
       Str("𝐱"),
       Str("𝑥"),
       Str("𝒙"),
       Str("𝓍"),
       Str("𝔁"),
       Str("𝗑"),
       Str("𝘅"),
       Str("𝘹"),
       Str("𝙭"),
       Str("𝚡")},
    [(int)'y']
    = {std::string("y"),
       Str("ʎ"),
       Str("𝔶"),
       Str("𝖞"),
       Str("𝕪"),
       Str("𝐲"),
       Str("𝑦"),
       Str("𝒚"),
       Str("𝓎"),
       Str("𝔂"),
       Str("𝗒"),
       Str("𝘆"),
       Str("𝘺"),
       Str("𝙮"),
       Str("𝚢")},
    [(int)'z']
    = {std::string("z"),
       Str("z"),
       Str("𝔷"),
       Str("𝖟"),
       Str("𝕫"),
       Str("𝐳"),
       Str("𝑧"),
       Str("𝒛"),
       Str("𝓏"),
       Str("𝔃"),
       Str("𝗓"),
       Str("𝘇"),
       Str("𝘻"),
       Str("𝙯"),
       Str("𝚣")},
    [(int)'0']
    = {std::string("0"),
       Str("0"),
       Str("0"),
       Str("0"),
       Str("𝟘"),
       Str("𝟎"),
       Str("0"),
       Str("0"),
       Str("0"),
       Str("0"),
       Str("0"),
       Str("𝟢"),
       Str("𝟬"),
       Str("0"),
       Str("𝟶")},
    [(int)'1']
    = {std::string("1"),
       Str("1"),
       Str("1"),
       Str("1"),
       Str("𝟙"),
       Str("𝟏"),
       Str("1"),
       Str("1"),
       Str("1"),
       Str("1"),
       Str("1"),
       Str("𝟣"),
       Str("𝟭"),
       Str("1"),
       Str("𝟷")},
    [(int)'2']
    = {std::string("2"),
       Str("2"),
       Str("2"),
       Str("2"),
       Str("𝟚"),
       Str("𝟐"),
       Str("2"),
       Str("2"),
       Str("2"),
       Str("2"),
       Str("2"),
       Str("𝟤"),
       Str("𝟮"),
       Str("2"),
       Str("𝟸")},
    [(int)'3']
    = {std::string("3"),
       Str("3"),
       Str("3"),
       Str("3"),
       Str("𝟛"),
       Str("𝟑"),
       Str("3"),
       Str("3"),
       Str("3"),
       Str("3"),
       Str("3"),
       Str("𝟥"),
       Str("𝟯"),
       Str("3"),
       Str("𝟹")},
    [(int)'4']
    = {std::string("4"),
       Str("4"),
       Str("4"),
       Str("4"),
       Str("𝟜"),
       Str("𝟒"),
       Str("4"),
       Str("4"),
       Str("4"),
       Str("4"),
       Str("4"),
       Str("𝟦"),
       Str("𝟰"),
       Str("4"),
       Str("𝟺")},
    [(int)'5']
    = {std::string("5"),
       Str("5"),
       Str("5"),
       Str("5"),
       Str("𝟝"),
       Str("𝟓"),
       Str("5"),
       Str("5"),
       Str("5"),
       Str("5"),
       Str("5"),
       Str("𝟧"),
       Str("𝟱"),
       Str("5"),
       Str("𝟻")},
    [(int)'6']
    = {std::string("6"),
       Str("6"),
       Str("6"),
       Str("6"),
       Str("𝟞"),
       Str("𝟔"),
       Str("6"),
       Str("6"),
       Str("6"),
       Str("6"),
       Str("6"),
       Str("𝟨"),
       Str("𝟲"),
       Str("6"),
       Str("𝟼")},
    [(int)'7']
    = {std::string("7"),
       Str("7"),
       Str("7"),
       Str("7"),
       Str("𝟟"),
       Str("𝟕"),
       Str("7"),
       Str("7"),
       Str("7"),
       Str("7"),
       Str("7"),
       Str("𝟩"),
       Str("𝟳"),
       Str("7"),
       Str("𝟽")},
    [(int)'8']
    = {std::string("8"),
       Str("8"),
       Str("8"),
       Str("8"),
       Str("𝟠"),
       Str("𝟖"),
       Str("8"),
       Str("8"),
       Str("8"),
       Str("8"),
       Str("8"),
       Str("𝟪"),
       Str("𝟴"),
       Str("8"),
       Str("𝟾")},
    [(int)'9']
    = {std::string("9"),
       Str("9"),
       Str("9"),
       Str("9"),
       Str("𝟡"),
       Str("𝟗"),
       Str("9"),
       Str("9"),
       Str("9"),
       Str("9"),
       Str("9"),
       Str("𝟫"),
       Str("𝟵"),
       Str("9"),
       Str("𝟿")},
};


Str hstd::styledUnicodeMapping(char ch, AsciiStyle style) {
    int chIdx = value_domain<char>::ord(ch);
    if (unicodeCharMappings[chIdx][(int)style] != Str("\0")) {
        return unicodeCharMappings[chIdx][(int)style];
    } else {
        return Str(1, ch);
    }
}

Str hstd::styledUnicodeMapping(Str const& str, AsciiStyle style) {
    Str result;
    result.reserve(str.size());
    for (const auto& ch : str) {
        result += styledUnicodeMapping(ch, style);
    }
    return result;
}

Str hstd::strip(
    CR<Str>     string,
    CR<CharSet> leading,
    CR<CharSet> trailing) {
    if (0 < string.size()) {
        Span<char> view = string.toSpan();
        LOGIC_ASSERTION_CHECK(
            view.data() != nullptr, "View data cannot be nullptr");
        char* end = view.data() + string.size();

        while (0 < view.size() && leading.contains(view.at(0))) {
            view.moveStart(1, end);
        }

        while (0 < view.size() && trailing.contains(view.at(1_B))) {
            view.moveEnd(-1, end);
        }

        return Str(view);
    } else {
        return Str();
    }
}

Vec<Str> hstd::split(CR<Str> str, char ch) {
    Vec<Str> res;
    for (const auto& it : str.split(ch)) { res.push_back(it); }
    return res;
}

Vec<Str> hstd::split_keep_separator(const Str& str, CharSet sep) {
    Vec<Str> result;
    int      prev = 0, curr = 0;
    while (curr < str.length()) {
        if (sep.contains(str[curr])) {
            if (prev != curr) {
                result.push_back(str.substr(prev, curr - prev));
            }
            prev = curr;
            while (curr < str.length() - 1 && str[curr + 1] == str[curr]) {
                curr++;
            }
            result.push_back(str.substr(prev, curr - prev + 1));
            curr++;
            prev = curr;
        } else {
            curr++;
        }
    }
    if (prev < curr) { result.push_back(str.substr(prev, curr - prev)); }
    return result;
}

Vec<Str> hstd::visibleUnicodeName(std::string_view str, bool useUnicode) {
    Vec<Str> result;
    for (char ch : str) {
        if (ch <= 127) {
            if (useUnicode) {
                result.push_back(visibleName(ch).first);
            } else {
                result.push_back(visibleName(ch).second);
            }
        } else {
            result.push_back(ch);
        }
    }

    return result;
}

Vec<Str> hstd::visibleUnicodeName(Str const& str, bool useUnicode) {
    return visibleUnicodeName(std::string_view{str.toBase()}, useUnicode);
}

Pair<Str, Str> hstd::visibleName(char ch) {
    switch (ch) {
            // clang-format off
        case '\x00': return {Str("␀"), "[NUL]"}; // Null character
        case '\x01': return {Str("␁"), "[SOH]"}; // Start of header
        case '\x02': return {Str("␂"), "[STX]"}; // Start of text
        case '\x03': return {Str("␃"), "[ETX]"}; // End of text
        case '\x04': return {Str("␄"), "[EOT]"}; // End transmission
        case '\x05': return {Str("␅"), "[ENQ]"}; // Enquiry
        case '\x06': return {Str("␆"), "[ACK]"}; // Acknowledge
        case '\x07': return {Str("␇"), "[BEL]"}; // Bell
        case '\x08': return {Str("␈"), "[BS]"};  // Backspace
        case '\x09': return {Str("␉"), "[HT]"};  // Horizontal tab
        case '\x0A': return {Str("␤"), "[LF]"};  // Line feed
        case '\x0B': return {Str("␋"), "[VT]"};  // Vertical tab
        case '\x0C': return {Str("␌"), "[FF]"};  // Form feed
        case '\x0D': return {Str("␍"), "[CR]"};  // Carriage return
        case '\x0E': return {Str("␎"), "[SO]"};  // Shift out
        case '\x0F': return {Str("␏"), "[SI]"};  // Shift in
        case '\x10': return {Str("␐"), "[DLE]"}; // Data link escape
        case '\x11': return {Str("␑"), "[DC1]"}; // Device control 1
        case '\x12': return {Str("␒"), "[DC2]"}; // Device control 2
        case '\x13': return {Str("␓"), "[DC3]"}; // Device control 3
        case '\x14': return {Str("␔"), "[DC4]"}; // Device control 4
        case '\x15': return {Str("␕"), "[NAK]"}; // Negative ack
        case '\x16': return {Str("␖"), "[SYN]"}; // Synchronous idle
        case '\x17': return {Str("␗"), "[ETB]"}; // End tr. block
        case '\x18': return {Str("␘"), "[CAN]"}; // Cancel
        case '\x19': return {Str("␙"), "[EM]"};  // End of medium
        case '\x1A': return {Str("␚"), "[SUB]"}; // Substitute
        case '\x1B': return {Str("␛"), "[ESC]"}; // Escape
        case '\x1C': return {Str("␜"), "[FS]"};  // File separator
        case '\x1D': return {Str("␝"), "[GS]"};  // Group separator
        case '\x1E': return {Str("␞"), "[RS]"};  // Record separator
        case '\x1F': return {Str("␟"), "[US]"};  // Unit separator
        case '\x7f': return {Str("␡"), "[DEL]"}; // Delete
        case ' ': return {Str("␣"), "[SPC]"};    // Space
            // clang-format on
        default: return {Str(1, ch), Str(1, ch)};
    }
}

Str hstd::indent(CR<Str> str, int spaces, char space, Str prefix) {
    auto lines = str.split('\n');
    for (auto& line : lines) {
        line = prefix + repeat(Str(space), spaces) + line;
    }
    return Str{"\n"}.join(lines);
}

Str hstd::normalize(CR<Str> in) {
    Str res;
    for (char c : in) {
        if (!(c == '_' || c == '-')) {
            if (islower(c) || isdigit(c)) {
                res += c;
            } else if (isupper(c)) {
                res += tolower(c);
            }
        }
    }
    return res;
}

Str hstd::repeat(CR<Str> str, int count) {
    Str res;
    res.reserve(str.size() * count);
    for (int i = 0; i < count; ++i) { res += str; }
    return res;
}

Str hstd::left_aligned(CR<Str> str, int n, char c) {
    auto s         = str;
    int  rune_size = rune_length(str);
    if (rune_size < n) { s.append(Str(c).repeated(n - rune_size)); }
    return s;
}

Str hstd::right_aligned(CR<Str> str, int n, char c) {
    Str res;
    int rune_size = rune_length(str);

    if (rune_size < n) { res.append(Str(c).repeated(n - rune_size)); }

    res.append(str);
    return res;
}

Str hstd::escape_for_write(const Str& str, bool quote) {
    Str res;
    res.reserve(str.size());
    if (quote) { res += "\""; }
    for (const auto& c : str) {
        if (c == '\t') {
            res += "\\t";
        } else if (c == '\n') {
            res += "\\n";
        } else if (c == '"' && quote) {
            res += "\\\"";
        } else {
            res += c;
        }
    }
    if (quote) { res += "\""; }
    return res;
}

int hstd::rune_length(const std::string& str) {
    int count = 0;
    for (int i = 0; i < str.size();) {
        unsigned char byte = static_cast<unsigned char>(str.at(i));
        if (byte <= 127) {
            i += 1;
        } else if ((byte >> 5) == 0b110) {
            i += 2;
        } else if ((byte >> 4) == 0b1110) {
            i += 3;
        } else if ((byte >> 3) == 0b11110) {
            i += 4;
        } else if ((byte >> 2) == 0b111110) {
            i += 5;
        } else if ((byte >> 1) == 0b1111110) {
            i += 6;
        } else {
            i += 1;
        }
        count++;
    }
    return count;
}

// This is mostly for fancy rendering, so should be ok as it is, but really
// it ought to be a generator of string view slices.
std::vector<std::string> hstd::rune_chunks(const std::string& str) {
    std::vector<std::string> runes;
    for (int i = 0; i < str.size();) {
        int           len  = 0;
        unsigned char byte = static_cast<unsigned char>(str.at(i));
        if (byte <= 127) {
            len = 1;
        } else if ((byte >> 5) == 0b110) {
            len = 2;
        } else if ((byte >> 4) == 0b1110) {
            len = 3;
        } else if ((byte >> 3) == 0b11110) {
            len = 4;
        } else if ((byte >> 2) == 0b111110) {
            len = 5;
        } else if ((byte >> 1) == 0b1111110) {
            len = 6;
        } else {
            len = 1; // Invalid UTF-8 sequence, treat as single byte
        }

        runes.push_back(str.substr(i, len));
        i += len;
    }
    return runes;
}

Str hstd::lstrip(CR<Str> string, CR<CharSet> chars) {
    return strip(string, chars, {});
}

Str hstd::rstrip(CR<Str> string, CR<CharSet> chars) {
    return strip(string, {}, chars);
}

Str hstd::wrap_text(const Vec<Str>& words, int maxWidth, bool justified) {
    Vec<Str> lines;
    Vec<Str> buffer;
    int      currentWidth = 0;

    auto fold_buffer = [&]() {
        if (justified && 1 < buffer.size()) {
            Vec<Str> padding;
            padding.resize(buffer.size() - 1);
            auto join_line = [&]() {
                // _dfmt("= = = = = = = = = =", buffer, padding);
                Str res;
                for (int i = 0; i < buffer.size(); ++i) {
                    if (0 < i) {
                        // _dfmt(padding.at(i - 1));
                        res += padding.at(i - 1);
                    }
                    // _dfmt(res, buffer.at(i), i, res.size());
                    res += buffer.at(i);
                }
                return res;
            };
            int slots      = buffer.size() - 1;
            int toAdd      = maxWidth - (currentWidth - slots);
            int addPerSlot = toAdd / slots;

            for (int i = 0; i < padding.size(); ++i) {
                padding.at(i) = Str{addPerSlot, ' '};
            }

            // I'm writing this code at 2024-12-31T22:53:23+04:00 and I
            // don't give a shit how performant this is.
            while (join_line().size() < maxWidth) {
                for (int i = 0; (i < padding.size())
                                && (join_line().size() < maxWidth);
                     ++i) {
                    padding.at(i).append(" ");
                }
            }

            auto res = join_line();
            // _dfmt(res.size(), res);
            lines.push_back(res);

        } else {
            // _dbg(buffer);
            Str line = std::accumulate(
                buffer.begin() + 1,
                buffer.end(),
                buffer[0],
                [](const Str& a, const Str& b) { return a + " "_ss + b; });
            lines.push_back(line);
        }
        buffer.clear();
        currentWidth = 0;
    };

    for (const auto& word : words) {
        if (maxWidth
            < (currentWidth + word.size() + (buffer.empty() ? 0 : 1))) {
            if (!buffer.empty()) { fold_buffer(); }
        }
        buffer.push_back(word);
        currentWidth += word.size() + (buffer.empty() ? 0 : 1);
    }

    if (!buffer.empty()) { fold_buffer(); }

    if (lines.empty()) {
        return "";
    } else {
        return std::accumulate(
            lines.begin() + 1,
            lines.end(),
            lines[0],
            [](const Str& a, const Str& b) { return a + "\n"_ss + b; });
    }
}

void hstd::replace_all(
    std::string&       str,
    const std::string& from,
    const std::string& to) {
    if (from.empty()) { return; }

    size_t pos = 0;
    while ((pos = str.find(from, pos)) != std::string::npos) {
        str.replace(pos, from.length(), to);
        pos += to.length();
    }
}

bool hstd::iequals(const std::string& a, const std::string& b) {
    if (a.length() != b.length()) {
        return false;
    } else {
        return std::equal(
            a.begin(), a.end(), b.begin(), b.end(), [](char a, char b) {
                return std::tolower(static_cast<unsigned char>(a))
                    == std::tolower(static_cast<unsigned char>(b));
            });
    }
}

std::string hstd::escape_literal(const std::string_view& in) {
    std::string res;
    res.reserve(in.size() + 2);
    res += "«";
    for (char c : in) {
        if (c == '\n') {
            res += "␤";

        } else {
            res += c;
        }
    }

    res += "»";

    return res;
}

std::string hstd::escape_literal(const std::string& in) {
    return escape_literal(std::string_view{in});
}

void hstd::validate_utf8(const std::string& str) {
    const unsigned char* bytes = reinterpret_cast<const unsigned char*>(
        str.data());
    size_t len = str.size();

    for (size_t i = 0; i < len; i++) {
        if (bytes[i] <= 0x7F) {
            // Single-byte character (ASCII)
            continue;
        } else if (bytes[i] >= 0xC2 && bytes[i] <= 0xDF) {
            // 2-byte sequence
            if (i + 1 >= len) {
                throw logic_assertion_error::init(std::format(
                    "Incomplete 2-byte UTF-8 sequence at position {}", i));
            }
            if ((bytes[i + 1] & 0xC0) != 0x80) {
                throw logic_assertion_error::init(std::format(
                    "Invalid 2-byte UTF-8 sequence at position {}", i));
            }
            i += 1;
        } else if (bytes[i] >= 0xE0 && bytes[i] <= 0xEF) {
            // 3-byte sequence
            if (i + 2 >= len) {
                throw logic_assertion_error::init(std::format(
                    "Incomplete 3-byte UTF-8 sequence at position {}", i));
            }
            if ((bytes[i + 1] & 0xC0) != 0x80
                || (bytes[i + 2] & 0xC0) != 0x80) {
                throw logic_assertion_error::init(std::format(
                    "Invalid 3-byte UTF-8 sequence at position {}", i));
            }

            // Special case for UTF-8 surrogate values
            if (bytes[i] == 0xE0 && (bytes[i + 1] < 0xA0)) {
                throw logic_assertion_error::init(std::format(
                    "Invalid 3-byte UTF-8 sequence (overlong encoding) at "
                    "position {}",
                    i));
            }
            if (bytes[i] == 0xED && (bytes[i + 1] > 0x9F)) {
                throw logic_assertion_error::init(std::format(
                    "Invalid 3-byte UTF-8 sequence (surrogate pair) at "
                    "position {}",
                    i));
            }

            i += 2;
        } else if (bytes[i] >= 0xF0 && bytes[i] <= 0xF4) {
            // 4-byte sequence
            if (i + 3 >= len) {
                throw logic_assertion_error::init(std::format(
                    "Incomplete 4-byte UTF-8 sequence at position {}", i));
            }
            if ((bytes[i + 1] & 0xC0) != 0x80
                || (bytes[i + 2] & 0xC0) != 0x80
                || (bytes[i + 3] & 0xC0) != 0x80) {
                throw logic_assertion_error::init(std::format(
                    "Invalid 4-byte UTF-8 sequence at position {}", i));
            }

            // Check for valid range
            if (bytes[i] == 0xF0 && (bytes[i + 1] < 0x90)) {
                throw logic_assertion_error::init(std::format(
                    "Invalid 4-byte UTF-8 sequence (overlong encoding) at "
                    "position {}",
                    i));
            }
            if (bytes[i] == 0xF4 && (bytes[i + 1] > 0x8F)) {
                throw logic_assertion_error::init(std::format(
                    "Invalid 4-byte UTF-8 sequence (out of Unicode range) "
                    "at position {}",
                    i));
            }

            i += 3;
        } else {
            throw logic_assertion_error::init(std::format(
                "Invalid UTF-8 leading byte 0x{:02X} at position {}",
                bytes[i],
                i));
        }
    }
}
