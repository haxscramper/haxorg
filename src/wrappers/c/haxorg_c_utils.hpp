#pragma once

#include <haxorg/sem/SemOrg.hpp>
#include <haxorg/api/SemBaseApi.hpp>
#include <haxorg/api/ParseContext.hpp>
#include <haxorg/imm/ImmOrgAdapter.hpp>
#include <wrappers/c/haxorg_c_api.h>
#include <hstd/stdlib/RangeSegmentation.hpp>
#include <haxorg/serde/SemOrgCereal.hpp>

namespace org::bind::c {


enum class MemoryPolicy : uintptr_t
{
    Reference = 0,
    Unique    = 1,
    Shared    = 2
};

inline void* tag_pointer(void* raw_ptr, MemoryPolicy policy) {
    return (void*)((uintptr_t)raw_ptr | (uintptr_t)policy);
}
inline MemoryPolicy get_pointer_policy(void* tagged_ptr) {
    return static_cast<MemoryPolicy>((uintptr_t)tagged_ptr & 3ULL);
}
inline void* untag_pointer(void* tagged_ptr) {
    return (void*)((uintptr_t)tagged_ptr & ~3ULL);
}

inline void clear_context(OrgContext* ctx) {
    if (ctx) {
        ctx->has_error    = 0;
        ctx->error_msg[0] = '\0';
    }
}
inline void set_context_error(OrgContext* ctx, const char* msg) {
    if (ctx) {
        ctx->has_error = 1;
        std::snprintf(ctx->error_msg, sizeof(ctx->error_msg), "%s", msg);
    }
}


template <typename CoreT>
CoreT* unwrap_instance(
    OrgContext*               ctx,
    haxorg_ptr_payload const& payload) {
    if (!payload.data) {
        set_context_error(ctx, "Instance pointer is null");
        return nullptr;
    }

    MemoryPolicy policy  = get_pointer_policy(payload.data);
    void*        raw_ptr = untag_pointer(payload.data);

    return static_cast<CoreT*>(raw_ptr);
}

template <typename CoreT>
void destroy_instance(void** tagged_instance_ptr, OrgContext* ctx) {
    clear_context(ctx);
    try {
        if (!tagged_instance_ptr || !*tagged_instance_ptr) { return; }
        void*        tagged_instance = *tagged_instance_ptr;
        MemoryPolicy policy          = get_pointer_policy(tagged_instance);
        void*        raw_ptr         = untag_pointer(tagged_instance);

        if (policy == MemoryPolicy::Shared) {
            delete static_cast<std::shared_ptr<CoreT>*>(raw_ptr);
        } else if (policy == MemoryPolicy::Unique) {
            delete static_cast<CoreT*>(raw_ptr);
        }

        *tagged_instance_ptr = nullptr;
    } catch (std::exception const& e) {
        set_context_error(ctx, e.what());
    } catch (...) {
        set_context_error(ctx, "Unknown exception during destroy");
    }
}

template <typename T>
struct VTable {
    static void const* get_vtable() { return nullptr; }
};

template <typename T>
concept IsCWrapped = requires(T t) {
    requires std::same_as<decltype(t.data), haxorg_ptr_payload>;
};

template <typename T>
concept IsExactlyValue = std::same_as<std::remove_cvref_t<T>, T>;

template <typename CppType, typename CType>
struct ArgUnwrapper;

// Fallback for primitives passed as-is (e.g., int, double)
template <typename CppType, typename CType>
struct ArgUnwrapper {
    static CppType unwrap(OrgContext* ctx, CType val) { return val; }
};

template <typename CppType, typename CType>
struct ArgUnwrapper<CppType&, CType> {
    static CppType& unwrap(OrgContext* ctx, CType val) {
        return *unwrap_instance<CppType>(ctx, val.data);
    }
};

template <typename CppType, typename CType>
struct ArgUnwrapper<CppType const&, CType> {
    static CppType const& unwrap(OrgContext* ctx, CType val) {
        return *unwrap_instance<CppType>(ctx, val.data);
    }
};

template <IsExactlyValue CppType, IsCWrapped CType>
struct ArgUnwrapper<CppType, CType> {
    static CppType const& unwrap(OrgContext* ctx, CType val) {
        return *unwrap_instance<CppType>(ctx, val.data);
    }
};

template <typename CppType, typename CType>
struct ArgUnwrapper<std::shared_ptr<CppType>, CType> {
    static std::shared_ptr<CppType> const& unwrap(
        OrgContext* ctx,
        CType       val) {
        return *unwrap_instance<std::shared_ptr<CppType>>(ctx, val.data);
    }
};


template <typename CppType, typename CType>
struct ArgUnwrapper<org::sem::SemId<CppType>, CType> {
    static org::sem::SemId<CppType> const& unwrap(
        OrgContext* ctx,
        CType       val) {
        return *unwrap_instance<org::sem::SemId<CppType>>(ctx, val.data);
    }
};


template <typename CppType, IsCWrapped CType>
struct ArgUnwrapper<CppType, CType> {
    static CppType unwrap(OrgContext* ctx, CType val) {
        return unwrap_instance<CppType>(ctx, val.data);
    }
};

template <hstd::IsEnum CppType, hstd::IsEnum CType>
struct ArgUnwrapper<CppType, CType> {
    static CppType unwrap(OrgContext*, CType val) {
        return static_cast<CppType>(val);
    }
};

template <typename T>
struct ExtractCoreType {
    using Type = T;
};
template <typename T>
struct ExtractCoreType<std::shared_ptr<T>> {
    using Type = T;
};


template <typename CType, typename CppRetT>
struct ResultTypeBuilder {
    using CoreT = typename ExtractCoreType<std::decay_t<CppRetT>>::Type;
    static CType build(void* t) {
        return {haxorg_ptr_payload{
            .data   = t,
            .vtable = VTable<CppRetT>::get_vtable(),
        }};
    }
    static CType build_null() { return {haxorg_ptr_payload{}}; }
};


namespace detail {

// Trait to infer MemoryPolicy from a C++ return type
template <typename T>
struct InferMemoryPolicy {
    static constexpr MemoryPolicy value = MemoryPolicy::Unique;
};

template <typename T>
struct InferMemoryPolicy<std::shared_ptr<T>> {
    static constexpr MemoryPolicy value = MemoryPolicy::Shared;
};

template <typename T>
struct InferMemoryPolicy<T const&> {
    static constexpr MemoryPolicy value = MemoryPolicy::Reference;
};

template <typename T>
struct InferMemoryPolicy<T&> {
    static constexpr MemoryPolicy value = MemoryPolicy::Reference;
};

template <
    typename ResultCType,
    typename ResultCppType,
    typename CppCallable,
    typename... CppArgs,
    typename... CArgs>
ResultCType execute_cpp_impl(
    CppCallable const& callable,
    OrgContext*        ctx,
    CArgs... c_args) {
    constexpr MemoryPolicy
        Policy = InferMemoryPolicy<ResultCppType>::value;
    clear_context(ctx);
    constexpr bool
        IsPassthrough = std::is_same_v<
                            std::remove_cvref_t<ResultCType>,
                            std::remove_cvref_t<ResultCppType>>
                     || std::is_enum_v<std::remove_cvref_t<ResultCppType>>;
    try {
        if constexpr (std::is_same_v<ResultCType, void>) {
            callable(ArgUnwrapper<CppArgs, CArgs>::unwrap(ctx, c_args)...);
            return;
        } else {
            decltype(auto) result = callable(
                ArgUnwrapper<CppArgs, CArgs>::unwrap(ctx, c_args)...);
            if constexpr (IsPassthrough) {
                return static_cast<ResultCType>(result);
            } else {
                void* raw_ptr = nullptr;

                if constexpr (
                    Policy == MemoryPolicy::Unique
                    || Policy == MemoryPolicy::Shared) {
                    using DecayedT = std::decay_t<decltype(result)>;
                    raw_ptr        = new DecayedT(
                        std::forward<decltype(result)>(result));
                } else if constexpr (Policy == MemoryPolicy::Reference) {
                    raw_ptr = (void*)(&result);
                }

                void* tagged_ptr = tag_pointer(raw_ptr, Policy);
                return ResultTypeBuilder<ResultCType, ResultCppType>::
                    build(tagged_ptr);
            }
        }
    } catch (std::exception const& e) {
        set_context_error(ctx, e.what());
        if constexpr (IsPassthrough) {
            return ResultCType{};
        } else if constexpr (!std::is_same_v<ResultCType, void>) {
            return ResultTypeBuilder<ResultCType, ResultCppType>::
                build_null();
        }
    } catch (...) {
        set_context_error(ctx, "Unknown C++ exception");
        if constexpr (IsPassthrough) {
            return ResultCType{};
        } else if constexpr (!std::is_same_v<ResultCType, void>) {
            return ResultTypeBuilder<ResultCType, ResultCppType>::
                build_null();
        }
    }
}

} // namespace detail

// Free function overload
template <
    typename ResultCType,
    typename ResultCppType,
    typename... CppArgs,
    typename... CArgs>
ResultCType execute_cpp(
    ResultCppType (*func)(CppArgs...),
    OrgContext* ctx,
    CArgs... c_args) {
    return detail::execute_cpp_impl<
        ResultCType,
        ResultCppType,
        decltype(func),
        CppArgs...>(func, ctx, c_args...);
}

// Non-const member function overload
template <
    typename ResultCType,
    typename Class,
    typename ResultCppType,
    typename... CppArgs,
    typename CFirstArg,
    typename... CArgs>
ResultCType execute_cpp(
    ResultCppType (Class::*method)(CppArgs...),
    OrgContext* ctx,
    CFirstArg   c_self,
    CArgs... c_args) {
    Class& self_ref = ArgUnwrapper<Class&, CFirstArg>::unwrap(ctx, c_self);
    auto   bound    = [&self_ref,
                       method](CppArgs... cpp_args) -> ResultCppType {
        return (self_ref.*method)(std::forward<CppArgs>(cpp_args)...);
    };
    return detail::execute_cpp_impl<
        ResultCType,
        ResultCppType,
        decltype(bound),
        CppArgs...>(std::move(bound), ctx, c_args...);
}

// Const member function overload
template <
    typename ResultCType,
    typename Class,
    typename ResultCppType,
    typename... CppArgs,
    typename CFirstArg,
    typename... CArgs>
ResultCType execute_cpp(
    ResultCppType (Class::*method)(CppArgs...) const,
    OrgContext* ctx,
    CFirstArg   c_self,
    CArgs... c_args) {
    Class const& self_ref = ArgUnwrapper<const Class&, CFirstArg>::unwrap(
        ctx, c_self);
    auto bound = [&self_ref,
                  method](CppArgs... cpp_args) -> ResultCppType {
        return (self_ref.*method)(std::forward<CppArgs>(cpp_args)...);
    };
    return detail::execute_cpp_impl<
        ResultCType,
        ResultCppType,
        decltype(bound),
        CppArgs...>(std::move(bound), ctx, c_args...);
}


template <typename BaseType, typename WrappedType>
void execute_destroy(OrgContext* ctx, WrappedType* type) {
    delete unwrap_instance<BaseType>(ctx, type->data);
    type->data.data = nullptr;
}


} // namespace org::bind::c
