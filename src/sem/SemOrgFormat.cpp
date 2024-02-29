#include <sem/SemOrgFormat.hpp>
#include <hstd/stdlib/algorithms.hpp>

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

std::string nestedHashtag(sem::SemId<sem::HashTag> const& hash) {
    if (hash->subtags.empty()) {
        return hash->head;
    } else if (hash->subtags.size() == 1) {
        return hash->head + "##" + nestedHashtag(hash->subtags.at(0));
    } else {
        return hash->head + "##["
             + (hash->subtags                  //
                | rv::transform(nestedHashtag) //
                | rv::intersperse(",")         //
                | rv::join                     //
                | rs::to<std::string>()        //
                )
             + "]";
    }
}

Formatter::Res colonHashtags(Formatter* f, CVec<SemId<HashTag>> tags) {
    return f->b.join(
        Vec<Formatter::Res>::Splice(
            tags
            | rv::transform([&](CR<SemId<HashTag>> tag) -> Formatter::Res {
                  return f->str(nestedHashtag(tag));
              })),
        f->str(":"));
}

auto Formatter::toString(SemId<Document> id) -> Res {
    Res result = b.stack();

    bool hadDocumentProperties = false;

    if (id->title) {
        b.add_at(result, b.line({str("#+title: "), toString(*id->title)}));
        hadDocumentProperties = true;
    }

    using Visibility = DocumentOptions::Visibility;
    if (id->options->initialVisibility != Visibility::ShowEverything) {
        Str res = "";
        switch (id->options->initialVisibility) {
            case Visibility::ShowEverything: res = "showeverything"; break;
            case Visibility::Content: res = "content"; break;
            case Visibility::Overview: res = "overview"; break;
            case Visibility::ShowAll: res = "showall"; break;
            case Visibility::Show2Levels: res = "show2levels"; break;
            case Visibility::Show3Levels: res = "show3levels"; break;
            case Visibility::Show4Levels: res = "show4levels"; break;
            case Visibility::Show5Levels: res = "show5levels"; break;
        }

        b.add_at(result, b.line({str("#+startup: "), str(res)}));
    }

    if (!id->filetags.empty()) {
        b.add_at(
            result,
            b.line(
                {str("#+filetags: :"),
                 colonHashtags(this, id->filetags),
                 str(":")}));
        hadDocumentProperties = true;
    }

    if (id->author) {
        b.add_at(
            result, b.line({str("#+author: "), toString(*id->author)}));
        hadDocumentProperties = true;
    }

    if (hadDocumentProperties) { b.add_at(result, str("")); }

    for (auto const& sub : id->subnodes) {
        b.add_at(result, toString(sub));
    }

    if (b.at(result).size() == 0) { b.add_at(result, str("")); }

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
    if (id->key) {
        return str(fmt(":{} {}", id->key.value(), id->value));
    } else {
        return str(id->value);
    }
}

auto Formatter::toString(SemId<Code> id) -> Res {
    auto result = b.stack();


    auto head = b.line({str("#+begin_src")});
    if (id->lang) { b.add_at(head, str(" " + *id->lang)); }

    if (id->parameters) {
        b.add_at(head, str(" "));
        b.add_at(head, toString(id->parameters.value()));
    }

    b.add_at(result, head);
    for (auto const& it : id->lines) {
        auto line = b.line();
        for (auto const& part : it.parts) {
            switch (part.getKind()) {
                case Code::Line::Part::Kind::Raw: {
                    b.add_at(line, str(part.getRaw().code));
                    break;
                }
                case Code::Line::Part::Kind::Callout: {
                    b.add_at(line, str(part.getCallout().name));
                    break;
                }
                case Code::Line::Part::Kind::Tangle: {
                    b.add_at(line, str(part.getTangle().target));
                    break;
                }
            }
        }

        b.add_at(result, line);
    }

    b.add_at(result, str("#+end_src"));

    return result;
}

auto Formatter::toString(SemId<Tblfm> id) -> Res {
    return str(__PRETTY_FUNCTION__);
}

auto Formatter::toString(SemId<List> id) -> Res {
    Res result = b.stack();
    for (auto const& it : id->subnodes) { b.add_at(result, toString(it)); }
    return result;
}

auto Formatter::toString(SemId<SubtreeLog> id) -> Res {
    return str(__PRETTY_FUNCTION__);
}

auto Formatter::toString(SemId<Empty> id) -> Res { return str(""); }

auto Formatter::toString(SemId<Newline> id) -> Res {
    auto result = b.stack();

    for (int i = 1; i < id->text.size(); ++i) {
        b.add_at(result, str(""));
    }

    return result;
}

auto Formatter::toString(SemId<Monospace> id) -> Res {
    return b.line(Vec<Res>::Splice(str("~"), toSubnodes(id), str("~")));
}

auto Formatter::toString(SemId<Link> id) -> Res {
    if (id->getLinkKind() == Link::Kind::Raw && !id->description) {
        return str(id->getRaw().text);
    }

    Res head = str("");
    switch (id->getLinkKind()) {
        case Link::Kind::Person: {
            head = str("person:" + id->getPerson().name);
            break;
        }

        case Link::Kind::File: {
            head = str("file:" + id->getFile().file);
            break;
        }

        case Link::Kind::Id: {
            head = str("id:" + id->getId().text);
            break;
        }

        case Link::Kind::Raw: {
            head = str(id->getRaw().text);
            break;
        }

        default: {
            LOG(FATAL) << fmt1(id->getLinkKind());
        }
    }

    if (id->description) {
        return b.line({
            str("[["),
            head,
            str("]["),
            toString(id->description.value()),
            str("]]"),
        });
    } else {
        return b.line({
            str("[["),
            head,
            str("]]"),
        });
    }
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

auto Formatter::toString(SemId<Call> id) -> Res {
    return b.line({str("#+call: ")});
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
    return str("#" + nestedHashtag(id));
}

auto Formatter::toString(SemId<MarkQuote> id) -> Res {
    return str(__PRETTY_FUNCTION__);
}

auto Formatter::toString(SemId<TextSeparator> id) -> Res {
    return str("------------");
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
    Res body = b.stack();
    if (id->header) {
        Res head = b.stack();
        b.add_at(head, toString(*id->header));
        b.add_at(head, str(" :: "));
        b.add_at(head, toString(id->at(0)));
        b.add_at(body, head);
        b.add_at(body, str(""));

        for (auto const& sub : id->subnodes | rv::drop(1)) {
            b.add_at(body, toString(sub));
        }
    } else {
        for (auto const& sub : id->subnodes) {
            b.add_at(body, toString(sub));
        }
    }

    return b.line({str("- "), body});
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
    Vec<Res> result;
    for (auto const& pos : id->positional) {
        result.push_back(toString(pos));
    }

    Vec<Str> its;
    for (auto const& k : id->named.keys()) { its.push_back(k); }

    rs::sort(its, [](CR<Str> lhs, CR<Str> rhs) -> bool {
        return lhs.toBase() < rhs.toBase();
    });

    for (auto const& key : its) {
        result.push_back(toString(id->named.at(key)));
    }

    return b.join(result, str(" "));
}

auto Formatter::toString(SemId<InlineMath> id) -> Res {
    return b.line({str("\\("), toString(id->at(0)), str("\\)")});
}

auto Formatter::toString(SemId<Subtree> id) -> Res {
    Res title = b.line({
        id->todo ? str(id->todo.value() + Str(" ")) : str(""),
        toString(id->title),
    });

    if (!id->tags.empty()) {
        b.add_at(title, str(" :"));
        b.add_at(title, colonHashtags(this, id->tags));
        b.add_at(title, str(":"));
    }

    Res head = b.stack({title});

    if (id->scheduled) {
        b.add_at(
            head, b.line({str("SCHEDULED: "), toString(*id->scheduled)}));
    }

    if (id->deadline) {
        b.add_at(
            head, b.line({str("DEADLINE: "), toString(*id->deadline)}));
    }

    if (id->closed) {
        b.add_at(head, b.line({str("CLOSED: "), toString(*id->closed)}));
    }

    if (!id->properties.empty() || id->treeId) {
        b.add_at(head, str(":PROPERTIES:"));
        if (id->treeId) {
            b.add_at(head, str(fmt(":ID: {}", *id->treeId)));
        }

        for (auto const& prop : id->properties) {
            using P = sem::Subtree::Property;
            switch (prop.getKind()) {
                case P::Kind::Created: {
                    b.add_at(
                        head,
                        b.line(
                            {str(":CREATED: "),
                             toString(prop.getCreated().time)}));
                    break;
                }
                default: {
                    LOG(FATAL) << fmt1(prop.getKind());
                }
            }
        }

        b.add_at(head, str(":END:"));
    }

    if (!id->logbook.empty()) {
        b.add_at(head, str(":LOGBOOK:"));
        for (auto const& log : id->logbook) {
            using Log                     = sem::SubtreeLog;
            Res                  log_head = str("");
            Opt<SemId<StmtList>> desc;
            switch (log->getLogKind()) {
                case Log::Kind::Tag: {
                    auto const& tag = log->getTag();
                    if (tag.desc) { desc = tag.desc; }

                    log_head = b.line({
                        str("- Tag \""),
                        toString(tag.tag),
                        str("\""),
                        str(tag.added ? " Added" : " Removed"),
                        str(" on "),
                        toString(tag.on),
                    });

                    break;
                }

                case Log::Kind::Refile: {
                    auto const& refile = log->getRefile();
                    if (refile.desc) { desc = refile.desc; }

                    log_head = b.line({
                        str("- Refiled on "),
                        toString(refile.on),
                        str(" from "),
                        toString(refile.from),
                    });

                    break;
                }

                case Log::Kind::State: {
                    auto const& state = log->getState();
                    if (state.desc) {
                        CHECK(!state.desc->isNil());
                        desc = state.desc;
                    }

                    log_head = b.line({
                        str(
                            fmt("- State \"{}\" from \"{}\" ",
                                state.from,
                                state.to)),
                        toString(state.on),
                    });

                    break;
                }

                case Log::Kind::Note: {
                    auto const& note = log->getNote();
                    if (note.desc) {
                        CHECK(!note.desc->isNil());
                        desc = note.desc;
                    }

                    log_head = b.line({
                        str("- Note taken on "),
                        toString(note.on),
                    });

                    break;
                }

                case Log::Kind::Clock: {
                    auto const& clock = log->getClock();

                    log_head = b.line({
                        str("CLOCK: "),
                        clock.range.index() == 0
                            ? toString(std::get<0>(clock.range))
                            : toString(std::get<1>(clock.range)),
                    });

                    break;
                }
                default: {
                    LOG(FATAL) << fmt1(log->getLogKind());
                }
            }

            if (desc) {
                b.add_at(log_head, str(" \\\\"));
                CHECK(!desc.value().isNil()) << fmt1(log->getLogKind());
                b.add_at(head, log_head);
                b.add_at(
                    head, b.indent(2, b.stack(toSubnodes(desc.value()))));
            } else {
                b.add_at(head, log_head);
            }
        }
        b.add_at(head, str(":END:"));
    }

    Res result = b.stack();

    b.add_at(
        result,
        b.line({str(std::string(id->level, '*')), str(" "), head}));

    if (!id->subnodes.empty()) {
        b.add_at(result, str(""));
        add_subnodes(result, id.asOrg());
    }

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
        str("#+begin_export " + id->exporter),
        toSubnodes(id),
        str("#+end_export")));
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
