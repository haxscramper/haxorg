#pragma once

#include <hstd/stdlib/ColText.hpp>
#include <hstd/stdlib/ColTextFormatter.hpp>

namespace hstd {

enum class hshow_verbosity : u8
{
    Minimal,
    Normal,
    Verbose,
    DataDump,
};

BOOST_DESCRIBE_ENUM(hshow_verbosity, Minimal, Normal, Verbose, DataDump);

#define hshow_flag_list(__impl, __sep)                                    \
    __impl(colored) __sep __impl(show_list_index)                         \
    __sep                 __impl(unicode_newlines)                        \
    __sep                 __impl(with_ranges)                             \
    __sep                 __impl(spell_empty_string)                      \
    __sep                 __impl(use_bin)                                 \
    __sep                 __impl(use_decimal)                             \
    __sep                 __impl(use_hex)                                 \
    __sep                 __impl(trim_prefix_zeros)                       \
    __sep                 __impl(split_numbers)                           \
    __sep                 __impl(use_commas)                              \
    __sep                 __impl(use_quotes)                              \
    __sep                 __impl(use_ascii)                               \
    __sep                 __impl(string_as_array)


enum class hshow_flag : u8
{
#define __ident(a) a
#define __comma ,
    hshow_flag_list(__ident, __comma)
#undef __ident
#undef __comma
};


BOOST_DESCRIBE_ENUM_BEGIN(hshow_flag)
#define __ident(a) BOOST_DESCRIBE_ENUM_ENTRY(hshow_flag, a)
#define __nop
hshow_flag_list(__ident, __nop)
#undef __ident
#undef __nop
    BOOST_DESCRIBE_ENUM_END(hshow_flag);


struct hshow_opts {
    IntSet<hshow_flag> flags = IntSet<hshow_flag>{
        hshow_flag::colored,
        hshow_flag::show_list_index,
        hshow_flag::spell_empty_string,
        hshow_flag::use_commas,
        hshow_flag::use_quotes,
        hshow_flag::trim_prefix_zeros,
    };

    int  indent      = 0;
    int  max_depth   = 120;
    int  max_len     = 320;
    bool quoteIdents = false; /// Add quotes around stings that are valid
                              /// identifirers
    hshow_verbosity verbosity = hshow_verbosity::Normal;

#define __flag_method(a)                                                  \
    hshow_opts& with_##a(bool set) { return cond(hshow_flag::a, set); }   \
    bool        get_##a() const { return flags.contains(hshow_flag::a); }
#define __nop

    hshow_flag_list(__flag_method, __nop)

#undef __flag_method
#undef __nop
        ;

    hshow_opts& cond(hshow_flag flag, bool doAdd);

    hshow_opts& incl(hshow_flag flag);
    hshow_opts& excl(hshow_flag flag);
    hshow_opts& with(IntSet<hshow_flag> flag);
};


// aux template to allow partial template specialization with concept
// constraints
template <typename T, typename Aux = int>
struct hshow {};

template <StdFormattable T>
struct hshow_std_format {
    static void format(ColStream& s, CR<T> value, CR<hshow_opts> opts) {
        s << std::format("{}", value);
    }
};


template <typename T>
ColText hshow1(CR<T> value, CR<hshow_opts> opts = hshow_opts{}) {
    ColStream s;
    hshow<T>::format(s, value, opts);
    return s.getBuffer();
}


template <typename T>
void hshow_ctx(ColStream& os, CR<T> value, CR<hshow_opts> opts) {
    hshow<T>::format(os, value, opts);
}

template <typename T>
struct hshow_integral_type {
    static void format(ColStream& s, CR<T> value, CR<hshow_opts> opts) {
        s << s.blue();
        if (opts.get_use_hex()) {
            s << std::format("{:X}", value);
        } else if (opts.get_use_bin()) {
            s << std::format("{:B}", value);
        } else {
            s << std::format("{}", value);
        }
        s << s.end();
    }
};

template <DescribedRecord R>
struct hshow_described_record {
    static void format(ColStream& s, CR<R> value, CR<hshow_opts> opts) {
        bool first = true;
        s << "{";
        for_each_field_value_with_bases(
            value, [&](char const* name, auto const& value) {
                if (!first) { s << ", "; }
                s << ".";
                s.cyan();
                s << name;
                s.end();
                s << " = ";
                hshow_ctx(s, value, opts);
                first = false;
            });
        s << "}";
    }
};

template <DescribedEnum E>
struct hshow_described_enum {
    static void format(ColStream& s, E value, CR<hshow_opts> opts) {
        char const* string = ::boost::describe::enum_to_string(
            value, nullptr);
        if (string == nullptr) {
            s.red();
            s << fmt("{} (invalid)", std::to_underlying(value));
            s.end();
        } else {
            s.green();
            s << string;
            s.end();
        }
    }
};

template <typename T>
struct hshow_indexed_list {
    static void format(ColStream& s, CR<T> value, CR<hshow_opts> opts) {
        int idx = 0;
        s << "[";
        for (auto const& it : value) {
            if (idx != 0) {
                if (opts.get_use_commas()) {
                    s << ", ";
                } else {
                    s << " ";
                }
            }

            if (opts.get_show_list_index()) { s << fmt("[{}]:", idx); }

            hshow_ctx(s, it, opts);
            ++idx;
        }
        s << "]";
    }
};

template <typename T>
struct hshow_unordered_set {
    static void format(ColStream& s, CR<T> value, CR<hshow_opts> opts) {
        int idx = 0;
        s << "{";
        for (auto const& it : value) {
            if (idx != 0) {
                if (opts.get_use_commas()) {
                    s << ", ";
                } else {
                    s << " ";
                }
            }

            hshow_ctx(s, it, opts);
            ++idx;
        }
        s << "}";
    }
};

template <typename T>
struct hshow_key_value_pairs {
    static void format(ColStream& s, CR<T> value, CR<hshow_opts> opts) {
        int idx = 0;
        s << "{";
        for (auto const& [key, value] : value) {
            if (idx != 0) {
                if (opts.get_use_commas()) {
                    s << ", ";
                } else {
                    s << " ";
                }
            }

            hshow_ctx(s, key, opts);
            s << ": ";
            hshow_ctx(s, value, opts);
            ++idx;
        }
        s << "}";
    }
};

// clang-format off
template <> struct hshow<char> : public hshow_std_format<char> {};
template <> struct hshow<i8> : public hshow_integral_type<i8> {};
template <> struct hshow<u8> : public hshow_integral_type<u8> {};
template <> struct hshow<i16> : public hshow_integral_type<i16> {};
template <> struct hshow<u16> : public hshow_integral_type<u16> {};
template <> struct hshow<i32> : public hshow_integral_type<i32> {};
template <> struct hshow<u32> : public hshow_integral_type<u32> {};
template <> struct hshow<i64> : public hshow_integral_type<i64> {};
template <> struct hshow<u64> : public hshow_integral_type<u64> {};
template <DescribedRecord R> struct hshow<R> : public hshow_described_record<R> {};
template <DescribedEnum E> struct hshow<E> : public hshow_described_enum<E> {};
template <typename T> struct hshow<Vec<T>> : public hshow_indexed_list<Vec<T>> {};
template <typename T> struct hshow<std::vector<T>> : public hshow_indexed_list<std::vector<T>> {};
template <typename T, int Size> struct hshow<SmallVec<T, Size>> : public hshow_indexed_list<SmallVec<T, Size>> {};
template <typename T> struct hshow<IntSet<T>> : public hshow_unordered_set<IntSet<T>> {};
// clang-format on


template <>
struct hshow<std::string_view> {
    static void format(
        ColStream&           os,
        CR<std::string_view> value,
        CR<hshow_opts>       opts);
};

template <>
struct hshow<char const*> {
    static void format(
        ColStream&     os,
        char const*    value,
        CR<hshow_opts> opts) {
        hshow<std::string_view>::format(os, value, opts);
    }
};

template <>
struct hshow<std::string> {
    static void format(
        ColStream&      os,
        CR<std::string> value,
        CR<hshow_opts>  opts) {
        hshow<std::string_view>::format(os, value, opts);
    }
};

template <>
struct hshow<Str> {
    static void format(ColStream& os, CR<Str> value, CR<hshow_opts> opts) {
        hshow<std::string_view>::format(os, value.toBase(), opts);
    }
};


template <>
struct hshow<char*> {
    static void format(ColStream& os, char* value, CR<hshow_opts> opts) {
        hshow<std::string_view>::format(os, value, opts);
    }
};

template <int N>
struct hshow<char[N]> {
    static void format(
        ColStream&     os,
        char const*    value,
        CR<hshow_opts> opts) {
        hshow<std::string_view>::format(os, value, opts);
    }
};

template <int N>
struct hshow<char const[N]> {
    static void format(
        ColStream&     os,
        char const     value[N],
        CR<hshow_opts> opts) {
        hshow<std::string_view>::format(os, value, opts);
    }
};

} // namespace hstd
