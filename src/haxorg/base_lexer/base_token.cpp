#include <haxorg/base_lexer/base_token.hpp>
#include <hstd/stdlib/strutils.hpp>

hstd::fmt_iter fmt::formatter<org::parse::OrgFill>::format(
    org::parse::OrgFill const& p,
    format_context&            ctx) const {
    ::hstd::fmt_ctx("<", ctx);
    ::hstd::fmt_ctx(escape_for_write(p.text), ctx);
    ::hstd::fmt_ctx(">", ctx);
    if (p.loc.has_value()) {
        ::hstd::fmt_ctx(":", ctx);
        ::hstd::fmt_ctx(p.loc->line, ctx);
        ::hstd::fmt_ctx(":", ctx);
        ::hstd::fmt_ctx(p.loc->column, ctx);
        ::hstd::fmt_ctx(":", ctx);
        ::hstd::fmt_ctx(p.loc->pos, ctx);
        ::hstd::fmt_ctx("@", ctx);
        ::hstd::fmt_ctx(p.loc->file_id.format(), ctx);
    }
    return ctx.out();
}
