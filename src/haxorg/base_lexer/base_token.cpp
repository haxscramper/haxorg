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

using otk = OrgTokenKind;


hstd::IntSet<OrgTokenKind> const org::parse::OrgTokenCmdBlockClose{
    otk::CmdSrcEnd,
    otk::CmdCenterEnd,
    otk::CmdExampleEnd,
    otk::CmdQuoteEnd,
    otk::CmdExportEnd,
    otk::CmdVerseEnd,
    otk::CmdCommentEnd,
    otk::CmdTableEnd,
    otk::CmdRowEnd,
    otk::CmdCellEnd,
    otk::CmdDynamicBlockEnd,
};

hstd::IntSet<OrgTokenKind> const org::parse::OrgTokenCmdBlockOpen{
    otk::CmdCenterBegin,
    otk::CmdExportBegin,
    otk::CmdExampleBegin,
    otk::CmdSrcBegin,
    otk::CmdQuoteBegin,
    otk::CmdVerseBegin,
    otk::CmdCommentBegin,
    otk::CmdTableBegin,
    otk::CmdRowBegin,
    otk::CmdCellBegin,
    otk::CmdDynamicBlockBegin,
};

hstd::IntSet<OrgTokenKind> const org::parse::OrgTokenCmdBlockLine{
    otk::CmdTitle,         otk::CmdHeader,
    otk::CmdName,          otk::CmdInclude,
    otk::CmdResults,       otk::CmdCaption,
    otk::CmdColumns,       otk::CmdAttr,
    otk::CmdAttr,          otk::CmdPropertyArgs,
    otk::CmdPropertyRaw,   otk::CmdPropertyText,
    otk::CmdOptions,       otk::CmdFiletags,
    otk::CmdTblfm,         otk::CmdLatexClass,
    otk::CmdLatexCompiler, otk::CmdLatexClassOptions,
    otk::CmdLatexHeader,   otk::CmdStartup,
    otk::CmdRow,           otk::CmdCell,
    otk::CmdAuthor,        otk::CmdCustomRaw,
    otk::CmdDescription,   otk::CmdLinkRaw,
    otk::CmdEmailRaw,      otk::CmdLatexHeaderExtraRaw,
    otk::CmdDateRaw,       otk::CmdLanguage,
    otk::CmdBindRaw,       otk::CmdCategoryRaw,
    otk::CmdSeqTodoRaw,    otk::CmdTagsRaw,
    otk::CmdPrioritiesRaw, otk::CmdMacroRaw,
    otk::CmdSetupfileRaw,  otk::CmdExcludeTagsRaw,
    otk::CmdHtmlHeadRaw,   otk::CmdSelectTagsRaw,
    otk::CmdDrawersRaw,    otk::CmdConstants,
    otk::CmdCreator,       otk::CmdCall,
    otk::CmdKeywordsRaw,
};
