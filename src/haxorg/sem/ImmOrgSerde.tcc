/* clang-format off */
template <>
struct ImmSemSerde<sem::CmdArgument, org::ImmCmdArgument> {
  static org::ImmCmdArgument to_immer(sem::CmdArgument const& value, AddContext const& ctx) {
    org::ImmCmdArgument result = SerdeDefaultProvider<org::ImmCmdArgument>::get();
    copy_field(result.key, value.key, ctx);
    copy_field(result.varname, value.varname, ctx);
    copy_field(result.value, value.value, ctx);
    copy_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<sem::CmdArgumentList, org::ImmCmdArgumentList> {
  static org::ImmCmdArgumentList to_immer(sem::CmdArgumentList const& value, AddContext const& ctx) {
    org::ImmCmdArgumentList result = SerdeDefaultProvider<org::ImmCmdArgumentList>::get();
    copy_field(result.args, value.args, ctx);
    copy_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<sem::CmdArguments, org::ImmCmdArguments> {
  static org::ImmCmdArguments to_immer(sem::CmdArguments const& value, AddContext const& ctx) {
    org::ImmCmdArguments result = SerdeDefaultProvider<org::ImmCmdArguments>::get();
    copy_field(result.positional, value.positional, ctx);
    copy_field(result.named, value.named, ctx);
    copy_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<sem::ErrorItem, org::ImmErrorItem> {
  static org::ImmErrorItem to_immer(sem::ErrorItem const& value, AddContext const& ctx) {
    org::ImmErrorItem result = SerdeDefaultProvider<org::ImmErrorItem>::get();
    copy_field(result.message, value.message, ctx);
    copy_field(result.function, value.function, ctx);
    copy_field(result.line, value.line, ctx);
    copy_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<sem::ErrorGroup, org::ImmErrorGroup> {
  static org::ImmErrorGroup to_immer(sem::ErrorGroup const& value, AddContext const& ctx) {
    org::ImmErrorGroup result = SerdeDefaultProvider<org::ImmErrorGroup>::get();
    copy_field(result.diagnostics, value.diagnostics, ctx);
    copy_field(result.function, value.function, ctx);
    copy_field(result.line, value.line, ctx);
    copy_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<sem::StmtList, org::ImmStmtList> {
  static org::ImmStmtList to_immer(sem::StmtList const& value, AddContext const& ctx) {
    org::ImmStmtList result = SerdeDefaultProvider<org::ImmStmtList>::get();
    copy_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<sem::Empty, org::ImmEmpty> {
  static org::ImmEmpty to_immer(sem::Empty const& value, AddContext const& ctx) {
    org::ImmEmpty result = SerdeDefaultProvider<org::ImmEmpty>::get();
    copy_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<sem::CmdCaption, org::ImmCmdCaption> {
  static org::ImmCmdCaption to_immer(sem::CmdCaption const& value, AddContext const& ctx) {
    org::ImmCmdCaption result = SerdeDefaultProvider<org::ImmCmdCaption>::get();
    copy_field(result.text, value.text, ctx);
    copy_field(result.parameters, value.parameters, ctx);
    copy_field(result.attached, value.attached, ctx);
    copy_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<sem::CmdName, org::ImmCmdName> {
  static org::ImmCmdName to_immer(sem::CmdName const& value, AddContext const& ctx) {
    org::ImmCmdName result = SerdeDefaultProvider<org::ImmCmdName>::get();
    copy_field(result.name, value.name, ctx);
    copy_field(result.parameters, value.parameters, ctx);
    copy_field(result.attached, value.attached, ctx);
    copy_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<sem::CmdCustomArgs, org::ImmCmdCustomArgs> {
  static org::ImmCmdCustomArgs to_immer(sem::CmdCustomArgs const& value, AddContext const& ctx) {
    org::ImmCmdCustomArgs result = SerdeDefaultProvider<org::ImmCmdCustomArgs>::get();
    copy_field(result.name, value.name, ctx);
    copy_field(result.isAttached, value.isAttached, ctx);
    copy_field(result.parameters, value.parameters, ctx);
    copy_field(result.attached, value.attached, ctx);
    copy_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<sem::CmdCustomRaw, org::ImmCmdCustomRaw> {
  static org::ImmCmdCustomRaw to_immer(sem::CmdCustomRaw const& value, AddContext const& ctx) {
    org::ImmCmdCustomRaw result = SerdeDefaultProvider<org::ImmCmdCustomRaw>::get();
    copy_field(result.name, value.name, ctx);
    copy_field(result.isAttached, value.isAttached, ctx);
    copy_field(result.text, value.text, ctx);
    copy_field(result.attached, value.attached, ctx);
    copy_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<sem::CmdCustomText, org::ImmCmdCustomText> {
  static org::ImmCmdCustomText to_immer(sem::CmdCustomText const& value, AddContext const& ctx) {
    org::ImmCmdCustomText result = SerdeDefaultProvider<org::ImmCmdCustomText>::get();
    copy_field(result.name, value.name, ctx);
    copy_field(result.isAttached, value.isAttached, ctx);
    copy_field(result.text, value.text, ctx);
    copy_field(result.attached, value.attached, ctx);
    copy_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<sem::CmdResults, org::ImmCmdResults> {
  static org::ImmCmdResults to_immer(sem::CmdResults const& value, AddContext const& ctx) {
    org::ImmCmdResults result = SerdeDefaultProvider<org::ImmCmdResults>::get();
    copy_field(result.parameters, value.parameters, ctx);
    copy_field(result.attached, value.attached, ctx);
    copy_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<sem::CmdTblfm, org::ImmCmdTblfm> {
  static org::ImmCmdTblfm to_immer(sem::CmdTblfm const& value, AddContext const& ctx) {
    org::ImmCmdTblfm result = SerdeDefaultProvider<org::ImmCmdTblfm>::get();
    copy_field(result.parameters, value.parameters, ctx);
    copy_field(result.attached, value.attached, ctx);
    copy_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<sem::HashTag, org::ImmHashTag> {
  static org::ImmHashTag to_immer(sem::HashTag const& value, AddContext const& ctx) {
    org::ImmHashTag result = SerdeDefaultProvider<org::ImmHashTag>::get();
    copy_field(result.head, value.head, ctx);
    copy_field(result.subtags, value.subtags, ctx);
    copy_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<sem::Footnote, org::ImmFootnote> {
  static org::ImmFootnote to_immer(sem::Footnote const& value, AddContext const& ctx) {
    org::ImmFootnote result = SerdeDefaultProvider<org::ImmFootnote>::get();
    copy_field(result.tag, value.tag, ctx);
    copy_field(result.definition, value.definition, ctx);
    copy_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<sem::Time, org::ImmTime> {
  static org::ImmTime to_immer(sem::Time const& value, AddContext const& ctx) {
    org::ImmTime result = SerdeDefaultProvider<org::ImmTime>::get();
    copy_field(result.isActive, value.isActive, ctx);
    copy_field(result.time, value.time, ctx);
    copy_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<sem::Time::Repeat, org::ImmTime::Repeat> {
  static org::ImmTime::Repeat to_immer(sem::Time::Repeat const& value, AddContext const& ctx) {
    org::ImmTime::Repeat result = SerdeDefaultProvider<org::ImmTime::Repeat>::get();
    copy_field(result.mode, value.mode, ctx);
    copy_field(result.period, value.period, ctx);
    copy_field(result.count, value.count, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<sem::Time::Static, org::ImmTime::Static> {
  static org::ImmTime::Static to_immer(sem::Time::Static const& value, AddContext const& ctx) {
    org::ImmTime::Static result = SerdeDefaultProvider<org::ImmTime::Static>::get();
    copy_field(result.repeat, value.repeat, ctx);
    copy_field(result.time, value.time, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<sem::Time::Dynamic, org::ImmTime::Dynamic> {
  static org::ImmTime::Dynamic to_immer(sem::Time::Dynamic const& value, AddContext const& ctx) {
    org::ImmTime::Dynamic result = SerdeDefaultProvider<org::ImmTime::Dynamic>::get();
    copy_field(result.expr, value.expr, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<sem::TimeRange, org::ImmTimeRange> {
  static org::ImmTimeRange to_immer(sem::TimeRange const& value, AddContext const& ctx) {
    org::ImmTimeRange result = SerdeDefaultProvider<org::ImmTimeRange>::get();
    copy_field(result.from, value.from, ctx);
    copy_field(result.to, value.to, ctx);
    copy_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<sem::Macro, org::ImmMacro> {
  static org::ImmMacro to_immer(sem::Macro const& value, AddContext const& ctx) {
    org::ImmMacro result = SerdeDefaultProvider<org::ImmMacro>::get();
    copy_field(result.name, value.name, ctx);
    copy_field(result.parameters, value.parameters, ctx);
    copy_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<sem::Symbol, org::ImmSymbol> {
  static org::ImmSymbol to_immer(sem::Symbol const& value, AddContext const& ctx) {
    org::ImmSymbol result = SerdeDefaultProvider<org::ImmSymbol>::get();
    copy_field(result.name, value.name, ctx);
    copy_field(result.parameters, value.parameters, ctx);
    copy_field(result.positional, value.positional, ctx);
    copy_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<sem::Symbol::Param, org::ImmSymbol::Param> {
  static org::ImmSymbol::Param to_immer(sem::Symbol::Param const& value, AddContext const& ctx) {
    org::ImmSymbol::Param result = SerdeDefaultProvider<org::ImmSymbol::Param>::get();
    copy_field(result.key, value.key, ctx);
    copy_field(result.value, value.value, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<sem::Escaped, org::ImmEscaped> {
  static org::ImmEscaped to_immer(sem::Escaped const& value, AddContext const& ctx) {
    org::ImmEscaped result = SerdeDefaultProvider<org::ImmEscaped>::get();
    copy_field(result.text, value.text, ctx);
    copy_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<sem::Newline, org::ImmNewline> {
  static org::ImmNewline to_immer(sem::Newline const& value, AddContext const& ctx) {
    org::ImmNewline result = SerdeDefaultProvider<org::ImmNewline>::get();
    copy_field(result.text, value.text, ctx);
    copy_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<sem::Space, org::ImmSpace> {
  static org::ImmSpace to_immer(sem::Space const& value, AddContext const& ctx) {
    org::ImmSpace result = SerdeDefaultProvider<org::ImmSpace>::get();
    copy_field(result.text, value.text, ctx);
    copy_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<sem::Word, org::ImmWord> {
  static org::ImmWord to_immer(sem::Word const& value, AddContext const& ctx) {
    org::ImmWord result = SerdeDefaultProvider<org::ImmWord>::get();
    copy_field(result.text, value.text, ctx);
    copy_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<sem::AtMention, org::ImmAtMention> {
  static org::ImmAtMention to_immer(sem::AtMention const& value, AddContext const& ctx) {
    org::ImmAtMention result = SerdeDefaultProvider<org::ImmAtMention>::get();
    copy_field(result.text, value.text, ctx);
    copy_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<sem::RawText, org::ImmRawText> {
  static org::ImmRawText to_immer(sem::RawText const& value, AddContext const& ctx) {
    org::ImmRawText result = SerdeDefaultProvider<org::ImmRawText>::get();
    copy_field(result.text, value.text, ctx);
    copy_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<sem::Punctuation, org::ImmPunctuation> {
  static org::ImmPunctuation to_immer(sem::Punctuation const& value, AddContext const& ctx) {
    org::ImmPunctuation result = SerdeDefaultProvider<org::ImmPunctuation>::get();
    copy_field(result.text, value.text, ctx);
    copy_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<sem::Placeholder, org::ImmPlaceholder> {
  static org::ImmPlaceholder to_immer(sem::Placeholder const& value, AddContext const& ctx) {
    org::ImmPlaceholder result = SerdeDefaultProvider<org::ImmPlaceholder>::get();
    copy_field(result.text, value.text, ctx);
    copy_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<sem::BigIdent, org::ImmBigIdent> {
  static org::ImmBigIdent to_immer(sem::BigIdent const& value, AddContext const& ctx) {
    org::ImmBigIdent result = SerdeDefaultProvider<org::ImmBigIdent>::get();
    copy_field(result.text, value.text, ctx);
    copy_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<sem::RadioTarget, org::ImmRadioTarget> {
  static org::ImmRadioTarget to_immer(sem::RadioTarget const& value, AddContext const& ctx) {
    org::ImmRadioTarget result = SerdeDefaultProvider<org::ImmRadioTarget>::get();
    copy_field(result.text, value.text, ctx);
    copy_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<sem::TextTarget, org::ImmTextTarget> {
  static org::ImmTextTarget to_immer(sem::TextTarget const& value, AddContext const& ctx) {
    org::ImmTextTarget result = SerdeDefaultProvider<org::ImmTextTarget>::get();
    copy_field(result.text, value.text, ctx);
    copy_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<sem::Bold, org::ImmBold> {
  static org::ImmBold to_immer(sem::Bold const& value, AddContext const& ctx) {
    org::ImmBold result = SerdeDefaultProvider<org::ImmBold>::get();
    copy_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<sem::Underline, org::ImmUnderline> {
  static org::ImmUnderline to_immer(sem::Underline const& value, AddContext const& ctx) {
    org::ImmUnderline result = SerdeDefaultProvider<org::ImmUnderline>::get();
    copy_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<sem::Monospace, org::ImmMonospace> {
  static org::ImmMonospace to_immer(sem::Monospace const& value, AddContext const& ctx) {
    org::ImmMonospace result = SerdeDefaultProvider<org::ImmMonospace>::get();
    copy_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<sem::MarkQuote, org::ImmMarkQuote> {
  static org::ImmMarkQuote to_immer(sem::MarkQuote const& value, AddContext const& ctx) {
    org::ImmMarkQuote result = SerdeDefaultProvider<org::ImmMarkQuote>::get();
    copy_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<sem::Verbatim, org::ImmVerbatim> {
  static org::ImmVerbatim to_immer(sem::Verbatim const& value, AddContext const& ctx) {
    org::ImmVerbatim result = SerdeDefaultProvider<org::ImmVerbatim>::get();
    copy_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<sem::Italic, org::ImmItalic> {
  static org::ImmItalic to_immer(sem::Italic const& value, AddContext const& ctx) {
    org::ImmItalic result = SerdeDefaultProvider<org::ImmItalic>::get();
    copy_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<sem::Strike, org::ImmStrike> {
  static org::ImmStrike to_immer(sem::Strike const& value, AddContext const& ctx) {
    org::ImmStrike result = SerdeDefaultProvider<org::ImmStrike>::get();
    copy_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<sem::Par, org::ImmPar> {
  static org::ImmPar to_immer(sem::Par const& value, AddContext const& ctx) {
    org::ImmPar result = SerdeDefaultProvider<org::ImmPar>::get();
    copy_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<sem::Latex, org::ImmLatex> {
  static org::ImmLatex to_immer(sem::Latex const& value, AddContext const& ctx) {
    org::ImmLatex result = SerdeDefaultProvider<org::ImmLatex>::get();
    copy_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<sem::Link, org::ImmLink> {
  static org::ImmLink to_immer(sem::Link const& value, AddContext const& ctx) {
    org::ImmLink result = SerdeDefaultProvider<org::ImmLink>::get();
    copy_field(result.description, value.description, ctx);
    copy_field(result.data, value.data, ctx);
    copy_field(result.attached, value.attached, ctx);
    copy_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<sem::Link::Raw, org::ImmLink::Raw> {
  static org::ImmLink::Raw to_immer(sem::Link::Raw const& value, AddContext const& ctx) {
    org::ImmLink::Raw result = SerdeDefaultProvider<org::ImmLink::Raw>::get();
    copy_field(result.text, value.text, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<sem::Link::Id, org::ImmLink::Id> {
  static org::ImmLink::Id to_immer(sem::Link::Id const& value, AddContext const& ctx) {
    org::ImmLink::Id result = SerdeDefaultProvider<org::ImmLink::Id>::get();
    copy_field(result.text, value.text, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<sem::Link::Person, org::ImmLink::Person> {
  static org::ImmLink::Person to_immer(sem::Link::Person const& value, AddContext const& ctx) {
    org::ImmLink::Person result = SerdeDefaultProvider<org::ImmLink::Person>::get();
    copy_field(result.name, value.name, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<sem::Link::UserProtocol, org::ImmLink::UserProtocol> {
  static org::ImmLink::UserProtocol to_immer(sem::Link::UserProtocol const& value, AddContext const& ctx) {
    org::ImmLink::UserProtocol result = SerdeDefaultProvider<org::ImmLink::UserProtocol>::get();
    copy_field(result.protocol, value.protocol, ctx);
    copy_field(result.target, value.target, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<sem::Link::Internal, org::ImmLink::Internal> {
  static org::ImmLink::Internal to_immer(sem::Link::Internal const& value, AddContext const& ctx) {
    org::ImmLink::Internal result = SerdeDefaultProvider<org::ImmLink::Internal>::get();
    copy_field(result.target, value.target, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<sem::Link::Footnote, org::ImmLink::Footnote> {
  static org::ImmLink::Footnote to_immer(sem::Link::Footnote const& value, AddContext const& ctx) {
    org::ImmLink::Footnote result = SerdeDefaultProvider<org::ImmLink::Footnote>::get();
    copy_field(result.target, value.target, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<sem::Link::File, org::ImmLink::File> {
  static org::ImmLink::File to_immer(sem::Link::File const& value, AddContext const& ctx) {
    org::ImmLink::File result = SerdeDefaultProvider<org::ImmLink::File>::get();
    copy_field(result.file, value.file, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<sem::Link::Attachment, org::ImmLink::Attachment> {
  static org::ImmLink::Attachment to_immer(sem::Link::Attachment const& value, AddContext const& ctx) {
    org::ImmLink::Attachment result = SerdeDefaultProvider<org::ImmLink::Attachment>::get();
    copy_field(result.file, value.file, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<sem::BlockCenter, org::ImmBlockCenter> {
  static org::ImmBlockCenter to_immer(sem::BlockCenter const& value, AddContext const& ctx) {
    org::ImmBlockCenter result = SerdeDefaultProvider<org::ImmBlockCenter>::get();
    copy_field(result.parameters, value.parameters, ctx);
    copy_field(result.attached, value.attached, ctx);
    copy_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<sem::BlockQuote, org::ImmBlockQuote> {
  static org::ImmBlockQuote to_immer(sem::BlockQuote const& value, AddContext const& ctx) {
    org::ImmBlockQuote result = SerdeDefaultProvider<org::ImmBlockQuote>::get();
    copy_field(result.parameters, value.parameters, ctx);
    copy_field(result.attached, value.attached, ctx);
    copy_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<sem::BlockComment, org::ImmBlockComment> {
  static org::ImmBlockComment to_immer(sem::BlockComment const& value, AddContext const& ctx) {
    org::ImmBlockComment result = SerdeDefaultProvider<org::ImmBlockComment>::get();
    copy_field(result.attached, value.attached, ctx);
    copy_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<sem::BlockVerse, org::ImmBlockVerse> {
  static org::ImmBlockVerse to_immer(sem::BlockVerse const& value, AddContext const& ctx) {
    org::ImmBlockVerse result = SerdeDefaultProvider<org::ImmBlockVerse>::get();
    copy_field(result.parameters, value.parameters, ctx);
    copy_field(result.attached, value.attached, ctx);
    copy_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<sem::BlockExample, org::ImmBlockExample> {
  static org::ImmBlockExample to_immer(sem::BlockExample const& value, AddContext const& ctx) {
    org::ImmBlockExample result = SerdeDefaultProvider<org::ImmBlockExample>::get();
    copy_field(result.parameters, value.parameters, ctx);
    copy_field(result.attached, value.attached, ctx);
    copy_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<sem::BlockExport, org::ImmBlockExport> {
  static org::ImmBlockExport to_immer(sem::BlockExport const& value, AddContext const& ctx) {
    org::ImmBlockExport result = SerdeDefaultProvider<org::ImmBlockExport>::get();
    copy_field(result.format, value.format, ctx);
    copy_field(result.exporter, value.exporter, ctx);
    copy_field(result.placement, value.placement, ctx);
    copy_field(result.content, value.content, ctx);
    copy_field(result.parameters, value.parameters, ctx);
    copy_field(result.attached, value.attached, ctx);
    copy_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<sem::BlockAdmonition, org::ImmBlockAdmonition> {
  static org::ImmBlockAdmonition to_immer(sem::BlockAdmonition const& value, AddContext const& ctx) {
    org::ImmBlockAdmonition result = SerdeDefaultProvider<org::ImmBlockAdmonition>::get();
    copy_field(result.parameters, value.parameters, ctx);
    copy_field(result.attached, value.attached, ctx);
    copy_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<sem::BlockCode, org::ImmBlockCode> {
  static org::ImmBlockCode to_immer(sem::BlockCode const& value, AddContext const& ctx) {
    org::ImmBlockCode result = SerdeDefaultProvider<org::ImmBlockCode>::get();
    copy_field(result.lang, value.lang, ctx);
    copy_field(result.switches, value.switches, ctx);
    copy_field(result.exports, value.exports, ctx);
    copy_field(result.result, value.result, ctx);
    copy_field(result.lines, value.lines, ctx);
    copy_field(result.cache, value.cache, ctx);
    copy_field(result.eval, value.eval, ctx);
    copy_field(result.noweb, value.noweb, ctx);
    copy_field(result.hlines, value.hlines, ctx);
    copy_field(result.tangle, value.tangle, ctx);
    copy_field(result.parameters, value.parameters, ctx);
    copy_field(result.attached, value.attached, ctx);
    copy_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<sem::BlockCode::Line, org::ImmBlockCode::Line> {
  static org::ImmBlockCode::Line to_immer(sem::BlockCode::Line const& value, AddContext const& ctx) {
    org::ImmBlockCode::Line result = SerdeDefaultProvider<org::ImmBlockCode::Line>::get();
    copy_field(result.parts, value.parts, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<sem::BlockCode::Line::Part, org::ImmBlockCode::Line::Part> {
  static org::ImmBlockCode::Line::Part to_immer(sem::BlockCode::Line::Part const& value, AddContext const& ctx) {
    org::ImmBlockCode::Line::Part result = SerdeDefaultProvider<org::ImmBlockCode::Line::Part>::get();
    copy_field(result.data, value.data, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<sem::BlockCode::Line::Part::Raw, org::ImmBlockCode::Line::Part::Raw> {
  static org::ImmBlockCode::Line::Part::Raw to_immer(sem::BlockCode::Line::Part::Raw const& value, AddContext const& ctx) {
    org::ImmBlockCode::Line::Part::Raw result = SerdeDefaultProvider<org::ImmBlockCode::Line::Part::Raw>::get();
    copy_field(result.code, value.code, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<sem::BlockCode::Line::Part::Callout, org::ImmBlockCode::Line::Part::Callout> {
  static org::ImmBlockCode::Line::Part::Callout to_immer(sem::BlockCode::Line::Part::Callout const& value, AddContext const& ctx) {
    org::ImmBlockCode::Line::Part::Callout result = SerdeDefaultProvider<org::ImmBlockCode::Line::Part::Callout>::get();
    copy_field(result.name, value.name, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<sem::BlockCode::Line::Part::Tangle, org::ImmBlockCode::Line::Part::Tangle> {
  static org::ImmBlockCode::Line::Part::Tangle to_immer(sem::BlockCode::Line::Part::Tangle const& value, AddContext const& ctx) {
    org::ImmBlockCode::Line::Part::Tangle result = SerdeDefaultProvider<org::ImmBlockCode::Line::Part::Tangle>::get();
    copy_field(result.target, value.target, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<sem::BlockCode::Switch, org::ImmBlockCode::Switch> {
  static org::ImmBlockCode::Switch to_immer(sem::BlockCode::Switch const& value, AddContext const& ctx) {
    org::ImmBlockCode::Switch result = SerdeDefaultProvider<org::ImmBlockCode::Switch>::get();
    copy_field(result.data, value.data, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<sem::BlockCode::Switch::LineStart, org::ImmBlockCode::Switch::LineStart> {
  static org::ImmBlockCode::Switch::LineStart to_immer(sem::BlockCode::Switch::LineStart const& value, AddContext const& ctx) {
    org::ImmBlockCode::Switch::LineStart result = SerdeDefaultProvider<org::ImmBlockCode::Switch::LineStart>::get();
    copy_field(result.start, value.start, ctx);
    copy_field(result.extendLast, value.extendLast, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<sem::BlockCode::Switch::CalloutFormat, org::ImmBlockCode::Switch::CalloutFormat> {
  static org::ImmBlockCode::Switch::CalloutFormat to_immer(sem::BlockCode::Switch::CalloutFormat const& value, AddContext const& ctx) {
    org::ImmBlockCode::Switch::CalloutFormat result = SerdeDefaultProvider<org::ImmBlockCode::Switch::CalloutFormat>::get();
    copy_field(result.format, value.format, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<sem::BlockCode::Switch::RemoveCallout, org::ImmBlockCode::Switch::RemoveCallout> {
  static org::ImmBlockCode::Switch::RemoveCallout to_immer(sem::BlockCode::Switch::RemoveCallout const& value, AddContext const& ctx) {
    org::ImmBlockCode::Switch::RemoveCallout result = SerdeDefaultProvider<org::ImmBlockCode::Switch::RemoveCallout>::get();
    copy_field(result.remove, value.remove, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<sem::BlockCode::Switch::EmphasizeLine, org::ImmBlockCode::Switch::EmphasizeLine> {
  static org::ImmBlockCode::Switch::EmphasizeLine to_immer(sem::BlockCode::Switch::EmphasizeLine const& value, AddContext const& ctx) {
    org::ImmBlockCode::Switch::EmphasizeLine result = SerdeDefaultProvider<org::ImmBlockCode::Switch::EmphasizeLine>::get();
    copy_field(result.line, value.line, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<sem::BlockCode::Switch::Dedent, org::ImmBlockCode::Switch::Dedent> {
  static org::ImmBlockCode::Switch::Dedent to_immer(sem::BlockCode::Switch::Dedent const& value, AddContext const& ctx) {
    org::ImmBlockCode::Switch::Dedent result = SerdeDefaultProvider<org::ImmBlockCode::Switch::Dedent>::get();
    copy_field(result.value, value.value, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<sem::BlockCode::EvalResult, org::ImmBlockCode::EvalResult> {
  static org::ImmBlockCode::EvalResult to_immer(sem::BlockCode::EvalResult const& value, AddContext const& ctx) {
    org::ImmBlockCode::EvalResult result = SerdeDefaultProvider<org::ImmBlockCode::EvalResult>::get();
    copy_field(result.data, value.data, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<sem::BlockCode::EvalResult::None, org::ImmBlockCode::EvalResult::None> {
  static org::ImmBlockCode::EvalResult::None to_immer(sem::BlockCode::EvalResult::None const& value, AddContext const& ctx) {
    org::ImmBlockCode::EvalResult::None result = SerdeDefaultProvider<org::ImmBlockCode::EvalResult::None>::get();
    return result;
  }
};

template <>
struct ImmSemSerde<sem::BlockCode::EvalResult::OrgValue, org::ImmBlockCode::EvalResult::OrgValue> {
  static org::ImmBlockCode::EvalResult::OrgValue to_immer(sem::BlockCode::EvalResult::OrgValue const& value, AddContext const& ctx) {
    org::ImmBlockCode::EvalResult::OrgValue result = SerdeDefaultProvider<org::ImmBlockCode::EvalResult::OrgValue>::get();
    copy_field(result.value, value.value, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<sem::BlockCode::EvalResult::File, org::ImmBlockCode::EvalResult::File> {
  static org::ImmBlockCode::EvalResult::File to_immer(sem::BlockCode::EvalResult::File const& value, AddContext const& ctx) {
    org::ImmBlockCode::EvalResult::File result = SerdeDefaultProvider<org::ImmBlockCode::EvalResult::File>::get();
    copy_field(result.path, value.path, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<sem::BlockCode::EvalResult::Raw, org::ImmBlockCode::EvalResult::Raw> {
  static org::ImmBlockCode::EvalResult::Raw to_immer(sem::BlockCode::EvalResult::Raw const& value, AddContext const& ctx) {
    org::ImmBlockCode::EvalResult::Raw result = SerdeDefaultProvider<org::ImmBlockCode::EvalResult::Raw>::get();
    copy_field(result.text, value.text, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<sem::SubtreeLog, org::ImmSubtreeLog> {
  static org::ImmSubtreeLog to_immer(sem::SubtreeLog const& value, AddContext const& ctx) {
    org::ImmSubtreeLog result = SerdeDefaultProvider<org::ImmSubtreeLog>::get();
    copy_field(result.log, value.log, ctx);
    copy_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<sem::SubtreeLog::DescribedLog, org::ImmSubtreeLog::DescribedLog> {
  static org::ImmSubtreeLog::DescribedLog to_immer(sem::SubtreeLog::DescribedLog const& value, AddContext const& ctx) {
    org::ImmSubtreeLog::DescribedLog result = SerdeDefaultProvider<org::ImmSubtreeLog::DescribedLog>::get();
    copy_field(result.desc, value.desc, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<sem::SubtreeLog::Priority, org::ImmSubtreeLog::Priority> {
  static org::ImmSubtreeLog::Priority to_immer(sem::SubtreeLog::Priority const& value, AddContext const& ctx) {
    org::ImmSubtreeLog::Priority result = SerdeDefaultProvider<org::ImmSubtreeLog::Priority>::get();
    copy_field(result.oldPriority, value.oldPriority, ctx);
    copy_field(result.newPriority, value.newPriority, ctx);
    copy_field(result.on, value.on, ctx);
    copy_field(result.action, value.action, ctx);
    copy_field(result.desc, value.desc, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<sem::SubtreeLog::Note, org::ImmSubtreeLog::Note> {
  static org::ImmSubtreeLog::Note to_immer(sem::SubtreeLog::Note const& value, AddContext const& ctx) {
    org::ImmSubtreeLog::Note result = SerdeDefaultProvider<org::ImmSubtreeLog::Note>::get();
    copy_field(result.on, value.on, ctx);
    copy_field(result.desc, value.desc, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<sem::SubtreeLog::Refile, org::ImmSubtreeLog::Refile> {
  static org::ImmSubtreeLog::Refile to_immer(sem::SubtreeLog::Refile const& value, AddContext const& ctx) {
    org::ImmSubtreeLog::Refile result = SerdeDefaultProvider<org::ImmSubtreeLog::Refile>::get();
    copy_field(result.on, value.on, ctx);
    copy_field(result.from, value.from, ctx);
    copy_field(result.desc, value.desc, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<sem::SubtreeLog::Clock, org::ImmSubtreeLog::Clock> {
  static org::ImmSubtreeLog::Clock to_immer(sem::SubtreeLog::Clock const& value, AddContext const& ctx) {
    org::ImmSubtreeLog::Clock result = SerdeDefaultProvider<org::ImmSubtreeLog::Clock>::get();
    copy_field(result.from, value.from, ctx);
    copy_field(result.to, value.to, ctx);
    copy_field(result.desc, value.desc, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<sem::SubtreeLog::State, org::ImmSubtreeLog::State> {
  static org::ImmSubtreeLog::State to_immer(sem::SubtreeLog::State const& value, AddContext const& ctx) {
    org::ImmSubtreeLog::State result = SerdeDefaultProvider<org::ImmSubtreeLog::State>::get();
    copy_field(result.from, value.from, ctx);
    copy_field(result.to, value.to, ctx);
    copy_field(result.on, value.on, ctx);
    copy_field(result.desc, value.desc, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<sem::SubtreeLog::Tag, org::ImmSubtreeLog::Tag> {
  static org::ImmSubtreeLog::Tag to_immer(sem::SubtreeLog::Tag const& value, AddContext const& ctx) {
    org::ImmSubtreeLog::Tag result = SerdeDefaultProvider<org::ImmSubtreeLog::Tag>::get();
    copy_field(result.on, value.on, ctx);
    copy_field(result.tag, value.tag, ctx);
    copy_field(result.added, value.added, ctx);
    copy_field(result.desc, value.desc, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<sem::SubtreeLog::Unknown, org::ImmSubtreeLog::Unknown> {
  static org::ImmSubtreeLog::Unknown to_immer(sem::SubtreeLog::Unknown const& value, AddContext const& ctx) {
    org::ImmSubtreeLog::Unknown result = SerdeDefaultProvider<org::ImmSubtreeLog::Unknown>::get();
    copy_field(result.desc, value.desc, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<sem::Subtree, org::ImmSubtree> {
  static org::ImmSubtree to_immer(sem::Subtree const& value, AddContext const& ctx) {
    org::ImmSubtree result = SerdeDefaultProvider<org::ImmSubtree>::get();
    copy_field(result.level, value.level, ctx);
    copy_field(result.treeId, value.treeId, ctx);
    copy_field(result.todo, value.todo, ctx);
    copy_field(result.completion, value.completion, ctx);
    copy_field(result.description, value.description, ctx);
    copy_field(result.tags, value.tags, ctx);
    copy_field(result.title, value.title, ctx);
    copy_field(result.logbook, value.logbook, ctx);
    copy_field(result.properties, value.properties, ctx);
    copy_field(result.closed, value.closed, ctx);
    copy_field(result.deadline, value.deadline, ctx);
    copy_field(result.scheduled, value.scheduled, ctx);
    copy_field(result.isComment, value.isComment, ctx);
    copy_field(result.isArchived, value.isArchived, ctx);
    copy_field(result.priority, value.priority, ctx);
    copy_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<sem::Subtree::Period, org::ImmSubtree::Period> {
  static org::ImmSubtree::Period to_immer(sem::Subtree::Period const& value, AddContext const& ctx) {
    org::ImmSubtree::Period result = SerdeDefaultProvider<org::ImmSubtree::Period>::get();
    copy_field(result.kind, value.kind, ctx);
    copy_field(result.from, value.from, ctx);
    copy_field(result.to, value.to, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<sem::Subtree::Property, org::ImmSubtree::Property> {
  static org::ImmSubtree::Property to_immer(sem::Subtree::Property const& value, AddContext const& ctx) {
    org::ImmSubtree::Property result = SerdeDefaultProvider<org::ImmSubtree::Property>::get();
    copy_field(result.mainSetRule, value.mainSetRule, ctx);
    copy_field(result.subSetRule, value.subSetRule, ctx);
    copy_field(result.inheritanceMode, value.inheritanceMode, ctx);
    copy_field(result.data, value.data, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<sem::Subtree::Property::Nonblocking, org::ImmSubtree::Property::Nonblocking> {
  static org::ImmSubtree::Property::Nonblocking to_immer(sem::Subtree::Property::Nonblocking const& value, AddContext const& ctx) {
    org::ImmSubtree::Property::Nonblocking result = SerdeDefaultProvider<org::ImmSubtree::Property::Nonblocking>::get();
    copy_field(result.isBlocking, value.isBlocking, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<sem::Subtree::Property::Trigger, org::ImmSubtree::Property::Trigger> {
  static org::ImmSubtree::Property::Trigger to_immer(sem::Subtree::Property::Trigger const& value, AddContext const& ctx) {
    org::ImmSubtree::Property::Trigger result = SerdeDefaultProvider<org::ImmSubtree::Property::Trigger>::get();
    return result;
  }
};

template <>
struct ImmSemSerde<sem::Subtree::Property::Origin, org::ImmSubtree::Property::Origin> {
  static org::ImmSubtree::Property::Origin to_immer(sem::Subtree::Property::Origin const& value, AddContext const& ctx) {
    org::ImmSubtree::Property::Origin result = SerdeDefaultProvider<org::ImmSubtree::Property::Origin>::get();
    copy_field(result.text, value.text, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<sem::Subtree::Property::ExportLatexClass, org::ImmSubtree::Property::ExportLatexClass> {
  static org::ImmSubtree::Property::ExportLatexClass to_immer(sem::Subtree::Property::ExportLatexClass const& value, AddContext const& ctx) {
    org::ImmSubtree::Property::ExportLatexClass result = SerdeDefaultProvider<org::ImmSubtree::Property::ExportLatexClass>::get();
    copy_field(result.latexClass, value.latexClass, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<sem::Subtree::Property::ExportLatexClassOptions, org::ImmSubtree::Property::ExportLatexClassOptions> {
  static org::ImmSubtree::Property::ExportLatexClassOptions to_immer(sem::Subtree::Property::ExportLatexClassOptions const& value, AddContext const& ctx) {
    org::ImmSubtree::Property::ExportLatexClassOptions result = SerdeDefaultProvider<org::ImmSubtree::Property::ExportLatexClassOptions>::get();
    copy_field(result.options, value.options, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<sem::Subtree::Property::ExportLatexHeader, org::ImmSubtree::Property::ExportLatexHeader> {
  static org::ImmSubtree::Property::ExportLatexHeader to_immer(sem::Subtree::Property::ExportLatexHeader const& value, AddContext const& ctx) {
    org::ImmSubtree::Property::ExportLatexHeader result = SerdeDefaultProvider<org::ImmSubtree::Property::ExportLatexHeader>::get();
    copy_field(result.header, value.header, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<sem::Subtree::Property::ExportLatexCompiler, org::ImmSubtree::Property::ExportLatexCompiler> {
  static org::ImmSubtree::Property::ExportLatexCompiler to_immer(sem::Subtree::Property::ExportLatexCompiler const& value, AddContext const& ctx) {
    org::ImmSubtree::Property::ExportLatexCompiler result = SerdeDefaultProvider<org::ImmSubtree::Property::ExportLatexCompiler>::get();
    copy_field(result.compiler, value.compiler, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<sem::Subtree::Property::Ordered, org::ImmSubtree::Property::Ordered> {
  static org::ImmSubtree::Property::Ordered to_immer(sem::Subtree::Property::Ordered const& value, AddContext const& ctx) {
    org::ImmSubtree::Property::Ordered result = SerdeDefaultProvider<org::ImmSubtree::Property::Ordered>::get();
    copy_field(result.isOrdered, value.isOrdered, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<sem::Subtree::Property::Effort, org::ImmSubtree::Property::Effort> {
  static org::ImmSubtree::Property::Effort to_immer(sem::Subtree::Property::Effort const& value, AddContext const& ctx) {
    org::ImmSubtree::Property::Effort result = SerdeDefaultProvider<org::ImmSubtree::Property::Effort>::get();
    copy_field(result.hours, value.hours, ctx);
    copy_field(result.minutes, value.minutes, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<sem::Subtree::Property::Visibility, org::ImmSubtree::Property::Visibility> {
  static org::ImmSubtree::Property::Visibility to_immer(sem::Subtree::Property::Visibility const& value, AddContext const& ctx) {
    org::ImmSubtree::Property::Visibility result = SerdeDefaultProvider<org::ImmSubtree::Property::Visibility>::get();
    copy_field(result.level, value.level, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<sem::Subtree::Property::ExportOptions, org::ImmSubtree::Property::ExportOptions> {
  static org::ImmSubtree::Property::ExportOptions to_immer(sem::Subtree::Property::ExportOptions const& value, AddContext const& ctx) {
    org::ImmSubtree::Property::ExportOptions result = SerdeDefaultProvider<org::ImmSubtree::Property::ExportOptions>::get();
    copy_field(result.backend, value.backend, ctx);
    copy_field(result.values, value.values, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<sem::Subtree::Property::Blocker, org::ImmSubtree::Property::Blocker> {
  static org::ImmSubtree::Property::Blocker to_immer(sem::Subtree::Property::Blocker const& value, AddContext const& ctx) {
    org::ImmSubtree::Property::Blocker result = SerdeDefaultProvider<org::ImmSubtree::Property::Blocker>::get();
    copy_field(result.blockers, value.blockers, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<sem::Subtree::Property::Unnumbered, org::ImmSubtree::Property::Unnumbered> {
  static org::ImmSubtree::Property::Unnumbered to_immer(sem::Subtree::Property::Unnumbered const& value, AddContext const& ctx) {
    org::ImmSubtree::Property::Unnumbered result = SerdeDefaultProvider<org::ImmSubtree::Property::Unnumbered>::get();
    return result;
  }
};

template <>
struct ImmSemSerde<sem::Subtree::Property::Created, org::ImmSubtree::Property::Created> {
  static org::ImmSubtree::Property::Created to_immer(sem::Subtree::Property::Created const& value, AddContext const& ctx) {
    org::ImmSubtree::Property::Created result = SerdeDefaultProvider<org::ImmSubtree::Property::Created>::get();
    copy_field(result.time, value.time, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<sem::Subtree::Property::CustomArgs, org::ImmSubtree::Property::CustomArgs> {
  static org::ImmSubtree::Property::CustomArgs to_immer(sem::Subtree::Property::CustomArgs const& value, AddContext const& ctx) {
    org::ImmSubtree::Property::CustomArgs result = SerdeDefaultProvider<org::ImmSubtree::Property::CustomArgs>::get();
    copy_field(result.name, value.name, ctx);
    copy_field(result.sub, value.sub, ctx);
    copy_field(result.parameters, value.parameters, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<sem::Subtree::Property::CustomRaw, org::ImmSubtree::Property::CustomRaw> {
  static org::ImmSubtree::Property::CustomRaw to_immer(sem::Subtree::Property::CustomRaw const& value, AddContext const& ctx) {
    org::ImmSubtree::Property::CustomRaw result = SerdeDefaultProvider<org::ImmSubtree::Property::CustomRaw>::get();
    copy_field(result.name, value.name, ctx);
    copy_field(result.value, value.value, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<sem::SubtreeCompletion, org::ImmSubtreeCompletion> {
  static org::ImmSubtreeCompletion to_immer(sem::SubtreeCompletion const& value, AddContext const& ctx) {
    org::ImmSubtreeCompletion result = SerdeDefaultProvider<org::ImmSubtreeCompletion>::get();
    copy_field(result.done, value.done, ctx);
    copy_field(result.full, value.full, ctx);
    copy_field(result.isPercent, value.isPercent, ctx);
    copy_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<sem::Cell, org::ImmCell> {
  static org::ImmCell to_immer(sem::Cell const& value, AddContext const& ctx) {
    org::ImmCell result = SerdeDefaultProvider<org::ImmCell>::get();
    copy_field(result.isBlock, value.isBlock, ctx);
    copy_field(result.parameters, value.parameters, ctx);
    copy_field(result.attached, value.attached, ctx);
    copy_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<sem::Row, org::ImmRow> {
  static org::ImmRow to_immer(sem::Row const& value, AddContext const& ctx) {
    org::ImmRow result = SerdeDefaultProvider<org::ImmRow>::get();
    copy_field(result.cells, value.cells, ctx);
    copy_field(result.isBlock, value.isBlock, ctx);
    copy_field(result.parameters, value.parameters, ctx);
    copy_field(result.attached, value.attached, ctx);
    copy_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<sem::Table, org::ImmTable> {
  static org::ImmTable to_immer(sem::Table const& value, AddContext const& ctx) {
    org::ImmTable result = SerdeDefaultProvider<org::ImmTable>::get();
    copy_field(result.rows, value.rows, ctx);
    copy_field(result.isBlock, value.isBlock, ctx);
    copy_field(result.parameters, value.parameters, ctx);
    copy_field(result.attached, value.attached, ctx);
    copy_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<sem::Paragraph, org::ImmParagraph> {
  static org::ImmParagraph to_immer(sem::Paragraph const& value, AddContext const& ctx) {
    org::ImmParagraph result = SerdeDefaultProvider<org::ImmParagraph>::get();
    copy_field(result.attached, value.attached, ctx);
    copy_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<sem::AnnotatedParagraph, org::ImmAnnotatedParagraph> {
  static org::ImmAnnotatedParagraph to_immer(sem::AnnotatedParagraph const& value, AddContext const& ctx) {
    org::ImmAnnotatedParagraph result = SerdeDefaultProvider<org::ImmAnnotatedParagraph>::get();
    copy_field(result.data, value.data, ctx);
    copy_field(result.attached, value.attached, ctx);
    copy_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<sem::AnnotatedParagraph::None, org::ImmAnnotatedParagraph::None> {
  static org::ImmAnnotatedParagraph::None to_immer(sem::AnnotatedParagraph::None const& value, AddContext const& ctx) {
    org::ImmAnnotatedParagraph::None result = SerdeDefaultProvider<org::ImmAnnotatedParagraph::None>::get();
    return result;
  }
};

template <>
struct ImmSemSerde<sem::AnnotatedParagraph::Footnote, org::ImmAnnotatedParagraph::Footnote> {
  static org::ImmAnnotatedParagraph::Footnote to_immer(sem::AnnotatedParagraph::Footnote const& value, AddContext const& ctx) {
    org::ImmAnnotatedParagraph::Footnote result = SerdeDefaultProvider<org::ImmAnnotatedParagraph::Footnote>::get();
    copy_field(result.name, value.name, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<sem::AnnotatedParagraph::Admonition, org::ImmAnnotatedParagraph::Admonition> {
  static org::ImmAnnotatedParagraph::Admonition to_immer(sem::AnnotatedParagraph::Admonition const& value, AddContext const& ctx) {
    org::ImmAnnotatedParagraph::Admonition result = SerdeDefaultProvider<org::ImmAnnotatedParagraph::Admonition>::get();
    copy_field(result.name, value.name, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<sem::AnnotatedParagraph::Timestamp, org::ImmAnnotatedParagraph::Timestamp> {
  static org::ImmAnnotatedParagraph::Timestamp to_immer(sem::AnnotatedParagraph::Timestamp const& value, AddContext const& ctx) {
    org::ImmAnnotatedParagraph::Timestamp result = SerdeDefaultProvider<org::ImmAnnotatedParagraph::Timestamp>::get();
    copy_field(result.time, value.time, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<sem::ColonExample, org::ImmColonExample> {
  static org::ImmColonExample to_immer(sem::ColonExample const& value, AddContext const& ctx) {
    org::ImmColonExample result = SerdeDefaultProvider<org::ImmColonExample>::get();
    copy_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<sem::CmdAttr, org::ImmCmdAttr> {
  static org::ImmCmdAttr to_immer(sem::CmdAttr const& value, AddContext const& ctx) {
    org::ImmCmdAttr result = SerdeDefaultProvider<org::ImmCmdAttr>::get();
    copy_field(result.target, value.target, ctx);
    copy_field(result.parameters, value.parameters, ctx);
    copy_field(result.attached, value.attached, ctx);
    copy_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<sem::Call, org::ImmCall> {
  static org::ImmCall to_immer(sem::Call const& value, AddContext const& ctx) {
    org::ImmCall result = SerdeDefaultProvider<org::ImmCall>::get();
    copy_field(result.name, value.name, ctx);
    copy_field(result.parameters, value.parameters, ctx);
    copy_field(result.isCommand, value.isCommand, ctx);
    copy_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<sem::List, org::ImmList> {
  static org::ImmList to_immer(sem::List const& value, AddContext const& ctx) {
    org::ImmList result = SerdeDefaultProvider<org::ImmList>::get();
    copy_field(result.attached, value.attached, ctx);
    copy_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<sem::ListItem, org::ImmListItem> {
  static org::ImmListItem to_immer(sem::ListItem const& value, AddContext const& ctx) {
    org::ImmListItem result = SerdeDefaultProvider<org::ImmListItem>::get();
    copy_field(result.checkbox, value.checkbox, ctx);
    copy_field(result.header, value.header, ctx);
    copy_field(result.bullet, value.bullet, ctx);
    copy_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<sem::DocumentOptions, org::ImmDocumentOptions> {
  static org::ImmDocumentOptions to_immer(sem::DocumentOptions const& value, AddContext const& ctx) {
    org::ImmDocumentOptions result = SerdeDefaultProvider<org::ImmDocumentOptions>::get();
    copy_field(result.initialVisibility, value.initialVisibility, ctx);
    copy_field(result.properties, value.properties, ctx);
    copy_field(result.exportConfig, value.exportConfig, ctx);
    copy_field(result.fixedWidthSections, value.fixedWidthSections, ctx);
    copy_field(result.startupIndented, value.startupIndented, ctx);
    copy_field(result.category, value.category, ctx);
    copy_field(result.setupfile, value.setupfile, ctx);
    copy_field(result.maxSubtreeLevelExport, value.maxSubtreeLevelExport, ctx);
    copy_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<sem::DocumentOptions::ExportConfig, org::ImmDocumentOptions::ExportConfig> {
  static org::ImmDocumentOptions::ExportConfig to_immer(sem::DocumentOptions::ExportConfig const& value, AddContext const& ctx) {
    org::ImmDocumentOptions::ExportConfig result = SerdeDefaultProvider<org::ImmDocumentOptions::ExportConfig>::get();
    copy_field(result.inlinetasks, value.inlinetasks, ctx);
    copy_field(result.footnotes, value.footnotes, ctx);
    copy_field(result.clock, value.clock, ctx);
    copy_field(result.author, value.author, ctx);
    copy_field(result.emphasis, value.emphasis, ctx);
    copy_field(result.specialStrings, value.specialStrings, ctx);
    copy_field(result.propertyDrawers, value.propertyDrawers, ctx);
    copy_field(result.statisticsCookies, value.statisticsCookies, ctx);
    copy_field(result.todoText, value.todoText, ctx);
    copy_field(result.brokenLinks, value.brokenLinks, ctx);
    copy_field(result.tocExport, value.tocExport, ctx);
    copy_field(result.tagExport, value.tagExport, ctx);
    copy_field(result.data, value.data, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<sem::DocumentOptions::ExportConfig::TaskExport, org::ImmDocumentOptions::ExportConfig::TaskExport> {
  static org::ImmDocumentOptions::ExportConfig::TaskExport to_immer(sem::DocumentOptions::ExportConfig::TaskExport const& value, AddContext const& ctx) {
    org::ImmDocumentOptions::ExportConfig::TaskExport result = SerdeDefaultProvider<org::ImmDocumentOptions::ExportConfig::TaskExport>::get();
    copy_field(result.taskWhitelist, value.taskWhitelist, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<sem::DocumentOptions::ExportConfig::DoExport, org::ImmDocumentOptions::ExportConfig::DoExport> {
  static org::ImmDocumentOptions::ExportConfig::DoExport to_immer(sem::DocumentOptions::ExportConfig::DoExport const& value, AddContext const& ctx) {
    org::ImmDocumentOptions::ExportConfig::DoExport result = SerdeDefaultProvider<org::ImmDocumentOptions::ExportConfig::DoExport>::get();
    copy_field(result.exportToc, value.exportToc, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<sem::DocumentOptions::ExportConfig::ExportFixed, org::ImmDocumentOptions::ExportConfig::ExportFixed> {
  static org::ImmDocumentOptions::ExportConfig::ExportFixed to_immer(sem::DocumentOptions::ExportConfig::ExportFixed const& value, AddContext const& ctx) {
    org::ImmDocumentOptions::ExportConfig::ExportFixed result = SerdeDefaultProvider<org::ImmDocumentOptions::ExportConfig::ExportFixed>::get();
    copy_field(result.exportLevels, value.exportLevels, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<sem::Document, org::ImmDocument> {
  static org::ImmDocument to_immer(sem::Document const& value, AddContext const& ctx) {
    org::ImmDocument result = SerdeDefaultProvider<org::ImmDocument>::get();
    copy_field(result.title, value.title, ctx);
    copy_field(result.author, value.author, ctx);
    copy_field(result.creator, value.creator, ctx);
    copy_field(result.filetags, value.filetags, ctx);
    copy_field(result.email, value.email, ctx);
    copy_field(result.language, value.language, ctx);
    copy_field(result.options, value.options, ctx);
    copy_field(result.exportFileName, value.exportFileName, ctx);
    copy_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<sem::FileTarget, org::ImmFileTarget> {
  static org::ImmFileTarget to_immer(sem::FileTarget const& value, AddContext const& ctx) {
    org::ImmFileTarget result = SerdeDefaultProvider<org::ImmFileTarget>::get();
    copy_field(result.path, value.path, ctx);
    copy_field(result.line, value.line, ctx);
    copy_field(result.searchTarget, value.searchTarget, ctx);
    copy_field(result.restrictToHeadlines, value.restrictToHeadlines, ctx);
    copy_field(result.targetId, value.targetId, ctx);
    copy_field(result.regexp, value.regexp, ctx);
    copy_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<sem::TextSeparator, org::ImmTextSeparator> {
  static org::ImmTextSeparator to_immer(sem::TextSeparator const& value, AddContext const& ctx) {
    org::ImmTextSeparator result = SerdeDefaultProvider<org::ImmTextSeparator>::get();
    copy_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<sem::Include, org::ImmInclude> {
  static org::ImmInclude to_immer(sem::Include const& value, AddContext const& ctx) {
    org::ImmInclude result = SerdeDefaultProvider<org::ImmInclude>::get();
    copy_field(result.path, value.path, ctx);
    copy_field(result.firstLine, value.firstLine, ctx);
    copy_field(result.lastLine, value.lastLine, ctx);
    copy_field(result.data, value.data, ctx);
    copy_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<sem::Include::Example, org::ImmInclude::Example> {
  static org::ImmInclude::Example to_immer(sem::Include::Example const& value, AddContext const& ctx) {
    org::ImmInclude::Example result = SerdeDefaultProvider<org::ImmInclude::Example>::get();
    return result;
  }
};

template <>
struct ImmSemSerde<sem::Include::Export, org::ImmInclude::Export> {
  static org::ImmInclude::Export to_immer(sem::Include::Export const& value, AddContext const& ctx) {
    org::ImmInclude::Export result = SerdeDefaultProvider<org::ImmInclude::Export>::get();
    return result;
  }
};

template <>
struct ImmSemSerde<sem::Include::Src, org::ImmInclude::Src> {
  static org::ImmInclude::Src to_immer(sem::Include::Src const& value, AddContext const& ctx) {
    org::ImmInclude::Src result = SerdeDefaultProvider<org::ImmInclude::Src>::get();
    return result;
  }
};

template <>
struct ImmSemSerde<sem::Include::OrgDocument, org::ImmInclude::OrgDocument> {
  static org::ImmInclude::OrgDocument to_immer(sem::Include::OrgDocument const& value, AddContext const& ctx) {
    org::ImmInclude::OrgDocument result = SerdeDefaultProvider<org::ImmInclude::OrgDocument>::get();
    copy_field(result.minLevel, value.minLevel, ctx);
    return result;
  }
};

template <>
struct ImmSemSerde<sem::DocumentGroup, org::ImmDocumentGroup> {
  static org::ImmDocumentGroup to_immer(sem::DocumentGroup const& value, AddContext const& ctx) {
    org::ImmDocumentGroup result = SerdeDefaultProvider<org::ImmDocumentGroup>::get();
    copy_field(result.subnodes, value.subnodes, ctx);
    return result;
  }
};

/* clang-format on */