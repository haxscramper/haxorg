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
  ImmAdapterT(org::imm::ImmAdapter const& other);
  org::sem::OrgDiagnostics const& getDiag() const;
};

template <>
struct org::imm::ImmAdapterT<org::imm::ImmErrorGroup> : public org::imm::ImmAdapterTBase<org::imm::ImmErrorGroup>, public org::imm::ImmAdapterErrorGroupAPI {
  USE_IMM_ADAPTER_BASE(org::imm::ImmErrorGroup)
  using api_type = org::imm::ImmAdapterErrorGroupAPI;
  BOOST_DESCRIBE_CLASS(ImmAdapterT, (ImmAdapterTBase, ImmAdapterErrorGroupAPI), (), (), ());
  ImmAdapterT(org::imm::ImmAdapter const& other);
  hstd::ext::ImmVec<org::imm::ImmIdT<org::imm::ImmErrorItem>> const& getDiagnostics() const;
};

template <>
struct org::imm::ImmAdapterT<org::imm::ImmStmt> : public org::imm::ImmAdapterTBase<org::imm::ImmStmt>, public org::imm::ImmAdapterStmtAPI {
  USE_IMM_ADAPTER_BASE(org::imm::ImmStmt)
  using api_type = org::imm::ImmAdapterStmtAPI;
  BOOST_DESCRIBE_CLASS(ImmAdapterT, (ImmAdapterTBase, ImmAdapterStmtAPI), (), (), ());
  ImmAdapterT(org::imm::ImmAdapter const& other);
  hstd::ext::ImmVec<org::imm::ImmIdT<org::imm::ImmOrg>> const& getAttached() const;
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
  ImmAdapterT(org::imm::ImmAdapter const& other);
  org::sem::AttrGroup const& getAttrs() const;
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
  ImmAdapterT(org::imm::ImmAdapter const& other);
  hstd::Str const& getText() const;
};

template <>
struct org::imm::ImmAdapterT<org::imm::ImmCmdCaption> : public org::imm::ImmAdapterTBase<org::imm::ImmCmdCaption>, public org::imm::ImmAdapterCmdCaptionAPI {
  USE_IMM_ADAPTER_BASE(org::imm::ImmCmdCaption)
  using api_type = org::imm::ImmAdapterCmdCaptionAPI;
  BOOST_DESCRIBE_CLASS(ImmAdapterT, (ImmAdapterTBase, ImmAdapterCmdCaptionAPI), (), (), ());
  ImmAdapterT(org::imm::ImmAdapter const& other);
  org::imm::ImmIdT<org::imm::ImmParagraph> const& getText() const;
};

template <>
struct org::imm::ImmAdapterT<org::imm::ImmCmdCreator> : public org::imm::ImmAdapterTBase<org::imm::ImmCmdCreator>, public org::imm::ImmAdapterCmdCreatorAPI {
  USE_IMM_ADAPTER_BASE(org::imm::ImmCmdCreator)
  using api_type = org::imm::ImmAdapterCmdCreatorAPI;
  BOOST_DESCRIBE_CLASS(ImmAdapterT, (ImmAdapterTBase, ImmAdapterCmdCreatorAPI), (), (), ());
  ImmAdapterT(org::imm::ImmAdapter const& other);
  org::imm::ImmIdT<org::imm::ImmParagraph> const& getText() const;
};

template <>
struct org::imm::ImmAdapterT<org::imm::ImmCmdAuthor> : public org::imm::ImmAdapterTBase<org::imm::ImmCmdAuthor>, public org::imm::ImmAdapterCmdAuthorAPI {
  USE_IMM_ADAPTER_BASE(org::imm::ImmCmdAuthor)
  using api_type = org::imm::ImmAdapterCmdAuthorAPI;
  BOOST_DESCRIBE_CLASS(ImmAdapterT, (ImmAdapterTBase, ImmAdapterCmdAuthorAPI), (), (), ());
  ImmAdapterT(org::imm::ImmAdapter const& other);
  org::imm::ImmIdT<org::imm::ImmParagraph> const& getText() const;
};

template <>
struct org::imm::ImmAdapterT<org::imm::ImmCmdEmail> : public org::imm::ImmAdapterTBase<org::imm::ImmCmdEmail>, public org::imm::ImmAdapterCmdEmailAPI {
  USE_IMM_ADAPTER_BASE(org::imm::ImmCmdEmail)
  using api_type = org::imm::ImmAdapterCmdEmailAPI;
  BOOST_DESCRIBE_CLASS(ImmAdapterT, (ImmAdapterTBase, ImmAdapterCmdEmailAPI), (), (), ());
  ImmAdapterT(org::imm::ImmAdapter const& other);
  hstd::Str const& getText() const;
};

template <>
struct org::imm::ImmAdapterT<org::imm::ImmCmdLanguage> : public org::imm::ImmAdapterTBase<org::imm::ImmCmdLanguage>, public org::imm::ImmAdapterCmdLanguageAPI {
  USE_IMM_ADAPTER_BASE(org::imm::ImmCmdLanguage)
  using api_type = org::imm::ImmAdapterCmdLanguageAPI;
  BOOST_DESCRIBE_CLASS(ImmAdapterT, (ImmAdapterTBase, ImmAdapterCmdLanguageAPI), (), (), ());
  ImmAdapterT(org::imm::ImmAdapter const& other);
  hstd::Str const& getText() const;
};

template <>
struct org::imm::ImmAdapterT<org::imm::ImmCmdColumns> : public org::imm::ImmAdapterTBase<org::imm::ImmCmdColumns>, public org::imm::ImmAdapterCmdColumnsAPI {
  USE_IMM_ADAPTER_BASE(org::imm::ImmCmdColumns)
  using api_type = org::imm::ImmAdapterCmdColumnsAPI;
  BOOST_DESCRIBE_CLASS(ImmAdapterT, (ImmAdapterTBase, ImmAdapterCmdColumnsAPI), (), (), ());
  ImmAdapterT(org::imm::ImmAdapter const& other);
  org::sem::ColumnView const& getView() const;
};

template <>
struct org::imm::ImmAdapterT<org::imm::ImmCmdName> : public org::imm::ImmAdapterTBase<org::imm::ImmCmdName>, public org::imm::ImmAdapterCmdNameAPI {
  USE_IMM_ADAPTER_BASE(org::imm::ImmCmdName)
  using api_type = org::imm::ImmAdapterCmdNameAPI;
  BOOST_DESCRIBE_CLASS(ImmAdapterT, (ImmAdapterTBase, ImmAdapterCmdNameAPI), (), (), ());
  ImmAdapterT(org::imm::ImmAdapter const& other);
  hstd::Str const& getName() const;
};

template <>
struct org::imm::ImmAdapterT<org::imm::ImmCmdCustomArgs> : public org::imm::ImmAdapterTBase<org::imm::ImmCmdCustomArgs>, public org::imm::ImmAdapterCmdCustomArgsAPI {
  USE_IMM_ADAPTER_BASE(org::imm::ImmCmdCustomArgs)
  using api_type = org::imm::ImmAdapterCmdCustomArgsAPI;
  BOOST_DESCRIBE_CLASS(ImmAdapterT, (ImmAdapterTBase, ImmAdapterCmdCustomArgsAPI), (), (), ());
  ImmAdapterT(org::imm::ImmAdapter const& other);
  hstd::Str const& getName() const;
  bool const& getIsAttached() const;
};

template <>
struct org::imm::ImmAdapterT<org::imm::ImmCmdCustomRaw> : public org::imm::ImmAdapterTBase<org::imm::ImmCmdCustomRaw>, public org::imm::ImmAdapterCmdCustomRawAPI {
  USE_IMM_ADAPTER_BASE(org::imm::ImmCmdCustomRaw)
  using api_type = org::imm::ImmAdapterCmdCustomRawAPI;
  BOOST_DESCRIBE_CLASS(ImmAdapterT, (ImmAdapterTBase, ImmAdapterCmdCustomRawAPI), (), (), ());
  ImmAdapterT(org::imm::ImmAdapter const& other);
  hstd::Str const& getName() const;
  bool const& getIsAttached() const;
  hstd::Str const& getText() const;
};

template <>
struct org::imm::ImmAdapterT<org::imm::ImmCmdCustomText> : public org::imm::ImmAdapterTBase<org::imm::ImmCmdCustomText>, public org::imm::ImmAdapterCmdCustomTextAPI {
  USE_IMM_ADAPTER_BASE(org::imm::ImmCmdCustomText)
  using api_type = org::imm::ImmAdapterCmdCustomTextAPI;
  BOOST_DESCRIBE_CLASS(ImmAdapterT, (ImmAdapterTBase, ImmAdapterCmdCustomTextAPI), (), (), ());
  ImmAdapterT(org::imm::ImmAdapter const& other);
  hstd::Str const& getName() const;
  bool const& getIsAttached() const;
  org::imm::ImmIdT<org::imm::ImmParagraph> const& getText() const;
};

template <>
struct org::imm::ImmAdapterT<org::imm::ImmCmdCall> : public org::imm::ImmAdapterTBase<org::imm::ImmCmdCall>, public org::imm::ImmAdapterCmdCallAPI {
  USE_IMM_ADAPTER_BASE(org::imm::ImmCmdCall)
  using api_type = org::imm::ImmAdapterCmdCallAPI;
  BOOST_DESCRIBE_CLASS(ImmAdapterT, (ImmAdapterTBase, ImmAdapterCmdCallAPI), (), (), ());
  ImmAdapterT(org::imm::ImmAdapter const& other);
  hstd::Str const& getName() const;
  hstd::Opt<hstd::Str> const& getFileName() const;
  org::sem::AttrGroup const& getInsideHeaderAttrs() const;
  org::sem::AttrGroup const& getCallAttrs() const;
  org::sem::AttrGroup const& getEndHeaderAttrs() const;
  hstd::ext::ImmVec<org::imm::ImmIdT<org::imm::ImmBlockCodeEvalResult>> const& getResult() const;
};

template <>
struct org::imm::ImmAdapterT<org::imm::ImmCmdTblfm> : public org::imm::ImmAdapterTBase<org::imm::ImmCmdTblfm>, public org::imm::ImmAdapterCmdTblfmAPI {
  USE_IMM_ADAPTER_BASE(org::imm::ImmCmdTblfm)
  using api_type = org::imm::ImmAdapterCmdTblfmAPI;
  BOOST_DESCRIBE_CLASS(ImmAdapterT, (ImmAdapterTBase, ImmAdapterCmdTblfmAPI), (), (), ());
  ImmAdapterT(org::imm::ImmAdapter const& other);
  org::sem::Tblfm const& getExpr() const;
};

template <>
struct org::imm::ImmAdapterT<org::imm::ImmHashTag> : public org::imm::ImmAdapterTBase<org::imm::ImmHashTag>, public org::imm::ImmAdapterHashTagAPI {
  USE_IMM_ADAPTER_BASE(org::imm::ImmHashTag)
  using api_type = org::imm::ImmAdapterHashTagAPI;
  BOOST_DESCRIBE_CLASS(ImmAdapterT, (ImmAdapterTBase, ImmAdapterHashTagAPI), (), (), ());
  ImmAdapterT(org::imm::ImmAdapter const& other);
  org::sem::HashTagText const& getText() const;
};

template <>
struct org::imm::ImmAdapterT<org::imm::ImmInlineFootnote> : public org::imm::ImmAdapterTBase<org::imm::ImmInlineFootnote>, public org::imm::ImmAdapterInlineFootnoteAPI {
  USE_IMM_ADAPTER_BASE(org::imm::ImmInlineFootnote)
  using api_type = org::imm::ImmAdapterInlineFootnoteAPI;
  BOOST_DESCRIBE_CLASS(ImmAdapterT, (ImmAdapterTBase, ImmAdapterInlineFootnoteAPI), (), (), ());
  ImmAdapterT(org::imm::ImmAdapter const& other);
  hstd::Str const& getTag() const;
  hstd::Opt<org::imm::ImmIdT<org::imm::ImmOrg>> const& getDefinition() const;
};

template <>
struct org::imm::ImmAdapterT<org::imm::ImmInlineExport> : public org::imm::ImmAdapterTBase<org::imm::ImmInlineExport>, public org::imm::ImmAdapterInlineExportAPI {
  USE_IMM_ADAPTER_BASE(org::imm::ImmInlineExport)
  using api_type = org::imm::ImmAdapterInlineExportAPI;
  BOOST_DESCRIBE_CLASS(ImmAdapterT, (ImmAdapterTBase, ImmAdapterInlineExportAPI), (), (), ());
  ImmAdapterT(org::imm::ImmAdapter const& other);
  hstd::Str const& getExporter() const;
  hstd::Str const& getContent() const;
};

template <>
struct org::imm::ImmAdapterT<org::imm::ImmTime> : public org::imm::ImmAdapterTBase<org::imm::ImmTime>, public org::imm::ImmAdapterTimeAPI {
  USE_IMM_ADAPTER_BASE(org::imm::ImmTime)
  using api_type = org::imm::ImmAdapterTimeAPI;
  BOOST_DESCRIBE_CLASS(ImmAdapterT, (ImmAdapterTBase, ImmAdapterTimeAPI), (), (), ());
  ImmAdapterT(org::imm::ImmAdapter const& other);
  bool const& getIsActive() const;
  org::imm::ImmTime::TimeVariant const& getTime() const;
};

template <>
struct org::imm::ImmAdapterT<org::imm::ImmTimeRange> : public org::imm::ImmAdapterTBase<org::imm::ImmTimeRange>, public org::imm::ImmAdapterTimeRangeAPI {
  USE_IMM_ADAPTER_BASE(org::imm::ImmTimeRange)
  using api_type = org::imm::ImmAdapterTimeRangeAPI;
  BOOST_DESCRIBE_CLASS(ImmAdapterT, (ImmAdapterTBase, ImmAdapterTimeRangeAPI), (), (), ());
  ImmAdapterT(org::imm::ImmAdapter const& other);
  org::imm::ImmIdT<org::imm::ImmTime> const& getFrom() const;
  org::imm::ImmIdT<org::imm::ImmTime> const& getTo() const;
};

template <>
struct org::imm::ImmAdapterT<org::imm::ImmMacro> : public org::imm::ImmAdapterTBase<org::imm::ImmMacro>, public org::imm::ImmAdapterMacroAPI {
  USE_IMM_ADAPTER_BASE(org::imm::ImmMacro)
  using api_type = org::imm::ImmAdapterMacroAPI;
  BOOST_DESCRIBE_CLASS(ImmAdapterT, (ImmAdapterTBase, ImmAdapterMacroAPI), (), (), ());
  ImmAdapterT(org::imm::ImmAdapter const& other);
  hstd::Str const& getName() const;
  org::sem::AttrGroup const& getAttrs() const;
};

template <>
struct org::imm::ImmAdapterT<org::imm::ImmSymbol> : public org::imm::ImmAdapterTBase<org::imm::ImmSymbol>, public org::imm::ImmAdapterSymbolAPI {
  USE_IMM_ADAPTER_BASE(org::imm::ImmSymbol)
  using api_type = org::imm::ImmAdapterSymbolAPI;
  BOOST_DESCRIBE_CLASS(ImmAdapterT, (ImmAdapterTBase, ImmAdapterSymbolAPI), (), (), ());
  ImmAdapterT(org::imm::ImmAdapter const& other);
  hstd::Str const& getName() const;
  hstd::ext::ImmVec<org::imm::ImmSymbol::Param> const& getParameters() const;
  hstd::ext::ImmVec<org::imm::ImmIdT<org::imm::ImmOrg>> const& getPositional() const;
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
  ImmAdapterT(org::imm::ImmAdapter const& other);
  hstd::ext::ImmVec<org::imm::ImmIdT<org::imm::ImmErrorSkipToken>> const& getSkipped() const;
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
  ImmAdapterT(org::imm::ImmAdapter const& other);
  hstd::ext::ImmVec<hstd::Str> const& getWords() const;
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
  ImmAdapterT(org::imm::ImmAdapter const& other);
  hstd::Opt<org::imm::ImmIdT<org::imm::ImmParagraph>> const& getDescription() const;
  org::sem::LinkTarget const& getTarget() const;
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
  ImmAdapterT(org::imm::ImmAdapter const& other);
  hstd::Str const& getName() const;
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
  ImmAdapterT(org::imm::ImmAdapter const& other);
  hstd::Str const& getExporter() const;
  hstd::Str const& getContent() const;
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
  ImmAdapterT(org::imm::ImmAdapter const& other);
  hstd::ext::ImmVec<org::sem::OrgCodeEvalOutput> const& getRaw() const;
  org::imm::ImmIdT<org::imm::ImmOrg> const& getNode() const;
};

template <>
struct org::imm::ImmAdapterT<org::imm::ImmBlockCode> : public org::imm::ImmAdapterTBase<org::imm::ImmBlockCode>, public org::imm::ImmAdapterBlockCodeAPI {
  USE_IMM_ADAPTER_BASE(org::imm::ImmBlockCode)
  using api_type = org::imm::ImmAdapterBlockCodeAPI;
  BOOST_DESCRIBE_CLASS(ImmAdapterT, (ImmAdapterTBase, ImmAdapterBlockCodeAPI), (), (), ());
  ImmAdapterT(org::imm::ImmAdapter const& other);
  hstd::Opt<hstd::Str> const& getLang() const;
  hstd::ext::ImmVec<org::imm::ImmIdT<org::imm::ImmBlockCodeEvalResult>> const& getResult() const;
  hstd::ext::ImmVec<org::sem::BlockCodeLine> const& getLines() const;
  org::sem::AttrGroup const& getSwitches() const;
};

template <>
struct org::imm::ImmAdapterT<org::imm::ImmSubtreeLog> : public org::imm::ImmAdapterTBase<org::imm::ImmSubtreeLog>, public org::imm::ImmAdapterSubtreeLogAPI {
  USE_IMM_ADAPTER_BASE(org::imm::ImmSubtreeLog)
  using api_type = org::imm::ImmAdapterSubtreeLogAPI;
  BOOST_DESCRIBE_CLASS(ImmAdapterT, (ImmAdapterTBase, ImmAdapterSubtreeLogAPI), (), (), ());
  ImmAdapterT(org::imm::ImmAdapter const& other);
  org::sem::SubtreeLogHead const& getHead() const;
  hstd::Opt<org::imm::ImmIdT<org::imm::ImmStmtList>> const& getDesc() const;
};

template <>
struct org::imm::ImmAdapterT<org::imm::ImmSubtree> : public org::imm::ImmAdapterTBase<org::imm::ImmSubtree>, public org::imm::ImmAdapterSubtreeAPI {
  USE_IMM_ADAPTER_BASE(org::imm::ImmSubtree)
  using api_type = org::imm::ImmAdapterSubtreeAPI;
  BOOST_DESCRIBE_CLASS(ImmAdapterT, (ImmAdapterTBase, ImmAdapterSubtreeAPI), (), (), ());
  ImmAdapterT(org::imm::ImmAdapter const& other);
  int const& getLevel() const;
  hstd::Opt<hstd::Str> const& getTreeId() const;
  hstd::Opt<hstd::Str> const& getTodo() const;
  hstd::Opt<org::sem::SubtreeCompletion> const& getCompletion() const;
  hstd::Opt<org::imm::ImmIdT<org::imm::ImmParagraph>> const& getDescription() const;
  hstd::ext::ImmVec<org::imm::ImmIdT<org::imm::ImmHashTag>> const& getTags() const;
  org::imm::ImmIdT<org::imm::ImmParagraph> const& getTitle() const;
  hstd::ext::ImmVec<org::imm::ImmIdT<org::imm::ImmSubtreeLog>> const& getLogbook() const;
  hstd::ext::ImmVec<org::sem::NamedProperty> const& getProperties() const;
  hstd::Opt<org::imm::ImmIdT<org::imm::ImmTime>> const& getClosed() const;
  hstd::Opt<org::imm::ImmIdT<org::imm::ImmTime>> const& getDeadline() const;
  hstd::Opt<org::imm::ImmIdT<org::imm::ImmTime>> const& getScheduled() const;
  bool const& getIsComment() const;
  bool const& getIsArchived() const;
  hstd::Opt<hstd::Str> const& getPriority() const;
};

template <>
struct org::imm::ImmAdapterT<org::imm::ImmCell> : public org::imm::ImmAdapterTBase<org::imm::ImmCell>, public org::imm::ImmAdapterCellAPI {
  USE_IMM_ADAPTER_BASE(org::imm::ImmCell)
  using api_type = org::imm::ImmAdapterCellAPI;
  BOOST_DESCRIBE_CLASS(ImmAdapterT, (ImmAdapterTBase, ImmAdapterCellAPI), (), (), ());
  ImmAdapterT(org::imm::ImmAdapter const& other);
  bool const& getIsBlock() const;
};

template <>
struct org::imm::ImmAdapterT<org::imm::ImmRow> : public org::imm::ImmAdapterTBase<org::imm::ImmRow>, public org::imm::ImmAdapterRowAPI {
  USE_IMM_ADAPTER_BASE(org::imm::ImmRow)
  using api_type = org::imm::ImmAdapterRowAPI;
  BOOST_DESCRIBE_CLASS(ImmAdapterT, (ImmAdapterTBase, ImmAdapterRowAPI), (), (), ());
  ImmAdapterT(org::imm::ImmAdapter const& other);
  hstd::ext::ImmVec<org::imm::ImmIdT<org::imm::ImmCell>> const& getCells() const;
  bool const& getIsBlock() const;
};

template <>
struct org::imm::ImmAdapterT<org::imm::ImmTable> : public org::imm::ImmAdapterTBase<org::imm::ImmTable>, public org::imm::ImmAdapterTableAPI {
  USE_IMM_ADAPTER_BASE(org::imm::ImmTable)
  using api_type = org::imm::ImmAdapterTableAPI;
  BOOST_DESCRIBE_CLASS(ImmAdapterT, (ImmAdapterTBase, ImmAdapterTableAPI), (), (), ());
  ImmAdapterT(org::imm::ImmAdapter const& other);
  hstd::ext::ImmVec<org::imm::ImmIdT<org::imm::ImmRow>> const& getRows() const;
  bool const& getIsBlock() const;
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
  ImmAdapterT(org::imm::ImmAdapter const& other);
  hstd::Str const& getTarget() const;
};

template <>
struct org::imm::ImmAdapterT<org::imm::ImmCmdExport> : public org::imm::ImmAdapterTBase<org::imm::ImmCmdExport>, public org::imm::ImmAdapterCmdExportAPI {
  USE_IMM_ADAPTER_BASE(org::imm::ImmCmdExport)
  using api_type = org::imm::ImmAdapterCmdExportAPI;
  BOOST_DESCRIBE_CLASS(ImmAdapterT, (ImmAdapterTBase, ImmAdapterCmdExportAPI), (), (), ());
  ImmAdapterT(org::imm::ImmAdapter const& other);
  hstd::Str const& getExporter() const;
  hstd::Str const& getContent() const;
};

template <>
struct org::imm::ImmAdapterT<org::imm::ImmCall> : public org::imm::ImmAdapterTBase<org::imm::ImmCall>, public org::imm::ImmAdapterCallAPI {
  USE_IMM_ADAPTER_BASE(org::imm::ImmCall)
  using api_type = org::imm::ImmAdapterCallAPI;
  BOOST_DESCRIBE_CLASS(ImmAdapterT, (ImmAdapterTBase, ImmAdapterCallAPI), (), (), ());
  ImmAdapterT(org::imm::ImmAdapter const& other);
  hstd::Str const& getName() const;
  org::sem::AttrGroup const& getAttrs() const;
  bool const& getIsCommand() const;
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
  ImmAdapterT(org::imm::ImmAdapter const& other);
  CheckboxState const& getCheckbox() const;
  hstd::Opt<org::imm::ImmIdT<org::imm::ImmParagraph>> const& getHeader() const;
  hstd::Opt<hstd::Str> const& getBullet() const;
};

template <>
struct org::imm::ImmAdapterT<org::imm::ImmDocumentOptions> : public org::imm::ImmAdapterTBase<org::imm::ImmDocumentOptions>, public org::imm::ImmAdapterDocumentOptionsAPI {
  USE_IMM_ADAPTER_BASE(org::imm::ImmDocumentOptions)
  using api_type = org::imm::ImmAdapterDocumentOptionsAPI;
  BOOST_DESCRIBE_CLASS(ImmAdapterT, (ImmAdapterTBase, ImmAdapterDocumentOptionsAPI), (), (), ());
  ImmAdapterT(org::imm::ImmAdapter const& other);
  InitialSubtreeVisibility const& getInitialVisibility() const;
  hstd::ext::ImmVec<org::sem::NamedProperty> const& getProperties() const;
  org::sem::DocumentExportConfig const& getExportConfig() const;
  hstd::Opt<bool> const& getFixedWidthSections() const;
  hstd::Opt<bool> const& getStartupIndented() const;
  hstd::Opt<hstd::Str> const& getCategory() const;
  hstd::Opt<hstd::Str> const& getSetupfile() const;
  hstd::Opt<int> const& getMaxSubtreeLevelExport() const;
  hstd::Opt<org::sem::ColumnView> const& getColumns() const;
  hstd::ext::ImmVec<org::sem::TodoKeyword> const& getTodoKeywords() const;
  hstd::ext::ImmVec<org::sem::TodoKeyword> const& getDoneKeywords() const;
};

template <>
struct org::imm::ImmAdapterT<org::imm::ImmDocumentFragment> : public org::imm::ImmAdapterTBase<org::imm::ImmDocumentFragment>, public org::imm::ImmAdapterDocumentFragmentAPI {
  USE_IMM_ADAPTER_BASE(org::imm::ImmDocumentFragment)
  using api_type = org::imm::ImmAdapterDocumentFragmentAPI;
  BOOST_DESCRIBE_CLASS(ImmAdapterT, (ImmAdapterTBase, ImmAdapterDocumentFragmentAPI), (), (), ());
  ImmAdapterT(org::imm::ImmAdapter const& other);
  int const& getBaseLine() const;
  int const& getBaseCol() const;
};

template <>
struct org::imm::ImmAdapterT<org::imm::ImmCriticMarkup> : public org::imm::ImmAdapterTBase<org::imm::ImmCriticMarkup>, public org::imm::ImmAdapterCriticMarkupAPI {
  USE_IMM_ADAPTER_BASE(org::imm::ImmCriticMarkup)
  using api_type = org::imm::ImmAdapterCriticMarkupAPI;
  BOOST_DESCRIBE_CLASS(ImmAdapterT, (ImmAdapterTBase, ImmAdapterCriticMarkupAPI), (), (), ());
  ImmAdapterT(org::imm::ImmAdapter const& other);
  org::imm::ImmCriticMarkup::Kind const& getKind() const;
};

template <>
struct org::imm::ImmAdapterT<org::imm::ImmDocument> : public org::imm::ImmAdapterTBase<org::imm::ImmDocument>, public org::imm::ImmAdapterDocumentAPI {
  USE_IMM_ADAPTER_BASE(org::imm::ImmDocument)
  using api_type = org::imm::ImmAdapterDocumentAPI;
  BOOST_DESCRIBE_CLASS(ImmAdapterT, (ImmAdapterTBase, ImmAdapterDocumentAPI), (), (), ());
  ImmAdapterT(org::imm::ImmAdapter const& other);
  hstd::Opt<org::imm::ImmIdT<org::imm::ImmParagraph>> const& getTitle() const;
  hstd::Opt<org::imm::ImmIdT<org::imm::ImmParagraph>> const& getAuthor() const;
  hstd::Opt<org::imm::ImmIdT<org::imm::ImmParagraph>> const& getCreator() const;
  hstd::ext::ImmVec<org::imm::ImmIdT<org::imm::ImmHashTag>> const& getFiletags() const;
  hstd::Opt<org::imm::ImmIdT<org::imm::ImmRawText>> const& getEmail() const;
  hstd::ext::ImmVec<hstd::Str> const& getLanguage() const;
  org::imm::ImmIdT<org::imm::ImmDocumentOptions> const& getOptions() const;
  hstd::Opt<hstd::Str> const& getExportFileName() const;
};

template <>
struct org::imm::ImmAdapterT<org::imm::ImmFileTarget> : public org::imm::ImmAdapterTBase<org::imm::ImmFileTarget>, public org::imm::ImmAdapterFileTargetAPI {
  USE_IMM_ADAPTER_BASE(org::imm::ImmFileTarget)
  using api_type = org::imm::ImmAdapterFileTargetAPI;
  BOOST_DESCRIBE_CLASS(ImmAdapterT, (ImmAdapterTBase, ImmAdapterFileTargetAPI), (), (), ());
  ImmAdapterT(org::imm::ImmAdapter const& other);
  hstd::Str const& getPath() const;
  hstd::Opt<int> const& getLine() const;
  hstd::Opt<hstd::Str> const& getSearchTarget() const;
  bool const& getRestrictToHeadlines() const;
  hstd::Opt<hstd::Str> const& getTargetId() const;
  hstd::Opt<hstd::Str> const& getRegexp() const;
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
  ImmAdapterT(org::imm::ImmAdapter const& other);
  hstd::Str const& getRelPath() const;
  hstd::Str const& getAbsPath() const;
  org::imm::ImmFile::Data const& getData() const;
};

template <>
struct org::imm::ImmAdapterT<org::imm::ImmDirectory> : public org::imm::ImmAdapterTBase<org::imm::ImmDirectory>, public org::imm::ImmAdapterDirectoryAPI {
  USE_IMM_ADAPTER_BASE(org::imm::ImmDirectory)
  using api_type = org::imm::ImmAdapterDirectoryAPI;
  BOOST_DESCRIBE_CLASS(ImmAdapterT, (ImmAdapterTBase, ImmAdapterDirectoryAPI), (), (), ());
  ImmAdapterT(org::imm::ImmAdapter const& other);
  hstd::Str const& getRelPath() const;
  hstd::Str const& getAbsPath() const;
};

template <>
struct org::imm::ImmAdapterT<org::imm::ImmSymlink> : public org::imm::ImmAdapterTBase<org::imm::ImmSymlink>, public org::imm::ImmAdapterSymlinkAPI {
  USE_IMM_ADAPTER_BASE(org::imm::ImmSymlink)
  using api_type = org::imm::ImmAdapterSymlinkAPI;
  BOOST_DESCRIBE_CLASS(ImmAdapterT, (ImmAdapterTBase, ImmAdapterSymlinkAPI), (), (), ());
  ImmAdapterT(org::imm::ImmAdapter const& other);
  bool const& getIsDirectory() const;
  hstd::Str const& getAbsPath() const;
};

template <>
struct org::imm::ImmAdapterT<org::imm::ImmCmdInclude> : public org::imm::ImmAdapterTBase<org::imm::ImmCmdInclude>, public org::imm::ImmAdapterCmdIncludeAPI {
  USE_IMM_ADAPTER_BASE(org::imm::ImmCmdInclude)
  using api_type = org::imm::ImmAdapterCmdIncludeAPI;
  BOOST_DESCRIBE_CLASS(ImmAdapterT, (ImmAdapterTBase, ImmAdapterCmdIncludeAPI), (), (), ());
  ImmAdapterT(org::imm::ImmAdapter const& other);
  hstd::Str const& getPath() const;
  hstd::Opt<int> const& getFirstLine() const;
  hstd::Opt<int> const& getLastLine() const;
  org::imm::ImmCmdInclude::Data const& getData() const;
};

}
/* clang-format on */