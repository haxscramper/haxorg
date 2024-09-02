#include "ImmOrgHash.hpp"

namespace {
template <typename T>
std::size_t imm_hash_build(T const& value) {
    std::size_t result = 0;
    for_each_field_with_bases<T>([&](auto const& field) {
        boost::hash_combine(
            result,
            std::hash<
                std::remove_cvref_t<decltype(value.*field.pointer)>>{}(
                value.*field.pointer));
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
