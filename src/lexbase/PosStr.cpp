#include <lexbase/PosStr.hpp>
#include <QRegularExpression>


void PosStr::print(ColStream& os, CR<PrintParams> params) const {
    if (params.withPos) {
        os << "#" << pos << "/" << view.size();
    }

    if (finished()) {
        os << TermColorFg8Bit::Red << " finished " << os.end();
    } else if (!params.withSeparation) {
        os << " ";
    }


    for (int i = params.startOffset; i < params.maxTokens && hasNext(i);
         ++i) {

        os << TermColorFg8Bit::Yellow;
        if (params.withSeparation) {
            os << " '" << visibleName(get(i)).first << "'";
        } else {
            os << visibleName(get(i)).first;
        }
        os << os.end();
    }

    os << " ";

    if (params.withEnd) {
        os << "\n";
    }
}

void PosStr::print() const { print(qcout, PrintParams()); }
void PosStr::print(ColStream& os) const { print(os, PrintParams()); }
void PosStr::print(CR<PrintParams> params) const { print(qcout, params); }
void PosStr::print(std::ostream& os, CR<PrintParams> params) const {
    ColStream stream{os};
    print(stream, params);
}


std::string PosStr::printToString(bool colored) const {
    return printToString(PrintParams{}, colored);
}

std::string PosStr::printToString(PrintParams params, bool colored) const {
    std::string     result;
    std::ostream stream{&result};
    ColStream   out{stream};
    params.withEnd = false;
    out.colored    = colored;
    print(out, params);
    return result;
}

PosStr::PosStr(std::stringView inView, int inPos) : view(inView), pos(inPos) {}

PosStr::PosStr(const char* data, int count, int inPos)
    : view(data, count), pos(inPos) {}

PosStr::PosStr(const std::string& str, int inPos)
    : view(str.data(), str.size()), pos(inPos) {}

Str PosStr::toStr() const { return Str(view); }

int PosStr::size() const { return view.size(); }

std::stringView PosStr::getOffsetView(int ahead) const {
    return std::stringView(
        view.data() + pos + ahead, view.size() - (pos + ahead));
}

void PosStr::pushSlice() { slices.push_back({pos}); }

int PosStr::getPos() const { return pos; }

void PosStr::setPos(int _pos) {
    assert(0 <= _pos && _pos < view.size());
    pos = _pos;
}

std::stringView PosStr::completeView(CR<SliceStartData> slice, Offset offset)
    const {
    return std::stringView(
        view.data() + slice.pos + offset.start,
        pos - slice.pos + offset.end);
}

PosStr PosStr::sliceBetween(int start, int end) const {
    return PosStr{std::stringView(view.data() + start, end - start + 1)};
}

PosStr PosStr::popSlice(Offset offset) {
    auto slice  = slices.pop_back_v();
    auto result = PosStr(completeView(slice, offset));
    return result;
}

PosStr PosStr::slice(AdvanceCb cb, Offset offset) {
    pushSlice();
    cb(*this);
    return popSlice(offset);
}

bool PosStr::hasNext(int shift) const {
    return 0 <= pos + shift && pos + shift < view.size();
}

void PosStr::back(int count) {
    for (int i = 0; i < count; ++i) {
        --pos;
    }
}

[[clang::xray_always_instrument]] void PosStr::next(int count) {
    for (int i = 0; i < count; ++i) {
        ++pos;
    }
}

[[clang::xray_always_instrument]] char PosStr::get(int offset) const {
    auto target = pos + offset;
    if (0 <= target && target < view.size()) {
        return view.at(target);
    } else {
        return char('\0');
    }
}

bool PosStr::finished() const { return get() == '\0'; }

bool PosStr::atStart() const { return pos == 0; }

bool PosStr::beforeEnd() const { return !hasNext(1); }

char PosStr::pop() {
    char result = get();
    next();
    return result;
}

[[clang::xray_always_instrument]] bool PosStr::at(
    char expected,
    int   offset) const {
    return get(offset) == expected;
}

[[clang::xray_always_instrument]] bool PosStr::at(
    CR<CharSet> expected,
    int         offset) const {
    return expected.contains(get(offset));
}

[[clang::xray_always_instrument]] bool PosStr::at(
    CR<std::string> expected,
    int         offset) const {
    int idx = 0;
    for (const auto& ch : expected) {
        if (get(offset + idx) != ch) {
            return false;
        }
        ++idx;
    }
    return true;
}

bool PosStr::at(CR<QRegularExpression> expected, int offset) const {
    auto result = expected.match(
        view,
        pos + offset,
        QRegularExpression::NormalMatch,
        QRegularExpression::AnchorAtOffsetMatchOption);

    return result.hasMatch();
}


std::string PosStr::getAhead(Slice<int> slice) const {
    std::string result;
    for (int idx : slice) {
        result += get(idx);
    }
    return result;
}

void PosStr::skipAny(CR<PosStr::CheckableSkip> expected, int offset) {
    std::visit([&](auto const& it) { return skip(it, offset); }, expected);
}

bool PosStr::atAny(CR<PosStr::CheckableSkip> expected, int offset) const {
    return std::visit(
        [&](auto const& it) { return at(it, offset); }, expected);
}

std::stringView viewForward(std::stringView view, int position, int span) {
    return view.sliced(
        position, std::min<int>(view.size() - position, span));
}


void PosStr::skip(CR<QRegularExpression> expected, int offset) {
    auto result = expected.match(
        view,
        pos + offset,
        QRegularExpression::NormalMatch,
        QRegularExpression::AnchorAtOffsetMatchOption);

    if (!result.hasMatch()) {
        // TODO move message generatoin logic into a separate function
        throw UnexpectedCharError(
            "Unexpected text encountered during lexing: found "
            "'$#' but expected regexp pattern $# at position $# "
            "view is $#"
            % to_string_vec(
                get(),
                expected.pattern(),
                pos + offset,
                viewForward(view, pos + offset, 20)));
    } else {
        next(result.capturedLength());
    }
}

void PosStr::skip(std::string expected, int offset) {
    if (at(expected, offset)) {
        next(expected.size());
    } else {
        throw UnexpectedCharError(
            "Unexpected text encountered during lexing: found "
            "'$#' but expected '$#' at position $# view is "
            "$#"
            % to_string_vec(
                get(),
                expected,
                pos + offset,
                viewForward(view, pos + offset, 20)));
    }
}


void PosStr::skip(char expected, int offset, int count) {
    if (get(offset) == expected) {
        next(count);
    } else {
        throw UnexpectedCharError(
            "Unexpected character encountered during lexing: found "
            "'$#' but expected '$#' at position $# view is "
            "$#"
            % to_string_vec(
                get(offset),
                expected,
                pos + offset,
                viewForward(view, pos + offset, 20)));
    }
}

void PosStr::skip(CR<CharSet> expected, int offset, int steps) {
    if (expected.contains(get(offset))) {
        next(steps);
    } else {
        throw UnexpectedCharError(
            "Unexpected character encountered during lexing: found "
            "'$#' but expected any of (char set) '$#'"
            "at position $# view is $#"
            % to_string_vec(
                get(offset),
                expected,
                pos + offset,
                viewForward(view, pos + offset, 20)));
    }
}


void PosStr::space(bool requireOne) {
    if (requireOne) {
        skip(' ');
    }
    skipZeroOrMore(charsets::HorizontalSpace);
}


bool PosStr::isEmptyLine() {
    auto before = 0;
    while (at(charsets::HorizontalSpace, before)) {
        --before;
    }

    if (!at(charsets::Newline, before)) {
        return false;
    }

    auto after = 0;
    while (at(charsets::HorizontalSpace, after)) {
        ++after;
    }
    if (!at(charsets::Newline, after)) {
        return false;
    }
    return true;
}

void PosStr::skipToEOL() { skipTo(charsets::Newline); }
void PosStr::skipToNextLine() {
    skipToEOL();
    next();
}

void PosStr::skipToEOF() { pos = view.size() - 1; }
void PosStr::skipPastEOF() { pos = view.size(); }
void PosStr::skipToSOF() { pos = 0; }

void PosStr::skipPastEOL() {
    skipTo(charsets::Newline);
    if (!finished() && at(charsets::Newline)) {
        next();
    }
}


bool PosStr::trySkipEmptyLine() {
    bool result = isEmptyLine();
    if (result) {
        skipPastEOL();
    }
    return result;
}

int PosStr::skipIndent(const int& maxIndent) {
    int result;
    while (at(charsets::HorizontalSpace)) {
        ++result;
        next();
        if (maxIndent <= result) {
            break;
        }
    }
    return result;
}

void PosStr::skipBeforeEOL() { skipBefore(charsets::Newline); }

int PosStr::getIndent() const {
    int result = 0;
    while (at(charsets::HorizontalSpace, result)) {
        ++result;
    }
    return result;
}

int PosStr::getColumn() const {
    int result = 0;
    int offset = -1;
    while (hasNext(offset) && !at('\n', offset)) {
        ++result;
        --offset;
    }

    return result;
}

bool PosStr::hasMoreIndent(const int& indent, const bool& exactIndent)
    const {
    bool result      = false;
    int  foundIndent = 0;
    while (at(charsets::HorizontalSpace, foundIndent)) {
        ++foundIndent;
        if (indent <= foundIndent) {
            break;
        }
    }

    if (foundIndent == indent) {
        return true;
    } else if (foundIndent <= indent) {
        return false;
    } else {
        return !exactIndent || at(charsets::HorizontalSpace, foundIndent);
    }
    return result;
}


void PosStr::skipIdent(const CharSet& chars) { skipZeroOrMore(chars); }

UnexpectedCharError PosStr::makeUnexpected(
    CR<std::string> expected, ///< What we expected to find?
    CR<std::string> parsing   ///< Description of the thing we are
                          /// parsing at the moment
) {
    return UnexpectedCharError(
        "Unexpected character encountered during lexing: found "
        "'$#' but expected $# while parsing $# at position $# view "
        "is $#"
        % to_string_vec(
            get(), expected, parsing, pos, viewForward(view, pos, 20)));
}


void skipBalancedSlice(PosStr& str, CR<BalancedSkipArgs> args) {
    auto fullCount = args.skippedStart ? 1 : 0;
    int  count[pow_v<2, 8 * sizeof(char)>::res] = {};
    while (str.hasNext()) {
        if (args.allowEscape && str.at('\\')) {
            str.next();
            str.next();
        } else if (str.at(args.openChars)) {
            ++fullCount;
            ++count[value_domain<char>::ord(str.pop())];
        } else if (str.at(args.closeChars)) {
            --fullCount;
            if ((0 < fullCount) || args.consumeLast) {
                --count[value_domain<char>::ord(str.pop())];
            }
            if (fullCount == 0) {
                return;
            }
        } else if (str.at(args.endChars)) {
            if (0 < fullCount) {
                if (args.doRaise) {
                    throw str.makeUnexpected(
                        "balanced opening/closing pair",
                        "balanced opening/closing pair");
                } else {
                    return;
                }
            } else {
                return;
            }
        } else {
            str.next();
        }
    }
    if (0 < fullCount && args.doRaise) {
        throw str.makeUnexpected(
            "balanced opening/closing pair",
            "balanced opening/closing pair");
    }
}

/// \brief Skip over decimal/hex/octal/binary digt
void skipDigit(Ref<PosStr> str) {
    if (str.at('-')) {
        str.next();
    }
    if (str.at("0x")) {
        str.next(2);
        str.skip(charsets::HexDigits);
        str.skipZeroOrMore(charsets::HexDigits + CharSet{'_'});
    } else if (str.at("0b")) {
        str.next(2);
        str.skip(CharSet{'0', '1'});
        str.skipZeroOrMore(CharSet{'0', '1'});
    } else {
        str.skip(charsets::Digits);
        str.skipZeroOrMore(
            charsets::Digits + CharSet{'_', '.'});
    }
}

void skipStringLit(PosStr& str) {
    auto found = false;
    str.next();
    while (!found) {
        found = str.at('"') && !str.at('\\', -1);
        str.next();
    }
}
