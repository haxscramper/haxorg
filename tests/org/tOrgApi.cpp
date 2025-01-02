#include "tOrgTestCommon.hpp"

template <typename T>
struct JsonSerde<sem::SemId<T>> {
    static sem::SemId<T> from_json(json const& j) {
        return sem::SemId<T>::Nil();
    }

    static json to_json(sem::SemId<T> value) {
        if (value.isNil()) {
            return json{};
        } else {
            return fmt("{}({:p})", value->getKind(), (void*)value.get());
        }
    }
};


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
using alias1, alias2, and human readable

Referencing [[id:subtree-id]]
)");

    auto map = sem::getAstTrackingMap({doc1, doc2});

    writeFile(getDebugFile("tracking.json"), to_json_eval(map).dump(2));


    auto doc2_par1 = doc2.at(1);
    EXPECT_EQ(doc2_par1->getKind(), OrgSemKind::Paragraph);
    writeFile(getDebugFile("repr.txt"), dbgString(doc2_par1));

    auto groups = sem::getSubnodeGroups(doc2_par1, map);

    // for (auto const& [idx, g] : enumerate(groups)) {
    //     _dfmt(idx, g.getKind(), g);
    //     if (g.isSingle()) {
    //         _dbg(dbgString(g.getSingle().node));
    //     } else {
    //         for (auto const& n : g.getRadioTarget().nodes) {
    //             _dbg(dbgString(n));
    //         }
    //     }
    // }

    EXPECT_TRUE(groups.at(2).isRadioTarget());
    EXPECT_TRUE(groups.at(5).isRadioTarget());
    EXPECT_TRUE(groups.at(1_B).isRadioTarget());
}
