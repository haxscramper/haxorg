/* clang-format off */
#pragma once
#define HAXORG_IMM_ORG_ADAPTER_GENERATED_INCLUDED
#pragma clang diagnostic ignored "-Wextra-qualification"
#include <haxorg/imm/ImmOrg.hpp>
namespace org::imm {
template <>
struct org::imm::ImmAdapterT<org::imm::ImmNoNode> : public org::imm::ImmAdapterTBase<org::imm::ImmNoNode>, public org::imm::ImmAdapterNoNodeAPI {
  USE_IMM_ADAPTER_BASE(org::imm::ImmNoNode)
  using api_type = org::imm::ImmAdapterNoNodeAPI;
  BOOST_DESCRIBE_CLASS(ImmAdapterT, (ImmAdapterTBase, ImmAdapterNoNodeAPI), (), (), ());
  ImmAdapterT(org::imm::ImmAdapter const& other);
};

template <>
struct org::imm::ImmAdapterT<org::imm::ImmErrorItem> : public org::imm::ImmAdapterTBase<org::imm::ImmErrorItem>, public org::imm::ImmAdapterErrorItemAPI {
  USE_IMM_ADAPTER_BASE(org::imm::ImmErrorItem)
  using api_type = org::imm::ImmAdapterErrorItemAPI;
  BOOST_DESCRIBE_CLASS(ImmAdapterT, (ImmAdapterTBase, ImmAdapterErrorItemAPI), (), (), ());
  org::sem::OrgDiagnostics getDiag() const;
  ImmAdapterT(org::imm::ImmAdapter const& other);
};

template <>
struct org::imm::ImmAdapterT<org::imm::ImmErrorGroup> : public org::imm::ImmAdapterTBase<org::imm::ImmErrorGroup>, public org::imm::ImmAdapterErrorGroupAPI {
  USE_IMM_ADAPTER_BASE(org::imm::ImmErrorGroup)
  using api_type = org::imm::ImmAdapterErrorGroupAPI;
  BOOST_DESCRIBE_CLASS(ImmAdapterT, (ImmAdapterTBase, ImmAdapterErrorGroupAPI), (), (), ());
  hstd::ext::ImmVec<org::imm::ImmIdT<org::imm::ImmErrorItem>> getDiagnostics() const;
  ImmAdapterT(org::imm::ImmAdapter const& other);
};

template <>
struct org::imm::ImmAdapterT<org::imm::ImmStmt> : public org::imm::ImmAdapterTBase<org::imm::ImmStmt>, public org::imm::ImmAdapterStmtAPI {
  USE_IMM_ADAPTER_BASE(org::imm::ImmStmt)
  using api_type = org::imm::ImmAdapterStmtAPI;
  BOOST_DESCRIBE_CLASS(ImmAdapterT, (ImmAdapterTBase, ImmAdapterStmtAPI), (), (), ());
  hstd::ext::ImmVec<org::imm::ImmIdT<org::imm::ImmOrg>> getAttached() const;
  ImmAdapterT(org::imm::ImmAdapter const& other);
};

template <>
struct org::imm::ImmAdapterT<org::imm::ImmInline> : public org::imm::ImmAdapterTBase<org::imm::ImmInline>, public org::imm::ImmAdapterInlineAPI {
  USE_IMM_ADAPTER_BASE(org::imm::ImmInline)
  using api_type = org::imm::ImmAdapterInlineAPI;
  BOOST_DESCRIBE_CLASS(ImmAdapterT, (ImmAdapterTBase, ImmAdapterInlineAPI), (), (), ());
  ImmAdapterT(org::imm::ImmAdapter const& other);
};

template <>
struct org::imm::ImmAdapterT<org::imm::ImmStmtList> : public org::imm::ImmAdapterTBase<org::imm::ImmStmtList>, public org::imm::ImmAdapterStmtListAPI {
  USE_IMM_ADAPTER_BASE(org::imm::ImmStmtList)
  using api_type = org::imm::ImmAdapterStmtListAPI;
  BOOST_DESCRIBE_CLASS(ImmAdapterT, (ImmAdapterTBase, ImmAdapterStmtListAPI), (), (), ());
  ImmAdapterT(org::imm::ImmAdapter const& other);
};

template <>
struct org::imm::ImmAdapterT<org::imm::ImmEmpty> : public org::imm::ImmAdapterTBase<org::imm::ImmEmpty>, public org::imm::ImmAdapterEmptyAPI {
  USE_IMM_ADAPTER_BASE(org::imm::ImmEmpty)
  using api_type = org::imm::ImmAdapterEmptyAPI;
  BOOST_DESCRIBE_CLASS(ImmAdapterT, (ImmAdapterTBase, ImmAdapterEmptyAPI), (), (), ());
  ImmAdapterT(org::imm::ImmAdapter const& other);
};

template <>
struct org::imm::ImmAdapterT<org::imm::ImmCmd> : public org::imm::ImmAdapterTBase<org::imm::ImmCmd>, public org::imm::ImmAdapterCmdAPI {
  USE_IMM_ADAPTER_BASE(org::imm::ImmCmd)
  using api_type = org::imm::ImmAdapterCmdAPI;
  BOOST_DESCRIBE_CLASS(ImmAdapterT, (ImmAdapterTBase, ImmAdapterCmdAPI), (), (), ());
  org::sem::AttrGroup getAttrs() const;
  ImmAdapterT(org::imm::ImmAdapter const& other);
};

template <>
struct org::imm::ImmAdapterT<org::imm::ImmBlock> : public org::imm::ImmAdapterTBase<org::imm::ImmBlock>, public org::imm::ImmAdapterBlockAPI {
  USE_IMM_ADAPTER_BASE(org::imm::ImmBlock)
  using api_type = org::imm::ImmAdapterBlockAPI;
  BOOST_DESCRIBE_CLASS(ImmAdapterT, (ImmAdapterTBase, ImmAdapterBlockAPI), (), (), ());
  ImmAdapterT(org::imm::ImmAdapter const& other);
};

template <>
struct org::imm::ImmAdapterT<org::imm::ImmLineCommand> : public org::imm::ImmAdapterTBase<org::imm::ImmLineCommand>, public org::imm::ImmAdapterLineCommandAPI {
  USE_IMM_ADAPTER_BASE(org::imm::ImmLineCommand)
  using api_type = org::imm::ImmAdapterLineCommandAPI;
  BOOST_DESCRIBE_CLASS(ImmAdapterT, (ImmAdapterTBase, ImmAdapterLineCommandAPI), (), (), ());
  ImmAdapterT(org::imm::ImmAdapter const& other);
};

template <>
struct org::imm::ImmAdapterT<org::imm::ImmAttached> : public org::imm::ImmAdapterTBase<org::imm::ImmAttached>, public org::imm::ImmAdapterAttachedAPI {
  USE_IMM_ADAPTER_BASE(org::imm::ImmAttached)
  using api_type = org::imm::ImmAdapterAttachedAPI;
  BOOST_DESCRIBE_CLASS(ImmAdapterT, (ImmAdapterTBase, ImmAdapterAttachedAPI), (), (), ());
  ImmAdapterT(org::imm::ImmAdapter const& other);
};

template <>
struct org::imm::ImmAdapterT<org::imm::ImmLeaf> : public org::imm::ImmAdapterTBase<org::imm::ImmLeaf>, public org::imm::ImmAdapterLeafAPI {
  USE_IMM_ADAPTER_BASE(org::imm::ImmLeaf)
  using api_type = org::imm::ImmAdapterLeafAPI;
  BOOST_DESCRIBE_CLASS(ImmAdapterT, (ImmAdapterTBase, ImmAdapterLeafAPI), (), (), ());
  hstd::Str const& getText() const;
  ImmAdapterT(org::imm::ImmAdapter const& other);
};

template <>
struct org::imm::ImmAdapterT<org::imm::ImmCmdCaption> : public org::imm::ImmAdapterTBase<org::imm::ImmCmdCaption>, public org::imm::ImmAdapterCmdCaptionAPI {
  USE_IMM_ADAPTER_BASE(org::imm::ImmCmdCaption)
  using api_type = org::imm::ImmAdapterCmdCaptionAPI;
  BOOST_DESCRIBE_CLASS(ImmAdapterT, (ImmAdapterTBase, ImmAdapterCmdCaptionAPI), (), (), ());
  org::imm::ImmAdapter getText() const;
  ImmAdapterT(org::imm::ImmAdapter const& other);
};

template <>
struct org::imm::ImmAdapterT<org::imm::ImmCmdCreator> : public org::imm::ImmAdapterTBase<org::imm::ImmCmdCreator>, public org::imm::ImmAdapterCmdCreatorAPI {
  USE_IMM_ADAPTER_BASE(org::imm::ImmCmdCreator)
  using api_type = org::imm::ImmAdapterCmdCreatorAPI;
  BOOST_DESCRIBE_CLASS(ImmAdapterT, (ImmAdapterTBase, ImmAdapterCmdCreatorAPI), (), (), ());
  org::imm::ImmAdapter getText() const;
  ImmAdapterT(org::imm::ImmAdapter const& other);
};

template <>
struct org::imm::ImmAdapterT<org::imm::ImmCmdAuthor> : public org::imm::ImmAdapterTBase<org::imm::ImmCmdAuthor>, public org::imm::ImmAdapterCmdAuthorAPI {
  USE_IMM_ADAPTER_BASE(org::imm::ImmCmdAuthor)
  using api_type = org::imm::ImmAdapterCmdAuthorAPI;
  BOOST_DESCRIBE_CLASS(ImmAdapterT, (ImmAdapterTBase, ImmAdapterCmdAuthorAPI), (), (), ());
  org::imm::ImmAdapter getText() const;
  ImmAdapterT(org::imm::ImmAdapter const& other);
};

template <>
struct org::imm::ImmAdapterT<org::imm::ImmCmdEmail> : public org::imm::ImmAdapterTBase<org::imm::ImmCmdEmail>, public org::imm::ImmAdapterCmdEmailAPI {
  USE_IMM_ADAPTER_BASE(org::imm::ImmCmdEmail)
  using api_type = org::imm::ImmAdapterCmdEmailAPI;
  BOOST_DESCRIBE_CLASS(ImmAdapterT, (ImmAdapterTBase, ImmAdapterCmdEmailAPI), (), (), ());
  hstd::Str const& getText() const;
  ImmAdapterT(org::imm::ImmAdapter const& other);
};

template <>
struct org::imm::ImmAdapterT<org::imm::ImmCmdLanguage> : public org::imm::ImmAdapterTBase<org::imm::ImmCmdLanguage>, public org::imm::ImmAdapterCmdLanguageAPI {
  USE_IMM_ADAPTER_BASE(org::imm::ImmCmdLanguage)
  using api_type = org::imm::ImmAdapterCmdLanguageAPI;
  BOOST_DESCRIBE_CLASS(ImmAdapterT, (ImmAdapterTBase, ImmAdapterCmdLanguageAPI), (), (), ());
  hstd::Str const& getText() const;
  ImmAdapterT(org::imm::ImmAdapter const& other);
};

template <>
struct org::imm::ImmAdapterT<org::imm::ImmCmdColumns> : public org::imm::ImmAdapterTBase<org::imm::ImmCmdColumns>, public org::imm::ImmAdapterCmdColumnsAPI {
  USE_IMM_ADAPTER_BASE(org::imm::ImmCmdColumns)
  using api_type = org::imm::ImmAdapterCmdColumnsAPI;
  BOOST_DESCRIBE_CLASS(ImmAdapterT, (ImmAdapterTBase, ImmAdapterCmdColumnsAPI), (), (), ());
  org::sem::ColumnView getView() const;
  ImmAdapterT(org::imm::ImmAdapter const& other);
};

template <>
struct org::imm::ImmAdapterT<org::imm::ImmCmdName> : public org::imm::ImmAdapterTBase<org::imm::ImmCmdName>, public org::imm::ImmAdapterCmdNameAPI {
  USE_IMM_ADAPTER_BASE(org::imm::ImmCmdName)
  using api_type = org::imm::ImmAdapterCmdNameAPI;
  BOOST_DESCRIBE_CLASS(ImmAdapterT, (ImmAdapterTBase, ImmAdapterCmdNameAPI), (), (), ());
  hstd::Str const& getName() const;
  ImmAdapterT(org::imm::ImmAdapter const& other);
};

template <>
struct org::imm::ImmAdapterT<org::imm::ImmCmdCustomArgs> : public org::imm::ImmAdapterTBase<org::imm::ImmCmdCustomArgs>, public org::imm::ImmAdapterCmdCustomArgsAPI {
  USE_IMM_ADAPTER_BASE(org::imm::ImmCmdCustomArgs)
  using api_type = org::imm::ImmAdapterCmdCustomArgsAPI;
  BOOST_DESCRIBE_CLASS(ImmAdapterT, (ImmAdapterTBase, ImmAdapterCmdCustomArgsAPI), (), (), ());
  hstd::Str const& getName() const;
  bool getIsAttached() const;
  ImmAdapterT(org::imm::ImmAdapter const& other);
};

template <>
struct org::imm::ImmAdapterT<org::imm::ImmCmdCustomRaw> : public org::imm::ImmAdapterTBase<org::imm::ImmCmdCustomRaw>, public org::imm::ImmAdapterCmdCustomRawAPI {
  USE_IMM_ADAPTER_BASE(org::imm::ImmCmdCustomRaw)
  using api_type = org::imm::ImmAdapterCmdCustomRawAPI;
  BOOST_DESCRIBE_CLASS(ImmAdapterT, (ImmAdapterTBase, ImmAdapterCmdCustomRawAPI), (), (), ());
  hstd::Str const& getName() const;
  bool getIsAttached() const;
  hstd::Str const& getText() const;
  ImmAdapterT(org::imm::ImmAdapter const& other);
};

template <>
struct org::imm::ImmAdapterT<org::imm::ImmCmdCustomText> : public org::imm::ImmAdapterTBase<org::imm::ImmCmdCustomText>, public org::imm::ImmAdapterCmdCustomTextAPI {
  USE_IMM_ADAPTER_BASE(org::imm::ImmCmdCustomText)
  using api_type = org::imm::ImmAdapterCmdCustomTextAPI;
  BOOST_DESCRIBE_CLASS(ImmAdapterT, (ImmAdapterTBase, ImmAdapterCmdCustomTextAPI), (), (), ());
  hstd::Str const& getName() const;
  bool getIsAttached() const;
  org::imm::ImmAdapter getText() const;
  ImmAdapterT(org::imm::ImmAdapter const& other);
};

template <>
struct org::imm::ImmAdapterT<org::imm::ImmCmdCall> : public org::imm::ImmAdapterTBase<org::imm::ImmCmdCall>, public org::imm::ImmAdapterCmdCallAPI {
  USE_IMM_ADAPTER_BASE(org::imm::ImmCmdCall)
  using api_type = org::imm::ImmAdapterCmdCallAPI;
  BOOST_DESCRIBE_CLASS(ImmAdapterT, (ImmAdapterTBase, ImmAdapterCmdCallAPI), (), (), ());
  hstd::Str const& getName() const;
  hstd::Opt<hstd::Str> const& getFileName() const;
  org::sem::AttrGroup getInsideHeaderAttrs() const;
  org::sem::AttrGroup getCallAttrs() const;
  org::sem::AttrGroup getEndHeaderAttrs() const;
  hstd::ext::ImmVec<org::imm::ImmIdT<org::imm::ImmBlockCodeEvalResult>> getResult() const;
  ImmAdapterT(org::imm::ImmAdapter const& other);
};

template <>
struct org::imm::ImmAdapterT<org::imm::ImmCmdTblfm> : public org::imm::ImmAdapterTBase<org::imm::ImmCmdTblfm>, public org::imm::ImmAdapterCmdTblfmAPI {
  USE_IMM_ADAPTER_BASE(org::imm::ImmCmdTblfm)
  using api_type = org::imm::ImmAdapterCmdTblfmAPI;
  BOOST_DESCRIBE_CLASS(ImmAdapterT, (ImmAdapterTBase, ImmAdapterCmdTblfmAPI), (), (), ());
  org::sem::Tblfm getExpr() const;
  ImmAdapterT(org::imm::ImmAdapter const& other);
};

template <>
struct org::imm::ImmAdapterT<org::imm::ImmHashTag> : public org::imm::ImmAdapterTBase<org::imm::ImmHashTag>, public org::imm::ImmAdapterHashTagAPI {
  USE_IMM_ADAPTER_BASE(org::imm::ImmHashTag)
  using api_type = org::imm::ImmAdapterHashTagAPI;
  BOOST_DESCRIBE_CLASS(ImmAdapterT, (ImmAdapterTBase, ImmAdapterHashTagAPI), (), (), ());
  org::sem::HashTagText getText() const;
  ImmAdapterT(org::imm::ImmAdapter const& other);
};

template <>
struct org::imm::ImmAdapterT<org::imm::ImmInlineFootnote> : public org::imm::ImmAdapterTBase<org::imm::ImmInlineFootnote>, public org::imm::ImmAdapterInlineFootnoteAPI {
  USE_IMM_ADAPTER_BASE(org::imm::ImmInlineFootnote)
  using api_type = org::imm::ImmAdapterInlineFootnoteAPI;
  BOOST_DESCRIBE_CLASS(ImmAdapterT, (ImmAdapterTBase, ImmAdapterInlineFootnoteAPI), (), (), ());
  hstd::Str const& getTag() const;
  hstd::Opt<org::imm::ImmAdapter> getDefinition() const;
  ImmAdapterT(org::imm::ImmAdapter const& other);
};

template <>
struct org::imm::ImmAdapterT<org::imm::ImmInlineExport> : public org::imm::ImmAdapterTBase<org::imm::ImmInlineExport>, public org::imm::ImmAdapterInlineExportAPI {
  USE_IMM_ADAPTER_BASE(org::imm::ImmInlineExport)
  using api_type = org::imm::ImmAdapterInlineExportAPI;
  BOOST_DESCRIBE_CLASS(ImmAdapterT, (ImmAdapterTBase, ImmAdapterInlineExportAPI), (), (), ());
  hstd::Str const& getExporter() const;
  hstd::Str const& getContent() const;
  ImmAdapterT(org::imm::ImmAdapter const& other);
};

template <>
struct org::imm::ImmAdapterT<org::imm::ImmTime> : public org::imm::ImmAdapterTBase<org::imm::ImmTime>, public org::imm::ImmAdapterTimeAPI {
  USE_IMM_ADAPTER_BASE(org::imm::ImmTime)
  using api_type = org::imm::ImmAdapterTimeAPI;
  BOOST_DESCRIBE_CLASS(ImmAdapterT, (ImmAdapterTBase, ImmAdapterTimeAPI), (), (), ());
  bool getIsActive() const;
  org::imm::ImmTime::TimeVariant getTime() const;
  ImmAdapterT(org::imm::ImmAdapter const& other);
};

template <>
struct org::imm::ImmAdapterT<org::imm::ImmTimeRange> : public org::imm::ImmAdapterTBase<org::imm::ImmTimeRange>, public org::imm::ImmAdapterTimeRangeAPI {
  USE_IMM_ADAPTER_BASE(org::imm::ImmTimeRange)
  using api_type = org::imm::ImmAdapterTimeRangeAPI;
  BOOST_DESCRIBE_CLASS(ImmAdapterT, (ImmAdapterTBase, ImmAdapterTimeRangeAPI), (), (), ());
  org::imm::ImmAdapter getFrom() const;
  org::imm::ImmAdapter getTo() const;
  ImmAdapterT(org::imm::ImmAdapter const& other);
};

template <>
struct org::imm::ImmAdapterT<org::imm::ImmMacro> : public org::imm::ImmAdapterTBase<org::imm::ImmMacro>, public org::imm::ImmAdapterMacroAPI {
  USE_IMM_ADAPTER_BASE(org::imm::ImmMacro)
  using api_type = org::imm::ImmAdapterMacroAPI;
  BOOST_DESCRIBE_CLASS(ImmAdapterT, (ImmAdapterTBase, ImmAdapterMacroAPI), (), (), ());
  hstd::Str const& getName() const;
  org::sem::AttrGroup getAttrs() const;
  ImmAdapterT(org::imm::ImmAdapter const& other);
};

template <>
struct org::imm::ImmAdapterT<org::imm::ImmSymbol> : public org::imm::ImmAdapterTBase<org::imm::ImmSymbol>, public org::imm::ImmAdapterSymbolAPI {
  USE_IMM_ADAPTER_BASE(org::imm::ImmSymbol)
  using api_type = org::imm::ImmAdapterSymbolAPI;
  BOOST_DESCRIBE_CLASS(ImmAdapterT, (ImmAdapterTBase, ImmAdapterSymbolAPI), (), (), ());
  hstd::Str const& getName() const;
  hstd::ext::ImmVec<org::imm::ImmSymbol::Param> getParameters() const;
  hstd::ext::ImmVec<org::imm::ImmIdT<org::imm::ImmOrg>> getPositional() const;
  ImmAdapterT(org::imm::ImmAdapter const& other);
};

template <>
struct org::imm::ImmAdapterT<org::imm::ImmEscaped> : public org::imm::ImmAdapterTBase<org::imm::ImmEscaped>, public org::imm::ImmAdapterEscapedAPI {
  USE_IMM_ADAPTER_BASE(org::imm::ImmEscaped)
  using api_type = org::imm::ImmAdapterEscapedAPI;
  BOOST_DESCRIBE_CLASS(ImmAdapterT, (ImmAdapterTBase, ImmAdapterEscapedAPI), (), (), ());
  ImmAdapterT(org::imm::ImmAdapter const& other);
};

template <>
struct org::imm::ImmAdapterT<org::imm::ImmNewline> : public org::imm::ImmAdapterTBase<org::imm::ImmNewline>, public org::imm::ImmAdapterNewlineAPI {
  USE_IMM_ADAPTER_BASE(org::imm::ImmNewline)
  using api_type = org::imm::ImmAdapterNewlineAPI;
  BOOST_DESCRIBE_CLASS(ImmAdapterT, (ImmAdapterTBase, ImmAdapterNewlineAPI), (), (), ());
  ImmAdapterT(org::imm::ImmAdapter const& other);
};

template <>
struct org::imm::ImmAdapterT<org::imm::ImmSpace> : public org::imm::ImmAdapterTBase<org::imm::ImmSpace>, public org::imm::ImmAdapterSpaceAPI {
  USE_IMM_ADAPTER_BASE(org::imm::ImmSpace)
  using api_type = org::imm::ImmAdapterSpaceAPI;
  BOOST_DESCRIBE_CLASS(ImmAdapterT, (ImmAdapterTBase, ImmAdapterSpaceAPI), (), (), ());
  ImmAdapterT(org::imm::ImmAdapter const& other);
};

template <>
struct org::imm::ImmAdapterT<org::imm::ImmWord> : public org::imm::ImmAdapterTBase<org::imm::ImmWord>, public org::imm::ImmAdapterWordAPI {
  USE_IMM_ADAPTER_BASE(org::imm::ImmWord)
  using api_type = org::imm::ImmAdapterWordAPI;
  BOOST_DESCRIBE_CLASS(ImmAdapterT, (ImmAdapterTBase, ImmAdapterWordAPI), (), (), ());
  ImmAdapterT(org::imm::ImmAdapter const& other);
};

template <>
struct org::imm::ImmAdapterT<org::imm::ImmAtMention> : public org::imm::ImmAdapterTBase<org::imm::ImmAtMention>, public org::imm::ImmAdapterAtMentionAPI {
  USE_IMM_ADAPTER_BASE(org::imm::ImmAtMention)
  using api_type = org::imm::ImmAdapterAtMentionAPI;
  BOOST_DESCRIBE_CLASS(ImmAdapterT, (ImmAdapterTBase, ImmAdapterAtMentionAPI), (), (), ());
  ImmAdapterT(org::imm::ImmAdapter const& other);
};

template <>
struct org::imm::ImmAdapterT<org::imm::ImmRawText> : public org::imm::ImmAdapterTBase<org::imm::ImmRawText>, public org::imm::ImmAdapterRawTextAPI {
  USE_IMM_ADAPTER_BASE(org::imm::ImmRawText)
  using api_type = org::imm::ImmAdapterRawTextAPI;
  BOOST_DESCRIBE_CLASS(ImmAdapterT, (ImmAdapterTBase, ImmAdapterRawTextAPI), (), (), ());
  ImmAdapterT(org::imm::ImmAdapter const& other);
};

template <>
struct org::imm::ImmAdapterT<org::imm::ImmPunctuation> : public org::imm::ImmAdapterTBase<org::imm::ImmPunctuation>, public org::imm::ImmAdapterPunctuationAPI {
  USE_IMM_ADAPTER_BASE(org::imm::ImmPunctuation)
  using api_type = org::imm::ImmAdapterPunctuationAPI;
  BOOST_DESCRIBE_CLASS(ImmAdapterT, (ImmAdapterTBase, ImmAdapterPunctuationAPI), (), (), ());
  ImmAdapterT(org::imm::ImmAdapter const& other);
};

template <>
struct org::imm::ImmAdapterT<org::imm::ImmPlaceholder> : public org::imm::ImmAdapterTBase<org::imm::ImmPlaceholder>, public org::imm::ImmAdapterPlaceholderAPI {
  USE_IMM_ADAPTER_BASE(org::imm::ImmPlaceholder)
  using api_type = org::imm::ImmAdapterPlaceholderAPI;
  BOOST_DESCRIBE_CLASS(ImmAdapterT, (ImmAdapterTBase, ImmAdapterPlaceholderAPI), (), (), ());
  ImmAdapterT(org::imm::ImmAdapter const& other);
};

template <>
struct org::imm::ImmAdapterT<org::imm::ImmBigIdent> : public org::imm::ImmAdapterTBase<org::imm::ImmBigIdent>, public org::imm::ImmAdapterBigIdentAPI {
  USE_IMM_ADAPTER_BASE(org::imm::ImmBigIdent)
  using api_type = org::imm::ImmAdapterBigIdentAPI;
  BOOST_DESCRIBE_CLASS(ImmAdapterT, (ImmAdapterTBase, ImmAdapterBigIdentAPI), (), (), ());
  ImmAdapterT(org::imm::ImmAdapter const& other);
};

template <>
struct org::imm::ImmAdapterT<org::imm::ImmTextTarget> : public org::imm::ImmAdapterTBase<org::imm::ImmTextTarget>, public org::imm::ImmAdapterTextTargetAPI {
  USE_IMM_ADAPTER_BASE(org::imm::ImmTextTarget)
  using api_type = org::imm::ImmAdapterTextTargetAPI;
  BOOST_DESCRIBE_CLASS(ImmAdapterT, (ImmAdapterTBase, ImmAdapterTextTargetAPI), (), (), ());
  ImmAdapterT(org::imm::ImmAdapter const& other);
};

template <>
struct org::imm::ImmAdapterT<org::imm::ImmErrorSkipToken> : public org::imm::ImmAdapterTBase<org::imm::ImmErrorSkipToken>, public org::imm::ImmAdapterErrorSkipTokenAPI {
  USE_IMM_ADAPTER_BASE(org::imm::ImmErrorSkipToken)
  using api_type = org::imm::ImmAdapterErrorSkipTokenAPI;
  BOOST_DESCRIBE_CLASS(ImmAdapterT, (ImmAdapterTBase, ImmAdapterErrorSkipTokenAPI), (), (), ());
  ImmAdapterT(org::imm::ImmAdapter const& other);
};

template <>
struct org::imm::ImmAdapterT<org::imm::ImmErrorSkipGroup> : public org::imm::ImmAdapterTBase<org::imm::ImmErrorSkipGroup>, public org::imm::ImmAdapterErrorSkipGroupAPI {
  USE_IMM_ADAPTER_BASE(org::imm::ImmErrorSkipGroup)
  using api_type = org::imm::ImmAdapterErrorSkipGroupAPI;
  BOOST_DESCRIBE_CLASS(ImmAdapterT, (ImmAdapterTBase, ImmAdapterErrorSkipGroupAPI), (), (), ());
  hstd::ext::ImmVec<org::imm::ImmIdT<org::imm::ImmErrorSkipToken>> getSkipped() const;
  ImmAdapterT(org::imm::ImmAdapter const& other);
};

template <>
struct org::imm::ImmAdapterT<org::imm::ImmMarkup> : public org::imm::ImmAdapterTBase<org::imm::ImmMarkup>, public org::imm::ImmAdapterMarkupAPI {
  USE_IMM_ADAPTER_BASE(org::imm::ImmMarkup)
  using api_type = org::imm::ImmAdapterMarkupAPI;
  BOOST_DESCRIBE_CLASS(ImmAdapterT, (ImmAdapterTBase, ImmAdapterMarkupAPI), (), (), ());
  ImmAdapterT(org::imm::ImmAdapter const& other);
};

template <>
struct org::imm::ImmAdapterT<org::imm::ImmBold> : public org::imm::ImmAdapterTBase<org::imm::ImmBold>, public org::imm::ImmAdapterBoldAPI {
  USE_IMM_ADAPTER_BASE(org::imm::ImmBold)
  using api_type = org::imm::ImmAdapterBoldAPI;
  BOOST_DESCRIBE_CLASS(ImmAdapterT, (ImmAdapterTBase, ImmAdapterBoldAPI), (), (), ());
  ImmAdapterT(org::imm::ImmAdapter const& other);
};

template <>
struct org::imm::ImmAdapterT<org::imm::ImmUnderline> : public org::imm::ImmAdapterTBase<org::imm::ImmUnderline>, public org::imm::ImmAdapterUnderlineAPI {
  USE_IMM_ADAPTER_BASE(org::imm::ImmUnderline)
  using api_type = org::imm::ImmAdapterUnderlineAPI;
  BOOST_DESCRIBE_CLASS(ImmAdapterT, (ImmAdapterTBase, ImmAdapterUnderlineAPI), (), (), ());
  ImmAdapterT(org::imm::ImmAdapter const& other);
};

template <>
struct org::imm::ImmAdapterT<org::imm::ImmMonospace> : public org::imm::ImmAdapterTBase<org::imm::ImmMonospace>, public org::imm::ImmAdapterMonospaceAPI {
  USE_IMM_ADAPTER_BASE(org::imm::ImmMonospace)
  using api_type = org::imm::ImmAdapterMonospaceAPI;
  BOOST_DESCRIBE_CLASS(ImmAdapterT, (ImmAdapterTBase, ImmAdapterMonospaceAPI), (), (), ());
  ImmAdapterT(org::imm::ImmAdapter const& other);
};

template <>
struct org::imm::ImmAdapterT<org::imm::ImmMarkQuote> : public org::imm::ImmAdapterTBase<org::imm::ImmMarkQuote>, public org::imm::ImmAdapterMarkQuoteAPI {
  USE_IMM_ADAPTER_BASE(org::imm::ImmMarkQuote)
  using api_type = org::imm::ImmAdapterMarkQuoteAPI;
  BOOST_DESCRIBE_CLASS(ImmAdapterT, (ImmAdapterTBase, ImmAdapterMarkQuoteAPI), (), (), ());
  ImmAdapterT(org::imm::ImmAdapter const& other);
};

template <>
struct org::imm::ImmAdapterT<org::imm::ImmVerbatim> : public org::imm::ImmAdapterTBase<org::imm::ImmVerbatim>, public org::imm::ImmAdapterVerbatimAPI {
  USE_IMM_ADAPTER_BASE(org::imm::ImmVerbatim)
  using api_type = org::imm::ImmAdapterVerbatimAPI;
  BOOST_DESCRIBE_CLASS(ImmAdapterT, (ImmAdapterTBase, ImmAdapterVerbatimAPI), (), (), ());
  ImmAdapterT(org::imm::ImmAdapter const& other);
};

template <>
struct org::imm::ImmAdapterT<org::imm::ImmItalic> : public org::imm::ImmAdapterTBase<org::imm::ImmItalic>, public org::imm::ImmAdapterItalicAPI {
  USE_IMM_ADAPTER_BASE(org::imm::ImmItalic)
  using api_type = org::imm::ImmAdapterItalicAPI;
  BOOST_DESCRIBE_CLASS(ImmAdapterT, (ImmAdapterTBase, ImmAdapterItalicAPI), (), (), ());
  ImmAdapterT(org::imm::ImmAdapter const& other);
};

template <>
struct org::imm::ImmAdapterT<org::imm::ImmStrike> : public org::imm::ImmAdapterTBase<org::imm::ImmStrike>, public org::imm::ImmAdapterStrikeAPI {
  USE_IMM_ADAPTER_BASE(org::imm::ImmStrike)
  using api_type = org::imm::ImmAdapterStrikeAPI;
  BOOST_DESCRIBE_CLASS(ImmAdapterT, (ImmAdapterTBase, ImmAdapterStrikeAPI), (), (), ());
  ImmAdapterT(org::imm::ImmAdapter const& other);
};

template <>
struct org::imm::ImmAdapterT<org::imm::ImmPar> : public org::imm::ImmAdapterTBase<org::imm::ImmPar>, public org::imm::ImmAdapterParAPI {
  USE_IMM_ADAPTER_BASE(org::imm::ImmPar)
  using api_type = org::imm::ImmAdapterParAPI;
  BOOST_DESCRIBE_CLASS(ImmAdapterT, (ImmAdapterTBase, ImmAdapterParAPI), (), (), ());
  ImmAdapterT(org::imm::ImmAdapter const& other);
};

template <>
struct org::imm::ImmAdapterT<org::imm::ImmRadioTarget> : public org::imm::ImmAdapterTBase<org::imm::ImmRadioTarget>, public org::imm::ImmAdapterRadioTargetAPI {
  USE_IMM_ADAPTER_BASE(org::imm::ImmRadioTarget)
  using api_type = org::imm::ImmAdapterRadioTargetAPI;
  BOOST_DESCRIBE_CLASS(ImmAdapterT, (ImmAdapterTBase, ImmAdapterRadioTargetAPI), (), (), ());
  hstd::ext::ImmVec<hstd::Str> getWords() const;
  ImmAdapterT(org::imm::ImmAdapter const& other);
};

template <>
struct org::imm::ImmAdapterT<org::imm::ImmLatex> : public org::imm::ImmAdapterTBase<org::imm::ImmLatex>, public org::imm::ImmAdapterLatexAPI {
  USE_IMM_ADAPTER_BASE(org::imm::ImmLatex)
  using api_type = org::imm::ImmAdapterLatexAPI;
  BOOST_DESCRIBE_CLASS(ImmAdapterT, (ImmAdapterTBase, ImmAdapterLatexAPI), (), (), ());
  ImmAdapterT(org::imm::ImmAdapter const& other);
};

template <>
struct org::imm::ImmAdapterT<org::imm::ImmLink> : public org::imm::ImmAdapterTBase<org::imm::ImmLink>, public org::imm::ImmAdapterLinkAPI {
  USE_IMM_ADAPTER_BASE(org::imm::ImmLink)
  using api_type = org::imm::ImmAdapterLinkAPI;
  BOOST_DESCRIBE_CLASS(ImmAdapterT, (ImmAdapterTBase, ImmAdapterLinkAPI), (), (), ());
  hstd::Opt<org::imm::ImmAdapterT<org::imm::ImmParagraph>> getDescription() const;
  org::sem::LinkTarget getTarget() const;
  ImmAdapterT(org::imm::ImmAdapter const& other);
};

template <>
struct org::imm::ImmAdapterT<org::imm::ImmBlockCenter> : public org::imm::ImmAdapterTBase<org::imm::ImmBlockCenter>, public org::imm::ImmAdapterBlockCenterAPI {
  USE_IMM_ADAPTER_BASE(org::imm::ImmBlockCenter)
  using api_type = org::imm::ImmAdapterBlockCenterAPI;
  BOOST_DESCRIBE_CLASS(ImmAdapterT, (ImmAdapterTBase, ImmAdapterBlockCenterAPI), (), (), ());
  ImmAdapterT(org::imm::ImmAdapter const& other);
};

template <>
struct org::imm::ImmAdapterT<org::imm::ImmBlockQuote> : public org::imm::ImmAdapterTBase<org::imm::ImmBlockQuote>, public org::imm::ImmAdapterBlockQuoteAPI {
  USE_IMM_ADAPTER_BASE(org::imm::ImmBlockQuote)
  using api_type = org::imm::ImmAdapterBlockQuoteAPI;
  BOOST_DESCRIBE_CLASS(ImmAdapterT, (ImmAdapterTBase, ImmAdapterBlockQuoteAPI), (), (), ());
  ImmAdapterT(org::imm::ImmAdapter const& other);
};

template <>
struct org::imm::ImmAdapterT<org::imm::ImmBlockComment> : public org::imm::ImmAdapterTBase<org::imm::ImmBlockComment>, public org::imm::ImmAdapterBlockCommentAPI {
  USE_IMM_ADAPTER_BASE(org::imm::ImmBlockComment)
  using api_type = org::imm::ImmAdapterBlockCommentAPI;
  BOOST_DESCRIBE_CLASS(ImmAdapterT, (ImmAdapterTBase, ImmAdapterBlockCommentAPI), (), (), ());
  ImmAdapterT(org::imm::ImmAdapter const& other);
};

template <>
struct org::imm::ImmAdapterT<org::imm::ImmBlockVerse> : public org::imm::ImmAdapterTBase<org::imm::ImmBlockVerse>, public org::imm::ImmAdapterBlockVerseAPI {
  USE_IMM_ADAPTER_BASE(org::imm::ImmBlockVerse)
  using api_type = org::imm::ImmAdapterBlockVerseAPI;
  BOOST_DESCRIBE_CLASS(ImmAdapterT, (ImmAdapterTBase, ImmAdapterBlockVerseAPI), (), (), ());
  ImmAdapterT(org::imm::ImmAdapter const& other);
};

template <>
struct org::imm::ImmAdapterT<org::imm::ImmBlockDynamicFallback> : public org::imm::ImmAdapterTBase<org::imm::ImmBlockDynamicFallback>, public org::imm::ImmAdapterBlockDynamicFallbackAPI {
  USE_IMM_ADAPTER_BASE(org::imm::ImmBlockDynamicFallback)
  using api_type = org::imm::ImmAdapterBlockDynamicFallbackAPI;
  BOOST_DESCRIBE_CLASS(ImmAdapterT, (ImmAdapterTBase, ImmAdapterBlockDynamicFallbackAPI), (), (), ());
  hstd::Str const& getName() const;
  ImmAdapterT(org::imm::ImmAdapter const& other);
};

template <>
struct org::imm::ImmAdapterT<org::imm::ImmBlockExample> : public org::imm::ImmAdapterTBase<org::imm::ImmBlockExample>, public org::imm::ImmAdapterBlockExampleAPI {
  USE_IMM_ADAPTER_BASE(org::imm::ImmBlockExample)
  using api_type = org::imm::ImmAdapterBlockExampleAPI;
  BOOST_DESCRIBE_CLASS(ImmAdapterT, (ImmAdapterTBase, ImmAdapterBlockExampleAPI), (), (), ());
  ImmAdapterT(org::imm::ImmAdapter const& other);
};

template <>
struct org::imm::ImmAdapterT<org::imm::ImmBlockExport> : public org::imm::ImmAdapterTBase<org::imm::ImmBlockExport>, public org::imm::ImmAdapterBlockExportAPI {
  USE_IMM_ADAPTER_BASE(org::imm::ImmBlockExport)
  using api_type = org::imm::ImmAdapterBlockExportAPI;
  BOOST_DESCRIBE_CLASS(ImmAdapterT, (ImmAdapterTBase, ImmAdapterBlockExportAPI), (), (), ());
  hstd::Str const& getExporter() const;
  hstd::Str const& getContent() const;
  ImmAdapterT(org::imm::ImmAdapter const& other);
};

template <>
struct org::imm::ImmAdapterT<org::imm::ImmBlockAdmonition> : public org::imm::ImmAdapterTBase<org::imm::ImmBlockAdmonition>, public org::imm::ImmAdapterBlockAdmonitionAPI {
  USE_IMM_ADAPTER_BASE(org::imm::ImmBlockAdmonition)
  using api_type = org::imm::ImmAdapterBlockAdmonitionAPI;
  BOOST_DESCRIBE_CLASS(ImmAdapterT, (ImmAdapterTBase, ImmAdapterBlockAdmonitionAPI), (), (), ());
  ImmAdapterT(org::imm::ImmAdapter const& other);
};

template <>
struct org::imm::ImmAdapterT<org::imm::ImmBlockCodeEvalResult> : public org::imm::ImmAdapterTBase<org::imm::ImmBlockCodeEvalResult>, public org::imm::ImmAdapterBlockCodeEvalResultAPI {
  USE_IMM_ADAPTER_BASE(org::imm::ImmBlockCodeEvalResult)
  using api_type = org::imm::ImmAdapterBlockCodeEvalResultAPI;
  BOOST_DESCRIBE_CLASS(ImmAdapterT, (ImmAdapterTBase, ImmAdapterBlockCodeEvalResultAPI), (), (), ());
  hstd::ext::ImmVec<org::sem::OrgCodeEvalOutput> getRaw() const;
  org::imm::ImmAdapter getNode() const;
  ImmAdapterT(org::imm::ImmAdapter const& other);
};

template <>
struct org::imm::ImmAdapterT<org::imm::ImmBlockCode> : public org::imm::ImmAdapterTBase<org::imm::ImmBlockCode>, public org::imm::ImmAdapterBlockCodeAPI {
  USE_IMM_ADAPTER_BASE(org::imm::ImmBlockCode)
  using api_type = org::imm::ImmAdapterBlockCodeAPI;
  BOOST_DESCRIBE_CLASS(ImmAdapterT, (ImmAdapterTBase, ImmAdapterBlockCodeAPI), (), (), ());
  hstd::Opt<hstd::Str> const& getLang() const;
  hstd::ext::ImmVec<org::imm::ImmIdT<org::imm::ImmBlockCodeEvalResult>> getResult() const;
  hstd::ext::ImmVec<org::sem::BlockCodeLine> getLines() const;
  org::sem::AttrGroup getSwitches() const;
  ImmAdapterT(org::imm::ImmAdapter const& other);
};

template <>
struct org::imm::ImmAdapterT<org::imm::ImmSubtreeLog> : public org::imm::ImmAdapterTBase<org::imm::ImmSubtreeLog>, public org::imm::ImmAdapterSubtreeLogAPI {
  USE_IMM_ADAPTER_BASE(org::imm::ImmSubtreeLog)
  using api_type = org::imm::ImmAdapterSubtreeLogAPI;
  BOOST_DESCRIBE_CLASS(ImmAdapterT, (ImmAdapterTBase, ImmAdapterSubtreeLogAPI), (), (), ());
  org::sem::SubtreeLogHead getHead() const;
  hstd::Opt<org::imm::ImmAdapterT<org::imm::ImmStmtList>> getDesc() const;
  ImmAdapterT(org::imm::ImmAdapter const& other);
};

template <>
struct org::imm::ImmAdapterT<org::imm::ImmSubtree> : public org::imm::ImmAdapterTBase<org::imm::ImmSubtree>, public org::imm::ImmAdapterSubtreeAPI {
  USE_IMM_ADAPTER_BASE(org::imm::ImmSubtree)
  using api_type = org::imm::ImmAdapterSubtreeAPI;
  BOOST_DESCRIBE_CLASS(ImmAdapterT, (ImmAdapterTBase, ImmAdapterSubtreeAPI), (), (), ());
  int getLevel() const;
  hstd::Opt<hstd::Str> const& getTreeId() const;
  hstd::Opt<hstd::Str> const& getTodo() const;
  hstd::Opt<org::sem::SubtreeCompletion> const& getCompletion() const;
  hstd::Opt<org::imm::ImmAdapterT<org::imm::ImmParagraph>> getDescription() const;
  hstd::ext::ImmVec<org::imm::ImmIdT<org::imm::ImmHashTag>> getTags() const;
  org::imm::ImmAdapter getTitle() const;
  hstd::ext::ImmVec<org::imm::ImmIdT<org::imm::ImmSubtreeLog>> getLogbook() const;
  hstd::ext::ImmVec<org::sem::NamedProperty> getProperties() const;
  hstd::Opt<org::imm::ImmAdapterT<org::imm::ImmTime>> getClosed() const;
  hstd::Opt<org::imm::ImmAdapterT<org::imm::ImmTime>> getDeadline() const;
  hstd::Opt<org::imm::ImmAdapterT<org::imm::ImmTime>> getScheduled() const;
  bool getIsComment() const;
  bool getIsArchived() const;
  hstd::Opt<hstd::Str> const& getPriority() const;
  ImmAdapterT(org::imm::ImmAdapter const& other);
};

template <>
struct org::imm::ImmAdapterT<org::imm::ImmCell> : public org::imm::ImmAdapterTBase<org::imm::ImmCell>, public org::imm::ImmAdapterCellAPI {
  USE_IMM_ADAPTER_BASE(org::imm::ImmCell)
  using api_type = org::imm::ImmAdapterCellAPI;
  BOOST_DESCRIBE_CLASS(ImmAdapterT, (ImmAdapterTBase, ImmAdapterCellAPI), (), (), ());
  bool getIsBlock() const;
  ImmAdapterT(org::imm::ImmAdapter const& other);
};

template <>
struct org::imm::ImmAdapterT<org::imm::ImmRow> : public org::imm::ImmAdapterTBase<org::imm::ImmRow>, public org::imm::ImmAdapterRowAPI {
  USE_IMM_ADAPTER_BASE(org::imm::ImmRow)
  using api_type = org::imm::ImmAdapterRowAPI;
  BOOST_DESCRIBE_CLASS(ImmAdapterT, (ImmAdapterTBase, ImmAdapterRowAPI), (), (), ());
  hstd::ext::ImmVec<org::imm::ImmIdT<org::imm::ImmCell>> getCells() const;
  bool getIsBlock() const;
  ImmAdapterT(org::imm::ImmAdapter const& other);
};

template <>
struct org::imm::ImmAdapterT<org::imm::ImmTable> : public org::imm::ImmAdapterTBase<org::imm::ImmTable>, public org::imm::ImmAdapterTableAPI {
  USE_IMM_ADAPTER_BASE(org::imm::ImmTable)
  using api_type = org::imm::ImmAdapterTableAPI;
  BOOST_DESCRIBE_CLASS(ImmAdapterT, (ImmAdapterTBase, ImmAdapterTableAPI), (), (), ());
  hstd::ext::ImmVec<org::imm::ImmIdT<org::imm::ImmRow>> getRows() const;
  bool getIsBlock() const;
  ImmAdapterT(org::imm::ImmAdapter const& other);
};

template <>
struct org::imm::ImmAdapterT<org::imm::ImmParagraph> : public org::imm::ImmAdapterTBase<org::imm::ImmParagraph>, public org::imm::ImmAdapterParagraphAPI {
  USE_IMM_ADAPTER_BASE(org::imm::ImmParagraph)
  using api_type = org::imm::ImmAdapterParagraphAPI;
  BOOST_DESCRIBE_CLASS(ImmAdapterT, (ImmAdapterTBase, ImmAdapterParagraphAPI), (), (), ());
  ImmAdapterT(org::imm::ImmAdapter const& other);
};

template <>
struct org::imm::ImmAdapterT<org::imm::ImmColonExample> : public org::imm::ImmAdapterTBase<org::imm::ImmColonExample>, public org::imm::ImmAdapterColonExampleAPI {
  USE_IMM_ADAPTER_BASE(org::imm::ImmColonExample)
  using api_type = org::imm::ImmAdapterColonExampleAPI;
  BOOST_DESCRIBE_CLASS(ImmAdapterT, (ImmAdapterTBase, ImmAdapterColonExampleAPI), (), (), ());
  ImmAdapterT(org::imm::ImmAdapter const& other);
};

template <>
struct org::imm::ImmAdapterT<org::imm::ImmCmdAttr> : public org::imm::ImmAdapterTBase<org::imm::ImmCmdAttr>, public org::imm::ImmAdapterCmdAttrAPI {
  USE_IMM_ADAPTER_BASE(org::imm::ImmCmdAttr)
  using api_type = org::imm::ImmAdapterCmdAttrAPI;
  BOOST_DESCRIBE_CLASS(ImmAdapterT, (ImmAdapterTBase, ImmAdapterCmdAttrAPI), (), (), ());
  hstd::Str const& getTarget() const;
  ImmAdapterT(org::imm::ImmAdapter const& other);
};

template <>
struct org::imm::ImmAdapterT<org::imm::ImmCmdExport> : public org::imm::ImmAdapterTBase<org::imm::ImmCmdExport>, public org::imm::ImmAdapterCmdExportAPI {
  USE_IMM_ADAPTER_BASE(org::imm::ImmCmdExport)
  using api_type = org::imm::ImmAdapterCmdExportAPI;
  BOOST_DESCRIBE_CLASS(ImmAdapterT, (ImmAdapterTBase, ImmAdapterCmdExportAPI), (), (), ());
  hstd::Str const& getExporter() const;
  hstd::Str const& getContent() const;
  ImmAdapterT(org::imm::ImmAdapter const& other);
};

template <>
struct org::imm::ImmAdapterT<org::imm::ImmCall> : public org::imm::ImmAdapterTBase<org::imm::ImmCall>, public org::imm::ImmAdapterCallAPI {
  USE_IMM_ADAPTER_BASE(org::imm::ImmCall)
  using api_type = org::imm::ImmAdapterCallAPI;
  BOOST_DESCRIBE_CLASS(ImmAdapterT, (ImmAdapterTBase, ImmAdapterCallAPI), (), (), ());
  hstd::Str const& getName() const;
  org::sem::AttrGroup getAttrs() const;
  bool getIsCommand() const;
  ImmAdapterT(org::imm::ImmAdapter const& other);
};

template <>
struct org::imm::ImmAdapterT<org::imm::ImmList> : public org::imm::ImmAdapterTBase<org::imm::ImmList>, public org::imm::ImmAdapterListAPI {
  USE_IMM_ADAPTER_BASE(org::imm::ImmList)
  using api_type = org::imm::ImmAdapterListAPI;
  BOOST_DESCRIBE_CLASS(ImmAdapterT, (ImmAdapterTBase, ImmAdapterListAPI), (), (), ());
  ImmAdapterT(org::imm::ImmAdapter const& other);
};

template <>
struct org::imm::ImmAdapterT<org::imm::ImmListItem> : public org::imm::ImmAdapterTBase<org::imm::ImmListItem>, public org::imm::ImmAdapterListItemAPI {
  USE_IMM_ADAPTER_BASE(org::imm::ImmListItem)
  using api_type = org::imm::ImmAdapterListItemAPI;
  BOOST_DESCRIBE_CLASS(ImmAdapterT, (ImmAdapterTBase, ImmAdapterListItemAPI), (), (), ());
  CheckboxState getCheckbox() const;
  hstd::Opt<org::imm::ImmAdapterT<org::imm::ImmParagraph>> getHeader() const;
  hstd::Opt<hstd::Str> const& getBullet() const;
  ImmAdapterT(org::imm::ImmAdapter const& other);
};

template <>
struct org::imm::ImmAdapterT<org::imm::ImmDocumentOptions> : public org::imm::ImmAdapterTBase<org::imm::ImmDocumentOptions>, public org::imm::ImmAdapterDocumentOptionsAPI {
  USE_IMM_ADAPTER_BASE(org::imm::ImmDocumentOptions)
  using api_type = org::imm::ImmAdapterDocumentOptionsAPI;
  BOOST_DESCRIBE_CLASS(ImmAdapterT, (ImmAdapterTBase, ImmAdapterDocumentOptionsAPI), (), (), ());
  InitialSubtreeVisibility getInitialVisibility() const;
  hstd::ext::ImmVec<org::sem::NamedProperty> getProperties() const;
  org::sem::DocumentExportConfig getExportConfig() const;
  hstd::Opt<bool> const& getFixedWidthSections() const;
  hstd::Opt<bool> const& getStartupIndented() const;
  hstd::Opt<hstd::Str> const& getCategory() const;
  hstd::Opt<hstd::Str> const& getSetupfile() const;
  hstd::Opt<int> const& getMaxSubtreeLevelExport() const;
  hstd::Opt<org::sem::ColumnView> const& getColumns() const;
  hstd::ext::ImmVec<org::sem::TodoKeyword> getTodoKeywords() const;
  hstd::ext::ImmVec<org::sem::TodoKeyword> getDoneKeywords() const;
  ImmAdapterT(org::imm::ImmAdapter const& other);
};

template <>
struct org::imm::ImmAdapterT<org::imm::ImmDocumentFragment> : public org::imm::ImmAdapterTBase<org::imm::ImmDocumentFragment>, public org::imm::ImmAdapterDocumentFragmentAPI {
  USE_IMM_ADAPTER_BASE(org::imm::ImmDocumentFragment)
  using api_type = org::imm::ImmAdapterDocumentFragmentAPI;
  BOOST_DESCRIBE_CLASS(ImmAdapterT, (ImmAdapterTBase, ImmAdapterDocumentFragmentAPI), (), (), ());
  int getBaseLine() const;
  int getBaseCol() const;
  ImmAdapterT(org::imm::ImmAdapter const& other);
};

template <>
struct org::imm::ImmAdapterT<org::imm::ImmCriticMarkup> : public org::imm::ImmAdapterTBase<org::imm::ImmCriticMarkup>, public org::imm::ImmAdapterCriticMarkupAPI {
  USE_IMM_ADAPTER_BASE(org::imm::ImmCriticMarkup)
  using api_type = org::imm::ImmAdapterCriticMarkupAPI;
  BOOST_DESCRIBE_CLASS(ImmAdapterT, (ImmAdapterTBase, ImmAdapterCriticMarkupAPI), (), (), ());
  org::imm::ImmCriticMarkup::Kind getKind() const;
  ImmAdapterT(org::imm::ImmAdapter const& other);
};

template <>
struct org::imm::ImmAdapterT<org::imm::ImmDocument> : public org::imm::ImmAdapterTBase<org::imm::ImmDocument>, public org::imm::ImmAdapterDocumentAPI {
  USE_IMM_ADAPTER_BASE(org::imm::ImmDocument)
  using api_type = org::imm::ImmAdapterDocumentAPI;
  BOOST_DESCRIBE_CLASS(ImmAdapterT, (ImmAdapterTBase, ImmAdapterDocumentAPI), (), (), ());
  hstd::Opt<org::imm::ImmAdapterT<org::imm::ImmParagraph>> getTitle() const;
  hstd::Opt<org::imm::ImmAdapterT<org::imm::ImmParagraph>> getAuthor() const;
  hstd::Opt<org::imm::ImmAdapterT<org::imm::ImmParagraph>> getCreator() const;
  hstd::ext::ImmVec<org::imm::ImmIdT<org::imm::ImmHashTag>> getFiletags() const;
  hstd::Opt<org::imm::ImmAdapterT<org::imm::ImmRawText>> getEmail() const;
  hstd::ext::ImmVec<hstd::Str> getLanguage() const;
  org::imm::ImmAdapter getOptions() const;
  hstd::Opt<hstd::Str> const& getExportFileName() const;
  ImmAdapterT(org::imm::ImmAdapter const& other);
};

template <>
struct org::imm::ImmAdapterT<org::imm::ImmFileTarget> : public org::imm::ImmAdapterTBase<org::imm::ImmFileTarget>, public org::imm::ImmAdapterFileTargetAPI {
  USE_IMM_ADAPTER_BASE(org::imm::ImmFileTarget)
  using api_type = org::imm::ImmAdapterFileTargetAPI;
  BOOST_DESCRIBE_CLASS(ImmAdapterT, (ImmAdapterTBase, ImmAdapterFileTargetAPI), (), (), ());
  hstd::Str const& getPath() const;
  hstd::Opt<int> const& getLine() const;
  hstd::Opt<hstd::Str> const& getSearchTarget() const;
  bool getRestrictToHeadlines() const;
  hstd::Opt<hstd::Str> const& getTargetId() const;
  hstd::Opt<hstd::Str> const& getRegexp() const;
  ImmAdapterT(org::imm::ImmAdapter const& other);
};

template <>
struct org::imm::ImmAdapterT<org::imm::ImmTextSeparator> : public org::imm::ImmAdapterTBase<org::imm::ImmTextSeparator>, public org::imm::ImmAdapterTextSeparatorAPI {
  USE_IMM_ADAPTER_BASE(org::imm::ImmTextSeparator)
  using api_type = org::imm::ImmAdapterTextSeparatorAPI;
  BOOST_DESCRIBE_CLASS(ImmAdapterT, (ImmAdapterTBase, ImmAdapterTextSeparatorAPI), (), (), ());
  ImmAdapterT(org::imm::ImmAdapter const& other);
};

template <>
struct org::imm::ImmAdapterT<org::imm::ImmDocumentGroup> : public org::imm::ImmAdapterTBase<org::imm::ImmDocumentGroup>, public org::imm::ImmAdapterDocumentGroupAPI {
  USE_IMM_ADAPTER_BASE(org::imm::ImmDocumentGroup)
  using api_type = org::imm::ImmAdapterDocumentGroupAPI;
  BOOST_DESCRIBE_CLASS(ImmAdapterT, (ImmAdapterTBase, ImmAdapterDocumentGroupAPI), (), (), ());
  ImmAdapterT(org::imm::ImmAdapter const& other);
};

template <>
struct org::imm::ImmAdapterT<org::imm::ImmFile> : public org::imm::ImmAdapterTBase<org::imm::ImmFile>, public org::imm::ImmAdapterFileAPI {
  USE_IMM_ADAPTER_BASE(org::imm::ImmFile)
  using api_type = org::imm::ImmAdapterFileAPI;
  BOOST_DESCRIBE_CLASS(ImmAdapterT, (ImmAdapterTBase, ImmAdapterFileAPI), (), (), ());
  hstd::Str const& getRelPath() const;
  hstd::Str const& getAbsPath() const;
  org::imm::ImmFile::Data getData() const;
  ImmAdapterT(org::imm::ImmAdapter const& other);
};

template <>
struct org::imm::ImmAdapterT<org::imm::ImmDirectory> : public org::imm::ImmAdapterTBase<org::imm::ImmDirectory>, public org::imm::ImmAdapterDirectoryAPI {
  USE_IMM_ADAPTER_BASE(org::imm::ImmDirectory)
  using api_type = org::imm::ImmAdapterDirectoryAPI;
  BOOST_DESCRIBE_CLASS(ImmAdapterT, (ImmAdapterTBase, ImmAdapterDirectoryAPI), (), (), ());
  hstd::Str const& getRelPath() const;
  hstd::Str const& getAbsPath() const;
  ImmAdapterT(org::imm::ImmAdapter const& other);
};

template <>
struct org::imm::ImmAdapterT<org::imm::ImmSymlink> : public org::imm::ImmAdapterTBase<org::imm::ImmSymlink>, public org::imm::ImmAdapterSymlinkAPI {
  USE_IMM_ADAPTER_BASE(org::imm::ImmSymlink)
  using api_type = org::imm::ImmAdapterSymlinkAPI;
  BOOST_DESCRIBE_CLASS(ImmAdapterT, (ImmAdapterTBase, ImmAdapterSymlinkAPI), (), (), ());
  bool getIsDirectory() const;
  hstd::Str const& getAbsPath() const;
  ImmAdapterT(org::imm::ImmAdapter const& other);
};

template <>
struct org::imm::ImmAdapterT<org::imm::ImmCmdInclude> : public org::imm::ImmAdapterTBase<org::imm::ImmCmdInclude>, public org::imm::ImmAdapterCmdIncludeAPI {
  USE_IMM_ADAPTER_BASE(org::imm::ImmCmdInclude)
  using api_type = org::imm::ImmAdapterCmdIncludeAPI;
  BOOST_DESCRIBE_CLASS(ImmAdapterT, (ImmAdapterTBase, ImmAdapterCmdIncludeAPI), (), (), ());
  hstd::Str const& getPath() const;
  hstd::Opt<int> const& getFirstLine() const;
  hstd::Opt<int> const& getLastLine() const;
  org::imm::ImmCmdInclude::Data getData() const;
  ImmAdapterT(org::imm::ImmAdapter const& other);
};

}
/* clang-format on */