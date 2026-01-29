#include "pyhaxorg_manual_impl.hpp"

int main() {
    org::parse::ParseContext ctx;
    auto node = ctx.parseFile("/home/haxscramper/tmp/doc1.org");
    std::cout << org::exportToTreeString(node, org::OrgTreeExportOpts{})
              << std::endl;
}
