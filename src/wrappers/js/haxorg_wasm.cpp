#include <string>

#include <emscripten.h>
#include <emscripten/bind.h>
#include <haxorg/sem/SemOrg.hpp>
#include <haxorg/sem/SemBaseApi.hpp>

using namespace emscripten;

template <typename T>
struct emscripten::smart_ptr_trait<org::sem::SemId<T>> {
    using PointerType  = org::sem::SemId<T>;
    using element_type = T;

    static T* get(PointerType const& ptr) {
        return const_cast<T*>(ptr.get());
    }

    static sharing_policy get_sharing_policy() {
        return sharing_policy::BY_EMVAL;
    }

    static PointerType* share(T* p, EM_VAL v) {
        return new PointerType(
            std::shared_ptr<T>(p, val_deleter(val::take_ownership(v))));
    }

    static PointerType* construct_null() { return new PointerType(); }

    class val_deleter {
      public:
        val_deleter() = delete;
        explicit val_deleter(val v) : v(v) {}
        void operator()(void const*) {
            v();
            // eventually we'll need to support emptied out val
            v = val::undefined();
        }

      private:
        val v;
    };
};


EMSCRIPTEN_BINDINGS(haxorg_wasm) {
    emscripten::class_<org::sem::Org>("Org")
        .property("loc", &org::sem::Org::loc)
        .smart_ptr<org::sem::SemId<org::sem::Org>>("Org")
        .property("subnodes", &org::sem::Org::subnodes)
        .function(
            "getKind",
            static_cast<OrgSemKind (org::sem::Org::*)() const>(
                &org::sem::Org::getKind),
            pure_virtual())
        .function(
            "isGenerated",
            static_cast<bool (org::sem::Org::*)() const>(
                &org::sem::Org::isGenerated))
        .function(
            "push_back",
            static_cast<void (org::sem::Org::*)(
                org::sem::SemId<org::sem::Org>)>(
                &org::sem::Org::push_back))
        .function(
            "size",
            static_cast<int (org::sem::Org::*)() const>(
                &org::sem::Org::size))
        .function(
            "insert",
            static_cast<void (org::sem::Org::*)(
                int, org::sem::SemId<org::sem::Org>)>(
                &org::sem::Org::insert))
        .function(
            "at",
            static_cast<org::sem::SemId<org::sem::Org> (org::sem::Org::*)(
                int) const>(&org::sem::Org::at))
        .function(
            "is_",
            static_cast<bool (org::sem::Org::*)(OrgSemKind) const>(
                &org::sem::Org::is))
        .function(
            "__getitem__",
            static_cast<org::sem::SemId<org::sem::Org> (org::sem::Org::*)(
                int) const>(&org::sem::Org::at));

    emscripten::function(
        "parseString",
        static_cast<org::sem::SemId<org::sem::Org> (*)(std::string const)>(
            &org::parseString));
}
