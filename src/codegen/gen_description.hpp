#pragma once

#include <yaml-cpp/yaml.h>
#include <boost/mp11.hpp>
#include <boost/describe.hpp>

#include <hstd/stdlib/Variant.hpp>
#include <hstd/system/macros.hpp>
#include <hstd/stdlib/Opt.hpp>
#include <hstd/stdlib/Vec.hpp>
#include <hstd/stdlib/Str.hpp>
#include <hstd/stdlib/Ptrs.hpp>

using namespace boost::describe;
using boost::mp11::mp_for_each;

struct GenTu {
    struct TParam {
        Str name;
        BOOST_DESCRIBE_CLASS(TParam, (), (), (), (name));
    };

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
        Opt<Vec<TParam>> params;
        Str              name;
        Vec<Ident>       arguments;
        Str              result;
        Doc              doc;
        Opt<Str>         impl;
        bool             isVirtual     = false;
        bool             isConst       = false;
        bool             isStatic      = false;
        bool             isPureVirtual = false;
        BOOST_DESCRIBE_CLASS(
            Function,
            (),
            (),
            (),
            (name,
             arguments,
             result,
             isVirtual,
             isConst,
             isStatic,
             doc,
             impl,
             isPureVirtual,
             params));
    };

    struct TypeGroup;
    struct Enum;
    struct Struct;
    struct Namespace;

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
        SPtr<Function>,
        SPtr<Namespace>,
        Include,
        Pass>;

    struct Field {
        bool     isStatic;
        bool     isConst;
        Str      name;
        Str      type;
        Opt<Str> value;
        Doc      doc;
        BOOST_DESCRIBE_CLASS(
            Field,
            (),
            (),
            (),
            (isStatic, isConst, name, type, value, doc));
    };

    struct Struct {
        Str           name;
        Vec<Field>    fields;
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
        Str         variantField;
        Str         variantName;
        Opt<Str>    variantValue;
        Str         kindGetter;

        BOOST_DESCRIBE_CLASS(
            TypeGroup,
            (),
            (),
            (),
            (types,
             iteratorMacroName,
             enumName,
             kindGetter,
             variantField,
             variantName,
             variantValue));
    };

    struct Namespace {
        Str        name;
        Vec<Entry> entries;
        BOOST_DESCRIBE_CLASS(Namespace, (), (), (), (name, entries));
    };

    Vec<Entry> entries;
    Str        path;

    BOOST_DESCRIBE_CLASS(GenTu, (), (), (), (entries, path));
};

struct GenUnit {
    GenTu      header;
    Opt<GenTu> source;
    BOOST_DESCRIBE_CLASS(GenUnit, (), (), (), (header, source));
};

struct GenFiles {
    Vec<GenUnit> files;
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
    opt = node[name];
}


template <typename T>
void visitValue(YAML::Node const& node, T& tree) {
    using Bd = describe_bases<T, mod_any_access>;
    using Md = describe_members<T, mod_any_access>;
    mp_for_each<Md>([&](auto const& field) {
        visitField(node, tree.*field.pointer, field.name);
    });
}
