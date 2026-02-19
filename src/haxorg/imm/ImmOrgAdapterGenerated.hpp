#pragma once

#include <haxorg/imm/ImmOrg.hpp>

namespace org::imm {
#define __DECLARE_VALUE_READ_FIELD(                                       \
    __FIELD_TYPE,                                                         \
    __FIELD_NAME,                                                         \
    __FIELD_UPPERCASE,                                                    \
    __PARENT_TYPE,                                                        \
    __PARENT_KIND)                                                        \
    [[refl]] BOOST_PP_REMOVE_PARENS(__FIELD_TYPE) const&                  \
        get##__FIELD_UPPERCASE() const;

#define __DECLARE_VALUE_WRITE_FIELD(                                      \
    __FIELD_TYPE,                                                         \
    __FIELD_NAME,                                                         \
    __FIELD_UPPERCASE,                                                    \
    __PARENT_TYPE,                                                        \
    __PARENT_KIND)                                                        \
    [[refl]]                                                              \
    void set##__FIELD_UPPERCASE(BOOST_PP_REMOVE_PARENS(__FIELD_TYPE)      \
                                    const& value);


#define __DECLARE_VALUE_READ_TYPE(__KIND)                                 \
    struct [[refl(R"({"default-constructor": false})")]] Imm##__KIND##    \
        ValueRead {                                                       \
        org::imm::Imm##__KIND* ptr;                                       \
        Imm##__KIND##ValueRead(org::imm::Imm##__KIND const* ptr)          \
            : ptr{const_cast<org::imm::Imm##__KIND*>(ptr)} {}             \
        EACH_IMM_ORG_Imm##__KIND##_FIELD_WITH_BASE_FIELDS(                \
            __DECLARE_VALUE_READ_FIELD);                                  \
        DESC_FIELDS(Imm##__KIND##ValueRead, ());                          \
    };                                                                    \
                                                                          \
    struct [[refl(R"({"default-constructor": false})")]] Imm##__KIND##    \
        Value : public org::imm::Imm##__KIND##ValueRead {                 \
        using org::imm::Imm##__KIND##ValueRead::Imm##__KIND##ValueRead;   \
        EACH_IMM_ORG_Imm##__KIND##_FIELD_WITH_BASE_FIELDS(                \
            __DECLARE_VALUE_WRITE_FIELD);                                 \
        DESC_FIELDS(Imm##__KIND##Value, ());                              \
    };


EACH_SEM_ORG_KIND(__DECLARE_VALUE_READ_TYPE)

#undef __DECLARE_VALUE_READ_TYPE
#undef __DECLARE_VALUE_READ_FIELD
#undef __DECLARE_VALUE_WRITE_FIELD

// Define specializations for all final (non-abstract) org-mode types.
#define __define_adapter(Derived, Base)                                   \
    template <>                                                           \
    struct [[refl(                                                        \
        "{\"default-constructor\": false, \"wrapper-name\": "             \
        "\"Imm" #Derived                                                  \
        "Adapter\", \"wrapper-has-params\": "                             \
        "false}")]] ImmAdapterT<org::imm::Imm##Derived>                   \
        : ImmAdapterTBase<Imm##Derived>                                   \
        , ImmAdapter##Derived##API {                                      \
        using api_type = ImmAdapter##Derived##API;                        \
        USE_IMM_ADAPTER_BASE(org::imm::Imm##Derived);                     \
        [[refl]] ImmAdapterT(org::imm::ImmAdapter const& other)           \
            : ImmAdapterTBase<Imm##Derived>{other} {                      \
            LOGIC_ASSERTION_CHECK_FMT(                                    \
                other.getKind() == OrgSemKind::Derived,                   \
                "Adapter type mismatch, creating {} from generic "        \
                "adapter of type {}",                                     \
                #Derived,                                                 \
                other.getKind());                                         \
        }                                                                 \
        [[refl]] org::imm::Imm##Derived##ValueRead getValue() const {     \
            return org::imm::Imm##Derived##ValueRead{&this->value()};     \
        };                                                                \
    };

EACH_SEM_ORG_FINAL_TYPE_BASE(__define_adapter)
#undef __define_adapter
} // namespace org::imm
