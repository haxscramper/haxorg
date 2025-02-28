#include <hstd/stdlib/Ptrs.hpp>
#include <hstd/ext/astdiff.hpp>
#include <gtest/gtest.h>
#include <hstd/stdlib/Map.hpp>
#include <hstd/stdlib/Filesystem.hpp>
#include <haxorg/sem/SemOrg.hpp>
#include <haxorg/test/org_parse_aux.hpp>
#include <haxorg/sem/SemAstDiff.hpp>

using namespace hstd::ext::diff;
using namespace hstd;
using namespace org::sem;
using namespace hstd::ext;
using namespace org;


struct OrgDiffBuilder : org::algo::OrgNodeDiff {
    org::test::MockFull srcParse;
    org::test::MockFull dstParse;


    sem::SemId<sem::Document> setOrg(std::string const& text, bool isSrc) {
        auto mock = isSrc ? &srcParse : &dstParse;
        mock->run(text);
        sem::OrgConverter converter{};
        return converter.toDocument(
            org::parse::OrgAdapter(&mock->nodes, org::parse::OrgId(0)));
    }

    sem::SemId<sem::Document> setSrc(std::string const& text) {
        return setOrg(text, true);
    }

    sem::SemId<sem::Document> setDst(std::string const& text) {
        return setOrg(text, false);
    }
};

TEST(OrgAstDiff, OrgOneWord) {
    OrgDiffBuilder builder{};
    auto           Src = builder.setSrc("word");
    auto           Dst = builder.setDst("word");
    builder.setDiffTrees(Src, Dst, builder.getOptions());
    auto changes = builder.diff->getAllChanges();
    EXPECT_TRUE(changes.empty());
}


TEST(OrgAstDiff, OrgChangedWord) {
    OrgDiffBuilder builder{};
    auto           Src = builder.setSrc("word1");
    auto           Dst = builder.setDst("word2");
    builder.setDiffTrees(Src, Dst, builder.getOptions());
    auto changes = builder.diff->getAllChanges();
    EXPECT_EQ(changes.size(), 1);
    auto ch0 = changes.at(0);
    EXPECT_EQ(builder.getSrc(ch0.src)->getKind(), OrgSemKind::Word);
    EXPECT_EQ(builder.getDst(ch0.dst)->getKind(), OrgSemKind::Word);

    EXPECT_EQ(builder.getSrcT<sem::Word>(ch0.src)->text, "word1");
    EXPECT_EQ(builder.getDstT<sem::Word>(ch0.dst)->text, "word2");
}

TEST(OrgAstDiff, OrgChangeNestedWord) {
    OrgDiffBuilder builder{};
    auto           Src = builder.setSrc("*word1*");
    auto           Dst = builder.setDst("*word2*");
    builder.setDiffTrees(Src, Dst, builder.getOptions());
    auto changes    = builder.diff->getAllChanges();
    auto change_fmt = builder.formatDiff();
    writeDebugFile(
        change_fmt.toString(false), "txt", true, "OrgChangeNestedWord");

    EXPECT_EQ(changes.size(), 1);
    auto ch0 = changes.at(0);
    EXPECT_EQ(builder.getSrc(ch0.src)->getKind(), OrgSemKind::Word);
    EXPECT_EQ(builder.getDst(ch0.dst)->getKind(), OrgSemKind::Word);

    EXPECT_EQ(builder.getSrcT<sem::Word>(ch0.src)->text, "word1");
    EXPECT_EQ(builder.getDstT<sem::Word>(ch0.dst)->text, "word2");
}

TEST(OrgAstDiff, OrgChangeDeeplyNestedWord) {
    OrgDiffBuilder builder{};

    auto Src = builder.setSrc(R"(
* Subtree1
** Subtree2
*** Subtree3

#+begin_center
word1
#+end_center
)");

    auto Dst = builder.setDst(R"(
* Subtree1
** Subtree2
*** Subtree3

#+begin_center
word2
#+end_center
)");

    builder.setDiffTrees(Src, Dst, builder.getOptions());
    auto changes    = builder.diff->getAllChanges();
    auto change_fmt = builder.formatDiff();
    writeDebugFile(
        change_fmt.toString(false),
        "txt",
        true,
        "OrgChangeDeeplyNestedWord");

    EXPECT_EQ(changes.size(), 1);
    auto ch0 = changes.at(0);
    EXPECT_EQ(builder.getSrc(ch0.src)->getKind(), OrgSemKind::Word);
    EXPECT_EQ(builder.getDst(ch0.dst)->getKind(), OrgSemKind::Word);

    EXPECT_EQ(builder.getSrcT<sem::Word>(ch0.src)->text, "word1");
    EXPECT_EQ(builder.getDstT<sem::Word>(ch0.dst)->text, "word2");
}
