#include <haxorg/sem/SemConvert.hpp>
#include <hstd/stdlib/Func.hpp>
#include <haxorg/parse/OrgSpec.hpp>

#include <hstd/stdlib/Debug.hpp>

#include <boost/preprocessor/facilities/overload.hpp>
#include <boost/preprocessor/facilities/empty.hpp>
#include <haxorg/sem/perfetto_org.hpp>
#include <haxorg/exporters/exportertree.hpp>
#include <boost/algorithm/string/replace.hpp>
#include <absl/log/log.h>
#include <haxorg/sem/SemOrgFormat.hpp>


struct convert_logic_error : CRTP_hexception<convert_logic_error> {};

using namespace sem;

using onk      = OrgNodeKind;
using otk      = OrgTokenKind;
using Err      = OrgConverter::Errors;
using Property = sem::NamedProperty;

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
    } else if (a.kind() == onk::Empty) {
        return "";
    } else {
        throw convert_logic_error::init(
            fmt("{} {} {}", function, line, a.treeRepr(false)));
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

OrgConverter::ConvResult<Table> OrgConverter::convertTable(__args) {
    __perf_trace("convert", "convertTable");
    auto __trace = trace(a);
    auto result  = Sem<Table>(a);

    if (auto args = one(a, N::Args);
        args.getKind() == onk::InlineStmtList) {
        result->isBlock = true;
        result->attrs   = convertAttrs(args).value();
    }

    for (auto const& in_row : many(a, N::Rows)) {
        SemId<Row> row = Sem<Row>(in_row);
        if (auto args = one(in_row, N::Args);
            args.getKind() == onk::InlineStmtList) {
            row->isBlock = true;
            row->attrs   = convertAttrs(args).value();
        }

        for (auto const& in_cell : one(in_row, N::Body)) {
            SemId<Cell> cell = Sem<Cell>(in_cell);
            if (auto args = one(in_cell, N::Args);
                args.getKind() == onk::InlineStmtList) {
                cell->isBlock = true;
                cell->attrs   = convertAttrs(args).value();
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


OrgConverter::ConvResult<HashTag> OrgConverter::convertHashTag(__args) {
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

OrgConverter::ConvResult<SubtreeLog> OrgConverter::convertSubtreeLog(
    __args) {
    __perf_trace("convert", "convertSubtreeLog");
    auto log = Sem<SubtreeLog>(a);


    using Entry          = SubtreeLog::LogEntry;
    using Log            = SubtreeLog;
    SemId<ListItem> item = convertListItem(a).value();
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
                throw convert_logic_error::init(
                    fmt("{} Unexpected priority log message structure",
                        words));
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

Opt<SemId<ErrorGroup>> OrgConverter::convertSubtreeDrawer(
    SemId<Subtree>& tree,
    In              a) {
    __perf_trace("convert", "convertSubtreeDrawer");
    auto __trace = trace(a);
    if (a.kind() != onk::Empty) {
        for (const auto& group : a) {
            switch (group.kind()) {
                case onk::SubtreeDescription: {
                    tree->description = convertParagraph(group[0]).value();
                    break;
                }

                case onk::DrawerLogbook: {
                    for (auto const& entry : group.at(0)) {
                        auto log = convertSubtreeLog(entry).value();
                        tree->logbook.push_back(log);
                    }
                    break;
                }

                case onk::DrawerPropertyList: {
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

    return std::nullopt;
}

Opt<SemId<ErrorGroup>> OrgConverter::convertPropertyList(
    SemId<Subtree>& tree,
    In              a) {
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
        auto par  = convertParagraph(one(a, N::Values)).value();
        auto par0 = par->at(0);

        if (par0->is(osk::Time)) {
            created.time = par0.as<sem::Time>()->getStatic().time;
            result       = Property(created);
        } else {
            return SemError(
                a,
                fmt("Could not parse property 'created' of the subtree -- "
                    "expected time node, but found {} at {}",
                    par0->getKind(),
                    getLocMsg(a)));
        }

    } else if (name == "visibility") {
        if (auto visibility = parseOrgEnum<
                sem::NamedProperty::Visibility::Level>(
                get_text(one(a, N::Values).at(0)));
            visibility) {
            Property::Visibility prop;
            prop.level = visibility.value();
            result     = Property(prop);
        } else {
            throw convert_logic_error::init("Unknown visibility");
        }

    } else if (name == "effort") {
        Str const&            value    = get_text(one(a, N::Values));
        Vec<Str>              duration = value.split(":");
        NamedProperty::Effort prop;

        if (duration.size() == 1) {
            prop.minutes = duration[0].toInt();
        } else if (duration.size() == 2) {
            prop.minutes = duration[1].toInt();
            prop.hours   = duration[0].toInt();
        }

        result = NamedProperty(prop);

    } else {
        NamedProperty::CustomRaw prop;
        prop.name = basename;
        if (one(a, N::Values).kind() == onk::RawText) {
            prop.value = get_text(one(a, N::Values));
        } else {
            for (auto const& arg : one(a, N::Values)) {
                prop.value += get_text(arg);
            }
        }
        result = NamedProperty(prop);
    }

    if (false && result) {
        const auto inh = get_text(one(a, N::InheritanceMode));
        if (inh == "!!") {
            result->inheritanceMode = NamedProperty::InheritanceMode::
                OnlyThis;
        } else if (inh == "!") {
            result->inheritanceMode = NamedProperty::InheritanceMode::
                OnlySub;
        }

        const auto sub = get_text(one(a, N::SubSetRule));
        if (sub == "+") {
            result->subSetRule = NamedProperty::SetMode::Add;
        } else if (sub == "-") {
            result->subSetRule = NamedProperty::SetMode::Subtract;
        }

        const auto main = get_text(one(a, N::MainSetRule));
        if (main == "+") {
            result->subSetRule = NamedProperty::SetMode::Add;
        } else if (main == "-") {
            result->subSetRule = NamedProperty::SetMode::Subtract;
        }
    }

    if (result) { tree->properties.push_back(*result); }

    return std::nullopt;
}

OrgConverter::ConvResult<Subtree> OrgConverter::convertSubtree(__args) {
    __perf_trace("convert", "convertSubtree");
    auto __trace = trace(a);
    auto tree    = Sem<Subtree>(a);

    tree->level = get_text(one(a, N::Prefix)).size();

    {
        auto __field = field(N::Title, a);
        tree->title  = convertParagraph(one(a, N::Title)).value();
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
        auto __field = field(N::Importance, a);
        auto urgency = one(a, N::Importance);
        if (urgency.kind() != onk::Empty) {
            tree->priority = strip(
                get_text(urgency), CharSet{'[', '#'}, CharSet{']'});
        }
    }

    {
        auto __field = field(N::Todo, a);
        auto todo    = one(a, N::Todo);
        if (todo.getKind() != onk::Empty) { tree->todo = get_text(todo); }
        if (tree->todo && tree->todo.value() == "COMMENT") {
            tree->todo.reset();
            tree->isComment = true;
        }
    }

    {
        auto __field = field(N::Tags, a);
        for (const auto& hash : one(a, N::Tags)) {
            auto tag = convertHashTag(hash).value();
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
            auto kind = convertWord(it.at(0)).value();
            auto time = convertTime(it.at(1)).value();
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
            tree->push_back(it.unwrap());
        }
    }

    return tree;
}

OrgConverter::ConvResult<Time> OrgConverter::convertTime(__args) {
    __perf_trace("convert", "convertTime");
    auto __trace = trace(a);

    bool cond = OrgSet{
                      onk::DynamicActiveTime,
                      onk::DynamicInactiveTime,
                      onk::StaticActiveTime,
                      onk::StaticInactiveTime,
                  }
                     .contains(a.kind());

    CHECK(cond) << "convert subtree" << fmt1(a.kind());

    auto time      = Sem<Time>(a);
    time->isActive = (a.kind() == onk::DynamicActiveTime)
                  || (a.kind() == onk::StaticActiveTime);

    if (a.kind() == onk::DynamicInactiveTime
        || a.kind() == onk::DynamicActiveTime) {
        time->time = Time::Dynamic{.expr = get_text(a)};
    } else if (
        a.kind() == onk::StaticActiveTime
        || a.kind() == onk::StaticInactiveTime) {

        std::string datetime;
        if (one(a, N::Year).kind() != onk::Empty) {
            datetime += get_text(one(a, N::Year));
        }

        if (one(a, N::Clock).kind() != onk::Empty) {
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

        if (auto z = one(a, N::Zone); z.kind() != onk::Empty) {
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
            return SemError(
                a,
                fmt("Could not parse date time entry in format: '{}' at "
                    "'{}'",
                    datetime,
                    getLocMsg(a)));
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

OrgConverter::ConvResult<TimeRange> OrgConverter::convertTimeRange(
    __args) {
    __perf_trace("convert", "convertTimeRange");
    auto __trace = trace(a);
    auto range   = Sem<TimeRange>(a);
    {
        auto __field = field(N::From, a);
        range->from  = convertTime(one(a, N::From)).value();
    }
    {
        auto __field = field(N::To, a);
        range->to    = convertTime(one(a, N::To)).value();
    }
    return range;
}

void addArgument(SemId<Attrs>& result, SemId<Attr> arg) {
    if (arg->arg.name) {
        auto key = normalize(arg->getName());
        if (result->named.contains(key)) {
            result->named[key]->args.push_back(arg);
        } else {
            auto args = SemId<AttrList>::New();
            args->args.push_back(arg);
            result->named.insert({key, args});
        }
    } else {
        result->positional->args.push_back(arg);
    }
}

OrgConverter::ConvResult<Macro> OrgConverter::convertMacro(__args) {
    __perf_trace("convert", "convertMacro");
    auto __trace = trace(a);
    auto macro   = Sem<Macro>(a);
    macro->name  = get_text(one(a, N::Name));
    macro->attrs = convertCallArguments(many(a, N::Args), a).value();
    return macro;
}

OrgConverter::ConvResult<Symbol> OrgConverter::convertSymbol(__args) {
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

OrgConverter::ConvResult<Paragraph> OrgConverter::convertParagraph(
    __args) {
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

OrgConverter::ConvResult<StmtList> OrgConverter::convertStmtList(__args) {
    __perf_trace("convert", "convertStmtList");
    auto __trace = trace(a);
    auto stmt    = Sem<StmtList>(a);
    for (auto const& it : flatConvertAttachedSubnodes(a)) {
        stmt->subnodes.push_back(it.unwrap());
    }
    return stmt;
}


OrgConverter::ConvResult<InlineFootnote> OrgConverter::
    convertInlineFootnote(__args) {
    __perf_trace("convert", "convertInlineFootnote");
    auto __trace     = trace(a);
    auto note        = Sem<InlineFootnote>(a);
    note->definition = convert(one(a, N::Definition));
    return note;
}

OrgConverter::ConvResult<Link> OrgConverter::convertLink(__args) {
    __perf_trace("convert", "convertLink");
    auto __trace   = trace(a);
    auto link      = Sem<Link>(a);
    auto getTarget = [&]() {
        return lstrip(get_text(one(a, N::Link)), CharSet{':'});
    };
    if (a.kind() == onk::RawLink) {
        link->data = Link::Raw{.text = get_text(a)};

    } else if (a.kind() == onk::Footnote) {
        link->data = Link::Footnote{
            .target = get_text(one(a, N::Definition))};

    } else if (one(a, N::Protocol).kind() == onk::Empty) {
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

    if (a.kind() == onk::Link) {
        if (one(a, N::Desc).kind() == onk::Paragraph) {
            link->description = convertParagraph(one(a, N::Desc)).value();
        }
    }

    return link;
}

OrgConverter::ConvResult<List> OrgConverter::convertList(__args) {
    __perf_trace("convert", "convertList");
    auto __trace = trace(a);
    auto list    = Sem<List>(a);
    for (const auto& it : a) { list->push_back(convert(it)); }

    return list;
}

OrgConverter::ConvResult<ListItem> OrgConverter::convertListItem(__args) {
    __perf_trace("convert", "convertListItem");
    auto __trace = trace(a);
    auto item    = Sem<ListItem>(a);
    if (one(a, N::Header).kind() != onk::Empty) {
        item->header = convertParagraph(one(a, N::Header)).value();
    }

    if (auto bullet = one(a, N::Bullet); bullet.kind() != onk::Empty) {
        item->bullet = strip(get_text(bullet), CharSet{' '}, CharSet{' '});
    }

    if (one(a, N::Checkbox).kind() != onk::Empty) {
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
            return SemError(
                a, fmt("Unexpected list item checkbox {}", text));
        }
    }

    {
        for (const auto& sub : one(a, N::Body)) {
            item->push_back(convert(sub));
        }
    }

    return item;
}

OrgConverter::ConvResult<CmdCaption> OrgConverter::convertCmdCaption(
    __args) {
    __perf_trace("convert", "convertCmdCaption");
    auto __trace  = trace(a);
    auto caption  = Sem<CmdCaption>(a);
    caption->text = convertParagraph(one(a, N::Args)[0]).value();

    return caption;
}


OrgConverter::ConvResult<CmdTblfm> OrgConverter::convertCmdTblfm(__args) {
    __perf_trace("convert", "convertCmdTblfm");
    auto __trace = trace(a);
    auto tblfm   = Sem<CmdTblfm>(a);

    return tblfm;
}


OrgConverter::ConvResult<Word> OrgConverter::convertWord(__args) {
    auto __trace = trace(a);
    return SemLeaf<Word>(a);
}

OrgConverter::ConvResult<Placeholder> OrgConverter::convertPlaceholder(
    __args) {
    __perf_trace("convert", "convertPlaceholder");
    auto __trace = trace(a);
    return SemLeaf<Placeholder>(a);
}

OrgConverter::ConvResult<Newline> OrgConverter::convertNewline(__args) {
    auto __trace = trace(a);
    return SemLeaf<Newline>(a);
}

OrgConverter::ConvResult<Space> OrgConverter::convertSpace(__args) {
    return SemLeaf<Space>(a);
}

OrgConverter::ConvResult<Escaped> OrgConverter::convertEscaped(__args) {
    return SemLeaf<Escaped>(a);
}

OrgConverter::ConvResult<RawText> OrgConverter::convertRawText(__args) {
    return SemLeaf<RawText>(a);
}

OrgConverter::ConvResult<RadioTarget> OrgConverter::convertRadioTarget(
    __args) {
    auto result = Sem<RadioTarget>(a);
    for (auto const& sub : a) { result->text += get_text(sub); }
    return result;
}

OrgConverter::ConvResult<TextTarget> OrgConverter::convertTextTarget(
    __args) {
    auto result = Sem<TextTarget>(a);
    for (auto const& sub : a) { result->text += get_text(sub); }
    return result;
}


OrgConverter::ConvResult<Punctuation> OrgConverter::convertPunctuation(
    __args) {
    auto __trace = trace(a);
    return SemLeaf<Punctuation>(a);
}

OrgConverter::ConvResult<BigIdent> OrgConverter::convertBigIdent(__args) {
    __perf_trace("convert", "convertBigIdent");
    auto __trace = trace(a);
    return SemLeaf<BigIdent>(a);
}

OrgConverter::ConvResult<MarkQuote> OrgConverter::convertMarkQuote(
    __args) {
    __perf_trace("convert", "convertMarkQuote");
    auto __trace = trace(a);
    return convertAllSubnodes<MarkQuote>(a);
}

OrgConverter::ConvResult<Verbatim> OrgConverter::convertVerbatim(__args) {
    __perf_trace("convert", "convertVerbatim");
    auto __trace = trace(a);
    return convertAllSubnodes<Verbatim>(a);
}

OrgConverter::ConvResult<Bold> OrgConverter::convertBold(__args) {
    __perf_trace("convert", "convertBold");
    auto __trace = trace(a);
    return convertAllSubnodes<Bold>(a);
}

OrgConverter::ConvResult<Monospace> OrgConverter::convertMonospace(
    __args) {
    __perf_trace("convert", "convertMonospace");
    auto __trace = trace(a);
    return convertAllSubnodes<Monospace>(a);
}

OrgConverter::ConvResult<Strike> OrgConverter::convertStrike(__args) {
    __perf_trace("convert", "convertStrike");
    auto __trace = trace(a);
    return convertAllSubnodes<Strike>(a);
}

OrgConverter::ConvResult<Par> OrgConverter::convertPar(__args) {
    __perf_trace("convert", "convertPar");
    auto __trace = trace(a);
    return convertAllSubnodes<Par>(a);
}

OrgConverter::ConvResult<Italic> OrgConverter::convertItalic(__args) {
    __perf_trace("convert", "convertItalic");
    auto __trace = trace(a);
    return convertAllSubnodes<Italic>(a);
}

OrgConverter::ConvResult<Underline> OrgConverter::convertUnderline(
    __args) {
    __perf_trace("convert", "convertUnderline");
    auto __trace = trace(a);
    return convertAllSubnodes<Underline>(a);
}

OrgConverter::ConvResult<BlockExample> OrgConverter::convertBlockExample(
    __args) {
    SemId<BlockExample> result = Sem<BlockExample>(a);
    for (auto const& it : many(a, N::Body)) {
        result->subnodes.push_back(convert(it));
    }

    return result;
}

OrgConverter::ConvResult<BlockDynamicFallback> OrgConverter::
    convertBlockDynamicFallback(__args) {
    SemId<BlockDynamicFallback> result = Sem<BlockDynamicFallback>(a);
    result->attrs = convertAttrs(one(a, N::Args)).optNode();

    result->name = normalize(get_text(one(a, N::Name)));
    boost::replace_all(result->name, "begin", "");
    for (auto const& it : many(a, N::Body)) {
        result->subnodes.push_back(convert(it));
    }

    return result;
}

OrgConverter::ConvResult<ColonExample> OrgConverter::convertColonExample(
    __args) {
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

OrgConverter::ConvResult<BlockExport> OrgConverter::convertBlockExport(
    __args) {
    auto eexport = Sem<BlockExport>(a);
    switch (a.kind()) {
        case onk::BlockExport:
            eexport->format = BlockExport::Format::Block;
            break;
        default: {
        }
    }

    auto values = convertAttrs(one(a, N::Args)).value();
    if (auto place = values->getAttrs("placement"); !place.empty()) {
        eexport->placement = place.at(0).getString();
        values->named.erase("placement");
    }


    eexport->exporter = get_text(one(a, N::Name));
    eexport->attrs    = values;
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

OrgConverter::ConvResult<BlockCenter> OrgConverter::convertBlockCenter(
    __args) {
    SemId<BlockCenter> res = Sem<BlockCenter>(a);
    for (const auto& sub : many(a, N::Body)) {
        auto aux = convert(sub);
        res->push_back(aux);
    }
    return res;
}

OrgConverter::ConvResult<BlockQuote> OrgConverter::convertBlockQuote(
    __args) {
    SemId<BlockQuote> quote = Sem<BlockQuote>(a);

    if (auto args = one(a, N::Args); args.kind() != onk::Empty) {
        quote->attrs = convertAttrs(args).value();
    }

    for (const auto& sub : flatConvertAttached(many(a, N::Body))) {
        quote->push_back(sub.unwrap());
    }
    return quote;
}

OrgConverter::ConvResult<BlockComment> OrgConverter::convertBlockComment(
    __args) {
    SemId<BlockComment> result = Sem<BlockComment>(a);
    for (const auto& sub : flatConvertAttached(many(a, N::Body))) {
        result->push_back(sub.unwrap());
    }
    return result;
}

OrgConverter::ConvResult<Latex> OrgConverter::convertMath(__args) {
    if (a.kind() == onk::InlineMath) {
        return Sem<Latex>(a);
    } else {
        throw convert_logic_error::init(
            "Unhanled kind for inline math TODO");
    }
}

OrgConverter::ConvResult<Include> OrgConverter::convertInclude(__args) {
    SemId<Include> include = Sem<Include>(a);
    auto           args    = convertAttrs(one(a, N::Args)).value();
    include->path          = args->positional->args.at(0)->arg.getString();

    if (auto kind = args->positional->args.get(1)) {
        Str ks = kind.value().get()->arg.value;
        if (ks == "src"_ss) {
            auto src      = sem::Include::Src{};
            include->data = src;

        } else {
            return SemError(a, fmt("Unhandled org include kind {}", ks));
        }

    } else {
        include->data = sem::Include::OrgDocument{};
    }

    if (args->named.contains("minlevel")) {
        include->getOrgDocument().minLevel //
            = args->named.at("minlevel")->args.at(0)->arg.getInt();
    }

    if (args->named.contains("lines")) {
        Str lines = strip(
            args->getAttrs("lines").at(0).getString(),
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

OrgConverter::ConvResult<TextSeparator> OrgConverter::convertTextSeparator(
    __args) {
    return Sem<TextSeparator>(a);
}

OrgConverter::ConvResult<AtMention> OrgConverter::convertAtMention(
    __args) {
    return SemLeaf<AtMention>(a);
}

OrgConverter::ConvResult<Attr> OrgConverter::convertAttr(__args) {
    auto        __trace = trace(a);
    SemId<Attr> result  = Sem<Attr>(a);
    Str         key     = get_text(one(a, N::Name));
    result->arg.value   = get_text(one(a, N::Value));

    if (!key.empty()) { result->arg.name = key.substr(1); }

    if (TraceState) {
        print(fmt("key:{} value:{}", result->arg.name, result->arg.value));
    }

    return result;
}

OrgConverter::ConvResult<Attrs> OrgConverter::convertAttrs(__args) {
    auto         __trace = trace(a);
    SemId<Attrs> result  = Sem<Attrs>(a);
    result->positional   = SemId<AttrList>::New();

    if (a.getKind() == onk::Attrs) {
        for (auto const& item : one(a, N::Values)) {
            addArgument(result, convertAttr(item).value());
        }
    } else if (a.getKind() == onk::InlineStmtList) {
        for (auto const& it : a) {
            addArgument(result, convertAttr(it).value());
        }
    } else {
        CHECK(a.getKind() == onk::Empty) << a.treeRepr();
    }

    return result;
}

OrgConverter::ConvResult<Attrs> OrgConverter::convertCallArguments(
    CVec<In> args,
    In       source) {
    auto result        = Sem<Attrs>(source);
    result->positional = SemId<AttrList>::New();

    for (auto const& arg : args) {
        auto conv = Sem<Attr>(arg);
        if (2 < arg.size() && get_text(arg.at(1)) == "=") {
            conv->arg.name = get_text(arg.at(0));
            for (int i = 2; i < arg.size(); ++i) {
                conv->arg.value += get_text(arg.at(i));
            }
        } else {
            for (int i = 0; i < arg.size(); ++i) {
                conv->arg.value += get_text(arg.at(i));
            }
        }

        addArgument(result, conv);
    }

    return result;
}

OrgConverter::ConvResult<CmdAttr> OrgConverter::convertCmdAttr(__args) {
    auto           __trace = trace(a);
    SemId<CmdAttr> result  = Sem<CmdAttr>(a);
    result->target         = normalize(get_text(one(a, N::Name)));
    result->attrs          = convertAttrs(one(a, N::Args)).value();

    return result;
}

OrgConverter::ConvResult<CmdName> OrgConverter::convertCmdName(__args) {
    auto           __trace = trace(a);
    SemId<CmdName> result  = Sem<CmdName>(a);
    auto           args    = convertAttr(a.at(0).at(0));

    if (auto name = args.optNode()) {
        result->name = name->value->arg.value;
    } else {
        result->push_back(args.optError().value());
    }

    return result;
}

SemId<ErrorItem> OrgConverter::SemErrorItem(
    In          adapter,
    CR<Str>     message,
    int         line,
    const char* function) {
    auto res      = Sem<ErrorItem>(adapter);
    res->message  = message;
    res->line     = line;
    res->function = function;
    if (TraceState) {
        print(fmt("{} {}", message, getLocMsg(adapter)), line, function);
    }
    return res;
}

SemId<ErrorGroup> OrgConverter::SemError(
    In          adapter,
    CR<Str>     message,
    int         line,
    const char* function) {
    auto res = Sem<ErrorGroup>(adapter);
    res->diagnostics.push_back(
        SemErrorItem(adapter, message, line, function));
    res->line     = line;
    res->function = function;
    return res;
}

SemId<ErrorGroup> OrgConverter::SemError(
    In                    adapter,
    Vec<SemId<ErrorItem>> errors,
    int                   line,
    const char*           function) {
    auto res         = Sem<ErrorGroup>(adapter);
    res->diagnostics = errors;
    res->line        = line;
    res->function    = function;
    return res;
}

OrgConverter::ConvResult<BlockCode> OrgConverter::convertBlockCode(
    __args) {
    SemId<BlockCode> result = Sem<BlockCode>(a);

    if (one(a, N::Lang).getKind() != onk::Empty) {
        result->lang = get_text(one(a, N::Lang));
    }

    if (one(a, N::HeaderArgs).kind() != onk::Empty) {
        auto args = convertAttrs(one(a, N::HeaderArgs)).optNode().value();
        result->attrs = args;
    }

    if (a.kind() == onk::SrcInlineCode) {
        BlockCodeLine& line = result->lines.emplace_back();
        for (auto const& it : one(a, N::Body)) {
            line.parts.push_back(
                BlockCodeLine::Part(BlockCodeLine::Part::Raw{
                    .code = get_text(it),
                }));
        }
    } else {
        for (auto const& it : one(a, N::Body)) {
            BlockCodeLine& line = result->lines.emplace_back();
            for (auto const& part : it) {
                switch (part.kind()) {
                    case onk::CodeText: {
                        line.parts.push_back(
                            BlockCodeLine::Part(BlockCodeLine::Part::Raw{
                                .code = get_text(part),
                            }));
                        break;
                    }
                    default: {
                        throw convert_logic_error::init(fmt1(part.kind()));
                    }
                }
            }
        }
    }

    if (auto res = one(a, N::Result); res.kind() != onk::Empty) {
        auto body = one(res, N::Body);
        auto conv = convert(body);
        if (auto link = conv.asOpt<sem::Link>(); link && link->isFile()) {
            result->result = sem::BlockCodeEvalResult{
                sem::BlockCodeEvalResult::File{
                    .path = link->getFile().file}};
        } else {
            result->result = sem::BlockCodeEvalResult{
                sem::BlockCodeEvalResult::Raw{
                    .text = sem::Formatter::format(conv)}};
        }
    }

    return result;
}

OrgConverter::ConvResult<Call> OrgConverter::convertCall(__args) {
    __perf_trace("convert", "convertCall");
    auto __trace = trace(a);
    if (a.kind() == onk::CmdCallCode) {
        auto call       = Sem<Call>(a);
        call->name      = get_text(one(a, N::Name));
        call->isCommand = true;
        call->attrs = convertCallArguments(many(a, N::Args), a).value();
        return call;
    } else {
        return SemError(a, "TODO Convert inline call");
    }
}


Vec<OrgConverter::ConvResult<Org>> OrgConverter::flatConvertAttached(
    Vec<OrgAdapter> items) {
    auto __trace = trace(std::nullopt);

    Vec<OrgConverter::ConvResult<Org>> result;

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


                int offset = 0;

                Opt<CRw<OrgAdapter>> next_opt = items.get(i + offset + 1);
                while (next_opt) {
                    if (next_opt->get().getKind() == onk::CmdTblfm) {
                        print(
                            fmt("tblfm attached {} + {} {}",
                                i,
                                offset,
                                next_opt->get().id));
                        auto tblfm = convertCmdTblfm(next_opt->get());
                        res_stmt->attached.push_back(tblfm.unwrap());
                        ++offset;
                    } else {
                        print(
                            fmt("next node is not post-attached {}",
                                next_opt->get().getKind()));
                        break;
                    }

                    next_opt = items.get(i + offset + 1);
                }

                i += offset;

            } else {
                print(
                    fmt("{} is not a statement, releasing attached",
                        res->getKind()));
                for (auto const& buf : buffer) { result.push_back(buf); }
            }
            buffer.clear();


            result.push_back(res);
        }
    }

    for (auto const& buf : buffer) { result.push_back(buf); }

    return result;
}

Vec<OrgConverter::ConvResult<Org>> OrgConverter::
    flatConvertAttachedSubnodes(In item) {
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

    switch (a.kind()) {
        case onk::Newline: return convertNewline(a).unwrap();
        case onk::StmtList: return convertStmtList(a).unwrap();
        case onk::Subtree: return convertSubtree(a).unwrap();
        case onk::TimeRange: return convertTimeRange(a).unwrap();
        case onk::Space: return convertSpace(a).unwrap();
        case onk::Word: return convertWord(a).unwrap();
        case onk::Bold: return convertBold(a).unwrap();
        case onk::Italic: return convertItalic(a).unwrap();
        case onk::Strike: return convertStrike(a).unwrap();
        case onk::Punctuation: return convertPunctuation(a).unwrap();
        case onk::Link: return convertLink(a).unwrap();
        case onk::Par: return convertPar(a).unwrap();
        case onk::BigIdent: return convertBigIdent(a).unwrap();
        case onk::Verbatim: return convertVerbatim(a).unwrap();
        case onk::RawText: return convertRawText(a).unwrap();
        case onk::List: return convertList(a).unwrap();
        case onk::ListItem: return convertListItem(a).unwrap();
        case onk::Placeholder: return convertPlaceholder(a).unwrap();
        case onk::Escaped: return convertEscaped(a).unwrap();
        case onk::TextSeparator: return convertTextSeparator(a).unwrap();
        case onk::AtMention: return convertAtMention(a).unwrap();
        case onk::Underline: return convertUnderline(a).unwrap();
        case onk::Target: return convertTextTarget(a).unwrap();
        case onk::RadioTarget: return convertRadioTarget(a).unwrap();
        case onk::InlineStmtList: return convertStmtList(a).unwrap();
        case onk::SrcInlineCode:
        case onk::BlockCode: return convertBlockCode(a).unwrap();
        case onk::InlineFootnote: return convertInlineFootnote(a).unwrap();
        case onk::BlockExport: return convertBlockExport(a).unwrap();
        case onk::Macro: return convertMacro(a).unwrap();
        case onk::Monospace: return convertMonospace(a).unwrap();
        case onk::BlockCenter: return convertBlockCenter(a).unwrap();
        case onk::BlockExample: return convertBlockExample(a).unwrap();
        case onk::HashTag: return convertHashTag(a).unwrap();
        case onk::ListTag: return convert(a[0]);
        case onk::InlineMath: return convertMath(a).unwrap();
        case onk::RawLink: return convertLink(a).unwrap();
        case onk::StaticActiveTime:
        case onk::StaticInactiveTime:
        case onk::DynamicActiveTime:
        case onk::DynamicInactiveTime: return convertTime(a).unwrap();
        case onk::Quote: return convertMarkQuote(a).unwrap();
        case onk::BlockComment: return convertBlockComment(a).unwrap();
        case onk::BlockQuote: return convertBlockQuote(a).unwrap();
        case onk::Colon: return convertPunctuation(a).unwrap();
        case onk::CmdInclude: return convertInclude(a).unwrap();
        case onk::Symbol: return convertSymbol(a).unwrap();
        case onk::Angle: return convertPlaceholder(a).unwrap();
        case onk::Empty: return Sem<Empty>(a);
        case onk::Table: return convertTable(a).unwrap();
        case onk::Footnote: return convertLink(a).unwrap();
        case onk::CmdTblfm: return convertCmdTblfm(a).unwrap();
        case onk::CmdAttr: return convertCmdAttr(a).unwrap();
        case onk::ColonExample: return convertColonExample(a).unwrap();
        case onk::CmdCaption: return convertCmdCaption(a).unwrap();
        case onk::CmdName: return convertCmdName(a).unwrap();
        case onk::CmdCallCode: return convertCall(a).unwrap();
        case onk::Paragraph: return convertParagraph(a).unwrap();
        case onk::BlockDynamicFallback:
            return convertBlockDynamicFallback(a).unwrap();
        default: {
            return SemError(a, fmt("ERR Unknown content {}", a.getKind()));
        }
    }
#undef CASE
}

void OrgConverter::convertDocumentOptions(
    SemId<DocumentOptions> opts,
    OrgAdapter             a) {
    if (opts->isGenerated()) { opts->original = a; }
    auto item      = a.at(0);
    auto parseBool = [](CR<Str> value) {
        return value == "t" || value == "T";
    };
    for (auto const& value : get_text(item).split(' ')) {
        if (value.contains(':')) {
            auto split = value.split(':');
            auto head  = split[0];
            auto tail  = split[1];
            if (org_streq(head, "broken-links")) {
                if (org_streq(tail, "mark")) {
                    opts->exportConfig.brokenLinks = DocumentExportConfig::
                        BrokenLinks::Mark;
                } else if (org_streq(tail, "t")) {
                    opts->exportConfig.brokenLinks = DocumentExportConfig::
                        BrokenLinks::Ignore;
                }
            } else if (org_streq(head, "toc")) {
                if (org_streq(tail, "t")) {
                    opts->exportConfig.tocExport = DocumentExportConfig::
                        DoExport{true};
                } else if (org_streq(tail, "nil")) {
                    opts->exportConfig.tocExport = DocumentExportConfig::
                        DoExport{false};
                } else if ('0' <= tail[0] && tail[0] <= '9') {
                    opts->exportConfig.tocExport = DocumentExportConfig::
                        ExportFixed{tail.toInt()};
                }
            } else if (org_streq(head, "<")) {
                opts->exportConfig.inlinetasks = parseBool(tail);
            } else if (org_streq(head, "f")) {
                opts->exportConfig.footnotes = parseBool(tail);
            } else if (org_streq(head, "c")) {
                opts->exportConfig.clock = parseBool(tail);
            } else if (org_streq(head, "author")) {
                opts->exportConfig.author = parseBool(tail);
            } else if (org_streq(head, "todo")) {
                opts->exportConfig.todoText = parseBool(tail);
            } else if (org_streq(head, "*")) {
                opts->exportConfig.emphasis = parseBool(tail);
            } else if (org_streq(head, "-")) {
                opts->exportConfig.specialStrings = parseBool(tail);
            } else {
                opts->push_back(SemError(
                    a,
                    fmt("Unexpected document option value {}, head:'{}', "
                        "tail:'{}'",
                        value,
                        head,
                        tail)));
            }

        } else if (org_streq(value, ":")) {
            opts->fixedWidthSections = true;
        } else {
            opts->push_back(SemError(
                a, fmt("Unexpected document option value {}", value)));
        }
    }
}

SemId<Document> OrgConverter::toDocument(OrgAdapter adapter) {
    auto __trace = trace(adapter);

    SemId<Document> doc = Sem<Document>(adapter);
    doc->options        = Sem<DocumentOptions>(adapter);
    using Prop          = NamedProperty;
    Vec<OrgAdapter> buffer;

    if (adapter.kind() == onk::StmtList) {
        for (const auto& sub : adapter) {
            auto __trace = trace(adapter, fmt1(sub.getKind()));
            switch (sub.kind()) {
                case onk::CmdColumns: {
                    break;
                }
                case onk::CmdTitle: {
                    doc->title = convertParagraph(sub[0]).value();
                    break;
                }
                case onk::CmdOptions: {
                    convertDocumentOptions(doc->options, sub);
                    break;
                }

                case onk::CmdPropertyArgs: {
                    Prop::CustomArgs prop;
                    prop.name = get_text(one(sub, N::Name));
                    auto conv = convertAttrs(one(sub, N::Args));
                    for (auto const& [key, list] : conv.value()->named) {
                        for (auto const& it : list->args) {
                            prop.attrs.push_back(it->arg);
                        }
                    }
                    for (auto const& it : conv.value()->positional->args) {
                        prop.attrs.push_back(it->arg);
                    }
                    doc->options->properties.push_back(Prop(prop));
                    break;
                }

                case onk::CmdStartup: {
                    Vec<Str> args = get_text(sub.at(0)).split(" ");
                    Str      text = normalize(args.at(0));
                    using K       = InitialSubtreeVisibility;
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
                        throw convert_logic_error::init(text);
                    }

                    if (auto it = args.get(1); it.has_value()) {
                        if (org_streq(*it, "indent")) {
                            doc->options->startupIndented = true;
                        }
                    }

                    break;
                }

                case onk::CmdLatexClass: {
                    Prop::ExportLatexClass res{};
                    res.latexClass = get_text(sub.at(0));
                    doc->options->properties.push_back(Prop(res));
                    break;
                }
                case onk::CmdLatexHeader: {
                    Prop::ExportLatexHeader res{};
                    res.header = get_text(sub.at(0));
                    doc->options->properties.push_back(Prop(res));
                    break;
                }
                case onk::CmdLatexCompiler: {
                    Prop::ExportLatexCompiler res{};
                    res.compiler = get_text(sub.at(0));
                    doc->options->properties.push_back(Prop(res));
                    break;
                }
                case onk::CmdLatexClassOptions: {
                    auto value = get_text(sub.at(0));
                    Prop::ExportLatexClassOptions res;
                    res.options.push_back(value);
                    doc->options->properties.push_back(Prop(res));
                    break;
                }
                case onk::CmdFiletags: {
                    for (auto const& hash : many(sub, N::Tags)) {
                        doc->filetags.push_back(
                            convertHashTag(hash).value());
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
        doc->subnodes.push_back(it.unwrap());
    }

    return doc;
}
