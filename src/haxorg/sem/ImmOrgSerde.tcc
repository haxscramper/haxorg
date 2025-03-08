/* clang-format off */
template <>
struct ImmSemSerde<org::sem::None, org::imm::ImmNone> {
  static org::imm::ImmNone to_immer(org::sem::None const& value, ImmAstEditContext& ctx) {
    org::imm::ImmNone result = hstd::SerdeDefaultProvider<org::imm::ImmNone>::get();
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    assign_immer_field(result.loc, value.loc, ctx);
    return result;
  }
  static org::sem::None from_immer(org::imm::ImmNone const& value, ImmAstContext const& ctx) {
    org::sem::None result = hstd::SerdeDefaultProvider<org::sem::None>::get();
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    assign_sem_field(result.loc, value.loc, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<org::sem::ErrorItem, org::imm::ImmErrorItem> {
  static org::imm::ImmErrorItem to_immer(org::sem::ErrorItem const& value, ImmAstEditContext& ctx) {
    org::imm::ImmErrorItem result = hstd::SerdeDefaultProvider<org::imm::ImmErrorItem>::get();
    assign_immer_field(result.message, value.message, ctx);
    assign_immer_field(result.function, value.function, ctx);
    assign_immer_field(result.line, value.line, ctx);
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    assign_immer_field(result.loc, value.loc, ctx);
    return result;
  }
  static org::sem::ErrorItem from_immer(org::imm::ImmErrorItem const& value, ImmAstContext const& ctx) {
    org::sem::ErrorItem result = hstd::SerdeDefaultProvider<org::sem::ErrorItem>::get();
    assign_sem_field(result.message, value.message, ctx);
    assign_sem_field(result.function, value.function, ctx);
    assign_sem_field(result.line, value.line, ctx);
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    assign_sem_field(result.loc, value.loc, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<org::sem::ErrorGroup, org::imm::ImmErrorGroup> {
  static org::imm::ImmErrorGroup to_immer(org::sem::ErrorGroup const& value, ImmAstEditContext& ctx) {
    org::imm::ImmErrorGroup result = hstd::SerdeDefaultProvider<org::imm::ImmErrorGroup>::get();
    assign_immer_field(result.diagnostics, value.diagnostics, ctx);
    assign_immer_field(result.function, value.function, ctx);
    assign_immer_field(result.line, value.line, ctx);
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    assign_immer_field(result.loc, value.loc, ctx);
    return result;
  }
  static org::sem::ErrorGroup from_immer(org::imm::ImmErrorGroup const& value, ImmAstContext const& ctx) {
    org::sem::ErrorGroup result = hstd::SerdeDefaultProvider<org::sem::ErrorGroup>::get();
    assign_sem_field(result.diagnostics, value.diagnostics, ctx);
    assign_sem_field(result.function, value.function, ctx);
    assign_sem_field(result.line, value.line, ctx);
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    assign_sem_field(result.loc, value.loc, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<org::sem::StmtList, org::imm::ImmStmtList> {
  static org::imm::ImmStmtList to_immer(org::sem::StmtList const& value, ImmAstEditContext& ctx) {
    org::imm::ImmStmtList result = hstd::SerdeDefaultProvider<org::imm::ImmStmtList>::get();
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    assign_immer_field(result.loc, value.loc, ctx);
    return result;
  }
  static org::sem::StmtList from_immer(org::imm::ImmStmtList const& value, ImmAstContext const& ctx) {
    org::sem::StmtList result = hstd::SerdeDefaultProvider<org::sem::StmtList>::get();
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    assign_sem_field(result.loc, value.loc, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<org::sem::Empty, org::imm::ImmEmpty> {
  static org::imm::ImmEmpty to_immer(org::sem::Empty const& value, ImmAstEditContext& ctx) {
    org::imm::ImmEmpty result = hstd::SerdeDefaultProvider<org::imm::ImmEmpty>::get();
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    assign_immer_field(result.loc, value.loc, ctx);
    return result;
  }
  static org::sem::Empty from_immer(org::imm::ImmEmpty const& value, ImmAstContext const& ctx) {
    org::sem::Empty result = hstd::SerdeDefaultProvider<org::sem::Empty>::get();
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    assign_sem_field(result.loc, value.loc, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<org::sem::CmdCaption, org::imm::ImmCmdCaption> {
  static org::imm::ImmCmdCaption to_immer(org::sem::CmdCaption const& value, ImmAstEditContext& ctx) {
    org::imm::ImmCmdCaption result = hstd::SerdeDefaultProvider<org::imm::ImmCmdCaption>::get();
    assign_immer_field(result.text, value.text, ctx);
    assign_immer_field(result.attrs, value.attrs, ctx);
    assign_immer_field(result.attached, value.attached, ctx);
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    assign_immer_field(result.loc, value.loc, ctx);
    return result;
  }
  static org::sem::CmdCaption from_immer(org::imm::ImmCmdCaption const& value, ImmAstContext const& ctx) {
    org::sem::CmdCaption result = hstd::SerdeDefaultProvider<org::sem::CmdCaption>::get();
    assign_sem_field(result.text, value.text, ctx);
    assign_sem_field(result.attrs, value.attrs, ctx);
    assign_sem_field(result.attached, value.attached, ctx);
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    assign_sem_field(result.loc, value.loc, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<org::sem::CmdColumns, org::imm::ImmCmdColumns> {
  static org::imm::ImmCmdColumns to_immer(org::sem::CmdColumns const& value, ImmAstEditContext& ctx) {
    org::imm::ImmCmdColumns result = hstd::SerdeDefaultProvider<org::imm::ImmCmdColumns>::get();
    assign_immer_field(result.view, value.view, ctx);
    assign_immer_field(result.attrs, value.attrs, ctx);
    assign_immer_field(result.attached, value.attached, ctx);
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    assign_immer_field(result.loc, value.loc, ctx);
    return result;
  }
  static org::sem::CmdColumns from_immer(org::imm::ImmCmdColumns const& value, ImmAstContext const& ctx) {
    org::sem::CmdColumns result = hstd::SerdeDefaultProvider<org::sem::CmdColumns>::get();
    assign_sem_field(result.view, value.view, ctx);
    assign_sem_field(result.attrs, value.attrs, ctx);
    assign_sem_field(result.attached, value.attached, ctx);
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    assign_sem_field(result.loc, value.loc, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<org::sem::CmdName, org::imm::ImmCmdName> {
  static org::imm::ImmCmdName to_immer(org::sem::CmdName const& value, ImmAstEditContext& ctx) {
    org::imm::ImmCmdName result = hstd::SerdeDefaultProvider<org::imm::ImmCmdName>::get();
    assign_immer_field(result.name, value.name, ctx);
    assign_immer_field(result.attrs, value.attrs, ctx);
    assign_immer_field(result.attached, value.attached, ctx);
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    assign_immer_field(result.loc, value.loc, ctx);
    return result;
  }
  static org::sem::CmdName from_immer(org::imm::ImmCmdName const& value, ImmAstContext const& ctx) {
    org::sem::CmdName result = hstd::SerdeDefaultProvider<org::sem::CmdName>::get();
    assign_sem_field(result.name, value.name, ctx);
    assign_sem_field(result.attrs, value.attrs, ctx);
    assign_sem_field(result.attached, value.attached, ctx);
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    assign_sem_field(result.loc, value.loc, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<org::sem::CmdCustomArgs, org::imm::ImmCmdCustomArgs> {
  static org::imm::ImmCmdCustomArgs to_immer(org::sem::CmdCustomArgs const& value, ImmAstEditContext& ctx) {
    org::imm::ImmCmdCustomArgs result = hstd::SerdeDefaultProvider<org::imm::ImmCmdCustomArgs>::get();
    assign_immer_field(result.name, value.name, ctx);
    assign_immer_field(result.isAttached, value.isAttached, ctx);
    assign_immer_field(result.attrs, value.attrs, ctx);
    assign_immer_field(result.attached, value.attached, ctx);
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    assign_immer_field(result.loc, value.loc, ctx);
    return result;
  }
  static org::sem::CmdCustomArgs from_immer(org::imm::ImmCmdCustomArgs const& value, ImmAstContext const& ctx) {
    org::sem::CmdCustomArgs result = hstd::SerdeDefaultProvider<org::sem::CmdCustomArgs>::get();
    assign_sem_field(result.name, value.name, ctx);
    assign_sem_field(result.isAttached, value.isAttached, ctx);
    assign_sem_field(result.attrs, value.attrs, ctx);
    assign_sem_field(result.attached, value.attached, ctx);
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    assign_sem_field(result.loc, value.loc, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<org::sem::CmdCustomRaw, org::imm::ImmCmdCustomRaw> {
  static org::imm::ImmCmdCustomRaw to_immer(org::sem::CmdCustomRaw const& value, ImmAstEditContext& ctx) {
    org::imm::ImmCmdCustomRaw result = hstd::SerdeDefaultProvider<org::imm::ImmCmdCustomRaw>::get();
    assign_immer_field(result.name, value.name, ctx);
    assign_immer_field(result.isAttached, value.isAttached, ctx);
    assign_immer_field(result.text, value.text, ctx);
    assign_immer_field(result.attached, value.attached, ctx);
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    assign_immer_field(result.loc, value.loc, ctx);
    return result;
  }
  static org::sem::CmdCustomRaw from_immer(org::imm::ImmCmdCustomRaw const& value, ImmAstContext const& ctx) {
    org::sem::CmdCustomRaw result = hstd::SerdeDefaultProvider<org::sem::CmdCustomRaw>::get();
    assign_sem_field(result.name, value.name, ctx);
    assign_sem_field(result.isAttached, value.isAttached, ctx);
    assign_sem_field(result.text, value.text, ctx);
    assign_sem_field(result.attached, value.attached, ctx);
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    assign_sem_field(result.loc, value.loc, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<org::sem::CmdCustomText, org::imm::ImmCmdCustomText> {
  static org::imm::ImmCmdCustomText to_immer(org::sem::CmdCustomText const& value, ImmAstEditContext& ctx) {
    org::imm::ImmCmdCustomText result = hstd::SerdeDefaultProvider<org::imm::ImmCmdCustomText>::get();
    assign_immer_field(result.name, value.name, ctx);
    assign_immer_field(result.isAttached, value.isAttached, ctx);
    assign_immer_field(result.text, value.text, ctx);
    assign_immer_field(result.attached, value.attached, ctx);
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    assign_immer_field(result.loc, value.loc, ctx);
    return result;
  }
  static org::sem::CmdCustomText from_immer(org::imm::ImmCmdCustomText const& value, ImmAstContext const& ctx) {
    org::sem::CmdCustomText result = hstd::SerdeDefaultProvider<org::sem::CmdCustomText>::get();
    assign_sem_field(result.name, value.name, ctx);
    assign_sem_field(result.isAttached, value.isAttached, ctx);
    assign_sem_field(result.text, value.text, ctx);
    assign_sem_field(result.attached, value.attached, ctx);
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    assign_sem_field(result.loc, value.loc, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<org::sem::CmdCall, org::imm::ImmCmdCall> {
  static org::imm::ImmCmdCall to_immer(org::sem::CmdCall const& value, ImmAstEditContext& ctx) {
    org::imm::ImmCmdCall result = hstd::SerdeDefaultProvider<org::imm::ImmCmdCall>::get();
    assign_immer_field(result.name, value.name, ctx);
    assign_immer_field(result.fileName, value.fileName, ctx);
    assign_immer_field(result.insideHeaderAttrs, value.insideHeaderAttrs, ctx);
    assign_immer_field(result.callAttrs, value.callAttrs, ctx);
    assign_immer_field(result.endHeaderAttrs, value.endHeaderAttrs, ctx);
    assign_immer_field(result.result, value.result, ctx);
    assign_immer_field(result.attrs, value.attrs, ctx);
    assign_immer_field(result.attached, value.attached, ctx);
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    assign_immer_field(result.loc, value.loc, ctx);
    return result;
  }
  static org::sem::CmdCall from_immer(org::imm::ImmCmdCall const& value, ImmAstContext const& ctx) {
    org::sem::CmdCall result = hstd::SerdeDefaultProvider<org::sem::CmdCall>::get();
    assign_sem_field(result.name, value.name, ctx);
    assign_sem_field(result.fileName, value.fileName, ctx);
    assign_sem_field(result.insideHeaderAttrs, value.insideHeaderAttrs, ctx);
    assign_sem_field(result.callAttrs, value.callAttrs, ctx);
    assign_sem_field(result.endHeaderAttrs, value.endHeaderAttrs, ctx);
    assign_sem_field(result.result, value.result, ctx);
    assign_sem_field(result.attrs, value.attrs, ctx);
    assign_sem_field(result.attached, value.attached, ctx);
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    assign_sem_field(result.loc, value.loc, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<org::sem::CmdTblfm, org::imm::ImmCmdTblfm> {
  static org::imm::ImmCmdTblfm to_immer(org::sem::CmdTblfm const& value, ImmAstEditContext& ctx) {
    org::imm::ImmCmdTblfm result = hstd::SerdeDefaultProvider<org::imm::ImmCmdTblfm>::get();
    assign_immer_field(result.expr, value.expr, ctx);
    assign_immer_field(result.attrs, value.attrs, ctx);
    assign_immer_field(result.attached, value.attached, ctx);
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    assign_immer_field(result.loc, value.loc, ctx);
    return result;
  }
  static org::sem::CmdTblfm from_immer(org::imm::ImmCmdTblfm const& value, ImmAstContext const& ctx) {
    org::sem::CmdTblfm result = hstd::SerdeDefaultProvider<org::sem::CmdTblfm>::get();
    assign_sem_field(result.expr, value.expr, ctx);
    assign_sem_field(result.attrs, value.attrs, ctx);
    assign_sem_field(result.attached, value.attached, ctx);
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    assign_sem_field(result.loc, value.loc, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<org::sem::HashTag, org::imm::ImmHashTag> {
  static org::imm::ImmHashTag to_immer(org::sem::HashTag const& value, ImmAstEditContext& ctx) {
    org::imm::ImmHashTag result = hstd::SerdeDefaultProvider<org::imm::ImmHashTag>::get();
    assign_immer_field(result.text, value.text, ctx);
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    assign_immer_field(result.loc, value.loc, ctx);
    return result;
  }
  static org::sem::HashTag from_immer(org::imm::ImmHashTag const& value, ImmAstContext const& ctx) {
    org::sem::HashTag result = hstd::SerdeDefaultProvider<org::sem::HashTag>::get();
    assign_sem_field(result.text, value.text, ctx);
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    assign_sem_field(result.loc, value.loc, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<org::sem::InlineFootnote, org::imm::ImmInlineFootnote> {
  static org::imm::ImmInlineFootnote to_immer(org::sem::InlineFootnote const& value, ImmAstEditContext& ctx) {
    org::imm::ImmInlineFootnote result = hstd::SerdeDefaultProvider<org::imm::ImmInlineFootnote>::get();
    assign_immer_field(result.tag, value.tag, ctx);
    assign_immer_field(result.definition, value.definition, ctx);
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    assign_immer_field(result.loc, value.loc, ctx);
    return result;
  }
  static org::sem::InlineFootnote from_immer(org::imm::ImmInlineFootnote const& value, ImmAstContext const& ctx) {
    org::sem::InlineFootnote result = hstd::SerdeDefaultProvider<org::sem::InlineFootnote>::get();
    assign_sem_field(result.tag, value.tag, ctx);
    assign_sem_field(result.definition, value.definition, ctx);
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    assign_sem_field(result.loc, value.loc, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<org::sem::InlineExport, org::imm::ImmInlineExport> {
  static org::imm::ImmInlineExport to_immer(org::sem::InlineExport const& value, ImmAstEditContext& ctx) {
    org::imm::ImmInlineExport result = hstd::SerdeDefaultProvider<org::imm::ImmInlineExport>::get();
    assign_immer_field(result.exporter, value.exporter, ctx);
    assign_immer_field(result.content, value.content, ctx);
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    assign_immer_field(result.loc, value.loc, ctx);
    return result;
  }
  static org::sem::InlineExport from_immer(org::imm::ImmInlineExport const& value, ImmAstContext const& ctx) {
    org::sem::InlineExport result = hstd::SerdeDefaultProvider<org::sem::InlineExport>::get();
    assign_sem_field(result.exporter, value.exporter, ctx);
    assign_sem_field(result.content, value.content, ctx);
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    assign_sem_field(result.loc, value.loc, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<org::sem::Time, org::imm::ImmTime> {
  static org::imm::ImmTime to_immer(org::sem::Time const& value, ImmAstEditContext& ctx) {
    org::imm::ImmTime result = hstd::SerdeDefaultProvider<org::imm::ImmTime>::get();
    assign_immer_field(result.isActive, value.isActive, ctx);
    assign_immer_field(result.time, value.time, ctx);
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    assign_immer_field(result.loc, value.loc, ctx);
    return result;
  }
  static org::sem::Time from_immer(org::imm::ImmTime const& value, ImmAstContext const& ctx) {
    org::sem::Time result = hstd::SerdeDefaultProvider<org::sem::Time>::get();
    assign_sem_field(result.isActive, value.isActive, ctx);
    assign_sem_field(result.time, value.time, ctx);
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    assign_sem_field(result.loc, value.loc, ctx);
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
    assign_immer_field(result.time, value.time, ctx);
    return result;
  }
  static org::sem::Time::Static from_immer(org::imm::ImmTime::Static const& value, ImmAstContext const& ctx) {
    org::sem::Time::Static result = hstd::SerdeDefaultProvider<org::sem::Time::Static>::get();
    assign_sem_field(result.repeat, value.repeat, ctx);
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
struct ImmSemSerde<org::sem::TimeRange, org::imm::ImmTimeRange> {
  static org::imm::ImmTimeRange to_immer(org::sem::TimeRange const& value, ImmAstEditContext& ctx) {
    org::imm::ImmTimeRange result = hstd::SerdeDefaultProvider<org::imm::ImmTimeRange>::get();
    assign_immer_field(result.from, value.from, ctx);
    assign_immer_field(result.to, value.to, ctx);
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    assign_immer_field(result.loc, value.loc, ctx);
    return result;
  }
  static org::sem::TimeRange from_immer(org::imm::ImmTimeRange const& value, ImmAstContext const& ctx) {
    org::sem::TimeRange result = hstd::SerdeDefaultProvider<org::sem::TimeRange>::get();
    assign_sem_field(result.from, value.from, ctx);
    assign_sem_field(result.to, value.to, ctx);
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    assign_sem_field(result.loc, value.loc, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<org::sem::Macro, org::imm::ImmMacro> {
  static org::imm::ImmMacro to_immer(org::sem::Macro const& value, ImmAstEditContext& ctx) {
    org::imm::ImmMacro result = hstd::SerdeDefaultProvider<org::imm::ImmMacro>::get();
    assign_immer_field(result.name, value.name, ctx);
    assign_immer_field(result.attrs, value.attrs, ctx);
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    assign_immer_field(result.loc, value.loc, ctx);
    return result;
  }
  static org::sem::Macro from_immer(org::imm::ImmMacro const& value, ImmAstContext const& ctx) {
    org::sem::Macro result = hstd::SerdeDefaultProvider<org::sem::Macro>::get();
    assign_sem_field(result.name, value.name, ctx);
    assign_sem_field(result.attrs, value.attrs, ctx);
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    assign_sem_field(result.loc, value.loc, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<org::sem::Symbol, org::imm::ImmSymbol> {
  static org::imm::ImmSymbol to_immer(org::sem::Symbol const& value, ImmAstEditContext& ctx) {
    org::imm::ImmSymbol result = hstd::SerdeDefaultProvider<org::imm::ImmSymbol>::get();
    assign_immer_field(result.name, value.name, ctx);
    assign_immer_field(result.parameters, value.parameters, ctx);
    assign_immer_field(result.positional, value.positional, ctx);
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    assign_immer_field(result.loc, value.loc, ctx);
    return result;
  }
  static org::sem::Symbol from_immer(org::imm::ImmSymbol const& value, ImmAstContext const& ctx) {
    org::sem::Symbol result = hstd::SerdeDefaultProvider<org::sem::Symbol>::get();
    assign_sem_field(result.name, value.name, ctx);
    assign_sem_field(result.parameters, value.parameters, ctx);
    assign_sem_field(result.positional, value.positional, ctx);
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    assign_sem_field(result.loc, value.loc, ctx);
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
struct ImmSemSerde<org::sem::Escaped, org::imm::ImmEscaped> {
  static org::imm::ImmEscaped to_immer(org::sem::Escaped const& value, ImmAstEditContext& ctx) {
    org::imm::ImmEscaped result = hstd::SerdeDefaultProvider<org::imm::ImmEscaped>::get();
    assign_immer_field(result.text, value.text, ctx);
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    assign_immer_field(result.loc, value.loc, ctx);
    return result;
  }
  static org::sem::Escaped from_immer(org::imm::ImmEscaped const& value, ImmAstContext const& ctx) {
    org::sem::Escaped result = hstd::SerdeDefaultProvider<org::sem::Escaped>::get();
    assign_sem_field(result.text, value.text, ctx);
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    assign_sem_field(result.loc, value.loc, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<org::sem::Newline, org::imm::ImmNewline> {
  static org::imm::ImmNewline to_immer(org::sem::Newline const& value, ImmAstEditContext& ctx) {
    org::imm::ImmNewline result = hstd::SerdeDefaultProvider<org::imm::ImmNewline>::get();
    assign_immer_field(result.text, value.text, ctx);
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    assign_immer_field(result.loc, value.loc, ctx);
    return result;
  }
  static org::sem::Newline from_immer(org::imm::ImmNewline const& value, ImmAstContext const& ctx) {
    org::sem::Newline result = hstd::SerdeDefaultProvider<org::sem::Newline>::get();
    assign_sem_field(result.text, value.text, ctx);
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    assign_sem_field(result.loc, value.loc, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<org::sem::Space, org::imm::ImmSpace> {
  static org::imm::ImmSpace to_immer(org::sem::Space const& value, ImmAstEditContext& ctx) {
    org::imm::ImmSpace result = hstd::SerdeDefaultProvider<org::imm::ImmSpace>::get();
    assign_immer_field(result.text, value.text, ctx);
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    assign_immer_field(result.loc, value.loc, ctx);
    return result;
  }
  static org::sem::Space from_immer(org::imm::ImmSpace const& value, ImmAstContext const& ctx) {
    org::sem::Space result = hstd::SerdeDefaultProvider<org::sem::Space>::get();
    assign_sem_field(result.text, value.text, ctx);
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    assign_sem_field(result.loc, value.loc, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<org::sem::Word, org::imm::ImmWord> {
  static org::imm::ImmWord to_immer(org::sem::Word const& value, ImmAstEditContext& ctx) {
    org::imm::ImmWord result = hstd::SerdeDefaultProvider<org::imm::ImmWord>::get();
    assign_immer_field(result.text, value.text, ctx);
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    assign_immer_field(result.loc, value.loc, ctx);
    return result;
  }
  static org::sem::Word from_immer(org::imm::ImmWord const& value, ImmAstContext const& ctx) {
    org::sem::Word result = hstd::SerdeDefaultProvider<org::sem::Word>::get();
    assign_sem_field(result.text, value.text, ctx);
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    assign_sem_field(result.loc, value.loc, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<org::sem::AtMention, org::imm::ImmAtMention> {
  static org::imm::ImmAtMention to_immer(org::sem::AtMention const& value, ImmAstEditContext& ctx) {
    org::imm::ImmAtMention result = hstd::SerdeDefaultProvider<org::imm::ImmAtMention>::get();
    assign_immer_field(result.text, value.text, ctx);
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    assign_immer_field(result.loc, value.loc, ctx);
    return result;
  }
  static org::sem::AtMention from_immer(org::imm::ImmAtMention const& value, ImmAstContext const& ctx) {
    org::sem::AtMention result = hstd::SerdeDefaultProvider<org::sem::AtMention>::get();
    assign_sem_field(result.text, value.text, ctx);
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    assign_sem_field(result.loc, value.loc, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<org::sem::RawText, org::imm::ImmRawText> {
  static org::imm::ImmRawText to_immer(org::sem::RawText const& value, ImmAstEditContext& ctx) {
    org::imm::ImmRawText result = hstd::SerdeDefaultProvider<org::imm::ImmRawText>::get();
    assign_immer_field(result.text, value.text, ctx);
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    assign_immer_field(result.loc, value.loc, ctx);
    return result;
  }
  static org::sem::RawText from_immer(org::imm::ImmRawText const& value, ImmAstContext const& ctx) {
    org::sem::RawText result = hstd::SerdeDefaultProvider<org::sem::RawText>::get();
    assign_sem_field(result.text, value.text, ctx);
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    assign_sem_field(result.loc, value.loc, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<org::sem::Punctuation, org::imm::ImmPunctuation> {
  static org::imm::ImmPunctuation to_immer(org::sem::Punctuation const& value, ImmAstEditContext& ctx) {
    org::imm::ImmPunctuation result = hstd::SerdeDefaultProvider<org::imm::ImmPunctuation>::get();
    assign_immer_field(result.text, value.text, ctx);
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    assign_immer_field(result.loc, value.loc, ctx);
    return result;
  }
  static org::sem::Punctuation from_immer(org::imm::ImmPunctuation const& value, ImmAstContext const& ctx) {
    org::sem::Punctuation result = hstd::SerdeDefaultProvider<org::sem::Punctuation>::get();
    assign_sem_field(result.text, value.text, ctx);
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    assign_sem_field(result.loc, value.loc, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<org::sem::Placeholder, org::imm::ImmPlaceholder> {
  static org::imm::ImmPlaceholder to_immer(org::sem::Placeholder const& value, ImmAstEditContext& ctx) {
    org::imm::ImmPlaceholder result = hstd::SerdeDefaultProvider<org::imm::ImmPlaceholder>::get();
    assign_immer_field(result.text, value.text, ctx);
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    assign_immer_field(result.loc, value.loc, ctx);
    return result;
  }
  static org::sem::Placeholder from_immer(org::imm::ImmPlaceholder const& value, ImmAstContext const& ctx) {
    org::sem::Placeholder result = hstd::SerdeDefaultProvider<org::sem::Placeholder>::get();
    assign_sem_field(result.text, value.text, ctx);
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    assign_sem_field(result.loc, value.loc, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<org::sem::BigIdent, org::imm::ImmBigIdent> {
  static org::imm::ImmBigIdent to_immer(org::sem::BigIdent const& value, ImmAstEditContext& ctx) {
    org::imm::ImmBigIdent result = hstd::SerdeDefaultProvider<org::imm::ImmBigIdent>::get();
    assign_immer_field(result.text, value.text, ctx);
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    assign_immer_field(result.loc, value.loc, ctx);
    return result;
  }
  static org::sem::BigIdent from_immer(org::imm::ImmBigIdent const& value, ImmAstContext const& ctx) {
    org::sem::BigIdent result = hstd::SerdeDefaultProvider<org::sem::BigIdent>::get();
    assign_sem_field(result.text, value.text, ctx);
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    assign_sem_field(result.loc, value.loc, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<org::sem::TextTarget, org::imm::ImmTextTarget> {
  static org::imm::ImmTextTarget to_immer(org::sem::TextTarget const& value, ImmAstEditContext& ctx) {
    org::imm::ImmTextTarget result = hstd::SerdeDefaultProvider<org::imm::ImmTextTarget>::get();
    assign_immer_field(result.text, value.text, ctx);
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    assign_immer_field(result.loc, value.loc, ctx);
    return result;
  }
  static org::sem::TextTarget from_immer(org::imm::ImmTextTarget const& value, ImmAstContext const& ctx) {
    org::sem::TextTarget result = hstd::SerdeDefaultProvider<org::sem::TextTarget>::get();
    assign_sem_field(result.text, value.text, ctx);
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    assign_sem_field(result.loc, value.loc, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<org::sem::Bold, org::imm::ImmBold> {
  static org::imm::ImmBold to_immer(org::sem::Bold const& value, ImmAstEditContext& ctx) {
    org::imm::ImmBold result = hstd::SerdeDefaultProvider<org::imm::ImmBold>::get();
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    assign_immer_field(result.loc, value.loc, ctx);
    return result;
  }
  static org::sem::Bold from_immer(org::imm::ImmBold const& value, ImmAstContext const& ctx) {
    org::sem::Bold result = hstd::SerdeDefaultProvider<org::sem::Bold>::get();
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    assign_sem_field(result.loc, value.loc, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<org::sem::Underline, org::imm::ImmUnderline> {
  static org::imm::ImmUnderline to_immer(org::sem::Underline const& value, ImmAstEditContext& ctx) {
    org::imm::ImmUnderline result = hstd::SerdeDefaultProvider<org::imm::ImmUnderline>::get();
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    assign_immer_field(result.loc, value.loc, ctx);
    return result;
  }
  static org::sem::Underline from_immer(org::imm::ImmUnderline const& value, ImmAstContext const& ctx) {
    org::sem::Underline result = hstd::SerdeDefaultProvider<org::sem::Underline>::get();
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    assign_sem_field(result.loc, value.loc, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<org::sem::Monospace, org::imm::ImmMonospace> {
  static org::imm::ImmMonospace to_immer(org::sem::Monospace const& value, ImmAstEditContext& ctx) {
    org::imm::ImmMonospace result = hstd::SerdeDefaultProvider<org::imm::ImmMonospace>::get();
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    assign_immer_field(result.loc, value.loc, ctx);
    return result;
  }
  static org::sem::Monospace from_immer(org::imm::ImmMonospace const& value, ImmAstContext const& ctx) {
    org::sem::Monospace result = hstd::SerdeDefaultProvider<org::sem::Monospace>::get();
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    assign_sem_field(result.loc, value.loc, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<org::sem::MarkQuote, org::imm::ImmMarkQuote> {
  static org::imm::ImmMarkQuote to_immer(org::sem::MarkQuote const& value, ImmAstEditContext& ctx) {
    org::imm::ImmMarkQuote result = hstd::SerdeDefaultProvider<org::imm::ImmMarkQuote>::get();
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    assign_immer_field(result.loc, value.loc, ctx);
    return result;
  }
  static org::sem::MarkQuote from_immer(org::imm::ImmMarkQuote const& value, ImmAstContext const& ctx) {
    org::sem::MarkQuote result = hstd::SerdeDefaultProvider<org::sem::MarkQuote>::get();
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    assign_sem_field(result.loc, value.loc, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<org::sem::Verbatim, org::imm::ImmVerbatim> {
  static org::imm::ImmVerbatim to_immer(org::sem::Verbatim const& value, ImmAstEditContext& ctx) {
    org::imm::ImmVerbatim result = hstd::SerdeDefaultProvider<org::imm::ImmVerbatim>::get();
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    assign_immer_field(result.loc, value.loc, ctx);
    return result;
  }
  static org::sem::Verbatim from_immer(org::imm::ImmVerbatim const& value, ImmAstContext const& ctx) {
    org::sem::Verbatim result = hstd::SerdeDefaultProvider<org::sem::Verbatim>::get();
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    assign_sem_field(result.loc, value.loc, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<org::sem::Italic, org::imm::ImmItalic> {
  static org::imm::ImmItalic to_immer(org::sem::Italic const& value, ImmAstEditContext& ctx) {
    org::imm::ImmItalic result = hstd::SerdeDefaultProvider<org::imm::ImmItalic>::get();
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    assign_immer_field(result.loc, value.loc, ctx);
    return result;
  }
  static org::sem::Italic from_immer(org::imm::ImmItalic const& value, ImmAstContext const& ctx) {
    org::sem::Italic result = hstd::SerdeDefaultProvider<org::sem::Italic>::get();
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    assign_sem_field(result.loc, value.loc, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<org::sem::Strike, org::imm::ImmStrike> {
  static org::imm::ImmStrike to_immer(org::sem::Strike const& value, ImmAstEditContext& ctx) {
    org::imm::ImmStrike result = hstd::SerdeDefaultProvider<org::imm::ImmStrike>::get();
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    assign_immer_field(result.loc, value.loc, ctx);
    return result;
  }
  static org::sem::Strike from_immer(org::imm::ImmStrike const& value, ImmAstContext const& ctx) {
    org::sem::Strike result = hstd::SerdeDefaultProvider<org::sem::Strike>::get();
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    assign_sem_field(result.loc, value.loc, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<org::sem::Par, org::imm::ImmPar> {
  static org::imm::ImmPar to_immer(org::sem::Par const& value, ImmAstEditContext& ctx) {
    org::imm::ImmPar result = hstd::SerdeDefaultProvider<org::imm::ImmPar>::get();
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    assign_immer_field(result.loc, value.loc, ctx);
    return result;
  }
  static org::sem::Par from_immer(org::imm::ImmPar const& value, ImmAstContext const& ctx) {
    org::sem::Par result = hstd::SerdeDefaultProvider<org::sem::Par>::get();
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    assign_sem_field(result.loc, value.loc, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<org::sem::RadioTarget, org::imm::ImmRadioTarget> {
  static org::imm::ImmRadioTarget to_immer(org::sem::RadioTarget const& value, ImmAstEditContext& ctx) {
    org::imm::ImmRadioTarget result = hstd::SerdeDefaultProvider<org::imm::ImmRadioTarget>::get();
    assign_immer_field(result.words, value.words, ctx);
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    assign_immer_field(result.loc, value.loc, ctx);
    return result;
  }
  static org::sem::RadioTarget from_immer(org::imm::ImmRadioTarget const& value, ImmAstContext const& ctx) {
    org::sem::RadioTarget result = hstd::SerdeDefaultProvider<org::sem::RadioTarget>::get();
    assign_sem_field(result.words, value.words, ctx);
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    assign_sem_field(result.loc, value.loc, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<org::sem::Latex, org::imm::ImmLatex> {
  static org::imm::ImmLatex to_immer(org::sem::Latex const& value, ImmAstEditContext& ctx) {
    org::imm::ImmLatex result = hstd::SerdeDefaultProvider<org::imm::ImmLatex>::get();
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    assign_immer_field(result.loc, value.loc, ctx);
    return result;
  }
  static org::sem::Latex from_immer(org::imm::ImmLatex const& value, ImmAstContext const& ctx) {
    org::sem::Latex result = hstd::SerdeDefaultProvider<org::sem::Latex>::get();
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    assign_sem_field(result.loc, value.loc, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<org::sem::Link, org::imm::ImmLink> {
  static org::imm::ImmLink to_immer(org::sem::Link const& value, ImmAstEditContext& ctx) {
    org::imm::ImmLink result = hstd::SerdeDefaultProvider<org::imm::ImmLink>::get();
    assign_immer_field(result.description, value.description, ctx);
    assign_immer_field(result.target, value.target, ctx);
    assign_immer_field(result.attached, value.attached, ctx);
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    assign_immer_field(result.loc, value.loc, ctx);
    return result;
  }
  static org::sem::Link from_immer(org::imm::ImmLink const& value, ImmAstContext const& ctx) {
    org::sem::Link result = hstd::SerdeDefaultProvider<org::sem::Link>::get();
    assign_sem_field(result.description, value.description, ctx);
    assign_sem_field(result.target, value.target, ctx);
    assign_sem_field(result.attached, value.attached, ctx);
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    assign_sem_field(result.loc, value.loc, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<org::sem::BlockCenter, org::imm::ImmBlockCenter> {
  static org::imm::ImmBlockCenter to_immer(org::sem::BlockCenter const& value, ImmAstEditContext& ctx) {
    org::imm::ImmBlockCenter result = hstd::SerdeDefaultProvider<org::imm::ImmBlockCenter>::get();
    assign_immer_field(result.attrs, value.attrs, ctx);
    assign_immer_field(result.attached, value.attached, ctx);
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    assign_immer_field(result.loc, value.loc, ctx);
    return result;
  }
  static org::sem::BlockCenter from_immer(org::imm::ImmBlockCenter const& value, ImmAstContext const& ctx) {
    org::sem::BlockCenter result = hstd::SerdeDefaultProvider<org::sem::BlockCenter>::get();
    assign_sem_field(result.attrs, value.attrs, ctx);
    assign_sem_field(result.attached, value.attached, ctx);
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    assign_sem_field(result.loc, value.loc, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<org::sem::BlockQuote, org::imm::ImmBlockQuote> {
  static org::imm::ImmBlockQuote to_immer(org::sem::BlockQuote const& value, ImmAstEditContext& ctx) {
    org::imm::ImmBlockQuote result = hstd::SerdeDefaultProvider<org::imm::ImmBlockQuote>::get();
    assign_immer_field(result.attrs, value.attrs, ctx);
    assign_immer_field(result.attached, value.attached, ctx);
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    assign_immer_field(result.loc, value.loc, ctx);
    return result;
  }
  static org::sem::BlockQuote from_immer(org::imm::ImmBlockQuote const& value, ImmAstContext const& ctx) {
    org::sem::BlockQuote result = hstd::SerdeDefaultProvider<org::sem::BlockQuote>::get();
    assign_sem_field(result.attrs, value.attrs, ctx);
    assign_sem_field(result.attached, value.attached, ctx);
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    assign_sem_field(result.loc, value.loc, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<org::sem::BlockComment, org::imm::ImmBlockComment> {
  static org::imm::ImmBlockComment to_immer(org::sem::BlockComment const& value, ImmAstEditContext& ctx) {
    org::imm::ImmBlockComment result = hstd::SerdeDefaultProvider<org::imm::ImmBlockComment>::get();
    assign_immer_field(result.attached, value.attached, ctx);
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    assign_immer_field(result.loc, value.loc, ctx);
    return result;
  }
  static org::sem::BlockComment from_immer(org::imm::ImmBlockComment const& value, ImmAstContext const& ctx) {
    org::sem::BlockComment result = hstd::SerdeDefaultProvider<org::sem::BlockComment>::get();
    assign_sem_field(result.attached, value.attached, ctx);
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    assign_sem_field(result.loc, value.loc, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<org::sem::BlockVerse, org::imm::ImmBlockVerse> {
  static org::imm::ImmBlockVerse to_immer(org::sem::BlockVerse const& value, ImmAstEditContext& ctx) {
    org::imm::ImmBlockVerse result = hstd::SerdeDefaultProvider<org::imm::ImmBlockVerse>::get();
    assign_immer_field(result.attrs, value.attrs, ctx);
    assign_immer_field(result.attached, value.attached, ctx);
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    assign_immer_field(result.loc, value.loc, ctx);
    return result;
  }
  static org::sem::BlockVerse from_immer(org::imm::ImmBlockVerse const& value, ImmAstContext const& ctx) {
    org::sem::BlockVerse result = hstd::SerdeDefaultProvider<org::sem::BlockVerse>::get();
    assign_sem_field(result.attrs, value.attrs, ctx);
    assign_sem_field(result.attached, value.attached, ctx);
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    assign_sem_field(result.loc, value.loc, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<org::sem::BlockDynamicFallback, org::imm::ImmBlockDynamicFallback> {
  static org::imm::ImmBlockDynamicFallback to_immer(org::sem::BlockDynamicFallback const& value, ImmAstEditContext& ctx) {
    org::imm::ImmBlockDynamicFallback result = hstd::SerdeDefaultProvider<org::imm::ImmBlockDynamicFallback>::get();
    assign_immer_field(result.name, value.name, ctx);
    assign_immer_field(result.attrs, value.attrs, ctx);
    assign_immer_field(result.attached, value.attached, ctx);
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    assign_immer_field(result.loc, value.loc, ctx);
    return result;
  }
  static org::sem::BlockDynamicFallback from_immer(org::imm::ImmBlockDynamicFallback const& value, ImmAstContext const& ctx) {
    org::sem::BlockDynamicFallback result = hstd::SerdeDefaultProvider<org::sem::BlockDynamicFallback>::get();
    assign_sem_field(result.name, value.name, ctx);
    assign_sem_field(result.attrs, value.attrs, ctx);
    assign_sem_field(result.attached, value.attached, ctx);
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    assign_sem_field(result.loc, value.loc, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<org::sem::BlockExample, org::imm::ImmBlockExample> {
  static org::imm::ImmBlockExample to_immer(org::sem::BlockExample const& value, ImmAstEditContext& ctx) {
    org::imm::ImmBlockExample result = hstd::SerdeDefaultProvider<org::imm::ImmBlockExample>::get();
    assign_immer_field(result.attrs, value.attrs, ctx);
    assign_immer_field(result.attached, value.attached, ctx);
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    assign_immer_field(result.loc, value.loc, ctx);
    return result;
  }
  static org::sem::BlockExample from_immer(org::imm::ImmBlockExample const& value, ImmAstContext const& ctx) {
    org::sem::BlockExample result = hstd::SerdeDefaultProvider<org::sem::BlockExample>::get();
    assign_sem_field(result.attrs, value.attrs, ctx);
    assign_sem_field(result.attached, value.attached, ctx);
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    assign_sem_field(result.loc, value.loc, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<org::sem::BlockExport, org::imm::ImmBlockExport> {
  static org::imm::ImmBlockExport to_immer(org::sem::BlockExport const& value, ImmAstEditContext& ctx) {
    org::imm::ImmBlockExport result = hstd::SerdeDefaultProvider<org::imm::ImmBlockExport>::get();
    assign_immer_field(result.exporter, value.exporter, ctx);
    assign_immer_field(result.content, value.content, ctx);
    assign_immer_field(result.attrs, value.attrs, ctx);
    assign_immer_field(result.attached, value.attached, ctx);
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    assign_immer_field(result.loc, value.loc, ctx);
    return result;
  }
  static org::sem::BlockExport from_immer(org::imm::ImmBlockExport const& value, ImmAstContext const& ctx) {
    org::sem::BlockExport result = hstd::SerdeDefaultProvider<org::sem::BlockExport>::get();
    assign_sem_field(result.exporter, value.exporter, ctx);
    assign_sem_field(result.content, value.content, ctx);
    assign_sem_field(result.attrs, value.attrs, ctx);
    assign_sem_field(result.attached, value.attached, ctx);
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    assign_sem_field(result.loc, value.loc, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<org::sem::BlockAdmonition, org::imm::ImmBlockAdmonition> {
  static org::imm::ImmBlockAdmonition to_immer(org::sem::BlockAdmonition const& value, ImmAstEditContext& ctx) {
    org::imm::ImmBlockAdmonition result = hstd::SerdeDefaultProvider<org::imm::ImmBlockAdmonition>::get();
    assign_immer_field(result.attrs, value.attrs, ctx);
    assign_immer_field(result.attached, value.attached, ctx);
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    assign_immer_field(result.loc, value.loc, ctx);
    return result;
  }
  static org::sem::BlockAdmonition from_immer(org::imm::ImmBlockAdmonition const& value, ImmAstContext const& ctx) {
    org::sem::BlockAdmonition result = hstd::SerdeDefaultProvider<org::sem::BlockAdmonition>::get();
    assign_sem_field(result.attrs, value.attrs, ctx);
    assign_sem_field(result.attached, value.attached, ctx);
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    assign_sem_field(result.loc, value.loc, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<org::sem::BlockCodeEvalResult, org::imm::ImmBlockCodeEvalResult> {
  static org::imm::ImmBlockCodeEvalResult to_immer(org::sem::BlockCodeEvalResult const& value, ImmAstEditContext& ctx) {
    org::imm::ImmBlockCodeEvalResult result = hstd::SerdeDefaultProvider<org::imm::ImmBlockCodeEvalResult>::get();
    assign_immer_field(result.raw, value.raw, ctx);
    assign_immer_field(result.node, value.node, ctx);
    assign_immer_field(result.attrs, value.attrs, ctx);
    assign_immer_field(result.attached, value.attached, ctx);
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    assign_immer_field(result.loc, value.loc, ctx);
    return result;
  }
  static org::sem::BlockCodeEvalResult from_immer(org::imm::ImmBlockCodeEvalResult const& value, ImmAstContext const& ctx) {
    org::sem::BlockCodeEvalResult result = hstd::SerdeDefaultProvider<org::sem::BlockCodeEvalResult>::get();
    assign_sem_field(result.raw, value.raw, ctx);
    assign_sem_field(result.node, value.node, ctx);
    assign_sem_field(result.attrs, value.attrs, ctx);
    assign_sem_field(result.attached, value.attached, ctx);
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    assign_sem_field(result.loc, value.loc, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<org::sem::BlockCode, org::imm::ImmBlockCode> {
  static org::imm::ImmBlockCode to_immer(org::sem::BlockCode const& value, ImmAstEditContext& ctx) {
    org::imm::ImmBlockCode result = hstd::SerdeDefaultProvider<org::imm::ImmBlockCode>::get();
    assign_immer_field(result.lang, value.lang, ctx);
    assign_immer_field(result.exports, value.exports, ctx);
    assign_immer_field(result.result, value.result, ctx);
    assign_immer_field(result.lines, value.lines, ctx);
    assign_immer_field(result.cache, value.cache, ctx);
    assign_immer_field(result.eval, value.eval, ctx);
    assign_immer_field(result.noweb, value.noweb, ctx);
    assign_immer_field(result.hlines, value.hlines, ctx);
    assign_immer_field(result.tangle, value.tangle, ctx);
    assign_immer_field(result.executionVars, value.executionVars, ctx);
    assign_immer_field(result.switches, value.switches, ctx);
    assign_immer_field(result.attrs, value.attrs, ctx);
    assign_immer_field(result.attached, value.attached, ctx);
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    assign_immer_field(result.loc, value.loc, ctx);
    return result;
  }
  static org::sem::BlockCode from_immer(org::imm::ImmBlockCode const& value, ImmAstContext const& ctx) {
    org::sem::BlockCode result = hstd::SerdeDefaultProvider<org::sem::BlockCode>::get();
    assign_sem_field(result.lang, value.lang, ctx);
    assign_sem_field(result.exports, value.exports, ctx);
    assign_sem_field(result.result, value.result, ctx);
    assign_sem_field(result.lines, value.lines, ctx);
    assign_sem_field(result.cache, value.cache, ctx);
    assign_sem_field(result.eval, value.eval, ctx);
    assign_sem_field(result.noweb, value.noweb, ctx);
    assign_sem_field(result.hlines, value.hlines, ctx);
    assign_sem_field(result.tangle, value.tangle, ctx);
    assign_sem_field(result.executionVars, value.executionVars, ctx);
    assign_sem_field(result.switches, value.switches, ctx);
    assign_sem_field(result.attrs, value.attrs, ctx);
    assign_sem_field(result.attached, value.attached, ctx);
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    assign_sem_field(result.loc, value.loc, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<org::sem::SubtreeLog, org::imm::ImmSubtreeLog> {
  static org::imm::ImmSubtreeLog to_immer(org::sem::SubtreeLog const& value, ImmAstEditContext& ctx) {
    org::imm::ImmSubtreeLog result = hstd::SerdeDefaultProvider<org::imm::ImmSubtreeLog>::get();
    assign_immer_field(result.head, value.head, ctx);
    assign_immer_field(result.desc, value.desc, ctx);
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    assign_immer_field(result.loc, value.loc, ctx);
    return result;
  }
  static org::sem::SubtreeLog from_immer(org::imm::ImmSubtreeLog const& value, ImmAstContext const& ctx) {
    org::sem::SubtreeLog result = hstd::SerdeDefaultProvider<org::sem::SubtreeLog>::get();
    assign_sem_field(result.head, value.head, ctx);
    assign_sem_field(result.desc, value.desc, ctx);
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    assign_sem_field(result.loc, value.loc, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<org::sem::Subtree, org::imm::ImmSubtree> {
  static org::imm::ImmSubtree to_immer(org::sem::Subtree const& value, ImmAstEditContext& ctx) {
    org::imm::ImmSubtree result = hstd::SerdeDefaultProvider<org::imm::ImmSubtree>::get();
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
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    assign_immer_field(result.loc, value.loc, ctx);
    return result;
  }
  static org::sem::Subtree from_immer(org::imm::ImmSubtree const& value, ImmAstContext const& ctx) {
    org::sem::Subtree result = hstd::SerdeDefaultProvider<org::sem::Subtree>::get();
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
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    assign_sem_field(result.loc, value.loc, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<org::sem::Cell, org::imm::ImmCell> {
  static org::imm::ImmCell to_immer(org::sem::Cell const& value, ImmAstEditContext& ctx) {
    org::imm::ImmCell result = hstd::SerdeDefaultProvider<org::imm::ImmCell>::get();
    assign_immer_field(result.isBlock, value.isBlock, ctx);
    assign_immer_field(result.attrs, value.attrs, ctx);
    assign_immer_field(result.attached, value.attached, ctx);
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    assign_immer_field(result.loc, value.loc, ctx);
    return result;
  }
  static org::sem::Cell from_immer(org::imm::ImmCell const& value, ImmAstContext const& ctx) {
    org::sem::Cell result = hstd::SerdeDefaultProvider<org::sem::Cell>::get();
    assign_sem_field(result.isBlock, value.isBlock, ctx);
    assign_sem_field(result.attrs, value.attrs, ctx);
    assign_sem_field(result.attached, value.attached, ctx);
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    assign_sem_field(result.loc, value.loc, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<org::sem::Row, org::imm::ImmRow> {
  static org::imm::ImmRow to_immer(org::sem::Row const& value, ImmAstEditContext& ctx) {
    org::imm::ImmRow result = hstd::SerdeDefaultProvider<org::imm::ImmRow>::get();
    assign_immer_field(result.cells, value.cells, ctx);
    assign_immer_field(result.isBlock, value.isBlock, ctx);
    assign_immer_field(result.attrs, value.attrs, ctx);
    assign_immer_field(result.attached, value.attached, ctx);
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    assign_immer_field(result.loc, value.loc, ctx);
    return result;
  }
  static org::sem::Row from_immer(org::imm::ImmRow const& value, ImmAstContext const& ctx) {
    org::sem::Row result = hstd::SerdeDefaultProvider<org::sem::Row>::get();
    assign_sem_field(result.cells, value.cells, ctx);
    assign_sem_field(result.isBlock, value.isBlock, ctx);
    assign_sem_field(result.attrs, value.attrs, ctx);
    assign_sem_field(result.attached, value.attached, ctx);
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    assign_sem_field(result.loc, value.loc, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<org::sem::Table, org::imm::ImmTable> {
  static org::imm::ImmTable to_immer(org::sem::Table const& value, ImmAstEditContext& ctx) {
    org::imm::ImmTable result = hstd::SerdeDefaultProvider<org::imm::ImmTable>::get();
    assign_immer_field(result.rows, value.rows, ctx);
    assign_immer_field(result.isBlock, value.isBlock, ctx);
    assign_immer_field(result.attrs, value.attrs, ctx);
    assign_immer_field(result.attached, value.attached, ctx);
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    assign_immer_field(result.loc, value.loc, ctx);
    return result;
  }
  static org::sem::Table from_immer(org::imm::ImmTable const& value, ImmAstContext const& ctx) {
    org::sem::Table result = hstd::SerdeDefaultProvider<org::sem::Table>::get();
    assign_sem_field(result.rows, value.rows, ctx);
    assign_sem_field(result.isBlock, value.isBlock, ctx);
    assign_sem_field(result.attrs, value.attrs, ctx);
    assign_sem_field(result.attached, value.attached, ctx);
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    assign_sem_field(result.loc, value.loc, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<org::sem::Paragraph, org::imm::ImmParagraph> {
  static org::imm::ImmParagraph to_immer(org::sem::Paragraph const& value, ImmAstEditContext& ctx) {
    org::imm::ImmParagraph result = hstd::SerdeDefaultProvider<org::imm::ImmParagraph>::get();
    assign_immer_field(result.attached, value.attached, ctx);
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    assign_immer_field(result.loc, value.loc, ctx);
    return result;
  }
  static org::sem::Paragraph from_immer(org::imm::ImmParagraph const& value, ImmAstContext const& ctx) {
    org::sem::Paragraph result = hstd::SerdeDefaultProvider<org::sem::Paragraph>::get();
    assign_sem_field(result.attached, value.attached, ctx);
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    assign_sem_field(result.loc, value.loc, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<org::sem::ColonExample, org::imm::ImmColonExample> {
  static org::imm::ImmColonExample to_immer(org::sem::ColonExample const& value, ImmAstEditContext& ctx) {
    org::imm::ImmColonExample result = hstd::SerdeDefaultProvider<org::imm::ImmColonExample>::get();
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    assign_immer_field(result.loc, value.loc, ctx);
    return result;
  }
  static org::sem::ColonExample from_immer(org::imm::ImmColonExample const& value, ImmAstContext const& ctx) {
    org::sem::ColonExample result = hstd::SerdeDefaultProvider<org::sem::ColonExample>::get();
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    assign_sem_field(result.loc, value.loc, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<org::sem::CmdAttr, org::imm::ImmCmdAttr> {
  static org::imm::ImmCmdAttr to_immer(org::sem::CmdAttr const& value, ImmAstEditContext& ctx) {
    org::imm::ImmCmdAttr result = hstd::SerdeDefaultProvider<org::imm::ImmCmdAttr>::get();
    assign_immer_field(result.target, value.target, ctx);
    assign_immer_field(result.attrs, value.attrs, ctx);
    assign_immer_field(result.attached, value.attached, ctx);
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    assign_immer_field(result.loc, value.loc, ctx);
    return result;
  }
  static org::sem::CmdAttr from_immer(org::imm::ImmCmdAttr const& value, ImmAstContext const& ctx) {
    org::sem::CmdAttr result = hstd::SerdeDefaultProvider<org::sem::CmdAttr>::get();
    assign_sem_field(result.target, value.target, ctx);
    assign_sem_field(result.attrs, value.attrs, ctx);
    assign_sem_field(result.attached, value.attached, ctx);
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    assign_sem_field(result.loc, value.loc, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<org::sem::CmdExport, org::imm::ImmCmdExport> {
  static org::imm::ImmCmdExport to_immer(org::sem::CmdExport const& value, ImmAstEditContext& ctx) {
    org::imm::ImmCmdExport result = hstd::SerdeDefaultProvider<org::imm::ImmCmdExport>::get();
    assign_immer_field(result.exporter, value.exporter, ctx);
    assign_immer_field(result.content, value.content, ctx);
    assign_immer_field(result.attrs, value.attrs, ctx);
    assign_immer_field(result.attached, value.attached, ctx);
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    assign_immer_field(result.loc, value.loc, ctx);
    return result;
  }
  static org::sem::CmdExport from_immer(org::imm::ImmCmdExport const& value, ImmAstContext const& ctx) {
    org::sem::CmdExport result = hstd::SerdeDefaultProvider<org::sem::CmdExport>::get();
    assign_sem_field(result.exporter, value.exporter, ctx);
    assign_sem_field(result.content, value.content, ctx);
    assign_sem_field(result.attrs, value.attrs, ctx);
    assign_sem_field(result.attached, value.attached, ctx);
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    assign_sem_field(result.loc, value.loc, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<org::sem::Call, org::imm::ImmCall> {
  static org::imm::ImmCall to_immer(org::sem::Call const& value, ImmAstEditContext& ctx) {
    org::imm::ImmCall result = hstd::SerdeDefaultProvider<org::imm::ImmCall>::get();
    assign_immer_field(result.name, value.name, ctx);
    assign_immer_field(result.attrs, value.attrs, ctx);
    assign_immer_field(result.isCommand, value.isCommand, ctx);
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    assign_immer_field(result.loc, value.loc, ctx);
    return result;
  }
  static org::sem::Call from_immer(org::imm::ImmCall const& value, ImmAstContext const& ctx) {
    org::sem::Call result = hstd::SerdeDefaultProvider<org::sem::Call>::get();
    assign_sem_field(result.name, value.name, ctx);
    assign_sem_field(result.attrs, value.attrs, ctx);
    assign_sem_field(result.isCommand, value.isCommand, ctx);
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    assign_sem_field(result.loc, value.loc, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<org::sem::List, org::imm::ImmList> {
  static org::imm::ImmList to_immer(org::sem::List const& value, ImmAstEditContext& ctx) {
    org::imm::ImmList result = hstd::SerdeDefaultProvider<org::imm::ImmList>::get();
    assign_immer_field(result.attached, value.attached, ctx);
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    assign_immer_field(result.loc, value.loc, ctx);
    return result;
  }
  static org::sem::List from_immer(org::imm::ImmList const& value, ImmAstContext const& ctx) {
    org::sem::List result = hstd::SerdeDefaultProvider<org::sem::List>::get();
    assign_sem_field(result.attached, value.attached, ctx);
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    assign_sem_field(result.loc, value.loc, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<org::sem::ListItem, org::imm::ImmListItem> {
  static org::imm::ImmListItem to_immer(org::sem::ListItem const& value, ImmAstEditContext& ctx) {
    org::imm::ImmListItem result = hstd::SerdeDefaultProvider<org::imm::ImmListItem>::get();
    assign_immer_field(result.checkbox, value.checkbox, ctx);
    assign_immer_field(result.header, value.header, ctx);
    assign_immer_field(result.bullet, value.bullet, ctx);
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    assign_immer_field(result.loc, value.loc, ctx);
    return result;
  }
  static org::sem::ListItem from_immer(org::imm::ImmListItem const& value, ImmAstContext const& ctx) {
    org::sem::ListItem result = hstd::SerdeDefaultProvider<org::sem::ListItem>::get();
    assign_sem_field(result.checkbox, value.checkbox, ctx);
    assign_sem_field(result.header, value.header, ctx);
    assign_sem_field(result.bullet, value.bullet, ctx);
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    assign_sem_field(result.loc, value.loc, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<org::sem::DocumentOptions, org::imm::ImmDocumentOptions> {
  static org::imm::ImmDocumentOptions to_immer(org::sem::DocumentOptions const& value, ImmAstEditContext& ctx) {
    org::imm::ImmDocumentOptions result = hstd::SerdeDefaultProvider<org::imm::ImmDocumentOptions>::get();
    assign_immer_field(result.initialVisibility, value.initialVisibility, ctx);
    assign_immer_field(result.properties, value.properties, ctx);
    assign_immer_field(result.exportConfig, value.exportConfig, ctx);
    assign_immer_field(result.fixedWidthSections, value.fixedWidthSections, ctx);
    assign_immer_field(result.startupIndented, value.startupIndented, ctx);
    assign_immer_field(result.category, value.category, ctx);
    assign_immer_field(result.setupfile, value.setupfile, ctx);
    assign_immer_field(result.maxSubtreeLevelExport, value.maxSubtreeLevelExport, ctx);
    assign_immer_field(result.columns, value.columns, ctx);
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    assign_immer_field(result.loc, value.loc, ctx);
    return result;
  }
  static org::sem::DocumentOptions from_immer(org::imm::ImmDocumentOptions const& value, ImmAstContext const& ctx) {
    org::sem::DocumentOptions result = hstd::SerdeDefaultProvider<org::sem::DocumentOptions>::get();
    assign_sem_field(result.initialVisibility, value.initialVisibility, ctx);
    assign_sem_field(result.properties, value.properties, ctx);
    assign_sem_field(result.exportConfig, value.exportConfig, ctx);
    assign_sem_field(result.fixedWidthSections, value.fixedWidthSections, ctx);
    assign_sem_field(result.startupIndented, value.startupIndented, ctx);
    assign_sem_field(result.category, value.category, ctx);
    assign_sem_field(result.setupfile, value.setupfile, ctx);
    assign_sem_field(result.maxSubtreeLevelExport, value.maxSubtreeLevelExport, ctx);
    assign_sem_field(result.columns, value.columns, ctx);
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    assign_sem_field(result.loc, value.loc, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<org::sem::Document, org::imm::ImmDocument> {
  static org::imm::ImmDocument to_immer(org::sem::Document const& value, ImmAstEditContext& ctx) {
    org::imm::ImmDocument result = hstd::SerdeDefaultProvider<org::imm::ImmDocument>::get();
    assign_immer_field(result.title, value.title, ctx);
    assign_immer_field(result.author, value.author, ctx);
    assign_immer_field(result.creator, value.creator, ctx);
    assign_immer_field(result.filetags, value.filetags, ctx);
    assign_immer_field(result.email, value.email, ctx);
    assign_immer_field(result.language, value.language, ctx);
    assign_immer_field(result.options, value.options, ctx);
    assign_immer_field(result.exportFileName, value.exportFileName, ctx);
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    assign_immer_field(result.loc, value.loc, ctx);
    return result;
  }
  static org::sem::Document from_immer(org::imm::ImmDocument const& value, ImmAstContext const& ctx) {
    org::sem::Document result = hstd::SerdeDefaultProvider<org::sem::Document>::get();
    assign_sem_field(result.title, value.title, ctx);
    assign_sem_field(result.author, value.author, ctx);
    assign_sem_field(result.creator, value.creator, ctx);
    assign_sem_field(result.filetags, value.filetags, ctx);
    assign_sem_field(result.email, value.email, ctx);
    assign_sem_field(result.language, value.language, ctx);
    assign_sem_field(result.options, value.options, ctx);
    assign_sem_field(result.exportFileName, value.exportFileName, ctx);
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    assign_sem_field(result.loc, value.loc, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<org::sem::FileTarget, org::imm::ImmFileTarget> {
  static org::imm::ImmFileTarget to_immer(org::sem::FileTarget const& value, ImmAstEditContext& ctx) {
    org::imm::ImmFileTarget result = hstd::SerdeDefaultProvider<org::imm::ImmFileTarget>::get();
    assign_immer_field(result.path, value.path, ctx);
    assign_immer_field(result.line, value.line, ctx);
    assign_immer_field(result.searchTarget, value.searchTarget, ctx);
    assign_immer_field(result.restrictToHeadlines, value.restrictToHeadlines, ctx);
    assign_immer_field(result.targetId, value.targetId, ctx);
    assign_immer_field(result.regexp, value.regexp, ctx);
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    assign_immer_field(result.loc, value.loc, ctx);
    return result;
  }
  static org::sem::FileTarget from_immer(org::imm::ImmFileTarget const& value, ImmAstContext const& ctx) {
    org::sem::FileTarget result = hstd::SerdeDefaultProvider<org::sem::FileTarget>::get();
    assign_sem_field(result.path, value.path, ctx);
    assign_sem_field(result.line, value.line, ctx);
    assign_sem_field(result.searchTarget, value.searchTarget, ctx);
    assign_sem_field(result.restrictToHeadlines, value.restrictToHeadlines, ctx);
    assign_sem_field(result.targetId, value.targetId, ctx);
    assign_sem_field(result.regexp, value.regexp, ctx);
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    assign_sem_field(result.loc, value.loc, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<org::sem::TextSeparator, org::imm::ImmTextSeparator> {
  static org::imm::ImmTextSeparator to_immer(org::sem::TextSeparator const& value, ImmAstEditContext& ctx) {
    org::imm::ImmTextSeparator result = hstd::SerdeDefaultProvider<org::imm::ImmTextSeparator>::get();
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    assign_immer_field(result.loc, value.loc, ctx);
    return result;
  }
  static org::sem::TextSeparator from_immer(org::imm::ImmTextSeparator const& value, ImmAstContext const& ctx) {
    org::sem::TextSeparator result = hstd::SerdeDefaultProvider<org::sem::TextSeparator>::get();
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    assign_sem_field(result.loc, value.loc, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<org::sem::DocumentGroup, org::imm::ImmDocumentGroup> {
  static org::imm::ImmDocumentGroup to_immer(org::sem::DocumentGroup const& value, ImmAstEditContext& ctx) {
    org::imm::ImmDocumentGroup result = hstd::SerdeDefaultProvider<org::imm::ImmDocumentGroup>::get();
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    assign_immer_field(result.loc, value.loc, ctx);
    return result;
  }
  static org::sem::DocumentGroup from_immer(org::imm::ImmDocumentGroup const& value, ImmAstContext const& ctx) {
    org::sem::DocumentGroup result = hstd::SerdeDefaultProvider<org::sem::DocumentGroup>::get();
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    assign_sem_field(result.loc, value.loc, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<org::sem::File, org::imm::ImmFile> {
  static org::imm::ImmFile to_immer(org::sem::File const& value, ImmAstEditContext& ctx) {
    org::imm::ImmFile result = hstd::SerdeDefaultProvider<org::imm::ImmFile>::get();
    assign_immer_field(result.relPath, value.relPath, ctx);
    assign_immer_field(result.absPath, value.absPath, ctx);
    assign_immer_field(result.data, value.data, ctx);
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    assign_immer_field(result.loc, value.loc, ctx);
    return result;
  }
  static org::sem::File from_immer(org::imm::ImmFile const& value, ImmAstContext const& ctx) {
    org::sem::File result = hstd::SerdeDefaultProvider<org::sem::File>::get();
    assign_sem_field(result.relPath, value.relPath, ctx);
    assign_sem_field(result.absPath, value.absPath, ctx);
    assign_sem_field(result.data, value.data, ctx);
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    assign_sem_field(result.loc, value.loc, ctx);
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
struct ImmSemSerde<org::sem::Directory, org::imm::ImmDirectory> {
  static org::imm::ImmDirectory to_immer(org::sem::Directory const& value, ImmAstEditContext& ctx) {
    org::imm::ImmDirectory result = hstd::SerdeDefaultProvider<org::imm::ImmDirectory>::get();
    assign_immer_field(result.relPath, value.relPath, ctx);
    assign_immer_field(result.absPath, value.absPath, ctx);
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    assign_immer_field(result.loc, value.loc, ctx);
    return result;
  }
  static org::sem::Directory from_immer(org::imm::ImmDirectory const& value, ImmAstContext const& ctx) {
    org::sem::Directory result = hstd::SerdeDefaultProvider<org::sem::Directory>::get();
    assign_sem_field(result.relPath, value.relPath, ctx);
    assign_sem_field(result.absPath, value.absPath, ctx);
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    assign_sem_field(result.loc, value.loc, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<org::sem::Symlink, org::imm::ImmSymlink> {
  static org::imm::ImmSymlink to_immer(org::sem::Symlink const& value, ImmAstEditContext& ctx) {
    org::imm::ImmSymlink result = hstd::SerdeDefaultProvider<org::imm::ImmSymlink>::get();
    assign_immer_field(result.isDirectory, value.isDirectory, ctx);
    assign_immer_field(result.absPath, value.absPath, ctx);
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    assign_immer_field(result.loc, value.loc, ctx);
    return result;
  }
  static org::sem::Symlink from_immer(org::imm::ImmSymlink const& value, ImmAstContext const& ctx) {
    org::sem::Symlink result = hstd::SerdeDefaultProvider<org::sem::Symlink>::get();
    assign_sem_field(result.isDirectory, value.isDirectory, ctx);
    assign_sem_field(result.absPath, value.absPath, ctx);
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    assign_sem_field(result.loc, value.loc, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<org::sem::CmdInclude, org::imm::ImmCmdInclude> {
  static org::imm::ImmCmdInclude to_immer(org::sem::CmdInclude const& value, ImmAstEditContext& ctx) {
    org::imm::ImmCmdInclude result = hstd::SerdeDefaultProvider<org::imm::ImmCmdInclude>::get();
    assign_immer_field(result.path, value.path, ctx);
    assign_immer_field(result.firstLine, value.firstLine, ctx);
    assign_immer_field(result.lastLine, value.lastLine, ctx);
    assign_immer_field(result.data, value.data, ctx);
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    assign_immer_field(result.loc, value.loc, ctx);
    return result;
  }
  static org::sem::CmdInclude from_immer(org::imm::ImmCmdInclude const& value, ImmAstContext const& ctx) {
    org::sem::CmdInclude result = hstd::SerdeDefaultProvider<org::sem::CmdInclude>::get();
    assign_sem_field(result.path, value.path, ctx);
    assign_sem_field(result.firstLine, value.firstLine, ctx);
    assign_sem_field(result.lastLine, value.lastLine, ctx);
    assign_sem_field(result.data, value.data, ctx);
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    assign_sem_field(result.loc, value.loc, ctx);
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