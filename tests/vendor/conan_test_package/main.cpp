#include <haxorg/api/SemBaseApi.hpp>
#include <haxorg/api/ParseContext.hpp>

int main() {
    org::parse::ParseContext ctx;

    org::sem::SemId<org::sem::Org> node = ctx.parseString(
        R"(**** COMPLETED Subtree
     CLOSED: [2000-01-03 Wed 10:43:40 +04]
     :PROPERTIES:
     :CREATED:  [2000-01-03 Wed 09:51:41 +04]
     :END:
     :LOGBOOK:
     - Tag "#work##xasd" Added on [2000-01-03 Wed 09:52:00 +04]
     CLOCK: [2000-01-03 Wed 09:51:50 +04]--[2000-01-03 Wed 10:43:40 +04] =>  0:52
     - State "WIP"        from "TODO"       [2000-01-03 Wed 09:51:50 +04]
     - State "COMPLETED"  from "WIP"        [2000-01-03 Wed 10:43:40 +04]
     :END:)",
        "<test>");

    return 0;
}
