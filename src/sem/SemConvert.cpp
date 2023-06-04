#include <sem/SemConvert.hpp>
#include <hstd/stdlib/Func.hpp>
#include <parse/OrgSpec.hpp>
#include <QDateTime>

#include <hstd/stdlib/Debug.hpp>

#include <boost/preprocessor/facilities/overload.hpp>
#include <boost/preprocessor/facilities/empty.hpp>
#include <hstd/wrappers/perfetto_aux.hpp>

#ifdef USE_PERFETTO
#    define __perf_trace(name) TRACE_EVENT("convert", name);
#else
#    define __perf_trace(a)
#endif

#define __INIT_REPORT(__subname, __node)                                  \
    (Report{                                                              \
        .line     = __LINE__,                                             \
        .location = __CURRENT_FILE_PATH__,                                \
        .name     = __func__,                                             \
        .node     = __node,                                               \
        .subname  = __subname,                                            \
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
        rep.semResult = (__org_node).get();                               \
        report(rep);                                                      \
    }

#define __json2(__org_node, __subname) __json3(__org_node, __subname, a);
#define __json1(__org_node) __json3(__org_node, std::nullopt, a);

#define __json(...)                                                       \
    BOOST_PP_CAT(                                                         \
        BOOST_PP_OVERLOAD(__json, __VA_ARGS__)(__VA_ARGS__),              \
        BOOST_PP_EMPTY())

using namespace sem;

using org      = OrgNodeKind;
using otk      = OrgTokenKind;
using Err      = OrgConverter::Errors;
using Property = sem::Subtree::Property;

#define __args Org *p, OrgAdapter a

using N   = OrgSpecName;
using osk = OrgSemKind;


OrgAdapter one(OrgAdapter node, OrgSpecName name) {
    return spec.getSingleSubnode(node, name);
}

Vec<OrgAdapter> many(OrgAdapter node, OrgSpecName name) {
    return spec.getMultipleSubnode(node, name);
}

Wrap<Table> OrgConverter::convertTable(__args) {
    __perf_trace("convertTable");
    __trace();
    auto result = Sem<Table>(p, a);

    return result;
};


Wrap<HashTag> OrgConverter::convertHashTag(__args) {
    __perf_trace("convertHashTag");
    __trace();
    auto                            result = Sem<HashTag>(p, a);
    Func<Wrap<HashTag>(OrgAdapter)> aux;
    result->head = strip(a.at(0).strVal(), CharSet{QChar('#')}, CharSet{});

    aux = [p, &aux, this](OrgAdapter a) -> Wrap<HashTag> {
        Wrap<HashTag> result = Sem<HashTag>(p, a);
        result->head         = strip(
            a.at(0).strVal(), CharSet{QChar('#')}, CharSet{});
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

void OrgConverter::convertSubtreeDrawer(Wrap<Subtree>& tree, In a) {
    __perf_trace("convertSubtreeDrawer");
    __trace();
    if (a.kind() != org::Empty) {
        for (const auto& group : a) {
            switch (group.kind()) {
                case org::SubtreeDescription: {
                    tree->description = convertParagraph(
                        tree.get(), group[0]);
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

void OrgConverter::convertPropertyList(Wrap<Subtree>& tree, In a) {
    __perf_trace("convertPropertyList");
    __trace();

    QString       name = normalize(strip(
        one(a, N::Name).strVal(),
        CharSet{QChar(':')},
        CharSet{QChar(':')}));
    Opt<Property> result;
    if (name == "exportoptions") {
        Property::ExportOptions res;
        res.backend = one(a, N::Subname).strVal();
        for (QString const& pair : one(a, N::Values).strVal().split(' ')) {
            auto kv           = pair.split(':');
            res.values[kv[0]] = kv[1];
        }

        result = Property(res);

    } else if (name == "id") {
        tree->treeId = one(a, N::Values).strVal();

    } else if (name == "created") {
        Property::Created created;
        created.time = convertTime(tree.get(), one(a, N::Values));
        result       = Property(created);

    } else if (name == "origin") {
        Property::Origin origin;
        origin.text = one(a, N::Values).strVal();
        result      = Property(origin);

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

Wrap<Subtree> OrgConverter::convertSubtree(__args) {
    __perf_trace("convertSubtree");
    __trace();
    auto tree = Sem<Subtree>(p, a);

    tree->level = one(a, N::Prefix).strVal().size();

    {
        __field(N::Title);
        tree->title = convertParagraph(tree.get(), one(a, N::Title));
    }

    { __field(N::Todo); }

    {
        __field(N::Tags);
        for (const auto& hash : one(a, N::Tags)) {
            tree->tags.push_back(convertHashTag(tree.get(), hash));
        }
    }

    {
        __field(N::Drawer);
        convertSubtreeDrawer(tree, one(a, N::Drawer));
    }

    {
        __field(N::Body);
        for (auto const& sub : one(a, N::Body)) {
            tree->push_back(convert(tree.get(), sub));
        }
    }

    return tree;
}

Wrap<Time> OrgConverter::convertTime(__args) {
    __perf_trace("convertTime");
    __trace();
    auto time      = Sem<Time>(p, a);
    time->isActive = (a.kind() == org::DynamicActiveTime)
                  || (a.kind() == org::StaticActiveTime);

    if (a.kind() == org::DynamicInactiveTime
        || a.kind() == org::DynamicActiveTime) {
        time->time = Time::Dynamic{.expr = a.strVal()};
    } else {
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

        QString datetime;
        if (one(a, N::Year).kind() != org::Empty) {
            datetime += one(a, N::Year).strVal();
        }

        if (one(a, N::Clock).kind() != org::Empty) {
            if (!datetime.isEmpty()) {
                datetime += " ";
            }
            datetime += one(a, N::Clock).strVal();
        }

        Vec<QString> formats = {
            "yyyy-MM-dd HH:mm:ss",
            "yyyy/MM/dd HH:mm:ss",
            "dd-MM-yyyy HH:mm:ss",
            "dd/MM/yyyy HH:mm:ss",
            "yyyy-MM-dd HH:mm",
            "HH:mm",
            "yyyy-MM-dd",
            // Add other formats as needed
        };

        QDateTime parsedDateTime;
        for (const auto& format : formats) {
            parsedDateTime = QDateTime::fromString(datetime, format);
            if (parsedDateTime.isValid()) {
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
            .time = parsedDateTime,
        };
        if (repeatMode != Mode::None) {
            time->getStatic().repeat = Time::Repeat{
                .mode = repeatMode,
            };
        }
    }

    __json(time);
    return time;
}

Wrap<TimeRange> OrgConverter::convertTimeRange(__args) {
    __perf_trace("convertTimeRange");
    __trace();
    auto range = Sem<TimeRange>(p, a);
    {
        __field(N::From);
        range->from = convertTime(range.get(), one(a, N::From));
    }
    {
        __field(N::To);
        range->to = convertTime(range.get(), one(a, N::To));
    }
    return range;
}

Wrap<Paragraph> OrgConverter::convertParagraph(__args) {
    // TODO detect admonition paragraphs during conversion and store
    // information about this -- right now `NOTE:` is represented using
    // first two starting elements for paragraph subnodes.

    __perf_trace("convertParagraph");
    __trace();
    auto par   = Sem<Paragraph>(p, a);
    bool first = true;
    for (const auto& item : a) {
        if (first && item.kind() == org::Footnote) {
            par->push_back(convertFootnote(par.get(), item));
        } else {
            par->push_back(convert(par.get(), item));
        }
        first = false;
    }

    return par;
}

Wrap<StmtList> OrgConverter::convertStmtList(__args) {
    __perf_trace("convertStmtList");
    __trace();
    auto stmt = Sem<StmtList>(p, a);

    for (OrgAdapter const& sub : a) {
        stmt->push_back(convert(stmt.get(), sub));
    }

    return stmt;
}


Wrap<Footnote> OrgConverter::convertFootnote(__args) {
    __perf_trace("convertLink");
    __trace();
    auto link = Sem<Footnote>(p, a);
    if (a.size() == 1) {
        link->tag = a[0].strVal();
    } else {
        qFatal("TODO");
    }

    return link;
}

Wrap<Link> OrgConverter::convertLink(__args) {
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

        } else {
            qCritical().noquote()
                << "Unhandled protocol kind" << protocol << "\n"
                << a.treeRepr();
        }
    }

    if (a.kind() == org::Link) {
        if (one(a, N::Desc).kind() == org::Paragraph) {
            link->description = convertParagraph(
                link.get(), one(a, N::Desc));
        }
    }

    return link;
}

Wrap<List> OrgConverter::convertList(__args) {
    __perf_trace("convertList");
    __trace();
    auto list = Sem<List>(p, a);
    for (const auto& it : a) {
        list->push_back(convert(list.get(), it));
    }

    return list;
}

Wrap<ListItem> OrgConverter::convertListItem(__args) {
    __perf_trace("convertListItem");
    __trace();
    auto item = Sem<ListItem>(p, a);
    if (one(a, N::Header).kind() != org::Empty) {
        item->header = convertParagraph(item.get(), one(a, N::Header));
    }

    for (const auto& sub : one(a, N::Body)) {
        item->push_back(convert(item.get(), sub));
    }

    return item;
}

Wrap<Caption> OrgConverter::convertCaption(__args) {
    __perf_trace("convertCaption");
    __trace();
    auto caption  = Sem<Caption>(p, a);
    caption->text = convertParagraph(caption.get(), one(a, N::Args)[0]);

    return caption;
}


Wrap<Word> OrgConverter::convertWord(__args) {
    __trace();
    return SemLeaf<Word>(p, a);
}

Wrap<Placeholder> OrgConverter::convertPlaceholder(__args) {
    __perf_trace("convertPlaceholder");
    __trace();
    return SemLeaf<Placeholder>(p, a);
}

Wrap<Newline> OrgConverter::convertNewline(__args) {
    __trace();
    return SemLeaf<Newline>(p, a);
}

Wrap<Space> OrgConverter::convertSpace(__args) {
    return SemLeaf<Space>(p, a);
}

Wrap<Escaped> OrgConverter::convertEscaped(__args) {
    return SemLeaf<Escaped>(p, a);
}

Wrap<RawText> OrgConverter::convertRawText(__args) {
    return SemLeaf<RawText>(p, a);
}

Wrap<Punctuation> OrgConverter::convertPunctuation(__args) {
    __trace();
    return SemLeaf<Punctuation>(p, a);
}

Wrap<BigIdent> OrgConverter::convertBigIdent(__args) {
    __perf_trace("convertBigIdent");
    __trace();
    return SemLeaf<BigIdent>(p, a);
}

Wrap<sem::ParseError> OrgConverter::convertParseError(__args) {
    return Sem<sem::ParseError>(p, a);
}


Wrap<MarkQuote> OrgConverter::convertMarkQuote(__args) {
    __perf_trace("convertMarkQuote");
    __trace();
    return convertAllSubnodes<MarkQuote>(p, a);
}

Wrap<Verbatim> OrgConverter::convertVerbatim(__args) {
    __perf_trace("convertVerbatim");
    __trace();
    return convertAllSubnodes<Verbatim>(p, a);
}

Wrap<Bold> OrgConverter::convertBold(__args) {
    __perf_trace("convertBold");
    __trace();
    return convertAllSubnodes<Bold>(p, a);
}

Wrap<Monospace> OrgConverter::convertMonospace(__args) {
    __perf_trace("convertMonospace");
    __trace();
    return convertAllSubnodes<Monospace>(p, a);
}

Wrap<Strike> OrgConverter::convertStrike(__args) {
    __perf_trace("convertStrike");
    __trace();
    return convertAllSubnodes<Strike>(p, a);
}

Wrap<Par> OrgConverter::convertPar(__args) {
    __perf_trace("convertPar");
    __trace();
    return convertAllSubnodes<Par>(p, a);
}

Wrap<Italic> OrgConverter::convertItalic(__args) {
    __perf_trace("convertItalic");
    __trace();
    return convertAllSubnodes<Italic>(p, a);
}

Wrap<Underline> OrgConverter::convertUnderline(__args) {
    __perf_trace("convertUnderline");
    __trace();
    return convertAllSubnodes<Underline>(p, a);
}

Wrap<Example> OrgConverter::convertExample(__args) {
    return convertAllSubnodes<Example>(p, a);
}

Wrap<Center> OrgConverter::convertCenter(__args) {
    return convertAllSubnodes<Center>(p, a);
}

Wrap<AdmonitionBlock> OrgConverter::convertAdmonitionBlock(__args) {
    return convertAllSubnodes<AdmonitionBlock>(p, a);
}

Wrap<Quote> OrgConverter::convertQuote(__args) {
    Wrap<Quote> quote = Sem<Quote>(p, a);
    quote->text       = convertParagraph(quote.get(), a[0]);
    return quote;
}

Wrap<LatexBody> OrgConverter::convertMath(__args) {
    Wrap<LatexBody> result;
    if (a.kind() == org::InlineMath) {
        result = Sem<InlineMath>(p, a);
    } else {
        qFatal("Unhanled kind for inline math TODO");
    }

    return result;
}

Wrap<Include> OrgConverter::convertInclude(__args) {
    Wrap<Include> include = Sem<Include>(p, a);
    qWarning() << "TODO implement include";

    return include;
}

Wrap<TextSeparator> OrgConverter::convertTextSeparator(__args) {
    return Sem<TextSeparator>(p, a);
}

Wrap<AtMention> OrgConverter::convertAtMention(__args) {
    return SemLeaf<AtMention>(p, a);
}


Vec<Wrap<Org>> OrgConverter::flatConvertAttached(__args) {
    Vec<Wrap<Org>>         result;
    Func<void(OrgAdapter)> aux;
    aux = [&](OrgAdapter a) {
        Wrap<Org> res;
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


Wrap<Org> OrgConverter::convert(__args) {
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
        case org::Footnote: {
            if (a.size() == 1) {
                return convertLink(p, a);
            } else {
                qFatal("TODO");
            }
        }

        case org::CommandCaption: {
            // TODO update parent nodes after restructuring
            Vec<Wrap<Org>> nested = flatConvertAttached(p, a);
            for (const auto& it : nested) {
                Q_CHECK_PTR(it);
            }

            Q_ASSERT_X(
                !nested.empty(),
                "nested command wrap",
                "Nested command result had size 0");

            if (nested.size() == 1) {
                return nested[0];
            } else if (SemTrailableCommands.contains(
                           nested.back()->getKind())) {
                // Get last wrapped statement
                Wrap<Stmt> trailed = nested.back()->as<Stmt>();
                for (const auto& it : nested[slice(0, 2_B)]) {
                    trailed->attached.push_back(it->as<Attached>());
                }
                return trailed;

            } else {
                Wrap<CommandGroup> group = Sem<CommandGroup>(p, a);
                for (const auto& it : nested) {
                    group->attached.push_back(it->as<Attached>());
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

void fillDocumentOptions(Wrap<DocumentOptions> opts, OrgAdapter a) {
    if (opts->isGenerated()) {
        opts->original = a;
    }

    for (OrgAdapter const& item : a) {
        QString value = item.strVal();
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

Wrap<Document> OrgConverter::toDocument(OrgAdapter adapter) {
    Wrap<Document> doc = Sem<Document>(nullptr, adapter);
    doc->options       = Sem<DocumentOptions>(doc.get(), adapter);
    using Prop         = Subtree::Property;

    if (adapter.kind() == org::StmtList) {
        for (const auto& sub : adapter) {
            switch (sub.kind()) {
                case org::Columns: {
                    qWarning() << "TODO: Skipping 'columns' node";
                    break;
                }
                case org::CommandTitle: {
                    doc->title = convertParagraph(doc.get(), sub[0]);
                    break;
                }
                case org::CommandOptions: {
                    fillDocumentOptions(doc->options, sub);
                    break;
                }
                case org::LatexClass: {
                    doc->options->properties.push_back(
                        Prop(Prop::ExportLatexClass{sub.at(0).strVal()}));
                    break;
                }
                case org::LatexHeader: {
                    doc->options->properties.push_back(
                        Prop(Prop::ExportLatexHeader{sub.at(0).strVal()}));
                    break;
                }
                case org::LatexCompiler: {
                    doc->options->properties.push_back(Prop(
                        Prop::ExportLatexCompiler{sub.at(0).strVal()}));
                    break;
                }
                default: {
                    doc->subnodes.push_back(convert(doc.get(), sub));
                    break;
                }
            }
        }
    } else {
        doc->subnodes.push_back(convert(doc.get(), adapter));
    }

    qInfo() << "Finished subtree walker";
    return doc;

    doc->assignIds();
    qInfo() << "Assigned IDs";
    doc->eachSubnodeRec([&](Org::Ptr const& org) {
        doc->backPtr[org->id.value()] = org;

        switch (org->getKind()) {
            case osk::Subtree: {
                auto subtree = org->as<Subtree>();
                if (auto id = subtree->treeId) {
                    doc->idTable[id.value()] = org->id.value();
                }

                break;
            }

            case osk::Paragraph: {
                auto par = org->as<Paragraph>();
                if (par->isFootnoteDefinition()) {
                    doc->footnoteTable[par->at(0)->as<Footnote>()->tag] = par->id
                                                                              .value();
                }
                break;
            }
        }
    });


    return doc;
}
