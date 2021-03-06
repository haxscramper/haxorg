{.experimental: "caseStmtMacros".}

import lexer, ast, common, buf
import hmisc/[helpers, hexceptions]
import std/[strutils, sequtils, strformat, streams]

import fusion/matching


using lexer: var Lexer

#[

* Some implementation notes

This parser assumes there is *no* hard runtime errors - whatewher user
wrote is *exactly* what they wanted to, and we can only try to figure out
their intentions as close as possible. This means multiple reparsing, or
long lookahead attempts are not out of ordinary, and meant to incorporate
most of the common edge cases, and provide generic fallback behavior in
other cases.

]#

type
  ParseConf* = object
    dropEmptyWords*: bool

using parseConf: ParseConf


proc classifyMarkKind*(ch: char): OrgNodeSubKind =
  case ch:
    of '+': oskStrike
    of '*': oskBold
    of '_': oskUnderline
    of '/': oskItalic
    of '~': oskMonospaced
    of '`': oskBacktick
    of '=': oskVerbatim
    else: oskNone

proc classifyWord*(word: string): OrgNodeSubKind =
  if allIt(word, it in OWhitespace):
    oskSpace

  elif allIt(word, it in OPunctChars):
    oskPunct

  else:
    oskText


proc parseStmtList*(lexer, parseConf): OrgNode
proc parseParagraph*(
  lexer, parseConf; subKind: OrgNodeSubKind = oskNone): OrgNode

proc parseBareIdent*(lexer, parseConf): OrgNode =
  lexer.skip()
  result = newBareIdent(getSkipWhile(lexer, OBareIdentChars).toSlice(lexer))

proc parseCommandArgs*(lexer, parseConf): OrgNode =
  result = onkRawText.newTree(lexer.getSkipToEOL(true).toSlice(lexer))

proc parseIdent*(lexer; subKind: OrgNodeSubKind = oskNone): OrgNode =
  var buf = initStrRanges(lexer)
  lexer.expect(OIdentStartChars)
  buf.add lexer.pop
  while lexer[] in OIdentChars:
    buf.add lexer.pop


  result = onkIdent.newTree(buf.toSlice(lexer))
  result.subKind = subKind

proc parseBigIdent*(
    lexer, parseConf; subkind: OrgNodeSubKind = oskNone): OrgNode =

  var buf = initEmptyStrRanges(lexer)
  lexer.expect(OBigIdentChars)
  while lexer[] in OIdentChars:
    buf.add lexer.pop()

  result = onkBigIdent.newTree(buf.toSlice(lexer))
  result.subKind = subKind

proc parseCmdArguments*(lexer, parseConf): OrgNode =
  lexer.skip()
  var flags: seq[OrgNode]
  while lexer[] == '-':
    flags.add onkCmdFlag.newTree(onkRawText.newTree(
      lexer.getSkipUntil(OWhitespace).toSlice(lexer)))

    lexer.skip()

  var args: seq[OrgNode]
  while lexer[] == ':':
    lexer.advance()
    args.add onkCmdValue.newTree(lexer.parseIdent())
    lexer.skip()

    var value = lexer.getSkipUntil({OEndOfFile, ':', '\n'}).toSlice(lexer)
    while value[^1] in OWhitespace:
      value.pop()

    args[^1].add onkRawText.newTree(value)

    # lexer.skip()

  result = onkCmdArguments.newTree(
    tern(flags.len > 0, newOStmtList(flags), newEmptyNode()),
    tern(args.len > 0, newOStmtList(args), newEmptyNode())
  )

  # lexer.nextLine()



proc parseCommand*(lexer, parseConf): OrgNode =
  ## Parse single-line command. Command arguments will be cut verbatim into
  ## resulting ast for user-defined processing.
  result = onkCommand.newTree()
  lexer.skipExpected("#+")
  result.add newOrgIdent(lexer.getSkipWhileTo(OIdentChars, ':').toSlice(lexer))
  lexer.advance()
  if normalize($result["name"].text) in ["attrlatex"]:
    result.add parseCmdArguments(lexer, parseConf)

  else:
    result.add parseCommandArgs(lexer, parseConf)

  if lexer[] == '\n':
    lexer.advance()


proc `=~`(str: StrSlice, str2: string): bool =
  normalize($str) == normalize(str2)

proc parseDrawer*(lexer, parseConf): OrgNode =
  result = onkDrawer.newTree()

  # echov lexer.pstringRanges()

  # echov lexer @? 0 .. 10
  result.add onkIdent.newTree(
    lexer.getInsideSimple(':', ':').toSlice(lexer))

  lexer.advance()
  var buf = lexer.initEmptyStrRanges()
  while not (lexer[":end:"] or lexer.atEnd()):
    # echov lexer @? 0 .. 3
    # echov lexer[":end:"]
    buf.add lexer.pop()

  buf.pop()

  var propLexer = newSublexer(buf.toSlice(lexer))
  var proplist = newOStmtList()
  if result["name"].text =~ "properties":
    # echov "found properties args"
    # echov propLexer @? 0 .. 10
    while propLexer[":"]:
      var prop = onkProperty.newTree()
      # echov propLexer @? 0 .. 10
      # echov propLexer[":"]
      propLexer.skipExpected(":")
      prop.add propLexer.parseIdent()

      propLexer.skipExpected(":")
      if propLexer.allUntil(OIdentChars, {':'}):
        prop.add propLexer.parseIdent()
        propLexer.skipExpected(":")

      else:
        prop.add newEmptyNode()

      if prop["name"].text =~ "header-args":
        propLexer.skip()
        # echov propLexer @? 0 .. 10
        prop.add propLexer.parseCmdArguments(parseConf)
        propLexer.advance()

      else:
        propLexer.skip()
        prop.add onkRawText.newTree(
          propLexer.getSkipToEOL().toSlice(lexer))

      propList.add prop

    # echov propLexer @? 0 .. 10
    result.add propList

  elif result["name"].text =~ "logbook":
    result.add propLexer.parseStmtList(parseConf)

  else:
    result.add onkRawText.newTree(buf.toSlice(lexer))



  lexer.nextLine()




proc parseDrawers*(lexer, parseConf): OrgNode =
  ## Parse one or mode drawers starting on current line.
  # echov lexer.lineStartsWith(":")
  # echov "Parsing drawers"
  # echov lexer @? 0 .. 10
  if lexer.lineStartsWith(":"):
    # var drawerLexer = lexer.newSublexer(
    #   lexer.cutIndentedBlock(
    #     lexer.indentTo(":"), fromInline = false)
    # )

    result = onkStmtList.newTree()

    while lexer[] == ':':
      # echov lexer @? 0 .. 10
      result.add parseDrawer(lexer, parseConf)

    # echov "Finished parsing drawer"


  else:
    return newEmptyNode()




proc parseOrgTable*(lexer, parseConf; parentRes: OrgNode): OrgNode =
  result = onkTable.newTree(parentRes[^1])
  var sublexer = newSublexer(
    lexer.getBuf(),
    lexer.getBlockUntil("#+end-table")
  )

  type
    RowFormatting = enum
      rfCompact
      rfOneline
      rfStmtList

  var rows = newOStmtList()
  var rowArgs: OrgNode
  while sublexer[] != OEndOfFile:
    rowArgs = sublexer.parseCommand(parseConf)[1]
    let body = sublexer.getBlockUntil("#+row")
    var cformat: RowFormatting

    block cellKind:
      var rowlexer = lexer.newSublexer(body)
      while true:
        if rowlexer[] in {'#', '\n'}:
          if rowlexer["#+cell:"]:
            cformat = rfStmtList
            break cellKind

          else:
            discard rowlexer.getSkipToEOL()
            rowlexer.advance()

        elif rowlexer[] in {' '}:
          discard rowlexer.skip()
          if rowlexer[] == '|':
            echo lexer.error("Fuck '   |'").msg

          elif rowlexer[] in {'#', '\n'}:
            discard rowlexer.getSkipToEOL()
            rowlexer.advance()

          else:
            echo rowlexer.error("????").msg

        elif rowlexer[] == '|':
          discard rowlexer.getSkipToEOL()
          if rowlexer[-1] == '|':
            cformat = rfCompact
            break cellKind

          else:
            cformat = rfOneline
            break cellKind

        else:
          raiseAssert("#[ IMPLEMENT ]#")


    var resrow = onkTableRow.newTree(rowArgs)
    block parseCell:
      var
        rowlexer = lexer.newSublexer(body)
        rowtext = newOStmtList()
        rowcells = newOStmtList()

      case cformat:
        of rfCompact:

          while rowlexer[] != OEndOfFile:
            if rowlexer[] == '|':
              rowlexer.advance()
              var cells = rowLexer.getSkipToEOL()
              lexer.advance()
              cells.pop()

              for elem in cells.toSlice(lexer).split('|'):
                rowcells.add onkTableCell.newTree(
                  newEmptyNode(), newWord(
                    elem.toSlice(lexer).strip().toSlice(lexer)))

            else:
              let slice = rowlexer.getSkipToEOL().toSlice(lexer)
              if slice.len > 0:
                # echov toSeq(items(slice))
                # echov slice
                # echov slice.ranges
                rowtext.add newWord(slice)
              rowlexer.advance()

        of rfOneLine:
          while rowlexer[] != OEndOfFile:
            if rowlexer[] == '|':
              rowlexer.advance()
              rowlexer.skip()
              rowcells.add onkTableCell.newTree(
                newEmptyNode(),
                newWord(rowLexer.getSkipToEOL().toSlice(lexer))
              )

              rowlexer.advance()

            else:
              let slice = rowlexer.getSkipToEOL().toSlice(lexer)
              if slice.len > 0:
                rowtext.add newWord(slice)

              rowlexer.advance()

        of rfStmtList:
          let pos = rowlexer.getPosition()
          rowtext.add newWord(
            rowlexer.getBlockUntil("#+cell:").toSlice(lexer)
          )

          while rowlexer[] != OEndOfFile:
            assert rowlexer[0 .. 6] == "#+cell:"
            rowcells.add onkTableCell.newTree(
              rowlexer.parseCommand(parseConf),
              newWord(
                rowlexer.getBlockUntil("#+cell:").toSlice(lexer)
              )
            )

      resrow.add rowtext
      resrow.add rowcells



    result.add resrow

proc parseResultBlock*(lexer, parseConf): OrgNode =
  # echov lexer @? 0 .. 10
  lexer.skipExpected("#+results")
  result = onkResult.newTree()
  if lexer["["]:
    result.add onkRawText.newTree(
      lexer.getInsideSimple('[', ']').toSlice(lexer))

  else:
    result.add newEmptyNode()

  lexer.nextLine()

  if lexer[":results:"]:
    result.add lexer.parseDrawer(parseConf)

  else:
    result.add onkRawText.newTree(lexer.getSkipToEOL().toSlice(lexer))

proc searchResult*(lexer, parseConf): int =
  var ahead = lexer
  result = -1
  while not ahead.atEnd():
    if ahead[] notin {'#', '\n', ' '}:
      return -1

    else:
      ahead.skip(Whitespace)

      # echov ahead @? 0 .. 10
      if not ahead["#+results"]:
        ahead.nextLine()

      else:
        return ahead.d.bufpos

proc parseNowebBlock*(lexer, parseConf): OrgNode =
  result = onkNowebMultilineBlock.newTree()
  while not lexer.atEnd():
    var nowRange: StrRanges
    while not (lexer["<<"] or lexer.atEnd()):
      nowRange.add lexer.pop()

    result.nowebBlock.slices.add NowebSlice(
      slice: nowRange.toSlice(lexer)
    )


    if not lexer.atEnd():
      lexer.advance()
      var body = lexer.getInsideBalanced('<', '>')
      result.nowebBlock.slices.add NowebSlice(
        isPlaceholder: true,
        slice: body
      )
      lexer.advance()


proc parseSnippetBlock*(lexer, parseConf): OrgNode =
  result = onkSnippetMultilineBlock.newTree()
  while not lexer.atEnd():
    var nowRange: StrRanges
    while not ((lexer["$"] and lexer[+1] in {'0' .. '9', '{'}) or lexer.atEnd()):
      nowRange.add lexer.pop()

    result.snippetBlock.slices.add SnippetSlice(
      slice: nowRange.toSlice(lexer)
    )

    if not lexer.atEnd():
      lexer.advance()
      if lexer[] in {'0' .. '9'}:
        result.snippetBlock.slices.add SnippetSlice(
          isPlaceholder: true,
          slice: lexer.initStrRanges().toSlice(lexer)
        )
        lexer.advance()

      else:
        var body = lexer.getInsideBalanced('{', '}')
        result.snippetBlock.slices.add SnippetSlice(
          isPlaceholder: true,
          hasBody: true,
          slice: body
        )

proc parseOrgSource*(lexer, parseConf; parentRes: OrgNode): OrgNode =
  result = onkSrcCode.newTree()

  var argsLexer = newSublexer(parentRes[1].text)

  argsLexer.skip()
  result.add argsLexer.parseIdent()
  argsLexer.skip()
  result.add argsLexer.parseCmdArguments(parseConf)


  result.add onkVerbatimMultilineBlock.newTree(
    lexer.getBlockUntil("#+end").toSlice(lexer))

  lexer.nextLine()

  let idx = lexer.searchResult(parseConf)
  if idx > 0:
    var prefCmds: seq[OrgNode]
    while not lexer["#+results"]:
      while lexer[] in OLineBreaks + OWhitespace:
        lexer.advance()

      prefCmds.add lexer.parseCommand(parseConf)

    result.add onkAssocStmtList.newTree(
      onkStmtList.newTree(prefCmds),
      lexer.parseResultBlock(parseConf)
    )

  else:
    result.add newEmptyNode()

  if result["header-args"]["args"].anyIt(
    it["name"].text == "noweb" and
    it["value"].text == "yes"
  ):
    result["body"] = result["body"].text.newSublexer().withResIt do:
      parseNowebBlock(it, parseConf)

  elif result["header-args"]["args"].anyIt(
    it["name"].text == "snippet" and
    it["value"].text == "yes"
  ):
    result["body"] = result["body"].text.newSublexer().withResIt do:
      parseSnippetBlock(it, parseConf)


proc parseMultilineCommand*(
    lexer, parseConf;
    balanced: bool = true,
    parseInside: bool = false
  ): OrgNode =
  ## Parse multiline command starting from `#+begin` and ending with
  ## `#+end`.
  ##
  ## - @arg{balanced} :: body of the multiline command might contains
  ##   unundented pairs of `#+begin/#+end` blocks with the same name.
  ## - @arg{parseInline} :: parse body of multiline command as statement
  ##   list, or cut it verbatim into resulting AST in form of multiline
  ##   code block
  # TODO control kind of resulting cutout block.

  # echov "Multiline command"

  result = OrgNode(kind: onkMultilineCommand)
  lexer.skipExpected("#+BEGIN")
  discard lexer.getSkipWhile({'-', '_'})

  result.add lexer.parseIdent()

  result.add parseCommandArgs(lexer, parseConf)
  lexer.nextLine()

  if result["name"].text == "table":
    result = lexer.parseOrgTable(parseConf, result)

  elif result["name"].text =~ "src":
    result = lexer.parseOrgSource(parseConf, result)

  else:
    result.add onkVerbatimMultilineBlock.newTree(
      lexer.getBlockUntil("#+end").toSlice(lexer))

  lexer.nextLine()


proc optGetWhile(lexer; chars: set[char], resKind: OrgNodeKind): OrgNode =
  if lexer[] in chars:
    result = newTree(resKind, lexer.getSkipWhile(chars).toSlice(lexer))

  else:
    result = newEmptyNode()


proc parseAtEntry*(lexer, parseConf): OrgNode =
  ## Parse any entry starting with `@` sign - metatags, annotations, inline
  ## backend passes.
  if lexer[0..1] == "@@":
    # Inline backend pass
    discard

  elif lexer[0..1] == "@[":
    # Annotation start
    discard

  elif lexer[] == '@' and lexer[+1] in OIdentChars:
    # Metatag start OR random `@` in the text
    lexer.advance()
    let id = lexer.parseIdent(oskMetaTagIdent)
    if lexer[] == '[':
      result = newTree(
        onkMetaTag,
        id,
        newTree(
          onkRawText,
          oskMetaTagArgs,
          lexer.getInsideSimple('[', ']').toSlice(lexer))
      )

    elif lexer[] == '{':
      result = newTree(onkMetaTag, id)
      result.add newEmptyNode(oskMetatagArgs)

    else:
      echo lexer.error("22").msg
      raiseAssert("#[ IMPLEMENT ]#")


    result.add onkStmtList.newTree()
    while lexer[] == '{':
      result[^1].add newTree(
        onkRawText, oskMetatagText, lexer.getInsideBalanced('{', '}'))

  else:
    raise lexer.error("Expected @-entry")


proc parseBracket*(lexer, parseConf; buf: var StrSlice): OrgNode =
  ## Parse any square bracket entry starting at current lexer position, and
  ## return it.

  if not lexer.isBalancedToEOL():
    buf.add lexer.pop()
    return

  # echov "Parse bracket"
  var ahead = lexer
  if lexer[0..1] == "[[":
    # Link start
    result = onkLink.newTree()
    lexer.advance()
    result.add onkRawText.newTree(lexer.getInsideBalanced('[', ']'))
    # echov lexer @? 0 .. 100
    if lexer[] == '[':
      result.add lexer.getInsideBalanced('[', ']').newSublexer().withResIt do:
        # echov it @? 0 .. 100
        parseParagraph(it, parseConf)

    else:
      lexer.advance(2)
      result.add newEmptyNode()

    lexer.advance()

  elif lexer[] == '[':
    # echov lexer @? 0 .. 10
    if lexer[+1 .. +3] == "fn:":
      var notelexer = lexer.getInsideBalanced(
        '[', ']').newSublexer()

      notelexer.advance(3)
      result = onkFootnote.newTree()
      if notelexer[] != ':':
        result.add notelexer.parseIdent()

      else:
        result.add newEmptyNode()

      notelexer.advance()

      result.add notelexer.parseParagraph(parseConf)


    else:
      const start = {'!', '>', '<', '*', '#', '?', '@'} + {'A' .. 'Z'}

      if lexer[+1] in start and
         lexer[+2] in start:
        let body = lexer.getInsideBalanced('[', ']').split('|')
        result = onkBracTag.newTree()
        for slice in body:
          result.add onkBareIdent.newTree(
            slice.toSlice(lexer).strip().toSlice(lexer))

      else:
        let body = lexer.getInsideBalanced('[', ']')
        result = onkTimeStamp.newTree(body)




proc parseMacro*(lexer, parseConf): OrgNode =
  lexer.skipExpected("{{")
  result = onkMacro.newTree(
    onkRawText.newTree(
      lexer.getInsideBalanced('{', '}')))

  lexer.skipExpected("}}")


proc parseOptMacro*(lexer, parseConf): OrgNode =
  case lexer.nextSet({'{'}, OBareIdentChars - {'{'}):
    of 0:
      discard lexer.getSkipUntil({'{'})
      if lexer["{{{"]:
        return onkResult.newTree(lexer.parseMacro(parseConf))

      else:
        return newEmptyNode()

    of 1:
      return newEmptyNode()


proc parseSrcInline*(lexer, parseConf): OrgNode =
  assert lexer["src_"]
  lexer.advance(4)
  result = onkSrcCode.newTree()
  result.add lexer.parseIdent()
  case lexer[]:
    of '[':
      result.add onkRawText.newTree(lexer.getInsideBalanced('[', ']'))
      result.add onkRawText.newTree(lexer.getInsideBalanced('{', '}'))

    of '{':
      result.add newEmptyNode()
      result.add onkRawText.newTree(lexer.getInsideBalanced('{', '}'))

    else:
      raiseAssert("#[ IMPLEMENT ]#")


  lexer.skip()
  result.add parseOptMacro(lexer, parseConf)

proc parseCallInline*(lexer, parseConf): OrgNode =
  assert lexer["call_"]
  lexer.advance(5)
  result = onkCallCode.newTree()
  result.add lexer.parseIdent()
  case lexer[]:
    of '[':
      result.add lexer.getInsideBalanced('[', ']').newSublexer().withResIt do:
        parseCmdArguments(it, parseConf)

      lexer.skip()
      result.add onkRawText.newTree(
        lexer.getInsideBalanced('(', ')'))

    of '(':
      result.add newEmptyNode()
      lexer.skip()
      result.add onkRawText.newTree(lexer.getInsideBalanced('(', ')'))

    else:
      raiseAssert("#[ IMPLEMENT ]#")

  lexer.skip()
  if lexer[] == '[':
    result.add lexer.getInsideBalanced('[', ']').newSublexer().withResIt do:
      parseCmdArguments(it, parseConf)

  else:
    result.add newEmptyNode()

  lexer.skip()
  result.add parseOptMacro(lexer, parseConf)


proc parseHashTag*(lexer, parseConf): OrgNode =
  assert lexer[] == '#'
  lexer.advance()

  proc aux(lexer, parseConf): OrgNode =
    result = onkHashTag.newTree()
    # `#tag`
    result.add lexer.parseIdent()

    # `#tag##[sub1, sub2]`
    if lexer[0 .. 2] == "##[":
      lexer.advance(3)

      while lexer[] != ']':
        # TODO on broken tags this would cause compilation errors and/or
        # whole text getting dragged into single tag body.
        result.add aux(lexer, parseConf)
        lexer.skip()
        if lexer[] != ']':
          lexer.skipExpected(",")
          lexer.skip()

      lexer.advance()

    # `#tag##sub`
    elif lexer[0 .. 1] == "##":
      lexer.advance(2)
      result.add aux(lexer, parseConf)



  return aux(lexer, parseConf)

proc parseInlineMath*(lexer, parseConf): OrgNode =
  ## Parse inline math expression, starting with any of `$`, `$$`, `\(`,
  ## and `\[`.

  assert lexer[] == '$'
  lexer.advance()
  result = onkMath.newTree(lexer.getSkipUntil({'$'}).toSlice(lexer))
  lexer.advance()

proc splitTextbuf*(
  lexer; buf: var StrSlice, dropEmpty: bool = true): seq[OrgNode] =

  func canAdd(slice: StrSlice): bool =
    not (dropEmpty and slice.allIt(it in OWhitespace))

  var text = lexer.initEmptyStrRanges().toSlice(lexer)
  var bigIdent = lexer.initEmptyStrRanges().toSlice(lexer)
  for i in indices(buf):
    let changeRegion =
      # Started whitespace region, flushing buffer
      (
        absAt(buf, i) in Whitespace and
        text.len > 0 and
        text.lastChar() notin Whitespace
      ) or
      # Finished whitespace region
      (
        absAt(buf, i) notin Whitespace and
        text.len > 0 and
        text.lastChar() in Whitespace
      )

    if changeRegion or (i == high(buf)):
      # Finished input buffer or found region change
      if i == high(buf) and not changeRegion:
        # Found last character.
        text.add i

      if (text[0] in OBigIdentChars or bigIdent.len > 0) and
        text.allOfIt(it in OBigIdentChars + OWhitespace):

        for idx in indices(text):
          bigIdent.add idx

        if i == high(buf):
          result.add onkBigIdent.newTree(bigIdent)

      else:
        if bigIdent.len > 0:
          var resIdx = toSeq(indices(bigIdent))
          var trailIdx: seq[int]

          for idx in rindices(bigIdent):
            if bigIdent.absAt(idx) in OWhitespace:
              trailIdx.add resIdx.pop

            else:
              break

          var res: StrRanges
          for idx in resIdx:
            res.add idx

          var trail: StrRanges
          for idx in reversed(trailIdx):
            trail.add idx

          if canAdd(res.toSlice(lexer)):
            result.add onkBigIdent.newTree(oskBigWord, res.toSlice(lexer))

          block:
            let trail = trail.toSlice(lexer)
            if trailIdx.len > 0 and canAdd(trail):
              result.add newTree(onkWord, classifyWord($trail), trail)


        bigIdent.ranges = @[]

        # if dropEmpty and text.allIt(it in OWhitespace):
        #   discard

        if canAdd(text):
          result.add newTree(onkWord, classifyWord($text), text)

      text = initStrRanges(i, i).toSlice(lexer)

      if i == high(buf) and changeRegion and canAdd(text):
        result.add newTree(onkWord, classifyWord($text), text)

    else:
      text.add i

proc getLastLevel(node: var OrgNode, level: int): var OrgNode =
  case level:
    of 0: return node
    of 1: return node[^1]
    of 2: return node[^1][^1]
    of 3: return node[^1][^1][^1]
    else: return getLastLevel(node, level - 4)

proc getLastLevel(node: OrgNode, level: int): OrgNode =
  case level:
    of 0: node
    of 1: node[^1]
    else: getLastLevel(node, level - 2)

proc parseSlashEntry*(lexer, parseConf; buf: var StrSlice): OrgNode =
  assert lexer[] == '\\'
  if lexer[+1] in OIdentStartChars:
    var ahead = lexer
    ahead.advance()
    if ahead.allUntil(OIdentChars, OWhitespace + {'{', OEndOfFile}):
      lexer.advance()
      result = onkSymbol.newTree(
        lexer.getSkipWhile(OIdentChars).toSlice(lexer))

      if lexer["{}"]:
        lexer.advance(2)

    else:
      buf.add lexer.pop()
      buf.add lexer.pop()

  else:
    buf.add lexer.pop()
    buf.add lexer.pop()

    # lexer.parseIdent()

proc parseAngleEntry*(lexer, parseConf; buf: var StrSlice): OrgNode =
  if not lexer.isBalancedToEOL():
    buf.add lexer.pop()

  else:
    var lexer = lexer.getInsideBalanced('<', '>').newSublexer()
    if lexer[0] == '+' and lexer[^1] == '+':
      lexer.advance()
      var buf = lexer.initEmptyStrRanges()
      while not lexer.atEnd():
        buf.add lexer.pop()

      buf.pop()

      var textlexer = newSublexer(buf.toSlice(lexer))
      result = onkPlaceholder.newTree(
        textlexer.parseParagraph(parseConf))

    elif lexer[0] == '<' and lexer[^1] == '>':
      lexer.advance()
      var buf = lexer.initStrRanges()
      while not lexer.atEnd():
        buf.add lexer.pop()

      buf.pop()

      result = onkRadioTarget.newTree(
        onkRawText.newTree(buf.toSlice(lexer)))

    else:
      result = onkPlaceholder.newTree(lexer.parseParagraph(parseConf))






proc parseText*(lexer, parseConf): seq[OrgNode] =
  # Text parsing is implemented using non-recusive descent parser that
  # maintains stack explicitly (instead of constructing it via function
  # calls). This is made in order to provide support for stack
  # introspection at any given moment of parsing, and perform context-aware
  # decisions. Input lexer is parsed *until the end* - e.g you need to
  # always pass sublexer.

  # TODO implement support for additional formatting options, delimited
  # pairs, and punctuation. `<placeholder>`, `(structured-punctuation)`.

  # TODO parse big idents - note that things like `MUST NOT`, `SHALL NOT`
  # need to be parsed as single node.
  var stack: seq[seq[tuple[pending: bool,
                           node: OrgNode]]]


  template getLayerOpen(ch: string): int =
    var layerOpen = -1
    for idx, layer in pairs(stack):
      if layer.len > 0 and
         layer[^1].pending and
         layer[^1].node.getStr() == ch
        :
        layerOpen = idx + 1

    layerOpen


  template closeAllWith(inLayerOpen: int, ch: string): untyped =
    # Force close all layers of parse stack, by moving nodes from several
    # layers into subnodes. This is used for explicitly handling closing
    # delimtiers.
    let layerOpen: int = inLayerOpen
    let foldTimes: int = stack.len - layerOpen
    var nodes: seq[OrgNode]
    for _ in 0 ..< foldTimes:
      nodes.add reversed(stack.pop.mapIt(it.node))

    for node in reversed(nodes):
      if node.kind == onkMarkup and node.len == 0:
        # TODO convert markup node not `Word` and set correc positional
        # information.
        stack[^1][^1].node.add node

      else:
        stack[^1][^1].node.add node

    stack[^1][^1].pending = false


  template closeWith(ch: string): untyped =
    # Close last pending node in stack is there is any, otherwise move
    # current layer not lower one. Used for handling closing buffer nodes
    # /or/ delimiters. Cannot fold multiple layers of stack - only change
    # `pending` tag if needed.
    let layer = stack.pop
    if (stack.len > 0 and stack.last.len > 0 and stack.last2.pending):
      stack.last2.pending = false
      stack.last2.node.add layer.mapIt(it.node)

    elif stack.len == 0:
      stack.add @[layer]

    else:
      stack.last.add layer

  template pushWith(newPending: bool, node: OrgNode): untyped =
    # Add new node to parse stack. If last-last one (last layer, last node
    # in layer) is pending opening, add new layer, otherwise push to the
    # same layer. All pending nodes will be closed in `closeWith`.
    if (stack.last.len > 0 and stack.last2.pending):
      stack.add @[@[(newPending, node)]]

    else:
      stack.last.add (newPending, node)

  var inVerbatim = false
  # FIXME account for different kinds of verbatim formatting - current
  # implementation will trigger no-verbatim mode for closing `~` after
  # opening `=`

  template pushBuf(): untyped =
    # If buffer is non-empty push it as new word. Most of the logic in this
    # template is for dealing with whitespaces in buffers and separating
    # them into smaller things. For example `"buffer with space"` should be
    # handled as five different `Word`, instead of a single one.

    # Buffer is pushed before parsing each inline entry such as `$math$`,
    # `#tags` etc.
    if len(buf) > 0 and inVerbatim:
      pushWith(false, onkRawText.newTree(buf))
      buf = lexer.initEmptyStrRanges().toSlice(lexer)

    elif len(buf) > 0:
      for node in lexer.splitTextBuf(buf, parseConf.dropEmptyWords):
        pushWith(false, node)


      buf = lexer.initEmptyStrRanges().toSlice(lexer)


  stack.add @[]

  var buf = lexer.initEmptyStrRanges().toSlice(lexer)

  while lexer[] != OEndOfFile:
    # More sophisticated heuristics should be used to detect edge cases
    # like `~/me~`, `*sentence*.` and others. Since particular details are
    # not fully fleshed out I will leave it as it is now, and concentrate
    # on other parts of the document.
    # echov lexer @? 0 .. 5

    const markChars = OMarkupChars + {'\'', '"'} +
      OPunctOpenChars + OPunctCloseChars - {'[', ']', '<', '>'}

    case lexer[]:
      of markChars:
        var ch: string
        var hadPop = false
        if not inVerbatim and lexer.isOpenAt(
          ch, markChars + OPunctOpenChars):
          # Start of the regular, constrained markup section.
          # Unconditinally push new layer.
          pushBuf()
          pushWith(true, newTree(onkMarkup, classifyMarkKind(ch[0]), $ch))

          if ch[0] in OVerbatimChars:
            inVerbatim = true

        elif lexer.isCloseAt(ch, markChars + OPunctCloseChars):
          # End of regular constrained section, unconditionally close
          # current layer, possibly with warnings for things like
          # `*/not-fully-italic*`
          if not inVerbatim or (inVerbatim and ch[0] in OVerbatimChars):
            pushBuf()
            let layer = getLayerOpen($ch[0].matchingPair())
            if layer != -1:
              closeAllWith(layer, $ch[0].matchingPair())
              inVerbatim = false

            else:
              buf.add lexer.pop()

          else:
            hadPop = true
            buf.add lexer.pop()

        elif lexer.isToggleAt(ch):
          # Detected unconstrained formatting block, will handle it
          # regardless.
          let layerOpen = getLayerOpen(ch)
          let isOpening = layerOpen == -1


          if ch[0] in OVerbatimChars:
            # Has matching unconstrained section open at one of the previous layers
            pushBuf()
            if isOpening:
              # Open new verbatim section
              inVerbatim = true
              pushWith(true, newTree(onkMarkup, classifyMarkKind(ch[0]), ch))

            else:
              inVerbatim = false
              closeAllWith(layerOpen, ch)

            lexer.advance()

          elif inVerbatim:
            hadPop = true
            buf.add lexer.pop()


          else:
            if isOpening:
              # Push new markup opening, no verbatim currently active
              pushWith(true, newTree(onkMarkup, classifyMarkKind(ch[0]), ch))
              lexer.advance()

            else:
              # Push new markup opening, no verbatim currently active
              closeAllWith(layerOpen, ch)
              lexer.advance()

        else:
          hadPop = true
          buf.add lexer.pop()

        if not hadPop:
          lexer.advance()


      of '$':
        if lexer[-1] in OEmptyChars:
          pushBuf()
          pushWith(false, parseInlineMath(lexer, parseConf))

        else:
          raiseAssert("#[ IMPLEMENT ]#")

      of '@':
        if lexer[-1] in OEmptyChars:
          pushBuf()
          pushWith(false, parseAtEntry(lexer, parseConf))

        else:
          buf.add lexer.pop

      of '#':
        if lexer[-1] in OEmptyChars and
           lexer[+1] == '[' and
           not inVerbatim:

          pushBuf()

          lexer.advance()
          pushWith(false, onkComment.newTree(
            lexer.getInsideBalanced('[', ']'),
          ))

          lexer.skipExpected("#")

        elif lexer[-1] in OEmptyChars and
             lexer[+1] in OWordChars and
             not inVerbatim:

          pushBuf()
          pushWith(false, parseHashTag(lexer, parseConf))

        else:
          buf.add lexer.pop

      of '[':
        if lexer[-1] in OEmptyChars and
           not inVerbatim:
          pushBuf()
          let node = parseBracket(lexer, parseConf, buf)
          if not node.isNil:
            pushWith(false, node)

        else:
          buf.add lexer.pop

      of '\\':
        let node = lexer.parseSlashEntry(parseConf, buf)
        if not node.isNil:
          pushWith(false, node)

      of '<':
        if inVerbatim:
          buf.add lexer.pop()

        else:
          let node = lexer.parseAngleEntry(parseConf, buf)
          if not node.isNil:
            pushWith(false, node)

      elif lexer["src_"]:
        pushWith(false, lexer.parseSrcInline(parseConf))

      elif lexer["call_"]:
        pushWith(false, lexer.parseCallInline(parseConf))

      else:
        buf.add lexer.pop

  pushBuf()
  while stack.len > 1:
    closeWith("")

  return stack[0].mapIt(it.node)



proc parseParagraph*(
    lexer, parseConf; subKind: OrgNodeSubKind = oskNone): OrgNode =
  result = onkParagraph.newTree(lexer.parseText(parseConf))
  result.subKind = subKind


proc parseOrgCookie*(lexer, parseConf): OrgNode =
  if lexer[] == '[':
    result = onkUrgencyStatus.newTree(
      getInsideSimple(lexer, '[', ']').toSlice(lexer))

  else:
    result = newEmptyNode()



proc parseList*(lexer, parseConf): OrgNode =
  # This is a horrible nest of vaguely justified checks, paired with
  # multiple assumptions on input validty, but general outline of
  # implementation is as follows:
  #
  # - in loop,determine particular type of current list start, get
  #   bullet chars.
  # - Create sublexer for whole item
  # - Partiallt parse item - counter, checkbox
  # - Found extent of list 'header', positions of completion cookies if any
  # - Create separate header sublexer, determine ranges for tag (for property list),
  #   header text and completion ranges.
  # - Create `tag`, `header` and `completion` subnodes from ranges parsed in
  #   previous step.
  #
  # Such convoluted implementation is necessary because positions of `::`
  # and `[/]` (especially `::`) are not well-defined. Tag separator might
  # occur anywhere in the list item header and completion cookie is a last
  # element in list /if/ it is present. Approach like this (rough scan
  # forward, then go back to scanned range, and run more intricate scan but
  # without worrying about start/end correctness) should allow (in theory)
  # for more sophisticated
  result = onkList.newTree()


  while lexer.listStartChar() != OEndOfFile:
    let start: char = lexer.listStartChar()
    let endset: set[char] = tern(start in ONumberedListChars, {'.', ')'}, {})
    let skipset: set[char] =
      case start:
        of '0': {'0' .. '9'}
        of 'a': {'a' .. 'z'}
        of 'A': {'A' .. 'Z'}
        of '-': {'-'}
        of '+': {'+'}
        of '*': {'*'}
        else: raiseAssert("#[ IMPLEMENT ]#")

    var bullet: StrRanges
    while lexer[] in skipset + endset:
      bullet.add lexer.pop()

    lexer.skip()
    var itemLexer = lexer.indentedSublexer(
      2,
      keepNewlines = true,
      fromInline = true,
      requireContinuation = false
    )


    let bulletSlice = $bullet.toSlice(lexer)
    let bulletClass =
      case bulletSlice:
        of "-": oskDashBullet
        of "+": oskPlusBullet
        of "*": oskStarBullet
        elif bulletSlice[0] in {'0' .. '9'}: oskNumBullet
        elif bulletSlice[0 .. ^2] in {'a' .. 'z', 'A' .. 'Z'}: oskLetterBullet
        elif bulletSlice[0 .. ^2] in {'I', 'M', 'x', 'V', 'v', 'i', 'm', 'x'}:
          oskRomanBullet

        else:
          oskNone



    var item = onkListItem.newTree(
      bulletClass,
      onkRawText.newTree(bullet.toSlice(lexer)))

    itemLexer.skip()
    # Parse counter-set and checkbox
    if itemLexer[] == '[':
      if itemLexer[+1] == '@':
        item.add onkCounter.newTree(
          itemLexer.getInsideSimple('[', ']').toSlice(lexer))

        itemLexer.skip()
        if itemLexer[] == '[':
          item.add onkCheckbox.newTree(
            itemLexer.getInsideSimple('[', ']').toSlice(lexer))

        else:
          item.add newEmptyNode()

      else:
        item.add newEmptyNode()

    else:
      item.add newEmptyNode()
      item.add newEmptyNode()

    # Extract header ranges for list element
    var headerRanges: StrRanges
    while true:
      # Crude heuristics, but it should work for now
      if itemLexer[] in OLineBreaks and itemLexer[+1] notin OWordChars:
        break

      headerRanges.add itemLexer.pop
      while itemLexer[] notin OLineBreaks:
        headerRanges.add itemLexer.pop

    # Create sublexer for header ranges and get subranges for tags and
    # completion cookies.
    var it = headerRanges.toSlice(lexer).newSublexer()
    let tagRanges = it.allRangesTo(
      "::",
      repeatIncluding = true,
      remaining = true # Get all indices in ranges
    )

    let cookieRanges = it.allRangesTo("[", remaining = true)

    var isValidCookie = true
    if cookieRanges.len > 1:
      # If completion cookie has multiple ranges and
      let sl = cookieRanges[^1].toSlice(lexer)
      for idx in rindices(sl):
        if sl.absAt(idx) notin {']', '[', '1' .. '9', '%', '/'}:
          isValidCookie = false
          break

    else:
      isValidCookie = false

    # There is no smart logic behind this wall of conditionals, it is just
    # a reasult of defensive coding against possible edge cases that I
    # managed to come up with.
    if tagRanges.len > 1:
      item.add tagRanges[0].toSlice(lexer).newSublexer().withResIt do:
        it.parseParagraph(parseConf, oskListTagText)

      let paragraph = overlapping(
        @[tagRanges[0], tagRanges[1]], tern(
          isValidCookie, # If completion cookie is present use it
          cookieRanges[^2],
          tagRanges[^1] # Otherwise get everything until the end of header
        )
      )

      if paragraph.len == 0:
        # Degenerate case with tag body being the only part in header. This
        # is a valid syntax, so no error here.
        item.add newEmptyNode()

      else:
        item.add paragraph.toSlice(lexer).newSublexer().withResIt do:
          it.parseParagraph(parseConf, oskListHeaderText)

    elif tagRanges.len == 1:
      item.add newEmptyNode()

      if isValidCookie:
        let overlap = overlapping(
          @[overlapping( # Get range for completion cookie
            @[cookieRanges[^2]], # Cookie will start at `[]` as usual
            cookieRanges[^1],
          )],
          tagRanges[0] # In case of missing `::` tag range will contain all
                       # header, need to exclude ranges for completion
                       # cookie.
        )

        item.add overlap.toSlice(lexer).newSublexer().withResIt do:
          it.parseParagraph(parseConf)

      else:
        item.add tagRanges[0].toSlice(lexer).newSublexer().withResIt do:
          it.parseParagraph(parseConf)


    if isValidCookie:
      item.add overlapping(
        @[cookieRanges[^2]], cookieRanges[^1]
      ).toSlice(lexer).newSublexer.withResIt do:
        onkCompletion.newTree(it.getInsideSimple('[', ']').toSlice(lexer))

    else:
      item.add newEmptyNode()

    item.add itemLexer.parseStmtList(parseConf)
    if item[^1].len == 0:
      item[^1] = newEmptyNode(oskListBodyText)

    else:
      item[^1].subKind = oskListBodyText

    result.add item


  var bullets: set[OrgNodeSubKind]
  var hasDescriptions: bool
  var allDescriptions = true
  for item in result:
    bullets.incl item.subKind
    if item["tag"].kind != onkEmptyNode:
      hasDescriptions = true

    else:
      allDescriptions = false

  if allDescriptions:
    result.subKind = oskFullDescList

  if hasDescriptions:
    result.subKind = oskPartialDescList

  elif bullets <= {oskDashBullet, oskPlusBullet, oskStarBullet}:
    result.subKind = oskUnorderedList

  elif bullets <= {oskNumBullet, oskLetterBullet, oskRomanBullet}:
    result.subKind = oskOrderedList

  else:
    result.subKind = oskMixedList


proc parseSubtree*(lexer, parseConf): OrgNode =
  ## Parse header node.
  ## - NOTE :: Only subtree header is parsed - @ret{["body"]} is
  ##   set to empty node and should be handled externally.
  # NOTE `@ret{["body"]}` should be rendered as `result["body"]`

  result = OrgNode(kind: onkSubtree)

  result.add onkBareIdent.newTree(lexer.getSkipWhile({'*'}).toSlice(lexer))
  lexer.skip()

  if lexer.atBigIdent():
    result.add lexer.parseBigIdent(parseConf, oskTodoIdent)

  else:
    result.add newEmptyNode(oskTodoIdent)

  lexer.skip()

  result.add parseOrgCookie(lexer, parseConf)

  lexer.skip()

  var headerLexer = lexer.indentedSublexer(
    result["prefix"].charLen(),
    keepNewlines = false,
    requireContinuation = true,
    fromInline = true
  )


  var
    tagsElems: seq[int]
    tagsFound = false
    completionElems: seq[int]
    completionFound = false
    headerElems: seq[int]
    allIdx: seq[int] = toSeq(indices(headerLexer.d.buf))


  var pos = allIdx.high
  while pos >= 0:
    if not tagsFound:
      if lexer.absAt(allIdx[pos]) == ':':
        var tagEnded = false
        while not tagEnded:
          dec pos
          while lexer.absAt(allIdx[pos]) notin OWhitespace:
            tagsElems.add allIdx[pos]

            if lexer.absAt(allIdx[pos]) == ':':
              dec pos

            else:
              break

          if lexer.absAt(allIdx[pos]) in OWhitespace:
            tagEnded = true


      tagsFound = true

    elif not completionFound:
      if lexer.absAt(allIdx[pos]) in OWhitespace:
        dec pos

      elif lexer.absAt(allIdx[pos]) == ']':
        var subbuf: seq[int]
        dec pos
        while lexer.absAt(allIdx[pos]) in {'0' .. '9', '/', '%'}:
          subbuf.add allIdx[pos]
          dec pos

        if lexer.absAt(allIdx[pos]) == '[':
          dec pos
          completionElems = subbuf

        else:
          headerElems.add subbuf

        completionFound = true

      else:
        completionFound = true

    else:
      headerElems.add allIdx[pos]
      dec pos

  block: # subtree title
    var headerBuf: StrRanges
    for idx in reversed(headerElems):
      headerBuf.add idx

    result.add headerBuf.toSlice(lexer).newSublexer().withResIt do:
      parseParagraph(it, parseConf)

  block:
    if completionElems.len > 0:
      var completionSlice: StrRanges
      for idx in reversed(completionElems):
        completionSlice.add idx

      result.add onkRawText.newTree(completionSlice.toSlice(lexer))

    else:
      result.add newEmptyNode()


  block:
    if tagsElems.len > 0:
      var tagsBuf = @[lexer.initEmptyStrRanges()]
      for idx in reversed(tagsElems):
        if lexer.absAt(idx) == ':':
          tagsBuf.add lexer.initEmptyStrRanges()

        else:
          tagsBuf[^1].add idx

      result.add onkOrgTag.newTree()
      for buf in tagsBuf:
        if buf.len > 0:
          result[^1].add onkRawText.newTree(oskOrgTagIdent, buf.toSlice(lexer))

    else:
      result.add newEmptyNode()


  lexer.advance()

  var timesLexer = lexer
  timesLexer.skip()
  if timesLexer.atBigIdent():
    var times = newOStmtList()
    while timesLexer.atBigIdent():
      times.add onkSubtreeTimes.newTree()
      times[^1].add timesLexer.parseBigIdent(parseConf)
      timesLexer.skipExpected(":")
      timesLexer.skip()
      if timesLexer["<"]:
        times[^1].add onkTimeStamp.newTree(
          timesLexer.getInsideBalanced('<', '>'))

      elif timesLexer["["]:
        # echov timesLexer @? 0 .. 10
        times[^1].add onkTimeStamp.newTree(
          timesLexer.getInsideBalanced('[', ']'))

      timesLexer.skip()

    result.add times

    lexer.d.bufpos = timesLexer.d.bufpos

  else:
    result.add newEmptyNode()

  lexer.gotoSOL()



  if lexer.lineStartsWith(":"):
    var drawerLexer = lexer.indentedSublexer(
      lexer.getIndent(),
      keepNewlines = true,
      requireContinuation = false,
      fromInline = false
    )

    result.add parseDrawers(drawerLexer, parseConf)

  else:
    result.add newEmptyNode()

  result.add newEmptyNode()

type
  OrgStart* = enum
    otkNone

    otkCommand
    otkBeginCommand
    otkIdent
    otkSubtreeStart
    otkListStart
    otkParagraph
    otkLineComment
    otkDrawer
    otkEof
    otkList


proc detectStart(lexer): OrgStart =
  let ch = lexer[]
  case ch:
    elif ch == '#':
      if lexer["#+begin"]:
        result = otkBeginCommand

      elif lexer["#+"]:
        result = otkCommand

      elif lexer["#["]:
        # Inline comment start
        result = otkParagraph

      elif lexer["# "]:
        # Comment until end of line
        result = otkLineComment

      else:
        # Text startsing with tag
        result = otkParagraph

    elif ch == '*':
      if lexer.column == 0:
        var idx = 0
        while lexer[idx] in {'*'}:
          inc idx

        if lexer[idx] in {' '}:
          # `***** Heading`
          result = otkSubtreeStart

        else:
          # `*First bold*`
          result = otkParagraph

      else:
        result = otkListStart

    elif ch in OListChars:
      if lexer.listStartChar() == OEndOfFile:
        result = otkParagraph

      else:
        result = otkList

    elif ch in OWordChars + {'['}:
      result = otkParagraph

    elif ch == '\n':
      lexer.skip({'\n'})
      return detectStart(lexer)

    elif ch == OEndOfFile:
      result = otkEOF

    elif ch == ':':
      var idx = 0
      while lexer[idx] in OIdentChars:
        inc idx

      if lexer[idx] == ':':
        result = otkDrawer

      else:
        result = otkParagraph

    elif lexer[] in OMarkupChars + {'\\'}:
      result = otkParagraph

    else:
      result = otkParagraph



proc parseStmtList*(lexer, parseConf): OrgNode =
  result = OrgNode(kind: onkStmtList)
  var assocListBuf: seq[OrgNode]

  var headerLevel = 0

  var treeStack: seq[seq[OrgNode]]

  template pushTree(tree) =
    if treeStack.len == 0:
      result.add tree

    else:
      if treeStack[^1][^1]["body"].kind == onkEmptyNode:
        treeStack[^1][^1]["body"] = newOStmtList()

      treeStack[^1][^1]["body"].add tree

  template pushAssoc =
    case assocListBuf.len:
      of 0: discard
      of 1:
        pushTree assocListBuf.pop()

      else:
        pushTree onkAssocStmtList.newTree(assocListBuf)
        assocListBuf = @[]

  while lexer[] != OEndOfFile:
    let kind = lexer.detectStart()
    case kind:
      of otkBeginCommand:
        let cmd = parseMultilineCommand(lexer, parseConf)
        if assocListBuf.len > 0:
          pushTree onkAssocStmtList.newTree(
            onkStmtList.newTree(assocListBuf),
            cmd
          )

          assocListBuf = @[]

        else:
          pushTree cmd

      of otkCommand:
        assocListBuf.add parseCommand(lexer, parseConf)

      of otkSubtreeStart:
        let tree = parseSubtree(lexer, parseConf)
        let newLevel = tree["prefix"].charlen
        if newLevel > headerLevel:
          headerLevel = newLevel
          treeStack.add @[tree]

        elif newLevel == headerLevel:
          treeStack[^1].add tree

        else:
          let level: seq[OrgNode] = treeStack.pop
          treeStack[^1][^1]["body"].add level
          treeStack.add @[tree]


      of otkParagraph:
        var paragraphLexer = lexer.indentedSublexer(
          0,
          keepNewlines = false,
          requireContinuation = false,
          fromInline = false,
          atEnd = (
            proc(lexer: var Lexer): bool =
              # Correct for adjacent regular text block with list right after
              result = lexer[0..1] in ["- ", "+ ", "* "]
          )

        )

        pushTree newTree(
          onkParagraph, oskStandaloneText, paragraphLexer.parseText(parseConf))

      of otkEOF:
        break

      of otkDrawer:
        pushTree parseDrawer(lexer, parseConf)

      of otkList:
        pushTree parseList(lexer, parseConf)

      else:
        raiseAssert(&"#[ IMPLEMENT for kind {kind} {instantiationInfo()} ]#")

    # echov lexer[]
    while lexer[] in Newlines:
      if lexer[] in {'\n'}:
        pushAssoc()

      lexer.advance()

  pushAssoc()

  while treeStack.len > 1:
    let level = treeStack.pop()
    treeStack[^1][^1]["body"].add level

  if treeStack.len > 0:
    result.add treeStack.pop()


const defaultParseConf*: ParseConf = ParseConf(
  dropEmptyWords: true
)

proc parseOrg*(str: string, parseConf: ParseConf = defaultParseConf): OrgNode =
  startHax()
  var lexer = newLexer(newStrBufSlice(str))

  try:
    result = parseStmtList(lexer, parseConf)

  except CodeError as err:
    pprintErr()
