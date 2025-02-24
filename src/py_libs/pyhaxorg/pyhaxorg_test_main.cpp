#include "pyhaxorg_manual_impl.hpp"

int main() {
    auto node = org::parseFile("/home/haxscramper/tmp/doc1.org", {});
    LOG(INFO) << org::exportToTreeString(node, org::OrgTreeExportOpts{});
}
