/* clang-format off */
template <>
struct ImmSemSerde<sem::None, org::ImmNone> {
  static org::ImmNone to_immer(sem::None const& value, ImmAstEditContext& ctx) {
    org::ImmNone result = SerdeDefaultProvider<org::ImmNone>::get();
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
  static sem::None from_immer(org::ImmNone const& value, ImmAstContext const& ctx) {
    sem::None result = SerdeDefaultProvider<sem::None>::get();
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<sem::ErrorItem, org::ImmErrorItem> {
  static org::ImmErrorItem to_immer(sem::ErrorItem const& value, ImmAstEditContext& ctx) {
    org::ImmErrorItem result = SerdeDefaultProvider<org::ImmErrorItem>::get();
    assign_immer_field(result.message, value.message, ctx);
    assign_immer_field(result.function, value.function, ctx);
    assign_immer_field(result.line, value.line, ctx);
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
  static sem::ErrorItem from_immer(org::ImmErrorItem const& value, ImmAstContext const& ctx) {
    sem::ErrorItem result = SerdeDefaultProvider<sem::ErrorItem>::get();
    assign_sem_field(result.message, value.message, ctx);
    assign_sem_field(result.function, value.function, ctx);
    assign_sem_field(result.line, value.line, ctx);
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<sem::ErrorGroup, org::ImmErrorGroup> {
  static org::ImmErrorGroup to_immer(sem::ErrorGroup const& value, ImmAstEditContext& ctx) {
    org::ImmErrorGroup result = SerdeDefaultProvider<org::ImmErrorGroup>::get();
    assign_immer_field(result.diagnostics, value.diagnostics, ctx);
    assign_immer_field(result.function, value.function, ctx);
    assign_immer_field(result.line, value.line, ctx);
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
  static sem::ErrorGroup from_immer(org::ImmErrorGroup const& value, ImmAstContext const& ctx) {
    sem::ErrorGroup result = SerdeDefaultProvider<sem::ErrorGroup>::get();
    assign_sem_field(result.diagnostics, value.diagnostics, ctx);
    assign_sem_field(result.function, value.function, ctx);
    assign_sem_field(result.line, value.line, ctx);
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<sem::StmtList, org::ImmStmtList> {
  static org::ImmStmtList to_immer(sem::StmtList const& value, ImmAstEditContext& ctx) {
    org::ImmStmtList result = SerdeDefaultProvider<org::ImmStmtList>::get();
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
  static sem::StmtList from_immer(org::ImmStmtList const& value, ImmAstContext const& ctx) {
    sem::StmtList result = SerdeDefaultProvider<sem::StmtList>::get();
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<sem::Empty, org::ImmEmpty> {
  static org::ImmEmpty to_immer(sem::Empty const& value, ImmAstEditContext& ctx) {
    org::ImmEmpty result = SerdeDefaultProvider<org::ImmEmpty>::get();
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
  static sem::Empty from_immer(org::ImmEmpty const& value, ImmAstContext const& ctx) {
    sem::Empty result = SerdeDefaultProvider<sem::Empty>::get();
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<sem::CmdCaption, org::ImmCmdCaption> {
  static org::ImmCmdCaption to_immer(sem::CmdCaption const& value, ImmAstEditContext& ctx) {
    org::ImmCmdCaption result = SerdeDefaultProvider<org::ImmCmdCaption>::get();
    assign_immer_field(result.text, value.text, ctx);
    assign_immer_field(result.attrs, value.attrs, ctx);
    assign_immer_field(result.attached, value.attached, ctx);
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
  static sem::CmdCaption from_immer(org::ImmCmdCaption const& value, ImmAstContext const& ctx) {
    sem::CmdCaption result = SerdeDefaultProvider<sem::CmdCaption>::get();
    assign_sem_field(result.text, value.text, ctx);
    assign_sem_field(result.attrs, value.attrs, ctx);
    assign_sem_field(result.attached, value.attached, ctx);
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<sem::CmdColumns, org::ImmCmdColumns> {
  static org::ImmCmdColumns to_immer(sem::CmdColumns const& value, ImmAstEditContext& ctx) {
    org::ImmCmdColumns result = SerdeDefaultProvider<org::ImmCmdColumns>::get();
    assign_immer_field(result.view, value.view, ctx);
    assign_immer_field(result.attrs, value.attrs, ctx);
    assign_immer_field(result.attached, value.attached, ctx);
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
  static sem::CmdColumns from_immer(org::ImmCmdColumns const& value, ImmAstContext const& ctx) {
    sem::CmdColumns result = SerdeDefaultProvider<sem::CmdColumns>::get();
    assign_sem_field(result.view, value.view, ctx);
    assign_sem_field(result.attrs, value.attrs, ctx);
    assign_sem_field(result.attached, value.attached, ctx);
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<sem::CmdName, org::ImmCmdName> {
  static org::ImmCmdName to_immer(sem::CmdName const& value, ImmAstEditContext& ctx) {
    org::ImmCmdName result = SerdeDefaultProvider<org::ImmCmdName>::get();
    assign_immer_field(result.name, value.name, ctx);
    assign_immer_field(result.attrs, value.attrs, ctx);
    assign_immer_field(result.attached, value.attached, ctx);
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
  static sem::CmdName from_immer(org::ImmCmdName const& value, ImmAstContext const& ctx) {
    sem::CmdName result = SerdeDefaultProvider<sem::CmdName>::get();
    assign_sem_field(result.name, value.name, ctx);
    assign_sem_field(result.attrs, value.attrs, ctx);
    assign_sem_field(result.attached, value.attached, ctx);
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<sem::CmdCustomArgs, org::ImmCmdCustomArgs> {
  static org::ImmCmdCustomArgs to_immer(sem::CmdCustomArgs const& value, ImmAstEditContext& ctx) {
    org::ImmCmdCustomArgs result = SerdeDefaultProvider<org::ImmCmdCustomArgs>::get();
    assign_immer_field(result.name, value.name, ctx);
    assign_immer_field(result.isAttached, value.isAttached, ctx);
    assign_immer_field(result.attrs, value.attrs, ctx);
    assign_immer_field(result.attached, value.attached, ctx);
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
  static sem::CmdCustomArgs from_immer(org::ImmCmdCustomArgs const& value, ImmAstContext const& ctx) {
    sem::CmdCustomArgs result = SerdeDefaultProvider<sem::CmdCustomArgs>::get();
    assign_sem_field(result.name, value.name, ctx);
    assign_sem_field(result.isAttached, value.isAttached, ctx);
    assign_sem_field(result.attrs, value.attrs, ctx);
    assign_sem_field(result.attached, value.attached, ctx);
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<sem::CmdCustomRaw, org::ImmCmdCustomRaw> {
  static org::ImmCmdCustomRaw to_immer(sem::CmdCustomRaw const& value, ImmAstEditContext& ctx) {
    org::ImmCmdCustomRaw result = SerdeDefaultProvider<org::ImmCmdCustomRaw>::get();
    assign_immer_field(result.name, value.name, ctx);
    assign_immer_field(result.isAttached, value.isAttached, ctx);
    assign_immer_field(result.text, value.text, ctx);
    assign_immer_field(result.attached, value.attached, ctx);
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
  static sem::CmdCustomRaw from_immer(org::ImmCmdCustomRaw const& value, ImmAstContext const& ctx) {
    sem::CmdCustomRaw result = SerdeDefaultProvider<sem::CmdCustomRaw>::get();
    assign_sem_field(result.name, value.name, ctx);
    assign_sem_field(result.isAttached, value.isAttached, ctx);
    assign_sem_field(result.text, value.text, ctx);
    assign_sem_field(result.attached, value.attached, ctx);
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<sem::CmdCustomText, org::ImmCmdCustomText> {
  static org::ImmCmdCustomText to_immer(sem::CmdCustomText const& value, ImmAstEditContext& ctx) {
    org::ImmCmdCustomText result = SerdeDefaultProvider<org::ImmCmdCustomText>::get();
    assign_immer_field(result.name, value.name, ctx);
    assign_immer_field(result.isAttached, value.isAttached, ctx);
    assign_immer_field(result.text, value.text, ctx);
    assign_immer_field(result.attached, value.attached, ctx);
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
  static sem::CmdCustomText from_immer(org::ImmCmdCustomText const& value, ImmAstContext const& ctx) {
    sem::CmdCustomText result = SerdeDefaultProvider<sem::CmdCustomText>::get();
    assign_sem_field(result.name, value.name, ctx);
    assign_sem_field(result.isAttached, value.isAttached, ctx);
    assign_sem_field(result.text, value.text, ctx);
    assign_sem_field(result.attached, value.attached, ctx);
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<sem::CmdResults, org::ImmCmdResults> {
  static org::ImmCmdResults to_immer(sem::CmdResults const& value, ImmAstEditContext& ctx) {
    org::ImmCmdResults result = SerdeDefaultProvider<org::ImmCmdResults>::get();
    assign_immer_field(result.attrs, value.attrs, ctx);
    assign_immer_field(result.attached, value.attached, ctx);
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
  static sem::CmdResults from_immer(org::ImmCmdResults const& value, ImmAstContext const& ctx) {
    sem::CmdResults result = SerdeDefaultProvider<sem::CmdResults>::get();
    assign_sem_field(result.attrs, value.attrs, ctx);
    assign_sem_field(result.attached, value.attached, ctx);
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<sem::CmdTblfm, org::ImmCmdTblfm> {
  static org::ImmCmdTblfm to_immer(sem::CmdTblfm const& value, ImmAstEditContext& ctx) {
    org::ImmCmdTblfm result = SerdeDefaultProvider<org::ImmCmdTblfm>::get();
    assign_immer_field(result.expr, value.expr, ctx);
    assign_immer_field(result.attrs, value.attrs, ctx);
    assign_immer_field(result.attached, value.attached, ctx);
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
  static sem::CmdTblfm from_immer(org::ImmCmdTblfm const& value, ImmAstContext const& ctx) {
    sem::CmdTblfm result = SerdeDefaultProvider<sem::CmdTblfm>::get();
    assign_sem_field(result.expr, value.expr, ctx);
    assign_sem_field(result.attrs, value.attrs, ctx);
    assign_sem_field(result.attached, value.attached, ctx);
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<sem::HashTag, org::ImmHashTag> {
  static org::ImmHashTag to_immer(sem::HashTag const& value, ImmAstEditContext& ctx) {
    org::ImmHashTag result = SerdeDefaultProvider<org::ImmHashTag>::get();
    assign_immer_field(result.head, value.head, ctx);
    assign_immer_field(result.subtags, value.subtags, ctx);
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
  static sem::HashTag from_immer(org::ImmHashTag const& value, ImmAstContext const& ctx) {
    sem::HashTag result = SerdeDefaultProvider<sem::HashTag>::get();
    assign_sem_field(result.head, value.head, ctx);
    assign_sem_field(result.subtags, value.subtags, ctx);
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<sem::InlineFootnote, org::ImmInlineFootnote> {
  static org::ImmInlineFootnote to_immer(sem::InlineFootnote const& value, ImmAstEditContext& ctx) {
    org::ImmInlineFootnote result = SerdeDefaultProvider<org::ImmInlineFootnote>::get();
    assign_immer_field(result.tag, value.tag, ctx);
    assign_immer_field(result.definition, value.definition, ctx);
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
  static sem::InlineFootnote from_immer(org::ImmInlineFootnote const& value, ImmAstContext const& ctx) {
    sem::InlineFootnote result = SerdeDefaultProvider<sem::InlineFootnote>::get();
    assign_sem_field(result.tag, value.tag, ctx);
    assign_sem_field(result.definition, value.definition, ctx);
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<sem::Time, org::ImmTime> {
  static org::ImmTime to_immer(sem::Time const& value, ImmAstEditContext& ctx) {
    org::ImmTime result = SerdeDefaultProvider<org::ImmTime>::get();
    assign_immer_field(result.isActive, value.isActive, ctx);
    assign_immer_field(result.time, value.time, ctx);
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
  static sem::Time from_immer(org::ImmTime const& value, ImmAstContext const& ctx) {
    sem::Time result = SerdeDefaultProvider<sem::Time>::get();
    assign_sem_field(result.isActive, value.isActive, ctx);
    assign_sem_field(result.time, value.time, ctx);
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<sem::Time::Repeat, org::ImmTime::Repeat> {
  static org::ImmTime::Repeat to_immer(sem::Time::Repeat const& value, ImmAstEditContext& ctx) {
    org::ImmTime::Repeat result = SerdeDefaultProvider<org::ImmTime::Repeat>::get();
    assign_immer_field(result.mode, value.mode, ctx);
    assign_immer_field(result.period, value.period, ctx);
    assign_immer_field(result.count, value.count, ctx);
    return result;
  }
  static sem::Time::Repeat from_immer(org::ImmTime::Repeat const& value, ImmAstContext const& ctx) {
    sem::Time::Repeat result = SerdeDefaultProvider<sem::Time::Repeat>::get();
    assign_sem_field(result.mode, value.mode, ctx);
    assign_sem_field(result.period, value.period, ctx);
    assign_sem_field(result.count, value.count, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<sem::Time::Static, org::ImmTime::Static> {
  static org::ImmTime::Static to_immer(sem::Time::Static const& value, ImmAstEditContext& ctx) {
    org::ImmTime::Static result = SerdeDefaultProvider<org::ImmTime::Static>::get();
    assign_immer_field(result.repeat, value.repeat, ctx);
    assign_immer_field(result.time, value.time, ctx);
    return result;
  }
  static sem::Time::Static from_immer(org::ImmTime::Static const& value, ImmAstContext const& ctx) {
    sem::Time::Static result = SerdeDefaultProvider<sem::Time::Static>::get();
    assign_sem_field(result.repeat, value.repeat, ctx);
    assign_sem_field(result.time, value.time, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<sem::Time::Dynamic, org::ImmTime::Dynamic> {
  static org::ImmTime::Dynamic to_immer(sem::Time::Dynamic const& value, ImmAstEditContext& ctx) {
    org::ImmTime::Dynamic result = SerdeDefaultProvider<org::ImmTime::Dynamic>::get();
    assign_immer_field(result.expr, value.expr, ctx);
    return result;
  }
  static sem::Time::Dynamic from_immer(org::ImmTime::Dynamic const& value, ImmAstContext const& ctx) {
    sem::Time::Dynamic result = SerdeDefaultProvider<sem::Time::Dynamic>::get();
    assign_sem_field(result.expr, value.expr, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<sem::TimeRange, org::ImmTimeRange> {
  static org::ImmTimeRange to_immer(sem::TimeRange const& value, ImmAstEditContext& ctx) {
    org::ImmTimeRange result = SerdeDefaultProvider<org::ImmTimeRange>::get();
    assign_immer_field(result.from, value.from, ctx);
    assign_immer_field(result.to, value.to, ctx);
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
  static sem::TimeRange from_immer(org::ImmTimeRange const& value, ImmAstContext const& ctx) {
    sem::TimeRange result = SerdeDefaultProvider<sem::TimeRange>::get();
    assign_sem_field(result.from, value.from, ctx);
    assign_sem_field(result.to, value.to, ctx);
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<sem::Macro, org::ImmMacro> {
  static org::ImmMacro to_immer(sem::Macro const& value, ImmAstEditContext& ctx) {
    org::ImmMacro result = SerdeDefaultProvider<org::ImmMacro>::get();
    assign_immer_field(result.name, value.name, ctx);
    assign_immer_field(result.attrs, value.attrs, ctx);
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
  static sem::Macro from_immer(org::ImmMacro const& value, ImmAstContext const& ctx) {
    sem::Macro result = SerdeDefaultProvider<sem::Macro>::get();
    assign_sem_field(result.name, value.name, ctx);
    assign_sem_field(result.attrs, value.attrs, ctx);
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<sem::Symbol, org::ImmSymbol> {
  static org::ImmSymbol to_immer(sem::Symbol const& value, ImmAstEditContext& ctx) {
    org::ImmSymbol result = SerdeDefaultProvider<org::ImmSymbol>::get();
    assign_immer_field(result.name, value.name, ctx);
    assign_immer_field(result.parameters, value.parameters, ctx);
    assign_immer_field(result.positional, value.positional, ctx);
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
  static sem::Symbol from_immer(org::ImmSymbol const& value, ImmAstContext const& ctx) {
    sem::Symbol result = SerdeDefaultProvider<sem::Symbol>::get();
    assign_sem_field(result.name, value.name, ctx);
    assign_sem_field(result.parameters, value.parameters, ctx);
    assign_sem_field(result.positional, value.positional, ctx);
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<sem::Symbol::Param, org::ImmSymbol::Param> {
  static org::ImmSymbol::Param to_immer(sem::Symbol::Param const& value, ImmAstEditContext& ctx) {
    org::ImmSymbol::Param result = SerdeDefaultProvider<org::ImmSymbol::Param>::get();
    assign_immer_field(result.key, value.key, ctx);
    assign_immer_field(result.value, value.value, ctx);
    return result;
  }
  static sem::Symbol::Param from_immer(org::ImmSymbol::Param const& value, ImmAstContext const& ctx) {
    sem::Symbol::Param result = SerdeDefaultProvider<sem::Symbol::Param>::get();
    assign_sem_field(result.key, value.key, ctx);
    assign_sem_field(result.value, value.value, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<sem::Escaped, org::ImmEscaped> {
  static org::ImmEscaped to_immer(sem::Escaped const& value, ImmAstEditContext& ctx) {
    org::ImmEscaped result = SerdeDefaultProvider<org::ImmEscaped>::get();
    assign_immer_field(result.text, value.text, ctx);
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
  static sem::Escaped from_immer(org::ImmEscaped const& value, ImmAstContext const& ctx) {
    sem::Escaped result = SerdeDefaultProvider<sem::Escaped>::get();
    assign_sem_field(result.text, value.text, ctx);
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<sem::Newline, org::ImmNewline> {
  static org::ImmNewline to_immer(sem::Newline const& value, ImmAstEditContext& ctx) {
    org::ImmNewline result = SerdeDefaultProvider<org::ImmNewline>::get();
    assign_immer_field(result.text, value.text, ctx);
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
  static sem::Newline from_immer(org::ImmNewline const& value, ImmAstContext const& ctx) {
    sem::Newline result = SerdeDefaultProvider<sem::Newline>::get();
    assign_sem_field(result.text, value.text, ctx);
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<sem::Space, org::ImmSpace> {
  static org::ImmSpace to_immer(sem::Space const& value, ImmAstEditContext& ctx) {
    org::ImmSpace result = SerdeDefaultProvider<org::ImmSpace>::get();
    assign_immer_field(result.text, value.text, ctx);
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
  static sem::Space from_immer(org::ImmSpace const& value, ImmAstContext const& ctx) {
    sem::Space result = SerdeDefaultProvider<sem::Space>::get();
    assign_sem_field(result.text, value.text, ctx);
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<sem::Word, org::ImmWord> {
  static org::ImmWord to_immer(sem::Word const& value, ImmAstEditContext& ctx) {
    org::ImmWord result = SerdeDefaultProvider<org::ImmWord>::get();
    assign_immer_field(result.text, value.text, ctx);
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
  static sem::Word from_immer(org::ImmWord const& value, ImmAstContext const& ctx) {
    sem::Word result = SerdeDefaultProvider<sem::Word>::get();
    assign_sem_field(result.text, value.text, ctx);
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<sem::AtMention, org::ImmAtMention> {
  static org::ImmAtMention to_immer(sem::AtMention const& value, ImmAstEditContext& ctx) {
    org::ImmAtMention result = SerdeDefaultProvider<org::ImmAtMention>::get();
    assign_immer_field(result.text, value.text, ctx);
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
  static sem::AtMention from_immer(org::ImmAtMention const& value, ImmAstContext const& ctx) {
    sem::AtMention result = SerdeDefaultProvider<sem::AtMention>::get();
    assign_sem_field(result.text, value.text, ctx);
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<sem::RawText, org::ImmRawText> {
  static org::ImmRawText to_immer(sem::RawText const& value, ImmAstEditContext& ctx) {
    org::ImmRawText result = SerdeDefaultProvider<org::ImmRawText>::get();
    assign_immer_field(result.text, value.text, ctx);
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
  static sem::RawText from_immer(org::ImmRawText const& value, ImmAstContext const& ctx) {
    sem::RawText result = SerdeDefaultProvider<sem::RawText>::get();
    assign_sem_field(result.text, value.text, ctx);
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<sem::Punctuation, org::ImmPunctuation> {
  static org::ImmPunctuation to_immer(sem::Punctuation const& value, ImmAstEditContext& ctx) {
    org::ImmPunctuation result = SerdeDefaultProvider<org::ImmPunctuation>::get();
    assign_immer_field(result.text, value.text, ctx);
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
  static sem::Punctuation from_immer(org::ImmPunctuation const& value, ImmAstContext const& ctx) {
    sem::Punctuation result = SerdeDefaultProvider<sem::Punctuation>::get();
    assign_sem_field(result.text, value.text, ctx);
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<sem::Placeholder, org::ImmPlaceholder> {
  static org::ImmPlaceholder to_immer(sem::Placeholder const& value, ImmAstEditContext& ctx) {
    org::ImmPlaceholder result = SerdeDefaultProvider<org::ImmPlaceholder>::get();
    assign_immer_field(result.text, value.text, ctx);
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
  static sem::Placeholder from_immer(org::ImmPlaceholder const& value, ImmAstContext const& ctx) {
    sem::Placeholder result = SerdeDefaultProvider<sem::Placeholder>::get();
    assign_sem_field(result.text, value.text, ctx);
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<sem::BigIdent, org::ImmBigIdent> {
  static org::ImmBigIdent to_immer(sem::BigIdent const& value, ImmAstEditContext& ctx) {
    org::ImmBigIdent result = SerdeDefaultProvider<org::ImmBigIdent>::get();
    assign_immer_field(result.text, value.text, ctx);
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
  static sem::BigIdent from_immer(org::ImmBigIdent const& value, ImmAstContext const& ctx) {
    sem::BigIdent result = SerdeDefaultProvider<sem::BigIdent>::get();
    assign_sem_field(result.text, value.text, ctx);
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<sem::RadioTarget, org::ImmRadioTarget> {
  static org::ImmRadioTarget to_immer(sem::RadioTarget const& value, ImmAstEditContext& ctx) {
    org::ImmRadioTarget result = SerdeDefaultProvider<org::ImmRadioTarget>::get();
    assign_immer_field(result.text, value.text, ctx);
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
  static sem::RadioTarget from_immer(org::ImmRadioTarget const& value, ImmAstContext const& ctx) {
    sem::RadioTarget result = SerdeDefaultProvider<sem::RadioTarget>::get();
    assign_sem_field(result.text, value.text, ctx);
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<sem::TextTarget, org::ImmTextTarget> {
  static org::ImmTextTarget to_immer(sem::TextTarget const& value, ImmAstEditContext& ctx) {
    org::ImmTextTarget result = SerdeDefaultProvider<org::ImmTextTarget>::get();
    assign_immer_field(result.text, value.text, ctx);
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
  static sem::TextTarget from_immer(org::ImmTextTarget const& value, ImmAstContext const& ctx) {
    sem::TextTarget result = SerdeDefaultProvider<sem::TextTarget>::get();
    assign_sem_field(result.text, value.text, ctx);
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<sem::Bold, org::ImmBold> {
  static org::ImmBold to_immer(sem::Bold const& value, ImmAstEditContext& ctx) {
    org::ImmBold result = SerdeDefaultProvider<org::ImmBold>::get();
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
  static sem::Bold from_immer(org::ImmBold const& value, ImmAstContext const& ctx) {
    sem::Bold result = SerdeDefaultProvider<sem::Bold>::get();
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<sem::Underline, org::ImmUnderline> {
  static org::ImmUnderline to_immer(sem::Underline const& value, ImmAstEditContext& ctx) {
    org::ImmUnderline result = SerdeDefaultProvider<org::ImmUnderline>::get();
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
  static sem::Underline from_immer(org::ImmUnderline const& value, ImmAstContext const& ctx) {
    sem::Underline result = SerdeDefaultProvider<sem::Underline>::get();
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<sem::Monospace, org::ImmMonospace> {
  static org::ImmMonospace to_immer(sem::Monospace const& value, ImmAstEditContext& ctx) {
    org::ImmMonospace result = SerdeDefaultProvider<org::ImmMonospace>::get();
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
  static sem::Monospace from_immer(org::ImmMonospace const& value, ImmAstContext const& ctx) {
    sem::Monospace result = SerdeDefaultProvider<sem::Monospace>::get();
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<sem::MarkQuote, org::ImmMarkQuote> {
  static org::ImmMarkQuote to_immer(sem::MarkQuote const& value, ImmAstEditContext& ctx) {
    org::ImmMarkQuote result = SerdeDefaultProvider<org::ImmMarkQuote>::get();
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
  static sem::MarkQuote from_immer(org::ImmMarkQuote const& value, ImmAstContext const& ctx) {
    sem::MarkQuote result = SerdeDefaultProvider<sem::MarkQuote>::get();
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<sem::Verbatim, org::ImmVerbatim> {
  static org::ImmVerbatim to_immer(sem::Verbatim const& value, ImmAstEditContext& ctx) {
    org::ImmVerbatim result = SerdeDefaultProvider<org::ImmVerbatim>::get();
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
  static sem::Verbatim from_immer(org::ImmVerbatim const& value, ImmAstContext const& ctx) {
    sem::Verbatim result = SerdeDefaultProvider<sem::Verbatim>::get();
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<sem::Italic, org::ImmItalic> {
  static org::ImmItalic to_immer(sem::Italic const& value, ImmAstEditContext& ctx) {
    org::ImmItalic result = SerdeDefaultProvider<org::ImmItalic>::get();
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
  static sem::Italic from_immer(org::ImmItalic const& value, ImmAstContext const& ctx) {
    sem::Italic result = SerdeDefaultProvider<sem::Italic>::get();
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<sem::Strike, org::ImmStrike> {
  static org::ImmStrike to_immer(sem::Strike const& value, ImmAstEditContext& ctx) {
    org::ImmStrike result = SerdeDefaultProvider<org::ImmStrike>::get();
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
  static sem::Strike from_immer(org::ImmStrike const& value, ImmAstContext const& ctx) {
    sem::Strike result = SerdeDefaultProvider<sem::Strike>::get();
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<sem::Par, org::ImmPar> {
  static org::ImmPar to_immer(sem::Par const& value, ImmAstEditContext& ctx) {
    org::ImmPar result = SerdeDefaultProvider<org::ImmPar>::get();
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
  static sem::Par from_immer(org::ImmPar const& value, ImmAstContext const& ctx) {
    sem::Par result = SerdeDefaultProvider<sem::Par>::get();
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<sem::Latex, org::ImmLatex> {
  static org::ImmLatex to_immer(sem::Latex const& value, ImmAstEditContext& ctx) {
    org::ImmLatex result = SerdeDefaultProvider<org::ImmLatex>::get();
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
  static sem::Latex from_immer(org::ImmLatex const& value, ImmAstContext const& ctx) {
    sem::Latex result = SerdeDefaultProvider<sem::Latex>::get();
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<sem::Link, org::ImmLink> {
  static org::ImmLink to_immer(sem::Link const& value, ImmAstEditContext& ctx) {
    org::ImmLink result = SerdeDefaultProvider<org::ImmLink>::get();
    assign_immer_field(result.description, value.description, ctx);
    assign_immer_field(result.target, value.target, ctx);
    assign_immer_field(result.attached, value.attached, ctx);
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
  static sem::Link from_immer(org::ImmLink const& value, ImmAstContext const& ctx) {
    sem::Link result = SerdeDefaultProvider<sem::Link>::get();
    assign_sem_field(result.description, value.description, ctx);
    assign_sem_field(result.target, value.target, ctx);
    assign_sem_field(result.attached, value.attached, ctx);
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<sem::BlockCenter, org::ImmBlockCenter> {
  static org::ImmBlockCenter to_immer(sem::BlockCenter const& value, ImmAstEditContext& ctx) {
    org::ImmBlockCenter result = SerdeDefaultProvider<org::ImmBlockCenter>::get();
    assign_immer_field(result.attrs, value.attrs, ctx);
    assign_immer_field(result.attached, value.attached, ctx);
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
  static sem::BlockCenter from_immer(org::ImmBlockCenter const& value, ImmAstContext const& ctx) {
    sem::BlockCenter result = SerdeDefaultProvider<sem::BlockCenter>::get();
    assign_sem_field(result.attrs, value.attrs, ctx);
    assign_sem_field(result.attached, value.attached, ctx);
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<sem::BlockQuote, org::ImmBlockQuote> {
  static org::ImmBlockQuote to_immer(sem::BlockQuote const& value, ImmAstEditContext& ctx) {
    org::ImmBlockQuote result = SerdeDefaultProvider<org::ImmBlockQuote>::get();
    assign_immer_field(result.attrs, value.attrs, ctx);
    assign_immer_field(result.attached, value.attached, ctx);
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
  static sem::BlockQuote from_immer(org::ImmBlockQuote const& value, ImmAstContext const& ctx) {
    sem::BlockQuote result = SerdeDefaultProvider<sem::BlockQuote>::get();
    assign_sem_field(result.attrs, value.attrs, ctx);
    assign_sem_field(result.attached, value.attached, ctx);
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<sem::BlockComment, org::ImmBlockComment> {
  static org::ImmBlockComment to_immer(sem::BlockComment const& value, ImmAstEditContext& ctx) {
    org::ImmBlockComment result = SerdeDefaultProvider<org::ImmBlockComment>::get();
    assign_immer_field(result.attached, value.attached, ctx);
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
  static sem::BlockComment from_immer(org::ImmBlockComment const& value, ImmAstContext const& ctx) {
    sem::BlockComment result = SerdeDefaultProvider<sem::BlockComment>::get();
    assign_sem_field(result.attached, value.attached, ctx);
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<sem::BlockVerse, org::ImmBlockVerse> {
  static org::ImmBlockVerse to_immer(sem::BlockVerse const& value, ImmAstEditContext& ctx) {
    org::ImmBlockVerse result = SerdeDefaultProvider<org::ImmBlockVerse>::get();
    assign_immer_field(result.attrs, value.attrs, ctx);
    assign_immer_field(result.attached, value.attached, ctx);
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
  static sem::BlockVerse from_immer(org::ImmBlockVerse const& value, ImmAstContext const& ctx) {
    sem::BlockVerse result = SerdeDefaultProvider<sem::BlockVerse>::get();
    assign_sem_field(result.attrs, value.attrs, ctx);
    assign_sem_field(result.attached, value.attached, ctx);
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<sem::BlockDynamicFallback, org::ImmBlockDynamicFallback> {
  static org::ImmBlockDynamicFallback to_immer(sem::BlockDynamicFallback const& value, ImmAstEditContext& ctx) {
    org::ImmBlockDynamicFallback result = SerdeDefaultProvider<org::ImmBlockDynamicFallback>::get();
    assign_immer_field(result.name, value.name, ctx);
    assign_immer_field(result.attrs, value.attrs, ctx);
    assign_immer_field(result.attached, value.attached, ctx);
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
  static sem::BlockDynamicFallback from_immer(org::ImmBlockDynamicFallback const& value, ImmAstContext const& ctx) {
    sem::BlockDynamicFallback result = SerdeDefaultProvider<sem::BlockDynamicFallback>::get();
    assign_sem_field(result.name, value.name, ctx);
    assign_sem_field(result.attrs, value.attrs, ctx);
    assign_sem_field(result.attached, value.attached, ctx);
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<sem::BlockExample, org::ImmBlockExample> {
  static org::ImmBlockExample to_immer(sem::BlockExample const& value, ImmAstEditContext& ctx) {
    org::ImmBlockExample result = SerdeDefaultProvider<org::ImmBlockExample>::get();
    assign_immer_field(result.attrs, value.attrs, ctx);
    assign_immer_field(result.attached, value.attached, ctx);
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
  static sem::BlockExample from_immer(org::ImmBlockExample const& value, ImmAstContext const& ctx) {
    sem::BlockExample result = SerdeDefaultProvider<sem::BlockExample>::get();
    assign_sem_field(result.attrs, value.attrs, ctx);
    assign_sem_field(result.attached, value.attached, ctx);
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<sem::BlockExport, org::ImmBlockExport> {
  static org::ImmBlockExport to_immer(sem::BlockExport const& value, ImmAstEditContext& ctx) {
    org::ImmBlockExport result = SerdeDefaultProvider<org::ImmBlockExport>::get();
    assign_immer_field(result.format, value.format, ctx);
    assign_immer_field(result.exporter, value.exporter, ctx);
    assign_immer_field(result.placement, value.placement, ctx);
    assign_immer_field(result.content, value.content, ctx);
    assign_immer_field(result.attrs, value.attrs, ctx);
    assign_immer_field(result.attached, value.attached, ctx);
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
  static sem::BlockExport from_immer(org::ImmBlockExport const& value, ImmAstContext const& ctx) {
    sem::BlockExport result = SerdeDefaultProvider<sem::BlockExport>::get();
    assign_sem_field(result.format, value.format, ctx);
    assign_sem_field(result.exporter, value.exporter, ctx);
    assign_sem_field(result.placement, value.placement, ctx);
    assign_sem_field(result.content, value.content, ctx);
    assign_sem_field(result.attrs, value.attrs, ctx);
    assign_sem_field(result.attached, value.attached, ctx);
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<sem::BlockAdmonition, org::ImmBlockAdmonition> {
  static org::ImmBlockAdmonition to_immer(sem::BlockAdmonition const& value, ImmAstEditContext& ctx) {
    org::ImmBlockAdmonition result = SerdeDefaultProvider<org::ImmBlockAdmonition>::get();
    assign_immer_field(result.attrs, value.attrs, ctx);
    assign_immer_field(result.attached, value.attached, ctx);
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
  static sem::BlockAdmonition from_immer(org::ImmBlockAdmonition const& value, ImmAstContext const& ctx) {
    sem::BlockAdmonition result = SerdeDefaultProvider<sem::BlockAdmonition>::get();
    assign_sem_field(result.attrs, value.attrs, ctx);
    assign_sem_field(result.attached, value.attached, ctx);
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<sem::BlockCode, org::ImmBlockCode> {
  static org::ImmBlockCode to_immer(sem::BlockCode const& value, ImmAstEditContext& ctx) {
    org::ImmBlockCode result = SerdeDefaultProvider<org::ImmBlockCode>::get();
    assign_immer_field(result.lang, value.lang, ctx);
    assign_immer_field(result.switches, value.switches, ctx);
    assign_immer_field(result.exports, value.exports, ctx);
    assign_immer_field(result.result, value.result, ctx);
    assign_immer_field(result.lines, value.lines, ctx);
    assign_immer_field(result.cache, value.cache, ctx);
    assign_immer_field(result.eval, value.eval, ctx);
    assign_immer_field(result.noweb, value.noweb, ctx);
    assign_immer_field(result.hlines, value.hlines, ctx);
    assign_immer_field(result.tangle, value.tangle, ctx);
    assign_immer_field(result.attrs, value.attrs, ctx);
    assign_immer_field(result.attached, value.attached, ctx);
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
  static sem::BlockCode from_immer(org::ImmBlockCode const& value, ImmAstContext const& ctx) {
    sem::BlockCode result = SerdeDefaultProvider<sem::BlockCode>::get();
    assign_sem_field(result.lang, value.lang, ctx);
    assign_sem_field(result.switches, value.switches, ctx);
    assign_sem_field(result.exports, value.exports, ctx);
    assign_sem_field(result.result, value.result, ctx);
    assign_sem_field(result.lines, value.lines, ctx);
    assign_sem_field(result.cache, value.cache, ctx);
    assign_sem_field(result.eval, value.eval, ctx);
    assign_sem_field(result.noweb, value.noweb, ctx);
    assign_sem_field(result.hlines, value.hlines, ctx);
    assign_sem_field(result.tangle, value.tangle, ctx);
    assign_sem_field(result.attrs, value.attrs, ctx);
    assign_sem_field(result.attached, value.attached, ctx);
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<sem::SubtreeLog, org::ImmSubtreeLog> {
  static org::ImmSubtreeLog to_immer(sem::SubtreeLog const& value, ImmAstEditContext& ctx) {
    org::ImmSubtreeLog result = SerdeDefaultProvider<org::ImmSubtreeLog>::get();
    assign_immer_field(result.log, value.log, ctx);
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
  static sem::SubtreeLog from_immer(org::ImmSubtreeLog const& value, ImmAstContext const& ctx) {
    sem::SubtreeLog result = SerdeDefaultProvider<sem::SubtreeLog>::get();
    assign_sem_field(result.log, value.log, ctx);
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<sem::SubtreeLog::DescribedLog, org::ImmSubtreeLog::DescribedLog> {
  static org::ImmSubtreeLog::DescribedLog to_immer(sem::SubtreeLog::DescribedLog const& value, ImmAstEditContext& ctx) {
    org::ImmSubtreeLog::DescribedLog result = SerdeDefaultProvider<org::ImmSubtreeLog::DescribedLog>::get();
    assign_immer_field(result.desc, value.desc, ctx);
    return result;
  }
  static sem::SubtreeLog::DescribedLog from_immer(org::ImmSubtreeLog::DescribedLog const& value, ImmAstContext const& ctx) {
    sem::SubtreeLog::DescribedLog result = SerdeDefaultProvider<sem::SubtreeLog::DescribedLog>::get();
    assign_sem_field(result.desc, value.desc, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<sem::SubtreeLog::Priority, org::ImmSubtreeLog::Priority> {
  static org::ImmSubtreeLog::Priority to_immer(sem::SubtreeLog::Priority const& value, ImmAstEditContext& ctx) {
    org::ImmSubtreeLog::Priority result = SerdeDefaultProvider<org::ImmSubtreeLog::Priority>::get();
    assign_immer_field(result.oldPriority, value.oldPriority, ctx);
    assign_immer_field(result.newPriority, value.newPriority, ctx);
    assign_immer_field(result.on, value.on, ctx);
    assign_immer_field(result.action, value.action, ctx);
    assign_immer_field(result.desc, value.desc, ctx);
    return result;
  }
  static sem::SubtreeLog::Priority from_immer(org::ImmSubtreeLog::Priority const& value, ImmAstContext const& ctx) {
    sem::SubtreeLog::Priority result = SerdeDefaultProvider<sem::SubtreeLog::Priority>::get();
    assign_sem_field(result.oldPriority, value.oldPriority, ctx);
    assign_sem_field(result.newPriority, value.newPriority, ctx);
    assign_sem_field(result.on, value.on, ctx);
    assign_sem_field(result.action, value.action, ctx);
    assign_sem_field(result.desc, value.desc, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<sem::SubtreeLog::Note, org::ImmSubtreeLog::Note> {
  static org::ImmSubtreeLog::Note to_immer(sem::SubtreeLog::Note const& value, ImmAstEditContext& ctx) {
    org::ImmSubtreeLog::Note result = SerdeDefaultProvider<org::ImmSubtreeLog::Note>::get();
    assign_immer_field(result.on, value.on, ctx);
    assign_immer_field(result.desc, value.desc, ctx);
    return result;
  }
  static sem::SubtreeLog::Note from_immer(org::ImmSubtreeLog::Note const& value, ImmAstContext const& ctx) {
    sem::SubtreeLog::Note result = SerdeDefaultProvider<sem::SubtreeLog::Note>::get();
    assign_sem_field(result.on, value.on, ctx);
    assign_sem_field(result.desc, value.desc, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<sem::SubtreeLog::Refile, org::ImmSubtreeLog::Refile> {
  static org::ImmSubtreeLog::Refile to_immer(sem::SubtreeLog::Refile const& value, ImmAstEditContext& ctx) {
    org::ImmSubtreeLog::Refile result = SerdeDefaultProvider<org::ImmSubtreeLog::Refile>::get();
    assign_immer_field(result.on, value.on, ctx);
    assign_immer_field(result.from, value.from, ctx);
    assign_immer_field(result.desc, value.desc, ctx);
    return result;
  }
  static sem::SubtreeLog::Refile from_immer(org::ImmSubtreeLog::Refile const& value, ImmAstContext const& ctx) {
    sem::SubtreeLog::Refile result = SerdeDefaultProvider<sem::SubtreeLog::Refile>::get();
    assign_sem_field(result.on, value.on, ctx);
    assign_sem_field(result.from, value.from, ctx);
    assign_sem_field(result.desc, value.desc, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<sem::SubtreeLog::Clock, org::ImmSubtreeLog::Clock> {
  static org::ImmSubtreeLog::Clock to_immer(sem::SubtreeLog::Clock const& value, ImmAstEditContext& ctx) {
    org::ImmSubtreeLog::Clock result = SerdeDefaultProvider<org::ImmSubtreeLog::Clock>::get();
    assign_immer_field(result.from, value.from, ctx);
    assign_immer_field(result.to, value.to, ctx);
    assign_immer_field(result.desc, value.desc, ctx);
    return result;
  }
  static sem::SubtreeLog::Clock from_immer(org::ImmSubtreeLog::Clock const& value, ImmAstContext const& ctx) {
    sem::SubtreeLog::Clock result = SerdeDefaultProvider<sem::SubtreeLog::Clock>::get();
    assign_sem_field(result.from, value.from, ctx);
    assign_sem_field(result.to, value.to, ctx);
    assign_sem_field(result.desc, value.desc, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<sem::SubtreeLog::State, org::ImmSubtreeLog::State> {
  static org::ImmSubtreeLog::State to_immer(sem::SubtreeLog::State const& value, ImmAstEditContext& ctx) {
    org::ImmSubtreeLog::State result = SerdeDefaultProvider<org::ImmSubtreeLog::State>::get();
    assign_immer_field(result.from, value.from, ctx);
    assign_immer_field(result.to, value.to, ctx);
    assign_immer_field(result.on, value.on, ctx);
    assign_immer_field(result.desc, value.desc, ctx);
    return result;
  }
  static sem::SubtreeLog::State from_immer(org::ImmSubtreeLog::State const& value, ImmAstContext const& ctx) {
    sem::SubtreeLog::State result = SerdeDefaultProvider<sem::SubtreeLog::State>::get();
    assign_sem_field(result.from, value.from, ctx);
    assign_sem_field(result.to, value.to, ctx);
    assign_sem_field(result.on, value.on, ctx);
    assign_sem_field(result.desc, value.desc, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<sem::SubtreeLog::Deadline, org::ImmSubtreeLog::Deadline> {
  static org::ImmSubtreeLog::Deadline to_immer(sem::SubtreeLog::Deadline const& value, ImmAstEditContext& ctx) {
    org::ImmSubtreeLog::Deadline result = SerdeDefaultProvider<org::ImmSubtreeLog::Deadline>::get();
    assign_immer_field(result.from, value.from, ctx);
    assign_immer_field(result.to, value.to, ctx);
    assign_immer_field(result.on, value.on, ctx);
    assign_immer_field(result.desc, value.desc, ctx);
    return result;
  }
  static sem::SubtreeLog::Deadline from_immer(org::ImmSubtreeLog::Deadline const& value, ImmAstContext const& ctx) {
    sem::SubtreeLog::Deadline result = SerdeDefaultProvider<sem::SubtreeLog::Deadline>::get();
    assign_sem_field(result.from, value.from, ctx);
    assign_sem_field(result.to, value.to, ctx);
    assign_sem_field(result.on, value.on, ctx);
    assign_sem_field(result.desc, value.desc, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<sem::SubtreeLog::Schedule, org::ImmSubtreeLog::Schedule> {
  static org::ImmSubtreeLog::Schedule to_immer(sem::SubtreeLog::Schedule const& value, ImmAstEditContext& ctx) {
    org::ImmSubtreeLog::Schedule result = SerdeDefaultProvider<org::ImmSubtreeLog::Schedule>::get();
    assign_immer_field(result.from, value.from, ctx);
    assign_immer_field(result.to, value.to, ctx);
    assign_immer_field(result.on, value.on, ctx);
    assign_immer_field(result.desc, value.desc, ctx);
    return result;
  }
  static sem::SubtreeLog::Schedule from_immer(org::ImmSubtreeLog::Schedule const& value, ImmAstContext const& ctx) {
    sem::SubtreeLog::Schedule result = SerdeDefaultProvider<sem::SubtreeLog::Schedule>::get();
    assign_sem_field(result.from, value.from, ctx);
    assign_sem_field(result.to, value.to, ctx);
    assign_sem_field(result.on, value.on, ctx);
    assign_sem_field(result.desc, value.desc, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<sem::SubtreeLog::Tag, org::ImmSubtreeLog::Tag> {
  static org::ImmSubtreeLog::Tag to_immer(sem::SubtreeLog::Tag const& value, ImmAstEditContext& ctx) {
    org::ImmSubtreeLog::Tag result = SerdeDefaultProvider<org::ImmSubtreeLog::Tag>::get();
    assign_immer_field(result.on, value.on, ctx);
    assign_immer_field(result.tag, value.tag, ctx);
    assign_immer_field(result.added, value.added, ctx);
    assign_immer_field(result.desc, value.desc, ctx);
    return result;
  }
  static sem::SubtreeLog::Tag from_immer(org::ImmSubtreeLog::Tag const& value, ImmAstContext const& ctx) {
    sem::SubtreeLog::Tag result = SerdeDefaultProvider<sem::SubtreeLog::Tag>::get();
    assign_sem_field(result.on, value.on, ctx);
    assign_sem_field(result.tag, value.tag, ctx);
    assign_sem_field(result.added, value.added, ctx);
    assign_sem_field(result.desc, value.desc, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<sem::SubtreeLog::Unknown, org::ImmSubtreeLog::Unknown> {
  static org::ImmSubtreeLog::Unknown to_immer(sem::SubtreeLog::Unknown const& value, ImmAstEditContext& ctx) {
    org::ImmSubtreeLog::Unknown result = SerdeDefaultProvider<org::ImmSubtreeLog::Unknown>::get();
    assign_immer_field(result.desc, value.desc, ctx);
    return result;
  }
  static sem::SubtreeLog::Unknown from_immer(org::ImmSubtreeLog::Unknown const& value, ImmAstContext const& ctx) {
    sem::SubtreeLog::Unknown result = SerdeDefaultProvider<sem::SubtreeLog::Unknown>::get();
    assign_sem_field(result.desc, value.desc, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<sem::Subtree, org::ImmSubtree> {
  static org::ImmSubtree to_immer(sem::Subtree const& value, ImmAstEditContext& ctx) {
    org::ImmSubtree result = SerdeDefaultProvider<org::ImmSubtree>::get();
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
    return result;
  }
  static sem::Subtree from_immer(org::ImmSubtree const& value, ImmAstContext const& ctx) {
    sem::Subtree result = SerdeDefaultProvider<sem::Subtree>::get();
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
    return result;
  }
};

template <>
struct ImmSemSerde<sem::Cell, org::ImmCell> {
  static org::ImmCell to_immer(sem::Cell const& value, ImmAstEditContext& ctx) {
    org::ImmCell result = SerdeDefaultProvider<org::ImmCell>::get();
    assign_immer_field(result.isBlock, value.isBlock, ctx);
    assign_immer_field(result.attrs, value.attrs, ctx);
    assign_immer_field(result.attached, value.attached, ctx);
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
  static sem::Cell from_immer(org::ImmCell const& value, ImmAstContext const& ctx) {
    sem::Cell result = SerdeDefaultProvider<sem::Cell>::get();
    assign_sem_field(result.isBlock, value.isBlock, ctx);
    assign_sem_field(result.attrs, value.attrs, ctx);
    assign_sem_field(result.attached, value.attached, ctx);
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<sem::Row, org::ImmRow> {
  static org::ImmRow to_immer(sem::Row const& value, ImmAstEditContext& ctx) {
    org::ImmRow result = SerdeDefaultProvider<org::ImmRow>::get();
    assign_immer_field(result.cells, value.cells, ctx);
    assign_immer_field(result.isBlock, value.isBlock, ctx);
    assign_immer_field(result.attrs, value.attrs, ctx);
    assign_immer_field(result.attached, value.attached, ctx);
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
  static sem::Row from_immer(org::ImmRow const& value, ImmAstContext const& ctx) {
    sem::Row result = SerdeDefaultProvider<sem::Row>::get();
    assign_sem_field(result.cells, value.cells, ctx);
    assign_sem_field(result.isBlock, value.isBlock, ctx);
    assign_sem_field(result.attrs, value.attrs, ctx);
    assign_sem_field(result.attached, value.attached, ctx);
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<sem::Table, org::ImmTable> {
  static org::ImmTable to_immer(sem::Table const& value, ImmAstEditContext& ctx) {
    org::ImmTable result = SerdeDefaultProvider<org::ImmTable>::get();
    assign_immer_field(result.rows, value.rows, ctx);
    assign_immer_field(result.isBlock, value.isBlock, ctx);
    assign_immer_field(result.attrs, value.attrs, ctx);
    assign_immer_field(result.attached, value.attached, ctx);
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
  static sem::Table from_immer(org::ImmTable const& value, ImmAstContext const& ctx) {
    sem::Table result = SerdeDefaultProvider<sem::Table>::get();
    assign_sem_field(result.rows, value.rows, ctx);
    assign_sem_field(result.isBlock, value.isBlock, ctx);
    assign_sem_field(result.attrs, value.attrs, ctx);
    assign_sem_field(result.attached, value.attached, ctx);
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<sem::Paragraph, org::ImmParagraph> {
  static org::ImmParagraph to_immer(sem::Paragraph const& value, ImmAstEditContext& ctx) {
    org::ImmParagraph result = SerdeDefaultProvider<org::ImmParagraph>::get();
    assign_immer_field(result.attached, value.attached, ctx);
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
  static sem::Paragraph from_immer(org::ImmParagraph const& value, ImmAstContext const& ctx) {
    sem::Paragraph result = SerdeDefaultProvider<sem::Paragraph>::get();
    assign_sem_field(result.attached, value.attached, ctx);
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<sem::ColonExample, org::ImmColonExample> {
  static org::ImmColonExample to_immer(sem::ColonExample const& value, ImmAstEditContext& ctx) {
    org::ImmColonExample result = SerdeDefaultProvider<org::ImmColonExample>::get();
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
  static sem::ColonExample from_immer(org::ImmColonExample const& value, ImmAstContext const& ctx) {
    sem::ColonExample result = SerdeDefaultProvider<sem::ColonExample>::get();
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<sem::CmdAttr, org::ImmCmdAttr> {
  static org::ImmCmdAttr to_immer(sem::CmdAttr const& value, ImmAstEditContext& ctx) {
    org::ImmCmdAttr result = SerdeDefaultProvider<org::ImmCmdAttr>::get();
    assign_immer_field(result.target, value.target, ctx);
    assign_immer_field(result.attrs, value.attrs, ctx);
    assign_immer_field(result.attached, value.attached, ctx);
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
  static sem::CmdAttr from_immer(org::ImmCmdAttr const& value, ImmAstContext const& ctx) {
    sem::CmdAttr result = SerdeDefaultProvider<sem::CmdAttr>::get();
    assign_sem_field(result.target, value.target, ctx);
    assign_sem_field(result.attrs, value.attrs, ctx);
    assign_sem_field(result.attached, value.attached, ctx);
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<sem::Call, org::ImmCall> {
  static org::ImmCall to_immer(sem::Call const& value, ImmAstEditContext& ctx) {
    org::ImmCall result = SerdeDefaultProvider<org::ImmCall>::get();
    assign_immer_field(result.name, value.name, ctx);
    assign_immer_field(result.attrs, value.attrs, ctx);
    assign_immer_field(result.isCommand, value.isCommand, ctx);
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
  static sem::Call from_immer(org::ImmCall const& value, ImmAstContext const& ctx) {
    sem::Call result = SerdeDefaultProvider<sem::Call>::get();
    assign_sem_field(result.name, value.name, ctx);
    assign_sem_field(result.attrs, value.attrs, ctx);
    assign_sem_field(result.isCommand, value.isCommand, ctx);
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<sem::List, org::ImmList> {
  static org::ImmList to_immer(sem::List const& value, ImmAstEditContext& ctx) {
    org::ImmList result = SerdeDefaultProvider<org::ImmList>::get();
    assign_immer_field(result.attached, value.attached, ctx);
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
  static sem::List from_immer(org::ImmList const& value, ImmAstContext const& ctx) {
    sem::List result = SerdeDefaultProvider<sem::List>::get();
    assign_sem_field(result.attached, value.attached, ctx);
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<sem::ListItem, org::ImmListItem> {
  static org::ImmListItem to_immer(sem::ListItem const& value, ImmAstEditContext& ctx) {
    org::ImmListItem result = SerdeDefaultProvider<org::ImmListItem>::get();
    assign_immer_field(result.checkbox, value.checkbox, ctx);
    assign_immer_field(result.header, value.header, ctx);
    assign_immer_field(result.bullet, value.bullet, ctx);
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
  static sem::ListItem from_immer(org::ImmListItem const& value, ImmAstContext const& ctx) {
    sem::ListItem result = SerdeDefaultProvider<sem::ListItem>::get();
    assign_sem_field(result.checkbox, value.checkbox, ctx);
    assign_sem_field(result.header, value.header, ctx);
    assign_sem_field(result.bullet, value.bullet, ctx);
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<sem::DocumentOptions, org::ImmDocumentOptions> {
  static org::ImmDocumentOptions to_immer(sem::DocumentOptions const& value, ImmAstEditContext& ctx) {
    org::ImmDocumentOptions result = SerdeDefaultProvider<org::ImmDocumentOptions>::get();
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
    return result;
  }
  static sem::DocumentOptions from_immer(org::ImmDocumentOptions const& value, ImmAstContext const& ctx) {
    sem::DocumentOptions result = SerdeDefaultProvider<sem::DocumentOptions>::get();
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
    return result;
  }
};

template <>
struct ImmSemSerde<sem::Document, org::ImmDocument> {
  static org::ImmDocument to_immer(sem::Document const& value, ImmAstEditContext& ctx) {
    org::ImmDocument result = SerdeDefaultProvider<org::ImmDocument>::get();
    assign_immer_field(result.title, value.title, ctx);
    assign_immer_field(result.author, value.author, ctx);
    assign_immer_field(result.creator, value.creator, ctx);
    assign_immer_field(result.filetags, value.filetags, ctx);
    assign_immer_field(result.email, value.email, ctx);
    assign_immer_field(result.language, value.language, ctx);
    assign_immer_field(result.options, value.options, ctx);
    assign_immer_field(result.exportFileName, value.exportFileName, ctx);
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
  static sem::Document from_immer(org::ImmDocument const& value, ImmAstContext const& ctx) {
    sem::Document result = SerdeDefaultProvider<sem::Document>::get();
    assign_sem_field(result.title, value.title, ctx);
    assign_sem_field(result.author, value.author, ctx);
    assign_sem_field(result.creator, value.creator, ctx);
    assign_sem_field(result.filetags, value.filetags, ctx);
    assign_sem_field(result.email, value.email, ctx);
    assign_sem_field(result.language, value.language, ctx);
    assign_sem_field(result.options, value.options, ctx);
    assign_sem_field(result.exportFileName, value.exportFileName, ctx);
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<sem::FileTarget, org::ImmFileTarget> {
  static org::ImmFileTarget to_immer(sem::FileTarget const& value, ImmAstEditContext& ctx) {
    org::ImmFileTarget result = SerdeDefaultProvider<org::ImmFileTarget>::get();
    assign_immer_field(result.path, value.path, ctx);
    assign_immer_field(result.line, value.line, ctx);
    assign_immer_field(result.searchTarget, value.searchTarget, ctx);
    assign_immer_field(result.restrictToHeadlines, value.restrictToHeadlines, ctx);
    assign_immer_field(result.targetId, value.targetId, ctx);
    assign_immer_field(result.regexp, value.regexp, ctx);
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
  static sem::FileTarget from_immer(org::ImmFileTarget const& value, ImmAstContext const& ctx) {
    sem::FileTarget result = SerdeDefaultProvider<sem::FileTarget>::get();
    assign_sem_field(result.path, value.path, ctx);
    assign_sem_field(result.line, value.line, ctx);
    assign_sem_field(result.searchTarget, value.searchTarget, ctx);
    assign_sem_field(result.restrictToHeadlines, value.restrictToHeadlines, ctx);
    assign_sem_field(result.targetId, value.targetId, ctx);
    assign_sem_field(result.regexp, value.regexp, ctx);
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<sem::TextSeparator, org::ImmTextSeparator> {
  static org::ImmTextSeparator to_immer(sem::TextSeparator const& value, ImmAstEditContext& ctx) {
    org::ImmTextSeparator result = SerdeDefaultProvider<org::ImmTextSeparator>::get();
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
  static sem::TextSeparator from_immer(org::ImmTextSeparator const& value, ImmAstContext const& ctx) {
    sem::TextSeparator result = SerdeDefaultProvider<sem::TextSeparator>::get();
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<sem::Include, org::ImmInclude> {
  static org::ImmInclude to_immer(sem::Include const& value, ImmAstEditContext& ctx) {
    org::ImmInclude result = SerdeDefaultProvider<org::ImmInclude>::get();
    assign_immer_field(result.path, value.path, ctx);
    assign_immer_field(result.firstLine, value.firstLine, ctx);
    assign_immer_field(result.lastLine, value.lastLine, ctx);
    assign_immer_field(result.data, value.data, ctx);
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
  static sem::Include from_immer(org::ImmInclude const& value, ImmAstContext const& ctx) {
    sem::Include result = SerdeDefaultProvider<sem::Include>::get();
    assign_sem_field(result.path, value.path, ctx);
    assign_sem_field(result.firstLine, value.firstLine, ctx);
    assign_sem_field(result.lastLine, value.lastLine, ctx);
    assign_sem_field(result.data, value.data, ctx);
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<sem::Include::Example, org::ImmInclude::Example> {
  static org::ImmInclude::Example to_immer(sem::Include::Example const& value, ImmAstEditContext& ctx) {
    org::ImmInclude::Example result = SerdeDefaultProvider<org::ImmInclude::Example>::get();
    return result;
  }
  static sem::Include::Example from_immer(org::ImmInclude::Example const& value, ImmAstContext const& ctx) {
    sem::Include::Example result = SerdeDefaultProvider<sem::Include::Example>::get();
    return result;
  }
};

template <>
struct ImmSemSerde<sem::Include::Export, org::ImmInclude::Export> {
  static org::ImmInclude::Export to_immer(sem::Include::Export const& value, ImmAstEditContext& ctx) {
    org::ImmInclude::Export result = SerdeDefaultProvider<org::ImmInclude::Export>::get();
    return result;
  }
  static sem::Include::Export from_immer(org::ImmInclude::Export const& value, ImmAstContext const& ctx) {
    sem::Include::Export result = SerdeDefaultProvider<sem::Include::Export>::get();
    return result;
  }
};

template <>
struct ImmSemSerde<sem::Include::Src, org::ImmInclude::Src> {
  static org::ImmInclude::Src to_immer(sem::Include::Src const& value, ImmAstEditContext& ctx) {
    org::ImmInclude::Src result = SerdeDefaultProvider<org::ImmInclude::Src>::get();
    return result;
  }
  static sem::Include::Src from_immer(org::ImmInclude::Src const& value, ImmAstContext const& ctx) {
    sem::Include::Src result = SerdeDefaultProvider<sem::Include::Src>::get();
    return result;
  }
};

template <>
struct ImmSemSerde<sem::Include::OrgDocument, org::ImmInclude::OrgDocument> {
  static org::ImmInclude::OrgDocument to_immer(sem::Include::OrgDocument const& value, ImmAstEditContext& ctx) {
    org::ImmInclude::OrgDocument result = SerdeDefaultProvider<org::ImmInclude::OrgDocument>::get();
    assign_immer_field(result.minLevel, value.minLevel, ctx);
    return result;
  }
  static sem::Include::OrgDocument from_immer(org::ImmInclude::OrgDocument const& value, ImmAstContext const& ctx) {
    sem::Include::OrgDocument result = SerdeDefaultProvider<sem::Include::OrgDocument>::get();
    assign_sem_field(result.minLevel, value.minLevel, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<sem::DocumentGroup, org::ImmDocumentGroup> {
  static org::ImmDocumentGroup to_immer(sem::DocumentGroup const& value, ImmAstEditContext& ctx) {
    org::ImmDocumentGroup result = SerdeDefaultProvider<org::ImmDocumentGroup>::get();
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
  static sem::DocumentGroup from_immer(org::ImmDocumentGroup const& value, ImmAstContext const& ctx) {
    sem::DocumentGroup result = SerdeDefaultProvider<sem::DocumentGroup>::get();
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
};

/* clang-format on */