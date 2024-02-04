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

template <typename T>
concept RangeV3 = requires(T t) {
    { std::begin(t) } -> std::input_or_output_iterator;
    { std::end(t) } -> std::input_or_output_iterator;
};


template <typename T, RangeV3 Range>
void Splice_Impl1(std::vector<T>& result, Range&& range) {
    std::copy(
        std::begin(range), std::end(range), std::back_inserter(result));
}

template <typename T>
void Splice_Impl1(Vec<T>& result, T&& arg) {
    result.push_back(std::forward<T>(arg));
}

template <typename T>
void Splice_Impl1(Vec<T>& result, Vec<T>&& arg) {
    result.append(std::forward<Vec<T>>(arg));
}

template <typename T>
void Splice_Impl(Vec<T>& result) {}

template <typename T, typename... Rest>
void Splice_Impl(Vec<T>& result, Vec<T>&& first, Rest&&... rest) {
    Splice_Impl1(result, std::forward<Vec<T>>(first));
    Splice_Impl(result, std::forward<Rest>(rest)...);
}

template <typename T, typename First, typename... Rest>
void Splice_Impl(Vec<T>& result, First&& first, Rest&&... rest) {
    Splice_Impl1(result, std::forward<First>(first));
    Splice_Impl(result, std::forward<Rest>(rest)...);
}

template <typename T, typename... Args>
Vec<T> Splice(Args&&... args) {
    Vec<T> result;
    Splice_Impl<T>(result, std::forward<Args>(args)...);
    return result;
}

void Formatter::add_subnodes(Res result, SemId id) {
    for (auto const& it : id->subnodes) { b.add_at(result, toString(it)); }
}

auto Formatter::toString(SemIdT<Word> id) -> Res { return str(id->text); }

auto Formatter::toString(SemIdT<Macro> id) -> Res {
    if (id->arguments.empty()) {
        return str(Str("{{{") + id->name + Str("}}}"));
    } else {
        return b.line(Splice<Res>(
            str(Str("{{{") + id->name + Str("(")),
            id->arguments //
                | rv::transform([&](CR<Str> s) { return str(s); }),
            str(")}}}") //
            ));
    }
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
    return str(id->text);
}

auto Formatter::toString(SemIdT<Footnote> id) -> Res {
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

auto Formatter::toString(SemIdT<CmdArgument> id) -> Res {
    return str(__PRETTY_FUNCTION__);
}

auto Formatter::toString(SemIdT<Code> id) -> Res {
    return str(__PRETTY_FUNCTION__);
}

auto Formatter::toString(SemIdT<List> id) -> Res {
    return str(__PRETTY_FUNCTION__);
}

auto Formatter::toString(SemIdT<SubtreeLog> id) -> Res {
    return str(__PRETTY_FUNCTION__);
}

auto Formatter::toString(SemIdT<Empty> id) -> Res { return str(""); }

auto Formatter::toString(SemIdT<Newline> id) -> Res { return str("\n"); }

auto Formatter::toString(SemIdT<Monospace> id) -> Res {
    return b.line(Splice<Res>(str("~"), toSubnodes(id), str("~")));
}

auto Formatter::toString(SemIdT<Link> id) -> Res {
    return str(__PRETTY_FUNCTION__);
}

auto Formatter::toString(SemIdT<Symbol> id) -> Res {
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

auto Formatter::toString(SemIdT<Caption> id) -> Res {
    return b.line({str("#+caption: "), toString(id->text)});
}

auto Formatter::toString(SemIdT<DocumentGroup> id) -> Res {
    return str(__PRETTY_FUNCTION__);
}

auto Formatter::toString(SemIdT<CommandGroup> id) -> Res {
    return str(__PRETTY_FUNCTION__);
}

auto Formatter::toString(SemIdT<Escaped> id) -> Res {
    return str("\\" + id->text);
}

auto Formatter::toString(SemIdT<Par> id) -> Res {
    return str(__PRETTY_FUNCTION__);
}

auto Formatter::toString(SemIdT<Placeholder> id) -> Res {
    return b.line(Splice<Res>(str("<"), toSubnodes(id), str(">")));
}

auto Formatter::toString(SemIdT<BigIdent> id) -> Res {
    return str(id->text);
}

auto Formatter::toString(SemIdT<HashTag> id) -> Res {
    std::function<std::string(sem::HashTag const& hash)> aux;
    aux = [&aux](sem::HashTag const& hash) -> std::string {
        if (hash.subtags.empty()) {
            return hash.head;
        } else {
            return hash.head + "##["
                 + (hash.subtags            //
                    | rv::transform(aux)    //
                    | rv::intersperse(",")  //
                    | rv::join              //
                    | rs::to<std::string>() //
                    )
                 + "]";
        }
    };

    return str(aux(*id.get()));
}

auto Formatter::toString(SemIdT<MarkQuote> id) -> Res {
    return str(__PRETTY_FUNCTION__);
}

auto Formatter::toString(SemIdT<TextSeparator> id) -> Res {

    return str(__PRETTY_FUNCTION__);
}

auto Formatter::toString(SemIdT<Time> id) -> Res {
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

auto Formatter::toString(SemIdT<StmtList> id) -> Res {
    return b.line(toSubnodes(id));
}

auto Formatter::toString(SemIdT<TimeRange> id) -> Res {
    return b.line({toString(id->from), str("--"), toString(id->to)});
}

auto Formatter::toString(SemIdT<Row> id) -> Res {
    return str(__PRETTY_FUNCTION__);
}

auto Formatter::toString(SemIdT<Completion> id) -> Res {
    return str(fmt("[{}/{}]", id->done, id->full));
}

auto Formatter::toString(SemIdT<Center> id) -> Res {
    return b.stack(Splice<Res>(
        str("#+begin_center"), toSubnodes(id), str("#+end_center")));
}

auto Formatter::toString(SemIdT<Bold> id) -> Res {
    return b.line(Splice<Res>(str("*"), toSubnodes(id), str("*")));
}

auto Formatter::toString(SemIdT<Space> id) -> Res { return str(id->text); }

auto Formatter::toString(SemIdT<ListItem> id) -> Res {
    return str(__PRETTY_FUNCTION__);
}

auto Formatter::toString(SemIdT<AtMention> id) -> Res {
    return str("@" + id->text);
}

auto Formatter::toString(SemIdT<Italic> id) -> Res {
    return b.line(Splice<Res>(str("/"), toSubnodes(id), str("/")));
}

auto Formatter::toString(SemIdT<Table> id) -> Res {
    return str(__PRETTY_FUNCTION__);
}

auto Formatter::toString(SemIdT<AdmonitionBlock> id) -> Res {
    return str(__PRETTY_FUNCTION__);
}

auto Formatter::toString(SemIdT<Strike> id) -> Res {
    return b.line(Splice<Res>(str("+"), toSubnodes(id), str("+")));
}

auto Formatter::toString(SemIdT<CmdArguments> id) -> Res {
    return str(__PRETTY_FUNCTION__);
}

auto Formatter::toString(SemIdT<InlineMath> id) -> Res {
    return b.line({str("\\("), toString(id->at(0)), str("\\)")});
}

auto Formatter::toString(SemIdT<Subtree> id) -> Res {
    Res result = b.stack();

    Res head = b.line({
        str(std::string(id->level, '*')),
        str(" "),
        id->todo ? str(id->todo.value() + Str(" ")) : str(""),
        toString(id->title),
    });

    add_subnodes(result, id.toId());

    return result;
}

auto Formatter::toString(SemIdT<DocumentOptions> id) -> Res {
    return str(__PRETTY_FUNCTION__);
}

auto Formatter::toString(SemIdT<Verbatim> id) -> Res {
    return b.line(Splice<Res>(str("="), toSubnodes(id), str("=")));
}

auto Formatter::toString(SemIdT<Quote> id) -> Res {
    return b.stack(Splice<Res>(
        str("#+begin_quote"), toSubnodes(id), str("#+end_quote")));
}

auto Formatter::toString(SemIdT<Verse> id) -> Res {
    return b.stack(Splice<Res>(
        str("#+begin_verse"), toSubnodes(id), str("#+end_verse")));
}


auto Formatter::toString(SemIdT<Include> id) -> Res {
    return str(__PRETTY_FUNCTION__);
}

auto Formatter::toString(SemIdT<Punctuation> id) -> Res {
    return str(id->text);
}

auto Formatter::toString(SemIdT<FileTarget> id) -> Res {
    return str(__PRETTY_FUNCTION__);
}

auto Formatter::toString(SemIdT<Export> id) -> Res {
    return b.stack(Splice<Res>(
        str("#+begin_export"), toSubnodes(id), str("#+end_export")));
}

auto Formatter::toString(SemIdT<Example> id) -> Res {
    return b.stack(Splice<Res>(
        str("#+begin_example"), toSubnodes(id), str("#+end_example")));
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
    return b.line(Splice<Res>(str("_"), toSubnodes(id), str("_")));
}

auto Formatter::toString(SemIdT<ParseError> id) -> Res {
    return str(__PRETTY_FUNCTION__);
}
