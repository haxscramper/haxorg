#include "haxorg/sem/SemBaseApi.hpp"
#include <hstd/stdlib/Ptrs.hpp>
#include <hstd/ext/astdiff.hpp>
#include <gtest/gtest.h>
#include <hstd/stdlib/Map.hpp>
#include <hstd/stdlib/Filesystem.hpp>
#include <haxorg/sem/SemOrg.hpp>
#include <haxorg/test/org_parse_aux.hpp>
#include <haxorg/sem/SemAstDiff.hpp>
#include "../common.hpp"
#include "tOrgTestCommon.hpp"
#include <hstd/ext/logger.hpp>
#include <hstd/stdlib/VariantFormatter.hpp>


using namespace hstd::ext::diff;
using namespace hstd;
using namespace org::sem;
using namespace hstd::ext;
using namespace org;


struct SemDiffBuilder : org::algo::SemNodeDiff {
    org::test::MockFull srcParse{"<src>"};
    org::test::MockFull dstParse{"<dst>"};

    sem::SemId<sem::Document> setOrg(std::string const& text, bool isSrc) {
        auto mock = isSrc ? &srcParse : &dstParse;
        mock->run(text);
        sem::OrgConverter converter{mock->parser->currentFile};
        return converter
            .convertDocument(
                org::parse::OrgAdapter(&mock->nodes, org::parse::OrgId(0)))
            .value();
    }

    sem::SemId<sem::Document> setSrc(std::string const& text) {
        return setOrg(text, true);
    }

    sem::SemId<sem::Document> setDst(std::string const& text) {
        return setOrg(text, false);
    }
};

TEST(OrgSemAstDiff, OrgOneWord) {
    SemDiffBuilder builder{};
    auto           Src = builder.setSrc("word");
    auto           Dst = builder.setDst("word");
    builder.setDiffTrees(Src, Dst, builder.getOptions());
    auto changes = builder.diff->getAllChanges();
    EXPECT_TRUE(changes.empty());
}


TEST(OrgSemAstDiff, OrgChangedWord) {
    SemDiffBuilder builder{};
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

TEST(OrgSemAstDiff, OrgChangeNestedWord) {
    SemDiffBuilder builder{};
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

TEST(OrgSemAstDiff, OrgChangeDeeplyNestedWord) {
    SemDiffBuilder builder{};

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

struct ImmDiffBuilder : org::algo::ImmNodeDiff {
    hstd::Vec<ImmNodeDiff::AstEdit> edits;
    org::sem::SemId<org::sem::Org>  SemSrc;
    org::sem::SemId<org::sem::Org>  SemDst;
    org::imm::ImmAstVersion         ImmSrc;
    org::imm::ImmAstVersion         ImmDst;

    org::imm::ImmAdapter src(hstd::Vec<int> const& path = {}) const {
        return ImmSrc.getRootAdapter().at(path);
    }

    org::imm::ImmAdapter dst(hstd::Vec<int> const& path = {}) const {
        return ImmDst.getRootAdapter().at(path);
    }

    ImmDiffBuilder(
        std::string const& Src,
        std::string const& Dst,
        bool               WithKeep,
        bool               DirectSubnodes = true)
        : org::algo::ImmNodeDiff{
              org::imm::ImmAstContext::init_start_context(),
              DirectSubnodes} {
        SemSrc = org::parseString(Src, "<src>");
        SemDst = org::parseString(Dst, "<dst>");
        {
            HSLOG_INFO("Add SRC root");
            HSLOG_DEPTH_SCOPE_ANON();
            ImmSrc = context->addRoot(SemSrc);
        }
        {
            HSLOG_INFO("Add DST root");
            HSLOG_DEPTH_SCOPE_ANON();
            ImmDst = context->addRoot(SemDst);
        }
        setDiffTrees(
            ImmSrc.getRootAdapter(),
            ImmDst.getRootAdapter(),
            getOptions());

        edits = getEdits(WithKeep);
    }

    using ImmNodeDiff::AstEdit;

    AstEdit::Replace const& getReplace(int idx) const {
        return edits.at(idx).getReplace();
    }

    AstEdit::Keep const& getKeep(int idx) const {
        return edits.at(idx).getKeep();
    }

    AstEdit::Insert const& getInsert(int idx) const {
        return edits.at(idx).getInsert();
    }

    AstEdit::Delete const& getDelete(int idx) const {
        return edits.at(idx).getDelete();
    }

    template <typename T>
    org::imm::ImmAdapterT<T> getReplaceSrcNode(int idx) const {
        return context->adapt(getReplace(idx).src).as<T>();
    }

    template <typename T>
    org::imm::ImmAdapterT<T> getReplaceDstNode(int idx) const {
        return context->adapt(getReplace(idx).dst).as<T>();
    }

    template <typename T>
    org::imm::ImmAdapterT<T> getKeepNode(int idx) const {
        return context->adapt(getKeep(idx).id).as<T>();
    }

    template <typename T>
    org::imm::ImmAdapterT<T> getInsertNode(int idx) const {
        return context->adapt(getInsert(idx).id).as<T>();
    }

    template <typename T>
    org::imm::ImmAdapterT<T> getDeleteNode(int idx) const {
        return context->adapt(getDelete(idx).id).as<T>();
    }

    void debug() {
        std::string buffer;
        buffer += printMapping().toString(false) + "\n";

        for (auto const& edit : edits) {
            buffer += hstd::fmt1(edit) + "\n";
        }

        writeFile(getDebugFile("diff_builder.txt"), buffer);

        writeTreeRepr(SemSrc, getDebugFile("SemSrc.yaml"));
        writeTreeRepr(SemDst, getDebugFile("SemDst.yaml"));
        imm::ImmAdapter::TreeReprConf conf;
        conf.withAuxFields  = true;
        conf.withReflFields = true;
        writeTreeRepr(
            ImmSrc.getRootAdapter(), getDebugFile("ImmSrc.txt"), conf);
        writeTreeRepr(
            ImmDst.getRootAdapter(), getDebugFile("ImmDst.txt"), conf);
    }
};

class OrgImmAstDiff : public ::testing::Test {
  protected:
    void SetUp() override {
        hstd::log::push_sink(hstd::log::init_file_sink(
            getDebugFile("test_log.log").native()));
    }

    virtual void TearDown() override { hstd::log::clear_sink_backends(); }
};

TEST_F(OrgImmAstDiff, SimpleInsertWords) {
    ImmDiffBuilder b{"word", "word two", true};
    b.debug();

    EXPECT_EQ(b.edits.size(), 5);
    EXPECT_EQ2(b.getReplace(0).src.id.getKind(), OrgSemKind::Document);
    EXPECT_EQ2(b.getReplace(1).src.id.getKind(), OrgSemKind::Paragraph);
    EXPECT_EQ2(b.getKeepNode<org::imm::ImmWord>(2)->text.get(), "word"_ss);
    EXPECT_EQ2(b.getInsertNode<org::imm::ImmSpace>(3)->text.get(), " "_ss);
    EXPECT_EQ2(
        b.getInsertNode<org::imm::ImmWord>(4)->text.get(), "two"_ss);
}


TEST_F(OrgImmAstDiff, SimpleDeleteWords) {
    ImmDiffBuilder b{"word two", "word", true};
    b.debug();

    EXPECT_EQ(b.edits.size(), 5);
    EXPECT_EQ2(b.getReplace(0).src.id.getKind(), OrgSemKind::Document);
    EXPECT_EQ2(b.getReplace(1).src.id.getKind(), OrgSemKind::Paragraph);
    EXPECT_EQ2(b.getKeepNode<org::imm::ImmWord>(2)->text.get(), "word"_ss);
    EXPECT_EQ2(b.getDeleteNode<org::imm::ImmSpace>(3)->text.get(), " "_ss);
    EXPECT_EQ2(
        b.getDeleteNode<org::imm::ImmWord>(4)->text.get(), "two"_ss);
}

TEST_F(OrgImmAstDiff, UpdateSubtreeProperty) {
    ImmDiffBuilder b{
        R"(
* subtree
  :properties:
  :id: first-id
  :end:
)",
        R"(
* subtree
  :properties:
  :id: second-id
  :end:
)",
        false};
    b.debug();

    EXPECT_EQ(b.edits.size(), 2);
    EXPECT_EQ2(b.getReplace(0).src.id.getKind(), OrgSemKind::Document);
    EXPECT_EQ2(b.getReplace(1).src.id.getKind(), OrgSemKind::Subtree);
}

TEST_F(OrgImmAstDiff, ChangeNodeKind) {
    ImmDiffBuilder b{R"(/italic/)", R"(*italic*)", true};
    b.debug();
    EXPECT_EQ(b.edits.size(), 4);
    EXPECT_EQ2(b.getReplace(0).src.id.getKind(), OrgSemKind::Document);
    EXPECT_EQ2(b.getReplace(0).dst.id.getKind(), OrgSemKind::Document);
    EXPECT_EQ2(b.getReplace(1).src.id.getKind(), OrgSemKind::Paragraph);
    EXPECT_EQ2(b.getReplace(1).dst.id.getKind(), OrgSemKind::Paragraph);
    EXPECT_EQ2(b.getReplace(2).src.id.getKind(), OrgSemKind::Italic);
    EXPECT_EQ2(b.getReplace(2).dst.id.getKind(), OrgSemKind::Bold);
    EXPECT_EQ2(b.getKeep(3).id.id.getKind(), OrgSemKind::Word);
    EXPECT_EQ2(
        b.getKeepNode<org::imm::ImmWord>(3)->text.get(), "italic"_ss);
}

TEST_F(OrgImmAstDiff, ListItemMove) {
    ImmDiffBuilder b{
        R"(
- item 1
- item 2
)",
        R"(
- item 2
- item 1
)",
        false};
    b.debug();
    EXPECT_EQ(b.edits.size(), 2);
    EXPECT_EQ2(b.getReplace(0).src.id.getKind(), OrgSemKind::Document);
    EXPECT_EQ2(b.getReplace(0).dst.id.getKind(), OrgSemKind::Document);
    EXPECT_EQ2(b.getReplace(0).src, b.src().uniq());
    EXPECT_EQ2(b.getReplace(0).dst, b.dst().uniq());
    EXPECT_EQ2(b.getReplace(1).src.id.getKind(), OrgSemKind::List);
    EXPECT_EQ2(b.getReplace(1).dst.id.getKind(), OrgSemKind::List);
}
