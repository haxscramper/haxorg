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

void Formatter::add_subnodes(Res result, SemId id) {
    for (auto const& it : id->subnodes) { b.add_at(result, toString(it)); }
}

auto Formatter::toString(SemIdT<Word> id) -> Res { return str(id->text); }

auto Formatter::toString(SemIdT<Macro> id) -> Res {
    LOG(FATAL);
    return str(__FUNCTION__);
}

auto Formatter::toString(SemIdT<Document> id) -> Res {
    Res result = b.stack();

    if (id->title) {
        b.add_at(result, b.line({str("#+title: "), toString(*id->title)}));
    }

    if (id->author) {
        b.add_at(
            result, b.line({str("#+author: "), toString(*id->author)}));
    }

    for (auto const& sub : id->subnodes) {
        b.add_at(result, toString(sub));
    }

    return result;
}

auto Formatter::toString(SemIdT<RawText> id) -> Res {
    LOG(FATAL);
    return str(__FUNCTION__);
}

auto Formatter::toString(SemIdT<Footnote> id) -> Res {
    LOG(FATAL);
    return str(__FUNCTION__);
}

auto Formatter::toString(SemIdT<CmdArgument> id) -> Res {
    LOG(FATAL);
    return str(__FUNCTION__);
}

auto Formatter::toString(SemIdT<Code> id) -> Res {
    LOG(FATAL);
    return str(__FUNCTION__);
}

auto Formatter::toString(SemIdT<List> id) -> Res {
    LOG(FATAL);
    return str(__FUNCTION__);
}

auto Formatter::toString(SemIdT<SubtreeLog> id) -> Res {
    LOG(FATAL);
    return str(__FUNCTION__);
}

auto Formatter::toString(SemIdT<Empty> id) -> Res {
    LOG(FATAL);
    return str(__FUNCTION__);
}

auto Formatter::toString(SemIdT<Newline> id) -> Res {
    LOG(FATAL);
    return str(__FUNCTION__);
}

auto Formatter::toString(SemIdT<Monospace> id) -> Res {
    LOG(FATAL);
    return str(__FUNCTION__);
}

auto Formatter::toString(SemIdT<Link> id) -> Res {
    LOG(FATAL);
    return str(__FUNCTION__);
}

auto Formatter::toString(SemIdT<Symbol> id) -> Res {
    LOG(FATAL);
    return str(__FUNCTION__);
}

auto Formatter::toString(SemIdT<Caption> id) -> Res {
    LOG(FATAL);
    return str(__FUNCTION__);
}

auto Formatter::toString(SemIdT<DocumentGroup> id) -> Res {
    LOG(FATAL);
    return str(__FUNCTION__);
}

auto Formatter::toString(SemIdT<CommandGroup> id) -> Res {
    LOG(FATAL);
    return str(__FUNCTION__);
}

auto Formatter::toString(SemIdT<Escaped> id) -> Res {
    LOG(FATAL);
    return str(__FUNCTION__);
}

auto Formatter::toString(SemIdT<Par> id) -> Res {
    LOG(FATAL);
    return str(__FUNCTION__);
}

auto Formatter::toString(SemIdT<Placeholder> id) -> Res {
    LOG(FATAL);
    return str(__FUNCTION__);
}

auto Formatter::toString(SemIdT<BigIdent> id) -> Res {
    LOG(FATAL);
    return str(__FUNCTION__);
}

auto Formatter::toString(SemIdT<HashTag> id) -> Res {
    LOG(FATAL);
    return str(__FUNCTION__);
}

auto Formatter::toString(SemIdT<MarkQuote> id) -> Res {
    LOG(FATAL);
    return str(__FUNCTION__);
}

auto Formatter::toString(SemIdT<TextSeparator> id) -> Res {
    LOG(FATAL);
    return str(__FUNCTION__);
}

auto Formatter::toString(SemIdT<Time> id) -> Res {
    LOG(FATAL);
    return str(__FUNCTION__);
}

auto Formatter::toString(SemIdT<StmtList> id) -> Res {
    LOG(FATAL);
    return str(__FUNCTION__);
}

auto Formatter::toString(SemIdT<TimeRange> id) -> Res {
    LOG(FATAL);
    return str(__FUNCTION__);
}

auto Formatter::toString(SemIdT<Row> id) -> Res {
    LOG(FATAL);
    return str(__FUNCTION__);
}

auto Formatter::toString(SemIdT<Completion> id) -> Res {
    LOG(FATAL);
    return str(__FUNCTION__);
}

auto Formatter::toString(SemIdT<Center> id) -> Res {
    LOG(FATAL);
    return str(__FUNCTION__);
}

auto Formatter::toString(SemIdT<Bold> id) -> Res {
    LOG(FATAL);
    return str(__FUNCTION__);
}

auto Formatter::toString(SemIdT<Space> id) -> Res { return str(id->text); }

auto Formatter::toString(SemIdT<ListItem> id) -> Res {
    LOG(FATAL);
    return str(__FUNCTION__);
}

auto Formatter::toString(SemIdT<AtMention> id) -> Res {
    LOG(FATAL);
    return str(__FUNCTION__);
}

auto Formatter::toString(SemIdT<Italic> id) -> Res {
    LOG(FATAL);
    return str(__FUNCTION__);
}

auto Formatter::toString(SemIdT<Table> id) -> Res {
    LOG(FATAL);
    return str(__FUNCTION__);
}

auto Formatter::toString(SemIdT<AdmonitionBlock> id) -> Res {
    LOG(FATAL);
    return str(__FUNCTION__);
}

auto Formatter::toString(SemIdT<Strike> id) -> Res {
    LOG(FATAL);
    return str(__FUNCTION__);
}

auto Formatter::toString(SemIdT<CmdArguments> id) -> Res {
    LOG(FATAL);
    return str(__FUNCTION__);
}

auto Formatter::toString(SemIdT<InlineMath> id) -> Res {
    LOG(FATAL);
    return str(__FUNCTION__);
}

auto Formatter::toString(SemIdT<Subtree> id) -> Res {
    LOG(FATAL);
    return str(__FUNCTION__);
}

auto Formatter::toString(SemIdT<DocumentOptions> id) -> Res {
    LOG(FATAL);
    return str(__FUNCTION__);
}

auto Formatter::toString(SemIdT<Verbatim> id) -> Res {
    LOG(FATAL);
    return str(__FUNCTION__);
}

auto Formatter::toString(SemIdT<Quote> id) -> Res {
    LOG(FATAL);
    return str(__FUNCTION__);
}

auto Formatter::toString(SemIdT<Include> id) -> Res {
    LOG(FATAL);
    return str(__FUNCTION__);
}

auto Formatter::toString(SemIdT<Punctuation> id) -> Res {
    LOG(FATAL);
    return str(__FUNCTION__);
}

auto Formatter::toString(SemIdT<FileTarget> id) -> Res {
    LOG(FATAL);
    return str(__FUNCTION__);
}

auto Formatter::toString(SemIdT<Export> id) -> Res {
    LOG(FATAL);
    return str(__FUNCTION__);
}

auto Formatter::toString(SemIdT<Example> id) -> Res {
    LOG(FATAL);
    return str(__FUNCTION__);
}

auto Formatter::toString(SemIdT<Paragraph> id) -> Res {
    Res result = b.stack();
    for (auto const& line :
         id->subnodes | rv::split_when([](sem::SemId id) {
             return id.getKind() == OrgSemKind::Newline;
         })) {
        Res line_out = b.line();
        for (auto const& item : line) {
            b.add_at(line_out, toString(item));
        }
        b.add_at(result, line_out);
    }
    return result;
}

auto Formatter::toString(SemIdT<Underline> id) -> Res {
    Res result = b.line();
    b.add_at(result, str("_"));
    add_subnodes(result, id.toId());
    b.add_at(result, str("_"));
    return result;
}

auto Formatter::toString(SemIdT<ParseError> id) -> Res {
    LOG(FATAL);
    return str(__FUNCTION__);
}
