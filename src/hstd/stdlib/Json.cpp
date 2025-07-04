#include "Json.hpp"

#include <string>
#include <hstd/stdlib/Func.hpp>


template class nlohmann::basic_json<>;

using namespace hstd;

std::string hstd::to_compact_json(
    const json&              j,
    const JsonFormatOptions& options) {
    std::unordered_map<std::size_t, int> sizes;

    Func<int(json const&)> getSize;
    getSize = [&](json const& j) -> int {
        std::size_t hash = std::hash<json>{}(j);
        if (!sizes.contains(hash)) {
            sizes[hash] = j.dump(
                               2,
                               ' ',
                               false,
                               json::error_handler_t::ignore)
                              .size();
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
                case json::value_t::string: {
                    try {
                        return j.dump();
                    } catch (json::type_error& err) {
                        return j.dump(
                            2, ' ', false, json::error_handler_t::ignore);
                    }

                    break;
                }
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
                        if (i < j.size() - 1) { result += ","; }
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
                            if (options.stableFieldOrder) {
                                return lhs.first < rhs.first;
                            } else {
                                return getSize(lhs.second)
                                     < getSize(rhs.second);
                            }
                        });

                    for (auto const& [key, sub] : items) {
                        result += "\n";
                        result += std::string(indent, ' ');
                        result += "\"" + key + "\": ";
                        result += format(indent + options.indent, sub);
                        if (i < j.size() - 1) { result += ","; }
                        ++i;
                    }

                    result += "}";

                    return result;
                }
                default: {
                    return "";
                }
            }
        }
    };


    return format(options.startIndent, j);
}

void hstd::filterFields(
    json&                           j,
    const std::vector<std::string>& fieldsToRemove) {
    if (j.is_object()) {
        for (auto it = j.begin(); it != j.end();) {
            if (std::find(
                    fieldsToRemove.begin(), fieldsToRemove.end(), it.key())
                != fieldsToRemove.end()) {
                it = j.erase(it);
            } else {
                filterFields(*it, fieldsToRemove);
                ++it;
            }
        }
    } else if (j.is_array()) {
        for (json& el : j) { filterFields(el, fieldsToRemove); }
    }
}
