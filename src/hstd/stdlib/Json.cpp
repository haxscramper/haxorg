#include "Json.hpp"

#include <string>
#include <regex>
#include <limits>
#include <hstd/stdlib/Func.hpp>


template class nlohmann::basic_json<>;


std::ostream& operator<<(std::ostream& os, const json& value) {
    std::stringstream ss;
    ss << value;
    os << std::string::fromStdString(ss.str());
    return os;
}

QDebug operator<<(QDebug os, const json& value) {
    QDebugStateSaver saved{os};
    return os << to_string(value);
}
std::string to_string(const json& j) {
    return std::string::fromStdString(nlohmann::to_string(j));
}

void to_json(json& j, CR<Str> str) { to_json(j, str.toBase()); }

void to_json(json& j, CR<std::string> str) { ns::to_json(j, str); }

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
                    bool                         first = true;
                    int                          i     = 0;
                    Vec<Pair<std::string, json>> items;
                    for (auto const& [key, sub] : j.items()) {
                        items.push_back({key, sub});
                    }

                    sort(
                        items.begin(),
                        items.end(),
                        [&](auto const& lhs, auto const& rhs) {
                            return getSize(lhs.second)
                                 < getSize(rhs.second);
                        });

                    for (auto const& [key, sub] : items) {
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

void from_json(const json& in, std::string& out) {
    out = std::string::fromStdString(in.get<std::string>());
}

void from_json(const json& in, int& out) { out = in.get<int>(); }

void from_json(const json& in, bool& out) { out = in.get<bool>(); }
