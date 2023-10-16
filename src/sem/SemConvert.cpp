#include <sem/SemConvert.hpp>
#include <hstd/stdlib/Func.hpp>
#include <parse/OrgSpec.hpp>
#include <QDateTime>

#include <hstd/stdlib/Debug.hpp>

#include <boost/preprocessor/facilities/overload.hpp>
#include <boost/preprocessor/facilities/empty.hpp>
#include <hstd/wrappers/perfetto_aux.hpp>
#include <exporters/exportertree.hpp>

#ifdef USE_PERFETTO
#    define __perf_trace(name) TRACE_EVENT("convert", name);
#else
#    define __perf_trace(a)
#endif

#define __INIT_REPORT(__subname, __node)                                  \
    (Report{                                                              \
        .location = __CURRENT_FILE_PATH__,                                \
        .line     = __LINE__,                                             \
        .name     = __func__,                                             \
        .subname  = __subname,                                            \
        .node     = __node,                                               \
    })

#define __trace2(__subname, __lex)                                        \
    {                                                                     \
        Report rep = __INIT_REPORT(__subname, __lex);                     \
        rep.kind   = ReportKind::Enter;                                   \
        rep.name   = __func__;                                            \
        report(rep);                                                      \
    }                                                                     \
                                                                          \
    finally CONCAT(close, __COUNTER__) = finally::init<Str>(              \
        ([&](CR<Str> name) {                                              \
            Report rep = __INIT_REPORT(__subname, __lex);                 \
            rep.kind   = ReportKind::Leave;                               \
            rep.name   = name;                                            \
            report(rep);                                                  \
        }),                                                               \
        Str(__func__));


#define __trace1(__subname) __trace2(__subname, a)
#define __trace0() __trace2(std::nullopt, a)

#define __trace(...)                                                      \
    BOOST_PP_CAT(                                                         \
        BOOST_PP_OVERLOAD(__trace, __VA_ARGS__)(__VA_ARGS__),             \
        BOOST_PP_EMPTY())


#define __field3(__field, __subname, __lex)                               \
    {                                                                     \
        Report rep = __INIT_REPORT(__subname, __lex);                     \
        rep.kind   = ReportKind::EnterField;                              \
        rep.field  = __field;                                             \
        report(rep);                                                      \
    }                                                                     \
                                                                          \
    finally CONCAT(close, __COUNTER__) = finally::init<Str>(              \
        ([&](CR<Str> name) {                                              \
            Report rep = __INIT_REPORT(__subname, __lex);                 \
            rep.kind   = ReportKind::LeaveField;                          \
            rep.name   = name;                                            \
            rep.field  = __field;                                         \
            report(rep);                                                  \
        }),                                                               \
        Str(__func__));


#define __field2(__field, __subname) __field3(__field, __subname, a)
#define __field1(__field) __field3(__field, std::nullopt, a)

#define __field(...)                                                      \
    BOOST_PP_CAT(                                                         \
        BOOST_PP_OVERLOAD(__field, __VA_ARGS__)(__VA_ARGS__),             \
        BOOST_PP_EMPTY())


#define __json3(__org_node, __subname, __a)                               \
    {                                                                     \
        Report rep    = __INIT_REPORT(__subname, __a);                    \
        rep.kind      = ReportKind::Json;                                 \
        rep.semResult = __org_node;                                       \
        report(rep);                                                      \
    }

#define __json2(__org_node, __subname) __json3(__org_node, __subname, a);
#define __json1(__org_node) __json3(__org_node, std::nullopt, a);

#define __json(...)                                                       \
    BOOST_PP_CAT(                                                         \
        BOOST_PP_OVERLOAD(__json, __VA_ARGS__)(__VA_ARGS__),              \
        BOOST_PP_EMPTY())


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
        qWarning() << "Unexpected value to parse big ident" << id;
        return K::Done;
    }
}

SemIdT<Table> OrgConverter::convertTable(__args) {
    __perf_trace("convertTable");
    __trace();
    auto result = Sem<Table>(p, a);

    return result;
};


SemIdT<HashTag> OrgConverter::convertHashTag(__args) {
    __perf_trace("convertHashTag");
    __trace();
    auto                              result = Sem<HashTag>(p, a);
    Func<SemIdT<HashTag>(OrgAdapter)> aux;
    result->head = strip(a.at(0).strVal(), CharSet{'#'}, CharSet{});

    aux = [p, &aux, this](OrgAdapter a) -> SemIdT<HashTag> {
        SemIdT<HashTag> result = Sem<HashTag>(p, a);
        result->head           = strip(
            a.at(0).strVal(), CharSet{'#'}, CharSet{});
        if (1 < a.size()) {
            for (auto& node : a.at(slice(1, 1_B))) {
                result->subtags.push_back(aux(node));
            }
        }
        return result;
    };

    if (1 < a.size()) {
        for (auto& node : a.at(slice(1, 1_B))) {
            result->subtags.push_back(aux(node));
        }
    }

    return result;
};

SemIdT<SubtreeLog> OrgConverter::convertSubtreeLog(__args) {
    __perf_trace("convertHashTag");
    auto log = Sem<SubtreeLog>(p, a);

    using Entry = SubtreeLog::LogEntry;
    using Log   = SubtreeLog;


    if (a.kind() == org::LogbookEntry) {
        auto head = one(a, N::Header);
        switch (head.kind()) {
            case org::LogbookTagChange: {
                Log::Tag tag;
                tag.tag   = convertHashTag(log, one(head, N::Tag));
                tag.added = one(head, N::State).strVal() == "Added";
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
                    one(head, N::Oldstate).strVal());
                state.to = parseBigIdent(one(head, N::Newstate).strVal());
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
                DLOG(INFO) << "Unexpected incoming tree kind for subtree "
                            "converter"
                         << head.kind();
                DLOG(INFO).noquote() << head.treeRepr();
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
    __perf_trace("convertSubtreeDrawer");
    __trace();
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
            }
        }
    }
}

void OrgConverter::convertPropertyList(SemIdT<Subtree>& tree, In a) {
    __perf_trace("convertPropertyList");
    __trace();

    std::string       name = normalize(strip(
        one(a, N::Name).strVal(),
        CharSet{':'},
        CharSet{':'}));
    Opt<Property> result;
    if (name == "exportoptions") {
        Property::ExportOptions res;
        res.backend = one(a, N::Subname).strVal();
        for (std::string const& pair : one(a, N::Values).strVal().split(' ')) {
            auto kv           = pair.split(':');
            res.values[kv[0]] = kv[1];
        }

        result = Property(res);

    } else if (name == "id") {
        tree->treeId = one(a, N::Values).strVal();

    } else if (name == "created") {
        Property::Created created;
        created.time = convertTime(tree, one(a, N::Values));
        result       = Property(created);

    } else if (name == "origin") {
        Property::Origin origin;
        origin.text = one(a, N::Values).strVal();
        result      = Property(origin);

    } else if (name == "visibility") {
        if (auto visibility = parseOrgEnum<
                sem::Subtree::Property::Visibility::Level>(
                one(a, N::Values).strVal());
            visibility) {
            Property::Visibility prop;
            prop.level = visibility.value();
            result     = Property(prop);
        }

    } else if (name == "effort") {
        std::string const&   value    = one(a, N::Values).strVal();
        auto             duration = value.split(":");
        Property::Effort prop;

        if (duration.length() == 1) {
            prop.minutes = duration[0].toInt();
        } else if (duration.length() == 2) {
            prop.minutes = duration[0].toInt();
            prop.hours   = duration[1].toInt();
        }

        result = Property(prop);

    } else {
        qCritical().noquote() << "Unknown property name" << name << "\n"
                              << a.treeRepr();
    }

    if (result) {
        const auto inh = one(a, N::InheritanceMode).strVal();
        if (inh == "!!") {
            result->inheritanceMode = Property::InheritanceMode::OnlyThis;
        } else if (inh == "!") {
            result->inheritanceMode = Property::InheritanceMode::OnlySub;
        }

        const auto sub = one(a, N::SubSetRule).strVal();
        if (sub == "+") {
            result->subSetRule = Property::SetMode::Add;
        } else if (sub == "-") {
            result->subSetRule = Property::SetMode::Subtract;
        }

        const auto main = one(a, N::MainSetRule).strVal();
        if (main == "+") {
            result->subSetRule = Property::SetMode::Add;
        } else if (main == "-") {
            result->subSetRule = Property::SetMode::Subtract;
        }

        tree->properties.push_back(*result);
    }
}

SemIdT<Subtree> OrgConverter::convertSubtree(__args) {
    __perf_trace("convertSubtree");
    __trace();
    auto tree = Sem<Subtree>(p, a);

    tree->level = one(a, N::Prefix).strVal().size();

    {
        __field(N::Title);
        __place(osp::TreeTitle);
        tree->title = convertParagraph(tree, one(a, N::Title));
    }

    { __field(N::Todo); }

    {
        __field(N::Tags);
        for (const auto& hash : one(a, N::Tags)) {
            tree->tags.push_back(convertHashTag(tree, hash));
        }
    }

    {
        __field(N::Drawer);
        convertSubtreeDrawer(tree, one(a, N::Drawer));
    }

    {
        __field(N::Body);
        __place(osp::TreeBody);
        for (auto const& sub : one(a, N::Body)) {
            auto subres = convert(tree, sub);
            tree->push_back(subres);
        }
    }

    return tree;
}

SemIdT<Time> OrgConverter::convertTime(__args) {
    __perf_trace("convertTime");
    __trace();

    Q_ASSERT_X(
        ((OrgSet{
              org::DynamicActiveTime,
              org::DynamicInactiveTime,
              org::StaticActiveTime,
              org::StaticInactiveTime,
          })
             .contains(a.kind())),
        "convert subtree",
        to_string(a.kind()));

    auto time      = Sem<Time>(p, a);
    time->isActive = (a.kind() == org::DynamicActiveTime)
                  || (a.kind() == org::StaticActiveTime);

    if (a.kind() == org::DynamicInactiveTime
        || a.kind() == org::DynamicActiveTime) {
        time->time = Time::Dynamic{.expr = a.strVal()};
    } else if (
        a.kind() == org::StaticActiveTime
        || a.kind() == org::StaticInactiveTime) {
        Str repeat      = one(a, N::Repeater).strVal();
        using Mode      = Time::Repeat::Mode;
        Mode repeatMode = Mode::None;

        if (0 < repeat.size()) {
            if (repeat.startsWith("++")) {
                repeatMode = Mode::FirstMatch;
                repeat     = repeat.dropPrefix("++");
            } else if (repeat.startsWith(".+")) {
                repeatMode = Mode::SameDay;
                repeat     = repeat.dropPrefix(".+");
            } else if (repeat.startsWith("+")) {
                repeatMode = Mode::Exact;
                repeat     = repeat.dropPrefix("+");
            }
        }

        std::string datetime;
        if (one(a, N::Year).kind() != org::Empty) {
            datetime += one(a, N::Year).strVal();
        }

        if (one(a, N::Clock).kind() != org::Empty) {
            if (!datetime.isEmpty()) {
                datetime += " ";
            }
            datetime += one(a, N::Clock).strVal();
        }

        struct Spec {
            std::string pattern;
            bool    useTime = true;
            bool    useDate = true;
        };

        Vec<Spec> formats = {
            Spec{.pattern = "yyyy-MM-dd HH:mm:ss"},
            Spec{.pattern = "yyyy/MM/dd HH:mm:ss"},
            Spec{.pattern = "dd-MM-yyyy HH:mm:ss"},
            Spec{.pattern = "dd/MM/yyyy HH:mm:ss"},
            Spec{.pattern = "yyyy-MM-dd HH:mm"},
            Spec{.pattern = "HH:mm", .useDate = false},
            Spec{.pattern = "yyyy-MM-dd", .useTime = false},
            // Add other formats as needed
        };

        QDateTime parsedDateTime;
        Spec      matching;
        for (const auto& format : formats) {
            parsedDateTime = QDateTime::fromString(
                datetime, format.pattern);
            if (parsedDateTime.isValid()) {
                matching = format;
                break;
            }
        }

        if (!parsedDateTime.isValid()) {
            // TODO implement proper, non-fatal error reporting
            qFatal(strdup(
                "Could not parse date time entry in format: $# at $#"
                % to_string_vec(datetime, getLocMsg(a))));
        }

        time->time = Time::Static{
            .time = UserTime(
                parsedDateTime, matching.useDate, matching.useTime)};

        if (repeatMode != Mode::None) {
            time->getStatic().repeat = Time::Repeat{
                .mode = repeatMode,
            };
        }
    }

    __json(time);
    return time;
}

SemIdT<TimeRange> OrgConverter::convertTimeRange(__args) {
    __perf_trace("convertTimeRange");
    __trace();
    auto range = Sem<TimeRange>(p, a);
    {
        __field(N::From);
        range->from = convertTime(range, one(a, N::From));
    }
    {
        __field(N::To);
        range->to = convertTime(range, one(a, N::To));
    }
    return range;
}

SemIdT<Macro> OrgConverter::convertMacro(__args) {
    __perf_trace("convertMacro");
    __trace();
    auto macro = Sem<Macro>(p, a);


    return macro;
}

SemIdT<Symbol> OrgConverter::convertSymbol(__args) {
    __perf_trace("convertSymbol");
    __trace();
    auto sym = Sem<Symbol>(p, a);

    int idx = 0;
    for (const auto& sub : a) {
        if (idx == 0) {
            sym->name = sub.strVal();
        } else if (sub.kind() == org::RawText) {
            auto params = sub.strVal().split(" ");
            for (int i = 0; i < params.size();) {
                if (params.at(i).startsWith(":")
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

    __perf_trace("convertParagraph");
    __trace();
    auto par   = Sem<Paragraph>(p, a);
    bool first = true;
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
    __perf_trace("convertStmtList");
    __trace();
    auto stmt = Sem<StmtList>(p, a);

    for (OrgAdapter const& sub : a) {
        stmt.push_back(convert(stmt, sub));
    }

    return stmt;
}


SemIdT<Footnote> OrgConverter::convertFootnote(__args) {
    __perf_trace("convertLink");
    __trace();
    if (a.kind() == org::InlineFootnote) {
        auto note        = Sem<Footnote>(p, a);
        note->definition = convert(note, a[0]);
        return note;
    } else {
        auto link = Sem<Footnote>(p, a);
        if (a.size() == 1) {
            link->tag = a[0].strVal();
        } else {
            qFatal("TODO");
        }

        return link;
    }
}

SemIdT<Link> OrgConverter::convertLink(__args) {
    __perf_trace("convertLink");
    __trace();
    auto link = Sem<Link>(p, a);
    if (a.kind() == org::RawLink) {
        link->data = Link::Raw{.text = a.strVal()};

    } else if (a.kind() == org::Footnote) {
        link->data = Link::Footnote{.target = one(a, N::Name).strVal()};

    } else {
        Str protocol = normalize(one(a, N::Protocol).strVal());
        if (protocol == "") {
            link->data = Link::Raw{.text = one(a, N::Link).strVal()};
        } else if (protocol == "id") {
            link->data = Link::Id{.text = one(a, N::Link).strVal()};

        } else if (protocol == "person") {
            link->data = Link::Person{.name = one(a, N::Link).strVal()};

        } else if (protocol == "file") {
            link->data = Link::File{.file = one(a, N::Link).strVal()};

        } else {
            qCritical().noquote()
                << "Unhandled protocol kind" << protocol << "\n"
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
    __perf_trace("convertList");
    __trace();
    auto list = Sem<List>(p, a);
    for (const auto& it : a) {
        list.push_back(convert(list, it));
    }

    return list;
}

SemIdT<ListItem> OrgConverter::convertListItem(__args) {
    __perf_trace("convertListItem");
    __trace();
    auto item = Sem<ListItem>(p, a);
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
    __perf_trace("convertCaption");
    __trace();
    auto caption  = Sem<Caption>(p, a);
    caption->text = convertParagraph(caption, one(a, N::Args)[0]);

    return caption;
}


SemIdT<Word> OrgConverter::convertWord(__args) {
    __trace();
    return SemLeaf<Word>(p, a);
}

SemIdT<Placeholder> OrgConverter::convertPlaceholder(__args) {
    __perf_trace("convertPlaceholder");
    __trace();
    return SemLeaf<Placeholder>(p, a);
}

SemIdT<Newline> OrgConverter::convertNewline(__args) {
    __trace();
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
    __trace();
    return SemLeaf<Punctuation>(p, a);
}

SemIdT<BigIdent> OrgConverter::convertBigIdent(__args) {
    __perf_trace("convertBigIdent");
    __trace();
    return SemLeaf<BigIdent>(p, a);
}

SemIdT<sem::ParseError> OrgConverter::convertParseError(__args) {
    return Sem<sem::ParseError>(p, a);
}


SemIdT<MarkQuote> OrgConverter::convertMarkQuote(__args) {
    __perf_trace("convertMarkQuote");
    __trace();
    return convertAllSubnodes<MarkQuote>(p, a);
}

SemIdT<Verbatim> OrgConverter::convertVerbatim(__args) {
    __perf_trace("convertVerbatim");
    __trace();
    return convertAllSubnodes<Verbatim>(p, a);
}

SemIdT<Bold> OrgConverter::convertBold(__args) {
    __perf_trace("convertBold");
    __trace();
    return convertAllSubnodes<Bold>(p, a);
}

SemIdT<Monospace> OrgConverter::convertMonospace(__args) {
    __perf_trace("convertMonospace");
    __trace();
    return convertAllSubnodes<Monospace>(p, a);
}

SemIdT<Strike> OrgConverter::convertStrike(__args) {
    __perf_trace("convertStrike");
    __trace();
    return convertAllSubnodes<Strike>(p, a);
}

SemIdT<Par> OrgConverter::convertPar(__args) {
    __perf_trace("convertPar");
    __trace();
    return convertAllSubnodes<Par>(p, a);
}

SemIdT<Italic> OrgConverter::convertItalic(__args) {
    __perf_trace("convertItalic");
    __trace();
    return convertAllSubnodes<Italic>(p, a);
}

SemIdT<Underline> OrgConverter::convertUnderline(__args) {
    __perf_trace("convertUnderline");
    __trace();
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

    eexport->exporter   = one(a, N::Name).strVal();
    eexport->parameters = values;
    eexport->content    = one(a, N::Body).strVal();

    return eexport;
}

SemIdT<Center> OrgConverter::convertCenter(__args) {
    return convertAllSubnodes<Center>(p, a);
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
        qFatal("Unhanled kind for inline math TODO");
    }
}

SemIdT<Include> OrgConverter::convertInclude(__args) {
    SemIdT<Include> include = Sem<Include>(p, a);
    qWarning() << "TODO implement include";

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
    std::string             key    = one(a, N::Name).strVal();
    result->value              = one(a, N::Value).strVal();

    if (!key.isEmpty()) {
        result->key = key.remove(':');
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
                Q_ASSERT(ok); // TODO generate proper error message
            } else {
                result->positional.push_back(arg);
            }
        }
    } else {
        Q_ASSERT(a.getKind() == org::Empty);
    }

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
                qFatal(strdup(
                    "TODO unhandled kind $#" % to_string_vec(a.kind())));
        }

        Q_CHECK_PTR(res);
        result.push_back(res);
        if (OrgTrailableCommands.contains(a.kind())) {
            aux(one(a, N::Body));
        }
    };

    aux(a);

    return result;
}


SemId OrgConverter::convert(__args) {
    __trace();
    if (!a.isValid()) {
        qWarning() << "Invalid node encountered during conversion" << a.id;
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
        case org::Footnote: {
            if (a.size() == 1) {
                return convertLink(p, a);
            } else {
                qFatal("TODO");
            }
        }

        case org::CommandCaption: {
            // TODO update parent nodes after restructuring
            Vec<SemId> nested = flatConvertAttached(p, a);
            for (const auto& it : nested) {
                Q_CHECK_PTR(it);
            }

            Q_ASSERT_X(
                !nested.empty(),
                "nested command wrap",
                "Nested command result had size 0");

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
                Q_CHECK_PTR(trailed);
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
            qCritical() << "Unhandled node type" << a.kind() << __LINE__;
            //            qCritical().noquote() << a.treeRepr();
            return Sem<Empty>(p, a);
            //            throw wrapError(Err::UnhandledKind(a.kind()), a);
    }
#undef CASE
}

void fillDocumentOptions(SemIdT<DocumentOptions> opts, OrgAdapter a) {
    if (opts->isGenerated()) {
        opts->original = a;
    }

    for (OrgAdapter const& item : a) {
        std::string value = item.strVal();
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
                } else if (tail[0].isDigit()) {
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
            qCritical() << "Unexpected document option value" << value;
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
                    qWarning() << "TODO: Skipping 'columns' node";
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
                case org::LatexClass: {
                    Prop::ExportLatexClass res{};
                    res.latexClass = sub.at(0).strVal();
                    doc->options->properties.push_back(Prop(res));
                    break;
                }
                case org::LatexHeader: {
                    Prop::ExportLatexHeader res{};
                    res.header = sub.at(0).strVal();
                    doc->options->properties.push_back(Prop(res));
                    break;
                }
                case org::LatexCompiler: {
                    Prop::ExportLatexCompiler res{};
                    res.compiler = sub.at(0).strVal();
                    doc->options->properties.push_back(Prop(res));
                    break;
                }
                case org::LatexClassOptions: {
                    auto value = sub.at(0).strVal();
                    if (value.startsWith('[')) {
                        value.remove('[');
                    }
                    if (value.endsWith(']')) {
                        value = value.chopped(1);
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
