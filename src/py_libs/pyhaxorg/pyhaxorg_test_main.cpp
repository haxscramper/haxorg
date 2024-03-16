#include "pyhaxorg_manual_impl.hpp"

int main() {
    auto node = parseFile("/home/haxscramper/tmp/doc1.org", {});
    LOG(INFO) << exportToTreeString(node, OrgTreeExportOpts{});
}
