#include <sem/ErrorWrite.hpp>
#include <QChar>

Characters unicode() {
    return Characters{
        .hbar       = QChar(L'─'),
        .vbar       = QChar(L'│'),
        .xbar       = QChar(L'┼'),
        .vbar_break = QChar(L'┆'),
        .vbar_gap   = QChar(L'┆'),
        .uarrow     = QChar(L'🭯'),
        .rarrow     = QChar(L'▶'),
        .ltop       = QChar(L'╭'),
        .mtop       = QChar(L'┬'),
        .rtop       = QChar(L'╮'),
        .lbot       = QChar(L'╰'),
        .rbot       = QChar(L'╯'),
        .mbot       = QChar(L'┴'),
        .lbox       = QChar(L'['),
        .rbox       = QChar(L']'),
        .lcross     = QChar(L'├'),
        .rcross     = QChar(L'┤'),
        .underbar   = QChar(L'┬'),
        .underline  = QChar(L'─'),
    };
}

Characters ascii() {
    return Characters{
        .hbar       = QChar('-'),
        .vbar       = QChar('|'),
        .xbar       = QChar('+'),
        .vbar_break = QChar('*'),
        .vbar_gap   = QChar(':'),
        .uarrow     = QChar('^'),
        .rarrow     = QChar('>'),
        .ltop       = QChar(','),
        .mtop       = QChar('v'),
        .rtop       = QChar('.'),
        .lbot       = QChar('`'),
        .rbot       = QChar('\''),
        .mbot       = QChar('^'),
        .lbox       = QChar('['),
        .rbox       = QChar(']'),
        .lcross     = QChar('|'),
        .rcross     = QChar('|'),
        .underbar   = QChar('|'),
        .underline  = QChar('^'),
    };
}
