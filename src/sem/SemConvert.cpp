#include <sem/SemConvert.hpp>
#include <hstd/stdlib/Func.hpp>
#include <parse/OrgSpec.hpp>

#include <hstd/stdlib/Debug.hpp>

#include <boost/preprocessor/facilities/overload.hpp>
#include <boost/preprocessor/facilities/empty.hpp>
#include <sem/perfetto_org.hpp>
#include <exporters/exportertree.hpp>
#include <absl/log/log.h>


using namespace sem;

using org      = OrgNodeKind;
using otk      = OrgTokenKind;
using Err      = OrgConverter::Errors;
using Property = sem::Subtree::Property;

Str get_text(
    OrgAdapter  a,
    int         line     = __builtin_LINE(),
    char const* function = __builtin_FUNCTION()) {
    if (a.isTerminal()) {
        return a.val().text;
    } else {
        LOG(FATAL) << fmt("{} {} {}", function, line, a.treeRepr(false));
    }
}

template <class E>
Opt<E> parseOrgEnum(std::string const& name) {
    bool found = false;
    E    r     = {};

    boost::mp11::mp_for_each<boost::describe::describe_enumerators<E>>(
        [&](auto D) {
            if (!found && normalize(D.name) == normalize(name)) {
                found = true;
                r     = D.value;
            }
        });

    if (found) {
        return r;
    } else {
        return std::nullopt;
    }
}

#define __args Up p, In a

using N   = OrgSpecName;
using osk = OrgSemKind;


OrgBigIdentKind parseBigIdent(std::string const& id) {
    using K = OrgBigIdentKind;
    if (id == "TODO") {
        return K::Todo;
    } else if (id == "WIP") {
        return K::Wip;
    } else if (id == "COMPLETED") {
        return K::Done;
    } else if (id == "DONE") {
        return K::Done;
    } else if (id == "CANCELED") {
        return K::Cancelled;
    } else if (id == "FAILED") {
        return K::Failed;
    } else if (id == "PARTIALLY") {
        return K::Partially;
    } else {
        LOG(WARNING) << "Unexpected value to parse big ident" << id;
        return K::Done;
    }
}

SemId<Table> OrgConverter::convertTable(__args) {
    __perf_trace("convert", "convertTable");
    auto __trace = trace(a);
    auto result  = Sem<Table>(p, a);

    return result;
};


SemId<HashTag> OrgConverter::convertHashTag(__args) {
    __perf_trace("convert", "convertHashTag");
    auto                             __trace = trace(a);
    auto                             result  = Sem<HashTag>(p, a);
    Func<SemId<HashTag>(OrgAdapter)> aux;
    result->head = strip(get_text(a.at(0)), CharSet{'#'}, CharSet{});


    aux = [p, &aux, this](OrgAdapter a) -> SemId<HashTag> {
        SemId<HashTag> result = Sem<HashTag>(p, a);
        result->head = strip(get_text(a.at(0)), CharSet{'#'}, CharSet{});
        if (1 < a.size()) {
            for (auto& node : a.at(slice(1, 1_B))) {
                auto conv = aux(node);
                result->subtags.push_back(conv);
            }
        }
        return result;
    };

    if (1 < a.size()) {
        for (auto& node : a.at(slice(1, 1_B))) {
            auto conv = aux(node);
            result->subtags.push_back(conv);
        }
    }

    return result;
};

SemId<SubtreeLog> OrgConverter::convertSubtreeLog(__args) {
    __perf_trace("convert", "convertSubtreeLog");
    auto log = Sem<SubtreeLog>(p, a);

    using Entry = SubtreeLog::LogEntry;
    using Log   = SubtreeLog;
    // TODO Implement subtree log conversion
    return log;
}

void OrgConverter::convertSubtreeDrawer(SemId<Subtree>& tree, In a) {
    __perf_trace("convert", "convertSubtreeDrawer");
    auto __trace = trace(a);
    if (a.kind() != org::Empty) {
        for (const auto& group : a) {
            switch (group.kind()) {
                case org::SubtreeDescription: {
                    tree->description = convertParagraph(tree, group[0]);
                    break;
                }

                case org::Logbook: {
                    for (auto const& entry : group) {
                        auto log = convertSubtreeLog(tree, entry);
                        tree->logbook.push_back(log);
                    }
                    break;
                }

                case org::PropertyList: {
                    for (const auto& prop : group) {
                        convertPropertyList(tree, prop);
                    }
                    break;
                }

                default: {
                }
            }
        }
    }
}

void OrgConverter::convertPropertyList(SemId<Subtree>& tree, In a) {
    __perf_trace("convert", "convertPropertyList");
    auto __trace = trace(a);

    std::string name = normalize(
        strip(get_text(one(a, N::Name)), CharSet{' ', ':'}, CharSet{':'}));

    Opt<Property> result;
    if (name == "exportoptions") {
        Property::ExportOptions res;
        res.backend = get_text(one(a, N::Subname));
        for (Str const& pair : get_text(one(a, N::Values)).split(' ')) {
            auto kv           = pair.split(':');
            res.values[kv[0]] = kv[1];
        }

        result = Property(res);

    } else if (name == "id") {
        tree->treeId = get_text(one(a, N::Values));

    } else if (name == "created") {
        Property::Created created;
        auto              par = convertParagraph(tree, one(a, N::Values));

        if (par->at(0).is(osk::Time)) {
            created.time = par->at(0).as<sem::Time>();
            result       = Property(created);
        } else {
            LOG(ERROR)
                << "Could not extract time from 'created' property\n"
                << a.treeRepr(true);
        }

    } else if (name == "origin") {
        Property::Origin origin;
        origin.text = convert(tree, one(a, N::Values));
        result      = Property(origin);

    } else if (name == "visibility") {
        if (auto visibility = parseOrgEnum<
                sem::Subtree::Property::Visibility::Level>(
                get_text(one(a, N::Values)));
            visibility) {
            Property::Visibility prop;
            prop.level = visibility.value();
            result     = Property(prop);
        }

    } else if (name == "effort") {
        Str const&       value    = get_text(one(a, N::Values));
        Vec<Str>         duration = value.split(":");
        Property::Effort prop;

        if (duration.size() == 1) {
            prop.minutes = duration[0].toInt();
        } else if (duration.size() == 2) {
            prop.minutes = duration[0].toInt();
            prop.hours   = duration[1].toInt();
        }

        result = Property(prop);

    } else {
        Property::Unknown prop;
        prop.value = convert(tree, one(a, N::Values));
        result     = Property(prop);
    }

    if (false && result) {
        const auto inh = get_text(one(a, N::InheritanceMode));
        if (inh == "!!") {
            result->inheritanceMode = Property::InheritanceMode::OnlyThis;
        } else if (inh == "!") {
            result->inheritanceMode = Property::InheritanceMode::OnlySub;
        }

        const auto sub = get_text(one(a, N::SubSetRule));
        if (sub == "+") {
            result->subSetRule = Property::SetMode::Add;
        } else if (sub == "-") {
            result->subSetRule = Property::SetMode::Subtract;
        }

        const auto main = get_text(one(a, N::MainSetRule));
        if (main == "+") {
            result->subSetRule = Property::SetMode::Add;
        } else if (main == "-") {
            result->subSetRule = Property::SetMode::Subtract;
        }

        tree->properties.push_back(*result);
    }
}

SemId<Subtree> OrgConverter::convertSubtree(__args) {
    __perf_trace("convert", "convertSubtree");
    auto __trace = trace(a);
    auto tree    = Sem<Subtree>(p, a);

    tree->level = get_text(one(a, N::Prefix)).size();

    {
        auto __field = field(N::Title, a);
        tree->title  = convertParagraph(tree, one(a, N::Title));
    }

    { auto __field = field(N::Todo, a); }

    {
        auto __field = field(N::Tags, a);
        for (const auto& hash : one(a, N::Tags)) {
            tree->tags.push_back(convertHashTag(tree, hash));
        }
    }

    {
        auto __field = field(N::Drawer, a);
        convertSubtreeDrawer(tree, one(a, N::Drawer));
    }

    {
        auto __field = field(N::Body, a);
        for (auto const& sub : one(a, N::Body)) {
            auto subres = convert(tree, sub);
            tree->push_back(subres);
        }
    }

    return tree;
}

SemId<Time> OrgConverter::convertTime(__args) {
    __perf_trace("convert", "convertTime");
    auto __trace = trace(a);

    bool cond = OrgSet{
                      org::DynamicActiveTime,
                      org::DynamicInactiveTime,
                      org::StaticActiveTime,
                      org::StaticInactiveTime,
                  }
                     .contains(a.kind());

    CHECK(cond) << "convert subtree" << fmt1(a.kind());

    auto time      = Sem<Time>(p, a);
    time->isActive = (a.kind() == org::DynamicActiveTime)
                  || (a.kind() == org::StaticActiveTime);

    if (a.kind() == org::DynamicInactiveTime
        || a.kind() == org::DynamicActiveTime) {
        time->time = Time::Dynamic{.expr = get_text(a)};
    } else if (
        a.kind() == org::StaticActiveTime
        || a.kind() == org::StaticInactiveTime) {

        using Mode      = Time::Repeat::Mode;
        Mode repeatMode = Mode::None;

        if (one(a, N::Repeater).kind() != org::Empty) {
            Str repeat = get_text(one(a, N::Repeater));
            if (repeat.starts_with("++")) {
                repeatMode = Mode::FirstMatch;
                repeat     = repeat.dropPrefix("++");
            } else if (repeat.starts_with(".+")) {
                repeatMode = Mode::SameDay;
                repeat     = repeat.dropPrefix(".+");
            } else if (repeat.starts_with("+")) {
                repeatMode = Mode::Exact;
                repeat     = repeat.dropPrefix("+");
            }
        }

        std::string datetime;
        if (one(a, N::Year).kind() != org::Empty) {
            datetime += get_text(one(a, N::Year));
        }

        if (one(a, N::Clock).kind() != org::Empty) {
            if (!datetime.empty()) { datetime += " "; }
            datetime += get_text(one(a, N::Clock));
        }

        struct Spec {
            std::string         pattern;
            UserTime::Alignment align = UserTime::Alignment::Second;
        };

        Vec<Spec> formats = {
            Spec{.pattern = "%Y-%m-%d %H:%M:%S"},
            Spec{.pattern = "%Y/%m/%d %H:%M:%S"},
            Spec{.pattern = "%d-%m-%Y %H:%M:%S"},
            Spec{.pattern = "%d/%m/%Y %H:%M:%S"},
            Spec{.pattern = "%Y-%m-%d %H:%M"},
            Spec{.pattern = "%Y-%m-%d", .align = UserTime::Alignment::Day},
            // Add other formats as needed
        };

        absl::Time parsedDateTime;
        bool       foundTime = false;
        Spec       matching;
        for (const auto& format : formats) {
            std::string error;
            if (absl::ParseTime(
                    format.pattern,
                    datetime,
                    absl::TimeZone(),
                    &parsedDateTime,
                    &error)) {
                matching  = format;
                foundTime = true;
                break;
            }
        }

        if (!foundTime) {
            // TODO implement proper, non-fatal error reporting
            LOG(ERROR)
                << ("Could not parse date time entry in format: '$#' at "
                    "'$#'"
                    % to_string_vec(datetime, getLocMsg(a)));
        }

        time->time = Time::Static{
            .time = UserTime{
                .time = parsedDateTime, .align = matching.align}};

        if (repeatMode != Mode::None) {
            time->getStatic().repeat = Time::Repeat{
                .mode = repeatMode,
            };
        }
    }

    print_json(time);
    return time;
}

SemId<TimeRange> OrgConverter::convertTimeRange(__args) {
    __perf_trace("convert", "convertTimeRange");
    auto __trace = trace(a);
    auto range   = Sem<TimeRange>(p, a);
    {
        auto __field = field(N::From, a);
        range->from  = convertTime(range, one(a, N::From));
    }
    {
        auto __field = field(N::To, a);
        range->to    = convertTime(range, one(a, N::To));
    }
    return range;
}

SemId<Macro> OrgConverter::convertMacro(__args) {
    __perf_trace("convert", "convertMacro");
    auto __trace = trace(a);
    auto macro   = Sem<Macro>(p, a);


    return macro;
}

SemId<Symbol> OrgConverter::convertSymbol(__args) {
    __perf_trace("convert", "convertSymbol");
    auto __trace = trace(a);
    auto sym     = Sem<Symbol>(p, a);

    int idx   = 0;
    sym->name = get_text(one(a, N::Name)).substr(1);
    for (const auto& sub : one(a, N::Args)) {
        auto params = get_text(sub).split(" ");
        for (int i = 0; i < params.size();) {
            if (params.at(i).starts_with(":") && (i + 1) < params.size()) {
                sym->parameters.push_back(Symbol::Param{
                    .key = params.at(i), .value = params.at(i + 1)});
                i += 2;
            } else {
                sym->parameters.push_back(
                    Symbol::Param{.value = params.at(i)});
                i += 1;
            }
        }
    }

    for (const auto& sub : one(a, N::Body)) {
        sym->positional.push_back(convert(sym, sub));
    }

    return sym;
}

SemId<Paragraph> OrgConverter::convertParagraph(__args) {
    // TODO detect admonition paragraphs during conversion and store
    // information about this -- right now `NOTE:` is represented using
    // first two starting elements for paragraph subnodes.

    __perf_trace("convert", "convertParagraph");
    auto __trace = trace(a);
    auto par     = Sem<Paragraph>(p, a);
    bool first   = true;
    for (const auto& item : a) {
        if (first && item.kind() == org::Footnote) {
            par.push_back(convertFootnote(par, item));
        } else {
            par.push_back(convert(par, item));
        }
        first = false;
    }

    return par;
}

SemId<StmtList> OrgConverter::convertStmtList(__args) {
    __perf_trace("convert", "convertStmtList");
    auto __trace = trace(a);
    auto stmt    = Sem<StmtList>(p, a);

    for (OrgAdapter const& sub : a) { stmt.push_back(convert(stmt, sub)); }

    return stmt;
}


SemId<Footnote> OrgConverter::convertFootnote(__args) {
    __perf_trace("convert", "convertFootnote");
    auto __trace = trace(a);
    if (a.kind() == org::InlineFootnote) {
        auto note        = Sem<Footnote>(p, a);
        note->definition = convert(note, one(a, N::Definition));
        return note;
    } else {
        auto link = Sem<Footnote>(p, a);
        link->tag = get_text(one(a, N::Definition));
        return link;
    }
}

SemId<Link> OrgConverter::convertLink(__args) {
    __perf_trace("convert", "convertLink");
    auto __trace = trace(a);
    auto link    = Sem<Link>(p, a);
    if (a.kind() == org::RawLink) {
        link->data = Link::Raw{.text = get_text(a)};

    } else if (a.kind() == org::Footnote) {
        link->data = Link::Footnote{.target = get_text(one(a, N::Name))};

    } else if (one(a, N::Protocol).kind() == org::Empty) {
        // TODO

    } else {
        Str protocol = normalize(get_text(one(a, N::Protocol)));
        if (protocol == "http" || protocol == "https") {
            link->data = Link::Raw{
                .text = protocol + ":"_ss + get_text(one(a, N::Link))};
        } else if (protocol == "id") {
            link->data = Link::Id{.text = get_text(one(a, N::Link))};

        } else if (protocol == "person") {
            // FIXME extract paragraph data
            // link->data = Link::Person{.name = one(a,
            // N::Link).val().text};
            link->data = Link::Person{};

        } else if (protocol == "file") {
            link->data = Link::File{.file = get_text(one(a, N::Link))};

        } else {
            LOG(ERROR) << "Unhandled protocol kind '" << protocol << "'\n"
                       << a.treeRepr();
        }
    }

    if (a.kind() == org::Link) {
        if (one(a, N::Desc).kind() == org::Paragraph) {
            link->description = convertParagraph(link, one(a, N::Desc));
        }
    }

    return link;
}

SemId<List> OrgConverter::convertList(__args) {
    __perf_trace("convert", "convertList");
    auto __trace = trace(a);
    auto list    = Sem<List>(p, a);
    for (const auto& it : a) { list.push_back(convert(list, it)); }

    return list;
}

SemId<ListItem> OrgConverter::convertListItem(__args) {
    __perf_trace("convert", "convertListItem");
    auto __trace = trace(a);
    auto item    = Sem<ListItem>(p, a);
    if (one(a, N::Header).kind() != org::Empty) {
        item->header = convertParagraph(item, one(a, N::Header));
    }

    {
        for (const auto& sub : one(a, N::Body)) {
            item.push_back(convert(item, sub));
        }
    }

    return item;
}

SemId<Caption> OrgConverter::convertCaption(__args) {
    __perf_trace("convert", "convertCaption");
    auto __trace  = trace(a);
    auto caption  = Sem<Caption>(p, a);
    caption->text = convertParagraph(caption, one(a, N::Args)[0]);

    return caption;
}


SemId<Tblfm> OrgConverter::convertTblfm(__args) {
    __perf_trace("convert", "convertTblfm");
    auto __trace = trace(a);
    auto tblfm   = Sem<Tblfm>(p, a);

    return tblfm;
}


SemId<Word> OrgConverter::convertWord(__args) {
    auto __trace = trace(a);
    return SemLeaf<Word>(p, a);
}

SemId<Placeholder> OrgConverter::convertPlaceholder(__args) {
    __perf_trace("convert", "convertPlaceholder");
    auto __trace = trace(a);
    return SemLeaf<Placeholder>(p, one(a, N::Body));
}

SemId<Newline> OrgConverter::convertNewline(__args) {
    auto __trace = trace(a);
    return SemLeaf<Newline>(p, a);
}

SemId<Space> OrgConverter::convertSpace(__args) {
    return SemLeaf<Space>(p, a);
}

SemId<Escaped> OrgConverter::convertEscaped(__args) {
    return SemLeaf<Escaped>(p, a);
}

SemId<RawText> OrgConverter::convertRawText(__args) {
    return SemLeaf<RawText>(p, a);
}

SemId<Punctuation> OrgConverter::convertPunctuation(__args) {
    auto __trace = trace(a);
    return SemLeaf<Punctuation>(p, a);
}

SemId<BigIdent> OrgConverter::convertBigIdent(__args) {
    __perf_trace("convert", "convertBigIdent");
    auto __trace = trace(a);
    return SemLeaf<BigIdent>(p, a);
}

SemId<sem::ParseError> OrgConverter::convertParseError(__args) {
    return Sem<sem::ParseError>(p, a);
}


SemId<MarkQuote> OrgConverter::convertMarkQuote(__args) {
    __perf_trace("convert", "convertMarkQuote");
    auto __trace = trace(a);
    return convertAllSubnodes<MarkQuote>(p, a);
}

SemId<Verbatim> OrgConverter::convertVerbatim(__args) {
    __perf_trace("convert", "convertVerbatim");
    auto __trace = trace(a);
    return convertAllSubnodes<Verbatim>(p, a);
}

SemId<Bold> OrgConverter::convertBold(__args) {
    __perf_trace("convert", "convertBold");
    auto __trace = trace(a);
    return convertAllSubnodes<Bold>(p, a);
}

SemId<Monospace> OrgConverter::convertMonospace(__args) {
    __perf_trace("convert", "convertMonospace");
    auto __trace = trace(a);
    return convertAllSubnodes<Monospace>(p, a);
}

SemId<Strike> OrgConverter::convertStrike(__args) {
    __perf_trace("convert", "convertStrike");
    auto __trace = trace(a);
    return convertAllSubnodes<Strike>(p, a);
}

SemId<Par> OrgConverter::convertPar(__args) {
    __perf_trace("convert", "convertPar");
    auto __trace = trace(a);
    return convertAllSubnodes<Par>(p, a);
}

SemId<Italic> OrgConverter::convertItalic(__args) {
    __perf_trace("convert", "convertItalic");
    auto __trace = trace(a);
    return convertAllSubnodes<Italic>(p, a);
}

SemId<Underline> OrgConverter::convertUnderline(__args) {
    __perf_trace("convert", "convertUnderline");
    auto __trace = trace(a);
    return convertAllSubnodes<Underline>(p, a);
}

SemId<Example> OrgConverter::convertExample(__args) {
    return convertAllSubnodes<Example>(p, a);
}

SemId<Export> OrgConverter::convertExport(__args) {
    auto eexport = Sem<Export>(p, a);
    switch (a.kind()) {
        case org::BlockExport:
            eexport->format = Export::Format::Block;
            break;
        default: {
        }
    }

    auto values = convertCmdArguments(eexport, one(a, N::Args));
    if (auto place = values->popArg("placement"); place) {
        eexport->placement = (*place)->getString();
    }

    eexport->exporter   = get_text(one(a, N::Name));
    eexport->parameters = values;
    for (auto const& item : one(a, N::Body)) {
        eexport->content = get_text(item);
    }

    return eexport;
}

SemId<Center> OrgConverter::convertCenter(__args) {
    SemId<Center> res = Sem<Center>(p, a);
    for (const auto& sub : many(a, N::Body)) {
        auto aux = convert(res, sub);
        res->push_back(aux);
    }
    return res;
}

SemId<AdmonitionBlock> OrgConverter::convertAdmonitionBlock(__args) {
    return convertAllSubnodes<AdmonitionBlock>(p, a);
}

SemId<Quote> OrgConverter::convertQuote(__args) {
    SemId<Quote> quote = Sem<Quote>(p, a);
    for (const auto& sub : many(a, N::Body)) {
        auto aux = convert(quote, sub);
        quote->push_back(aux);
    }
    return quote;
}

SemId<LatexBody> OrgConverter::convertMath(__args) {
    if (a.kind() == org::InlineMath) {
        return Sem<InlineMath>(p, a).as<LatexBody>();
    } else {
        LOG(FATAL) << "Unhanled kind for inline math TODO";
    }
}

SemId<Include> OrgConverter::convertInclude(__args) {
    SemId<Include> include = Sem<Include>(p, a);
    LOG(WARNING) << "TODO implement include";

    return include;
}

SemId<TextSeparator> OrgConverter::convertTextSeparator(__args) {
    return Sem<TextSeparator>(p, a);
}

SemId<AtMention> OrgConverter::convertAtMention(__args) {
    return SemLeaf<AtMention>(p, a);
}

SemId<CmdArgument> OrgConverter::convertCmdArgument(__args) {
    SemId<CmdArgument> result = Sem<CmdArgument>(p, a);
    Str                key    = get_text(one(a, N::Name));
    result->value             = get_text(one(a, N::Value));

    if (!key.empty()) {
        // result->key = key.remove(':');
    }


    return result;
}

SemId<CmdArguments> OrgConverter::convertCmdArguments(__args) {
    SemId<CmdArguments> result  = Sem<CmdArguments>(p, a);
    auto                add_arg = [&](SemId<CmdArgument> arg) {
        if (arg->key) {
            bool ok = result->named.insert({arg->key.value(), arg}).second;
            CHECK(ok); // TODO generate proper error message
        } else {
            result->positional.push_back(arg);
        }
    };

    if (a.getKind() == org::CmdArguments) {
        for (auto const& item : one(a, N::Values)) {
            add_arg(convertCmdArgument(result, item));
        }
    } else if (a.getKind() == org::InlineStmtList) {
        for (auto const& it : a) {
            add_arg(convertCmdArgument(result, it));
        }
    } else {
        CHECK(a.getKind() == org::Empty) << a.treeRepr();
    }

    return result;
}

SemId<Code> OrgConverter::convertCode(__args) {
    SemId<Code> result = Sem<Code>(p, a);
    auto        body   = one(a, N::Body);

    return result;
}


Vec<SemId<Org>> OrgConverter::flatConvertAttached(__args) {
    Vec<SemId<Org>>        result;
    Func<void(OrgAdapter)> aux;
    aux = [&](OrgAdapter a) {
        SemId res = SemId<Org>::Nil();
        switch (a.kind()) {
            case org::CommandCaption: res = convertCaption(p, a); break;
            default:
                LOG(FATAL)
                    << "TODO unhandled kind $#" % to_string_vec(a.kind());
        }

        CHECK(!res.isNil());
        result.push_back(res);
        if (OrgTrailableCommands.contains(a.kind())) {
            aux(one(a, N::Body));
        }
    };

    aux(a);

    return result;
}


SemId<Org> OrgConverter::convert(__args) {
    auto __trace = trace(a);
    if (!a.isValid()) {
        LOG(WARNING) << "Invalid node encountered during conversion"
                     << fmt1(a.id);
        return Sem<Space>(p, a);
    }

#define CASE(Kind)                                                        \
    case org::Kind: return convert##Kind(p, a);
    switch (a.kind()) {
        CASE(Newline);
        CASE(StmtList);
        CASE(Subtree);
        CASE(TimeRange);
        CASE(Paragraph);
        CASE(Space);
        CASE(Word);
        CASE(Bold);
        CASE(Italic);
        CASE(Strike);
        CASE(Punctuation);
        CASE(Link);
        CASE(Par);
        CASE(BigIdent);
        CASE(Verbatim);
        CASE(RawText);
        CASE(List);
        CASE(ListItem);
        CASE(Placeholder);
        CASE(Escaped);
        CASE(TextSeparator);
        CASE(AtMention);
        CASE(Underline);
        case org::SrcInlineCode:
        case org::SrcCode: return convertCode(p, a);
        case org::InlineFootnote: return convertFootnote(p, a);
        case org::BlockExport: return convertExport(p, a);
        case org::Macro: return convertMacro(p, a);
        case org::Monospace: return convertMonospace(p, a);
        case org::CenterBlock: return convertCenter(p, a);
        case org::Example: return convertExample(p, a);
        case org::AdmonitionBlock: return convertAdmonitionBlock(p, a);
        case org::HashTag: return convertHashTag(p, a);
        case org::Error: return convertParseError(p, a);
        case org::ListTag: return convert(p, a[0]);
        case org::InlineMath: return convertMath(p, a);
        case org::RawLink: return convertLink(p, a);
        case org::StaticActiveTime:
        case org::StaticInactiveTime:
        case org::DynamicActiveTime:
        case org::DynamicInactiveTime: return convertTime(p, a);
        case org::Quote: return convertMarkQuote(p, a);
        case org::QuoteBlock: return convertQuote(p, a);
        case org::Colon: return convertPunctuation(p, a);
        case org::CommandInclude: return convertInclude(p, a);
        case org::Symbol: return convertSymbol(p, a);
        case org::Angle: return convertPlaceholder(p, a);
        case org::Empty: return Sem<Empty>(p, a);
        case org::Table: return convertTable(p, a);
        case org::Footnote: return convertFootnote(p, a);
        case org::CommandTblfm: return convertTblfm(p, a);
        case org::CommandCaption: {
            // TODO update parent nodes after restructuring
            Vec<SemId<Org>> nested = flatConvertAttached(p, a);
            for (const auto& it : nested) { CHECK(!it.isNil()); }

            CHECK(!nested.empty()) << "nested command wrap"
                                   << "Nested command result had size 0";

            if (nested.size() == 1) {
                return nested[0];
            } else if (SemSet{
                           osk::Code,
                           osk::Quote,
                       }
                           .contains(nested.back()->getKind())) {
                // Get last wrapped statement
                SemId lastNested = nested.back();
                Stmt* trailed = dynamic_cast<sem::Stmt*>(lastNested.get());
                CHECK(trailed != nullptr);
                for (const auto& it : nested[slice(0, 2_B)]) {
                    trailed->attached.push_back(it);
                }
                return lastNested;

            } else {
                SemId<CommandGroup> group = Sem<CommandGroup>(p, a);
                for (const auto& it : nested) {
                    group->attached.push_back(it);
                }
                return group;
            }
        }

        default:
            LOG(ERROR) << fmt("Unhandled node type {} {}", a.kind(), a.id);
            return Sem<Empty>(p, a);
    }
#undef CASE
}

void fillDocumentOptions(SemId<DocumentOptions> opts, OrgAdapter a) {
    if (opts->isGenerated()) { opts->original = a; }
    auto item = a.at(0);
    for (auto const& value : get_text(item).split(' ')) {
        if (value.contains(':')) {
            auto split = value.split(':');
            auto head  = split[0];
            auto tail  = split[1];
            if (head == "broken-links") {
                if (tail == "mark") {
                    opts->brokenLinks = DocumentOptions::BrokenLinks::Mark;
                } else if (tail == "t") {
                    opts->brokenLinks = DocumentOptions::BrokenLinks::
                        Ignore;
                }
            } else if (head == "toc") {
                if (tail == "t") {
                    opts->tocExport = DocumentOptions::DoExport{true};
                } else if (tail == "nil") {
                    opts->tocExport = DocumentOptions::DoExport{false};
                } else if ('0' <= tail[0] && tail[0] <= '9') {
                    opts->tocExport = DocumentOptions::ExportFixed{
                        tail.toInt()};
                }
            }

        } else if (value == ":") {
            opts->fixedWidthSections = true;
        } else if (value == "<") {
            opts->includeTimestamps = true;
        } else if (value == "^") {
            opts->plaintextSubscripts = true;
        } else {
            LOG(ERROR) << "Unexpected document option value" << value;
        }
    }
}

SemId<Document> OrgConverter::toDocument(OrgAdapter adapter) {
    SemId<Document> doc = Sem<Document>(SemId<Org>::Nil(), adapter);
    doc->options        = Sem<DocumentOptions>(doc, adapter);
    using Prop          = Subtree::Property;

    if (adapter.kind() == org::StmtList) {
        for (const auto& sub : adapter) {
            switch (sub.kind()) {
                case org::Columns: {
                    LOG(WARNING) << "TODO: Skipping 'columns' node";
                    break;
                }
                case org::CommandTitle: {
                    doc->title = convertParagraph(doc, sub[0]);
                    break;
                }
                case org::CommandOptions: {
                    fillDocumentOptions(doc->options, sub);
                    break;
                }

                case org::CmdPropertyRaw:
                case org::CmdPropertyText:
                case org::CmdPropertyArgs: {
                    LOG(WARNING)
                        << "TODO handle property conversion for options";
                    break;
                }

                case org::LatexClass: {
                    Prop::ExportLatexClass res{};
                    res.latexClass = get_text(sub.at(0));
                    doc->options->properties.push_back(Prop(res));
                    break;
                }
                case org::LatexHeader: {
                    Prop::ExportLatexHeader res{};
                    res.header = get_text(sub.at(0));
                    doc->options->properties.push_back(Prop(res));
                    break;
                }
                case org::LatexCompiler: {
                    Prop::ExportLatexCompiler res{};
                    res.compiler = get_text(sub.at(0));
                    doc->options->properties.push_back(Prop(res));
                    break;
                }
                case org::LatexClassOptions: {
                    auto value = get_text(sub.at(0));
                    Prop::ExportLatexClassOptions res;
                    res.options.push_back(value);
                    doc->options->properties.push_back(Prop(res));
                    break;
                }
                default: {
                    doc->subnodes.push_back(convert(doc, sub));
                    break;
                }
            }
        }
    } else {
        doc->subnodes.push_back(convert(doc, adapter));
    }

    return doc;
}
