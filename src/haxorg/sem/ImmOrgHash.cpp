#include "ImmOrgHash.hpp"
#include <hstd/ext/logger.hpp>

using namespace hstd;

namespace {
const std::string loc_field = std::string{"loc"};

template <typename T>
std::size_t imm_hash_build(T const& value) {
    std::size_t result = 0;
    HSLOG_INFO("ast.imm", hstd::value_metadata<T>::typeName());
    HSLOG_DEPTH_SCOPE_ANON();
    // HSLOG_TRACE_STACKTRACE("ast.imm", trace);
    for_each_field_with_bases<T>([&](auto const& field) {
        using FieldType = DESC_FIELD_TYPE(field);
        if (std::is_same_v<Opt<org::parse::LineCol>, FieldType>
            && field.name == loc_field) {
            // pass
        } else {
            auto hash_value = std::hash<
                std::remove_cvref_t<decltype(value.*field.pointer)>>{}(
                value.*field.pointer);
            auto tmp_result = result;
            hstd::hax_hash_combine(result, hash_value);
            HSLOG_INFO(
                "ast.imm",
                hstd::fmt(
                    "{} {} hash 0x{:X} + 0x{:X} => 0x{:X}",
                    field.name,
                    value.*field.pointer,
                    hash_value,
                    tmp_result,
                    result));
        }
    });

    HSLOG_INFO("ast.imm", hstd::fmt("END-HASH 0x{:X}", result));
    return result;
}

template <typename T>
bool imm_eq_build(T const* lhs, T const* rhs) {
    bool result = true;
    for_each_field_with_bases<T>([&](auto const& field) {
        using FieldType = DESC_FIELD_TYPE(field);
        if (std::is_same_v<Opt<org::parse::LineCol>, FieldType>
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
    std::size_t std::hash<org::imm::Imm##__kind>::operator()(             \
        org::imm::Imm##__kind const& it) const noexcept {                 \
        return imm_hash_build(it);                                        \
    }

EACH_SEM_ORG_KIND(_define_hash)
#undef _define_hash


#define _define_hash(__parent, __qual, _)                                 \
    std::size_t std::hash<org::imm::Imm##__parent::__qual>::operator()(   \
        org::imm::Imm##__parent::__qual const& it) const noexcept {       \
        return imm_hash_build(it);                                        \
    }

EACH_SEM_ORG_RECORD_NESTED(_define_hash)
#undef _define_hash


#define _declare_hash(__qual, _)                                          \
    std::size_t std::hash<org::sem::__qual>::operator()(                  \
        org::sem::__qual const& it) const noexcept {                      \
        return imm_hash_build(it);                                        \
    }

EACH_SHARED_ORG_RECORD(_declare_hash)
#undef _declare_hash


// eq comparison methods

#define _eq_method(__QualType, _)                                         \
    bool org::imm::Imm##__QualType::operator==(                           \
        org::imm::Imm##__QualType const& other) const {                   \
        return imm_eq_build<org::imm::Imm##__QualType>(this, &other);     \
    }

EACH_SEM_ORG_RECORD(_eq_method)
#undef _eq_method

#define _eq_method(__QualType, _)                                         \
    bool org::sem::__QualType::operator==(                                \
        org::sem::__QualType const& other) const {                        \
        return imm_eq_build<org::sem::__QualType>(this, &other);          \
    }

EACH_SHARED_ORG_RECORD(_eq_method)
#undef _eq_method

bool org::sem::HashTagFlat::operator<(
    sem::HashTagFlat const& other) const {
    return this->tags < other.tags;
}
