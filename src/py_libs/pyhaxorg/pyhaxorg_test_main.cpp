#include "pyhaxorg_manual_impl.hpp"

int main() {
    auto node = org::parseFile("/home/haxscramper/tmp/doc1.org", {});
    std::cout << org::exportToTreeString(node, org::OrgTreeExportOpts{})
              << std::endl;
}
