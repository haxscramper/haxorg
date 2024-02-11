#include <QObject>
#include <sem/SemOrg.hpp>

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
} // namespace org_qml
