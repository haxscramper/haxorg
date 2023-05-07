#include <hstd/stdlib/strutils.hpp>
#include <QDebug>

QString unicodeCharMappings[256][15] = {
    [(int)'A']
    = {QString("A"),
       QString("Ɐ"),
       QString("𝔄"),
       QString("𝕬"),
       QString("𝔸"),
       QString("𝐀"),
       QString("𝐴"),
       QString("𝑨"),
       QString("𝒜"),
       QString("𝓐"),
       QString("𝖠"),
       QString("𝗔"),
       QString("𝘈"),
       QString("𝘼"),
       QString("𝙰")},
    [(int)'B']
    = {QString("B"),
       QString("B"),
       QString("𝔅"),
       QString("𝕭"),
       QString("𝔹"),
       QString("𝐁"),
       QString("𝐵"),
       QString("𝑩"),
       QString("ℬ"),
       QString("𝓑"),
       QString("𝖡"),
       QString("𝗕"),
       QString("𝘉"),
       QString("𝘽"),
       QString("𝙱")},
    [(int)'C']
    = {QString("C"),
       QString("Ɔ"),
       QString("ℭ"),
       QString("𝕮"),
       QString("ℂ"),
       QString("𝐂"),
       QString("𝐶"),
       QString("𝑪"),
       QString("𝒞"),
       QString("𝓒"),
       QString("𝖢"),
       QString("𝗖"),
       QString("𝘊"),
       QString("𝘾"),
       QString("𝙲")},
    [(int)'D']
    = {QString("D"),
       QString("D"),
       QString("𝔇"),
       QString("𝕯"),
       QString("𝔻"),
       QString("𝐃"),
       QString("𝐷"),
       QString("𝑫"),
       QString("𝒟"),
       QString("𝓓"),
       QString("𝖣"),
       QString("𝗗"),
       QString("𝘋"),
       QString("𝘿"),
       QString("𝙳")},
    [(int)'E']
    = {QString("E"),
       QString("Ǝ"),
       QString("𝔈"),
       QString("𝕰"),
       QString("𝔼"),
       QString("𝐄"),
       QString("𝐸"),
       QString("𝑬"),
       QString("ℰ"),
       QString("𝓔"),
       QString("𝖤"),
       QString("𝗘"),
       QString("𝘌"),
       QString("𝙀"),
       QString("𝙴")},
    [(int)'F']
    = {QString("F"),
       QString("Ⅎ"),
       QString("𝔉"),
       QString("𝕱"),
       QString("𝔽"),
       QString("𝐅"),
       QString("𝐹"),
       QString("𝑭"),
       QString("ℱ"),
       QString("𝓕"),
       QString("𝖥"),
       QString("𝗙"),
       QString("𝘍"),
       QString("𝙁"),
       QString("𝙵")},
    [(int)'G']
    = {QString("G"),
       QString("⅁"),
       QString("𝔊"),
       QString("𝕲"),
       QString("𝔾"),
       QString("𝐆"),
       QString("𝐺"),
       QString("𝑮"),
       QString("𝒢"),
       QString("𝓖"),
       QString("𝖦"),
       QString("𝗚"),
       QString("𝘎"),
       QString("𝙂"),
       QString("𝙶")},
    [(int)'H']
    = {QString("H"),
       QString("H"),
       QString("ℌ"),
       QString("𝕳"),
       QString("ℍ"),
       QString("𝐇"),
       QString("𝐻"),
       QString("𝑯"),
       QString("ℋ"),
       QString("𝓗"),
       QString("𝖧"),
       QString("𝗛"),
       QString("𝘏"),
       QString("𝙃"),
       QString("𝙷")},
    [(int)'I']
    = {QString("I"),
       QString("I"),
       QString("ℑ"),
       QString("𝕴"),
       QString("𝕀"),
       QString("𝐈"),
       QString("𝐼"),
       QString("𝑰"),
       QString("ℐ"),
       QString("𝓘"),
       QString("𝖨"),
       QString("𝗜"),
       QString("𝘐"),
       QString("𝙄"),
       QString("𝙸")},
    [(int)'J']
    = {QString("J"),
       QString("ſ"),
       QString("𝔍"),
       QString("𝕵"),
       QString("𝕁"),
       QString("𝐉"),
       QString("𝐽"),
       QString("𝑱"),
       QString("𝒥"),
       QString("𝓙"),
       QString("𝖩"),
       QString("𝗝"),
       QString("𝘑"),
       QString("𝙅"),
       QString("𝙹")},
    [(int)'K']
    = {QString("K"),
       QString("Ʞ"),
       QString("𝔎"),
       QString("𝕶"),
       QString("𝕂"),
       QString("𝐊"),
       QString("𝐾"),
       QString("𝑲"),
       QString("𝒦"),
       QString("𝓚"),
       QString("𝖪"),
       QString("𝗞"),
       QString("𝘒"),
       QString("𝙆"),
       QString("𝙺")},
    [(int)'L']
    = {QString("L"),
       QString("Ꞁ"),
       QString("𝔏"),
       QString("𝕷"),
       QString("𝕃"),
       QString("𝐋"),
       QString("𝐿"),
       QString("𝑳"),
       QString("ℒ"),
       QString("𝓛"),
       QString("𝖫"),
       QString("𝗟"),
       QString("𝘓"),
       QString("𝙇"),
       QString("𝙻")},
    [(int)'M']
    = {QString("M"),
       QString("Ɯ"),
       QString("𝔐"),
       QString("𝕸"),
       QString("𝕄"),
       QString("𝐌"),
       QString("𝑀"),
       QString("𝑴"),
       QString("ℳ"),
       QString("𝓜"),
       QString("𝖬"),
       QString("𝗠"),
       QString("𝘔"),
       QString("𝙈"),
       QString("𝙼")},
    [(int)'N']
    = {QString("N"),
       QString("N"),
       QString("𝔑"),
       QString("𝕹"),
       QString("ℕ"),
       QString("𝐍"),
       QString("𝑁"),
       QString("𝑵"),
       QString("𝒩"),
       QString("𝓝"),
       QString("𝖭"),
       QString("𝗡"),
       QString("𝘕"),
       QString("𝙉"),
       QString("𝙽")},
    [(int)'O']
    = {QString("O"),
       QString("O"),
       QString("𝔒"),
       QString("𝕺"),
       QString("𝕆"),
       QString("𝐎"),
       QString("𝑂"),
       QString("𝑶"),
       QString("𝒪"),
       QString("𝓞"),
       QString("𝖮"),
       QString("𝗢"),
       QString("𝘖"),
       QString("𝙊"),
       QString("𝙾")},
    [(int)'P']
    = {QString("P"),
       QString("Ԁ"),
       QString("𝔓"),
       QString("𝕻"),
       QString("ℙ"),
       QString("𝐏"),
       QString("𝑃"),
       QString("𝑷"),
       QString("𝒫"),
       QString("𝓟"),
       QString("𝖯"),
       QString("𝗣"),
       QString("𝘗"),
       QString("𝙋"),
       QString("𝙿")},
    [(int)'Q']
    = {QString("Q"),
       QString("Ò"),
       QString("𝔔"),
       QString("𝕼"),
       QString("ℚ"),
       QString("𝐐"),
       QString("𝑄"),
       QString("𝑸"),
       QString("𝒬"),
       QString("𝓠"),
       QString("𝖰"),
       QString("𝗤"),
       QString("𝘘"),
       QString("𝙌"),
       QString("𝚀")},
    [(int)'R']
    = {QString("R"),
       QString("ᴚ"),
       QString("ℜ"),
       QString("𝕽"),
       QString("ℝ"),
       QString("𝐑"),
       QString("𝑅"),
       QString("𝑹"),
       QString("ℛ"),
       QString("𝓡"),
       QString("𝖱"),
       QString("𝗥"),
       QString("𝘙"),
       QString("𝙍"),
       QString("𝚁")},
    [(int)'S']
    = {QString("S"),
       QString("S"),
       QString("𝔖"),
       QString("𝕾"),
       QString("𝕊"),
       QString("𝐒"),
       QString("𝑆"),
       QString("𝑺"),
       QString("𝒮"),
       QString("𝓢"),
       QString("𝖲"),
       QString("𝗦"),
       QString("𝘚"),
       QString("𝙎"),
       QString("𝚂")},
    [(int)'T']
    = {QString("T"),
       QString("Ʇ"),
       QString("𝔗"),
       QString("𝕿"),
       QString("𝕋"),
       QString("𝐓"),
       QString("𝑇"),
       QString("𝑻"),
       QString("𝒯"),
       QString("𝓣"),
       QString("𝖳"),
       QString("𝗧"),
       QString("𝘛"),
       QString("𝙏"),
       QString("𝚃")},
    [(int)'U']
    = {QString("U"),
       QString("∩"),
       QString("𝔘"),
       QString("𝖀"),
       QString("𝕌"),
       QString("𝐔"),
       QString("𝑈"),
       QString("𝑼"),
       QString("𝒰"),
       QString("𝓤"),
       QString("𝖴"),
       QString("𝗨"),
       QString("𝘜"),
       QString("𝙐"),
       QString("𝚄")},
    [(int)'V']
    = {QString("V"),
       QString("Ʌ"),
       QString("𝔙"),
       QString("𝖁"),
       QString("𝕍"),
       QString("𝐕"),
       QString("𝑉"),
       QString("𝑽"),
       QString("𝒱"),
       QString("𝓥"),
       QString("𝖵"),
       QString("𝗩"),
       QString("𝘝"),
       QString("𝙑"),
       QString("𝚅")},
    [(int)'W']
    = {QString("W"),
       QString("ʍ"),
       QString("𝔚"),
       QString("𝖂"),
       QString("𝕎"),
       QString("𝐖"),
       QString("𝑊"),
       QString("𝑾"),
       QString("𝒲"),
       QString("𝓦"),
       QString("𝖶"),
       QString("𝗪"),
       QString("𝘞"),
       QString("𝙒"),
       QString("𝚆")},
    [(int)'X']
    = {QString("X"),
       QString("X"),
       QString("𝔛"),
       QString("𝖃"),
       QString("𝕏"),
       QString("𝐗"),
       QString("𝑋"),
       QString("𝑿"),
       QString("𝒳"),
       QString("𝓧"),
       QString("𝖷"),
       QString("𝗫"),
       QString("𝘟"),
       QString("𝙓"),
       QString("𝚇")},
    [(int)'Y']
    = {QString("Y"),
       QString("⅄"),
       QString("𝔜"),
       QString("𝖄"),
       QString("𝕐"),
       QString("𝐘"),
       QString("𝑌"),
       QString("𝒀"),
       QString("𝒴"),
       QString("𝓨"),
       QString("𝖸"),
       QString("𝗬"),
       QString("𝘠"),
       QString("𝙔"),
       QString("𝚈")},
    [(int)'Z']
    = {QString("Z"),
       QString("Z"),
       QString("ℨ"),
       QString("𝖅"),
       QString("ℤ"),
       QString("𝐙"),
       QString("𝑍"),
       QString("𝒁"),
       QString("𝒵"),
       QString("𝓩"),
       QString("𝖹"),
       QString("𝗭"),
       QString("𝘡"),
       QString("𝙕"),
       QString("𝚉")},
    [(int)'a']
    = {QString("a"),
       QString("ɐ"),
       QString("𝔞"),
       QString("𝖆"),
       QString("𝕒"),
       QString("𝐚"),
       QString("𝑎"),
       QString("𝒂"),
       QString("𝒶"),
       QString("𝓪"),
       QString("𝖺"),
       QString("𝗮"),
       QString("𝘢"),
       QString("𝙖"),
       QString("𝚊")},
    [(int)'b']
    = {QString("b"),
       QString("q"),
       QString("𝔟"),
       QString("𝖇"),
       QString("𝕓"),
       QString("𝐛"),
       QString("𝑏"),
       QString("𝒃"),
       QString("𝒷"),
       QString("𝓫"),
       QString("𝖻"),
       QString("𝗯"),
       QString("𝘣"),
       QString("𝙗"),
       QString("𝚋")},
    [(int)'c']
    = {QString("c"),
       QString("ɔ"),
       QString("𝔠"),
       QString("𝖈"),
       QString("𝕔"),
       QString("𝐜"),
       QString("𝑐"),
       QString("𝒄"),
       QString("𝒸"),
       QString("𝓬"),
       QString("𝖼"),
       QString("𝗰"),
       QString("𝘤"),
       QString("𝙘"),
       QString("𝚌")},
    [(int)'d']
    = {QString("d"),
       QString("p"),
       QString("𝔡"),
       QString("𝖉"),
       QString("𝕕"),
       QString("𝐝"),
       QString("𝑑"),
       QString("𝒅"),
       QString("𝒹"),
       QString("𝓭"),
       QString("𝖽"),
       QString("𝗱"),
       QString("𝘥"),
       QString("𝙙"),
       QString("𝚍")},
    [(int)'e']
    = {QString("e"),
       QString("ǝ"),
       QString("𝔢"),
       QString("𝖊"),
       QString("𝕖"),
       QString("𝐞"),
       QString("𝑒"),
       QString("𝒆"),
       QString("ℯ"),
       QString("𝓮"),
       QString("𝖾"),
       QString("𝗲"),
       QString("𝘦"),
       QString("𝙚"),
       QString("𝚎")},
    [(int)'f']
    = {QString("f"),
       QString("ɟ"),
       QString("𝔣"),
       QString("𝖋"),
       QString("𝕗"),
       QString("𝐟"),
       QString("𝑓"),
       QString("𝒇"),
       QString("𝒻"),
       QString("𝓯"),
       QString("𝖿"),
       QString("𝗳"),
       QString("𝘧"),
       QString("𝙛"),
       QString("𝚏")},
    [(int)'g']
    = {QString("g"),
       QString("ᵷ"),
       QString("𝔤"),
       QString("𝖌"),
       QString("𝕘"),
       QString("𝐠"),
       QString("𝑔"),
       QString("𝒈"),
       QString("ℊ"),
       QString("𝓰"),
       QString("𝗀"),
       QString("𝗴"),
       QString("𝘨"),
       QString("𝙜"),
       QString("𝚐")},
    [(int)'h']
    = {QString("h"),
       QString("ɥ"),
       QString("𝔥"),
       QString("𝖍"),
       QString("𝕙"),
       QString("𝐡"),
       QString("ℎ"),
       QString("𝒉"),
       QString("𝒽"),
       QString("𝓱"),
       QString("𝗁"),
       QString("𝗵"),
       QString("𝘩"),
       QString("𝙝"),
       QString("𝚑")},
    [(int)'i']
    = {QString("i"),
       QString("ᴉ"),
       QString("𝔦"),
       QString("𝖎"),
       QString("𝕚"),
       QString("𝐢"),
       QString("𝑖"),
       QString("𝒊"),
       QString("𝒾"),
       QString("𝓲"),
       QString("𝗂"),
       QString("𝗶"),
       QString("𝘪"),
       QString("𝙞"),
       QString("𝚒")},
    [(int)'j']
    = {QString("j"),
       QString("f"),
       QString("𝔧"),
       QString("𝖏"),
       QString("𝕛"),
       QString("𝐣"),
       QString("𝑗"),
       QString("𝒋"),
       QString("𝒿"),
       QString("𝓳"),
       QString("𝗃"),
       QString("𝗷"),
       QString("𝘫"),
       QString("𝙟"),
       QString("𝚓")},
    [(int)'k']
    = {QString("k"),
       QString("ʞ"),
       QString("𝔨"),
       QString("𝖐"),
       QString("𝕜"),
       QString("𝐤"),
       QString("𝑘"),
       QString("𝒌"),
       QString("𝓀"),
       QString("𝓴"),
       QString("𝗄"),
       QString("𝗸"),
       QString("𝘬"),
       QString("𝙠"),
       QString("𝚔")},
    [(int)'l']
    = {QString("l"),
       QString("ꞁ"),
       QString("𝔩"),
       QString("𝖑"),
       QString("𝕝"),
       QString("𝐥"),
       QString("𝑙"),
       QString("𝒍"),
       QString("𝓁"),
       QString("𝓵"),
       QString("𝗅"),
       QString("𝗹"),
       QString("𝘭"),
       QString("𝙡"),
       QString("𝚕")},
    [(int)'m']
    = {QString("m"),
       QString("ɯ"),
       QString("𝔪"),
       QString("𝖒"),
       QString("𝕞"),
       QString("𝐦"),
       QString("𝑚"),
       QString("𝒎"),
       QString("𝓂"),
       QString("𝓶"),
       QString("𝗆"),
       QString("𝗺"),
       QString("𝘮"),
       QString("𝙢"),
       QString("𝚖")},
    [(int)'n']
    = {QString("n"),
       QString("u"),
       QString("𝔫"),
       QString("𝖓"),
       QString("𝕟"),
       QString("𝐧"),
       QString("𝑛"),
       QString("𝒏"),
       QString("𝓃"),
       QString("𝓷"),
       QString("𝗇"),
       QString("𝗻"),
       QString("𝘯"),
       QString("𝙣"),
       QString("𝚗")},
    [(int)'o']
    = {QString("o"),
       QString("o"),
       QString("𝔬"),
       QString("𝖔"),
       QString("𝕠"),
       QString("𝐨"),
       QString("𝑜"),
       QString("𝒐"),
       QString("ℴ"),
       QString("𝓸"),
       QString("𝗈"),
       QString("𝗼"),
       QString("𝘰"),
       QString("𝙤"),
       QString("𝚘")},
    [(int)'p']
    = {QString("p"),
       QString("d"),
       QString("𝔭"),
       QString("𝖕"),
       QString("𝕡"),
       QString("𝐩"),
       QString("𝑝"),
       QString("𝒑"),
       QString("𝓅"),
       QString("𝓹"),
       QString("𝗉"),
       QString("𝗽"),
       QString("𝘱"),
       QString("𝙥"),
       QString("𝚙")},
    [(int)'q']
    = {QString("q"),
       QString("b"),
       QString("𝔮"),
       QString("𝖖"),
       QString("𝕢"),
       QString("𝐪"),
       QString("𝑞"),
       QString("𝒒"),
       QString("𝓆"),
       QString("𝓺"),
       QString("𝗊"),
       QString("𝗾"),
       QString("𝘲"),
       QString("𝙦"),
       QString("𝚚")},
    [(int)'r']
    = {QString("r"),
       QString("ɹ"),
       QString("𝔯"),
       QString("𝖗"),
       QString("𝕣"),
       QString("𝐫"),
       QString("𝑟"),
       QString("𝒓"),
       QString("𝓇"),
       QString("𝓻"),
       QString("𝗋"),
       QString("𝗿"),
       QString("𝘳"),
       QString("𝙧"),
       QString("𝚛")},
    [(int)'s']
    = {QString("s"),
       QString("s"),
       QString("𝔰"),
       QString("𝖘"),
       QString("𝕤"),
       QString("𝐬"),
       QString("𝑠"),
       QString("𝒔"),
       QString("𝓈"),
       QString("𝓼"),
       QString("𝗌"),
       QString("𝘀"),
       QString("𝘴"),
       QString("𝙨"),
       QString("𝚜")},
    [(int)'t']
    = {QString("t"),
       QString("ʇ"),
       QString("𝔱"),
       QString("𝖙"),
       QString("𝕥"),
       QString("𝐭"),
       QString("𝑡"),
       QString("𝒕"),
       QString("𝓉"),
       QString("𝓽"),
       QString("𝗍"),
       QString("𝘁"),
       QString("𝘵"),
       QString("𝙩"),
       QString("𝚝")},
    [(int)'u']
    = {QString("u"),
       QString("n"),
       QString("𝔲"),
       QString("𝖚"),
       QString("𝕦"),
       QString("𝐮"),
       QString("𝑢"),
       QString("𝒖"),
       QString("𝓊"),
       QString("𝓾"),
       QString("𝗎"),
       QString("𝘂"),
       QString("𝘶"),
       QString("𝙪"),
       QString("𝚞")},
    [(int)'v']
    = {QString("v"),
       QString("ʌ"),
       QString("𝔳"),
       QString("𝖛"),
       QString("𝕧"),
       QString("𝐯"),
       QString("𝑣"),
       QString("𝒗"),
       QString("𝓋"),
       QString("𝓿"),
       QString("𝗏"),
       QString("𝘃"),
       QString("𝘷"),
       QString("𝙫"),
       QString("𝚟")},
    [(int)'w']
    = {QString("w"),
       QString("ʍ"),
       QString("𝔴"),
       QString("𝖜"),
       QString("𝕨"),
       QString("𝐰"),
       QString("𝑤"),
       QString("𝒘"),
       QString("𝓌"),
       QString("𝔀"),
       QString("𝗐"),
       QString("𝘄"),
       QString("𝘸"),
       QString("𝙬"),
       QString("𝚠")},
    [(int)'x']
    = {QString("x"),
       QString("x"),
       QString("𝔵"),
       QString("𝖝"),
       QString("𝕩"),
       QString("𝐱"),
       QString("𝑥"),
       QString("𝒙"),
       QString("𝓍"),
       QString("𝔁"),
       QString("𝗑"),
       QString("𝘅"),
       QString("𝘹"),
       QString("𝙭"),
       QString("𝚡")},
    [(int)'y']
    = {QString("y"),
       QString("ʎ"),
       QString("𝔶"),
       QString("𝖞"),
       QString("𝕪"),
       QString("𝐲"),
       QString("𝑦"),
       QString("𝒚"),
       QString("𝓎"),
       QString("𝔂"),
       QString("𝗒"),
       QString("𝘆"),
       QString("𝘺"),
       QString("𝙮"),
       QString("𝚢")},
    [(int)'z']
    = {QString("z"),
       QString("z"),
       QString("𝔷"),
       QString("𝖟"),
       QString("𝕫"),
       QString("𝐳"),
       QString("𝑧"),
       QString("𝒛"),
       QString("𝓏"),
       QString("𝔃"),
       QString("𝗓"),
       QString("𝘇"),
       QString("𝘻"),
       QString("𝙯"),
       QString("𝚣")},
    [(int)'0']
    = {QString("0"),
       QString("0"),
       QString("0"),
       QString("0"),
       QString("𝟘"),
       QString("𝟎"),
       QString("0"),
       QString("0"),
       QString("0"),
       QString("0"),
       QString("0"),
       QString("𝟢"),
       QString("𝟬"),
       QString("0"),
       QString("𝟶")},
    [(int)'1']
    = {QString("1"),
       QString("1"),
       QString("1"),
       QString("1"),
       QString("𝟙"),
       QString("𝟏"),
       QString("1"),
       QString("1"),
       QString("1"),
       QString("1"),
       QString("1"),
       QString("𝟣"),
       QString("𝟭"),
       QString("1"),
       QString("𝟷")},
    [(int)'2']
    = {QString("2"),
       QString("2"),
       QString("2"),
       QString("2"),
       QString("𝟚"),
       QString("𝟐"),
       QString("2"),
       QString("2"),
       QString("2"),
       QString("2"),
       QString("2"),
       QString("𝟤"),
       QString("𝟮"),
       QString("2"),
       QString("𝟸")},
    [(int)'3']
    = {QString("3"),
       QString("3"),
       QString("3"),
       QString("3"),
       QString("𝟛"),
       QString("𝟑"),
       QString("3"),
       QString("3"),
       QString("3"),
       QString("3"),
       QString("3"),
       QString("𝟥"),
       QString("𝟯"),
       QString("3"),
       QString("𝟹")},
    [(int)'4']
    = {QString("4"),
       QString("4"),
       QString("4"),
       QString("4"),
       QString("𝟜"),
       QString("𝟒"),
       QString("4"),
       QString("4"),
       QString("4"),
       QString("4"),
       QString("4"),
       QString("𝟦"),
       QString("𝟰"),
       QString("4"),
       QString("𝟺")},
    [(int)'5']
    = {QString("5"),
       QString("5"),
       QString("5"),
       QString("5"),
       QString("𝟝"),
       QString("𝟓"),
       QString("5"),
       QString("5"),
       QString("5"),
       QString("5"),
       QString("5"),
       QString("𝟧"),
       QString("𝟱"),
       QString("5"),
       QString("𝟻")},
    [(int)'6']
    = {QString("6"),
       QString("6"),
       QString("6"),
       QString("6"),
       QString("𝟞"),
       QString("𝟔"),
       QString("6"),
       QString("6"),
       QString("6"),
       QString("6"),
       QString("6"),
       QString("𝟨"),
       QString("𝟲"),
       QString("6"),
       QString("𝟼")},
    [(int)'7']
    = {QString("7"),
       QString("7"),
       QString("7"),
       QString("7"),
       QString("𝟟"),
       QString("𝟕"),
       QString("7"),
       QString("7"),
       QString("7"),
       QString("7"),
       QString("7"),
       QString("𝟩"),
       QString("𝟳"),
       QString("7"),
       QString("𝟽")},
    [(int)'8']
    = {QString("8"),
       QString("8"),
       QString("8"),
       QString("8"),
       QString("𝟠"),
       QString("𝟖"),
       QString("8"),
       QString("8"),
       QString("8"),
       QString("8"),
       QString("8"),
       QString("𝟪"),
       QString("𝟴"),
       QString("8"),
       QString("𝟾")},
    [(int)'9']
    = {QString("9"),
       QString("9"),
       QString("9"),
       QString("9"),
       QString("𝟡"),
       QString("𝟗"),
       QString("9"),
       QString("9"),
       QString("9"),
       QString("9"),
       QString("9"),
       QString("𝟫"),
       QString("𝟵"),
       QString("9"),
       QString("𝟿")},
};


QString styledUnicodeMapping(QChar ch, AsciiStyle style) {
    char latin = ch.toLatin1();
    if (unicodeCharMappings[(int)latin][(int)style] != QString("\0")) {
        return unicodeCharMappings[(int)latin][(int)style];
    } else {
        return ch;
    }
}

QString styledUnicodeMapping(QString const& str, AsciiStyle style) {
    QString result;
    result.reserve(str.size());
    for (const auto& ch : str) {
        result += styledUnicodeMapping(ch, style);
    }
    return result;
}

Str strip(CR<Str> string, CR<CharSet> leading, CR<CharSet> trailing) {
    if (0 < string.size()) {
        Span<QChar> view = string.toSpan();
        Q_CHECK_PTR(view.data());
        QChar* end = view.data() + string.size();

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

Vec<Str> split(CR<Str> str, QChar ch) {
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

Vec<Str> visibleUnicodeName(QString str) {
    Vec<Str> result;
    for (QChar ch : str) {
        if (ch.unicode() <= 127) {
            result.push_back(visibleName(ch).first);
        } else {
            result.push_back(ch);
        }
    }

    return result;
}

Pair<QChar, QString> visibleName(QChar ch) {
    switch (ch.unicode()) {
        case '\x00': return {QChar(L'␀'), "[NUL]"}; // Null character
        case '\x01': return {QChar(L'␁'), "[SOH]"}; // Start of header
        case '\x02': return {QChar(L'␂'), "[STX]"}; // Start of text
        case '\x03': return {QChar(L'␃'), "[ETX]"}; // End of text
        case '\x04': return {QChar(L'␄'), "[EOT]"}; // End transmission
        case '\x05': return {QChar(L'␅'), "[ENQ]"}; // Enquiry
        case '\x06': return {QChar(L'␆'), "[ACK]"}; // Acknowledge
        case '\x07': return {QChar(L'␇'), "[BEL]"}; // Bell
        case '\x08': return {QChar(L'␈'), "[BS]"};  // Backspace
        case '\x09': return {QChar(L'␉'), "[HT]"};  // Horizontal tab
        case '\x0A': return {QChar(L'␤'), "[LF]"};  // Line feed
        case '\x0B': return {QChar(L'␋'), "[VT]"};  // Vertical tab
        case '\x0C': return {QChar(L'␌'), "[FF]"};  // Form feed
        case '\x0D': return {QChar(L'␍'), "[CR]"};  // Carriage return
        case '\x0E': return {QChar(L'␎'), "[SO]"};  // Shift out
        case '\x0F': return {QChar(L'␏'), "[SI]"};  // Shift in
        case '\x10': return {QChar(L'␐'), "[DLE]"}; // Data link escape
        case '\x11': return {QChar(L'␑'), "[DC1]"}; // Device control 1
        case '\x12': return {QChar(L'␒'), "[DC2]"}; // Device control 2
        case '\x13': return {QChar(L'␓'), "[DC3]"}; // Device control 3
        case '\x14': return {QChar(L'␔'), "[DC4]"}; // Device control 4
        case '\x15': return {QChar(L'␕'), "[NAK]"}; // Negative ack
        case '\x16': return {QChar(L'␖'), "[SYN]"}; // Synchronous idle
        case '\x17': return {QChar(L'␗'), "[ETB]"}; // End tr. block
        case '\x18': return {QChar(L'␘'), "[CAN]"}; // Cancel
        case '\x19': return {QChar(L'␙'), "[EM]"};  // End of medium
        case '\x1A': return {QChar(L'␚'), "[SUB]"}; // Substitute
        case '\x1B': return {QChar(L'␛'), "[ESC]"}; // Escape
        case '\x1C': return {QChar(L'␜'), "[FS]"};  // File separator
        case '\x1D': return {QChar(L'␝'), "[GS]"};  // Group separator
        case '\x1E': return {QChar(L'␞'), "[RS]"};  // Record separator
        case '\x1F': return {QChar(L'␟'), "[US]"};  // Unit separator
        case '\x7f': return {QChar(L'␡'), "[DEL]"}; // Delete
        case ' ': return {QChar(L'␣'), "[SPC]"};    // Space
        default: return {QChar(ch), QString(ch)};
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
    for (QChar c : in) {
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

QString left_aligned(CR<QString> str, int n, QChar c) {
    auto s = str;
    if (s.size() < n) {
        s.append(QString(c).repeated(n - s.size()));
    }
    return s;
}

QString right_aligned(CR<QString> str, int n, QChar c) {
    QString res;
    if (str.size() < n) {
        res.append(QString(c).repeated(n - str.size()));
    }
    res.append(str);
    return res;
}

QString escape_for_write(const QString& str, bool quote) {
    QString res;
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
