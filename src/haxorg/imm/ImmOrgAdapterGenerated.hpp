/* clang-format off */
#pragma once
#include <haxorg/imm/ImmOrg.hpp>
namespace org::imm {
struct ImmNoNodeValueRead {
  BOOST_DESCRIBE_CLASS(ImmNoNodeValueRead, (), (), (), ());
  org::imm::ImmNoNode* ptr;
  ImmNoNodeValueRead(org::imm::ImmNoNode const* ptr) : ptr{const_cast<org::imm::ImmNoNode*>(ptr)} {  }
};

template <>
struct ImmAdapterT<org::imm::ImmNoNode> : public org::imm::ImmAdapterTBase<org::imm::ImmNoNode>, public org::imm::ImmAdapterNoNodeAPI {
  USE_IMM_ADAPTER_BASE(org::imm::ImmNoNode)
  using api_type = org::imm::ImmAdapterNoNodeAPI;
  BOOST_DESCRIBE_CLASS(ImmAdapterT, (ImmAdapterTBase, ImmAdapterNoNodeAPI), (), (), ());
  ImmAdapterT(org::imm::ImmAdapter const& other) { LOGIC_ASSERTION_CHECK_FMT("Adapter type mismatch, cannot create adapter of type {} from generic adapter of type {}", "NoNode", other.getKind()) }
  org::imm::ImmNoNodeValueRead getValue() const { return org::imm::ImmNoNodeValueRead{&this->value()}; }
};

struct ImmErrorItemValueRead {
  BOOST_DESCRIBE_CLASS(ImmErrorItemValueRead, (), (), (), ());
  org::imm::ImmErrorItem* ptr;
  org::sem::OrgDiagnostics const& getDiag() const;
  ImmErrorItemValueRead(org::imm::ImmErrorItem const* ptr) : ptr{const_cast<org::imm::ImmErrorItem*>(ptr)} {  }
};

template <>
struct ImmAdapterT<org::imm::ImmErrorItem> : public org::imm::ImmAdapterTBase<org::imm::ImmErrorItem>, public org::imm::ImmAdapterErrorItemAPI {
  USE_IMM_ADAPTER_BASE(org::imm::ImmErrorItem)
  using api_type = org::imm::ImmAdapterErrorItemAPI;
  BOOST_DESCRIBE_CLASS(ImmAdapterT, (ImmAdapterTBase, ImmAdapterErrorItemAPI), (), (), ());
  ImmAdapterT(org::imm::ImmAdapter const& other) { LOGIC_ASSERTION_CHECK_FMT("Adapter type mismatch, cannot create adapter of type {} from generic adapter of type {}", "ErrorItem", other.getKind()) }
  org::imm::ImmErrorItemValueRead getValue() const { return org::imm::ImmErrorItemValueRead{&this->value()}; }
};

struct ImmErrorGroupValueRead {
  BOOST_DESCRIBE_CLASS(ImmErrorGroupValueRead, (), (), (), ());
  org::imm::ImmErrorGroup* ptr;
  hstd::ext::ImmVec<org::imm::ImmIdT<org::imm::ImmErrorItem>> const& getDiagnostics() const;
  ImmErrorGroupValueRead(org::imm::ImmErrorGroup const* ptr) : ptr{const_cast<org::imm::ImmErrorGroup*>(ptr)} {  }
};

template <>
struct ImmAdapterT<org::imm::ImmErrorGroup> : public org::imm::ImmAdapterTBase<org::imm::ImmErrorGroup>, public org::imm::ImmAdapterErrorGroupAPI {
  USE_IMM_ADAPTER_BASE(org::imm::ImmErrorGroup)
  using api_type = org::imm::ImmAdapterErrorGroupAPI;
  BOOST_DESCRIBE_CLASS(ImmAdapterT, (ImmAdapterTBase, ImmAdapterErrorGroupAPI), (), (), ());
  ImmAdapterT(org::imm::ImmAdapter const& other) { LOGIC_ASSERTION_CHECK_FMT("Adapter type mismatch, cannot create adapter of type {} from generic adapter of type {}", "ErrorGroup", other.getKind()) }
  org::imm::ImmErrorGroupValueRead getValue() const { return org::imm::ImmErrorGroupValueRead{&this->value()}; }
};

struct ImmStmtValueRead {
  BOOST_DESCRIBE_CLASS(ImmStmtValueRead, (), (), (), ());
  org::imm::ImmStmt* ptr;
  hstd::ext::ImmVec<org::imm::ImmIdT<org::imm::ImmOrg>> const& getAttached() const;
  ImmStmtValueRead(org::imm::ImmStmt const* ptr) : ptr{const_cast<org::imm::ImmStmt*>(ptr)} {  }
};

template <>
struct ImmAdapterT<org::imm::ImmStmt> : public org::imm::ImmAdapterTBase<org::imm::ImmStmt>, public org::imm::ImmAdapterStmtAPI {
  USE_IMM_ADAPTER_BASE(org::imm::ImmStmt)
  using api_type = org::imm::ImmAdapterStmtAPI;
  BOOST_DESCRIBE_CLASS(ImmAdapterT, (ImmAdapterTBase, ImmAdapterStmtAPI), (), (), ());
  ImmAdapterT(org::imm::ImmAdapter const& other) { LOGIC_ASSERTION_CHECK_FMT("Adapter type mismatch, cannot create adapter of type {} from generic adapter of type {}", "Stmt", other.getKind()) }
  org::imm::ImmStmtValueRead getValue() const { return org::imm::ImmStmtValueRead{&this->value()}; }
};

struct ImmInlineValueRead {
  BOOST_DESCRIBE_CLASS(ImmInlineValueRead, (), (), (), ());
  org::imm::ImmInline* ptr;
  ImmInlineValueRead(org::imm::ImmInline const* ptr) : ptr{const_cast<org::imm::ImmInline*>(ptr)} {  }
};

template <>
struct ImmAdapterT<org::imm::ImmInline> : public org::imm::ImmAdapterTBase<org::imm::ImmInline>, public org::imm::ImmAdapterInlineAPI {
  USE_IMM_ADAPTER_BASE(org::imm::ImmInline)
  using api_type = org::imm::ImmAdapterInlineAPI;
  BOOST_DESCRIBE_CLASS(ImmAdapterT, (ImmAdapterTBase, ImmAdapterInlineAPI), (), (), ());
  ImmAdapterT(org::imm::ImmAdapter const& other) { LOGIC_ASSERTION_CHECK_FMT("Adapter type mismatch, cannot create adapter of type {} from generic adapter of type {}", "Inline", other.getKind()) }
  org::imm::ImmInlineValueRead getValue() const { return org::imm::ImmInlineValueRead{&this->value()}; }
};

struct ImmStmtListValueRead {
  BOOST_DESCRIBE_CLASS(ImmStmtListValueRead, (), (), (), ());
  org::imm::ImmStmtList* ptr;
  ImmStmtListValueRead(org::imm::ImmStmtList const* ptr) : ptr{const_cast<org::imm::ImmStmtList*>(ptr)} {  }
};

template <>
struct ImmAdapterT<org::imm::ImmStmtList> : public org::imm::ImmAdapterTBase<org::imm::ImmStmtList>, public org::imm::ImmAdapterStmtListAPI {
  USE_IMM_ADAPTER_BASE(org::imm::ImmStmtList)
  using api_type = org::imm::ImmAdapterStmtListAPI;
  BOOST_DESCRIBE_CLASS(ImmAdapterT, (ImmAdapterTBase, ImmAdapterStmtListAPI), (), (), ());
  ImmAdapterT(org::imm::ImmAdapter const& other) { LOGIC_ASSERTION_CHECK_FMT("Adapter type mismatch, cannot create adapter of type {} from generic adapter of type {}", "StmtList", other.getKind()) }
  org::imm::ImmStmtListValueRead getValue() const { return org::imm::ImmStmtListValueRead{&this->value()}; }
};

struct ImmEmptyValueRead {
  BOOST_DESCRIBE_CLASS(ImmEmptyValueRead, (), (), (), ());
  org::imm::ImmEmpty* ptr;
  ImmEmptyValueRead(org::imm::ImmEmpty const* ptr) : ptr{const_cast<org::imm::ImmEmpty*>(ptr)} {  }
};

template <>
struct ImmAdapterT<org::imm::ImmEmpty> : public org::imm::ImmAdapterTBase<org::imm::ImmEmpty>, public org::imm::ImmAdapterEmptyAPI {
  USE_IMM_ADAPTER_BASE(org::imm::ImmEmpty)
  using api_type = org::imm::ImmAdapterEmptyAPI;
  BOOST_DESCRIBE_CLASS(ImmAdapterT, (ImmAdapterTBase, ImmAdapterEmptyAPI), (), (), ());
  ImmAdapterT(org::imm::ImmAdapter const& other) { LOGIC_ASSERTION_CHECK_FMT("Adapter type mismatch, cannot create adapter of type {} from generic adapter of type {}", "Empty", other.getKind()) }
  org::imm::ImmEmptyValueRead getValue() const { return org::imm::ImmEmptyValueRead{&this->value()}; }
};

struct ImmCmdValueRead {
  BOOST_DESCRIBE_CLASS(ImmCmdValueRead, (), (), (), ());
  org::imm::ImmCmd* ptr;
  org::sem::AttrGroup const& getAttrs() const;
  ImmCmdValueRead(org::imm::ImmCmd const* ptr) : ptr{const_cast<org::imm::ImmCmd*>(ptr)} {  }
};

template <>
struct ImmAdapterT<org::imm::ImmCmd> : public org::imm::ImmAdapterTBase<org::imm::ImmCmd>, public org::imm::ImmAdapterCmdAPI {
  USE_IMM_ADAPTER_BASE(org::imm::ImmCmd)
  using api_type = org::imm::ImmAdapterCmdAPI;
  BOOST_DESCRIBE_CLASS(ImmAdapterT, (ImmAdapterTBase, ImmAdapterCmdAPI), (), (), ());
  ImmAdapterT(org::imm::ImmAdapter const& other) { LOGIC_ASSERTION_CHECK_FMT("Adapter type mismatch, cannot create adapter of type {} from generic adapter of type {}", "Cmd", other.getKind()) }
  org::imm::ImmCmdValueRead getValue() const { return org::imm::ImmCmdValueRead{&this->value()}; }
};

struct ImmBlockValueRead {
  BOOST_DESCRIBE_CLASS(ImmBlockValueRead, (), (), (), ());
  org::imm::ImmBlock* ptr;
  ImmBlockValueRead(org::imm::ImmBlock const* ptr) : ptr{const_cast<org::imm::ImmBlock*>(ptr)} {  }
};

template <>
struct ImmAdapterT<org::imm::ImmBlock> : public org::imm::ImmAdapterTBase<org::imm::ImmBlock>, public org::imm::ImmAdapterBlockAPI {
  USE_IMM_ADAPTER_BASE(org::imm::ImmBlock)
  using api_type = org::imm::ImmAdapterBlockAPI;
  BOOST_DESCRIBE_CLASS(ImmAdapterT, (ImmAdapterTBase, ImmAdapterBlockAPI), (), (), ());
  ImmAdapterT(org::imm::ImmAdapter const& other) { LOGIC_ASSERTION_CHECK_FMT("Adapter type mismatch, cannot create adapter of type {} from generic adapter of type {}", "Block", other.getKind()) }
  org::imm::ImmBlockValueRead getValue() const { return org::imm::ImmBlockValueRead{&this->value()}; }
};

struct ImmLineCommandValueRead {
  BOOST_DESCRIBE_CLASS(ImmLineCommandValueRead, (), (), (), ());
  org::imm::ImmLineCommand* ptr;
  ImmLineCommandValueRead(org::imm::ImmLineCommand const* ptr) : ptr{const_cast<org::imm::ImmLineCommand*>(ptr)} {  }
};

template <>
struct ImmAdapterT<org::imm::ImmLineCommand> : public org::imm::ImmAdapterTBase<org::imm::ImmLineCommand>, public org::imm::ImmAdapterLineCommandAPI {
  USE_IMM_ADAPTER_BASE(org::imm::ImmLineCommand)
  using api_type = org::imm::ImmAdapterLineCommandAPI;
  BOOST_DESCRIBE_CLASS(ImmAdapterT, (ImmAdapterTBase, ImmAdapterLineCommandAPI), (), (), ());
  ImmAdapterT(org::imm::ImmAdapter const& other) { LOGIC_ASSERTION_CHECK_FMT("Adapter type mismatch, cannot create adapter of type {} from generic adapter of type {}", "LineCommand", other.getKind()) }
  org::imm::ImmLineCommandValueRead getValue() const { return org::imm::ImmLineCommandValueRead{&this->value()}; }
};

struct ImmAttachedValueRead {
  BOOST_DESCRIBE_CLASS(ImmAttachedValueRead, (), (), (), ());
  org::imm::ImmAttached* ptr;
  ImmAttachedValueRead(org::imm::ImmAttached const* ptr) : ptr{const_cast<org::imm::ImmAttached*>(ptr)} {  }
};

template <>
struct ImmAdapterT<org::imm::ImmAttached> : public org::imm::ImmAdapterTBase<org::imm::ImmAttached>, public org::imm::ImmAdapterAttachedAPI {
  USE_IMM_ADAPTER_BASE(org::imm::ImmAttached)
  using api_type = org::imm::ImmAdapterAttachedAPI;
  BOOST_DESCRIBE_CLASS(ImmAdapterT, (ImmAdapterTBase, ImmAdapterAttachedAPI), (), (), ());
  ImmAdapterT(org::imm::ImmAdapter const& other) { LOGIC_ASSERTION_CHECK_FMT("Adapter type mismatch, cannot create adapter of type {} from generic adapter of type {}", "Attached", other.getKind()) }
  org::imm::ImmAttachedValueRead getValue() const { return org::imm::ImmAttachedValueRead{&this->value()}; }
};

struct ImmLeafValueRead {
  BOOST_DESCRIBE_CLASS(ImmLeafValueRead, (), (), (), ());
  org::imm::ImmLeaf* ptr;
  hstd::ext::ImmBox<hstd::Str> const& getText() const;
  ImmLeafValueRead(org::imm::ImmLeaf const* ptr) : ptr{const_cast<org::imm::ImmLeaf*>(ptr)} {  }
};

template <>
struct ImmAdapterT<org::imm::ImmLeaf> : public org::imm::ImmAdapterTBase<org::imm::ImmLeaf>, public org::imm::ImmAdapterLeafAPI {
  USE_IMM_ADAPTER_BASE(org::imm::ImmLeaf)
  using api_type = org::imm::ImmAdapterLeafAPI;
  BOOST_DESCRIBE_CLASS(ImmAdapterT, (ImmAdapterTBase, ImmAdapterLeafAPI), (), (), ());
  ImmAdapterT(org::imm::ImmAdapter const& other) { LOGIC_ASSERTION_CHECK_FMT("Adapter type mismatch, cannot create adapter of type {} from generic adapter of type {}", "Leaf", other.getKind()) }
  org::imm::ImmLeafValueRead getValue() const { return org::imm::ImmLeafValueRead{&this->value()}; }
};

struct ImmCmdCaptionValueRead {
  BOOST_DESCRIBE_CLASS(ImmCmdCaptionValueRead, (), (), (), ());
  org::imm::ImmCmdCaption* ptr;
  org::imm::ImmIdT<org::imm::ImmParagraph> const& getText() const;
  ImmCmdCaptionValueRead(org::imm::ImmCmdCaption const* ptr) : ptr{const_cast<org::imm::ImmCmdCaption*>(ptr)} {  }
};

template <>
struct ImmAdapterT<org::imm::ImmCmdCaption> : public org::imm::ImmAdapterTBase<org::imm::ImmCmdCaption>, public org::imm::ImmAdapterCmdCaptionAPI {
  USE_IMM_ADAPTER_BASE(org::imm::ImmCmdCaption)
  using api_type = org::imm::ImmAdapterCmdCaptionAPI;
  BOOST_DESCRIBE_CLASS(ImmAdapterT, (ImmAdapterTBase, ImmAdapterCmdCaptionAPI), (), (), ());
  ImmAdapterT(org::imm::ImmAdapter const& other) { LOGIC_ASSERTION_CHECK_FMT("Adapter type mismatch, cannot create adapter of type {} from generic adapter of type {}", "CmdCaption", other.getKind()) }
  org::imm::ImmCmdCaptionValueRead getValue() const { return org::imm::ImmCmdCaptionValueRead{&this->value()}; }
};

struct ImmCmdCreatorValueRead {
  BOOST_DESCRIBE_CLASS(ImmCmdCreatorValueRead, (), (), (), ());
  org::imm::ImmCmdCreator* ptr;
  org::imm::ImmIdT<org::imm::ImmParagraph> const& getText() const;
  ImmCmdCreatorValueRead(org::imm::ImmCmdCreator const* ptr) : ptr{const_cast<org::imm::ImmCmdCreator*>(ptr)} {  }
};

template <>
struct ImmAdapterT<org::imm::ImmCmdCreator> : public org::imm::ImmAdapterTBase<org::imm::ImmCmdCreator>, public org::imm::ImmAdapterCmdCreatorAPI {
  USE_IMM_ADAPTER_BASE(org::imm::ImmCmdCreator)
  using api_type = org::imm::ImmAdapterCmdCreatorAPI;
  BOOST_DESCRIBE_CLASS(ImmAdapterT, (ImmAdapterTBase, ImmAdapterCmdCreatorAPI), (), (), ());
  ImmAdapterT(org::imm::ImmAdapter const& other) { LOGIC_ASSERTION_CHECK_FMT("Adapter type mismatch, cannot create adapter of type {} from generic adapter of type {}", "CmdCreator", other.getKind()) }
  org::imm::ImmCmdCreatorValueRead getValue() const { return org::imm::ImmCmdCreatorValueRead{&this->value()}; }
};

struct ImmCmdAuthorValueRead {
  BOOST_DESCRIBE_CLASS(ImmCmdAuthorValueRead, (), (), (), ());
  org::imm::ImmCmdAuthor* ptr;
  org::imm::ImmIdT<org::imm::ImmParagraph> const& getText() const;
  ImmCmdAuthorValueRead(org::imm::ImmCmdAuthor const* ptr) : ptr{const_cast<org::imm::ImmCmdAuthor*>(ptr)} {  }
};

template <>
struct ImmAdapterT<org::imm::ImmCmdAuthor> : public org::imm::ImmAdapterTBase<org::imm::ImmCmdAuthor>, public org::imm::ImmAdapterCmdAuthorAPI {
  USE_IMM_ADAPTER_BASE(org::imm::ImmCmdAuthor)
  using api_type = org::imm::ImmAdapterCmdAuthorAPI;
  BOOST_DESCRIBE_CLASS(ImmAdapterT, (ImmAdapterTBase, ImmAdapterCmdAuthorAPI), (), (), ());
  ImmAdapterT(org::imm::ImmAdapter const& other) { LOGIC_ASSERTION_CHECK_FMT("Adapter type mismatch, cannot create adapter of type {} from generic adapter of type {}", "CmdAuthor", other.getKind()) }
  org::imm::ImmCmdAuthorValueRead getValue() const { return org::imm::ImmCmdAuthorValueRead{&this->value()}; }
};

struct ImmCmdEmailValueRead {
  BOOST_DESCRIBE_CLASS(ImmCmdEmailValueRead, (), (), (), ());
  org::imm::ImmCmdEmail* ptr;
  hstd::ext::ImmBox<hstd::Str> const& getText() const;
  ImmCmdEmailValueRead(org::imm::ImmCmdEmail const* ptr) : ptr{const_cast<org::imm::ImmCmdEmail*>(ptr)} {  }
};

template <>
struct ImmAdapterT<org::imm::ImmCmdEmail> : public org::imm::ImmAdapterTBase<org::imm::ImmCmdEmail>, public org::imm::ImmAdapterCmdEmailAPI {
  USE_IMM_ADAPTER_BASE(org::imm::ImmCmdEmail)
  using api_type = org::imm::ImmAdapterCmdEmailAPI;
  BOOST_DESCRIBE_CLASS(ImmAdapterT, (ImmAdapterTBase, ImmAdapterCmdEmailAPI), (), (), ());
  ImmAdapterT(org::imm::ImmAdapter const& other) { LOGIC_ASSERTION_CHECK_FMT("Adapter type mismatch, cannot create adapter of type {} from generic adapter of type {}", "CmdEmail", other.getKind()) }
  org::imm::ImmCmdEmailValueRead getValue() const { return org::imm::ImmCmdEmailValueRead{&this->value()}; }
};

struct ImmCmdLanguageValueRead {
  BOOST_DESCRIBE_CLASS(ImmCmdLanguageValueRead, (), (), (), ());
  org::imm::ImmCmdLanguage* ptr;
  hstd::ext::ImmBox<hstd::Str> const& getText() const;
  ImmCmdLanguageValueRead(org::imm::ImmCmdLanguage const* ptr) : ptr{const_cast<org::imm::ImmCmdLanguage*>(ptr)} {  }
};

template <>
struct ImmAdapterT<org::imm::ImmCmdLanguage> : public org::imm::ImmAdapterTBase<org::imm::ImmCmdLanguage>, public org::imm::ImmAdapterCmdLanguageAPI {
  USE_IMM_ADAPTER_BASE(org::imm::ImmCmdLanguage)
  using api_type = org::imm::ImmAdapterCmdLanguageAPI;
  BOOST_DESCRIBE_CLASS(ImmAdapterT, (ImmAdapterTBase, ImmAdapterCmdLanguageAPI), (), (), ());
  ImmAdapterT(org::imm::ImmAdapter const& other) { LOGIC_ASSERTION_CHECK_FMT("Adapter type mismatch, cannot create adapter of type {} from generic adapter of type {}", "CmdLanguage", other.getKind()) }
  org::imm::ImmCmdLanguageValueRead getValue() const { return org::imm::ImmCmdLanguageValueRead{&this->value()}; }
};

struct ImmCmdColumnsValueRead {
  BOOST_DESCRIBE_CLASS(ImmCmdColumnsValueRead, (), (), (), ());
  org::imm::ImmCmdColumns* ptr;
  org::sem::ColumnView const& getView() const;
  ImmCmdColumnsValueRead(org::imm::ImmCmdColumns const* ptr) : ptr{const_cast<org::imm::ImmCmdColumns*>(ptr)} {  }
};

template <>
struct ImmAdapterT<org::imm::ImmCmdColumns> : public org::imm::ImmAdapterTBase<org::imm::ImmCmdColumns>, public org::imm::ImmAdapterCmdColumnsAPI {
  USE_IMM_ADAPTER_BASE(org::imm::ImmCmdColumns)
  using api_type = org::imm::ImmAdapterCmdColumnsAPI;
  BOOST_DESCRIBE_CLASS(ImmAdapterT, (ImmAdapterTBase, ImmAdapterCmdColumnsAPI), (), (), ());
  ImmAdapterT(org::imm::ImmAdapter const& other) { LOGIC_ASSERTION_CHECK_FMT("Adapter type mismatch, cannot create adapter of type {} from generic adapter of type {}", "CmdColumns", other.getKind()) }
  org::imm::ImmCmdColumnsValueRead getValue() const { return org::imm::ImmCmdColumnsValueRead{&this->value()}; }
};

struct ImmCmdNameValueRead {
  BOOST_DESCRIBE_CLASS(ImmCmdNameValueRead, (), (), (), ());
  org::imm::ImmCmdName* ptr;
  hstd::ext::ImmBox<hstd::Str> const& getName() const;
  ImmCmdNameValueRead(org::imm::ImmCmdName const* ptr) : ptr{const_cast<org::imm::ImmCmdName*>(ptr)} {  }
};

template <>
struct ImmAdapterT<org::imm::ImmCmdName> : public org::imm::ImmAdapterTBase<org::imm::ImmCmdName>, public org::imm::ImmAdapterCmdNameAPI {
  USE_IMM_ADAPTER_BASE(org::imm::ImmCmdName)
  using api_type = org::imm::ImmAdapterCmdNameAPI;
  BOOST_DESCRIBE_CLASS(ImmAdapterT, (ImmAdapterTBase, ImmAdapterCmdNameAPI), (), (), ());
  ImmAdapterT(org::imm::ImmAdapter const& other) { LOGIC_ASSERTION_CHECK_FMT("Adapter type mismatch, cannot create adapter of type {} from generic adapter of type {}", "CmdName", other.getKind()) }
  org::imm::ImmCmdNameValueRead getValue() const { return org::imm::ImmCmdNameValueRead{&this->value()}; }
};

struct ImmCmdCustomArgsValueRead {
  BOOST_DESCRIBE_CLASS(ImmCmdCustomArgsValueRead, (), (), (), ());
  org::imm::ImmCmdCustomArgs* ptr;
  hstd::ext::ImmBox<hstd::Str> const& getName() const;
  bool const& getIsattached() const;
  ImmCmdCustomArgsValueRead(org::imm::ImmCmdCustomArgs const* ptr) : ptr{const_cast<org::imm::ImmCmdCustomArgs*>(ptr)} {  }
};

template <>
struct ImmAdapterT<org::imm::ImmCmdCustomArgs> : public org::imm::ImmAdapterTBase<org::imm::ImmCmdCustomArgs>, public org::imm::ImmAdapterCmdCustomArgsAPI {
  USE_IMM_ADAPTER_BASE(org::imm::ImmCmdCustomArgs)
  using api_type = org::imm::ImmAdapterCmdCustomArgsAPI;
  BOOST_DESCRIBE_CLASS(ImmAdapterT, (ImmAdapterTBase, ImmAdapterCmdCustomArgsAPI), (), (), ());
  ImmAdapterT(org::imm::ImmAdapter const& other) { LOGIC_ASSERTION_CHECK_FMT("Adapter type mismatch, cannot create adapter of type {} from generic adapter of type {}", "CmdCustomArgs", other.getKind()) }
  org::imm::ImmCmdCustomArgsValueRead getValue() const { return org::imm::ImmCmdCustomArgsValueRead{&this->value()}; }
};

struct ImmCmdCustomRawValueRead {
  BOOST_DESCRIBE_CLASS(ImmCmdCustomRawValueRead, (), (), (), ());
  org::imm::ImmCmdCustomRaw* ptr;
  hstd::ext::ImmBox<hstd::Str> const& getName() const;
  bool const& getIsattached() const;
  hstd::ext::ImmBox<hstd::Str> const& getText() const;
  ImmCmdCustomRawValueRead(org::imm::ImmCmdCustomRaw const* ptr) : ptr{const_cast<org::imm::ImmCmdCustomRaw*>(ptr)} {  }
};

template <>
struct ImmAdapterT<org::imm::ImmCmdCustomRaw> : public org::imm::ImmAdapterTBase<org::imm::ImmCmdCustomRaw>, public org::imm::ImmAdapterCmdCustomRawAPI {
  USE_IMM_ADAPTER_BASE(org::imm::ImmCmdCustomRaw)
  using api_type = org::imm::ImmAdapterCmdCustomRawAPI;
  BOOST_DESCRIBE_CLASS(ImmAdapterT, (ImmAdapterTBase, ImmAdapterCmdCustomRawAPI), (), (), ());
  ImmAdapterT(org::imm::ImmAdapter const& other) { LOGIC_ASSERTION_CHECK_FMT("Adapter type mismatch, cannot create adapter of type {} from generic adapter of type {}", "CmdCustomRaw", other.getKind()) }
  org::imm::ImmCmdCustomRawValueRead getValue() const { return org::imm::ImmCmdCustomRawValueRead{&this->value()}; }
};

struct ImmCmdCustomTextValueRead {
  BOOST_DESCRIBE_CLASS(ImmCmdCustomTextValueRead, (), (), (), ());
  org::imm::ImmCmdCustomText* ptr;
  hstd::ext::ImmBox<hstd::Str> const& getName() const;
  bool const& getIsattached() const;
  org::imm::ImmIdT<org::imm::ImmParagraph> const& getText() const;
  ImmCmdCustomTextValueRead(org::imm::ImmCmdCustomText const* ptr) : ptr{const_cast<org::imm::ImmCmdCustomText*>(ptr)} {  }
};

template <>
struct ImmAdapterT<org::imm::ImmCmdCustomText> : public org::imm::ImmAdapterTBase<org::imm::ImmCmdCustomText>, public org::imm::ImmAdapterCmdCustomTextAPI {
  USE_IMM_ADAPTER_BASE(org::imm::ImmCmdCustomText)
  using api_type = org::imm::ImmAdapterCmdCustomTextAPI;
  BOOST_DESCRIBE_CLASS(ImmAdapterT, (ImmAdapterTBase, ImmAdapterCmdCustomTextAPI), (), (), ());
  ImmAdapterT(org::imm::ImmAdapter const& other) { LOGIC_ASSERTION_CHECK_FMT("Adapter type mismatch, cannot create adapter of type {} from generic adapter of type {}", "CmdCustomText", other.getKind()) }
  org::imm::ImmCmdCustomTextValueRead getValue() const { return org::imm::ImmCmdCustomTextValueRead{&this->value()}; }
};

struct ImmCmdCallValueRead {
  BOOST_DESCRIBE_CLASS(ImmCmdCallValueRead, (), (), (), ());
  org::imm::ImmCmdCall* ptr;
  hstd::ext::ImmBox<hstd::Str> const& getName() const;
  hstd::ext::ImmBox<hstd::Opt<hstd::Str>> const& getFilename() const;
  org::sem::AttrGroup const& getInsideheaderattrs() const;
  org::sem::AttrGroup const& getCallattrs() const;
  org::sem::AttrGroup const& getEndheaderattrs() const;
  hstd::ext::ImmVec<org::imm::ImmIdT<org::imm::ImmBlockCodeEvalResult>> const& getResult() const;
  ImmCmdCallValueRead(org::imm::ImmCmdCall const* ptr) : ptr{const_cast<org::imm::ImmCmdCall*>(ptr)} {  }
};

template <>
struct ImmAdapterT<org::imm::ImmCmdCall> : public org::imm::ImmAdapterTBase<org::imm::ImmCmdCall>, public org::imm::ImmAdapterCmdCallAPI {
  USE_IMM_ADAPTER_BASE(org::imm::ImmCmdCall)
  using api_type = org::imm::ImmAdapterCmdCallAPI;
  BOOST_DESCRIBE_CLASS(ImmAdapterT, (ImmAdapterTBase, ImmAdapterCmdCallAPI), (), (), ());
  ImmAdapterT(org::imm::ImmAdapter const& other) { LOGIC_ASSERTION_CHECK_FMT("Adapter type mismatch, cannot create adapter of type {} from generic adapter of type {}", "CmdCall", other.getKind()) }
  org::imm::ImmCmdCallValueRead getValue() const { return org::imm::ImmCmdCallValueRead{&this->value()}; }
};

struct ImmCmdTblfmValueRead {
  BOOST_DESCRIBE_CLASS(ImmCmdTblfmValueRead, (), (), (), ());
  org::imm::ImmCmdTblfm* ptr;
  org::sem::Tblfm const& getExpr() const;
  ImmCmdTblfmValueRead(org::imm::ImmCmdTblfm const* ptr) : ptr{const_cast<org::imm::ImmCmdTblfm*>(ptr)} {  }
};

template <>
struct ImmAdapterT<org::imm::ImmCmdTblfm> : public org::imm::ImmAdapterTBase<org::imm::ImmCmdTblfm>, public org::imm::ImmAdapterCmdTblfmAPI {
  USE_IMM_ADAPTER_BASE(org::imm::ImmCmdTblfm)
  using api_type = org::imm::ImmAdapterCmdTblfmAPI;
  BOOST_DESCRIBE_CLASS(ImmAdapterT, (ImmAdapterTBase, ImmAdapterCmdTblfmAPI), (), (), ());
  ImmAdapterT(org::imm::ImmAdapter const& other) { LOGIC_ASSERTION_CHECK_FMT("Adapter type mismatch, cannot create adapter of type {} from generic adapter of type {}", "CmdTblfm", other.getKind()) }
  org::imm::ImmCmdTblfmValueRead getValue() const { return org::imm::ImmCmdTblfmValueRead{&this->value()}; }
};

struct ImmHashTagValueRead {
  BOOST_DESCRIBE_CLASS(ImmHashTagValueRead, (), (), (), ());
  org::imm::ImmHashTag* ptr;
  org::sem::HashTagText const& getText() const;
  ImmHashTagValueRead(org::imm::ImmHashTag const* ptr) : ptr{const_cast<org::imm::ImmHashTag*>(ptr)} {  }
};

template <>
struct ImmAdapterT<org::imm::ImmHashTag> : public org::imm::ImmAdapterTBase<org::imm::ImmHashTag>, public org::imm::ImmAdapterHashTagAPI {
  USE_IMM_ADAPTER_BASE(org::imm::ImmHashTag)
  using api_type = org::imm::ImmAdapterHashTagAPI;
  BOOST_DESCRIBE_CLASS(ImmAdapterT, (ImmAdapterTBase, ImmAdapterHashTagAPI), (), (), ());
  ImmAdapterT(org::imm::ImmAdapter const& other) { LOGIC_ASSERTION_CHECK_FMT("Adapter type mismatch, cannot create adapter of type {} from generic adapter of type {}", "HashTag", other.getKind()) }
  org::imm::ImmHashTagValueRead getValue() const { return org::imm::ImmHashTagValueRead{&this->value()}; }
};

struct ImmInlineFootnoteValueRead {
  BOOST_DESCRIBE_CLASS(ImmInlineFootnoteValueRead, (), (), (), ());
  org::imm::ImmInlineFootnote* ptr;
  hstd::ext::ImmBox<hstd::Str> const& getTag() const;
  hstd::ext::ImmBox<hstd::Opt<org::imm::ImmIdT<org::imm::ImmOrg>>> const& getDefinition() const;
  ImmInlineFootnoteValueRead(org::imm::ImmInlineFootnote const* ptr) : ptr{const_cast<org::imm::ImmInlineFootnote*>(ptr)} {  }
};

template <>
struct ImmAdapterT<org::imm::ImmInlineFootnote> : public org::imm::ImmAdapterTBase<org::imm::ImmInlineFootnote>, public org::imm::ImmAdapterInlineFootnoteAPI {
  USE_IMM_ADAPTER_BASE(org::imm::ImmInlineFootnote)
  using api_type = org::imm::ImmAdapterInlineFootnoteAPI;
  BOOST_DESCRIBE_CLASS(ImmAdapterT, (ImmAdapterTBase, ImmAdapterInlineFootnoteAPI), (), (), ());
  ImmAdapterT(org::imm::ImmAdapter const& other) { LOGIC_ASSERTION_CHECK_FMT("Adapter type mismatch, cannot create adapter of type {} from generic adapter of type {}", "InlineFootnote", other.getKind()) }
  org::imm::ImmInlineFootnoteValueRead getValue() const { return org::imm::ImmInlineFootnoteValueRead{&this->value()}; }
};

struct ImmInlineExportValueRead {
  BOOST_DESCRIBE_CLASS(ImmInlineExportValueRead, (), (), (), ());
  org::imm::ImmInlineExport* ptr;
  hstd::ext::ImmBox<hstd::Str> const& getExporter() const;
  hstd::ext::ImmBox<hstd::Str> const& getContent() const;
  ImmInlineExportValueRead(org::imm::ImmInlineExport const* ptr) : ptr{const_cast<org::imm::ImmInlineExport*>(ptr)} {  }
};

template <>
struct ImmAdapterT<org::imm::ImmInlineExport> : public org::imm::ImmAdapterTBase<org::imm::ImmInlineExport>, public org::imm::ImmAdapterInlineExportAPI {
  USE_IMM_ADAPTER_BASE(org::imm::ImmInlineExport)
  using api_type = org::imm::ImmAdapterInlineExportAPI;
  BOOST_DESCRIBE_CLASS(ImmAdapterT, (ImmAdapterTBase, ImmAdapterInlineExportAPI), (), (), ());
  ImmAdapterT(org::imm::ImmAdapter const& other) { LOGIC_ASSERTION_CHECK_FMT("Adapter type mismatch, cannot create adapter of type {} from generic adapter of type {}", "InlineExport", other.getKind()) }
  org::imm::ImmInlineExportValueRead getValue() const { return org::imm::ImmInlineExportValueRead{&this->value()}; }
};

struct ImmTimeValueRead {
  BOOST_DESCRIBE_CLASS(ImmTimeValueRead, (), (), (), ());
  org::imm::ImmTime* ptr;
  bool const& getIsactive() const;
  org::imm::ImmTime::TimeVariant const& getTime() const;
  ImmTimeValueRead(org::imm::ImmTime const* ptr) : ptr{const_cast<org::imm::ImmTime*>(ptr)} {  }
};

template <>
struct ImmAdapterT<org::imm::ImmTime> : public org::imm::ImmAdapterTBase<org::imm::ImmTime>, public org::imm::ImmAdapterTimeAPI {
  USE_IMM_ADAPTER_BASE(org::imm::ImmTime)
  using api_type = org::imm::ImmAdapterTimeAPI;
  BOOST_DESCRIBE_CLASS(ImmAdapterT, (ImmAdapterTBase, ImmAdapterTimeAPI), (), (), ());
  ImmAdapterT(org::imm::ImmAdapter const& other) { LOGIC_ASSERTION_CHECK_FMT("Adapter type mismatch, cannot create adapter of type {} from generic adapter of type {}", "Time", other.getKind()) }
  org::imm::ImmTimeValueRead getValue() const { return org::imm::ImmTimeValueRead{&this->value()}; }
};

struct ImmTimeRangeValueRead {
  BOOST_DESCRIBE_CLASS(ImmTimeRangeValueRead, (), (), (), ());
  org::imm::ImmTimeRange* ptr;
  org::imm::ImmIdT<org::imm::ImmTime> const& getFrom() const;
  org::imm::ImmIdT<org::imm::ImmTime> const& getTo() const;
  ImmTimeRangeValueRead(org::imm::ImmTimeRange const* ptr) : ptr{const_cast<org::imm::ImmTimeRange*>(ptr)} {  }
};

template <>
struct ImmAdapterT<org::imm::ImmTimeRange> : public org::imm::ImmAdapterTBase<org::imm::ImmTimeRange>, public org::imm::ImmAdapterTimeRangeAPI {
  USE_IMM_ADAPTER_BASE(org::imm::ImmTimeRange)
  using api_type = org::imm::ImmAdapterTimeRangeAPI;
  BOOST_DESCRIBE_CLASS(ImmAdapterT, (ImmAdapterTBase, ImmAdapterTimeRangeAPI), (), (), ());
  ImmAdapterT(org::imm::ImmAdapter const& other) { LOGIC_ASSERTION_CHECK_FMT("Adapter type mismatch, cannot create adapter of type {} from generic adapter of type {}", "TimeRange", other.getKind()) }
  org::imm::ImmTimeRangeValueRead getValue() const { return org::imm::ImmTimeRangeValueRead{&this->value()}; }
};

struct ImmMacroValueRead {
  BOOST_DESCRIBE_CLASS(ImmMacroValueRead, (), (), (), ());
  org::imm::ImmMacro* ptr;
  hstd::ext::ImmBox<hstd::Str> const& getName() const;
  org::sem::AttrGroup const& getAttrs() const;
  ImmMacroValueRead(org::imm::ImmMacro const* ptr) : ptr{const_cast<org::imm::ImmMacro*>(ptr)} {  }
};

template <>
struct ImmAdapterT<org::imm::ImmMacro> : public org::imm::ImmAdapterTBase<org::imm::ImmMacro>, public org::imm::ImmAdapterMacroAPI {
  USE_IMM_ADAPTER_BASE(org::imm::ImmMacro)
  using api_type = org::imm::ImmAdapterMacroAPI;
  BOOST_DESCRIBE_CLASS(ImmAdapterT, (ImmAdapterTBase, ImmAdapterMacroAPI), (), (), ());
  ImmAdapterT(org::imm::ImmAdapter const& other) { LOGIC_ASSERTION_CHECK_FMT("Adapter type mismatch, cannot create adapter of type {} from generic adapter of type {}", "Macro", other.getKind()) }
  org::imm::ImmMacroValueRead getValue() const { return org::imm::ImmMacroValueRead{&this->value()}; }
};

struct ImmSymbolValueRead {
  BOOST_DESCRIBE_CLASS(ImmSymbolValueRead, (), (), (), ());
  org::imm::ImmSymbol* ptr;
  hstd::ext::ImmBox<hstd::Str> const& getName() const;
  hstd::ext::ImmVec<org::imm::ImmSymbol::Param> const& getParameters() const;
  hstd::ext::ImmVec<org::imm::ImmIdT<org::imm::ImmOrg>> const& getPositional() const;
  ImmSymbolValueRead(org::imm::ImmSymbol const* ptr) : ptr{const_cast<org::imm::ImmSymbol*>(ptr)} {  }
};

template <>
struct ImmAdapterT<org::imm::ImmSymbol> : public org::imm::ImmAdapterTBase<org::imm::ImmSymbol>, public org::imm::ImmAdapterSymbolAPI {
  USE_IMM_ADAPTER_BASE(org::imm::ImmSymbol)
  using api_type = org::imm::ImmAdapterSymbolAPI;
  BOOST_DESCRIBE_CLASS(ImmAdapterT, (ImmAdapterTBase, ImmAdapterSymbolAPI), (), (), ());
  ImmAdapterT(org::imm::ImmAdapter const& other) { LOGIC_ASSERTION_CHECK_FMT("Adapter type mismatch, cannot create adapter of type {} from generic adapter of type {}", "Symbol", other.getKind()) }
  org::imm::ImmSymbolValueRead getValue() const { return org::imm::ImmSymbolValueRead{&this->value()}; }
};

struct ImmEscapedValueRead {
  BOOST_DESCRIBE_CLASS(ImmEscapedValueRead, (), (), (), ());
  org::imm::ImmEscaped* ptr;
  ImmEscapedValueRead(org::imm::ImmEscaped const* ptr) : ptr{const_cast<org::imm::ImmEscaped*>(ptr)} {  }
};

template <>
struct ImmAdapterT<org::imm::ImmEscaped> : public org::imm::ImmAdapterTBase<org::imm::ImmEscaped>, public org::imm::ImmAdapterEscapedAPI {
  USE_IMM_ADAPTER_BASE(org::imm::ImmEscaped)
  using api_type = org::imm::ImmAdapterEscapedAPI;
  BOOST_DESCRIBE_CLASS(ImmAdapterT, (ImmAdapterTBase, ImmAdapterEscapedAPI), (), (), ());
  ImmAdapterT(org::imm::ImmAdapter const& other) { LOGIC_ASSERTION_CHECK_FMT("Adapter type mismatch, cannot create adapter of type {} from generic adapter of type {}", "Escaped", other.getKind()) }
  org::imm::ImmEscapedValueRead getValue() const { return org::imm::ImmEscapedValueRead{&this->value()}; }
};

struct ImmNewlineValueRead {
  BOOST_DESCRIBE_CLASS(ImmNewlineValueRead, (), (), (), ());
  org::imm::ImmNewline* ptr;
  ImmNewlineValueRead(org::imm::ImmNewline const* ptr) : ptr{const_cast<org::imm::ImmNewline*>(ptr)} {  }
};

template <>
struct ImmAdapterT<org::imm::ImmNewline> : public org::imm::ImmAdapterTBase<org::imm::ImmNewline>, public org::imm::ImmAdapterNewlineAPI {
  USE_IMM_ADAPTER_BASE(org::imm::ImmNewline)
  using api_type = org::imm::ImmAdapterNewlineAPI;
  BOOST_DESCRIBE_CLASS(ImmAdapterT, (ImmAdapterTBase, ImmAdapterNewlineAPI), (), (), ());
  ImmAdapterT(org::imm::ImmAdapter const& other) { LOGIC_ASSERTION_CHECK_FMT("Adapter type mismatch, cannot create adapter of type {} from generic adapter of type {}", "Newline", other.getKind()) }
  org::imm::ImmNewlineValueRead getValue() const { return org::imm::ImmNewlineValueRead{&this->value()}; }
};

struct ImmSpaceValueRead {
  BOOST_DESCRIBE_CLASS(ImmSpaceValueRead, (), (), (), ());
  org::imm::ImmSpace* ptr;
  ImmSpaceValueRead(org::imm::ImmSpace const* ptr) : ptr{const_cast<org::imm::ImmSpace*>(ptr)} {  }
};

template <>
struct ImmAdapterT<org::imm::ImmSpace> : public org::imm::ImmAdapterTBase<org::imm::ImmSpace>, public org::imm::ImmAdapterSpaceAPI {
  USE_IMM_ADAPTER_BASE(org::imm::ImmSpace)
  using api_type = org::imm::ImmAdapterSpaceAPI;
  BOOST_DESCRIBE_CLASS(ImmAdapterT, (ImmAdapterTBase, ImmAdapterSpaceAPI), (), (), ());
  ImmAdapterT(org::imm::ImmAdapter const& other) { LOGIC_ASSERTION_CHECK_FMT("Adapter type mismatch, cannot create adapter of type {} from generic adapter of type {}", "Space", other.getKind()) }
  org::imm::ImmSpaceValueRead getValue() const { return org::imm::ImmSpaceValueRead{&this->value()}; }
};

struct ImmWordValueRead {
  BOOST_DESCRIBE_CLASS(ImmWordValueRead, (), (), (), ());
  org::imm::ImmWord* ptr;
  ImmWordValueRead(org::imm::ImmWord const* ptr) : ptr{const_cast<org::imm::ImmWord*>(ptr)} {  }
};

template <>
struct ImmAdapterT<org::imm::ImmWord> : public org::imm::ImmAdapterTBase<org::imm::ImmWord>, public org::imm::ImmAdapterWordAPI {
  USE_IMM_ADAPTER_BASE(org::imm::ImmWord)
  using api_type = org::imm::ImmAdapterWordAPI;
  BOOST_DESCRIBE_CLASS(ImmAdapterT, (ImmAdapterTBase, ImmAdapterWordAPI), (), (), ());
  ImmAdapterT(org::imm::ImmAdapter const& other) { LOGIC_ASSERTION_CHECK_FMT("Adapter type mismatch, cannot create adapter of type {} from generic adapter of type {}", "Word", other.getKind()) }
  org::imm::ImmWordValueRead getValue() const { return org::imm::ImmWordValueRead{&this->value()}; }
};

struct ImmAtMentionValueRead {
  BOOST_DESCRIBE_CLASS(ImmAtMentionValueRead, (), (), (), ());
  org::imm::ImmAtMention* ptr;
  ImmAtMentionValueRead(org::imm::ImmAtMention const* ptr) : ptr{const_cast<org::imm::ImmAtMention*>(ptr)} {  }
};

template <>
struct ImmAdapterT<org::imm::ImmAtMention> : public org::imm::ImmAdapterTBase<org::imm::ImmAtMention>, public org::imm::ImmAdapterAtMentionAPI {
  USE_IMM_ADAPTER_BASE(org::imm::ImmAtMention)
  using api_type = org::imm::ImmAdapterAtMentionAPI;
  BOOST_DESCRIBE_CLASS(ImmAdapterT, (ImmAdapterTBase, ImmAdapterAtMentionAPI), (), (), ());
  ImmAdapterT(org::imm::ImmAdapter const& other) { LOGIC_ASSERTION_CHECK_FMT("Adapter type mismatch, cannot create adapter of type {} from generic adapter of type {}", "AtMention", other.getKind()) }
  org::imm::ImmAtMentionValueRead getValue() const { return org::imm::ImmAtMentionValueRead{&this->value()}; }
};

struct ImmRawTextValueRead {
  BOOST_DESCRIBE_CLASS(ImmRawTextValueRead, (), (), (), ());
  org::imm::ImmRawText* ptr;
  ImmRawTextValueRead(org::imm::ImmRawText const* ptr) : ptr{const_cast<org::imm::ImmRawText*>(ptr)} {  }
};

template <>
struct ImmAdapterT<org::imm::ImmRawText> : public org::imm::ImmAdapterTBase<org::imm::ImmRawText>, public org::imm::ImmAdapterRawTextAPI {
  USE_IMM_ADAPTER_BASE(org::imm::ImmRawText)
  using api_type = org::imm::ImmAdapterRawTextAPI;
  BOOST_DESCRIBE_CLASS(ImmAdapterT, (ImmAdapterTBase, ImmAdapterRawTextAPI), (), (), ());
  ImmAdapterT(org::imm::ImmAdapter const& other) { LOGIC_ASSERTION_CHECK_FMT("Adapter type mismatch, cannot create adapter of type {} from generic adapter of type {}", "RawText", other.getKind()) }
  org::imm::ImmRawTextValueRead getValue() const { return org::imm::ImmRawTextValueRead{&this->value()}; }
};

struct ImmPunctuationValueRead {
  BOOST_DESCRIBE_CLASS(ImmPunctuationValueRead, (), (), (), ());
  org::imm::ImmPunctuation* ptr;
  ImmPunctuationValueRead(org::imm::ImmPunctuation const* ptr) : ptr{const_cast<org::imm::ImmPunctuation*>(ptr)} {  }
};

template <>
struct ImmAdapterT<org::imm::ImmPunctuation> : public org::imm::ImmAdapterTBase<org::imm::ImmPunctuation>, public org::imm::ImmAdapterPunctuationAPI {
  USE_IMM_ADAPTER_BASE(org::imm::ImmPunctuation)
  using api_type = org::imm::ImmAdapterPunctuationAPI;
  BOOST_DESCRIBE_CLASS(ImmAdapterT, (ImmAdapterTBase, ImmAdapterPunctuationAPI), (), (), ());
  ImmAdapterT(org::imm::ImmAdapter const& other) { LOGIC_ASSERTION_CHECK_FMT("Adapter type mismatch, cannot create adapter of type {} from generic adapter of type {}", "Punctuation", other.getKind()) }
  org::imm::ImmPunctuationValueRead getValue() const { return org::imm::ImmPunctuationValueRead{&this->value()}; }
};

struct ImmPlaceholderValueRead {
  BOOST_DESCRIBE_CLASS(ImmPlaceholderValueRead, (), (), (), ());
  org::imm::ImmPlaceholder* ptr;
  ImmPlaceholderValueRead(org::imm::ImmPlaceholder const* ptr) : ptr{const_cast<org::imm::ImmPlaceholder*>(ptr)} {  }
};

template <>
struct ImmAdapterT<org::imm::ImmPlaceholder> : public org::imm::ImmAdapterTBase<org::imm::ImmPlaceholder>, public org::imm::ImmAdapterPlaceholderAPI {
  USE_IMM_ADAPTER_BASE(org::imm::ImmPlaceholder)
  using api_type = org::imm::ImmAdapterPlaceholderAPI;
  BOOST_DESCRIBE_CLASS(ImmAdapterT, (ImmAdapterTBase, ImmAdapterPlaceholderAPI), (), (), ());
  ImmAdapterT(org::imm::ImmAdapter const& other) { LOGIC_ASSERTION_CHECK_FMT("Adapter type mismatch, cannot create adapter of type {} from generic adapter of type {}", "Placeholder", other.getKind()) }
  org::imm::ImmPlaceholderValueRead getValue() const { return org::imm::ImmPlaceholderValueRead{&this->value()}; }
};

struct ImmBigIdentValueRead {
  BOOST_DESCRIBE_CLASS(ImmBigIdentValueRead, (), (), (), ());
  org::imm::ImmBigIdent* ptr;
  ImmBigIdentValueRead(org::imm::ImmBigIdent const* ptr) : ptr{const_cast<org::imm::ImmBigIdent*>(ptr)} {  }
};

template <>
struct ImmAdapterT<org::imm::ImmBigIdent> : public org::imm::ImmAdapterTBase<org::imm::ImmBigIdent>, public org::imm::ImmAdapterBigIdentAPI {
  USE_IMM_ADAPTER_BASE(org::imm::ImmBigIdent)
  using api_type = org::imm::ImmAdapterBigIdentAPI;
  BOOST_DESCRIBE_CLASS(ImmAdapterT, (ImmAdapterTBase, ImmAdapterBigIdentAPI), (), (), ());
  ImmAdapterT(org::imm::ImmAdapter const& other) { LOGIC_ASSERTION_CHECK_FMT("Adapter type mismatch, cannot create adapter of type {} from generic adapter of type {}", "BigIdent", other.getKind()) }
  org::imm::ImmBigIdentValueRead getValue() const { return org::imm::ImmBigIdentValueRead{&this->value()}; }
};

struct ImmTextTargetValueRead {
  BOOST_DESCRIBE_CLASS(ImmTextTargetValueRead, (), (), (), ());
  org::imm::ImmTextTarget* ptr;
  ImmTextTargetValueRead(org::imm::ImmTextTarget const* ptr) : ptr{const_cast<org::imm::ImmTextTarget*>(ptr)} {  }
};

template <>
struct ImmAdapterT<org::imm::ImmTextTarget> : public org::imm::ImmAdapterTBase<org::imm::ImmTextTarget>, public org::imm::ImmAdapterTextTargetAPI {
  USE_IMM_ADAPTER_BASE(org::imm::ImmTextTarget)
  using api_type = org::imm::ImmAdapterTextTargetAPI;
  BOOST_DESCRIBE_CLASS(ImmAdapterT, (ImmAdapterTBase, ImmAdapterTextTargetAPI), (), (), ());
  ImmAdapterT(org::imm::ImmAdapter const& other) { LOGIC_ASSERTION_CHECK_FMT("Adapter type mismatch, cannot create adapter of type {} from generic adapter of type {}", "TextTarget", other.getKind()) }
  org::imm::ImmTextTargetValueRead getValue() const { return org::imm::ImmTextTargetValueRead{&this->value()}; }
};

struct ImmErrorSkipTokenValueRead {
  BOOST_DESCRIBE_CLASS(ImmErrorSkipTokenValueRead, (), (), (), ());
  org::imm::ImmErrorSkipToken* ptr;
  ImmErrorSkipTokenValueRead(org::imm::ImmErrorSkipToken const* ptr) : ptr{const_cast<org::imm::ImmErrorSkipToken*>(ptr)} {  }
};

template <>
struct ImmAdapterT<org::imm::ImmErrorSkipToken> : public org::imm::ImmAdapterTBase<org::imm::ImmErrorSkipToken>, public org::imm::ImmAdapterErrorSkipTokenAPI {
  USE_IMM_ADAPTER_BASE(org::imm::ImmErrorSkipToken)
  using api_type = org::imm::ImmAdapterErrorSkipTokenAPI;
  BOOST_DESCRIBE_CLASS(ImmAdapterT, (ImmAdapterTBase, ImmAdapterErrorSkipTokenAPI), (), (), ());
  ImmAdapterT(org::imm::ImmAdapter const& other) { LOGIC_ASSERTION_CHECK_FMT("Adapter type mismatch, cannot create adapter of type {} from generic adapter of type {}", "ErrorSkipToken", other.getKind()) }
  org::imm::ImmErrorSkipTokenValueRead getValue() const { return org::imm::ImmErrorSkipTokenValueRead{&this->value()}; }
};

struct ImmErrorSkipGroupValueRead {
  BOOST_DESCRIBE_CLASS(ImmErrorSkipGroupValueRead, (), (), (), ());
  org::imm::ImmErrorSkipGroup* ptr;
  hstd::ext::ImmVec<org::imm::ImmIdT<org::imm::ImmErrorSkipToken>> const& getSkipped() const;
  ImmErrorSkipGroupValueRead(org::imm::ImmErrorSkipGroup const* ptr) : ptr{const_cast<org::imm::ImmErrorSkipGroup*>(ptr)} {  }
};

template <>
struct ImmAdapterT<org::imm::ImmErrorSkipGroup> : public org::imm::ImmAdapterTBase<org::imm::ImmErrorSkipGroup>, public org::imm::ImmAdapterErrorSkipGroupAPI {
  USE_IMM_ADAPTER_BASE(org::imm::ImmErrorSkipGroup)
  using api_type = org::imm::ImmAdapterErrorSkipGroupAPI;
  BOOST_DESCRIBE_CLASS(ImmAdapterT, (ImmAdapterTBase, ImmAdapterErrorSkipGroupAPI), (), (), ());
  ImmAdapterT(org::imm::ImmAdapter const& other) { LOGIC_ASSERTION_CHECK_FMT("Adapter type mismatch, cannot create adapter of type {} from generic adapter of type {}", "ErrorSkipGroup", other.getKind()) }
  org::imm::ImmErrorSkipGroupValueRead getValue() const { return org::imm::ImmErrorSkipGroupValueRead{&this->value()}; }
};

struct ImmMarkupValueRead {
  BOOST_DESCRIBE_CLASS(ImmMarkupValueRead, (), (), (), ());
  org::imm::ImmMarkup* ptr;
  ImmMarkupValueRead(org::imm::ImmMarkup const* ptr) : ptr{const_cast<org::imm::ImmMarkup*>(ptr)} {  }
};

template <>
struct ImmAdapterT<org::imm::ImmMarkup> : public org::imm::ImmAdapterTBase<org::imm::ImmMarkup>, public org::imm::ImmAdapterMarkupAPI {
  USE_IMM_ADAPTER_BASE(org::imm::ImmMarkup)
  using api_type = org::imm::ImmAdapterMarkupAPI;
  BOOST_DESCRIBE_CLASS(ImmAdapterT, (ImmAdapterTBase, ImmAdapterMarkupAPI), (), (), ());
  ImmAdapterT(org::imm::ImmAdapter const& other) { LOGIC_ASSERTION_CHECK_FMT("Adapter type mismatch, cannot create adapter of type {} from generic adapter of type {}", "Markup", other.getKind()) }
  org::imm::ImmMarkupValueRead getValue() const { return org::imm::ImmMarkupValueRead{&this->value()}; }
};

struct ImmBoldValueRead {
  BOOST_DESCRIBE_CLASS(ImmBoldValueRead, (), (), (), ());
  org::imm::ImmBold* ptr;
  ImmBoldValueRead(org::imm::ImmBold const* ptr) : ptr{const_cast<org::imm::ImmBold*>(ptr)} {  }
};

template <>
struct ImmAdapterT<org::imm::ImmBold> : public org::imm::ImmAdapterTBase<org::imm::ImmBold>, public org::imm::ImmAdapterBoldAPI {
  USE_IMM_ADAPTER_BASE(org::imm::ImmBold)
  using api_type = org::imm::ImmAdapterBoldAPI;
  BOOST_DESCRIBE_CLASS(ImmAdapterT, (ImmAdapterTBase, ImmAdapterBoldAPI), (), (), ());
  ImmAdapterT(org::imm::ImmAdapter const& other) { LOGIC_ASSERTION_CHECK_FMT("Adapter type mismatch, cannot create adapter of type {} from generic adapter of type {}", "Bold", other.getKind()) }
  org::imm::ImmBoldValueRead getValue() const { return org::imm::ImmBoldValueRead{&this->value()}; }
};

struct ImmUnderlineValueRead {
  BOOST_DESCRIBE_CLASS(ImmUnderlineValueRead, (), (), (), ());
  org::imm::ImmUnderline* ptr;
  ImmUnderlineValueRead(org::imm::ImmUnderline const* ptr) : ptr{const_cast<org::imm::ImmUnderline*>(ptr)} {  }
};

template <>
struct ImmAdapterT<org::imm::ImmUnderline> : public org::imm::ImmAdapterTBase<org::imm::ImmUnderline>, public org::imm::ImmAdapterUnderlineAPI {
  USE_IMM_ADAPTER_BASE(org::imm::ImmUnderline)
  using api_type = org::imm::ImmAdapterUnderlineAPI;
  BOOST_DESCRIBE_CLASS(ImmAdapterT, (ImmAdapterTBase, ImmAdapterUnderlineAPI), (), (), ());
  ImmAdapterT(org::imm::ImmAdapter const& other) { LOGIC_ASSERTION_CHECK_FMT("Adapter type mismatch, cannot create adapter of type {} from generic adapter of type {}", "Underline", other.getKind()) }
  org::imm::ImmUnderlineValueRead getValue() const { return org::imm::ImmUnderlineValueRead{&this->value()}; }
};

struct ImmMonospaceValueRead {
  BOOST_DESCRIBE_CLASS(ImmMonospaceValueRead, (), (), (), ());
  org::imm::ImmMonospace* ptr;
  ImmMonospaceValueRead(org::imm::ImmMonospace const* ptr) : ptr{const_cast<org::imm::ImmMonospace*>(ptr)} {  }
};

template <>
struct ImmAdapterT<org::imm::ImmMonospace> : public org::imm::ImmAdapterTBase<org::imm::ImmMonospace>, public org::imm::ImmAdapterMonospaceAPI {
  USE_IMM_ADAPTER_BASE(org::imm::ImmMonospace)
  using api_type = org::imm::ImmAdapterMonospaceAPI;
  BOOST_DESCRIBE_CLASS(ImmAdapterT, (ImmAdapterTBase, ImmAdapterMonospaceAPI), (), (), ());
  ImmAdapterT(org::imm::ImmAdapter const& other) { LOGIC_ASSERTION_CHECK_FMT("Adapter type mismatch, cannot create adapter of type {} from generic adapter of type {}", "Monospace", other.getKind()) }
  org::imm::ImmMonospaceValueRead getValue() const { return org::imm::ImmMonospaceValueRead{&this->value()}; }
};

struct ImmMarkQuoteValueRead {
  BOOST_DESCRIBE_CLASS(ImmMarkQuoteValueRead, (), (), (), ());
  org::imm::ImmMarkQuote* ptr;
  ImmMarkQuoteValueRead(org::imm::ImmMarkQuote const* ptr) : ptr{const_cast<org::imm::ImmMarkQuote*>(ptr)} {  }
};

template <>
struct ImmAdapterT<org::imm::ImmMarkQuote> : public org::imm::ImmAdapterTBase<org::imm::ImmMarkQuote>, public org::imm::ImmAdapterMarkQuoteAPI {
  USE_IMM_ADAPTER_BASE(org::imm::ImmMarkQuote)
  using api_type = org::imm::ImmAdapterMarkQuoteAPI;
  BOOST_DESCRIBE_CLASS(ImmAdapterT, (ImmAdapterTBase, ImmAdapterMarkQuoteAPI), (), (), ());
  ImmAdapterT(org::imm::ImmAdapter const& other) { LOGIC_ASSERTION_CHECK_FMT("Adapter type mismatch, cannot create adapter of type {} from generic adapter of type {}", "MarkQuote", other.getKind()) }
  org::imm::ImmMarkQuoteValueRead getValue() const { return org::imm::ImmMarkQuoteValueRead{&this->value()}; }
};

struct ImmVerbatimValueRead {
  BOOST_DESCRIBE_CLASS(ImmVerbatimValueRead, (), (), (), ());
  org::imm::ImmVerbatim* ptr;
  ImmVerbatimValueRead(org::imm::ImmVerbatim const* ptr) : ptr{const_cast<org::imm::ImmVerbatim*>(ptr)} {  }
};

template <>
struct ImmAdapterT<org::imm::ImmVerbatim> : public org::imm::ImmAdapterTBase<org::imm::ImmVerbatim>, public org::imm::ImmAdapterVerbatimAPI {
  USE_IMM_ADAPTER_BASE(org::imm::ImmVerbatim)
  using api_type = org::imm::ImmAdapterVerbatimAPI;
  BOOST_DESCRIBE_CLASS(ImmAdapterT, (ImmAdapterTBase, ImmAdapterVerbatimAPI), (), (), ());
  ImmAdapterT(org::imm::ImmAdapter const& other) { LOGIC_ASSERTION_CHECK_FMT("Adapter type mismatch, cannot create adapter of type {} from generic adapter of type {}", "Verbatim", other.getKind()) }
  org::imm::ImmVerbatimValueRead getValue() const { return org::imm::ImmVerbatimValueRead{&this->value()}; }
};

struct ImmItalicValueRead {
  BOOST_DESCRIBE_CLASS(ImmItalicValueRead, (), (), (), ());
  org::imm::ImmItalic* ptr;
  ImmItalicValueRead(org::imm::ImmItalic const* ptr) : ptr{const_cast<org::imm::ImmItalic*>(ptr)} {  }
};

template <>
struct ImmAdapterT<org::imm::ImmItalic> : public org::imm::ImmAdapterTBase<org::imm::ImmItalic>, public org::imm::ImmAdapterItalicAPI {
  USE_IMM_ADAPTER_BASE(org::imm::ImmItalic)
  using api_type = org::imm::ImmAdapterItalicAPI;
  BOOST_DESCRIBE_CLASS(ImmAdapterT, (ImmAdapterTBase, ImmAdapterItalicAPI), (), (), ());
  ImmAdapterT(org::imm::ImmAdapter const& other) { LOGIC_ASSERTION_CHECK_FMT("Adapter type mismatch, cannot create adapter of type {} from generic adapter of type {}", "Italic", other.getKind()) }
  org::imm::ImmItalicValueRead getValue() const { return org::imm::ImmItalicValueRead{&this->value()}; }
};

struct ImmStrikeValueRead {
  BOOST_DESCRIBE_CLASS(ImmStrikeValueRead, (), (), (), ());
  org::imm::ImmStrike* ptr;
  ImmStrikeValueRead(org::imm::ImmStrike const* ptr) : ptr{const_cast<org::imm::ImmStrike*>(ptr)} {  }
};

template <>
struct ImmAdapterT<org::imm::ImmStrike> : public org::imm::ImmAdapterTBase<org::imm::ImmStrike>, public org::imm::ImmAdapterStrikeAPI {
  USE_IMM_ADAPTER_BASE(org::imm::ImmStrike)
  using api_type = org::imm::ImmAdapterStrikeAPI;
  BOOST_DESCRIBE_CLASS(ImmAdapterT, (ImmAdapterTBase, ImmAdapterStrikeAPI), (), (), ());
  ImmAdapterT(org::imm::ImmAdapter const& other) { LOGIC_ASSERTION_CHECK_FMT("Adapter type mismatch, cannot create adapter of type {} from generic adapter of type {}", "Strike", other.getKind()) }
  org::imm::ImmStrikeValueRead getValue() const { return org::imm::ImmStrikeValueRead{&this->value()}; }
};

struct ImmParValueRead {
  BOOST_DESCRIBE_CLASS(ImmParValueRead, (), (), (), ());
  org::imm::ImmPar* ptr;
  ImmParValueRead(org::imm::ImmPar const* ptr) : ptr{const_cast<org::imm::ImmPar*>(ptr)} {  }
};

template <>
struct ImmAdapterT<org::imm::ImmPar> : public org::imm::ImmAdapterTBase<org::imm::ImmPar>, public org::imm::ImmAdapterParAPI {
  USE_IMM_ADAPTER_BASE(org::imm::ImmPar)
  using api_type = org::imm::ImmAdapterParAPI;
  BOOST_DESCRIBE_CLASS(ImmAdapterT, (ImmAdapterTBase, ImmAdapterParAPI), (), (), ());
  ImmAdapterT(org::imm::ImmAdapter const& other) { LOGIC_ASSERTION_CHECK_FMT("Adapter type mismatch, cannot create adapter of type {} from generic adapter of type {}", "Par", other.getKind()) }
  org::imm::ImmParValueRead getValue() const { return org::imm::ImmParValueRead{&this->value()}; }
};

struct ImmRadioTargetValueRead {
  BOOST_DESCRIBE_CLASS(ImmRadioTargetValueRead, (), (), (), ());
  org::imm::ImmRadioTarget* ptr;
  hstd::ext::ImmVec<hstd::Str> const& getWords() const;
  ImmRadioTargetValueRead(org::imm::ImmRadioTarget const* ptr) : ptr{const_cast<org::imm::ImmRadioTarget*>(ptr)} {  }
};

template <>
struct ImmAdapterT<org::imm::ImmRadioTarget> : public org::imm::ImmAdapterTBase<org::imm::ImmRadioTarget>, public org::imm::ImmAdapterRadioTargetAPI {
  USE_IMM_ADAPTER_BASE(org::imm::ImmRadioTarget)
  using api_type = org::imm::ImmAdapterRadioTargetAPI;
  BOOST_DESCRIBE_CLASS(ImmAdapterT, (ImmAdapterTBase, ImmAdapterRadioTargetAPI), (), (), ());
  ImmAdapterT(org::imm::ImmAdapter const& other) { LOGIC_ASSERTION_CHECK_FMT("Adapter type mismatch, cannot create adapter of type {} from generic adapter of type {}", "RadioTarget", other.getKind()) }
  org::imm::ImmRadioTargetValueRead getValue() const { return org::imm::ImmRadioTargetValueRead{&this->value()}; }
};

struct ImmLatexValueRead {
  BOOST_DESCRIBE_CLASS(ImmLatexValueRead, (), (), (), ());
  org::imm::ImmLatex* ptr;
  ImmLatexValueRead(org::imm::ImmLatex const* ptr) : ptr{const_cast<org::imm::ImmLatex*>(ptr)} {  }
};

template <>
struct ImmAdapterT<org::imm::ImmLatex> : public org::imm::ImmAdapterTBase<org::imm::ImmLatex>, public org::imm::ImmAdapterLatexAPI {
  USE_IMM_ADAPTER_BASE(org::imm::ImmLatex)
  using api_type = org::imm::ImmAdapterLatexAPI;
  BOOST_DESCRIBE_CLASS(ImmAdapterT, (ImmAdapterTBase, ImmAdapterLatexAPI), (), (), ());
  ImmAdapterT(org::imm::ImmAdapter const& other) { LOGIC_ASSERTION_CHECK_FMT("Adapter type mismatch, cannot create adapter of type {} from generic adapter of type {}", "Latex", other.getKind()) }
  org::imm::ImmLatexValueRead getValue() const { return org::imm::ImmLatexValueRead{&this->value()}; }
};

struct ImmLinkValueRead {
  BOOST_DESCRIBE_CLASS(ImmLinkValueRead, (), (), (), ());
  org::imm::ImmLink* ptr;
  hstd::ext::ImmBox<hstd::Opt<org::imm::ImmIdT<org::imm::ImmParagraph>>> const& getDescription() const;
  org::sem::LinkTarget const& getTarget() const;
  ImmLinkValueRead(org::imm::ImmLink const* ptr) : ptr{const_cast<org::imm::ImmLink*>(ptr)} {  }
};

template <>
struct ImmAdapterT<org::imm::ImmLink> : public org::imm::ImmAdapterTBase<org::imm::ImmLink>, public org::imm::ImmAdapterLinkAPI {
  USE_IMM_ADAPTER_BASE(org::imm::ImmLink)
  using api_type = org::imm::ImmAdapterLinkAPI;
  BOOST_DESCRIBE_CLASS(ImmAdapterT, (ImmAdapterTBase, ImmAdapterLinkAPI), (), (), ());
  ImmAdapterT(org::imm::ImmAdapter const& other) { LOGIC_ASSERTION_CHECK_FMT("Adapter type mismatch, cannot create adapter of type {} from generic adapter of type {}", "Link", other.getKind()) }
  org::imm::ImmLinkValueRead getValue() const { return org::imm::ImmLinkValueRead{&this->value()}; }
};

struct ImmBlockCenterValueRead {
  BOOST_DESCRIBE_CLASS(ImmBlockCenterValueRead, (), (), (), ());
  org::imm::ImmBlockCenter* ptr;
  ImmBlockCenterValueRead(org::imm::ImmBlockCenter const* ptr) : ptr{const_cast<org::imm::ImmBlockCenter*>(ptr)} {  }
};

template <>
struct ImmAdapterT<org::imm::ImmBlockCenter> : public org::imm::ImmAdapterTBase<org::imm::ImmBlockCenter>, public org::imm::ImmAdapterBlockCenterAPI {
  USE_IMM_ADAPTER_BASE(org::imm::ImmBlockCenter)
  using api_type = org::imm::ImmAdapterBlockCenterAPI;
  BOOST_DESCRIBE_CLASS(ImmAdapterT, (ImmAdapterTBase, ImmAdapterBlockCenterAPI), (), (), ());
  ImmAdapterT(org::imm::ImmAdapter const& other) { LOGIC_ASSERTION_CHECK_FMT("Adapter type mismatch, cannot create adapter of type {} from generic adapter of type {}", "BlockCenter", other.getKind()) }
  org::imm::ImmBlockCenterValueRead getValue() const { return org::imm::ImmBlockCenterValueRead{&this->value()}; }
};

struct ImmBlockQuoteValueRead {
  BOOST_DESCRIBE_CLASS(ImmBlockQuoteValueRead, (), (), (), ());
  org::imm::ImmBlockQuote* ptr;
  ImmBlockQuoteValueRead(org::imm::ImmBlockQuote const* ptr) : ptr{const_cast<org::imm::ImmBlockQuote*>(ptr)} {  }
};

template <>
struct ImmAdapterT<org::imm::ImmBlockQuote> : public org::imm::ImmAdapterTBase<org::imm::ImmBlockQuote>, public org::imm::ImmAdapterBlockQuoteAPI {
  USE_IMM_ADAPTER_BASE(org::imm::ImmBlockQuote)
  using api_type = org::imm::ImmAdapterBlockQuoteAPI;
  BOOST_DESCRIBE_CLASS(ImmAdapterT, (ImmAdapterTBase, ImmAdapterBlockQuoteAPI), (), (), ());
  ImmAdapterT(org::imm::ImmAdapter const& other) { LOGIC_ASSERTION_CHECK_FMT("Adapter type mismatch, cannot create adapter of type {} from generic adapter of type {}", "BlockQuote", other.getKind()) }
  org::imm::ImmBlockQuoteValueRead getValue() const { return org::imm::ImmBlockQuoteValueRead{&this->value()}; }
};

struct ImmBlockCommentValueRead {
  BOOST_DESCRIBE_CLASS(ImmBlockCommentValueRead, (), (), (), ());
  org::imm::ImmBlockComment* ptr;
  ImmBlockCommentValueRead(org::imm::ImmBlockComment const* ptr) : ptr{const_cast<org::imm::ImmBlockComment*>(ptr)} {  }
};

template <>
struct ImmAdapterT<org::imm::ImmBlockComment> : public org::imm::ImmAdapterTBase<org::imm::ImmBlockComment>, public org::imm::ImmAdapterBlockCommentAPI {
  USE_IMM_ADAPTER_BASE(org::imm::ImmBlockComment)
  using api_type = org::imm::ImmAdapterBlockCommentAPI;
  BOOST_DESCRIBE_CLASS(ImmAdapterT, (ImmAdapterTBase, ImmAdapterBlockCommentAPI), (), (), ());
  ImmAdapterT(org::imm::ImmAdapter const& other) { LOGIC_ASSERTION_CHECK_FMT("Adapter type mismatch, cannot create adapter of type {} from generic adapter of type {}", "BlockComment", other.getKind()) }
  org::imm::ImmBlockCommentValueRead getValue() const { return org::imm::ImmBlockCommentValueRead{&this->value()}; }
};

struct ImmBlockVerseValueRead {
  BOOST_DESCRIBE_CLASS(ImmBlockVerseValueRead, (), (), (), ());
  org::imm::ImmBlockVerse* ptr;
  ImmBlockVerseValueRead(org::imm::ImmBlockVerse const* ptr) : ptr{const_cast<org::imm::ImmBlockVerse*>(ptr)} {  }
};

template <>
struct ImmAdapterT<org::imm::ImmBlockVerse> : public org::imm::ImmAdapterTBase<org::imm::ImmBlockVerse>, public org::imm::ImmAdapterBlockVerseAPI {
  USE_IMM_ADAPTER_BASE(org::imm::ImmBlockVerse)
  using api_type = org::imm::ImmAdapterBlockVerseAPI;
  BOOST_DESCRIBE_CLASS(ImmAdapterT, (ImmAdapterTBase, ImmAdapterBlockVerseAPI), (), (), ());
  ImmAdapterT(org::imm::ImmAdapter const& other) { LOGIC_ASSERTION_CHECK_FMT("Adapter type mismatch, cannot create adapter of type {} from generic adapter of type {}", "BlockVerse", other.getKind()) }
  org::imm::ImmBlockVerseValueRead getValue() const { return org::imm::ImmBlockVerseValueRead{&this->value()}; }
};

struct ImmBlockDynamicFallbackValueRead {
  BOOST_DESCRIBE_CLASS(ImmBlockDynamicFallbackValueRead, (), (), (), ());
  org::imm::ImmBlockDynamicFallback* ptr;
  hstd::ext::ImmBox<hstd::Str> const& getName() const;
  ImmBlockDynamicFallbackValueRead(org::imm::ImmBlockDynamicFallback const* ptr) : ptr{const_cast<org::imm::ImmBlockDynamicFallback*>(ptr)} {  }
};

template <>
struct ImmAdapterT<org::imm::ImmBlockDynamicFallback> : public org::imm::ImmAdapterTBase<org::imm::ImmBlockDynamicFallback>, public org::imm::ImmAdapterBlockDynamicFallbackAPI {
  USE_IMM_ADAPTER_BASE(org::imm::ImmBlockDynamicFallback)
  using api_type = org::imm::ImmAdapterBlockDynamicFallbackAPI;
  BOOST_DESCRIBE_CLASS(ImmAdapterT, (ImmAdapterTBase, ImmAdapterBlockDynamicFallbackAPI), (), (), ());
  ImmAdapterT(org::imm::ImmAdapter const& other) { LOGIC_ASSERTION_CHECK_FMT("Adapter type mismatch, cannot create adapter of type {} from generic adapter of type {}", "BlockDynamicFallback", other.getKind()) }
  org::imm::ImmBlockDynamicFallbackValueRead getValue() const { return org::imm::ImmBlockDynamicFallbackValueRead{&this->value()}; }
};

struct ImmBlockExampleValueRead {
  BOOST_DESCRIBE_CLASS(ImmBlockExampleValueRead, (), (), (), ());
  org::imm::ImmBlockExample* ptr;
  ImmBlockExampleValueRead(org::imm::ImmBlockExample const* ptr) : ptr{const_cast<org::imm::ImmBlockExample*>(ptr)} {  }
};

template <>
struct ImmAdapterT<org::imm::ImmBlockExample> : public org::imm::ImmAdapterTBase<org::imm::ImmBlockExample>, public org::imm::ImmAdapterBlockExampleAPI {
  USE_IMM_ADAPTER_BASE(org::imm::ImmBlockExample)
  using api_type = org::imm::ImmAdapterBlockExampleAPI;
  BOOST_DESCRIBE_CLASS(ImmAdapterT, (ImmAdapterTBase, ImmAdapterBlockExampleAPI), (), (), ());
  ImmAdapterT(org::imm::ImmAdapter const& other) { LOGIC_ASSERTION_CHECK_FMT("Adapter type mismatch, cannot create adapter of type {} from generic adapter of type {}", "BlockExample", other.getKind()) }
  org::imm::ImmBlockExampleValueRead getValue() const { return org::imm::ImmBlockExampleValueRead{&this->value()}; }
};

struct ImmBlockExportValueRead {
  BOOST_DESCRIBE_CLASS(ImmBlockExportValueRead, (), (), (), ());
  org::imm::ImmBlockExport* ptr;
  hstd::ext::ImmBox<hstd::Str> const& getExporter() const;
  hstd::ext::ImmBox<hstd::Str> const& getContent() const;
  ImmBlockExportValueRead(org::imm::ImmBlockExport const* ptr) : ptr{const_cast<org::imm::ImmBlockExport*>(ptr)} {  }
};

template <>
struct ImmAdapterT<org::imm::ImmBlockExport> : public org::imm::ImmAdapterTBase<org::imm::ImmBlockExport>, public org::imm::ImmAdapterBlockExportAPI {
  USE_IMM_ADAPTER_BASE(org::imm::ImmBlockExport)
  using api_type = org::imm::ImmAdapterBlockExportAPI;
  BOOST_DESCRIBE_CLASS(ImmAdapterT, (ImmAdapterTBase, ImmAdapterBlockExportAPI), (), (), ());
  ImmAdapterT(org::imm::ImmAdapter const& other) { LOGIC_ASSERTION_CHECK_FMT("Adapter type mismatch, cannot create adapter of type {} from generic adapter of type {}", "BlockExport", other.getKind()) }
  org::imm::ImmBlockExportValueRead getValue() const { return org::imm::ImmBlockExportValueRead{&this->value()}; }
};

struct ImmBlockAdmonitionValueRead {
  BOOST_DESCRIBE_CLASS(ImmBlockAdmonitionValueRead, (), (), (), ());
  org::imm::ImmBlockAdmonition* ptr;
  ImmBlockAdmonitionValueRead(org::imm::ImmBlockAdmonition const* ptr) : ptr{const_cast<org::imm::ImmBlockAdmonition*>(ptr)} {  }
};

template <>
struct ImmAdapterT<org::imm::ImmBlockAdmonition> : public org::imm::ImmAdapterTBase<org::imm::ImmBlockAdmonition>, public org::imm::ImmAdapterBlockAdmonitionAPI {
  USE_IMM_ADAPTER_BASE(org::imm::ImmBlockAdmonition)
  using api_type = org::imm::ImmAdapterBlockAdmonitionAPI;
  BOOST_DESCRIBE_CLASS(ImmAdapterT, (ImmAdapterTBase, ImmAdapterBlockAdmonitionAPI), (), (), ());
  ImmAdapterT(org::imm::ImmAdapter const& other) { LOGIC_ASSERTION_CHECK_FMT("Adapter type mismatch, cannot create adapter of type {} from generic adapter of type {}", "BlockAdmonition", other.getKind()) }
  org::imm::ImmBlockAdmonitionValueRead getValue() const { return org::imm::ImmBlockAdmonitionValueRead{&this->value()}; }
};

struct ImmBlockCodeEvalResultValueRead {
  BOOST_DESCRIBE_CLASS(ImmBlockCodeEvalResultValueRead, (), (), (), ());
  org::imm::ImmBlockCodeEvalResult* ptr;
  hstd::ext::ImmVec<org::sem::OrgCodeEvalOutput> const& getRaw() const;
  org::imm::ImmIdT<org::imm::ImmOrg> const& getNode() const;
  ImmBlockCodeEvalResultValueRead(org::imm::ImmBlockCodeEvalResult const* ptr) : ptr{const_cast<org::imm::ImmBlockCodeEvalResult*>(ptr)} {  }
};

template <>
struct ImmAdapterT<org::imm::ImmBlockCodeEvalResult> : public org::imm::ImmAdapterTBase<org::imm::ImmBlockCodeEvalResult>, public org::imm::ImmAdapterBlockCodeEvalResultAPI {
  USE_IMM_ADAPTER_BASE(org::imm::ImmBlockCodeEvalResult)
  using api_type = org::imm::ImmAdapterBlockCodeEvalResultAPI;
  BOOST_DESCRIBE_CLASS(ImmAdapterT, (ImmAdapterTBase, ImmAdapterBlockCodeEvalResultAPI), (), (), ());
  ImmAdapterT(org::imm::ImmAdapter const& other) { LOGIC_ASSERTION_CHECK_FMT("Adapter type mismatch, cannot create adapter of type {} from generic adapter of type {}", "BlockCodeEvalResult", other.getKind()) }
  org::imm::ImmBlockCodeEvalResultValueRead getValue() const { return org::imm::ImmBlockCodeEvalResultValueRead{&this->value()}; }
};

struct ImmBlockCodeValueRead {
  BOOST_DESCRIBE_CLASS(ImmBlockCodeValueRead, (), (), (), ());
  org::imm::ImmBlockCode* ptr;
  hstd::ext::ImmBox<hstd::Opt<hstd::Str>> const& getLang() const;
  hstd::ext::ImmVec<org::imm::ImmIdT<org::imm::ImmBlockCodeEvalResult>> const& getResult() const;
  hstd::ext::ImmVec<org::sem::BlockCodeLine> const& getLines() const;
  org::sem::AttrGroup const& getSwitches() const;
  ImmBlockCodeValueRead(org::imm::ImmBlockCode const* ptr) : ptr{const_cast<org::imm::ImmBlockCode*>(ptr)} {  }
};

template <>
struct ImmAdapterT<org::imm::ImmBlockCode> : public org::imm::ImmAdapterTBase<org::imm::ImmBlockCode>, public org::imm::ImmAdapterBlockCodeAPI {
  USE_IMM_ADAPTER_BASE(org::imm::ImmBlockCode)
  using api_type = org::imm::ImmAdapterBlockCodeAPI;
  BOOST_DESCRIBE_CLASS(ImmAdapterT, (ImmAdapterTBase, ImmAdapterBlockCodeAPI), (), (), ());
  ImmAdapterT(org::imm::ImmAdapter const& other) { LOGIC_ASSERTION_CHECK_FMT("Adapter type mismatch, cannot create adapter of type {} from generic adapter of type {}", "BlockCode", other.getKind()) }
  org::imm::ImmBlockCodeValueRead getValue() const { return org::imm::ImmBlockCodeValueRead{&this->value()}; }
};

struct ImmSubtreeLogValueRead {
  BOOST_DESCRIBE_CLASS(ImmSubtreeLogValueRead, (), (), (), ());
  org::imm::ImmSubtreeLog* ptr;
  org::sem::SubtreeLogHead const& getHead() const;
  hstd::ext::ImmBox<hstd::Opt<org::imm::ImmIdT<org::imm::ImmStmtList>>> const& getDesc() const;
  ImmSubtreeLogValueRead(org::imm::ImmSubtreeLog const* ptr) : ptr{const_cast<org::imm::ImmSubtreeLog*>(ptr)} {  }
};

template <>
struct ImmAdapterT<org::imm::ImmSubtreeLog> : public org::imm::ImmAdapterTBase<org::imm::ImmSubtreeLog>, public org::imm::ImmAdapterSubtreeLogAPI {
  USE_IMM_ADAPTER_BASE(org::imm::ImmSubtreeLog)
  using api_type = org::imm::ImmAdapterSubtreeLogAPI;
  BOOST_DESCRIBE_CLASS(ImmAdapterT, (ImmAdapterTBase, ImmAdapterSubtreeLogAPI), (), (), ());
  ImmAdapterT(org::imm::ImmAdapter const& other) { LOGIC_ASSERTION_CHECK_FMT("Adapter type mismatch, cannot create adapter of type {} from generic adapter of type {}", "SubtreeLog", other.getKind()) }
  org::imm::ImmSubtreeLogValueRead getValue() const { return org::imm::ImmSubtreeLogValueRead{&this->value()}; }
};

struct ImmSubtreeValueRead {
  BOOST_DESCRIBE_CLASS(ImmSubtreeValueRead, (), (), (), ());
  org::imm::ImmSubtree* ptr;
  int const& getLevel() const;
  hstd::ext::ImmBox<hstd::Opt<hstd::Str>> const& getTreeid() const;
  hstd::ext::ImmBox<hstd::Opt<hstd::Str>> const& getTodo() const;
  hstd::ext::ImmBox<hstd::Opt<org::sem::SubtreeCompletion>> const& getCompletion() const;
  hstd::ext::ImmBox<hstd::Opt<org::imm::ImmIdT<org::imm::ImmParagraph>>> const& getDescription() const;
  hstd::ext::ImmVec<org::imm::ImmIdT<org::imm::ImmHashTag>> const& getTags() const;
  org::imm::ImmIdT<org::imm::ImmParagraph> const& getTitle() const;
  hstd::ext::ImmVec<org::imm::ImmIdT<org::imm::ImmSubtreeLog>> const& getLogbook() const;
  hstd::ext::ImmVec<org::sem::NamedProperty> const& getProperties() const;
  hstd::ext::ImmBox<hstd::Opt<org::imm::ImmIdT<org::imm::ImmTime>>> const& getClosed() const;
  hstd::ext::ImmBox<hstd::Opt<org::imm::ImmIdT<org::imm::ImmTime>>> const& getDeadline() const;
  hstd::ext::ImmBox<hstd::Opt<org::imm::ImmIdT<org::imm::ImmTime>>> const& getScheduled() const;
  bool const& getIscomment() const;
  bool const& getIsarchived() const;
  hstd::ext::ImmBox<hstd::Opt<hstd::Str>> const& getPriority() const;
  ImmSubtreeValueRead(org::imm::ImmSubtree const* ptr) : ptr{const_cast<org::imm::ImmSubtree*>(ptr)} {  }
};

template <>
struct ImmAdapterT<org::imm::ImmSubtree> : public org::imm::ImmAdapterTBase<org::imm::ImmSubtree>, public org::imm::ImmAdapterSubtreeAPI {
  USE_IMM_ADAPTER_BASE(org::imm::ImmSubtree)
  using api_type = org::imm::ImmAdapterSubtreeAPI;
  BOOST_DESCRIBE_CLASS(ImmAdapterT, (ImmAdapterTBase, ImmAdapterSubtreeAPI), (), (), ());
  ImmAdapterT(org::imm::ImmAdapter const& other) { LOGIC_ASSERTION_CHECK_FMT("Adapter type mismatch, cannot create adapter of type {} from generic adapter of type {}", "Subtree", other.getKind()) }
  org::imm::ImmSubtreeValueRead getValue() const { return org::imm::ImmSubtreeValueRead{&this->value()}; }
};

struct ImmCellValueRead {
  BOOST_DESCRIBE_CLASS(ImmCellValueRead, (), (), (), ());
  org::imm::ImmCell* ptr;
  bool const& getIsblock() const;
  ImmCellValueRead(org::imm::ImmCell const* ptr) : ptr{const_cast<org::imm::ImmCell*>(ptr)} {  }
};

template <>
struct ImmAdapterT<org::imm::ImmCell> : public org::imm::ImmAdapterTBase<org::imm::ImmCell>, public org::imm::ImmAdapterCellAPI {
  USE_IMM_ADAPTER_BASE(org::imm::ImmCell)
  using api_type = org::imm::ImmAdapterCellAPI;
  BOOST_DESCRIBE_CLASS(ImmAdapterT, (ImmAdapterTBase, ImmAdapterCellAPI), (), (), ());
  ImmAdapterT(org::imm::ImmAdapter const& other) { LOGIC_ASSERTION_CHECK_FMT("Adapter type mismatch, cannot create adapter of type {} from generic adapter of type {}", "Cell", other.getKind()) }
  org::imm::ImmCellValueRead getValue() const { return org::imm::ImmCellValueRead{&this->value()}; }
};

struct ImmRowValueRead {
  BOOST_DESCRIBE_CLASS(ImmRowValueRead, (), (), (), ());
  org::imm::ImmRow* ptr;
  hstd::ext::ImmVec<org::imm::ImmIdT<org::imm::ImmCell>> const& getCells() const;
  bool const& getIsblock() const;
  ImmRowValueRead(org::imm::ImmRow const* ptr) : ptr{const_cast<org::imm::ImmRow*>(ptr)} {  }
};

template <>
struct ImmAdapterT<org::imm::ImmRow> : public org::imm::ImmAdapterTBase<org::imm::ImmRow>, public org::imm::ImmAdapterRowAPI {
  USE_IMM_ADAPTER_BASE(org::imm::ImmRow)
  using api_type = org::imm::ImmAdapterRowAPI;
  BOOST_DESCRIBE_CLASS(ImmAdapterT, (ImmAdapterTBase, ImmAdapterRowAPI), (), (), ());
  ImmAdapterT(org::imm::ImmAdapter const& other) { LOGIC_ASSERTION_CHECK_FMT("Adapter type mismatch, cannot create adapter of type {} from generic adapter of type {}", "Row", other.getKind()) }
  org::imm::ImmRowValueRead getValue() const { return org::imm::ImmRowValueRead{&this->value()}; }
};

struct ImmTableValueRead {
  BOOST_DESCRIBE_CLASS(ImmTableValueRead, (), (), (), ());
  org::imm::ImmTable* ptr;
  hstd::ext::ImmVec<org::imm::ImmIdT<org::imm::ImmRow>> const& getRows() const;
  bool const& getIsblock() const;
  ImmTableValueRead(org::imm::ImmTable const* ptr) : ptr{const_cast<org::imm::ImmTable*>(ptr)} {  }
};

template <>
struct ImmAdapterT<org::imm::ImmTable> : public org::imm::ImmAdapterTBase<org::imm::ImmTable>, public org::imm::ImmAdapterTableAPI {
  USE_IMM_ADAPTER_BASE(org::imm::ImmTable)
  using api_type = org::imm::ImmAdapterTableAPI;
  BOOST_DESCRIBE_CLASS(ImmAdapterT, (ImmAdapterTBase, ImmAdapterTableAPI), (), (), ());
  ImmAdapterT(org::imm::ImmAdapter const& other) { LOGIC_ASSERTION_CHECK_FMT("Adapter type mismatch, cannot create adapter of type {} from generic adapter of type {}", "Table", other.getKind()) }
  org::imm::ImmTableValueRead getValue() const { return org::imm::ImmTableValueRead{&this->value()}; }
};

struct ImmParagraphValueRead {
  BOOST_DESCRIBE_CLASS(ImmParagraphValueRead, (), (), (), ());
  org::imm::ImmParagraph* ptr;
  ImmParagraphValueRead(org::imm::ImmParagraph const* ptr) : ptr{const_cast<org::imm::ImmParagraph*>(ptr)} {  }
};

template <>
struct ImmAdapterT<org::imm::ImmParagraph> : public org::imm::ImmAdapterTBase<org::imm::ImmParagraph>, public org::imm::ImmAdapterParagraphAPI {
  USE_IMM_ADAPTER_BASE(org::imm::ImmParagraph)
  using api_type = org::imm::ImmAdapterParagraphAPI;
  BOOST_DESCRIBE_CLASS(ImmAdapterT, (ImmAdapterTBase, ImmAdapterParagraphAPI), (), (), ());
  ImmAdapterT(org::imm::ImmAdapter const& other) { LOGIC_ASSERTION_CHECK_FMT("Adapter type mismatch, cannot create adapter of type {} from generic adapter of type {}", "Paragraph", other.getKind()) }
  org::imm::ImmParagraphValueRead getValue() const { return org::imm::ImmParagraphValueRead{&this->value()}; }
};

struct ImmColonExampleValueRead {
  BOOST_DESCRIBE_CLASS(ImmColonExampleValueRead, (), (), (), ());
  org::imm::ImmColonExample* ptr;
  ImmColonExampleValueRead(org::imm::ImmColonExample const* ptr) : ptr{const_cast<org::imm::ImmColonExample*>(ptr)} {  }
};

template <>
struct ImmAdapterT<org::imm::ImmColonExample> : public org::imm::ImmAdapterTBase<org::imm::ImmColonExample>, public org::imm::ImmAdapterColonExampleAPI {
  USE_IMM_ADAPTER_BASE(org::imm::ImmColonExample)
  using api_type = org::imm::ImmAdapterColonExampleAPI;
  BOOST_DESCRIBE_CLASS(ImmAdapterT, (ImmAdapterTBase, ImmAdapterColonExampleAPI), (), (), ());
  ImmAdapterT(org::imm::ImmAdapter const& other) { LOGIC_ASSERTION_CHECK_FMT("Adapter type mismatch, cannot create adapter of type {} from generic adapter of type {}", "ColonExample", other.getKind()) }
  org::imm::ImmColonExampleValueRead getValue() const { return org::imm::ImmColonExampleValueRead{&this->value()}; }
};

struct ImmCmdAttrValueRead {
  BOOST_DESCRIBE_CLASS(ImmCmdAttrValueRead, (), (), (), ());
  org::imm::ImmCmdAttr* ptr;
  hstd::ext::ImmBox<hstd::Str> const& getTarget() const;
  ImmCmdAttrValueRead(org::imm::ImmCmdAttr const* ptr) : ptr{const_cast<org::imm::ImmCmdAttr*>(ptr)} {  }
};

template <>
struct ImmAdapterT<org::imm::ImmCmdAttr> : public org::imm::ImmAdapterTBase<org::imm::ImmCmdAttr>, public org::imm::ImmAdapterCmdAttrAPI {
  USE_IMM_ADAPTER_BASE(org::imm::ImmCmdAttr)
  using api_type = org::imm::ImmAdapterCmdAttrAPI;
  BOOST_DESCRIBE_CLASS(ImmAdapterT, (ImmAdapterTBase, ImmAdapterCmdAttrAPI), (), (), ());
  ImmAdapterT(org::imm::ImmAdapter const& other) { LOGIC_ASSERTION_CHECK_FMT("Adapter type mismatch, cannot create adapter of type {} from generic adapter of type {}", "CmdAttr", other.getKind()) }
  org::imm::ImmCmdAttrValueRead getValue() const { return org::imm::ImmCmdAttrValueRead{&this->value()}; }
};

struct ImmCmdExportValueRead {
  BOOST_DESCRIBE_CLASS(ImmCmdExportValueRead, (), (), (), ());
  org::imm::ImmCmdExport* ptr;
  hstd::ext::ImmBox<hstd::Str> const& getExporter() const;
  hstd::ext::ImmBox<hstd::Str> const& getContent() const;
  ImmCmdExportValueRead(org::imm::ImmCmdExport const* ptr) : ptr{const_cast<org::imm::ImmCmdExport*>(ptr)} {  }
};

template <>
struct ImmAdapterT<org::imm::ImmCmdExport> : public org::imm::ImmAdapterTBase<org::imm::ImmCmdExport>, public org::imm::ImmAdapterCmdExportAPI {
  USE_IMM_ADAPTER_BASE(org::imm::ImmCmdExport)
  using api_type = org::imm::ImmAdapterCmdExportAPI;
  BOOST_DESCRIBE_CLASS(ImmAdapterT, (ImmAdapterTBase, ImmAdapterCmdExportAPI), (), (), ());
  ImmAdapterT(org::imm::ImmAdapter const& other) { LOGIC_ASSERTION_CHECK_FMT("Adapter type mismatch, cannot create adapter of type {} from generic adapter of type {}", "CmdExport", other.getKind()) }
  org::imm::ImmCmdExportValueRead getValue() const { return org::imm::ImmCmdExportValueRead{&this->value()}; }
};

struct ImmCallValueRead {
  BOOST_DESCRIBE_CLASS(ImmCallValueRead, (), (), (), ());
  org::imm::ImmCall* ptr;
  hstd::ext::ImmBox<hstd::Str> const& getName() const;
  org::sem::AttrGroup const& getAttrs() const;
  bool const& getIscommand() const;
  ImmCallValueRead(org::imm::ImmCall const* ptr) : ptr{const_cast<org::imm::ImmCall*>(ptr)} {  }
};

template <>
struct ImmAdapterT<org::imm::ImmCall> : public org::imm::ImmAdapterTBase<org::imm::ImmCall>, public org::imm::ImmAdapterCallAPI {
  USE_IMM_ADAPTER_BASE(org::imm::ImmCall)
  using api_type = org::imm::ImmAdapterCallAPI;
  BOOST_DESCRIBE_CLASS(ImmAdapterT, (ImmAdapterTBase, ImmAdapterCallAPI), (), (), ());
  ImmAdapterT(org::imm::ImmAdapter const& other) { LOGIC_ASSERTION_CHECK_FMT("Adapter type mismatch, cannot create adapter of type {} from generic adapter of type {}", "Call", other.getKind()) }
  org::imm::ImmCallValueRead getValue() const { return org::imm::ImmCallValueRead{&this->value()}; }
};

struct ImmListValueRead {
  BOOST_DESCRIBE_CLASS(ImmListValueRead, (), (), (), ());
  org::imm::ImmList* ptr;
  ImmListValueRead(org::imm::ImmList const* ptr) : ptr{const_cast<org::imm::ImmList*>(ptr)} {  }
};

template <>
struct ImmAdapterT<org::imm::ImmList> : public org::imm::ImmAdapterTBase<org::imm::ImmList>, public org::imm::ImmAdapterListAPI {
  USE_IMM_ADAPTER_BASE(org::imm::ImmList)
  using api_type = org::imm::ImmAdapterListAPI;
  BOOST_DESCRIBE_CLASS(ImmAdapterT, (ImmAdapterTBase, ImmAdapterListAPI), (), (), ());
  ImmAdapterT(org::imm::ImmAdapter const& other) { LOGIC_ASSERTION_CHECK_FMT("Adapter type mismatch, cannot create adapter of type {} from generic adapter of type {}", "List", other.getKind()) }
  org::imm::ImmListValueRead getValue() const { return org::imm::ImmListValueRead{&this->value()}; }
};

struct ImmListItemValueRead {
  BOOST_DESCRIBE_CLASS(ImmListItemValueRead, (), (), (), ());
  org::imm::ImmListItem* ptr;
  CheckboxState const& getCheckbox() const;
  hstd::ext::ImmBox<hstd::Opt<org::imm::ImmIdT<org::imm::ImmParagraph>>> const& getHeader() const;
  hstd::ext::ImmBox<hstd::Opt<hstd::Str>> const& getBullet() const;
  ImmListItemValueRead(org::imm::ImmListItem const* ptr) : ptr{const_cast<org::imm::ImmListItem*>(ptr)} {  }
};

template <>
struct ImmAdapterT<org::imm::ImmListItem> : public org::imm::ImmAdapterTBase<org::imm::ImmListItem>, public org::imm::ImmAdapterListItemAPI {
  USE_IMM_ADAPTER_BASE(org::imm::ImmListItem)
  using api_type = org::imm::ImmAdapterListItemAPI;
  BOOST_DESCRIBE_CLASS(ImmAdapterT, (ImmAdapterTBase, ImmAdapterListItemAPI), (), (), ());
  ImmAdapterT(org::imm::ImmAdapter const& other) { LOGIC_ASSERTION_CHECK_FMT("Adapter type mismatch, cannot create adapter of type {} from generic adapter of type {}", "ListItem", other.getKind()) }
  org::imm::ImmListItemValueRead getValue() const { return org::imm::ImmListItemValueRead{&this->value()}; }
};

struct ImmDocumentOptionsValueRead {
  BOOST_DESCRIBE_CLASS(ImmDocumentOptionsValueRead, (), (), (), ());
  org::imm::ImmDocumentOptions* ptr;
  InitialSubtreeVisibility const& getInitialvisibility() const;
  hstd::ext::ImmVec<org::sem::NamedProperty> const& getProperties() const;
  org::sem::DocumentExportConfig const& getExportconfig() const;
  hstd::ext::ImmBox<hstd::Opt<bool>> const& getFixedwidthsections() const;
  hstd::ext::ImmBox<hstd::Opt<bool>> const& getStartupindented() const;
  hstd::ext::ImmBox<hstd::Opt<hstd::Str>> const& getCategory() const;
  hstd::ext::ImmBox<hstd::Opt<hstd::Str>> const& getSetupfile() const;
  hstd::ext::ImmBox<hstd::Opt<int>> const& getMaxsubtreelevelexport() const;
  hstd::ext::ImmBox<hstd::Opt<org::sem::ColumnView>> const& getColumns() const;
  hstd::ext::ImmVec<org::sem::TodoKeyword> const& getTodokeywords() const;
  hstd::ext::ImmVec<org::sem::TodoKeyword> const& getDonekeywords() const;
  ImmDocumentOptionsValueRead(org::imm::ImmDocumentOptions const* ptr) : ptr{const_cast<org::imm::ImmDocumentOptions*>(ptr)} {  }
};

template <>
struct ImmAdapterT<org::imm::ImmDocumentOptions> : public org::imm::ImmAdapterTBase<org::imm::ImmDocumentOptions>, public org::imm::ImmAdapterDocumentOptionsAPI {
  USE_IMM_ADAPTER_BASE(org::imm::ImmDocumentOptions)
  using api_type = org::imm::ImmAdapterDocumentOptionsAPI;
  BOOST_DESCRIBE_CLASS(ImmAdapterT, (ImmAdapterTBase, ImmAdapterDocumentOptionsAPI), (), (), ());
  ImmAdapterT(org::imm::ImmAdapter const& other) { LOGIC_ASSERTION_CHECK_FMT("Adapter type mismatch, cannot create adapter of type {} from generic adapter of type {}", "DocumentOptions", other.getKind()) }
  org::imm::ImmDocumentOptionsValueRead getValue() const { return org::imm::ImmDocumentOptionsValueRead{&this->value()}; }
};

struct ImmDocumentFragmentValueRead {
  BOOST_DESCRIBE_CLASS(ImmDocumentFragmentValueRead, (), (), (), ());
  org::imm::ImmDocumentFragment* ptr;
  int const& getBaseline() const;
  int const& getBasecol() const;
  ImmDocumentFragmentValueRead(org::imm::ImmDocumentFragment const* ptr) : ptr{const_cast<org::imm::ImmDocumentFragment*>(ptr)} {  }
};

template <>
struct ImmAdapterT<org::imm::ImmDocumentFragment> : public org::imm::ImmAdapterTBase<org::imm::ImmDocumentFragment>, public org::imm::ImmAdapterDocumentFragmentAPI {
  USE_IMM_ADAPTER_BASE(org::imm::ImmDocumentFragment)
  using api_type = org::imm::ImmAdapterDocumentFragmentAPI;
  BOOST_DESCRIBE_CLASS(ImmAdapterT, (ImmAdapterTBase, ImmAdapterDocumentFragmentAPI), (), (), ());
  ImmAdapterT(org::imm::ImmAdapter const& other) { LOGIC_ASSERTION_CHECK_FMT("Adapter type mismatch, cannot create adapter of type {} from generic adapter of type {}", "DocumentFragment", other.getKind()) }
  org::imm::ImmDocumentFragmentValueRead getValue() const { return org::imm::ImmDocumentFragmentValueRead{&this->value()}; }
};

struct ImmCriticMarkupValueRead {
  BOOST_DESCRIBE_CLASS(ImmCriticMarkupValueRead, (), (), (), ());
  org::imm::ImmCriticMarkup* ptr;
  org::imm::ImmCriticMarkup::Kind const& getKind() const;
  ImmCriticMarkupValueRead(org::imm::ImmCriticMarkup const* ptr) : ptr{const_cast<org::imm::ImmCriticMarkup*>(ptr)} {  }
};

template <>
struct ImmAdapterT<org::imm::ImmCriticMarkup> : public org::imm::ImmAdapterTBase<org::imm::ImmCriticMarkup>, public org::imm::ImmAdapterCriticMarkupAPI {
  USE_IMM_ADAPTER_BASE(org::imm::ImmCriticMarkup)
  using api_type = org::imm::ImmAdapterCriticMarkupAPI;
  BOOST_DESCRIBE_CLASS(ImmAdapterT, (ImmAdapterTBase, ImmAdapterCriticMarkupAPI), (), (), ());
  ImmAdapterT(org::imm::ImmAdapter const& other) { LOGIC_ASSERTION_CHECK_FMT("Adapter type mismatch, cannot create adapter of type {} from generic adapter of type {}", "CriticMarkup", other.getKind()) }
  org::imm::ImmCriticMarkupValueRead getValue() const { return org::imm::ImmCriticMarkupValueRead{&this->value()}; }
};

struct ImmDocumentValueRead {
  BOOST_DESCRIBE_CLASS(ImmDocumentValueRead, (), (), (), ());
  org::imm::ImmDocument* ptr;
  hstd::ext::ImmBox<hstd::Opt<org::imm::ImmIdT<org::imm::ImmParagraph>>> const& getTitle() const;
  hstd::ext::ImmBox<hstd::Opt<org::imm::ImmIdT<org::imm::ImmParagraph>>> const& getAuthor() const;
  hstd::ext::ImmBox<hstd::Opt<org::imm::ImmIdT<org::imm::ImmParagraph>>> const& getCreator() const;
  hstd::ext::ImmVec<org::imm::ImmIdT<org::imm::ImmHashTag>> const& getFiletags() const;
  hstd::ext::ImmBox<hstd::Opt<org::imm::ImmIdT<org::imm::ImmRawText>>> const& getEmail() const;
  hstd::ext::ImmVec<hstd::Str> const& getLanguage() const;
  org::imm::ImmIdT<org::imm::ImmDocumentOptions> const& getOptions() const;
  hstd::ext::ImmBox<hstd::Opt<hstd::Str>> const& getExportfilename() const;
  ImmDocumentValueRead(org::imm::ImmDocument const* ptr) : ptr{const_cast<org::imm::ImmDocument*>(ptr)} {  }
};

template <>
struct ImmAdapterT<org::imm::ImmDocument> : public org::imm::ImmAdapterTBase<org::imm::ImmDocument>, public org::imm::ImmAdapterDocumentAPI {
  USE_IMM_ADAPTER_BASE(org::imm::ImmDocument)
  using api_type = org::imm::ImmAdapterDocumentAPI;
  BOOST_DESCRIBE_CLASS(ImmAdapterT, (ImmAdapterTBase, ImmAdapterDocumentAPI), (), (), ());
  ImmAdapterT(org::imm::ImmAdapter const& other) { LOGIC_ASSERTION_CHECK_FMT("Adapter type mismatch, cannot create adapter of type {} from generic adapter of type {}", "Document", other.getKind()) }
  org::imm::ImmDocumentValueRead getValue() const { return org::imm::ImmDocumentValueRead{&this->value()}; }
};

struct ImmFileTargetValueRead {
  BOOST_DESCRIBE_CLASS(ImmFileTargetValueRead, (), (), (), ());
  org::imm::ImmFileTarget* ptr;
  hstd::ext::ImmBox<hstd::Str> const& getPath() const;
  hstd::ext::ImmBox<hstd::Opt<int>> const& getLine() const;
  hstd::ext::ImmBox<hstd::Opt<hstd::Str>> const& getSearchtarget() const;
  bool const& getRestricttoheadlines() const;
  hstd::ext::ImmBox<hstd::Opt<hstd::Str>> const& getTargetid() const;
  hstd::ext::ImmBox<hstd::Opt<hstd::Str>> const& getRegexp() const;
  ImmFileTargetValueRead(org::imm::ImmFileTarget const* ptr) : ptr{const_cast<org::imm::ImmFileTarget*>(ptr)} {  }
};

template <>
struct ImmAdapterT<org::imm::ImmFileTarget> : public org::imm::ImmAdapterTBase<org::imm::ImmFileTarget>, public org::imm::ImmAdapterFileTargetAPI {
  USE_IMM_ADAPTER_BASE(org::imm::ImmFileTarget)
  using api_type = org::imm::ImmAdapterFileTargetAPI;
  BOOST_DESCRIBE_CLASS(ImmAdapterT, (ImmAdapterTBase, ImmAdapterFileTargetAPI), (), (), ());
  ImmAdapterT(org::imm::ImmAdapter const& other) { LOGIC_ASSERTION_CHECK_FMT("Adapter type mismatch, cannot create adapter of type {} from generic adapter of type {}", "FileTarget", other.getKind()) }
  org::imm::ImmFileTargetValueRead getValue() const { return org::imm::ImmFileTargetValueRead{&this->value()}; }
};

struct ImmTextSeparatorValueRead {
  BOOST_DESCRIBE_CLASS(ImmTextSeparatorValueRead, (), (), (), ());
  org::imm::ImmTextSeparator* ptr;
  ImmTextSeparatorValueRead(org::imm::ImmTextSeparator const* ptr) : ptr{const_cast<org::imm::ImmTextSeparator*>(ptr)} {  }
};

template <>
struct ImmAdapterT<org::imm::ImmTextSeparator> : public org::imm::ImmAdapterTBase<org::imm::ImmTextSeparator>, public org::imm::ImmAdapterTextSeparatorAPI {
  USE_IMM_ADAPTER_BASE(org::imm::ImmTextSeparator)
  using api_type = org::imm::ImmAdapterTextSeparatorAPI;
  BOOST_DESCRIBE_CLASS(ImmAdapterT, (ImmAdapterTBase, ImmAdapterTextSeparatorAPI), (), (), ());
  ImmAdapterT(org::imm::ImmAdapter const& other) { LOGIC_ASSERTION_CHECK_FMT("Adapter type mismatch, cannot create adapter of type {} from generic adapter of type {}", "TextSeparator", other.getKind()) }
  org::imm::ImmTextSeparatorValueRead getValue() const { return org::imm::ImmTextSeparatorValueRead{&this->value()}; }
};

struct ImmDocumentGroupValueRead {
  BOOST_DESCRIBE_CLASS(ImmDocumentGroupValueRead, (), (), (), ());
  org::imm::ImmDocumentGroup* ptr;
  ImmDocumentGroupValueRead(org::imm::ImmDocumentGroup const* ptr) : ptr{const_cast<org::imm::ImmDocumentGroup*>(ptr)} {  }
};

template <>
struct ImmAdapterT<org::imm::ImmDocumentGroup> : public org::imm::ImmAdapterTBase<org::imm::ImmDocumentGroup>, public org::imm::ImmAdapterDocumentGroupAPI {
  USE_IMM_ADAPTER_BASE(org::imm::ImmDocumentGroup)
  using api_type = org::imm::ImmAdapterDocumentGroupAPI;
  BOOST_DESCRIBE_CLASS(ImmAdapterT, (ImmAdapterTBase, ImmAdapterDocumentGroupAPI), (), (), ());
  ImmAdapterT(org::imm::ImmAdapter const& other) { LOGIC_ASSERTION_CHECK_FMT("Adapter type mismatch, cannot create adapter of type {} from generic adapter of type {}", "DocumentGroup", other.getKind()) }
  org::imm::ImmDocumentGroupValueRead getValue() const { return org::imm::ImmDocumentGroupValueRead{&this->value()}; }
};

struct ImmFileValueRead {
  BOOST_DESCRIBE_CLASS(ImmFileValueRead, (), (), (), ());
  org::imm::ImmFile* ptr;
  hstd::ext::ImmBox<hstd::Str> const& getRelpath() const;
  hstd::ext::ImmBox<hstd::Str> const& getAbspath() const;
  org::imm::ImmFile::Data const& getData() const;
  ImmFileValueRead(org::imm::ImmFile const* ptr) : ptr{const_cast<org::imm::ImmFile*>(ptr)} {  }
};

template <>
struct ImmAdapterT<org::imm::ImmFile> : public org::imm::ImmAdapterTBase<org::imm::ImmFile>, public org::imm::ImmAdapterFileAPI {
  USE_IMM_ADAPTER_BASE(org::imm::ImmFile)
  using api_type = org::imm::ImmAdapterFileAPI;
  BOOST_DESCRIBE_CLASS(ImmAdapterT, (ImmAdapterTBase, ImmAdapterFileAPI), (), (), ());
  ImmAdapterT(org::imm::ImmAdapter const& other) { LOGIC_ASSERTION_CHECK_FMT("Adapter type mismatch, cannot create adapter of type {} from generic adapter of type {}", "File", other.getKind()) }
  org::imm::ImmFileValueRead getValue() const { return org::imm::ImmFileValueRead{&this->value()}; }
};

struct ImmDirectoryValueRead {
  BOOST_DESCRIBE_CLASS(ImmDirectoryValueRead, (), (), (), ());
  org::imm::ImmDirectory* ptr;
  hstd::ext::ImmBox<hstd::Str> const& getRelpath() const;
  hstd::ext::ImmBox<hstd::Str> const& getAbspath() const;
  ImmDirectoryValueRead(org::imm::ImmDirectory const* ptr) : ptr{const_cast<org::imm::ImmDirectory*>(ptr)} {  }
};

template <>
struct ImmAdapterT<org::imm::ImmDirectory> : public org::imm::ImmAdapterTBase<org::imm::ImmDirectory>, public org::imm::ImmAdapterDirectoryAPI {
  USE_IMM_ADAPTER_BASE(org::imm::ImmDirectory)
  using api_type = org::imm::ImmAdapterDirectoryAPI;
  BOOST_DESCRIBE_CLASS(ImmAdapterT, (ImmAdapterTBase, ImmAdapterDirectoryAPI), (), (), ());
  ImmAdapterT(org::imm::ImmAdapter const& other) { LOGIC_ASSERTION_CHECK_FMT("Adapter type mismatch, cannot create adapter of type {} from generic adapter of type {}", "Directory", other.getKind()) }
  org::imm::ImmDirectoryValueRead getValue() const { return org::imm::ImmDirectoryValueRead{&this->value()}; }
};

struct ImmSymlinkValueRead {
  BOOST_DESCRIBE_CLASS(ImmSymlinkValueRead, (), (), (), ());
  org::imm::ImmSymlink* ptr;
  bool const& getIsdirectory() const;
  hstd::ext::ImmBox<hstd::Str> const& getAbspath() const;
  ImmSymlinkValueRead(org::imm::ImmSymlink const* ptr) : ptr{const_cast<org::imm::ImmSymlink*>(ptr)} {  }
};

template <>
struct ImmAdapterT<org::imm::ImmSymlink> : public org::imm::ImmAdapterTBase<org::imm::ImmSymlink>, public org::imm::ImmAdapterSymlinkAPI {
  USE_IMM_ADAPTER_BASE(org::imm::ImmSymlink)
  using api_type = org::imm::ImmAdapterSymlinkAPI;
  BOOST_DESCRIBE_CLASS(ImmAdapterT, (ImmAdapterTBase, ImmAdapterSymlinkAPI), (), (), ());
  ImmAdapterT(org::imm::ImmAdapter const& other) { LOGIC_ASSERTION_CHECK_FMT("Adapter type mismatch, cannot create adapter of type {} from generic adapter of type {}", "Symlink", other.getKind()) }
  org::imm::ImmSymlinkValueRead getValue() const { return org::imm::ImmSymlinkValueRead{&this->value()}; }
};

struct ImmCmdIncludeValueRead {
  BOOST_DESCRIBE_CLASS(ImmCmdIncludeValueRead, (), (), (), ());
  org::imm::ImmCmdInclude* ptr;
  hstd::ext::ImmBox<hstd::Str> const& getPath() const;
  hstd::ext::ImmBox<hstd::Opt<int>> const& getFirstline() const;
  hstd::ext::ImmBox<hstd::Opt<int>> const& getLastline() const;
  org::imm::ImmCmdInclude::Data const& getData() const;
  ImmCmdIncludeValueRead(org::imm::ImmCmdInclude const* ptr) : ptr{const_cast<org::imm::ImmCmdInclude*>(ptr)} {  }
};

template <>
struct ImmAdapterT<org::imm::ImmCmdInclude> : public org::imm::ImmAdapterTBase<org::imm::ImmCmdInclude>, public org::imm::ImmAdapterCmdIncludeAPI {
  USE_IMM_ADAPTER_BASE(org::imm::ImmCmdInclude)
  using api_type = org::imm::ImmAdapterCmdIncludeAPI;
  BOOST_DESCRIBE_CLASS(ImmAdapterT, (ImmAdapterTBase, ImmAdapterCmdIncludeAPI), (), (), ());
  ImmAdapterT(org::imm::ImmAdapter const& other) { LOGIC_ASSERTION_CHECK_FMT("Adapter type mismatch, cannot create adapter of type {} from generic adapter of type {}", "CmdInclude", other.getKind()) }
  org::imm::ImmCmdIncludeValueRead getValue() const { return org::imm::ImmCmdIncludeValueRead{&this->value()}; }
};

}
/* clang-format on */