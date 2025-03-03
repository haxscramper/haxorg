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
  :hashtag_def: #hashtag1
  :hashtag_def: #nested##[alias1,alias2]
  :end:

Regular paragraph [fn:note]

[fn:note] footnote paragraph
)");

    auto doc2 = testParseString(R"(
using alias1, alias2, and human readable

Referencing [[id:subtree-id]]

Mention #hashtag1 and #nested##alias1 with #nested##alias2
)");

    auto map = org::getAstTrackingMap({doc1, doc2});

    writeFile(getDebugFile("tracking.json"), to_json_eval(map).dump(2));


    auto doc2_par1 = doc2.at(1);
    auto doc2_par3 = doc2.at(5);
    EXPECT_EQ2(doc2_par1->getKind(), OrgSemKind::Paragraph);
    EXPECT_EQ2(doc2_par1->getKind(), OrgSemKind::Paragraph);
    writeFile(getDebugFile("repr.txt"), dbgString(doc2_par1));

    {
        auto groups = org::getSubnodeGroups(doc2_par1, map);
        EXPECT_TRUE(groups.at(2).isRadioTarget());
        EXPECT_TRUE(groups.at(5).isRadioTarget());
        EXPECT_TRUE(groups.at(1_B).isRadioTarget());
    }

    {
        auto group = org::getSubnodeGroups(doc2_par3, map);

        EXPECT_TRUE(group.at(2).isTrackedHashtag());
        EXPECT_TRUE(group.at(6).isTrackedHashtag());
        EXPECT_TRUE(group.at(10).isTrackedHashtag());
        auto t2  = group.at(2).getTrackedHashtag();
        auto t6  = group.at(6).getTrackedHashtag();
        auto t10 = group.at(10).getTrackedHashtag();

        EXPECT_EQ2(t2.targets.size(), 1);
        EXPECT_EQ2(
            t2.targets.begin()->first, sem::HashTagFlat{{"hashtag1"}});
        EXPECT_EQ2(t6.targets.size(), 1);
        EXPECT_EQ2(
            t6.targets.begin()->first,
            (sem::HashTagFlat{{"nested", "alias1"}}));
        EXPECT_EQ2(t10.targets.size(), 1);
        EXPECT_EQ2(
            t10.targets.begin()->first,
            (sem::HashTagFlat{{"nested", "alias2"}}));
    }
}

TEST(OrgApi, EvalCodeBlocks) {
    auto doc = testParseString(
        R"(#+begin_src test :results value raw
content
#+end_src)",
        getDebugFile("eval_code_blocks"));
    org::OrgCodeEvalParameters conf;
    Vec<sem::OrgCodeEvalInput> buf;

    conf.evalBlock =
        [&](sem::OrgCodeEvalInput const& in) -> sem::OrgCodeEvalOutput {
        buf.push_back(in);
        return sem::OrgCodeEvalOutput{.stdout = "*bold*"};
    };
    conf.debug->setTraceFile(getDebugFile("EvalCodeBlock.log"));
    auto ev = org::evaluateCodeBlocks(doc, conf);

    writeTreeRepr(doc, getDebugFile("eval-pre.json"));
    writeTreeRepr(ev, getDebugFile("eval-post.json"));

    writeTreeRepr(doc, getDebugFile("eval-pre.txt"));
    writeTreeRepr(ev, getDebugFile("eval-post.txt"));

    EXPECT_EQ2(buf.at(0).language, "test");
    EXPECT_EQ2(
        buf.at(0).resultFormat, sem::OrgCodeEvalInput::ResultFormat::Raw);
    EXPECT_EQ2(
        buf.at(0).resultType, sem::OrgCodeEvalInput::ResultType::Scalar);

    EXPECT_EQ2(ev->getKind(), OrgSemKind::Document);
    EXPECT_EQ2(ev.at(0)->getKind(), OrgSemKind::BlockCode);
    auto bc = ev.at(0).as<sem::BlockCode>();
    EXPECT_EQ2(bc->result.size(), 1);
    EXPECT_EQ2(
        bc->result.at(0)->getKind(), OrgSemKind::BlockCodeEvalResult);
    auto res = bc->result.at(0).as<sem::BlockCodeEvalResult>();
    EXPECT_EQ2(res->node->getKind(), OrgSemKind::StmtList);
    EXPECT_EQ2(res->node.at(0)->getKind(), OrgSemKind::Paragraph);
    EXPECT_EQ2(res->node.at(0).at(0)->getKind(), OrgSemKind::Bold);
    EXPECT_EQ2(res->node.at(0).at(0).at(0)->getKind(), OrgSemKind::Word);
    auto w = res->node.at(0).at(0).at(0).as<sem::Word>();
    EXPECT_EQ2(w->text, "bold");
}
