#pragma once

#include <boost/mp11/list.hpp>
#include <google/protobuf/any.pb.h>
#include <hstd/ext/hstd_serde.hpp>
#include <hstd/stdlib/Exception.hpp>
#include <hstd/stdlib/Str.hpp>
#include <hstd/stdlib/Vec.hpp>
#include <optional>
#include <ranges>
#include <string>
#include <variant>
#include <vector>

namespace hstd::serde {

namespace detail {

template <typename L>
struct as_mp_list;

template <typename... Ts>
struct as_mp_list<boost::mp11::mp_list<Ts...>> {
    using type = boost::mp11::mp_list<Ts...>; // identity, NOT mp_list<L>
};

template <typename L>
using as_mp_list_t = typename as_mp_list<L>::type;

template <typename T>
struct is_mp_list : std::false_type {};

template <typename... Ts>
struct is_mp_list<boost::mp11::mp_list<Ts...>> : std::true_type {};


} // namespace detail

template <typename... Ts>
concept NoneAreMpLists = (!detail::is_mp_list<std::remove_cvref_t<Ts>>::value && ...);

/// Maps a wrapper protobuf object to its `Any` payload field. Specialize
/// for each wrapper type (e.g. `IAttribute`).
template <typename Proto>
struct DispatchProtoPayload;

template <>
struct DispatchProtoPayload<google::protobuf::Any> {
    static google::protobuf::Any const& getPayload(google::protobuf::Any const& value) {
        return value;
    }
};

namespace detail {

template <NoneAreMpLists... Ts>
std::vector<std::string> expectedPayloadNames(boost::mp11::mp_list<Ts...>) {
    std::vector<std::string> result;
    result.reserve(sizeof...(Ts));
    (result.push_back(std::string{Ts::descriptor()->full_name()}), ...);
    return result;
}

[[noreturn]] inline void throw_unexpected_payload(
    google::protobuf::Any const&    payload,
    std::string const&              owner,
    std::string const&              context,
    std::vector<std::string> const& expected) {
    std::string names;
    for (auto const& e : expected) { names += fmt("\n  type.googleapis.com/{}", e); }
    throw logic_unhandled_kind_error::init(
        fmt("Unexpected payload URL for '{}': '{}'. {}Expected payloads:{}",
            owner,
            payload.type_url(),
            context,
            names));
}

[[noreturn]] inline void throw_missing_payload(
    std::string const&              owner,
    std::vector<std::string> const& expected,
    std::vector<std::string> const& actual) {
    std::string expectedNames;
    for (auto const& e : expected) { expectedNames += fmt("\n  {}", e); }
    std::string actualNames;
    for (auto const& a : actual) { actualNames += fmt("\n  {}", a); }
    throw read_error::init(
        fmt("Could not find required payload in '{}'. Expected one of:{}\n"
            "Has payloads:{}",
            owner,
            expectedNames,
            actualNames));
}

[[noreturn]] inline void throw_duplicate_payload(
    std::string const&              owner,
    std::string const&              matchedType,
    std::vector<std::string> const& expected) {
    throw std::invalid_argument{
        fmt("'{}' contains multiple payloads matching the allowed type list "
            "(second match: '{}')",
            owner,
            matchedType)};
}

template <NoneAreMpLists... Ts>
std::optional<std::variant<Ts...>> tryUnpack(
    google::protobuf::Any const& payload,
    std::string const&           owner,
    boost::mp11::mp_list<Ts...>) {
    std::optional<std::variant<Ts...>> result;
    auto                               tryOne = [&]<typename T>() {
        if (!result && payload.template Is<T>()) {
            T msg;
            if (!payload.UnpackTo(&msg)) {
                throw read_error::init(
                    fmt("Failed to unpack payload '{}' as '{}' in '{}'",
                        payload.type_url(),
                        T::descriptor()->full_name(),
                        owner));
            }
            result = std::variant<Ts...>{std::move(msg)};
        }
    };
    (tryOne.template operator()<Ts>(), ...);
    return result;
}

template <NoneAreMpLists... Ts>
std::optional<std::variant<Ts...>> findUniqueImpl(
    std::ranges::input_range auto&& range,
    std::string const&              owner,
    boost::mp11::mp_list<Ts...>     list) {
    std::optional<std::variant<Ts...>> result;
    for (auto const& item : range) {
        auto const& payload = DispatchProtoPayload<
            std::remove_cvref_t<decltype(item)>>::getPayload(item);
        auto match = tryUnpack(payload, owner, list);
        if (match) {
            if (result) {
                std::visit(
                    [&](auto const& msg) {
                        throw_duplicate_payload(
                            owner,
                            std::string{std::remove_cvref_t<decltype(msg)>::descriptor()
                                            ->full_name()},
                            expectedPayloadNames(list));
                    },
                    *match);
            }
            result = std::move(match);
        }
    }
    return result;
}

} // namespace detail

/// Unpack a single `Any` into a variant of the allowed payload types.
/// Throws `logic_unhandled_kind_error` if the payload matches none.
template <typename List>
auto unpackVariant(
    google::protobuf::Any const& payload,
    std::string const&           owner,
    std::string const&           context = "") {
    auto impl = [&]<typename... Ts>(boost::mp11::mp_list<Ts...> l) {
        auto result = detail::tryUnpack(payload, owner, l);
        if (result) { return std::move(*result); }
        detail::throw_unexpected_payload(
            payload, owner, context, detail::expectedPayloadNames(l));
    };
    return impl(detail::as_mp_list_t<List>{});
}

template <NoneAreMpLists... Ts>
auto unpackVariantT(
    google::protobuf::Any const& payload,
    std::string const&           owner,
    std::string const&           context = "") {
    return unpackVariant<boost::mp11::mp_list<Ts...>>(payload, owner, context);
}

/// Find the unique object in `range` whose payload matches one of the
/// listed types. Returns the unpacked payload, or nullopt if none match.
/// Throws `std::invalid_argument` if more than one object matches.
template <typename List>
auto findUnique(std::ranges::input_range auto&& range, std::string const& owner) {
    auto list = detail::as_mp_list_t<List>{};
    return [&]<NoneAreMpLists... Ts>(boost::mp11::mp_list<Ts...> l) {
        return detail::findUniqueImpl(std::forward<decltype(range)>(range), owner, l);
    }(list);
}

template <NoneAreMpLists... Ts>
auto findUniqueT(std::ranges::input_range auto&& range, std::string const& owner) {
    return findUnique<boost::mp11::mp_list<Ts...>>(
        std::forward<decltype(range)>(range), owner);
}

/// Like `findUnique`, but throws `read_error` when nothing matches.
template <typename List>
auto findUniqueRequired(std::ranges::input_range auto&& range, std::string const& owner) {
    auto result = findUnique<List>(std::forward<decltype(range)>(range), owner);
    if (result) { return std::move(*result); }
    auto                     list = detail::as_mp_list_t<List>{};
    std::vector<std::string> actual;
    for (auto const& item : range) {
        actual.push_back(
            DispatchProtoPayload<std::remove_cvref_t<decltype(item)>>::getPayload(item)
                .type_url());
    }
    detail::throw_missing_payload(owner, detail::expectedPayloadNames(list), actual);
}

template <NoneAreMpLists... Ts>
auto findUniqueRequiredT(
    std::ranges::input_range auto&& range,
    std::string const&              owner) {
    return findUniqueRequired<boost::mp11::mp_list<Ts...>>(
        std::forward<decltype(range)>(range), owner);
}

/// Like `findUnique`, but returns a pointer to the wrapper object in which
/// the matching payload was found (nullptr if none). Throws on duplicates.
template <typename List>
auto findUniqueObject(std::ranges::input_range auto&& range, std::string const& owner) {
    using Item        = std::remove_cvref_t<std::ranges::range_value_t<decltype(range)>>;
    auto        list  = detail::as_mp_list_t<List>{};
    Item const* found = nullptr;
    auto        impl  = [&]<NoneAreMpLists... Ts>(boost::mp11::mp_list<Ts...> l) {
        for (auto const& item : range) {
            auto const& payload = DispatchProtoPayload<Item>::getPayload(item);
            bool        matches = (payload.template Is<Ts>() || ...);
            if (matches) {
                if (found) {
                    detail::throw_duplicate_payload(
                        owner, payload.type_url(), detail::expectedPayloadNames(l));
                }
                found = std::addressof(item);
            }
        }
        return found;
    };
    return impl(list);
}

template <NoneAreMpLists... Ts>
auto findUniqueObjectT(std::ranges::input_range auto&& range, std::string const& owner) {
    return findUniqueObject<boost::mp11::mp_list<Ts...>>(
        std::forward<decltype(range)>(range), owner);
}

/// Like `findUniqueObject`, but throws `read_error` when nothing matches.
template <typename List>
auto findUniqueObjectRequired(
    std::ranges::input_range auto&& range,
    std::string const&              owner) {
    auto result = findUniqueObject<List>(std::forward<decltype(range)>(range), owner);
    if (result) { return result; }
    auto                     list = detail::as_mp_list_t<List>{};
    std::vector<std::string> actual;
    for (auto const& item : range) {
        actual.push_back(
            DispatchProtoPayload<std::remove_cvref_t<
                std::ranges::range_value_t<decltype(range)>>>::getPayload(item)
                .type_url());
    }
    detail::throw_missing_payload(owner, detail::expectedPayloadNames(list), actual);
}

template <NoneAreMpLists... Ts>
auto findUniqueObjectRequiredT(
    std::ranges::input_range auto&& range,
    std::string const&              owner) {
    return findUniqueObjectRequired<boost::mp11::mp_list<Ts...>>(
        std::forward<decltype(range)>(range), owner);
}

} // namespace hstd::serde
