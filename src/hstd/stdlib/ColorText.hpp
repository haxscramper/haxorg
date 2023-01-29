std::string operator $(const TermColorFg& fg) {
    std::string result;
    /*!Convert foreground color to human-readble representation
     */
    ;
    result = toStr(fg.uint8);
    ;
    if (((fg.uint8) < (15))) {
        result.add(
            ((R"(($1))")
             % (toStr(ForegroundColor(
                 ((low(ForegroundColor).uint8) + (fg.uint8)))))));
    };
    return result;
};

std::string operator $(const TermColorBg& bg) {
    std::string result;
    /*!Convert background color to human-readable representation
     */
    ;
    result = toStr(bg.uint8);
    ;
    if (((bg.uint8) < (15))) {
        result.add(
            ((R"(($1))")
             % (toStr(BackgroundColor(
                 ((low(BackgroundColor).uint8) + (bg.uint8)))))));
    };
    return result;
};

bool operator==(
    const((TermColorBg) | (TermColorFg))
        & a const((TermColorBg) | (TermColorFg)) & b, ) {
    bool result;
    /*!Color equality comparison
     */
    ;
    ((a.uint8) == (b.uint8));
    return result;
};

/* TYPE DEF ColStyle* = object
  fg*: TermColorFg           ## Styling options
  ## Foreground color
  bg*: TermColorBg           ## Background
  style*: set[Style]         ## Other styling options (italic, underline, dim,
                             ## bright etc.)
   */
struct ColStyle {
    TermColorFg fg;   /*!Foreground color
                       */
    TermColorBg bg;   /*!Background
                       */
    set<Style> style; /*!Other styling options (italic, underline, dim,
bright etc.)
*/
};
;
/* TYPE DEF ColRune* = object
  rune*: Rune                ## Single unicode rune with applied coloring
  style*: ColStyle
 */
struct ColRune {
    Rune     rune;
    ColStyle style;
};
;
/* TYPE DEF ColText* = object
  runes*: seq[ColRune]       ## Sequence of colored unicode runes
   */
struct ColText {
    Vec<ColRune> runes;
};
;
/* TYPE DEF ColRuneLine* = seq[ColRune] */ using ColRuneLine = Vec<
    ColRune>;
;
/* TYPE DEF ColRuneGrid* = seq[ColRuneLine] */ using ColRuneGrid = Vec<
    ColRuneLine>;
;
/* TYPE DEF ColModifier* = ForegroundColor | BackgroundColor | TermColorFg
   | TermColorBg | set[Style] | Style | ColStyle */
/* FIXME INFIX ColModifier* = ForegroundColor | BackgroundColor |
TermColorFg | TermColorBg | set[Style] | Style | ColStyle */
;
;

int len(const ColText& text) {
    int result;
    /*!Number of *runes* in text
     */
    ;
    text.runes.len;
    return result;
};

void add(ColText& text, const((ColRune) | (seq[ColRune])) & rune) {
    /*!Append one or more colored runes to the text
     */
    ;
    text.runes.add(rune);
};

Vec<ColRune> items(const ColText& text) {
    Vec<ColRune> result{};
    /*!Iterate over all runes left to right
     */
    ;
    for (const auto item : text.runes) {
        result.push_back(item);
    };
    return result;
};

Vec<ColRune> ritems(const ColText& text) {
    Vec<ColRune> result{};
    /*!Iterate over all runes right to left
     */
    ;

    auto idx = text.runes.high;
    ;
    ;
    while (((0) <= (idx))) {
        result.push_back(text.runes[idx]);
        -= idx;
    };
    return result;
};

bool operator==(const ColStyle& s1 const ColStyle& s2, ) {
    bool result;
    /*!Compare styles for equality - foreground, background and style
     */
    ;
    ((((((s1.fg) == (s2.fg))) && (((s1.bg) == (s2.bg)))))
     && (((s1.style) == (s2.style))));
    return result;
};

bool contains(const ColStyle& ps, const Style& s) {
    bool result;
    /*!Check if coloring contains specific style option
     */
    ;
    ps.style.contains(s);
    return result;
};

TermColorBg termColor(const BackgroundColor& bg) {
    TermColorBg result;
    /*!Convert `std/terminal.BackgroundColor` to terminal background color
     */
    ;
    if (((bg) != (bgDefault))) {
        result = TermColorBg(((bg.uint8) - (low(BackgroundColor).uint8)));
        ;
    };
    return result;
};

TermColorFg termColor(const ForegroundColor& bg) {
    TermColorFg result;
    /*!Convert `std/terminal.ForegroundColor` to terminal foreground color
     */
    ;
    if (((bg) != (fgDefault))) {
        result = TermColorFg(((bg.uint8) - (low(ForegroundColor).uint8)));
        ;
    };
    return result;
};

bool operator==(const TermColorFg& f1, const ForegroundColor& f2) {
    bool result;
    /*!Compare for equality with `std/terminal` color
     */
    ;
    ((termColor(f2)) == (f1));
    return result;
};

bool operator==(const TermColorBg& f1, const BackgroundColor& f2) {
    bool result;
    /*!Compare for equality with `std/terminal` color
     */
    ;
    ((termColor(f2)) == (f1));
    return result;
};

ColStyle initColStyle(
    const ForegroundColor& fg    = fgDefault,
    const BackgroundColor& bg    = bgDefault,
    const set<Style>&      style = {}) {
    ColStyle result;
    /*!Initialize color style with given options
     */
    ;
    ColStyle{
        .fg    = fg.termColor,
        .bg    = bg.termColor,
        .style = style,
    };
    return result;
};

ColStyle colStyle(const ForegroundColor& fg) {
    ColStyle result;
    /*!Convert to style with only foreground option set
     */
    ;
    ColStyle{
        .fg = fg.termColor,
    };
    return result;
};

ColStyle colStyle(const BackgroundColor& bg) {
    ColStyle result;
    /*!Convert to style with only background option set
     */
    ;
    ColStyle{
        .bg = bg.termColor,
    };
    return result;
};

ColStyle colStyle(const TermColorFg& fg) {
    ColStyle result;
    /*!Convert to style with only foreground color set
     */
    ;
    ColStyle{
        .fg = fg,
    };
    return result;
};

ColStyle colStyle(const TermColorBg& bg) {
    ColStyle result;
    /*!Convert to style with only background color set
     */
    ;
    ColStyle{
        .bg = bg,
    };
    return result;
};

ColStyle colStyle(const set<Style>& style) {
    ColStyle result;
    /*!Convert to style with given set of styling options
     */
    ;
    ColStyle{
        .style = style,
    };
    return result;
};

ColStyle colStyle(const Style& style) {
    ColStyle result;
    /*!Convert to style with single styling option set
     */
    ;
    ColStyle{
        .style = {style},
    };
    return result;
};

ColStyle colStyle(const ColStyle& style) {
    ColStyle result;
    /*!Passthrough proc, used to simplify mapping of the `ColModifier`
    typeclass to the `ColStyle` object.
    */
    ;
    style;
    return result;
};

ColRune default(const typedesc<ColRune>& rune) {
    ColRune result;
    /*!Default value of the colored rune
     */
    ;
    ColRune{
        .style = initColStyle(),
    };
    return result;
};

ColStyle default(const typedesc<ColStyle>& style) {
    ColStyle result;
    /*!Default value of the color style
     */
    ;
    ColStyle{
        .fg = fgDefault.termColor(),
        .bg = bgDefault.termColor(),
    };
    return result;
};

Rune uc(const static<Str>& s) {
    Rune result;
    /*!Create single unicode rune from std::string literal - `uc"⮰"`
     */
    ;
    runeAt(s, 0);
    return result;
};

bool isDefault(const((TermColorFg) | (TermColorBg)) & col) {
    bool result;
    /*!Check if foreground or background color have default value
     */
    ;
    ((col.uint8) == (0));
    return result;
};

void operator+=(ColStyle& s1, const ColStyle& s2) {
    /*!Merge two styling optons, overriding target if the source has
    non-default value for background or foreground colors
    */
    ;
    s1.style = ((s1.style) + (s2.style));
    ;
    s1.fg = else { s2.fg.isDefault() }
    else {
        s2.fg;
    };
    ;
    s1.bg = else { s2.bg.isDefault() }
    else {
        s2.bg;
    };
    ;
};

ColStyle operator+(const ColStyle& s1 const ColStyle& s2, ) {
    ColStyle result;
    /*!Merge two styles. Second one overrides colors if they are
     * non-default.
     */
    ;
    result = s1;
    ;
    ((result) += (s2));
    return result;
};

ColStyle operator+(
    const ColModifier&                a,
    const /* distinct */ ColModifier& b) {
    ColStyle result;
    /*!Merge two color modifiers and generate color style
    (`fgRed+{styleUnderline}`)
    */
    ;
    ((colStyle(a)) + (colStyle(b)));
    return result;
};

ColRune toColRune(const Rune& rune, const ColStyle& style) {
    ColRune result;
    /*!Convert colered rune to styled one with `style`
     */
    ;
    ColRune{
        .rune  = rune,
        .style = style,
    };
    return result;
};

ColText toColText(
    const Str&      text,
    const ColStyle& style = default(ColStyle)) {
    ColText result;
    /*!Convert text colored one using given style
     */
    ;
    for (const auto rune : runes(text)) {
        result.add(toColRune(rune, style));
    };
    return result;
};

ColText operator+(const Str& text, const ColModifier& style) {
    ColText result;
    /*!Convert text colored one using given style
     */
    ;
    toColText(text, colStyle(style));
    return result;
};

ColRune operator+(const char& ch, const ColModifier& style) {
    ColRune result;
    /*!Convert character to colored rune with given style
     */
    ;
    toColRune(Rune(ch), colStyle(style));
    return result;
};

ColRune operator+(const Rune& r, const ColModifier& style) {
    ColRune result;
    /*!Convert rune to colored one with given style modifier
     */
    ;
    toColRune(r, colStyle(style));
    return result;
};

void setStyle(
    ColText& text,
    const ColStyle& new,
    const bool& override = true) {
    /*!Set style for all runes in text, optionally overriding non-defaulted
    values (or resetting them completely)
    */
    ;
    for (const auto ch : mitems(text.runes)) {
        if (override) {
            ch.style.fg = new.fg;
            ;
            ch.style.bg = new.bg;
            ;
            ch.style.style = new.style;
            ;
        } else {
            if (isDefault(ch.style.fg)) {
                ch.style.fg = new.fg;
                ;
            };
            if (isDefault(ch.style.bg)) {
                ch.style.bg = new.bg;
                ;
            };
            for (const auto s : new.style) {
                ch.style.style.incl(s);
            };
        };
    };
};

ColText operator+(const ColText& text, const ColModifier& style) {
    ColText result;
    /*!Apply styling options to colored text
     */
    ;
    result = text;
    ;
    result.setStyle(colStyle(style), false);
    return result;
};

ColText toColText(const ColText& text) {
    ColText result;
    /*!Passthrough implementation of converter to colored text
     */
    ;
    text;
    return result;
};

ColText toColText(const ColRune& rune) {
    ColText result;
    /*!Convert single rune to colored text
     */
    ;
    ColText { .runes = (@({rune})), };
    return result;
};

ColText clt(const Str& str) {
    ColText result;
    /*!Shorthand to construct colored text std::string with default value
    (`clt"default"`)
    */
    ;
    ((str) + (default(ColStyle)));
    return result;
};

ColText clt(const char& ch) {
    ColText result;
    /*!Shorthand to construct colored text with single character
     */
    ;
    toColText(((ch) + (default(ColStyle))));
    return result;
};

ColRune clr(const char& ch) {
    ColRune result;
    /*!Construct colored rune with default styling
     */
    ;
    ((ch) + (default(ColStyle)));
    return result;
};

bool isNewline(const ColRune& rune) {
    bool result;
    /*!Check if rune is a newline rune
     */
    ;
    ((rune.rune) == (Rune(int('\n'))));
    return result;
};

ColText toLower(const ColText& text) {
    ColText result;
    /*!Convert colored text to lowercase
     */
    ;
    result = text;
    ;
    for (const auto rune : mitems(result.runes)) {
        rune.rune = toLower(rune.rune);
        ;
    };
    return result;
};

ColText toUpper(const ColText& text) {
    ColText result;
    /*!Convert colored text to uppercase
     */
    ;
    result = text;
    ;
    for (const auto rune : mitems(result.runes)) {
        rune.rune = toUpper(rune.rune);
        ;
    };
    return result;
};

ColText alignLeft(
    const ColText& text,
    const int&     length,
    const ColRune& padding = clr(' ')) {
    ColText result;
    /*!Align colored text left, using padding rune to fill in missing
    elements
    */
    ;
    result = text;
    ;
    if (((result.len) < (length))) {
        result.runes.add(padding.repeat(((length) - (result.len))));
    };
    return result;
};

ColText alignCenter(
    const ColText& text,
    const int&     length,
    const ColRune& padding = clr(' ')) {
    ColText result;
    /*!Center colored text, using padding rune to fill in missing elements
     */
    ;
    if (((result.len) < (length))) {

        const auto diff = ((length) - (text.len));
        ;
        const auto left = ((diff)div(2));
        ;
        const auto right = ((diff) - (left));
        ;
        ;
        result.runes.add(padding.repeat(left));
        result.add(text.runes);
        result.runes.add(padding.repeat(right));
    };
    return result;
};

ColText alignRight(
    const ColText& text,
    const int&     length,
    const ColRune& padding = clr(' ')) {
    ColText result;
    /*!Align colored text right, using padding rune to fill in missing
    elements
    */
    ;
    if (((text.len) < (length))) {
        result.runes.add(padding.repeat(((length) - (text.len))));
    };
    result.runes.add(text.runes);
    return result;
};

ColText operator| <<(const ColText& s, const int& l) {
    ColText result;
    /*!Shorthand for left align of the colored text. Since library is
    mostly used for final message formatting it is a very common operation
    and it was implemented as an operator as well.
    */
    ;
    alignLeft(s, l);
    return result;
};

ColText operator|>>(const ColText& s, const int& l) {
    ColText result;
    /*!Shorthand of the right align of the colored text.
     */
    ;
    alignRight(s, l);
    return result;
};

bool operator==(const ColRune& rune, const char& ch) {
    bool result;
    /*!Compare rune for equality with regular character
     */
    ;
    ((rune.rune) == (Rune(int(ch))));
    return result;
};

bool hasNewline(const ColText& text) {
    bool result;
    /*!Check if colored text has any newlines
     */
    ;
    for (const auto rune : text.runes) {
        if (isNewline(rune)) {
            return true;
            ;
        };
    };
    return result;
};

bool hasOnlyTailNewline(const ColText& text) {
    bool result;
    /*!Check if colored text has only trailing newlines and no in-body ones
     */
    ;

    auto onTail = true;
    ;
    ;
    result = true;
    ;
    for (const auto rune : ritems(text)) {
        if (isNewline(rune)) {
            if ((!(onTail))) {
                return false;
                ;
            };
        } else {
            onTail = false;
            ;
        };
    };
    return result;
};

void newline(ColText& text) {
    /*!Append newline to the colored text
     */
    ;
    text.runes.add(((uc(R"(\n)")) + (default(ColStyle))));
};

Vec<ColRuneLine> lines(const ColText& text) {
    Vec<ColRuneLine> result{};
    /*!Iterate over lines of the colored text
     */
    ;

    ColRuneLine buf;
    ;
    ;
    for (const auto rune : text.runes) {
        if (rune.isNewline) {
            result.push_back(buf);
            buf.setLen(0);
        } else {
            buf.add(rune);
        };
    };
    if (((buf.len) > (0))) {
        result.push_back(buf);
    };
    return result;
};

int width(const ColText& text) {
    int result;
    /*!Get maximum width (line length) of the colored text
     */
    ;

    auto buf = 0;
    ;
    ;
    for (const auto rune : text.runes) {
        if (rune.isNewline) {
            result = max(buf, result);
            ;
            buf = 0;
            ;
        } else {
            += buf;
        };
    };
    if (((buf) > (0))) {
        return buf;
        ;
    };
    return result;
};

void add(ColText& colored, const ColText& other) {
    /*!Add one colored text block to another
     */
    ;
    colored.runes.add(other.runes);
};

void add(ColText& colored, const ColRuneLine& other) {
    /*!Add colored rune line (sequence of runes) to colored text
     */
    ;
    colored.runes.add(other);
};

void add(ColText& colored, const ColRune& rune) {
    /*!Add colored rune to the text
     */
    ;
    colored.runes.add(rune);
};

void add(ColText& colored, const((std::string) | (char)) & ch) {
    /*!Add std::string or character with default style to colored text,
     */
    ;
    colored.add(((ch) + (default(ColStyle))));
};

ColText indent(
    const ColText& str,
    const int&     count,
    const int&     indentAfter = -1,
    const ColText& indent      = clt(R"( )"),
    const ColText& prefix      = clt(R"()")) {
    ColText result;
    /*!Indent colored text lines by `count` repetitions of the `indent`
    text. Add `prefix` before each line.

    - `indentAfter` - first line to start applying indentation after
      (defaults to `-1`, so indentation is applied to the whole text). Can
      be used to allow `[header, line, line]` text to be easily processed
    */
    ;

    auto idx = 0;
    ;
    ;
    for (const auto line : lines(str)) {
        if (((idx) <= (indentAfter))) {
            result.add(line);
        } else {
            result.newline();
            for (int _ = 0; _ < ((count) - (prefix.len)); ++i) {
                result.add(indent);
            };
            result.add(prefix);
            result.add(line);
        };
        += idx;
    };
    return result;
};

ColText join(const Vec<ColText>& text, const ColText& sep) {
    ColText result;

    auto first = true;
    ;
    ;
    for (const auto item : text) {
        if ((!(first))) {
            result.add(sep);
        };
        first = false;
        ;
        result.add(item);
    };
    return result;
};

ColText stripLines(
    const ColText&   text,
    const bool&      leading = false,
    const bool&      trails  = true,
    const set<char>& chars   = {' '}) {
    ColText result;
    /*!Strip character from each line in text
     */
    ;

    auto idx = 0;
    ;
    ;
    for (const auto line : lines(text)) {

        auto start = 0;
        ;
        ;
        if (leading) {
            while (
                ((((((int(line[start].rune)) <= (ord(high(char)))))
                   && (((char(line[start].rune))in(chars)))))
                 && (((start) < (high(line)))))) {
                += start;
            };
        };

        auto final = high(line);
        ;
        ;
        if (trails) {
            while (
                ((((((int(line[final].rune)) <= (ord(high(char)))))
                   && (((char(line[final].rune))in(chars)))))
                 && (((0) < (final))))) {
                -= final;
            };
        };
        if (((((((start) == (final)))
               && (((int(line[final].rune)) <= (ord(high(char)))))))
             && (((char(line[final].rune))in(chars))))) {
            if (((idx) > (0))) {
                result.add(clt(R"(\n)"));
            };
        } else {
            if (((idx) > (0))) {
                result.add(clt(R"(\n)"));
            };
            result.add(line[rangeIncl(start, final)]);
        };
        += idx;
    };
    return result;
};

ColText operator&(const ColText& t1, const ColText& t2) {
    ColText result;
    /*!Concatenate two colored text blocks
     */
    ;
    result = t1;
    ;
    result.runes.add(t2.runes);
    return result;
};

ColText operator&(const ColText& t1, const Str& t2) {
    ColText result;
    /*!Concatenate colored text and regular std::string (with default
     * style)
     */
    ;
    result = t1;
    ;
    result.add(clt(t2));
    return result;
};

ColText operator&(const Str& t1, const ColText& t2) {
    ColText result;
    /*!Concatenate colored text and regular std::string (with default
     * style)
     */
    ;
    result = toColText(t1);
    ;
    result.add(t2);
    return result;
};

uint8 code(const TermColorFg& col) {
    uint8 result;
    /*!Get ansi code for the 16-color foreground terminal color
     */
    ;
    ((col.uint8) + (low(ForegroundColor).uint8));
    return result;
};

uint8 code(const TermColorBg& col) {
    uint8 result;
    /*!Get ansi code for the 16-color background terminal color
     */
    ;
    ((col.uint8) + (low(BackgroundColor).uint8));
    return result;
};

std::string ansiEsc(const SomeInteger& code) {
    std::string result;
    /*!Create ansi escape sequence with given code
     */
    ;
    ((((R"([)") & (toStr(code)))) & (R"(m)"));
    return result;
};

std::string ansiEsc(const TermColorFg& col) {
    std::string result;
    /*!Create ansi escape sequence with given terminal color
     */
    ;
    if (((col.uint8) <= (7))) {
        ansiEsc(code(col));
    } else if (((col.uint8) <= (15))) {
        ansiEsc(((code(col)) + (60)));
    } else {
        ((((R"([38;5;)") & (toStr((col.uint8))))) & (R"(m)"));
    };
    return result;
};

std::string ansiEsc(const TermColorBg& col) {
    std::string result;
    /*!Create ansi escape sequence with given terminal color
     */
    ;
    if (((col.uint8) <= (7))) {
        ansiEsc(code(col));
    } else if (((col.uint8) <= (15))) {
        ansiEsc(((code(col)) + (60)));
    } else {
        ((((R"([48;5;)") & (toStr((col.uint8))))) & (R"(m)"));
    };
    return result;
};

std::string ansiEsc(const Style& style, const bool& open) {
    std::string result;
    /*!Create ansi escape sequence with given style. `open` controls
    whether styling sequence is used for open or for close
    */
    ;

    const auto diff = else { open }
    else {
        20;
    };
    ;
    ;
    switch (style) {
        case styleBright: {
            ansiEsc(((1) + (diff)));
            break;
        }
        case styleDim: {
            ansiEsc(((2) + (diff)));
            break;
        }
        case styleItalic: {
            ansiEsc(((3) + (diff)));
            break;
        }
        case styleUnderscore: {
            ansiEsc(((4) + (diff)));
            break;
        }
        case styleBlink: {
            ansiEsc(((5) + (diff)));
            break;
        }
        case styleBlinkRapid: {
            ansiEsc(((6) + (diff)));
            break;
        }
        case styleReverse: {
            ansiEsc(((7) + (diff)));
            break;
        }
        case styleHidden: {
            ansiEsc(((8) + (diff)));
            break;
        }
        case styleStrikethrough: {
            ansiEsc(((9) + (diff)));
            break;
        }
    };
    return result;
};

std::string ansiDiff(const ColStyle& s1 const ColStyle& s2, ) {
    std::string result;
    /*!Generate ansi escape sequences to transition from style `s1` to
    style `s2`
    */
    ;
    if (((s2.fg) != (s1.fg))) {
        if (s2.fg.isDefault()) {
            ((result) &= (ansiEsc(39)));
        } else {
            ((result) &= (ansiEsc(s2.fg)));
        };
    };
    if (((s2.bg) != (s1.bg))) {
        if (s2.bg.isDefault()) {
            ((result) &= (ansiEsc(49)));
        } else {
            ((result) &= (ansiEsc(s2.bg)));
        };
    };
    for (const auto style : (((s1.style) - (s2.style)))) {
        ((result) &= (ansiEsc(style, false)));
    };
    for (const auto style : (((s2.style) - (s1.style)))) {
        ((result) &= (ansiEsc(style, true)));
    };
    return result;
};

std::string lispRepr(const ColRune& rune) {
    std::string result;
    (&(R"(({rune.rune} :fg {rune.style.fg} :bg {rune.style.bg} :style {rune.style.style}))"));
    return result;
};

std::string lispRepr(const ColText& rune) {
    std::string result;
    result = R"(()";
    ;
    for (const auto [idx, rune] : rune.runes) {
        if (((0) < (idx))) {
            result.add(R"(\n )");
        };
        result.add(lispRepr(rune));
    };
    ((result) &= (R"())"));
    return result;
};

std::string toStd::String(const ColRune& rune, const bool& color = true) {
    std::string result;
    /*!Convert colored rune to regular std::string, with ansi escape
    sequences. `color` controls whether styling is going to be applied or
    not.
    */
    ;
    if (color) {
        ((result) &= (ansiDiff(default(ColStyle), rune.style)));
        ((result) &= (toStr(rune.rune)));
        ((result) &= (ansiEsc(0)));
    } else {
        result = toStr(rune.rune);
        ;
    };
    return result;
};

std::string toStd::String(
    const Vec<ColRune>& runes,
    const bool&         color = true) {
    std::string result;
    /*!Convert sequence of colored runes to the std::string, with ansi
    escape sequences in. `color` controls whether styling is going to be
    applied or not.
    */
    ;
    if (color) {

        auto prev = initColStyle();
        ;
        ;
        for (const auto rune : runes) {
            ((result) &= (ansiDiff(prev, rune.style)));
            ((result) &= (toStr(rune.rune)));
            prev = rune.style;
            ;
        };
        if ((((((!(prev.fg.isDefault()))) || ((!(prev.bg.isDefault())))))
             || (((0) < (prev.style.len()))))) {
            ((result) &= (ansiEsc(0)));
        };
    } else {
        for (const auto rune : runes) {
            ((result) &= (toStr(rune.rune)));
        };
    };
    return result;
};

std::string toStd::String(const ColText& text, const bool& color = true) {
    std::string result;
    /*!Convert colored text to std::string with ansi escape sequences
     */
    ;
    toStd::String(text.runes, color);
    return result;
};
/* TODO CONST SECTION */;

std::string operator $(const ColRune& colored) {
    std::string result;
    /*!Convert to std::string with ansi escape sequences. To disable
    coloring use `toStd::String` procedure instead.
    */
    ;
    toStd::String(colored);
    return result;
};

std::string operator $(const ColRuneLine& colr) {
    std::string result;
    /*!Convert to std::string with ansi escape sequences. To disable
    coloring use `toStd::String` procedure instead.
    */
    ;
    toStd::String(colr);
    return result;
};

std::string operator $(const ColText& text) {
    std::string result;
    /*!Convert to std::string with ansi escape sequences. To disable
    coloring use `toStd::String` procedure instead.
    */
    ;
    toStd::String(text.runes);
    return result;
};

std::string operator $(const ColRuneGrid& colr) {
    std::string result;
    /*!Convert to multiline std::string with ansi escape sequences. To
    disable coloring use `toStd::String` procedure instead.
    */
    ;
    for (const auto [idx, line] : colr) {
        if (((idx) > (0))) {
            ((result) &= (R"(\n)"));
        };
        result.add(toStd::String(line));
    };
    return result;
};

TermColorFg termFg(
    const range<rangeIncl(0, 5)>& r const range<rangeIncl(0, 5)>& g,
    const range<rangeIncl(0, 5)>&                                 b, ) {
    TermColorFg result;
    /*!Create 256-terminal color with given red, green and blue coloring.
    Colors are mapped to 216-element color cube.
    */
    ;
    TermColorFg(
        ((((((offset256) + (b.uint8))) + (((g.uint8) * (scaleGreen)))))
         + (((scaleRed) * (r.uint8)))));
    return result;
};

TermColorBg termBg(
    const range<rangeIncl(0, 5)>& r const range<rangeIncl(0, 5)>& g,
    const range<rangeIncl(0, 5)>&                                 b, ) {
    TermColorBg result;
    /*!256-color for background. Maps to 216-element color cube.
     */
    ;
    TermColorBg(
        ((((((offset256) + (b.uint8))) + (((g.uint8) * (scaleGreen)))))
         + (((scaleRed) * (r.uint8)))));
    return result;
};

TermColorBg termBg(const range<rangeIncl(0, 23)>& gray) {
    TermColorBg result;
    /*!Create 256-color with given grey background value (from 0 to 23, for
    total 24 shades).
    */
    ;
    TermColorBg(((offsetGray) + (gray.uint8)));
    return result;
};

TermColorFg termFg(const range<rangeIncl(0, 23)>& gray) {
    TermColorFg result;
    /*!Grey foreground value
     */
    ;
    TermColorFg(((offsetGray) + (gray.uint8)));
    return result;
};

void addIndent(
    ColText&       res,
    const int&     level,
    const int&     sep    = 2,
    const ColRune& prefix = clr(' ')) {
    /*!Add indentation prefix to the colored text.
     */
    ;
    for (int _ = 0; _ < ((level) * (sep)); ++i) {
        res.add(prefix);
    };
};

template <typename R1, typename R2>
void operator[] =(
    ColRuneGrid&   buf,
    const R1&      rowIdx,
    const R2&      colIdx,
    const ColRune& ch,
    const ColRune& fill = clr(' ')) {

    void aux(
        const int& row const int& col,
        ,
        ColRuneGrid&   buf,
        const ColRune& ch) {
        for (int _ = buf.len; _ <= row; ++i) {
            buf.add((@({fill})));
        };
        ((buf[row]) &= (repeat(
             fill, max(((((col) - (buf[row].len))) + (1)), 0))));
        buf[row][col] = ch;
    };

    Vec<int> rows;
    Vec<int> cols;
    constexpr if (((rowIdx)is(int))) { rows = (@({rowIdx})); }
    else constexpr if (((rowIdx)is(((Slice[int]) | (openArray[int]))))) {
        for (const auto row : rowIdx) {
            rows.add(row);
        }
    }
    constexpr if (((colIdx)is(int))) { cols = (@({colIdx})); }
    else constexpr if (((colIdx)is(((Slice[int]) | (openArray[int]))))) {
        for (const auto col : colIdx) {
            cols.add(col);
        };
    }
    for (const auto row : rows) {
        for (const auto col : cols) {
            aux(row, col, buf, ch);
        }
    }
}

void operator[] =(
    ColRuneGrid&              buf,
    const int& row const int& col,
    const ColText&            str) {
    auto rowIdx = 0;
    for (const auto line : lines(str)) {
        for (const auto [colIdx, ch] : line) {
            buf[((row) + (rowIdx)), ((col) + (colIdx))] = ch;
            ;
        };
        += rowIdx;
    };
};

void operator[] =(
    ColRuneGrid&              buf,
    const int& row const int& col,
    const char&               ch) {
    buf[row, col] = toColRune(Rune(ch), initColStyle());
};

ColRuneGrid grid(const ColText& text) {
    ColRuneGrid result;
    for (const auto line : lines(text)) {
        result.add(line);
    }
    return result;
};

void addf(
    ColText&                           text,
    const Str&                         formatstr,
    const varargs<ColText, toColText>& colored) {
    for (const auto fr : addfFragments(formatstr)) {
        switch (fr.kind) {
            case addfDollar: {
                text.add(R"($)");
                break;
            }
            case addfText: {
                text.add(fr.text);
                break;
            }
            case addfVar:
            case addfExpr: {
                assert(
                    false,
                    R"(var/expr formatting is not supported for colored text yet)");
                break;
            }
            case addfPositional:
            case addfIndexed:
            case addfBackIndexed: {
                const auto idx = else { ((fr.kind) == (addfBackIndexed)) }
                else {
                    fr.idx;
                };
                assert((((((0) <= (idx))) && (((idx) < (colored.len))))));
                text.add(colored[idx]);
                break;
            }
        };
    };
};

ColText operator%(
    const Str&                format,
    const openArray<ColText>& interpolate) {
    ColText result;
    /*!Shorthand for colored text interpolation
     */
    ;
    result.addf(format, interpolate);
    return result;
};
