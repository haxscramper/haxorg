#pragma once

#include <haxorg/imm/ImmOrgAdapterGenerated.hpp>


namespace org::imm {

#define __declare_adapter(Derived)                                                       \
    template <>                                                                          \
    struct ImmAdapterT<org::imm::Imm##Derived> : public ImmAdapterTBase<Imm##Derived> {  \
        USE_IMM_ADAPTER_BASE(Imm##Derived);                                              \
    };

__declare_adapter(Org);

template <typename T>
template <typename F>
inline ImmAdapterT<F> ImmAdapterTBase<T>::getField(
    org::imm::ImmIdT<F> T::* fieldPtr) const {
    return ImmAdapterT<F>{(get()->*fieldPtr).asOrg(), ctx, {}};
}

template <typename T>
template <typename F>
ImmAdapterT<F> ImmAdapterTBase<T>::getField(
    org::imm::ImmIdT<F> T::*    fieldPtr,
    ImmSubnodeAccessStep const& step) const {
    return ImmAdapterT<F>{(get()->*fieldPtr).asOrg(), ctx, path.add(step)};
}

template <typename T>
struct remove_sem_org {
    using type = hstd::remove_smart_pointer<T>::type;
};

template <>
struct remove_sem_org<ImmId> {
    using type = ImmOrg;
};

template <>
struct remove_sem_org<ImmAdapter> {
    using type = ImmOrg;
};

template <typename T>
struct remove_sem_org<ImmIdT<T>> {
    using type = hstd::remove_smart_pointer<T>::type;
};

template <typename T>
struct remove_sem_org<ImmAdapterT<T>> {
    using type = hstd::remove_smart_pointer<T>::type;
};


template <typename T>
concept IsImmOrg = std::derived_from<typename remove_sem_org<T>::type, ImmOrg>;


/// \brief Map immutable AST type to the sem type, defines inner type
/// `sem_type`
template <typename Imm>
struct imm_to_sem_map {};

/// \brief Map sem AST type to the immer type, defines inner type
/// `imm_type`
template <typename Mut>
struct sem_to_imm_map {};

#define _gen_map(__Kind)                                                                 \
    template <>                                                                          \
    struct imm_to_sem_map<org::imm::Imm##__Kind> {                                       \
        using sem_type = org::sem::__Kind;                                               \
    };                                                                                   \
    template <>                                                                          \
    struct sem_to_imm_map<org::sem::__Kind> {                                            \
        using imm_type = org::imm::Imm##__Kind;                                          \
    };
EACH_SEM_ORG_KIND(_gen_map)
#undef _gen_map


sem::SemId<sem::Org> sem_from_immer(
    org::imm::ImmId const&   id,
    ImmAstContext const&     ctx,
    ImmSemSerdeConfig const& config = ImmSemSerdeConfig{});

org::imm::ImmId immer_from_sem(
    org::sem::SemId<org::sem::Org> const& id,
    ImmAstEditContext&                    ctx,
    ImmSemSerdeConfig const&              config = ImmSemSerdeConfig{});

}; // namespace org::imm


template <typename T>
struct fmt::formatter<org::imm::ImmAdapterT<T>> {
    constexpr auto parse(fmt::format_parse_context& ctx) { return ctx.begin(); }
    hstd::fmt_iter format(org::imm::ImmAdapterT<T> const& p, fmt::format_context& ctx)
        const {
        return hstd::fmt_ctx(p.id, ctx);
    }
};
