#include <haxorg/sem/SemConvert.hpp>
#include <hstd/stdlib/Func.hpp>
#include <haxorg/parse/OrgSpec.hpp>

#include <hstd/stdlib/Debug.hpp>

#include <boost/preprocessor/facilities/overload.hpp>
#include <boost/preprocessor/facilities/empty.hpp>
#include <haxorg/sem/perfetto_org.hpp>
#include <haxorg/exporters/exportertree.hpp>
#include <absl/log/log.h>
#include <haxorg/sem/SemOrgFormat.hpp>
#include <lexy/dsl/identifier.hpp>
#include <lexy_ext/report_error.hpp>
#include <lexy/input/string_input.hpp>

#include <lexy/callback.hpp>
#include <lexy/dsl.hpp>
#include <lexy/input/string_input.hpp>
#include <lexy/action/parse.hpp>
#include <lexy/callback.hpp>
#include <lexy/callback/container.hpp>
#include <lexy/action/trace.hpp>
#include <stack>

struct convert_logic_error : hstd::CRTP_hexception<convert_logic_error> {};

using namespace org::sem;
using namespace org::algo;
using namespace org;
using namespace hstd;

using onk      = OrgNodeKind;
using otk      = OrgTokenKind;
using Err      = OrgConverter::Errors;
using Property = org::sem::NamedProperty;

namespace {
bool org_streq(CR<Str> str1, CR<Str> str2) {
    return normalize(str1) == normalize(str2);
}

Str strip_space(Str const& space) {
    return strip(space, CharSet{' '}, CharSet{' '});
}

org::sem::SubtreePath convertSubtreePath(Str const& path) {
    org::sem::SubtreePath res;
    for (auto const& item :
         strip(path, CharSet{'*', ' '}, CharSet{' '}).split("/")) {
        res.path.push_back(strip_space(item));
    }
    return res;
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

Opt<UserTime> ParseUserTime(
    std::string                datetime,
    Opt<absl::TimeZone> const& zone) {
    struct Spec {
        std::string         pattern;
        UserTime::Alignment align = UserTime::Alignment::Second;
    };

    Vec<Spec> formats = {
        Spec{.pattern = "%Y-%m-%d %H:%M:%S"},
        Spec{.pattern = "%Y/%m/%d %H:%M:%S"},
        Spec{.pattern = "%d-%m-%Y %H:%M:%S"},
        Spec{.pattern = "%d/%m/%Y %H:%M:%S"},
        Spec{.pattern = "%Y-%m-%d %a %H:%M:%S"},
        Spec{
            .pattern = "%Y-%m-%d %H:%M",
            .align   = UserTime::Alignment::Minute,
        },
        Spec{.pattern = "%Y-%m-%d", .align = UserTime::Alignment::Day},
        // Add other formats as needed
    };

    absl::Time parsedDateTime;
    for (const auto& format : formats) {
        std::string error;
        if (absl::ParseTime(
                format.pattern,
                datetime,
                zone ? zone.value() : absl::TimeZone(),
                &parsedDateTime,
                &error)) {

            return UserTime{
                .time  = parsedDateTime,
                .align = format.align,
                .zone  = zone,
            };
        }
    }

    return std::nullopt;
}


} // namespace

Str get_text(
    org::parse::OrgAdapter a,
    int                    line     = __builtin_LINE(),
    char const*            function = __builtin_FUNCTION()) {
    if (a.isTerminal()) {
        return a.val().text;
    } else if (a.kind() == onk::Empty) {
        return "";
    } else if (a.kind() == onk::InlineStmtList) {
        Str res;
        for (auto const& it : a) { res += get_text(it); }
        return res;
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
        result->attrs   = convertAttrs(args);
    }

    for (auto const& in_row : many(a, N::Rows)) {
        SemId<Row> row = Sem<Row>(in_row);
        if (auto args = one(in_row, N::Args);
            args.getKind() == onk::InlineStmtList) {
            row->isBlock = true;
            row->attrs   = convertAttrs(args);
        }

        for (auto const& in_cell : one(in_row, N::Body)) {
            SemId<Cell> cell = Sem<Cell>(in_cell);
            if (auto args = one(in_cell, N::Args);
                args.getKind() == onk::InlineStmtList) {
                cell->isBlock = true;
                cell->attrs   = convertAttrs(args);
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
    auto __trace = trace(a);
    auto result  = Sem<HashTag>(a);

    Func<sem::HashTagText(org::parse::OrgAdapter)> aux;
    aux = [&aux, this](org::parse::OrgAdapter a) -> sem::HashTagText {
        sem::HashTagText text;
        text.head = strip(get_text(a.at(0)), CharSet{'#'}, CharSet{});
        if (1 < a.size()) {
            for (auto& node : a.at(slice(1, 1_B))) {
                auto conv = aux(node);
                text.subtags.push_back(conv);
            }
        }
        return text;
    };

    sem::HashTagText text;
    text.head = strip(get_text(a.at(0)), CharSet{'#'}, CharSet{});
    if (1 < a.size()) {
        for (auto& node : a.at(slice(1, 1_B))) {
            auto conv = aux(node);
            text.subtags.push_back(conv);
        }
    }

    result->text = text;

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


    using Log            = SubtreeLogHead;
    SemId<ListItem> item = convertListItem(a).value();
    SemId<Org>      par0 = item->at(0);

    SemSet limit{osk::Newline};

    Vec<Str> words = //
        own_view(filter_subnodes<Word>(par0, limit))
        | rv::transform(
            [](OrgArg arg) { return normalize(arg.as<Word>()->text); })
        | rs::to<Vec>();

    auto node_after = [&](CR<Str>    word,
                          CR<SemSet> target) -> Opt<sem::SemId<sem::Org>> {
        auto __trace = trace(a, "node_after");
        print(
            fmt("Searching for '{}' after '{}' in {}",
                target,
                word,
                par0->subnodes));
        for (int i = 0; i < par0.size(); ++i) {
            if (auto w = par0.at(i)->dyn_cast<sem::Leaf>();
                w != nullptr && normalize(w->text) == word) {
                print(fmt("[{}] = {}({})", i, w->getKind(), w->text));
                auto offset = i + 1;
                while (offset < par0.size()) {
                    auto t = par0.at(offset);
                    print(fmt("[{}] = {}", offset, t->getKind()));
                    if ((SemSet{osk::Word} - target)
                            .contains(t->getKind())) {
                        goto found_search_limit;
                    } else if (target.contains(t->getKind())) {
                        return t;
                    } else {
                        ++offset;
                    }
                }

            found_search_limit:
            }
        }
        return std::nullopt;
    };

    auto time_after = [&](CR<Str> word) -> Opt<sem::SemId<sem::Time>> {
        auto t = node_after(word, SemSet{osk::Time});
        if (t) {
            return t.value().as<sem::Time>();
        } else {
            return std::nullopt;
        }
    };

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
            clock.from = times.at(0).as<Time>()->getStaticTime();
        } else {
            auto range = times.at(0).as<TimeRange>();
            clock.from = range->from->getStaticTime();
            clock.to   = range->to->getStaticTime();
        }

        log->head = Log{clock};
    } else {
        Vec<SemId<Time>> times = filter_subnodes<Time>(par0, limit);

        if (words.at(0) == "tag") {
            auto res = Log::Tag{};
            if (auto tag = node_after("tag", {osk::HashTag})) {
                res.tag = tag->as<sem::HashTag>()->text;
            } else {
                return SemError(
                    a, "No hashtag provided for the 'tag' value");
            }

            if (auto on = time_after("on")) {
                res.on = on.value()->getStaticTime();
            }

            if (words.at(1) == "added") {
                res.added = true;
            } else {
                res.added = false;
            }

            log->head = Log{res};

        } else if (words.at(0) == "state") {
            auto __trace = trace(a, "state");
            auto states  = Log::State{};
            if (auto state = node_after("state", {osk::BigIdent})) {
                states.to = state.value().as<sem::BigIdent>()->text;
            } else {
                return SemError(
                    a,
                    "No current state provided for the subtree state log "
                    "change");
            }
            if (auto from = node_after("from", {osk::BigIdent})) {
                states.from = from.value().as<sem::BigIdent>()->text;
            }


            Vec<SemId<Time>> times = filter_subnodes<Time>(par0, limit);
            if (auto from = time_after("on")) {
                states.on = from.value()->getStaticTime();
            } else if (times.has(0)) {
                states.on = times.at(0)->getStaticTime();
            }

            log->head = Log{states};

        } else if (words.at(0) == "refiled") {
            auto             __trace = trace(a, "refiled");
            Vec<SemId<Time>> times   = filter_subnodes<Time>(par0, limit);
            Vec<SemId<Link>> link    = filter_subnodes<Link>(par0, limit);
            auto             refile  = Log::Refile{};
            CHECK(!times.empty())
                << a.treeRepr() << ExporterTree::treeRepr(item).toString();

            if (auto time = time_after("on")) {
                refile.on = time.value()->getStaticTime();
            } else {
                return SemError(
                    a, "No 'on' time for the refiled subtree log");
            }

            if (!link.empty()) { refile.from = link.at(0)->target; }
            log->head = Log{refile};

        } else if (words.at(1) == "deadline") {
            auto             __trace = trace(a, "deadline");
            Vec<SemId<Time>> times   = filter_subnodes<Time>(par0, limit);
            auto             dead    = Log::Deadline{};
            auto             on      = time_after("on");
            auto             from    = time_after("from");
            log->head                = Log{dead};

        } else if (words.at(0) == "priority") {
            auto __trace = trace(a, "priority");
            print(fmt("words {}", words));
            Vec<SemId<Time>> times = filter_subnodes<Time>(par0, limit);
            Vec<SemId<BigIdent>> priorities = filter_subnodes<BigIdent>(
                par0, limit);
            auto priority = Log::Priority{};

            if (words.contains("added")) {
                if (auto new_ = node_after("priority", {osk::BigIdent})) {
                    priority.newPriority = new_->as<sem::BigIdent>()->text;
                }

                priority.action = Log::Priority::Action::Added;
            } else if (words.contains("changed")) {
                if (auto new_ = node_after("priority", {osk::BigIdent})) {
                    priority.newPriority = new_->as<sem::BigIdent>()->text;
                }

                if (auto old_ = node_after("from", {osk::BigIdent})) {
                    priority.oldPriority = old_->as<sem::BigIdent>()->text;
                }

                priority.action = Log::Priority::Action::Changed;
            } else if (words.contains("removed")) {
                if (auto old_ = node_after("from", {osk::BigIdent})) {
                    priority.oldPriority = old_->as<sem::BigIdent>()->text;
                }
                priority.action = Log::Priority::Action::Removed;
            } else {
                throw convert_logic_error::init(
                    fmt("{} Unexpected priority log message structure",
                        words));
            }

            if (auto on = time_after("on")) {
                priority.on = on.value()->getStaticTime();
            }

            log->head = Log{priority};

        } else if (words.at(0) == "note" && !times.empty()) {
            auto __trace = trace(a, "note");
            auto note    = Log::Note{};

            if (auto on = time_after("on")) {
                note.on = on.value()->getStaticTime();
            }

            log->head = Log{note};

        } else {
            auto __trace = trace(a, "unknown");
            auto unknown = Log::Unknown{};
            auto stmt    = SemId<StmtList>::New();
            for (auto const& sub : item->subnodes) {
                stmt->subnodes.push_back(sub);
            }

            log->desc = stmt;
            log->head = Log{unknown};
        }
    }

    if (!log->head.isUnknown()) {
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

    auto __trace = trace(
        a, fmt("property-'{}' (base: '{}')", name, basename));

    auto get_values_text = [&]() {
        return strip_space(get_text(one(a, N::Values)));
    };

    auto handled = [&](int         line     = __builtin_LINE(),
                       char const* function = __builtin_FUNCTION()) {
        print(fmt("handled '{}'", name), line, function);
    };

    Opt<Property> result;
    if (name == "exportoptions") {
        handled();
        Property::ExportOptions res;
        res.backend = get_text(one(a, N::Subname));
        for (Str const& pair : get_values_text().split(' ')) {
            auto kv           = pair.split(':');
            res.values[kv[0]] = kv[1];
        }

        result = Property(res);

    } else if (name == "id") {
        handled();
        tree->treeId = get_values_text();

    } else if (name == "radioid") {
        handled();
        Property::RadioId radio;
        for (Str const& pair : get_values_text().split(' ')) {
            radio.words.push_back(pair);
        }

        result = Property{radio};
    } else if (name == "hashtagdef") {
        handled();
        Property::HashtagDef def;
        auto par = convertParagraph(one(a, N::Values)).value();
        print(fmt("{}", a.treeRepr()));
        print(fmt("{}", ExporterTree::treeRepr(par).toString(false)));
        for (int i = 0; i < par.size(); ++i) {
            auto sub = par.at(i);
            if (sub->is(OrgSemKind::Space)) {
                continue;
            } else if (auto tag = sub.asOpt<sem::HashTag>()) {
                if (def.hashtag.head.empty()) {
                    def.hashtag = tag.value->text;
                } else {
                    return SemError(
                        a,
                        fmt(":hashtag_def: property can contain only one "
                            "definition, to assign multiple definitions "
                            "to the subtree use repeated `:hashtag_def:` "
                            "property blocks."));
                }
            } else {
                return SemError(
                    a,
                    fmt("Hashtag definition property can only contain "
                        "space or hashtag node, but found node of kind {}",
                        tag->getKind()));
            }
        }

        result = Property{def};
    } else if (name == "created") {
        handled();
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
        handled();
        if (auto visibility = parseOrgEnum<
                sem::NamedProperty::Visibility::Level>(
                get_text(one(a, N::Values)));
            visibility) {
            Property::Visibility prop;
            prop.level = visibility.value();
            result     = Property(prop);
        } else {
            throw convert_logic_error::init("Unknown visibility");
        }

    } else if (name == "cookiedata") {
        handled();
        NamedProperty::CookieData p;
        for (auto const& arg : get_values_text().split(" ")) {
            auto norm = normalize(arg);
            if (norm == "todo") {
                p.source = sem::NamedProperty::CookieData::TodoSource::
                    Todo;
            } else if (norm == "recursive") {
                p.isRecursive = true;
            } else if (norm == "both") {
                p.source = sem::NamedProperty::CookieData::TodoSource::
                    Both;
            } else if (norm == "checkbox") {
                p.source = sem::NamedProperty::CookieData::TodoSource::
                    Checkbox;
            } else {
                return SemError(
                    a, fmt("Unexpected cookie data parameter: {}", arg));
            }
        }

        result = NamedProperty{p};

    } else if (name == "effort") {
        handled();
        Str const&            value    = get_values_text();
        Vec<Str>              duration = value.split(":");
        NamedProperty::Effort prop;

        if (duration.size() == 1) {
            prop.minutes = duration[0].toInt();
        } else if (duration.size() == 2) {
            prop.minutes = duration[1].toInt();
            prop.hours   = duration[0].toInt();
        }

        result = NamedProperty(prop);
    } else if (name == "archivefile") {
        handled();
        NamedProperty::ArchiveFile file{};
        file.file = get_values_text();
        result    = NamedProperty{file};
    } else if (name == "archivetime") {
        handled();
        NamedProperty::ArchiveTime prop{};
        Str                        time = get_values_text();
        Slice<int>                 span = slice(0, time.size() - 1);
        Opt<absl::TimeZone>        zone;
        if (time.at(3_B) == '+' || time.at(3_B) == '-') {
            span.last -= 3;
            zone = ConvertToTimeZone(
                Str{time.at(slice(2_B, 1_B))}.toBase());
        } else if (time.at(5_B) == '+' || time.at(5_B) == '-') {
            span.last -= 5;
            zone = ConvertToTimeZone(
                Str{time.at(slice(4_B, 1_B))}.toBase());
        }

        auto          datetime = Str{time.at(span)}.toBase();
        Opt<UserTime> parsed   = ParseUserTime(datetime, zone);

        if (parsed.has_value()) {
            prop.time = parsed.value();
            result    = NamedProperty{prop};
        } else {
            throw convert_logic_error::init(
                fmt("broken datetime or broken zone from value {} "
                    "(datetime: '{}', zone: '{}')",
                    time,
                    datetime,
                    zone));
        }

    } else if (name == "archivecategory") {
        handled();
        NamedProperty::ArchiveCategory file{};
        file.category = get_values_text();
        result        = NamedProperty{file};
    } else if (name == "archivetodo") {
        handled();
        NamedProperty::ArchiveTodo file{};
        file.todo = get_values_text();
        result    = NamedProperty{file};
    } else if (name == "archive") {
        handled();
        NamedProperty::ArchiveTarget file{};
        auto                         dsl = get_values_text().split("::");
        file.pattern                     = dsl.at(0);
        file.path.path = lstrip(dsl.at(1), CharSet{'*', ' '}).split("/");
        result         = NamedProperty{file};
    } else if (name == "archiveolpath") {
        handled();
        NamedProperty::ArchiveOlpath path{};
        path.path = convertSubtreePath(get_values_text());
        result    = NamedProperty{path};
    } else if (name.starts_with("propjson")) {
        handled();
        NamedProperty::CustomSubtreeJson prop{};
        auto name = strip(basename, CharSet{':'}, CharSet{':'}).split(':');
        if (name.has(1)) { prop.name = normalize(name.at(1)); }
        prop.value = json::parse(strip_space(get_text(one(a, N::Values))));
        result     = NamedProperty{prop};
    } else if (name.starts_with("propargs")) {
        handled();
        NamedProperty::CustomSubtreeFlags prop{};
        auto name = strip(basename, CharSet{':'}, CharSet{':'}).split(':');
        if (name.has(1)) { prop.name = normalize(name.at(1)); }
        prop.value = convertAttrs(one(a, N::Values));
        result     = NamedProperty{prop};
    } else if (
        one(a, N::Values).kind() == onk::InlineStmtList
        && rs::all_of(
            gen_view(one(a, N::Values).items()),
            [](org::parse::OrgAdapter const& a) {
                return a.getKind() == onk::AttrValue;
            })) {
        handled();
        NamedProperty::CustomArgs prop;
        auto                      name = strip(
                        get_text(one(a, N::Name)),
                        CharSet{':'},
                        CharSet{':'})
                        .split(':');

        prop.name = name.at(0);
        if (name.has(1)) { prop.sub = name.at(1); }
        prop.attrs = convertAttrs(one(a, N::Values));
        result     = NamedProperty{prop};

    } else {
        handled();
        NamedProperty::CustomRaw prop;
        prop.name = basename;
        if (one(a, N::Values).kind() == onk::RawText) {
            prop.value = get_values_text();
        } else {
            prop.value = get_text(one(a, N::Values));
        }
        result = NamedProperty(prop);
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
        auto __field    = field(N::Completion, a);
        auto completion = one(a, N::Completion);
        if (completion.kind() != onk::Empty) {
            auto text = strip(
                get_text(completion), CharSet{'['}, CharSet{']'});
            sem::SubtreeCompletion res;
            if (text.ends_with("%")) {
                res.isPercent = true;
                res.done      = rstrip(text, CharSet{'%'}).toInt();
                res.full      = 100;
            } else {
                res.isPercent = false;
                auto split    = text.split("/");
                res.done      = split.at(0).toInt();
                res.full      = split.at(1).toInt();
            }

            tree->completion = res;
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
            if (tag->text.head == "ARCHIVE") {
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

            if (!time->isStatic()) {
                return SemError(
                    a,
                    fmt("Subtree times are expected to have static time, "
                        "provided value is not static."));
            }

            if (org_streq(kind->text, "closed")) {
                tree->closed = time->getStaticTime();
            } else if (org_streq(kind->text, "deadline")) {
                tree->deadline = time->getStaticTime();
            } else if (org_streq(kind->text, "scheduled")) {
                tree->scheduled = time->getStaticTime();
            } else {
                return SemError(
                    a,
                    fmt("Accepted subtree time kinds are 'closed', "
                        "'deadline', 'scheduled', but the value was '{}'",
                        kind));
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

    bool cond = org::parse::OrgSet{
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


        Opt<absl::TimeZone> zone;

        if (auto z = one(a, N::Zone); z.kind() != onk::Empty) {
            zone = ConvertToTimeZone(get_text(z));
        }

        auto parsed = ParseUserTime(datetime, zone);

        if (parsed.has_value()) {
            time->time = Time::Static{.time = parsed.value()};

        } else {
            return SemError(
                a,
                fmt("Could not parse date time entry in format: '{}' at "
                    "'{}'",
                    datetime,
                    getLocMsg(a)));
        }
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

void addArgument(sem::AttrGroup& result, sem::AttrValue const& arg) {
    if (arg.name) {
        auto key = normalize(arg.name.value());
        if (result.named.contains(key)) {
            result.named[key].items.push_back(arg);
        } else {
            sem::AttrList args;
            args.items.push_back(arg);
            result.named.insert({key, args});
        }
    } else {
        result.positional.items.push_back(arg);
    }
}

OrgConverter::ConvResult<Macro> OrgConverter::convertMacro(__args) {
    __perf_trace("convert", "convertMacro");
    auto __trace = trace(a);
    auto macro   = Sem<Macro>(a);
    macro->name  = get_text(one(a, N::Name));
    macro->attrs = convertAttrs(one(a, N::Args));
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
        link->target = LinkTarget{LinkTarget::Raw{.text = get_text(a)}};

    } else if (a.kind() == onk::Footnote) {
        link->target = LinkTarget{LinkTarget::Footnote{
            .target = get_text(one(a, N::Definition))}};
    } else if (one(a, N::Protocol).kind() == onk::Empty) {
        Str target = getTarget();
        if (target.starts_with(".") || target.starts_with("/")) {
            link->target = LinkTarget{LinkTarget::File{.file = target}};
        } else if (target.starts_with("*")) {
            int level = 0;
            for (auto const& c : target) {
                if (c == '*') {
                    ++level;
                } else {
                    break;
                }
            }
            link->target = LinkTarget{LinkTarget::SubtreeTitle{
                .level = level,
                .title = lstrip(target, CharSet{'*', ' '}).split("/"),
            }};

        } else {
            link->target = LinkTarget{
                LinkTarget::Internal{.target = target}};
        }

    } else {
        Str protocol_raw = get_text(one(a, N::Protocol));
        Str protocol     = normalize(get_text(one(a, N::Protocol)));
        print(fmt(
            "Protocol is '{}', normalized {}", protocol_raw, protocol));
        if (protocol == "http" || protocol == "https") {
            link->target = LinkTarget{
                LinkTarget::Raw{.text = protocol + ":"_ss + getTarget()}};
        } else if (protocol == "id") {
            link->target = LinkTarget{
                LinkTarget::Id{.text = strip(getTarget(), {' '}, {' '})}};

        } else if (protocol == "person") {
            link->target = LinkTarget{LinkTarget::Person{}};
            for (auto const& it : one(a, N::Link)) {
                link->target.getPerson().name += get_text(it);
            }

        } else if (protocol == "file") {
            link->target = LinkTarget{
                LinkTarget::File{.file = getTarget()}};

        } else if (protocol == "attachment") {
            link->target = LinkTarget{
                LinkTarget::Attachment{.file = getTarget()}};
        } else if (protocol_raw == "#") {
            link->target = LinkTarget{
                LinkTarget::CustomId{.text = getTarget()}};

        } else {
            link->target = LinkTarget{
                LinkTarget::UserProtocol{.protocol = protocol}};
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

namespace dsl  = lexy::dsl;
using lexy_tok = lexy::string_lexeme<>;
Str lexy_str(lexy_tok const& t) {
    return Str{std::string{t.begin(), t.end()}};
}


namespace tblfmt_grammar {

#define sc static constexpr
#define sc_char static constexpr const char*

struct axis_direction {
    sc_char name = "axis_direction";
    sc auto rule //
        = (dsl::peek(dsl::lit_c<'>'>)
           >> dsl::capture(dsl::token(dsl::while_one(dsl::lit_c<'>'>))))
        | (dsl::peek(dsl::lit_c<'<'>)
           >> dsl::capture(dsl::token(dsl::while_one(dsl::lit_c<'<'>)))) //
        ;

    sc auto value = lexy::as_string<std::string>;
};

struct axis_spec {
    using type   = sem::Tblfm::Expr::AxisRef::Position::Index;
    sc_char name = "axis_spec";
    sc auto rule                                              //
        = dsl::opt(dsl::capture(dsl::token(dsl::lit_c<'-'>))) //
        + dsl::integer<int>                                   //
        + dsl::opt(dsl::p<axis_direction>)                    //
        ;


    static type impl(
        Opt<std::string>        sign,
        int                     position,
        Opt<std::string> const& convert) {
        axis_spec::type result;
        return result;
    }

    sc auto value = lexy::callback<axis_spec::type>(overloaded{
        [](lexy::string_lexeme<> const& sgn,
           int                          position,
           std::string const&           base) {
            return impl(
                std::string{sgn.begin(), sgn.end()}, position, base);
        },
        [](lexy::string_lexeme<> const& sgn,
           int                          position,
           lexy::nullopt const&         base) {
            return impl(
                std::string{sgn.begin(), sgn.end()},
                position,
                std::nullopt);
        },
        [](lexy::nullopt const& sgb,
           int                  position,
           std::string const&   base) {
            return impl(std::nullopt, position, base);
        },
        [](lexy::nullopt const& sgn,
           int                  position,
           lexy::nullopt const& base) {
            return impl(std::nullopt, position, std::nullopt);
        },
    });
};

struct axis_name {
    using type    = sem::Tblfm::Expr::AxisRef::Position::Name;
    sc_char name  = "axis_name";
    sc auto rule  = dsl::identifier(dsl::ascii::alpha_digit_underscore);
    sc auto value = lexy::callback<type>(
        [](lexy::string_lexeme<> const& name) {
            type res;
            res.name = std::string{name.begin(), name.end()};
            return res;
        });
};

struct axis_pos {
    using type   = sem::Tblfm::Expr::AxisRef::Position;
    sc auto rule = (dsl::peek(dsl::ascii::digit / dsl::lit_c<'-'>)
                    >> dsl::p<axis_spec>)
                 | (dsl::peek(dsl::ascii::alpha) >> dsl::p<axis_name>);
    sc auto value = lexy::callback<type>(
        [](axis_spec::type const& t) {
            type res;
            res.data = t;
            return res;
        },
        [](axis_name::type const& t) {
            type res;
            res.data = t;
            return res;
        });
};

struct axis_ref {
    sc_char name = "axis_ref";
    using type   = sem::Tblfm::Expr::AxisRef;
    sc auto rule //
        = dsl::opt(dsl::lit_c<'$'> >> dsl::p<axis_pos>)
        + dsl::opt(dsl::lit_c<'@'> >> dsl::p<axis_pos>);

    sc auto value = lexy::callback<type>(
        [](std::optional<axis_pos::type> col,
           std::optional<axis_pos::type> row) {
            type ref;
            return ref;
        });
};

struct axis_range {
    sc_char name  = "axis_range";
    using type    = sem::Tblfm::Expr::RangeRef;
    sc auto rule  = dsl::p<axis_ref> + LEXY_LIT("..") + dsl::p<axis_ref>;
    sc auto value = lexy::callback<type>(
        [](axis_ref::type const& first, axis_ref::type const& last) {
            type res;
            res.first = first;
            res.last  = last;
            return res;
        });
};

struct expr;

std::unordered_map<std::string, int> operator_precedence = {
    {"+", 1},
    {"-", 1},
    {"*", 2},
    {"/", 2}};

sem::Tblfm::Expr fold_expression_stack(
    std::vector<sem::Tblfm::Expr> const& exprs) {
    std::stack<sem::Tblfm::Expr> output;
    std::stack<std::string>      operators;

    auto precedence = [](const std::string& op) {
        return operator_precedence.contains(op) ? operator_precedence[op]
                                                : -1;
    };

    auto apply_operator = [&]() {
        sem::Tblfm::Expr::Call call;
        call.name = operators.top();
        operators.pop();
        for (int i = 0; i < 2 && !output.empty(); ++i) {
            call.args.push_back(std::move(output.top()));
            output.pop();
        }
        std::reverse(call.args.begin(), call.args.end());
        output.push(
            sem::Tblfm::Expr{sem::Tblfm::Expr::Call{std::move(call)}});
    };

    for (auto const& expr : exprs) {
        if (expr.isCall()) {
            auto const& call = expr.getCall();
            if (operator_precedence.contains(call.name)) {
                while (!operators.empty()
                       && precedence(operators.top())
                              >= precedence(call.name)) {
                    apply_operator();
                }
                operators.push(call.name);
            } else {
                output.push(
                    sem::Tblfm::Expr{sem::Tblfm::Expr::Call{call}});
            }
        } else {
            output.push(expr);
        }
    }

    while (!operators.empty()) { apply_operator(); }

    return output.top();
}


struct call_args {
    sc_char name  = "call_args";
    using type    = std::vector<sem::Tblfm::Expr>;
    sc auto rule  = dsl::list(dsl::recurse<expr>, dsl::sep(dsl::comma));
    sc auto value = lexy::as_list<type>;
};


struct call {
    sc_char name = "call";
    using type   = sem::Tblfm::Expr::Call;
    sc auto rule                             //
        = dsl::identifier(dsl::ascii::alpha) //
        + dsl::lit_c<'('>                    //
        + dsl::p<call_args>                  //
        + dsl::lit_c<')'>;

    sc auto value = lexy::bind(
        lexy::callback<type>([](lexy::string_lexeme<> const& name,
                                call_args::type const&       args) {
            type result;
            result.name = Str{std::string{name.begin(), name.end()}};
            result.args = Vec<sem::Tblfm::Expr>{args.begin(), args.end()};
            return result;
        }),
        lexy::_1,
        lexy::_2);
};

struct expr {
    sc_char name = "expr";
    using type   = sem::Tblfm::Expr;
    sc auto rule //
        = (dsl::peek(dsl::ascii::alpha) >> dsl::p<call>)
        | (dsl::capture(dsl::token(LEXY_LITERAL_SET(
            LEXY_LIT("*"),
            LEXY_LIT("+"),
            LEXY_LIT("+"),
            LEXY_LIT("/"),
            LEXY_LIT("-")))))
        | (dsl::peek(dsl::p<axis_ref> + LEXY_LIT(".."))
           >> dsl::p<axis_range>)
        | (dsl::peek(dsl::lit_c<'$'> | dsl::lit_c<'@'>)
           >> dsl::p<axis_ref>)
        | (dsl::integer<int>);

    sc auto value = lexy::callback<type>(overloaded{
        [](call::type const& c) {
            type res;
            res.data = c;
            return res;
        },
        [](lexy::string_lexeme<> const& op) {
            type                   res;
            sem::Tblfm::Expr::Call c{};
            c.name   = Str{std::string{op.begin(), op.end()}};
            res.data = c;
            return res;
        },
        [](int const& op) {
            type                         res;
            sem::Tblfm::Expr::IntLiteral c{};
            c.value  = op;
            res.data = c;
            return res;
        },
        [](axis_ref::type const& c) {
            type res;
            res.data = c;
            return res;
        },
        [](axis_range::type const& c) {
            type res;
            res.data = c;
            return res;
        },
    });
};

struct expr_list {
    sc_char name  = "expr_list";
    using type    = std::vector<sem::Tblfm::Expr>;
    sc auto rule  = dsl::list(dsl::p<expr>);
    sc auto value = lexy::as_list<type>;
};

struct assign_flag {
    sc_char name = "assign_flag";
    using type   = sem::Tblfm::Assign::Flag;
    sc auto rule //
        = dsl::lit_c<';'>
        + dsl::capture(dsl::token(
            (dsl::peek(dsl::lit_c<'%'>)
             >> (dsl::lit_c<'%'>                  //
                 + dsl::while_(dsl::ascii::digit) //
                 + dsl::lit_c<'.'>                //
                 + dsl::while_(dsl::ascii::digit) //
                 + dsl::lit_c<'f'>))));

    sc auto value = lexy::callback<type>(
        [](lexy::string_lexeme<> const& op) {
            type res = type::CellBool;

            return res;
        });
};

struct assign {
    sc_char name = "assign";
    using type   = sem::Tblfm::Assign;
    sc auto rule           //
        = dsl::p<axis_ref> //
        + dsl::lit_c<'='>  //
        + dsl::p<expr_list>
        + dsl::opt(dsl::peek(dsl::lit_c<';'>) >> dsl::p<assign_flag>);

    static type impl(
        axis_ref::type const&         axis,
        expr_list::type const&        expr,
        Opt<assign_flag::type> const& flag) {

        sem::Tblfm::Expr fold = fold_expression_stack(expr);

        type res;

        return res;
    }

    sc auto value = lexy::callback<type>(overloaded{
        [](axis_ref::type const&  axis,
           expr_list::type const& expr,
           lexy::nullopt const&) {
            return impl(axis, expr, std::nullopt);
        },
        [](axis_ref::type const&    axis,
           expr_list::type const&   expr,
           assign_flag::type const& flag) {
            return impl(axis, expr, flag);
        },
    });
};

struct tblfmt {
    sc_char name  = "tblfmt";
    sc auto rule  = dsl::list(dsl::p<assign>, dsl::sep(LEXY_LIT("::")));
    sc auto value = lexy::as_list<std::vector<sem::Tblfm::Assign>>;
};

}; // namespace tblfmt_grammar

struct CollectErrors {
    struct _sink {
        using return_type = std::vector<std::string>;

        template <typename Input, typename Reader, typename Tag>
        void operator()(
            const lexy::error_context<Input>& context,
            const lexy::error<Reader, Tag>&   error) {
            std::string out;
            lexy_ext::_detail::write_error(
                std::back_inserter(out), context, error, {}, nullptr);
            errors.push_back(out);
        }

        std::vector<std::string> finish() && { return errors; }

        std::vector<std::string> errors;
    };

    constexpr auto sink() const { return _sink{}; }
};

template <typename Rule>
auto run_lexy_parse(Str const& expr, OrgConverter* conv) {
    conv->print(expr);

    if (conv->TraceState) {
        std::string        str;
        lexy::string_input input{expr.data(), expr.data() + expr.size()};

        lexy::visualization_options opts{};
        opts.flags = lexy::visualize_use_unicode
                   | lexy::visualize_use_symbols | lexy::visualize_space;
        lexy::trace_to<Rule>(
            std::back_insert_iterator(str),
            lexy::zstring_input(input.data()),
            opts);

        conv->print(str);
    }

    return lexy::parse<Rule>(
        lexy::string_input{expr.data(), expr.data() + expr.size()},
        CollectErrors{});
}

OrgConverter::ConvResult<CmdTblfm> OrgConverter::convertCmdTblfm(__args) {
    __perf_trace("convert", "convertCmdTblfm");
    auto __trace = trace(a);
    auto res     = Sem<CmdTblfm>(a);


    Str expr = get_text(one(a, N::Values));

    auto result = run_lexy_parse<tblfmt_grammar::tblfmt>(expr, this);

    if (result.has_value()) {
        auto v          = result.value();
        res->expr.exprs = Vec<sem::Tblfm::Assign>{v.begin(), v.end()};
        return res;
    } else {
        return SemError(
            a,
            fmt("Table format expression failed\n{}",
                join("\n", result.errors())));
    }
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
    for (auto const& sub : a) {
        if (sub.getKind() != OrgNodeKind::Space) {
            result->words.push_back(get_text(sub));
        }
    }
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
    auto                __trace = trace(a);
    SemId<BlockExample> result  = Sem<BlockExample>(a);
    for (auto const& it : many(a, N::Body)) {
        result->subnodes.push_back(convert(it));
    }

    return result;
}

OrgConverter::ConvResult<BlockDynamicFallback> OrgConverter::
    convertBlockDynamicFallback(__args) {
    auto                        __trace = trace(a);
    SemId<BlockDynamicFallback> result  = Sem<BlockDynamicFallback>(a);
    result->attrs                       = convertAttrs(one(a, N::Args));

    result->name = normalize(get_text(one(a, N::Name)));
    hstd::replace_all(result->name, "begin", "");
    for (auto const& it : many(a, N::Body)) {
        result->subnodes.push_back(convert(it));
    }

    return result;
}

OrgConverter::ConvResult<CriticMarkup> OrgConverter::convertCriticMarkup(
    __args) {
    auto                __trace = trace(a);
    SemId<CriticMarkup> result  = Sem<CriticMarkup>(a);
    auto                head    = get_text(one(a, N::Name));
    auto                assoc   = one(a, N::Assoc);
    auto                body    = one(a, N::Body);

    using K = CriticMarkup::Kind;

    if (head.ends_with("--")) {
        result->kind = K::Deletion;
    } else if (head.ends_with("++")) {
        result->kind = K::Addition;
    } else if (head.ends_with("==")) {
        result->kind = K::Highlighting;
    } else if (head.ends_with(">>")) {
        result->kind = K::Comment;
    } else if (head.ends_with("~~")) {
        result->kind = K::Substitution;
    }

    if (assoc.getKind() != onk::Empty) {
        result->push_back(convert(assoc));
    }

    result->push_back(convert(body));

    return result;
}


OrgConverter::ConvResult<ColonExample> OrgConverter::convertColonExample(
    __args) {
    auto                __trace = trace(a);
    SemId<ColonExample> result  = Sem<ColonExample>(a);
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
    auto __trace = trace(a);
    auto eexport = Sem<BlockExport>(a);

    auto values       = convertAttrs(one(a, N::Args));
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
    auto               __trace = trace(a);
    SemId<BlockCenter> res     = Sem<BlockCenter>(a);
    for (const auto& sub : many(a, N::Body)) {
        auto aux = convert(sub);
        res->push_back(aux);
    }
    return res;
}

OrgConverter::ConvResult<BlockQuote> OrgConverter::convertBlockQuote(
    __args) {
    auto              __trace = trace(a);
    SemId<BlockQuote> quote   = Sem<BlockQuote>(a);

    if (auto args = one(a, N::Args); args.kind() != onk::Empty) {
        quote->attrs = convertAttrs(args);
    }

    for (const auto& sub : flatConvertAttached(many(a, N::Body))) {
        quote->push_back(sub.unwrap());
    }
    return quote;
}

OrgConverter::ConvResult<BlockComment> OrgConverter::convertBlockComment(
    __args) {
    auto                __trace = trace(a);
    SemId<BlockComment> result  = Sem<BlockComment>(a);
    for (const auto& sub : flatConvertAttached(many(a, N::Body))) {
        result->push_back(sub.unwrap());
    }
    return result;
}

OrgConverter::ConvResult<Latex> OrgConverter::convertMath(__args) {
    auto __trace = trace(a);
    if (a.kind() == onk::InlineMath) {
        return Sem<Latex>(a);
    } else {
        throw convert_logic_error::init(
            "Unhanled kind for inline math TODO");
    }
}

OrgConverter::ConvResult<CmdInclude> OrgConverter::convertCmdInclude(
    __args) {
    auto              __trace = trace(a);
    SemId<CmdInclude> include = Sem<CmdInclude>(a);
    auto              args    = convertAttrs(one(a, N::Args));
    include->path             = args.positional.items.at(0).getString();

    if (TraceState) { print(fmt("args: {}", args)); }

    if (auto kind = args.positional.items.get(1)) {
        Str ks = kind.value().get().getString();
        if (ks == "src"_ss) {
            auto src      = sem::CmdInclude::Src{};
            include->data = src;
            // Add empty source code block, converter logic does not have
            // access to the files, so the actual content of the block will
            // be filled in `sem::parseDirectoryOpts` or by the other
            // processing pass.
            auto content = Sem<BlockCode>(a);
            include->push_back(content);

        } else if (ks == "example"_ss) {
            auto ex       = sem::CmdInclude::Example{};
            include->data = ex;
            auto content  = Sem<BlockExample>(a);
            include->push_back(content);

        } else if (ks == "export"_ss) {
            auto ex       = sem::CmdInclude::Export{};
            include->data = ex;
            auto content  = Sem<BlockExport>(a);
            include->push_back(content);
        } else {
            auto ex       = sem::CmdInclude::Custom{};
            ex.blockName  = ks;
            include->data = ex;
        }

    } else {
        sem::CmdInclude::OrgDocument doc{};
        if (include->path.contains("::")) {
            auto split    = include->path.split("::");
            include->path = split.at(0);
            auto second   = strip_space(split.at(1));
            if (second.starts_with("*")) {
                doc.subtreePath = convertSubtreePath(second);
            } else if (second.starts_with("#")) {
                doc.customIdTarget = strip(
                    second, CharSet{'#', ' '}, CharSet{' '});
            }
        }
        include->data = doc;
    }

    if (auto minlevel = args.named.pop_opt("minlevel")) {
        include->getOrgDocument().minLevel //
            = minlevel->items.at(0).getInt();
    }

    if (auto only = args.named.pop_opt("onlycontents")) {
        include->getOrgDocument().onlyContent = only->items.at(0)
                                                    .getBool();
    }
    if (auto arg = args.named.pop_opt("lines")) {
        Str lines = strip(
            arg->items.at(0).getString(), CharSet{'"'}, CharSet{'"'});
        Vec<Str> split = lines.split("-");
        if (lines.starts_with("-")) {
            include->lastLine = split.at(1).toInt();
        } else if (lines.ends_with("-")) {
            include->firstLine = split.at(0).toInt();
        } else {
            include->firstLine = split.at(0).toInt();
            include->lastLine  = split.at(1).toInt();
        }
    }


    return include;
}

OrgConverter::ConvResult<TextSeparator> OrgConverter::convertTextSeparator(
    __args) {
    auto __trace = trace(a);
    return Sem<TextSeparator>(a);
}

OrgConverter::ConvResult<AtMention> OrgConverter::convertAtMention(
    __args) {
    auto __trace = trace(a);
    return SemLeaf<AtMention>(a);
}

sem::AttrValue OrgConverter::convertAttr(__args) {
    auto           __trace = trace(a);
    sem::AttrValue result;

    if (one(a, N::Name).getKind() != onk::Empty) {
        result.name = lstrip(get_text(one(a, N::Name)), CharSet{':'});
        print(fmt("Result name '{}'", result.name.value()));
    }

    if (one(a, N::Subname).getKind() != onk::Empty) {
        result.varname = get_text(one(a, N::Subname));
        print(fmt("Result varname '{}'", result.varname.value()));
    }

    if (one(a, N::Value).getKind() == onk::RawText) {
        Str value = get_text(one(a, N::Value));
        print(fmt("Text value is '{}'", value));

        if (value.starts_with('"') && value.ends_with('"')) {
            result.isQuoted = true;
            value           = value.substr(1, value.size() - 2);
        }

        auto split = value.split(':');
        if (!result.isQuoted && split.size() == 2
            && !value.contains("::")) {
            AttrValue::FileReference fr{};
            fr.file      = split.at(0);
            fr.reference = split.at(1);
            print(fmt("Attribute is file reference {}", fr));
            result.data = fr;
        } else {
            AttrValue::TextValue tv{};
            tv.value = value;
            print(fmt("Attribute is text value {}", tv));

            result.data = tv;
        }
    } else if (one(a, N::Value).getKind() == onk::AttrLisp) {
        AttrValue::LispValue ev{};
        ev.code = convertLisp(one(a, N::Value));
        print("Attribute is lisp value");
        result.data = ev;
    } else {
        AttrValue::TextValue tv{};
        tv.value += get_text(one(a, N::Value));
        print(fmt("Attribute is text value {}", tv));
        result.data = tv;
    }

    if (one(a, N::Cells).getKind() != onk::Empty) {
        for (auto const& it : one(a, N::Cells)) {
            AttrValue::DimensionSpan dim;
            auto                     axis = get_text(it);
            if (axis == "" || axis == "*") {
                dim.first = 0;
                dim.last  = -1;
            } else {
                auto split = axis.split(':');
                dim.first  = split.at(0).toInt();
                if (split.has(1)) { dim.last = split.at(1).toInt(); }
            }
            print(fmt("Attribute dimension span {}", dim));
            result.span.push_back(dim);
        }
    }

    return result;
}

sem::AttrGroup OrgConverter::convertAttrs(__args) {
    auto           __trace = trace(a);
    sem::AttrGroup result;

    Opt<sem::AttrValue> last_named;

    auto push_argument = [&](sem::AttrValue const& it) {
        if (it.name) {
            addArgument(result, it);
            last_named = it;
        } else {
            if (last_named) {
                auto tmp = it;
                tmp.name = last_named->name;
                addArgument(result, tmp);
            } else {
                addArgument(result, it);
            }
        }
    };

    if (a.getKind() == onk::Attrs) {
        for (auto const& item : one(a, N::Values)) {
            push_argument(convertAttr(item));
        }
    } else if (a.getKind() == onk::InlineStmtList) {
        for (auto const& it : a) {
            push_argument(convertAttr(it)); //
        }
    } else {
        CHECK(a.getKind() == onk::Empty) << a.treeRepr();
    }

    return result;
}

LispCode OrgConverter::convertLisp(In a) {
    auto __trace = trace(a);
    using L      = sem::LispCode;
    L out;
    if (a.getKind() == onk::AttrLisp) {
        return convertLisp(one(a, N::Value));
    } else if (a.getKind() == onk::InlineStmtList) {
        Vec<LispCode> items;
        for (auto const& it : a) { items.push_back(convertLisp(it)); }
        if (!items.empty() && items.front().isIdent()) {
            L::Call res;
            res.name = items.front().getIdent().name;
            if (items.has(1)) {
                res.args = Vec<LispCode>{items.at(slice(1, 1_B))};
            }
            out.data = res;
        } else {
            L::List res;
            res.items = items;
            out.data  = res;
        }
    } else {
        Str v = get_text(a);
        if (v.starts_with('"') && v.ends_with('"')) {
            L::Text res;
            res.value = v.substr(1, v.size() - 2);
            out.data  = res;
        } else if (no_exception([&]() { v.toInt(); })) {
            L::Number res;
            res.value = v.toInt();
            out.data  = res;
        } else if (no_exception([&]() { v.toFloat(); })) {
            L::Real res;
            res.value = v.toFloat();
            out.data  = res;
        } else if (v == "t") {
            L::Boolean res;
            res.value = true;
            out.data  = res;
        } else if (v == "nil") {
            L::Boolean res;
            res.value = false;
            out.data  = res;
        } else {
            L::Ident res;
            res.name = v;
            out.data = res;
        }
    }

    return out;
}

OrgConverter::ConvResult<CmdAttr> OrgConverter::convertCmdAttr(__args) {
    auto           __trace = trace(a);
    SemId<CmdAttr> result  = Sem<CmdAttr>(a);
    result->target         = normalize(get_text(one(a, N::Name)));
    result->attrs          = convertAttrs(one(a, N::Args));

    return result;
}

namespace columns_grammar {

struct aggregate {
    using type   = sem::ColumnView::Summary;
    sc auto rule = dsl::curly_bracketed(
        dsl::identifier(dsl::ascii::character - dsl::lit_c<'}'>));
    sc auto value = lexy::callback<type>([](lexy_tok const& tok) {
        type res;
        Str  agg = lexy_str(tok);
        if (agg == ":min" || agg == "min" || agg == "@min") {
            res.data = type::MathAggregate{
                .kind = type::MathAggregate::Kind::Min};
        } else if (agg == ":max" || agg == "max" || agg == "@max") {
            res.data = type::MathAggregate{
                .kind = type::MathAggregate::Kind::Max};
        } else if (agg == "est+") {
            res.data = type::MathAggregate{
                .kind = type::MathAggregate::Kind::LowHighEst};
        } else if (agg == "x" || agg == "X") {
            res.data = type::CheckboxAggregate{
                .kind = type::CheckboxAggregate::Kind::IfAllNested};
        } else if (agg == "x/" || agg == "X/") {
            res.data = type::CheckboxAggregate{
                .kind = type::CheckboxAggregate::Kind::
                    AggregateFractionRec};
        } else if (agg == "x%" || agg == "X%") {
            res.data = type::CheckboxAggregate{
                .kind = type::CheckboxAggregate::Kind::
                    AggregatePercentRec};
        }

        return res;
    });
};

struct field {
    using type   = Pair<Str, Opt<Str>>;
    sc_char name = "field";
    sc auto rule                                              //
        = dsl::identifier(dsl::ascii::alpha_digit_underscore) //
        + dsl::opt(
              dsl::peek(dsl::lit_c<'('>)
              >> dsl::round_bracketed(dsl::identifier(
                  dsl::ascii::character - dsl::lit_c<')'>))) //
        ;

    sc auto value = lexy::bind(
        lexy::callback<type>(
            [](lexy_tok const& prop, Opt<lexy_tok> const& title) {
                type res;
                res.first = lexy_str(prop);
                if (title) { res.second = lexy_str(title.value()); }
                return res;
            }),
        lexy::_1,
        lexy::_2 or Opt<lexy_tok>{});
};

struct column {
    sc_char name = "column";
    using type   = sem::ColumnView::Column;
    sc auto rule                                                      //
        = dsl::lit_c<'%'>                                             //
        + dsl::opt(dsl::peek(dsl::ascii::digit) >> dsl::integer<int>) //
        + dsl::opt(dsl::peek(dsl::ascii::alpha) >> dsl::p<field>)     //
        + dsl::opt(dsl::peek(dsl::lit_c<'{'>) >> dsl::p<aggregate>)   //
        ;

    sc auto value = //
        lexy::bind(
            lexy::callback<type>([](Opt<int> const&             width,
                                    Opt<field::type> const&     fld,
                                    Opt<aggregate::type> const& agg) {
                type res;
                res.width = width;
                if (fld) {
                    res.property      = fld.value().first;
                    res.propertyTitle = fld.value().second;
                }
                res.summary = agg;
                return res;
            }),
            lexy::_1 or Opt<int>{},
            lexy::_2 or Opt<field::type>{},
            lexy::_3 or Opt<aggregate::type>{});
};

struct columns {
    sc_char name  = "columns";
    sc auto rule  = dsl::list(dsl::p<column>, dsl::sep(dsl::ascii::space));
    sc auto value = lexy::as_list<std::vector<column::type>>;
};
} // namespace columns_grammar

OrgConverter::ConvResult<CmdColumns> OrgConverter::convertCmdColumns(
    __args) {
    auto              __trace = trace(a);
    SemId<CmdColumns> result  = Sem<CmdColumns>(a);

    Str expr = get_text(one(a, N::Args));

    auto spec = run_lexy_parse<columns_grammar::columns>(expr, this);

    if (spec.has_value()) {
        auto v               = spec.value();
        result->view.columns = Vec<sem::ColumnView::Column>{
            v.begin(), v.end()};
        return result;
    } else {
        return SemError(
            a,
            fmt("Column format expression failed\n{}",
                join("\n", spec.errors())));
    }

    return result;
}

OrgConverter::ConvResult<CmdName> OrgConverter::convertCmdName(__args) {
    auto           __trace = trace(a);
    SemId<CmdName> result  = Sem<CmdName>(a);
    result->name           = convertAttr(a.at(0).at(0)).getString();
    return result;
}

OrgConverter::ConvResult<InlineExport> OrgConverter::convertInlineExport(
    __args) {
    auto                __trace = trace(a);
    SemId<InlineExport> result  = Sem<InlineExport>(a);
    result->exporter = lstrip(get_text(one(a, N::Name)), CharSet{'@'});
    result->content  = Str{get_text(one(a, N::Body)).at(slice(1, 3_B))};
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
    auto             __trace = trace(a);
    SemId<BlockCode> result  = Sem<BlockCode>(a);

    {
        auto __field = field(N::Lang, a);
        if (one(a, N::Lang).getKind() != onk::Empty) {
            result->lang = get_text(one(a, N::Lang));
        }
    }

    {
        auto __field = field(N::HeaderArgs, a);
        if (one(a, N::HeaderArgs).kind() != onk::Empty) {
            result->attrs = convertAttrs(one(a, N::HeaderArgs));
        }
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
        auto __field = field(N::Body, a);
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
                    case onk::CodeTangle: {
                        line.parts.push_back(BlockCodeLine::Part{
                            BlockCodeLine::Part::Tangle{
                                // .target =
                            }});
                        break;
                    }
                    default: {
                        throw convert_logic_error::init(fmt1(part.kind()));
                    }
                }
            }
        }
    }

    {
        auto __field = field(N::Result, a);
        if (auto res = one(a, N::Result); res.kind() != onk::Empty) {
            auto body = one(res, N::Body);
            auto conv = convert(body);
            print(fmt("Parsed result body as {}", conv->getKind()));
            auto result_block  = Sem<sem::BlockCodeEvalResult>(res);
            result_block->node = conv;
            result->result.push_back(result_block);
        }
    }

    return result;
}

OrgConverter::ConvResult<CmdCall> OrgConverter::convertCmdCall(__args) {
    __perf_trace("convert", "convertCall");
    auto __trace = trace(a);
    if (a.kind() == onk::CmdCallCode) {
        auto call               = Sem<CmdCall>(a);
        call->name              = get_text(one(a, N::Name));
        call->insideHeaderAttrs = convertAttrs(one(a, N::HeaderArgs));
        call->callAttrs         = convertAttrs(one(a, N::Args));
        call->endHeaderAttrs    = convertAttrs(one(a, N::EndArgs));
        return call;
    } else {
        return SemError(a, "TODO Convert inline call");
    }
}


Vec<OrgConverter::ConvResult<Org>> OrgConverter::flatConvertAttached(
    Vec<org::parse::OrgAdapter> items) {
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

                Opt<CRw<org::parse::OrgAdapter>> next_opt = items.get(
                    i + offset + 1);
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
    Vec<org::parse::OrgAdapter> items;
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
        case onk::InlineExport: return convertInlineExport(a).unwrap();
        case onk::StaticActiveTime:
        case onk::StaticInactiveTime:
        case onk::DynamicActiveTime:
        case onk::DynamicInactiveTime: return convertTime(a).unwrap();
        case onk::Quote: return convertMarkQuote(a).unwrap();
        case onk::BlockComment: return convertBlockComment(a).unwrap();
        case onk::BlockQuote: return convertBlockQuote(a).unwrap();
        case onk::Colon: return convertPunctuation(a).unwrap();
        case onk::CmdInclude: return convertCmdInclude(a).unwrap();
        case onk::Symbol: return convertSymbol(a).unwrap();
        case onk::Angle: return convertPlaceholder(a).unwrap();
        case onk::Empty: return Sem<Empty>(a);
        case onk::Table: return convertTable(a).unwrap();
        case onk::Footnote: return convertLink(a).unwrap();
        case onk::CmdTblfm: return convertCmdTblfm(a).unwrap();
        case onk::CmdAttr: return convertCmdAttr(a).unwrap();
        case onk::CmdColumns: return convertCmdColumns(a).unwrap();
        case onk::ColonExample: return convertColonExample(a).unwrap();
        case onk::CmdCaption: return convertCmdCaption(a).unwrap();
        case onk::CmdName: return convertCmdName(a).unwrap();
        case onk::CmdCallCode: return convertCmdCall(a).unwrap();
        case onk::Paragraph: return convertParagraph(a).unwrap();
        case onk::CriticMarkStructure:
            return convertCriticMarkup(a).unwrap();
        case onk::BlockDynamicFallback:
            return convertBlockDynamicFallback(a).unwrap();
        case onk::ErrorWrap: {
            auto group = Sem<ErrorGroup>(a);
            for (auto const& sub : a) {
                if (sub.isMono() && sub.getMono().isError()) {
                    auto mono = sub.getMono().getError();
                    LOGIC_ASSERTION_CHECK(
                        mono.box,
                        "Mono error for node should have box data");
                    group->diagnostics.push_back(SemErrorItem(
                        sub,
                        fmt("{} at {}:{} {}",
                            mono.box->error,
                            mono.box->failToken->line,
                            mono.box->failToken->col,
                            escape_literal(mono.box->failToken->text)),
                        mono.box->parserLine,
                        mono.box->parserFunction.c_str()));
                } else {
                    group->push_back(convert(sub));
                }
            }
            return group;
        }
        default: {
            return SemError(a, fmt("ERR Unknown content {}", a.getKind()));
        }
    }
#undef CASE
}

void OrgConverter::convertDocumentOptions(
    SemId<DocumentOptions> opts,
    org::parse::OrgAdapter a) {
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


using Prop = NamedProperty;


bool OrgConverter::updateDocument(
    SemId<Document>&         doc,
    const parse::OrgAdapter& sub) {
    switch (sub.kind()) {
        case onk::CmdColumns: {
            if (auto columns = convertCmdColumns(sub)) {
                auto cols             = columns.value();
                doc->options->columns = cols->view;
            } else {
                doc->push_back(columns.error());
            }
            return true;
        }
        case onk::CmdTitle: {
            if (auto title = convertParagraph(sub[0])) {
                doc->title = title.value();
            } else {
                doc->push_back(title.error());
            }
            return true;
        }
        case onk::CmdOptions: {
            convertDocumentOptions(doc->options, sub);
            return true;
        }

        case onk::CmdPropertyArgs: {
            Prop::CustomArgs prop;
            prop.name  = get_text(one(sub, N::Name));
            prop.attrs = convertAttrs(one(sub, N::Args));
            doc->options->properties.push_back(Prop(prop));
            return true;
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
                doc->options->initialVisibility = K::ShowEverything;
            } else {
                throw convert_logic_error::init(text);
            }

            if (auto it = args.get(1); it.has_value()) {
                if (org_streq(*it, "indent")) {
                    doc->options->startupIndented = true;
                }
            }

            return true;
        }

        case onk::CmdLatexClass: {
            Prop::ExportLatexClass res{};
            res.latexClass = get_text(sub.at(0));
            doc->options->properties.push_back(Prop(res));
            return true;
        }
        case onk::CmdLatexHeader: {
            Prop::ExportLatexHeader res{};
            res.header = get_text(sub.at(0));
            doc->options->properties.push_back(Prop(res));
            return true;
        }
        case onk::CmdLatexCompiler: {
            Prop::ExportLatexCompiler res{};
            res.compiler = get_text(sub.at(0));
            doc->options->properties.push_back(Prop(res));
            return true;
        }
        case onk::CmdLatexClassOptions: {
            auto                          value = get_text(sub.at(0));
            Prop::ExportLatexClassOptions res;
            res.options.push_back(value);
            doc->options->properties.push_back(Prop(res));
            return true;
        }
        case onk::CmdKeywords: {
            return true;
        }
        case onk::CmdFiletags: {
            for (auto const& hash : many(sub, N::Tags)) {
                doc->filetags.push_back(convertHashTag(hash).value());
            }
            return true;
        }

        default: {
            return false;
        }
    }
}

OrgConverter::ConvResult<Document> OrgConverter::convertDocumentFragments(
    const hstd::Vec<InFragment>& fragments) {
    auto __trace        = trace(std::nullopt, "document-fragment-list");
    SemId<Document> doc = Sem<Document>(fragments.front().node);
    doc->options        = Sem<DocumentOptions>(fragments.front().node);
    for (auto const frag : fragments) {
        auto __trace = trace(std::nullopt, "document-fragment");
        Vec<parse::OrgAdapter> buffer;
        for (const auto& sub : frag.node) {
            auto __trace = trace(sub, fmt1(sub.getKind()));
            if (!updateDocument(doc, sub)) { buffer.push_back(sub); }
        }

        SemId<DocumentFragment> outFragment = Sem<DocumentFragment>(
            frag.node);
        outFragment->baseLine = frag.baseLine;
        outFragment->baseCol  = frag.baseCol;

        for (auto const& it : flatConvertAttached(buffer)) {
            outFragment->subnodes.push_back(it.unwrap());
        }

        doc->subnodes.push_back(outFragment);
    }

    return doc;
}

org::sem::OrgConverter::ConvResult<Document> OrgConverter::convertDocument(
    __args) {
    auto __trace = trace(a);

    SemId<Document> doc = Sem<Document>(a);
    doc->options        = Sem<DocumentOptions>(a);

    Vec<parse::OrgAdapter> buffer;
    for (const auto& sub : a) {
        auto __trace = trace(sub, fmt1(sub.getKind()));
        if (!updateDocument(doc, sub)) { buffer.push_back(sub); }
    }

    for (auto const& it : flatConvertAttached(buffer)) {
        doc->subnodes.push_back(it.unwrap());
    }

    return doc;
}
