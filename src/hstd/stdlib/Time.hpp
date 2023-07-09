#pragma once

#include <QDateTime>
#include <hstd/stdlib/Variant.hpp>
#include <hstd/system/aux_utils.hpp>


struct UserTime {
    DECL_DESCRIBED_ENUM(Kind, DateTime, Date, Time);

    Kind getKind() const {
        if (swl::holds_alternative<QDateTime>(time)) {
            return Kind::DateTime;
        } else if (swl::holds_alternative<QTime>(time)) {
            return Kind::Time;
        } else {
            return Kind::Date;
        }
    }

    using UserTimeData = Variant<QDateTime, QDate, QTime>;
    UserTimeData time;
    UserTime() {}
    UserTime(UserTimeData const& data) : time(data) {}
    UserTime(QDateTime const& dt, bool useDate, bool useTime) {
        if (useDate && useTime) {
            time = dt;
        } else if (useDate) {
            time = dt.date();
        } else if (useTime) {
            time = dt.time();
        }
    }

    bool hasDate() const {
        return swl::holds_alternative<QDate>(time)
            || swl::holds_alternative<QDateTime>(time);
    }

    bool hasTime() const {
        return swl::holds_alternative<QTime>(time)
            || swl::holds_alternative<QDateTime>(time);
    }

    QDateTime const& getDateTimeVar() const {
        return swl::get<QDateTime>(time);
    }

    QDate const& getDateVar() const { return swl::get<QDate>(time); }

    QTime const& getTimeVar() const { return swl::get<QTime>(time); }

    QDateTime min() const {
        if (hasDate() && hasTime()) {
            return getDateTimeVar();
        } else if (hasDate()) {
            return QDateTime(getDateVar(), QTime(0, 0, 0));
        } else {
            return QDateTime(QDate(), getTimeVar());
        }
    }


    QDateTime max() const {
        if (hasDate() && hasTime()) {
            return getDateTimeVar();
        } else if (hasDate()) {
            return QDateTime(getDateVar(), QTime(23, 59, 59));
        } else {
            return QDateTime(QDate(), getTimeVar());
        }
    }

    QTime getTime() const {
        if (hasDate() && hasTime()) {
            return getDateTimeVar().time();
        } else if (hasTime()) {
            return getTimeVar();
        } else {
            return QTime();
        }
    }

    QDate getDate() const {
        if (hasDate() && hasTime()) {
            return getDateTimeVar().date();
        } else if (hasDate()) {
            return getDateVar();
        } else {
            return QDate();
        }
    }

    QDateTime getDateTime() const {
        if (hasDate() && hasTime()) {
            return getDateTimeVar();
        } else {
            QDateTime result;
            if (hasDate()) {
                result.setDate(getDateVar());
            } else {
                result.setTime(getTimeVar());
            }

            return result;
        }
    }
};
