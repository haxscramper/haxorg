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

json List::toJson() const {
    json res = newJson();
    subnodesJson(res);
    return res;
}

json Block::attachedJson() const {
    json res;
    return res;
}

json ListItem::toJson() const {
    json res = newJson();

    res["header"] = header ? header.value()->toJson() : json();
    subnodesJson(res);

    return res;
}

json Markup::toJson() const {
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
    json res        = newJson();
    res["isActive"] = isActive;
    res["isStatic"] = isStatic();
    if (isStatic()) {
        Time::Static const& impl = getStatic();
        json                repeat;
        if (impl.repeat.has_value()) {
            auto& r        = *impl.repeat;
            repeat["mode"] = to_string(r.mode);
        }
        json jtime;
        jtime["repeat"] = repeat;
        jtime["time"]   = impl.time.toString(Qt::ISODate);
        res["static"]   = jtime;
    } else {
        res["dynamic"] = getDynamic().expr;
    }

    return res;
}

json TimeRange::toJson() const {
    json res    = newJson();
    res["from"] = from->toJson();
    res["to"]   = to->toJson();
    return res;
}
