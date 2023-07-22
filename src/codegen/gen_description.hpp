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
#include <hstd/stdlib/Ptrs.hpp>

using namespace boost::describe;
using boost::mp11::mp_for_each;

struct GenTu {
    struct Ident {
        Str      name;
        Str      type;
        Opt<Str> value;
        BOOST_DESCRIBE_CLASS(Ident, (), (), (), (name, type, value));
    };

    struct Doc {
        Str brief;
        Str full;
        BOOST_DESCRIBE_CLASS(Doc, (), (), (), (brief, full));
    };

    struct EnumField {
        Str      name;
        Opt<Str> value;
        Doc      doc;
        BOOST_DESCRIBE_CLASS(EnumField, (), (), (), (name, value, doc));
    };

    struct Enum {
        Str            name;
        Vec<EnumField> fields;
        Doc            doc;
        Opt<Str>       base;
        BOOST_DESCRIBE_CLASS(Enum, (), (), (), (name, fields, doc, base));
    };

    struct Function {
        Str        name;
        Vec<Ident> arguments;
        Str        result;
        Doc        doc;
        bool       isVirtual = false;
        bool       isConst   = false;
        bool       isStatic  = false;
        BOOST_DESCRIBE_CLASS(
            Function,
            (),
            (),
            (),
            (name, arguments, result, isVirtual, isConst, doc));
    };

    struct TypeGroup;
    struct Enum;
    struct Struct;
    struct Include {
        Str  what;
        bool isSystem = false;
        BOOST_DESCRIBE_CLASS(Include, (), (), (), (what, isSystem));
    };
    struct Pass {
        Str what;
        BOOST_DESCRIBE_CLASS(Pass, (), (), (), (what));
    };


    using Entry = Variant<
        SPtr<Enum>,
        SPtr<Struct>,
        SPtr<TypeGroup>,
        Include,
        Pass>;

    struct Struct {
        Str           name;
        Vec<Ident>    fields;
        Vec<Function> methods;
        Vec<Str>      bases;
        Vec<Entry>    nested;
        bool          concreteKind = true;

        Doc doc;
        BOOST_DESCRIBE_CLASS(
            Struct,
            (),
            (),
            (),
            (name, fields, methods, bases, nested, doc, concreteKind));
    };

    struct TypeGroup {
        Vec<Struct> types;
        Str         iteratorMacroName;
        Str         enumName;

        BOOST_DESCRIBE_CLASS(
            TypeGroup,
            (),
            (),
            (),
            (types, iteratorMacroName, enumName));
    };

    Vec<Entry> entries;
    Str        path;

    BOOST_DESCRIBE_CLASS(GenTu, (), (), (), (entries, path));
};

struct GenFiles {
    Vec<GenTu> files;
    BOOST_DESCRIBE_CLASS(GenFiles, (), (), (), (files));
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

inline void visitValue(YAML::Node const& node, GenTu::Entry& rhs) {
    Str kind = node["kind"].as<Str>();
    if (kind == "Enum") {
        auto result = std::make_shared<GenTu::Enum>();
        visitValue(node, *result);
        rhs = result;
    } else if (kind == "Struct") {
        auto result = std::make_shared<GenTu::Struct>();
        visitValue(node, *result);
        rhs = result;
    } else if (kind == "TypeGroup") {
        auto result = std::make_shared<GenTu::TypeGroup>();
        visitValue(node, *result);
        rhs = result;
    }
}

namespace YAML {

template <typename T>
struct convert<std::shared_ptr<T>> {
    static bool decode(Node const& node, std::shared_ptr<T>& rhs) {
        rhs = std::make_shared<T>();
        convert<T>::decode(*rhs);
        return true;
    }
};

template <>
struct convert<GenTu::Ident> {
    static bool decode(Node const& node, GenTu::Ident& rhs) {
        visitValue(node, rhs);
        return true;
    }
};

template <>
struct convert<GenTu::Function> {
    static bool decode(Node const& node, GenTu::Function& rhs) {
        visitValue(node, rhs);
        return true;
    }
};

template <>
struct convert<GenTu::Enum> {
    static bool decode(Node const& node, GenTu::Enum& rhs) {
        visitValue(node, rhs);
        return true;
    }
};

template <>
struct convert<GenTu::Struct> {
    static bool decode(Node const& node, GenTu::Struct& rhs) {
        visitValue(node, rhs);
        return true;
    }
};

template <>
struct convert<GenTu::TypeGroup> {
    static bool decode(Node const& node, GenTu::TypeGroup& rhs) {
        visitValue(node, rhs);
        return true;
    }
};

template <>
struct convert<GenTu::Entry> {
    static bool decode(Node const& node, GenTu::Entry& rhs) {
        visitValue(node, rhs);
        return true;
    }
};

template <>
struct convert<GenTu> {
    static bool decode(Node const& node, GenTu& rhs) {
        visitValue(node, rhs);
        return true;
    }
};
} // namespace YAML
