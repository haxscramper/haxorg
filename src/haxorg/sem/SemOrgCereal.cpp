#include "SemOrgCereal.hpp"

#include <cereal/types/unordered_map.hpp>
#include <cereal/types/vector.hpp>
#include <cereal/types/variant.hpp>
#include <cereal/archives/portable_binary.hpp>
#include <cereal/archives/binary.hpp>
#include <cereal/archives/xml.hpp>
#include <cereal/archives/json.hpp>
#include <cereal/types/string.hpp>
#include <hstd/system/reflection.hpp>

int level = 0;

// #define __trace_call()                                                    \
//     std::cerr << fmt(                                                     \
//         "{}Calling {}", hstd::Str{level++, ' '}, __PRETTY_FUNCTION__)     \
//               << std::endl;                                               \
//     auto __scope = hstd::finally{[&]() { --level; }};

#define __trace_call()

using namespace org::imm;

template <typename T>
struct OrgCereal {};

template <typename T>
concept HasOrgCerealSpecialization //
    = requires { typename OrgCereal<T>; }
   && requires(
          cereal::BinaryOutputArchive&         bin_out,
          cereal::BinaryInputArchive&          bin_in,
          cereal::PortableBinaryOutputArchive& pbin_out,
          cereal::PortableBinaryInputArchive&  pbin_in,
          cereal::JSONOutputArchive&           json_out,
          cereal::JSONInputArchive&            json_in,
          cereal::XMLOutputArchive&            xml_out,
          cereal::XMLInputArchive&             xml_in,
          T const&                             const_value,
          T&                                   value) {
          {
              OrgCereal<T>::save(bin_out, const_value)
          } -> std::same_as<void>;
          { OrgCereal<T>::load(bin_in, value) } -> std::same_as<void>;
          {
              OrgCereal<T>::save(pbin_out, const_value)
          } -> std::same_as<void>;
          { OrgCereal<T>::load(pbin_in, value) } -> std::same_as<void>;
          {
              OrgCereal<T>::save(json_out, const_value)
          } -> std::same_as<void>;
          { OrgCereal<T>::load(json_in, value) } -> std::same_as<void>;
          {
              OrgCereal<T>::save(xml_out, const_value)
          } -> std::same_as<void>;
          { OrgCereal<T>::load(xml_in, value) } -> std::same_as<void>;
      };

template <typename Archive, typename T>
void org_cereal_save(Archive& archive, T const& value) {
    OrgCereal<T>::save(archive, value);
}

template <typename Archive, typename T>
void org_cereal_load(Archive& archive, T& value) {
    OrgCereal<T>::load(archive, value);
}


template <hstd::IsEnum E>
struct OrgCereal<E> {
    template <typename Archive>
    static void save(Archive& archive, E const& id) {
        __trace_call();
        org_cereal_save(
            archive, static_cast<std::underlying_type_t<E>>(id));
    }

    template <typename Archive>
    static void load(Archive& archive, E& id) {
        __trace_call();
        std::underlying_type_t<E> value;
        org_cereal_load(archive, value);
        id = static_cast<E>(value);
    }
};

template <>
struct OrgCereal<cctz::time_zone> {
    template <typename Archive>
    static void save(Archive& archive, cctz::time_zone const& zone) {
        __trace_call();
        org_cereal_save(archive, zone.name());
    }

    template <typename Archive>
    static void load(Archive& archive, cctz::time_zone& id) {
        __trace_call();
        std::string name;
        org_cereal_load(archive, name);
        cctz::load_time_zone(name, &id);
    }
};

template <>
struct OrgCereal<cctz::civil_second> {
    template <typename Archive>
    static void save(Archive& archive, cctz::civil_second const& time) {
        __trace_call();
        org_cereal_save(archive, time.year());
        org_cereal_save(archive, time.month());
        org_cereal_save(archive, time.day());
        org_cereal_save(archive, time.hour());
        org_cereal_save(archive, time.minute());
        org_cereal_save(archive, time.second());
    }

    template <typename Archive>
    static void load(Archive& archive, cctz::civil_second& time) {
        __trace_call();
        int year{};
        int month{};
        int day{};
        int hour{};
        int minute{};
        int second{};
        org_cereal_load(archive, year);
        org_cereal_load(archive, month);
        org_cereal_load(archive, day);
        org_cereal_load(archive, hour);
        org_cereal_load(archive, minute);
        org_cereal_load(archive, second);
        time = cctz::civil_second{year, month, day, hour, minute, second};
    }
};


template <>
struct OrgCereal<org::imm::ImmId> {
    template <typename Archive>
    static void save(Archive& archive, org::imm::ImmId const& id) {
        __trace_call();
        org_cereal_save(archive, id.getValue());
    }

    template <typename Archive>
    static void load(Archive& archive, org::imm::ImmId& id) {
        __trace_call();
        org::imm::ImmId::IdType id_value{};
        org_cereal_load(archive, id_value);
        id = org::imm::ImmId::FromValue(id_value);
    }
};

#define CEREAL_TRIVIAL_BUILTIN(__type)                                    \
    template <>                                                           \
    struct OrgCereal<__type> {                                            \
        template <typename Archive>                                       \
        static void save(Archive& archive, __type const& id) {            \
            __trace_call();                                               \
            archive(id);                                                  \
        }                                                                 \
                                                                          \
        template <typename Archive>                                       \
        static void load(Archive& archive, __type& id) {                  \
            __trace_call();                                               \
            archive(id);                                                  \
        }                                                                 \
    };

CEREAL_TRIVIAL_BUILTIN(int);
CEREAL_TRIVIAL_BUILTIN(float);
CEREAL_TRIVIAL_BUILTIN(hstd::u64);
CEREAL_TRIVIAL_BUILTIN(bool);
CEREAL_TRIVIAL_BUILTIN(std::string);
CEREAL_TRIVIAL_BUILTIN(std::size_t);
CEREAL_TRIVIAL_BUILTIN(short);
CEREAL_TRIVIAL_BUILTIN(unsigned short);
CEREAL_TRIVIAL_BUILTIN(long);

template <>
struct OrgCereal<hstd::Str> {
    template <typename Archive>
    static void save(Archive& archive, hstd::Str const& id) {
        __trace_call();
        org_cereal_save<Archive, std::string>(archive, id.toBase());
    }

    template <typename Archive>
    static void load(Archive& archive, hstd::Str& id) {
        __trace_call();
        org_cereal_load<Archive, std::string>(archive, id);
    }
};

template <typename T>
struct OrgCereal<org::imm::ImmIdT<T>> {
    template <typename Archive>
    static void save(Archive& archive, org::imm::ImmIdT<T> const& id) {
        __trace_call();
        org_cereal_save(archive, id.getValue());
    }

    template <typename Archive>
    static void load(Archive& archive, org::imm::ImmIdT<T>& id) {
        __trace_call();
        typename org::imm::ImmIdT<T>::IdType id_value{};
        org_cereal_load(archive, id_value);
        id = org::imm::ImmIdT<T>::FromValue(id_value);
    }
};
template <typename... Args>
struct OrgCereal<std::variant<Args...>> {
    using VT = std::variant<Args...>;
    template <typename Archive>
    static void save(Archive& archive, VT const& id) {
        __trace_call();
        org_cereal_save(archive, id.index());
        std::visit(
            [&](auto const& it) { org_cereal_save(archive, it); }, id);
    }

    template <typename Archive>
    static void load(Archive& archive, VT& id) {
        __trace_call();
        int index{};
        org_cereal_load(archive, index);
        VT result = hstd::variant_from_index<VT>(index);
        std::visit(
            [&](auto& out) { org_cereal_load(archive, out); }, result);
    }
};


template <typename T>
struct OrgCereal<std::optional<T>> {
    template <typename Archive>
    static void save(Archive& archive, std::optional<T> const& value) {
        __trace_call();
        if (value) {
            org_cereal_save(archive, true);
            org_cereal_save(archive, value.value());
        } else {
            org_cereal_save(archive, false);
        }
    }

    template <typename Archive>
    static void load(Archive& archive, std::optional<T>& value) {
        __trace_call();
        bool has_value;
        org_cereal_load(archive, has_value);
        if (has_value) {
            value = hstd::SerdeDefaultProvider<T>::get();
            org_cereal_load(archive, *value);
        } else {
            value = std::nullopt;
        }
    }
};

template <typename T>
struct OrgCereal<immer::box<T>> {
    template <typename Archive>
    static void save(Archive& archive, immer::box<T> const& value) {
        __trace_call();
        org_cereal_save(archive, value.get());
    }

    template <typename Archive>
    static void load(Archive& archive, immer::box<T>& value) {
        __trace_call();
        T tmp = hstd::SerdeDefaultProvider<T>::get();
        org_cereal_load(archive, tmp);
        value = tmp;
    }
};

template <typename T>
struct OrgCereal<immer::flex_vector<T>> {
    template <typename Archive>
    static void save(
        Archive&                     archive,
        immer::flex_vector<T> const& value) {
        __trace_call();
        archive(cereal::make_size_tag(value.size()));
        for (auto const& it : value) { archive(it); }
    }

    template <typename Archive>
    static void load(Archive& archive, immer::flex_vector<T>& value) {
        __trace_call();
        immer::flex_vector_transient<T> tmp  = value.transient();
        int                             size = 0;
        archive(size);
        for (int i = 0; i < size; ++i) {
            if constexpr (std::is_default_constructible_v<T>) {
                T tmp_value{};
                org_cereal_load(archive, tmp_value);
                tmp.push_back(tmp_value);
            } else {
                T tmp_value = hstd::SerdeDefaultProvider<T>::get();
                org_cereal_load(archive, tmp_value);
                tmp.push_back(tmp_value);
            }
        }
        value = tmp.persistent();
    }
};

template <typename T, typename Container>
struct OrgCerealIterableSequence {
    template <typename Archive>
    static void save(Archive& archive, Container const& value) {
        __trace_call();
        archive(cereal::make_size_tag(value.size()));
        for (auto const& it : value) { org_cereal_save(archive, it); }
    }

    template <typename Archive>
    static void load(Archive& archive, Container& value) {
        __trace_call();
        int size = 0;
        archive(size);

        if constexpr (std::is_default_constructible_v<T>) {
            value.resize(size);
        } else {
            value.resize(size, hstd::SerdeDefaultProvider<T>::get());
        }

        for (auto& it : value) { org_cereal_load(archive, it); }
    }
};

template <typename T>
struct OrgCereal<hstd::Vec<T>>
    : public OrgCerealIterableSequence<T, hstd::Vec<T>> {};

template <typename T, int Size>
struct OrgCereal<hstd::SmallVec<T, Size>>
    : public OrgCerealIterableSequence<T, hstd::SmallVec<T, Size>> {};

template <typename K, typename V>
struct OrgCereal<immer::map<K, V>> {
    template <typename Archive>
    static void save(Archive& archive, immer::map<K, V> const& map) {
        __trace_call();
        archive(cereal::make_size_tag(static_cast<int>(map.size())));
        for (auto const& [key, value] : map) {
            org_cereal_save(archive, key);
            org_cereal_save(archive, value);
        }
    }

    template <typename Archive>
    static void load(Archive& archive, immer::map<K, V>& map) {
        __trace_call();
        int  size = 0;
        auto tmp  = map.transient();
        archive(cereal::make_size_tag(size));
        for (int i = 0; i < size; ++i) {
            K key   = hstd::SerdeDefaultProvider<K>::get();
            V value = hstd::SerdeDefaultProvider<V>::get();
            org_cereal_load(archive, key);
            org_cereal_load(archive, value);
            map.set(key, value);
        }
        map = tmp.persistent();
    }
};

template <typename K, typename V>
struct OrgCereal<hstd::ext::ImmMap<K, V>> {
    template <typename Archive>
    static void save(
        Archive&                       archive,
        hstd::ext::ImmMap<K, V> const& map) {
        __trace_call();
        OrgCereal<immer::map<K, V>>::save(archive, map);
    }

    template <typename Archive>
    static void load(Archive& archive, hstd::ext::ImmMap<K, V>& map) {
        __trace_call();
        OrgCereal<immer::map<K, V>>::load(archive, map);
    }
};

template <typename K, typename V>
struct OrgCereal<std::unordered_map<K, V>> {
    template <typename Archive>
    static void save(
        Archive&                        archive,
        std::unordered_map<K, V> const& map) {
        __trace_call();
        archive(cereal::make_size_tag(static_cast<int>(map.size())));
        for (auto const& [key, value] : map) {
            org_cereal_save(archive, key);
            org_cereal_save(archive, value);
        }
    }

    template <typename Archive>
    static void load(Archive& archive, std::unordered_map<K, V>& map) {
        __trace_call();
        int size = 0;
        archive(cereal::make_size_tag(size));
        for (int i = 0; i < size; ++i) {
            K key   = hstd::SerdeDefaultProvider<K>::get();
            V value = hstd::SerdeDefaultProvider<V>::get();
            org_cereal_load(archive, key);
            org_cereal_load(archive, value);
            map.insert_or_assign(key, value);
        }
    }
};

template <typename K, typename V>
struct OrgCereal<hstd::UnorderedMap<K, V>> {
    template <typename Archive>
    static void save(
        Archive&                        archive,
        hstd::UnorderedMap<K, V> const& value) {
        __trace_call();
        OrgCereal<std::unordered_map<K, V>>::save(archive, value);
    }

    template <typename Archive>
    static void load(Archive& archive, hstd::UnorderedMap<K, V>& value) {
        __trace_call();
        OrgCereal<std::unordered_map<K, V>>::load(archive, value);
    }
};

template <hstd::dod::IsIdType Id, typename T>
struct OrgCereal<hstd::dod::Store<Id, T>> {
    template <typename Archive>
    static void save(
        Archive&                       archive,
        hstd::dod::Store<Id, T> const& value) {
        __trace_call();
        org_cereal_save(archive, value.content);
    }

    template <typename Archive>
    static void load(Archive& archive, hstd::dod::Store<Id, T>& value) {
        __trace_call();
        org_cereal_load(archive, value.content);
    }
};

template <hstd::DescribedRecord T>
struct OrgCereal<T> {
    template <typename Archive>
    static void save(Archive& archive, T const& value) {
        __trace_call();
        hstd::for_each_field_value_with_bases(
            value, [&](char const*, auto const& field) {
                org_cereal_save(archive, field);
            });
    }

    template <typename Archive>
    static void load(Archive& archive, T& value) {
        __trace_call();
        hstd::for_each_field_value_with_bases(
            value, [&](char const*, auto& field) {
                org_cereal_load(archive, field);
            });
    }
};

template <org::imm::IsImmOrgValueType T>
struct OrgCereal<ImmAstKindStore<T>> {
    template <typename Archive>
    static void save(Archive& archive, ImmAstKindStore<T> const& value) {
        __trace_call();
        archive(CEREAL_NVP_("content", value.values.content));
        archive(CEREAL_NVP_("id_map", value.values.id_map));
    }

    template <typename Archive>
    static void load(Archive& archive, ImmAstKindStore<T>& value) {
        __trace_call();
        org_cereal_load(archive, value.values.content);
        org_cereal_load(archive, value.values.id_map);
    }
};

template <>
struct OrgCereal<ImmAstStore> {
    template <typename Archive>
    static void save(Archive& archive, ImmAstStore const& value) {
        __trace_call();
#define _kind(__Kind)                                                     \
    OrgCereal<ImmAstKindStore<Imm##__Kind>>::save(                        \
        archive, value.store##__Kind);
        EACH_SEM_ORG_KIND(_kind);
#undef _kind
    };

    template <typename Archive>
    static void load(Archive& archive, ImmAstStore& value) {
        __trace_call();
#define _kind(__Kind)                                                     \
    OrgCereal<ImmAstKindStore<Imm##__Kind>>::load(                        \
        archive, value.store##__Kind);
        EACH_SEM_ORG_KIND(_kind);
#undef _kind
    };
};

template <>
struct OrgCereal<std::shared_ptr<ImmAstContext>> {
    template <typename Archive>
    static void save(
        Archive&                              archive,
        std::shared_ptr<ImmAstContext> const& value) {
        org_cereal_save(archive, *value->store);
        org_cereal_save(archive, *value->currentTrack);
    }

    template <typename Archive>
    static void load(
        Archive&                        archive,
        std::shared_ptr<ImmAstContext>& value) {
        org_cereal_load(archive, *value->store);
        org_cereal_load(archive, *value->currentTrack);
    }
};

namespace cereal {
template <class Archive, HasOrgCerealSpecialization T>
void save(Archive& archive, T const& value) {
    __trace_call();
    OrgCereal<T>::save(archive, value);
}

template <class Archive, HasOrgCerealSpecialization T>
void load(Archive& archive, T& value) {
    OrgCereal<T>::load(archive, value);
}
} // namespace cereal


std::string org::imm::serializeToPortableBinary(
    const std::shared_ptr<ImmAstContext>& store) {
    std::ostringstream                  oss{std::ios::binary};
    cereal::PortableBinaryOutputArchive archive{oss};
    org_cereal_save(archive, store);
    return oss.str();
}

void org::imm::readFromPortableBinary(
    std::string const&              binary,
    std::shared_ptr<ImmAstContext>& store) {
    std::istringstream                 iss{binary};
    cereal::PortableBinaryInputArchive archive{iss};
    org_cereal_load<
        cereal::PortableBinaryInputArchive,
        std::shared_ptr<ImmAstContext>>(archive, store);
}

std::string org::imm::serializeToJSON(
    const std::shared_ptr<ImmAstContext>& store) {

    {
        std::ofstream             oss{"/tmp/wip_json_dump.json"};
        cereal::JSONOutputArchive archive{oss};
        org_cereal_save(archive, store);
    }

    std::ostringstream        oss{};
    cereal::JSONOutputArchive archive{oss};
    org_cereal_save(archive, store);
    return oss.str();
}
