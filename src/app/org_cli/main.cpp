#include <boost/describe.hpp>
#include <boost/mp11.hpp>
#include <fmt/base.h>
#include <fmt/format.h>
#include <map>
#include <optional>
#include <string_view>
#include <type_traits>
#include <variant>

template <class T>
struct field_annotations;

template <class T, class MemberPtr>
struct annotation_for_member {
    using type = std::monostate;
    static constexpr std::optional<type> get() { return std::nullopt; }
};

#define ANNOTATE_MEMBER(Struct, Member, Value)                                           \
    template <>                                                                          \
    struct annotation_for_member<Struct, decltype(&Struct::Member)> {                    \
        static constexpr auto value = (Value);                                           \
        using type                  = decltype(value);                                   \
        static constexpr std::optional<type> get() { return value; }                     \
    };

template <class T, class F>
void for_each_mutable_field(T& value, F&& f) {
    using members = boost::describe::describe_members<T, boost::describe::mod_public>;

    boost::mp11::mp_for_each<members>([&](auto D) {
        using descriptor        = decltype(D);
        constexpr auto ptr      = descriptor::pointer;
        using member_type       = std::remove_reference_t<decltype(value.*ptr)>;
        using annotation_traits = annotation_for_member<T, decltype(ptr)>;
        using annotation_type   = typename annotation_traits::type;

        f.template operator()<member_type, annotation_type>(
            value.*ptr, std::string_view{descriptor::name}, annotation_traits::get());
    });
}

inline std::string to_kebab(std::string_view name) {
    std::string result(name);
    for (char& c : result) {
        if (c == '_') { c = '-'; }
    }
    return result;
}

template <class T>
constexpr std::string_view type_name() {
    if constexpr (std::is_same_v<T, bool>) {
        return "bool";
    } else if constexpr (std::is_integral_v<T>) {
        return "int";
    } else if constexpr (std::is_floating_point_v<T>) {
        return "float";
    } else if constexpr (
        std::is_same_v<T, std::string> || std::is_same_v<T, std::string_view>) {
        return "string";
    } else {
        return "value";
    }
}

template <class A>
std::string annotation_text(std::optional<A> const& a) {
    if constexpr (std::is_same_v<A, std::monostate>) {
        return {};
    } else {
        return a ? fmt::format("  [{}]", *a) : std::string{};
    }
}


template <class T, class F>
void for_each_leaf(T& value, std::string const& prefix, F&& f) {
    using members = boost::describe::describe_members<T, boost::describe::mod_public>;

    boost::mp11::mp_for_each<members>([&](auto D) {
        using descriptor   = decltype(D);
        constexpr auto ptr = descriptor::pointer;
        using member_type  = std::remove_reference_t<decltype(value.*ptr)>;

        std::string name = prefix.empty() ? to_kebab(descriptor::name)
                                          : prefix + "." + to_kebab(descriptor::name);

        if constexpr (boost::describe::has_describe_members<member_type>::value) {
            for_each_leaf(value.*ptr, name, f);
        } else {
            using annotation_traits = annotation_for_member<T, decltype(ptr)>;
            f(value.*ptr, name, annotation_traits::get());
        }
    });
}


inline std::map<std::string, std::optional<std::string>> tokenize(int argc, char** argv) {
    std::map<std::string, std::optional<std::string>> out;
    for (int i = 1; i < argc; ++i) {
        std::string tok = argv[i];
        if (tok.empty() || tok[0] != '-') { continue; }

        std::size_t start = tok.find_first_not_of('-');
        if (start == std::string::npos) { continue; }
        std::string body = tok.substr(start);

        auto eq = body.find('=');
        if (eq != std::string::npos) {
            out[body.substr(0, eq)] = body.substr(eq + 1);
        } else if (i + 1 < argc && argv[i + 1][0] != '-') {
            out[body] = std::string(argv[i + 1]);
            ++i;
        } else {
            out[body] = std::nullopt; // boolean flag
        }
    }
    return out;
}

template <class T>
void assign_value(T& field, std::optional<std::string> const& val) {
    if constexpr (std::is_same_v<T, bool>) {
        field = val ? (*val == "true" || *val == "1") : true;
    } else if constexpr (std::is_integral_v<T>) {
        field = static_cast<T>(std::stoll(*val));
    } else if constexpr (std::is_floating_point_v<T>) {
        field = static_cast<T>(std::stod(*val));
    } else { // std::string / std::string_view
        field = T{*val};
    }
}


template <class T>
void print_help(std::string_view program) {
    fmt::println("Usage: {} [options]", program);
    fmt::println("Options:");
    T dummy{};
    for_each_leaf(dummy, "", [](auto& field, std::string const& name, auto annotation) {
        using FieldType = std::remove_reference_t<decltype(field)>;
        fmt::println(
            "  --{:<32} <{}>{}",
            name,
            type_name<FieldType>(),
            annotation_text(annotation));
    });
}

template <class T>
T parse(int argc, char** argv) {
    auto args = tokenize(argc, argv);
    T    result{};
    for_each_leaf(result, "", [&](auto& field, std::string const& name, auto) {
        auto it = args.find(name);
        if (it != args.end()) { assign_value(field, it->second); }
    });
    return result;
}


struct Sub2 {
    int sub_nested2;
};
BOOST_DESCRIBE_STRUCT(Sub2, (), (sub_nested2))

struct Nested {
    Sub2 sub_field1;
};
BOOST_DESCRIBE_STRUCT(Nested, (), (sub_field1))

struct Main {
    std::string input;
    int         count;
    bool        verbose;
    Nested      parent_field;
};
BOOST_DESCRIBE_STRUCT(Main, (), (input, count, verbose, parent_field))

ANNOTATE_MEMBER(Main, input, std::string_view{"path to the input file"})
ANNOTATE_MEMBER(Main, count, std::string_view{"number of iterations"})

int main(int argc, char** argv) {
    for (int i = 1; i < argc; ++i) {
        if (std::string_view{argv[i]} == "--help") {
            print_help<Main>(argv[0]);
            return 0;
        }
    }

    Main opts = parse<Main>(argc, argv);

    for_each_leaf(opts, "", [](auto& field, std::string const& name, auto) {
        fmt::println("{} = {}", name, field);
    });
}
