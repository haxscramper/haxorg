#pragma once
#include "org_qml.hpp"

namespace org_qml {
#define _case(__Kind)                                                     \
    template <>                                                           \
    struct serde<::org_qml::__Kind, ::sem::SemId<::sem::__Kind>> {        \
        using qml_type = ::org_qml::__Kind;                               \
        using cxx_type = ::sem::SemId<::sem::__Kind>;                     \
        static qml_type cxx_to_qml(cxx_type value) {                      \
            return qml_type{value};                                       \
        }                                                                 \
        static cxx_type qml_to_cxx(qml_type value) {                      \
            return value.__data.as<::sem::__Kind>();                      \
        }                                                                 \
    };

EACH_SEM_ORG_KIND(_case)
#undef _case
} // namespace org_qml
