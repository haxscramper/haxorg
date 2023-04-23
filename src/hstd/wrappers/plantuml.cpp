#include <hstd/wrappers/plantuml.hpp>
#include <hstd/stdlib/strformat.hpp>

QString puml::Gantt::toString() const {
    QString result;

    result += "@startgantt\n";

    for (const auto& it : events) {
        result += it.toString() + "\n";
    }

    result += "@endgantt\n";

    return result;
}

QString puml::Gantt::Event::toString() const {
    QString result;
    result += "[${name}] starts on ${start}\n"
            "[${name}] ends on ${end}\n" %
            fold_format_pairs({{"name", name},
                               {"start", start.toString(Qt::ISODate)},
                               {"end", stop.toString(Qt::ISODate)}})
            ;


    return result;
}
