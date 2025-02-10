#include "ImmOrgHash.hpp"

namespace {
const std::string loc_field = std::string{"loc"};

template <typename T>
std::size_t imm_hash_build(T const& value) {
    std::size_t result = 0;
    for_each_field_with_bases<T>([&](auto const& field) {
        using FieldType = DESC_FIELD_TYPE(field);
        if (std::is_same_v<Opt<LineCol>, FieldType>
            && field.name == loc_field) {
            // pass
        } else {
            boost::hash_combine(
                result,
                std::hash<
                    std::remove_cvref_t<decltype(value.*field.pointer)>>{}(
                    value.*field.pointer));
        }
    });
    return result;
}

template <typename T>
bool imm_eq_build(T const* lhs, T const* rhs) {
    bool result = true;
    for_each_field_with_bases<T>([&](auto const& field) {
        using FieldType = DESC_FIELD_TYPE(field);
        if (std::is_same_v<Opt<LineCol>, FieldType>
            && field.name == loc_field) {
            // pass
        } else if (result) {
            result &= lhs->*field.pointer == rhs->*field.pointer;
        }
    });
    return result;
}

} // namespace

#define _define_hash(__kind)                                              \
    std::size_t std::hash<org::Imm##__kind>::operator()(                  \
        org::Imm##__kind const& it) const noexcept {                      \
        return imm_hash_build(it);                                        \
    }

EACH_SEM_ORG_KIND(_define_hash)
#undef _define_hash


#define _define_hash(__parent, __qual, _)                                 \
    std::size_t std::hash<org::Imm##__parent::__qual>::operator()(        \
        org::Imm##__parent::__qual const& it) const noexcept {            \
        return imm_hash_build(it);                                        \
    }

EACH_SEM_ORG_RECORD_NESTED(_define_hash)
#undef _define_hash


#define _declare_hash(__qual, _)                                          \
    std::size_t std::hash<sem::__qual>::operator()(sem::__qual const& it) \
        const noexcept {                                                  \
        return imm_hash_build(it);                                        \
    }

EACH_SHARED_ORG_RECORD(_declare_hash)
#undef _declare_hash


// eq comparison methods

#define _eq_method(__QualType, _)                                         \
    bool org::Imm##__QualType::operator==(                                \
        org::Imm##__QualType const& other) const {                        \
        return imm_eq_build<org::Imm##__QualType>(this, &other);          \
    }

EACH_SEM_ORG_RECORD(_eq_method)
#undef _eq_method

#define _eq_method(__QualType, _)                                         \
    bool sem::__QualType::operator==(sem::__QualType const& other)        \
        const {                                                           \
        return imm_eq_build<sem::__QualType>(this, &other);               \
    }

EACH_SHARED_ORG_RECORD(_eq_method)
#undef _eq_method

bool sem::HashTagFlat::operator<(sem::HashTagFlat const& other) const {
    return this->tags < other.tags;
}
