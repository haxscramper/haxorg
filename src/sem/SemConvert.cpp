#include <sem/SemConvert.hpp>
#include <hstd/stdlib/Func.hpp>
#include <parse/OrgSpec.hpp>
#include <QDateTime>

#include <hstd/stdlib/Debug.hpp>

#include <boost/preprocessor/facilities/overload.hpp>
#include <boost/preprocessor/facilities/empty.hpp>


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
    __trace();
    auto result = Sem<Table>(p, a);

    return result;
};


Wrap<HashTag> OrgConverter::convertHashTag(__args) {
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

Wrap<Subtree> OrgConverter::convertSubtree(__args) {
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
        OrgAdapter drawer = one(a, N::Drawer);
        if (drawer.kind() != org::Empty) {
            for (const auto& group : drawer) {
                switch (group.kind()) {
                    case org::SubtreeDescription: {
                        tree->description = convertParagraph(
                            tree.get(), group[0]);
                        break;
                    }

                    case org::PropertyList: {
                        for (const auto& prop : group) {
                            QString name = normalize(strip(
                                one(prop, N::Name).strVal(),
                                CharSet{QChar(':')},
                                CharSet{QChar(':')}));
                            if (name == "exportoptions") {
                                Property::ExportOptions res;
                                res.backend = one(prop, N::Subname)
                                                  .strVal();
                                for (QString const& pair :
                                     one(prop, N::Values)
                                         .strVal()
                                         .split(' ')) {
                                    auto kv           = pair.split(':');
                                    res.values[kv[0]] = kv[1];
                                }
                                tree->properties.push_back(Property(res));

                            } else if (name == "id") {
                                tree->id = one(prop, N::Values).strVal();

                            } else {
                                qCritical().noquote()
                                    << "Unknown property name" << name
                                    << "\n"
                                    << prop.treeRepr();
                            }
                        }
                        break;
                    }
                }
            }
        }
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
        datetime += one(a, N::Year).strVal();
        if (one(a, N::Clock).kind() != org::Empty) {
            datetime += " ";
            datetime += one(a, N::Clock).strVal();
        }

        Vec<QString> formats = {
            "yyyy-MM-dd HH:mm:ss",
            "yyyy/MM/dd HH:mm:ss",
            "dd-MM-yyyy HH:mm:ss",
            "dd/MM/yyyy HH:mm:ss",
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
                "Could not parse date time entry in format: $#"
                % to_string_vec(datetime)));
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

    __trace();
    auto par = Sem<Paragraph>(p, a);
    for (const auto& item : a) {
        par->push_back(convert(par.get(), item));
    }

    return par;
}

Wrap<StmtList> OrgConverter::convertStmtList(__args) {
    auto stmt = Sem<StmtList>(p, a);

    for (OrgAdapter const& sub : a) {
        stmt->push_back(convert(stmt.get(), sub));
    }

    return stmt;
}


Wrap<Link> OrgConverter::convertLink(__args) {
    __trace();
    auto link = Sem<Link>(p, a);
    if (a.kind() == org::RawLink) {
        link->data = Link::Raw{.text = a.strVal()};

    } else if (a.kind() == org::Footnote) {
        link->data = Link::Footnote{.target = a.strVal()};

    } else {
        Str protocol = normalize(one(a, N::Protocol).strVal());
        if (protocol == "") {
            link->data = Link::Raw{.text = one(a, N::Link).strVal()};
        } else if (protocol == "id") {
            link->data = Link::Id{.text = one(a, N::Link).strVal()};
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
    __trace();
    auto list = Sem<List>(p, a);
    for (const auto& it : a) {
        list->push_back(convert(list.get(), it));
    }

    return list;
}

Wrap<ListItem> OrgConverter::convertListItem(__args) {
    __trace();
    auto item = Sem<ListItem>(p, a);

    return item;
}

Wrap<Caption> OrgConverter::convertCaption(__args) {
    __trace();
    auto caption  = Sem<Caption>(p, a);
    caption->text = convertParagraph(caption.get(), one(a, N::Args)[0]);

    return caption;
}

// clang-format off
Wrap<Word> OrgConverter::convertWord(__args) { __trace(); return SemLeaf<Word>(p, a); }
Wrap<Placeholder> OrgConverter::convertPlaceholder(__args) { __trace(); return SemLeaf<Placeholder>(p, a); }
Wrap<Newline> OrgConverter::convertNewline(__args) { __trace(); return SemLeaf<Newline>(p, a); }
Wrap<Space> OrgConverter::convertSpace(__args) { return SemLeaf<Space>(p, a); }
Wrap<RawText> OrgConverter::convertRawText(__args) { return SemLeaf<RawText>(p, a); }
Wrap<Punctuation> OrgConverter::convertPunctuation(__args) { __trace(); return SemLeaf<Punctuation>(p, a); }
Wrap<BigIdent> OrgConverter::convertBigIdent(__args) { __trace(); return SemLeaf<BigIdent>(p, a); }
// clang-format on


// clang-format off
Wrap<MarkQuote> OrgConverter::convertMarkQuote(__args) { __trace(); return convertAllSubnodes<MarkQuote>(p, a); }
Wrap<Verbatim> OrgConverter::convertVerbatim(__args) { __trace(); return convertAllSubnodes<Verbatim>(p, a); }
Wrap<Bold> OrgConverter::convertBold(__args) { __trace(); return convertAllSubnodes<Bold>(p, a); }
Wrap<Par> OrgConverter::convertPar(__args) { __trace(); return convertAllSubnodes<Par>(p, a); }
Wrap<Italic> OrgConverter::convertItalic(__args) { __trace(); return convertAllSubnodes<Italic>(p, a); }
// clang-format on


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

Vec<Wrap<Org>> OrgConverter::flatConvertAttached(__args) {
    Vec<Wrap<Org>>         result;
    Func<void(OrgAdapter)> aux;
    qDebug() << "Fat convert of" << a.kind();
    aux = [&](OrgAdapter a) {
        qDebug() << "Recursing over" << a.kind();
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
        CASE(Punctuation);
        CASE(Link);
        CASE(Par);
        CASE(BigIdent);
        CASE(Verbatim);
        CASE(RawText);
        CASE(List);
        CASE(ListItem);
        CASE(Placeholder);
        case org::InlineMath: return convertMath(p, a);
        case org::RawLink: return convertLink(p, a);
        case org::StaticActiveTime:
        case org::StaticInactiveTime:
        case org::DynamicActiveTime:
        case org::DynamicInactiveTime: return convertTime(p, a);
        case org::SkipSpace: return convertSpace(p, a);
        case org::SkipNewline: return convertNewline(p, a);
        case org::Quote: return convertMarkQuote(p, a);
        case org::QuoteBlock: return convertQuote(p, a);
        case org::Colon: return convertPunctuation(p, a);
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
            qCritical() << "Unhandled node type";
            qCritical().noquote() << a.treeRepr();
            throw wrapError(Err::UnhandledKind(a.kind()), a);
    }
#undef CASE
}

Wrap<Document> OrgConverter::toDocument(OrgAdapter adapter) {
    Wrap<Document> doc = Sem<Document>(nullptr, adapter);

    if (adapter.kind() == org::StmtList) {
        for (const auto& sub : adapter) {
            if (sub.kind() == org::CommandTitle) {
                doc->title = convertParagraph(doc.get(), sub[0]);
            } else {
                doc->subnodes.push_back(convert(doc.get(), sub));
            }
        }
    } else {
        doc->subnodes.push_back(convert(doc.get(), adapter));
    }


    Func<void(Org*)> auxDocument;
    auxDocument = [&](Org* org) {
        switch (org->getKind()) {
            case osk::Subtree: {
                auto subtree = org->as<Subtree>();
                if (auto id = subtree->id) {
                    doc->idTable[id.value()] = subtree;
                }

                for (const auto& item : org->subnodes) {
                    auxDocument(item.get());
                }
                break;
            }

            default: {
                for (const auto& item : org->subnodes) {
                    auxDocument(item.get());
                }
                break;
            }

                // case orgAnnotatedParagraph:
                //     switch (org.paragraph.kind) {
                //         case aopFootnote:
                //             doc.footnoteTable[org.paragraph.footnote.ident]
                //             = org; break;

                //         default:
                //             break;
                //     }
                //     break;

                // default:
                //     break;
        }
    };


    return doc;
}
