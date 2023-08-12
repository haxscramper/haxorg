#include "Json.hpp"

#include <string>
#include <regex>
#include <limits>
#include <hstd/stdlib/Func.hpp>


template class nlohmann::basic_json<>;


QTextStream& operator<<(QTextStream& os, const json& value) {
    std::stringstream ss;
    ss << value;
    os << QString::fromStdString(ss.str());
    return os;
}

QDebug operator<<(QDebug os, const json& value) {
    QDebugStateSaver saved{os};
    return os << to_string(value);
}
QString to_string(const json& j) {
    return QString::fromStdString(nlohmann::to_string(j));
}

void to_json(json& j, CR<Str> str) { to_json(j, str.toBase()); }

void to_json(json& j, CR<QString> str) {
    ns::to_json(j, str.toStdString());
}

void to_json(json& j, int i) { ns::to_json(j, i); }


std::string to_compact_json(
    const json&              j,
    const JsonFormatOptions& options) {
    std::unordered_map<std::size_t, int> sizes;

    Func<int(json const&)> getSize;
    getSize = [&](json const& j) -> int {
        std::size_t hash = std::hash<json>{}(j);
        if (!sizes.contains(hash)) {
            sizes[hash] = j.dump().size();
        }

        return sizes.at(hash);
    };

    Func<std::string(int indent, json const&)> format;

    format = [&](int indent, json const& j) -> std::string {
        int size = getSize(j);
        if (size < options.width - indent) {
            return j.dump();
        } else {
            switch (j.type()) {
                case json::value_t::string:
                case json::value_t::boolean:
                case json::value_t::number_float:
                case json::value_t::number_integer:
                case json::value_t::number_unsigned:
                    return j.dump();
                    break;

                case json::value_t::array: {
                    std::string result;
                    result += "[";
                    bool first = true;
                    for (int i = 0; i < j.size(); ++i) {
                        json const& sub = j[i];
                        result += "\n";
                        result += std::string(indent, ' ');
                        result += format(indent + options.indent, sub);
                        if (i < j.size() - 1) {
                            result += ",";
                        }
                    }

                    result += "]";

                    return result;
                }

                case json::value_t::object: {
                    std::string result;
                    result += "{";
                    bool first = true;
                    int  i     = 0;
                    for (auto const& [key, sub] : j.items()) {
                        result += "\n";
                        result += std::string(indent, ' ');
                        result += "\"" + key + "\": ";
                        result += format(indent + options.indent, sub);
                        if (i < j.size() - 1) {
                            result += ",";
                        }
                        ++i;
                    }

                    result += "}";

                    return result;
                }
            }
        }
    };


    return format(options.startIndent, j);
}
