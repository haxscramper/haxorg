#ifndef PLANTUML_HPP
#define PLANTUML_HPP

#include <QDate>
#include <QString>
#include <hstd/stdlib/Opt.hpp>
#include <hstd/system/reflection.hpp>
#include <hstd/stdlib/Vec.hpp>


namespace puml {

#define _property(name, field, type) Opt<type> field;

#define _e_property(Name, field, ...)                                     \
    DECL_DESCRIBED_ENUM(Name, __VA_ARGS__);                               \
    Opt<Name> field;


struct Gantt {
    _property(Title, title, QString);
    _property(DateFormat, dateFormat, QString);
    _property(Today, today, QDate);
    _e_property(PrintScale, printscale, daily, weekly, monthly, yearly);
    _e_property(Scale, scale, auto_, fixed, compact);
    _property(ProjectStart, projectstart, QDate);
    _property(ProjectEnd, projectend, QDate);
    _property(Legend, legend, QString);
    _property(BarStyle, barstyle, QString);
    _property(TaskBarStyle, taskbarstyle, QString);
    _property(Calendar, calendar, QString);
    _property(WorkingDays, workingdays, QString);
    _property(WeekEnds, weekEnds, QString);
    _property(Holidays, holidays, QDate);

    struct CloseDay {
        struct Weekday {};
        struct Range {
            QDate start;
            QDate end;
        };

        SUB_VARIANTS(Kind, Data, data, getKind, Weekday, Range);
        Data data;
    };

    struct Event {
        QDate      start;
        QDate      stop;
        QString    name;
        Opt<int>   completion;
        Vec<Event> nested;

        QString toString() const;
    };

    Vec<Event> events;

    QString toString() const;
};

}; // namespace puml

#endif // PLANTUML_HPP
