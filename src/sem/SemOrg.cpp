#include "SemOrg.hpp"

template <typename T>
sem::SemIdT<T> sem::SemId::as() const {
    SemIdT<T> result = SemIdT<T>(*this);
    if constexpr (!std::is_abstract_v<T>) {
        Q_ASSERT_X(
            this->get()->getKind() == T::staticKind,
            "cast sem ID node",
            "Cannot convert sem ID node of kind $# to $# (ID $#)"
                % to_string_vec(
                    this->get()->getKind(),
                    T::staticKind,
                    this->getReadableId()));
    }

    return result;
}


void sem::SubtreeLog::setDescription(sem::SemIdT<sem::StmtList> desc) {
    std::visit(
        overloaded{
            [](Clock&) {},
            [&](auto& value) { value.desc = desc; },
        },
        log);
}

#define forward_declare(__Kind)                                           \
    template sem::SemIdT<sem::__Kind> sem::SemId::as() const;


EACH_SEM_ORG_KIND(forward_declare)
#undef forward_declare
