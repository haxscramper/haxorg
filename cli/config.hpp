#pragma once

#include <hstd/stdlib/Json.hpp>
#include <QCommandLineParser>
#include <QCoreApplication>
#include <QDir>
#include <QFileInfo>
#include <hstd/stdlib/Func.hpp>

template <typename T>
void to_json(json& out, Slice<T> const& value) {
    if (!out.is_object()) {
        out = json::object();
    }
    out["first"]  = value.first;
    out["second"] = value.last;
}

inline void to_json(json& out, QFileInfo const& value) {
    out = json(value.absoluteFilePath().toStdString());
}

inline void to_json(json& out, QDir const& value) {
    out = json(value.absolutePath().toStdString());
}


namespace cli {
struct OptConfig {
    Vec<QString> name;
    QString      doc;
    bool         isFlag = false;
    QString      getSingleName() const { return join("-", name); }

    QCommandLineOption getOpt() const {
        QCommandLineOption result = QCommandLineOption(
            getSingleName(), doc);
        if (!isFlag) {
            result.setValueName("value");
        }
        return result;
    }
};

template <class C, typename T>
T getPointerType(T C::*v);

template <typename T>
struct OptWalker;

template <typename T>
struct LeafOptWalker {
    static Vec<OptConfig> get(Vec<QString> const& prefix) {
        return Vec<OptConfig>{};
    }
};

template <DescribedEnum E>
struct OptWalker<E> : LeafOptWalker<E> {};


template <>
struct OptWalker<bool> : LeafOptWalker<bool> {};

template <>
struct OptWalker<QDir> : LeafOptWalker<QDir> {};

template <>
struct OptWalker<QString> : LeafOptWalker<QString> {};

template <>
struct OptWalker<Slice<int>> : LeafOptWalker<Slice<int>> {};

template <>
struct OptWalker<QFileInfo> : LeafOptWalker<QFileInfo> {};

template <typename T>
struct OptWalker<Opt<T>> {
    static Vec<OptConfig> get(Vec<QString> const& prefix) {
        return OptWalker<T>::get(prefix);
    }
};


template <DescribedRecord T>
struct OptWalker<T> {
    static Vec<OptConfig> get(Vec<QString> const& prefix) {
        using Bd = boost::describe::
            describe_bases<T, boost::describe::mod_any_access>;
        using Md = boost::describe::
            describe_members<T, boost::describe::mod_any_access>;
        Vec<OptConfig> result;

        boost::mp11::mp_for_each<Bd>([&](auto Base) {
            result.append(
                OptWalker<std::remove_cvref_t<
                    typename decltype(Base)::type>>::get(prefix));
        });

        boost::mp11::mp_for_each<Md>([&](auto const& field) {
            using FieldType = std::remove_cvref_t<decltype(getPointerType(
                field.pointer))>;

            auto parent = OptConfig{
                .doc    = T().getDocFor(field.name),
                .isFlag = std::is_same<FieldType, bool>::value,
                .name   = prefix + Vec<QString>{QString(field.name)}};

            result.push_back(parent);
            result.append(OptWalker<FieldType>::get(parent.name));
        });

        return result;
    }
};


template <typename T>
struct CliValueWriter;

template <DescribedEnum E>
struct CliValueWriter<E> {
    static void write(E* target, QString const& value) {
        Q_CHECK_PTR(target);
        *target = enum_serde<E>::from_string(value).value();
    }
};

template <>
struct CliValueWriter<int> {
    static void write(int* target, QString const& value) {
        Q_CHECK_PTR(target);
        *target = value.toInt();
    }
};

template <>
struct CliValueWriter<bool> {
    static void write(bool* target, QString const& value) {
        Q_CHECK_PTR(target);
        *target = value == "true";
    }
};

template <>
struct CliValueWriter<Slice<int>> {
    static void write(Slice<int>* target, QString const& value) {
        Q_CHECK_PTR(target);
        auto range    = value.split(":");
        target->first = range.at(0).toInt();
        target->last  = range.at(1).toInt();
    }
};

template <>
struct CliValueWriter<QFileInfo> {
    static void write(QFileInfo* target, QString const& value) {
        Q_CHECK_PTR(target);
        target->setFile(value);
    }
};

template <>
struct CliValueWriter<QString> {
    static void write(QString* target, QString const& value) {
        Q_CHECK_PTR(target);
        *target = value;
    }
};

template <>
struct CliValueWriter<QDir> {
    static void write(QDir* target, QString const& value) {
        Q_CHECK_PTR(target);
        *target = QDir(value);
    }
};


struct ReflectiveCliBase {
    struct FieldHandle {
        struct Object {
            ReflectiveCliBase* base;
        };

        struct Primitive {
            std::any target;

            Func<void(std::any value, QString const& write)> onWrite;
            void setFrom(QString const& value) { onWrite(target, value); }
        };

        struct None {};
        SUB_VARIANTS(Kind, Data, data, getKind, None, Object, Primitive);
        Data data;
        bool isNone() const { return getKind() == Kind::None; }

        template <DescribedRecord T>
        static FieldHandle init(T* record) {
            return FieldHandle{Object{record}};
        }

        template <typename T>
        static FieldHandle init(T* record) {
            return FieldHandle{Primitive{
                .target  = std::any(record),
                .onWrite = [](std::any target, QString const& value) {
                    T* pointer = std::any_cast<T*>(target);
                    Q_CHECK_PTR(pointer);
                    CliValueWriter<T>::write(pointer, value);
                }}};
        }

        template <typename T>
        static FieldHandle init(Opt<T>* record) {
            if (!record->has_value()) {
                (*record) = T{};
            }

            return FieldHandle::init(&(record->value()));
        }
    };

    virtual FieldHandle getHandle(QString const& path) = 0;

    FieldHandle getHandle(CVec<QString> path) {
        FieldHandle handle = getHandle(path.at(0));
        for (auto const& step : path[slice(1, 1_B)]) {
            if (handle.getKind() == FieldHandle::Kind::Object) {
                handle = handle.getObject().base->getHandle(step);
            } else {
                qFatal() << "Cannot get sub-entry from handle of "
                            "non-object type";
            }
        }

        return handle;
    }

    virtual QString getDocFor(QString const& field) const { return ""; }
};

template <typename Derived>
struct ReflectiveCli
    : ReflectiveCliBase
    , CRTP_this_method<Derived> {
    using CRTP_this_method<Derived>::_this;

    DECL_FIELDS(ReflectiveCli, ());

    using ReflectiveCliBase::getHandle;

    virtual FieldHandle getHandle(QString const& path) override {
        FieldHandle result;

        using Bd = boost::describe::
            describe_bases<Derived, boost::describe::mod_any_access>;
        using Md = boost::describe::
            describe_members<Derived, boost::describe::mod_any_access>;

        boost::mp11::mp_for_each<Md>([&](auto const& field) {
            if (result.isNone() && field.name == path) {
                result = FieldHandle::init(&(_this()->*field.pointer));
            }
        });

        if (!result.isNone()) {
            return result;
        }

        boost::mp11::mp_for_each<Bd>([&](auto Base) {
            getHandle<std::remove_cvref_t<typename decltype(Base)::type>>(
                path);
        });

        return result;
    }
};

struct TraceConfig : ReflectiveCli<TraceConfig> {
    DECL_FIELDS(
        TraceConfig,
        (),
        ((Opt<QFileInfo>), to, std::nullopt),
        ((bool), enabled, false),
        ((Slice<int>), extent, (slice(0, value_domain<int>::high()))),
        ((bool), dump, false),
        ((Opt<QFileInfo>), dumpTo, std::nullopt));

    virtual QString getDocFor(const QString& field) const {
        if (field == "to") {
            return "File to write debug output to";
        } else if (field == "enabled") {
            return "Is trace enabled";
        } else {
            return "";
        }
    }
};

struct Exporter : ReflectiveCli<Exporter> {
    struct Base : ReflectiveCli<Base> {
        DECL_FIELDS(
            Base,
            (),
            ((TraceConfig), trace, TraceConfig{}),
            ((QFileInfo), target, QFileInfo{}),
            ((Opt<QDir>), outDir, std::nullopt),
            ((Opt<QDir>), tmpDir, std::nullopt));
    };

    struct Tex : Base {
        DECL_FIELDS(Tex, (Base));
    };

    struct HTML : Base {
        DECL_FIELDS(HTML, (Base));
    };

    struct SExpr : Base {
        DECL_FIELDS(SExpr, (Base));
    };

    struct Gantt : Base {
        DECL_FIELDS(Gantt, (Base));
    };

    struct EventLog : Base {
        DECL_FIELDS(EventLog, (Base));
    };

    struct MindMap : Base {
        DECL_FIELDS(MindMap, (Base));
    };

    struct SubtreeStructure : Base {
        DECL_FIELDS(SubtreeStructure, (Base));
    };

    struct Lex : Base {
        DECL_DESCRIBED_ENUM(Kind, Html, Csv, Annotated, Yaml, Json);
        DECL_FIELDS(Lex, (Base), ((Kind), kind, Kind::Csv));
    };

    struct Parse : Base {
        DECL_DESCRIBED_ENUM(Kind, Yaml, Json, Html, Tree);
        DECL_FIELDS(Parse, (Base), ((Kind), kind, Kind::Yaml));
    };

    struct Json : Base {
        DECL_FIELDS(Json, (Base));
    };

    struct Yaml : Base {
        DECL_FIELDS(Yaml, (Base));
    };

    struct QDocument : Base {
        DECL_DESCRIBED_ENUM(Kind, Html, Md, Txt);
        DECL_FIELDS(QDocument, (Base), ((Kind), kind, Kind::Html));
    };

    struct Langtool : Base {
        DECL_FIELDS(
            Langtool,
            (Base),
            ((Opt<QFileInfo>), httpCache, std::nullopt));
    };

    struct NLP : Base {
        DECL_FIELDS(
            NLP,
            (Base),
            ((Opt<QFileInfo>), httpCache, std::nullopt));
    };

    DECL_FIELDS(
        Exporter,
        (),
        ((Opt<QDocument>), qdoc, std::nullopt),
        ((Opt<Yaml>), yaml, std::nullopt),
        ((Opt<Json>), json, std::nullopt),
        ((Opt<Parse>), parse, std::nullopt),
        ((Opt<Lex>), lex, std::nullopt),
        ((Opt<Gantt>), gantt, std::nullopt),
        ((Opt<EventLog>), eventLog, std::nullopt),
        ((Opt<SubtreeStructure>), subtreeStructure, std::nullopt),
        ((Opt<MindMap>), mmap, std::nullopt),
        ((Opt<SExpr>), sexpr, std::nullopt),
        ((Opt<HTML>), html, std::nullopt),
        ((Opt<Tex>), tex, std::nullopt),
        ((Opt<Langtool>), langtool, std::nullopt),
        ((Opt<NLP>), nlp, std::nullopt));

    virtual QString getDocFor(const QString& field) const {
        if (field == "tex") {
            return "Latex exporter";
        } else {
            return "";
        }
    }
};

struct Tracer : ReflectiveCli<Tracer> {
    DECL_FIELDS(
        Tracer,
        (),
        ((TraceConfig), lex, TraceConfig{}),
        ((TraceConfig), parse, TraceConfig{}),
        ((TraceConfig), sem, TraceConfig{}));
};

struct Main : ReflectiveCli<Main> {
    DECL_FIELDS(
        Main,
        (),
        ((QString), source, ""),
        ((Exporter), exp, Exporter{}),
        ((Tracer), trace, Tracer{}))
};
} // namespace cli
