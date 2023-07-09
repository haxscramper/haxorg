#include "SemOrg.hpp"

template <typename T>
sem::SemIdT<T> sem::SemId::as() const {
    SemIdT<T> result = SemIdT<T>(*this);
    if constexpr (!std::is_abstract_v<T>) {
        Q_ASSERT_X(
            this->get()->getKind() == T::staticKind,
            "cast sem ID node",
            "Cannot convert sem ID node of kind $# to $#"
                % to_string_vec(this->get()->getKind(), T::staticKind));
    }

    return result;
}

#define forward_declare(__Kind)                                           \
    template sem::SemIdT<sem::__Kind> sem::SemId::as() const;

EACH_SEM_ORG_KIND(forward_declare)
#undef forward_declare

template class std::
    variant<sem::SemIdT<sem::Time>, sem::SemIdT<sem::TimeRange>>;

template class UnorderedMap<Str, Str>;

#define __SUB_VARIANT_UNION_DEFINE_FIELD_COPY(EnumName, Type)             \
    case __PACK_IDX0(EnumName)::Type:                                     \
        this->Type##_field = other.Type##_field;                          \
        break;

#define __SUB_VARIANT_UNION_DEFINE_FIELD_DESTROY(EnumName, Type)          \
    case __PACK_IDX0(EnumName)::Type:                                     \
        Type##_field.~Type();                                             \
        break;

#define SUB_VARIANTS_UNION_DEFINE(                                        \
    EnumName, VariantName, VariantParent, fieldName, kindGetterName, ...) \
                                                                          \
    VariantParent::VariantName::VariantName()                             \
        : kindValue(VariantParent::EnumName::__PACK_IDX0(__VA_ARGS__))    \
        , CONCAT(__PACK_IDX0(__VA_ARGS__), _field)(                       \
              __PACK_IDX0(__VA_ARGS__)()) {}                              \
                                                                          \
    VariantParent::VariantName::VariantName(                              \
        VariantParent::VariantName const& other)                          \
        : kindValue(other.kindValue) {                                    \
        switch (kindValue) {                                              \
            FOR_EACH_CALL_WITH_PASS(                                      \
                __SUB_VARIANT_UNION_DEFINE_FIELD_COPY,                    \
                (VariantParent::EnumName),                                \
                __VA_ARGS__)                                              \
        }                                                                 \
    }                                                                     \
                                                                          \
    VariantParent::VariantName& VariantParent::VariantName::operator=(    \
        VariantParent::VariantName const& other) {                        \
        this->kindValue = other.kindValue;                                \
        switch (kindValue) {                                              \
            FOR_EACH_CALL_WITH_PASS(                                      \
                __SUB_VARIANT_UNION_DEFINE_FIELD_COPY,                    \
                (VariantParent::EnumName),                                \
                __VA_ARGS__)                                              \
        }                                                                 \
    }                                                                     \
                                                                          \
    VariantParent::VariantName::~VariantName() {                          \
        switch (kindValue) {                                              \
            FOR_EACH_CALL_WITH_PASS(                                      \
                __SUB_VARIANT_UNION_DEFINE_FIELD_DESTROY,                 \
                (VariantParent::EnumName),                                \
                __VA_ARGS__)                                              \
        }                                                                 \
    }


SUB_VARIANTS_UNION_DEFINE(
    Kind,
    Data,
    sem::Subtree::Property,
    data,
    getKind,
    Ordered,
    ExportOptions,
    Nonblocking,
    Origin,
    ExportLatexHeader,
    ExportLatexCompiler,
    ExportLatexClass,
    Trigger,
    Visibility,
    Effort,
    Blocker,
    Unnumbered,
    Created);
