#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include <QString>
#include <QTextStream>

#include <boost/mp11.hpp>
#include <boost/describe.hpp>

#include <locale>
#include <codecvt>

#ifdef __GNUG__
#    include <cstdlib>
#    include <memory>
#    include <cxxabi.h>

inline QString demangle(const char* name) {

    int status = -4; // some arbitrary value to eliminate the compiler
                     // warning

    // enable c++11 by passing the flag -std=c++11 to g++
    std::unique_ptr<char, void (*)(void*)> res{
        abi::__cxa_demangle(name, NULL, NULL, &status), std::free};

    return (status == 0) ? res.get() : name;
}

#else

// does nothing if not g++
inline QString demangle(const char* name) { return name; }

#endif


template <typename T>
concept StringStreamable = requires(T value, QTextStream& os) {
                               {
                                   os << value
                                   } -> std::same_as<QTextStream&>;
                           };

template <typename T>
QString to_string(T const& value)
    requires StringStreamable<T>
{
    QString     out;
    QTextStream os{&out};
    os << value;
    return out;
}

inline QString to_string(bool b) { return b ? "true" : "false"; }

template <typename T>
concept StringConvertible = requires(T value) {
                                {
                                    to_string(value)
                                    } -> std::same_as<QString>;
                            };

template <typename T>
concept IsEnum = std::is_enum<T>::value;

template <IsEnum T>
QTextStream& operator<<(QTextStream& os, T value) {
    return os << QString::number((int)value);
}

inline QTextStream& operator<<(QTextStream& os, std::string const& value) {
    return os << QString::fromStdString(value);
}

/// \brief Escape string literal, converting newline and other (TODO)
/// control characters into unicode.
inline QString escape_literal(QString const& in) {
    QString res;
    res.reserve(in.size() + 2);
    res += "«";
    for (QChar c : in) {
        if (c == '\n') {
            res += "␤";

        } else {
            res += c;
        }
    }

    res += "»";

    return res;
}

template <typename Iterable>
QTextStream& join(
    QTextStream&    os,
    QString const&  sep,
    Iterable const& list) {
    int index = 0;
    for (const auto& it : list) {
        if (0 < index) {
            os << sep;
        }
        os << to_string(it);
        ++index;
    }
    return os;
}

template <typename Iterable>
QString join(QString const& sep, Iterable const& list) {
    QString     out;
    QTextStream os{&out};
    join(os, sep, list);
    return out;
}

/// \brief Small insanity to allow for `os << "[" << join(os, "", "wer")
/// <<` and other stuff without having to break everything into multiple
/// lines. Yes, this overload makes zero sense but whatever.
inline QTextStream& operator<<(QTextStream& os, QTextStream const& value) {
    return os;
}


inline std::ostream& operator<<(
    std::ostream&       os,
    std::ostream const& value) {
    return os;
}


inline std::ostream& operator<<(std::ostream& os, QString const& value) {
    return os << value.toStdString();
}

#define __xxloc() std::cout << __FILE__ << ":" << __LINE__ << "\n";

extern QTextStream qcout;
