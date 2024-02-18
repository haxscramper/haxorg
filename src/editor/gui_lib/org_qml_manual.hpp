#pragma once
#include <QObject>
#include <sem/SemOrg.hpp>
#include <QJsonObject>

namespace org_qml {
template <typename QmlOut, typename CxxIn>
struct serde {
    static QmlOut cxx_to_qml(CxxIn const& value) { return value; }
    static CxxIn  qml_to_cxx(QmlOut const& value) { return value; }
};

template <>
struct serde<QString, Str> {
    static QString cxx_to_qml(Str const& value) {
        return QString::fromStdString(value);
    }
    static Str qml_to_cxx(QString const& value) {
        QByteArray tmp = value.toLatin1();
        return std::string{tmp.data(), static_cast<size_t>(tmp.size())};
    }
};

struct Org {
    Q_GADGET
  public:
    Org() = default;
    Org(sem::SemId<sem::Org> const& id) : __data(id.as<sem::Org>()) {}
    sem::SemId<sem::Org>   __data;
    Q_INVOKABLE QString    getRichText() const;
    Q_INVOKABLE void       setRichText(QString const& value);
    Q_INVOKABLE QJsonValue getJson() const;
    Q_INVOKABLE Org        at(int index);
    Q_INVOKABLE int        size() { return __data->subnodes.size(); }

    Q_INVOKABLE QString getKind() const {
        return QString::fromStdString(fmt1(__data->getKind()));
    }
};
} // namespace org_qml
