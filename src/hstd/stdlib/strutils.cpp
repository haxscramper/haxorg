#include <hstd/stdlib/strutils.hpp>
#include <absl/log/log.h>
#include <absl/log/check.h>

std::string unicodeCharMappings[256][15] = {
    [(int)'A']
    = {std::string("A"),
       std::string("Ɐ"),
       std::string("𝔄"),
       std::string("𝕬"),
       std::string("𝔸"),
       std::string("𝐀"),
       std::string("𝐴"),
       std::string("𝑨"),
       std::string("𝒜"),
       std::string("𝓐"),
       std::string("𝖠"),
       std::string("𝗔"),
       std::string("𝘈"),
       std::string("𝘼"),
       std::string("𝙰")},
    [(int)'B']
    = {std::string("B"),
       std::string("B"),
       std::string("𝔅"),
       std::string("𝕭"),
       std::string("𝔹"),
       std::string("𝐁"),
       std::string("𝐵"),
       std::string("𝑩"),
       std::string("ℬ"),
       std::string("𝓑"),
       std::string("𝖡"),
       std::string("𝗕"),
       std::string("𝘉"),
       std::string("𝘽"),
       std::string("𝙱")},
    [(int)'C']
    = {std::string("C"),
       std::string("Ɔ"),
       std::string("ℭ"),
       std::string("𝕮"),
       std::string("ℂ"),
       std::string("𝐂"),
       std::string("𝐶"),
       std::string("𝑪"),
       std::string("𝒞"),
       std::string("𝓒"),
       std::string("𝖢"),
       std::string("𝗖"),
       std::string("𝘊"),
       std::string("𝘾"),
       std::string("𝙲")},
    [(int)'D']
    = {std::string("D"),
       std::string("D"),
       std::string("𝔇"),
       std::string("𝕯"),
       std::string("𝔻"),
       std::string("𝐃"),
       std::string("𝐷"),
       std::string("𝑫"),
       std::string("𝒟"),
       std::string("𝓓"),
       std::string("𝖣"),
       std::string("𝗗"),
       std::string("𝘋"),
       std::string("𝘿"),
       std::string("𝙳")},
    [(int)'E']
    = {std::string("E"),
       std::string("Ǝ"),
       std::string("𝔈"),
       std::string("𝕰"),
       std::string("𝔼"),
       std::string("𝐄"),
       std::string("𝐸"),
       std::string("𝑬"),
       std::string("ℰ"),
       std::string("𝓔"),
       std::string("𝖤"),
       std::string("𝗘"),
       std::string("𝘌"),
       std::string("𝙀"),
       std::string("𝙴")},
    [(int)'F']
    = {std::string("F"),
       std::string("Ⅎ"),
       std::string("𝔉"),
       std::string("𝕱"),
       std::string("𝔽"),
       std::string("𝐅"),
       std::string("𝐹"),
       std::string("𝑭"),
       std::string("ℱ"),
       std::string("𝓕"),
       std::string("𝖥"),
       std::string("𝗙"),
       std::string("𝘍"),
       std::string("𝙁"),
       std::string("𝙵")},
    [(int)'G']
    = {std::string("G"),
       std::string("⅁"),
       std::string("𝔊"),
       std::string("𝕲"),
       std::string("𝔾"),
       std::string("𝐆"),
       std::string("𝐺"),
       std::string("𝑮"),
       std::string("𝒢"),
       std::string("𝓖"),
       std::string("𝖦"),
       std::string("𝗚"),
       std::string("𝘎"),
       std::string("𝙂"),
       std::string("𝙶")},
    [(int)'H']
    = {std::string("H"),
       std::string("H"),
       std::string("ℌ"),
       std::string("𝕳"),
       std::string("ℍ"),
       std::string("𝐇"),
       std::string("𝐻"),
       std::string("𝑯"),
       std::string("ℋ"),
       std::string("𝓗"),
       std::string("𝖧"),
       std::string("𝗛"),
       std::string("𝘏"),
       std::string("𝙃"),
       std::string("𝙷")},
    [(int)'I']
    = {std::string("I"),
       std::string("I"),
       std::string("ℑ"),
       std::string("𝕴"),
       std::string("𝕀"),
       std::string("𝐈"),
       std::string("𝐼"),
       std::string("𝑰"),
       std::string("ℐ"),
       std::string("𝓘"),
       std::string("𝖨"),
       std::string("𝗜"),
       std::string("𝘐"),
       std::string("𝙄"),
       std::string("𝙸")},
    [(int)'J']
    = {std::string("J"),
       std::string("ſ"),
       std::string("𝔍"),
       std::string("𝕵"),
       std::string("𝕁"),
       std::string("𝐉"),
       std::string("𝐽"),
       std::string("𝑱"),
       std::string("𝒥"),
       std::string("𝓙"),
       std::string("𝖩"),
       std::string("𝗝"),
       std::string("𝘑"),
       std::string("𝙅"),
       std::string("𝙹")},
    [(int)'K']
    = {std::string("K"),
       std::string("Ʞ"),
       std::string("𝔎"),
       std::string("𝕶"),
       std::string("𝕂"),
       std::string("𝐊"),
       std::string("𝐾"),
       std::string("𝑲"),
       std::string("𝒦"),
       std::string("𝓚"),
       std::string("𝖪"),
       std::string("𝗞"),
       std::string("𝘒"),
       std::string("𝙆"),
       std::string("𝙺")},
    [(int)'L']
    = {std::string("L"),
       std::string("Ꞁ"),
       std::string("𝔏"),
       std::string("𝕷"),
       std::string("𝕃"),
       std::string("𝐋"),
       std::string("𝐿"),
       std::string("𝑳"),
       std::string("ℒ"),
       std::string("𝓛"),
       std::string("𝖫"),
       std::string("𝗟"),
       std::string("𝘓"),
       std::string("𝙇"),
       std::string("𝙻")},
    [(int)'M']
    = {std::string("M"),
       std::string("Ɯ"),
       std::string("𝔐"),
       std::string("𝕸"),
       std::string("𝕄"),
       std::string("𝐌"),
       std::string("𝑀"),
       std::string("𝑴"),
       std::string("ℳ"),
       std::string("𝓜"),
       std::string("𝖬"),
       std::string("𝗠"),
       std::string("𝘔"),
       std::string("𝙈"),
       std::string("𝙼")},
    [(int)'N']
    = {std::string("N"),
       std::string("N"),
       std::string("𝔑"),
       std::string("𝕹"),
       std::string("ℕ"),
       std::string("𝐍"),
       std::string("𝑁"),
       std::string("𝑵"),
       std::string("𝒩"),
       std::string("𝓝"),
       std::string("𝖭"),
       std::string("𝗡"),
       std::string("𝘕"),
       std::string("𝙉"),
       std::string("𝙽")},
    [(int)'O']
    = {std::string("O"),
       std::string("O"),
       std::string("𝔒"),
       std::string("𝕺"),
       std::string("𝕆"),
       std::string("𝐎"),
       std::string("𝑂"),
       std::string("𝑶"),
       std::string("𝒪"),
       std::string("𝓞"),
       std::string("𝖮"),
       std::string("𝗢"),
       std::string("𝘖"),
       std::string("𝙊"),
       std::string("𝙾")},
    [(int)'P']
    = {std::string("P"),
       std::string("Ԁ"),
       std::string("𝔓"),
       std::string("𝕻"),
       std::string("ℙ"),
       std::string("𝐏"),
       std::string("𝑃"),
       std::string("𝑷"),
       std::string("𝒫"),
       std::string("𝓟"),
       std::string("𝖯"),
       std::string("𝗣"),
       std::string("𝘗"),
       std::string("𝙋"),
       std::string("𝙿")},
    [(int)'Q']
    = {std::string("Q"),
       std::string("Ò"),
       std::string("𝔔"),
       std::string("𝕼"),
       std::string("ℚ"),
       std::string("𝐐"),
       std::string("𝑄"),
       std::string("𝑸"),
       std::string("𝒬"),
       std::string("𝓠"),
       std::string("𝖰"),
       std::string("𝗤"),
       std::string("𝘘"),
       std::string("𝙌"),
       std::string("𝚀")},
    [(int)'R']
    = {std::string("R"),
       std::string("ᴚ"),
       std::string("ℜ"),
       std::string("𝕽"),
       std::string("ℝ"),
       std::string("𝐑"),
       std::string("𝑅"),
       std::string("𝑹"),
       std::string("ℛ"),
       std::string("𝓡"),
       std::string("𝖱"),
       std::string("𝗥"),
       std::string("𝘙"),
       std::string("𝙍"),
       std::string("𝚁")},
    [(int)'S']
    = {std::string("S"),
       std::string("S"),
       std::string("𝔖"),
       std::string("𝕾"),
       std::string("𝕊"),
       std::string("𝐒"),
       std::string("𝑆"),
       std::string("𝑺"),
       std::string("𝒮"),
       std::string("𝓢"),
       std::string("𝖲"),
       std::string("𝗦"),
       std::string("𝘚"),
       std::string("𝙎"),
       std::string("𝚂")},
    [(int)'T']
    = {std::string("T"),
       std::string("Ʇ"),
       std::string("𝔗"),
       std::string("𝕿"),
       std::string("𝕋"),
       std::string("𝐓"),
       std::string("𝑇"),
       std::string("𝑻"),
       std::string("𝒯"),
       std::string("𝓣"),
       std::string("𝖳"),
       std::string("𝗧"),
       std::string("𝘛"),
       std::string("𝙏"),
       std::string("𝚃")},
    [(int)'U']
    = {std::string("U"),
       std::string("∩"),
       std::string("𝔘"),
       std::string("𝖀"),
       std::string("𝕌"),
       std::string("𝐔"),
       std::string("𝑈"),
       std::string("𝑼"),
       std::string("𝒰"),
       std::string("𝓤"),
       std::string("𝖴"),
       std::string("𝗨"),
       std::string("𝘜"),
       std::string("𝙐"),
       std::string("𝚄")},
    [(int)'V']
    = {std::string("V"),
       std::string("Ʌ"),
       std::string("𝔙"),
       std::string("𝖁"),
       std::string("𝕍"),
       std::string("𝐕"),
       std::string("𝑉"),
       std::string("𝑽"),
       std::string("𝒱"),
       std::string("𝓥"),
       std::string("𝖵"),
       std::string("𝗩"),
       std::string("𝘝"),
       std::string("𝙑"),
       std::string("𝚅")},
    [(int)'W']
    = {std::string("W"),
       std::string("ʍ"),
       std::string("𝔚"),
       std::string("𝖂"),
       std::string("𝕎"),
       std::string("𝐖"),
       std::string("𝑊"),
       std::string("𝑾"),
       std::string("𝒲"),
       std::string("𝓦"),
       std::string("𝖶"),
       std::string("𝗪"),
       std::string("𝘞"),
       std::string("𝙒"),
       std::string("𝚆")},
    [(int)'X']
    = {std::string("X"),
       std::
           string("X"),
       std::
           string("𝔛"),
       std::
           string("𝖃"),
       std::
           string("𝕏"),
       std::
           string("𝐗"),
       std::
           string("𝑋"),
       std::
           string("𝑿"),
       std::
           string("𝒳"),
       std::
           string("𝓧"),
       std::
           string("𝖷"),
       std::
           string("𝗫"),
       std::
           string("𝘟"),
       std::
           string("𝙓"),
       std::
           string("𝚇")},
    [(int)'Y']
    = {std::string("Y"),
       std::
           string("⅄"),
       std::
           string("𝔜"),
       std::
           string("𝖄"),
       std::
           string("𝕐"),
       std::
           string("𝐘"),
       std::
           string("𝑌"),
       std::
           string("𝒀"),
       std::
           string("𝒴"),
       std::
           string("𝓨"),
       std::
           string("𝖸"),
       std::
           string("𝗬"),
       std::
           string("𝘠"),
       std::
           string("𝙔"),
       std::
           string("𝚈")},
    [(int)'Z']
    = {std::string("Z"),
       std::
           string("Z"),
       std::
           string("ℨ"),
       std::
           string("𝖅"),
       std::
           string("ℤ"),
       std::
           string("𝐙"),
       std::
           string("𝑍"),
       std::
           string("𝒁"),
       std::
           string("𝒵"),
       std::
           string("𝓩"),
       std::
           string("𝖹"),
       std::
           string("𝗭"),
       std::
           string("𝘡"),
       std::
           string("𝙕"),
       std::
           string("𝚉")},
    [(int)'a']
    = {std::string("a"),
       std::
           string("ɐ"),
       std::
           string("𝔞"),
       std::
           string("𝖆"),
       std::
           string("𝕒"),
       std::
           string("𝐚"),
       std::
           string("𝑎"),
       std::
           string("𝒂"),
       std::
           string("𝒶"),
       std::
           string("𝓪"),
       std::
           string("𝖺"),
       std::
           string("𝗮"),
       std::
           string("𝘢"),
       std::
           string("𝙖"),
       std::
           string("𝚊")},
    [(int)'b']
    = {std::string("b"),
       std::
           string("q"),
       std::
           string("𝔟"),
       std::
           string("𝖇"),
       std::
           string("𝕓"),
       std::
           string("𝐛"),
       std::
           string("𝑏"),
       std::
           string("𝒃"),
       std::
           string("𝒷"),
       std::
           string("𝓫"),
       std::
           string("𝖻"),
       std::
           string("𝗯"),
       std::
           string("𝘣"),
       std::
           string("𝙗"),
       std::
           string("𝚋")},
    [(int)'c']
    = {std::string("c"),
       std::
           string("ɔ"),
       std::
           string("𝔠"),
       std::
           string("𝖈"),
       std::
           string("𝕔"),
       std::
           string("𝐜"),
       std::
           string("𝑐"),
       std::
           string("𝒄"),
       std::
           string("𝒸"),
       std::
           string("𝓬"),
       std::
           string("𝖼"),
       std::
           string("𝗰"),
       std::
           string("𝘤"),
       std::
           string("𝙘"),
       std::
           string("𝚌")},
    [(int)'d']
    = {std::string("d"),
       std::
           string("p"),
       std::
           string("𝔡"),
       std::
           string("𝖉"),
       std::
           string("𝕕"),
       std::
           string("𝐝"),
       std::
           string("𝑑"),
       std::
           string("𝒅"),
       std::
           string("𝒹"),
       std::
           string("𝓭"),
       std::
           string("𝖽"),
       std::
           string("𝗱"),
       std::
           string("𝘥"),
       std::
           string("𝙙"),
       std::
           string("𝚍")},
    [(int)'e']
    = {std::string("e"),
       std::
           string("ǝ"),
       std::
           string("𝔢"),
       std::
           string("𝖊"),
       std::
           string("𝕖"),
       std::
           string("𝐞"),
       std::
           string("𝑒"),
       std::
           string("𝒆"),
       std::
           string("ℯ"),
       std::
           string("𝓮"),
       std::
           string("𝖾"),
       std::
           string("𝗲"),
       std::
           string("𝘦"),
       std::
           string("𝙚"),
       std::
           string("𝚎")},
    [(int)'f']
    = {std::string("f"),
       std::
           string("ɟ"),
       std::
           string("𝔣"),
       std::
           string("𝖋"),
       std::
           string("𝕗"),
       std::
           string("𝐟"),
       std::
           string("𝑓"),
       std::
           string("𝒇"),
       std::
           string("𝒻"),
       std::
           string("𝓯"),
       std::
           string("𝖿"),
       std::
           string("𝗳"),
       std::
           string("𝘧"),
       std::
           string("𝙛"),
       std::
           string("𝚏")},
    [(int)'g']
    = {std::string("g"),
       std::
           string("ᵷ"),
       std::
           string("𝔤"),
       std::
           string("𝖌"),
       std::
           string("𝕘"),
       std::
           string("𝐠"),
       std::
           string("𝑔"),
       std::
           string("𝒈"),
       std::
           string("ℊ"),
       std::
           string("𝓰"),
       std::
           string("𝗀"),
       std::
           string("𝗴"),
       std::
           string("𝘨"),
       std::
           string("𝙜"),
       std::
           string("𝚐")},
    [(int)'h']
    = {std::string("h"),
       std::
           string("ɥ"),
       std::
           string("𝔥"),
       std::
           string("𝖍"),
       std::
           string("𝕙"),
       std::
           string("𝐡"),
       std::
           string("ℎ"),
       std::
           string("𝒉"),
       std::
           string("𝒽"),
       std::
           string("𝓱"),
       std::
           string("𝗁"),
       std::
           string("𝗵"),
       std::
           string("𝘩"),
       std::
           string("𝙝"),
       std::
           string("𝚑")},
    [(int)'i']
    = {std::string("i"),
       std::
           string("ᴉ"),
       std::
           string("𝔦"),
       std::
           string("𝖎"),
       std::
           string("𝕚"),
       std::
           string("𝐢"),
       std::
           string("𝑖"),
       std::
           string("𝒊"),
       std::
           string("𝒾"),
       std::
           string("𝓲"),
       std::
           string("𝗂"),
       std::
           string("𝗶"),
       std::
           string("𝘪"),
       std::
           string("𝙞"),
       std::
           string("𝚒")},
    [(int)'j']
    = {std::string("j"),
       std::
           string("f"),
       std::
           string("𝔧"),
       std::
           string("𝖏"),
       std::
           string("𝕛"),
       std::
           string("𝐣"),
       std::
           string("𝑗"),
       std::
           string("𝒋"),
       std::
           string("𝒿"),
       std::
           string("𝓳"),
       std::
           string("𝗃"),
       std::
           string("𝗷"),
       std::
           string("𝘫"),
       std::
           string("𝙟"),
       std::
           string("𝚓")},
    [(int)'k']
    = {std::string("k"),
       std::
           string("ʞ"),
       std::
           string("𝔨"),
       std::
           string("𝖐"),
       std::
           string("𝕜"),
       std::
           string("𝐤"),
       std::
           string("𝑘"),
       std::
           string("𝒌"),
       std::
           string("𝓀"),
       std::
           string("𝓴"),
       std::
           string("𝗄"),
       std::
           string("𝗸"),
       std::
           string("𝘬"),
       std::
           string("𝙠"),
       std::
           string("𝚔")},
    [(int)'l']
    = {std::string("l"),
       std::
           string("ꞁ"),
       std::
           string("𝔩"),
       std::
           string("𝖑"),
       std::
           string("𝕝"),
       std::
           string("𝐥"),
       std::
           string("𝑙"),
       std::
           string("𝒍"),
       std::
           string("𝓁"),
       std::
           string("𝓵"),
       std::
           string("𝗅"),
       std::
           string("𝗹"),
       std::
           string("𝘭"),
       std::
           string("𝙡"),
       std::
           string("𝚕")},
    [(int)'m']
    = {std::string("m"),
       std::
           string("ɯ"),
       std::
           string("𝔪"),
       std::
           string("𝖒"),
       std::
           string("𝕞"),
       std::
           string("𝐦"),
       std::
           string("𝑚"),
       std::
           string("𝒎"),
       std::
           string("𝓂"),
       std::
           string("𝓶"),
       std::
           string("𝗆"),
       std::
           string("𝗺"),
       std::
           string("𝘮"),
       std::
           string("𝙢"),
       std::
           string("𝚖")},
    [(int)'n']
    = {std::string("n"),
       std::
           string("u"),
       std::
           string("𝔫"),
       std::
           string("𝖓"),
       std::
           string("𝕟"),
       std::
           string("𝐧"),
       std::
           string("𝑛"),
       std::
           string("𝒏"),
       std::
           string("𝓃"),
       std::
           string("𝓷"),
       std::
           string("𝗇"),
       std::
           string("𝗻"),
       std::
           string("𝘯"),
       std::
           string("𝙣"),
       std::
           string("𝚗")},
    [(int)'o']
    = {std::string("o"),
       std::
           string("o"),
       std::
           string("𝔬"),
       std::
           string("𝖔"),
       std::
           string("𝕠"),
       std::
           string("𝐨"),
       std::
           string("𝑜"),
       std::
           string("𝒐"),
       std::
           string("ℴ"),
       std::
           string("𝓸"),
       std::
           string("𝗈"),
       std::
           string("𝗼"),
       std::
           string("𝘰"),
       std::
           string("𝙤"),
       std::
           string("𝚘")},
    [(int)'p']
    = {std::string("p"),
       std::
           string("d"),
       std::
           string("𝔭"),
       std::
           string("𝖕"),
       std::
           string("𝕡"),
       std::
           string("𝐩"),
       std::
           string("𝑝"),
       std::
           string("𝒑"),
       std::
           string("𝓅"),
       std::
           string("𝓹"),
       std::
           string("𝗉"),
       std::
           string("𝗽"),
       std::
           string("𝘱"),
       std::
           string("𝙥"),
       std::
           string("𝚙")},
    [(int)'q']
    = {std::string("q"),
       std::
           string("b"),
       std::
           string("𝔮"),
       std::
           string("𝖖"),
       std::
           string("𝕢"),
       std::
           string("𝐪"),
       std::
           string("𝑞"),
       std::
           string("𝒒"),
       std::
           string("𝓆"),
       std::
           string("𝓺"),
       std::
           string("𝗊"),
       std::
           string("𝗾"),
       std::
           string("𝘲"),
       std::
           string("𝙦"),
       std::
           string("𝚚")},
    [(int)'r']
    = {std::string("r"),
       std::
           string("ɹ"),
       std::
           string("𝔯"),
       std::
           string("𝖗"),
       std::
           string("𝕣"),
       std::
           string("𝐫"),
       std::
           string("𝑟"),
       std::
           string("𝒓"),
       std::
           string("𝓇"),
       std::
           string("𝓻"),
       std::
           string("𝗋"),
       std::
           string("𝗿"),
       std::
           string("𝘳"),
       std::
           string("𝙧"),
       std::
           string("𝚛")},
    [(int)'s']
    = {std::string("s"),
       std::
           string("s"),
       std::
           string("𝔰"),
       std::
           string("𝖘"),
       std::
           string("𝕤"),
       std::
           string("𝐬"),
       std::
           string("𝑠"),
       std::
           string("𝒔"),
       std::
           string("𝓈"),
       std::
           string("𝓼"),
       std::
           string("𝗌"),
       std::
           string("𝘀"),
       std::
           string("𝘴"),
       std::
           string("𝙨"),
       std::
           string("𝚜")},
    [(int)'t']
    = {std::string("t"),
       std::
           string("ʇ"),
       std::
           string("𝔱"),
       std::
           string("𝖙"),
       std::
           string("𝕥"),
       std::
           string("𝐭"),
       std::
           string("𝑡"),
       std::
           string("𝒕"),
       std::
           string("𝓉"),
       std::
           string("𝓽"),
       std::
           string("𝗍"),
       std::
           string("𝘁"),
       std::
           string("𝘵"),
       std::
           string("𝙩"),
       std::
           string("𝚝")},
    [(int)'u']
    = {std::string("u"),
       std::
           string("n"),
       std::
           string("𝔲"),
       std::
           string("𝖚"),
       std::
           string("𝕦"),
       std::
           string("𝐮"),
       std::
           string("𝑢"),
       std::
           string("𝒖"),
       std::
           string("𝓊"),
       std::
           string("𝓾"),
       std::
           string("𝗎"),
       std::
           string("𝘂"),
       std::
           string("𝘶"),
       std::
           string("𝙪"),
       std::
           string("𝚞")},
    [(int)'v']
    = {std::string("v"),
       std::
           string("ʌ"),
       std::
           string("𝔳"),
       std::
           string("𝖛"),
       std::
           string("𝕧"),
       std::
           string("𝐯"),
       std::
           string("𝑣"),
       std::
           string("𝒗"),
       std::
           string("𝓋"),
       std::
           string("𝓿"),
       std::
           string("𝗏"),
       std::
           string("𝘃"),
       std::
           string("𝘷"),
       std::
           string("𝙫"),
       std::
           string("𝚟")},
    [(int)'w']
    = {std::string("w"),
       std::
           string("ʍ"),
       std::
           string("𝔴"),
       std::
           string("𝖜"),
       std::
           string("𝕨"),
       std::
           string("𝐰"),
       std::
           string("𝑤"),
       std::
           string("𝒘"),
       std::
           string("𝓌"),
       std::
           string("𝔀"),
       std::
           string("𝗐"),
       std::
           string("𝘄"),
       std::
           string("𝘸"),
       std::
           string("𝙬"),
       std::
           string("𝚠")},
    [(int)'x']
    = {std::string("x"),
       std::
           string("x"),
       std::
           string("𝔵"),
       std::
           string("𝖝"),
       std::
           string("𝕩"),
       std::
           string("𝐱"),
       std::
           string("𝑥"),
       std::
           string("𝒙"),
       std::
           string("𝓍"),
       std::
           string("𝔁"),
       std::
           string("𝗑"),
       std::
           string("𝘅"),
       std::
           string("𝘹"),
       std::
           string("𝙭"),
       std::
           string("𝚡")},
    [(int)'y']
    = {std::string("y"),
       std::
           string("ʎ"),
       std::
           string("𝔶"),
       std::
           string("𝖞"),
       std::
           string("𝕪"),
       std::
           string("𝐲"),
       std::
           string("𝑦"),
       std::
           string("𝒚"),
       std::
           string("𝓎"),
       std::
           string("𝔂"),
       std::
           string("𝗒"),
       std::
           string("𝘆"),
       std::
           string("𝘺"),
       std::
           string("𝙮"),
       std::
           string("𝚢")},
    [(int)'z']
    = {std::string("z"),
       std::
           string("z"),
       std::
           string("𝔷"),
       std::
           string("𝖟"),
       std::
           string("𝕫"),
       std::
           string("𝐳"),
       std::
           string("𝑧"),
       std::
           string("𝒛"),
       std::
           string("𝓏"),
       std::
           string("𝔃"),
       std::
           string("𝗓"),
       std::
           string("𝘇"),
       std::
           string("𝘻"),
       std::
           string("𝙯"),
       std::
           string("𝚣")},
    [(int)'0']
    = {std::string("0"),
       std::
           string("0"),
       std::
           string("0"),
       std::
           string("0"),
       std::
           string("𝟘"),
       std::
           string("𝟎"),
       std::
           string("0"),
       std::
           string("0"),
       std::
           string("0"),
       std::
           string("0"),
       std::
           string("0"),
       std::
           string("𝟢"),
       std::
           string("𝟬"),
       std::
           string("0"),
       std::
           string("𝟶")},
    [(int)'1']
    = {std::string("1"),
       std::
           string("1"),
       std::
           string("1"),
       std::
           string("1"),
       std::
           string("𝟙"),
       std::
           string("𝟏"),
       std::
           string("1"),
       std::
           string("1"),
       std::
           string("1"),
       std::
           string("1"),
       std::
           string("1"),
       std::
           string("𝟣"),
       std::
           string("𝟭"),
       std::
           string("1"),
       std::
           string("𝟷")},
    [(int)'2']
    = {std::string("2"),
       std::
           string("2"),
       std::
           string("2"),
       std::
           string("2"),
       std::
           string("𝟚"),
       std::
           string("𝟐"),
       std::
           string("2"),
       std::
           string("2"),
       std::
           string("2"),
       std::
           string("2"),
       std::
           string("2"),
       std::
           string("𝟤"),
       std::
           string("𝟮"),
       std::
           string("2"),
       std::
           string("𝟸")},
    [(int)'3']
    = {std::string("3"),
       std::
           string("3"),
       std::
           string("3"),
       std::
           string("3"),
       std::
           string("𝟛"),
       std::
           string("𝟑"),
       std::
           string("3"),
       std::
           string("3"),
       std::
           string("3"),
       std::
           string("3"),
       std::
           string("3"),
       std::
           string("𝟥"),
       std::
           string("𝟯"),
       std::
           string("3"),
       std::
           string("𝟹")},
    [(int)'4']
    = {std::string("4"),
       std::
           string("4"),
       std::
           string("4"),
       std::
           string("4"),
       std::
           string("𝟜"),
       std::
           string("𝟒"),
       std::
           string("4"),
       std::
           string("4"),
       std::
           string("4"),
       std::
           string("4"),
       std::
           string("4"),
       std::
           string("𝟦"),
       std::
           string("𝟰"),
       std::
           string("4"),
       std::
           string("𝟺")},
    [(int)'5']
    = {std::string("5"),
       std::
           string("5"),
       std::
           string("5"),
       std::
           string("5"),
       std::
           string("𝟝"),
       std::
           string("𝟓"),
       std::
           string("5"),
       std::
           string("5"),
       std::
           string("5"),
       std::
           string("5"),
       std::
           string("5"),
       std::
           string("𝟧"),
       std::
           string("𝟱"),
       std::
           string("5"),
       std::
           string("𝟻")},
    [(int)'6']
    = {std::string("6"),
       std::
           string("6"),
       std::
           string("6"),
       std::
           string("6"),
       std::
           string("𝟞"),
       std::
           string("𝟔"),
       std::
           string("6"),
       std::
           string("6"),
       std::
           string("6"),
       std::
           string("6"),
       std::
           string("6"),
       std::
           string("𝟨"),
       std::
           string("𝟲"),
       std::
           string("6"),
       std::
           string("𝟼")},
    [(int)'7']
    = {std::string("7"),
       std::
           string("7"),
       std::
           string("7"),
       std::
           string("7"),
       std::
           string("𝟟"),
       std::
           string("𝟕"),
       std::
           string("7"),
       std::
           string("7"),
       std::
           string("7"),
       std::
           string("7"),
       std::
           string("7"),
       std::
           string("𝟩"),
       std::
           string("𝟳"),
       std::
           string("7"),
       std::
           string("𝟽")},
    [(int)'8']
    = {std::string("8"),
       std::
           string("8"),
       std::
           string("8"),
       std::
           string("8"),
       std::
           string("𝟠"),
       std::
           string("𝟖"),
       std::
           string("8"),
       std::
           string("8"),
       std::
           string("8"),
       std::
           string("8"),
       std::
           string("8"),
       std::
           string("𝟪"),
       std::
           string("𝟴"),
       std::
           string("8"),
       std::
           string("𝟾")},
    [(int)'9']
    = {std::string("9"),
       std::
           string("9"),
       std::
           string("9"),
       std::
           string("9"),
       std::
           string("𝟡"),
       std::
           string("𝟗"),
       std::
           string("9"),
       std::
           string("9"),
       std::
           string("9"),
       std::
           string("9"),
       std::
           string("9"),
       std::
           string("𝟫"),
       std::
           string("𝟵"),
       std::
           string("9"),
       std::
           string("𝟿")},
};


std::string styledUnicodeMapping(char ch, AsciiStyle style) {
    if (unicodeCharMappings[(int)ch][(int)style] != std::string("\0")) {
        return unicodeCharMappings[(int)ch][(int)style];
    } else {
        return std::string(1, ch);
    }
}

std::string styledUnicodeMapping(
    std::string const& str,
    AsciiStyle         style) {
    std::string result;
    result.reserve(str.size());
    for (const auto& ch : str) {
        result += styledUnicodeMapping(ch, style);
    }
    return result;
}

Str strip(CR<Str> string, CR<CharSet> leading, CR<CharSet> trailing) {
    if (0 < string.size()) {
        Span<char> view = string.toSpan();
        CHECK(view.data() != nullptr);
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

Vec<Str> split(CR<Str> str, char ch) {
    Vec<Str> res;
    for (const auto& it : str.split(ch)) {
        res.push_back(it);
    }
    return res;
}

Vec<Str> split_keep_separator(const Str& str, CharSet sep) {
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
    if (prev < curr) {
        result.push_back(str.substr(prev, curr - prev));
    }
    return result;
}

Vec<Str> visibleUnicodeName(std::string str, bool useUnicode) {
    Vec<Str> result;
    for (char ch : str) {
        if (ch.unicode() <= 127) {
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

Pair<char, std::string> visibleName(char ch) {
    switch (ch.unicode()) {
        case '\x00': return {char(L'␀'), "[NUL]"}; // Null character
        case '\x01': return {char(L'␁'), "[SOH]"}; // Start of header
        case '\x02': return {char(L'␂'), "[STX]"}; // Start of text
        case '\x03': return {char(L'␃'), "[ETX]"}; // End of text
        case '\x04': return {char(L'␄'), "[EOT]"}; // End transmission
        case '\x05': return {char(L'␅'), "[ENQ]"}; // Enquiry
        case '\x06': return {char(L'␆'), "[ACK]"}; // Acknowledge
        case '\x07': return {char(L'␇'), "[BEL]"}; // Bell
        case '\x08': return {char(L'␈'), "[BS]"};  // Backspace
        case '\x09': return {char(L'␉'), "[HT]"};  // Horizontal tab
        case '\x0A': return {char(L'␤'), "[LF]"};  // Line feed
        case '\x0B': return {char(L'␋'), "[VT]"};  // Vertical tab
        case '\x0C': return {char(L'␌'), "[FF]"};  // Form feed
        case '\x0D': return {char(L'␍'), "[CR]"};  // Carriage return
        case '\x0E': return {char(L'␎'), "[SO]"};  // Shift out
        case '\x0F': return {char(L'␏'), "[SI]"};  // Shift in
        case '\x10': return {char(L'␐'), "[DLE]"}; // Data link escape
        case '\x11': return {char(L'␑'), "[DC1]"}; // Device control 1
        case '\x12': return {char(L'␒'), "[DC2]"}; // Device control 2
        case '\x13': return {char(L'␓'), "[DC3]"}; // Device control 3
        case '\x14': return {char(L'␔'), "[DC4]"}; // Device control 4
        case '\x15': return {char(L'␕'), "[NAK]"}; // Negative ack
        case '\x16': return {char(L'␖'), "[SYN]"}; // Synchronous idle
        case '\x17': return {char(L'␗'), "[ETB]"}; // End tr. block
        case '\x18': return {char(L'␘'), "[CAN]"}; // Cancel
        case '\x19': return {char(L'␙'), "[EM]"};  // End of medium
        case '\x1A': return {char(L'␚'), "[SUB]"}; // Substitute
        case '\x1B': return {char(L'␛'), "[ESC]"}; // Escape
        case '\x1C': return {char(L'␜'), "[FS]"};  // File separator
        case '\x1D': return {char(L'␝'), "[GS]"};  // Group separator
        case '\x1E': return {char(L'␞'), "[RS]"};  // Record separator
        case '\x1F': return {char(L'␟'), "[US]"};  // Unit separator
        case '\x7f': return {char(L'␡'), "[DEL]"}; // Delete
        case ' ': return {char(L'␣'), "[SPC]"};    // Space
        default: return {char(ch), std::string(ch)};
    }
}

Str indent(CR<Str> str, int spaces, char space, Str prefix) {
    auto lines = str.split('\n');
    for (auto& line : lines) {
        line = prefix + repeat(Str(space), spaces) + line;
    }
    return join("\n", lines);
}

Str normalize(CR<Str> in) {
    Str res;
    for (char c : in) {
        if (!(c == '_' || c == '-')) {
            if (c.isLower()) {
                res += c;
            } else if (c.isUpper()) {
                res += c.toLower();
            }
        }
    }
    return res;
}

Str repeat(CR<Str> str, int count) {
    Str res;
    res.reserve(str.size() * count);
    for (int i = 0; i < count; ++i) {
        res += str;
    }
    return res;
}

std::string left_aligned(CR<std::string> str, int n, char c) {
    auto s = str;
    if (s.size() < n) {
        s.append(std::string(c).repeated(n - s.size()));
    }
    return s;
}

std::string right_aligned(CR<std::string> str, int n, char c) {
    std::string res;
    if (str.size() < n) {
        res.append(std::string(c).repeated(n - str.size()));
    }
    res.append(str);
    return res;
}

std::string escape_for_write(const std::string& str, bool quote) {
    std::string res;
    res.reserve(str.size());
    if (quote) {
        res += "\"";
    }
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
    if (quote) {
        res += "\"";
    }
    return res;
}
