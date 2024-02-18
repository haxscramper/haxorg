#include "pyhaxorg_manual_impl.hpp"

int main() {
    auto            ctx  = OrgContext();
    auto            node = ctx.parseFile("/home/haxscramper/tmp/doc1.org");
    OrgExporterTree exp;
    LOG(INFO) << exp.toString(node, ExporterTreeOpts{});
}
