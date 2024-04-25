#include "pyhaxorg_manual_impl.hpp"

int main() {
    auto node = sem::parseFile("/home/haxscramper/tmp/doc1.org", {});
    LOG(INFO) << exportToTreeString(node, sem::OrgTreeExportOpts{});
}
