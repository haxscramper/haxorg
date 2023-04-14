#include <sem/ErrorWrite.hpp>

Characters unicode() {
    return Characters{
        .hbar       = L'─',
                .vbar       = L'│',
                .xbar       = L'┼',
                .vbar_break = L'┆',
                .vbar_gap   = L'┆',
                .uarrow     = L'🭯',
                .rarrow     = L'▶',
                .ltop       = L'╭',
                .mtop       = L'┬',
                .rtop       = L'╮',
                .lbot       = L'╰',
                .rbot       = L'╯',
                .mbot       = L'┴',
                .lbox       = L'[',
                .rbox       = L']',
                .lcross     = L'├',
                .rcross     = L'┤',
                .underbar   = L'┬',
                .underline  = L'─',
    };
}

Characters ascii() {
    return Characters{
        .hbar       = '-',
                .vbar       = '|',
                .xbar       = '+',
                .vbar_break = '*',
                .vbar_gap   = ':',
                .uarrow     = '^',
                .rarrow     = '>',
                .ltop       = ',',
                .mtop       = 'v',
                .rtop       = '.',
                .lbot       = '`',
                .rbot       = '\'',
                .mbot       = '^',
                .lbox       = '[',
                .rbox       = ']',
                .lcross     = '|',
                .rcross     = '|',
                .underbar   = '|',
                .underline  = '^',
    };
}
