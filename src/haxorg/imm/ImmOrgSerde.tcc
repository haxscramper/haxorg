/* clang-format off */
template <>
struct ImmSemSerde<org::sem::NoNode /* d_org */, org::imm::ImmNoNode /* d_org */> {
  static org::imm::ImmNoNode /* d_org */ to_immer(org::sem::NoNode const& /* d_org */ value, ImmAstEditContext& ctx) {
    org::imm::ImmNoNode /* d_org */ result = hstd::SerdeDefaultProvider<org::imm::ImmNoNode /* d_org */>::get();
    assign_immer_field(result.loc, value.loc, ctx);
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
  static org::sem::NoNode /* d_org */ from_immer(org::imm::ImmNoNode const& /* d_org */ value, ImmAstContext const& ctx) {
    org::sem::NoNode /* d_org */ result = hstd::SerdeDefaultProvider<org::sem::NoNode /* d_org */>::get();
    assign_sem_field(result.loc, value.loc, ctx);
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<org::sem::ErrorItem /* d_org */, org::imm::ImmErrorItem /* d_org */> {
  static org::imm::ImmErrorItem /* d_org */ to_immer(org::sem::ErrorItem const& /* d_org */ value, ImmAstEditContext& ctx) {
    org::imm::ImmErrorItem /* d_org */ result = hstd::SerdeDefaultProvider<org::imm::ImmErrorItem /* d_org */>::get();
    assign_immer_field(result.diag, value.diag, ctx);
    assign_immer_field(result.loc, value.loc, ctx);
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
  static org::sem::ErrorItem /* d_org */ from_immer(org::imm::ImmErrorItem const& /* d_org */ value, ImmAstContext const& ctx) {
    org::sem::ErrorItem /* d_org */ result = hstd::SerdeDefaultProvider<org::sem::ErrorItem /* d_org */>::get();
    assign_sem_field(result.diag, value.diag, ctx);
    assign_sem_field(result.loc, value.loc, ctx);
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<org::sem::ErrorGroup /* d_org */, org::imm::ImmErrorGroup /* d_org */> {
  static org::imm::ImmErrorGroup /* d_org */ to_immer(org::sem::ErrorGroup const& /* d_org */ value, ImmAstEditContext& ctx) {
    org::imm::ImmErrorGroup /* d_org */ result = hstd::SerdeDefaultProvider<org::imm::ImmErrorGroup /* d_org */>::get();
    assign_immer_field(result.diagnostics, value.diagnostics, ctx);
    assign_immer_field(result.loc, value.loc, ctx);
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
  static org::sem::ErrorGroup /* d_org */ from_immer(org::imm::ImmErrorGroup const& /* d_org */ value, ImmAstContext const& ctx) {
    org::sem::ErrorGroup /* d_org */ result = hstd::SerdeDefaultProvider<org::sem::ErrorGroup /* d_org */>::get();
    assign_sem_field(result.diagnostics, value.diagnostics, ctx);
    assign_sem_field(result.loc, value.loc, ctx);
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<org::sem::StmtList /* d_org */, org::imm::ImmStmtList /* d_org */> {
  static org::imm::ImmStmtList /* d_org */ to_immer(org::sem::StmtList const& /* d_org */ value, ImmAstEditContext& ctx) {
    org::imm::ImmStmtList /* d_org */ result = hstd::SerdeDefaultProvider<org::imm::ImmStmtList /* d_org */>::get();
    assign_immer_field(result.loc, value.loc, ctx);
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
  static org::sem::StmtList /* d_org */ from_immer(org::imm::ImmStmtList const& /* d_org */ value, ImmAstContext const& ctx) {
    org::sem::StmtList /* d_org */ result = hstd::SerdeDefaultProvider<org::sem::StmtList /* d_org */>::get();
    assign_sem_field(result.loc, value.loc, ctx);
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<org::sem::Empty /* d_org */, org::imm::ImmEmpty /* d_org */> {
  static org::imm::ImmEmpty /* d_org */ to_immer(org::sem::Empty const& /* d_org */ value, ImmAstEditContext& ctx) {
    org::imm::ImmEmpty /* d_org */ result = hstd::SerdeDefaultProvider<org::imm::ImmEmpty /* d_org */>::get();
    assign_immer_field(result.loc, value.loc, ctx);
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
  static org::sem::Empty /* d_org */ from_immer(org::imm::ImmEmpty const& /* d_org */ value, ImmAstContext const& ctx) {
    org::sem::Empty /* d_org */ result = hstd::SerdeDefaultProvider<org::sem::Empty /* d_org */>::get();
    assign_sem_field(result.loc, value.loc, ctx);
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<org::sem::CmdCaption /* d_org */, org::imm::ImmCmdCaption /* d_org */> {
  static org::imm::ImmCmdCaption /* d_org */ to_immer(org::sem::CmdCaption const& /* d_org */ value, ImmAstEditContext& ctx) {
    org::imm::ImmCmdCaption /* d_org */ result = hstd::SerdeDefaultProvider<org::imm::ImmCmdCaption /* d_org */>::get();
    assign_immer_field(result.text, value.text, ctx);
    assign_immer_field(result.attrs, value.attrs, ctx);
    assign_immer_field(result.attached, value.attached, ctx);
    assign_immer_field(result.loc, value.loc, ctx);
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
  static org::sem::CmdCaption /* d_org */ from_immer(org::imm::ImmCmdCaption const& /* d_org */ value, ImmAstContext const& ctx) {
    org::sem::CmdCaption /* d_org */ result = hstd::SerdeDefaultProvider<org::sem::CmdCaption /* d_org */>::get();
    assign_sem_field(result.text, value.text, ctx);
    assign_sem_field(result.attrs, value.attrs, ctx);
    assign_sem_field(result.attached, value.attached, ctx);
    assign_sem_field(result.loc, value.loc, ctx);
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<org::sem::CmdCreator /* d_org */, org::imm::ImmCmdCreator /* d_org */> {
  static org::imm::ImmCmdCreator /* d_org */ to_immer(org::sem::CmdCreator const& /* d_org */ value, ImmAstEditContext& ctx) {
    org::imm::ImmCmdCreator /* d_org */ result = hstd::SerdeDefaultProvider<org::imm::ImmCmdCreator /* d_org */>::get();
    assign_immer_field(result.text, value.text, ctx);
    assign_immer_field(result.attrs, value.attrs, ctx);
    assign_immer_field(result.attached, value.attached, ctx);
    assign_immer_field(result.loc, value.loc, ctx);
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
  static org::sem::CmdCreator /* d_org */ from_immer(org::imm::ImmCmdCreator const& /* d_org */ value, ImmAstContext const& ctx) {
    org::sem::CmdCreator /* d_org */ result = hstd::SerdeDefaultProvider<org::sem::CmdCreator /* d_org */>::get();
    assign_sem_field(result.text, value.text, ctx);
    assign_sem_field(result.attrs, value.attrs, ctx);
    assign_sem_field(result.attached, value.attached, ctx);
    assign_sem_field(result.loc, value.loc, ctx);
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<org::sem::CmdAuthor /* d_org */, org::imm::ImmCmdAuthor /* d_org */> {
  static org::imm::ImmCmdAuthor /* d_org */ to_immer(org::sem::CmdAuthor const& /* d_org */ value, ImmAstEditContext& ctx) {
    org::imm::ImmCmdAuthor /* d_org */ result = hstd::SerdeDefaultProvider<org::imm::ImmCmdAuthor /* d_org */>::get();
    assign_immer_field(result.text, value.text, ctx);
    assign_immer_field(result.attrs, value.attrs, ctx);
    assign_immer_field(result.attached, value.attached, ctx);
    assign_immer_field(result.loc, value.loc, ctx);
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
  static org::sem::CmdAuthor /* d_org */ from_immer(org::imm::ImmCmdAuthor const& /* d_org */ value, ImmAstContext const& ctx) {
    org::sem::CmdAuthor /* d_org */ result = hstd::SerdeDefaultProvider<org::sem::CmdAuthor /* d_org */>::get();
    assign_sem_field(result.text, value.text, ctx);
    assign_sem_field(result.attrs, value.attrs, ctx);
    assign_sem_field(result.attached, value.attached, ctx);
    assign_sem_field(result.loc, value.loc, ctx);
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<org::sem::CmdEmail /* d_org */, org::imm::ImmCmdEmail /* d_org */> {
  static org::imm::ImmCmdEmail /* d_org */ to_immer(org::sem::CmdEmail const& /* d_org */ value, ImmAstEditContext& ctx) {
    org::imm::ImmCmdEmail /* d_org */ result = hstd::SerdeDefaultProvider<org::imm::ImmCmdEmail /* d_org */>::get();
    assign_immer_field(result.text, value.text, ctx);
    assign_immer_field(result.attrs, value.attrs, ctx);
    assign_immer_field(result.attached, value.attached, ctx);
    assign_immer_field(result.loc, value.loc, ctx);
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
  static org::sem::CmdEmail /* d_org */ from_immer(org::imm::ImmCmdEmail const& /* d_org */ value, ImmAstContext const& ctx) {
    org::sem::CmdEmail /* d_org */ result = hstd::SerdeDefaultProvider<org::sem::CmdEmail /* d_org */>::get();
    assign_sem_field(result.text, value.text, ctx);
    assign_sem_field(result.attrs, value.attrs, ctx);
    assign_sem_field(result.attached, value.attached, ctx);
    assign_sem_field(result.loc, value.loc, ctx);
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<org::sem::CmdLanguage /* d_org */, org::imm::ImmCmdLanguage /* d_org */> {
  static org::imm::ImmCmdLanguage /* d_org */ to_immer(org::sem::CmdLanguage const& /* d_org */ value, ImmAstEditContext& ctx) {
    org::imm::ImmCmdLanguage /* d_org */ result = hstd::SerdeDefaultProvider<org::imm::ImmCmdLanguage /* d_org */>::get();
    assign_immer_field(result.text, value.text, ctx);
    assign_immer_field(result.attrs, value.attrs, ctx);
    assign_immer_field(result.attached, value.attached, ctx);
    assign_immer_field(result.loc, value.loc, ctx);
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
  static org::sem::CmdLanguage /* d_org */ from_immer(org::imm::ImmCmdLanguage const& /* d_org */ value, ImmAstContext const& ctx) {
    org::sem::CmdLanguage /* d_org */ result = hstd::SerdeDefaultProvider<org::sem::CmdLanguage /* d_org */>::get();
    assign_sem_field(result.text, value.text, ctx);
    assign_sem_field(result.attrs, value.attrs, ctx);
    assign_sem_field(result.attached, value.attached, ctx);
    assign_sem_field(result.loc, value.loc, ctx);
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<org::sem::CmdColumns /* d_org */, org::imm::ImmCmdColumns /* d_org */> {
  static org::imm::ImmCmdColumns /* d_org */ to_immer(org::sem::CmdColumns const& /* d_org */ value, ImmAstEditContext& ctx) {
    org::imm::ImmCmdColumns /* d_org */ result = hstd::SerdeDefaultProvider<org::imm::ImmCmdColumns /* d_org */>::get();
    assign_immer_field(result.view, value.view, ctx);
    assign_immer_field(result.attrs, value.attrs, ctx);
    assign_immer_field(result.attached, value.attached, ctx);
    assign_immer_field(result.loc, value.loc, ctx);
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
  static org::sem::CmdColumns /* d_org */ from_immer(org::imm::ImmCmdColumns const& /* d_org */ value, ImmAstContext const& ctx) {
    org::sem::CmdColumns /* d_org */ result = hstd::SerdeDefaultProvider<org::sem::CmdColumns /* d_org */>::get();
    assign_sem_field(result.view, value.view, ctx);
    assign_sem_field(result.attrs, value.attrs, ctx);
    assign_sem_field(result.attached, value.attached, ctx);
    assign_sem_field(result.loc, value.loc, ctx);
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<org::sem::CmdName /* d_org */, org::imm::ImmCmdName /* d_org */> {
  static org::imm::ImmCmdName /* d_org */ to_immer(org::sem::CmdName const& /* d_org */ value, ImmAstEditContext& ctx) {
    org::imm::ImmCmdName /* d_org */ result = hstd::SerdeDefaultProvider<org::imm::ImmCmdName /* d_org */>::get();
    assign_immer_field(result.name, value.name, ctx);
    assign_immer_field(result.attrs, value.attrs, ctx);
    assign_immer_field(result.attached, value.attached, ctx);
    assign_immer_field(result.loc, value.loc, ctx);
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
  static org::sem::CmdName /* d_org */ from_immer(org::imm::ImmCmdName const& /* d_org */ value, ImmAstContext const& ctx) {
    org::sem::CmdName /* d_org */ result = hstd::SerdeDefaultProvider<org::sem::CmdName /* d_org */>::get();
    assign_sem_field(result.name, value.name, ctx);
    assign_sem_field(result.attrs, value.attrs, ctx);
    assign_sem_field(result.attached, value.attached, ctx);
    assign_sem_field(result.loc, value.loc, ctx);
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<org::sem::CmdCustomArgs /* d_org */, org::imm::ImmCmdCustomArgs /* d_org */> {
  static org::imm::ImmCmdCustomArgs /* d_org */ to_immer(org::sem::CmdCustomArgs const& /* d_org */ value, ImmAstEditContext& ctx) {
    org::imm::ImmCmdCustomArgs /* d_org */ result = hstd::SerdeDefaultProvider<org::imm::ImmCmdCustomArgs /* d_org */>::get();
    assign_immer_field(result.name, value.name, ctx);
    assign_immer_field(result.isAttached, value.isAttached, ctx);
    assign_immer_field(result.attrs, value.attrs, ctx);
    assign_immer_field(result.attached, value.attached, ctx);
    assign_immer_field(result.loc, value.loc, ctx);
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
  static org::sem::CmdCustomArgs /* d_org */ from_immer(org::imm::ImmCmdCustomArgs const& /* d_org */ value, ImmAstContext const& ctx) {
    org::sem::CmdCustomArgs /* d_org */ result = hstd::SerdeDefaultProvider<org::sem::CmdCustomArgs /* d_org */>::get();
    assign_sem_field(result.name, value.name, ctx);
    assign_sem_field(result.isAttached, value.isAttached, ctx);
    assign_sem_field(result.attrs, value.attrs, ctx);
    assign_sem_field(result.attached, value.attached, ctx);
    assign_sem_field(result.loc, value.loc, ctx);
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<org::sem::CmdCustomRaw /* d_org */, org::imm::ImmCmdCustomRaw /* d_org */> {
  static org::imm::ImmCmdCustomRaw /* d_org */ to_immer(org::sem::CmdCustomRaw const& /* d_org */ value, ImmAstEditContext& ctx) {
    org::imm::ImmCmdCustomRaw /* d_org */ result = hstd::SerdeDefaultProvider<org::imm::ImmCmdCustomRaw /* d_org */>::get();
    assign_immer_field(result.name, value.name, ctx);
    assign_immer_field(result.isAttached, value.isAttached, ctx);
    assign_immer_field(result.text, value.text, ctx);
    assign_immer_field(result.attached, value.attached, ctx);
    assign_immer_field(result.loc, value.loc, ctx);
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
  static org::sem::CmdCustomRaw /* d_org */ from_immer(org::imm::ImmCmdCustomRaw const& /* d_org */ value, ImmAstContext const& ctx) {
    org::sem::CmdCustomRaw /* d_org */ result = hstd::SerdeDefaultProvider<org::sem::CmdCustomRaw /* d_org */>::get();
    assign_sem_field(result.name, value.name, ctx);
    assign_sem_field(result.isAttached, value.isAttached, ctx);
    assign_sem_field(result.text, value.text, ctx);
    assign_sem_field(result.attached, value.attached, ctx);
    assign_sem_field(result.loc, value.loc, ctx);
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<org::sem::CmdCustomText /* d_org */, org::imm::ImmCmdCustomText /* d_org */> {
  static org::imm::ImmCmdCustomText /* d_org */ to_immer(org::sem::CmdCustomText const& /* d_org */ value, ImmAstEditContext& ctx) {
    org::imm::ImmCmdCustomText /* d_org */ result = hstd::SerdeDefaultProvider<org::imm::ImmCmdCustomText /* d_org */>::get();
    assign_immer_field(result.name, value.name, ctx);
    assign_immer_field(result.isAttached, value.isAttached, ctx);
    assign_immer_field(result.text, value.text, ctx);
    assign_immer_field(result.attached, value.attached, ctx);
    assign_immer_field(result.loc, value.loc, ctx);
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
  static org::sem::CmdCustomText /* d_org */ from_immer(org::imm::ImmCmdCustomText const& /* d_org */ value, ImmAstContext const& ctx) {
    org::sem::CmdCustomText /* d_org */ result = hstd::SerdeDefaultProvider<org::sem::CmdCustomText /* d_org */>::get();
    assign_sem_field(result.name, value.name, ctx);
    assign_sem_field(result.isAttached, value.isAttached, ctx);
    assign_sem_field(result.text, value.text, ctx);
    assign_sem_field(result.attached, value.attached, ctx);
    assign_sem_field(result.loc, value.loc, ctx);
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<org::sem::CmdCall /* d_org */, org::imm::ImmCmdCall /* d_org */> {
  static org::imm::ImmCmdCall /* d_org */ to_immer(org::sem::CmdCall const& /* d_org */ value, ImmAstEditContext& ctx) {
    org::imm::ImmCmdCall /* d_org */ result = hstd::SerdeDefaultProvider<org::imm::ImmCmdCall /* d_org */>::get();
    assign_immer_field(result.name, value.name, ctx);
    assign_immer_field(result.fileName, value.fileName, ctx);
    assign_immer_field(result.insideHeaderAttrs, value.insideHeaderAttrs, ctx);
    assign_immer_field(result.callAttrs, value.callAttrs, ctx);
    assign_immer_field(result.endHeaderAttrs, value.endHeaderAttrs, ctx);
    assign_immer_field(result.result, value.result, ctx);
    assign_immer_field(result.attrs, value.attrs, ctx);
    assign_immer_field(result.attached, value.attached, ctx);
    assign_immer_field(result.loc, value.loc, ctx);
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
  static org::sem::CmdCall /* d_org */ from_immer(org::imm::ImmCmdCall const& /* d_org */ value, ImmAstContext const& ctx) {
    org::sem::CmdCall /* d_org */ result = hstd::SerdeDefaultProvider<org::sem::CmdCall /* d_org */>::get();
    assign_sem_field(result.name, value.name, ctx);
    assign_sem_field(result.fileName, value.fileName, ctx);
    assign_sem_field(result.insideHeaderAttrs, value.insideHeaderAttrs, ctx);
    assign_sem_field(result.callAttrs, value.callAttrs, ctx);
    assign_sem_field(result.endHeaderAttrs, value.endHeaderAttrs, ctx);
    assign_sem_field(result.result, value.result, ctx);
    assign_sem_field(result.attrs, value.attrs, ctx);
    assign_sem_field(result.attached, value.attached, ctx);
    assign_sem_field(result.loc, value.loc, ctx);
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<org::sem::CmdTblfm /* d_org */, org::imm::ImmCmdTblfm /* d_org */> {
  static org::imm::ImmCmdTblfm /* d_org */ to_immer(org::sem::CmdTblfm const& /* d_org */ value, ImmAstEditContext& ctx) {
    org::imm::ImmCmdTblfm /* d_org */ result = hstd::SerdeDefaultProvider<org::imm::ImmCmdTblfm /* d_org */>::get();
    assign_immer_field(result.expr, value.expr, ctx);
    assign_immer_field(result.attrs, value.attrs, ctx);
    assign_immer_field(result.attached, value.attached, ctx);
    assign_immer_field(result.loc, value.loc, ctx);
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
  static org::sem::CmdTblfm /* d_org */ from_immer(org::imm::ImmCmdTblfm const& /* d_org */ value, ImmAstContext const& ctx) {
    org::sem::CmdTblfm /* d_org */ result = hstd::SerdeDefaultProvider<org::sem::CmdTblfm /* d_org */>::get();
    assign_sem_field(result.expr, value.expr, ctx);
    assign_sem_field(result.attrs, value.attrs, ctx);
    assign_sem_field(result.attached, value.attached, ctx);
    assign_sem_field(result.loc, value.loc, ctx);
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<org::sem::HashTag /* d_org */, org::imm::ImmHashTag /* d_org */> {
  static org::imm::ImmHashTag /* d_org */ to_immer(org::sem::HashTag const& /* d_org */ value, ImmAstEditContext& ctx) {
    org::imm::ImmHashTag /* d_org */ result = hstd::SerdeDefaultProvider<org::imm::ImmHashTag /* d_org */>::get();
    assign_immer_field(result.text, value.text, ctx);
    assign_immer_field(result.loc, value.loc, ctx);
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
  static org::sem::HashTag /* d_org */ from_immer(org::imm::ImmHashTag const& /* d_org */ value, ImmAstContext const& ctx) {
    org::sem::HashTag /* d_org */ result = hstd::SerdeDefaultProvider<org::sem::HashTag /* d_org */>::get();
    assign_sem_field(result.text, value.text, ctx);
    assign_sem_field(result.loc, value.loc, ctx);
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<org::sem::InlineFootnote /* d_org */, org::imm::ImmInlineFootnote /* d_org */> {
  static org::imm::ImmInlineFootnote /* d_org */ to_immer(org::sem::InlineFootnote const& /* d_org */ value, ImmAstEditContext& ctx) {
    org::imm::ImmInlineFootnote /* d_org */ result = hstd::SerdeDefaultProvider<org::imm::ImmInlineFootnote /* d_org */>::get();
    assign_immer_field(result.tag, value.tag, ctx);
    assign_immer_field(result.definition, value.definition, ctx);
    assign_immer_field(result.loc, value.loc, ctx);
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
  static org::sem::InlineFootnote /* d_org */ from_immer(org::imm::ImmInlineFootnote const& /* d_org */ value, ImmAstContext const& ctx) {
    org::sem::InlineFootnote /* d_org */ result = hstd::SerdeDefaultProvider<org::sem::InlineFootnote /* d_org */>::get();
    assign_sem_field(result.tag, value.tag, ctx);
    assign_sem_field(result.definition, value.definition, ctx);
    assign_sem_field(result.loc, value.loc, ctx);
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<org::sem::InlineExport /* d_org */, org::imm::ImmInlineExport /* d_org */> {
  static org::imm::ImmInlineExport /* d_org */ to_immer(org::sem::InlineExport const& /* d_org */ value, ImmAstEditContext& ctx) {
    org::imm::ImmInlineExport /* d_org */ result = hstd::SerdeDefaultProvider<org::imm::ImmInlineExport /* d_org */>::get();
    assign_immer_field(result.exporter, value.exporter, ctx);
    assign_immer_field(result.content, value.content, ctx);
    assign_immer_field(result.loc, value.loc, ctx);
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
  static org::sem::InlineExport /* d_org */ from_immer(org::imm::ImmInlineExport const& /* d_org */ value, ImmAstContext const& ctx) {
    org::sem::InlineExport /* d_org */ result = hstd::SerdeDefaultProvider<org::sem::InlineExport /* d_org */>::get();
    assign_sem_field(result.exporter, value.exporter, ctx);
    assign_sem_field(result.content, value.content, ctx);
    assign_sem_field(result.loc, value.loc, ctx);
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<org::sem::Time /* d_org */, org::imm::ImmTime /* d_org */> {
  static org::imm::ImmTime /* d_org */ to_immer(org::sem::Time const& /* d_org */ value, ImmAstEditContext& ctx) {
    org::imm::ImmTime /* d_org */ result = hstd::SerdeDefaultProvider<org::imm::ImmTime /* d_org */>::get();
    assign_immer_field(result.isActive, value.isActive, ctx);
    assign_immer_field(result.time, value.time, ctx);
    assign_immer_field(result.loc, value.loc, ctx);
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
  static org::sem::Time /* d_org */ from_immer(org::imm::ImmTime const& /* d_org */ value, ImmAstContext const& ctx) {
    org::sem::Time /* d_org */ result = hstd::SerdeDefaultProvider<org::sem::Time /* d_org */>::get();
    assign_sem_field(result.isActive, value.isActive, ctx);
    assign_sem_field(result.time, value.time, ctx);
    assign_sem_field(result.loc, value.loc, ctx);
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<org::sem::Time::Repeat, org::imm::ImmTime::Repeat> {
  static org::imm::ImmTime::Repeat to_immer(org::sem::Time::Repeat const& value, ImmAstEditContext& ctx) {
    org::imm::ImmTime::Repeat result = hstd::SerdeDefaultProvider<org::imm::ImmTime::Repeat>::get();
    assign_immer_field(result.mode, value.mode, ctx);
    assign_immer_field(result.period, value.period, ctx);
    assign_immer_field(result.count, value.count, ctx);
    return result;
  }
  static org::sem::Time::Repeat from_immer(org::imm::ImmTime::Repeat const& value, ImmAstContext const& ctx) {
    org::sem::Time::Repeat result = hstd::SerdeDefaultProvider<org::sem::Time::Repeat>::get();
    assign_sem_field(result.mode, value.mode, ctx);
    assign_sem_field(result.period, value.period, ctx);
    assign_sem_field(result.count, value.count, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<org::sem::Time::Static, org::imm::ImmTime::Static> {
  static org::imm::ImmTime::Static to_immer(org::sem::Time::Static const& value, ImmAstEditContext& ctx) {
    org::imm::ImmTime::Static result = hstd::SerdeDefaultProvider<org::imm::ImmTime::Static>::get();
    assign_immer_field(result.repeat, value.repeat, ctx);
    assign_immer_field(result.warn, value.warn, ctx);
    assign_immer_field(result.time, value.time, ctx);
    return result;
  }
  static org::sem::Time::Static from_immer(org::imm::ImmTime::Static const& value, ImmAstContext const& ctx) {
    org::sem::Time::Static result = hstd::SerdeDefaultProvider<org::sem::Time::Static>::get();
    assign_sem_field(result.repeat, value.repeat, ctx);
    assign_sem_field(result.warn, value.warn, ctx);
    assign_sem_field(result.time, value.time, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<org::sem::Time::Dynamic, org::imm::ImmTime::Dynamic> {
  static org::imm::ImmTime::Dynamic to_immer(org::sem::Time::Dynamic const& value, ImmAstEditContext& ctx) {
    org::imm::ImmTime::Dynamic result = hstd::SerdeDefaultProvider<org::imm::ImmTime::Dynamic>::get();
    assign_immer_field(result.expr, value.expr, ctx);
    return result;
  }
  static org::sem::Time::Dynamic from_immer(org::imm::ImmTime::Dynamic const& value, ImmAstContext const& ctx) {
    org::sem::Time::Dynamic result = hstd::SerdeDefaultProvider<org::sem::Time::Dynamic>::get();
    assign_sem_field(result.expr, value.expr, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<org::sem::TimeRange /* d_org */, org::imm::ImmTimeRange /* d_org */> {
  static org::imm::ImmTimeRange /* d_org */ to_immer(org::sem::TimeRange const& /* d_org */ value, ImmAstEditContext& ctx) {
    org::imm::ImmTimeRange /* d_org */ result = hstd::SerdeDefaultProvider<org::imm::ImmTimeRange /* d_org */>::get();
    assign_immer_field(result.from, value.from, ctx);
    assign_immer_field(result.to, value.to, ctx);
    assign_immer_field(result.loc, value.loc, ctx);
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
  static org::sem::TimeRange /* d_org */ from_immer(org::imm::ImmTimeRange const& /* d_org */ value, ImmAstContext const& ctx) {
    org::sem::TimeRange /* d_org */ result = hstd::SerdeDefaultProvider<org::sem::TimeRange /* d_org */>::get();
    assign_sem_field(result.from, value.from, ctx);
    assign_sem_field(result.to, value.to, ctx);
    assign_sem_field(result.loc, value.loc, ctx);
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<org::sem::Macro /* d_org */, org::imm::ImmMacro /* d_org */> {
  static org::imm::ImmMacro /* d_org */ to_immer(org::sem::Macro const& /* d_org */ value, ImmAstEditContext& ctx) {
    org::imm::ImmMacro /* d_org */ result = hstd::SerdeDefaultProvider<org::imm::ImmMacro /* d_org */>::get();
    assign_immer_field(result.name, value.name, ctx);
    assign_immer_field(result.attrs, value.attrs, ctx);
    assign_immer_field(result.loc, value.loc, ctx);
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
  static org::sem::Macro /* d_org */ from_immer(org::imm::ImmMacro const& /* d_org */ value, ImmAstContext const& ctx) {
    org::sem::Macro /* d_org */ result = hstd::SerdeDefaultProvider<org::sem::Macro /* d_org */>::get();
    assign_sem_field(result.name, value.name, ctx);
    assign_sem_field(result.attrs, value.attrs, ctx);
    assign_sem_field(result.loc, value.loc, ctx);
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<org::sem::Symbol /* d_org */, org::imm::ImmSymbol /* d_org */> {
  static org::imm::ImmSymbol /* d_org */ to_immer(org::sem::Symbol const& /* d_org */ value, ImmAstEditContext& ctx) {
    org::imm::ImmSymbol /* d_org */ result = hstd::SerdeDefaultProvider<org::imm::ImmSymbol /* d_org */>::get();
    assign_immer_field(result.name, value.name, ctx);
    assign_immer_field(result.parameters, value.parameters, ctx);
    assign_immer_field(result.positional, value.positional, ctx);
    assign_immer_field(result.loc, value.loc, ctx);
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
  static org::sem::Symbol /* d_org */ from_immer(org::imm::ImmSymbol const& /* d_org */ value, ImmAstContext const& ctx) {
    org::sem::Symbol /* d_org */ result = hstd::SerdeDefaultProvider<org::sem::Symbol /* d_org */>::get();
    assign_sem_field(result.name, value.name, ctx);
    assign_sem_field(result.parameters, value.parameters, ctx);
    assign_sem_field(result.positional, value.positional, ctx);
    assign_sem_field(result.loc, value.loc, ctx);
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<org::sem::Symbol::Param, org::imm::ImmSymbol::Param> {
  static org::imm::ImmSymbol::Param to_immer(org::sem::Symbol::Param const& value, ImmAstEditContext& ctx) {
    org::imm::ImmSymbol::Param result = hstd::SerdeDefaultProvider<org::imm::ImmSymbol::Param>::get();
    assign_immer_field(result.key, value.key, ctx);
    assign_immer_field(result.value, value.value, ctx);
    return result;
  }
  static org::sem::Symbol::Param from_immer(org::imm::ImmSymbol::Param const& value, ImmAstContext const& ctx) {
    org::sem::Symbol::Param result = hstd::SerdeDefaultProvider<org::sem::Symbol::Param>::get();
    assign_sem_field(result.key, value.key, ctx);
    assign_sem_field(result.value, value.value, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<org::sem::Escaped /* d_org */, org::imm::ImmEscaped /* d_org */> {
  static org::imm::ImmEscaped /* d_org */ to_immer(org::sem::Escaped const& /* d_org */ value, ImmAstEditContext& ctx) {
    org::imm::ImmEscaped /* d_org */ result = hstd::SerdeDefaultProvider<org::imm::ImmEscaped /* d_org */>::get();
    assign_immer_field(result.text, value.text, ctx);
    assign_immer_field(result.loc, value.loc, ctx);
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
  static org::sem::Escaped /* d_org */ from_immer(org::imm::ImmEscaped const& /* d_org */ value, ImmAstContext const& ctx) {
    org::sem::Escaped /* d_org */ result = hstd::SerdeDefaultProvider<org::sem::Escaped /* d_org */>::get();
    assign_sem_field(result.text, value.text, ctx);
    assign_sem_field(result.loc, value.loc, ctx);
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<org::sem::Newline /* d_org */, org::imm::ImmNewline /* d_org */> {
  static org::imm::ImmNewline /* d_org */ to_immer(org::sem::Newline const& /* d_org */ value, ImmAstEditContext& ctx) {
    org::imm::ImmNewline /* d_org */ result = hstd::SerdeDefaultProvider<org::imm::ImmNewline /* d_org */>::get();
    assign_immer_field(result.text, value.text, ctx);
    assign_immer_field(result.loc, value.loc, ctx);
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
  static org::sem::Newline /* d_org */ from_immer(org::imm::ImmNewline const& /* d_org */ value, ImmAstContext const& ctx) {
    org::sem::Newline /* d_org */ result = hstd::SerdeDefaultProvider<org::sem::Newline /* d_org */>::get();
    assign_sem_field(result.text, value.text, ctx);
    assign_sem_field(result.loc, value.loc, ctx);
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<org::sem::Space /* d_org */, org::imm::ImmSpace /* d_org */> {
  static org::imm::ImmSpace /* d_org */ to_immer(org::sem::Space const& /* d_org */ value, ImmAstEditContext& ctx) {
    org::imm::ImmSpace /* d_org */ result = hstd::SerdeDefaultProvider<org::imm::ImmSpace /* d_org */>::get();
    assign_immer_field(result.text, value.text, ctx);
    assign_immer_field(result.loc, value.loc, ctx);
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
  static org::sem::Space /* d_org */ from_immer(org::imm::ImmSpace const& /* d_org */ value, ImmAstContext const& ctx) {
    org::sem::Space /* d_org */ result = hstd::SerdeDefaultProvider<org::sem::Space /* d_org */>::get();
    assign_sem_field(result.text, value.text, ctx);
    assign_sem_field(result.loc, value.loc, ctx);
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<org::sem::Word /* d_org */, org::imm::ImmWord /* d_org */> {
  static org::imm::ImmWord /* d_org */ to_immer(org::sem::Word const& /* d_org */ value, ImmAstEditContext& ctx) {
    org::imm::ImmWord /* d_org */ result = hstd::SerdeDefaultProvider<org::imm::ImmWord /* d_org */>::get();
    assign_immer_field(result.text, value.text, ctx);
    assign_immer_field(result.loc, value.loc, ctx);
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
  static org::sem::Word /* d_org */ from_immer(org::imm::ImmWord const& /* d_org */ value, ImmAstContext const& ctx) {
    org::sem::Word /* d_org */ result = hstd::SerdeDefaultProvider<org::sem::Word /* d_org */>::get();
    assign_sem_field(result.text, value.text, ctx);
    assign_sem_field(result.loc, value.loc, ctx);
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<org::sem::AtMention /* d_org */, org::imm::ImmAtMention /* d_org */> {
  static org::imm::ImmAtMention /* d_org */ to_immer(org::sem::AtMention const& /* d_org */ value, ImmAstEditContext& ctx) {
    org::imm::ImmAtMention /* d_org */ result = hstd::SerdeDefaultProvider<org::imm::ImmAtMention /* d_org */>::get();
    assign_immer_field(result.text, value.text, ctx);
    assign_immer_field(result.loc, value.loc, ctx);
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
  static org::sem::AtMention /* d_org */ from_immer(org::imm::ImmAtMention const& /* d_org */ value, ImmAstContext const& ctx) {
    org::sem::AtMention /* d_org */ result = hstd::SerdeDefaultProvider<org::sem::AtMention /* d_org */>::get();
    assign_sem_field(result.text, value.text, ctx);
    assign_sem_field(result.loc, value.loc, ctx);
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<org::sem::RawText /* d_org */, org::imm::ImmRawText /* d_org */> {
  static org::imm::ImmRawText /* d_org */ to_immer(org::sem::RawText const& /* d_org */ value, ImmAstEditContext& ctx) {
    org::imm::ImmRawText /* d_org */ result = hstd::SerdeDefaultProvider<org::imm::ImmRawText /* d_org */>::get();
    assign_immer_field(result.text, value.text, ctx);
    assign_immer_field(result.loc, value.loc, ctx);
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
  static org::sem::RawText /* d_org */ from_immer(org::imm::ImmRawText const& /* d_org */ value, ImmAstContext const& ctx) {
    org::sem::RawText /* d_org */ result = hstd::SerdeDefaultProvider<org::sem::RawText /* d_org */>::get();
    assign_sem_field(result.text, value.text, ctx);
    assign_sem_field(result.loc, value.loc, ctx);
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<org::sem::Punctuation /* d_org */, org::imm::ImmPunctuation /* d_org */> {
  static org::imm::ImmPunctuation /* d_org */ to_immer(org::sem::Punctuation const& /* d_org */ value, ImmAstEditContext& ctx) {
    org::imm::ImmPunctuation /* d_org */ result = hstd::SerdeDefaultProvider<org::imm::ImmPunctuation /* d_org */>::get();
    assign_immer_field(result.text, value.text, ctx);
    assign_immer_field(result.loc, value.loc, ctx);
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
  static org::sem::Punctuation /* d_org */ from_immer(org::imm::ImmPunctuation const& /* d_org */ value, ImmAstContext const& ctx) {
    org::sem::Punctuation /* d_org */ result = hstd::SerdeDefaultProvider<org::sem::Punctuation /* d_org */>::get();
    assign_sem_field(result.text, value.text, ctx);
    assign_sem_field(result.loc, value.loc, ctx);
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<org::sem::Placeholder /* d_org */, org::imm::ImmPlaceholder /* d_org */> {
  static org::imm::ImmPlaceholder /* d_org */ to_immer(org::sem::Placeholder const& /* d_org */ value, ImmAstEditContext& ctx) {
    org::imm::ImmPlaceholder /* d_org */ result = hstd::SerdeDefaultProvider<org::imm::ImmPlaceholder /* d_org */>::get();
    assign_immer_field(result.text, value.text, ctx);
    assign_immer_field(result.loc, value.loc, ctx);
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
  static org::sem::Placeholder /* d_org */ from_immer(org::imm::ImmPlaceholder const& /* d_org */ value, ImmAstContext const& ctx) {
    org::sem::Placeholder /* d_org */ result = hstd::SerdeDefaultProvider<org::sem::Placeholder /* d_org */>::get();
    assign_sem_field(result.text, value.text, ctx);
    assign_sem_field(result.loc, value.loc, ctx);
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<org::sem::BigIdent /* d_org */, org::imm::ImmBigIdent /* d_org */> {
  static org::imm::ImmBigIdent /* d_org */ to_immer(org::sem::BigIdent const& /* d_org */ value, ImmAstEditContext& ctx) {
    org::imm::ImmBigIdent /* d_org */ result = hstd::SerdeDefaultProvider<org::imm::ImmBigIdent /* d_org */>::get();
    assign_immer_field(result.text, value.text, ctx);
    assign_immer_field(result.loc, value.loc, ctx);
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
  static org::sem::BigIdent /* d_org */ from_immer(org::imm::ImmBigIdent const& /* d_org */ value, ImmAstContext const& ctx) {
    org::sem::BigIdent /* d_org */ result = hstd::SerdeDefaultProvider<org::sem::BigIdent /* d_org */>::get();
    assign_sem_field(result.text, value.text, ctx);
    assign_sem_field(result.loc, value.loc, ctx);
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<org::sem::TextTarget /* d_org */, org::imm::ImmTextTarget /* d_org */> {
  static org::imm::ImmTextTarget /* d_org */ to_immer(org::sem::TextTarget const& /* d_org */ value, ImmAstEditContext& ctx) {
    org::imm::ImmTextTarget /* d_org */ result = hstd::SerdeDefaultProvider<org::imm::ImmTextTarget /* d_org */>::get();
    assign_immer_field(result.text, value.text, ctx);
    assign_immer_field(result.loc, value.loc, ctx);
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
  static org::sem::TextTarget /* d_org */ from_immer(org::imm::ImmTextTarget const& /* d_org */ value, ImmAstContext const& ctx) {
    org::sem::TextTarget /* d_org */ result = hstd::SerdeDefaultProvider<org::sem::TextTarget /* d_org */>::get();
    assign_sem_field(result.text, value.text, ctx);
    assign_sem_field(result.loc, value.loc, ctx);
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<org::sem::ErrorSkipToken /* d_org */, org::imm::ImmErrorSkipToken /* d_org */> {
  static org::imm::ImmErrorSkipToken /* d_org */ to_immer(org::sem::ErrorSkipToken const& /* d_org */ value, ImmAstEditContext& ctx) {
    org::imm::ImmErrorSkipToken /* d_org */ result = hstd::SerdeDefaultProvider<org::imm::ImmErrorSkipToken /* d_org */>::get();
    assign_immer_field(result.text, value.text, ctx);
    assign_immer_field(result.loc, value.loc, ctx);
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
  static org::sem::ErrorSkipToken /* d_org */ from_immer(org::imm::ImmErrorSkipToken const& /* d_org */ value, ImmAstContext const& ctx) {
    org::sem::ErrorSkipToken /* d_org */ result = hstd::SerdeDefaultProvider<org::sem::ErrorSkipToken /* d_org */>::get();
    assign_sem_field(result.text, value.text, ctx);
    assign_sem_field(result.loc, value.loc, ctx);
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<org::sem::ErrorSkipGroup /* d_org */, org::imm::ImmErrorSkipGroup /* d_org */> {
  static org::imm::ImmErrorSkipGroup /* d_org */ to_immer(org::sem::ErrorSkipGroup const& /* d_org */ value, ImmAstEditContext& ctx) {
    org::imm::ImmErrorSkipGroup /* d_org */ result = hstd::SerdeDefaultProvider<org::imm::ImmErrorSkipGroup /* d_org */>::get();
    assign_immer_field(result.skipped, value.skipped, ctx);
    assign_immer_field(result.loc, value.loc, ctx);
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
  static org::sem::ErrorSkipGroup /* d_org */ from_immer(org::imm::ImmErrorSkipGroup const& /* d_org */ value, ImmAstContext const& ctx) {
    org::sem::ErrorSkipGroup /* d_org */ result = hstd::SerdeDefaultProvider<org::sem::ErrorSkipGroup /* d_org */>::get();
    assign_sem_field(result.skipped, value.skipped, ctx);
    assign_sem_field(result.loc, value.loc, ctx);
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<org::sem::Bold /* d_org */, org::imm::ImmBold /* d_org */> {
  static org::imm::ImmBold /* d_org */ to_immer(org::sem::Bold const& /* d_org */ value, ImmAstEditContext& ctx) {
    org::imm::ImmBold /* d_org */ result = hstd::SerdeDefaultProvider<org::imm::ImmBold /* d_org */>::get();
    assign_immer_field(result.loc, value.loc, ctx);
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
  static org::sem::Bold /* d_org */ from_immer(org::imm::ImmBold const& /* d_org */ value, ImmAstContext const& ctx) {
    org::sem::Bold /* d_org */ result = hstd::SerdeDefaultProvider<org::sem::Bold /* d_org */>::get();
    assign_sem_field(result.loc, value.loc, ctx);
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<org::sem::Underline /* d_org */, org::imm::ImmUnderline /* d_org */> {
  static org::imm::ImmUnderline /* d_org */ to_immer(org::sem::Underline const& /* d_org */ value, ImmAstEditContext& ctx) {
    org::imm::ImmUnderline /* d_org */ result = hstd::SerdeDefaultProvider<org::imm::ImmUnderline /* d_org */>::get();
    assign_immer_field(result.loc, value.loc, ctx);
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
  static org::sem::Underline /* d_org */ from_immer(org::imm::ImmUnderline const& /* d_org */ value, ImmAstContext const& ctx) {
    org::sem::Underline /* d_org */ result = hstd::SerdeDefaultProvider<org::sem::Underline /* d_org */>::get();
    assign_sem_field(result.loc, value.loc, ctx);
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<org::sem::Monospace /* d_org */, org::imm::ImmMonospace /* d_org */> {
  static org::imm::ImmMonospace /* d_org */ to_immer(org::sem::Monospace const& /* d_org */ value, ImmAstEditContext& ctx) {
    org::imm::ImmMonospace /* d_org */ result = hstd::SerdeDefaultProvider<org::imm::ImmMonospace /* d_org */>::get();
    assign_immer_field(result.loc, value.loc, ctx);
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
  static org::sem::Monospace /* d_org */ from_immer(org::imm::ImmMonospace const& /* d_org */ value, ImmAstContext const& ctx) {
    org::sem::Monospace /* d_org */ result = hstd::SerdeDefaultProvider<org::sem::Monospace /* d_org */>::get();
    assign_sem_field(result.loc, value.loc, ctx);
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<org::sem::MarkQuote /* d_org */, org::imm::ImmMarkQuote /* d_org */> {
  static org::imm::ImmMarkQuote /* d_org */ to_immer(org::sem::MarkQuote const& /* d_org */ value, ImmAstEditContext& ctx) {
    org::imm::ImmMarkQuote /* d_org */ result = hstd::SerdeDefaultProvider<org::imm::ImmMarkQuote /* d_org */>::get();
    assign_immer_field(result.loc, value.loc, ctx);
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
  static org::sem::MarkQuote /* d_org */ from_immer(org::imm::ImmMarkQuote const& /* d_org */ value, ImmAstContext const& ctx) {
    org::sem::MarkQuote /* d_org */ result = hstd::SerdeDefaultProvider<org::sem::MarkQuote /* d_org */>::get();
    assign_sem_field(result.loc, value.loc, ctx);
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<org::sem::Verbatim /* d_org */, org::imm::ImmVerbatim /* d_org */> {
  static org::imm::ImmVerbatim /* d_org */ to_immer(org::sem::Verbatim const& /* d_org */ value, ImmAstEditContext& ctx) {
    org::imm::ImmVerbatim /* d_org */ result = hstd::SerdeDefaultProvider<org::imm::ImmVerbatim /* d_org */>::get();
    assign_immer_field(result.loc, value.loc, ctx);
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
  static org::sem::Verbatim /* d_org */ from_immer(org::imm::ImmVerbatim const& /* d_org */ value, ImmAstContext const& ctx) {
    org::sem::Verbatim /* d_org */ result = hstd::SerdeDefaultProvider<org::sem::Verbatim /* d_org */>::get();
    assign_sem_field(result.loc, value.loc, ctx);
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<org::sem::Italic /* d_org */, org::imm::ImmItalic /* d_org */> {
  static org::imm::ImmItalic /* d_org */ to_immer(org::sem::Italic const& /* d_org */ value, ImmAstEditContext& ctx) {
    org::imm::ImmItalic /* d_org */ result = hstd::SerdeDefaultProvider<org::imm::ImmItalic /* d_org */>::get();
    assign_immer_field(result.loc, value.loc, ctx);
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
  static org::sem::Italic /* d_org */ from_immer(org::imm::ImmItalic const& /* d_org */ value, ImmAstContext const& ctx) {
    org::sem::Italic /* d_org */ result = hstd::SerdeDefaultProvider<org::sem::Italic /* d_org */>::get();
    assign_sem_field(result.loc, value.loc, ctx);
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<org::sem::Strike /* d_org */, org::imm::ImmStrike /* d_org */> {
  static org::imm::ImmStrike /* d_org */ to_immer(org::sem::Strike const& /* d_org */ value, ImmAstEditContext& ctx) {
    org::imm::ImmStrike /* d_org */ result = hstd::SerdeDefaultProvider<org::imm::ImmStrike /* d_org */>::get();
    assign_immer_field(result.loc, value.loc, ctx);
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
  static org::sem::Strike /* d_org */ from_immer(org::imm::ImmStrike const& /* d_org */ value, ImmAstContext const& ctx) {
    org::sem::Strike /* d_org */ result = hstd::SerdeDefaultProvider<org::sem::Strike /* d_org */>::get();
    assign_sem_field(result.loc, value.loc, ctx);
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<org::sem::Par /* d_org */, org::imm::ImmPar /* d_org */> {
  static org::imm::ImmPar /* d_org */ to_immer(org::sem::Par const& /* d_org */ value, ImmAstEditContext& ctx) {
    org::imm::ImmPar /* d_org */ result = hstd::SerdeDefaultProvider<org::imm::ImmPar /* d_org */>::get();
    assign_immer_field(result.loc, value.loc, ctx);
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
  static org::sem::Par /* d_org */ from_immer(org::imm::ImmPar const& /* d_org */ value, ImmAstContext const& ctx) {
    org::sem::Par /* d_org */ result = hstd::SerdeDefaultProvider<org::sem::Par /* d_org */>::get();
    assign_sem_field(result.loc, value.loc, ctx);
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<org::sem::RadioTarget /* d_org */, org::imm::ImmRadioTarget /* d_org */> {
  static org::imm::ImmRadioTarget /* d_org */ to_immer(org::sem::RadioTarget const& /* d_org */ value, ImmAstEditContext& ctx) {
    org::imm::ImmRadioTarget /* d_org */ result = hstd::SerdeDefaultProvider<org::imm::ImmRadioTarget /* d_org */>::get();
    assign_immer_field(result.words, value.words, ctx);
    assign_immer_field(result.loc, value.loc, ctx);
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
  static org::sem::RadioTarget /* d_org */ from_immer(org::imm::ImmRadioTarget const& /* d_org */ value, ImmAstContext const& ctx) {
    org::sem::RadioTarget /* d_org */ result = hstd::SerdeDefaultProvider<org::sem::RadioTarget /* d_org */>::get();
    assign_sem_field(result.words, value.words, ctx);
    assign_sem_field(result.loc, value.loc, ctx);
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<org::sem::Latex /* d_org */, org::imm::ImmLatex /* d_org */> {
  static org::imm::ImmLatex /* d_org */ to_immer(org::sem::Latex const& /* d_org */ value, ImmAstEditContext& ctx) {
    org::imm::ImmLatex /* d_org */ result = hstd::SerdeDefaultProvider<org::imm::ImmLatex /* d_org */>::get();
    assign_immer_field(result.loc, value.loc, ctx);
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
  static org::sem::Latex /* d_org */ from_immer(org::imm::ImmLatex const& /* d_org */ value, ImmAstContext const& ctx) {
    org::sem::Latex /* d_org */ result = hstd::SerdeDefaultProvider<org::sem::Latex /* d_org */>::get();
    assign_sem_field(result.loc, value.loc, ctx);
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<org::sem::Link /* d_org */, org::imm::ImmLink /* d_org */> {
  static org::imm::ImmLink /* d_org */ to_immer(org::sem::Link const& /* d_org */ value, ImmAstEditContext& ctx) {
    org::imm::ImmLink /* d_org */ result = hstd::SerdeDefaultProvider<org::imm::ImmLink /* d_org */>::get();
    assign_immer_field(result.description, value.description, ctx);
    assign_immer_field(result.target, value.target, ctx);
    assign_immer_field(result.attached, value.attached, ctx);
    assign_immer_field(result.loc, value.loc, ctx);
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
  static org::sem::Link /* d_org */ from_immer(org::imm::ImmLink const& /* d_org */ value, ImmAstContext const& ctx) {
    org::sem::Link /* d_org */ result = hstd::SerdeDefaultProvider<org::sem::Link /* d_org */>::get();
    assign_sem_field(result.description, value.description, ctx);
    assign_sem_field(result.target, value.target, ctx);
    assign_sem_field(result.attached, value.attached, ctx);
    assign_sem_field(result.loc, value.loc, ctx);
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<org::sem::BlockCenter /* d_org */, org::imm::ImmBlockCenter /* d_org */> {
  static org::imm::ImmBlockCenter /* d_org */ to_immer(org::sem::BlockCenter const& /* d_org */ value, ImmAstEditContext& ctx) {
    org::imm::ImmBlockCenter /* d_org */ result = hstd::SerdeDefaultProvider<org::imm::ImmBlockCenter /* d_org */>::get();
    assign_immer_field(result.attrs, value.attrs, ctx);
    assign_immer_field(result.attached, value.attached, ctx);
    assign_immer_field(result.loc, value.loc, ctx);
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
  static org::sem::BlockCenter /* d_org */ from_immer(org::imm::ImmBlockCenter const& /* d_org */ value, ImmAstContext const& ctx) {
    org::sem::BlockCenter /* d_org */ result = hstd::SerdeDefaultProvider<org::sem::BlockCenter /* d_org */>::get();
    assign_sem_field(result.attrs, value.attrs, ctx);
    assign_sem_field(result.attached, value.attached, ctx);
    assign_sem_field(result.loc, value.loc, ctx);
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<org::sem::BlockQuote /* d_org */, org::imm::ImmBlockQuote /* d_org */> {
  static org::imm::ImmBlockQuote /* d_org */ to_immer(org::sem::BlockQuote const& /* d_org */ value, ImmAstEditContext& ctx) {
    org::imm::ImmBlockQuote /* d_org */ result = hstd::SerdeDefaultProvider<org::imm::ImmBlockQuote /* d_org */>::get();
    assign_immer_field(result.attrs, value.attrs, ctx);
    assign_immer_field(result.attached, value.attached, ctx);
    assign_immer_field(result.loc, value.loc, ctx);
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
  static org::sem::BlockQuote /* d_org */ from_immer(org::imm::ImmBlockQuote const& /* d_org */ value, ImmAstContext const& ctx) {
    org::sem::BlockQuote /* d_org */ result = hstd::SerdeDefaultProvider<org::sem::BlockQuote /* d_org */>::get();
    assign_sem_field(result.attrs, value.attrs, ctx);
    assign_sem_field(result.attached, value.attached, ctx);
    assign_sem_field(result.loc, value.loc, ctx);
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<org::sem::BlockComment /* d_org */, org::imm::ImmBlockComment /* d_org */> {
  static org::imm::ImmBlockComment /* d_org */ to_immer(org::sem::BlockComment const& /* d_org */ value, ImmAstEditContext& ctx) {
    org::imm::ImmBlockComment /* d_org */ result = hstd::SerdeDefaultProvider<org::imm::ImmBlockComment /* d_org */>::get();
    assign_immer_field(result.attached, value.attached, ctx);
    assign_immer_field(result.loc, value.loc, ctx);
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
  static org::sem::BlockComment /* d_org */ from_immer(org::imm::ImmBlockComment const& /* d_org */ value, ImmAstContext const& ctx) {
    org::sem::BlockComment /* d_org */ result = hstd::SerdeDefaultProvider<org::sem::BlockComment /* d_org */>::get();
    assign_sem_field(result.attached, value.attached, ctx);
    assign_sem_field(result.loc, value.loc, ctx);
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<org::sem::BlockVerse /* d_org */, org::imm::ImmBlockVerse /* d_org */> {
  static org::imm::ImmBlockVerse /* d_org */ to_immer(org::sem::BlockVerse const& /* d_org */ value, ImmAstEditContext& ctx) {
    org::imm::ImmBlockVerse /* d_org */ result = hstd::SerdeDefaultProvider<org::imm::ImmBlockVerse /* d_org */>::get();
    assign_immer_field(result.attrs, value.attrs, ctx);
    assign_immer_field(result.attached, value.attached, ctx);
    assign_immer_field(result.loc, value.loc, ctx);
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
  static org::sem::BlockVerse /* d_org */ from_immer(org::imm::ImmBlockVerse const& /* d_org */ value, ImmAstContext const& ctx) {
    org::sem::BlockVerse /* d_org */ result = hstd::SerdeDefaultProvider<org::sem::BlockVerse /* d_org */>::get();
    assign_sem_field(result.attrs, value.attrs, ctx);
    assign_sem_field(result.attached, value.attached, ctx);
    assign_sem_field(result.loc, value.loc, ctx);
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<org::sem::BlockDynamicFallback /* d_org */, org::imm::ImmBlockDynamicFallback /* d_org */> {
  static org::imm::ImmBlockDynamicFallback /* d_org */ to_immer(org::sem::BlockDynamicFallback const& /* d_org */ value, ImmAstEditContext& ctx) {
    org::imm::ImmBlockDynamicFallback /* d_org */ result = hstd::SerdeDefaultProvider<org::imm::ImmBlockDynamicFallback /* d_org */>::get();
    assign_immer_field(result.name, value.name, ctx);
    assign_immer_field(result.attrs, value.attrs, ctx);
    assign_immer_field(result.attached, value.attached, ctx);
    assign_immer_field(result.loc, value.loc, ctx);
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
  static org::sem::BlockDynamicFallback /* d_org */ from_immer(org::imm::ImmBlockDynamicFallback const& /* d_org */ value, ImmAstContext const& ctx) {
    org::sem::BlockDynamicFallback /* d_org */ result = hstd::SerdeDefaultProvider<org::sem::BlockDynamicFallback /* d_org */>::get();
    assign_sem_field(result.name, value.name, ctx);
    assign_sem_field(result.attrs, value.attrs, ctx);
    assign_sem_field(result.attached, value.attached, ctx);
    assign_sem_field(result.loc, value.loc, ctx);
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<org::sem::BlockExample /* d_org */, org::imm::ImmBlockExample /* d_org */> {
  static org::imm::ImmBlockExample /* d_org */ to_immer(org::sem::BlockExample const& /* d_org */ value, ImmAstEditContext& ctx) {
    org::imm::ImmBlockExample /* d_org */ result = hstd::SerdeDefaultProvider<org::imm::ImmBlockExample /* d_org */>::get();
    assign_immer_field(result.attrs, value.attrs, ctx);
    assign_immer_field(result.attached, value.attached, ctx);
    assign_immer_field(result.loc, value.loc, ctx);
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
  static org::sem::BlockExample /* d_org */ from_immer(org::imm::ImmBlockExample const& /* d_org */ value, ImmAstContext const& ctx) {
    org::sem::BlockExample /* d_org */ result = hstd::SerdeDefaultProvider<org::sem::BlockExample /* d_org */>::get();
    assign_sem_field(result.attrs, value.attrs, ctx);
    assign_sem_field(result.attached, value.attached, ctx);
    assign_sem_field(result.loc, value.loc, ctx);
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<org::sem::BlockExport /* d_org */, org::imm::ImmBlockExport /* d_org */> {
  static org::imm::ImmBlockExport /* d_org */ to_immer(org::sem::BlockExport const& /* d_org */ value, ImmAstEditContext& ctx) {
    org::imm::ImmBlockExport /* d_org */ result = hstd::SerdeDefaultProvider<org::imm::ImmBlockExport /* d_org */>::get();
    assign_immer_field(result.exporter, value.exporter, ctx);
    assign_immer_field(result.content, value.content, ctx);
    assign_immer_field(result.attrs, value.attrs, ctx);
    assign_immer_field(result.attached, value.attached, ctx);
    assign_immer_field(result.loc, value.loc, ctx);
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
  static org::sem::BlockExport /* d_org */ from_immer(org::imm::ImmBlockExport const& /* d_org */ value, ImmAstContext const& ctx) {
    org::sem::BlockExport /* d_org */ result = hstd::SerdeDefaultProvider<org::sem::BlockExport /* d_org */>::get();
    assign_sem_field(result.exporter, value.exporter, ctx);
    assign_sem_field(result.content, value.content, ctx);
    assign_sem_field(result.attrs, value.attrs, ctx);
    assign_sem_field(result.attached, value.attached, ctx);
    assign_sem_field(result.loc, value.loc, ctx);
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<org::sem::BlockAdmonition /* d_org */, org::imm::ImmBlockAdmonition /* d_org */> {
  static org::imm::ImmBlockAdmonition /* d_org */ to_immer(org::sem::BlockAdmonition const& /* d_org */ value, ImmAstEditContext& ctx) {
    org::imm::ImmBlockAdmonition /* d_org */ result = hstd::SerdeDefaultProvider<org::imm::ImmBlockAdmonition /* d_org */>::get();
    assign_immer_field(result.attrs, value.attrs, ctx);
    assign_immer_field(result.attached, value.attached, ctx);
    assign_immer_field(result.loc, value.loc, ctx);
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
  static org::sem::BlockAdmonition /* d_org */ from_immer(org::imm::ImmBlockAdmonition const& /* d_org */ value, ImmAstContext const& ctx) {
    org::sem::BlockAdmonition /* d_org */ result = hstd::SerdeDefaultProvider<org::sem::BlockAdmonition /* d_org */>::get();
    assign_sem_field(result.attrs, value.attrs, ctx);
    assign_sem_field(result.attached, value.attached, ctx);
    assign_sem_field(result.loc, value.loc, ctx);
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<org::sem::BlockCodeEvalResult /* d_org */, org::imm::ImmBlockCodeEvalResult /* d_org */> {
  static org::imm::ImmBlockCodeEvalResult /* d_org */ to_immer(org::sem::BlockCodeEvalResult const& /* d_org */ value, ImmAstEditContext& ctx) {
    org::imm::ImmBlockCodeEvalResult /* d_org */ result = hstd::SerdeDefaultProvider<org::imm::ImmBlockCodeEvalResult /* d_org */>::get();
    assign_immer_field(result.raw, value.raw, ctx);
    assign_immer_field(result.node, value.node, ctx);
    assign_immer_field(result.attrs, value.attrs, ctx);
    assign_immer_field(result.attached, value.attached, ctx);
    assign_immer_field(result.loc, value.loc, ctx);
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
  static org::sem::BlockCodeEvalResult /* d_org */ from_immer(org::imm::ImmBlockCodeEvalResult const& /* d_org */ value, ImmAstContext const& ctx) {
    org::sem::BlockCodeEvalResult /* d_org */ result = hstd::SerdeDefaultProvider<org::sem::BlockCodeEvalResult /* d_org */>::get();
    assign_sem_field(result.raw, value.raw, ctx);
    assign_sem_field(result.node, value.node, ctx);
    assign_sem_field(result.attrs, value.attrs, ctx);
    assign_sem_field(result.attached, value.attached, ctx);
    assign_sem_field(result.loc, value.loc, ctx);
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<org::sem::BlockCode /* d_org */, org::imm::ImmBlockCode /* d_org */> {
  static org::imm::ImmBlockCode /* d_org */ to_immer(org::sem::BlockCode const& /* d_org */ value, ImmAstEditContext& ctx) {
    org::imm::ImmBlockCode /* d_org */ result = hstd::SerdeDefaultProvider<org::imm::ImmBlockCode /* d_org */>::get();
    assign_immer_field(result.lang, value.lang, ctx);
    assign_immer_field(result.result, value.result, ctx);
    assign_immer_field(result.lines, value.lines, ctx);
    assign_immer_field(result.switches, value.switches, ctx);
    assign_immer_field(result.attrs, value.attrs, ctx);
    assign_immer_field(result.attached, value.attached, ctx);
    assign_immer_field(result.loc, value.loc, ctx);
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
  static org::sem::BlockCode /* d_org */ from_immer(org::imm::ImmBlockCode const& /* d_org */ value, ImmAstContext const& ctx) {
    org::sem::BlockCode /* d_org */ result = hstd::SerdeDefaultProvider<org::sem::BlockCode /* d_org */>::get();
    assign_sem_field(result.lang, value.lang, ctx);
    assign_sem_field(result.result, value.result, ctx);
    assign_sem_field(result.lines, value.lines, ctx);
    assign_sem_field(result.switches, value.switches, ctx);
    assign_sem_field(result.attrs, value.attrs, ctx);
    assign_sem_field(result.attached, value.attached, ctx);
    assign_sem_field(result.loc, value.loc, ctx);
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<org::sem::SubtreeLog /* d_org */, org::imm::ImmSubtreeLog /* d_org */> {
  static org::imm::ImmSubtreeLog /* d_org */ to_immer(org::sem::SubtreeLog const& /* d_org */ value, ImmAstEditContext& ctx) {
    org::imm::ImmSubtreeLog /* d_org */ result = hstd::SerdeDefaultProvider<org::imm::ImmSubtreeLog /* d_org */>::get();
    assign_immer_field(result.head, value.head, ctx);
    assign_immer_field(result.desc, value.desc, ctx);
    assign_immer_field(result.loc, value.loc, ctx);
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
  static org::sem::SubtreeLog /* d_org */ from_immer(org::imm::ImmSubtreeLog const& /* d_org */ value, ImmAstContext const& ctx) {
    org::sem::SubtreeLog /* d_org */ result = hstd::SerdeDefaultProvider<org::sem::SubtreeLog /* d_org */>::get();
    assign_sem_field(result.head, value.head, ctx);
    assign_sem_field(result.desc, value.desc, ctx);
    assign_sem_field(result.loc, value.loc, ctx);
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<org::sem::Subtree /* d_org */, org::imm::ImmSubtree /* d_org */> {
  static org::imm::ImmSubtree /* d_org */ to_immer(org::sem::Subtree const& /* d_org */ value, ImmAstEditContext& ctx) {
    org::imm::ImmSubtree /* d_org */ result = hstd::SerdeDefaultProvider<org::imm::ImmSubtree /* d_org */>::get();
    assign_immer_field(result.level, value.level, ctx);
    assign_immer_field(result.treeId, value.treeId, ctx);
    assign_immer_field(result.todo, value.todo, ctx);
    assign_immer_field(result.completion, value.completion, ctx);
    assign_immer_field(result.description, value.description, ctx);
    assign_immer_field(result.tags, value.tags, ctx);
    assign_immer_field(result.title, value.title, ctx);
    assign_immer_field(result.logbook, value.logbook, ctx);
    assign_immer_field(result.properties, value.properties, ctx);
    assign_immer_field(result.closed, value.closed, ctx);
    assign_immer_field(result.deadline, value.deadline, ctx);
    assign_immer_field(result.scheduled, value.scheduled, ctx);
    assign_immer_field(result.isComment, value.isComment, ctx);
    assign_immer_field(result.isArchived, value.isArchived, ctx);
    assign_immer_field(result.priority, value.priority, ctx);
    assign_immer_field(result.loc, value.loc, ctx);
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
  static org::sem::Subtree /* d_org */ from_immer(org::imm::ImmSubtree const& /* d_org */ value, ImmAstContext const& ctx) {
    org::sem::Subtree /* d_org */ result = hstd::SerdeDefaultProvider<org::sem::Subtree /* d_org */>::get();
    assign_sem_field(result.level, value.level, ctx);
    assign_sem_field(result.treeId, value.treeId, ctx);
    assign_sem_field(result.todo, value.todo, ctx);
    assign_sem_field(result.completion, value.completion, ctx);
    assign_sem_field(result.description, value.description, ctx);
    assign_sem_field(result.tags, value.tags, ctx);
    assign_sem_field(result.title, value.title, ctx);
    assign_sem_field(result.logbook, value.logbook, ctx);
    assign_sem_field(result.properties, value.properties, ctx);
    assign_sem_field(result.closed, value.closed, ctx);
    assign_sem_field(result.deadline, value.deadline, ctx);
    assign_sem_field(result.scheduled, value.scheduled, ctx);
    assign_sem_field(result.isComment, value.isComment, ctx);
    assign_sem_field(result.isArchived, value.isArchived, ctx);
    assign_sem_field(result.priority, value.priority, ctx);
    assign_sem_field(result.loc, value.loc, ctx);
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<org::sem::Cell /* d_org */, org::imm::ImmCell /* d_org */> {
  static org::imm::ImmCell /* d_org */ to_immer(org::sem::Cell const& /* d_org */ value, ImmAstEditContext& ctx) {
    org::imm::ImmCell /* d_org */ result = hstd::SerdeDefaultProvider<org::imm::ImmCell /* d_org */>::get();
    assign_immer_field(result.isBlock, value.isBlock, ctx);
    assign_immer_field(result.attrs, value.attrs, ctx);
    assign_immer_field(result.attached, value.attached, ctx);
    assign_immer_field(result.loc, value.loc, ctx);
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
  static org::sem::Cell /* d_org */ from_immer(org::imm::ImmCell const& /* d_org */ value, ImmAstContext const& ctx) {
    org::sem::Cell /* d_org */ result = hstd::SerdeDefaultProvider<org::sem::Cell /* d_org */>::get();
    assign_sem_field(result.isBlock, value.isBlock, ctx);
    assign_sem_field(result.attrs, value.attrs, ctx);
    assign_sem_field(result.attached, value.attached, ctx);
    assign_sem_field(result.loc, value.loc, ctx);
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<org::sem::Row /* d_org */, org::imm::ImmRow /* d_org */> {
  static org::imm::ImmRow /* d_org */ to_immer(org::sem::Row const& /* d_org */ value, ImmAstEditContext& ctx) {
    org::imm::ImmRow /* d_org */ result = hstd::SerdeDefaultProvider<org::imm::ImmRow /* d_org */>::get();
    assign_immer_field(result.cells, value.cells, ctx);
    assign_immer_field(result.isBlock, value.isBlock, ctx);
    assign_immer_field(result.attrs, value.attrs, ctx);
    assign_immer_field(result.attached, value.attached, ctx);
    assign_immer_field(result.loc, value.loc, ctx);
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
  static org::sem::Row /* d_org */ from_immer(org::imm::ImmRow const& /* d_org */ value, ImmAstContext const& ctx) {
    org::sem::Row /* d_org */ result = hstd::SerdeDefaultProvider<org::sem::Row /* d_org */>::get();
    assign_sem_field(result.cells, value.cells, ctx);
    assign_sem_field(result.isBlock, value.isBlock, ctx);
    assign_sem_field(result.attrs, value.attrs, ctx);
    assign_sem_field(result.attached, value.attached, ctx);
    assign_sem_field(result.loc, value.loc, ctx);
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<org::sem::Table /* d_org */, org::imm::ImmTable /* d_org */> {
  static org::imm::ImmTable /* d_org */ to_immer(org::sem::Table const& /* d_org */ value, ImmAstEditContext& ctx) {
    org::imm::ImmTable /* d_org */ result = hstd::SerdeDefaultProvider<org::imm::ImmTable /* d_org */>::get();
    assign_immer_field(result.rows, value.rows, ctx);
    assign_immer_field(result.isBlock, value.isBlock, ctx);
    assign_immer_field(result.attrs, value.attrs, ctx);
    assign_immer_field(result.attached, value.attached, ctx);
    assign_immer_field(result.loc, value.loc, ctx);
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
  static org::sem::Table /* d_org */ from_immer(org::imm::ImmTable const& /* d_org */ value, ImmAstContext const& ctx) {
    org::sem::Table /* d_org */ result = hstd::SerdeDefaultProvider<org::sem::Table /* d_org */>::get();
    assign_sem_field(result.rows, value.rows, ctx);
    assign_sem_field(result.isBlock, value.isBlock, ctx);
    assign_sem_field(result.attrs, value.attrs, ctx);
    assign_sem_field(result.attached, value.attached, ctx);
    assign_sem_field(result.loc, value.loc, ctx);
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<org::sem::Paragraph /* d_org */, org::imm::ImmParagraph /* d_org */> {
  static org::imm::ImmParagraph /* d_org */ to_immer(org::sem::Paragraph const& /* d_org */ value, ImmAstEditContext& ctx) {
    org::imm::ImmParagraph /* d_org */ result = hstd::SerdeDefaultProvider<org::imm::ImmParagraph /* d_org */>::get();
    assign_immer_field(result.attached, value.attached, ctx);
    assign_immer_field(result.loc, value.loc, ctx);
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
  static org::sem::Paragraph /* d_org */ from_immer(org::imm::ImmParagraph const& /* d_org */ value, ImmAstContext const& ctx) {
    org::sem::Paragraph /* d_org */ result = hstd::SerdeDefaultProvider<org::sem::Paragraph /* d_org */>::get();
    assign_sem_field(result.attached, value.attached, ctx);
    assign_sem_field(result.loc, value.loc, ctx);
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<org::sem::ColonExample /* d_org */, org::imm::ImmColonExample /* d_org */> {
  static org::imm::ImmColonExample /* d_org */ to_immer(org::sem::ColonExample const& /* d_org */ value, ImmAstEditContext& ctx) {
    org::imm::ImmColonExample /* d_org */ result = hstd::SerdeDefaultProvider<org::imm::ImmColonExample /* d_org */>::get();
    assign_immer_field(result.loc, value.loc, ctx);
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
  static org::sem::ColonExample /* d_org */ from_immer(org::imm::ImmColonExample const& /* d_org */ value, ImmAstContext const& ctx) {
    org::sem::ColonExample /* d_org */ result = hstd::SerdeDefaultProvider<org::sem::ColonExample /* d_org */>::get();
    assign_sem_field(result.loc, value.loc, ctx);
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<org::sem::CmdAttr /* d_org */, org::imm::ImmCmdAttr /* d_org */> {
  static org::imm::ImmCmdAttr /* d_org */ to_immer(org::sem::CmdAttr const& /* d_org */ value, ImmAstEditContext& ctx) {
    org::imm::ImmCmdAttr /* d_org */ result = hstd::SerdeDefaultProvider<org::imm::ImmCmdAttr /* d_org */>::get();
    assign_immer_field(result.target, value.target, ctx);
    assign_immer_field(result.attrs, value.attrs, ctx);
    assign_immer_field(result.attached, value.attached, ctx);
    assign_immer_field(result.loc, value.loc, ctx);
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
  static org::sem::CmdAttr /* d_org */ from_immer(org::imm::ImmCmdAttr const& /* d_org */ value, ImmAstContext const& ctx) {
    org::sem::CmdAttr /* d_org */ result = hstd::SerdeDefaultProvider<org::sem::CmdAttr /* d_org */>::get();
    assign_sem_field(result.target, value.target, ctx);
    assign_sem_field(result.attrs, value.attrs, ctx);
    assign_sem_field(result.attached, value.attached, ctx);
    assign_sem_field(result.loc, value.loc, ctx);
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<org::sem::CmdExport /* d_org */, org::imm::ImmCmdExport /* d_org */> {
  static org::imm::ImmCmdExport /* d_org */ to_immer(org::sem::CmdExport const& /* d_org */ value, ImmAstEditContext& ctx) {
    org::imm::ImmCmdExport /* d_org */ result = hstd::SerdeDefaultProvider<org::imm::ImmCmdExport /* d_org */>::get();
    assign_immer_field(result.exporter, value.exporter, ctx);
    assign_immer_field(result.content, value.content, ctx);
    assign_immer_field(result.attrs, value.attrs, ctx);
    assign_immer_field(result.attached, value.attached, ctx);
    assign_immer_field(result.loc, value.loc, ctx);
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
  static org::sem::CmdExport /* d_org */ from_immer(org::imm::ImmCmdExport const& /* d_org */ value, ImmAstContext const& ctx) {
    org::sem::CmdExport /* d_org */ result = hstd::SerdeDefaultProvider<org::sem::CmdExport /* d_org */>::get();
    assign_sem_field(result.exporter, value.exporter, ctx);
    assign_sem_field(result.content, value.content, ctx);
    assign_sem_field(result.attrs, value.attrs, ctx);
    assign_sem_field(result.attached, value.attached, ctx);
    assign_sem_field(result.loc, value.loc, ctx);
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<org::sem::Call /* d_org */, org::imm::ImmCall /* d_org */> {
  static org::imm::ImmCall /* d_org */ to_immer(org::sem::Call const& /* d_org */ value, ImmAstEditContext& ctx) {
    org::imm::ImmCall /* d_org */ result = hstd::SerdeDefaultProvider<org::imm::ImmCall /* d_org */>::get();
    assign_immer_field(result.name, value.name, ctx);
    assign_immer_field(result.attrs, value.attrs, ctx);
    assign_immer_field(result.isCommand, value.isCommand, ctx);
    assign_immer_field(result.loc, value.loc, ctx);
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
  static org::sem::Call /* d_org */ from_immer(org::imm::ImmCall const& /* d_org */ value, ImmAstContext const& ctx) {
    org::sem::Call /* d_org */ result = hstd::SerdeDefaultProvider<org::sem::Call /* d_org */>::get();
    assign_sem_field(result.name, value.name, ctx);
    assign_sem_field(result.attrs, value.attrs, ctx);
    assign_sem_field(result.isCommand, value.isCommand, ctx);
    assign_sem_field(result.loc, value.loc, ctx);
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<org::sem::List /* d_org */, org::imm::ImmList /* d_org */> {
  static org::imm::ImmList /* d_org */ to_immer(org::sem::List const& /* d_org */ value, ImmAstEditContext& ctx) {
    org::imm::ImmList /* d_org */ result = hstd::SerdeDefaultProvider<org::imm::ImmList /* d_org */>::get();
    assign_immer_field(result.attached, value.attached, ctx);
    assign_immer_field(result.loc, value.loc, ctx);
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
  static org::sem::List /* d_org */ from_immer(org::imm::ImmList const& /* d_org */ value, ImmAstContext const& ctx) {
    org::sem::List /* d_org */ result = hstd::SerdeDefaultProvider<org::sem::List /* d_org */>::get();
    assign_sem_field(result.attached, value.attached, ctx);
    assign_sem_field(result.loc, value.loc, ctx);
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<org::sem::ListItem /* d_org */, org::imm::ImmListItem /* d_org */> {
  static org::imm::ImmListItem /* d_org */ to_immer(org::sem::ListItem const& /* d_org */ value, ImmAstEditContext& ctx) {
    org::imm::ImmListItem /* d_org */ result = hstd::SerdeDefaultProvider<org::imm::ImmListItem /* d_org */>::get();
    assign_immer_field(result.checkbox, value.checkbox, ctx);
    assign_immer_field(result.header, value.header, ctx);
    assign_immer_field(result.bullet, value.bullet, ctx);
    assign_immer_field(result.loc, value.loc, ctx);
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
  static org::sem::ListItem /* d_org */ from_immer(org::imm::ImmListItem const& /* d_org */ value, ImmAstContext const& ctx) {
    org::sem::ListItem /* d_org */ result = hstd::SerdeDefaultProvider<org::sem::ListItem /* d_org */>::get();
    assign_sem_field(result.checkbox, value.checkbox, ctx);
    assign_sem_field(result.header, value.header, ctx);
    assign_sem_field(result.bullet, value.bullet, ctx);
    assign_sem_field(result.loc, value.loc, ctx);
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<org::sem::DocumentOptions /* d_org */, org::imm::ImmDocumentOptions /* d_org */> {
  static org::imm::ImmDocumentOptions /* d_org */ to_immer(org::sem::DocumentOptions const& /* d_org */ value, ImmAstEditContext& ctx) {
    org::imm::ImmDocumentOptions /* d_org */ result = hstd::SerdeDefaultProvider<org::imm::ImmDocumentOptions /* d_org */>::get();
    assign_immer_field(result.initialVisibility, value.initialVisibility, ctx);
    assign_immer_field(result.properties, value.properties, ctx);
    assign_immer_field(result.exportConfig, value.exportConfig, ctx);
    assign_immer_field(result.fixedWidthSections, value.fixedWidthSections, ctx);
    assign_immer_field(result.startupIndented, value.startupIndented, ctx);
    assign_immer_field(result.category, value.category, ctx);
    assign_immer_field(result.setupfile, value.setupfile, ctx);
    assign_immer_field(result.maxSubtreeLevelExport, value.maxSubtreeLevelExport, ctx);
    assign_immer_field(result.columns, value.columns, ctx);
    assign_immer_field(result.todoKeywords, value.todoKeywords, ctx);
    assign_immer_field(result.doneKeywords, value.doneKeywords, ctx);
    assign_immer_field(result.loc, value.loc, ctx);
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
  static org::sem::DocumentOptions /* d_org */ from_immer(org::imm::ImmDocumentOptions const& /* d_org */ value, ImmAstContext const& ctx) {
    org::sem::DocumentOptions /* d_org */ result = hstd::SerdeDefaultProvider<org::sem::DocumentOptions /* d_org */>::get();
    assign_sem_field(result.initialVisibility, value.initialVisibility, ctx);
    assign_sem_field(result.properties, value.properties, ctx);
    assign_sem_field(result.exportConfig, value.exportConfig, ctx);
    assign_sem_field(result.fixedWidthSections, value.fixedWidthSections, ctx);
    assign_sem_field(result.startupIndented, value.startupIndented, ctx);
    assign_sem_field(result.category, value.category, ctx);
    assign_sem_field(result.setupfile, value.setupfile, ctx);
    assign_sem_field(result.maxSubtreeLevelExport, value.maxSubtreeLevelExport, ctx);
    assign_sem_field(result.columns, value.columns, ctx);
    assign_sem_field(result.todoKeywords, value.todoKeywords, ctx);
    assign_sem_field(result.doneKeywords, value.doneKeywords, ctx);
    assign_sem_field(result.loc, value.loc, ctx);
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<org::sem::DocumentFragment /* d_org */, org::imm::ImmDocumentFragment /* d_org */> {
  static org::imm::ImmDocumentFragment /* d_org */ to_immer(org::sem::DocumentFragment const& /* d_org */ value, ImmAstEditContext& ctx) {
    org::imm::ImmDocumentFragment /* d_org */ result = hstd::SerdeDefaultProvider<org::imm::ImmDocumentFragment /* d_org */>::get();
    assign_immer_field(result.baseLine, value.baseLine, ctx);
    assign_immer_field(result.baseCol, value.baseCol, ctx);
    assign_immer_field(result.loc, value.loc, ctx);
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
  static org::sem::DocumentFragment /* d_org */ from_immer(org::imm::ImmDocumentFragment const& /* d_org */ value, ImmAstContext const& ctx) {
    org::sem::DocumentFragment /* d_org */ result = hstd::SerdeDefaultProvider<org::sem::DocumentFragment /* d_org */>::get();
    assign_sem_field(result.baseLine, value.baseLine, ctx);
    assign_sem_field(result.baseCol, value.baseCol, ctx);
    assign_sem_field(result.loc, value.loc, ctx);
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<org::sem::CriticMarkup /* d_org */, org::imm::ImmCriticMarkup /* d_org */> {
  static org::imm::ImmCriticMarkup /* d_org */ to_immer(org::sem::CriticMarkup const& /* d_org */ value, ImmAstEditContext& ctx) {
    org::imm::ImmCriticMarkup /* d_org */ result = hstd::SerdeDefaultProvider<org::imm::ImmCriticMarkup /* d_org */>::get();
    assign_immer_field(result.kind, value.kind, ctx);
    assign_immer_field(result.loc, value.loc, ctx);
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
  static org::sem::CriticMarkup /* d_org */ from_immer(org::imm::ImmCriticMarkup const& /* d_org */ value, ImmAstContext const& ctx) {
    org::sem::CriticMarkup /* d_org */ result = hstd::SerdeDefaultProvider<org::sem::CriticMarkup /* d_org */>::get();
    assign_sem_field(result.kind, value.kind, ctx);
    assign_sem_field(result.loc, value.loc, ctx);
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<org::sem::Document /* d_org */, org::imm::ImmDocument /* d_org */> {
  static org::imm::ImmDocument /* d_org */ to_immer(org::sem::Document const& /* d_org */ value, ImmAstEditContext& ctx) {
    org::imm::ImmDocument /* d_org */ result = hstd::SerdeDefaultProvider<org::imm::ImmDocument /* d_org */>::get();
    assign_immer_field(result.title, value.title, ctx);
    assign_immer_field(result.author, value.author, ctx);
    assign_immer_field(result.creator, value.creator, ctx);
    assign_immer_field(result.filetags, value.filetags, ctx);
    assign_immer_field(result.email, value.email, ctx);
    assign_immer_field(result.language, value.language, ctx);
    assign_immer_field(result.options, value.options, ctx);
    assign_immer_field(result.exportFileName, value.exportFileName, ctx);
    assign_immer_field(result.loc, value.loc, ctx);
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
  static org::sem::Document /* d_org */ from_immer(org::imm::ImmDocument const& /* d_org */ value, ImmAstContext const& ctx) {
    org::sem::Document /* d_org */ result = hstd::SerdeDefaultProvider<org::sem::Document /* d_org */>::get();
    assign_sem_field(result.title, value.title, ctx);
    assign_sem_field(result.author, value.author, ctx);
    assign_sem_field(result.creator, value.creator, ctx);
    assign_sem_field(result.filetags, value.filetags, ctx);
    assign_sem_field(result.email, value.email, ctx);
    assign_sem_field(result.language, value.language, ctx);
    assign_sem_field(result.options, value.options, ctx);
    assign_sem_field(result.exportFileName, value.exportFileName, ctx);
    assign_sem_field(result.loc, value.loc, ctx);
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<org::sem::FileTarget /* d_org */, org::imm::ImmFileTarget /* d_org */> {
  static org::imm::ImmFileTarget /* d_org */ to_immer(org::sem::FileTarget const& /* d_org */ value, ImmAstEditContext& ctx) {
    org::imm::ImmFileTarget /* d_org */ result = hstd::SerdeDefaultProvider<org::imm::ImmFileTarget /* d_org */>::get();
    assign_immer_field(result.path, value.path, ctx);
    assign_immer_field(result.line, value.line, ctx);
    assign_immer_field(result.searchTarget, value.searchTarget, ctx);
    assign_immer_field(result.restrictToHeadlines, value.restrictToHeadlines, ctx);
    assign_immer_field(result.targetId, value.targetId, ctx);
    assign_immer_field(result.regexp, value.regexp, ctx);
    assign_immer_field(result.loc, value.loc, ctx);
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
  static org::sem::FileTarget /* d_org */ from_immer(org::imm::ImmFileTarget const& /* d_org */ value, ImmAstContext const& ctx) {
    org::sem::FileTarget /* d_org */ result = hstd::SerdeDefaultProvider<org::sem::FileTarget /* d_org */>::get();
    assign_sem_field(result.path, value.path, ctx);
    assign_sem_field(result.line, value.line, ctx);
    assign_sem_field(result.searchTarget, value.searchTarget, ctx);
    assign_sem_field(result.restrictToHeadlines, value.restrictToHeadlines, ctx);
    assign_sem_field(result.targetId, value.targetId, ctx);
    assign_sem_field(result.regexp, value.regexp, ctx);
    assign_sem_field(result.loc, value.loc, ctx);
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<org::sem::TextSeparator /* d_org */, org::imm::ImmTextSeparator /* d_org */> {
  static org::imm::ImmTextSeparator /* d_org */ to_immer(org::sem::TextSeparator const& /* d_org */ value, ImmAstEditContext& ctx) {
    org::imm::ImmTextSeparator /* d_org */ result = hstd::SerdeDefaultProvider<org::imm::ImmTextSeparator /* d_org */>::get();
    assign_immer_field(result.loc, value.loc, ctx);
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
  static org::sem::TextSeparator /* d_org */ from_immer(org::imm::ImmTextSeparator const& /* d_org */ value, ImmAstContext const& ctx) {
    org::sem::TextSeparator /* d_org */ result = hstd::SerdeDefaultProvider<org::sem::TextSeparator /* d_org */>::get();
    assign_sem_field(result.loc, value.loc, ctx);
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<org::sem::DocumentGroup /* d_org */, org::imm::ImmDocumentGroup /* d_org */> {
  static org::imm::ImmDocumentGroup /* d_org */ to_immer(org::sem::DocumentGroup const& /* d_org */ value, ImmAstEditContext& ctx) {
    org::imm::ImmDocumentGroup /* d_org */ result = hstd::SerdeDefaultProvider<org::imm::ImmDocumentGroup /* d_org */>::get();
    assign_immer_field(result.loc, value.loc, ctx);
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
  static org::sem::DocumentGroup /* d_org */ from_immer(org::imm::ImmDocumentGroup const& /* d_org */ value, ImmAstContext const& ctx) {
    org::sem::DocumentGroup /* d_org */ result = hstd::SerdeDefaultProvider<org::sem::DocumentGroup /* d_org */>::get();
    assign_sem_field(result.loc, value.loc, ctx);
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<org::sem::File /* d_org */, org::imm::ImmFile /* d_org */> {
  static org::imm::ImmFile /* d_org */ to_immer(org::sem::File const& /* d_org */ value, ImmAstEditContext& ctx) {
    org::imm::ImmFile /* d_org */ result = hstd::SerdeDefaultProvider<org::imm::ImmFile /* d_org */>::get();
    assign_immer_field(result.relPath, value.relPath, ctx);
    assign_immer_field(result.absPath, value.absPath, ctx);
    assign_immer_field(result.data, value.data, ctx);
    assign_immer_field(result.loc, value.loc, ctx);
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
  static org::sem::File /* d_org */ from_immer(org::imm::ImmFile const& /* d_org */ value, ImmAstContext const& ctx) {
    org::sem::File /* d_org */ result = hstd::SerdeDefaultProvider<org::sem::File /* d_org */>::get();
    assign_sem_field(result.relPath, value.relPath, ctx);
    assign_sem_field(result.absPath, value.absPath, ctx);
    assign_sem_field(result.data, value.data, ctx);
    assign_sem_field(result.loc, value.loc, ctx);
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<org::sem::File::Document, org::imm::ImmFile::Document> {
  static org::imm::ImmFile::Document to_immer(org::sem::File::Document const& value, ImmAstEditContext& ctx) {
    org::imm::ImmFile::Document result = hstd::SerdeDefaultProvider<org::imm::ImmFile::Document>::get();
    return result;
  }
  static org::sem::File::Document from_immer(org::imm::ImmFile::Document const& value, ImmAstContext const& ctx) {
    org::sem::File::Document result = hstd::SerdeDefaultProvider<org::sem::File::Document>::get();
    return result;
  }
};

template <>
struct ImmSemSerde<org::sem::File::Attachment, org::imm::ImmFile::Attachment> {
  static org::imm::ImmFile::Attachment to_immer(org::sem::File::Attachment const& value, ImmAstEditContext& ctx) {
    org::imm::ImmFile::Attachment result = hstd::SerdeDefaultProvider<org::imm::ImmFile::Attachment>::get();
    return result;
  }
  static org::sem::File::Attachment from_immer(org::imm::ImmFile::Attachment const& value, ImmAstContext const& ctx) {
    org::sem::File::Attachment result = hstd::SerdeDefaultProvider<org::sem::File::Attachment>::get();
    return result;
  }
};

template <>
struct ImmSemSerde<org::sem::File::Source, org::imm::ImmFile::Source> {
  static org::imm::ImmFile::Source to_immer(org::sem::File::Source const& value, ImmAstEditContext& ctx) {
    org::imm::ImmFile::Source result = hstd::SerdeDefaultProvider<org::imm::ImmFile::Source>::get();
    return result;
  }
  static org::sem::File::Source from_immer(org::imm::ImmFile::Source const& value, ImmAstContext const& ctx) {
    org::sem::File::Source result = hstd::SerdeDefaultProvider<org::sem::File::Source>::get();
    return result;
  }
};

template <>
struct ImmSemSerde<org::sem::Directory /* d_org */, org::imm::ImmDirectory /* d_org */> {
  static org::imm::ImmDirectory /* d_org */ to_immer(org::sem::Directory const& /* d_org */ value, ImmAstEditContext& ctx) {
    org::imm::ImmDirectory /* d_org */ result = hstd::SerdeDefaultProvider<org::imm::ImmDirectory /* d_org */>::get();
    assign_immer_field(result.relPath, value.relPath, ctx);
    assign_immer_field(result.absPath, value.absPath, ctx);
    assign_immer_field(result.loc, value.loc, ctx);
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
  static org::sem::Directory /* d_org */ from_immer(org::imm::ImmDirectory const& /* d_org */ value, ImmAstContext const& ctx) {
    org::sem::Directory /* d_org */ result = hstd::SerdeDefaultProvider<org::sem::Directory /* d_org */>::get();
    assign_sem_field(result.relPath, value.relPath, ctx);
    assign_sem_field(result.absPath, value.absPath, ctx);
    assign_sem_field(result.loc, value.loc, ctx);
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<org::sem::Symlink /* d_org */, org::imm::ImmSymlink /* d_org */> {
  static org::imm::ImmSymlink /* d_org */ to_immer(org::sem::Symlink const& /* d_org */ value, ImmAstEditContext& ctx) {
    org::imm::ImmSymlink /* d_org */ result = hstd::SerdeDefaultProvider<org::imm::ImmSymlink /* d_org */>::get();
    assign_immer_field(result.isDirectory, value.isDirectory, ctx);
    assign_immer_field(result.absPath, value.absPath, ctx);
    assign_immer_field(result.loc, value.loc, ctx);
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
  static org::sem::Symlink /* d_org */ from_immer(org::imm::ImmSymlink const& /* d_org */ value, ImmAstContext const& ctx) {
    org::sem::Symlink /* d_org */ result = hstd::SerdeDefaultProvider<org::sem::Symlink /* d_org */>::get();
    assign_sem_field(result.isDirectory, value.isDirectory, ctx);
    assign_sem_field(result.absPath, value.absPath, ctx);
    assign_sem_field(result.loc, value.loc, ctx);
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<org::sem::CmdInclude /* d_org */, org::imm::ImmCmdInclude /* d_org */> {
  static org::imm::ImmCmdInclude /* d_org */ to_immer(org::sem::CmdInclude const& /* d_org */ value, ImmAstEditContext& ctx) {
    org::imm::ImmCmdInclude /* d_org */ result = hstd::SerdeDefaultProvider<org::imm::ImmCmdInclude /* d_org */>::get();
    assign_immer_field(result.path, value.path, ctx);
    assign_immer_field(result.firstLine, value.firstLine, ctx);
    assign_immer_field(result.lastLine, value.lastLine, ctx);
    assign_immer_field(result.data, value.data, ctx);
    assign_immer_field(result.loc, value.loc, ctx);
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
  static org::sem::CmdInclude /* d_org */ from_immer(org::imm::ImmCmdInclude const& /* d_org */ value, ImmAstContext const& ctx) {
    org::sem::CmdInclude /* d_org */ result = hstd::SerdeDefaultProvider<org::sem::CmdInclude /* d_org */>::get();
    assign_sem_field(result.path, value.path, ctx);
    assign_sem_field(result.firstLine, value.firstLine, ctx);
    assign_sem_field(result.lastLine, value.lastLine, ctx);
    assign_sem_field(result.data, value.data, ctx);
    assign_sem_field(result.loc, value.loc, ctx);
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<org::sem::CmdInclude::IncludeBase, org::imm::ImmCmdInclude::IncludeBase> {
  static org::imm::ImmCmdInclude::IncludeBase to_immer(org::sem::CmdInclude::IncludeBase const& value, ImmAstEditContext& ctx) {
    org::imm::ImmCmdInclude::IncludeBase result = hstd::SerdeDefaultProvider<org::imm::ImmCmdInclude::IncludeBase>::get();
    return result;
  }
  static org::sem::CmdInclude::IncludeBase from_immer(org::imm::ImmCmdInclude::IncludeBase const& value, ImmAstContext const& ctx) {
    org::sem::CmdInclude::IncludeBase result = hstd::SerdeDefaultProvider<org::sem::CmdInclude::IncludeBase>::get();
    return result;
  }
};

template <>
struct ImmSemSerde<org::sem::CmdInclude::Example, org::imm::ImmCmdInclude::Example> {
  static org::imm::ImmCmdInclude::Example to_immer(org::sem::CmdInclude::Example const& value, ImmAstEditContext& ctx) {
    org::imm::ImmCmdInclude::Example result = hstd::SerdeDefaultProvider<org::imm::ImmCmdInclude::Example>::get();
    return result;
  }
  static org::sem::CmdInclude::Example from_immer(org::imm::ImmCmdInclude::Example const& value, ImmAstContext const& ctx) {
    org::sem::CmdInclude::Example result = hstd::SerdeDefaultProvider<org::sem::CmdInclude::Example>::get();
    return result;
  }
};

template <>
struct ImmSemSerde<org::sem::CmdInclude::Export, org::imm::ImmCmdInclude::Export> {
  static org::imm::ImmCmdInclude::Export to_immer(org::sem::CmdInclude::Export const& value, ImmAstEditContext& ctx) {
    org::imm::ImmCmdInclude::Export result = hstd::SerdeDefaultProvider<org::imm::ImmCmdInclude::Export>::get();
    assign_immer_field(result.language, value.language, ctx);
    return result;
  }
  static org::sem::CmdInclude::Export from_immer(org::imm::ImmCmdInclude::Export const& value, ImmAstContext const& ctx) {
    org::sem::CmdInclude::Export result = hstd::SerdeDefaultProvider<org::sem::CmdInclude::Export>::get();
    assign_sem_field(result.language, value.language, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<org::sem::CmdInclude::Custom, org::imm::ImmCmdInclude::Custom> {
  static org::imm::ImmCmdInclude::Custom to_immer(org::sem::CmdInclude::Custom const& value, ImmAstEditContext& ctx) {
    org::imm::ImmCmdInclude::Custom result = hstd::SerdeDefaultProvider<org::imm::ImmCmdInclude::Custom>::get();
    assign_immer_field(result.blockName, value.blockName, ctx);
    return result;
  }
  static org::sem::CmdInclude::Custom from_immer(org::imm::ImmCmdInclude::Custom const& value, ImmAstContext const& ctx) {
    org::sem::CmdInclude::Custom result = hstd::SerdeDefaultProvider<org::sem::CmdInclude::Custom>::get();
    assign_sem_field(result.blockName, value.blockName, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<org::sem::CmdInclude::Src, org::imm::ImmCmdInclude::Src> {
  static org::imm::ImmCmdInclude::Src to_immer(org::sem::CmdInclude::Src const& value, ImmAstEditContext& ctx) {
    org::imm::ImmCmdInclude::Src result = hstd::SerdeDefaultProvider<org::imm::ImmCmdInclude::Src>::get();
    assign_immer_field(result.language, value.language, ctx);
    return result;
  }
  static org::sem::CmdInclude::Src from_immer(org::imm::ImmCmdInclude::Src const& value, ImmAstContext const& ctx) {
    org::sem::CmdInclude::Src result = hstd::SerdeDefaultProvider<org::sem::CmdInclude::Src>::get();
    assign_sem_field(result.language, value.language, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<org::sem::CmdInclude::OrgDocument, org::imm::ImmCmdInclude::OrgDocument> {
  static org::imm::ImmCmdInclude::OrgDocument to_immer(org::sem::CmdInclude::OrgDocument const& value, ImmAstEditContext& ctx) {
    org::imm::ImmCmdInclude::OrgDocument result = hstd::SerdeDefaultProvider<org::imm::ImmCmdInclude::OrgDocument>::get();
    assign_immer_field(result.onlyContent, value.onlyContent, ctx);
    assign_immer_field(result.subtreePath, value.subtreePath, ctx);
    assign_immer_field(result.minLevel, value.minLevel, ctx);
    assign_immer_field(result.customIdTarget, value.customIdTarget, ctx);
    return result;
  }
  static org::sem::CmdInclude::OrgDocument from_immer(org::imm::ImmCmdInclude::OrgDocument const& value, ImmAstContext const& ctx) {
    org::sem::CmdInclude::OrgDocument result = hstd::SerdeDefaultProvider<org::sem::CmdInclude::OrgDocument>::get();
    assign_sem_field(result.onlyContent, value.onlyContent, ctx);
    assign_sem_field(result.subtreePath, value.subtreePath, ctx);
    assign_sem_field(result.minLevel, value.minLevel, ctx);
    assign_sem_field(result.customIdTarget, value.customIdTarget, ctx);
    return result;
  }
};

/* clang-format on */