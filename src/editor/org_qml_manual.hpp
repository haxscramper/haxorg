#include <QObject>
#include <sem/SemOrg.hpp>

namespace org_qml {
template <typename QmlOut, typename CxxIn>
struct serde {
    static QmlOut cxx_to_qml(CxxIn const& value) { return value; }
    static CxxIn  qml_to_cxx(QmlOut const& value) { return value; }
};
} // namespace org_qml
