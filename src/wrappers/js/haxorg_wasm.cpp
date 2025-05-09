#include <string>

#include <emscripten.h>
#include <emscripten/bind.h>
#include <haxorg/sem/SemOrg.hpp>
#include <haxorg/sem/SemBaseApi.hpp>
#include <hstd/system/Formatter.hpp>
#include "node_utils.hpp"
#include "haxorg_wasm_manual.hpp"

using namespace emscripten;

namespace em = emscripten;

EMSCRIPTEN_BINDINGS(haxorg_wasm) {
    class_<org::sem::Org>("Org")
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


    em::class_<org::sem::Paragraph, em::base<org::sem::Org>>("Paragraph")
        .smart_ptr<org::sem::SemId<org::sem::Paragraph>>("Paragraph");

    org::bind::js::bind_optional<org::sem::SemId<org::sem::Paragraph>>(
        "OptOfParagraph");
    em::class_<org::sem::Document, em::base<org::sem::Org>>("Document")
        .smart_ptr<org::sem::SemId<org::sem::Document>>("Document")
        .property("title", &org::sem::Document::title);


    function(
        "parseString",
        static_cast<org::sem::SemId<org::sem::Org> (*)(std::string const)>(
            &org::parseString));

    org::bind::js::bind_enum<OrgSemKind>("OrgSemKind");

    haxorg_wasm_manual_register();
}
