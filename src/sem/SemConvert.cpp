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

namespace {
bool org_streq(CR<Str> str1, CR<Str> str2) {
    return normalize(str1) == normalize(str2);
}

absl::TimeZone ConvertToTimeZone(std::string z) {
    int  hours    = 0;
    int  minutes  = 0;
    bool positive = true;

    if (z[0] == '+' || z[0] == '-') {
        positive = (z[0] == '+');
        z        = z.substr(1);
    }

    if (z.size() == 2) {
        hours = std::stoi(z);
    } else if (z.size() == 4) {
        hours   = std::stoi(z.substr(0, 2));
        minutes = std::stoi(z.substr(2, 2));
    }

    int offset = hours * 3600 + minutes * 60;
    if (!positive) { offset = -offset; }

    return absl::FixedTimeZone(offset);
}

} // namespace

Str get_text(
    OrgAdapter  a,
    int         line     = __builtin_LINE(),
    char const* function = __builtin_FUNCTION()) {
    if (a.isTerminal()) {
        return a.val().text;
    } else if (a.kind() == org::Empty) {
        return "";
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

#define __args In a

using N   = OrgSpecName;
using osk = OrgSemKind;


SemId<Table> OrgConverter::convertTable(__args) {
    __perf_trace("convert", "convertTable");
    auto __trace = trace(a);
    auto result  = Sem<Table>(a);

    if (auto args = one(a, N::Args);
        args.getKind() == org::InlineStmtList) {
        result->isBlock    = true;
        result->parameters = convertCmdArguments(args);
    }

    for (auto const& in_row : many(a, N::Rows)) {
        SemId<Row> row = Sem<Row>(in_row);
        if (auto args = one(in_row, N::Args);
            args.getKind() == org::InlineStmtList) {
            row->isBlock    = true;
            row->parameters = convertCmdArguments(args);
        }

        for (auto const& in_cell : one(in_row, N::Body)) {
            SemId<Cell> cell = Sem<Cell>(in_cell);
            if (auto args = one(in_cell, N::Args);
                args.getKind() == org::InlineStmtList) {
                cell->isBlock    = true;
                cell->parameters = convertCmdArguments(args);
            }

            for (auto const& sub : one(in_cell, N::Body)) {
                cell->push_back(convert(sub));
            }

            row->cells.push_back(cell);
        }

        result->rows.push_back(row);
    }


    return result;
};


SemId<HashTag> OrgConverter::convertHashTag(__args) {
    __perf_trace("convert", "convertHashTag");
    auto                             __trace = trace(a);
    auto                             result  = Sem<HashTag>(a);
    Func<SemId<HashTag>(OrgAdapter)> aux;
    result->head = strip(get_text(a.at(0)), CharSet{'#'}, CharSet{});


    aux = [&aux, this](OrgAdapter a) -> SemId<HashTag> {
        SemId<HashTag> result = Sem<HashTag>(a);
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

template <sem::IsOrg T>
Vec<SemId<T>> filter_subnodes(sem::OrgArg node, CR<SemSet> limiter) {
    return node->subnodes //
         | rv::take_while([&limiter](sem::OrgArg arg) {
               return !limiter.contains(arg->getKind());
           })
         | rv::remove_if(
               [](sem::OrgArg arg) { return !arg->is(T::staticKind); })
         | rv::transform([](OrgArg arg) { return arg.as<T>(); })
         | rs::to<Vec>();
}

SemId<SubtreeLog> OrgConverter::convertSubtreeLog(__args) {
    __perf_trace("convert", "convertSubtreeLog");
    auto log = Sem<SubtreeLog>(a);


    using Entry          = SubtreeLog::LogEntry;
    using Log            = SubtreeLog;
    SemId<ListItem> item = convertListItem(a);
    SemId<Org>      par0 = item->at(0);

    SemSet limit{osk::Newline};

    Vec<Str> words = //
        own_view(filter_subnodes<Word>(par0, limit))
        | rv::transform(
            [](OrgArg arg) { return normalize(arg.as<Word>()->text); })
        | rs::to<Vec>();

    if (words.empty()) {
        Vec<SemId<Org>> times =   //
            item->at(0)->subnodes //
            | rv::remove_if([](sem::OrgArg arg) {
                  return !(arg->is(osk::Time) || arg->is(osk::TimeRange));
              })
            | rs::to<Vec>();

        auto clock = Log::Clock{};
        CHECK(!times.empty())
            << a.treeRepr() << ExporterTree::treeRepr(item).toString();
        if (times.at(0)->is(osk::Time)) {
            clock.from = times.at(0).as<Time>();
        } else {
            auto range = times.at(0).as<TimeRange>();
            clock.from = range->from;
            clock.to   = range->to;
        }

        log->log = clock;
    } else {
        Vec<SemId<Time>> times = filter_subnodes<Time>(par0, limit);

        if (words.at(0) == "tag") {
            auto                tag  = Log::Tag{};
            Vec<SemId<HashTag>> tags = filter_subnodes<HashTag>(
                par0, limit);
            CHECK(!tags.empty() && !times.empty()) << a.treeRepr();
            tag.tag = tags.at(0);
            tag.on  = times.at(0);
            if (words.at(1) == "added") {
                tag.added = true;
            } else {
                tag.added = false;
            }

            log->log = tag;

        } else if (words.at(0) == "state") {
            Vec<Str> big_idents = //
                own_view(filter_subnodes<BigIdent>(par0, limit))
                | rv::transform(
                    [](SemId<BigIdent> arg) { return arg->text; })
                | rs::to<Vec>();

            auto states = Log::State{};
            CHECK(!big_idents.empty()) << a.treeRepr();
            states.from = big_idents.at(0);
            if (1 < big_idents.size()) { states.to = big_idents.at(1); }
            states.on = times.at(0);
            log->log  = states;

        } else if (words.at(0) == "refiled") {
            Vec<SemId<Time>> times  = filter_subnodes<Time>(par0, limit);
            Vec<SemId<Link>> link   = filter_subnodes<Link>(par0, limit);
            auto             refile = Log::Refile{};
            CHECK(!times.empty())
                << a.treeRepr() << ExporterTree::treeRepr(item).toString();

            refile.on = times.at(0);
            if (!link.empty()) { refile.from = link.at(0); }
            log->log = refile;

        } else if (words.at(0) == "priority") {
            Vec<SemId<Time>> times = filter_subnodes<Time>(par0, limit);
            Vec<SemId<BigIdent>> priorities = filter_subnodes<BigIdent>(
                par0, limit);
            auto priority = Log::Priority{};

            if (words.contains("added")) {
                priority.newPriority = priorities.at(0)->text;
                priority.action      = Log::Priority::Action::Added;
            } else if (words.contains("changed")) {
                priority.newPriority = priorities.at(0)->text;
                priority.oldPriority = priorities.at(0)->text;
                priority.action      = Log::Priority::Action::Changed;
            } else if (words.contains("removed")) {
                priority.oldPriority = priorities.at(0)->text;
                priority.action      = Log::Priority::Action::Removed;
            } else {
                LOG(FATAL) << fmt1(words)
                           << " Unexpected priority log message structure";
            }

            priority.on = times.at(0);
            log->log    = priority;

        } else if (words.at(0) == "note" && !times.empty()) {
            auto note = Log::Note{};
            note.on   = times.at(0);
            log->log  = note;

        } else {
            auto unknown = Log::Unknown{};
            auto stmt    = SemId<StmtList>::New();
            for (auto const& sub : item->subnodes) {
                stmt->subnodes.push_back(sub);
            }
            unknown.desc = stmt;
            log->log     = unknown;
        }
    }

    if (log->getLogKind() != Log::Kind::Unknown) {
        auto description = //
            par0->subnodes //
            | rv::drop_while([](sem::OrgArg arg) {
                  return !(
                      arg->is(osk::Punctuation)
                      && arg.as<Punctuation>()->text == "\\\\");
              })
            | rv::drop(1) //
            | rv::drop_while([](sem::OrgArg arg) {
                  return arg->is(osk::Newline) || arg->is(osk::Space);
              })
            | rs::to<Vec>();

        if (!description.empty() || 1 < item->subnodes.size()) {
            SemId<StmtList> desc = SemId<StmtList>::New();
            if (!description.empty()) {
                SemId<Paragraph> para = SemId<Paragraph>::New();
                for (auto const& it : description) { para->push_back(it); }
                desc->push_back(para);
            }

            if (1 < item->subnodes.size()) {
                for (int i = 1; i < item->subnodes.size(); ++i) {
                    desc->push_back(item->subnodes.at(i));
                }
            }

            CHECK(!desc.isNil());
            log->setDescription(desc);
        }
    }


    return log;
}

void OrgConverter::convertSubtreeDrawer(SemId<Subtree>& tree, In a) {
    __perf_trace("convert", "convertSubtreeDrawer");
    auto __trace = trace(a);
    if (a.kind() != org::Empty) {
        for (const auto& group : a) {
            switch (group.kind()) {
                case org::SubtreeDescription: {
                    tree->description = convertParagraph(group[0]);
                    break;
                }

                case org::Logbook: {
                    for (auto const& entry : group.at(0)) {
                        auto log = convertSubtreeLog(entry);
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

    std::string basename = strip(
        get_text(one(a, N::Name)), CharSet{' ', ':'}, CharSet{':'});
    std::string name = normalize(basename);

    auto __trace = trace(a, fmt("property-{}", name));

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
        tree->treeId = strip(get_text(one(a, N::Values)), {' '}, {' '});

    } else if (name == "created") {
        Property::Created created;
        auto              par  = convertParagraph(one(a, N::Values));
        auto              par0 = par->at(0);

        if (par0->is(osk::Time)) {
            created.time = par0.as<sem::Time>();
            result       = Property(created);
        } else {
            LOG(FATAL)
                << "Could not extract time from 'created' property\n"
                << a.treeRepr(true);
        }

    } else if (name == "origin") {
        Property::Origin origin;
        origin.text = convert(one(a, N::Values)).as<sem::Paragraph>();
        result      = Property(origin);

    } else if (name == "visibility") {
        if (auto visibility = parseOrgEnum<
                sem::Subtree::Property::Visibility::Level>(
                get_text(one(a, N::Values).at(0)));
            visibility) {
            Property::Visibility prop;
            prop.level = visibility.value();
            result     = Property(prop);
        } else {
            LOG(FATAL) << "Unknown visibility";
        }

    } else if (name == "effort") {
        Str const&       value    = get_text(one(a, N::Values));
        Vec<Str>         duration = value.split(":");
        Property::Effort prop;

        if (duration.size() == 1) {
            prop.minutes = duration[0].toInt();
        } else if (duration.size() == 2) {
            prop.minutes = duration[1].toInt();
            prop.hours   = duration[0].toInt();
        }

        result = Property(prop);

    } else {
        Property::Unknown prop;
        prop.name  = basename;
        prop.value = convert(one(a, N::Values));
        if (prop.value->is(osk::StmtList)
            && prop.value->subnodes.size() == 1) {
            prop.value = prop.value->at(0);
        }
        result = Property(prop);
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
    }

    if (result) { tree->properties.push_back(*result); }
}

SemId<Subtree> OrgConverter::convertSubtree(__args) {
    __perf_trace("convert", "convertSubtree");
    auto __trace = trace(a);
    auto tree    = Sem<Subtree>(a);

    tree->level = get_text(one(a, N::Prefix)).size();

    {
        auto __field = field(N::Title, a);
        tree->title  = convertParagraph(one(a, N::Title));
        auto& sn     = tree->title->subnodes;
        if (Opt<sem::SemId<sem::Org>> first = sn.get(0); first) {
            if (auto ident = first.value().asOpt<sem::BigIdent>();
                ident && ident->text == "COMMENT") {
                tree->isComment = true;
                int offset      = 1;
                while (sn.has(offset) && sn.at(offset)->is(osk::Space)) {
                    ++offset;
                }

                sn.erase(sn.begin(), sn.begin() + offset);
            }
        }
    }

    {
        auto __field = field(N::Todo, a);
        auto todo    = one(a, N::Todo);
        if (todo.getKind() != org::Empty) { tree->todo = get_text(todo); }
        if (tree->todo && tree->todo.value() == "COMMENT") {
            tree->todo.reset();
            tree->isComment = true;
        }
    }

    {
        auto __field = field(N::Tags, a);
        for (const auto& hash : one(a, N::Tags)) {
            auto tag = convertHashTag(hash);
            if (tag->head == "ARCHIVE") {
                tree->isArchived = true;
            } else {
                tree->tags.push_back(tag);
            }
        }
    }

    {
        auto __field = field(N::Times, a);
        for (auto const& it : one(a, N::Times)) {
            auto kind = convertWord(it.at(0));
            auto time = convertTime(it.at(1));
            if (org_streq(kind->text, "closed")) {
                tree->closed = time;
            } else if (org_streq(kind->text, "deadline")) {
                tree->deadline = time;
            } else if (org_streq(kind->text, "scheduled")) {
                tree->deadline = time;
            }
        }
    }

    {
        auto __field = field(N::Drawer, a);
        convertSubtreeDrawer(tree, one(a, N::Drawer));
    }

    {
        auto __field = field(N::Body, a);
        for (auto const& it :
             flatConvertAttachedSubnodes(one(a, N::Body))) {
            tree->push_back(it);
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

    auto time      = Sem<Time>(a);
    time->isActive = (a.kind() == org::DynamicActiveTime)
                  || (a.kind() == org::StaticActiveTime);

    if (a.kind() == org::DynamicInactiveTime
        || a.kind() == org::DynamicActiveTime) {
        time->time = Time::Dynamic{.expr = get_text(a)};
    } else if (
        a.kind() == org::StaticActiveTime
        || a.kind() == org::StaticInactiveTime) {

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
            Spec{
                .pattern = "%Y-%m-%d %H:%M",
                .align   = UserTime::Alignment::Minute,
            },
            Spec{.pattern = "%Y-%m-%d", .align = UserTime::Alignment::Day},
            // Add other formats as needed
        };


        Opt<absl::TimeZone> zone;

        if (auto z = one(a, N::Zone); z.kind() != org::Empty) {
            zone = ConvertToTimeZone(get_text(z));
        }

        absl::Time parsedDateTime;
        bool       foundTime = false;
        Spec       matching;
        for (const auto& format : formats) {
            std::string error;
            if (absl::ParseTime(
                    format.pattern,
                    datetime,
                    zone ? zone.value() : absl::TimeZone(),
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
                .time  = parsedDateTime,
                .align = matching.align,
                .zone  = zone,
            }};
    }

    print_json(time);
    return time;
}

SemId<TimeRange> OrgConverter::convertTimeRange(__args) {
    __perf_trace("convert", "convertTimeRange");
    auto __trace = trace(a);
    auto range   = Sem<TimeRange>(a);
    {
        auto __field = field(N::From, a);
        range->from  = convertTime(one(a, N::From));
    }
    {
        auto __field = field(N::To, a);
        range->to    = convertTime(one(a, N::To));
    }
    return range;
}

SemId<Macro> OrgConverter::convertMacro(__args) {
    __perf_trace("convert", "convertMacro");
    auto __trace = trace(a);
    auto macro   = Sem<Macro>(a);
    macro->name  = get_text(one(a, N::Name));

    return macro;
}

SemId<Symbol> OrgConverter::convertSymbol(__args) {
    __perf_trace("convert", "convertSymbol");
    auto __trace = trace(a);
    auto sym     = Sem<Symbol>(a);

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
        sym->positional.push_back(convert(sub));
    }

    return sym;
}

SemId<Paragraph> OrgConverter::convertParagraph(__args) {
    // TODO detect admonition paragraphs during conversion and store
    // information about this -- right now `NOTE:` is represented using
    // first two starting elements for paragraph subnodes.

    __perf_trace("convert", "convertParagraph");
    auto __trace = trace(a);
    auto par     = Sem<Paragraph>(a);
    for (const auto& item : a) { par->push_back(convert(item)); }

    while (!par->subnodes.empty()
           && SemSet{osk::Newline, osk::Space}.contains(
               par->subnodes.back()->getKind())) {
        par->subnodes.pop_back();
    }

    return par;
}

namespace {
OrgSet AnnotatedParagraphStarts{
    org::BigIdent,
    org::Footnote,
    org::StaticActiveTime,
    org::StaticInactiveTime};
}

SemId<AnnotatedParagraph> OrgConverter::convertAnnotatedParagraph(__args) {
    auto __trace = trace(a);
    auto par     = Sem<AnnotatedParagraph>(a);
    auto it      = a.begin();
    switch ((*it).getKind()) {
        case org::Footnote: {
            auto footnote = convertFootnote(*it);
            ++it;
            par->data = AnnotatedParagraph::Footnote{
                .name = footnote->tag};
            break;
        }

        case org::BigIdent: {
            auto ident = convertBigIdent(*it);
            ++it;
            if ((*it).getKind() == org::Colon) { ++it; }
            par->data = AnnotatedParagraph::Admonition{.name = ident};
            break;
        }

        case org::StaticActiveTime:
        case org::StaticInactiveTime: {
            auto time = convertTime(*it);
            ++it;
            par->data = AnnotatedParagraph::Timestamp{.time = time};
            break;
        }

        default: {
            LOG(FATAL) << fmt1(a.at(0).getKind());
        }
    }


    auto end = a.end();

    while (it != end && (*it).getKind() == org::Space) { ++it; }

    while (it != end) {
        par->push_back(convert(*it));
        ++it;
    }

    while (!par->subnodes.empty()
           && SemSet{osk::Newline, osk::Space}.contains(
               par->subnodes.back()->getKind())) {
        par->subnodes.pop_back();
    }

    return par;
}

SemId<StmtList> OrgConverter::convertStmtList(__args) {
    __perf_trace("convert", "convertStmtList");
    auto __trace   = trace(a);
    auto stmt      = Sem<StmtList>(a);
    stmt->subnodes = flatConvertAttachedSubnodes(a);
    return stmt;
}


SemId<Footnote> OrgConverter::convertFootnote(__args) {
    __perf_trace("convert", "convertFootnote");
    auto __trace = trace(a);
    if (a.kind() == org::InlineFootnote) {
        auto note        = Sem<Footnote>(a);
        note->definition = convert(one(a, N::Definition));
        return note;
    } else {
        auto link = Sem<Footnote>(a);
        link->tag = get_text(one(a, N::Definition));
        return link;
    }
}

SemId<Link> OrgConverter::convertLink(__args) {
    __perf_trace("convert", "convertLink");
    auto __trace   = trace(a);
    auto link      = Sem<Link>(a);
    auto getTarget = [&]() {
        return lstrip(get_text(one(a, N::Link)), CharSet{':'});
    };
    if (a.kind() == org::RawLink) {
        link->data = Link::Raw{.text = get_text(a)};

    } else if (a.kind() == org::Footnote) {
        link->data = Link::Footnote{
            .target = get_text(one(a, N::Definition))};

    } else if (one(a, N::Protocol).kind() == org::Empty) {
        Str target = getTarget();
        if (target.starts_with(".") || target.starts_with("/")) {
            link->data = Link::File{.file = target};
        } else {
            link->data = Link::Internal{.target = target};
        }

    } else {
        Str protocol = normalize(get_text(one(a, N::Protocol)));
        if (protocol == "http" || protocol == "https") {
            link->data = Link::Raw{
                .text = protocol + ":"_ss + getTarget()};
        } else if (protocol == "id") {
            link->data = Link::Id{
                .text = strip(getTarget(), {' '}, {' '})};

        } else if (protocol == "person") {
            link->data = Link::Person{};
            for (auto const& it : one(a, N::Link)) {
                link->getPerson().name += get_text(it);
            }

        } else if (protocol == "file") {
            link->data = Link::File{.file = getTarget()};

        } else if (protocol == "attachment") {
            link->data = Link::Attachment{.file = getTarget()};

        } else {
            link->data = Link::UserProtocol{.protocol = protocol};
        }
    }

    if (a.kind() == org::Link) {
        if (one(a, N::Desc).kind() == org::Paragraph) {
            link->description = convertParagraph(one(a, N::Desc));
        }
    }

    return link;
}

SemId<List> OrgConverter::convertList(__args) {
    __perf_trace("convert", "convertList");
    auto __trace = trace(a);
    auto list    = Sem<List>(a);
    for (const auto& it : a) { list->push_back(convert(it)); }

    return list;
}

SemId<ListItem> OrgConverter::convertListItem(__args) {
    __perf_trace("convert", "convertListItem");
    auto __trace = trace(a);
    auto item    = Sem<ListItem>(a);
    if (one(a, N::Header).kind() != org::Empty) {
        item->header = convertParagraph(one(a, N::Header));
    }

    if (auto bullet = one(a, N::Bullet); bullet.kind() != org::Empty) {
        item->bullet = strip(get_text(bullet), CharSet{' '}, CharSet{' '});
    }

    if (one(a, N::Checkbox).kind() != org::Empty) {
        Str text = strip(
            get_text(one(a, N::Checkbox)),
            CharSet{'[', ' '},
            CharSet{' ', ']'});

        print(fmt("Normalized checkbox: {}", escape_literal(text)));

        if (text == "x" || text == "X") {
            item->checkbox = ListItem::Checkbox::Done;
        } else if (text == "") {
            item->checkbox = ListItem::Checkbox::Empty;
        } else if (text == "-") {
            item->checkbox = ListItem::Checkbox::Partial;
        } else {
            LOG(FATAL) << text;
        }
    }

    {
        for (const auto& sub : one(a, N::Body)) {
            item->push_back(convert(sub));
        }
    }

    return item;
}

SemId<Caption> OrgConverter::convertCaption(__args) {
    __perf_trace("convert", "convertCaption");
    auto __trace  = trace(a);
    auto caption  = Sem<Caption>(a);
    caption->text = convertParagraph(one(a, N::Args)[0]);

    return caption;
}


SemId<Tblfm> OrgConverter::convertTblfm(__args) {
    __perf_trace("convert", "convertTblfm");
    auto __trace = trace(a);
    auto tblfm   = Sem<Tblfm>(a);

    return tblfm;
}


SemId<Word> OrgConverter::convertWord(__args) {
    auto __trace = trace(a);
    return SemLeaf<Word>(a);
}

SemId<Placeholder> OrgConverter::convertPlaceholder(__args) {
    __perf_trace("convert", "convertPlaceholder");
    auto __trace = trace(a);
    return SemLeaf<Placeholder>(a);
}

SemId<Newline> OrgConverter::convertNewline(__args) {
    auto __trace = trace(a);
    return SemLeaf<Newline>(a);
}

SemId<Space> OrgConverter::convertSpace(__args) {
    return SemLeaf<Space>(a);
}

SemId<Escaped> OrgConverter::convertEscaped(__args) {
    return SemLeaf<Escaped>(a);
}

SemId<RawText> OrgConverter::convertRawText(__args) {
    return SemLeaf<RawText>(a);
}

SemId<RadioTarget> OrgConverter::convertRadioTarget(__args) {
    auto result = Sem<RadioTarget>(a);
    for (auto const& sub : a) { result->text += get_text(sub); }
    return result;
}

SemId<TextTarget> OrgConverter::convertTextTarget(__args) {
    auto result = Sem<TextTarget>(a);
    for (auto const& sub : a) { result->text += get_text(sub); }
    return result;
}


SemId<Punctuation> OrgConverter::convertPunctuation(__args) {
    auto __trace = trace(a);
    return SemLeaf<Punctuation>(a);
}

SemId<BigIdent> OrgConverter::convertBigIdent(__args) {
    __perf_trace("convert", "convertBigIdent");
    auto __trace = trace(a);
    return SemLeaf<BigIdent>(a);
}

SemId<sem::ParseError> OrgConverter::convertParseError(__args) {
    return Sem<sem::ParseError>(a);
}


SemId<MarkQuote> OrgConverter::convertMarkQuote(__args) {
    __perf_trace("convert", "convertMarkQuote");
    auto __trace = trace(a);
    return convertAllSubnodes<MarkQuote>(a);
}

SemId<Verbatim> OrgConverter::convertVerbatim(__args) {
    __perf_trace("convert", "convertVerbatim");
    auto __trace = trace(a);
    return convertAllSubnodes<Verbatim>(a);
}

SemId<Bold> OrgConverter::convertBold(__args) {
    __perf_trace("convert", "convertBold");
    auto __trace = trace(a);
    return convertAllSubnodes<Bold>(a);
}

SemId<Monospace> OrgConverter::convertMonospace(__args) {
    __perf_trace("convert", "convertMonospace");
    auto __trace = trace(a);
    return convertAllSubnodes<Monospace>(a);
}

SemId<Strike> OrgConverter::convertStrike(__args) {
    __perf_trace("convert", "convertStrike");
    auto __trace = trace(a);
    return convertAllSubnodes<Strike>(a);
}

SemId<Par> OrgConverter::convertPar(__args) {
    __perf_trace("convert", "convertPar");
    auto __trace = trace(a);
    return convertAllSubnodes<Par>(a);
}

SemId<Italic> OrgConverter::convertItalic(__args) {
    __perf_trace("convert", "convertItalic");
    auto __trace = trace(a);
    return convertAllSubnodes<Italic>(a);
}

SemId<Underline> OrgConverter::convertUnderline(__args) {
    __perf_trace("convert", "convertUnderline");
    auto __trace = trace(a);
    return convertAllSubnodes<Underline>(a);
}

SemId<Example> OrgConverter::convertExample(__args) {
    SemId<Example> result = Sem<Example>(a);
    for (auto const& it : many(a, N::Body)) {
        result->subnodes.push_back(convert(it));
    }

    return result;
}

SemId<ColonExample> OrgConverter::convertColonExample(__args) {
    SemId<ColonExample> result = Sem<ColonExample>(a);
    for (auto const& it : many(a, N::Body)) {
        if (it.isMono()) {
            result->subnodes.push_back(Sem<RawText>(it));
        } else {
            result->subnodes.push_back(SemLeaf<RawText>(it));
        }
    }
    return result;
}

SemId<Export> OrgConverter::convertExport(__args) {
    auto eexport = Sem<Export>(a);
    switch (a.kind()) {
        case org::BlockExport:
            eexport->format = Export::Format::Block;
            break;
        default: {
        }
    }

    auto values = convertCmdArguments(one(a, N::Args));
    if (auto place = values->getArguments("placement"); place) {
        eexport->placement = place->value->args.at(0)->getString();
        values->named.erase("placement");
    }


    eexport->exporter   = get_text(one(a, N::Name));
    eexport->parameters = values;
    {
        auto lines = one(a, N::Body);
        int  idx   = 0;
        int  size  = lines.size();
        for (auto const& item : lines) {
            ++idx;
            if (idx < size) { eexport->content += get_text(item); }
        }
    }

    return eexport;
}

SemId<Center> OrgConverter::convertCenter(__args) {
    SemId<Center> res = Sem<Center>(a);
    for (const auto& sub : many(a, N::Body)) {
        auto aux = convert(sub);
        res->push_back(aux);
    }
    return res;
}

SemId<AdmonitionBlock> OrgConverter::convertAdmonitionBlock(__args) {
    return convertAllSubnodes<AdmonitionBlock>(a);
}

SemId<Quote> OrgConverter::convertQuote(__args) {
    SemId<Quote> quote = Sem<Quote>(a);

    if (auto args = one(a, N::Args); args.kind() != org::Empty) {
        quote->parameters = convertCmdArguments(args);
    }

    for (const auto& sub : flatConvertAttached(many(a, N::Body))) {
        quote->push_back(sub);
    }
    return quote;
}

SemId<CommentBlock> OrgConverter::convertCommentBlock(__args) {
    SemId<CommentBlock> result = Sem<CommentBlock>(a);
    for (const auto& sub : flatConvertAttached(many(a, N::Body))) {
        result->push_back(sub);
    }
    return result;
}

SemId<LatexBody> OrgConverter::convertMath(__args) {
    if (a.kind() == org::InlineMath) {
        return Sem<InlineMath>(a).as<LatexBody>();
    } else {
        LOG(FATAL) << "Unhanled kind for inline math TODO";
    }
}

SemId<Include> OrgConverter::convertInclude(__args) {
    SemId<Include> include = Sem<Include>(a);
    auto           args    = convertCmdArguments(one(a, N::Args));
    include->path          = args->positional->args.at(0)->getString();

    if (auto kind = args->positional->args.get(1)) {
        Str ks = kind.value().get()->value;
        if (ks == "src"_ss) {
            auto src      = sem::Include::Src{};
            include->data = src;

        } else {
            LOG(FATAL) << fmt("Unhandled org include kind {}", ks);
        }

    } else {
        include->data = sem::Include::OrgDocument{};
    }

    if (args->named.contains("minlevel")) {
        include->getOrgDocument().minLevel = args->named.at("minlevel")
                                                 ->args.at(0)
                                                 ->getInt();
    }

    if (args->named.contains("lines")) {
        Str lines = strip(
            (**args->getArguments("lines")).args.at(0)->getString(),
            CharSet{'"'},
            CharSet{'"'});
        Vec<Str> split = lines.split("-");
        if (lines.starts_with("-")) {
            include->lastLine = split.at(1).toInt() - 1;
        } else if (lines.ends_with("-")) {
            include->firstLine = split.at(0).toInt() - 1;
        } else {
            include->firstLine = split.at(0).toInt() - 1;
            include->lastLine  = split.at(1).toInt() - 1;
        }
    }


    return include;
}

SemId<TextSeparator> OrgConverter::convertTextSeparator(__args) {
    return Sem<TextSeparator>(a);
}

SemId<AtMention> OrgConverter::convertAtMention(__args) {
    return SemLeaf<AtMention>(a);
}

SemId<CmdArgument> OrgConverter::convertCmdArgument(__args) {
    auto               __trace = trace(a);
    SemId<CmdArgument> result  = Sem<CmdArgument>(a);
    Str                key     = get_text(one(a, N::Name));
    result->value              = get_text(one(a, N::Value));

    if (!key.empty()) { result->key = key.substr(1); }

    if (TraceState) {
        print(fmt("key:{} value:{}", result->key, result->value));
    }

    return result;
}

SemId<CmdArguments> OrgConverter::convertCmdArguments(__args) {
    auto                __trace = trace(a);
    SemId<CmdArguments> result  = Sem<CmdArguments>(a);

    auto add_arg = [&](SemId<CmdArgument> arg) {
        if (arg->key) {
            auto key = normalize(*arg->key);
            if (result->named.contains(key)) {
                result->named[key]->args.push_back(arg);
            } else {
                auto args = SemId<CmdArgumentList>::New();
                args->args.push_back(arg);
                result->named.insert({key, args});
            }
        } else {
            if (result->positional.isNil()) {
                result->positional = SemId<CmdArgumentList>::New();
            }
            result->positional->args.push_back(arg);
        }
    };

    if (a.getKind() == org::CmdArguments) {
        for (auto const& item : one(a, N::Values)) {
            add_arg(convertCmdArgument(item));
        }
    } else if (a.getKind() == org::InlineStmtList) {
        for (auto const& it : a) { add_arg(convertCmdArgument(it)); }
    } else {
        CHECK(a.getKind() == org::Empty) << a.treeRepr();
    }

    return result;
}

SemId<CmdAttr> OrgConverter::convertCmdAttr(__args) {
    auto           __trace = trace(a);
    SemId<CmdAttr> result  = Sem<CmdAttr>(a);
    result->target         = normalize(get_text(one(a, N::Name)));
    result->parameters     = convertCmdArguments(one(a, N::Args));

    return result;
}

SemId<Code> OrgConverter::convertCode(__args) {
    SemId<Code> result = Sem<Code>(a);

    if (one(a, N::Lang).getKind() != org::Empty) {
        result->lang = get_text(one(a, N::Lang));
    }

    if (one(a, N::HeaderArgs).kind() != org::Empty) {
        result->parameters = convertCmdArguments(one(a, N::HeaderArgs));
    }

    if (a.kind() == org::SrcInlineCode) {
        Code::Line& line = result->lines.emplace_back();
        for (auto const& it : one(a, N::Body)) {
            line.parts.push_back(Code::Line::Part(Code::Line::Part::Raw{
                .code = get_text(it),
            }));
        }
    } else {
        for (auto const& it : one(a, N::Body)) {
            Code::Line& line = result->lines.emplace_back();
            for (auto const& part : it) {
                switch (part.kind()) {
                    case org::CodeText: {
                        line.parts.push_back(
                            Code::Line::Part(Code::Line::Part::Raw{
                                .code = get_text(part),
                            }));
                        break;
                    }
                    default: {
                        LOG(FATAL) << fmt1(part.kind());
                    }
                }
            }
        }
    }

    return result;
}


Vec<SemId<Org>> OrgConverter::flatConvertAttached(Vec<OrgAdapter> items) {
    auto            __trace = trace(std::nullopt);
    Vec<SemId<Org>> result;

    Vec<sem::SemId<sem::Org>> buffer;
    for (int i = 0; i < items.size(); ++i) {
        auto it  = items.at(i);
        auto res = convert(it);
        if (res->dyn_cast<sem::Attached>()) {
            print(fmt("{} is attached", res->getKind()));
            buffer.push_back(res);
        } else {
            if (auto res_stmt = res.asOpt<sem::Stmt>()) {
                print(fmt(
                    "{} is a statement, adding attached", res->getKind()));
                if (auto par = res_stmt.asOpt<sem::Paragraph>();
                    par && par->subnodes.size() == 1) {
                    if (auto link = par->subnodes.at(0)
                                        .asOpt<sem::Link>()) {
                        link->attached = buffer;
                    } else {
                        res_stmt->attached = buffer;
                    }
                } else {
                    res_stmt->attached = buffer;
                }
            } else {
                print(
                    fmt("{} is not a statement, releasing attached",
                        res->getKind()));
                for (auto const& buf : buffer) { result.push_back(buf); }
            }
            buffer.clear();
            result.push_back(res);
        }

        int offset = 0;
        for (auto next_opt = items.get(i + offset + 1);
             next_opt && next_opt->get().getKind() == org::CommandTblfm;
             ++offset) {

            auto tblfm = convertTblfm(next_opt->get());
            LOG(FATAL) << "TODO";
        }

        i += offset;
    }

    for (auto const& buf : buffer) { result.push_back(buf); }

    return result;
}

Vec<SemId<Org>> OrgConverter::flatConvertAttachedSubnodes(In item) {
    Vec<OrgAdapter> items;
    for (auto const& sub : item) { items.push_back(sub); }
    return flatConvertAttached(items);
}


SemId<Org> OrgConverter::convert(__args) {
    auto __trace = trace(a);
    if (!a.isValid()) {
        LOG(WARNING) << "Invalid node encountered during conversion"
                     << fmt1(a.id);
        return Sem<Space>(a);
    }

#define CASE(Kind)                                                        \
    case org::Kind: return convert##Kind(a);
    switch (a.kind()) {
        CASE(Newline);
        CASE(StmtList);
        CASE(Subtree);
        CASE(TimeRange);
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
        case org::Target: return convertTextTarget(a);
        case org::RadioTarget: return convertRadioTarget(a);
        case org::InlineStmtList: return convertStmtList(a);
        case org::SrcInlineCode:
        case org::SrcCode: return convertCode(a);
        case org::InlineFootnote: return convertFootnote(a);
        case org::BlockExport: return convertExport(a);
        case org::Macro: return convertMacro(a);
        case org::Monospace: return convertMonospace(a);
        case org::CenterBlock: return convertCenter(a);
        case org::Example: return convertExample(a);
        case org::AdmonitionBlock: return convertAdmonitionBlock(a);
        case org::HashTag: return convertHashTag(a);
        case org::Error: return convertParseError(a);
        case org::ListTag: return convert(a[0]);
        case org::InlineMath: return convertMath(a);
        case org::RawLink: return convertLink(a);
        case org::StaticActiveTime:
        case org::StaticInactiveTime:
        case org::DynamicActiveTime:
        case org::DynamicInactiveTime: return convertTime(a);
        case org::Quote: return convertMarkQuote(a);
        case org::CommentBlock: return convertCommentBlock(a);
        case org::QuoteBlock: return convertQuote(a);
        case org::Colon: return convertPunctuation(a);
        case org::CommandInclude: return convertInclude(a);
        case org::Symbol: return convertSymbol(a);
        case org::Angle: return convertPlaceholder(a);
        case org::Empty: return Sem<Empty>(a);
        case org::Table: return convertTable(a);
        case org::Footnote: return convertLink(a);
        case org::CommandTblfm: return convertTblfm(a);
        case org::CommandAttr: return convertCmdAttr(a);
        case org::ColonExample: return convertColonExample(a);
        case org::CommandCaption: return convertCaption(a); break;
        case org::Paragraph: {
            if (2 < a.size()
                && AnnotatedParagraphStarts.contains(a.at(0).kind())) {
                if (a.at(0).kind() == org::BigIdent) {
                    // NOTE: ....
                    if (2 < a.size() && a.at(1).kind() == org::Colon) {
                        return convertAnnotatedParagraph(a);
                    } else {
                        return convertParagraph(a);
                    }
                } else {
                    return convertAnnotatedParagraph(a);
                }
            } else {
                return convertParagraph(a);
            }
        }

        default: {
            print(fmt("ERR Unknown content {}", a.getKind()));
            return Sem<Empty>(a);
        }
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
            if (org_streq(head, "broken-links")) {
                if (org_streq(tail, "mark")) {
                    opts->brokenLinks = DocumentOptions::BrokenLinks::Mark;
                } else if (org_streq(tail, "t")) {
                    opts->brokenLinks = DocumentOptions::BrokenLinks::
                        Ignore;
                }
            } else if (org_streq(head, "toc")) {
                if (org_streq(tail, "t")) {
                    opts->tocExport = DocumentOptions::DoExport{true};
                } else if (org_streq(tail, "nil")) {
                    opts->tocExport = DocumentOptions::DoExport{false};
                } else if ('0' <= tail[0] && tail[0] <= '9') {
                    opts->tocExport = DocumentOptions::ExportFixed{
                        tail.toInt()};
                }
            }

        } else if (org_streq(value, ":")) {
            opts->fixedWidthSections = true;
        } else if (org_streq(value, "<")) {
            opts->includeTimestamps = true;
        } else if (org_streq(value, "^")) {
            opts->plaintextSubscripts = true;
        } else {
            LOG(ERROR) << "Unexpected document option value" << value;
        }
    }
}

SemId<Document> OrgConverter::toDocument(OrgAdapter adapter) {
    auto __trace = trace(adapter);

    SemId<Document> doc = Sem<Document>(adapter);
    doc->options        = Sem<DocumentOptions>(adapter);
    using Prop          = Subtree::Property;
    Vec<OrgAdapter> buffer;

    if (adapter.kind() == org::StmtList) {
        for (const auto& sub : adapter) {
            auto __trace = trace(adapter, fmt1(sub.getKind()));
            switch (sub.kind()) {
                case org::Columns: {
                    break;
                }
                case org::CommandTitle: {
                    doc->title = convertParagraph(sub[0]);
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

                case org::CommandStartup: {
                    Str text = normalize(get_text(sub.at(0)));
                    using K  = DocumentOptions::Visibility;
                    if (text == "content") {
                        doc->options->initialVisibility = K::Content;
                    } else if (text == "overview") {
                        doc->options->initialVisibility = K::Overview;
                    } else if (text == "showall") {
                        doc->options->initialVisibility = K::ShowAll;
                    } else if (text == "show2levels") {
                        doc->options->initialVisibility = K::Show2Levels;
                    } else if (text == "show3levels") {
                        doc->options->initialVisibility = K::Show3Levels;
                    } else if (text == "show4levels") {
                        doc->options->initialVisibility = K::Show4Levels;
                    } else if (text == "show4levels") {
                        doc->options->initialVisibility = K::Show4Levels;
                    } else if (text == "showeverything") {
                        doc->options->initialVisibility = K::
                            ShowEverything;
                    } else {
                        LOG(FATAL) << text;
                    }
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
                case org::Filetags: {

                    for (auto const& hash : many(sub, N::Tags)) {
                        doc->filetags.push_back(convertHashTag(hash));
                    }
                    break;
                }

                default: {
                    buffer.push_back(sub);
                    break;
                }
            }
        }
    } else {
        buffer.push_back(adapter);
    }

    for (auto const& it : flatConvertAttached(buffer)) {
        doc->subnodes.push_back(it);
    }

    return doc;
}
