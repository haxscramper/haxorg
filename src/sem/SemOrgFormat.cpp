#include <sem/SemOrgFormat.hpp>

using namespace sem;

auto Formatter::toString(SemId<Org> id) -> Res {
    if (id.isNil()) {
        return str("");
    } else {
        switch (id->getKind()) {
#define _case(__Kind)                                                     \
    case OrgSemKind::__Kind: return toString(id.as<__Kind>());
            EACH_SEM_ORG_KIND(_case)
#undef _case
        }
    }
}


void Formatter::add_subnodes(Res result, SemId<Org> id) {
    for (auto const& it : id->subnodes) { b.add_at(result, toString(it)); }
}

auto Formatter::toString(SemId<Word> id) -> Res { return str(id->text); }

auto Formatter::toString(SemId<Macro> id) -> Res {
    if (id->arguments.empty()) {
        return str(Str("{{{") + id->name + Str("}}}"));
    } else {
        return b.line(Vec<Res>::Splice(
            str(Str("{{{") + id->name + Str("(")),
            id->arguments //
                | rv::transform([&](CR<Str> s) { return str(s); }),
            str(")}}}") //
            ));
    }
}

auto Formatter::toString(SemId<Document> id) -> Res {
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

auto Formatter::toString(SemId<RawText> id) -> Res {
    return str(id->text);
}

auto Formatter::toString(SemId<Footnote> id) -> Res {
    if (id->definition) {
        return b.line({
            str("[fn::"),
            toString(id->definition.value()),
            str("]"),
        });
    } else {
        return str(fmt("[fn:{}]", id->tag));
    }
}

auto Formatter::toString(SemId<CmdArgument> id) -> Res {
    return str(__PRETTY_FUNCTION__);
}

auto Formatter::toString(SemId<Code> id) -> Res {
    return str(__PRETTY_FUNCTION__);
}

auto Formatter::toString(SemId<Tblfm> id) -> Res {
    return str(__PRETTY_FUNCTION__);
}

auto Formatter::toString(SemId<List> id) -> Res {
    return str(__PRETTY_FUNCTION__);
}

auto Formatter::toString(SemId<SubtreeLog> id) -> Res {
    return str(__PRETTY_FUNCTION__);
}

auto Formatter::toString(SemId<Empty> id) -> Res { return str(""); }

auto Formatter::toString(SemId<Newline> id) -> Res { return str("\n"); }

auto Formatter::toString(SemId<Monospace> id) -> Res {
    return b.line(Vec<Res>::Splice(str("~"), toSubnodes(id), str("~")));
}

auto Formatter::toString(SemId<Link> id) -> Res {
    return str(__PRETTY_FUNCTION__);
}

auto Formatter::toString(SemId<Symbol> id) -> Res {
    Res result = b.line({str("\\" + id->name)});
    for (auto const& [key, value] : id->parameters) {
        if (key) {
            b.add_at(
                result,
                b.line({
                    str("["),
                    str(*key),
                    str("="),
                    str(value),
                    str("]"),
                }));
        } else {
            b.add_at(result, b.line({str("["), str(value), str("]")}));
        }
    }

    for (auto const& it : id->positional) {
        b.add_at(result, b.line({str("{"), toString(it), str("}")}));
    }

    return result;
}

auto Formatter::toString(SemId<Caption> id) -> Res {
    return b.line({str("#+caption: "), toString(id->text)});
}

auto Formatter::toString(SemId<CmdResults> id) -> Res {
    return b.line({str("#+results: ")});
}

auto Formatter::toString(SemId<CmdName> id) -> Res {
    return b.line({str("#+name: ")});
}

auto Formatter::toString(SemId<CmdFiletags> id) -> Res {
    return b.line({str("#+filetags: ")});
}

auto Formatter::toString(SemId<DocumentGroup> id) -> Res {
    return str(__PRETTY_FUNCTION__);
}

auto Formatter::toString(SemId<CommandGroup> id) -> Res {
    return str(__PRETTY_FUNCTION__);
}

auto Formatter::toString(SemId<Escaped> id) -> Res {
    return str("\\" + id->text);
}

auto Formatter::toString(SemId<Par> id) -> Res {
    return str(__PRETTY_FUNCTION__);
}

auto Formatter::toString(SemId<Placeholder> id) -> Res {
    return b.line(Vec<Res>::Splice(str("<"), toSubnodes(id), str(">")));
}

auto Formatter::toString(SemId<BigIdent> id) -> Res {
    return str(id->text);
}

auto Formatter::toString(SemId<HashTag> id) -> Res {
    std::function<std::string(sem::SemId<sem::HashTag> const& hash)> aux;
    aux = [&aux](sem::SemId<sem::HashTag> const& hash) -> std::string {
        if (hash->subtags.empty()) {
            return hash->head;
        } else {
            return hash->head + "##["
                 + (hash->subtags           //
                    | rv::transform(aux)    //
                    | rv::intersperse(",")  //
                    | rv::join              //
                    | rs::to<std::string>() //
                    )
                 + "]";
        }
    };

    return str(aux(id));
}

auto Formatter::toString(SemId<MarkQuote> id) -> Res {
    return str(__PRETTY_FUNCTION__);
}

auto Formatter::toString(SemId<TextSeparator> id) -> Res {

    return str(__PRETTY_FUNCTION__);
}

auto Formatter::toString(SemId<Time> id) -> Res {
    Res result = b.line();

    b.add_at(result, str(id->isActive ? "<" : "["));
    if (id->isStatic()) {
        UserTime const& time = id->getStatic().time;
        b.add_at(result, str(time.format()));
    } else {
        b.add_at(result, str(id->getDynamic().expr));
    }
    b.add_at(result, str(id->isActive ? ">" : "]"));

    return result;
}

auto Formatter::toString(SemId<StmtList> id) -> Res {
    return b.line(toSubnodes(id));
}

auto Formatter::toString(SemId<TimeRange> id) -> Res {
    return b.line({toString(id->from), str("--"), toString(id->to)});
}

auto Formatter::toString(SemId<Row> id) -> Res {
    return str(__PRETTY_FUNCTION__);
}

auto Formatter::toString(SemId<Completion> id) -> Res {
    return str(fmt("[{}/{}]", id->done, id->full));
}

auto Formatter::toString(SemId<Center> id) -> Res {
    return b.stack(Vec<Res>::Splice(
        str("#+begin_center"), toSubnodes(id), str("#+end_center")));
}

auto Formatter::toString(SemId<Bold> id) -> Res {
    return b.line(Vec<Res>::Splice(str("*"), toSubnodes(id), str("*")));
}

auto Formatter::toString(SemId<Space> id) -> Res { return str(id->text); }

auto Formatter::toString(SemId<ListItem> id) -> Res {
    return str(__PRETTY_FUNCTION__);
}

auto Formatter::toString(SemId<AtMention> id) -> Res {
    return str("@" + id->text);
}

auto Formatter::toString(SemId<Italic> id) -> Res {
    return b.line(Vec<Res>::Splice(str("/"), toSubnodes(id), str("/")));
}

auto Formatter::toString(SemId<Table> id) -> Res {
    return str(__PRETTY_FUNCTION__);
}

auto Formatter::toString(SemId<AdmonitionBlock> id) -> Res {
    return str(__PRETTY_FUNCTION__);
}

auto Formatter::toString(SemId<Strike> id) -> Res {
    return b.line(Vec<Res>::Splice(str("+"), toSubnodes(id), str("+")));
}

auto Formatter::toString(SemId<CmdArguments> id) -> Res {
    return str(__PRETTY_FUNCTION__);
}

auto Formatter::toString(SemId<InlineMath> id) -> Res {
    return b.line({str("\\("), toString(id->at(0)), str("\\)")});
}

auto Formatter::toString(SemId<Subtree> id) -> Res {
    Res result = b.stack();

    Res head = b.line({
        str(std::string(id->level, '*')),
        str(" "),
        id->todo ? str(id->todo.value() + Str(" ")) : str(""),
        toString(id->title),
    });

    b.add_at(result, head);
    if (!id->subnodes.empty()) { add_subnodes(result, id.asOrg()); }


    return result;
}

auto Formatter::toString(SemId<DocumentOptions> id) -> Res {
    return str(__PRETTY_FUNCTION__);
}

auto Formatter::toString(SemId<Verbatim> id) -> Res {
    return b.line(Vec<Res>::Splice(str("="), toSubnodes(id), str("=")));
}

auto Formatter::toString(SemId<Quote> id) -> Res {
    return b.stack(Vec<Res>::Splice(
        str("#+begin_quote"), toSubnodes(id), str("#+end_quote")));
}

auto Formatter::toString(SemId<Verse> id) -> Res {
    return b.stack(Vec<Res>::Splice(
        str("#+begin_verse"), toSubnodes(id), str("#+end_verse")));
}


auto Formatter::toString(SemId<Include> id) -> Res {
    return str(__PRETTY_FUNCTION__);
}

auto Formatter::toString(SemId<Punctuation> id) -> Res {
    return str(id->text);
}

auto Formatter::toString(SemId<FileTarget> id) -> Res {
    return str(__PRETTY_FUNCTION__);
}

auto Formatter::toString(SemId<Export> id) -> Res {
    return b.stack(Vec<Res>::Splice(
        str("#+begin_export"), toSubnodes(id), str("#+end_export")));
}

auto Formatter::toString(SemId<Example> id) -> Res {
    return b.stack(Vec<Res>::Splice(
        str("#+begin_example"), toSubnodes(id), str("#+end_example")));
}

auto Formatter::toString(SemId<Paragraph> id) -> Res {
    Res result = b.stack();
    for (auto const& line :
         id->subnodes | rv::split_when([](sem::SemId<sem::Org> id) {
             return id->getKind() == OrgSemKind::Newline;
         })) {
        Res line_out = b.line();
        for (auto const& item : line) {
            b.add_at(line_out, toString(item));
        }
        b.add_at(result, line_out);
    }
    return result;
}

auto Formatter::toString(SemId<Underline> id) -> Res {
    return b.line(Vec<Res>::Splice(str("_"), toSubnodes(id), str("_")));
}

auto Formatter::toString(SemId<ParseError> id) -> Res {
    return str(__PRETTY_FUNCTION__);
}
