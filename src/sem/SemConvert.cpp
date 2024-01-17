#include <sem/SemConvert.hpp>
#include <hstd/stdlib/Func.hpp>
#include <parse/OrgSpec.hpp>

#include <hstd/stdlib/Debug.hpp>

#include <boost/preprocessor/facilities/overload.hpp>
#include <boost/preprocessor/facilities/empty.hpp>
#include <hstd/wrappers/perfetto_aux.hpp>
#include <exporters/exportertree.hpp>
#include <absl/log/log.h>

#define __place(location)                                                 \
    PlacementScope CONCAT(locationScope, __COUNTER__) = PlacementScope(   \
        location, this);

using namespace sem;

using org      = OrgNodeKind;
using otk      = OrgTokenKind;
using osp      = OrgSemPlacement;
using Err      = OrgConverter::Errors;
using Property = sem::Subtree::Property;

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

SemIdT<Table> OrgConverter::convertTable(__args) {
    __perf_trace("convert", "convertTable");
    auto __trace = trace(a);
    auto result  = Sem<Table>(p, a);

    return result;
};


SemIdT<HashTag> OrgConverter::convertHashTag(__args) {
    __perf_trace("convert", "convertHashTag");
    auto                              __trace = trace(a);
    auto                              result  = Sem<HashTag>(p, a);
    Func<SemIdT<HashTag>(OrgAdapter)> aux;
    result->head = strip(a.at(0).val().getText(), CharSet{'#'}, CharSet{});


    aux = [p, &aux, this](OrgAdapter a) -> SemIdT<HashTag> {
        SemIdT<HashTag> result = Sem<HashTag>(p, a);
        result->head           = strip(
            a.at(0).val().getText(), CharSet{'#'}, CharSet{});
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

SemIdT<SubtreeLog> OrgConverter::convertSubtreeLog(__args) {
    __perf_trace("convert", "convertHashTag");
    auto log = Sem<SubtreeLog>(p, a);

    using Entry = SubtreeLog::LogEntry;
    using Log   = SubtreeLog;


    if (a.kind() == org::LogbookEntry) {
        auto head = one(a, N::Header);
        switch (head.kind()) {
            case org::LogbookTagChange: {
                Log::Tag tag;
                tag.tag   = convertHashTag(log, one(head, N::Tag));
                tag.added = one(head, N::State).val().getText() == "Added";
                tag.on    = convertTime(log, one(head, N::Time));

                log->log = Entry(tag);
                break;
            }

            case org::LogbookNote: {
                Log::Note note{};

                note.on = convertTime(log, one(head, N::Time));

                log->log = Entry(note);
                break;
            }

            case org::LogbookStateChange: {
                Log::State state{};

                state.from = parseBigIdent(
                    one(head, N::Oldstate).val().getText());
                state.to = parseBigIdent(
                    one(head, N::Newstate).val().getText());
                state.on = convertTime(log, one(head, N::Time));

                log->log = Entry(state);
                break;
            }

            case org::LogbookRefile: {
                Log::Refile refile;

                refile.on   = convertTime(log, one(head, N::Time));
                refile.from = convertLink(log, one(head, N::From));

                log->log = Entry(refile);
                break;
            }

            default: {
                LOG(INFO) << "Unexpected incoming tree kind for subtree "
                             "converter"
                          << fmt1(head.kind());
                LOG(INFO) << head.treeRepr();
            }
        }

        auto desc = one(a, N::Description);

        if (desc.kind() != org::Empty) {
            log->setDescription(convertStmtList(log, desc));
        }

    } else {
        Log::Clock clock;
        auto       time = one(a, N::Time);

        if (time.kind() == org::TimeRange) {
            clock.range = convertTimeRange(log, time);
        } else {
            clock.range = convertTime(log, time);
        }


        log->log = Entry(clock);
    }

    return log;
}

void OrgConverter::convertSubtreeDrawer(SemIdT<Subtree>& tree, In a) {
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

void OrgConverter::convertPropertyList(SemIdT<Subtree>& tree, In a) {
    __perf_trace("convert", "convertPropertyList");
    auto __trace = trace(a);

    std::string name = normalize(strip(
        one(a, N::Name).val().getText(), CharSet{':'}, CharSet{':'}));

    Opt<Property> result;
    if (name == "exportoptions") {
        Property::ExportOptions res;
        res.backend = one(a, N::Subname).val().getText();
        for (Str const& pair :
             one(a, N::Values).val().getText().split(' ')) {
            auto kv           = pair.split(':');
            res.values[kv[0]] = kv[1];
        }

        result = Property(res);

    } else if (name == "id") {
        tree->treeId = one(a, N::Values).val().getText();

    } else if (name == "created") {
        Property::Created created;
        auto              par = convertParagraph(tree, one(a, N::Values));

        created.time = par->at(0).as<sem::Time>();
        result       = Property(created);

    } else if (name == "origin") {
        Property::Origin origin;
        origin.text = one(a, N::Values).val().getText();
        result      = Property(origin);

    } else if (name == "visibility") {
        if (auto visibility = parseOrgEnum<
                sem::Subtree::Property::Visibility::Level>(
                one(a, N::Values).val().getText());
            visibility) {
            Property::Visibility prop;
            prop.level = visibility.value();
            result     = Property(prop);
        }

    } else if (name == "effort") {
        Str const&       value    = one(a, N::Values).val().getText();
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
        LOG(ERROR) << "Unknown property name"
                   << one(a, N::Name).val().getText() << "\n"
                   << a.treeRepr();
    }

    if (false && result) {
        const auto inh = one(a, N::InheritanceMode).val().getText();
        if (inh == "!!") {
            result->inheritanceMode = Property::InheritanceMode::OnlyThis;
        } else if (inh == "!") {
            result->inheritanceMode = Property::InheritanceMode::OnlySub;
        }

        const auto sub = one(a, N::SubSetRule).val().getText();
        if (sub == "+") {
            result->subSetRule = Property::SetMode::Add;
        } else if (sub == "-") {
            result->subSetRule = Property::SetMode::Subtract;
        }

        const auto main = one(a, N::MainSetRule).val().getText();
        if (main == "+") {
            result->subSetRule = Property::SetMode::Add;
        } else if (main == "-") {
            result->subSetRule = Property::SetMode::Subtract;
        }

        tree->properties.push_back(*result);
    }
}

SemIdT<Subtree> OrgConverter::convertSubtree(__args) {
    __perf_trace("convert", "convertSubtree");
    auto __trace = trace(a);
    auto tree    = Sem<Subtree>(p, a);

    tree->level = one(a, N::Prefix).val().getText().size();

    {
        auto __field = field(N::Title, a);
        __place(osp::TreeTitle);
        tree->title = convertParagraph(tree, one(a, N::Title));
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
        __place(osp::TreeBody);
        for (auto const& sub : one(a, N::Body)) {
            auto subres = convert(tree, sub);
            tree->push_back(subres);
        }
    }

    return tree;
}

SemIdT<Time> OrgConverter::convertTime(__args) {
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
        time->time = Time::Dynamic{.expr = a.val().getText()};
    } else if (
        a.kind() == org::StaticActiveTime
        || a.kind() == org::StaticInactiveTime) {

        using Mode      = Time::Repeat::Mode;
        Mode repeatMode = Mode::None;

        if (one(a, N::Repeater).kind() != org::Empty) {
            Str repeat = one(a, N::Repeater).val().getText();
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
            datetime += one(a, N::Year).val().getText();
        }

        if (one(a, N::Clock).kind() != org::Empty) {
            if (!datetime.empty()) { datetime += " "; }
            datetime += one(a, N::Clock).val().getText();
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

SemIdT<TimeRange> OrgConverter::convertTimeRange(__args) {
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

SemIdT<Macro> OrgConverter::convertMacro(__args) {
    __perf_trace("convert", "convertMacro");
    auto __trace = trace(a);
    auto macro   = Sem<Macro>(p, a);


    return macro;
}

SemIdT<Symbol> OrgConverter::convertSymbol(__args) {
    __perf_trace("convert", "convertSymbol");
    auto __trace = trace(a);
    auto sym     = Sem<Symbol>(p, a);

    int idx = 0;
    for (const auto& sub : a) {
        if (idx == 0) {
            sym->name = sub.val().getText();
        } else if (sub.kind() == org::RawText) {
            auto params = sub.val().getText().split(" ");
            for (int i = 0; i < params.size();) {
                if (params.at(i).starts_with(":")
                    && (i + 1) < params.size()) {
                    sym->parameters.push_back(Symbol::Param{
                        .key = params.at(i), .value = params.at(i + 1)});
                    i += 2;
                } else {
                    sym->parameters.push_back(
                        Symbol::Param{.value = params.at(i)});
                    i += 1;
                }
            }
        } else {
            sym->positional.push_back(convert(sym, sub));
        }
        ++idx;
    }
    return sym;
}

SemIdT<Paragraph> OrgConverter::convertParagraph(__args) {
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

SemIdT<StmtList> OrgConverter::convertStmtList(__args) {
    __perf_trace("convert", "convertStmtList");
    auto __trace = trace(a);
    auto stmt    = Sem<StmtList>(p, a);

    for (OrgAdapter const& sub : a) { stmt.push_back(convert(stmt, sub)); }

    return stmt;
}


SemIdT<Footnote> OrgConverter::convertFootnote(__args) {
    __perf_trace("convert", "convertLink");
    auto __trace = trace(a);
    if (a.kind() == org::InlineFootnote) {
        auto note        = Sem<Footnote>(p, a);
        note->definition = convert(note, a[0]);
        return note;
    } else {
        auto link = Sem<Footnote>(p, a);
        if (a.size() == 1) {
            link->tag = a[0].val().getText();
        } else {
            LOG(FATAL) << ("TODO");
        }

        return link;
    }
}

SemIdT<Link> OrgConverter::convertLink(__args) {
    __perf_trace("convert", "convertLink");
    auto __trace = trace(a);
    auto link    = Sem<Link>(p, a);
    if (a.kind() == org::RawLink) {
        link->data = Link::Raw{.text = a.val().getText()};

    } else if (a.kind() == org::Footnote) {
        link->data = Link::Footnote{
            .target = one(a, N::Name).val().getText()};

    } else {
        Str protocol = normalize(one(a, N::Protocol).val().getText());
        if (protocol == "") {
            link->data = Link::Raw{
                .text = one(a, N::Link).val().getText()};
        } else if (protocol == "id") {
            link->data = Link::Id{.text = one(a, N::Link).val().getText()};

        } else if (protocol == "person") {
            link->data = Link::Person{
                .name = one(a, N::Link).val().getText()};

        } else if (protocol == "file") {
            link->data = Link::File{
                .file = one(a, N::Link).val().getText()};

        } else {
            LOG(ERROR) << "Unhandled protocol kind" << protocol << "\n"
                       << a.treeRepr();
        }
    }

    if (a.kind() == org::Link) {
        if (one(a, N::Desc).kind() == org::Paragraph) {
            __place(osp::LinkDescription);
            link->description = convertParagraph(link, one(a, N::Desc));
        }
    }

    return link;
}

SemIdT<List> OrgConverter::convertList(__args) {
    __perf_trace("convert", "convertList");
    auto __trace = trace(a);
    auto list    = Sem<List>(p, a);
    for (const auto& it : a) { list.push_back(convert(list, it)); }

    return list;
}

SemIdT<ListItem> OrgConverter::convertListItem(__args) {
    __perf_trace("convert", "convertListItem");
    auto __trace = trace(a);
    auto item    = Sem<ListItem>(p, a);
    if (one(a, N::Header).kind() != org::Empty) {
        __place(osp::ListItemDesc);
        item->header = convertParagraph(item, one(a, N::Header));
    }

    {
        __place(osp::ListItemBody);
        for (const auto& sub : one(a, N::Body)) {
            item.push_back(convert(item, sub));
        }
    }

    return item;
}

SemIdT<Caption> OrgConverter::convertCaption(__args) {
    __perf_trace("convert", "convertCaption");
    auto __trace  = trace(a);
    auto caption  = Sem<Caption>(p, a);
    caption->text = convertParagraph(caption, one(a, N::Args)[0]);

    return caption;
}


SemIdT<Word> OrgConverter::convertWord(__args) {
    auto __trace = trace(a);
    return SemLeaf<Word>(p, a);
}

SemIdT<Placeholder> OrgConverter::convertPlaceholder(__args) {
    __perf_trace("convert", "convertPlaceholder");
    auto __trace = trace(a);
    return SemLeaf<Placeholder>(p, one(a, N::Body));
}

SemIdT<Newline> OrgConverter::convertNewline(__args) {
    auto __trace = trace(a);
    return SemLeaf<Newline>(p, a);
}

SemIdT<Space> OrgConverter::convertSpace(__args) {
    return SemLeaf<Space>(p, a);
}

SemIdT<Escaped> OrgConverter::convertEscaped(__args) {
    return SemLeaf<Escaped>(p, a);
}

SemIdT<RawText> OrgConverter::convertRawText(__args) {
    return SemLeaf<RawText>(p, a);
}

SemIdT<Punctuation> OrgConverter::convertPunctuation(__args) {
    auto __trace = trace(a);
    return SemLeaf<Punctuation>(p, a);
}

SemIdT<BigIdent> OrgConverter::convertBigIdent(__args) {
    __perf_trace("convert", "convertBigIdent");
    auto __trace = trace(a);
    return SemLeaf<BigIdent>(p, a);
}

SemIdT<sem::ParseError> OrgConverter::convertParseError(__args) {
    return Sem<sem::ParseError>(p, a);
}


SemIdT<MarkQuote> OrgConverter::convertMarkQuote(__args) {
    __perf_trace("convert", "convertMarkQuote");
    auto __trace = trace(a);
    return convertAllSubnodes<MarkQuote>(p, a);
}

SemIdT<Verbatim> OrgConverter::convertVerbatim(__args) {
    __perf_trace("convert", "convertVerbatim");
    auto __trace = trace(a);
    return convertAllSubnodes<Verbatim>(p, a);
}

SemIdT<Bold> OrgConverter::convertBold(__args) {
    __perf_trace("convert", "convertBold");
    auto __trace = trace(a);
    return convertAllSubnodes<Bold>(p, a);
}

SemIdT<Monospace> OrgConverter::convertMonospace(__args) {
    __perf_trace("convert", "convertMonospace");
    auto __trace = trace(a);
    return convertAllSubnodes<Monospace>(p, a);
}

SemIdT<Strike> OrgConverter::convertStrike(__args) {
    __perf_trace("convert", "convertStrike");
    auto __trace = trace(a);
    return convertAllSubnodes<Strike>(p, a);
}

SemIdT<Par> OrgConverter::convertPar(__args) {
    __perf_trace("convert", "convertPar");
    auto __trace = trace(a);
    return convertAllSubnodes<Par>(p, a);
}

SemIdT<Italic> OrgConverter::convertItalic(__args) {
    __perf_trace("convert", "convertItalic");
    auto __trace = trace(a);
    return convertAllSubnodes<Italic>(p, a);
}

SemIdT<Underline> OrgConverter::convertUnderline(__args) {
    __perf_trace("convert", "convertUnderline");
    auto __trace = trace(a);
    return convertAllSubnodes<Underline>(p, a);
}

SemIdT<Example> OrgConverter::convertExample(__args) {
    return convertAllSubnodes<Example>(p, a);
}

SemIdT<Export> OrgConverter::convertExport(__args) {
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

    eexport->exporter   = one(a, N::Name).val().getText();
    eexport->parameters = values;
    eexport->content    = one(a, N::Body).val().getText();

    return eexport;
}

SemIdT<Center> OrgConverter::convertCenter(__args) {
    SemIdT<Center> res = Sem<Center>(p, a);
    for (const auto& sub : many(a, N::Body)) {
        res->push_back(convert(res, sub));
    }
    return res;
}

SemIdT<AdmonitionBlock> OrgConverter::convertAdmonitionBlock(__args) {
    return convertAllSubnodes<AdmonitionBlock>(p, a);
}

SemIdT<Quote> OrgConverter::convertQuote(__args) {
    SemIdT<Quote> quote = Sem<Quote>(p, a);
    quote->text         = convertParagraph(quote, a[0]);
    return quote;
}

SemIdT<LatexBody> OrgConverter::convertMath(__args) {
    if (a.kind() == org::InlineMath) {
        return Sem<InlineMath>(p, a);
    } else {
        LOG(FATAL) << "Unhanled kind for inline math TODO";
    }
}

SemIdT<Include> OrgConverter::convertInclude(__args) {
    SemIdT<Include> include = Sem<Include>(p, a);
    LOG(WARNING) << "TODO implement include";

    return include;
}

SemIdT<TextSeparator> OrgConverter::convertTextSeparator(__args) {
    return Sem<TextSeparator>(p, a);
}

SemIdT<AtMention> OrgConverter::convertAtMention(__args) {
    return SemLeaf<AtMention>(p, a);
}

SemIdT<CmdArgument> OrgConverter::convertCmdArgument(__args) {
    SemIdT<CmdArgument> result = Sem<CmdArgument>(p, a);
    Str                 key    = one(a, N::Name).val().getText();
    result->value              = one(a, N::Value).val().getText();

    if (!key.empty()) {
        // result->key = key.remove(':');
    }


    return result;
}

SemIdT<CmdArguments> OrgConverter::convertCmdArguments(__args) {
    SemIdT<CmdArguments> result = Sem<CmdArguments>(p, a);
    if (a.getKind() == org::CmdArguments) {
        for (auto const& item : one(a, N::Values)) {
            SemIdT<CmdArgument> arg = convertCmdArgument(result, item);
            if (arg->key) {
                bool ok = result->named.insert({arg->key.value(), arg})
                              .second;
                CHECK(ok); // TODO generate proper error message
            } else {
                result->positional.push_back(arg);
            }
        }
    } else {
        CHECK(a.getKind() == org::Empty);
    }

    return result;
}

SemIdT<Code> OrgConverter::convertCode(__args) {
    SemIdT<Code> result = Sem<Code>(p, a);
    auto         body   = one(a, N::Body);

    return result;
}


Vec<SemId> OrgConverter::flatConvertAttached(__args) {
    Vec<SemId>             result;
    Func<void(OrgAdapter)> aux;
    aux = [&](OrgAdapter a) {
        SemId res = SemId::Nil();
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


SemId OrgConverter::convert(__args) {
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
        case org::SkipSpace: return convertSpace(p, a);
        // NOTE not sure what to do with this node kind when it reaches
        // this point
        case org::SkipAny: return convertSpace(p, a);
        case org::SkipNewline: return convertNewline(p, a);
        case org::Quote: return convertMarkQuote(p, a);
        case org::QuoteBlock: return convertQuote(p, a);
        case org::Colon: return convertPunctuation(p, a);
        case org::CommandInclude: return convertInclude(p, a);
        case org::Symbol: return convertSymbol(p, a);
        case org::Angle: return convertPlaceholder(p, a);
        case org::Footnote: {
            if (a.size() == 1) {
                return convertLink(p, a);
            } else {
                LOG(FATAL)
                    << "TODO implement conversion of nested footnote";
            }
        }

        case org::CommandCaption: {
            // TODO update parent nodes after restructuring
            Vec<SemId> nested = flatConvertAttached(p, a);
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
                SemIdT<CommandGroup> group = Sem<CommandGroup>(p, a);
                for (const auto& it : nested) {
                    group->attached.push_back(it);
                }
                return group;
            }
        }

        default:
            LOG(FATAL) << fmt("Unhandled node type {} {}", a.kind(), a.id);
            return Sem<Empty>(p, a);
    }
#undef CASE
}

void fillDocumentOptions(SemIdT<DocumentOptions> opts, OrgAdapter a) {
    if (opts->isGenerated()) { opts->original = a; }
    auto item = a.at(0);
    for (auto const& value : item.val().getText().split(' ')) {
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
                    opts->tocExport = true;
                } else if (tail == "nil") {
                    opts->tocExport = false;
                } else if ('0' <= tail[0] && tail[0] <= '9') {
                    opts->tocExport = tail.toInt();
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

SemIdT<Document> OrgConverter::toDocument(OrgAdapter adapter) {
    SemIdT<Document> doc = Sem<Document>(SemId::Nil(), adapter);
    doc->options         = Sem<DocumentOptions>(doc, adapter);
    using Prop           = Subtree::Property;

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
                    res.latexClass = sub.at(0).val().getText();
                    doc->options->properties.push_back(Prop(res));
                    break;
                }
                case org::LatexHeader: {
                    Prop::ExportLatexHeader res{};
                    res.header = sub.at(0).val().getText();
                    doc->options->properties.push_back(Prop(res));
                    break;
                }
                case org::LatexCompiler: {
                    Prop::ExportLatexCompiler res{};
                    res.compiler = sub.at(0).val().getText();
                    doc->options->properties.push_back(Prop(res));
                    break;
                }
                case org::LatexClassOptions: {
                    auto value = sub.at(0).val().getText();
                    if (value.starts_with('[')) {
                        LOG(FATAL) << "TODO";
                        // value.remove('[');
                    }
                    if (value.starts_with(']')) {
                        LOG(FATAL) << "TODO";
                        //  value = value.chopped(1);
                    }

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


    doc.eachSubnodeRec([&](sem::SemId const& org) {
        switch (org->getKind()) {
            case osk::Subtree: {
                auto subtree = org.as<Subtree>();
                if (auto id = subtree->treeId) {
                    doc->idTable.insert({id.value(), org});
                }

                break;
            }

            case osk::Paragraph: {
                auto par = org.as<Paragraph>();
                if (par->isFootnoteDefinition()) {
                    auto tag = par->at(0).as<Footnote>()->tag;
                    doc->footnoteTable.insert({tag, par});
                }
                break;
            }
        }
    });


    return doc;
}
