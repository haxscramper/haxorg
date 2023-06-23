#include <hstd/wrappers/plantuml.hpp>
#include <hstd/stdlib/strformat.hpp>
#include <hstd/stdlib/Func.hpp>

QString puml::Gantt::toString() const {
    QString result;

    Slice<QDate> convex = timeSpan ? *timeSpan : events[0].convex();
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
    json res     = json::object();
    res["start"] = start.toString(Qt::ISODate);
    res["stop"]  = stop.toString(Qt::ISODate);
    res["name"]  = name;

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


Slice<QDate> puml::Gantt::Event::convex() const {
    Slice<QDate> convex = slice(start, stop);
    for (const auto& it : nested) {
        convex = convex.widen(it.convex());
    }

    return convex;
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
            int days = ctx.parent->start.daysTo(ctx.e.start);
            result += "[${name}] starts ${start} days ${direction} [${parent}]'s start and ends on ${end}\n"
                    % fold_format_pairs(
                          {{"name", ctx.e.name},
                           {"parent", ctx.parent->name},
                           {"direction", to_string(0 < days ? "after"  : "before")},
                           {"start", to_string(std::abs(days))},
                           {"end",  ctx.e.stop.toString(Qt::ISODate)}});

        } else {
            result += "[${name}] starts on ${start} and ends on ${end}\n"
                    % fold_format_pairs(
                          {{"name", ctx.e.name},
                           {"start", ctx.e.start.toString(Qt::ISODate)},
                           {"end", ctx.e.stop.toString(Qt::ISODate)}});
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
