#include <sem/SemOrg.hpp>

using namespace sem;

template <typename T>
json for_each_convert(Vec<T> const& values) {
    json res = json::array();
    for (const auto& it : values) {
        res.push_back(it->toJson());
    }
    return res;
}

template <typename T>
json opt_convert(Opt<T> const& value) {
    json res = json();
    if (value.has_value()) {
        res = value.value()->toJson();
    }
    return res;
}

json Row::toJson() const {
    json res;
    subnodesJson(res);
    return res;
}

json Table::toJson() const {
    json res;
    subnodesJson(res);
    return res;
}

json HashTag::toJson() const {
    json res;
    subnodesJson(res);
    return res;
}

json StmtList::toJson() const {
    json res;
    subnodesJson(res);
    return res;
}


json Completion::toJson() const {
    json res;
    res["done"]      = done;
    res["full"]      = full;
    res["isPercent"] = isPercent;
    return res;
}

json Subtree::toJson() const {
    json res;
    subnodesJson(res);
    res["level"]       = level;
    res["todo"]        = todo;
    res["tags"]        = for_each_convert(tags);
    res["logbook"]     = for_each_convert(logbook);
    res["description"] = opt_convert(description);
    res["completion"]  = opt_convert(completion);
    res["title"]       = title ? title->toJson() : json();
    return res;
}

json SubtreeLog::toJson() const {
    json res;
    subnodesJson(res);
    return res;
}

json TimeRange::toJson() const {
    json res;
    subnodesJson(res);
    return res;
}
