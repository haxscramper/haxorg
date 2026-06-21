#include <boost/describe.hpp>
#include <boost/mp11.hpp>
#include <fmt/base.h>
#include <fmt/format.h>
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


struct Person {
    int              id;
    std::string_view name;
    double           salary;
};

BOOST_DESCRIBE_STRUCT(Person, (), (id, name, salary))

ANNOTATE_MEMBER(Person, id, std::string_view{"primary_key"})
ANNOTATE_MEMBER(Person, name, 42)

int main() {
    Person person{1, "alice", 10.0};

    for_each_mutable_field(
        person,
        []<typename FieldType, typename AnnotationType>(
            FieldType&                           field,
            std::string_view                     name,
            std::optional<AnnotationType> const& annotation) {
            fmt::println("{}: {}", field, name);
        });
}
