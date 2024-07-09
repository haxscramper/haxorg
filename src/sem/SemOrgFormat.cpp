#include <sem/SemOrgFormat.hpp>
#include <hstd/stdlib/algorithms.hpp>

using namespace sem;

auto Formatter::toString(SemId<Org> id, CR<Context> ctx) -> Res {
    if (id.isNil()) { return str("<nil>"); }
    if (id.isNil()) {
        return str("");
    } else {
        switch (id->getKind()) {
#define _case(__Kind)                                                     \
    case OrgSemKind::__Kind: return toString(id.as<__Kind>(), ctx);
            EACH_SEM_ORG_KIND(_case)
#undef _case
        }
    }
}


void Formatter::add_subnodes(Res result, SemId<Org> id, CR<Context> ctx) {
    for (auto const& it : id->subnodes) {
        b.add_at(result, toString(it, ctx));
    }
}

auto Formatter::toString(SemId<RadioTarget> id, CR<Context> ctx) -> Res {
    if (id.isNil()) { return str("<nil>"); }
    return str("<<<"_ss + id->text + ">>>"_ss);
}

auto Formatter::toString(SemId<TextTarget> id, CR<Context> ctx) -> Res {
    if (id.isNil()) { return str("<nil>"); }
    return str("<<"_ss + id->text + ">>"_ss);
}

auto Formatter::toString(SemId<Word> id, CR<Context> ctx) -> Res {
    if (id.isNil()) { return str("<nil>"); }
    return str(id->text);
}

auto Formatter::toString(SemId<Macro> id, CR<Context> ctx) -> Res {
    if (id.isNil()) { return str("<nil>"); }
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

auto Formatter::toString(SemId<Document> id, CR<Context> ctx) -> Res {
    if (id.isNil()) { return str("<nil>"); }
    Res result = b.stack();

    bool hadDocumentProperties = false;

    if (id->title) {
        b.add_at(
            result, b.line({str("#+title: "), toString(*id->title, ctx)}));
        hadDocumentProperties = true;
    }

    using Visibility = DocumentOptions::Visibility;
    if (id->options
        && id->options->initialVisibility != Visibility::ShowEverything) {
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
            result,
            b.line({str("#+author: "), toString(*id->author, ctx)}));
        hadDocumentProperties = true;
    }

    if (hadDocumentProperties) { b.add_at(result, str("")); }

    for (auto const& sub : id->subnodes) {
        b.add_at(result, toString(sub, ctx));
    }

    if (b.at(result).size() == 0) { b.add_at(result, str("")); }

    return result;
}

auto Formatter::toString(SemId<RawText> id, CR<Context> ctx) -> Res {
    if (id.isNil()) { return str("<nil>"); }
    return str(id->text);
}

auto Formatter::toString(SemId<Footnote> id, CR<Context> ctx) -> Res {
    if (id.isNil()) { return str("<nil>"); }
    if (id->definition) {
        return b.line({
            str("[fn::"),
            toString(id->definition.value(), ctx),
            str("]"),
        });
    } else {
        return str(fmt("[fn:{}]", id->tag));
    }
}

auto Formatter::toString(SemId<CmdArgument> id, CR<Context> ctx) -> Res {
    if (id.isNil()) { return str("<nil>"); }
    if (id->key) {
        return str(fmt(":{} {}", id->key.value(), id->value));
    } else {
        return str(id->value);
    }
}

auto Formatter::toString(SemId<Code> id, CR<Context> ctx) -> Res {
    if (id.isNil()) { return str("<nil>"); }
    bool isInline = ctx.isInline;

    auto result = isInline ? b.line() : b.stack();
    auto head   = isInline ? b.line({str("src_")})
                           : b.line({str("#+begin_src")});

    if (id->lang) {
        b.add_at(head, str((isInline ? "" : " ") + *id->lang));
    }

    if (id->parameters) {
        if (isInline) {
            b.add_at(head, str("["));
        } else {
            b.add_at(head, str(" "));
        }

        b.add_at(head, toString(id->parameters.value(), ctx));
        if (isInline) { b.add_at(head, str("]")); }
    }

    b.add_at(result, head);
    if (isInline) { b.add_at(result, str("{")); }
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

    if (isInline) {
        b.add_at(result, str("}"));
    } else {
        b.add_at(result, str("#+end_src"));
    }

    return result;
}

auto Formatter::toString(SemId<Tblfm> id, CR<Context> ctx) -> Res {
    if (id.isNil()) { return str("<nil>"); }
    return str(__PRETTY_FUNCTION__);
}

auto Formatter::toString(SemId<List> id, CR<Context> ctx) -> Res {
    if (id.isNil()) { return str("<nil>"); }
    Res result = b.stack();
    for (auto const& it : id->subnodes) {
        b.add_at(result, toString(it, ctx));
    }
    return result;
}

auto Formatter::toString(SemId<SubtreeLog> id, CR<Context> ctx) -> Res {
    if (id.isNil()) { return str("<nil>"); }
    return str(__PRETTY_FUNCTION__);
}

auto Formatter::toString(SemId<Empty> id, CR<Context> ctx) -> Res {
    if (id.isNil()) { return str("<nil>"); }
    return str("");
}

auto Formatter::toString(SemId<Newline> id, CR<Context> ctx) -> Res {
    if (id.isNil()) { return str("<nil>"); }
    auto result = b.stack();

    for (int i = 1; i < id->text.size(); ++i) {
        b.add_at(result, str(""));
    }

    return result;
}

auto Formatter::toString(SemId<Monospace> id, CR<Context> ctx) -> Res {
    if (id.isNil()) { return str("<nil>"); }
    return b.line(
        Vec<Res>::Splice(str("~"), toSubnodes(id, ctx), str("~")));
}

auto Formatter::toString(SemId<Link> id, CR<Context> ctx) -> Res {
    if (id.isNil()) { return str("<nil>"); }
    if (id->getLinkKind() == Link::Kind::Raw && !id->description) {
        return str(id->getRaw().text);
    }

    Res head = str("");
    switch (id->getLinkKind()) {
        case Link::Kind::Person: {
            head = str("person:" + id->getPerson().name);
            break;
        }

        case Link::Kind::Attachment: {
            head = str("attachment:" + id->getAttachment().file);
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

        case Link::Kind::Internal: {
            head = str(id->getInternal().target);
            break;
        }

        case Link::Kind::Raw: {
            head = str(id->getRaw().text);
            break;
        }

        case Link::Kind::Footnote: {
            head = str("fn:"_ss + id->getFootnote().target);
            break;
        }

        default: {
            LOG(FATAL) << fmt1(id->getLinkKind());
        }
    }

    if (id->getLinkKind() == Link::Kind::Footnote
        && !id->description.has_value()) {
        return b.line({
            str("["),
            head,
            str("]"),
        });
    } else if (id->description) {
        return b.line({
            str("[["),
            head,
            str("]["),
            toString(id->description.value(), ctx),
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

auto Formatter::toString(SemId<Symbol> id, CR<Context> ctx) -> Res {
    if (id.isNil()) { return str("<nil>"); }
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
        b.add_at(result, b.line({str("{"), toString(it, ctx), str("}")}));
    }

    return result;
}

auto Formatter::toString(SemId<Caption> id, CR<Context> ctx) -> Res {
    if (id.isNil()) { return str("<nil>"); }
    return b.line({str("#+caption: "), toString(id->text, ctx)});
}

auto Formatter::toString(SemId<CmdResults> id, CR<Context> ctx) -> Res {
    if (id.isNil()) { return str("<nil>"); }
    return b.line({str("#+results: ")});
}

auto Formatter::toString(SemId<CmdName> id, CR<Context> ctx) -> Res {
    if (id.isNil()) { return str("<nil>"); }
    return b.line({str("#+name: ")});
}

auto Formatter::toString(SemId<Call> id, CR<Context> ctx) -> Res {
    if (id.isNil()) { return str("<nil>"); }
    return b.line({str("#+call: ")});
}

auto Formatter::toString(SemId<DocumentGroup> id, CR<Context> ctx) -> Res {
    if (id.isNil()) { return str("<nil>"); }
    return str(__PRETTY_FUNCTION__);
}

auto Formatter::toString(SemId<CommandGroup> id, CR<Context> ctx) -> Res {
    if (id.isNil()) { return str("<nil>"); }
    return str(__PRETTY_FUNCTION__);
}

auto Formatter::toString(SemId<Escaped> id, CR<Context> ctx) -> Res {
    if (id.isNil()) { return str("<nil>"); }
    return str("\\" + id->text);
}

auto Formatter::toString(SemId<Par> id, CR<Context> ctx) -> Res {
    if (id.isNil()) { return str("<nil>"); }
    return str(__PRETTY_FUNCTION__);
}

auto Formatter::toString(SemId<Placeholder> id, CR<Context> ctx) -> Res {
    if (id.isNil()) { return str("<nil>"); }
    return b.line(Vec<Res>::Splice(str("<"), str(id->text), str(">")));
}

auto Formatter::toString(SemId<BigIdent> id, CR<Context> ctx) -> Res {
    if (id.isNil()) { return str("<nil>"); }
    return str(id->text);
}


auto Formatter::toString(SemId<HashTag> id, CR<Context> ctx) -> Res {
    if (id.isNil()) { return str("<nil>"); }
    return str("#" + nestedHashtag(id));
}

auto Formatter::toString(SemId<MarkQuote> id, CR<Context> ctx) -> Res {
    if (id.isNil()) { return str("<nil>"); }
    return str(__PRETTY_FUNCTION__);
}

auto Formatter::toString(SemId<TextSeparator> id, CR<Context> ctx) -> Res {
    if (id.isNil()) { return str("<nil>"); }
    return str("------------");
}

auto Formatter::toString(SemId<Time> id, CR<Context> ctx) -> Res {
    if (id.isNil()) { return str("<nil>"); }
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

auto Formatter::toString(SemId<StmtList> id, CR<Context> ctx) -> Res {
    if (id.isNil()) { return str("<nil>"); }
    return b.line(toSubnodes(id, ctx));
}

auto Formatter::toString(SemId<TimeRange> id, CR<Context> ctx) -> Res {
    if (id.isNil()) { return str("<nil>"); }
    return b.line(
        {toString(id->from, ctx), str("--"), toString(id->to, ctx)});
}

auto Formatter::toString(SemId<Row> id, CR<Context> ctx) -> Res {
    if (id.isNil()) { return str("<nil>"); }
    return str(__PRETTY_FUNCTION__);
}

auto Formatter::toString(SemId<Cell> id, CR<Context> ctx) -> Res {
    if (id.isNil()) { return str("<nil>"); }
    return str(__PRETTY_FUNCTION__);
}


auto Formatter::toString(SemId<Completion> id, CR<Context> ctx) -> Res {
    if (id.isNil()) { return str("<nil>"); }
    return str(fmt("[{}/{}]", id->done, id->full));
}

auto Formatter::toString(SemId<Center> id, CR<Context> ctx) -> Res {
    if (id.isNil()) { return str("<nil>"); }
    return b.stack(Vec<Res>::Splice(
        str("#+begin_center"), toSubnodes(id, ctx), str("#+end_center")));
}

auto Formatter::toString(SemId<Bold> id, CR<Context> ctx) -> Res {
    if (id.isNil()) { return str("<nil>"); }
    return b.line(
        Vec<Res>::Splice(str("*"), toSubnodes(id, ctx), str("*")));
}

auto Formatter::toString(SemId<Space> id, CR<Context> ctx) -> Res {
    if (id.isNil()) { return str("<nil>"); }
    return str(id->text);
}

auto Formatter::toString(SemId<ListItem> id, CR<Context> ctx) -> Res {
    if (id.isNil()) { return str("<nil>"); }
    Res body = b.stack();
    if (id->header) {
        Res head = b.stack();
        b.add_at(head, toString(*id->header, ctx));
        b.add_at(head, str(" :: "));
        if (id->subnodes.has(0)) {
            b.add_at(head, toString(id->at(0), ctx));
            b.add_at(body, head);
            b.add_at(body, str(""));

            for (auto const& sub : id->subnodes | rv::drop(1)) {
                b.add_at(body, toString(sub, ctx));
            }
        }
    } else {
        for (auto const& sub : id->subnodes) {
            b.add_at(body, toString(sub, ctx));
        }
    }

    Str checkbox;
    switch (id->checkbox) {
        case ListItem::Checkbox::Empty: checkbox = "[ ] "; break;
        case ListItem::Checkbox::Done: checkbox = "[x] "; break;
        case ListItem::Checkbox::Partial: checkbox = "[-] "; break;
        case ListItem::Checkbox::None: checkbox = ""; break;
    }


    return b.line({str("- " + checkbox), body});
}

auto Formatter::toString(SemId<AtMention> id, CR<Context> ctx) -> Res {
    if (id.isNil()) { return str("<nil>"); }
    return str("@" + id->text);
}

auto Formatter::toString(SemId<Italic> id, CR<Context> ctx) -> Res {
    if (id.isNil()) { return str("<nil>"); }
    return b.line(
        Vec<Res>::Splice(str("/"), toSubnodes(id, ctx), str("/")));
}

auto Formatter::toString(SemId<Table> id, CR<Context> ctx) -> Res {
    if (id.isNil()) { return str("<nil>"); }
    Res result = b.stack();
    for (auto const& in_row : id->rows) {
        Res row = b.line({str("| ")});
        for (auto const& in_cell : in_row->cells) {
            Res cell = b.line();
            for (auto const& item : in_cell->subnodes) {
                b.add_at(cell, str(" "));
                b.add_at(cell, toString(item, ctx));
                b.add_at(cell, str(" "));
            }

            b.add_at(row, cell);
            b.add_at(row, str("|"));
        }


        b.add_at(result, row);
    }

    return result;
}

auto Formatter::toString(SemId<AdmonitionBlock> id, CR<Context> ctx)
    -> Res {
    if (id.isNil()) { return str("<nil>"); }
    return str(__PRETTY_FUNCTION__);
}

auto Formatter::toString(SemId<CmdAttr> id, CR<Context> ctx) -> Res {
    if (id.isNil()) { return str("<nil>"); }
    return b.line(
        {str("#+attr_"_ss + id->target + ": "_ss),
         toString(id->parameters, ctx)});
}

auto Formatter::toString(SemId<Strike> id, CR<Context> ctx) -> Res {
    if (id.isNil()) { return str("<nil>"); }
    return b.line(
        Vec<Res>::Splice(str("+"), toSubnodes(id, ctx), str("+")));
}

auto Formatter::toString(SemId<CmdArgumentList> id, CR<Context> ctx)
    -> Res {
    if (id.isNil()) { return str("<nil>"); }

    Vec<Res> result;
    for (auto const& it : id->args) {
        result.push_back(toString(it, ctx));
    }

    return b.join(result, str(" "));
}


auto Formatter::toString(SemId<CmdArguments> id, CR<Context> ctx) -> Res {
    if (id.isNil()) { return str("<nil>"); }
    Vec<Res> result;
    if (!id->positional.isNil()) {
        for (auto const& pos : id->positional->args) {
            result.push_back(toString(pos, ctx));
        }
    }

    Vec<Str> its;
    for (auto const& k : id->named.keys()) { its.push_back(k); }

    rs::sort(its, [](CR<Str> lhs, CR<Str> rhs) -> bool {
        return lhs.toBase() < rhs.toBase();
    });

    for (auto const& key : its) {
        result.push_back(toString(id->named.at(key), ctx));
    }

    return b.join(result, str(" "));
}

auto Formatter::toString(SemId<InlineMath> id, CR<Context> ctx) -> Res {
    if (id.isNil()) { return str("<nil>"); }
    if (id->subnodes.size() == 0) {
        return str("\\(\\)");
    } else {
        return b.line({str("\\("), toString(id->at(0), ctx), str("\\)")});
    }
}

auto Formatter::toString(SemId<Subtree> id, CR<Context> ctx) -> Res {
    if (id.isNil()) { return str("<nil>"); }
    Res title = b.line({});
    {
        Vec<Res> lead;
        Vec<Res> tags;

        if (id->todo) { lead.push_back(str(id->todo.value())); }
        if (id->isComment) { lead.push_back(str("COMMENT")); }
        if (id->isArchived) { tags.push_back(str("ARCHIVE")); }

        if (!id->title->subnodes.empty()) {
            lead.push_back(toString(id->title, ctx));
        }

        if (!id->tags.empty()) {
            tags.push_back(colonHashtags(this, id->tags));
        }

        if (!tags.empty()) {
            lead.push_back(b.line({
                str(":"),
                b.join(tags, str(":")),
                str(":"),
            }));
        }

        b.add_at(title, b.join(lead, str(" ")));
    }

    Res head = b.stack({title});

    if (id->scheduled) {
        b.add_at(
            head,
            b.line({str("SCHEDULED: "), toString(*id->scheduled, ctx)}));
    }

    if (id->deadline) {
        b.add_at(
            head,
            b.line({str("DEADLINE: "), toString(*id->deadline, ctx)}));
    }

    if (id->closed) {
        b.add_at(
            head, b.line({str("CLOSED: "), toString(*id->closed, ctx)}));
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
                             toString(prop.getCreated().time, ctx)}));
                    break;
                }
                case P::Kind::Unknown: {
                    b.add_at(
                        head,
                        b.line(
                            {str(":"_ss + prop.getUnknown().name
                                 + ": "_ss),
                             toString(prop.getUnknown().value, ctx)}));
                    break;
                }
                case P::Kind::Effort: {
                    b.add_at(
                        head,
                        b.line(
                            {str(":CREATED: "),
                             str(
                                 fmt("{}:{}",
                                     prop.getEffort().hours,
                                     prop.getEffort().minutes))}));
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
                        toString(tag.tag, ctx),
                        str("\""),
                        str(tag.added ? " Added" : " Removed"),
                        str(" on "),
                        toString(tag.on, ctx),
                    });

                    break;
                }

                case Log::Kind::Refile: {
                    auto const& refile = log->getRefile();
                    if (refile.desc) { desc = refile.desc; }

                    log_head = b.line({
                        str("- Refiled on "),
                        toString(refile.on, ctx),
                        str(" from "),
                        toString(refile.from, ctx),
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
                        toString(state.on, ctx),
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
                        toString(note.on, ctx),
                    });

                    break;
                }

                case Log::Kind::Clock: {
                    auto const& clock = log->getClock();

                    if (clock.to) {
                        log_head = b.line({
                            str("CLOCK: "),
                            toString(clock.from, ctx),
                            str("--"),
                            toString(clock.to.value(), ctx),
                        });
                    } else {
                        log_head = b.line({
                            str("CLOCK: "),
                            toString(clock.from, ctx),
                        });
                    }


                    break;
                }

                case Log::Kind::Priority: {
                    auto const& priority = log->getPriority();
                    switch (priority.action) {
                        case Log::Priority::Action::Added: {
                            log_head = b.line({
                                str("- Priority "),
                                str(priority.newPriority.value()),
                                str(" added on "),
                                toString(priority.on, ctx),
                            });
                            break;
                        }
                        case Log::Priority::Action::Changed: {
                            log_head = b.line({
                                str("- Priority "),
                                str(priority.newPriority.value()),
                                str(" changed from "),
                                str(priority.oldPriority.value()),
                                str(" on "),
                                toString(priority.on, ctx),
                            });
                            break;
                        }
                        case Log::Priority::Action::Removed: {
                            log_head = b.line({
                                str("- Priority "),
                                str(priority.oldPriority.value()),
                                str(" removed on "),
                                toString(priority.on, ctx),
                            });
                            break;
                        }
                    }

                    break;
                }

                default: {
                    log_head = b.line({
                        str(" -"),
                        toString(log->getUnknown().desc.value(), ctx),
                    });
                }
            }

            if (desc) {
                b.add_at(log_head, str(" \\\\"));
                CHECK(!desc.value().isNil()) << fmt1(log->getLogKind());
                b.add_at(head, log_head);
                b.add_at(
                    head,
                    b.indent(2, b.stack(toSubnodes(desc.value(), ctx))));
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
        add_subnodes(result, id.asOrg(), ctx);
    }

    return result;
}

auto Formatter::toString(SemId<DocumentOptions> id, CR<Context> ctx)
    -> Res {
    if (id.isNil()) { return str("<nil>"); }
    return str(__PRETTY_FUNCTION__);
}

auto Formatter::toString(SemId<Verbatim> id, CR<Context> ctx) -> Res {
    if (id.isNil()) { return str("<nil>"); }
    return b.line(
        Vec<Res>::Splice(str("="), toSubnodes(id, ctx), str("=")));
}

auto Formatter::toString(SemId<Quote> id, CR<Context> ctx) -> Res {
    if (id.isNil()) { return str("<nil>"); }
    return b.stack(Vec<Res>::Splice(
        str("#+begin_quote"), toSubnodes(id, ctx), str("#+end_quote")));
}

auto Formatter::toString(SemId<CommentBlock> id, CR<Context> ctx) -> Res {
    if (id.isNil()) { return str("<nil>"); }
    return b.stack(Vec<Res>::Splice(
        str("#+begin_comment"),
        toSubnodes(id, ctx),
        str("#+end_comment")));
}

auto Formatter::toString(SemId<Verse> id, CR<Context> ctx) -> Res {
    if (id.isNil()) { return str("<nil>"); }
    return b.stack(Vec<Res>::Splice(
        str("#+begin_verse"), toSubnodes(id, ctx), str("#+end_verse")));
}


auto Formatter::toString(SemId<Include> id, CR<Context> ctx) -> Res {
    if (id.isNil()) { return str("<nil>"); }
    return str(__PRETTY_FUNCTION__);
}

auto Formatter::toString(SemId<Punctuation> id, CR<Context> ctx) -> Res {
    if (id.isNil()) { return str("<nil>"); }
    return str(id->text);
}

auto Formatter::toString(SemId<FileTarget> id, CR<Context> ctx) -> Res {
    if (id.isNil()) { return str("<nil>"); }
    return str(__PRETTY_FUNCTION__);
}

template <typename T>
Vec<T> OptVec(CR<Opt<T>> value) {
    if (value) {
        return Vec<T>{*value};
    } else {
        return Vec<T>{};
    }
}

auto Formatter::toString(SemId<Export> id, CR<Context> ctx) -> Res {
    if (id.isNil()) { return str("<nil>"); }
    Res head = b.line();
    b.add_at(head, str("#+begin_export " + id->exporter));
    if (id->parameters) {
        b.add_at(head, str(" "));
        b.add_at(head, toString(id->parameters.value(), ctx));
    }

    if (id->placement) {
        b.add_at(head, str(":placement " + id->placement.value()));
    }

    return b.stack(
        Vec<Res>::Splice(head, str(id->content), str("#+end_export")));
}

auto Formatter::toString(SemId<Example> id, CR<Context> ctx) -> Res {
    if (id.isNil()) { return str("<nil>"); }
    return b.stack(Vec<Res>::Splice(
        str("#+begin_example"),
        toSubnodes(id, ctx),
        str("#+end_example")));
}

auto Formatter::toString(SemId<ColonExample> id, CR<Context> ctx) -> Res {
    if (id.isNil()) { return str("<nil>"); }
    return b.stack(Vec<Res>::Splice(
        id->subnodes | rv::transform([&](OrgArg sub) {
            return b.line({str(": "), toString(sub, ctx)});
        })));
}


auto Formatter::toString(SemId<Paragraph> id, CR<Context> ctx) -> Res {
    if (id.isNil()) { return str("<nil>"); }
    Res     result = b.stack();
    Context ctx2   = ctx;
    ctx2.isInline  = true;
    for (auto const& line :
         id->subnodes | rv::split_when([](sem::SemId<sem::Org> id) {
             return id->getKind() == OrgSemKind::Newline;
         })) {
        Res line_out = b.line();
        for (auto const& item : line) {
            b.add_at(line_out, toString(item, ctx2));
        }
        b.add_at(result, line_out);
    }
    return result;
}

auto Formatter::toString(SemId<AnnotatedParagraph> id, CR<Context> ctx)
    -> Res {
    if (id.isNil()) { return str("<nil>"); }
    Res     result = b.stack();
    bool    first  = true;
    Context ctx2   = ctx;
    ctx2.isInline  = true;
    for (auto const& line :
         id->subnodes | rv::split_when([](sem::SemId<sem::Org> id) {
             return id->getKind() == OrgSemKind::Newline;
         })) {
        Res line_out = b.line();
        if (first) {
            switch (id->getAnnotationKind()) {
                case sem::AnnotatedParagraph::AnnotationKind::Admonition: {
                    b.add_at(
                        line_out, toString(id->getAdmonition().name, ctx));
                    break;
                }
                case sem::AnnotatedParagraph::AnnotationKind::Timestamp: {
                    b.add_at(
                        line_out, toString(id->getTimestamp().time, ctx));
                    break;
                }
                case sem::AnnotatedParagraph::AnnotationKind::Footnote: {
                    b.add_at(
                        line_out,
                        str(fmt("[fn:{}]", id->getFootnote().name)));
                    break;
                }
                case sem::AnnotatedParagraph::AnnotationKind::None: {
                }
            }

            if (id->getAnnotationKind()
                != sem::AnnotatedParagraph::AnnotationKind::None) {
                b.add_at(line_out, str(" "));
            }
            first = false;
        }


        for (auto const& item : line) {
            b.add_at(line_out, toString(item, ctx2));
        }
        b.add_at(result, line_out);
    }


    return result;
}

auto Formatter::toString(SemId<Underline> id, CR<Context> ctx) -> Res {
    if (id.isNil()) { return str("<nil>"); }
    return b.line(
        Vec<Res>::Splice(str("_"), toSubnodes(id, ctx), str("_")));
}

auto Formatter::toString(SemId<ParseError> id, CR<Context> ctx) -> Res {
    if (id.isNil()) { return str("<nil>"); }
    return str(__PRETTY_FUNCTION__);
}
