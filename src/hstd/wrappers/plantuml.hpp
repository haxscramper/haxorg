#ifndef PLANTUML_HPP
#define PLANTUML_HPP

#include <QDate>
#include <string>
#include <hstd/stdlib/Opt.hpp>
#include <hstd/system/reflection.hpp>
#include <hstd/stdlib/Vec.hpp>
#include <hstd/stdlib/Json.hpp>
#include <hstd/stdlib/Time.hpp>


namespace puml {

#define _property(name, field, type) Opt<type> field;

#define _e_property(Name, field, ...)                                     \
    DECL_DESCRIBED_ENUM(Name, __VA_ARGS__);                               \
    Opt<Name> field;


struct Gantt {
    _property(Title, title, std::string);
    _property(DateFormat, dateFormat, std::string);
    _property(Today, today, QDate);
    _e_property(PrintScale, printscale, daily, weekly, monthly, yearly);
    _e_property(Scale, scale, auto_, fixed, compact);
    _property(ProjectStart, projectstart, QDate);
    _property(ProjectEnd, projectend, QDate);
    _property(Legend, legend, std::string);
    _property(BarStyle, barstyle, std::string);
    _property(TaskBarStyle, taskbarstyle, std::string);
    _property(Calendar, calendar, std::string);
    _property(WorkingDays, workingdays, std::string);
    _property(WeekEnds, weekEnds, std::string);
    _property(Holidays, holidays, UserTime);

    struct CloseDay {
        struct Weekday {};
        struct Range {
            UserTime start;
            UserTime end;
        };

        SUB_VARIANTS(Kind, Data, data, getKind, Weekday, Range);
        Data data;
    };

    struct Event {
        UserTime   start;
        UserTime   stop;
        std::string    name;
        Opt<int>   completion;
        Vec<Event> nested;

        bool hasHours   = true;
        bool hasMinutes = true;
        bool hasSeconds = true;

        Slice<QDateTime> convex() const;
        Slice<QDateTime> minmax() const;

        std::string toString() const;

        json toJson() const;
    };

    Opt<Slice<QDateTime>> timeSpan;

    Vec<Event> events;

    std::string toString() const;
    json    toJson() const;
};

}; // namespace puml

#endif // PLANTUML_HPP
