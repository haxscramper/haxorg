#include <haxorg/sem/SemOrg.hpp>
#include <haxorg/sem/SemOrgBase.hpp>

template <typename O>
O* org::sem::SemId<O>::get() {
    return value.get();
}

template <typename O>
const O* org::sem::SemId<O>::get() const {
    return value.get();
}

template <typename O>
const O* org::sem::SemId<O>::operator->() const {
    return get();
}

template <typename O>
const O& org::sem::SemId<O>::operator*() const {
    return *value;
}

template <typename O>
OrgSemKind org::sem::SemId<O>::getNodeKind() const {
    return get()->getKind();
}

template <typename O>
int org::sem::SemId<O>::size() const {
    return value->subnodes.size();
}

template <typename O>
org::sem::SemId<O>::SubnodeVec::const_iterator org::sem::SemId<O>::end() const {
    return value->subnodes.end();
}

template <typename O>
org::sem::SemId<O>::SubnodeVec::const_iterator org::sem::SemId<O>::begin() const {
    return value->subnodes.begin();
}

template <typename O>
org::sem::SemId<O>::SubnodeVec::iterator org::sem::SemId<O>::end() {
    return value->subnodes.end();
}

template <typename O>
org::sem::SemId<O>::SubnodeVec::iterator org::sem::SemId<O>::begin() {
    return value->subnodes.begin();
}

template <typename O>
hstd::Opt<org::sem::SemId<org::sem::Org>> org::sem::SemId<O>::get(
    hstd::BackwardsIndex idx) {
    return value->get(idx);
}

template <typename O>
hstd::Opt<org::sem::SemId<org::sem::Org>> org::sem::SemId<O>::get(int idx) {
    return value->get(idx);
}

template <typename O>
org::sem::SemId<org::sem::Org> org::sem::SemId<O>::at(hstd::BackwardsIndex idx) {
    return value->at(idx);
}

template <typename O>
org::sem::SemId<org::sem::Org> org::sem::SemId<O>::at(int idx) {
    return value->at(idx);
}

template <typename O>
org::sem::SemId<org::sem::Org> org::sem::SemId<O>::asOrg() const {
    return as<sem::Org>();
}

template <typename O>
O& org::sem::SemId<O>::operator*() {
    return *value;
}

template <typename O>
O* org::sem::SemId<O>::operator->() {
    return get();
}

int org::sem::Org::size() const { return subnodes.size(); }

void org::sem::Org::insert(int pos, SemId<Org> node) {
    subnodes.insert(begin() + pos, node);
}

template <typename T>
hstd::Vec<org::sem::SemId<T>> org::sem::Org::subAs() const {
    hstd::Vec<SemId<T>> result;
    for (auto const& sub : subnodes) {
        if (sub->getKind() == T::staticKind) { result.push_back(sub.template as<T>()); }
    }
    return result;
}

#define _kind(__KIND)                                                                    \
    template hstd::Vec<org::sem::SemId<org::sem::__KIND>> org::sem::Org::subAs() const;

EACH_SEM_ORG_KIND(_kind)

#undef _kind

#define _sem_id(__KIND, __BASE) template class org::sem::SemId<org::sem::__KIND>;

EACH_SEM_ORG_TYPE_BASE(_sem_id);
_sem_id(Org, Org);

#undef _sem_id
