#include <sem/SemOrgFormat.hpp>

using namespace sem;

auto Formatter::toString(SemId id) -> Res {
    if (id.isNil()) {
        return str("");
    } else {
        switch (id.getKind()) {
#define _case(__Kind)                                                     \
    case OrgSemKind::__Kind: return toString(id.as<__Kind>());
            EACH_SEM_ORG_KIND(_case)
#undef _case
        }
    }
}

auto Formatter::toString(SemIdT<Word> id) -> Res { return str(id->text); }

auto Formatter::toString(SemIdT<Macro> id) -> Res {
    return str(__FUNCTION__);
}

auto Formatter::toString(SemIdT<Document> id) -> Res {
    return str(__FUNCTION__);
}

auto Formatter::toString(SemIdT<RawText> id) -> Res {
    return str(__FUNCTION__);
}

auto Formatter::toString(SemIdT<Footnote> id) -> Res {
    return str(__FUNCTION__);
}

auto Formatter::toString(SemIdT<CmdArgument> id) -> Res {
    return str(__FUNCTION__);
}

auto Formatter::toString(SemIdT<Code> id) -> Res {
    return str(__FUNCTION__);
}

auto Formatter::toString(SemIdT<List> id) -> Res {
    return str(__FUNCTION__);
}

auto Formatter::toString(SemIdT<SubtreeLog> id) -> Res {
    return str(__FUNCTION__);
}

auto Formatter::toString(SemIdT<Empty> id) -> Res {
    return str(__FUNCTION__);
}

auto Formatter::toString(SemIdT<Newline> id) -> Res {
    return str(__FUNCTION__);
}

auto Formatter::toString(SemIdT<Monospace> id) -> Res {
    return str(__FUNCTION__);
}

auto Formatter::toString(SemIdT<Link> id) -> Res {
    return str(__FUNCTION__);
}

auto Formatter::toString(SemIdT<Symbol> id) -> Res {
    return str(__FUNCTION__);
}

auto Formatter::toString(SemIdT<Caption> id) -> Res {
    return str(__FUNCTION__);
}

auto Formatter::toString(SemIdT<DocumentGroup> id) -> Res {
    return str(__FUNCTION__);
}

auto Formatter::toString(SemIdT<CommandGroup> id) -> Res {
    return str(__FUNCTION__);
}

auto Formatter::toString(SemIdT<Escaped> id) -> Res {
    return str(__FUNCTION__);
}

auto Formatter::toString(SemIdT<Par> id) -> Res {
    return str(__FUNCTION__);
}

auto Formatter::toString(SemIdT<Placeholder> id) -> Res {
    return str(__FUNCTION__);
}

auto Formatter::toString(SemIdT<BigIdent> id) -> Res {
    return str(__FUNCTION__);
}

auto Formatter::toString(SemIdT<HashTag> id) -> Res {
    return str(__FUNCTION__);
}

auto Formatter::toString(SemIdT<MarkQuote> id) -> Res {
    return str(__FUNCTION__);
}

auto Formatter::toString(SemIdT<TextSeparator> id) -> Res {
    return str(__FUNCTION__);
}

auto Formatter::toString(SemIdT<Time> id) -> Res {
    return str(__FUNCTION__);
}

auto Formatter::toString(SemIdT<StmtList> id) -> Res {
    return str(__FUNCTION__);
}

auto Formatter::toString(SemIdT<TimeRange> id) -> Res {
    return str(__FUNCTION__);
}

auto Formatter::toString(SemIdT<Row> id) -> Res {
    return str(__FUNCTION__);
}

auto Formatter::toString(SemIdT<Completion> id) -> Res {
    return str(__FUNCTION__);
}

auto Formatter::toString(SemIdT<Center> id) -> Res {
    return str(__FUNCTION__);
}

auto Formatter::toString(SemIdT<Bold> id) -> Res {
    return str(__FUNCTION__);
}

auto Formatter::toString(SemIdT<Space> id) -> Res {
    return str(__FUNCTION__);
}

auto Formatter::toString(SemIdT<ListItem> id) -> Res {
    return str(__FUNCTION__);
}

auto Formatter::toString(SemIdT<AtMention> id) -> Res {
    return str(__FUNCTION__);
}

auto Formatter::toString(SemIdT<Italic> id) -> Res {
    return str(__FUNCTION__);
}

auto Formatter::toString(SemIdT<Table> id) -> Res {
    return str(__FUNCTION__);
}

auto Formatter::toString(SemIdT<AdmonitionBlock> id) -> Res {
    return str(__FUNCTION__);
}

auto Formatter::toString(SemIdT<Strike> id) -> Res {
    return str(__FUNCTION__);
}

auto Formatter::toString(SemIdT<CmdArguments> id) -> Res {
    return str(__FUNCTION__);
}

auto Formatter::toString(SemIdT<InlineMath> id) -> Res {
    return str(__FUNCTION__);
}

auto Formatter::toString(SemIdT<Subtree> id) -> Res {
    return str(__FUNCTION__);
}

auto Formatter::toString(SemIdT<DocumentOptions> id) -> Res {
    return str(__FUNCTION__);
}

auto Formatter::toString(SemIdT<Verbatim> id) -> Res {
    return str(__FUNCTION__);
}

auto Formatter::toString(SemIdT<Quote> id) -> Res {
    return str(__FUNCTION__);
}

auto Formatter::toString(SemIdT<Include> id) -> Res {
    return str(__FUNCTION__);
}

auto Formatter::toString(SemIdT<Punctuation> id) -> Res {
    return str(__FUNCTION__);
}

auto Formatter::toString(SemIdT<FileTarget> id) -> Res {
    return str(__FUNCTION__);
}

auto Formatter::toString(SemIdT<Export> id) -> Res {
    return str(__FUNCTION__);
}

auto Formatter::toString(SemIdT<Example> id) -> Res {
    return str(__FUNCTION__);
}

auto Formatter::toString(SemIdT<Paragraph> id) -> Res {
    return str(__FUNCTION__);
}

auto Formatter::toString(SemIdT<Underline> id) -> Res {
    return str(__FUNCTION__);
}

auto Formatter::toString(SemIdT<ParseError> id) -> Res {
    return str(__FUNCTION__);
}
