#pragma once

#include <yaml-cpp/yaml.h>
#include <boost/mp11.hpp>
#include <boost/describe.hpp>

#include <hstd/stdlib/Variant.hpp>
#include <hstd/system/macros.hpp>
#include <hstd/stdlib/Opt.hpp>
#include <hstd/stdlib/Vec.hpp>
#include <hstd/stdlib/Str.hpp>
#include <hstd/stdlib/Yaml.hpp>

using namespace boost::describe;
using boost::mp11::mp_for_each;

struct GenDescription {
    struct Ident {
        Str      name;
        Str      type;
        Opt<Str> value;
        BOOST_DESCRIBE_CLASS(Ident, (), (), (), (name, type, value));
    };

    struct Enum {
        Str        name;
        Vec<Ident> fields;
        BOOST_DESCRIBE_CLASS(Enum, (), (), (), (name, fields));
    };

    struct Function {
        Str        name;
        Vec<Ident> arguments;
        Str        result;
        BOOST_DESCRIBE_CLASS(
            Function,
            (),
            (),
            (),
            (name, arguments, result));
    };

    struct Struct {
        Str           name;
        Vec<Ident>    fields;
        Vec<Function> methods;
        Vec<Str>      bases;
        using Nested = Variant<Enum, Struct>;
        Vec<Nested> nested;
        BOOST_DESCRIBE_CLASS(
            Struct,
            (),
            (),
            (),
            (name, fields, methods, nested));
    };

    struct TypeGroup {
        Vec<Struct> types;
        BOOST_DESCRIBE_CLASS(TypeGroup, (), (), (), (types));
    };

    using Entry = Variant<Enum, Struct, TypeGroup>;
    Vec<Entry> entries;
    BOOST_DESCRIBE_CLASS(GenDescription, (), (), (), (entries));
};

template <typename T>
void visitValue(YAML::Node const& node, T& tree);


template <>
struct YAML::convert<Str> {
    static Node encode(Str const& str) {
        Node result;
        result = str.toStdString();
        return result;
    }
    static bool decode(Node const& in, Str& out) {
        out = Str::fromStdString(in.as<std::string>());
        return true;
    }
};


// clang-format off
inline void visitValue(YAML::Node const& node, Str& str) { str = node.as<Str>(); }
inline void visitValue(YAML::Node const& node, bool& str) { str = node.as<bool>(); }
inline void visitValue(YAML::Node const& node, int& str) { str = node.as<int>(); }
inline void visitField(YAML::Node const& node, Str& str, char const* name) { visitValue(node[name], str); }
inline void visitField(YAML::Node const& node, bool& str, char const* name) { visitValue(node[name], str); }
inline void visitField(YAML::Node const& node, int& str, char const* name) { visitValue(node[name], str); }
// clang-format on

template <typename T>
void visitValue(YAML::Node const& node, Vec<T>& opt) {
    if (node && node.IsSequence()) {
        for (auto const& it : node) {
            T result;
            visitValue(it, result);
            opt.push_back(result);
        }
    }
}

template <typename T>
void visitValue(YAML::Node const& node, Opt<T>& opt) {
    if (node && !node.IsNull()) {
        T result;
        visitValue(node, result);
        opt = result;
    }
}

template <typename T>
void visitField(YAML::Node const& node, T& opt, char const* name) {
    visitValue(node[name], opt);
}


template <typename T>
void visitValue(YAML::Node const& node, T& tree) {
    using Bd = describe_bases<T, mod_any_access>;
    using Md = describe_members<T, mod_any_access>;
    mp_for_each<Md>([&](auto const& field) {
        visitField(node, tree.*field.pointer, field.name);
    });
}

inline void visitValue(
    YAML::Node const&               node,
    GenDescription::Struct::Nested& rhs) {
    Str kind = node["kind"].as<Str>();
    if (kind == "Enum") {
        GenDescription::Enum result;
        visitValue(node, result);
        rhs = result;
    } else if (kind == "Struct") {
        GenDescription::Struct result;
        visitValue(node, result);
        rhs = result;
    }
}

inline void visitValue(
    YAML::Node const&      node,
    GenDescription::Entry& rhs) {
    Str kind = node["kind"].as<Str>();
    if (kind == "Enum") {
        GenDescription::Enum result;
        visitValue(node, result);
        rhs = result;
    } else if (kind == "Struct") {
        GenDescription::Struct result;
        visitValue(node, result);
        rhs = result;
    } else if (kind == "TypeGroup") {
        GenDescription::TypeGroup result;
        visitValue(node, result);
        rhs = result;
    }
}

namespace YAML {
template <>
struct convert<GenDescription::Ident> {
    static bool decode(Node const& node, GenDescription::Ident& rhs) {
        visitValue(node, rhs);
        return true;
    }
};

template <>
struct convert<GenDescription::Function> {
    static bool decode(Node const& node, GenDescription::Function& rhs) {
        visitValue(node, rhs);
        return true;
    }
};

template <>
struct convert<GenDescription::Enum> {
    static bool decode(Node const& node, GenDescription::Enum& rhs) {
        visitValue(node, rhs);
        return true;
    }
};

template <>
struct convert<GenDescription::Struct> {
    static bool decode(Node const& node, GenDescription::Struct& rhs) {
        visitValue(node, rhs);
        return true;
    }
};

template <>
struct convert<GenDescription::TypeGroup> {
    static bool decode(Node const& node, GenDescription::TypeGroup& rhs) {
        visitValue(node, rhs);
        return true;
    }
};

template <>
struct convert<GenDescription::Entry> {
    static bool decode(Node const& node, GenDescription::Entry& rhs) {
        visitValue(node, rhs);
        return true;
    }
};

template <>
struct convert<GenDescription> {
    static bool decode(Node const& node, GenDescription& rhs) {
        visitValue(node, rhs);
        return true;
    }
};
} // namespace YAML
