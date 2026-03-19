#pragma once

#include <haxorg/sem/SemOrg.hpp>
#include <haxorg/api/SemBaseApi.hpp>
#include <haxorg/api/ParseContext.hpp>
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
CoreT* unwrap_instance(void* tagged_instance, OrgContext* ctx = nullptr) {
    if (!tagged_instance) {
        set_context_error(ctx, "Instance pointer is null");
        return nullptr;
    }

    MemoryPolicy policy  = get_pointer_policy(tagged_instance);
    void*        raw_ptr = untag_pointer(tagged_instance);

    if (policy == MemoryPolicy::Shared) {
        return static_cast<std::shared_ptr<CoreT>*>(raw_ptr)->get();
    }

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

template <typename CoreT, typename CHandleT>
struct CoreUnwrapper {
    static CoreT* unwrap_ptr(CHandleT handle, OrgContext* ctx) {
        return unwrap_instance<CoreT>(handle.instance, ctx);
    }
    static CoreT& unwrap_ref(CHandleT handle, OrgContext* ctx) {
        CoreT* ptr = unwrap_ptr(handle, ctx);
        if (!ptr) {
            throw std::runtime_error(
                "Attempted to bind null handle to C++ reference/value");
        }
        return *ptr;
    }
};

template <typename CppType, typename CType>
struct ArgUnwrapper;

// Fallback for primitives passed as-is (e.g., int, double)
template <typename CppType, typename CType>
struct ArgUnwrapper {
    static CppType unwrap(CType val, OrgContext*) {
        return static_cast<CppType>(val);
    }
};


template <typename CppRetT>
struct VTable;


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
        return {t, VTable<CppRetT>::get_vtable()};
    }
    static CType build_null() {
        return {nullptr, VTable<CppRetT>::get_vtable()};
    }
};

namespace detail {

template <
    typename ResultCType,
    MemoryPolicy Policy,
    typename Ret,
    typename Callable,
    typename... CppArgs,
    typename... CArgs>
ResultCType execute_cpp_impl(
    Callable&&  callable,
    OrgContext* ctx,
    CArgs... c_args) {
    clear_context(ctx);
    try {
        if constexpr (std::is_same_v<ResultCType, void>) {
            callable(ArgUnwrapper<CppArgs, CArgs>::unwrap(c_args, ctx)...);
            return;
        } else {
            decltype(auto) result = callable(
                ArgUnwrapper<CppArgs, CArgs>::unwrap(c_args, ctx)...);
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
            return ResultTypeBuilder<ResultCType, Ret>::build(tagged_ptr);
        }
    } catch (std::exception const& e) {
        set_context_error(ctx, e.what());
        if constexpr (!std::is_same_v<ResultCType, void>) {
            return ResultTypeBuilder<ResultCType, Ret>::build_null();
        }
    } catch (...) {
        set_context_error(ctx, "Unknown C++ exception");
        if constexpr (!std::is_same_v<ResultCType, void>) {
            return ResultTypeBuilder<ResultCType, Ret>::build_null();
        }
    }
}

} // namespace detail

// Free function overload
template <
    typename ResultCType,
    MemoryPolicy Policy,
    typename Ret,
    typename... CppArgs,
    typename... CArgs>
ResultCType execute_cpp(
    Ret (*func)(CppArgs...),
    OrgContext* ctx,
    CArgs... c_args) {
    return detail::execute_cpp_impl<
        ResultCType,
        Policy,
        Ret,
        decltype(func),
        CppArgs...>(func, ctx, c_args...);
}

// Non-const member function overload
template <
    typename ResultCType,
    MemoryPolicy Policy,
    typename Class,
    typename Ret,
    typename... CppArgs,
    typename CFirstArg,
    typename... CArgs>
ResultCType execute_cpp(
    Ret (Class::*method)(CppArgs...),
    OrgContext* ctx,
    CFirstArg   c_self,
    CArgs... c_args) {
    Class& self_ref = ArgUnwrapper<Class&, CFirstArg>::unwrap(c_self, ctx);
    auto   bound    = [&self_ref, method](CppArgs... cpp_args) -> Ret {
        return (self_ref.*method)(std::forward<CppArgs>(cpp_args)...);
    };
    return detail::execute_cpp_impl<
        ResultCType,
        Policy,
        Ret,
        decltype(bound),
        CppArgs...>(std::move(bound), ctx, c_args...);
}

// Const member function overload
template <
    typename ResultCType,
    MemoryPolicy Policy,
    typename Class,
    typename Ret,
    typename... CppArgs,
    typename CFirstArg,
    typename... CArgs>
ResultCType execute_cpp(
    Ret (Class::*method)(CppArgs...) const,
    OrgContext* ctx,
    CFirstArg   c_self,
    CArgs... c_args) {
    Class const& self_ref = ArgUnwrapper<const Class&, CFirstArg>::unwrap(
        c_self, ctx);
    auto bound = [&self_ref, method](CppArgs... cpp_args) -> Ret {
        return (self_ref.*method)(std::forward<CppArgs>(cpp_args)...);
    };
    return detail::execute_cpp_impl<
        ResultCType,
        Policy,
        Ret,
        decltype(bound),
        CppArgs...>(std::move(bound), ctx, c_args...);
}

template <typename BaseType, typename WrappedType>
void execute_destroy(WrappedType* type) {}


template <typename T>
struct VTable<hstd::Vec<T>> {
    static haxorg_HstdVec_vtable const* vtable_get() {
        using Self = VTable<hstd::Vec<T>>;
        static haxorg_HstdVec_vtable data{
            .size = &Self::size,
        };
        return &data;
    }

    static int size(const haxorg_HstdVec* self, OrgContext* ctx) {
        return execute_cpp(&hstd::Vec<T>::size, self, ctx);
    }

    static T const& back(const haxorg_HstdVec* self, OrgContext* ctx) {
        return execute_cpp(&hstd::Vec<T>::back, self, ctx);
    }

    static void* at(
        const haxorg_HstdVec* self,
        size_t                index,
        OrgContext*           ctx) {
        return execute_cpp(&hstd::Vec<T>::at, self, index, ctx);
    }

    static void pop_back(haxorg_HstdVec* self, OrgContext* ctx) {
        return execute_cpp(&hstd::Vec<T>::at, ctx);
    }

    static void destroy(haxorg_HstdVec* self, OrgContext* ctx) {
        return execute_destroy<hstd::Vec<T>>(self);
    }
};


} // namespace org::bind::c
