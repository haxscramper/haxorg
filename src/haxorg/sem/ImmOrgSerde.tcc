/* clang-format off */
template <>
struct ImmSemSerde<org::sem::None, org::Immsem::None> {
  static org::Immsem::None to_immer(org::sem::None const& value, ImmAstEditContext& ctx) {
    org::Immsem::None result = SerdeDefaultProvider<org::Immsem::None>::get();
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    assign_immer_field(result.loc, value.loc, ctx);
    return result;
  }
  static org::sem::None from_immer(org::Immsem::None const& value, ImmAstContext const& ctx) {
    org::sem::None result = SerdeDefaultProvider<org::sem::None>::get();
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    assign_sem_field(result.loc, value.loc, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<org::sem::ErrorItem, org::Immsem::ErrorItem> {
  static org::Immsem::ErrorItem to_immer(org::sem::ErrorItem const& value, ImmAstEditContext& ctx) {
    org::Immsem::ErrorItem result = SerdeDefaultProvider<org::Immsem::ErrorItem>::get();
    assign_immer_field(result.message, value.message, ctx);
    assign_immer_field(result.function, value.function, ctx);
    assign_immer_field(result.line, value.line, ctx);
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    assign_immer_field(result.loc, value.loc, ctx);
    return result;
  }
  static org::sem::ErrorItem from_immer(org::Immsem::ErrorItem const& value, ImmAstContext const& ctx) {
    org::sem::ErrorItem result = SerdeDefaultProvider<org::sem::ErrorItem>::get();
    assign_sem_field(result.message, value.message, ctx);
    assign_sem_field(result.function, value.function, ctx);
    assign_sem_field(result.line, value.line, ctx);
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    assign_sem_field(result.loc, value.loc, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<org::sem::ErrorGroup, org::Immsem::ErrorGroup> {
  static org::Immsem::ErrorGroup to_immer(org::sem::ErrorGroup const& value, ImmAstEditContext& ctx) {
    org::Immsem::ErrorGroup result = SerdeDefaultProvider<org::Immsem::ErrorGroup>::get();
    assign_immer_field(result.diagnostics, value.diagnostics, ctx);
    assign_immer_field(result.function, value.function, ctx);
    assign_immer_field(result.line, value.line, ctx);
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    assign_immer_field(result.loc, value.loc, ctx);
    return result;
  }
  static org::sem::ErrorGroup from_immer(org::Immsem::ErrorGroup const& value, ImmAstContext const& ctx) {
    org::sem::ErrorGroup result = SerdeDefaultProvider<org::sem::ErrorGroup>::get();
    assign_sem_field(result.diagnostics, value.diagnostics, ctx);
    assign_sem_field(result.function, value.function, ctx);
    assign_sem_field(result.line, value.line, ctx);
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    assign_sem_field(result.loc, value.loc, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<org::sem::StmtList, org::Immsem::StmtList> {
  static org::Immsem::StmtList to_immer(org::sem::StmtList const& value, ImmAstEditContext& ctx) {
    org::Immsem::StmtList result = SerdeDefaultProvider<org::Immsem::StmtList>::get();
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    assign_immer_field(result.loc, value.loc, ctx);
    return result;
  }
  static org::sem::StmtList from_immer(org::Immsem::StmtList const& value, ImmAstContext const& ctx) {
    org::sem::StmtList result = SerdeDefaultProvider<org::sem::StmtList>::get();
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    assign_sem_field(result.loc, value.loc, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<org::sem::Empty, org::Immsem::Empty> {
  static org::Immsem::Empty to_immer(org::sem::Empty const& value, ImmAstEditContext& ctx) {
    org::Immsem::Empty result = SerdeDefaultProvider<org::Immsem::Empty>::get();
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    assign_immer_field(result.loc, value.loc, ctx);
    return result;
  }
  static org::sem::Empty from_immer(org::Immsem::Empty const& value, ImmAstContext const& ctx) {
    org::sem::Empty result = SerdeDefaultProvider<org::sem::Empty>::get();
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    assign_sem_field(result.loc, value.loc, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<org::sem::CmdCaption, org::Immsem::CmdCaption> {
  static org::Immsem::CmdCaption to_immer(org::sem::CmdCaption const& value, ImmAstEditContext& ctx) {
    org::Immsem::CmdCaption result = SerdeDefaultProvider<org::Immsem::CmdCaption>::get();
    assign_immer_field(result.text, value.text, ctx);
    assign_immer_field(result.attrs, value.attrs, ctx);
    assign_immer_field(result.attached, value.attached, ctx);
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    assign_immer_field(result.loc, value.loc, ctx);
    return result;
  }
  static org::sem::CmdCaption from_immer(org::Immsem::CmdCaption const& value, ImmAstContext const& ctx) {
    org::sem::CmdCaption result = SerdeDefaultProvider<org::sem::CmdCaption>::get();
    assign_sem_field(result.text, value.text, ctx);
    assign_sem_field(result.attrs, value.attrs, ctx);
    assign_sem_field(result.attached, value.attached, ctx);
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    assign_sem_field(result.loc, value.loc, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<org::sem::CmdColumns, org::Immsem::CmdColumns> {
  static org::Immsem::CmdColumns to_immer(org::sem::CmdColumns const& value, ImmAstEditContext& ctx) {
    org::Immsem::CmdColumns result = SerdeDefaultProvider<org::Immsem::CmdColumns>::get();
    assign_immer_field(result.view, value.view, ctx);
    assign_immer_field(result.attrs, value.attrs, ctx);
    assign_immer_field(result.attached, value.attached, ctx);
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    assign_immer_field(result.loc, value.loc, ctx);
    return result;
  }
  static org::sem::CmdColumns from_immer(org::Immsem::CmdColumns const& value, ImmAstContext const& ctx) {
    org::sem::CmdColumns result = SerdeDefaultProvider<org::sem::CmdColumns>::get();
    assign_sem_field(result.view, value.view, ctx);
    assign_sem_field(result.attrs, value.attrs, ctx);
    assign_sem_field(result.attached, value.attached, ctx);
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    assign_sem_field(result.loc, value.loc, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<org::sem::CmdName, org::Immsem::CmdName> {
  static org::Immsem::CmdName to_immer(org::sem::CmdName const& value, ImmAstEditContext& ctx) {
    org::Immsem::CmdName result = SerdeDefaultProvider<org::Immsem::CmdName>::get();
    assign_immer_field(result.name, value.name, ctx);
    assign_immer_field(result.attrs, value.attrs, ctx);
    assign_immer_field(result.attached, value.attached, ctx);
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    assign_immer_field(result.loc, value.loc, ctx);
    return result;
  }
  static org::sem::CmdName from_immer(org::Immsem::CmdName const& value, ImmAstContext const& ctx) {
    org::sem::CmdName result = SerdeDefaultProvider<org::sem::CmdName>::get();
    assign_sem_field(result.name, value.name, ctx);
    assign_sem_field(result.attrs, value.attrs, ctx);
    assign_sem_field(result.attached, value.attached, ctx);
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    assign_sem_field(result.loc, value.loc, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<org::sem::CmdCustomArgs, org::Immsem::CmdCustomArgs> {
  static org::Immsem::CmdCustomArgs to_immer(org::sem::CmdCustomArgs const& value, ImmAstEditContext& ctx) {
    org::Immsem::CmdCustomArgs result = SerdeDefaultProvider<org::Immsem::CmdCustomArgs>::get();
    assign_immer_field(result.name, value.name, ctx);
    assign_immer_field(result.isAttached, value.isAttached, ctx);
    assign_immer_field(result.attrs, value.attrs, ctx);
    assign_immer_field(result.attached, value.attached, ctx);
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    assign_immer_field(result.loc, value.loc, ctx);
    return result;
  }
  static org::sem::CmdCustomArgs from_immer(org::Immsem::CmdCustomArgs const& value, ImmAstContext const& ctx) {
    org::sem::CmdCustomArgs result = SerdeDefaultProvider<org::sem::CmdCustomArgs>::get();
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
struct ImmSemSerde<org::sem::CmdCustomRaw, org::Immsem::CmdCustomRaw> {
  static org::Immsem::CmdCustomRaw to_immer(org::sem::CmdCustomRaw const& value, ImmAstEditContext& ctx) {
    org::Immsem::CmdCustomRaw result = SerdeDefaultProvider<org::Immsem::CmdCustomRaw>::get();
    assign_immer_field(result.name, value.name, ctx);
    assign_immer_field(result.isAttached, value.isAttached, ctx);
    assign_immer_field(result.text, value.text, ctx);
    assign_immer_field(result.attached, value.attached, ctx);
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    assign_immer_field(result.loc, value.loc, ctx);
    return result;
  }
  static org::sem::CmdCustomRaw from_immer(org::Immsem::CmdCustomRaw const& value, ImmAstContext const& ctx) {
    org::sem::CmdCustomRaw result = SerdeDefaultProvider<org::sem::CmdCustomRaw>::get();
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
struct ImmSemSerde<org::sem::CmdCustomText, org::Immsem::CmdCustomText> {
  static org::Immsem::CmdCustomText to_immer(org::sem::CmdCustomText const& value, ImmAstEditContext& ctx) {
    org::Immsem::CmdCustomText result = SerdeDefaultProvider<org::Immsem::CmdCustomText>::get();
    assign_immer_field(result.name, value.name, ctx);
    assign_immer_field(result.isAttached, value.isAttached, ctx);
    assign_immer_field(result.text, value.text, ctx);
    assign_immer_field(result.attached, value.attached, ctx);
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    assign_immer_field(result.loc, value.loc, ctx);
    return result;
  }
  static org::sem::CmdCustomText from_immer(org::Immsem::CmdCustomText const& value, ImmAstContext const& ctx) {
    org::sem::CmdCustomText result = SerdeDefaultProvider<org::sem::CmdCustomText>::get();
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
struct ImmSemSerde<org::sem::CmdResults, org::Immsem::CmdResults> {
  static org::Immsem::CmdResults to_immer(org::sem::CmdResults const& value, ImmAstEditContext& ctx) {
    org::Immsem::CmdResults result = SerdeDefaultProvider<org::Immsem::CmdResults>::get();
    assign_immer_field(result.attrs, value.attrs, ctx);
    assign_immer_field(result.attached, value.attached, ctx);
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    assign_immer_field(result.loc, value.loc, ctx);
    return result;
  }
  static org::sem::CmdResults from_immer(org::Immsem::CmdResults const& value, ImmAstContext const& ctx) {
    org::sem::CmdResults result = SerdeDefaultProvider<org::sem::CmdResults>::get();
    assign_sem_field(result.attrs, value.attrs, ctx);
    assign_sem_field(result.attached, value.attached, ctx);
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    assign_sem_field(result.loc, value.loc, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<org::sem::CmdTblfm, org::Immsem::CmdTblfm> {
  static org::Immsem::CmdTblfm to_immer(org::sem::CmdTblfm const& value, ImmAstEditContext& ctx) {
    org::Immsem::CmdTblfm result = SerdeDefaultProvider<org::Immsem::CmdTblfm>::get();
    assign_immer_field(result.expr, value.expr, ctx);
    assign_immer_field(result.attrs, value.attrs, ctx);
    assign_immer_field(result.attached, value.attached, ctx);
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    assign_immer_field(result.loc, value.loc, ctx);
    return result;
  }
  static org::sem::CmdTblfm from_immer(org::Immsem::CmdTblfm const& value, ImmAstContext const& ctx) {
    org::sem::CmdTblfm result = SerdeDefaultProvider<org::sem::CmdTblfm>::get();
    assign_sem_field(result.expr, value.expr, ctx);
    assign_sem_field(result.attrs, value.attrs, ctx);
    assign_sem_field(result.attached, value.attached, ctx);
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    assign_sem_field(result.loc, value.loc, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<org::sem::HashTag, org::Immsem::HashTag> {
  static org::Immsem::HashTag to_immer(org::sem::HashTag const& value, ImmAstEditContext& ctx) {
    org::Immsem::HashTag result = SerdeDefaultProvider<org::Immsem::HashTag>::get();
    assign_immer_field(result.text, value.text, ctx);
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    assign_immer_field(result.loc, value.loc, ctx);
    return result;
  }
  static org::sem::HashTag from_immer(org::Immsem::HashTag const& value, ImmAstContext const& ctx) {
    org::sem::HashTag result = SerdeDefaultProvider<org::sem::HashTag>::get();
    assign_sem_field(result.text, value.text, ctx);
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    assign_sem_field(result.loc, value.loc, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<org::sem::InlineFootnote, org::Immsem::InlineFootnote> {
  static org::Immsem::InlineFootnote to_immer(org::sem::InlineFootnote const& value, ImmAstEditContext& ctx) {
    org::Immsem::InlineFootnote result = SerdeDefaultProvider<org::Immsem::InlineFootnote>::get();
    assign_immer_field(result.tag, value.tag, ctx);
    assign_immer_field(result.definition, value.definition, ctx);
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    assign_immer_field(result.loc, value.loc, ctx);
    return result;
  }
  static org::sem::InlineFootnote from_immer(org::Immsem::InlineFootnote const& value, ImmAstContext const& ctx) {
    org::sem::InlineFootnote result = SerdeDefaultProvider<org::sem::InlineFootnote>::get();
    assign_sem_field(result.tag, value.tag, ctx);
    assign_sem_field(result.definition, value.definition, ctx);
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    assign_sem_field(result.loc, value.loc, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<org::sem::InlineExport, org::Immsem::InlineExport> {
  static org::Immsem::InlineExport to_immer(org::sem::InlineExport const& value, ImmAstEditContext& ctx) {
    org::Immsem::InlineExport result = SerdeDefaultProvider<org::Immsem::InlineExport>::get();
    assign_immer_field(result.exporter, value.exporter, ctx);
    assign_immer_field(result.content, value.content, ctx);
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    assign_immer_field(result.loc, value.loc, ctx);
    return result;
  }
  static org::sem::InlineExport from_immer(org::Immsem::InlineExport const& value, ImmAstContext const& ctx) {
    org::sem::InlineExport result = SerdeDefaultProvider<org::sem::InlineExport>::get();
    assign_sem_field(result.exporter, value.exporter, ctx);
    assign_sem_field(result.content, value.content, ctx);
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    assign_sem_field(result.loc, value.loc, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<org::sem::Time, org::Immsem::Time> {
  static org::Immsem::Time to_immer(org::sem::Time const& value, ImmAstEditContext& ctx) {
    org::Immsem::Time result = SerdeDefaultProvider<org::Immsem::Time>::get();
    assign_immer_field(result.isActive, value.isActive, ctx);
    assign_immer_field(result.time, value.time, ctx);
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    assign_immer_field(result.loc, value.loc, ctx);
    return result;
  }
  static org::sem::Time from_immer(org::Immsem::Time const& value, ImmAstContext const& ctx) {
    org::sem::Time result = SerdeDefaultProvider<org::sem::Time>::get();
    assign_sem_field(result.isActive, value.isActive, ctx);
    assign_sem_field(result.time, value.time, ctx);
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    assign_sem_field(result.loc, value.loc, ctx);
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
struct ImmSemSerde<org::sem::TimeRange, org::Immsem::TimeRange> {
  static org::Immsem::TimeRange to_immer(org::sem::TimeRange const& value, ImmAstEditContext& ctx) {
    org::Immsem::TimeRange result = SerdeDefaultProvider<org::Immsem::TimeRange>::get();
    assign_immer_field(result.from, value.from, ctx);
    assign_immer_field(result.to, value.to, ctx);
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    assign_immer_field(result.loc, value.loc, ctx);
    return result;
  }
  static org::sem::TimeRange from_immer(org::Immsem::TimeRange const& value, ImmAstContext const& ctx) {
    org::sem::TimeRange result = SerdeDefaultProvider<org::sem::TimeRange>::get();
    assign_sem_field(result.from, value.from, ctx);
    assign_sem_field(result.to, value.to, ctx);
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    assign_sem_field(result.loc, value.loc, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<org::sem::Macro, org::Immsem::Macro> {
  static org::Immsem::Macro to_immer(org::sem::Macro const& value, ImmAstEditContext& ctx) {
    org::Immsem::Macro result = SerdeDefaultProvider<org::Immsem::Macro>::get();
    assign_immer_field(result.name, value.name, ctx);
    assign_immer_field(result.attrs, value.attrs, ctx);
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    assign_immer_field(result.loc, value.loc, ctx);
    return result;
  }
  static org::sem::Macro from_immer(org::Immsem::Macro const& value, ImmAstContext const& ctx) {
    org::sem::Macro result = SerdeDefaultProvider<org::sem::Macro>::get();
    assign_sem_field(result.name, value.name, ctx);
    assign_sem_field(result.attrs, value.attrs, ctx);
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    assign_sem_field(result.loc, value.loc, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<org::sem::Symbol, org::Immsem::Symbol> {
  static org::Immsem::Symbol to_immer(org::sem::Symbol const& value, ImmAstEditContext& ctx) {
    org::Immsem::Symbol result = SerdeDefaultProvider<org::Immsem::Symbol>::get();
    assign_immer_field(result.name, value.name, ctx);
    assign_immer_field(result.parameters, value.parameters, ctx);
    assign_immer_field(result.positional, value.positional, ctx);
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    assign_immer_field(result.loc, value.loc, ctx);
    return result;
  }
  static org::sem::Symbol from_immer(org::Immsem::Symbol const& value, ImmAstContext const& ctx) {
    org::sem::Symbol result = SerdeDefaultProvider<org::sem::Symbol>::get();
    assign_sem_field(result.name, value.name, ctx);
    assign_sem_field(result.parameters, value.parameters, ctx);
    assign_sem_field(result.positional, value.positional, ctx);
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    assign_sem_field(result.loc, value.loc, ctx);
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
struct ImmSemSerde<org::sem::Escaped, org::Immsem::Escaped> {
  static org::Immsem::Escaped to_immer(org::sem::Escaped const& value, ImmAstEditContext& ctx) {
    org::Immsem::Escaped result = SerdeDefaultProvider<org::Immsem::Escaped>::get();
    assign_immer_field(result.text, value.text, ctx);
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    assign_immer_field(result.loc, value.loc, ctx);
    return result;
  }
  static org::sem::Escaped from_immer(org::Immsem::Escaped const& value, ImmAstContext const& ctx) {
    org::sem::Escaped result = SerdeDefaultProvider<org::sem::Escaped>::get();
    assign_sem_field(result.text, value.text, ctx);
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    assign_sem_field(result.loc, value.loc, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<org::sem::Newline, org::Immsem::Newline> {
  static org::Immsem::Newline to_immer(org::sem::Newline const& value, ImmAstEditContext& ctx) {
    org::Immsem::Newline result = SerdeDefaultProvider<org::Immsem::Newline>::get();
    assign_immer_field(result.text, value.text, ctx);
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    assign_immer_field(result.loc, value.loc, ctx);
    return result;
  }
  static org::sem::Newline from_immer(org::Immsem::Newline const& value, ImmAstContext const& ctx) {
    org::sem::Newline result = SerdeDefaultProvider<org::sem::Newline>::get();
    assign_sem_field(result.text, value.text, ctx);
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    assign_sem_field(result.loc, value.loc, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<org::sem::Space, org::Immsem::Space> {
  static org::Immsem::Space to_immer(org::sem::Space const& value, ImmAstEditContext& ctx) {
    org::Immsem::Space result = SerdeDefaultProvider<org::Immsem::Space>::get();
    assign_immer_field(result.text, value.text, ctx);
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    assign_immer_field(result.loc, value.loc, ctx);
    return result;
  }
  static org::sem::Space from_immer(org::Immsem::Space const& value, ImmAstContext const& ctx) {
    org::sem::Space result = SerdeDefaultProvider<org::sem::Space>::get();
    assign_sem_field(result.text, value.text, ctx);
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    assign_sem_field(result.loc, value.loc, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<org::sem::Word, org::Immsem::Word> {
  static org::Immsem::Word to_immer(org::sem::Word const& value, ImmAstEditContext& ctx) {
    org::Immsem::Word result = SerdeDefaultProvider<org::Immsem::Word>::get();
    assign_immer_field(result.text, value.text, ctx);
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    assign_immer_field(result.loc, value.loc, ctx);
    return result;
  }
  static org::sem::Word from_immer(org::Immsem::Word const& value, ImmAstContext const& ctx) {
    org::sem::Word result = SerdeDefaultProvider<org::sem::Word>::get();
    assign_sem_field(result.text, value.text, ctx);
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    assign_sem_field(result.loc, value.loc, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<org::sem::AtMention, org::Immsem::AtMention> {
  static org::Immsem::AtMention to_immer(org::sem::AtMention const& value, ImmAstEditContext& ctx) {
    org::Immsem::AtMention result = SerdeDefaultProvider<org::Immsem::AtMention>::get();
    assign_immer_field(result.text, value.text, ctx);
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    assign_immer_field(result.loc, value.loc, ctx);
    return result;
  }
  static org::sem::AtMention from_immer(org::Immsem::AtMention const& value, ImmAstContext const& ctx) {
    org::sem::AtMention result = SerdeDefaultProvider<org::sem::AtMention>::get();
    assign_sem_field(result.text, value.text, ctx);
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    assign_sem_field(result.loc, value.loc, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<org::sem::RawText, org::Immsem::RawText> {
  static org::Immsem::RawText to_immer(org::sem::RawText const& value, ImmAstEditContext& ctx) {
    org::Immsem::RawText result = SerdeDefaultProvider<org::Immsem::RawText>::get();
    assign_immer_field(result.text, value.text, ctx);
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    assign_immer_field(result.loc, value.loc, ctx);
    return result;
  }
  static org::sem::RawText from_immer(org::Immsem::RawText const& value, ImmAstContext const& ctx) {
    org::sem::RawText result = SerdeDefaultProvider<org::sem::RawText>::get();
    assign_sem_field(result.text, value.text, ctx);
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    assign_sem_field(result.loc, value.loc, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<org::sem::Punctuation, org::Immsem::Punctuation> {
  static org::Immsem::Punctuation to_immer(org::sem::Punctuation const& value, ImmAstEditContext& ctx) {
    org::Immsem::Punctuation result = SerdeDefaultProvider<org::Immsem::Punctuation>::get();
    assign_immer_field(result.text, value.text, ctx);
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    assign_immer_field(result.loc, value.loc, ctx);
    return result;
  }
  static org::sem::Punctuation from_immer(org::Immsem::Punctuation const& value, ImmAstContext const& ctx) {
    org::sem::Punctuation result = SerdeDefaultProvider<org::sem::Punctuation>::get();
    assign_sem_field(result.text, value.text, ctx);
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    assign_sem_field(result.loc, value.loc, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<org::sem::Placeholder, org::Immsem::Placeholder> {
  static org::Immsem::Placeholder to_immer(org::sem::Placeholder const& value, ImmAstEditContext& ctx) {
    org::Immsem::Placeholder result = SerdeDefaultProvider<org::Immsem::Placeholder>::get();
    assign_immer_field(result.text, value.text, ctx);
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    assign_immer_field(result.loc, value.loc, ctx);
    return result;
  }
  static org::sem::Placeholder from_immer(org::Immsem::Placeholder const& value, ImmAstContext const& ctx) {
    org::sem::Placeholder result = SerdeDefaultProvider<org::sem::Placeholder>::get();
    assign_sem_field(result.text, value.text, ctx);
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    assign_sem_field(result.loc, value.loc, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<org::sem::BigIdent, org::Immsem::BigIdent> {
  static org::Immsem::BigIdent to_immer(org::sem::BigIdent const& value, ImmAstEditContext& ctx) {
    org::Immsem::BigIdent result = SerdeDefaultProvider<org::Immsem::BigIdent>::get();
    assign_immer_field(result.text, value.text, ctx);
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    assign_immer_field(result.loc, value.loc, ctx);
    return result;
  }
  static org::sem::BigIdent from_immer(org::Immsem::BigIdent const& value, ImmAstContext const& ctx) {
    org::sem::BigIdent result = SerdeDefaultProvider<org::sem::BigIdent>::get();
    assign_sem_field(result.text, value.text, ctx);
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    assign_sem_field(result.loc, value.loc, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<org::sem::TextTarget, org::Immsem::TextTarget> {
  static org::Immsem::TextTarget to_immer(org::sem::TextTarget const& value, ImmAstEditContext& ctx) {
    org::Immsem::TextTarget result = SerdeDefaultProvider<org::Immsem::TextTarget>::get();
    assign_immer_field(result.text, value.text, ctx);
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    assign_immer_field(result.loc, value.loc, ctx);
    return result;
  }
  static org::sem::TextTarget from_immer(org::Immsem::TextTarget const& value, ImmAstContext const& ctx) {
    org::sem::TextTarget result = SerdeDefaultProvider<org::sem::TextTarget>::get();
    assign_sem_field(result.text, value.text, ctx);
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    assign_sem_field(result.loc, value.loc, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<org::sem::Bold, org::Immsem::Bold> {
  static org::Immsem::Bold to_immer(org::sem::Bold const& value, ImmAstEditContext& ctx) {
    org::Immsem::Bold result = SerdeDefaultProvider<org::Immsem::Bold>::get();
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    assign_immer_field(result.loc, value.loc, ctx);
    return result;
  }
  static org::sem::Bold from_immer(org::Immsem::Bold const& value, ImmAstContext const& ctx) {
    org::sem::Bold result = SerdeDefaultProvider<org::sem::Bold>::get();
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    assign_sem_field(result.loc, value.loc, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<org::sem::Underline, org::Immsem::Underline> {
  static org::Immsem::Underline to_immer(org::sem::Underline const& value, ImmAstEditContext& ctx) {
    org::Immsem::Underline result = SerdeDefaultProvider<org::Immsem::Underline>::get();
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    assign_immer_field(result.loc, value.loc, ctx);
    return result;
  }
  static org::sem::Underline from_immer(org::Immsem::Underline const& value, ImmAstContext const& ctx) {
    org::sem::Underline result = SerdeDefaultProvider<org::sem::Underline>::get();
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    assign_sem_field(result.loc, value.loc, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<org::sem::Monospace, org::Immsem::Monospace> {
  static org::Immsem::Monospace to_immer(org::sem::Monospace const& value, ImmAstEditContext& ctx) {
    org::Immsem::Monospace result = SerdeDefaultProvider<org::Immsem::Monospace>::get();
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    assign_immer_field(result.loc, value.loc, ctx);
    return result;
  }
  static org::sem::Monospace from_immer(org::Immsem::Monospace const& value, ImmAstContext const& ctx) {
    org::sem::Monospace result = SerdeDefaultProvider<org::sem::Monospace>::get();
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    assign_sem_field(result.loc, value.loc, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<org::sem::MarkQuote, org::Immsem::MarkQuote> {
  static org::Immsem::MarkQuote to_immer(org::sem::MarkQuote const& value, ImmAstEditContext& ctx) {
    org::Immsem::MarkQuote result = SerdeDefaultProvider<org::Immsem::MarkQuote>::get();
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    assign_immer_field(result.loc, value.loc, ctx);
    return result;
  }
  static org::sem::MarkQuote from_immer(org::Immsem::MarkQuote const& value, ImmAstContext const& ctx) {
    org::sem::MarkQuote result = SerdeDefaultProvider<org::sem::MarkQuote>::get();
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    assign_sem_field(result.loc, value.loc, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<org::sem::Verbatim, org::Immsem::Verbatim> {
  static org::Immsem::Verbatim to_immer(org::sem::Verbatim const& value, ImmAstEditContext& ctx) {
    org::Immsem::Verbatim result = SerdeDefaultProvider<org::Immsem::Verbatim>::get();
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    assign_immer_field(result.loc, value.loc, ctx);
    return result;
  }
  static org::sem::Verbatim from_immer(org::Immsem::Verbatim const& value, ImmAstContext const& ctx) {
    org::sem::Verbatim result = SerdeDefaultProvider<org::sem::Verbatim>::get();
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    assign_sem_field(result.loc, value.loc, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<org::sem::Italic, org::Immsem::Italic> {
  static org::Immsem::Italic to_immer(org::sem::Italic const& value, ImmAstEditContext& ctx) {
    org::Immsem::Italic result = SerdeDefaultProvider<org::Immsem::Italic>::get();
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    assign_immer_field(result.loc, value.loc, ctx);
    return result;
  }
  static org::sem::Italic from_immer(org::Immsem::Italic const& value, ImmAstContext const& ctx) {
    org::sem::Italic result = SerdeDefaultProvider<org::sem::Italic>::get();
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    assign_sem_field(result.loc, value.loc, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<org::sem::Strike, org::Immsem::Strike> {
  static org::Immsem::Strike to_immer(org::sem::Strike const& value, ImmAstEditContext& ctx) {
    org::Immsem::Strike result = SerdeDefaultProvider<org::Immsem::Strike>::get();
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    assign_immer_field(result.loc, value.loc, ctx);
    return result;
  }
  static org::sem::Strike from_immer(org::Immsem::Strike const& value, ImmAstContext const& ctx) {
    org::sem::Strike result = SerdeDefaultProvider<org::sem::Strike>::get();
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    assign_sem_field(result.loc, value.loc, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<org::sem::Par, org::Immsem::Par> {
  static org::Immsem::Par to_immer(org::sem::Par const& value, ImmAstEditContext& ctx) {
    org::Immsem::Par result = SerdeDefaultProvider<org::Immsem::Par>::get();
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    assign_immer_field(result.loc, value.loc, ctx);
    return result;
  }
  static org::sem::Par from_immer(org::Immsem::Par const& value, ImmAstContext const& ctx) {
    org::sem::Par result = SerdeDefaultProvider<org::sem::Par>::get();
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    assign_sem_field(result.loc, value.loc, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<org::sem::RadioTarget, org::Immsem::RadioTarget> {
  static org::Immsem::RadioTarget to_immer(org::sem::RadioTarget const& value, ImmAstEditContext& ctx) {
    org::Immsem::RadioTarget result = SerdeDefaultProvider<org::Immsem::RadioTarget>::get();
    assign_immer_field(result.words, value.words, ctx);
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    assign_immer_field(result.loc, value.loc, ctx);
    return result;
  }
  static org::sem::RadioTarget from_immer(org::Immsem::RadioTarget const& value, ImmAstContext const& ctx) {
    org::sem::RadioTarget result = SerdeDefaultProvider<org::sem::RadioTarget>::get();
    assign_sem_field(result.words, value.words, ctx);
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    assign_sem_field(result.loc, value.loc, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<org::sem::Latex, org::Immsem::Latex> {
  static org::Immsem::Latex to_immer(org::sem::Latex const& value, ImmAstEditContext& ctx) {
    org::Immsem::Latex result = SerdeDefaultProvider<org::Immsem::Latex>::get();
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    assign_immer_field(result.loc, value.loc, ctx);
    return result;
  }
  static org::sem::Latex from_immer(org::Immsem::Latex const& value, ImmAstContext const& ctx) {
    org::sem::Latex result = SerdeDefaultProvider<org::sem::Latex>::get();
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    assign_sem_field(result.loc, value.loc, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<org::sem::Link, org::Immsem::Link> {
  static org::Immsem::Link to_immer(org::sem::Link const& value, ImmAstEditContext& ctx) {
    org::Immsem::Link result = SerdeDefaultProvider<org::Immsem::Link>::get();
    assign_immer_field(result.description, value.description, ctx);
    assign_immer_field(result.target, value.target, ctx);
    assign_immer_field(result.attached, value.attached, ctx);
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    assign_immer_field(result.loc, value.loc, ctx);
    return result;
  }
  static org::sem::Link from_immer(org::Immsem::Link const& value, ImmAstContext const& ctx) {
    org::sem::Link result = SerdeDefaultProvider<org::sem::Link>::get();
    assign_sem_field(result.description, value.description, ctx);
    assign_sem_field(result.target, value.target, ctx);
    assign_sem_field(result.attached, value.attached, ctx);
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    assign_sem_field(result.loc, value.loc, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<org::sem::BlockCenter, org::Immsem::BlockCenter> {
  static org::Immsem::BlockCenter to_immer(org::sem::BlockCenter const& value, ImmAstEditContext& ctx) {
    org::Immsem::BlockCenter result = SerdeDefaultProvider<org::Immsem::BlockCenter>::get();
    assign_immer_field(result.attrs, value.attrs, ctx);
    assign_immer_field(result.attached, value.attached, ctx);
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    assign_immer_field(result.loc, value.loc, ctx);
    return result;
  }
  static org::sem::BlockCenter from_immer(org::Immsem::BlockCenter const& value, ImmAstContext const& ctx) {
    org::sem::BlockCenter result = SerdeDefaultProvider<org::sem::BlockCenter>::get();
    assign_sem_field(result.attrs, value.attrs, ctx);
    assign_sem_field(result.attached, value.attached, ctx);
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    assign_sem_field(result.loc, value.loc, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<org::sem::BlockQuote, org::Immsem::BlockQuote> {
  static org::Immsem::BlockQuote to_immer(org::sem::BlockQuote const& value, ImmAstEditContext& ctx) {
    org::Immsem::BlockQuote result = SerdeDefaultProvider<org::Immsem::BlockQuote>::get();
    assign_immer_field(result.attrs, value.attrs, ctx);
    assign_immer_field(result.attached, value.attached, ctx);
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    assign_immer_field(result.loc, value.loc, ctx);
    return result;
  }
  static org::sem::BlockQuote from_immer(org::Immsem::BlockQuote const& value, ImmAstContext const& ctx) {
    org::sem::BlockQuote result = SerdeDefaultProvider<org::sem::BlockQuote>::get();
    assign_sem_field(result.attrs, value.attrs, ctx);
    assign_sem_field(result.attached, value.attached, ctx);
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    assign_sem_field(result.loc, value.loc, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<org::sem::BlockComment, org::Immsem::BlockComment> {
  static org::Immsem::BlockComment to_immer(org::sem::BlockComment const& value, ImmAstEditContext& ctx) {
    org::Immsem::BlockComment result = SerdeDefaultProvider<org::Immsem::BlockComment>::get();
    assign_immer_field(result.attached, value.attached, ctx);
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    assign_immer_field(result.loc, value.loc, ctx);
    return result;
  }
  static org::sem::BlockComment from_immer(org::Immsem::BlockComment const& value, ImmAstContext const& ctx) {
    org::sem::BlockComment result = SerdeDefaultProvider<org::sem::BlockComment>::get();
    assign_sem_field(result.attached, value.attached, ctx);
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    assign_sem_field(result.loc, value.loc, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<org::sem::BlockVerse, org::Immsem::BlockVerse> {
  static org::Immsem::BlockVerse to_immer(org::sem::BlockVerse const& value, ImmAstEditContext& ctx) {
    org::Immsem::BlockVerse result = SerdeDefaultProvider<org::Immsem::BlockVerse>::get();
    assign_immer_field(result.attrs, value.attrs, ctx);
    assign_immer_field(result.attached, value.attached, ctx);
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    assign_immer_field(result.loc, value.loc, ctx);
    return result;
  }
  static org::sem::BlockVerse from_immer(org::Immsem::BlockVerse const& value, ImmAstContext const& ctx) {
    org::sem::BlockVerse result = SerdeDefaultProvider<org::sem::BlockVerse>::get();
    assign_sem_field(result.attrs, value.attrs, ctx);
    assign_sem_field(result.attached, value.attached, ctx);
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    assign_sem_field(result.loc, value.loc, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<org::sem::BlockDynamicFallback, org::Immsem::BlockDynamicFallback> {
  static org::Immsem::BlockDynamicFallback to_immer(org::sem::BlockDynamicFallback const& value, ImmAstEditContext& ctx) {
    org::Immsem::BlockDynamicFallback result = SerdeDefaultProvider<org::Immsem::BlockDynamicFallback>::get();
    assign_immer_field(result.name, value.name, ctx);
    assign_immer_field(result.attrs, value.attrs, ctx);
    assign_immer_field(result.attached, value.attached, ctx);
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    assign_immer_field(result.loc, value.loc, ctx);
    return result;
  }
  static org::sem::BlockDynamicFallback from_immer(org::Immsem::BlockDynamicFallback const& value, ImmAstContext const& ctx) {
    org::sem::BlockDynamicFallback result = SerdeDefaultProvider<org::sem::BlockDynamicFallback>::get();
    assign_sem_field(result.name, value.name, ctx);
    assign_sem_field(result.attrs, value.attrs, ctx);
    assign_sem_field(result.attached, value.attached, ctx);
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    assign_sem_field(result.loc, value.loc, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<org::sem::BlockExample, org::Immsem::BlockExample> {
  static org::Immsem::BlockExample to_immer(org::sem::BlockExample const& value, ImmAstEditContext& ctx) {
    org::Immsem::BlockExample result = SerdeDefaultProvider<org::Immsem::BlockExample>::get();
    assign_immer_field(result.attrs, value.attrs, ctx);
    assign_immer_field(result.attached, value.attached, ctx);
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    assign_immer_field(result.loc, value.loc, ctx);
    return result;
  }
  static org::sem::BlockExample from_immer(org::Immsem::BlockExample const& value, ImmAstContext const& ctx) {
    org::sem::BlockExample result = SerdeDefaultProvider<org::sem::BlockExample>::get();
    assign_sem_field(result.attrs, value.attrs, ctx);
    assign_sem_field(result.attached, value.attached, ctx);
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    assign_sem_field(result.loc, value.loc, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<org::sem::BlockExport, org::Immsem::BlockExport> {
  static org::Immsem::BlockExport to_immer(org::sem::BlockExport const& value, ImmAstEditContext& ctx) {
    org::Immsem::BlockExport result = SerdeDefaultProvider<org::Immsem::BlockExport>::get();
    assign_immer_field(result.exporter, value.exporter, ctx);
    assign_immer_field(result.content, value.content, ctx);
    assign_immer_field(result.attrs, value.attrs, ctx);
    assign_immer_field(result.attached, value.attached, ctx);
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    assign_immer_field(result.loc, value.loc, ctx);
    return result;
  }
  static org::sem::BlockExport from_immer(org::Immsem::BlockExport const& value, ImmAstContext const& ctx) {
    org::sem::BlockExport result = SerdeDefaultProvider<org::sem::BlockExport>::get();
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
struct ImmSemSerde<org::sem::BlockAdmonition, org::Immsem::BlockAdmonition> {
  static org::Immsem::BlockAdmonition to_immer(org::sem::BlockAdmonition const& value, ImmAstEditContext& ctx) {
    org::Immsem::BlockAdmonition result = SerdeDefaultProvider<org::Immsem::BlockAdmonition>::get();
    assign_immer_field(result.attrs, value.attrs, ctx);
    assign_immer_field(result.attached, value.attached, ctx);
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    assign_immer_field(result.loc, value.loc, ctx);
    return result;
  }
  static org::sem::BlockAdmonition from_immer(org::Immsem::BlockAdmonition const& value, ImmAstContext const& ctx) {
    org::sem::BlockAdmonition result = SerdeDefaultProvider<org::sem::BlockAdmonition>::get();
    assign_sem_field(result.attrs, value.attrs, ctx);
    assign_sem_field(result.attached, value.attached, ctx);
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    assign_sem_field(result.loc, value.loc, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<org::sem::BlockCode, org::Immsem::BlockCode> {
  static org::Immsem::BlockCode to_immer(org::sem::BlockCode const& value, ImmAstEditContext& ctx) {
    org::Immsem::BlockCode result = SerdeDefaultProvider<org::Immsem::BlockCode>::get();
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
    assign_immer_field(result.loc, value.loc, ctx);
    return result;
  }
  static org::sem::BlockCode from_immer(org::Immsem::BlockCode const& value, ImmAstContext const& ctx) {
    org::sem::BlockCode result = SerdeDefaultProvider<org::sem::BlockCode>::get();
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
    assign_sem_field(result.loc, value.loc, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<org::sem::SubtreeLog, org::Immsem::SubtreeLog> {
  static org::Immsem::SubtreeLog to_immer(org::sem::SubtreeLog const& value, ImmAstEditContext& ctx) {
    org::Immsem::SubtreeLog result = SerdeDefaultProvider<org::Immsem::SubtreeLog>::get();
    assign_immer_field(result.head, value.head, ctx);
    assign_immer_field(result.desc, value.desc, ctx);
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    assign_immer_field(result.loc, value.loc, ctx);
    return result;
  }
  static org::sem::SubtreeLog from_immer(org::Immsem::SubtreeLog const& value, ImmAstContext const& ctx) {
    org::sem::SubtreeLog result = SerdeDefaultProvider<org::sem::SubtreeLog>::get();
    assign_sem_field(result.head, value.head, ctx);
    assign_sem_field(result.desc, value.desc, ctx);
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    assign_sem_field(result.loc, value.loc, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<org::sem::Subtree, org::Immsem::Subtree> {
  static org::Immsem::Subtree to_immer(org::sem::Subtree const& value, ImmAstEditContext& ctx) {
    org::Immsem::Subtree result = SerdeDefaultProvider<org::Immsem::Subtree>::get();
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
  static org::sem::Subtree from_immer(org::Immsem::Subtree const& value, ImmAstContext const& ctx) {
    org::sem::Subtree result = SerdeDefaultProvider<org::sem::Subtree>::get();
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
struct ImmSemSerde<org::sem::Cell, org::Immsem::Cell> {
  static org::Immsem::Cell to_immer(org::sem::Cell const& value, ImmAstEditContext& ctx) {
    org::Immsem::Cell result = SerdeDefaultProvider<org::Immsem::Cell>::get();
    assign_immer_field(result.isBlock, value.isBlock, ctx);
    assign_immer_field(result.attrs, value.attrs, ctx);
    assign_immer_field(result.attached, value.attached, ctx);
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    assign_immer_field(result.loc, value.loc, ctx);
    return result;
  }
  static org::sem::Cell from_immer(org::Immsem::Cell const& value, ImmAstContext const& ctx) {
    org::sem::Cell result = SerdeDefaultProvider<org::sem::Cell>::get();
    assign_sem_field(result.isBlock, value.isBlock, ctx);
    assign_sem_field(result.attrs, value.attrs, ctx);
    assign_sem_field(result.attached, value.attached, ctx);
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    assign_sem_field(result.loc, value.loc, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<org::sem::Row, org::Immsem::Row> {
  static org::Immsem::Row to_immer(org::sem::Row const& value, ImmAstEditContext& ctx) {
    org::Immsem::Row result = SerdeDefaultProvider<org::Immsem::Row>::get();
    assign_immer_field(result.cells, value.cells, ctx);
    assign_immer_field(result.isBlock, value.isBlock, ctx);
    assign_immer_field(result.attrs, value.attrs, ctx);
    assign_immer_field(result.attached, value.attached, ctx);
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    assign_immer_field(result.loc, value.loc, ctx);
    return result;
  }
  static org::sem::Row from_immer(org::Immsem::Row const& value, ImmAstContext const& ctx) {
    org::sem::Row result = SerdeDefaultProvider<org::sem::Row>::get();
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
struct ImmSemSerde<org::sem::Table, org::Immsem::Table> {
  static org::Immsem::Table to_immer(org::sem::Table const& value, ImmAstEditContext& ctx) {
    org::Immsem::Table result = SerdeDefaultProvider<org::Immsem::Table>::get();
    assign_immer_field(result.rows, value.rows, ctx);
    assign_immer_field(result.isBlock, value.isBlock, ctx);
    assign_immer_field(result.attrs, value.attrs, ctx);
    assign_immer_field(result.attached, value.attached, ctx);
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    assign_immer_field(result.loc, value.loc, ctx);
    return result;
  }
  static org::sem::Table from_immer(org::Immsem::Table const& value, ImmAstContext const& ctx) {
    org::sem::Table result = SerdeDefaultProvider<org::sem::Table>::get();
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
struct ImmSemSerde<org::sem::Paragraph, org::Immsem::Paragraph> {
  static org::Immsem::Paragraph to_immer(org::sem::Paragraph const& value, ImmAstEditContext& ctx) {
    org::Immsem::Paragraph result = SerdeDefaultProvider<org::Immsem::Paragraph>::get();
    assign_immer_field(result.attached, value.attached, ctx);
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    assign_immer_field(result.loc, value.loc, ctx);
    return result;
  }
  static org::sem::Paragraph from_immer(org::Immsem::Paragraph const& value, ImmAstContext const& ctx) {
    org::sem::Paragraph result = SerdeDefaultProvider<org::sem::Paragraph>::get();
    assign_sem_field(result.attached, value.attached, ctx);
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    assign_sem_field(result.loc, value.loc, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<org::sem::ColonExample, org::Immsem::ColonExample> {
  static org::Immsem::ColonExample to_immer(org::sem::ColonExample const& value, ImmAstEditContext& ctx) {
    org::Immsem::ColonExample result = SerdeDefaultProvider<org::Immsem::ColonExample>::get();
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    assign_immer_field(result.loc, value.loc, ctx);
    return result;
  }
  static org::sem::ColonExample from_immer(org::Immsem::ColonExample const& value, ImmAstContext const& ctx) {
    org::sem::ColonExample result = SerdeDefaultProvider<org::sem::ColonExample>::get();
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    assign_sem_field(result.loc, value.loc, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<org::sem::CmdAttr, org::Immsem::CmdAttr> {
  static org::Immsem::CmdAttr to_immer(org::sem::CmdAttr const& value, ImmAstEditContext& ctx) {
    org::Immsem::CmdAttr result = SerdeDefaultProvider<org::Immsem::CmdAttr>::get();
    assign_immer_field(result.target, value.target, ctx);
    assign_immer_field(result.attrs, value.attrs, ctx);
    assign_immer_field(result.attached, value.attached, ctx);
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    assign_immer_field(result.loc, value.loc, ctx);
    return result;
  }
  static org::sem::CmdAttr from_immer(org::Immsem::CmdAttr const& value, ImmAstContext const& ctx) {
    org::sem::CmdAttr result = SerdeDefaultProvider<org::sem::CmdAttr>::get();
    assign_sem_field(result.target, value.target, ctx);
    assign_sem_field(result.attrs, value.attrs, ctx);
    assign_sem_field(result.attached, value.attached, ctx);
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    assign_sem_field(result.loc, value.loc, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<org::sem::CmdExport, org::Immsem::CmdExport> {
  static org::Immsem::CmdExport to_immer(org::sem::CmdExport const& value, ImmAstEditContext& ctx) {
    org::Immsem::CmdExport result = SerdeDefaultProvider<org::Immsem::CmdExport>::get();
    assign_immer_field(result.exporter, value.exporter, ctx);
    assign_immer_field(result.content, value.content, ctx);
    assign_immer_field(result.attrs, value.attrs, ctx);
    assign_immer_field(result.attached, value.attached, ctx);
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    assign_immer_field(result.loc, value.loc, ctx);
    return result;
  }
  static org::sem::CmdExport from_immer(org::Immsem::CmdExport const& value, ImmAstContext const& ctx) {
    org::sem::CmdExport result = SerdeDefaultProvider<org::sem::CmdExport>::get();
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
struct ImmSemSerde<org::sem::Call, org::Immsem::Call> {
  static org::Immsem::Call to_immer(org::sem::Call const& value, ImmAstEditContext& ctx) {
    org::Immsem::Call result = SerdeDefaultProvider<org::Immsem::Call>::get();
    assign_immer_field(result.name, value.name, ctx);
    assign_immer_field(result.attrs, value.attrs, ctx);
    assign_immer_field(result.isCommand, value.isCommand, ctx);
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    assign_immer_field(result.loc, value.loc, ctx);
    return result;
  }
  static org::sem::Call from_immer(org::Immsem::Call const& value, ImmAstContext const& ctx) {
    org::sem::Call result = SerdeDefaultProvider<org::sem::Call>::get();
    assign_sem_field(result.name, value.name, ctx);
    assign_sem_field(result.attrs, value.attrs, ctx);
    assign_sem_field(result.isCommand, value.isCommand, ctx);
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    assign_sem_field(result.loc, value.loc, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<org::sem::List, org::Immsem::List> {
  static org::Immsem::List to_immer(org::sem::List const& value, ImmAstEditContext& ctx) {
    org::Immsem::List result = SerdeDefaultProvider<org::Immsem::List>::get();
    assign_immer_field(result.attached, value.attached, ctx);
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    assign_immer_field(result.loc, value.loc, ctx);
    return result;
  }
  static org::sem::List from_immer(org::Immsem::List const& value, ImmAstContext const& ctx) {
    org::sem::List result = SerdeDefaultProvider<org::sem::List>::get();
    assign_sem_field(result.attached, value.attached, ctx);
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    assign_sem_field(result.loc, value.loc, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<org::sem::ListItem, org::Immsem::ListItem> {
  static org::Immsem::ListItem to_immer(org::sem::ListItem const& value, ImmAstEditContext& ctx) {
    org::Immsem::ListItem result = SerdeDefaultProvider<org::Immsem::ListItem>::get();
    assign_immer_field(result.checkbox, value.checkbox, ctx);
    assign_immer_field(result.header, value.header, ctx);
    assign_immer_field(result.bullet, value.bullet, ctx);
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    assign_immer_field(result.loc, value.loc, ctx);
    return result;
  }
  static org::sem::ListItem from_immer(org::Immsem::ListItem const& value, ImmAstContext const& ctx) {
    org::sem::ListItem result = SerdeDefaultProvider<org::sem::ListItem>::get();
    assign_sem_field(result.checkbox, value.checkbox, ctx);
    assign_sem_field(result.header, value.header, ctx);
    assign_sem_field(result.bullet, value.bullet, ctx);
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    assign_sem_field(result.loc, value.loc, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<org::sem::DocumentOptions, org::Immsem::DocumentOptions> {
  static org::Immsem::DocumentOptions to_immer(org::sem::DocumentOptions const& value, ImmAstEditContext& ctx) {
    org::Immsem::DocumentOptions result = SerdeDefaultProvider<org::Immsem::DocumentOptions>::get();
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
  static org::sem::DocumentOptions from_immer(org::Immsem::DocumentOptions const& value, ImmAstContext const& ctx) {
    org::sem::DocumentOptions result = SerdeDefaultProvider<org::sem::DocumentOptions>::get();
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
struct ImmSemSerde<org::sem::Document, org::Immsem::Document> {
  static org::Immsem::Document to_immer(org::sem::Document const& value, ImmAstEditContext& ctx) {
    org::Immsem::Document result = SerdeDefaultProvider<org::Immsem::Document>::get();
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
  static org::sem::Document from_immer(org::Immsem::Document const& value, ImmAstContext const& ctx) {
    org::sem::Document result = SerdeDefaultProvider<org::sem::Document>::get();
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
struct ImmSemSerde<org::sem::FileTarget, org::Immsem::FileTarget> {
  static org::Immsem::FileTarget to_immer(org::sem::FileTarget const& value, ImmAstEditContext& ctx) {
    org::Immsem::FileTarget result = SerdeDefaultProvider<org::Immsem::FileTarget>::get();
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
  static org::sem::FileTarget from_immer(org::Immsem::FileTarget const& value, ImmAstContext const& ctx) {
    org::sem::FileTarget result = SerdeDefaultProvider<org::sem::FileTarget>::get();
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
struct ImmSemSerde<org::sem::TextSeparator, org::Immsem::TextSeparator> {
  static org::Immsem::TextSeparator to_immer(org::sem::TextSeparator const& value, ImmAstEditContext& ctx) {
    org::Immsem::TextSeparator result = SerdeDefaultProvider<org::Immsem::TextSeparator>::get();
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    assign_immer_field(result.loc, value.loc, ctx);
    return result;
  }
  static org::sem::TextSeparator from_immer(org::Immsem::TextSeparator const& value, ImmAstContext const& ctx) {
    org::sem::TextSeparator result = SerdeDefaultProvider<org::sem::TextSeparator>::get();
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    assign_sem_field(result.loc, value.loc, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<org::sem::DocumentGroup, org::Immsem::DocumentGroup> {
  static org::Immsem::DocumentGroup to_immer(org::sem::DocumentGroup const& value, ImmAstEditContext& ctx) {
    org::Immsem::DocumentGroup result = SerdeDefaultProvider<org::Immsem::DocumentGroup>::get();
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    assign_immer_field(result.loc, value.loc, ctx);
    return result;
  }
  static org::sem::DocumentGroup from_immer(org::Immsem::DocumentGroup const& value, ImmAstContext const& ctx) {
    org::sem::DocumentGroup result = SerdeDefaultProvider<org::sem::DocumentGroup>::get();
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    assign_sem_field(result.loc, value.loc, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<org::sem::File, org::Immsem::File> {
  static org::Immsem::File to_immer(org::sem::File const& value, ImmAstEditContext& ctx) {
    org::Immsem::File result = SerdeDefaultProvider<org::Immsem::File>::get();
    assign_immer_field(result.relPath, value.relPath, ctx);
    assign_immer_field(result.absPath, value.absPath, ctx);
    assign_immer_field(result.data, value.data, ctx);
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    assign_immer_field(result.loc, value.loc, ctx);
    return result;
  }
  static org::sem::File from_immer(org::Immsem::File const& value, ImmAstContext const& ctx) {
    org::sem::File result = SerdeDefaultProvider<org::sem::File>::get();
    assign_sem_field(result.relPath, value.relPath, ctx);
    assign_sem_field(result.absPath, value.absPath, ctx);
    assign_sem_field(result.data, value.data, ctx);
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    assign_sem_field(result.loc, value.loc, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<sem::File::Document, org::ImmFile::Document> {
  static org::ImmFile::Document to_immer(sem::File::Document const& value, ImmAstEditContext& ctx) {
    org::ImmFile::Document result = SerdeDefaultProvider<org::ImmFile::Document>::get();
    return result;
  }
  static sem::File::Document from_immer(org::ImmFile::Document const& value, ImmAstContext const& ctx) {
    sem::File::Document result = SerdeDefaultProvider<sem::File::Document>::get();
    return result;
  }
};

template <>
struct ImmSemSerde<sem::File::Attachment, org::ImmFile::Attachment> {
  static org::ImmFile::Attachment to_immer(sem::File::Attachment const& value, ImmAstEditContext& ctx) {
    org::ImmFile::Attachment result = SerdeDefaultProvider<org::ImmFile::Attachment>::get();
    return result;
  }
  static sem::File::Attachment from_immer(org::ImmFile::Attachment const& value, ImmAstContext const& ctx) {
    sem::File::Attachment result = SerdeDefaultProvider<sem::File::Attachment>::get();
    return result;
  }
};

template <>
struct ImmSemSerde<sem::File::Source, org::ImmFile::Source> {
  static org::ImmFile::Source to_immer(sem::File::Source const& value, ImmAstEditContext& ctx) {
    org::ImmFile::Source result = SerdeDefaultProvider<org::ImmFile::Source>::get();
    return result;
  }
  static sem::File::Source from_immer(org::ImmFile::Source const& value, ImmAstContext const& ctx) {
    sem::File::Source result = SerdeDefaultProvider<sem::File::Source>::get();
    return result;
  }
};

template <>
struct ImmSemSerde<org::sem::Directory, org::Immsem::Directory> {
  static org::Immsem::Directory to_immer(org::sem::Directory const& value, ImmAstEditContext& ctx) {
    org::Immsem::Directory result = SerdeDefaultProvider<org::Immsem::Directory>::get();
    assign_immer_field(result.relPath, value.relPath, ctx);
    assign_immer_field(result.absPath, value.absPath, ctx);
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    assign_immer_field(result.loc, value.loc, ctx);
    return result;
  }
  static org::sem::Directory from_immer(org::Immsem::Directory const& value, ImmAstContext const& ctx) {
    org::sem::Directory result = SerdeDefaultProvider<org::sem::Directory>::get();
    assign_sem_field(result.relPath, value.relPath, ctx);
    assign_sem_field(result.absPath, value.absPath, ctx);
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    assign_sem_field(result.loc, value.loc, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<org::sem::Symlink, org::Immsem::Symlink> {
  static org::Immsem::Symlink to_immer(org::sem::Symlink const& value, ImmAstEditContext& ctx) {
    org::Immsem::Symlink result = SerdeDefaultProvider<org::Immsem::Symlink>::get();
    assign_immer_field(result.isDirectory, value.isDirectory, ctx);
    assign_immer_field(result.absPath, value.absPath, ctx);
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    assign_immer_field(result.loc, value.loc, ctx);
    return result;
  }
  static org::sem::Symlink from_immer(org::Immsem::Symlink const& value, ImmAstContext const& ctx) {
    org::sem::Symlink result = SerdeDefaultProvider<org::sem::Symlink>::get();
    assign_sem_field(result.isDirectory, value.isDirectory, ctx);
    assign_sem_field(result.absPath, value.absPath, ctx);
    assign_sem_field(result.subnodes, value.subnodes, ctx);
    assign_sem_field(result.loc, value.loc, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<org::sem::CmdInclude, org::Immsem::CmdInclude> {
  static org::Immsem::CmdInclude to_immer(org::sem::CmdInclude const& value, ImmAstEditContext& ctx) {
    org::Immsem::CmdInclude result = SerdeDefaultProvider<org::Immsem::CmdInclude>::get();
    assign_immer_field(result.path, value.path, ctx);
    assign_immer_field(result.firstLine, value.firstLine, ctx);
    assign_immer_field(result.lastLine, value.lastLine, ctx);
    assign_immer_field(result.data, value.data, ctx);
    assign_immer_field(result.subnodes, value.subnodes, ctx);
    assign_immer_field(result.loc, value.loc, ctx);
    return result;
  }
  static org::sem::CmdInclude from_immer(org::Immsem::CmdInclude const& value, ImmAstContext const& ctx) {
    org::sem::CmdInclude result = SerdeDefaultProvider<org::sem::CmdInclude>::get();
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
struct ImmSemSerde<sem::CmdInclude::IncludeBase, org::ImmCmdInclude::IncludeBase> {
  static org::ImmCmdInclude::IncludeBase to_immer(sem::CmdInclude::IncludeBase const& value, ImmAstEditContext& ctx) {
    org::ImmCmdInclude::IncludeBase result = SerdeDefaultProvider<org::ImmCmdInclude::IncludeBase>::get();
    return result;
  }
  static sem::CmdInclude::IncludeBase from_immer(org::ImmCmdInclude::IncludeBase const& value, ImmAstContext const& ctx) {
    sem::CmdInclude::IncludeBase result = SerdeDefaultProvider<sem::CmdInclude::IncludeBase>::get();
    return result;
  }
};

template <>
struct ImmSemSerde<sem::CmdInclude::Example, org::ImmCmdInclude::Example> {
  static org::ImmCmdInclude::Example to_immer(sem::CmdInclude::Example const& value, ImmAstEditContext& ctx) {
    org::ImmCmdInclude::Example result = SerdeDefaultProvider<org::ImmCmdInclude::Example>::get();
    return result;
  }
  static sem::CmdInclude::Example from_immer(org::ImmCmdInclude::Example const& value, ImmAstContext const& ctx) {
    sem::CmdInclude::Example result = SerdeDefaultProvider<sem::CmdInclude::Example>::get();
    return result;
  }
};

template <>
struct ImmSemSerde<sem::CmdInclude::Export, org::ImmCmdInclude::Export> {
  static org::ImmCmdInclude::Export to_immer(sem::CmdInclude::Export const& value, ImmAstEditContext& ctx) {
    org::ImmCmdInclude::Export result = SerdeDefaultProvider<org::ImmCmdInclude::Export>::get();
    assign_immer_field(result.language, value.language, ctx);
    return result;
  }
  static sem::CmdInclude::Export from_immer(org::ImmCmdInclude::Export const& value, ImmAstContext const& ctx) {
    sem::CmdInclude::Export result = SerdeDefaultProvider<sem::CmdInclude::Export>::get();
    assign_sem_field(result.language, value.language, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<sem::CmdInclude::Custom, org::ImmCmdInclude::Custom> {
  static org::ImmCmdInclude::Custom to_immer(sem::CmdInclude::Custom const& value, ImmAstEditContext& ctx) {
    org::ImmCmdInclude::Custom result = SerdeDefaultProvider<org::ImmCmdInclude::Custom>::get();
    assign_immer_field(result.blockName, value.blockName, ctx);
    return result;
  }
  static sem::CmdInclude::Custom from_immer(org::ImmCmdInclude::Custom const& value, ImmAstContext const& ctx) {
    sem::CmdInclude::Custom result = SerdeDefaultProvider<sem::CmdInclude::Custom>::get();
    assign_sem_field(result.blockName, value.blockName, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<sem::CmdInclude::Src, org::ImmCmdInclude::Src> {
  static org::ImmCmdInclude::Src to_immer(sem::CmdInclude::Src const& value, ImmAstEditContext& ctx) {
    org::ImmCmdInclude::Src result = SerdeDefaultProvider<org::ImmCmdInclude::Src>::get();
    assign_immer_field(result.language, value.language, ctx);
    return result;
  }
  static sem::CmdInclude::Src from_immer(org::ImmCmdInclude::Src const& value, ImmAstContext const& ctx) {
    sem::CmdInclude::Src result = SerdeDefaultProvider<sem::CmdInclude::Src>::get();
    assign_sem_field(result.language, value.language, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<sem::CmdInclude::OrgDocument, org::ImmCmdInclude::OrgDocument> {
  static org::ImmCmdInclude::OrgDocument to_immer(sem::CmdInclude::OrgDocument const& value, ImmAstEditContext& ctx) {
    org::ImmCmdInclude::OrgDocument result = SerdeDefaultProvider<org::ImmCmdInclude::OrgDocument>::get();
    assign_immer_field(result.onlyContent, value.onlyContent, ctx);
    assign_immer_field(result.subtreePath, value.subtreePath, ctx);
    assign_immer_field(result.minLevel, value.minLevel, ctx);
    assign_immer_field(result.customIdTarget, value.customIdTarget, ctx);
    return result;
  }
  static sem::CmdInclude::OrgDocument from_immer(org::ImmCmdInclude::OrgDocument const& value, ImmAstContext const& ctx) {
    sem::CmdInclude::OrgDocument result = SerdeDefaultProvider<sem::CmdInclude::OrgDocument>::get();
    assign_sem_field(result.onlyContent, value.onlyContent, ctx);
    assign_sem_field(result.subtreePath, value.subtreePath, ctx);
    assign_sem_field(result.minLevel, value.minLevel, ctx);
    assign_sem_field(result.customIdTarget, value.customIdTarget, ctx);
    return result;
  }
};

/* clang-format on */