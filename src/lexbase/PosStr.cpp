#include <lexbase/PosStr.hpp>


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
void PosStr::print(QTextStream& os, CR<PrintParams> params) const {
    ColStream stream{os};
    print(stream, params);
}


QString PosStr::printToString(bool colored) const {
    return printToString(PrintParams{}, colored);
}

QString PosStr::printToString(PrintParams params, bool colored) const {
    QString     result;
    QTextStream stream{&result};
    ColStream   out{stream};
    params.withEnd = false;
    out.colored    = colored;
    print(out, params);
    return result;
}

PosStr::PosStr(QStringView inView, int inPos) : view(inView), pos(inPos) {}

PosStr::PosStr(const QChar* data, int count, int inPos)
    : view(data, count), pos(inPos) {}

PosStr::PosStr(const QString& str, int inPos)
    : view(str.data(), str.size()), pos(inPos) {}

Str PosStr::toStr() const { return Str(view); }

int PosStr::size() const { return view.size(); }

QStringView PosStr::getOffsetView(int ahead) const {
    return QStringView(
        view.data() + pos + ahead, view.size() - (pos + ahead));
}

void PosStr::pushSlice() { slices.push_back({pos}); }

int PosStr::getPos() const { return pos; }

void PosStr::setPos(int _pos) {
    assert(0 <= _pos && _pos < view.size());
    pos = _pos;
}

QStringView PosStr::completeView(CR<SliceStartData> slice, Offset offset)
    const {
    return QStringView(
        view.data() + slice.pos + offset.start,
        pos - slice.pos + offset.end);
}

PosStr PosStr::sliceBetween(int start, int end) const {
    return PosStr{QStringView(view.data() + start, end - start + 1)};
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

void PosStr::next(int count) {
    for (int i = 0; i < count; ++i) {
        ++pos;
    }
}

QChar PosStr::get(int offset) const {
    QChar result = QChar(QChar('\0'));
    auto  target = pos + offset;
    if (0 <= target && target < view.size()) {
        result = view[target];
    }
    return result;
}

bool PosStr::finished() const { return get() == QChar('\0'); }

bool PosStr::atStart() const { return pos == 0; }

bool PosStr::beforeEnd() const { return !hasNext(1); }

QChar PosStr::pop() {
    QChar result = get();
    next();
    return result;
}

bool PosStr::at(QChar expected, int offset) const {
    return get(offset) == expected;
}

bool PosStr::at(CR<CharSet> expected, int offset) const {
    return expected.contains(get(offset));
}

bool PosStr::at(CR<QString> expected, int offset) const {
    int idx = 0;
    for (const auto& ch : expected) {
        if (get(offset + idx) != ch) {
            return false;
        }
        ++idx;
    }
    return true;
}

QString PosStr::getAhead(Slice<int> slice) const {
    QString result;
    for (int idx : slice) {
        result += get(idx);
    }
    return result;
}

void PosStr::skipAny(CR<PosStr::CheckableSkip> expected, int offset) {
    switch (expected.index()) {
        case 0: skip(std::get<0>(expected), offset); break;
        case 1: skip(std::get<1>(expected), offset); break;
        case 2: skip(std::get<2>(expected), offset); break;
    }
}

bool PosStr::atAny(CR<PosStr::CheckableSkip> expected, int offset) const {
    switch (expected.index()) {
        case 0: return at(std::get<0>(expected), offset);
        case 1: return at(std::get<1>(expected), offset);
        case 2: return at(std::get<2>(expected), offset);
    }
}

void PosStr::skip(QString expected, int offset) {
    if (at(expected, offset)) {
        next(expected.size());
    } else {
        throw UnexpectedCharError(
            "Unexpected character encountered during lexing: found "
            "QChar('$#') but expected QChar('$#')"
            % to_string_vec(get(), expected));
    }
}


void PosStr::skip(QChar expected, int offset, int count) {
    if (get(offset) == expected) {
        next(count);
    } else {
        throw UnexpectedCharError(
            "Unexpected character encountered during lexing: found "
            "QChar('$#') but expected QChar('$#')"
            % to_string_vec(get(offset), expected));
    }
}

void PosStr::skip(CR<CharSet> expected, int offset, int steps) {
    if (expected.contains(get(offset))) {
        next(steps);
    } else {
        throw UnexpectedCharError(
            "Unexpected character encountered during lexing: found "
            "QChar('$#') but expected any of (char set) QChar('$#')"
            % to_string_vec(get(offset), expected));
    }
}


void PosStr::space(bool requireOne) {
    if (requireOne) {
        skip(QChar(' '));
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
    while (hasNext(offset) && !at(QChar('\n'), offset)) {
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
    CR<QString> expected, //< What we expected to find?
    CR<QString> parsing   //< Description of the thing we are
                          // parsing at the moment
) {
    return UnexpectedCharError(
        "Unexpected character encountered during lexing: found "
        "QChar('$#') but expected $# while parsing $#"
        % to_string_vec(get(), expected, parsing));
}


void skipBalancedSlice(PosStr& str, CR<BalancedSkipArgs> args) {
    auto fullCount = args.skippedStart ? 1 : 0;
    int  count[sizeof(char) * 8];
    while (str.hasNext()) {
        if (args.allowEscape && str.at(QChar('\\'))) {
            str.next();
            str.next();
        } else if (str.at(args.openChars)) {
            ++fullCount;
            ++count[ord(str.pop())];
        } else if (str.at(args.closeChars)) {
            --fullCount;
            if ((0 < fullCount) || args.consumeLast) {
                --count[ord(str.pop())];
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

void skipDigit(Ref<PosStr> str) {
    if (str.at(QChar('-'))) {
        str.next();
    }
    if (str.at("0x")) {
        str.next(2);
        str.skip(charsets::HexDigits);
        str.skipZeroOrMore(charsets::HexDigits + CharSet{QChar('_')});
    } else if (str.at("0b")) {
        str.next(2);
        str.skip(CharSet{QChar('0'), QChar('1')});
        str.skipZeroOrMore(CharSet{QChar('0'), QChar('1')});
    } else {
        str.skip(charsets::Digits);
        str.skipZeroOrMore(
            charsets::Digits + CharSet{QChar('_'), QChar('.')});
    }
}

void skipStringLit(PosStr& str) {
    auto found = false;
    str.next();
    while (!found) {
        found = str.at(QChar('"')) && !str.at(QChar('\\'), -1);
        str.next();
    }
}
