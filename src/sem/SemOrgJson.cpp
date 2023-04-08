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

json ListItem::toJson() const {
    json res = newJson();

    res["header"] = header ? header.value()->toJson() : json();
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
    using Prop = Subtree::Properties;
    using k    = Prop::PropertyKind;

    json res = newJson();
    subnodesJson(res);
    res["level"]       = level;
    res["todo"]        = todo;
    res["tags"]        = for_each_convert(tags);
    res["logbook"]     = for_each_convert(logbook);
    res["description"] = opt_convert(description);
    res["completion"]  = opt_convert(completion);
    res["title"]       = title ? title->toJson() : json();

    json drawer = json::object();
    {
        json props = json::array();
        for (const auto& prop : properties) {
            json exp;
            std::visit(
                [&](auto const& prop) {
                    exp["kind"] = to_string(prop.getKind());
                },
                prop);

            std::visit(
                overloaded{
                    [&](CR<Prop::ExportOptions> prop) {
                        exp["backend"] = prop.backend;
                        exp["args"]    = prop.values;
                    },
                    [](auto&&) {}},
                prop);

            props.push_back(exp);
        }

        drawer["props"] = props;
    }

    {
        json log      = json::object();
        drawer["log"] = log;
    }

    res["drawer"] = drawer;

    return res;
}

json Link::toJson() const {
    json res    = newJson();
    res["TODO"] = __LINE__;
    return res;
}

json Caption::toJson() const {
    json res    = newJson();
    res["text"] = text->toJson();
    return res;
}

json CommandGroup::toJson() const {
    json res;
    res["TODO"] = __LINE__;
    return res;
}

json Quote::toJson() const {
    json res    = newJson();
    res["text"] = text->toJson();
    return res;
}

json InlineMath::toJson() const {
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
