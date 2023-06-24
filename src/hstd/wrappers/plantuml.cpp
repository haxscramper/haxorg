#include <hstd/wrappers/plantuml.hpp>
#include <hstd/stdlib/strformat.hpp>
#include <hstd/stdlib/Func.hpp>

QString puml::Gantt::toString() const {
    QString result;

    Slice<QDateTime> convex = timeSpan ? *timeSpan : events[0].convex();
    if (!timeSpan) {
        for (const auto& it : events) {
            convex = convex.widen(it.convex());
        }
    }

    result += "@startgantt\n";
    result += "Project starts on  " + convex.first.toString(Qt::ISODate)
            + "\n";

    for (const auto& it : events) {
        result += it.toString() + "\n";
    }

    result += "@endgantt\n";

    return result;
}


json puml::Gantt::Event::toJson() const {
    json res               = json::object();
    res["start"]           = start.getDateTime().toString(Qt::ISODate);
    res["stop"]            = stop.getDateTime().toString(Qt::ISODate);
    res["name"]            = name;
    res["start_date_only"] = !start.hasTime();
    res["stop_date_only"]  = !start.hasTime();

    if (completion) {
        res["completion"] = completion.value();
    } else {
        res["completion"] = json();
    }

    json nested = json::array();
    for (auto const& sub : this->nested) {
        nested.push_back(sub.toJson());
    }
    res["nested"] = nested;
    return res;
}


json puml::Gantt::toJson() const {
    json result      = json::object();
    result["events"] = json::array();

    for (auto const& ev : events) {
        result["events"].push_back(ev.toJson());
    }

    return result;
}


Slice<QDateTime> puml::Gantt::Event::convex() const {
    Slice<QDateTime> convex = minmax();
    for (const auto& it : nested) {
        convex = convex.widen(it.convex());
    }

    return convex;
}

Slice<QDateTime> puml::Gantt::Event::minmax() const {
    return slice(this->start.min(), this->stop.max());
}

QString puml::Gantt::Event::toString() const {
    QString result;
    struct PassCtx {
        CR<Event>  e;
        Opt<Event> parent;
    };

    Func<void(CR<PassCtx>)> aux;


    aux = [&result, &aux](CR<PassCtx> ctx) {
        if (ctx.parent) {
            int days = ctx.parent->start.getDate().daysTo(
                ctx.e.start.getDate());
            result += "[${name}] starts ${start} days ${direction} [${parent}]'s start and ends on ${end}\n"
                    % fold_format_pairs(
                          {{"name", ctx.e.name},
                           {"parent", ctx.parent->name},
                           {"direction", to_string(0 < days ? "after"  : "before")},
                           {"start", to_string(std::abs(days))},
                           {"end",  ctx.e.stop.getDate().toString(Qt::ISODate)}});

        } else {
            result += "[${name}] starts on ${start} and ends on ${end}\n"
                    % fold_format_pairs(
                          {{"name", ctx.e.name},
                           {"start",
                            ctx.e.start.getDate().toString(Qt::ISODate)},
                           {"end",
                            ctx.e.stop.getDate().toString(Qt::ISODate)}});
        }


        if (!ctx.e.nested.empty()) {
            for (const auto& it : ctx.e.nested) {
                aux({.e = it, .parent = ctx.e});
            }
        }
    };

    aux(PassCtx{.e = *this, .parent = std::nullopt});

    return result;
}
