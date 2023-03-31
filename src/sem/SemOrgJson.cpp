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
    json res = newJson();
    subnodesJson(res);
    return res;
}

json Table::toJson() const {
    json res = newJson();
    subnodesJson(res);
    return res;
}

json HashTag::toJson() const {
    json res = newJson();
    subnodesJson(res);
    return res;
}

json StmtList::toJson() const {
    json res = newJson();
    subnodesJson(res);
    return res;
}


json Completion::toJson() const {
    json res         = newJson();
    res["done"]      = done;
    res["full"]      = full;
    res["isPercent"] = isPercent;
    return res;
}


json Subtree::toJson() const {
    json res = newJson();
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
    json res = newJson();
    subnodesJson(res);
    return res;
}

json Paragraph::toJson() const {
    json res = newJson();
    subnodesJson(res);
    return res;
}

json Link::toJson() const {
    json res = newJson();


    return res;
}

json Time::toJson() const {
    json res = newJson();
    if (std::holds_alternative<Time::Static>(time)) {
        res["kind"]        = "static";
        res["static_time"] = "TODO static time";
    } else {
        res["kind"]         = "dynamic";
        res["dynamic_time"] = "TODO dynamic time";
    }

    return res;
}

json TimeRange::toJson() const {
    json res    = newJson();
    res["from"] = from->toJson();
    res["to"]   = to->toJson();
    return res;
}
