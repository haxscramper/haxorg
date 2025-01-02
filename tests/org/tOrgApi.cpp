#include "tOrgTestCommon.hpp"


TEST(OrgApi, AstTrackingCollection) {
    auto doc1 = testParseString(R"(
* subtree
  :properties:
  :radio_id: alias1
  :radio_id: alias2
  :radio_id: human readable
  :id: subtree-id
  :end:

Regular paragraph [fn:note]

[fn:note] footnote paragraph
)");

    auto doc2 = testParseString(R"(
Other text using alias1, alias2, and human readable thing

Referencing [[id:subtree-id]]
)");

    auto map = sem::getAstTrackingMap({doc1, doc2});
}
