(use-modules (oop goops))
(use-modules (srfi srfi-1))
(use-modules (language tree-il))
(use-modules (ice-9 pretty-print))
(use-modules (ice-9 format))

(define (is-positional field)
  (eq? (length field) 1))

(define (get-positional-defs field-defs)
  (remove (lambda (field) (not (is-positional field))) field-defs))

(define (get-optional-defs field-defs)
  (remove (lambda (field) (is-positional field)) field-defs))

(define (get-positional-fields field-defs)
  (map (lambda (field-def)
         (let* ((field-name (car field-def))
                (field-kwd (symbol->keyword field-name)))
           `(,field-name #:init-keyword ,field-kwd)))
       (get-positional-defs field-defs)))

(define (get-optional-fields field-defs)
  (map (lambda (field-def)
         (let* ((field-name (car field-def))
                (field-kwd (symbol->keyword field-name))
                (default-value (cdr field-def)))
           `(,field-name
             #:init-keyword ,field-kwd
             #:init-form ,default-value)))
       (get-optional-defs field-defs)))

(define-macro (simple-define-type type-name make-fn-name . field-defs)
  (let* ((positional-fields (get-positional-fields field-defs))
         (optional-fields (get-optional-fields field-defs))
         (positional-args
          (map (lambda (field-def) (car field-def))
               (get-positional-defs field-defs)))
         (pass-args
          (fold
           (lambda (prev next) (append prev next))
           (list)
           (map (lambda (field-def)
                  (list (symbol->keyword (car field-def)) (car field-def)))
                field-defs)))
         (optional-args
          (map (lambda (field-def) (cons (car field-def) (cdr field-def)))
               (get-optional-defs field-defs))))
    `(begin
       (define-class ,type-name ()
         ,@positional-fields
         ,@optional-fields)
       (define* (,make-fn-name ,@positional-args #:key ,@optional-args)
         (make ,type-name ,@pass-args)))))

;; (pretty-print
;;  (tree-il->scheme
;;   (macroexpand
;;    '()
;;    )))

(simple-define-type <doc> d:doc (brief) (full ""))
(simple-define-type <enum-field> d:efield (name) (doc) (value ""))
(simple-define-type <enum> d:enum (name) (doc) (items))
(simple-define-type <field> d:field (type) (name) (doc) (value "") (kind "Field"))
(simple-define-type <ident> d:ident (type) (name) (value ""))

(simple-define-type
 <type> d:struct
 (name)
 (doc)
 (fields (list))
 (nested (list))
 (methods (list))
 (bases (list))
 (concreteKind #t)
 (kind "Struct"))

(simple-define-type
 <group> d:group
 (entries)
 (enumName "")
 (iteratorMacroName "")
 (variantName #f)
 (kind "Group"))

(simple-define-type
 <method> d:method
 (result)
 (name)
 (doc)
 (arguments (list))
 (isConst #f)
 (isVirtual #f)
 (kind "Method"))


(define (t:int) "int")
(define (t:str) "QString")
(define (t:vec arg) (format #f "Vec<~a>" arg))
(define* (t:id #:optional target)
  (if target (format #f "SemIdT<~a>" target) "SemId"))
(define* (t:opt arg) (format #f "Opt<~a>" arg))
(define* (t:osk) "OrgSemKind")
(define* (t:cr arg) (format #f "CR<~a>" arg))
(define* (t:var #:rest args) (format #f "Variant<~a>" (string-join args ", ")))

(define* (d:id-field id name doc)
  (d:field (t:id id) name doc #:value (format #f "SemIdT<~a>::Nil()" id)))

(define* (d:vec-field type name doc)
  (d:field (t:vec type) name doc #:value "{}"))

(define* (d:opt-field type name doc)
  (d:field (t:opt type) name doc #:value "std::nullopt"))

(d:group
 (list
  (d:struct 'Org
            (d:doc "Base class for org mode types")
            #:methods
            (list
             (d:method (t:osk) "getKind"
                       (d:doc "Get current kind of the sem org node")
                       #:isVirtual #t #:isConst #t)
             (d:method "OrgNodeKind" "getOriginalKind"
                       (d:doc "Get original kind of the parser org node")
                       #:isConst #t))
            #:fields
            (list
             (d:field (t:opt "LineCol") "loc"
                      (d:doc "Original node location") #:value "std::nullopt"))
            #:concreteKind #f)
  (d:struct 'Stmt
            (d:doc
             "Base class for all document-level entries. Note that some node kinds
might also have inline entries (examples include links, source code blocks,
call blocks)")
            #:bases '(Org) #:concreteKind #f)
  (d:struct 'Inline
            (d:doc "Base class for all inline elements")
            #:bases '(Org) #:concreteKind #f)
  (d:struct 'StmtList
            (d:doc "Zero or more statement nodes")
            #:bases '(Org))
  (d:struct 'Empty (d:doc "Node without content") #:bases '(Org))
  (d:struct 'Row (d:doc "Table row") #:bases '(Org))
  (d:struct 'Table (d:doc "Table")
            #:bases '(Stmt)
            #:fields
            (list
             (d:field (t:vec (t:id "Row")) "rows"
                      (d:doc "List of rows for the table") #:value "{}")))
  (d:struct 'HashTag (d:doc "Single or nested inline hash-tag")
            #:bases '(Inline)
            #:fields
            (list
             (d:field "Str" "head" (d:doc "Main part of the tag"))
             (d:field (t:vec (t:id "HashTag")) "subtags"
                      (d:doc "List of nested tags") #:value "{}"))
            #:methods
            (list
             (d:method "bool" "prefixMatch"
                       (d:doc "Check if list of tag names is a prefix for either
  of the nested hash tags in this one")
                       #:isConst #t
                       #:arguments (list (d:ident (t:cr (t:vec (t:str))) "prefix")))))
  (d:struct 'Footnote
            (d:doc "Inline and regular footnote definition"
                   #:full "\\note in-text link to the footnotes are implemented using `Link` nodes")
            #:bases '(Inline)
            #:fields
            (list
             (d:field "Str" "tag" (d:doc "Footnote text target name") #:value "")
             (d:field (t:opt (t:id)) "definition" (d:doc "Link to possibly resolved definition") #:value "std::nullopt")))
  (d:struct 'Completion
            (d:doc "Completion status of the subtree list element")
            #:bases '(Inline)
            #:fields
            (list
             (d:field "int" "done" (d:doc "Number of completed tasks") #:value "0")
             (d:field "int" "full" (d:doc "Full number of tasks") #:value "0")
             (d:field "bool" "isPercent" (d:doc "Use fraction or percent to display completion") #:value "false")))
  (d:struct 'Paragraph
            (d:doc "Top-level or inline paragraph")
            #:bases '(Stmt)
            #:methods
            (list
             (d:method "bool" "isFootnoteDefinition" (d:doc "Check if paragraph defines footnote") #:isConst #t)))
  (d:struct 'Format
            (d:doc "Base class for branch of formatting node classes")
            #:bases '(Org)
            #:concreteKind #f)
  (d:struct 'Center (d:doc "Center nested content in export") #:bases '(Format))
  (d:struct 'Command (d:doc "Base class for block or line commands") #:bases '(Org) #:concreteKind #f)
  (d:struct 'LineCommand (d:doc "Line commands") #:bases '(Command) #:concreteKind #f)
  ;; TODO rename to the standalone command
  (d:struct 'Standalone
            (d:doc "Standalone commands that can be placed individuall on the the
top level and don't have to be attached to any subsequent elements"
                   )
            #:bases '(LineCommand)
            #:concreteKind #f)
  (d:struct 'Attached
            (d:doc "Line command that might get attached to some block element")
            #:bases '(LineCommand)
            #:concreteKind #f)
  (d:struct 'Caption
            (d:doc "Caption annotation for any subsequent node")
            #:bases '(Attached)
            #:fields
            (list
             (d:field (t:id "Paragraph") "text" (d:doc "Content description") #:value "SemIdT<Paragraph>::Nil()")))
  (d:struct 'CommandGroup
            (d:doc "Multiple attachable commands will get grouped into this element
 unless it is possible to attached them to some adjacent block command")
            #:bases '(Stmt)
            #:concreteKind #f)
  (d:struct 'Block
            (d:doc "Block command type")
            #:bases '(Command)
            #:concreteKind #f
            )
  (d:struct 'Quote
            (d:doc "Quotation block")
            #:fields
            (list
             (d:field (t:id "Paragraph") "text"
                      (d:doc "Quote content") #:value "SemIdT<Paragraph>::Nil()")))
  (d:struct 'Example (d:doc "Example block") #:bases '(Block))
  (d:struct 'Export (d:doc "Direct export passthrough")
            #:bases '(Block)
            #:nested
            (list
             (d:enum "Format" (d:doc "Export block format type")
                     (list
                      (d:efield "Inline" (d:doc "Export directly in the paragraph"))
                      (d:efield "Line" (d:doc "Single line of export"))
                      (d:efield "Block" (d:doc "Multiple lines of export")))))
            #:fields
            (list
             (d:field "Format" "format" (d:doc "Export block type") #:value "Format::Inline")
             (d:field (t:str) "exporter" (d:doc "Exporter backend name"))
             (d:field (t:str) "content" (d:doc "Raw exporter content string"))))
  (d:struct 'AdmonitionBlock (d:doc "Block of text with admonition tag: 'note', 'warning'")
            #:bases '(Block))
  (d:struct 'Code
            (d:doc "Base class for all code blocks")
            #:bases '(Block)
            #:nested
            (list
             (d:struct
              'Switch (d:doc "Extra configuration switches that can be used to control
representation of the rendered code block. This field does not
exactly correspond to the `-XX` parameters that can be passed
directly in the field, but also works with attached `#+options`
from the block")
              #:nested
              (d:group
               (list
                (d:struct 'CalloutFormat (d:doc "")
                          #:fields (list (d:field "Str" "format" (d:doc "") #:value "")))
                (d:struct 'RemoveCallout (d:doc "")
                          #:fields (list (d:field "bool" "remove" (d:doc "") #:value "true")))
                (d:struct 'EmphasizeLine (d:doc "Emphasize single line -- can be repeated multiple times")
                          #:fields (list (d:field (t:vec "int") "line" (d:doc "") #:value "{}")))
                (d:struct 'Dedent (d:doc "")
                          #:fields (list (d:field "int" "value" (d:doc "") #:value "0"))))
               #:variantName "Data")
              #:fields (list (d:field "Data" "data" (d:doc ""))))
             (d:enum 'Results (d:doc "What to do with newly evaluated result")
                     (list (d:efield "Replace" (d:doc "Remove old result, replace with new value"))))
             (d:enum 'Exports (d:doc "What part of the code block should be visible in export")
                     (list
                      (d:efield "None" (d:doc "Hide both original code and run result"))
                      (d:efield "Both" (d:doc "Show output and code"))
                      (d:efield "Code" (d:doc "Show only code"))
                      (d:efield "Results" (d:doc "Show only evaluation results")))))
            #:fields
            (list
             (d:field (t:opt (t:str)) "lang" (d:doc "Code block language name") #:value "std::nullopt")
             (d:field (t:vec "Switch") "switches" (d:doc "Switch options for block") #:value "{}")
             (d:field "Exports" "exports" (d:doc "What to export") #:value "Exports::Both")
             (d:field "bool" "cache" (d:doc "Do cache values?") #:value "false")
             (d:field "bool" "eval" (d:doc "Eval on export?") #:value "false")
             (d:field "bool" "noweb" (d:doc "Web-tangle code on export/run") #:value "false")
             (d:field "bool" "hlines" (d:doc "?") #:value "false")
             (d:field "bool" "tangle" (d:doc "?") #:value "false")))
  (d:struct 'Time
            (d:doc "Single static or dynamic timestamp (active or inactive)")
            #:bases '(Org)
            #:nested
            (list
             (d:struct
              'Repeat
              (d:doc "Repetition information for static time")
              #:nested
              (list
               (d:enum 'Mode (d:doc "Timestamp repetition mode")
                       (list
                        (d:efield "None" (d:doc "Do not repeat task on completion"))
                        (d:efield "Exact" (d:doc "?"))
                        (d:efield "FirstMatch" (d:doc "Repeat on the first matching day in the future"))
                        (d:efield "SameDay" (d:doc "Repeat task on the same day next week/month/year"))))
               (d:enum 'Period
                       (d:doc "Repetition period. Temporary placeholder for now, until I
figure out what would be the proper way to represent whatever
org can do ... which is to be determined as well")
                       (list
                        (d:efield "Year" (d:doc ""))
                        (d:efield "Month" (d:doc ""))
                        (d:efield "Week" (d:doc ""))
                        (d:efield "Day" (d:doc ""))
                        (d:efield "Hour" (d:doc ""))
                        (d:efield "Minute" (d:doc ""))))
               )
              #:fields
              (list
               (d:field "Mode" "mode" (d:doc "mode"))
               (d:field "Period" "period" (d:doc "period"))
               (d:field "int" "count" (d:doc "count"))
               )
              )
             )
            )
  (d:struct 'TimeRange (d:doc "Range of time delimited by two points")
            #:bases '(Org)
            #:fields
            (list
             (d:field (t:id "Time") "from" (d:doc "Starting time") #:value "SemIdT<Time>::Nil()")
             (d:field (t:id "Time") "to" (d:doc "Finishing time") #:value "SemIdT<Time>::Nil()")))
  (d:struct 'Macro (d:doc "Inline macro invocation")
            #:bases '(Org)
            #:fields
            (list
             (d:field (t:str) "name" (d:doc "Macro name") #:value "")
             (d:field (t:vec (t:str)) "arguments" (d:doc "Raw uninterpreted macro arguments") #:value "{}")))
  (d:struct 'Symbol (d:doc "Text symbol or symbol command")
            #:bases '(Org)
            #:nested
            (list
             (d:struct 'Param (d:doc "Symbol parameters")
                       #:fields
                       (list
                        (d:field (t:opt (t:str)) "key" (d:doc "Key -- for non-positional"))
                        (d:field (t:str) "value" (d:doc "Uninterpreted value")))))
            #:fields
            (list
             (d:field (t:str) "name" (d:doc "Name of the symbol"))
             (d:field (t:vec "Param") "parameters" (d:doc "Optional list of parameters"))
             (d:field (t:id) "positional" (d:doc "Positional parameters"))))
  (d:struct 'SubtreeLog (d:doc "Single subtree log entry")
            #:bases '(Org)
            #:nested
            (list
             (d:struct 'DescribedLog (d:doc "Base value for the log variant")
                       #:fields
                       (list
                        (d:field (t:opt (t:id "StmtList")) "desc"
                                 (d:doc "Optional description of the log entry")
                                 #:value "SemIdT<StmtList>::Nil()")))
             (d:group
              (list
               (d:struct 'Note (d:doc "Timestamped note")
                         #:bases '(DescribedLog)
                         #:fields (list (d:id-field "Time" "on" (d:doc "Where log was taken"))))
               (d:struct 'Refile (d:doc "Refiling action")
                         #:bases '(DescribedLog)
                         #:fields
                         (list
                          (d:id-field "Time" "on" (d:doc "When the refiling happened"))
                          (d:id-field "Link" "from" (d:doc "Link to the original subtree"))))
               (d:struct 'Clock (d:doc "Clock entry `CLOCK: [2023-04-30 Sun 13:29:04]--[2023-04-30 Sun 14:51:16] => 1:22`")
                         #:bases '(DescribedLog)
                         #:fields
                         (list
                          (d:field (t:var (t:id "Time") (t:id "TimeRange"))
                                   "range"
                                   (d:doc "Start-end or only start period")
                                   #:value "SemIdT<Time>::Nil()")))
               (d:struct 'State (d:doc "Change of the subtree state -- `- State \"WIP\" from \"TODO\" [2023-04-30 Sun 13:29:04]`")
                         #:bases '(DescribedLog)
                         #:fields
                         (list
                          (d:field "OrgBigIdentKind" "from" (d:doc "From"))
                          (d:field "OrgBigIdentKind" "to" (d:doc "To"))
                          (d:id-field "Time" "on" (d:doc "On"))))
               (d:struct 'Tag (d:doc "Assign tag to the subtree `- Tag \"project##haxorg\" Added on [2023-04-30 Sun 13:29:06]`")
                         #:bases '(DescribedLog)
                         #:fields
                         (list
                          (d:id-field "Time" "on" (d:doc "When the log was assigned"))
                          (d:id-field "HashTag" "tag" (d:doc "Tag in question"))
                          (d:field "bool" "added" (d:doc "Added/removed?") #:value "false"))))
              #:enumName "Kind"
              #:variantName "LogEntry"))
            #:fields
            (list
             (d:field "LogEntry" "log" (d:doc "Log") #:value "Note{}")))
  (d:struct 'Subtree (d:doc "Subtree")
            #:bases '(Org)
            #:fields
            (list
             (d:field "int" "level" (d:doc "Subtree level") #:value "0")
             (d:opt-field (t:str) "treeId" (d:doc ":ID: property"))
             (d:opt-field (t:str) "todo" (d:doc "Todo state of the tree"))
             (d:opt-field (t:id "Completion") "completion" (d:doc "Task completion state"))
             (d:vec-field (t:id "HashTag") "tags" (d:doc "Trailing tags"))
             (d:id-field "Paragraph" "title" (d:doc "Main title"))
             (d:vec-field (t:id "SubtreeLog") "logbook" (d:doc "Associated subtree log"))
             (d:vec-field "Property" "properties" (d:doc "Immediate properties"))
             (d:opt-field (t:id "Time") "closed" (d:doc "When subtree was marked as closed"))
             (d:opt-field (t:id "Time") "deadline" (d:doc "When is the deadline"))
             (d:opt-field (t:id "Time") "scheduled" (d:doc "When the event is scheduled"))))
  (d:struct 'LatexBody (d:doc "Latex code body") #:bases '(Org) #:concreteKind #f)
  (d:struct 'InlineMath (d:doc "Inline math") #:bases '(LatexBody))
  (d:struct 'Leaf (d:doc "Final node") #:bases '(Org) #:concreteKind #f
            #:fields (list (d:field (t:str) "text" (d:doc "Final leaf value") #:value "")))
  (d:struct 'Escaped (d:doc "Escaped text") #:bases '(Leaf))
  (d:struct 'Newline (d:doc "\\n newline") #:bases '(Leaf))
  (d:struct 'Space (d:doc "' ' space") #:bases '(Leaf))
  (d:struct 'Word (d:doc "word") #:bases '(Leaf))
  (d:struct 'AtMention (d:doc "@mention") #:bases '(Leaf))
  (d:struct 'RawText (d:doc "") #:bases '(Leaf))
  (d:struct 'Punctuation (d:doc "") #:bases '(Leaf))
  (d:struct 'Placeholder (d:doc "") #:bases '(Leaf))
  (d:struct 'BigIdent (d:doc "") #:bases '(Leaf))
  (d:struct 'Markup (d:doc "") #:bases '(Org) #:concreteKind #f)
  (d:struct 'Bold (d:doc "") #:bases '(Markup))
  (d:struct 'Underline (d:doc "") #:bases '(Markup))
  (d:struct 'Monospace (d:doc "") #:bases '(Markup))
  (d:struct 'MarkQuote (d:doc "") #:bases '(Markup))
  (d:struct 'Verbatim (d:doc "") #:bases '(Markup))
  (d:struct 'Italic (d:doc "") #:bases '(Markup))
  (d:struct 'Strike (d:doc "") #:bases '(Markup))
  (d:struct 'Par (d:doc "") #:bases '(Markup))
  (d:struct 'List (d:doc "") #:bases '(Org)
            #:methods (list (d:method "bool" "isDescriptionList" (d:doc "") #:isConst #t)))
  ;; TODO
  (d:struct 'ListItem (d:doc "") #:bases '(Org))
  ;; TODO
  (d:struct 'Link (d:doc "") #:bases '(Org))
  )
 #:enumName "OrgSemKind"
 #:iteratorMacroName "EACH_ORG_SEM_KIND")
