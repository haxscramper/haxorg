#include "setup.hpp"
#include <gui_lib/org_qml_backend.hpp>

void Setup::applicationAvailable() {}
void Setup::qmlEngineAvailable(QQmlEngine* engine) {
    qmlRegisterType<OrgBackend>("OrgQml", 1, 0, "OrgBackend");
}
void Setup::cleanupTestCase() {}
