#include <haxorg/sem/SemOrgFormat.hpp>
#include <hstd/stdlib/algorithms.hpp>

using namespace org::sem;
using namespace hstd;
using namespace org::algo;

#pragma clang diagnostic error "-Wswitch"


namespace {
long GetTimeDelta(CR<UserTime> from, CR<UserTime> to) {
    auto from_utc = absl::ToCivilSecond(
        from.time, from.zone ? *from.zone : absl::TimeZone{});
    auto to_utc = absl::ToCivilSecond(
        to.time, to.zone ? *to.zone : absl::TimeZone{});
    return to_utc - from_utc;
}

std::string FormatTimeDelta(long delta_seconds) {
    long delta   = delta_seconds / 60;
    long hours   = delta / 60;
    long minutes = delta % 60;
    return std::format("{}:{:02}", hours, minutes);
}

std::string FormatPath(org::sem::SubtreePath const& path) {
    return join("/", path.path);
}

} // namespace

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

void Formatter::add(Res id, Res other) {
    auto const& bl = b.at(other);
    if (bl.size() == 0 && (bl.isLine() || bl.isStack())) {
        return;
    } else {
        b.add_at(id, other);
    }
}

void Formatter::add_subnodes(Res result, SemId<Org> id, CR<Context> ctx) {
    for (auto const& it : id->subnodes) { add(result, toString(it, ctx)); }
}

auto Formatter::toString(SemId<RadioTarget> id, CR<Context> ctx) -> Res {
    if (id.isNil()) { return str("<nil>"); }
    return b.line(Vec<Res>::Splice(
        str("<<<"),
        rv::transform(
            id->words | rv::intersperse(" ") | rv::join,
            [&](CR<Str> word) { return this->str(word.toBase()); })
            | rs::to<Vec>(),
        str(">>>")));
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
    Vec<Res> parameters;

    for (auto const& it : id->attrs.positional.items) {
        parameters.push_back(str(it.getString()));
    }

    for (auto const& key : sorted(id->attrs.named.keys())) {
        for (auto const& it : id->attrs.named.at(key).items) {
            parameters.push_back(
                str(fmt("{}={}", it.name.value(), it.getString())));
        }
    }

    if (parameters.empty()) {
        return str(Str("{{{") + id->name + Str("}}}"));
    } else {
        return b.line(Vec<Res>::Splice(
            str(Str("{{{") + id->name + Str("(")),
            b.join(parameters, str(", ")),
            str(")}}}") //
            ));
    }
}

std::string nestedHashtag(org::sem::HashTagText const& hash) {
    if (hash.subtags.empty()) {
        return hash.head;
    } else if (hash.subtags.size() == 1) {
        return hash.head + "##" + nestedHashtag(hash.subtags.at(0));
    } else {
        return hash.head + "##["
             + (hash.subtags                   //
                | rv::transform(nestedHashtag) //
                | rv::intersperse(",")         //
                | rv::join                     //
                | rs::to<std::string>()        //
                )
             + "]";
    }
}


auto Formatter::toString(sem::HashTagText const& hash, CR<Context> ctx)
    -> Res {
    return str(nestedHashtag(hash));
}

Formatter::Res colonHashtags(Formatter* f, CVec<SemId<HashTag>> tags) {
    return f->b.join(
        Vec<Formatter::Res>::Splice(
            tags
            | rv::transform([&](CR<SemId<HashTag>> tag) -> Formatter::Res {
                  return f->str(nestedHashtag(tag->text));
              })),
        f->str(":"));
}

auto Formatter::toString(SemId<Document> id, CR<Context> ctx) -> Res {
    if (id.isNil()) { return str("<nil>"); }
    Res result = b.stack();

    bool hadDocumentProperties = false;

    if (id->title) {
        add(result, b.line({str("#+title: "), toString(*id->title, ctx)}));
        hadDocumentProperties = true;
    }

    using Visibility = InitialSubtreeVisibility;
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

        add(result, b.line({str("#+startup: "), str(res)}));
    }

    if (id->options && id->options->columns) {
        Vec<Res> buf;
        buf.push_back(str("#+columns:"));

        for (auto const& col : id->options->columns.value().columns) {
            Str res;
            res += "%";
            if (col.width) { res += fmt1(col.width.value()); }

            if (col.property) { res += col.property.value(); }

            if (col.propertyTitle) {
                res += fmt("({})", col.propertyTitle.value());
            }
            using type = sem::ColumnView::Summary;

            if (col.summary) {
                auto const& s = col.summary.value();
                res += "[";
                if (s.isCheckboxAggregate()) {
                    auto const& check = s.getCheckboxAggregate();
                    switch (check.kind) {
                        case type::CheckboxAggregate::Kind::
                            AggregateFractionRec: {
                            res += "x/";
                            break;
                        }
                        case type::CheckboxAggregate::Kind::
                            AggregatePercentRec: {
                            res += "x%";
                            break;
                        }
                        case type::CheckboxAggregate::Kind::IfAllNested: {
                            res += "x";
                            break;
                        }
                    }
                } else {
                    auto const& math = s.getMathAggregate();
                    switch (math.kind) {
                        case type::MathAggregate::Kind::Max: {
                            res += "min";
                            break;
                        }
                        case type::MathAggregate::Kind::LowHighEst: {
                            res += "est+";
                            break;
                        }
                        case type::MathAggregate::Kind::Mean: {
                            res += "avg";
                            break;
                        }
                        case type::MathAggregate::Kind::Min: {
                            res += "min";
                            break;
                        }
                        case type::MathAggregate::Kind::Sum: {
                            res += "sum";
                            break;
                        }
                    }
                }
                res += "]";
            }

            buf.push_back(str(res));
        }

        add(result, b.join(buf, str(" ")));
    }

    if (!id->filetags.empty()) {
        add(result,
            b.line(
                {str("#+filetags: :"),
                 colonHashtags(this, id->filetags),
                 str(":")}));
        hadDocumentProperties = true;
    }

    if (id->author) {
        add(result,
            b.line({str("#+author: "), toString(*id->author, ctx)}));
        hadDocumentProperties = true;
    }

    if (!id->options.isNil()) {
        for (auto const& prop : id->options->properties) {
            using P = sem::NamedProperty;
            switch (prop.getKind()) {
                case P::Kind::CustomRaw: {
                    add(result,
                        b.line({
                            str("#+property: "),
                            str(prop.getCustomRaw().name),
                            str(" "),
                            str(prop.getCustomRaw().value),
                        }));
                    break;
                }
                case P::Kind::CustomArgs: {
                    Vec<Res> tmp;
                    tmp.push_back(str("#+property: "));
                    tmp.push_back(str(prop.getCustomArgs().name));
                    for (auto const& it :
                         prop.getCustomArgs().attrs.getFlatArgs()) {
                        tmp.push_back(str(" "));
                        tmp.push_back(toString(it, ctx));
                    }
                    add(result, b.line(tmp));
                    break;
                }
                case P::Kind::ExportLatexHeader: {
                    add(result,
                        str(
                            fmt("#+latex_header: {}",
                                prop.getExportLatexHeader().header)));
                    break;
                }
                case P::Kind::ExportLatexClass: {
                    add(result,
                        str(
                            fmt("#+latex_header: {}",
                                prop.getExportLatexClass().latexClass)));
                    break;
                }
                case P::Kind::ExportLatexClassOptions: {
                    add(result,
                        str(fmt(
                            "#+latex_class_options: {}",
                            prop.getExportLatexClassOptions().options.at(
                                0))));
                    break;
                }
                default: {
                    throw std::logic_error(
                        fmt("Unexpected document-level property: {}",
                            prop.getKind()));
                }
            }
        }
    }

    if (hadDocumentProperties) { add(result, str("")); }

    for (auto const& sub : id->subnodes) {
        add(result, toString(sub, ctx));
    }

    if (b.at(result).size() == 0) { add(result, str("")); }

    return result;
}

auto Formatter::toString(SemId<RawText> id, CR<Context> ctx) -> Res {
    if (id.isNil()) { return str("<nil>"); }
    return str(id->text);
}

auto Formatter::toString(SemId<InlineFootnote> id, CR<Context> ctx)
    -> Res {
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

auto Formatter::toString(sem::AttrValue const& id, CR<Context> ctx)
    -> Res {
    Str value = id.getString().replaceAll("\"", "\\\"");

    if (id.isQuoted) { value = escape_for_write(value, true); }

    auto varname = id.varname.has_value()
                     ? Str{fmt("{}={}", id.varname.value(), value)}
                     : value;


    if (id.name) {
        return str(fmt(":{} {}", id.name.value(), varname));
    } else {
        return str(varname);
    }
}

auto Formatter::toString(SemId<BlockCodeEvalResult> id, CR<Context> ctx)
    -> Res {
    if (id.isNil()) { return str("<nil>"); }
    return str("TODO");
}

auto Formatter::toString(SemId<BlockCode> id, CR<Context> ctx) -> Res {
    if (id.isNil()) { return str("<nil>"); }
    bool isInline = ctx.isInline;

    auto     result = isInline ? b.line() : b.stack();
    Vec<Res> parameters;
    if (!id->attrs.isEmpty()) {
        parameters.push_back(toString(id->attrs, ctx));
    }

    auto head = isInline ? b.line({str("src_")})
                         : b.line({str("#+begin_src")});

    if (id->lang) { add(head, str((isInline ? "" : " ") + *id->lang)); }

    if (!parameters.empty()) {
        if (isInline) {
            add(head, str("["));
        } else {
            add(head, str(" "));
        }

        add(head, b.join(parameters, str(" ")));

        if (isInline) { add(head, str("]")); }
    }

    if (id->exports != BlockCodeExports::Both) { // 'both' is the default
        add(head, str(":exports "));
        switch (id->exports) {
            case BlockCodeExports::Both: {
                add(head, str("both"));
                break;
            }
            case BlockCodeExports::Code: {
                add(head, str("code"));
                break;
            }
            case BlockCodeExports::Results: {
                add(head, str("results"));
                break;
            }
            case BlockCodeExports::None: {
                add(head, str("results"));
                break;
            }
        }
    }

    add(result, head);
    if (isInline) { add(result, str("{")); }
    for (auto const& it : id->lines) {
        auto line = b.line();
        for (auto const& part : it.parts) {
            switch (part.getKind()) {
                case BlockCodeLine::Part::Kind::Raw: {
                    add(line, str(part.getRaw().code));
                    break;
                }
                case BlockCodeLine::Part::Kind::Callout: {
                    add(line, str(part.getCallout().name));
                    break;
                }
                case BlockCodeLine::Part::Kind::Tangle: {
                    add(line, str(part.getTangle().target));
                    break;
                }
            }
        }

        if (it.parts.empty()) { add(line, str("")); }

        add(result, line);
    }

    if (isInline) {
        add(result, str("}"));
    } else {
        add(result, str("#+end_src"));
    }

    auto out = stackAttached(result, id.as<sem::Stmt>(), ctx);
    return out;
}

auto Formatter::toString(SemId<CmdTblfm> id, CR<Context> ctx) -> Res {
    if (id.isNil()) { return str("<nil>"); }
    return str(__PRETTY_FUNCTION__);
}

auto Formatter::toString(SemId<List> id, CR<Context> ctx) -> Res {
    if (id.isNil()) { return str("<nil>"); }
    Res result = b.stack();
    for (auto const& it : id->subnodes) { add(result, toString(it, ctx)); }

    return stackAttached(result, id.as<sem::Stmt>(), ctx);
}

auto Formatter::toString(SemId<SubtreeLog> id, CR<Context> ctx) -> Res {
    if (id.isNil()) { return str("<nil>"); }
    return str(__PRETTY_FUNCTION__);
}

auto Formatter::toString(SemId<Empty> id, CR<Context> ctx) -> Res {
    if (id.isNil()) { return str("<nil>"); }
    return str("");
}

auto Formatter::toString(SemId<None> id, CR<Context> ctx) -> Res {
    if (id.isNil()) { return str("<nil>"); }
    return str("");
}

auto Formatter::toString(SemId<Newline> id, CR<Context> ctx) -> Res {
    if (id.isNil()) { return str("<nil>"); }
    auto result = b.stack();

    for (int i = 1; i < id->text.size(); ++i) { add(result, str("")); }

    return result;
}

auto Formatter::toString(SemId<Monospace> id, CR<Context> ctx) -> Res {
    if (id.isNil()) { return str("<nil>"); }
    return b.line(
        Vec<Res>::Splice(str("~"), toSubnodes(id, ctx), str("~")));
}

auto Formatter::toString(sem::LinkTarget const& t, CR<Context> ctx)
    -> Res {

    Res head = str("");
    switch (t.getKind()) {
        case LinkTarget::Kind::Person: {
            head = str("person:" + t.getPerson().name);
            break;
        }

        case LinkTarget::Kind::Attachment: {
            head = str("attachment:" + t.getAttachment().file);
            break;
        }

        case LinkTarget::Kind::File: {
            head = str("file:" + t.getFile().file);
            break;
        }

        case LinkTarget::Kind::Id: {
            head = str("id:" + t.getId().text);
            break;
        }

        case LinkTarget::Kind::Internal: {
            head = str(t.getInternal().target);
            break;
        }

        case LinkTarget::Kind::Raw: {
            head = str(t.getRaw().text);
            break;
        }

        case LinkTarget::Kind::CustomId: {
            head = str("#" + t.getCustomId().text);
            break;
        }

        case LinkTarget::Kind::SubtreeTitle: {
            head = str("*" + FormatPath(t.getSubtreeTitle().title));
            break;
        }

        case LinkTarget::Kind::Footnote: {
            head = str("fn:"_ss + t.getFootnote().target);
            break;
        }

        case LinkTarget::Kind::UserProtocol: {
            head = str(
                t.getUserProtocol().protocol + ":"_ss
                + t.getUserProtocol().target);
        }
    }

    return head;
}

auto Formatter::toString(SemId<Link> id, CR<Context> ctx) -> Res {
    if (id.isNil()) { return str("<nil>"); }
    auto const& t = id->target;
    if (t.getKind() == LinkTarget::Kind::Raw && !id->description) {
        return str(t.getRaw().text);
    } else {
        Res head = toString(t, ctx);
        if (t.getKind() == LinkTarget::Kind::Footnote
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
}

auto Formatter::toString(SemId<Symbol> id, CR<Context> ctx) -> Res {
    if (id.isNil()) { return str("<nil>"); }
    Res result = b.line({str("\\" + id->name)});
    for (auto const& [key, value] : id->parameters) {
        if (key) {
            add(result,
                b.line({
                    str("["),
                    str(*key),
                    str("="),
                    str(value),
                    str("]"),
                }));
        } else {
            add(result, b.line({str("["), str(value), str("]")}));
        }
    }

    for (auto const& it : id->positional) {
        add(result, b.line({str("{"), toString(it, ctx), str("}")}));
    }

    return result;
}

auto Formatter::toString(SemId<CmdCaption> id, CR<Context> ctx) -> Res {
    if (id.isNil()) { return str("<nil>"); }
    return b.line({str("#+caption: "), toString(id->text, ctx)});
}

auto Formatter::toString(SemId<CmdColumns> id, CR<Context> ctx) -> Res {
    if (id.isNil()) { return str("<nil>"); }
    return b.line({str("#+columns: ")});
}

auto Formatter::toString(SemId<CmdCall> id, CR<Context> ctx) -> Res {
    if (id.isNil()) { return str("<nil>"); }
    auto res = b.line({str("#+call: ")});
    if (!id->insideHeaderAttrs.isEmpty()) {
        b.add_at(res, str("["));
        b.add_at(res, toString(id->insideHeaderAttrs, ctx));
        b.add_at(res, str("]"));
    }

    if (!id->callAttrs.isEmpty()) {
        b.add_at(res, str("("));

        b.add_at(res, str(")"));
    }

    if (!id->insideHeaderAttrs.isEmpty()) {
        b.add_at(res, str(" "));
        b.add_at(res, toString(id->insideHeaderAttrs, ctx));
    }

    return res;
}

auto Formatter::toString(SemId<CmdCustomRaw> id, CR<Context> ctx) -> Res {
    if (id.isNil()) { return str("<nil>"); }
    return b.line({str(fmt("#+{}: {}", id->name, id->text))});
}

auto Formatter::toString(SemId<CmdCustomArgs> id, CR<Context> ctx) -> Res {
    if (id.isNil()) { return str("<nil>"); }
    return b.line({str(fmt("#+{}:", id->name)), toString(id->attrs, ctx)});
}

auto Formatter::toString(SemId<CmdCustomText> id, CR<Context> ctx) -> Res {
    if (id.isNil()) { return str("<nil>"); }
    return b.line({str(fmt("#+{}: ", id->name)), toString(id->text, ctx)});
}

auto Formatter::toString(SemId<CmdName> id, CR<Context> ctx) -> Res {
    if (id.isNil()) { return str("<nil>"); }
    return b.line({str("#+name: " + id->name)});
}

auto Formatter::toString(SemId<ErrorGroup> id, CR<Context> ctx) -> Res {
    if (id.isNil()) { return str("<nil>"); }
    auto result = b.line({});
    for (auto const& sub : id->diagnostics) {
        add(result, toString(sub, ctx));
    }
    return result;
}

auto Formatter::toString(SemId<ErrorItem> id, CR<Context> ctx) -> Res {
    if (id.isNil()) { return str("<nil>"); }
    return b.line({str(id->message)});
}

auto Formatter::toString(SemId<Call> id, CR<Context> ctx) -> Res {
    if (id.isNil()) { return str("<nil>"); }
    auto result = b.line({
        str("#+call: "),
        str(id->name),
    });

    Vec<Res> parameters;


    for (auto const& it : id->attrs.positional.items) {
        if (it.getString().contains(",")) {
            parameters.push_back(str(fmt("={}=", it.getString())));
        } else {
            parameters.push_back(str(it.getString()));
        }
    }

    for (auto const& key : sorted(id->attrs.named.keys())) {
        for (auto const& it : id->attrs.named.at(key).items) {
            parameters.push_back(
                str(fmt("{}={}", it.name.value(), it.getString())));
        }
    }

    add(result, str("("));
    if (!parameters.empty()) {
        add(result, b.join(parameters, str(", ")));
    }
    add(result, str(")"));

    return result;
}

auto Formatter::toString(SemId<DocumentGroup> id, CR<Context> ctx) -> Res {
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
    return str("#" + nestedHashtag(id->text));
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

    add(result, str(id->isActive ? "<" : "["));
    if (id->isStatic()) {
        UserTime const& time = id->getStatic().time;
        add(result, str(time.format(UserTime::Format::OrgFormat)));
    } else {
        add(result, str(id->getDynamic().expr));
    }
    add(result, str(id->isActive ? ">" : "]"));

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


auto Formatter::toString(sem::SubtreeCompletion const& id, CR<Context> ctx)
    -> Res {
    if (id.isPercent) {
        return str(fmt("[{}%]", id.done));
    } else {
        return str(fmt("[{}/{}]", id.done, id.full));
    }
}

auto Formatter::toString(SemId<BlockCenter> id, CR<Context> ctx) -> Res {
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
        Res head = b.line();
        add(head, toString(*id->header, ctx));
        add(head, str(" :: "));
        if (id->subnodes.has(0)) {
            add(head, toString(id->at(0), ctx));
            add(body, head);
            add(body, str(""));

            for (auto const& sub : id->subnodes | rv::drop(1)) {
                add(body, toString(sub, ctx));
            }
        }
    } else {
        for (auto const& sub : id->subnodes) {
            add(body, toString(sub, ctx));
        }
    }

    Str checkbox;
    switch (id->checkbox) {
        case ListItem::Checkbox::Empty: checkbox = "[ ] "; break;
        case ListItem::Checkbox::Done: checkbox = "[x] "; break;
        case ListItem::Checkbox::Partial: checkbox = "[-] "; break;
        case ListItem::Checkbox::None: checkbox = ""; break;
    }


    return b.line({
        str((id->bullet ? id->bullet.value() + " "_ss : "- ") + checkbox),
        body,
    });
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
    if (id->isBlock) {
        add(result,
            b.line({
                str("#+begin_table"),
                toString(id->attrs, ctx),
            }));
    }

    for (auto const& in_row : id->rows) {
        if (in_row->isBlock) {
            Res row = b.stack({b.line({
                str("#+row:"),
                toString(in_row->attrs, ctx),
            })});

            for (auto const& in_cell : in_row->cells) {
                if (in_cell->isBlock) {
                    Res cell = b.stack({b.line({
                        str("#+cell:"),
                        toString(in_cell->attrs, ctx),
                    })});
                    for (auto const& item : in_cell) {
                        add(cell, toString(item, ctx));
                    }
                    add(row, cell);
                } else {
                    Res cell = b.line({str("| ")});
                    for (auto const& item : in_cell) {
                        add(cell, toString(item, ctx));
                    }
                    add(row, cell);
                }
            }
            add(result, row);
        } else {
            Res row = b.line({str("| ")});
            for (auto const& in_cell : in_row->cells) {
                Res cell = b.line();
                for (auto const& item : in_cell->subnodes) {
                    add(cell, str(" "));
                    add(cell, toString(item, ctx));
                    add(cell, str(" "));
                }

                add(row, cell);
                add(row, str("|"));
            }


            add(result, row);
        }
    }

    if (id->isBlock) { add(result, str("#+end_table")); }

    return stackAttached(result, id.as<sem::Stmt>(), ctx);
}

auto Formatter::toString(SemId<BlockAdmonition> id, CR<Context> ctx)
    -> Res {
    if (id.isNil()) { return str("<nil>"); }
    return str(__PRETTY_FUNCTION__);
}

auto Formatter::toString(SemId<CmdAttr> id, CR<Context> ctx) -> Res {
    if (id.isNil()) { return str("<nil>"); }
    return b.line({
        str("#+attr_"_ss + id->target + ": "_ss),
        toString(id->attrs, ctx),
    });
}

auto Formatter::toString(SemId<Strike> id, CR<Context> ctx) -> Res {
    if (id.isNil()) { return str("<nil>"); }
    return b.line(
        Vec<Res>::Splice(str("+"), toSubnodes(id, ctx), str("+")));
}


auto Formatter::toString(const AttrGroup& id, CR<Context> ctx) -> Res {
    Vec<Res> result;
    for (auto const& pos : id.positional.items) {
        result.push_back(toString(pos, ctx));
    }

    Vec<Str> its;
    for (auto const& k : id.named.keys()) { its.push_back(k); }

    rs::sort(its, [](CR<Str> lhs, CR<Str> rhs) -> bool {
        return lhs.toBase() < rhs.toBase();
    });

    for (auto const& key : its) {
        result.push_back(toString(id.named.at(key), ctx));
    }

    if (result.empty()) {
        return str("");
    } else {
        return b.join(result, str(" "));
    }
}

auto Formatter::toString(SemId<Latex> id, CR<Context> ctx) -> Res {
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
        if (id->priority) {
            lead.push_back(str(fmt("[#{}]", id->priority.value())));
        }
        if (id->isArchived) { tags.push_back(str("ARCHIVE")); }

        if (!id->title->subnodes.empty()) {
            lead.push_back(toString(id->title, ctx));
        }

        if (id->completion) {
            lead.push_back(toString(id->completion.value(), ctx));
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


        add(title, b.join(lead, str(" ")));
    }

    Res head = b.stack({title});

    if (id->scheduled) {
        add(head,
            b.line({str("SCHEDULED: "), toString(*id->scheduled, ctx)}));
    }

    if (id->deadline) {
        add(head,
            b.line({str("DEADLINE: "), toString(*id->deadline, ctx)}));
    }

    if (id->closed) {
        add(head, b.line({str("CLOSED: "), toString(*id->closed, ctx)}));
    }

    if (!id->properties.empty() || id->treeId) {
        add(head, str(":PROPERTIES:"));
        if (id->treeId) { add(head, str(fmt(":ID: {}", *id->treeId))); }

        for (auto const& prop : id->properties) {
            using P = sem::NamedProperty;
            switch (prop.getKind()) {
                case P::Kind::CustomSubtreeFlags: {
                    add(head,
                        b.line({
                            str(
                                fmt(":prop_args:{}:",
                                    prop.getCustomSubtreeFlags().name)),
                            toString(
                                prop.getCustomSubtreeFlags().value, ctx),
                        }));
                    break;
                }
                case P::Kind::CustomSubtreeJson: {
                    add(head,
                        str(
                            fmt(":prop_json:{}: {}",
                                prop.getCustomSubtreeJson().name,
                                prop.getCustomSubtreeJson()
                                    .value.getRef()
                                    .dump())));
                    break;
                }
                case P::Kind::ExportLatexCompiler: {
                    add(head,
                        str(
                            fmt(":latex_compiler: {}",
                                prop.getExportLatexCompiler().compiler)));
                    break;
                }
                case P::Kind::ExportOptions: {
                    add(head,
                        str(
                            fmt(":export_options:{}: {}",
                                prop.getExportOptions().backend,
                                prop.getExportOptions().values
                                    | rv::transform(
                                        [](Pair<Str, Str> const& pair) {
                                            return fmt(
                                                "{}:{}",
                                                pair.first,
                                                pair.second);
                                        })
                                    | rv::intersperse(" ") //
                                    | rv::join             //
                                    | rs::to<std::string>())));
                    break;
                }
                case P::Kind::ExportLatexClassOptions: {
                    add(head,
                        str(fmt(
                            ":latex_class_options: {}",
                            prop.getExportLatexClassOptions().options)));
                    break;
                }
                case P::Kind::CookieData: {
                    add(head,
                        str(fmt(
                            ":cookie: {}{}",
                            prop.getCookieData().source,
                            prop.getCookieData().isRecursive ? " recursive"
                                                             : "")));
                    break;
                }
                case P::Kind::ExportLatexHeader: {
                    add(head,
                        str(
                            fmt(":latex_header: {}",
                                prop.getExportLatexHeader().header)));
                    break;
                }
                case P::Kind::ExportLatexClass: {
                    add(head,
                        str(
                            fmt(":latex_class: {}",
                                prop.getExportLatexClass().latexClass)));
                    break;
                }
                case P::Kind::Trigger: {
                    add(head, str(fmt(":trigger:")));
                    break;
                }
                case P::Kind::ArchiveTodo: {
                    add(head,
                        str(
                            fmt(":archive_todo: {}",
                                prop.getArchiveTodo().todo)));
                    break;
                }
                case P::Kind::ArchiveTarget: {
                    add(head,
                        str(fmt(
                            ":archive: {}::* {}",
                            prop.getArchiveTarget().pattern,
                            FormatPath(prop.getArchiveTarget().path))));
                    break;
                }
                case P::Kind::ArchiveOlpath: {
                    add(head,
                        str(fmt(
                            ":archive_olpath: {}",
                            FormatPath(prop.getArchiveOlpath().path))));
                    break;
                }
                case P::Kind::ArchiveTime: {
                    add(head,
                        str(
                            fmt(":archive_time: [{}]",
                                prop.getArchiveTime().time.format(
                                    UserTime::Format::OrgFormat))));
                    break;
                }
                case P::Kind::Ordered: {
                    add(head,
                        str(fmt(
                            ":ordered: {}",
                            prop.getOrdered().isOrdered ? "t" : "nil")));
                    break;
                }
                case P::Kind::Nonblocking: {
                    add(head,
                        str(fmt(
                            ":nonblocking: {}",
                            prop.getNonblocking().isBlocking ? "t"
                                                             : "nil")));
                    break;
                }
                case P::Kind::HashtagDef: {
                    add(head,
                        str(fmt(
                            ":hashtag_def: {}",
                            nestedHashtag(prop.getHashtagDef().hashtag))));
                    break;
                }
                case P::Kind::CustomArgs: {
                    auto const& ca   = prop.getCustomArgs();
                    auto        line = b.line();
                    add(line,
                        str(
                            fmt(":{}:{}{} ",
                                ca.name,
                                ca.sub.value_or(""),
                                ca.sub ? ":" : "")));

                    add(line, toString(ca.attrs, ctx));
                    add(head, line);
                    break;
                }
                case P::Kind::RadioId: {
                    add(head,
                        str(
                            fmt(":radio_id: {}",
                                join(" ", prop.getRadioId().words))));
                    break;
                }
                case P::Kind::Unnumbered: {
                    add(head, str(fmt(":unnumbered:")));
                    break;
                }
                case P::Kind::Blocker: {
                    add(head,
                        str(fmt(
                            ":blocker: {}", prop.getBlocker().blockers)));
                    break;
                }
                case P::Kind::ArchiveCategory: {
                    add(head,
                        str(
                            fmt(":archive_category: {}",
                                prop.getArchiveCategory().category)));
                    break;
                }
                case P::Kind::Created: {
                    add(head,
                        b.line({
                            str(":CREATED: ["),
                            str(prop.getCreated().time.format(
                                UserTime::Format::OrgFormat)),
                            str("]"),
                        }));
                    break;
                }
                case P::Kind::CustomRaw: {
                    add(head,
                        b.line({
                            str(":"_ss + prop.getCustomRaw().name
                                + ": "_ss),
                            str(prop.getCustomRaw().value),
                        }));
                    break;
                }
                case P::Kind::Effort: {
                    add(head,
                        b.line(
                            {str(":EFFORT: "),
                             str(
                                 fmt("{}:{}",
                                     prop.getEffort().hours,
                                     prop.getEffort().minutes))}));
                    break;
                }
                case P::Kind::Visibility: {
                    add(head,
                        str(
                            fmt(":visibility: {}",
                                prop.getVisibility().level)));
                    break;
                }
                case P::Kind::ArchiveFile: {
                    add(head,
                        str(
                            fmt(":archive_file: {}",
                                prop.getArchiveFile().file)));
                    break;
                }
            }
        }

        add(head, str(":END:"));
    }

    if (!id->logbook.empty()) {
        add(head, str(":LOGBOOK:"));
        for (auto const& log : id->logbook) {
            using Log    = sem::SubtreeLogHead;
            Res log_head = str("");
            switch (log->head.getLogKind()) {
                case Log::Kind::Tag: {
                    auto const& tag = log->head.getTag();

                    log_head = b.line({
                        str("- Tag \"#"),
                        toString(tag.tag, ctx),
                        str("\""),
                        str(tag.added ? " Added" : " Removed"),
                        str(" on "),
                        toString(tag.on, ctx),
                    });

                    break;
                }

                case Log::Kind::Refile: {
                    auto const& refile = log->head.getRefile();

                    log_head = b.line({
                        str("- Refiled on "),
                        toString(refile.on, ctx),
                        str(" from [["),
                        toString(refile.from, ctx),
                        str("]]"),
                    });

                    break;
                }

                case Log::Kind::State: {
                    auto const& state = log->head.getState();

                    log_head = b.line({
                        str(
                            fmt("- State \"{}\" from \"{}\" ",
                                state.to,
                                state.from)),
                        toString(state.on, ctx),
                    });

                    break;
                }

                case Log::Kind::Note: {
                    auto const& note = log->head.getNote();
                    log_head         = b.line({
                        str("- Note taken on "),
                        toString(note.on, ctx),
                    });

                    break;
                }

                case Log::Kind::Clock: {
                    auto const& clock = log->head.getClock();

                    if (clock.to) {
                        log_head = b.line({
                            str("CLOCK: "),
                            toString(clock.from, ctx),
                            str("--"),
                            toString(clock.to.value(), ctx),
                            str(
                                fmt(" => {}",
                                    FormatTimeDelta(GetTimeDelta(
                                        clock.from, clock.to.value())))),
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
                    auto const& priority = log->head.getPriority();
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
                        str("- "),
                        toString(log->desc.value(), ctx),
                    });
                }
            }

            if (log->desc) {
                add(log_head, str(" \\\\"));
                CHECK(!log->desc.value().isNil())
                    << fmt1(log->head.getLogKind());
                add(head, log_head);
                add(head,
                    b.indent(
                        2,
                        b.stack(
                            toSubnodes(log->desc.value().asOrg(), ctx))));
            } else {
                add(head, log_head);
            }
        }
        add(head, str(":END:"));
    }

    Res result = b.stack();

    add(result,
        b.line({str(std::string(id->level, '*')), str(" "), head}));

    if (!id->subnodes.empty()) {
        add(result, str(""));
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

auto Formatter::toString(SemId<BlockQuote> id, CR<Context> ctx) -> Res {
    if (id.isNil()) { return str("<nil>"); }
    return stackAttached(
        b.stack(Vec<Res>::Splice(
            b.line({str("#+begin_quote"), toString(id->attrs, ctx)}),
            toSubnodes(id, ctx),
            str("#+end_quote"))),
        id.as<sem::Stmt>(),
        ctx);
}

auto Formatter::toString(SemId<BlockComment> id, CR<Context> ctx) -> Res {
    if (id.isNil()) { return str("<nil>"); }
    return b.stack(Vec<Res>::Splice(
        str("#+begin_comment"),
        toSubnodes(id, ctx),
        str("#+end_comment")));
}

auto Formatter::toString(SemId<BlockVerse> id, CR<Context> ctx) -> Res {
    if (id.isNil()) { return str("<nil>"); }
    return b.stack(Vec<Res>::Splice(
        str("#+begin_verse"), toSubnodes(id, ctx), str("#+end_verse")));
}


auto Formatter::toString(SemId<CmdInclude> id, CR<Context> ctx) -> Res {
    if (id.isNil()) { return str("<nil>"); }
    return str(__PRETTY_FUNCTION__);
}

auto Formatter::toString(SemId<File> id, CR<Context> ctx) -> Res {
    if (id.isNil()) { return str("<nil>"); }
    return str(__PRETTY_FUNCTION__);
}

auto Formatter::toString(SemId<Directory> id, CR<Context> ctx) -> Res {
    if (id.isNil()) { return str("<nil>"); }
    return str(__PRETTY_FUNCTION__);
}

auto Formatter::toString(SemId<Symlink> id, CR<Context> ctx) -> Res {
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

auto Formatter::toString(SemId<BlockExport> id, CR<Context> ctx) -> Res {
    if (id.isNil()) { return str("<nil>"); }
    Res head = b.line();
    add(head, str("#+begin_export " + id->exporter));
    if (!id->attrs.isEmpty()) {
        add(head, str(" "));
        add(head, toString(id->attrs, ctx));
    }

    return b.stack(
        Vec<Res>::Splice(head, str(id->content), str("#+end_export")));
}

auto Formatter::toString(SemId<InlineExport> id, CR<Context> ctx) -> Res {
    return str(fmt("@@{}:{}@@", id->exporter, id->content));
}

auto Formatter::toString(SemId<CmdExport> id, CR<Context> ctx) -> Res {
    return str(fmt("#+export_{}: {}", id->exporter, id->content));
}

auto Formatter::toString(SemId<BlockExample> id, CR<Context> ctx) -> Res {
    if (id.isNil()) { return str("<nil>"); }
    return b.stack(Vec<Res>::Splice(
        str("#+begin_example"),
        toSubnodes(id, ctx),
        str("#+end_example")));
}

auto Formatter::toString(SemId<BlockDynamicFallback> id, CR<Context> ctx)
    -> Res {
    if (id.isNil()) { return str("<nil>"); }
    return b.stack(Vec<Res>::Splice(
        str("#+begin_" + id->name),
        toSubnodes(id, ctx),
        str("#+end_" + id->name)));
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
            add(line_out, toString(item, ctx2));
        }
        add(result, line_out);
    }

    if (id.size() == 1 && id.at(0)->is(OrgSemKind::Link)) {
        return stackAttached(result, id.at(0).as<sem::Stmt>(), ctx);
    } else {
        return stackAttached(result, id.as<sem::Stmt>(), ctx);
    }
}

auto Formatter::toString(SemId<Underline> id, CR<Context> ctx) -> Res {
    if (id.isNil()) { return str("<nil>"); }
    return b.line(
        Vec<Res>::Splice(str("_"), toSubnodes(id, ctx), str("_")));
}


Formatter::Res Formatter::stackAttached(
    Res         prev,
    SemId<Stmt> stmt,
    CR<Context> ctx) {
    if (stmt->attached.empty()) {
        return prev;
    } else {
        auto res = b.stack();
        for (auto const& attach : stmt->attached) {
            add(res, toString(attach, ctx));
        }
        add(res, prev);
        return res;
    }
}
