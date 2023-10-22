//#include "semdatastream.hpp"

//#include <boost/mp11.hpp>


//template <typename Sem>
//struct Walker {
//    QDataStream& stream;
//    bool         isReading;

//    template <typename T>
//    void visit(T& out) {
//        if (isReading) {
//            stream >> out;
//        } else {
//            stream << out;
//        }
//    }

//    template <typename T>
//    void visit(T const& in) {
//        CHECK(!isReading);
//        stream << in;
//    }
//};

//using namespace boost::describe;
//using boost::mp11::mp_for_each;


//// QDataStream& operator>>(QDataStream& in, sem::SemIdT<T>& value) {
////     return in;
//// }

//// QDataStream& operator<<(QDataStream& out, sem::SemIdT<T> const& value) {
////     return out;
//// }

//sem::ContextStore* currentContenxt;

//template <typename T>
//struct SerdeDefaultProvider<sem::SemIdT<T>> {
//    static sem::SemIdT<T> get() {
//        Q_CHECK_PTR(currentContenxt);
//        sem::SemIdT<T> result = sem::SemIdT<T>::Nil();
//        result.context        = currentContenxt;
//        return result;
//    }
//};


//template <>
//struct SerdeDefaultProvider<sem::SemId> {
//    static sem::SemId get() {
//        Q_CHECK_PTR(currentContenxt);
//        sem::SemId result = sem::SemId::Nil();
//        result.context    = currentContenxt;
//        return result;
//    }
//};

//template <>
//struct SerdeDefaultProvider<sem::Subtree::Property> {
//    static sem::Subtree::Property get() {
//        return sem::Subtree::Property{sem::Subtree::Property::Created{}};
//    }
//};

//template <>
//struct SerdeDefaultProvider<sem::SubtreeLog::Priority> {
//    static sem::SubtreeLog::Priority get() {
//        return sem::SubtreeLog::Priority{};
//    }
//};


//// template <>
//// struct SerdeDefaultProvider<sem::Code::Switch> {
////     static sem::Code::Switch get() {
////         return sem::Code::Switch{
////             sem::Code::Switch::Data{sem::Code::Switch::Dedent{}}};
////     }
//// };

//template <>
//struct SerdeDefaultProvider<sem::Code::Switch::LineStart> {
//    static sem::Code::Switch::LineStart get() {
//        return sem::Code::Switch::LineStart{};
//    }
//};


//QDataStream& operator>>(QDataStream& in, sem::SemId& value) {
//    in >> value.id;
//    Q_CHECK_PTR(currentContenxt);
//    value.context = currentContenxt;
//    return in;
//}

//QDataStream& operator<<(QDataStream& out, sem::SemId const& value) {
//    out << value.id;
//    return out;
//}

//template <typename T>
//QDataStream& operator>>(QDataStream& in, Vec<T>& value) {
//    int size = 0;
//    in >> size;
//    value.resize(size, SerdeDefaultProvider<T>::get());
//    for (auto& it : value) {
//        in >> it;
//    }
//    return in;
//}

//template <typename T>
//QDataStream& operator<<(QDataStream& out, Vec<T> const& value) {
//    out << value.size();
//    for (auto const& it : value) {
//        out << it;
//    }
//    return out;
//}

//template <typename T>
//QDataStream& operator>>(QDataStream& in, sem::SemIdT<T>& value) {
//    sem::SemId tmp = sem::SemId::Nil();
//    in >> tmp;
//    value = typename sem::SemIdT<T>(tmp);
//    Q_CHECK_PTR(currentContenxt);
//    value.context = currentContenxt;
//    return in;
//}

//template <typename T>
//QDataStream& operator<<(QDataStream& out, sem::SemIdT<T> const& value) {
//    out << value.toId();
//    return out;
//}

//template <typename T>
//QDataStream& operator<<(QDataStream& out, Opt<T> const& value) {
//    out << value.has_value();
//    if (value) {
//        out << value.value();
//    }
//    return out;
//}

//template <typename T>
//QDataStream& operator>>(QDataStream& in, Opt<T>& value) {
//    bool hasValue = false;
//    in >> hasValue;
//    if (hasValue) {
//        T tmp = SerdeDefaultProvider<T>::get();
//        in >> tmp;
//        value = tmp;
//    }
//    return in;
//}

//template <typename K, typename V>
//QDataStream& operator<<(
//    QDataStream&              out,
//    UnorderedMap<K, V> const& value) {
//    out << static_cast<int>(value.size());
//    for (auto const& [key, next] : value) {
//        out << key;
//        out << next;
//    }
//    return out;
//}

//template <typename K, typename V>
//QDataStream& operator>>(QDataStream& out, UnorderedMap<K, V>& value) {
//    int size = 0;
//    out >> size;
//    for (int i = 0; i < size; ++i) {
//        K key  = SerdeDefaultProvider<K>::get();
//        V next = SerdeDefaultProvider<V>::get();
//        out >> key;
//        out >> next;
//        value.insert({key, next});
//    }
//    return out;
//}


//template <IsVariant T>
//QDataStream& operator<<(QDataStream& out, T const& value) {
//    out << static_cast<int>(value.index());
//    std::visit([&](auto const& it) { out << it; }, value);
//    return out;
//}


//template <IsVariant T>
//QDataStream& operator>>(QDataStream& out, T& value) {
//    int idx = 0;
//    out >> idx;
//    value = variant_from_index<T>(idx);
//    std::visit([&](auto& res) { out >> res; }, value);
//    return out;
//}

//QDataStream& operator>>(QDataStream& in, UserTime& value) {
//    in >> value.time;
//    return in;
//}

//QDataStream& operator<<(QDataStream& out, UserTime const& value) {
//    out << value.time;
//    return out;
//}

//QDataStream& operator>>(QDataStream& in, LineCol& value) {
//    in >> value.line >> value.column >> value.pos;
//    return in;
//}

//QDataStream& operator<<(QDataStream& out, LineCol const& value) {
//    out << value.line << value.column << value.pos;
//    return out;
//}


//QDataStream& operator>>(QDataStream& in, OrgAdapter& value) {
//    OrgId::id_base_type id;
//    in >> id;
//    value.id.setValue(id);
//    return in;
//}

//QDataStream& operator<<(QDataStream& out, OrgAdapter const& value) {
//    out << value.id.getValue();
//    return out;
//}

//template <DescribedRecord T>
//QDataStream& operator<<(QDataStream& out, T const& value) {
//    mp_for_each<describe_bases<T, mod_any_access>>([&](auto Base) {
//        write_value<typename decltype(Base)::type>(out, value);
//    });

//    mp_for_each<describe_members<T, mod_any_access>>(
//        [&](auto const& field) { out << value.*field.pointer; });

//    return out;
//}

//template <DescribedRecord T>
//QDataStream& operator>>(QDataStream& out, T& value) {
//    using Bd = describe_bases<T, mod_any_access>;
//    mp_for_each<Bd>([&](auto Base) {
//        read_value<typename decltype(Base)::type>(out, value);
//    });

//    mp_for_each<describe_members<T, mod_any_access>>(
//        [&](auto const& field) { out >> value.*field.pointer; });

//    return out;
//}

//template <DescribedRecord T>
//void write_value(QDataStream& out, T const& value) {
//    mp_for_each<describe_bases<T, mod_any_access>>([&](auto Base) {
//        write_value<typename decltype(Base)::type>(out, value);
//    });

//    mp_for_each<describe_members<T, mod_any_access>>(
//        [&](auto const& field) { out << value.*field.pointer; });
//}

//template <DescribedRecord T>
//void read_value(QDataStream& out, T& value) {
//    using Bd = describe_bases<T, mod_any_access>;
//    mp_for_each<Bd>([&](auto Base) {
//        read_value<typename decltype(Base)::type>(out, value);
//    });

//    mp_for_each<describe_members<T, mod_any_access>>(
//        [&](auto const& field) { out >> value.*field.pointer; });
//}

//template <typename Kind>
//void read_store(QDataStream& in, sem::KindStore<Kind>& store) {
//    int size = 0;
//    in >> size;
//    store.values.resize(size);
//    for (Kind& value : store.values) {
//        in >> value.subnodes >> value.loc >> value.original >> value.parent
//            >> value.placementContext;
//        read_value(in, value);
//    }
//}

//template <typename Kind>
//void write_store(QDataStream& out, sem::KindStore<Kind> const& store) {
//    out << store.size();
//    for (Kind const& value : store.values) {
//        out << value.subnodes << value.loc << value.original
//            << value.parent << value.placementContext;
//        write_value(out, value);
//    }
//}

//void SemDataStream::read(QDataStream& in, sem::ParseUnitStore& store) {
//    int enum_count = 0;
//    in >> enum_count;
//    for (int i = 0; i < enum_count; ++i) {
//        OrgSemKind kind;
//        in >> kind;
//        switch (kind) {
//#define _case(__Kind)                                                     \
//    case OrgSemKind::__Kind: {                                            \
//        read_store<sem::__Kind>(in, store.store##__Kind);                 \
//        break;                                                            \
//    }
//            EACH_SEM_ORG_KIND(_case)
//#undef _case
//        }
//    }
//}


//void SemDataStream::write(
//    QDataStream&               out,
//    const sem::ParseUnitStore& store) {
//    int enum_count = 0;
//    for (auto const& k : sliceT<OrgSemKind>()) {
//        ++enum_count;
//    }
//    out << enum_count;
//    for (auto const& kind : sliceT<OrgSemKind>()) {
//        out << kind;
//        switch (kind) {

//#define _case(__Kind)                                                     \
//    case OrgSemKind::__Kind: {                                            \
//        write_store<sem::__Kind>(out, store.store##__Kind);               \
//        break;                                                            \
//    }
//            EACH_SEM_ORG_KIND(_case)
//#undef _case
//        }
//    }
//}

//void SemDataStream::read(QDataStream& in, sem::ContextStore* store) {
//    int storeCount = 0;
//    in >> storeCount;
//    CHECK_X(storeCount == 1, "DBG", to_string(storeCount));
//    currentContenxt = store;
//    store->stores.resize(storeCount, store);
//    for (sem::ParseUnitStore& unit : store->stores) {
//        read(in, unit);
//    }
//    currentContenxt = nullptr;
//}

//void SemDataStream::write(
//    QDataStream&             out,
//    const sem::ContextStore& store) {
//    out << (int)store.stores.size();
//    for (auto const& unit : store.stores) {
//        write(out, unit);
//    }
//}

//void SemDataStream::read(
//    QDataStream&       in,
//    sem::ContextStore* store,
//    sem::SemId*        rootNode) {
//    in >> rootNode->id;
//    rootNode->context = store;
//    read(in, store);
//}


//void SemDataStream::write(
//    QDataStream&             out,
//    const sem::ContextStore& store,
//    const sem::SemId&        rootNode) {
//    out << rootNode.id;
//    write(out, store);
//}
