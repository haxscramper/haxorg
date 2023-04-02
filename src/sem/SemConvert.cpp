#include <sem/SemConvert.hpp>
#include <hstd/stdlib/Func.hpp>
#include <parse/OrgSpec.hpp>
#include <QDateTime>

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
using namespace properties;

using org = OrgNodeKind;
using otk = OrgTokenKind;
using Err = OrgConverter::Errors;

template <typename T>
Wrap<T> Sem(sem::Org* parent, OrgAdapter adapter) {
    return std::make_shared<T>(parent, adapter);
}

template <typename T>
Wrap<T> SemLeaf(sem::Org* parent, OrgAdapter adapter) {
    auto res  = Sem<T>(parent, adapter);
    res->text = adapter.strVal();
    return res;
}

#define __args Org *p, OrgAdapter a

using N = OrgSpecName;


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
    auto                      result = Sem<HashTag>(p, a);
    Func<HashTag(OrgAdapter)> aux;
    result->head = strip(a.at(0).strVal(), CharSet{QChar('#')}, CharSet{});

    aux = [p, &aux](OrgAdapter a) -> HashTag {
        HashTag result{p, a};
        result.head = strip(
            a.at(0).strVal(), CharSet{QChar('#')}, CharSet{});
        if (1 < a.size()) {
            for (auto& node : a.at(slice(1, 1_B))) {
                result.subtags.push_back(aux(node));
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

    {
        __field(N::Title);
        tree->title = convertParagraph(tree.get(), one(a, N::Title));
    }

    { __field(N::Todo); }

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

    } else {
        Str protocol = normalize(one(a, N::Protocol).strVal());
        if (false) {

        } else {
            qCritical() << "Unhandled protocol kind" << protocol;
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

// clang-format off
Wrap<Word> OrgConverter::convertWord(__args) { __trace(); return SemLeaf<Word>(p, a); }
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

Wrap<Org> OrgConverter::convert(__args) {
    __trace();
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
        case org::RawLink: return convertLink(p, a);
        case org::StaticActiveTime:
        case org::StaticInactiveTime:
        case org::DynamicActiveTime:
        case org::DynamicInactiveTime: return convertTime(p, a);
        case org::SkipSpace: return convertSpace(p, a);
        case org::SkipNewline: return convertNewline(p, a);
        case org::Quote: return convertMarkQuote(p, a);
        default:
            qCritical() << "Unhandled node type";
            qCritical().noquote() << a.treeRepr();
            throw wrapError(Err::UnhandledKind(a.kind()), a);
    }
#undef CASE
}
