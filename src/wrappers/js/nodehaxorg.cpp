/* clang-format off */
struct UserTimeBreakdownJs : public Napi::ObjectWrap<UserTimeBreakdownJs> {};

struct UserTimeJs : public Napi::ObjectWrap<UserTimeJs> {
  Napi::Value getBreakdown(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &UserTimeJs::getBreakdown); }
  Napi::Value format(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &UserTimeJs::format); }
};

struct LineColJs : public Napi::ObjectWrap<LineColJs> {};

struct OrgJsonJs : public Napi::ObjectWrap<OrgJsonJs> {
  Napi::Value getKind(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &OrgJsonJs::getKind); }
  Napi::Value getJsonString(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &OrgJsonJs::getJsonString); }
  Napi::Value at(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &OrgJsonJs::at); }
  Napi::Value at(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &OrgJsonJs::at); }
  Napi::Value getString(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &OrgJsonJs::getString); }
  Napi::Value getField(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &OrgJsonJs::getField); }
  Napi::Value getItem(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &OrgJsonJs::getItem); }
  Napi::Value getInt(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &OrgJsonJs::getInt); }
  Napi::Value getBool(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &OrgJsonJs::getBool); }
  Napi::Value getArray(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &OrgJsonJs::getArray); }
};

struct OrgJs : public Napi::ObjectWrap<OrgJs> {
  Napi::Value getKind(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &OrgJs::getKind); }
  Napi::Value isGenerated(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &OrgJs::isGenerated); }
  Napi::Value push_back(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &OrgJs::push_back); }
  Napi::Value insert(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &OrgJs::insert); }
  Napi::Value at(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &OrgJs::at); }
  Napi::Value is(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &OrgJs::is); }
};

struct OperationsTracerJs : public Napi::ObjectWrap<OperationsTracerJs> {
  Napi::Value setTraceFileStr(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &OperationsTracerJs::setTraceFileStr); }
  Napi::Value sendMessage(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &OperationsTracerJs::sendMessage); }
};

struct ImmIdJs : public Napi::ObjectWrap<ImmIdJs> {
  Napi::Value getKind(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ImmIdJs::getKind); }
  Napi::Value is(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ImmIdJs::is); }
  Napi::Value getNodeIndex(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ImmIdJs::getNodeIndex); }
  Napi::Value getReadableId(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ImmIdJs::getReadableId); }
};

struct ImmPathStepJs : public Napi::ObjectWrap<ImmPathStepJs> {};

struct ImmPathJs : public Napi::ObjectWrap<ImmPathJs> {
  Napi::Value empty(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ImmPathJs::empty); }
};

struct ImmUniqIdJs : public Napi::ObjectWrap<ImmUniqIdJs> {};

struct ImmNoneValueReadJs : public Napi::ObjectWrap<ImmNoneValueReadJs> {};

struct ImmErrorItemValueReadJs : public Napi::ObjectWrap<ImmErrorItemValueReadJs> {
  Napi::Value getMessage(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ImmErrorItemValueReadJs::getMessage); }
  Napi::Value getFunction(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ImmErrorItemValueReadJs::getFunction); }
  Napi::Value getLine(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ImmErrorItemValueReadJs::getLine); }
};

struct ImmErrorGroupValueReadJs : public Napi::ObjectWrap<ImmErrorGroupValueReadJs> {
  Napi::Value getDiagnostics(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ImmErrorGroupValueReadJs::getDiagnostics); }
  Napi::Value getFunction(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ImmErrorGroupValueReadJs::getFunction); }
  Napi::Value getLine(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ImmErrorGroupValueReadJs::getLine); }
};

struct ImmStmtListValueReadJs : public Napi::ObjectWrap<ImmStmtListValueReadJs> {};

struct ImmEmptyValueReadJs : public Napi::ObjectWrap<ImmEmptyValueReadJs> {};

struct ImmCmdCaptionValueReadJs : public Napi::ObjectWrap<ImmCmdCaptionValueReadJs> {
  Napi::Value getText(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ImmCmdCaptionValueReadJs::getText); }
};

struct ImmCmdColumnsValueReadJs : public Napi::ObjectWrap<ImmCmdColumnsValueReadJs> {
  Napi::Value getView(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ImmCmdColumnsValueReadJs::getView); }
};

struct ImmCmdNameValueReadJs : public Napi::ObjectWrap<ImmCmdNameValueReadJs> {
  Napi::Value getName(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ImmCmdNameValueReadJs::getName); }
};

struct ImmCmdCustomArgsValueReadJs : public Napi::ObjectWrap<ImmCmdCustomArgsValueReadJs> {
  Napi::Value getName(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ImmCmdCustomArgsValueReadJs::getName); }
  Napi::Value getIsattached(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ImmCmdCustomArgsValueReadJs::getIsattached); }
};

struct ImmCmdCustomRawValueReadJs : public Napi::ObjectWrap<ImmCmdCustomRawValueReadJs> {
  Napi::Value getName(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ImmCmdCustomRawValueReadJs::getName); }
  Napi::Value getIsattached(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ImmCmdCustomRawValueReadJs::getIsattached); }
  Napi::Value getText(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ImmCmdCustomRawValueReadJs::getText); }
};

struct ImmCmdCustomTextValueReadJs : public Napi::ObjectWrap<ImmCmdCustomTextValueReadJs> {
  Napi::Value getName(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ImmCmdCustomTextValueReadJs::getName); }
  Napi::Value getIsattached(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ImmCmdCustomTextValueReadJs::getIsattached); }
  Napi::Value getText(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ImmCmdCustomTextValueReadJs::getText); }
};

struct ImmCmdCallValueReadJs : public Napi::ObjectWrap<ImmCmdCallValueReadJs> {
  Napi::Value getName(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ImmCmdCallValueReadJs::getName); }
  Napi::Value getFilename(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ImmCmdCallValueReadJs::getFilename); }
  Napi::Value getInsideheaderattrs(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ImmCmdCallValueReadJs::getInsideheaderattrs); }
  Napi::Value getCallattrs(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ImmCmdCallValueReadJs::getCallattrs); }
  Napi::Value getEndheaderattrs(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ImmCmdCallValueReadJs::getEndheaderattrs); }
  Napi::Value getResult(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ImmCmdCallValueReadJs::getResult); }
};

struct ImmCmdTblfmValueReadJs : public Napi::ObjectWrap<ImmCmdTblfmValueReadJs> {
  Napi::Value getExpr(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ImmCmdTblfmValueReadJs::getExpr); }
};

struct ImmHashTagValueReadJs : public Napi::ObjectWrap<ImmHashTagValueReadJs> {
  Napi::Value getText(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ImmHashTagValueReadJs::getText); }
};

struct ImmInlineFootnoteValueReadJs : public Napi::ObjectWrap<ImmInlineFootnoteValueReadJs> {
  Napi::Value getTag(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ImmInlineFootnoteValueReadJs::getTag); }
  Napi::Value getDefinition(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ImmInlineFootnoteValueReadJs::getDefinition); }
};

struct ImmInlineExportValueReadJs : public Napi::ObjectWrap<ImmInlineExportValueReadJs> {
  Napi::Value getExporter(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ImmInlineExportValueReadJs::getExporter); }
  Napi::Value getContent(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ImmInlineExportValueReadJs::getContent); }
};

struct ImmTimeValueReadJs : public Napi::ObjectWrap<ImmTimeValueReadJs> {
  Napi::Value getIsactive(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ImmTimeValueReadJs::getIsactive); }
  Napi::Value getTime(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ImmTimeValueReadJs::getTime); }
};

struct ImmTimeRangeValueReadJs : public Napi::ObjectWrap<ImmTimeRangeValueReadJs> {
  Napi::Value getFrom(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ImmTimeRangeValueReadJs::getFrom); }
  Napi::Value getTo(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ImmTimeRangeValueReadJs::getTo); }
};

struct ImmMacroValueReadJs : public Napi::ObjectWrap<ImmMacroValueReadJs> {
  Napi::Value getName(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ImmMacroValueReadJs::getName); }
  Napi::Value getAttrs(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ImmMacroValueReadJs::getAttrs); }
};

struct ImmSymbolValueReadJs : public Napi::ObjectWrap<ImmSymbolValueReadJs> {
  Napi::Value getName(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ImmSymbolValueReadJs::getName); }
  Napi::Value getParameters(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ImmSymbolValueReadJs::getParameters); }
  Napi::Value getPositional(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ImmSymbolValueReadJs::getPositional); }
};

struct ImmEscapedValueReadJs : public Napi::ObjectWrap<ImmEscapedValueReadJs> {};

struct ImmNewlineValueReadJs : public Napi::ObjectWrap<ImmNewlineValueReadJs> {};

struct ImmSpaceValueReadJs : public Napi::ObjectWrap<ImmSpaceValueReadJs> {};

struct ImmWordValueReadJs : public Napi::ObjectWrap<ImmWordValueReadJs> {};

struct ImmAtMentionValueReadJs : public Napi::ObjectWrap<ImmAtMentionValueReadJs> {};

struct ImmRawTextValueReadJs : public Napi::ObjectWrap<ImmRawTextValueReadJs> {};

struct ImmPunctuationValueReadJs : public Napi::ObjectWrap<ImmPunctuationValueReadJs> {};

struct ImmPlaceholderValueReadJs : public Napi::ObjectWrap<ImmPlaceholderValueReadJs> {};

struct ImmBigIdentValueReadJs : public Napi::ObjectWrap<ImmBigIdentValueReadJs> {};

struct ImmTextTargetValueReadJs : public Napi::ObjectWrap<ImmTextTargetValueReadJs> {};

struct ImmBoldValueReadJs : public Napi::ObjectWrap<ImmBoldValueReadJs> {};

struct ImmUnderlineValueReadJs : public Napi::ObjectWrap<ImmUnderlineValueReadJs> {};

struct ImmMonospaceValueReadJs : public Napi::ObjectWrap<ImmMonospaceValueReadJs> {};

struct ImmMarkQuoteValueReadJs : public Napi::ObjectWrap<ImmMarkQuoteValueReadJs> {};

struct ImmVerbatimValueReadJs : public Napi::ObjectWrap<ImmVerbatimValueReadJs> {};

struct ImmItalicValueReadJs : public Napi::ObjectWrap<ImmItalicValueReadJs> {};

struct ImmStrikeValueReadJs : public Napi::ObjectWrap<ImmStrikeValueReadJs> {};

struct ImmParValueReadJs : public Napi::ObjectWrap<ImmParValueReadJs> {};

struct ImmRadioTargetValueReadJs : public Napi::ObjectWrap<ImmRadioTargetValueReadJs> {
  Napi::Value getWords(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ImmRadioTargetValueReadJs::getWords); }
};

struct ImmLatexValueReadJs : public Napi::ObjectWrap<ImmLatexValueReadJs> {};

struct ImmLinkValueReadJs : public Napi::ObjectWrap<ImmLinkValueReadJs> {
  Napi::Value getDescription(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ImmLinkValueReadJs::getDescription); }
  Napi::Value getTarget(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ImmLinkValueReadJs::getTarget); }
};

struct ImmBlockCenterValueReadJs : public Napi::ObjectWrap<ImmBlockCenterValueReadJs> {};

struct ImmBlockQuoteValueReadJs : public Napi::ObjectWrap<ImmBlockQuoteValueReadJs> {};

struct ImmBlockCommentValueReadJs : public Napi::ObjectWrap<ImmBlockCommentValueReadJs> {};

struct ImmBlockVerseValueReadJs : public Napi::ObjectWrap<ImmBlockVerseValueReadJs> {};

struct ImmBlockDynamicFallbackValueReadJs : public Napi::ObjectWrap<ImmBlockDynamicFallbackValueReadJs> {
  Napi::Value getName(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ImmBlockDynamicFallbackValueReadJs::getName); }
};

struct ImmBlockExampleValueReadJs : public Napi::ObjectWrap<ImmBlockExampleValueReadJs> {};

struct ImmBlockExportValueReadJs : public Napi::ObjectWrap<ImmBlockExportValueReadJs> {
  Napi::Value getExporter(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ImmBlockExportValueReadJs::getExporter); }
  Napi::Value getContent(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ImmBlockExportValueReadJs::getContent); }
};

struct ImmBlockAdmonitionValueReadJs : public Napi::ObjectWrap<ImmBlockAdmonitionValueReadJs> {};

struct ImmBlockCodeEvalResultValueReadJs : public Napi::ObjectWrap<ImmBlockCodeEvalResultValueReadJs> {
  Napi::Value getRaw(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ImmBlockCodeEvalResultValueReadJs::getRaw); }
  Napi::Value getNode(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ImmBlockCodeEvalResultValueReadJs::getNode); }
};

struct ImmBlockCodeValueReadJs : public Napi::ObjectWrap<ImmBlockCodeValueReadJs> {
  Napi::Value getLang(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ImmBlockCodeValueReadJs::getLang); }
  Napi::Value getExports(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ImmBlockCodeValueReadJs::getExports); }
  Napi::Value getResult(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ImmBlockCodeValueReadJs::getResult); }
  Napi::Value getLines(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ImmBlockCodeValueReadJs::getLines); }
  Napi::Value getCache(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ImmBlockCodeValueReadJs::getCache); }
  Napi::Value getEval(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ImmBlockCodeValueReadJs::getEval); }
  Napi::Value getNoweb(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ImmBlockCodeValueReadJs::getNoweb); }
  Napi::Value getHlines(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ImmBlockCodeValueReadJs::getHlines); }
  Napi::Value getTangle(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ImmBlockCodeValueReadJs::getTangle); }
  Napi::Value getSwitches(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ImmBlockCodeValueReadJs::getSwitches); }
};

struct ImmSubtreeLogValueReadJs : public Napi::ObjectWrap<ImmSubtreeLogValueReadJs> {
  Napi::Value getHead(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ImmSubtreeLogValueReadJs::getHead); }
  Napi::Value getDesc(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ImmSubtreeLogValueReadJs::getDesc); }
};

struct ImmSubtreeValueReadJs : public Napi::ObjectWrap<ImmSubtreeValueReadJs> {
  Napi::Value getLevel(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ImmSubtreeValueReadJs::getLevel); }
  Napi::Value getTreeid(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ImmSubtreeValueReadJs::getTreeid); }
  Napi::Value getTodo(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ImmSubtreeValueReadJs::getTodo); }
  Napi::Value getCompletion(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ImmSubtreeValueReadJs::getCompletion); }
  Napi::Value getDescription(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ImmSubtreeValueReadJs::getDescription); }
  Napi::Value getTags(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ImmSubtreeValueReadJs::getTags); }
  Napi::Value getTitle(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ImmSubtreeValueReadJs::getTitle); }
  Napi::Value getLogbook(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ImmSubtreeValueReadJs::getLogbook); }
  Napi::Value getProperties(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ImmSubtreeValueReadJs::getProperties); }
  Napi::Value getClosed(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ImmSubtreeValueReadJs::getClosed); }
  Napi::Value getDeadline(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ImmSubtreeValueReadJs::getDeadline); }
  Napi::Value getScheduled(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ImmSubtreeValueReadJs::getScheduled); }
  Napi::Value getIscomment(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ImmSubtreeValueReadJs::getIscomment); }
  Napi::Value getIsarchived(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ImmSubtreeValueReadJs::getIsarchived); }
  Napi::Value getPriority(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ImmSubtreeValueReadJs::getPriority); }
};

struct ImmCellValueReadJs : public Napi::ObjectWrap<ImmCellValueReadJs> {
  Napi::Value getIsblock(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ImmCellValueReadJs::getIsblock); }
};

struct ImmRowValueReadJs : public Napi::ObjectWrap<ImmRowValueReadJs> {
  Napi::Value getCells(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ImmRowValueReadJs::getCells); }
  Napi::Value getIsblock(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ImmRowValueReadJs::getIsblock); }
};

struct ImmTableValueReadJs : public Napi::ObjectWrap<ImmTableValueReadJs> {
  Napi::Value getRows(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ImmTableValueReadJs::getRows); }
  Napi::Value getIsblock(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ImmTableValueReadJs::getIsblock); }
};

struct ImmParagraphValueReadJs : public Napi::ObjectWrap<ImmParagraphValueReadJs> {};

struct ImmColonExampleValueReadJs : public Napi::ObjectWrap<ImmColonExampleValueReadJs> {};

struct ImmCmdAttrValueReadJs : public Napi::ObjectWrap<ImmCmdAttrValueReadJs> {
  Napi::Value getTarget(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ImmCmdAttrValueReadJs::getTarget); }
};

struct ImmCmdExportValueReadJs : public Napi::ObjectWrap<ImmCmdExportValueReadJs> {
  Napi::Value getExporter(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ImmCmdExportValueReadJs::getExporter); }
  Napi::Value getContent(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ImmCmdExportValueReadJs::getContent); }
};

struct ImmCallValueReadJs : public Napi::ObjectWrap<ImmCallValueReadJs> {
  Napi::Value getName(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ImmCallValueReadJs::getName); }
  Napi::Value getAttrs(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ImmCallValueReadJs::getAttrs); }
  Napi::Value getIscommand(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ImmCallValueReadJs::getIscommand); }
};

struct ImmListValueReadJs : public Napi::ObjectWrap<ImmListValueReadJs> {};

struct ImmListItemValueReadJs : public Napi::ObjectWrap<ImmListItemValueReadJs> {
  Napi::Value getCheckbox(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ImmListItemValueReadJs::getCheckbox); }
  Napi::Value getHeader(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ImmListItemValueReadJs::getHeader); }
  Napi::Value getBullet(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ImmListItemValueReadJs::getBullet); }
};

struct ImmDocumentOptionsValueReadJs : public Napi::ObjectWrap<ImmDocumentOptionsValueReadJs> {
  Napi::Value getInitialvisibility(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ImmDocumentOptionsValueReadJs::getInitialvisibility); }
  Napi::Value getProperties(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ImmDocumentOptionsValueReadJs::getProperties); }
  Napi::Value getExportconfig(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ImmDocumentOptionsValueReadJs::getExportconfig); }
  Napi::Value getFixedwidthsections(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ImmDocumentOptionsValueReadJs::getFixedwidthsections); }
  Napi::Value getStartupindented(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ImmDocumentOptionsValueReadJs::getStartupindented); }
  Napi::Value getCategory(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ImmDocumentOptionsValueReadJs::getCategory); }
  Napi::Value getSetupfile(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ImmDocumentOptionsValueReadJs::getSetupfile); }
  Napi::Value getMaxsubtreelevelexport(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ImmDocumentOptionsValueReadJs::getMaxsubtreelevelexport); }
  Napi::Value getColumns(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ImmDocumentOptionsValueReadJs::getColumns); }
};

struct ImmDocumentFragmentValueReadJs : public Napi::ObjectWrap<ImmDocumentFragmentValueReadJs> {
  Napi::Value getBaseline(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ImmDocumentFragmentValueReadJs::getBaseline); }
  Napi::Value getBasecol(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ImmDocumentFragmentValueReadJs::getBasecol); }
};

struct ImmCriticMarkupValueReadJs : public Napi::ObjectWrap<ImmCriticMarkupValueReadJs> {
  Napi::Value getKind(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ImmCriticMarkupValueReadJs::getKind); }
};

struct ImmDocumentValueReadJs : public Napi::ObjectWrap<ImmDocumentValueReadJs> {
  Napi::Value getTitle(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ImmDocumentValueReadJs::getTitle); }
  Napi::Value getAuthor(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ImmDocumentValueReadJs::getAuthor); }
  Napi::Value getCreator(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ImmDocumentValueReadJs::getCreator); }
  Napi::Value getFiletags(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ImmDocumentValueReadJs::getFiletags); }
  Napi::Value getEmail(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ImmDocumentValueReadJs::getEmail); }
  Napi::Value getLanguage(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ImmDocumentValueReadJs::getLanguage); }
  Napi::Value getOptions(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ImmDocumentValueReadJs::getOptions); }
  Napi::Value getExportfilename(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ImmDocumentValueReadJs::getExportfilename); }
};

struct ImmFileTargetValueReadJs : public Napi::ObjectWrap<ImmFileTargetValueReadJs> {
  Napi::Value getPath(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ImmFileTargetValueReadJs::getPath); }
  Napi::Value getLine(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ImmFileTargetValueReadJs::getLine); }
  Napi::Value getSearchtarget(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ImmFileTargetValueReadJs::getSearchtarget); }
  Napi::Value getRestricttoheadlines(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ImmFileTargetValueReadJs::getRestricttoheadlines); }
  Napi::Value getTargetid(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ImmFileTargetValueReadJs::getTargetid); }
  Napi::Value getRegexp(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ImmFileTargetValueReadJs::getRegexp); }
};

struct ImmTextSeparatorValueReadJs : public Napi::ObjectWrap<ImmTextSeparatorValueReadJs> {};

struct ImmDocumentGroupValueReadJs : public Napi::ObjectWrap<ImmDocumentGroupValueReadJs> {};

struct ImmFileValueReadJs : public Napi::ObjectWrap<ImmFileValueReadJs> {
  Napi::Value getRelpath(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ImmFileValueReadJs::getRelpath); }
  Napi::Value getAbspath(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ImmFileValueReadJs::getAbspath); }
  Napi::Value getData(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ImmFileValueReadJs::getData); }
};

struct ImmDirectoryValueReadJs : public Napi::ObjectWrap<ImmDirectoryValueReadJs> {
  Napi::Value getRelpath(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ImmDirectoryValueReadJs::getRelpath); }
  Napi::Value getAbspath(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ImmDirectoryValueReadJs::getAbspath); }
};

struct ImmSymlinkValueReadJs : public Napi::ObjectWrap<ImmSymlinkValueReadJs> {
  Napi::Value getIsdirectory(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ImmSymlinkValueReadJs::getIsdirectory); }
  Napi::Value getAbspath(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ImmSymlinkValueReadJs::getAbspath); }
};

struct ImmCmdIncludeValueReadJs : public Napi::ObjectWrap<ImmCmdIncludeValueReadJs> {
  Napi::Value getPath(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ImmCmdIncludeValueReadJs::getPath); }
  Napi::Value getFirstline(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ImmCmdIncludeValueReadJs::getFirstline); }
  Napi::Value getLastline(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ImmCmdIncludeValueReadJs::getLastline); }
  Napi::Value getData(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ImmCmdIncludeValueReadJs::getData); }
};

struct ImmAstContextJs : public Napi::ObjectWrap<ImmAstContextJs> {
  Napi::Value addRoot(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &ImmAstContextJs::addRoot); }
  Napi::Value get(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &ImmAstContextJs::get); }
};

struct ImmAstVersionJs : public Napi::ObjectWrap<ImmAstVersionJs> {
  Napi::Value getRoot(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ImmAstVersionJs::getRoot); }
  Napi::Value getRootAdapter(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ImmAstVersionJs::getRootAdapter); }
  Napi::Value getContext(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ImmAstVersionJs::getContext); }
};

struct ImmAdapterJs : public Napi::ObjectWrap<ImmAdapterJs> {
  Napi::Value size(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ImmAdapterJs::size); }
  Napi::Value isNil(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ImmAdapterJs::isNil); }
  Napi::Value isRoot(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ImmAdapterJs::isRoot); }
  Napi::Value getKind(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ImmAdapterJs::getKind); }
  Napi::Value uniq(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ImmAdapterJs::uniq); }
  Napi::Value treeReprString(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ImmAdapterJs::treeReprString); }
  Napi::Value treeReprStringOpts(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ImmAdapterJs::treeReprStringOpts); }
  Napi::Value isDirectParentOf(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ImmAdapterJs::isDirectParentOf); }
  Napi::Value isIndirectParentOf(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ImmAdapterJs::isIndirectParentOf); }
  Napi::Value isSubnodeOf(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ImmAdapterJs::isSubnodeOf); }
  Napi::Value getParent(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ImmAdapterJs::getParent); }
  Napi::Value getSelfIndex(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ImmAdapterJs::getSelfIndex); }
  Napi::Value at(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ImmAdapterJs::at); }
  Napi::Value at(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ImmAdapterJs::at); }
  Napi::Value at(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ImmAdapterJs::at); }
  Napi::Value at(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ImmAdapterJs::at); }
  Napi::Value is(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ImmAdapterJs::is); }
  Napi::Value sub(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ImmAdapterJs::sub); }
};

struct ImmAdapterVirtualBaseJs : public Napi::ObjectWrap<ImmAdapterVirtualBaseJs> {};

struct OrgParseFragmentJs : public Napi::ObjectWrap<OrgParseFragmentJs> {};

struct OrgParseParametersJs : public Napi::ObjectWrap<OrgParseParametersJs> {};

struct OrgDirectoryParseParametersJs : public Napi::ObjectWrap<OrgDirectoryParseParametersJs> {};

struct OrgYamlExportOptsJs : public Napi::ObjectWrap<OrgYamlExportOptsJs> {};

struct OrgTreeExportOptsJs : public Napi::ObjectWrap<OrgTreeExportOptsJs> {};

struct AstTrackingPathJs : public Napi::ObjectWrap<AstTrackingPathJs> {
  Napi::Value getParent(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &AstTrackingPathJs::getParent); }
  Napi::Value getNode(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &AstTrackingPathJs::getNode); }
};

struct AstTrackingAlternativesJs : public Napi::ObjectWrap<AstTrackingAlternativesJs> {
  Napi::Value getAllNodes(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &AstTrackingAlternativesJs::getAllNodes); }
  Napi::Value getNode(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &AstTrackingAlternativesJs::getNode); }
};

struct AstTrackingGroupJs : public Napi::ObjectWrap<AstTrackingGroupJs> {
  Napi::Value getRadioTarget(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &AstTrackingGroupJs::getRadioTarget); }
  Napi::Value getTrackedHashtag(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &AstTrackingGroupJs::getTrackedHashtag); }
  Napi::Value getTrackedHashtag(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &AstTrackingGroupJs::getTrackedHashtag); }
  Napi::Value getSingle(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &AstTrackingGroupJs::getSingle); }
  Napi::Value getRadioTarget(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &AstTrackingGroupJs::getRadioTarget); }
  Napi::Value getSingle(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &AstTrackingGroupJs::getSingle); }
  Napi::Value isSingle(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &AstTrackingGroupJs::isSingle); }
  Napi::Value isTrackedHashtag(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &AstTrackingGroupJs::isTrackedHashtag); }
  Napi::Value isRadioTarget(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &AstTrackingGroupJs::isRadioTarget); }
};

struct AstTrackingMapJs : public Napi::ObjectWrap<AstTrackingMapJs> {
  Napi::Value getIdPath(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &AstTrackingMapJs::getIdPath); }
  Napi::Value getNamePath(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &AstTrackingMapJs::getNamePath); }
  Napi::Value getAnchorTarget(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &AstTrackingMapJs::getAnchorTarget); }
  Napi::Value getFootnotePath(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &AstTrackingMapJs::getFootnotePath); }
};

struct SequenceSegmentJs : public Napi::ObjectWrap<SequenceSegmentJs> {};

struct SequenceSegmentGroupJs : public Napi::ObjectWrap<SequenceSegmentGroupJs> {};

struct SequenceAnnotationTagJs : public Napi::ObjectWrap<SequenceAnnotationTagJs> {};

struct SequenceAnnotationJs : public Napi::ObjectWrap<SequenceAnnotationJs> {
  Napi::Value isAnnotatedWith(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &SequenceAnnotationJs::isAnnotatedWith); }
};

struct MapLinkJs : public Napi::ObjectWrap<MapLinkJs> {};

struct MapNodePropJs : public Napi::ObjectWrap<MapNodePropJs> {
  Napi::Value getSubtreeId(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &MapNodePropJs::getSubtreeId); }
  Napi::Value getFootnoteName(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &MapNodePropJs::getFootnoteName); }
};

struct MapEdgePropJs : public Napi::ObjectWrap<MapEdgePropJs> {};

struct MapNodeJs : public Napi::ObjectWrap<MapNodeJs> {
  Napi::Value operator==(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &MapNodeJs::operator==); }
  Napi::Value operator<(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &MapNodeJs::operator<); }
};

struct MapEdgeJs : public Napi::ObjectWrap<MapEdgeJs> {};

struct MapGraphJs : public Napi::ObjectWrap<MapGraphJs> {
  Napi::Value nodeCount(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &MapGraphJs::nodeCount); }
  Napi::Value edgeCount(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &MapGraphJs::edgeCount); }
  Napi::Value outNodes(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &MapGraphJs::outNodes); }
  Napi::Value inNodes(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &MapGraphJs::inNodes); }
  Napi::Value adjEdges(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &MapGraphJs::adjEdges); }
  Napi::Value adjNodes(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &MapGraphJs::adjNodes); }
  Napi::Value outEdges(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &MapGraphJs::outEdges); }
  Napi::Value inEdges(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &MapGraphJs::inEdges); }
  Napi::Value outDegree(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &MapGraphJs::outDegree); }
  Napi::Value inDegree(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &MapGraphJs::inDegree); }
  Napi::Value isRegisteredNode(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &MapGraphJs::isRegisteredNode); }
  Napi::Value isRegisteredNode(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &MapGraphJs::isRegisteredNode); }
  Napi::Value at(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &MapGraphJs::at); }
  Napi::Value at(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &MapGraphJs::at); }
  Napi::Value addEdge(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &MapGraphJs::addEdge); }
  Napi::Value addEdge(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &MapGraphJs::addEdge); }
  Napi::Value addNode(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &MapGraphJs::addNode); }
  Napi::Value addNode(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &MapGraphJs::addNode); }
  Napi::Value hasEdge(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &MapGraphJs::hasEdge); }
  Napi::Value hasNode(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &MapGraphJs::hasNode); }
  Napi::Value hasEdge(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &MapGraphJs::hasEdge); }
};

struct MapGraphStateJs : public Napi::ObjectWrap<MapGraphStateJs> {
  Napi::Value FromAstContext(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &MapGraphStateJs::FromAstContext); }
};

struct PyCodeEvalParametersJs : public Napi::ObjectWrap<PyCodeEvalParametersJs> {
  Napi::Value setTraceFile(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &PyCodeEvalParametersJs::setTraceFile); }
};

struct ExporterPythonJs : public Napi::ObjectWrap<ExporterPythonJs> {
  Napi::Value enableBufferTrace(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &ExporterPythonJs::enableBufferTrace); }
  Napi::Value getTraceBuffer(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ExporterPythonJs::getTraceBuffer); }
  Napi::Value enableFileTrace(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &ExporterPythonJs::enableFileTrace); }
  Napi::Value setVisitAnyIdAround(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &ExporterPythonJs::setVisitAnyIdAround); }
  Napi::Value setVisitAnyIdIn(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &ExporterPythonJs::setVisitAnyIdIn); }
  Napi::Value setVisitAnyField(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &ExporterPythonJs::setVisitAnyField); }
  Napi::Value setEvalTopCb(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &ExporterPythonJs::setEvalTopCb); }
  Napi::Value setVisitIdAround(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &ExporterPythonJs::setVisitIdAround); }
  Napi::Value setEvalIdAround(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &ExporterPythonJs::setEvalIdAround); }
  Napi::Value setVisitIdInCb(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &ExporterPythonJs::setVisitIdInCb); }
  Napi::Value setEvalIdIn(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &ExporterPythonJs::setEvalIdIn); }
  Napi::Value setVisitLeafField(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &ExporterPythonJs::setVisitLeafField); }
  Napi::Value setEvalLeafField(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &ExporterPythonJs::setEvalLeafField); }
  Napi::Value setVisitOrgField(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &ExporterPythonJs::setVisitOrgField); }
  Napi::Value setEvalOrgField(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &ExporterPythonJs::setEvalOrgField); }
  Napi::Value setSelf(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &ExporterPythonJs::setSelf); }
  Napi::Value setNewOrgRes(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &ExporterPythonJs::setNewOrgRes); }
  Napi::Value setNewAnyOrgRes(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &ExporterPythonJs::setNewAnyOrgRes); }
  Napi::Value setNewLeafRes(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &ExporterPythonJs::setNewLeafRes); }
  Napi::Value setNewAnyLeafRes(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &ExporterPythonJs::setNewAnyLeafRes); }
  Napi::Value setPushVisitAnyId(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &ExporterPythonJs::setPushVisitAnyId); }
  Napi::Value setPopVisitAnyId(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &ExporterPythonJs::setPopVisitAnyId); }
  Napi::Value setPushVisitId(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &ExporterPythonJs::setPushVisitId); }
  Napi::Value setPopVisitIdCb(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &ExporterPythonJs::setPopVisitIdCb); }
  Napi::Value setVisitAnyHookCb(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &ExporterPythonJs::setVisitAnyHookCb); }
  Napi::Value setVisitIdHook(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &ExporterPythonJs::setVisitIdHook); }
  Napi::Value print_trace(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &ExporterPythonJs::print_trace); }
  Napi::Value evalTop(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &ExporterPythonJs::evalTop); }
  Napi::Value eval(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &ExporterPythonJs::eval); }
};

struct LispCodeJs : public Napi::ObjectWrap<LispCodeJs> {
  Napi::Value operator==(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &LispCodeJs::operator==); }
  Napi::Value LispCode(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &LispCodeJs::LispCode); }
  Napi::Value isCall(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &LispCodeJs::isCall); }
  Napi::Value getCall(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &LispCodeJs::getCall); }
  Napi::Value getCall(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &LispCodeJs::getCall); }
  Napi::Value isList(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &LispCodeJs::isList); }
  Napi::Value getList(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &LispCodeJs::getList); }
  Napi::Value getList(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &LispCodeJs::getList); }
  Napi::Value isKeyValue(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &LispCodeJs::isKeyValue); }
  Napi::Value getKeyValue(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &LispCodeJs::getKeyValue); }
  Napi::Value getKeyValue(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &LispCodeJs::getKeyValue); }
  Napi::Value isNumber(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &LispCodeJs::isNumber); }
  Napi::Value getNumber(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &LispCodeJs::getNumber); }
  Napi::Value getNumber(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &LispCodeJs::getNumber); }
  Napi::Value isText(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &LispCodeJs::isText); }
  Napi::Value getText(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &LispCodeJs::getText); }
  Napi::Value getText(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &LispCodeJs::getText); }
  Napi::Value isIdent(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &LispCodeJs::isIdent); }
  Napi::Value getIdent(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &LispCodeJs::getIdent); }
  Napi::Value getIdent(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &LispCodeJs::getIdent); }
  Napi::Value isBoolean(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &LispCodeJs::isBoolean); }
  Napi::Value getBoolean(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &LispCodeJs::getBoolean); }
  Napi::Value getBoolean(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &LispCodeJs::getBoolean); }
  Napi::Value isReal(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &LispCodeJs::isReal); }
  Napi::Value getReal(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &LispCodeJs::getReal); }
  Napi::Value getReal(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &LispCodeJs::getReal); }
  Napi::Value getKind(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &LispCodeJs::getKind); }
  Napi::Value getKind(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &LispCodeJs::getKind); }
  Napi::Value sub_variant_get_name(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &LispCodeJs::sub_variant_get_name); }
  Napi::Value sub_variant_get_data(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &LispCodeJs::sub_variant_get_data); }
  Napi::Value sub_variant_get_kind(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &LispCodeJs::sub_variant_get_kind); }
};

struct TblfmJs : public Napi::ObjectWrap<TblfmJs> {
  Napi::Value operator==(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &TblfmJs::operator==); }
};

struct AttrValueJs : public Napi::ObjectWrap<AttrValueJs> {
  Napi::Value getBool(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &AttrValueJs::getBool); }
  Napi::Value getInt(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &AttrValueJs::getInt); }
  Napi::Value getString(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &AttrValueJs::getString); }
  Napi::Value getFile(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &AttrValueJs::getFile); }
  Napi::Value getReference(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &AttrValueJs::getReference); }
  Napi::Value getDouble(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &AttrValueJs::getDouble); }
  Napi::Value operator==(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &AttrValueJs::operator==); }
  Napi::Value AttrValue(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &AttrValueJs::AttrValue); }
  Napi::Value isTextValue(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &AttrValueJs::isTextValue); }
  Napi::Value getTextValue(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &AttrValueJs::getTextValue); }
  Napi::Value getTextValue(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &AttrValueJs::getTextValue); }
  Napi::Value isFileReference(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &AttrValueJs::isFileReference); }
  Napi::Value getFileReference(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &AttrValueJs::getFileReference); }
  Napi::Value getFileReference(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &AttrValueJs::getFileReference); }
  Napi::Value isLispValue(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &AttrValueJs::isLispValue); }
  Napi::Value getLispValue(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &AttrValueJs::getLispValue); }
  Napi::Value getLispValue(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &AttrValueJs::getLispValue); }
  Napi::Value getDataKind(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &AttrValueJs::getDataKind); }
  Napi::Value getDataKind(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &AttrValueJs::getDataKind); }
  Napi::Value sub_variant_get_name(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &AttrValueJs::sub_variant_get_name); }
  Napi::Value sub_variant_get_data(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &AttrValueJs::sub_variant_get_data); }
  Napi::Value sub_variant_get_kind(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &AttrValueJs::sub_variant_get_kind); }
};

struct HashTagFlatJs : public Napi::ObjectWrap<HashTagFlatJs> {
  Napi::Value operator==(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &HashTagFlatJs::operator==); }
  Napi::Value operator<(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &HashTagFlatJs::operator<); }
};

struct HashTagTextJs : public Napi::ObjectWrap<HashTagTextJs> {
  Napi::Value operator==(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &HashTagTextJs::operator==); }
  Napi::Value prefixMatch(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &HashTagTextJs::prefixMatch); }
  Napi::Value getFlatHashes(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &HashTagTextJs::getFlatHashes); }
};

struct SubtreePathJs : public Napi::ObjectWrap<SubtreePathJs> {
  Napi::Value operator==(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &SubtreePathJs::operator==); }
};

struct LinkTargetJs : public Napi::ObjectWrap<LinkTargetJs> {
  Napi::Value operator==(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &LinkTargetJs::operator==); }
  Napi::Value isRaw(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &LinkTargetJs::isRaw); }
  Napi::Value getRaw(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &LinkTargetJs::getRaw); }
  Napi::Value getRaw(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &LinkTargetJs::getRaw); }
  Napi::Value isId(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &LinkTargetJs::isId); }
  Napi::Value getId(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &LinkTargetJs::getId); }
  Napi::Value getId(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &LinkTargetJs::getId); }
  Napi::Value isCustomId(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &LinkTargetJs::isCustomId); }
  Napi::Value getCustomId(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &LinkTargetJs::getCustomId); }
  Napi::Value getCustomId(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &LinkTargetJs::getCustomId); }
  Napi::Value isSubtreeTitle(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &LinkTargetJs::isSubtreeTitle); }
  Napi::Value getSubtreeTitle(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &LinkTargetJs::getSubtreeTitle); }
  Napi::Value getSubtreeTitle(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &LinkTargetJs::getSubtreeTitle); }
  Napi::Value isPerson(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &LinkTargetJs::isPerson); }
  Napi::Value getPerson(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &LinkTargetJs::getPerson); }
  Napi::Value getPerson(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &LinkTargetJs::getPerson); }
  Napi::Value isUserProtocol(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &LinkTargetJs::isUserProtocol); }
  Napi::Value getUserProtocol(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &LinkTargetJs::getUserProtocol); }
  Napi::Value getUserProtocol(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &LinkTargetJs::getUserProtocol); }
  Napi::Value isInternal(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &LinkTargetJs::isInternal); }
  Napi::Value getInternal(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &LinkTargetJs::getInternal); }
  Napi::Value getInternal(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &LinkTargetJs::getInternal); }
  Napi::Value isFootnote(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &LinkTargetJs::isFootnote); }
  Napi::Value getFootnote(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &LinkTargetJs::getFootnote); }
  Napi::Value getFootnote(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &LinkTargetJs::getFootnote); }
  Napi::Value isFile(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &LinkTargetJs::isFile); }
  Napi::Value getFile(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &LinkTargetJs::getFile); }
  Napi::Value getFile(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &LinkTargetJs::getFile); }
  Napi::Value isAttachment(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &LinkTargetJs::isAttachment); }
  Napi::Value getAttachment(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &LinkTargetJs::getAttachment); }
  Napi::Value getAttachment(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &LinkTargetJs::getAttachment); }
  Napi::Value getKind(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &LinkTargetJs::getKind); }
  Napi::Value getKind(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &LinkTargetJs::getKind); }
  Napi::Value sub_variant_get_name(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &LinkTargetJs::sub_variant_get_name); }
  Napi::Value sub_variant_get_data(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &LinkTargetJs::sub_variant_get_data); }
  Napi::Value sub_variant_get_kind(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &LinkTargetJs::sub_variant_get_kind); }
};

struct SubtreeLogHeadJs : public Napi::ObjectWrap<SubtreeLogHeadJs> {
  Napi::Value operator==(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &SubtreeLogHeadJs::operator==); }
  Napi::Value isPriority(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &SubtreeLogHeadJs::isPriority); }
  Napi::Value getPriority(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &SubtreeLogHeadJs::getPriority); }
  Napi::Value getPriority(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &SubtreeLogHeadJs::getPriority); }
  Napi::Value isNote(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &SubtreeLogHeadJs::isNote); }
  Napi::Value getNote(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &SubtreeLogHeadJs::getNote); }
  Napi::Value getNote(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &SubtreeLogHeadJs::getNote); }
  Napi::Value isRefile(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &SubtreeLogHeadJs::isRefile); }
  Napi::Value getRefile(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &SubtreeLogHeadJs::getRefile); }
  Napi::Value getRefile(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &SubtreeLogHeadJs::getRefile); }
  Napi::Value isClock(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &SubtreeLogHeadJs::isClock); }
  Napi::Value getClock(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &SubtreeLogHeadJs::getClock); }
  Napi::Value getClock(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &SubtreeLogHeadJs::getClock); }
  Napi::Value isState(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &SubtreeLogHeadJs::isState); }
  Napi::Value getState(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &SubtreeLogHeadJs::getState); }
  Napi::Value getState(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &SubtreeLogHeadJs::getState); }
  Napi::Value isDeadline(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &SubtreeLogHeadJs::isDeadline); }
  Napi::Value getDeadline(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &SubtreeLogHeadJs::getDeadline); }
  Napi::Value getDeadline(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &SubtreeLogHeadJs::getDeadline); }
  Napi::Value isSchedule(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &SubtreeLogHeadJs::isSchedule); }
  Napi::Value getSchedule(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &SubtreeLogHeadJs::getSchedule); }
  Napi::Value getSchedule(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &SubtreeLogHeadJs::getSchedule); }
  Napi::Value isTag(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &SubtreeLogHeadJs::isTag); }
  Napi::Value getTag(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &SubtreeLogHeadJs::getTag); }
  Napi::Value getTag(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &SubtreeLogHeadJs::getTag); }
  Napi::Value isUnknown(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &SubtreeLogHeadJs::isUnknown); }
  Napi::Value getUnknown(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &SubtreeLogHeadJs::getUnknown); }
  Napi::Value getUnknown(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &SubtreeLogHeadJs::getUnknown); }
  Napi::Value getLogKind(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &SubtreeLogHeadJs::getLogKind); }
  Napi::Value getLogKind(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &SubtreeLogHeadJs::getLogKind); }
  Napi::Value sub_variant_get_name(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &SubtreeLogHeadJs::sub_variant_get_name); }
  Napi::Value sub_variant_get_data(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &SubtreeLogHeadJs::sub_variant_get_data); }
  Napi::Value sub_variant_get_kind(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &SubtreeLogHeadJs::sub_variant_get_kind); }
};

struct SubtreeCompletionJs : public Napi::ObjectWrap<SubtreeCompletionJs> {
  Napi::Value operator==(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &SubtreeCompletionJs::operator==); }
};

struct AttrListJs : public Napi::ObjectWrap<AttrListJs> {
  Napi::Value operator==(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &AttrListJs::operator==); }
};

struct AttrGroupJs : public Napi::ObjectWrap<AttrGroupJs> {
  Napi::Value getFlatArgs(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &AttrGroupJs::getFlatArgs); }
  Napi::Value getAttrs(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &AttrGroupJs::getAttrs); }
  Napi::Value setNamedAttr(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &AttrGroupJs::setNamedAttr); }
  Napi::Value setPositionalAttr(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &AttrGroupJs::setPositionalAttr); }
  Napi::Value getPositionalSize(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &AttrGroupJs::getPositionalSize); }
  Napi::Value getNamedSize(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &AttrGroupJs::getNamedSize); }
  Napi::Value isEmpty(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &AttrGroupJs::isEmpty); }
  Napi::Value getAll(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &AttrGroupJs::getAll); }
  Napi::Value atPositional(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &AttrGroupJs::atPositional); }
  Napi::Value getPositional(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &AttrGroupJs::getPositional); }
  Napi::Value atNamed(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &AttrGroupJs::atNamed); }
  Napi::Value getNamed(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &AttrGroupJs::getNamed); }
  Napi::Value atFirstNamed(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &AttrGroupJs::atFirstNamed); }
  Napi::Value getFirstNamed(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &AttrGroupJs::getFirstNamed); }
  Napi::Value atVarNamed(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &AttrGroupJs::atVarNamed); }
  Napi::Value getVarNamed(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &AttrGroupJs::getVarNamed); }
  Napi::Value atFirstVarNamed(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &AttrGroupJs::atFirstVarNamed); }
  Napi::Value getFirstVarNamed(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &AttrGroupJs::getFirstVarNamed); }
  Napi::Value operator==(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &AttrGroupJs::operator==); }
};

struct OrgCodeEvalInputJs : public Napi::ObjectWrap<OrgCodeEvalInputJs> {
  Napi::Value operator==(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &OrgCodeEvalInputJs::operator==); }
};

struct OrgCodeEvalOutputJs : public Napi::ObjectWrap<OrgCodeEvalOutputJs> {
  Napi::Value operator==(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &OrgCodeEvalOutputJs::operator==); }
};

struct ColumnViewJs : public Napi::ObjectWrap<ColumnViewJs> {
  Napi::Value operator==(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ColumnViewJs::operator==); }
};

struct BlockCodeLineJs : public Napi::ObjectWrap<BlockCodeLineJs> {
  Napi::Value operator==(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &BlockCodeLineJs::operator==); }
};

struct DocumentExportConfigJs : public Napi::ObjectWrap<DocumentExportConfigJs> {
  Napi::Value operator==(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &DocumentExportConfigJs::operator==); }
  Napi::Value isDoExport(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &DocumentExportConfigJs::isDoExport); }
  Napi::Value getDoExport(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &DocumentExportConfigJs::getDoExport); }
  Napi::Value getDoExport(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &DocumentExportConfigJs::getDoExport); }
  Napi::Value isExportFixed(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &DocumentExportConfigJs::isExportFixed); }
  Napi::Value getExportFixed(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &DocumentExportConfigJs::getExportFixed); }
  Napi::Value getExportFixed(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &DocumentExportConfigJs::getExportFixed); }
  Napi::Value getTocExportKind(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &DocumentExportConfigJs::getTocExportKind); }
  Napi::Value getTocExportKind(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &DocumentExportConfigJs::getTocExportKind); }
  Napi::Value sub_variant_get_name(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &DocumentExportConfigJs::sub_variant_get_name); }
  Napi::Value sub_variant_get_data(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &DocumentExportConfigJs::sub_variant_get_data); }
  Napi::Value sub_variant_get_kind(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &DocumentExportConfigJs::sub_variant_get_kind); }
};

struct SubtreePeriodJs : public Napi::ObjectWrap<SubtreePeriodJs> {
  Napi::Value operator==(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &SubtreePeriodJs::operator==); }
};

struct NamedPropertyJs : public Napi::ObjectWrap<NamedPropertyJs> {
  Napi::Value isMatching(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &NamedPropertyJs::isMatching); }
  Napi::Value getName(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &NamedPropertyJs::getName); }
  Napi::Value getSubKind(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &NamedPropertyJs::getSubKind); }
  Napi::Value operator==(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &NamedPropertyJs::operator==); }
  Napi::Value isNonblocking(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &NamedPropertyJs::isNonblocking); }
  Napi::Value getNonblocking(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &NamedPropertyJs::getNonblocking); }
  Napi::Value getNonblocking(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &NamedPropertyJs::getNonblocking); }
  Napi::Value isArchiveTime(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &NamedPropertyJs::isArchiveTime); }
  Napi::Value getArchiveTime(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &NamedPropertyJs::getArchiveTime); }
  Napi::Value getArchiveTime(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &NamedPropertyJs::getArchiveTime); }
  Napi::Value isArchiveFile(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &NamedPropertyJs::isArchiveFile); }
  Napi::Value getArchiveFile(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &NamedPropertyJs::getArchiveFile); }
  Napi::Value getArchiveFile(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &NamedPropertyJs::getArchiveFile); }
  Napi::Value isArchiveOlpath(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &NamedPropertyJs::isArchiveOlpath); }
  Napi::Value getArchiveOlpath(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &NamedPropertyJs::getArchiveOlpath); }
  Napi::Value getArchiveOlpath(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &NamedPropertyJs::getArchiveOlpath); }
  Napi::Value isArchiveTarget(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &NamedPropertyJs::isArchiveTarget); }
  Napi::Value getArchiveTarget(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &NamedPropertyJs::getArchiveTarget); }
  Napi::Value getArchiveTarget(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &NamedPropertyJs::getArchiveTarget); }
  Napi::Value isArchiveCategory(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &NamedPropertyJs::isArchiveCategory); }
  Napi::Value getArchiveCategory(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &NamedPropertyJs::getArchiveCategory); }
  Napi::Value getArchiveCategory(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &NamedPropertyJs::getArchiveCategory); }
  Napi::Value isArchiveTodo(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &NamedPropertyJs::isArchiveTodo); }
  Napi::Value getArchiveTodo(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &NamedPropertyJs::getArchiveTodo); }
  Napi::Value getArchiveTodo(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &NamedPropertyJs::getArchiveTodo); }
  Napi::Value isTrigger(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &NamedPropertyJs::isTrigger); }
  Napi::Value getTrigger(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &NamedPropertyJs::getTrigger); }
  Napi::Value getTrigger(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &NamedPropertyJs::getTrigger); }
  Napi::Value isExportLatexClass(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &NamedPropertyJs::isExportLatexClass); }
  Napi::Value getExportLatexClass(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &NamedPropertyJs::getExportLatexClass); }
  Napi::Value getExportLatexClass(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &NamedPropertyJs::getExportLatexClass); }
  Napi::Value isCookieData(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &NamedPropertyJs::isCookieData); }
  Napi::Value getCookieData(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &NamedPropertyJs::getCookieData); }
  Napi::Value getCookieData(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &NamedPropertyJs::getCookieData); }
  Napi::Value isExportLatexClassOptions(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &NamedPropertyJs::isExportLatexClassOptions); }
  Napi::Value getExportLatexClassOptions(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &NamedPropertyJs::getExportLatexClassOptions); }
  Napi::Value getExportLatexClassOptions(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &NamedPropertyJs::getExportLatexClassOptions); }
  Napi::Value isExportLatexHeader(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &NamedPropertyJs::isExportLatexHeader); }
  Napi::Value getExportLatexHeader(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &NamedPropertyJs::getExportLatexHeader); }
  Napi::Value getExportLatexHeader(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &NamedPropertyJs::getExportLatexHeader); }
  Napi::Value isExportLatexCompiler(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &NamedPropertyJs::isExportLatexCompiler); }
  Napi::Value getExportLatexCompiler(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &NamedPropertyJs::getExportLatexCompiler); }
  Napi::Value getExportLatexCompiler(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &NamedPropertyJs::getExportLatexCompiler); }
  Napi::Value isOrdered(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &NamedPropertyJs::isOrdered); }
  Napi::Value getOrdered(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &NamedPropertyJs::getOrdered); }
  Napi::Value getOrdered(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &NamedPropertyJs::getOrdered); }
  Napi::Value isEffort(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &NamedPropertyJs::isEffort); }
  Napi::Value getEffort(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &NamedPropertyJs::getEffort); }
  Napi::Value getEffort(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &NamedPropertyJs::getEffort); }
  Napi::Value isVisibility(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &NamedPropertyJs::isVisibility); }
  Napi::Value getVisibility(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &NamedPropertyJs::getVisibility); }
  Napi::Value getVisibility(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &NamedPropertyJs::getVisibility); }
  Napi::Value isExportOptions(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &NamedPropertyJs::isExportOptions); }
  Napi::Value getExportOptions(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &NamedPropertyJs::getExportOptions); }
  Napi::Value getExportOptions(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &NamedPropertyJs::getExportOptions); }
  Napi::Value isBlocker(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &NamedPropertyJs::isBlocker); }
  Napi::Value getBlocker(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &NamedPropertyJs::getBlocker); }
  Napi::Value getBlocker(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &NamedPropertyJs::getBlocker); }
  Napi::Value isUnnumbered(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &NamedPropertyJs::isUnnumbered); }
  Napi::Value getUnnumbered(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &NamedPropertyJs::getUnnumbered); }
  Napi::Value getUnnumbered(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &NamedPropertyJs::getUnnumbered); }
  Napi::Value isCreated(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &NamedPropertyJs::isCreated); }
  Napi::Value getCreated(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &NamedPropertyJs::getCreated); }
  Napi::Value getCreated(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &NamedPropertyJs::getCreated); }
  Napi::Value isRadioId(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &NamedPropertyJs::isRadioId); }
  Napi::Value getRadioId(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &NamedPropertyJs::getRadioId); }
  Napi::Value getRadioId(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &NamedPropertyJs::getRadioId); }
  Napi::Value isHashtagDef(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &NamedPropertyJs::isHashtagDef); }
  Napi::Value getHashtagDef(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &NamedPropertyJs::getHashtagDef); }
  Napi::Value getHashtagDef(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &NamedPropertyJs::getHashtagDef); }
  Napi::Value isCustomArgs(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &NamedPropertyJs::isCustomArgs); }
  Napi::Value getCustomArgs(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &NamedPropertyJs::getCustomArgs); }
  Napi::Value getCustomArgs(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &NamedPropertyJs::getCustomArgs); }
  Napi::Value isCustomRaw(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &NamedPropertyJs::isCustomRaw); }
  Napi::Value getCustomRaw(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &NamedPropertyJs::getCustomRaw); }
  Napi::Value getCustomRaw(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &NamedPropertyJs::getCustomRaw); }
  Napi::Value isCustomSubtreeJson(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &NamedPropertyJs::isCustomSubtreeJson); }
  Napi::Value getCustomSubtreeJson(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &NamedPropertyJs::getCustomSubtreeJson); }
  Napi::Value getCustomSubtreeJson(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &NamedPropertyJs::getCustomSubtreeJson); }
  Napi::Value isCustomSubtreeFlags(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &NamedPropertyJs::isCustomSubtreeFlags); }
  Napi::Value getCustomSubtreeFlags(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &NamedPropertyJs::getCustomSubtreeFlags); }
  Napi::Value getCustomSubtreeFlags(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &NamedPropertyJs::getCustomSubtreeFlags); }
  Napi::Value getKind(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &NamedPropertyJs::getKind); }
  Napi::Value getKind(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &NamedPropertyJs::getKind); }
  Napi::Value sub_variant_get_name(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &NamedPropertyJs::sub_variant_get_name); }
  Napi::Value sub_variant_get_data(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &NamedPropertyJs::sub_variant_get_data); }
  Napi::Value sub_variant_get_kind(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &NamedPropertyJs::sub_variant_get_kind); }
};

struct NoneJs : public Napi::ObjectWrap<NoneJs> {
  Napi::Value getKind(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &NoneJs::getKind); }
};

struct ErrorItemJs : public Napi::ObjectWrap<ErrorItemJs> {
  Napi::Value getKind(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ErrorItemJs::getKind); }
};

struct ErrorGroupJs : public Napi::ObjectWrap<ErrorGroupJs> {
  Napi::Value getKind(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ErrorGroupJs::getKind); }
};

struct StmtJs : public Napi::ObjectWrap<StmtJs> {
  Napi::Value getAttached(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &StmtJs::getAttached); }
  Napi::Value getCaption(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &StmtJs::getCaption); }
  Napi::Value getName(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &StmtJs::getName); }
  Napi::Value getAttrs(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &StmtJs::getAttrs); }
  Napi::Value getFirstAttr(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &StmtJs::getFirstAttr); }
};

struct InlineJs : public Napi::ObjectWrap<InlineJs> {};

struct StmtListJs : public Napi::ObjectWrap<StmtListJs> {
  Napi::Value getKind(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &StmtListJs::getKind); }
};

struct EmptyJs : public Napi::ObjectWrap<EmptyJs> {
  Napi::Value getKind(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &EmptyJs::getKind); }
};

struct LeafJs : public Napi::ObjectWrap<LeafJs> {
  Napi::Value getText(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &LeafJs::getText); }
};

struct TimeJs : public Napi::ObjectWrap<TimeJs> {
  Napi::Value getKind(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &TimeJs::getKind); }
  Napi::Value getYear(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &TimeJs::getYear); }
  Napi::Value getMonth(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &TimeJs::getMonth); }
  Napi::Value getDay(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &TimeJs::getDay); }
  Napi::Value getHour(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &TimeJs::getHour); }
  Napi::Value getMinute(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &TimeJs::getMinute); }
  Napi::Value getSecond(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &TimeJs::getSecond); }
  Napi::Value getStaticTime(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &TimeJs::getStaticTime); }
  Napi::Value isStatic(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &TimeJs::isStatic); }
  Napi::Value getStatic(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &TimeJs::getStatic); }
  Napi::Value getStatic(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &TimeJs::getStatic); }
  Napi::Value isDynamic(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &TimeJs::isDynamic); }
  Napi::Value getDynamic(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &TimeJs::getDynamic); }
  Napi::Value getDynamic(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &TimeJs::getDynamic); }
  Napi::Value getTimeKind(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &TimeJs::getTimeKind); }
  Napi::Value getTimeKind(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &TimeJs::getTimeKind); }
  Napi::Value sub_variant_get_name(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &TimeJs::sub_variant_get_name); }
  Napi::Value sub_variant_get_data(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &TimeJs::sub_variant_get_data); }
  Napi::Value sub_variant_get_kind(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &TimeJs::sub_variant_get_kind); }
};

struct TimeRangeJs : public Napi::ObjectWrap<TimeRangeJs> {
  Napi::Value getKind(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &TimeRangeJs::getKind); }
};

struct MacroJs : public Napi::ObjectWrap<MacroJs> {
  Napi::Value getKind(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &MacroJs::getKind); }
};

struct SymbolJs : public Napi::ObjectWrap<SymbolJs> {
  Napi::Value getKind(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &SymbolJs::getKind); }
};

struct MarkupJs : public Napi::ObjectWrap<MarkupJs> {};

struct RadioTargetJs : public Napi::ObjectWrap<RadioTargetJs> {
  Napi::Value getKind(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &RadioTargetJs::getKind); }
};

struct LatexJs : public Napi::ObjectWrap<LatexJs> {
  Napi::Value getKind(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &LatexJs::getKind); }
};

struct SubtreeLogJs : public Napi::ObjectWrap<SubtreeLogJs> {
  Napi::Value getKind(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &SubtreeLogJs::getKind); }
  Napi::Value setDescription(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &SubtreeLogJs::setDescription); }
};

struct SubtreeJs : public Napi::ObjectWrap<SubtreeJs> {
  Napi::Value getKind(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &SubtreeJs::getKind); }
  Napi::Value getTimePeriods(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &SubtreeJs::getTimePeriods); }
  Napi::Value getProperties(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &SubtreeJs::getProperties); }
  Napi::Value getProperty(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &SubtreeJs::getProperty); }
  Napi::Value removeProperty(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &SubtreeJs::removeProperty); }
  Napi::Value setProperty(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &SubtreeJs::setProperty); }
  Napi::Value setPropertyStrValue(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &SubtreeJs::setPropertyStrValue); }
  Napi::Value getCleanTitle(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &SubtreeJs::getCleanTitle); }
};

struct ColonExampleJs : public Napi::ObjectWrap<ColonExampleJs> {
  Napi::Value getKind(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ColonExampleJs::getKind); }
};

struct CallJs : public Napi::ObjectWrap<CallJs> {
  Napi::Value getKind(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &CallJs::getKind); }
};

struct ListItemJs : public Napi::ObjectWrap<ListItemJs> {
  Napi::Value getKind(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ListItemJs::getKind); }
  Napi::Value isDescriptionItem(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ListItemJs::isDescriptionItem); }
  Napi::Value getCleanHeader(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ListItemJs::getCleanHeader); }
};

struct DocumentOptionsJs : public Napi::ObjectWrap<DocumentOptionsJs> {
  Napi::Value getKind(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &DocumentOptionsJs::getKind); }
  Napi::Value getProperties(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &DocumentOptionsJs::getProperties); }
  Napi::Value getProperty(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &DocumentOptionsJs::getProperty); }
};

struct DocumentFragmentJs : public Napi::ObjectWrap<DocumentFragmentJs> {
  Napi::Value getKind(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &DocumentFragmentJs::getKind); }
};

struct CriticMarkupJs : public Napi::ObjectWrap<CriticMarkupJs> {
  Napi::Value getKind(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &CriticMarkupJs::getKind); }
};

struct DocumentJs : public Napi::ObjectWrap<DocumentJs> {
  Napi::Value getKind(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &DocumentJs::getKind); }
  Napi::Value getProperties(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &DocumentJs::getProperties); }
  Napi::Value getProperty(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &DocumentJs::getProperty); }
};

struct FileTargetJs : public Napi::ObjectWrap<FileTargetJs> {
  Napi::Value getKind(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &FileTargetJs::getKind); }
};

struct TextSeparatorJs : public Napi::ObjectWrap<TextSeparatorJs> {
  Napi::Value getKind(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &TextSeparatorJs::getKind); }
};

struct DocumentGroupJs : public Napi::ObjectWrap<DocumentGroupJs> {
  Napi::Value getKind(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &DocumentGroupJs::getKind); }
};

struct FileJs : public Napi::ObjectWrap<FileJs> {
  Napi::Value getKind(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &FileJs::getKind); }
  Napi::Value isDocument(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &FileJs::isDocument); }
  Napi::Value getDocument(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &FileJs::getDocument); }
  Napi::Value getDocument(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &FileJs::getDocument); }
  Napi::Value isAttachment(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &FileJs::isAttachment); }
  Napi::Value getAttachment(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &FileJs::getAttachment); }
  Napi::Value getAttachment(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &FileJs::getAttachment); }
  Napi::Value isSource(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &FileJs::isSource); }
  Napi::Value getSource(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &FileJs::getSource); }
  Napi::Value getSource(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &FileJs::getSource); }
  Napi::Value getFileKind(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &FileJs::getFileKind); }
  Napi::Value getFileKind(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &FileJs::getFileKind); }
  Napi::Value sub_variant_get_name(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &FileJs::sub_variant_get_name); }
  Napi::Value sub_variant_get_data(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &FileJs::sub_variant_get_data); }
  Napi::Value sub_variant_get_kind(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &FileJs::sub_variant_get_kind); }
};

struct DirectoryJs : public Napi::ObjectWrap<DirectoryJs> {
  Napi::Value getKind(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &DirectoryJs::getKind); }
};

struct SymlinkJs : public Napi::ObjectWrap<SymlinkJs> {
  Napi::Value getKind(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &SymlinkJs::getKind); }
};

struct CmdIncludeJs : public Napi::ObjectWrap<CmdIncludeJs> {
  Napi::Value getKind(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &CmdIncludeJs::getKind); }
  Napi::Value isExample(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &CmdIncludeJs::isExample); }
  Napi::Value getExample(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &CmdIncludeJs::getExample); }
  Napi::Value getExample(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &CmdIncludeJs::getExample); }
  Napi::Value isExport(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &CmdIncludeJs::isExport); }
  Napi::Value getExport(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &CmdIncludeJs::getExport); }
  Napi::Value getExport(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &CmdIncludeJs::getExport); }
  Napi::Value isCustom(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &CmdIncludeJs::isCustom); }
  Napi::Value getCustom(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &CmdIncludeJs::getCustom); }
  Napi::Value getCustom(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &CmdIncludeJs::getCustom); }
  Napi::Value isSrc(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &CmdIncludeJs::isSrc); }
  Napi::Value getSrc(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &CmdIncludeJs::getSrc); }
  Napi::Value getSrc(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &CmdIncludeJs::getSrc); }
  Napi::Value isOrgDocument(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &CmdIncludeJs::isOrgDocument); }
  Napi::Value getOrgDocument(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &CmdIncludeJs::getOrgDocument); }
  Napi::Value getOrgDocument(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &CmdIncludeJs::getOrgDocument); }
  Napi::Value getIncludeKind(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &CmdIncludeJs::getIncludeKind); }
  Napi::Value getIncludeKind(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &CmdIncludeJs::getIncludeKind); }
  Napi::Value sub_variant_get_name(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &CmdIncludeJs::sub_variant_get_name); }
  Napi::Value sub_variant_get_data(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &CmdIncludeJs::sub_variant_get_data); }
  Napi::Value sub_variant_get_kind(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &CmdIncludeJs::sub_variant_get_kind); }
};

struct MapConfigJs : public Napi::ObjectWrap<MapConfigJs> {};

struct ImmIdTNone : public Napi::ObjectWrap<ImmIdTNone> {};

struct ImmIdTErrorItem : public Napi::ObjectWrap<ImmIdTErrorItem> {};

struct ImmIdTErrorGroup : public Napi::ObjectWrap<ImmIdTErrorGroup> {};

struct ImmIdTStmt : public Napi::ObjectWrap<ImmIdTStmt> {};

struct ImmIdTInline : public Napi::ObjectWrap<ImmIdTInline> {};

struct ImmIdTStmtList : public Napi::ObjectWrap<ImmIdTStmtList> {};

struct ImmIdTEmpty : public Napi::ObjectWrap<ImmIdTEmpty> {};

struct ImmIdTCmd : public Napi::ObjectWrap<ImmIdTCmd> {};

struct ImmIdTBlock : public Napi::ObjectWrap<ImmIdTBlock> {};

struct ImmIdTLineCommand : public Napi::ObjectWrap<ImmIdTLineCommand> {};

struct ImmIdTAttached : public Napi::ObjectWrap<ImmIdTAttached> {};

struct ImmIdTLeaf : public Napi::ObjectWrap<ImmIdTLeaf> {};

struct ImmIdTCmdCaption : public Napi::ObjectWrap<ImmIdTCmdCaption> {};

struct ImmIdTCmdColumns : public Napi::ObjectWrap<ImmIdTCmdColumns> {};

struct ImmIdTCmdName : public Napi::ObjectWrap<ImmIdTCmdName> {};

struct ImmIdTCmdCustomArgs : public Napi::ObjectWrap<ImmIdTCmdCustomArgs> {};

struct ImmIdTCmdCustomRaw : public Napi::ObjectWrap<ImmIdTCmdCustomRaw> {};

struct ImmIdTCmdCustomText : public Napi::ObjectWrap<ImmIdTCmdCustomText> {};

struct ImmIdTCmdCall : public Napi::ObjectWrap<ImmIdTCmdCall> {};

struct ImmIdTCmdTblfm : public Napi::ObjectWrap<ImmIdTCmdTblfm> {};

struct ImmIdTHashTag : public Napi::ObjectWrap<ImmIdTHashTag> {};

struct ImmIdTInlineFootnote : public Napi::ObjectWrap<ImmIdTInlineFootnote> {};

struct ImmIdTInlineExport : public Napi::ObjectWrap<ImmIdTInlineExport> {};

struct ImmIdTTime : public Napi::ObjectWrap<ImmIdTTime> {};

struct ImmIdTTimeRange : public Napi::ObjectWrap<ImmIdTTimeRange> {};

struct ImmIdTMacro : public Napi::ObjectWrap<ImmIdTMacro> {};

struct ImmIdTSymbol : public Napi::ObjectWrap<ImmIdTSymbol> {};

struct ImmIdTEscaped : public Napi::ObjectWrap<ImmIdTEscaped> {};

struct ImmIdTNewline : public Napi::ObjectWrap<ImmIdTNewline> {};

struct ImmIdTSpace : public Napi::ObjectWrap<ImmIdTSpace> {};

struct ImmIdTWord : public Napi::ObjectWrap<ImmIdTWord> {};

struct ImmIdTAtMention : public Napi::ObjectWrap<ImmIdTAtMention> {};

struct ImmIdTRawText : public Napi::ObjectWrap<ImmIdTRawText> {};

struct ImmIdTPunctuation : public Napi::ObjectWrap<ImmIdTPunctuation> {};

struct ImmIdTPlaceholder : public Napi::ObjectWrap<ImmIdTPlaceholder> {};

struct ImmIdTBigIdent : public Napi::ObjectWrap<ImmIdTBigIdent> {};

struct ImmIdTTextTarget : public Napi::ObjectWrap<ImmIdTTextTarget> {};

struct ImmIdTMarkup : public Napi::ObjectWrap<ImmIdTMarkup> {};

struct ImmIdTBold : public Napi::ObjectWrap<ImmIdTBold> {};

struct ImmIdTUnderline : public Napi::ObjectWrap<ImmIdTUnderline> {};

struct ImmIdTMonospace : public Napi::ObjectWrap<ImmIdTMonospace> {};

struct ImmIdTMarkQuote : public Napi::ObjectWrap<ImmIdTMarkQuote> {};

struct ImmIdTVerbatim : public Napi::ObjectWrap<ImmIdTVerbatim> {};

struct ImmIdTItalic : public Napi::ObjectWrap<ImmIdTItalic> {};

struct ImmIdTStrike : public Napi::ObjectWrap<ImmIdTStrike> {};

struct ImmIdTPar : public Napi::ObjectWrap<ImmIdTPar> {};

struct ImmIdTRadioTarget : public Napi::ObjectWrap<ImmIdTRadioTarget> {};

struct ImmIdTLatex : public Napi::ObjectWrap<ImmIdTLatex> {};

struct ImmIdTLink : public Napi::ObjectWrap<ImmIdTLink> {};

struct ImmIdTBlockCenter : public Napi::ObjectWrap<ImmIdTBlockCenter> {};

struct ImmIdTBlockQuote : public Napi::ObjectWrap<ImmIdTBlockQuote> {};

struct ImmIdTBlockComment : public Napi::ObjectWrap<ImmIdTBlockComment> {};

struct ImmIdTBlockVerse : public Napi::ObjectWrap<ImmIdTBlockVerse> {};

struct ImmIdTBlockDynamicFallback : public Napi::ObjectWrap<ImmIdTBlockDynamicFallback> {};

struct ImmIdTBlockExample : public Napi::ObjectWrap<ImmIdTBlockExample> {};

struct ImmIdTBlockExport : public Napi::ObjectWrap<ImmIdTBlockExport> {};

struct ImmIdTBlockAdmonition : public Napi::ObjectWrap<ImmIdTBlockAdmonition> {};

struct ImmIdTBlockCodeEvalResult : public Napi::ObjectWrap<ImmIdTBlockCodeEvalResult> {};

struct ImmIdTBlockCode : public Napi::ObjectWrap<ImmIdTBlockCode> {};

struct ImmIdTSubtreeLog : public Napi::ObjectWrap<ImmIdTSubtreeLog> {};

struct ImmIdTSubtree : public Napi::ObjectWrap<ImmIdTSubtree> {};

struct ImmIdTCell : public Napi::ObjectWrap<ImmIdTCell> {};

struct ImmIdTRow : public Napi::ObjectWrap<ImmIdTRow> {};

struct ImmIdTTable : public Napi::ObjectWrap<ImmIdTTable> {};

struct ImmIdTParagraph : public Napi::ObjectWrap<ImmIdTParagraph> {};

struct ImmIdTColonExample : public Napi::ObjectWrap<ImmIdTColonExample> {};

struct ImmIdTCmdAttr : public Napi::ObjectWrap<ImmIdTCmdAttr> {};

struct ImmIdTCmdExport : public Napi::ObjectWrap<ImmIdTCmdExport> {};

struct ImmIdTCall : public Napi::ObjectWrap<ImmIdTCall> {};

struct ImmIdTList : public Napi::ObjectWrap<ImmIdTList> {};

struct ImmIdTListItem : public Napi::ObjectWrap<ImmIdTListItem> {};

struct ImmIdTDocumentOptions : public Napi::ObjectWrap<ImmIdTDocumentOptions> {};

struct ImmIdTDocumentFragment : public Napi::ObjectWrap<ImmIdTDocumentFragment> {};

struct ImmIdTCriticMarkup : public Napi::ObjectWrap<ImmIdTCriticMarkup> {};

struct ImmIdTDocument : public Napi::ObjectWrap<ImmIdTDocument> {};

struct ImmIdTFileTarget : public Napi::ObjectWrap<ImmIdTFileTarget> {};

struct ImmIdTTextSeparator : public Napi::ObjectWrap<ImmIdTTextSeparator> {};

struct ImmIdTDocumentGroup : public Napi::ObjectWrap<ImmIdTDocumentGroup> {};

struct ImmIdTFile : public Napi::ObjectWrap<ImmIdTFile> {};

struct ImmIdTDirectory : public Napi::ObjectWrap<ImmIdTDirectory> {};

struct ImmIdTSymlink : public Napi::ObjectWrap<ImmIdTSymlink> {};

struct ImmIdTCmdInclude : public Napi::ObjectWrap<ImmIdTCmdInclude> {};

struct ImmNoneValueJs : public Napi::ObjectWrap<ImmNoneValueJs> {};

struct ImmErrorItemValueJs : public Napi::ObjectWrap<ImmErrorItemValueJs> {
  Napi::Value setMessage(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &ImmErrorItemValueJs::setMessage); }
  Napi::Value setFunction(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &ImmErrorItemValueJs::setFunction); }
  Napi::Value setLine(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &ImmErrorItemValueJs::setLine); }
};

struct ImmErrorGroupValueJs : public Napi::ObjectWrap<ImmErrorGroupValueJs> {
  Napi::Value setDiagnostics(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &ImmErrorGroupValueJs::setDiagnostics); }
  Napi::Value setFunction(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &ImmErrorGroupValueJs::setFunction); }
  Napi::Value setLine(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &ImmErrorGroupValueJs::setLine); }
};

struct ImmStmtListValueJs : public Napi::ObjectWrap<ImmStmtListValueJs> {};

struct ImmEmptyValueJs : public Napi::ObjectWrap<ImmEmptyValueJs> {};

struct ImmCmdCaptionValueJs : public Napi::ObjectWrap<ImmCmdCaptionValueJs> {
  Napi::Value setText(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &ImmCmdCaptionValueJs::setText); }
};

struct ImmCmdColumnsValueJs : public Napi::ObjectWrap<ImmCmdColumnsValueJs> {
  Napi::Value setView(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &ImmCmdColumnsValueJs::setView); }
};

struct ImmCmdNameValueJs : public Napi::ObjectWrap<ImmCmdNameValueJs> {
  Napi::Value setName(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &ImmCmdNameValueJs::setName); }
};

struct ImmCmdCustomArgsValueJs : public Napi::ObjectWrap<ImmCmdCustomArgsValueJs> {
  Napi::Value setName(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &ImmCmdCustomArgsValueJs::setName); }
  Napi::Value setIsattached(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &ImmCmdCustomArgsValueJs::setIsattached); }
};

struct ImmCmdCustomRawValueJs : public Napi::ObjectWrap<ImmCmdCustomRawValueJs> {
  Napi::Value setName(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &ImmCmdCustomRawValueJs::setName); }
  Napi::Value setIsattached(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &ImmCmdCustomRawValueJs::setIsattached); }
  Napi::Value setText(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &ImmCmdCustomRawValueJs::setText); }
};

struct ImmCmdCustomTextValueJs : public Napi::ObjectWrap<ImmCmdCustomTextValueJs> {
  Napi::Value setName(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &ImmCmdCustomTextValueJs::setName); }
  Napi::Value setIsattached(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &ImmCmdCustomTextValueJs::setIsattached); }
  Napi::Value setText(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &ImmCmdCustomTextValueJs::setText); }
};

struct ImmCmdCallValueJs : public Napi::ObjectWrap<ImmCmdCallValueJs> {
  Napi::Value setName(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &ImmCmdCallValueJs::setName); }
  Napi::Value setFilename(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &ImmCmdCallValueJs::setFilename); }
  Napi::Value setInsideheaderattrs(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &ImmCmdCallValueJs::setInsideheaderattrs); }
  Napi::Value setCallattrs(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &ImmCmdCallValueJs::setCallattrs); }
  Napi::Value setEndheaderattrs(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &ImmCmdCallValueJs::setEndheaderattrs); }
  Napi::Value setResult(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &ImmCmdCallValueJs::setResult); }
};

struct ImmCmdTblfmValueJs : public Napi::ObjectWrap<ImmCmdTblfmValueJs> {
  Napi::Value setExpr(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &ImmCmdTblfmValueJs::setExpr); }
};

struct ImmHashTagValueJs : public Napi::ObjectWrap<ImmHashTagValueJs> {
  Napi::Value setText(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &ImmHashTagValueJs::setText); }
};

struct ImmInlineFootnoteValueJs : public Napi::ObjectWrap<ImmInlineFootnoteValueJs> {
  Napi::Value setTag(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &ImmInlineFootnoteValueJs::setTag); }
  Napi::Value setDefinition(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &ImmInlineFootnoteValueJs::setDefinition); }
};

struct ImmInlineExportValueJs : public Napi::ObjectWrap<ImmInlineExportValueJs> {
  Napi::Value setExporter(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &ImmInlineExportValueJs::setExporter); }
  Napi::Value setContent(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &ImmInlineExportValueJs::setContent); }
};

struct ImmTimeValueJs : public Napi::ObjectWrap<ImmTimeValueJs> {
  Napi::Value setIsactive(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &ImmTimeValueJs::setIsactive); }
  Napi::Value setTime(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &ImmTimeValueJs::setTime); }
};

struct ImmTimeRangeValueJs : public Napi::ObjectWrap<ImmTimeRangeValueJs> {
  Napi::Value setFrom(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &ImmTimeRangeValueJs::setFrom); }
  Napi::Value setTo(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &ImmTimeRangeValueJs::setTo); }
};

struct ImmMacroValueJs : public Napi::ObjectWrap<ImmMacroValueJs> {
  Napi::Value setName(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &ImmMacroValueJs::setName); }
  Napi::Value setAttrs(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &ImmMacroValueJs::setAttrs); }
};

struct ImmSymbolValueJs : public Napi::ObjectWrap<ImmSymbolValueJs> {
  Napi::Value setName(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &ImmSymbolValueJs::setName); }
  Napi::Value setParameters(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &ImmSymbolValueJs::setParameters); }
  Napi::Value setPositional(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &ImmSymbolValueJs::setPositional); }
};

struct ImmEscapedValueJs : public Napi::ObjectWrap<ImmEscapedValueJs> {};

struct ImmNewlineValueJs : public Napi::ObjectWrap<ImmNewlineValueJs> {};

struct ImmSpaceValueJs : public Napi::ObjectWrap<ImmSpaceValueJs> {};

struct ImmWordValueJs : public Napi::ObjectWrap<ImmWordValueJs> {};

struct ImmAtMentionValueJs : public Napi::ObjectWrap<ImmAtMentionValueJs> {};

struct ImmRawTextValueJs : public Napi::ObjectWrap<ImmRawTextValueJs> {};

struct ImmPunctuationValueJs : public Napi::ObjectWrap<ImmPunctuationValueJs> {};

struct ImmPlaceholderValueJs : public Napi::ObjectWrap<ImmPlaceholderValueJs> {};

struct ImmBigIdentValueJs : public Napi::ObjectWrap<ImmBigIdentValueJs> {};

struct ImmTextTargetValueJs : public Napi::ObjectWrap<ImmTextTargetValueJs> {};

struct ImmBoldValueJs : public Napi::ObjectWrap<ImmBoldValueJs> {};

struct ImmUnderlineValueJs : public Napi::ObjectWrap<ImmUnderlineValueJs> {};

struct ImmMonospaceValueJs : public Napi::ObjectWrap<ImmMonospaceValueJs> {};

struct ImmMarkQuoteValueJs : public Napi::ObjectWrap<ImmMarkQuoteValueJs> {};

struct ImmVerbatimValueJs : public Napi::ObjectWrap<ImmVerbatimValueJs> {};

struct ImmItalicValueJs : public Napi::ObjectWrap<ImmItalicValueJs> {};

struct ImmStrikeValueJs : public Napi::ObjectWrap<ImmStrikeValueJs> {};

struct ImmParValueJs : public Napi::ObjectWrap<ImmParValueJs> {};

struct ImmRadioTargetValueJs : public Napi::ObjectWrap<ImmRadioTargetValueJs> {
  Napi::Value setWords(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &ImmRadioTargetValueJs::setWords); }
};

struct ImmLatexValueJs : public Napi::ObjectWrap<ImmLatexValueJs> {};

struct ImmLinkValueJs : public Napi::ObjectWrap<ImmLinkValueJs> {
  Napi::Value setDescription(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &ImmLinkValueJs::setDescription); }
  Napi::Value setTarget(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &ImmLinkValueJs::setTarget); }
};

struct ImmBlockCenterValueJs : public Napi::ObjectWrap<ImmBlockCenterValueJs> {};

struct ImmBlockQuoteValueJs : public Napi::ObjectWrap<ImmBlockQuoteValueJs> {};

struct ImmBlockCommentValueJs : public Napi::ObjectWrap<ImmBlockCommentValueJs> {};

struct ImmBlockVerseValueJs : public Napi::ObjectWrap<ImmBlockVerseValueJs> {};

struct ImmBlockDynamicFallbackValueJs : public Napi::ObjectWrap<ImmBlockDynamicFallbackValueJs> {
  Napi::Value setName(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &ImmBlockDynamicFallbackValueJs::setName); }
};

struct ImmBlockExampleValueJs : public Napi::ObjectWrap<ImmBlockExampleValueJs> {};

struct ImmBlockExportValueJs : public Napi::ObjectWrap<ImmBlockExportValueJs> {
  Napi::Value setExporter(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &ImmBlockExportValueJs::setExporter); }
  Napi::Value setContent(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &ImmBlockExportValueJs::setContent); }
};

struct ImmBlockAdmonitionValueJs : public Napi::ObjectWrap<ImmBlockAdmonitionValueJs> {};

struct ImmBlockCodeEvalResultValueJs : public Napi::ObjectWrap<ImmBlockCodeEvalResultValueJs> {
  Napi::Value setRaw(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &ImmBlockCodeEvalResultValueJs::setRaw); }
  Napi::Value setNode(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &ImmBlockCodeEvalResultValueJs::setNode); }
};

struct ImmBlockCodeValueJs : public Napi::ObjectWrap<ImmBlockCodeValueJs> {
  Napi::Value setLang(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &ImmBlockCodeValueJs::setLang); }
  Napi::Value setExports(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &ImmBlockCodeValueJs::setExports); }
  Napi::Value setResult(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &ImmBlockCodeValueJs::setResult); }
  Napi::Value setLines(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &ImmBlockCodeValueJs::setLines); }
  Napi::Value setCache(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &ImmBlockCodeValueJs::setCache); }
  Napi::Value setEval(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &ImmBlockCodeValueJs::setEval); }
  Napi::Value setNoweb(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &ImmBlockCodeValueJs::setNoweb); }
  Napi::Value setHlines(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &ImmBlockCodeValueJs::setHlines); }
  Napi::Value setTangle(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &ImmBlockCodeValueJs::setTangle); }
  Napi::Value setSwitches(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &ImmBlockCodeValueJs::setSwitches); }
};

struct ImmSubtreeLogValueJs : public Napi::ObjectWrap<ImmSubtreeLogValueJs> {
  Napi::Value setHead(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &ImmSubtreeLogValueJs::setHead); }
  Napi::Value setDesc(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &ImmSubtreeLogValueJs::setDesc); }
};

struct ImmSubtreeValueJs : public Napi::ObjectWrap<ImmSubtreeValueJs> {
  Napi::Value setLevel(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &ImmSubtreeValueJs::setLevel); }
  Napi::Value setTreeid(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &ImmSubtreeValueJs::setTreeid); }
  Napi::Value setTodo(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &ImmSubtreeValueJs::setTodo); }
  Napi::Value setCompletion(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &ImmSubtreeValueJs::setCompletion); }
  Napi::Value setDescription(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &ImmSubtreeValueJs::setDescription); }
  Napi::Value setTags(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &ImmSubtreeValueJs::setTags); }
  Napi::Value setTitle(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &ImmSubtreeValueJs::setTitle); }
  Napi::Value setLogbook(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &ImmSubtreeValueJs::setLogbook); }
  Napi::Value setProperties(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &ImmSubtreeValueJs::setProperties); }
  Napi::Value setClosed(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &ImmSubtreeValueJs::setClosed); }
  Napi::Value setDeadline(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &ImmSubtreeValueJs::setDeadline); }
  Napi::Value setScheduled(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &ImmSubtreeValueJs::setScheduled); }
  Napi::Value setIscomment(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &ImmSubtreeValueJs::setIscomment); }
  Napi::Value setIsarchived(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &ImmSubtreeValueJs::setIsarchived); }
  Napi::Value setPriority(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &ImmSubtreeValueJs::setPriority); }
};

struct ImmCellValueJs : public Napi::ObjectWrap<ImmCellValueJs> {
  Napi::Value setIsblock(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &ImmCellValueJs::setIsblock); }
};

struct ImmRowValueJs : public Napi::ObjectWrap<ImmRowValueJs> {
  Napi::Value setCells(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &ImmRowValueJs::setCells); }
  Napi::Value setIsblock(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &ImmRowValueJs::setIsblock); }
};

struct ImmTableValueJs : public Napi::ObjectWrap<ImmTableValueJs> {
  Napi::Value setRows(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &ImmTableValueJs::setRows); }
  Napi::Value setIsblock(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &ImmTableValueJs::setIsblock); }
};

struct ImmParagraphValueJs : public Napi::ObjectWrap<ImmParagraphValueJs> {};

struct ImmColonExampleValueJs : public Napi::ObjectWrap<ImmColonExampleValueJs> {};

struct ImmCmdAttrValueJs : public Napi::ObjectWrap<ImmCmdAttrValueJs> {
  Napi::Value setTarget(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &ImmCmdAttrValueJs::setTarget); }
};

struct ImmCmdExportValueJs : public Napi::ObjectWrap<ImmCmdExportValueJs> {
  Napi::Value setExporter(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &ImmCmdExportValueJs::setExporter); }
  Napi::Value setContent(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &ImmCmdExportValueJs::setContent); }
};

struct ImmCallValueJs : public Napi::ObjectWrap<ImmCallValueJs> {
  Napi::Value setName(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &ImmCallValueJs::setName); }
  Napi::Value setAttrs(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &ImmCallValueJs::setAttrs); }
  Napi::Value setIscommand(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &ImmCallValueJs::setIscommand); }
};

struct ImmListValueJs : public Napi::ObjectWrap<ImmListValueJs> {};

struct ImmListItemValueJs : public Napi::ObjectWrap<ImmListItemValueJs> {
  Napi::Value setCheckbox(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &ImmListItemValueJs::setCheckbox); }
  Napi::Value setHeader(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &ImmListItemValueJs::setHeader); }
  Napi::Value setBullet(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &ImmListItemValueJs::setBullet); }
};

struct ImmDocumentOptionsValueJs : public Napi::ObjectWrap<ImmDocumentOptionsValueJs> {
  Napi::Value setInitialvisibility(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &ImmDocumentOptionsValueJs::setInitialvisibility); }
  Napi::Value setProperties(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &ImmDocumentOptionsValueJs::setProperties); }
  Napi::Value setExportconfig(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &ImmDocumentOptionsValueJs::setExportconfig); }
  Napi::Value setFixedwidthsections(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &ImmDocumentOptionsValueJs::setFixedwidthsections); }
  Napi::Value setStartupindented(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &ImmDocumentOptionsValueJs::setStartupindented); }
  Napi::Value setCategory(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &ImmDocumentOptionsValueJs::setCategory); }
  Napi::Value setSetupfile(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &ImmDocumentOptionsValueJs::setSetupfile); }
  Napi::Value setMaxsubtreelevelexport(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &ImmDocumentOptionsValueJs::setMaxsubtreelevelexport); }
  Napi::Value setColumns(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &ImmDocumentOptionsValueJs::setColumns); }
};

struct ImmDocumentFragmentValueJs : public Napi::ObjectWrap<ImmDocumentFragmentValueJs> {
  Napi::Value setBaseline(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &ImmDocumentFragmentValueJs::setBaseline); }
  Napi::Value setBasecol(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &ImmDocumentFragmentValueJs::setBasecol); }
};

struct ImmCriticMarkupValueJs : public Napi::ObjectWrap<ImmCriticMarkupValueJs> {
  Napi::Value setKind(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &ImmCriticMarkupValueJs::setKind); }
};

struct ImmDocumentValueJs : public Napi::ObjectWrap<ImmDocumentValueJs> {
  Napi::Value setTitle(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &ImmDocumentValueJs::setTitle); }
  Napi::Value setAuthor(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &ImmDocumentValueJs::setAuthor); }
  Napi::Value setCreator(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &ImmDocumentValueJs::setCreator); }
  Napi::Value setFiletags(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &ImmDocumentValueJs::setFiletags); }
  Napi::Value setEmail(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &ImmDocumentValueJs::setEmail); }
  Napi::Value setLanguage(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &ImmDocumentValueJs::setLanguage); }
  Napi::Value setOptions(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &ImmDocumentValueJs::setOptions); }
  Napi::Value setExportfilename(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &ImmDocumentValueJs::setExportfilename); }
};

struct ImmFileTargetValueJs : public Napi::ObjectWrap<ImmFileTargetValueJs> {
  Napi::Value setPath(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &ImmFileTargetValueJs::setPath); }
  Napi::Value setLine(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &ImmFileTargetValueJs::setLine); }
  Napi::Value setSearchtarget(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &ImmFileTargetValueJs::setSearchtarget); }
  Napi::Value setRestricttoheadlines(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &ImmFileTargetValueJs::setRestricttoheadlines); }
  Napi::Value setTargetid(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &ImmFileTargetValueJs::setTargetid); }
  Napi::Value setRegexp(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &ImmFileTargetValueJs::setRegexp); }
};

struct ImmTextSeparatorValueJs : public Napi::ObjectWrap<ImmTextSeparatorValueJs> {};

struct ImmDocumentGroupValueJs : public Napi::ObjectWrap<ImmDocumentGroupValueJs> {};

struct ImmFileValueJs : public Napi::ObjectWrap<ImmFileValueJs> {
  Napi::Value setRelpath(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &ImmFileValueJs::setRelpath); }
  Napi::Value setAbspath(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &ImmFileValueJs::setAbspath); }
  Napi::Value setData(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &ImmFileValueJs::setData); }
};

struct ImmDirectoryValueJs : public Napi::ObjectWrap<ImmDirectoryValueJs> {
  Napi::Value setRelpath(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &ImmDirectoryValueJs::setRelpath); }
  Napi::Value setAbspath(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &ImmDirectoryValueJs::setAbspath); }
};

struct ImmSymlinkValueJs : public Napi::ObjectWrap<ImmSymlinkValueJs> {
  Napi::Value setIsdirectory(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &ImmSymlinkValueJs::setIsdirectory); }
  Napi::Value setAbspath(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &ImmSymlinkValueJs::setAbspath); }
};

struct ImmCmdIncludeValueJs : public Napi::ObjectWrap<ImmCmdIncludeValueJs> {
  Napi::Value setPath(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &ImmCmdIncludeValueJs::setPath); }
  Napi::Value setFirstline(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &ImmCmdIncludeValueJs::setFirstline); }
  Napi::Value setLastline(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &ImmCmdIncludeValueJs::setLastline); }
  Napi::Value setData(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &ImmCmdIncludeValueJs::setData); }
};

struct ImmAdapterOrgAPIJs : public Napi::ObjectWrap<ImmAdapterOrgAPIJs> {};

struct CmdJs : public Napi::ObjectWrap<CmdJs> {
  Napi::Value getAttrs(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &CmdJs::getAttrs); }
  Napi::Value getFirstAttr(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &CmdJs::getFirstAttr); }
};

struct CmdCustomRawJs : public Napi::ObjectWrap<CmdCustomRawJs> {
  Napi::Value getKind(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &CmdCustomRawJs::getKind); }
};

struct CmdCustomTextJs : public Napi::ObjectWrap<CmdCustomTextJs> {
  Napi::Value getKind(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &CmdCustomTextJs::getKind); }
};

struct LinkJs : public Napi::ObjectWrap<LinkJs> {
  Napi::Value getKind(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &LinkJs::getKind); }
};

struct BlockCommentJs : public Napi::ObjectWrap<BlockCommentJs> {
  Napi::Value getKind(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &BlockCommentJs::getKind); }
};

struct ParagraphJs : public Napi::ObjectWrap<ParagraphJs> {
  Napi::Value getKind(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ParagraphJs::getKind); }
  Napi::Value isFootnoteDefinition(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ParagraphJs::isFootnoteDefinition); }
  Napi::Value getFootnoteName(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ParagraphJs::getFootnoteName); }
  Napi::Value hasAdmonition(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ParagraphJs::hasAdmonition); }
  Napi::Value getAdmonitions(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ParagraphJs::getAdmonitions); }
  Napi::Value getAdmonitionNodes(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ParagraphJs::getAdmonitionNodes); }
  Napi::Value hasTimestamp(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ParagraphJs::hasTimestamp); }
  Napi::Value getTimestamps(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ParagraphJs::getTimestamps); }
  Napi::Value getTimestampNodes(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ParagraphJs::getTimestampNodes); }
  Napi::Value hasLeadHashtags(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ParagraphJs::hasLeadHashtags); }
  Napi::Value getLeadHashtags(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ParagraphJs::getLeadHashtags); }
  Napi::Value getBody(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ParagraphJs::getBody); }
};

struct ListJs : public Napi::ObjectWrap<ListJs> {
  Napi::Value getKind(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ListJs::getKind); }
  Napi::Value getListAttrs(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ListJs::getListAttrs); }
  Napi::Value getListFormattingMode(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ListJs::getListFormattingMode); }
  Napi::Value isDescriptionList(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ListJs::isDescriptionList); }
  Napi::Value isNumberedList(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ListJs::isNumberedList); }
};

struct HashTagJs : public Napi::ObjectWrap<HashTagJs> {
  Napi::Value getKind(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &HashTagJs::getKind); }
};

struct InlineFootnoteJs : public Napi::ObjectWrap<InlineFootnoteJs> {
  Napi::Value getKind(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &InlineFootnoteJs::getKind); }
};

struct InlineExportJs : public Napi::ObjectWrap<InlineExportJs> {
  Napi::Value getKind(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &InlineExportJs::getKind); }
};

struct EscapedJs : public Napi::ObjectWrap<EscapedJs> {
  Napi::Value getKind(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &EscapedJs::getKind); }
};

struct NewlineJs : public Napi::ObjectWrap<NewlineJs> {
  Napi::Value getKind(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &NewlineJs::getKind); }
};

struct SpaceJs : public Napi::ObjectWrap<SpaceJs> {
  Napi::Value getKind(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &SpaceJs::getKind); }
};

struct WordJs : public Napi::ObjectWrap<WordJs> {
  Napi::Value getKind(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &WordJs::getKind); }
};

struct AtMentionJs : public Napi::ObjectWrap<AtMentionJs> {
  Napi::Value getKind(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &AtMentionJs::getKind); }
};

struct RawTextJs : public Napi::ObjectWrap<RawTextJs> {
  Napi::Value getKind(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &RawTextJs::getKind); }
};

struct PunctuationJs : public Napi::ObjectWrap<PunctuationJs> {
  Napi::Value getKind(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &PunctuationJs::getKind); }
};

struct PlaceholderJs : public Napi::ObjectWrap<PlaceholderJs> {
  Napi::Value getKind(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &PlaceholderJs::getKind); }
};

struct BigIdentJs : public Napi::ObjectWrap<BigIdentJs> {
  Napi::Value getKind(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &BigIdentJs::getKind); }
};

struct TextTargetJs : public Napi::ObjectWrap<TextTargetJs> {
  Napi::Value getKind(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &TextTargetJs::getKind); }
};

struct BoldJs : public Napi::ObjectWrap<BoldJs> {
  Napi::Value getKind(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &BoldJs::getKind); }
};

struct UnderlineJs : public Napi::ObjectWrap<UnderlineJs> {
  Napi::Value getKind(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &UnderlineJs::getKind); }
};

struct MonospaceJs : public Napi::ObjectWrap<MonospaceJs> {
  Napi::Value getKind(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &MonospaceJs::getKind); }
};

struct MarkQuoteJs : public Napi::ObjectWrap<MarkQuoteJs> {
  Napi::Value getKind(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &MarkQuoteJs::getKind); }
};

struct VerbatimJs : public Napi::ObjectWrap<VerbatimJs> {
  Napi::Value getKind(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &VerbatimJs::getKind); }
};

struct ItalicJs : public Napi::ObjectWrap<ItalicJs> {
  Napi::Value getKind(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ItalicJs::getKind); }
};

struct StrikeJs : public Napi::ObjectWrap<StrikeJs> {
  Napi::Value getKind(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &StrikeJs::getKind); }
};

struct ParJs : public Napi::ObjectWrap<ParJs> {
  Napi::Value getKind(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ParJs::getKind); }
};

struct ImmAdapterStmtAPIJs : public Napi::ObjectWrap<ImmAdapterStmtAPIJs> {};

struct ImmAdapterSubtreeAPIJs : public Napi::ObjectWrap<ImmAdapterSubtreeAPIJs> {};

struct ImmAdapterNoneAPIJs : public Napi::ObjectWrap<ImmAdapterNoneAPIJs> {};

struct ImmAdapterAttrAPIJs : public Napi::ObjectWrap<ImmAdapterAttrAPIJs> {};

struct ImmAdapterAttrListAPIJs : public Napi::ObjectWrap<ImmAdapterAttrListAPIJs> {};

struct ImmAdapterAttrsAPIJs : public Napi::ObjectWrap<ImmAdapterAttrsAPIJs> {};

struct ImmAdapterErrorItemAPIJs : public Napi::ObjectWrap<ImmAdapterErrorItemAPIJs> {};

struct ImmAdapterErrorGroupAPIJs : public Napi::ObjectWrap<ImmAdapterErrorGroupAPIJs> {};

struct ImmAdapterStmtListAPIJs : public Napi::ObjectWrap<ImmAdapterStmtListAPIJs> {};

struct ImmAdapterEmptyAPIJs : public Napi::ObjectWrap<ImmAdapterEmptyAPIJs> {};

struct ImmAdapterInlineAPIJs : public Napi::ObjectWrap<ImmAdapterInlineAPIJs> {};

struct ImmAdapterTimeAPIJs : public Napi::ObjectWrap<ImmAdapterTimeAPIJs> {};

struct ImmAdapterTimeRangeAPIJs : public Napi::ObjectWrap<ImmAdapterTimeRangeAPIJs> {};

struct ImmAdapterMacroAPIJs : public Napi::ObjectWrap<ImmAdapterMacroAPIJs> {};

struct ImmAdapterSymbolAPIJs : public Napi::ObjectWrap<ImmAdapterSymbolAPIJs> {};

struct ImmAdapterLeafAPIJs : public Napi::ObjectWrap<ImmAdapterLeafAPIJs> {};

struct ImmAdapterMarkupAPIJs : public Napi::ObjectWrap<ImmAdapterMarkupAPIJs> {};

struct ImmAdapterLatexAPIJs : public Napi::ObjectWrap<ImmAdapterLatexAPIJs> {};

struct ImmAdapterSubtreeLogAPIJs : public Napi::ObjectWrap<ImmAdapterSubtreeLogAPIJs> {};

struct ImmAdapterColonExampleAPIJs : public Napi::ObjectWrap<ImmAdapterColonExampleAPIJs> {};

struct ImmAdapterCallAPIJs : public Napi::ObjectWrap<ImmAdapterCallAPIJs> {};

struct ImmAdapterFileAPIJs : public Napi::ObjectWrap<ImmAdapterFileAPIJs> {};

struct ImmAdapterDirectoryAPIJs : public Napi::ObjectWrap<ImmAdapterDirectoryAPIJs> {
  Napi::Value getFsSubnode(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ImmAdapterDirectoryAPIJs::getFsSubnode); }
};

struct ImmAdapterSymlinkAPIJs : public Napi::ObjectWrap<ImmAdapterSymlinkAPIJs> {};

struct ImmAdapterDocumentFragmentAPIJs : public Napi::ObjectWrap<ImmAdapterDocumentFragmentAPIJs> {};

struct ImmAdapterCriticMarkupAPIJs : public Napi::ObjectWrap<ImmAdapterCriticMarkupAPIJs> {};

struct ImmAdapterListItemAPIJs : public Napi::ObjectWrap<ImmAdapterListItemAPIJs> {};

struct ImmAdapterDocumentOptionsAPIJs : public Napi::ObjectWrap<ImmAdapterDocumentOptionsAPIJs> {};

struct ImmAdapterDocumentAPIJs : public Napi::ObjectWrap<ImmAdapterDocumentAPIJs> {};

struct ImmAdapterFileTargetAPIJs : public Napi::ObjectWrap<ImmAdapterFileTargetAPIJs> {};

struct ImmAdapterTextSeparatorAPIJs : public Napi::ObjectWrap<ImmAdapterTextSeparatorAPIJs> {};

struct ImmAdapterCmdIncludeAPIJs : public Napi::ObjectWrap<ImmAdapterCmdIncludeAPIJs> {};

struct ImmAdapterDocumentGroupAPIJs : public Napi::ObjectWrap<ImmAdapterDocumentGroupAPIJs> {};

struct BlockJs : public Napi::ObjectWrap<BlockJs> {};

struct LineCommandJs : public Napi::ObjectWrap<LineCommandJs> {};

struct CmdCustomArgsJs : public Napi::ObjectWrap<CmdCustomArgsJs> {
  Napi::Value getKind(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &CmdCustomArgsJs::getKind); }
};

struct CmdTblfmJs : public Napi::ObjectWrap<CmdTblfmJs> {
  Napi::Value getKind(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &CmdTblfmJs::getKind); }
};

struct CellJs : public Napi::ObjectWrap<CellJs> {
  Napi::Value getKind(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &CellJs::getKind); }
};

struct RowJs : public Napi::ObjectWrap<RowJs> {
  Napi::Value getKind(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &RowJs::getKind); }
};

struct ImmAdapterCmdAPIJs : public Napi::ObjectWrap<ImmAdapterCmdAPIJs> {};

struct ImmAdapterCmdCustomRawAPIJs : public Napi::ObjectWrap<ImmAdapterCmdCustomRawAPIJs> {};

struct ImmAdapterCmdCustomTextAPIJs : public Napi::ObjectWrap<ImmAdapterCmdCustomTextAPIJs> {};

struct ImmAdapterLinkAPIJs : public Napi::ObjectWrap<ImmAdapterLinkAPIJs> {};

struct ImmAdapterBlockCommentAPIJs : public Napi::ObjectWrap<ImmAdapterBlockCommentAPIJs> {};

struct ImmAdapterParagraphAPIJs : public Napi::ObjectWrap<ImmAdapterParagraphAPIJs> {};

struct ImmAdapterListAPIJs : public Napi::ObjectWrap<ImmAdapterListAPIJs> {};

struct ImmSubtreeAdapter : public Napi::ObjectWrap<ImmSubtreeAdapter> {
  Napi::Value ImmAdapterT(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &ImmSubtreeAdapter::ImmAdapterT); }
  Napi::Value getValue(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ImmSubtreeAdapter::getValue); }
};

struct ImmNoneAdapter : public Napi::ObjectWrap<ImmNoneAdapter> {
  Napi::Value ImmAdapterT(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &ImmNoneAdapter::ImmAdapterT); }
  Napi::Value getValue(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ImmNoneAdapter::getValue); }
};

struct ImmErrorItemAdapter : public Napi::ObjectWrap<ImmErrorItemAdapter> {
  Napi::Value ImmAdapterT(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &ImmErrorItemAdapter::ImmAdapterT); }
  Napi::Value getValue(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ImmErrorItemAdapter::getValue); }
};

struct ImmErrorGroupAdapter : public Napi::ObjectWrap<ImmErrorGroupAdapter> {
  Napi::Value ImmAdapterT(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &ImmErrorGroupAdapter::ImmAdapterT); }
  Napi::Value getValue(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ImmErrorGroupAdapter::getValue); }
};

struct ImmStmtListAdapter : public Napi::ObjectWrap<ImmStmtListAdapter> {
  Napi::Value ImmAdapterT(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &ImmStmtListAdapter::ImmAdapterT); }
  Napi::Value getValue(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ImmStmtListAdapter::getValue); }
};

struct ImmEmptyAdapter : public Napi::ObjectWrap<ImmEmptyAdapter> {
  Napi::Value ImmAdapterT(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &ImmEmptyAdapter::ImmAdapterT); }
  Napi::Value getValue(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ImmEmptyAdapter::getValue); }
};

struct ImmAdapterHashTagAPIJs : public Napi::ObjectWrap<ImmAdapterHashTagAPIJs> {};

struct ImmAdapterInlineFootnoteAPIJs : public Napi::ObjectWrap<ImmAdapterInlineFootnoteAPIJs> {};

struct ImmAdapterSubtreeCompletionAPIJs : public Napi::ObjectWrap<ImmAdapterSubtreeCompletionAPIJs> {};

struct ImmTimeAdapter : public Napi::ObjectWrap<ImmTimeAdapter> {
  Napi::Value ImmAdapterT(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &ImmTimeAdapter::ImmAdapterT); }
  Napi::Value getValue(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ImmTimeAdapter::getValue); }
};

struct ImmTimeRangeAdapter : public Napi::ObjectWrap<ImmTimeRangeAdapter> {
  Napi::Value ImmAdapterT(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &ImmTimeRangeAdapter::ImmAdapterT); }
  Napi::Value getValue(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ImmTimeRangeAdapter::getValue); }
};

struct ImmMacroAdapter : public Napi::ObjectWrap<ImmMacroAdapter> {
  Napi::Value ImmAdapterT(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &ImmMacroAdapter::ImmAdapterT); }
  Napi::Value getValue(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ImmMacroAdapter::getValue); }
};

struct ImmSymbolAdapter : public Napi::ObjectWrap<ImmSymbolAdapter> {
  Napi::Value ImmAdapterT(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &ImmSymbolAdapter::ImmAdapterT); }
  Napi::Value getValue(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ImmSymbolAdapter::getValue); }
};

struct ImmAdapterEscapedAPIJs : public Napi::ObjectWrap<ImmAdapterEscapedAPIJs> {};

struct ImmAdapterNewlineAPIJs : public Napi::ObjectWrap<ImmAdapterNewlineAPIJs> {};

struct ImmAdapterSpaceAPIJs : public Napi::ObjectWrap<ImmAdapterSpaceAPIJs> {};

struct ImmAdapterWordAPIJs : public Napi::ObjectWrap<ImmAdapterWordAPIJs> {};

struct ImmAdapterAtMentionAPIJs : public Napi::ObjectWrap<ImmAdapterAtMentionAPIJs> {};

struct ImmAdapterRawTextAPIJs : public Napi::ObjectWrap<ImmAdapterRawTextAPIJs> {};

struct ImmAdapterPunctuationAPIJs : public Napi::ObjectWrap<ImmAdapterPunctuationAPIJs> {};

struct ImmAdapterPlaceholderAPIJs : public Napi::ObjectWrap<ImmAdapterPlaceholderAPIJs> {};

struct ImmAdapterBigIdentAPIJs : public Napi::ObjectWrap<ImmAdapterBigIdentAPIJs> {};

struct ImmAdapterTextTargetAPIJs : public Napi::ObjectWrap<ImmAdapterTextTargetAPIJs> {};

struct ImmAdapterBoldAPIJs : public Napi::ObjectWrap<ImmAdapterBoldAPIJs> {};

struct ImmAdapterUnderlineAPIJs : public Napi::ObjectWrap<ImmAdapterUnderlineAPIJs> {};

struct ImmAdapterMonospaceAPIJs : public Napi::ObjectWrap<ImmAdapterMonospaceAPIJs> {};

struct ImmAdapterMarkQuoteAPIJs : public Napi::ObjectWrap<ImmAdapterMarkQuoteAPIJs> {};

struct ImmAdapterRadioTargetAPIJs : public Napi::ObjectWrap<ImmAdapterRadioTargetAPIJs> {};

struct ImmAdapterVerbatimAPIJs : public Napi::ObjectWrap<ImmAdapterVerbatimAPIJs> {};

struct ImmAdapterItalicAPIJs : public Napi::ObjectWrap<ImmAdapterItalicAPIJs> {};

struct ImmAdapterStrikeAPIJs : public Napi::ObjectWrap<ImmAdapterStrikeAPIJs> {};

struct ImmAdapterParAPIJs : public Napi::ObjectWrap<ImmAdapterParAPIJs> {};

struct ImmLatexAdapter : public Napi::ObjectWrap<ImmLatexAdapter> {
  Napi::Value ImmAdapterT(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &ImmLatexAdapter::ImmAdapterT); }
  Napi::Value getValue(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ImmLatexAdapter::getValue); }
};

struct ImmSubtreeLogAdapter : public Napi::ObjectWrap<ImmSubtreeLogAdapter> {
  Napi::Value ImmAdapterT(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &ImmSubtreeLogAdapter::ImmAdapterT); }
  Napi::Value getValue(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ImmSubtreeLogAdapter::getValue); }
};

struct ImmColonExampleAdapter : public Napi::ObjectWrap<ImmColonExampleAdapter> {
  Napi::Value ImmAdapterT(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &ImmColonExampleAdapter::ImmAdapterT); }
  Napi::Value getValue(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ImmColonExampleAdapter::getValue); }
};

struct ImmCallAdapter : public Napi::ObjectWrap<ImmCallAdapter> {
  Napi::Value ImmAdapterT(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &ImmCallAdapter::ImmAdapterT); }
  Napi::Value getValue(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ImmCallAdapter::getValue); }
};

struct ImmFileAdapter : public Napi::ObjectWrap<ImmFileAdapter> {
  Napi::Value ImmAdapterT(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &ImmFileAdapter::ImmAdapterT); }
  Napi::Value getValue(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ImmFileAdapter::getValue); }
};

struct ImmDirectoryAdapter : public Napi::ObjectWrap<ImmDirectoryAdapter> {
  Napi::Value ImmAdapterT(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &ImmDirectoryAdapter::ImmAdapterT); }
  Napi::Value getValue(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ImmDirectoryAdapter::getValue); }
};

struct ImmSymlinkAdapter : public Napi::ObjectWrap<ImmSymlinkAdapter> {
  Napi::Value ImmAdapterT(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &ImmSymlinkAdapter::ImmAdapterT); }
  Napi::Value getValue(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ImmSymlinkAdapter::getValue); }
};

struct ImmDocumentFragmentAdapter : public Napi::ObjectWrap<ImmDocumentFragmentAdapter> {
  Napi::Value ImmAdapterT(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &ImmDocumentFragmentAdapter::ImmAdapterT); }
  Napi::Value getValue(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ImmDocumentFragmentAdapter::getValue); }
};

struct ImmCriticMarkupAdapter : public Napi::ObjectWrap<ImmCriticMarkupAdapter> {
  Napi::Value ImmAdapterT(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &ImmCriticMarkupAdapter::ImmAdapterT); }
  Napi::Value getValue(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ImmCriticMarkupAdapter::getValue); }
};

struct ImmListItemAdapter : public Napi::ObjectWrap<ImmListItemAdapter> {
  Napi::Value ImmAdapterT(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &ImmListItemAdapter::ImmAdapterT); }
  Napi::Value getValue(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ImmListItemAdapter::getValue); }
};

struct ImmDocumentOptionsAdapter : public Napi::ObjectWrap<ImmDocumentOptionsAdapter> {
  Napi::Value ImmAdapterT(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &ImmDocumentOptionsAdapter::ImmAdapterT); }
  Napi::Value getValue(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ImmDocumentOptionsAdapter::getValue); }
};

struct ImmDocumentAdapter : public Napi::ObjectWrap<ImmDocumentAdapter> {
  Napi::Value ImmAdapterT(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &ImmDocumentAdapter::ImmAdapterT); }
  Napi::Value getValue(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ImmDocumentAdapter::getValue); }
};

struct ImmFileTargetAdapter : public Napi::ObjectWrap<ImmFileTargetAdapter> {
  Napi::Value ImmAdapterT(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &ImmFileTargetAdapter::ImmAdapterT); }
  Napi::Value getValue(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ImmFileTargetAdapter::getValue); }
};

struct ImmTextSeparatorAdapter : public Napi::ObjectWrap<ImmTextSeparatorAdapter> {
  Napi::Value ImmAdapterT(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &ImmTextSeparatorAdapter::ImmAdapterT); }
  Napi::Value getValue(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ImmTextSeparatorAdapter::getValue); }
};

struct ImmCmdIncludeAdapter : public Napi::ObjectWrap<ImmCmdIncludeAdapter> {
  Napi::Value ImmAdapterT(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &ImmCmdIncludeAdapter::ImmAdapterT); }
  Napi::Value getValue(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ImmCmdIncludeAdapter::getValue); }
};

struct ImmDocumentGroupAdapter : public Napi::ObjectWrap<ImmDocumentGroupAdapter> {
  Napi::Value ImmAdapterT(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &ImmDocumentGroupAdapter::ImmAdapterT); }
  Napi::Value getValue(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ImmDocumentGroupAdapter::getValue); }
};

struct BlockCenterJs : public Napi::ObjectWrap<BlockCenterJs> {
  Napi::Value getKind(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &BlockCenterJs::getKind); }
};

struct BlockQuoteJs : public Napi::ObjectWrap<BlockQuoteJs> {
  Napi::Value getKind(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &BlockQuoteJs::getKind); }
};

struct BlockVerseJs : public Napi::ObjectWrap<BlockVerseJs> {
  Napi::Value getKind(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &BlockVerseJs::getKind); }
};

struct BlockDynamicFallbackJs : public Napi::ObjectWrap<BlockDynamicFallbackJs> {
  Napi::Value getKind(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &BlockDynamicFallbackJs::getKind); }
};

struct BlockExampleJs : public Napi::ObjectWrap<BlockExampleJs> {
  Napi::Value getKind(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &BlockExampleJs::getKind); }
};

struct BlockExportJs : public Napi::ObjectWrap<BlockExportJs> {
  Napi::Value getKind(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &BlockExportJs::getKind); }
  Napi::Value getPlacement(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &BlockExportJs::getPlacement); }
};

struct BlockAdmonitionJs : public Napi::ObjectWrap<BlockAdmonitionJs> {
  Napi::Value getKind(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &BlockAdmonitionJs::getKind); }
};

struct BlockCodeEvalResultJs : public Napi::ObjectWrap<BlockCodeEvalResultJs> {
  Napi::Value getKind(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &BlockCodeEvalResultJs::getKind); }
};

struct BlockCodeJs : public Napi::ObjectWrap<BlockCodeJs> {
  Napi::Value getKind(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &BlockCodeJs::getKind); }
  Napi::Value getVariable(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &BlockCodeJs::getVariable); }
};

struct TableJs : public Napi::ObjectWrap<TableJs> {
  Napi::Value getKind(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &TableJs::getKind); }
};

struct AttachedJs : public Napi::ObjectWrap<AttachedJs> {};

struct ImmAdapterLineCommandAPIJs : public Napi::ObjectWrap<ImmAdapterLineCommandAPIJs> {};

struct ImmAdapterCmdCustomArgsAPIJs : public Napi::ObjectWrap<ImmAdapterCmdCustomArgsAPIJs> {};

struct ImmAdapterCmdTblfmAPIJs : public Napi::ObjectWrap<ImmAdapterCmdTblfmAPIJs> {};

struct ImmAdapterBlockAPIJs : public Napi::ObjectWrap<ImmAdapterBlockAPIJs> {};

struct ImmAdapterCellAPIJs : public Napi::ObjectWrap<ImmAdapterCellAPIJs> {};

struct ImmAdapterRowAPIJs : public Napi::ObjectWrap<ImmAdapterRowAPIJs> {};

struct ImmCmdCustomRawAdapter : public Napi::ObjectWrap<ImmCmdCustomRawAdapter> {
  Napi::Value ImmAdapterT(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &ImmCmdCustomRawAdapter::ImmAdapterT); }
  Napi::Value getValue(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ImmCmdCustomRawAdapter::getValue); }
};

struct ImmCmdCustomTextAdapter : public Napi::ObjectWrap<ImmCmdCustomTextAdapter> {
  Napi::Value ImmAdapterT(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &ImmCmdCustomTextAdapter::ImmAdapterT); }
  Napi::Value getValue(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ImmCmdCustomTextAdapter::getValue); }
};

struct ImmLinkAdapter : public Napi::ObjectWrap<ImmLinkAdapter> {
  Napi::Value ImmAdapterT(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &ImmLinkAdapter::ImmAdapterT); }
  Napi::Value getValue(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ImmLinkAdapter::getValue); }
};

struct ImmBlockCommentAdapter : public Napi::ObjectWrap<ImmBlockCommentAdapter> {
  Napi::Value ImmAdapterT(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &ImmBlockCommentAdapter::ImmAdapterT); }
  Napi::Value getValue(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ImmBlockCommentAdapter::getValue); }
};

struct ImmParagraphAdapter : public Napi::ObjectWrap<ImmParagraphAdapter> {
  Napi::Value ImmAdapterT(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &ImmParagraphAdapter::ImmAdapterT); }
  Napi::Value getValue(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ImmParagraphAdapter::getValue); }
};

struct ImmListAdapter : public Napi::ObjectWrap<ImmListAdapter> {
  Napi::Value ImmAdapterT(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &ImmListAdapter::ImmAdapterT); }
  Napi::Value getValue(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ImmListAdapter::getValue); }
};

struct ImmHashTagAdapter : public Napi::ObjectWrap<ImmHashTagAdapter> {
  Napi::Value ImmAdapterT(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &ImmHashTagAdapter::ImmAdapterT); }
  Napi::Value getValue(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ImmHashTagAdapter::getValue); }
};

struct ImmInlineFootnoteAdapter : public Napi::ObjectWrap<ImmInlineFootnoteAdapter> {
  Napi::Value ImmAdapterT(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &ImmInlineFootnoteAdapter::ImmAdapterT); }
  Napi::Value getValue(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ImmInlineFootnoteAdapter::getValue); }
};

struct ImmEscapedAdapter : public Napi::ObjectWrap<ImmEscapedAdapter> {
  Napi::Value ImmAdapterT(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &ImmEscapedAdapter::ImmAdapterT); }
  Napi::Value getValue(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ImmEscapedAdapter::getValue); }
};

struct ImmNewlineAdapter : public Napi::ObjectWrap<ImmNewlineAdapter> {
  Napi::Value ImmAdapterT(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &ImmNewlineAdapter::ImmAdapterT); }
  Napi::Value getValue(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ImmNewlineAdapter::getValue); }
};

struct ImmSpaceAdapter : public Napi::ObjectWrap<ImmSpaceAdapter> {
  Napi::Value ImmAdapterT(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &ImmSpaceAdapter::ImmAdapterT); }
  Napi::Value getValue(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ImmSpaceAdapter::getValue); }
};

struct ImmWordAdapter : public Napi::ObjectWrap<ImmWordAdapter> {
  Napi::Value ImmAdapterT(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &ImmWordAdapter::ImmAdapterT); }
  Napi::Value getValue(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ImmWordAdapter::getValue); }
};

struct ImmAtMentionAdapter : public Napi::ObjectWrap<ImmAtMentionAdapter> {
  Napi::Value ImmAdapterT(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &ImmAtMentionAdapter::ImmAdapterT); }
  Napi::Value getValue(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ImmAtMentionAdapter::getValue); }
};

struct ImmRawTextAdapter : public Napi::ObjectWrap<ImmRawTextAdapter> {
  Napi::Value ImmAdapterT(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &ImmRawTextAdapter::ImmAdapterT); }
  Napi::Value getValue(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ImmRawTextAdapter::getValue); }
};

struct ImmPunctuationAdapter : public Napi::ObjectWrap<ImmPunctuationAdapter> {
  Napi::Value ImmAdapterT(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &ImmPunctuationAdapter::ImmAdapterT); }
  Napi::Value getValue(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ImmPunctuationAdapter::getValue); }
};

struct ImmPlaceholderAdapter : public Napi::ObjectWrap<ImmPlaceholderAdapter> {
  Napi::Value ImmAdapterT(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &ImmPlaceholderAdapter::ImmAdapterT); }
  Napi::Value getValue(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ImmPlaceholderAdapter::getValue); }
};

struct ImmBigIdentAdapter : public Napi::ObjectWrap<ImmBigIdentAdapter> {
  Napi::Value ImmAdapterT(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &ImmBigIdentAdapter::ImmAdapterT); }
  Napi::Value getValue(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ImmBigIdentAdapter::getValue); }
};

struct ImmTextTargetAdapter : public Napi::ObjectWrap<ImmTextTargetAdapter> {
  Napi::Value ImmAdapterT(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &ImmTextTargetAdapter::ImmAdapterT); }
  Napi::Value getValue(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ImmTextTargetAdapter::getValue); }
};

struct ImmBoldAdapter : public Napi::ObjectWrap<ImmBoldAdapter> {
  Napi::Value ImmAdapterT(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &ImmBoldAdapter::ImmAdapterT); }
  Napi::Value getValue(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ImmBoldAdapter::getValue); }
};

struct ImmUnderlineAdapter : public Napi::ObjectWrap<ImmUnderlineAdapter> {
  Napi::Value ImmAdapterT(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &ImmUnderlineAdapter::ImmAdapterT); }
  Napi::Value getValue(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ImmUnderlineAdapter::getValue); }
};

struct ImmMonospaceAdapter : public Napi::ObjectWrap<ImmMonospaceAdapter> {
  Napi::Value ImmAdapterT(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &ImmMonospaceAdapter::ImmAdapterT); }
  Napi::Value getValue(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ImmMonospaceAdapter::getValue); }
};

struct ImmMarkQuoteAdapter : public Napi::ObjectWrap<ImmMarkQuoteAdapter> {
  Napi::Value ImmAdapterT(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &ImmMarkQuoteAdapter::ImmAdapterT); }
  Napi::Value getValue(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ImmMarkQuoteAdapter::getValue); }
};

struct ImmRadioTargetAdapter : public Napi::ObjectWrap<ImmRadioTargetAdapter> {
  Napi::Value ImmAdapterT(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &ImmRadioTargetAdapter::ImmAdapterT); }
  Napi::Value getValue(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ImmRadioTargetAdapter::getValue); }
};

struct ImmVerbatimAdapter : public Napi::ObjectWrap<ImmVerbatimAdapter> {
  Napi::Value ImmAdapterT(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &ImmVerbatimAdapter::ImmAdapterT); }
  Napi::Value getValue(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ImmVerbatimAdapter::getValue); }
};

struct ImmItalicAdapter : public Napi::ObjectWrap<ImmItalicAdapter> {
  Napi::Value ImmAdapterT(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &ImmItalicAdapter::ImmAdapterT); }
  Napi::Value getValue(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ImmItalicAdapter::getValue); }
};

struct ImmStrikeAdapter : public Napi::ObjectWrap<ImmStrikeAdapter> {
  Napi::Value ImmAdapterT(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &ImmStrikeAdapter::ImmAdapterT); }
  Napi::Value getValue(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ImmStrikeAdapter::getValue); }
};

struct ImmParAdapter : public Napi::ObjectWrap<ImmParAdapter> {
  Napi::Value ImmAdapterT(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &ImmParAdapter::ImmAdapterT); }
  Napi::Value getValue(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ImmParAdapter::getValue); }
};

struct CmdCaptionJs : public Napi::ObjectWrap<CmdCaptionJs> {
  Napi::Value getKind(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &CmdCaptionJs::getKind); }
};

struct CmdColumnsJs : public Napi::ObjectWrap<CmdColumnsJs> {
  Napi::Value getKind(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &CmdColumnsJs::getKind); }
};

struct CmdNameJs : public Napi::ObjectWrap<CmdNameJs> {
  Napi::Value getKind(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &CmdNameJs::getKind); }
};

struct CmdCallJs : public Napi::ObjectWrap<CmdCallJs> {
  Napi::Value getKind(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &CmdCallJs::getKind); }
};

struct CmdAttrJs : public Napi::ObjectWrap<CmdAttrJs> {
  Napi::Value getKind(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &CmdAttrJs::getKind); }
};

struct CmdExportJs : public Napi::ObjectWrap<CmdExportJs> {
  Napi::Value getKind(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &CmdExportJs::getKind); }
};

struct ImmAdapterAttachedAPIJs : public Napi::ObjectWrap<ImmAdapterAttachedAPIJs> {};

struct ImmCmdCustomArgsAdapter : public Napi::ObjectWrap<ImmCmdCustomArgsAdapter> {
  Napi::Value ImmAdapterT(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &ImmCmdCustomArgsAdapter::ImmAdapterT); }
  Napi::Value getValue(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ImmCmdCustomArgsAdapter::getValue); }
};

struct ImmCmdTblfmAdapter : public Napi::ObjectWrap<ImmCmdTblfmAdapter> {
  Napi::Value ImmAdapterT(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &ImmCmdTblfmAdapter::ImmAdapterT); }
  Napi::Value getValue(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ImmCmdTblfmAdapter::getValue); }
};

struct ImmAdapterBlockCenterAPIJs : public Napi::ObjectWrap<ImmAdapterBlockCenterAPIJs> {};

struct ImmAdapterBlockQuoteAPIJs : public Napi::ObjectWrap<ImmAdapterBlockQuoteAPIJs> {};

struct ImmAdapterBlockVerseAPIJs : public Napi::ObjectWrap<ImmAdapterBlockVerseAPIJs> {};

struct ImmAdapterBlockExampleAPIJs : public Napi::ObjectWrap<ImmAdapterBlockExampleAPIJs> {};

struct ImmAdapterInlineExportAPIJs : public Napi::ObjectWrap<ImmAdapterInlineExportAPIJs> {};

struct ImmAdapterCmdExportAPIJs : public Napi::ObjectWrap<ImmAdapterCmdExportAPIJs> {};

struct ImmAdapterBlockExportAPIJs : public Napi::ObjectWrap<ImmAdapterBlockExportAPIJs> {};

struct ImmAdapterBlockDynamicFallbackAPIJs : public Napi::ObjectWrap<ImmAdapterBlockDynamicFallbackAPIJs> {};

struct ImmAdapterBlockAdmonitionAPIJs : public Napi::ObjectWrap<ImmAdapterBlockAdmonitionAPIJs> {};

struct ImmAdapterBlockCodeEvalResultAPIJs : public Napi::ObjectWrap<ImmAdapterBlockCodeEvalResultAPIJs> {};

struct ImmAdapterBlockCodeAPIJs : public Napi::ObjectWrap<ImmAdapterBlockCodeAPIJs> {};

struct ImmAdapterTableAPIJs : public Napi::ObjectWrap<ImmAdapterTableAPIJs> {};

struct ImmCellAdapter : public Napi::ObjectWrap<ImmCellAdapter> {
  Napi::Value ImmAdapterT(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &ImmCellAdapter::ImmAdapterT); }
  Napi::Value getValue(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ImmCellAdapter::getValue); }
};

struct ImmRowAdapter : public Napi::ObjectWrap<ImmRowAdapter> {
  Napi::Value ImmAdapterT(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &ImmRowAdapter::ImmAdapterT); }
  Napi::Value getValue(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ImmRowAdapter::getValue); }
};

struct ImmAdapterCmdCaptionAPIJs : public Napi::ObjectWrap<ImmAdapterCmdCaptionAPIJs> {};

struct ImmAdapterCmdColumnsAPIJs : public Napi::ObjectWrap<ImmAdapterCmdColumnsAPIJs> {};

struct ImmAdapterCmdNameAPIJs : public Napi::ObjectWrap<ImmAdapterCmdNameAPIJs> {};

struct ImmAdapterCmdCallAPIJs : public Napi::ObjectWrap<ImmAdapterCmdCallAPIJs> {};

struct ImmAdapterCmdResultsAPIJs : public Napi::ObjectWrap<ImmAdapterCmdResultsAPIJs> {};

struct ImmAdapterCmdAttrAPIJs : public Napi::ObjectWrap<ImmAdapterCmdAttrAPIJs> {};

struct ImmBlockCenterAdapter : public Napi::ObjectWrap<ImmBlockCenterAdapter> {
  Napi::Value ImmAdapterT(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &ImmBlockCenterAdapter::ImmAdapterT); }
  Napi::Value getValue(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ImmBlockCenterAdapter::getValue); }
};

struct ImmBlockQuoteAdapter : public Napi::ObjectWrap<ImmBlockQuoteAdapter> {
  Napi::Value ImmAdapterT(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &ImmBlockQuoteAdapter::ImmAdapterT); }
  Napi::Value getValue(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ImmBlockQuoteAdapter::getValue); }
};

struct ImmBlockVerseAdapter : public Napi::ObjectWrap<ImmBlockVerseAdapter> {
  Napi::Value ImmAdapterT(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &ImmBlockVerseAdapter::ImmAdapterT); }
  Napi::Value getValue(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ImmBlockVerseAdapter::getValue); }
};

struct ImmBlockExampleAdapter : public Napi::ObjectWrap<ImmBlockExampleAdapter> {
  Napi::Value ImmAdapterT(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &ImmBlockExampleAdapter::ImmAdapterT); }
  Napi::Value getValue(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ImmBlockExampleAdapter::getValue); }
};

struct ImmInlineExportAdapter : public Napi::ObjectWrap<ImmInlineExportAdapter> {
  Napi::Value ImmAdapterT(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &ImmInlineExportAdapter::ImmAdapterT); }
  Napi::Value getValue(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ImmInlineExportAdapter::getValue); }
};

struct ImmCmdExportAdapter : public Napi::ObjectWrap<ImmCmdExportAdapter> {
  Napi::Value ImmAdapterT(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &ImmCmdExportAdapter::ImmAdapterT); }
  Napi::Value getValue(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ImmCmdExportAdapter::getValue); }
};

struct ImmBlockExportAdapter : public Napi::ObjectWrap<ImmBlockExportAdapter> {
  Napi::Value ImmAdapterT(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &ImmBlockExportAdapter::ImmAdapterT); }
  Napi::Value getValue(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ImmBlockExportAdapter::getValue); }
};

struct ImmBlockDynamicFallbackAdapter : public Napi::ObjectWrap<ImmBlockDynamicFallbackAdapter> {
  Napi::Value ImmAdapterT(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &ImmBlockDynamicFallbackAdapter::ImmAdapterT); }
  Napi::Value getValue(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ImmBlockDynamicFallbackAdapter::getValue); }
};

struct ImmBlockAdmonitionAdapter : public Napi::ObjectWrap<ImmBlockAdmonitionAdapter> {
  Napi::Value ImmAdapterT(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &ImmBlockAdmonitionAdapter::ImmAdapterT); }
  Napi::Value getValue(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ImmBlockAdmonitionAdapter::getValue); }
};

struct ImmBlockCodeEvalResultAdapter : public Napi::ObjectWrap<ImmBlockCodeEvalResultAdapter> {
  Napi::Value ImmAdapterT(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &ImmBlockCodeEvalResultAdapter::ImmAdapterT); }
  Napi::Value getValue(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ImmBlockCodeEvalResultAdapter::getValue); }
};

struct ImmBlockCodeAdapter : public Napi::ObjectWrap<ImmBlockCodeAdapter> {
  Napi::Value ImmAdapterT(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &ImmBlockCodeAdapter::ImmAdapterT); }
  Napi::Value getValue(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ImmBlockCodeAdapter::getValue); }
};

struct ImmTableAdapter : public Napi::ObjectWrap<ImmTableAdapter> {
  Napi::Value ImmAdapterT(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &ImmTableAdapter::ImmAdapterT); }
  Napi::Value getValue(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ImmTableAdapter::getValue); }
};

struct ImmCmdCaptionAdapter : public Napi::ObjectWrap<ImmCmdCaptionAdapter> {
  Napi::Value ImmAdapterT(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &ImmCmdCaptionAdapter::ImmAdapterT); }
  Napi::Value getValue(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ImmCmdCaptionAdapter::getValue); }
};

struct ImmCmdColumnsAdapter : public Napi::ObjectWrap<ImmCmdColumnsAdapter> {
  Napi::Value ImmAdapterT(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &ImmCmdColumnsAdapter::ImmAdapterT); }
  Napi::Value getValue(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ImmCmdColumnsAdapter::getValue); }
};

struct ImmCmdNameAdapter : public Napi::ObjectWrap<ImmCmdNameAdapter> {
  Napi::Value ImmAdapterT(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &ImmCmdNameAdapter::ImmAdapterT); }
  Napi::Value getValue(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ImmCmdNameAdapter::getValue); }
};

struct ImmCmdCallAdapter : public Napi::ObjectWrap<ImmCmdCallAdapter> {
  Napi::Value ImmAdapterT(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &ImmCmdCallAdapter::ImmAdapterT); }
  Napi::Value getValue(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ImmCmdCallAdapter::getValue); }
};

struct ImmCmdAttrAdapter : public Napi::ObjectWrap<ImmCmdAttrAdapter> {
  Napi::Value ImmAdapterT(Napi::CallbackInfo const& info) { return WrapMethod(info, getPtr(), &ImmCmdAttrAdapter::ImmAdapterT); }
  Napi::Value getValue(Napi::CallbackInfo const& info) { return WrapConstMethod(info, getPtr(), &ImmCmdAttrAdapter::getValue); }
};

Napi::Object InitModule(Napi::Env env, Napi::Object exports) {
  UserTimeBreakdownJs::Init(env, exports)
  UserTimeJs::Init(env, exports)
  LineColJs::Init(env, exports)
  OrgJsonJs::Init(env, exports)
  OrgJs::Init(env, exports)
  OperationsTracerJs::Init(env, exports)
  ImmIdJs::Init(env, exports)
  ImmPathStepJs::Init(env, exports)
  ImmPathJs::Init(env, exports)
  ImmUniqIdJs::Init(env, exports)
  ImmNoneValueReadJs::Init(env, exports)
  ImmErrorItemValueReadJs::Init(env, exports)
  ImmErrorGroupValueReadJs::Init(env, exports)
  ImmStmtListValueReadJs::Init(env, exports)
  ImmEmptyValueReadJs::Init(env, exports)
  ImmCmdCaptionValueReadJs::Init(env, exports)
  ImmCmdColumnsValueReadJs::Init(env, exports)
  ImmCmdNameValueReadJs::Init(env, exports)
  ImmCmdCustomArgsValueReadJs::Init(env, exports)
  ImmCmdCustomRawValueReadJs::Init(env, exports)
  ImmCmdCustomTextValueReadJs::Init(env, exports)
  ImmCmdCallValueReadJs::Init(env, exports)
  ImmCmdTblfmValueReadJs::Init(env, exports)
  ImmHashTagValueReadJs::Init(env, exports)
  ImmInlineFootnoteValueReadJs::Init(env, exports)
  ImmInlineExportValueReadJs::Init(env, exports)
  ImmTimeValueReadJs::Init(env, exports)
  ImmTimeRangeValueReadJs::Init(env, exports)
  ImmMacroValueReadJs::Init(env, exports)
  ImmSymbolValueReadJs::Init(env, exports)
  ImmEscapedValueReadJs::Init(env, exports)
  ImmNewlineValueReadJs::Init(env, exports)
  ImmSpaceValueReadJs::Init(env, exports)
  ImmWordValueReadJs::Init(env, exports)
  ImmAtMentionValueReadJs::Init(env, exports)
  ImmRawTextValueReadJs::Init(env, exports)
  ImmPunctuationValueReadJs::Init(env, exports)
  ImmPlaceholderValueReadJs::Init(env, exports)
  ImmBigIdentValueReadJs::Init(env, exports)
  ImmTextTargetValueReadJs::Init(env, exports)
  ImmBoldValueReadJs::Init(env, exports)
  ImmUnderlineValueReadJs::Init(env, exports)
  ImmMonospaceValueReadJs::Init(env, exports)
  ImmMarkQuoteValueReadJs::Init(env, exports)
  ImmVerbatimValueReadJs::Init(env, exports)
  ImmItalicValueReadJs::Init(env, exports)
  ImmStrikeValueReadJs::Init(env, exports)
  ImmParValueReadJs::Init(env, exports)
  ImmRadioTargetValueReadJs::Init(env, exports)
  ImmLatexValueReadJs::Init(env, exports)
  ImmLinkValueReadJs::Init(env, exports)
  ImmBlockCenterValueReadJs::Init(env, exports)
  ImmBlockQuoteValueReadJs::Init(env, exports)
  ImmBlockCommentValueReadJs::Init(env, exports)
  ImmBlockVerseValueReadJs::Init(env, exports)
  ImmBlockDynamicFallbackValueReadJs::Init(env, exports)
  ImmBlockExampleValueReadJs::Init(env, exports)
  ImmBlockExportValueReadJs::Init(env, exports)
  ImmBlockAdmonitionValueReadJs::Init(env, exports)
  ImmBlockCodeEvalResultValueReadJs::Init(env, exports)
  ImmBlockCodeValueReadJs::Init(env, exports)
  ImmSubtreeLogValueReadJs::Init(env, exports)
  ImmSubtreeValueReadJs::Init(env, exports)
  ImmCellValueReadJs::Init(env, exports)
  ImmRowValueReadJs::Init(env, exports)
  ImmTableValueReadJs::Init(env, exports)
  ImmParagraphValueReadJs::Init(env, exports)
  ImmColonExampleValueReadJs::Init(env, exports)
  ImmCmdAttrValueReadJs::Init(env, exports)
  ImmCmdExportValueReadJs::Init(env, exports)
  ImmCallValueReadJs::Init(env, exports)
  ImmListValueReadJs::Init(env, exports)
  ImmListItemValueReadJs::Init(env, exports)
  ImmDocumentOptionsValueReadJs::Init(env, exports)
  ImmDocumentFragmentValueReadJs::Init(env, exports)
  ImmCriticMarkupValueReadJs::Init(env, exports)
  ImmDocumentValueReadJs::Init(env, exports)
  ImmFileTargetValueReadJs::Init(env, exports)
  ImmTextSeparatorValueReadJs::Init(env, exports)
  ImmDocumentGroupValueReadJs::Init(env, exports)
  ImmFileValueReadJs::Init(env, exports)
  ImmDirectoryValueReadJs::Init(env, exports)
  ImmSymlinkValueReadJs::Init(env, exports)
  ImmCmdIncludeValueReadJs::Init(env, exports)
  ImmAstContextJs::Init(env, exports)
  ImmAstVersionJs::Init(env, exports)
  ImmAdapterJs::Init(env, exports)
  ImmAdapterVirtualBaseJs::Init(env, exports)
  OrgParseFragmentJs::Init(env, exports)
  OrgParseParametersJs::Init(env, exports)
  OrgDirectoryParseParametersJs::Init(env, exports)
  OrgYamlExportOptsJs::Init(env, exports)
  OrgTreeExportOptsJs::Init(env, exports)
  AstTrackingPathJs::Init(env, exports)
  AstTrackingAlternativesJs::Init(env, exports)
  AstTrackingGroupJs::Init(env, exports)
  AstTrackingMapJs::Init(env, exports)
  SequenceSegmentJs::Init(env, exports)
  SequenceSegmentGroupJs::Init(env, exports)
  SequenceAnnotationTagJs::Init(env, exports)
  SequenceAnnotationJs::Init(env, exports)
  MapLinkJs::Init(env, exports)
  MapNodePropJs::Init(env, exports)
  MapEdgePropJs::Init(env, exports)
  MapNodeJs::Init(env, exports)
  MapEdgeJs::Init(env, exports)
  MapGraphJs::Init(env, exports)
  MapGraphStateJs::Init(env, exports)
  PyCodeEvalParametersJs::Init(env, exports)
  ExporterPythonJs::Init(env, exports)
  LispCodeJs::Init(env, exports)
  TblfmJs::Init(env, exports)
  AttrValueJs::Init(env, exports)
  HashTagFlatJs::Init(env, exports)
  HashTagTextJs::Init(env, exports)
  SubtreePathJs::Init(env, exports)
  LinkTargetJs::Init(env, exports)
  SubtreeLogHeadJs::Init(env, exports)
  SubtreeCompletionJs::Init(env, exports)
  AttrListJs::Init(env, exports)
  AttrGroupJs::Init(env, exports)
  OrgCodeEvalInputJs::Init(env, exports)
  OrgCodeEvalOutputJs::Init(env, exports)
  ColumnViewJs::Init(env, exports)
  BlockCodeLineJs::Init(env, exports)
  DocumentExportConfigJs::Init(env, exports)
  SubtreePeriodJs::Init(env, exports)
  NamedPropertyJs::Init(env, exports)
  NoneJs::Init(env, exports)
  ErrorItemJs::Init(env, exports)
  ErrorGroupJs::Init(env, exports)
  StmtJs::Init(env, exports)
  InlineJs::Init(env, exports)
  StmtListJs::Init(env, exports)
  EmptyJs::Init(env, exports)
  LeafJs::Init(env, exports)
  TimeJs::Init(env, exports)
  TimeRangeJs::Init(env, exports)
  MacroJs::Init(env, exports)
  SymbolJs::Init(env, exports)
  MarkupJs::Init(env, exports)
  RadioTargetJs::Init(env, exports)
  LatexJs::Init(env, exports)
  SubtreeLogJs::Init(env, exports)
  SubtreeJs::Init(env, exports)
  ColonExampleJs::Init(env, exports)
  CallJs::Init(env, exports)
  ListItemJs::Init(env, exports)
  DocumentOptionsJs::Init(env, exports)
  DocumentFragmentJs::Init(env, exports)
  CriticMarkupJs::Init(env, exports)
  DocumentJs::Init(env, exports)
  FileTargetJs::Init(env, exports)
  TextSeparatorJs::Init(env, exports)
  DocumentGroupJs::Init(env, exports)
  FileJs::Init(env, exports)
  DirectoryJs::Init(env, exports)
  SymlinkJs::Init(env, exports)
  CmdIncludeJs::Init(env, exports)
  MapConfigJs::Init(env, exports)
  ImmIdTNone::Init(env, exports)
  ImmIdTErrorItem::Init(env, exports)
  ImmIdTErrorGroup::Init(env, exports)
  ImmIdTStmt::Init(env, exports)
  ImmIdTInline::Init(env, exports)
  ImmIdTStmtList::Init(env, exports)
  ImmIdTEmpty::Init(env, exports)
  ImmIdTCmd::Init(env, exports)
  ImmIdTBlock::Init(env, exports)
  ImmIdTLineCommand::Init(env, exports)
  ImmIdTAttached::Init(env, exports)
  ImmIdTLeaf::Init(env, exports)
  ImmIdTCmdCaption::Init(env, exports)
  ImmIdTCmdColumns::Init(env, exports)
  ImmIdTCmdName::Init(env, exports)
  ImmIdTCmdCustomArgs::Init(env, exports)
  ImmIdTCmdCustomRaw::Init(env, exports)
  ImmIdTCmdCustomText::Init(env, exports)
  ImmIdTCmdCall::Init(env, exports)
  ImmIdTCmdTblfm::Init(env, exports)
  ImmIdTHashTag::Init(env, exports)
  ImmIdTInlineFootnote::Init(env, exports)
  ImmIdTInlineExport::Init(env, exports)
  ImmIdTTime::Init(env, exports)
  ImmIdTTimeRange::Init(env, exports)
  ImmIdTMacro::Init(env, exports)
  ImmIdTSymbol::Init(env, exports)
  ImmIdTEscaped::Init(env, exports)
  ImmIdTNewline::Init(env, exports)
  ImmIdTSpace::Init(env, exports)
  ImmIdTWord::Init(env, exports)
  ImmIdTAtMention::Init(env, exports)
  ImmIdTRawText::Init(env, exports)
  ImmIdTPunctuation::Init(env, exports)
  ImmIdTPlaceholder::Init(env, exports)
  ImmIdTBigIdent::Init(env, exports)
  ImmIdTTextTarget::Init(env, exports)
  ImmIdTMarkup::Init(env, exports)
  ImmIdTBold::Init(env, exports)
  ImmIdTUnderline::Init(env, exports)
  ImmIdTMonospace::Init(env, exports)
  ImmIdTMarkQuote::Init(env, exports)
  ImmIdTVerbatim::Init(env, exports)
  ImmIdTItalic::Init(env, exports)
  ImmIdTStrike::Init(env, exports)
  ImmIdTPar::Init(env, exports)
  ImmIdTRadioTarget::Init(env, exports)
  ImmIdTLatex::Init(env, exports)
  ImmIdTLink::Init(env, exports)
  ImmIdTBlockCenter::Init(env, exports)
  ImmIdTBlockQuote::Init(env, exports)
  ImmIdTBlockComment::Init(env, exports)
  ImmIdTBlockVerse::Init(env, exports)
  ImmIdTBlockDynamicFallback::Init(env, exports)
  ImmIdTBlockExample::Init(env, exports)
  ImmIdTBlockExport::Init(env, exports)
  ImmIdTBlockAdmonition::Init(env, exports)
  ImmIdTBlockCodeEvalResult::Init(env, exports)
  ImmIdTBlockCode::Init(env, exports)
  ImmIdTSubtreeLog::Init(env, exports)
  ImmIdTSubtree::Init(env, exports)
  ImmIdTCell::Init(env, exports)
  ImmIdTRow::Init(env, exports)
  ImmIdTTable::Init(env, exports)
  ImmIdTParagraph::Init(env, exports)
  ImmIdTColonExample::Init(env, exports)
  ImmIdTCmdAttr::Init(env, exports)
  ImmIdTCmdExport::Init(env, exports)
  ImmIdTCall::Init(env, exports)
  ImmIdTList::Init(env, exports)
  ImmIdTListItem::Init(env, exports)
  ImmIdTDocumentOptions::Init(env, exports)
  ImmIdTDocumentFragment::Init(env, exports)
  ImmIdTCriticMarkup::Init(env, exports)
  ImmIdTDocument::Init(env, exports)
  ImmIdTFileTarget::Init(env, exports)
  ImmIdTTextSeparator::Init(env, exports)
  ImmIdTDocumentGroup::Init(env, exports)
  ImmIdTFile::Init(env, exports)
  ImmIdTDirectory::Init(env, exports)
  ImmIdTSymlink::Init(env, exports)
  ImmIdTCmdInclude::Init(env, exports)
  ImmNoneValueJs::Init(env, exports)
  ImmErrorItemValueJs::Init(env, exports)
  ImmErrorGroupValueJs::Init(env, exports)
  ImmStmtListValueJs::Init(env, exports)
  ImmEmptyValueJs::Init(env, exports)
  ImmCmdCaptionValueJs::Init(env, exports)
  ImmCmdColumnsValueJs::Init(env, exports)
  ImmCmdNameValueJs::Init(env, exports)
  ImmCmdCustomArgsValueJs::Init(env, exports)
  ImmCmdCustomRawValueJs::Init(env, exports)
  ImmCmdCustomTextValueJs::Init(env, exports)
  ImmCmdCallValueJs::Init(env, exports)
  ImmCmdTblfmValueJs::Init(env, exports)
  ImmHashTagValueJs::Init(env, exports)
  ImmInlineFootnoteValueJs::Init(env, exports)
  ImmInlineExportValueJs::Init(env, exports)
  ImmTimeValueJs::Init(env, exports)
  ImmTimeRangeValueJs::Init(env, exports)
  ImmMacroValueJs::Init(env, exports)
  ImmSymbolValueJs::Init(env, exports)
  ImmEscapedValueJs::Init(env, exports)
  ImmNewlineValueJs::Init(env, exports)
  ImmSpaceValueJs::Init(env, exports)
  ImmWordValueJs::Init(env, exports)
  ImmAtMentionValueJs::Init(env, exports)
  ImmRawTextValueJs::Init(env, exports)
  ImmPunctuationValueJs::Init(env, exports)
  ImmPlaceholderValueJs::Init(env, exports)
  ImmBigIdentValueJs::Init(env, exports)
  ImmTextTargetValueJs::Init(env, exports)
  ImmBoldValueJs::Init(env, exports)
  ImmUnderlineValueJs::Init(env, exports)
  ImmMonospaceValueJs::Init(env, exports)
  ImmMarkQuoteValueJs::Init(env, exports)
  ImmVerbatimValueJs::Init(env, exports)
  ImmItalicValueJs::Init(env, exports)
  ImmStrikeValueJs::Init(env, exports)
  ImmParValueJs::Init(env, exports)
  ImmRadioTargetValueJs::Init(env, exports)
  ImmLatexValueJs::Init(env, exports)
  ImmLinkValueJs::Init(env, exports)
  ImmBlockCenterValueJs::Init(env, exports)
  ImmBlockQuoteValueJs::Init(env, exports)
  ImmBlockCommentValueJs::Init(env, exports)
  ImmBlockVerseValueJs::Init(env, exports)
  ImmBlockDynamicFallbackValueJs::Init(env, exports)
  ImmBlockExampleValueJs::Init(env, exports)
  ImmBlockExportValueJs::Init(env, exports)
  ImmBlockAdmonitionValueJs::Init(env, exports)
  ImmBlockCodeEvalResultValueJs::Init(env, exports)
  ImmBlockCodeValueJs::Init(env, exports)
  ImmSubtreeLogValueJs::Init(env, exports)
  ImmSubtreeValueJs::Init(env, exports)
  ImmCellValueJs::Init(env, exports)
  ImmRowValueJs::Init(env, exports)
  ImmTableValueJs::Init(env, exports)
  ImmParagraphValueJs::Init(env, exports)
  ImmColonExampleValueJs::Init(env, exports)
  ImmCmdAttrValueJs::Init(env, exports)
  ImmCmdExportValueJs::Init(env, exports)
  ImmCallValueJs::Init(env, exports)
  ImmListValueJs::Init(env, exports)
  ImmListItemValueJs::Init(env, exports)
  ImmDocumentOptionsValueJs::Init(env, exports)
  ImmDocumentFragmentValueJs::Init(env, exports)
  ImmCriticMarkupValueJs::Init(env, exports)
  ImmDocumentValueJs::Init(env, exports)
  ImmFileTargetValueJs::Init(env, exports)
  ImmTextSeparatorValueJs::Init(env, exports)
  ImmDocumentGroupValueJs::Init(env, exports)
  ImmFileValueJs::Init(env, exports)
  ImmDirectoryValueJs::Init(env, exports)
  ImmSymlinkValueJs::Init(env, exports)
  ImmCmdIncludeValueJs::Init(env, exports)
  ImmAdapterOrgAPIJs::Init(env, exports)
  CmdJs::Init(env, exports)
  CmdCustomRawJs::Init(env, exports)
  CmdCustomTextJs::Init(env, exports)
  LinkJs::Init(env, exports)
  BlockCommentJs::Init(env, exports)
  ParagraphJs::Init(env, exports)
  ListJs::Init(env, exports)
  HashTagJs::Init(env, exports)
  InlineFootnoteJs::Init(env, exports)
  InlineExportJs::Init(env, exports)
  EscapedJs::Init(env, exports)
  NewlineJs::Init(env, exports)
  SpaceJs::Init(env, exports)
  WordJs::Init(env, exports)
  AtMentionJs::Init(env, exports)
  RawTextJs::Init(env, exports)
  PunctuationJs::Init(env, exports)
  PlaceholderJs::Init(env, exports)
  BigIdentJs::Init(env, exports)
  TextTargetJs::Init(env, exports)
  BoldJs::Init(env, exports)
  UnderlineJs::Init(env, exports)
  MonospaceJs::Init(env, exports)
  MarkQuoteJs::Init(env, exports)
  VerbatimJs::Init(env, exports)
  ItalicJs::Init(env, exports)
  StrikeJs::Init(env, exports)
  ParJs::Init(env, exports)
  ImmAdapterStmtAPIJs::Init(env, exports)
  ImmAdapterSubtreeAPIJs::Init(env, exports)
  ImmAdapterNoneAPIJs::Init(env, exports)
  ImmAdapterAttrAPIJs::Init(env, exports)
  ImmAdapterAttrListAPIJs::Init(env, exports)
  ImmAdapterAttrsAPIJs::Init(env, exports)
  ImmAdapterErrorItemAPIJs::Init(env, exports)
  ImmAdapterErrorGroupAPIJs::Init(env, exports)
  ImmAdapterStmtListAPIJs::Init(env, exports)
  ImmAdapterEmptyAPIJs::Init(env, exports)
  ImmAdapterInlineAPIJs::Init(env, exports)
  ImmAdapterTimeAPIJs::Init(env, exports)
  ImmAdapterTimeRangeAPIJs::Init(env, exports)
  ImmAdapterMacroAPIJs::Init(env, exports)
  ImmAdapterSymbolAPIJs::Init(env, exports)
  ImmAdapterLeafAPIJs::Init(env, exports)
  ImmAdapterMarkupAPIJs::Init(env, exports)
  ImmAdapterLatexAPIJs::Init(env, exports)
  ImmAdapterSubtreeLogAPIJs::Init(env, exports)
  ImmAdapterColonExampleAPIJs::Init(env, exports)
  ImmAdapterCallAPIJs::Init(env, exports)
  ImmAdapterFileAPIJs::Init(env, exports)
  ImmAdapterDirectoryAPIJs::Init(env, exports)
  ImmAdapterSymlinkAPIJs::Init(env, exports)
  ImmAdapterDocumentFragmentAPIJs::Init(env, exports)
  ImmAdapterCriticMarkupAPIJs::Init(env, exports)
  ImmAdapterListItemAPIJs::Init(env, exports)
  ImmAdapterDocumentOptionsAPIJs::Init(env, exports)
  ImmAdapterDocumentAPIJs::Init(env, exports)
  ImmAdapterFileTargetAPIJs::Init(env, exports)
  ImmAdapterTextSeparatorAPIJs::Init(env, exports)
  ImmAdapterCmdIncludeAPIJs::Init(env, exports)
  ImmAdapterDocumentGroupAPIJs::Init(env, exports)
  BlockJs::Init(env, exports)
  LineCommandJs::Init(env, exports)
  CmdCustomArgsJs::Init(env, exports)
  CmdTblfmJs::Init(env, exports)
  CellJs::Init(env, exports)
  RowJs::Init(env, exports)
  ImmAdapterCmdAPIJs::Init(env, exports)
  ImmAdapterCmdCustomRawAPIJs::Init(env, exports)
  ImmAdapterCmdCustomTextAPIJs::Init(env, exports)
  ImmAdapterLinkAPIJs::Init(env, exports)
  ImmAdapterBlockCommentAPIJs::Init(env, exports)
  ImmAdapterParagraphAPIJs::Init(env, exports)
  ImmAdapterListAPIJs::Init(env, exports)
  ImmSubtreeAdapter::Init(env, exports)
  ImmNoneAdapter::Init(env, exports)
  ImmErrorItemAdapter::Init(env, exports)
  ImmErrorGroupAdapter::Init(env, exports)
  ImmStmtListAdapter::Init(env, exports)
  ImmEmptyAdapter::Init(env, exports)
  ImmAdapterHashTagAPIJs::Init(env, exports)
  ImmAdapterInlineFootnoteAPIJs::Init(env, exports)
  ImmAdapterSubtreeCompletionAPIJs::Init(env, exports)
  ImmTimeAdapter::Init(env, exports)
  ImmTimeRangeAdapter::Init(env, exports)
  ImmMacroAdapter::Init(env, exports)
  ImmSymbolAdapter::Init(env, exports)
  ImmAdapterEscapedAPIJs::Init(env, exports)
  ImmAdapterNewlineAPIJs::Init(env, exports)
  ImmAdapterSpaceAPIJs::Init(env, exports)
  ImmAdapterWordAPIJs::Init(env, exports)
  ImmAdapterAtMentionAPIJs::Init(env, exports)
  ImmAdapterRawTextAPIJs::Init(env, exports)
  ImmAdapterPunctuationAPIJs::Init(env, exports)
  ImmAdapterPlaceholderAPIJs::Init(env, exports)
  ImmAdapterBigIdentAPIJs::Init(env, exports)
  ImmAdapterTextTargetAPIJs::Init(env, exports)
  ImmAdapterBoldAPIJs::Init(env, exports)
  ImmAdapterUnderlineAPIJs::Init(env, exports)
  ImmAdapterMonospaceAPIJs::Init(env, exports)
  ImmAdapterMarkQuoteAPIJs::Init(env, exports)
  ImmAdapterRadioTargetAPIJs::Init(env, exports)
  ImmAdapterVerbatimAPIJs::Init(env, exports)
  ImmAdapterItalicAPIJs::Init(env, exports)
  ImmAdapterStrikeAPIJs::Init(env, exports)
  ImmAdapterParAPIJs::Init(env, exports)
  ImmLatexAdapter::Init(env, exports)
  ImmSubtreeLogAdapter::Init(env, exports)
  ImmColonExampleAdapter::Init(env, exports)
  ImmCallAdapter::Init(env, exports)
  ImmFileAdapter::Init(env, exports)
  ImmDirectoryAdapter::Init(env, exports)
  ImmSymlinkAdapter::Init(env, exports)
  ImmDocumentFragmentAdapter::Init(env, exports)
  ImmCriticMarkupAdapter::Init(env, exports)
  ImmListItemAdapter::Init(env, exports)
  ImmDocumentOptionsAdapter::Init(env, exports)
  ImmDocumentAdapter::Init(env, exports)
  ImmFileTargetAdapter::Init(env, exports)
  ImmTextSeparatorAdapter::Init(env, exports)
  ImmCmdIncludeAdapter::Init(env, exports)
  ImmDocumentGroupAdapter::Init(env, exports)
  BlockCenterJs::Init(env, exports)
  BlockQuoteJs::Init(env, exports)
  BlockVerseJs::Init(env, exports)
  BlockDynamicFallbackJs::Init(env, exports)
  BlockExampleJs::Init(env, exports)
  BlockExportJs::Init(env, exports)
  BlockAdmonitionJs::Init(env, exports)
  BlockCodeEvalResultJs::Init(env, exports)
  BlockCodeJs::Init(env, exports)
  TableJs::Init(env, exports)
  AttachedJs::Init(env, exports)
  ImmAdapterLineCommandAPIJs::Init(env, exports)
  ImmAdapterCmdCustomArgsAPIJs::Init(env, exports)
  ImmAdapterCmdTblfmAPIJs::Init(env, exports)
  ImmAdapterBlockAPIJs::Init(env, exports)
  ImmAdapterCellAPIJs::Init(env, exports)
  ImmAdapterRowAPIJs::Init(env, exports)
  ImmCmdCustomRawAdapter::Init(env, exports)
  ImmCmdCustomTextAdapter::Init(env, exports)
  ImmLinkAdapter::Init(env, exports)
  ImmBlockCommentAdapter::Init(env, exports)
  ImmParagraphAdapter::Init(env, exports)
  ImmListAdapter::Init(env, exports)
  ImmHashTagAdapter::Init(env, exports)
  ImmInlineFootnoteAdapter::Init(env, exports)
  ImmEscapedAdapter::Init(env, exports)
  ImmNewlineAdapter::Init(env, exports)
  ImmSpaceAdapter::Init(env, exports)
  ImmWordAdapter::Init(env, exports)
  ImmAtMentionAdapter::Init(env, exports)
  ImmRawTextAdapter::Init(env, exports)
  ImmPunctuationAdapter::Init(env, exports)
  ImmPlaceholderAdapter::Init(env, exports)
  ImmBigIdentAdapter::Init(env, exports)
  ImmTextTargetAdapter::Init(env, exports)
  ImmBoldAdapter::Init(env, exports)
  ImmUnderlineAdapter::Init(env, exports)
  ImmMonospaceAdapter::Init(env, exports)
  ImmMarkQuoteAdapter::Init(env, exports)
  ImmRadioTargetAdapter::Init(env, exports)
  ImmVerbatimAdapter::Init(env, exports)
  ImmItalicAdapter::Init(env, exports)
  ImmStrikeAdapter::Init(env, exports)
  ImmParAdapter::Init(env, exports)
  CmdCaptionJs::Init(env, exports)
  CmdColumnsJs::Init(env, exports)
  CmdNameJs::Init(env, exports)
  CmdCallJs::Init(env, exports)
  CmdAttrJs::Init(env, exports)
  CmdExportJs::Init(env, exports)
  ImmAdapterAttachedAPIJs::Init(env, exports)
  ImmCmdCustomArgsAdapter::Init(env, exports)
  ImmCmdTblfmAdapter::Init(env, exports)
  ImmAdapterBlockCenterAPIJs::Init(env, exports)
  ImmAdapterBlockQuoteAPIJs::Init(env, exports)
  ImmAdapterBlockVerseAPIJs::Init(env, exports)
  ImmAdapterBlockExampleAPIJs::Init(env, exports)
  ImmAdapterInlineExportAPIJs::Init(env, exports)
  ImmAdapterCmdExportAPIJs::Init(env, exports)
  ImmAdapterBlockExportAPIJs::Init(env, exports)
  ImmAdapterBlockDynamicFallbackAPIJs::Init(env, exports)
  ImmAdapterBlockAdmonitionAPIJs::Init(env, exports)
  ImmAdapterBlockCodeEvalResultAPIJs::Init(env, exports)
  ImmAdapterBlockCodeAPIJs::Init(env, exports)
  ImmAdapterTableAPIJs::Init(env, exports)
  ImmCellAdapter::Init(env, exports)
  ImmRowAdapter::Init(env, exports)
  ImmAdapterCmdCaptionAPIJs::Init(env, exports)
  ImmAdapterCmdColumnsAPIJs::Init(env, exports)
  ImmAdapterCmdNameAPIJs::Init(env, exports)
  ImmAdapterCmdCallAPIJs::Init(env, exports)
  ImmAdapterCmdResultsAPIJs::Init(env, exports)
  ImmAdapterCmdAttrAPIJs::Init(env, exports)
  ImmBlockCenterAdapter::Init(env, exports)
  ImmBlockQuoteAdapter::Init(env, exports)
  ImmBlockVerseAdapter::Init(env, exports)
  ImmBlockExampleAdapter::Init(env, exports)
  ImmInlineExportAdapter::Init(env, exports)
  ImmCmdExportAdapter::Init(env, exports)
  ImmBlockExportAdapter::Init(env, exports)
  ImmBlockDynamicFallbackAdapter::Init(env, exports)
  ImmBlockAdmonitionAdapter::Init(env, exports)
  ImmBlockCodeEvalResultAdapter::Init(env, exports)
  ImmBlockCodeAdapter::Init(env, exports)
  ImmTableAdapter::Init(env, exports)
  ImmCmdCaptionAdapter::Init(env, exports)
  ImmCmdColumnsAdapter::Init(env, exports)
  ImmCmdNameAdapter::Init(env, exports)
  ImmCmdCallAdapter::Init(env, exports)
  ImmCmdAttrAdapter::Init(env, exports)
  return exports;
}

NODE_API_MODULE(pyhaxorg, InitModule);
/* clang-format on */