#include "semdatastream.hpp"

#include <boost/mp11.hpp>


template <typename Sem>
struct Walker {
    QDataStream& stream;
    bool         isReading;

    template <typename T>
    void visit(T& out) {
        if (isReading) {
            stream >> out;
        } else {
            stream << out;
        }
    }

    template <typename T>
    void visit(T const& in) {
        Q_ASSERT(!isReading);
        stream << in;
    }
};

using namespace boost::describe;
using boost::mp11::mp_for_each;


// QDataStream& operator>>(QDataStream& in, sem::SemIdT<T>& value) {
//     return in;
// }

// QDataStream& operator<<(QDataStream& out, sem::SemIdT<T> const& value) {
//     return out;
// }


template <typename T>
concept DefaultConstructible = std::is_default_constructible_v<T>;

template <typename T>
struct DefaultBuilder {};

template <DefaultConstructible T>
struct DefaultBuilder<T> {
    static T get() { return T{}; }
};

sem::ContextStore* currentContenxt;

template <typename T>
struct DefaultBuilder<sem::SemIdT<T>> {
    static sem::SemIdT<T> get() {
        sem::SemIdT<T> result = sem::SemIdT<T>::Nil();
        result.context        = currentContenxt;
        return result;
    }
};


template <>
struct DefaultBuilder<sem::SemId> {
    static sem::SemId get() {
        sem::SemId result = sem::SemId::Nil();
        result.context    = currentContenxt;
        return result;
    }
};

template <>
struct DefaultBuilder<sem::Subtree::Property> {
    static sem::Subtree::Property get() {
        return sem::Subtree::Property{sem::Subtree::Property::Created{}};
    }
};

template <>
struct DefaultBuilder<sem::Code::Switch> {
    static sem::Code::Switch get() {
        return sem::Code::Switch{sem::Code::Switch::Dedent{}};
    }
};


QDataStream& operator>>(QDataStream& in, sem::SemId& value) {
    in >> value.id;
    return in;
}

QDataStream& operator<<(QDataStream& out, sem::SemId const& value) {
    out << value.id;
    return out;
}

template <typename T>
QDataStream& operator>>(QDataStream& in, Vec<T>& value) {
    int size = 0;
    in >> size;
    value.resize(size, DefaultBuilder<T>::get());
    for (auto& it : value) {
        in >> it;
    }
    return in;
}

template <typename T>
QDataStream& operator<<(QDataStream& out, Vec<T> const& value) {
    out << value.size();
    for (auto const& it : value) {
        out << it;
    }
    return out;
}

template <typename T>
QDataStream& operator>>(QDataStream& in, sem::SemIdT<T>& value) {
    sem::SemId tmp = sem::SemId::Nil();
    in >> tmp;
    value = typename sem::SemIdT<T>(tmp);
    return in;
}

template <typename T>
QDataStream& operator<<(QDataStream& out, sem::SemIdT<T> const& value) {
    out << value.toId();
    return out;
}

template <typename T>
QDataStream& operator<<(QDataStream& out, Opt<T> const& value) {
    out << value.has_value();
    if (value) {
        out << value.value();
    }
    return out;
}

template <typename T>
QDataStream& operator>>(QDataStream& in, Opt<T>& value) {
    bool hasValue = false;
    in >> hasValue;
    if (hasValue) {
        T tmp = DefaultBuilder<T>::get();
        in >> tmp;
        value = tmp;
    }
    return in;
}

template <typename K, typename V>
QDataStream& operator<<(
    QDataStream&              out,
    UnorderedMap<K, V> const& value) {
    out << static_cast<int>(value.size());
    for (auto const& [key, next] : value) {
        out << key;
        out << next;
    }
    return out;
}

template <typename K, typename V>
QDataStream& operator>>(QDataStream& out, UnorderedMap<K, V>& value) {
    return out;
}


template <IsVariant T>
QDataStream& operator<<(QDataStream& out, T const& value) {
    out << static_cast<int>(value.index());
    std::visit([&](auto const& it) { out << it; }, value);
    return out;
}

template <IsVariant T>
QDataStream& operator>>(QDataStream& out, T& value) {


    return out;
}

QDataStream& operator>>(QDataStream& in, UserTime& value) {
    in >> value.time;
    return in;
}

QDataStream& operator<<(QDataStream& out, UserTime const& value) {
    out << value.time;
    return out;
}


template <DescribedRecord T>
QDataStream& operator<<(QDataStream& out, T const& value) {
    mp_for_each<describe_bases<T, mod_any_access>>([&](auto Base) {
        write_value<typename decltype(Base)::type>(out, value);
    });

    mp_for_each<describe_members<T, mod_any_access>>(
        [&](auto const& field) { out << value.*field.pointer; });

    return out;
}

template <DescribedRecord T>
QDataStream& operator>>(QDataStream& out, T& value) {
    using Bd = describe_bases<T, mod_any_access>;
    mp_for_each<Bd>([&](auto Base) {
        read_value<typename decltype(Base)::type>(out, value);
    });

    mp_for_each<describe_members<T, mod_any_access>>(
        [&](auto const& field) { out >> value.*field.pointer; });

    return out;
}

template <typename T>
void write_value(QDataStream& out, T const& value) {
    mp_for_each<describe_bases<T, mod_any_access>>([&](auto Base) {
        write_value<typename decltype(Base)::type>(out, value);
    });

    mp_for_each<describe_members<T, mod_any_access>>(
        [&](auto const& field) { out << value.*field.pointer; });
}

template <typename T>
void read_value(QDataStream& out, T& value) {
    using Bd = describe_bases<T, mod_any_access>;
    mp_for_each<Bd>([&](auto Base) {
        read_value<typename decltype(Base)::type>(out, value);
    });

    mp_for_each<describe_members<T, mod_any_access>>(
        [&](auto const& field) { out >> value.*field.pointer; });
}

template <typename Kind>
void read_store(QDataStream& in, sem::KindStore<Kind>& store) {
    int size = 0;
    in >> size;
    store.values.resize(size);
    for (auto& value : store.values) {
        read_value(in, value);
    }
}

template <typename Kind>
void write_store(QDataStream& out, sem::KindStore<Kind> const& store) {
    out << store.size();
    for (auto const& value : store.values) {
        write_value(out, value);
    }
}

void SemDataStream::read(QDataStream& in, sem::ParseUnitStore& store) {
    int enum_count = 0;
    in >> enum_count;
    for (int i = 0; i < enum_count; ++i) {
        OrgSemKind kind;
        in >> kind;
        switch (kind) {
#define _case(__Kind)                                                     \
    case OrgSemKind::__Kind: {                                            \
        read_store<sem::__Kind>(in, store.store##__Kind);                 \
    }
            EACH_SEM_ORG_KIND(_case)
#undef _case
        }
    }
}

void SemDataStream::write(
    QDataStream&               out,
    const sem::ParseUnitStore& store) {
    int enum_count = 0;
    for (auto const& k : sliceT<OrgSemKind>()) {
        ++enum_count;
    }
    out << enum_count;
    for (auto const& kind : sliceT<OrgSemKind>()) {
        out << kind;
        switch (kind) {

#define _case(__Kind)                                                     \
    case OrgSemKind::__Kind: {                                            \
        write_store<sem::__Kind>(out, store.store##__Kind);               \
    }
            EACH_SEM_ORG_KIND(_case)
#undef _case
        }
    }
}

void SemDataStream::read(QDataStream& in, sem::ContextStore* store) {
    int storeCount;
    in >> storeCount;
    currentContenxt = store;
    store->stores.resize(storeCount, store);
    for (sem::ParseUnitStore& unit : store->stores) {
        read(in, store);
    }
    currentContenxt = nullptr;
}

void SemDataStream::write(
    QDataStream&             out,
    const sem::ContextStore& store) {
    out << store.stores.size();
}
