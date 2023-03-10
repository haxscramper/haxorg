import std/[unittest, strutils, sequtils, macros]
import haxorg, haxorg/[
  lexer, parser, ast, buf, exporter, common, semorg,
  exporter_tex,
  exporter_html,
  exporter_purepdf,
  exporter_md,
  coderun_nim
]

import hmisc/hdebug_misc
import hmisc/other/[oswrap, hshell]
import hmisc/hexceptions
import fusion/matching


suite "Sublexer":
  proc lex(str: string): Lexer = newLexer(newStrBufSlice(str))

  test "New lexer advance":
    var lexer = lex "12345"
    check lexer[] == '1'
    check lexer.pop() == 0
    check lexer[] == '2'

  test "Simple sublexer range":
    var lexer = lex "[123][456]"
    #                0123456789

    var sub1 = lexer.newSublexer(@[(0, 3)])
    check sub1[] == '['


    var sub2 = lexer.newSublexer(@[(6, 8)])
    check sub2[] == '4'
    sub2.advance()
    check sub2[] == '5'
    check sub2.pop() == 7

    var sub3 = lexer.newSublexer(@[(0, 1), (3, 4)])
    check toSeq(sub3) == "[13]"

  test "Cut indented part":
    let str = """
  ABC
  DEF
GHK
"""

    var lexer = lex str
    var sub = lexer.indentedSublexer(
      2,
      requireContinuation = false,
      fromInline = false,
      keepNewlines = false
    )

    check toSeq(sub) == "ABCDEF"

  test "Block until":
    let str = """
  #+row:

    123
#+end
"""
    echo toSeq(pairs(str)).join("\n")


    var lexer = lex str

    var sub = lexer.blockSublexer("#+end")
    check toSeq(sub) == toSeq("#+row:\n\n  123\n")

func s(node: OrgNode): string = node.strVal()

proc parseOrg2(str: string): OrgNode = parseOrg(str)[0][0]
proc parseOrg1(str: string): OrgNode = parseOrg(str)[0]

suite "Example document parser":
  test "Simple markup elements":
    for markup in "/_+*":
      let node = parseOrg(markup & "hello" & markup)
      # echo node.treeRepr()
      node[0][0].assertMatch:
        Markup(strVal: == $markup, [Word(strVal: "hello")])

    parseOrg("*/bold/*")[0][0].assertMatch:
      Markup(strVal: "*"):
        Markup(strVal: "/"):
          Word(strVal: "bold")

  test "Verbatim elements":
    Markup(strVal: "~", [RawText(strVal: "HELLO")]) := parseOrg("~HELLO~")[0][0]

  test "Big idents":
    BigIdent(strVal: "MUST NOT") := parseOrg("MUST NOT")[0][0]
    BigIdent(strVal: "OPTIONAL") := parseOrg("OPTIONAL")[0][0]

  test "Bracket tags":
    let node = parseOrg("[!!!|>>>] User MUST NOT trigger bugs")
    node[0].assertMatch:
      Paragraph:
        BracTag:
          BareIdent(strVal: "!!!")
          BareIdent(strVal: ">>>")
        Word(strVal: "User")
        BigIdent(strVal: "MUST NOT")
        Word(strVal: "trigger")
        Word(strVal: "bugs")

  test "Links":
    RadioTarget[RawText(s: "radio target")] := parseOrg2("<<radio target>>")
    parseOrg2("[[LINK][description]]").assertMatch:
      Link:
        RawText(s: "LINK")
        Paragraph[Word(s: "description")]

    parseOrg2("[[LINK]]").assertMatch:
      Link[RawText(s: "LINK"), EmptyNode()]

    parseOrg2("[[BROKEN]").assertMatch:
      Word(s: "[[BROKEN]")

    let node = parseOrg2("[[BROKEN]")

  test "Lists":
    echo treeRepr parseOrg("""
Documentation for hhh
- NOTE :: prints out "123"
""")

  test "Inline source code elements":
    parseOrg2("src_sh[:eval false]{ls -l} {{{\"hello\"}}}").assertMatch:
      SrcCode:
        Ident(s: "sh")
        RawText(s: ":eval false")
        RawText(s: "ls -l")
        Result:
          Macro:
            RawText(s: "\"hello\"")

    let node = parseOrg2("src_sh[:eval false]{ls -l} {{{\"hello\"}}}")

  test "Edge cases for inline markup":
    parseOrg2("=tree-sitter=-based").assertMatch:
      Markup(str: "="):
        RawText(s: "tree-sitter")
      Word(s: "-based")

    parseOrg2("(~mkdir~)").assertMatch:
      Markup(str: "("):
        Markup(str: "~"):
          RawText(s: "mkdir")

  test "shit":
    if false:
      let tree = parseOrg """
#+TITLE: @date:2020-12-23; @time:11:24;

* TODO    [#A] Long heading **un``con``str**ained \
  123
   :properties:
   :created:  <2020-12-24 Thu 10:01>
   :end:

Regular *text*

#+begin-code: nim
123
  5678
#+end-code
"""



    if false:
      let tree = parseOrg("src_sh[:eval false]{ls -l} {{{\"hello\"}}}")

    if false:
      let tree = parseOrg("""
#+begin_src ipython :results output verbatim :noweb yes
print("| ?????? | ?????? | ?????? | ?????????????? |")
# <<hello>>
# <<world(arg=12)>>
""")

    if false:
      let tree = parseOrg("""
#+begin_src ipython :snippet yes
$1
${1:$(make-string (string-width yas-text) ?\=)}
#+end_src
""")



    if false:
      let tree = parseOrg("""
- [@cnt] [X] tag ~:::~ world
  Heeader :: :: Body [1/2]
  + zz
- @arg{input} :: Input argument
""")

# Regulartext
# - aaaa :: bbb
# - aaaa :: bbb


    if false:
      let tree = parseOrg(
        "call_hello[-r -n :eval false :var a=2](val=12)[:post args]")

    if false: discard parseOrg("* __un__**co``n``str**a")

    if false: discard parseOrg("*/bold*")
    # if false: discard
    if false: discard parseOrg("~*/bold MUST NOT/*~")
    if false: discard parseOrg("*/bold MUST NOT/*")
    if false: discard parseOrg("user MUST NOT")
    if false: discard parseOrg("~~*/bold, but in verbatim/*~~")
    if false: discard parseOrg(r"\alpha{}hello")
    if false: discard parseOrg("~[[LINK][DESCRIPTION]]~")
    if false: discard parseOrg("[[Link]Broken~")
    if false: echo treeRepr(parseOrg2("Hello* world"))
    if false:
      echo treeRepr(parseOrg("""
** PARTIALLY ???????????? ?????????????? ???????????????????? ?????????????????? [0/2]  :world:hello:
   CLOSED: [2021-01-03 Sun 20:12] DEADLINE: <2021-01-23 Sat>
   :PROPERTIES:
   :CREATED:  <2021-01-03 Sun 20:11>
   :END:
   :LOGBOOK:
   - State "PARTIALLY"  from "IN_PROGRESS" [2021-01-03 Sun 20:12] \\
     Some fixups
   - Refiled on [2020-05-02 Sat 14:40] from [[id:e2de69d4-4073-477f-af6b-cc2cd8d5a122][Quick latex input [17/26]]]
   :END:
"""))

    startHax()
    if true:
      echo treeRepr parseOrg("""
#+name: hello
#+name: hello

#+name: hello
#+BEGIN_SRC nim

#+END_SRC

#+name: hello
#+name: hello
""")

    if false:
      echo treeRepr parseOrg("""
#+BEGIN_SRC m4circuit :file parallel-operator.png
capacitor(); llabel(,1/pC_1,); resistor(,,E); llabel(,R_3,);
parallel_(
  `resistor(,,E);llabel(,R_2,);',
  `inductor;llabel(,pL_1,);resistor(,,E);llabel(,R_4,);'
);
line;
#+END_SRC

#+attr_latex: :wdith 10cm
#+results[fa0e568c6ed7cd4ae7a41732ab80fde0e5005972]:
[[file:parallel-operator.png]]
""")

    if false: discard parseOrg("Joe said \"Hello /world/\".")
    if false: discard parseOrg("Most (optional) arguments")
    if false: discard parseOrg("[fn:NAME: a definition with *bold*]")
    if false: discard parseOrg("``#+name``'d")
    if false: discard parseOrg("""
[FEATURE] changed something

- ADDED ::
  - <++> ~<++>~
  - <<radio link>> ~<<verbatim>>~
  - <link to documentation> ~<verbatim>~
""")
    if false:
      discard parseOrg("""
IF zzz THEN
  do something
ENDIF
EXIT
""")
    # if true: discard parseOrg("__//un zz__**con``N``sss**")


    if false:
      let tree = parseOrg("* *bold*")

    if false:
      let tree = parseOrg(
        r"???????? ???????? $\phi = \atan \frac{X}{R}$ _??????????????????_. ?????? /????????????????????????/")

    if false:
      let tree = parseOrg("""
#[ inline comment ]#
Inline #[comment]# in text
#tag##[subtag##sub2##[sub3],sub4,subg5##sub6]
@meta{tag}
@meta2{tag}
@meta3[arg]{tag}{{ arg2 }}
""")


    if false:
      let tree = parseOrg("""
#+begin-table
  #+row:
    # One step above regular table - you can put comments on row content
    | col1 | col2 | col3 |
  #+row: :color red # Putting comments on rows is possible now
    | column1 # This allows you to put comments
    | column2 # Imagine writing some non-trivial formula and then commenting
    | column3 # On parts for it
    | column4 # Though in this case comment probably is a part of cell body

    # Yes, you loose some readability wrt. to this thing being table-like, but
    # there are always tradeoffs.
  #+row:
    #+cell:

      Longest column format, but the most flexible one. You can put
      anything in the column, including subtables, code blocks and more.

    #+cell: :name named-cell

      Another advantage - naming and custom arguments are possible too.
      Putting cell sizes (multi-col/row), naming, specialized formatting
      commands and much more.

#+end-table
""")

suite "Semorg":
  test "From document":
    var conf = defaultParseConf
    conf.dropEmptyWords = false
    let node = parseOrg("""
* Sessions
  :properties:
  :header-args:nim: :session session-1
  :end:

#+BEGIN_SRC nim :exports both output
proc printArg(arg: int) =
  echo arg
#+END_SRC

#+BEGIN_SRC nim :exports both output drawer
printArg(1230)
#+END_SRC

[[code:printArg(int).arg]]

- Organize all :: installation options /into/ table or something, instead of
  this hand-made monster with barely formatted links
- More informative post-installation *message* for modification of the
  @env{PATH}.
""", conf)



    try:
      var semNode = node.toSemOrgDocument()
      echo semNode.treeRepr()
      case 3:
        of 0:
          defaultExportDispatcher.exportTo(
            semNode, AbsFile("/tmp/doc.html"))

          execShell(shCmd(tidy, -i, "/tmp/doc.html"), doRaise = false)

        of 1:
          defaultExportDispatcher.exportTo(semNode, AbsFile("/tmp/doc.pdf"))

        of 2:
          defaultExportDispatcher.exportUsing(
            "pure-pdf", semNode, AbsFile("/tmp/doc.pdf"))

        of 3:
          defaultExportDispatcher.exportTo(
            semNode, AbsFile("/tmp/doc.md"))

        else:
          discard

    except:
      pprintErr()
      fail()

  test "zz":
    echo treeRepr(parseOrg("Document"))

import haxorg/spellcheck

suite "Spellchecker":
  test "Hunspell":
    var conf = defaultParseConf
    conf.dropEmptyWords = false
    let str = """
* Header text with sme mistkes

Regular pargraph wth some mistakes
"""

    let node = parseOrg(str, conf)

    checkSpelling(node, str)
