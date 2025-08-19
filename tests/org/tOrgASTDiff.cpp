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

using namespace hstd::ext::diff;
using namespace hstd;
using namespace org::sem;
using namespace hstd::ext;
using namespace org;


struct SemDiffBuilder : org::algo::SemNodeDiff {
    org::test::MockFull srcParse;
    org::test::MockFull dstParse;


    sem::SemId<sem::Document> setOrg(std::string const& text, bool isSrc) {
        auto mock = isSrc ? &srcParse : &dstParse;
        mock->run(text);
        sem::OrgConverter converter{};
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
    org::imm::ImmAstContext::Ptr    context;
    hstd::Vec<ImmNodeDiff::AstEdit> edits;
    ImmDiffBuilder(
        std::string const& Src,
        std::string const& Dst,
        bool               WithKeep) {
        context     = org::imm::ImmAstContext::init_start_context();
        auto SemSrc = org::parseString(Src);
        auto SemDst = org::parseString(Dst);
        auto ImmSrc = context->addRoot(SemSrc);
        auto ImmDst = context->addRoot(SemDst);
        setDiffTrees(
            ImmSrc.getRootAdapter(),
            ImmDst.getRootAdapter(),
            getOptions(),
            context);

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
    }
};

TEST(OrgImmAstDiff, ImmAstDiffSimple) {
    ImmDiffBuilder builder{"word", "word two", true};
    builder.debug();

    EXPECT_EQ(builder.edits.size(), 5);
    EXPECT_EQ2(
        builder.getReplace(0).src.id.getKind(), OrgSemKind::Document);
    EXPECT_EQ2(
        builder.getReplace(1).src.id.getKind(), OrgSemKind::Paragraph);
    EXPECT_EQ2(
        builder.getKeepNode<org::imm::ImmWord>(2)->text.get(), "word"_ss);
    EXPECT_EQ2(
        builder.getInsertNode<org::imm::ImmSpace>(3)->text.get(), " "_ss);
    EXPECT_EQ2(
        builder.getInsertNode<org::imm::ImmWord>(4)->text.get(), "two"_ss);
}
