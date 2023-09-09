(use-modules (oop goops))
(use-modules (srfi srfi-1))
(use-modules (language tree-il))
(use-modules (ice-9 pretty-print))
(use-modules (ice-9 format))

(define (is-positional field)
  ;; For simplicity -- has default value => optional, does not have default => required
  (eq? (length field) 1))

(define (get-positional-defs field-defs)
  (remove (lambda (field) (not (is-positional field))) field-defs))

(define (get-optional-defs field-defs)
  (remove (lambda (field) (is-positional field)) field-defs))

(define (get-positional-fields field-defs)
  ;; List of non-default fields
  (map (lambda (field-def)
         (let* ((field-name (car field-def))
                (field-kwd (symbol->keyword field-name)))
           `(,field-name #:init-keyword ,field-kwd)))
       (get-positional-defs field-defs)))

(define (get-optional-fields field-defs)
  ;; Map positional fields
  (map (lambda (field-def)
         (let* ((field-name (car field-def))
                (field-kwd (symbol->keyword field-name))
                (default-value (cdr field-def)))
           ;; GOOPS field definition syntax with init keyword and default *expression*
           ;; (NOTE: will be evaluated each time object constructed, so can be dynamic)
           `(,field-name
             #:init-keyword ,field-kwd
             #:init-form ,default-value)))
       (get-optional-defs field-defs)))

(define-macro (simple-define-type type-name make-fn-name . field-defs)
  ;; Simplified syntax to define types that will be read into the C++ data
  ;; structures when the script is evaluated. NOTE: field names and must
  ;; match with the definitions in the compiled code.
  (let* ((positional-fields (get-positional-fields field-defs))
         (optional-fields (get-optional-fields field-defs))
         (positional-args
          (map (lambda (field-def) (car field-def))
               (get-positional-defs field-defs)))
         (pass-args
          ;; Direct bypass for the arguments provided to the constructor
          ;; function that is defined by this macro
          (fold
           (lambda (prev next) (append prev next))
           (list)
           (map (lambda (field-def)
                  ;; Convert field name to the keyword type so call to the
                  ;; GOOPS constructor can find the right values
                  (list (symbol->keyword (car field-def)) (car field-def)))
                field-defs)))
         ;; Optional arguments with default values
         (optional-args
          ;; `(key value)' pairs for optional arguments
          (map (lambda (field-def) (cons (car field-def) (cdr field-def)))
               (get-optional-defs field-defs))))
    `(begin
       ;; Splice positional and non-positional fields for the definition -- `,@'
       ;; unpacks everything into a flat list
       (define-class ,type-name () ,@positional-fields ,@optional-fields)
       ;; Splice remaining elements into the constructor function definition
       (define* (,make-fn-name ,@positional-args #:key ,@optional-args)
         (make ,type-name ,@pass-args)))))

;; (pretty-print
;;  (tree-il->scheme
;;   (macroexpand
;;    '()
;;    )))

(simple-define-type <doc> d:doc (brief) (full ""))
(simple-define-type <enum-field> d:efield (name) (doc) (value #f))
(simple-define-type <enum> d:enum (name) (doc) (fields) (base "short int") (kind "Enum"))
(simple-define-type
 <field> d:field
 (type) (name) (doc) (value #f) (kind "Field") (isStatic #f) (isConst #f))

(simple-define-type <ident> d:ident (type) (name) (value #f))

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
 (types)
 (enumName "Kind")
 (iteratorMacroName "")
 (variantName "Data")
 (variantField "data")
 (variantValue #f)
 (kindGetter "getKind")
 (kind "Group"))

(simple-define-type
 <method> d:method
 (result)
 (name)
 (doc)
 (arguments (list))
 (isConst #f)
 (isStatic #f)
 (impl #f)
 (params #f)
 (isVirtual #f)
 (isPureVirtual #f)
 (kind "Method"))

(simple-define-type <tparam> d:param (name))
(simple-define-type <file> d:file (path) (entries))
(simple-define-type <unit> d:unit (header) (source #f))
(simple-define-type <namespace> d:namespace (name) (entries) (kind "Namespace"))
(simple-define-type <full> d:full (files))

(simple-define-type <include> d:include (what) (isSystem) (kind "Include"))
(simple-define-type <passthrough> d:pass (what) (kind "Pass"))

(define (t:int) "int")
(define (t:str) "Str")
(define (t:vec arg) (format #f "Vec<~a>" arg))
(define* (t:id #:optional target)
  (if target (format #f "SemIdT<~a>" target) "SemId"))
(define* (t:opt arg) (format #f "Opt<~a>" arg))
(define* (t:osk) "OrgSemKind")
(define* (t:cr arg) (format #f "CR<~a>" arg))
(define* (t:r arg) (format #f "~a&" arg))
(define* (t:var #:rest args) (format #f "Variant<~a>" (string-join args ", ")))
(define* (t:map key value) (format #f "UnorderedMap<~a, ~a>" key value))

(define* (d:id-field id name doc)
  (d:field (t:id id) name doc #:value (format #f "SemIdT<~a>::Nil()" id)))

(define* (d:vec-field type name doc)
  (d:field (t:vec type) name doc #:value "{}"))

(define* (d:opt-field type name doc)
  (d:field (t:opt type) name doc #:value "std::nullopt"))

(define* (slot-concat! obj slot-name new-value do-prepend?)
  (let ((current-value (slot-ref obj slot-name)))
    (let ((new-list (if do-prepend?
                        (cons new-value current-value)
                        (append current-value (list new-value)))))
      (slot-set! obj slot-name new-list))))

(define* (slot-prepend! obj slot-name new-value)
  (slot-concat! obj slot-name new-value #t))

(define* (slot-append! obj slot-name new-value)
  (slot-concat! obj slot-name new-value #f))

(define* (d:simple-enum name doc #:rest values)
  (d:enum name doc
          (map (lambda (name) (d:efield name (d:doc ""))) values)))

(define* (d:org #:rest args)
  (let* ((def (apply d:struct args))
         (kind (slot-ref def 'name))
         (base (car (slot-ref def 'bases))))
    ;; Inherit base constructor for all types
    (slot-prepend!
     def 'nested (d:pass (format #f "using ~a::~a;" base base)))
    (when (slot-ref def 'concreteKind)
      ;; For concrete kinds -- define static field with provided value
      (slot-prepend!
       def 'fields
       (d:field (t:osk) "staticKind" (d:doc "Document")
                #:isConst #t
                #:isStatic #t
                ;; #:value (format #f "~a::~a" (t:osk) kind)
                ))
      ;; Override kind getter
      (slot-prepend!
       def 'methods
       (d:method (t:osk) "getKind" (d:doc "") #:isConst #t #:isVirtual #t #:isPureVirtual #f
                 #:impl (format #f "return ~a::~a;" (t:osk) kind)))
      ;; Static 'create' method that will call into the global node store
      (slot-prepend!
       def 'methods
       (d:method (t:id kind) "create" (d:doc "")
                 #:isStatic #t
                 #:arguments (list
                              (d:ident (t:id) "parent")
                              (d:ident (t:opt "OrgAdapter")  "original" #:value "std::nullopt")))))
    def))

(define types
  (list
   (d:org 'Stmt
          (d:doc
           "Base class for all document-level entries. Note that some node kinds
might also have inline entries (examples include links, source code blocks,
call blocks)")
          #:bases '(Org)
          #:concreteKind #f
          #:fields (list (d:field (t:vec (t:id)) "attached" (d:doc "")))
          #:methods (list (d:method (t:opt (t:id)) "getAttached" (d:doc "")
                                    #:arguments (list (d:ident (t:osk) "kind"))))
          #:nested
          (list
           (d:pass "Stmt() {}")
           (d:pass "Stmt(SemId parent, CVec<SemId> attached, CVec<SemId> subnodes) : Org(parent, subnodes), attached(attached) {}")))
   (d:org 'Inline
          (d:doc "Base class for all inline elements")
          #:bases '(Org) #:concreteKind #f)
   (d:org 'StmtList
          (d:doc "Zero or more statement nodes")
          #:bases '(Org))
   (d:org 'Empty (d:doc "Node without content") #:bases '(Org))
   (d:org 'Row (d:doc "Table row") #:bases '(Org))
   (d:org 'Table (d:doc "Table")
          #:bases '(Stmt)
          #:fields
          (list
           (d:field (t:vec (t:id "Row")) "rows"
                    (d:doc "List of rows for the table") #:value "{}")))
   (d:org 'HashTag (d:doc "Single or nested inline hash-tag")
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
   (d:org 'Footnote
          (d:doc "Inline and regular footnote definition"
                 #:full "\\note in-text link to the footnotes are implemented using `Link` nodes")
          #:bases '(Inline)
          #:fields
          (list
           (d:field "Str" "tag" (d:doc "Footnote text target name") #:value "\"\"")
           (d:field (t:opt (t:id)) "definition" (d:doc "Link to possibly resolved definition") #:value "std::nullopt")))
   (d:org 'Completion
          (d:doc "Completion status of the subtree list element")
          #:bases '(Inline)
          #:fields
          (list
           (d:field "int" "done" (d:doc "Number of completed tasks") #:value "0")
           (d:field "int" "full" (d:doc "Full number of tasks") #:value "0")
           (d:field "bool" "isPercent" (d:doc "Use fraction or percent to display completion") #:value "false")))
   (d:org 'Paragraph
          (d:doc "Top-level or inline paragraph")
          #:bases '(Stmt)
          #:methods
          (list
           (d:method "bool" "isFootnoteDefinition" (d:doc "Check if paragraph defines footnote") #:isConst #t
                     #:impl "return !subnodes.empty() && at(0)->is(OrgSemKind::Footnote);")))
   (d:org 'Format
          (d:doc "Base class for branch of formatting node classes")
          #:bases '(Org)
          #:concreteKind #f)
   (d:org 'Center (d:doc "Center nested content in export") #:bases '(Format))
   (d:org 'Command (d:doc "Base class for block or line commands") #:bases '(Org) #:concreteKind #f)
   (d:org 'LineCommand (d:doc "Line commands") #:bases '(Command) #:concreteKind #f)
   ;; TODO rename to the standalone command
   (d:org 'Standalone
          (d:doc "Standalone commands that can be placed individuall on the the
top level and don't have to be attached to any subsequent elements")
          #:bases '(LineCommand)
          #:concreteKind #f)
   (d:org 'Attached
          (d:doc "Line command that might get attached to some block element")
          #:bases '(LineCommand)
          #:concreteKind #f)
   (d:org 'Caption
          (d:doc "Caption annotation for any subsequent node")
          #:bases '(Attached)
          #:fields
          (list
           (d:id-field "Paragraph" "text" (d:doc "Content description"))))
   (d:org 'CommandGroup
          (d:doc "Multiple attachable commands will get grouped into this element
 unless it is possible to attached them to some adjacent block command")
          #:bases '(Stmt))
   (d:org 'Block
          (d:doc "Block command type")
          #:bases '(Command)
          #:concreteKind #f
          )
   (d:org 'Quote (d:doc "Quotation block")
          #:bases '(Org)
          #:fields
          (list
           (d:id-field "Paragraph" "text" (d:doc "Quote content"))))
   (d:org 'Example (d:doc "Example block") #:bases '(Block))
   (d:org 'CmdArguments (d:doc "Additional arguments for command blocks")
          #:bases '(Org)
          #:methods
          (list
           (d:method (t:opt (t:id "CmdArgument")) "popArg"
                     (d:doc "Remove argument value from the map and return it if present"
                            #:full "Some argument values can be processed directly during convert, others will be mapped in respective exporter backends. This is a convenience method to remove things during convert stage")
                     #:arguments
                     (list
                      (d:ident (t:str) "key"))))
          #:fields
          (list
           (d:field (t:vec (t:id "CmdArgument")) "positional" (d:doc "Positional arguments that had no keys"))
           (d:field (t:map (t:str) (t:id "CmdArgument")) "named" (d:doc "Stored key-value mapping"))))
   (d:org 'CmdArgument (d:doc "Single key-value (or positional)")
          #:bases '(Org)
          #:fields
          (list
           (d:opt-field (t:str) "key" (d:doc "Key"))
           (d:field (t:str) "value" (d:doc "Value")))
          #:methods
          (list
           (d:method (t:opt "int") "getInt" (d:doc "Parse argument as integer value") #:isConst #t)
           (d:method (t:opt "bool") "getBool" (d:doc "Get argument as bool") #:isConst #t)
           (d:method (t:str) "getString" (d:doc "Get original string") #:isConst #t))
          )
   (d:org 'Export (d:doc "Direct export passthrough")
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
           (d:id-field "CmdArguments" "parameters"
                       (d:doc "Additional parameters aside from 'exporter"))
           (d:opt-field (t:str) "placement" (d:doc "Customized position of the text in the final exporting document."))
           (d:field (t:str) "content" (d:doc "Raw exporter content string"))))
   (d:org 'AdmonitionBlock (d:doc "Block of text with admonition tag: 'note', 'warning'")
          #:bases '(Block))
   (d:org 'Code
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
            (list
             (d:group
              (list
               (d:struct 'LineStart (d:doc "Enumerate code lines starting from `start` value instead of default indexing.")
                         #:fields
                         (list
                          (d:field "int" "start" (d:doc "First line number"))
                          (d:field "bool" "extendLast" (d:doc "Continue numbering from the previous block nstead of starting anew") #:value "false")
                          )
                         )
               (d:struct 'CalloutFormat (d:doc "")
                         #:fields (list (d:field "Str" "format" (d:doc "") #:value "\"\"")))
               (d:struct 'RemoveCallout (d:doc "")
                         #:fields (list (d:field "bool" "remove" (d:doc "") #:value "true")))
               (d:struct 'EmphasizeLine (d:doc "Emphasize single line -- can be repeated multiple times")
                         #:fields (list (d:field (t:vec "int") "line" (d:doc "") #:value "{}")))
               (d:struct 'Dedent (d:doc "")
                         #:fields (list (d:field "int" "value" (d:doc "") #:value "0")))))))
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
           (d:id-field "CmdArguments" "parameters"
                       (d:doc "Additional parameters that are language-specific"))
           (d:field "bool" "cache" (d:doc "Do cache values?") #:value "false")
           (d:field "bool" "eval" (d:doc "Eval on export?") #:value "false")
           (d:field "bool" "noweb" (d:doc "Web-tangle code on export/run") #:value "false")
           (d:field "bool" "hlines" (d:doc "?") #:value "false")
           (d:field "bool" "tangle" (d:doc "?") #:value "false")))
   (d:org 'Time
          (d:doc "Single static or dynamic timestamp (active or inactive)")
          #:bases '(Org)
          #:fields
          (list
           (d:field "bool" "isActive" (d:doc "<active> vs [inactive]") #:value "false"))
          #:nested
          (list
           (d:pass "bool isStatic() const { return std::holds_alternative<Static>(time); }")
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
                      (d:efield "Minute" (d:doc "")))))
            #:fields
            (list
             (d:field "Mode" "mode" (d:doc "mode"))
             (d:field "Period" "period" (d:doc "period"))
             (d:field "int" "count" (d:doc "count"))))
           (d:group
            (list
             (d:struct 'Static (d:doc "")
                       #:fields (list (d:field (t:opt "Repeat") "repeat" (d:doc ""))
                                      (d:field "UserTime" "time" (d:doc ""))))
             (d:struct 'Dynamic (d:doc "")
                       #:fields (list (d:field (t:str) "expr" (d:doc "")))))
            #:kindGetter "getTimeKind"
            #:enumName "TimeKind"
            #:variantField "time"
            #:variantName "TimeVariant")))
   (d:org 'TimeRange (d:doc "Range of time delimited by two points")
          #:bases '(Org)
          #:fields
          (list
           (d:id-field "Time" "from" (d:doc "Starting time"))
           (d:id-field "Time" "to" (d:doc "Finishing time"))))
   (d:org 'Macro (d:doc "Inline macro invocation")
          #:bases '(Org)
          #:fields
          (list
           (d:field (t:str) "name" (d:doc "Macro name") #:value "\"\"")
           (d:field (t:vec (t:str)) "arguments" (d:doc "Raw uninterpreted macro arguments") #:value "{}")))
   (d:org 'Symbol (d:doc "Text symbol or symbol command")
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
           (d:field (t:vec (t:id)) "positional" (d:doc "Positional parameters"))))
   (d:org 'SubtreeLog (d:doc "Single subtree log entry")
          #:bases '(Org)
          #:methods
          (list
           (d:method "void" "setDescription" (d:doc "")
                     #:arguments (list (d:ident (t:id "StmtList") "desc"))))
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
             (d:struct 'Priority (d:doc "Priority added")
                       #:bases '(DescribedLog)
                       #:nested (list (d:simple-enum "Action" (d:doc "Priority change action") "Added" "Removed" "Changed"))
                       #:fields (list (d:opt-field  "QString" "oldPriority" (d:doc "Previous priority for change and removal"))
                                      (d:opt-field  "QString" "newPriority" (d:doc "New priority for change and addition"))
                                      (d:id-field "Time" "on" (d:doc "When priority was changed"))))
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
                        (d:field "OrgBigIdentKind" "from" (d:doc ""))
                        (d:field "OrgBigIdentKind" "to" (d:doc ""))
                        (d:id-field "Time" "on" (d:doc ""))))
             (d:struct 'Tag (d:doc "Assign tag to the subtree `- Tag \"project##haxorg\" Added on [2023-04-30 Sun 13:29:06]`")
                       #:bases '(DescribedLog)
                       #:fields
                       (list
                        (d:id-field "Time" "on" (d:doc "When the log was assigned"))
                        (d:id-field "HashTag" "tag" (d:doc "Tag in question"))
                        (d:field "bool" "added" (d:doc "Added/removed?") #:value "false"))))
            #:kindGetter "getLogKind"
            #:variantField "log"
            #:variantValue "Note{}"
            #:variantName "LogEntry")))
   (d:org 'Subtree (d:doc "Subtree")
          #:bases '(Org)
          #:fields
          (list
           (d:field "int" "level" (d:doc "Subtree level") #:value "0")
           (d:opt-field (t:str) "treeId" (d:doc ":ID: property"))
           (d:opt-field (t:str) "todo" (d:doc "Todo state of the tree"))
           (d:opt-field (t:id "Completion") "completion" (d:doc "Task completion state"))
           (d:opt-field (t:id "Paragraph") "description" (d:doc ""))
           (d:vec-field (t:id "HashTag") "tags" (d:doc "Trailing tags"))
           (d:id-field "Paragraph" "title" (d:doc "Main title"))
           (d:vec-field (t:id "SubtreeLog") "logbook" (d:doc "Associated subtree log"))
           (d:vec-field "Property" "properties" (d:doc "Immediate properties"))
           (d:opt-field (t:id "Time") "closed" (d:doc "When subtree was marked as closed"))
           (d:opt-field (t:id "Time") "deadline" (d:doc "When is the deadline"))
           (d:opt-field (t:id "Time") "scheduled" (d:doc "When the event is scheduled")))
          #:methods
          (list
           (d:method (t:vec "Period") "getTimePeriods" (d:doc "") #:isConst #t
                     #:arguments (list (d:ident "IntSet<Period::Kind>" "kinds")))
           (d:method (t:vec "Property") "getProperties" (d:doc "") #:isConst #t
                     #:arguments (list (d:ident "Property::Kind" "kind")
                                       (d:ident (t:cr (t:str)) "subkind" #:value "\"\"")))
           (d:method (t:opt "Property") "getProperty" (d:doc "") #:isConst #t
                     #:arguments (list (d:ident "Property::Kind" "kind")
                                       (d:ident (t:cr (t:str)) "subkind" #:value "\"\"")))
           (d:method (t:vec "Property") "getContextualProperties" (d:doc "") #:isConst #t
                     #:arguments (list (d:ident "Property::Kind" "kind")
                                       (d:ident (t:cr (t:str)) "subkind" #:value "\"\"")))
           (d:method (t:opt "Property") "getContextualProperty" (d:doc "") #:isConst #t
                     #:arguments (list (d:ident "Property::Kind" "kind")
                                       (d:ident (t:cr (t:str)) "subkind" #:value "\"\""))))
          #:nested
          (list
           (d:struct 'Period (d:doc "Type of the subtree associated time periods")
                     #:fields
                     (list
                      (d:field "Kind" "kind"
                               (d:doc "Time period kind -- not associated with point/range distinction"))
                      (d:field (t:var (t:id "Time") (t:id "TimeRange")) "period"
                               (d:doc "Stored time point/range")))
                     #:methods
                     (list
                      (d:method (t:id "Time") "getTime" (d:doc "Get associated time point")
                                #:impl "return std::get<SemIdT<Time>>(period);")
                      (d:method (t:id "Time") "getTimeRange" (d:doc "Get associated time period")
                                #:impl "return std::get<SemIdT<TimeRange>>(period);"))
                     ;; TODO constructors
                     #:nested
                     (list
                      (d:enum 'Kind (d:doc "Period kind")
                              (list
                               (d:efield "Clocked" (d:doc "Time period of the task execution."))
                               (d:efield "Scheduled" (d:doc "Date of task execution start plus it's estimated effort duration. If the latter one is missing then only a single time point is returned"))
                               (d:efield "Titled" (d:doc "Single point or time range used in title. Single point can also be a simple time, such as `12:20`"))
                               (d:efield "Deadline" (d:doc "Date of task completion. Must be a single time point"))
                               (d:efield "Created" (d:doc "When the subtree was created"))
                               (d:efield "Repeated" (d:doc "Last repeat time of the recurring tasks"))))
                      (d:pass "Period(CR<Variant<SemIdT<Time>, SemIdT<TimeRange>>> period, Kind kind) : period(period), kind(kind) {}")))
           (d:struct 'Property (d:doc "Single subtree property")
                     #:fields
                     (list
                      (d:field "SetMode" "mainSetRule" (d:doc "") #:value "SetMode::Override")
                      (d:field "SetMode" "subSetRule" (d:doc "") #:value "SetMode::Override")
                      (d:field "InheritanceMode" "inheritanceMode" (d:doc "") #:value "InheritanceMode::ThisAndSub"))
                     #:nested
                     (list
                      (d:simple-enum "SetMode" (d:doc "") "Override" "Add" "Subtract")
                      (d:simple-enum "InheritanceMode" (d:doc "") "ThisAndSub" "OnlyThis" "OnlySub")
                      (d:group
                       (list
                        (d:struct 'Nonblocking (d:doc "")
                                  #:fields (list (d:field "bool" "isBlocking" (d:doc ""))))
                        (d:struct 'Trigger (d:doc ""))
                        (d:struct 'Origin (d:doc "")
                                  #:fields (list (d:field (t:str) "text" (d:doc ""))))
                        (d:struct 'ExportLatexClass (d:doc "")
                                  #:fields (list (d:field (t:str) "latexClass" (d:doc ""))))
                        (d:struct 'ExportLatexClassOptions (d:doc "")
                                  #:fields (list (d:field (t:vec (t:str)) "options" (d:doc ""))))
                        (d:struct 'ExportLatexHeader (d:doc "")
                                  #:fields (list (d:field (t:str) "header" (d:doc ""))))
                        (d:struct 'ExportLatexCompiler (d:doc "")
                                  #:fields (list (d:field (t:str) "compiler" (d:doc ""))))
                        (d:struct 'Ordered (d:doc "")
                                  #:fields (list (d:field "bool" "isOrdered" (d:doc ""))))
                        (d:struct 'Effort (d:doc "")
                                  #:fields
                                  (list
                                   (d:field "int" "hours" (d:doc "") #:value "0")
                                   (d:field "int" "minutes" (d:doc "") #:value "0")))
                        (d:struct 'Visibility (d:doc "")
                                  #:nested
                                  (list
                                   (d:simple-enum "Level" (d:doc "") "Folded" "Children" "Content" "All"))
                                  #:fields (list (d:field "Level" "level" (d:doc ""))))
                        (d:struct 'ExportOptions (d:doc "")
                                  #:fields
                                  (list (d:field (t:str) "backend" (d:doc ""))
                                        (d:field "UnorderedMap<Str, Str>" "values" (d:doc ""))))
                        (d:struct 'Blocker (d:doc "")
                                  #:fields (list (d:field (t:vec (t:str)) "blockers" (d:doc ""))))
                        (d:struct 'Unnumbered (d:doc ""))
                        (d:struct 'Created (d:doc "")
                                  #:fields (list (d:id-field "Time" "time" (d:doc ""))))))
                      (d:pass "Property(CR<Data> data) : data(data) {}")
                      (d:pass "bool matches(Kind kind, CR<QString> subkind = \"\") const;")
                      )
                     )
           )
          )
   (d:org 'LatexBody (d:doc "Latex code body") #:bases '(Org) #:concreteKind #f)
   (d:org 'InlineMath (d:doc "Inline math") #:bases '(LatexBody))
   (d:org 'Leaf (d:doc "Final node") #:bases '(Org) #:concreteKind #f
          #:fields (list (d:field (t:str) "text" (d:doc "Final leaf value") #:value "\"\"")))
   (d:org 'Escaped (d:doc "Escaped text") #:bases '(Leaf))
   (d:org 'Newline (d:doc "\\n newline") #:bases '(Leaf))
   (d:org 'Space (d:doc "' ' space") #:bases '(Leaf))
   (d:org 'Word (d:doc "word") #:bases '(Leaf))
   (d:org 'AtMention (d:doc "@mention") #:bases '(Leaf))
   (d:org 'RawText (d:doc "") #:bases '(Leaf))
   (d:org 'Punctuation (d:doc "") #:bases '(Leaf))
   (d:org 'Placeholder (d:doc "") #:bases '(Leaf))
   (d:org 'BigIdent (d:doc "") #:bases '(Leaf))
   (d:org 'Markup (d:doc "") #:bases '(Org) #:concreteKind #f)
   (d:org 'Bold (d:doc "") #:bases '(Markup))
   (d:org 'Underline (d:doc "") #:bases '(Markup))
   (d:org 'Monospace (d:doc "") #:bases '(Markup))
   (d:org 'MarkQuote (d:doc "") #:bases '(Markup))
   (d:org 'Verbatim (d:doc "") #:bases '(Markup))
   (d:org 'Italic (d:doc "") #:bases '(Markup))
   (d:org 'Strike (d:doc "") #:bases '(Markup))
   (d:org 'Par (d:doc "") #:bases '(Markup))
   (d:org 'List (d:doc "") #:bases '(Org)
          #:methods (list (d:method "bool" "isDescriptionList" (d:doc "") #:isConst #t)))
   (d:org 'ListItem (d:doc "") #:bases '(Org)
          #:fields
          (list
           (d:field "Checkbox" "checkbox" (d:doc "") #:value "Checkbox::None")
           (d:field (t:opt (t:id "Paragraph")) "header" (d:doc "") #:value "std::nullopt"))
          #:nested
          (list (d:simple-enum "Checkbox" (d:doc "") "None" "Done" "Empty"))
          #:methods
          (list
           (d:method "bool" "isDescriptionItem" (d:doc "") #:isConst #t
                     #:impl "return header.has_value();")))
   ;; TODO
   (d:org 'Link (d:doc "") #:bases '(Org)
          #:fields
          (list
           (d:field (t:opt (t:id "Paragraph")) "description" (d:doc "") #:value "std::nullopt"))
          #:methods
          (list
           (d:method (t:opt (t:id)) "resolve" (d:doc "") #:isConst #t
                     #:arguments (list (d:ident (t:cr "Document") "doc")))
           (d:method (t:opt (t:id)) "resolve" (d:doc "") #:isConst #t))
          #:nested
          (list
           (d:group
            (list
             (d:struct 'Raw (d:doc "") #:fields (list (d:field (t:str) "text" (d:doc ""))))
             (d:struct 'Id (d:doc "") #:fields (list (d:field (t:str) "text" (d:doc ""))))
             (d:struct 'Person (d:doc "") #:fields (list (d:field (t:str) "name" (d:doc ""))))
             (d:struct 'Footnote (d:doc "") #:fields (list (d:field (t:str) "target" (d:doc ""))))
             (d:struct 'File (d:doc "") #:fields (list (d:field (t:str) "file" (d:doc "")))))
            #:kindGetter "getLinkKind")))
   (d:org 'Document (d:doc "") #:bases '(Org)
          #:methods
          (list
           (d:method (t:opt (t:id)) "resolve" (d:doc "")
                     #:isConst #t
                     #:arguments (list (d:ident (t:cr (t:id)) "node")))
           (d:method (t:opt (t:id "Subtree")) "getSubtree" (d:doc "")
                     #:isConst #t
                     #:arguments (list (d:ident (t:cr (t:str)) "id")))
           (d:method (t:vec "Subtree::Property") "getProperties" (d:doc "")
                     #:isConst #t
                     #:arguments (list (d:ident "Subtree::Property::Kind" "kind")
                                       (d:ident (t:cr (t:str)) "subKind" #:value "\"\"")))
           (d:method (t:opt "Subtree::Property") "getProperty" (d:doc "")
                     #:isConst #t
                     #:arguments (list (d:ident "Subtree::Property::Kind" "kind")
                                       (d:ident (t:cr (t:str)) "subKind" #:value "\"\""))))
          #:fields
          (list
           (d:field (t:map (t:str) (t:id)) "idTable" (d:doc ""))
           (d:field (t:map (t:str) (t:id)) "nameTable" (d:doc ""))
           (d:field (t:map (t:str) (t:id)) "footnoteTable" (d:doc ""))
           (d:field (t:map (t:str) (t:id)) "anchorTable" (d:doc ""))
           (d:opt-field (t:id "Paragraph") "title" (d:doc ""))
           (d:opt-field (t:id "Paragraph") "author" (d:doc ""))
           (d:opt-field (t:id "Paragraph") "creator" (d:doc ""))
           (d:opt-field (t:id "RawText") "email" (d:doc ""))
           (d:opt-field (t:vec (t:str)) "language" (d:doc ""))
           (d:id-field "DocumentOptions" "options" (d:doc ""))
           (d:opt-field (t:str) "exportFileName" (d:doc ""))))
   (d:org 'ParseError (d:doc "") #:bases '(Org))
   (d:org 'FileTarget (d:doc "") #:bases '(Org)
          #:fields
          (list
           (d:field (t:str) "path" (d:doc ""))
           (d:opt-field "int" "line" (d:doc ""))
           (d:opt-field (t:str) "searchTarget" (d:doc ""))
           (d:field "bool" "restrictToHeadlines" (d:doc "") #:value "false")
           (d:opt-field (t:str) "targetId" (d:doc ""))
           (d:opt-field (t:str) "regexp" (d:doc ""))))
   (d:org 'TextSeparator (d:doc "") #:bases '(Org))
   (d:org 'Include (d:doc "") #:bases '(Org)
          #:nested
          (list
           (d:group
            (list
             (d:struct 'Example (d:doc ""))
             (d:struct 'Export (d:doc ""))
             (d:struct 'Src (d:doc ""))
             (d:struct 'OrgDocument (d:doc "")))
            #:kindGetter "getIncludeKind")))
   (d:org 'DocumentOptions (d:doc "") #:bases '(Org)
          #:methods
          (list
           (d:method (t:vec "Subtree::Property") "getProperties" (d:doc "")
                     #:isConst #t
                     #:arguments (list (d:ident "Subtree::Property::Kind" "kind")
                                       (d:ident (t:cr (t:str)) "subKind" #:value "\"\"")))
           (d:method (t:opt "Subtree::Property") "getProperty" (d:doc "")
                     #:isConst #t
                     #:arguments (list (d:ident "Subtree::Property::Kind" "kind")
                                       (d:ident (t:cr (t:str)) "subKind" #:value "\"\""))))
          #:nested
          (list
           (d:pass "using TocExport = Variant<bool, int>;")
           (d:simple-enum "BrokenLinks" (d:doc "") "Raise" "Ignore" "Mark")
           (d:simple-enum "Visibility" (d:doc "")
                          "Overview" "Content" "ShowAll" "Show2Levels" "Show3Levels"
                          "Show4Levels" "Show5Levels" "ShowEverything"))
          #:fields
          (list
           (d:field "BrokenLinks" "brokenLinks" (d:doc "") #:value "BrokenLinks::Mark")
           (d:field "Visibility" "initialVisibility" (d:doc "") #:value "Visibility::ShowEverything")
           (d:field "TocExport" "tocExport" (d:doc "") #:value "false")
           (d:field (t:vec "Subtree::Property") "properties" (d:doc ""))
           (d:field "bool" "smartQuotes" (d:doc "") #:value "false")
           (d:field "bool" "emphasizedText" (d:doc "") #:value "false")
           (d:field "bool" "specialStrings" (d:doc "") #:value "false")
           (d:field "bool" "fixedWidthSections" (d:doc "") #:value "false")
           (d:field "bool" "includeTimestamps" (d:doc "") #:value "false")
           (d:field "bool" "preserveLineBreaks" (d:doc "") #:value "false")
           (d:field "bool" "plaintextSubscripts" (d:doc "") #:value "false")
           (d:field "bool" "exportArchived" (d:doc "") #:value "false")
           (d:field "bool" "exportWithAuthor" (d:doc "") #:value "false")
           (d:field "bool" "exportBrokenLinks" (d:doc "") #:value "false")
           (d:field "bool" "exportWithClock" (d:doc "") #:value "false")
           (d:field "bool" "exportWithCreator" (d:doc "") #:value "false")))
   (d:org 'DocumentGroup (d:doc "") #:bases '(Org))))

(define enums
  (list
   (d:enum
    "OrgSemPlacement"
    (d:doc "Semantic location of the sem org node in the parent tree")
    (list
     (d:efield "TreeTitle" (d:doc "Subtree title"))
     (d:efield "TreeBody" (d:doc "Inner content of the subtree"))
     (d:efield "LinkDescription" (d:doc "Description paragraph for the link"))
     (d:efield "ListItemBody" (d:doc "Statement list or inner content of the list item body"))
     (d:efield "ListItemDesc" (d:doc "Description part of the list item"))
     (d:efield "DocBody" (d:doc "Toplevel document"))))
   (d:enum
    "OrgHorizontalDirection" (d:doc "")
    (list
     (d:efield "ohdNone"   (d:doc "No specific positioning requirements"))
     (d:efield "ohdLeft"   (d:doc "Align to the left"))
     (d:efield "ohdRight"  (d:doc "Align to the right"))
     (d:efield "ohdCenter" (d:doc "Align to the center"))))

   (d:enum
    "OrgVerticalDirection" (d:doc "")
    (list
     (d:efield "ovdNone"   (d:doc "No specific positioning"))
     (d:efield "ovdTop"    (d:doc "Align to the top"))
     (d:efield "ovdCenter" (d:doc "Center"))
     (d:efield "ovdBottom" (d:doc "Bottom"))))

   (d:enum
    "OrgSpecName" (d:doc "")
    (list
     (d:efield "Unnamed" (d:doc ""))
     (d:efield "Result" (d:doc ""))
     (d:efield "Year" (d:doc ""))
     (d:efield "Day" (d:doc ""))
     (d:efield "Clock" (d:doc ""))
     (d:efield "Repeater" (d:doc ""))
     (d:efield "Link" (d:doc ""))
     (d:efield "Tags" (d:doc ""))
     (d:efield "Tag" (d:doc ""))
     (d:efield "State" (d:doc ""))
     (d:efield "Protocol" (d:doc ""))
     (d:efield "Desc" (d:doc ""))
     (d:efield "Times" (d:doc ""))
     (d:efield "Drawer" (d:doc ""))
     (d:efield "Args" (d:doc ""))
     (d:efield "Name" (d:doc ""))
     (d:efield "Definition" (d:doc ""))
     (d:efield "Body" (d:doc ""))
     (d:efield "HeaderArgs" (d:doc ""))
     (d:efield "File" (d:doc ""))
     (d:efield "Kind" (d:doc ""))
     (d:efield "Lang" (d:doc ""))
     (d:efield "Prefix" (d:doc ""))
     (d:efield "Text" (d:doc ""))
     (d:efield "Todo" (d:doc ""))
     (d:efield "Urgency" (d:doc ""))
     (d:efield "Title" (d:doc ""))
     (d:efield "Completion" (d:doc ""))
     (d:efield "Head" (d:doc ""))
     (d:efield "Subnodes" (d:doc ""))
     (d:efield "Properties" (d:doc ""))
     (d:efield "Logbook" (d:doc ""))
     (d:efield "Description" (d:doc ""))
     (d:efield "Logs" (d:doc ""))
     (d:efield "Newstate" (d:doc ""))
     (d:efield "Oldstate" (d:doc ""))
     (d:efield "Time" (d:doc ""))
     (d:efield "From" (d:doc ""))
     (d:efield "EndArgs" (d:doc ""))
     (d:efield "Flags" (d:doc ""))
     (d:efield "Value" (d:doc ""))
     (d:efield "Assoc" (d:doc ""))
     (d:efield "Main" (d:doc ""))
     (d:efield "Hash" (d:doc ""))
     (d:efield "Bullet" (d:doc ""))
     (d:efield "Counter" (d:doc ""))
     (d:efield "Checkbox" (d:doc ""))
     (d:efield "Header" (d:doc ""))
     (d:efield "To" (d:doc ""))
     (d:efield "Diff" (d:doc ""))
     (d:efield "Property" (d:doc ""))
     (d:efield "Subname" (d:doc ""))
     (d:efield "Values" (d:doc ""))
     (d:efield "Cells" (d:doc ""))
     (d:efield "Rows" (d:doc ""))
     (d:efield "Lines" (d:doc ""))
     (d:efield "Chunks" (d:doc ""))
     (d:efield "InheritanceMode" (d:doc ""))
     (d:efield "MainSetRule" (d:doc ""))
     (d:efield "SubSetRule" (d:doc ""))))

   (d:enum
    "OrgNodeKind" (d:doc "")
    (list
     (d:efield "None" (d:doc "Default valye for node - invalid state"))
     (d:efield "Document" (d:doc "Toplevel part of the ast, not created by parser, and only used in `semorg` stage"))
     (d:efield "UserNode" (d:doc "User-defined node [[code:OrgUserNode]]"))
     (d:efield "Empty" (d:doc "Empty node - valid state that does not contain any value"))

     (d:efield "Error" (d:doc "Failed node parse" #:full "
   Failed node parse - technically there are no /wrong/ syntax in the
   org-mode document because everything can be considered a one large
   word or a paragraph with flat `Word` content.

   Error node's extent covers all subnodes that were constructed
   during nested content parsing plus ErrorTerminator node with error
   token (description of the parsing failure). So failure node will be
   structured as `[Error <some content> <ErrorToken>
   <ErrorTermiator>]`. Second-to-last is the invalid token itself,
   error terminator will hold fake token that referes to an error.

   Error node can be produced by any parsing routine, although it is
   mostly used in the low-level text elements, since high-level
   structures are mostly detected based on the correct syntax - for
   example, `*** subtree` (and any title variations) can never be an
   error in itself. Title /text/ might contain an error, but invalid
   it is not possible to write an invalid subtree - it is either `*
   ANYTHING` or not a subtree at all.
   "))

     (d:efield "ErrorTerminator" (d:doc "Terminator node for failure in nested structure parsing"))
     (d:efield "ErrorToken" (d:doc "Single invalid token"))
     (d:efield "InlineStmtList" (d:doc ""))
     (d:efield "StmtList" (d:doc "List of statements, possibly recursive. Used as toplevel
                 part of the document, in recursive parsing of subtrees,
                 or as regular list, in cases where multiple subnodes have
                 to be grouped together."))

     (d:efield "AssocStmtList" (d:doc "Associated list of statements - AST elements like commands and links are grouped together if placed on adjacent lines"))
     (d:efield "Subtree" (d:doc "Section subtree"))
     (d:efield "SubtreeTimes" (d:doc "Time? associated with subtree entry"))
     (d:efield "SubtreeStars" (d:doc ""))
     (d:efield "Completion" (d:doc "Task compleation cookie, indicated either in percents of completion, or as `<done>/<todo>` ratio."))
     (d:efield "Checkbox" (d:doc "Single checkbox item like `[X]` or `[-]`"))
     (d:efield "List" (d:doc ""))
     (d:efield "Bullet" (d:doc "List item prefix"))
     (d:efield "ListItem" (d:doc ""))
     (d:efield "ListTag" (d:doc "Auxilliary wrapper for the paragraph placed at the start of the description list."))
     (d:efield "Counter" (d:doc ""))
     (d:efield "Comment" (d:doc "Inline or trailling comment. Can be used addition to `#+comment:`
   line or `#+begin-comment` section. Nested comment syntax is allowed
   (`#[ level1 #[ level2 ]# ]#`), but only outermost one is
   represented as separate AST node, everything else is a `.text`"))
     (d:efield "RawText" (d:doc "Raw string of text from input buffer. Things like particular syntax
   details of every single command, link formats are not handled in
   parser, deferring formatting to future processing layers "))
     (d:efield "Unparsed" (d:doc "Part of the org-mode document that is yet to be parsed. This node
   should not be created manually, it is only used for handling
   mutually recursive DSLs such as tables, which might include lists,
   which in turn might contain more tables in different bullet points."))
     (d:efield "Command" (d:doc "Undefined single-line command -- most likely custom user-provided oe"))
     (d:efield "CommandArguments" (d:doc "Arguments for the command block"))
     (d:efield "CommandTitle" (d:doc "`#+title:` - full document title"))
     (d:efield "CommandAuthor" (d:doc "`#+author:` Document author"))
     (d:efield "CommandCreator" (d:doc "`#+creator:` Document creator"))
     (d:efield "CommandInclude" (d:doc "`#+include:` - include other org-mode document (or subsection of it), source code or backend-specific chunk."))
     (d:efield "CommandLanguage" (d:doc "`#+language:`"))
     (d:efield "CommandAttrHtml" (d:doc "`#+attr_html:`"))
     (d:efield "CommandName" (d:doc "`#+name:` - name of the associated entry"))
     (d:efield "CommandHeader" (d:doc "`#+header:` - extended list of parameters passed to associated block"))
     (d:efield "CommandOptions" (d:doc "`#+options:` - document-wide formatting options"))
     (d:efield "CommandTblfm" (d:doc ""))
     (d:efield "CommandBackendOptions" (d:doc "Backend-specific configuration options like `#+latex_header` `#+latex_class` etc."))
     (d:efield "AttrImg" (d:doc ""))
     (d:efield "CommandCaption" (d:doc "`#+caption:` command"))
     (d:efield "File" (d:doc ""))
     (d:efield "BlockExport" (d:doc ""))
     (d:efield "InlineExport" (d:doc ""))
     (d:efield "MultilineCommand" (d:doc "Multiline command such as code block, latex equation, large block
   of passthrough code. Some built-in org-mode commands do not
   requires `#+begin` prefix, (such as `#+quote` or `#+example`) are
   represented by this type of block as well."))
     (d:efield "Result" (d:doc "Command evaluation result"))
     (d:efield "Ident" (d:doc "regular identifier - `alnum + [-_]` characters for punctuation.
   Identifiers are compared and parsed in style-insensetive manner,
   meaning `CODE_BLOCK`, `code-block` and `codeblock` are identical."))
     (d:efield "BareIdent" (d:doc "Bare identifier - any characters are allowed"))
     (d:efield "AdmonitionTag" (d:doc "Big ident used in conjunction with colon at the start of paragraph
   is considered an admonition tag: `NOTE: Text`, `WARNING: text` etc."))
     (d:efield "BigIdent" (d:doc "full-uppsercase identifier such as `MUST` or `TODO`"))
     (d:efield "VerbatimMultilineBlock" (d:doc "Verbatim mulitiline block that *might* be a part of
   `orgMultilineCommand` (in case of `#+begin-src`), but not
   necessarily. Can also be a part of =quote= and =example= multiline
   blocks."))
     (d:efield "CodeLine" (d:doc "Single line of source code"))
     (d:efield "CodeText" (d:doc "Block of source code text"))
     (d:efield "CodeTangle" (d:doc "Single tangle target in the code block"))
     (d:efield "CodeCallout" (d:doc "`(refs:` callout in the source code"))
     (d:efield "QuoteBlock" (d:doc "`#+quote:` block in code"))
     (d:efield "AdmonitionBlock" (d:doc ""))
     (d:efield "CenterBlock" (d:doc "'"))
     (d:efield "Example" (d:doc "Verbatim example text block"))
     (d:efield "SrcCode" (d:doc "Block of source code - can be multiline, single-line and"))
     (d:efield "SrcInlineCode" (d:doc "inline piece of code (such as `src_nim`). Latter is different from
     regular monospaced text inside of `~~` pair as it contains
     additional internal structure, optional parameter for code
     evaluation etc."))

     (d:efield "CallCode" (d:doc "Call to named source code block. Inline, multiline, or single-line."))
     (d:efield "PassCode" (d:doc "Passthrough block. Inline, multiline, or single-line. Syntax is
     `@@<backend-name>:<any-body>@@`. Has line and block syntax
     respectively"))
     (d:efield "CmdArguments" (d:doc "Command arguments"))
     (d:efield "CmdFlag" (d:doc "Flag for source code block. For example `-n`, which is used to to make source code block export with lines"))
     (d:efield "CmdKey" (d:doc ""))
     (d:efield "CmdValue" (d:doc ""))
     (d:efield "CmdNamedValue" (d:doc "Key-value pair for source code block call."))
     (d:efield "UrgencyStatus" (d:doc "Subtree importance level, such as `[#A]` or `[#B]`. Default
     org-mode only allows single character for contents inside of `[]`,
     but this parser makes it possible to use any regular identifier,
     such as `[#urgent]`."))
     (d:efield "TextSeparator" (d:doc "Long horizontal line `----`"))
     (d:efield "Paragraph" (d:doc "Single 'paragraph' of text. Used as generic container for any place
     in AST where unordered sentence might be encountered (e.g. caption, link description) - not limited
     to actual paragraph"))
     (d:efield "AnnotatedParagraph" (d:doc "Annotated paragraph -- a wrapper around a regular paragraph kind
     with added admonition, footnote, list tag prefix and similar types.
     `[fn:ID] Some Text` is an annotated paragraph, just like `NOTE:
     Text` or `- Prefix :: Body` (in this case list header is an
     annotated paragraph)"))
     (d:efield "Bold" (d:doc "Region of text with formatting, which contains standalone words -
     can itself contain subnodes, which allows to represent nested
     formatting regions, such as `*bold /italic/*` text. Particular type
     of identifier is stored in string form in `str` field for `OrgNode`
     -- bold is represented as `\"*\"`, italic as `/` and so on. In case
     of explicit open/close pairs only opening one is stored.

     NOTE: when structured sentences are enabled, regular punctuation
     elements like `some text (notes)` are also represented as `Word,
     Word, Markup(str: \"(\", [Word])` - e.g. structure is not fully flat."))
     (d:efield "Italic" (d:doc ""))
     (d:efield "Verbatim" (d:doc ""))
     (d:efield "Backtick" (d:doc ""))
     (d:efield "Underline" (d:doc ""))
     (d:efield "Strike" (d:doc ""))
     (d:efield "Quote" (d:doc ""))
     (d:efield "Angle" (d:doc ""))
     (d:efield "Monospace" (d:doc ""))
     (d:efield "Par" (d:doc ""))

     (d:efield "InlineMath" (d:doc "Inline latex math. Contains latex math body - either from `$dollar-wrapped$` or `\\(paren-wrapped\\)` inline text."))
     (d:efield "DisplayMath" (d:doc "Inline display latex math from `$$double-dollar$$` or `\\[bracket-wrapped\\]` code."))
     (d:efield "Space" (d:doc "Space or tab character in regular text"))
     (d:efield "Punctuation" (d:doc ""))
     (d:efield "Colon" (d:doc ""))
     (d:efield "Word" (d:doc "Regular word - technically not different from `orgIdent`, but
     defined separately to disiguish between places where special syntax
     is required and free-form text."))

     (d:efield "Escaped" (d:doc "Escaped formatting character in the text"))
     (d:efield "Newline" (d:doc ""))
     (d:efield "SkipNewline" (d:doc ""))
     (d:efield "SkipSpace" (d:doc ""))
     (d:efield "SkipAny" (d:doc ""))
     (d:efield "RawLink" (d:doc "Raw unwrapped link that was pasted in text"))
     (d:efield "Link" (d:doc "External or internal link. Consists of one or two elements - target
     (url, file location etc.) and description (`orgParagraph` of text).
     Description might be empty, and represented as empty node in this
     case. For external links particular formatting of the address is
     not handled by parser and instead contains raw string from input
     text."))

     (d:efield "Macro" (d:doc "Org-mode macro replacement - during export each macro is expanded
     and evaluated according to it's environment. Body of the macro is
     not parsed fully during org-mode evaluation, but is checked for
     correct parenthesis balance (as macro might contain elisp code)"))

     (d:efield "BackendRaw" (d:doc "Raw content to be passed to a particular backend. This is the most
     compact way of quoting export strings, after `#+<backend>:
     <single-backend-line>` and `#+begin-export <backend>`
     `<multiple-lines>`."))

     (d:efield "Symbol" (d:doc "Special symbol that should be exported differently to various
     backends - greek letters (`\alpha`), mathematical notations and so
     on."))

     (d:efield "TimeAssoc" (d:doc "Time association pair for the subtree deadlines."))
     (d:efield "StaticActiveTime" (d:doc ""))
     (d:efield "StaticInactiveTime" (d:doc ""))
     (d:efield "DynamicActiveTime" (d:doc ""))
     (d:efield "DynamicInactiveTime" (d:doc "Single date and time entry (active or inactive), possibly with
   repeater interval. Is not parsed directly, and instead contains
   `orgRawText` that can be parsed later"))

     (d:efield "TimeRange" (d:doc "Date and time range format - two `orgDateTime` entries"))
     (d:efield "SimpleTime" (d:doc "Result of the time range evaluation or trailing annotation a subtree"))
     (d:efield "Details" (d:doc "`#+begin_details`  section"))
     (d:efield "Summary" (d:doc "`#+begin_summary` section"))
     (d:efield "Table" (d:doc "Org-mode table. Tables can be writtein in different formats, but in
   the end they are all represented using single ast type. NOTE: it is
   not guaranteed that all subnodes for table are exactly
   `orgTableRow` - sometimes additional property metadata might be
   used, making AST like `Table[AssocStmtList[Command[_],
   TableRow[_]]]` possible"))

     (d:efield "TableRow" (d:doc "Horizontal table row"))
     (d:efield "TableCell" (d:doc "Single cell in row. Might contain anyting, including other tables, simple text paragraph etc."))

     (d:efield "InlineFootnote" (d:doc "Inline footnote with text placed directly in the node body."))
     (d:efield "Footnote" (d:doc "Footnote entry. Just as regular links - internal content is not
   parsed, and instead just cut out verbatim into target AST node."))

     (d:efield "Horizontal" (d:doc "Horizotal rule. Rule body might contain other subnodes, to represnt
   `---- some text ----` kind of formatting."))

     (d:efield "Filetags" (d:doc "`#+filetags:` line command"))
     (d:efield "OrgTag" (d:doc "Original format of org-mode tags in form of `:tagname:`. Might
   contain one or mode identifgiers, but does not provide support for
   nesting - `:tag1:tag2:`. Can only be placed within restricted set
   of places such as subtree headings and has separate place in AST
   when allowed (`orgSubtree` always has subnode `№4` with either
   `orgEmpty` or `orgOrgTag`)"))
     (d:efield "HashTag" (d:doc "More commonly used `#hashtag` format, with some additional
   extension. Can be placed anywere in the document (including section
   headers), but does not have separate place in AST (e.g. considered
   regular part of the text)"))

     (d:efield "MetaSymbol" (d:doc "`\\sym{}` with explicit arguments"))
     (d:efield "AtMention" (d:doc "`@user`"))
     (d:efield "BracTag" (d:doc "Custom extension to org-mode. Similarly to `BigIdent` used to have
   something like informal keywords `MUST`, `OPTIONAL`, but instead
   aimed /specifically/ at commit message headers - `[FEATURE]`,
   `[FIX]` and so on."))

     (d:efield "Drawer" (d:doc "Single enclosed drawer like `:properties: ... :end:` or `:logbook: ... :end:`"))
     (d:efield "LatexClass" (d:doc ""))
     (d:efield "LatexHeader" (d:doc ""))
     (d:efield "LatexCompiler" (d:doc ""))
     (d:efield "LatexClassOptions" (d:doc ""))
     (d:efield "HtmlHead" (d:doc ""))
     (d:efield "Columns" (d:doc "`#+columns:` line command for specifying formatting of the org-mode
   clock table visualization on per-file basis."))

     (d:efield "PropertyList" (d:doc ""))
     (d:efield "Property" (d:doc "Property entry, either in `#+property:` command, or in `:property:` drawer"))
     (d:efield "Placeholder" (d:doc "Placeholder entry in text, usually writte like `<text to replace>`"))
     (d:efield "SubtreeDescription" (d:doc "`:description:` entry"))
     (d:efield "SubtreeUrgency" (d:doc ""))
     (d:efield "Logbook" (d:doc "`:logbook:` entry storing note information"))
     (d:efield "LogbookEntry" (d:doc ""))
     (d:efield "LogbookStateChange" (d:doc "Annotation about change in the subtree todo state"))
     (d:efield "LogbookNote" (d:doc "Timestamped log note on the subtree"))
     (d:efield "LogbookClock" (d:doc "`CLOCK` entry in the subtree"))
     (d:efield "LogbookRefile" (d:doc "`Refile` entry in the subtree logbook drawer"))
     (d:efield "LogbookPriority" (d:doc "Change in the subtree priority"))
     (d:efield "LogbookPriorityChangeAction" (d:doc "Action to change subtree"))
     (d:efield "LogbookReschedule" (d:doc ""))
     (d:efield "LogbookTagChange" (d:doc ""))
     (d:efield "LogbookTagChangeAction" (d:doc ""))
     (d:efield "RadioTarget" (d:doc "`<<<RADIO>>>`"))
     (d:efield "Target" (d:doc "`<<TARGET>>`"))))

   (d:enum
    "OrgTextContext" (d:doc "")
    (list
     (d:efield "otcPlain" (d:doc ""))
     (d:efield "otcSubtree0" (d:doc ""))
     (d:efield "otcSubtree1" (d:doc ""))
     (d:efield "otcSubtree2" (d:doc ""))
     (d:efield "otcSubtree3" (d:doc ""))
     (d:efield "otcSubtree4" (d:doc ""))
     (d:efield "otcSubtree5" (d:doc ""))
     (d:efield "otcSubtree6" (d:doc ""))
     (d:efield "otcSubtree7" (d:doc ""))
     (d:efield "otcSubtree8" (d:doc ""))
     (d:efield "otcSubtree9" (d:doc ""))
     (d:efield "otcSubtree10" (d:doc ""))
     (d:efield "otcSubtree11" (d:doc ""))
     (d:efield "otcSubtree12" (d:doc ""))
     (d:efield "otcSubtreeOther" (d:doc ""))
     (d:efield "otcBold" (d:doc ""))
     (d:efield "otcItalic" (d:doc ""))
     (d:efield "otcStrike" (d:doc ""))
     (d:efield "otcUnderline" (d:doc ""))
     (d:efield "otcMonospaceInline" (d:doc ""))
     (d:efield "otcMonospaceBlock" (d:doc ""))))

   (d:enum
    "OrgBigIdentKind" (d:doc "")
    (list
     (d:efield "None" (d:doc ""))
     (d:efield "Must" (d:doc "MUST This word, or the terms \"REQUIRED\" or \"SHALL\", mean that the
   definition is an absolute requirement of the specification."))
     (d:efield "MustNot" (d:doc "MUST NOT This phrase, or the phrase \"SHALL NOT\", mean that the
   definition is an absolute prohibition of the specification."))
     (d:efield "Should" (d:doc "SHOULD This word, or the adjective \"RECOMMENDED\", mean that there
   may exist valid reasons in particular circumstances to ignore a
   particular item, but the full implications must be understood and
   carefully weighed before choosing a different course."))
     (d:efield "ShouldNot" (d:doc "SHOULD NOT This phrase, or the phrase \"NOT RECOMMENDED\" mean that
   there may exist valid reasons in particular circumstances when the
   particular behavior is acceptable or even useful, but the full
   implications should be understood and the case carefully weighed
   before implementing any behavior described with this label."))
     (d:efield "Required" (d:doc ""))
     (d:efield "Optional" (d:doc "MAY This word, or the adjective \"OPTIONAL\", mean that an item is
   truly optional. One vendor may choose to include the item because a
   particular marketplace requires it or because the vendor feels that
   it enhances the product while another vendor may omit the same
   item. An implementation which does not include a particular option
   MUST be prepared to interoperate with another implementation which
   does include the option, though perhaps with reduced functionality.
   In the same vein an implementation which does include a particular
   option MUST be prepared to interoperate with another implementation
   which does not include the option (except, of course, for the
   feature the option provides.)"))
     (d:efield "ReallyShouldNot" (d:doc ""))
     (d:efield "OughtTo" (d:doc ""))
     (d:efield "WouldProbably" (d:doc ""))
     (d:efield "MayWishTo" (d:doc ""))
     (d:efield "Could" (d:doc ""))
     (d:efield "Might" (d:doc ""))
     (d:efield "Possible" (d:doc ""))
     (d:efield "Todo" (d:doc ""))
     (d:efield "Idea" (d:doc ""))
     (d:efield "Error" (d:doc ""))
     (d:efield "Fixme" (d:doc ""))
     (d:efield "Doc" (d:doc ""))
     (d:efield "Refactor" (d:doc ""))
     (d:efield "Review" (d:doc ""))
     (d:efield "Hack" (d:doc ""))
     (d:efield "Implement" (d:doc ""))
     (d:efield "Example" (d:doc ""))
     (d:efield "Question" (d:doc ""))
     (d:efield "Assume" (d:doc ""))
     (d:efield "Internal" (d:doc ""))
     (d:efield "Design" (d:doc ""))
     (d:efield "Why" (d:doc ""))
     (d:efield "Wip" (d:doc ""))
     (d:efield "Fix" (d:doc ""))
     (d:efield "Clean" (d:doc ""))
     (d:efield "Feature" (d:doc ""))
     (d:efield "Style" (d:doc ""))
     (d:efield "Repo" (d:doc ""))
     (d:efield "Skip" (d:doc ""))
     (d:efield "Break" (d:doc ""))
     (d:efield "Poc" (d:doc ""))
     (d:efield "Next" (d:doc ""))
     (d:efield "Later" (d:doc ""))
     (d:efield "Postponed" (d:doc ""))
     (d:efield "Stalled" (d:doc ""))
     (d:efield "Done" (d:doc ""))
     (d:efield "Partially" (d:doc ""))
     (d:efield "Cancelled" (d:doc ""))
     (d:efield "Failed" (d:doc ""))
     (d:efield "Note" (d:doc ""))
     (d:efield "Tip" (d:doc ""))
     (d:efield "Important" (d:doc ""))
     (d:efield "Caution" (d:doc ""))
     (d:efield "Warning" (d:doc ""))
     (d:efield "UserCodeComment" (d:doc "User-defined comment message"))
     (d:efield "UserCommitMsg" (d:doc "User-defined commit message ident"))
     (d:efield "UserTaskState" (d:doc "User-defined task state"))
     (d:efield "UserAdmonition" (d:doc "User-defined admonition label"))
     (d:efield "Other" (d:doc "User-defined big-idents, not included in default set."))
     ;; It is not hard to support
     ;; https://en.wikipedia.org/wiki/Structured_English keywords. Maybe I
     ;; will merge it with haxdoc somehow, maybe not, for not I just placed
     ;; them here as a reminder to myself. My current idea is to overlay
     ;; semi-structured explanation in the documenation with actual code.
     ;; Structured keywords can be used as an anchor points (e.g. `IF` maps
     ;; to real condition, `THEN` to the body and so on).
     (d:efield "StructIf" (d:doc ""))
     (d:efield "StructAnd" (d:doc ""))
     (d:efield "StructOr" (d:doc ""))
     (d:efield "StructNot" (d:doc ""))
     (d:efield "StructGet" (d:doc ""))
     (d:efield "StructSet" (d:doc ""))
     (d:efield "StructThen" (d:doc ""))
     (d:efield "StructElse" (d:doc ""))
     (d:efield "StructWhile" (d:doc ""))))

   (d:enum
    "OrgTokenKind" (d:doc "")
    (list
     (d:efield "None" (d:doc ""))
     (d:efield "Eof" (d:doc ""))
     (d:efield "GroupStart" (d:doc "Start of the tokenizer token group"))
     (d:efield "GroupEnd" (d:doc "Tokenizer token group end"))
     (d:efield "ErrorTerminator" (d:doc ""))
     (d:efield "CommandPrefix" (d:doc ""))
     (d:efield "LineCommand" (d:doc ""))
     (d:efield "CommandBegin" (d:doc "`#+begin` part of the multiline command. `begin_<block-type>` is
   split into two tokens - `begin_` prefix and `ockBegin<block-type>`
   section."))
     (d:efield "CommandEnd" (d:doc ""))
     (d:efield "DoubleColon" (d:doc ""))
     (d:efield "Text" (d:doc ""))
     (d:efield "StmtList" (d:doc "Unlexed group of statements - used in the list content to enable
   secondary parsing."))
     (d:efield "StmtListOpen" (d:doc "Start of the expanded statement list content"))
     (d:efield "StmtListClose" (d:doc "End of the expanded statement list content"))
     (d:efield "ListStart" (d:doc "Start of the list token group"))
     (d:efield "ListItemStart" (d:doc "Start of the list item element"))
     (d:efield "ListClock" (d:doc "`CLOCK:` entry at the start of the logbook entry list"))
     (d:efield "ListPlus" (d:doc ""))
     (d:efield "ListStar" (d:doc ""))
     (d:efield "ListDescOpen" (d:doc "Start of the description list key,"))
     (d:efield "ListDescClose" (d:doc "End of the description list key `::`"))
     (d:efield "ListItemEnd" (d:doc "End of the list item"))
     (d:efield "ListEnd" (d:doc "Complete end of the list token group"))
     (d:efield "Checkbox" (d:doc "List or subtree checkbox"))
     (d:efield "SubtreeTodoState" (d:doc ""))
     (d:efield "SubtreeUrgency" (d:doc "Subtree importance marker"))
     (d:efield "SubtreeCompletion" (d:doc "Subtree completion marker"))
     (d:efield "SubtreeStars" (d:doc "Subtree prefix"))
     (d:efield "SubtreeTagSeparator" (d:doc ""))
     (d:efield "SubtreeTime" (d:doc ""))
     (d:efield "SubtreeEnd" (d:doc ""))
     (d:efield "ImplicitTime" (d:doc "You can write time ranges without any additional formatting for
   subtrees that have a diary timestamps. For example, you have a
   complex date predicate, but event occurs for `18:00-21:00`, so you
   write it in the random place in the subtree."))

     (d:efield "TimeDuration" (d:doc "Time duration for the `effort` property or time range length evaluation"))
     (d:efield "InactiveTimeBegin" (d:doc "Start of the inactive timestamp (`[2022-03-12]`)"))
     (d:efield "InactiveTimeEnd" (d:doc ""))
     (d:efield "ActiveTimeBegin" (d:doc "Start of the active timestamp `<2030-02-03>`"))
     (d:efield "ActiveTimeEnd" (d:doc ""))
     (d:efield "DynamicTimeContent" (d:doc "Dynamic time content"))
     (d:efield "StaticTimeDatePart" (d:doc "year-month-day part of the timestamp"))
     (d:efield "StaticTimeDayPart" (d:doc "weekday part of the timestamp"))
     (d:efield "StaticTimeClockPart" (d:doc "Clock part of the timestamp"))
     (d:efield "StaticTimeRepeater" (d:doc "Type of the time repeater: `+`, `++`, `.+`"))

     (d:efield "TimeDash" (d:doc "Separator dash between two periods in the time range (`<start>--<finish.`)"))
     (d:efield "TimeArrow" (d:doc "Time range evaluation arrow `[from]--[to] =>`"))
     (d:efield "Comment" (d:doc "line or inline comment"))
     (d:efield "ListDoubleColon" (d:doc "Double colon between description list tag and body"))
     (d:efield "CommandArgumentsBegin" (d:doc "List of command arguments"))
     (d:efield "CommandArgumentsEnd" (d:doc "End of the command arguments list"))
     (d:efield "CommandKey" (d:doc ""))
     (d:efield "CommandValue" (d:doc ""))
     (d:efield "CommandFlag" (d:doc ""))
     (d:efield "CommandBracket" (d:doc "`#+results[HASH...]`"))
     (d:efield "ColonLiteral" (d:doc "Literal block with `:`"))
     (d:efield "ColonIdent" (d:doc "Drawer or source code block wrappers with colon-wrapped
   identifiers. `:results:`, `:end:` etc."))

     (d:efield "ColonProperties" (d:doc "Start of the `:PROPERTIES:` block drawer block"))
     (d:efield "ColonDescription" (d:doc "Start of the `:description:` drawer block"))
     (d:efield "ColonEnd" (d:doc ""))
     (d:efield "ColonLogbook" (d:doc ""))
     (d:efield "RawLogbook" (d:doc ""))
     (d:efield "LogbookStart" (d:doc ""))
     (d:efield "LogbookEnd" (d:doc ""))
     (d:efield "RawProperty" (d:doc ""))
     (d:efield "Link" (d:doc "Any kind of link"))
     (d:efield "CommandContentStart" (d:doc ""))
     (d:efield "CommandContentEnd" (d:doc ""))
     (d:efield "CodeContent" (d:doc "Block of code inside `#+begin_src`"))
     (d:efield "CodeContentBegin" (d:doc "Start of the expanded code content"))
     (d:efield "CodeContentEnd" (d:doc "End of the expanded code content"))
     (d:efield "CodeText" (d:doc "Uninterrupted text span without newlines - either a whole line or
   sub subsection of it if callout or tangle elements were detected"))

     (d:efield "TableContent" (d:doc "Block of text inside `#+table`"))
     (d:efield "QuoteContent" (d:doc "`#+quote` content"))
     (d:efield "BackendPass"  (d:doc "Backend-specific passthrough"))
     (d:efield "LogBook"      (d:doc "Logbook including content"))
     (d:efield "Drawer"       (d:doc "Drawer including content"))
     (d:efield "Indent"       (d:doc "Increase in indentation"))
     (d:efield "Dedent"       (d:doc "Decrease in indentation"))
     (d:efield "SameIndent" (d:doc ""))
     (d:efield "NoIndent" (d:doc ""))
     (d:efield "BoldOpen" (d:doc ""))
     (d:efield "BoldClose" (d:doc ""))
     (d:efield "BoldInline" (d:doc ""))
     (d:efield "BoldInlineOpen" (d:doc ""))
     (d:efield "BoldInlineClose" (d:doc ""))
     (d:efield "ItalicOpen" (d:doc ""))
     (d:efield "ItalicClose" (d:doc ""))
     (d:efield "ItalicInline" (d:doc ""))
     (d:efield "ItalicInlineOpen" (d:doc ""))
     (d:efield "ItalicInlineClose" (d:doc ""))
     (d:efield "VerbatimOpen" (d:doc ""))
     (d:efield "VerbatimClose" (d:doc ""))
     (d:efield "VerbatimInline" (d:doc ""))
     (d:efield "VerbatimInlineOpen" (d:doc ""))
     (d:efield "VerbatimInlineClose" (d:doc ""))
     (d:efield "MonospaceOpen" (d:doc ""))
     (d:efield "MonospaceClose" (d:doc ""))
     (d:efield "MonospaceInline" (d:doc ""))
     (d:efield "MonospaceInlineOpen" (d:doc ""))
     (d:efield "MonospaceInlineClose" (d:doc ""))
     (d:efield "BacktickOpen" (d:doc ""))
     (d:efield "BacktickClose" (d:doc ""))
     (d:efield "BacktickInline" (d:doc ""))
     (d:efield "BacktickInlineOpen" (d:doc ""))
     (d:efield "BacktickInlineClose" (d:doc ""))
     (d:efield "UnderlineOpen" (d:doc ""))
     (d:efield "UnderlineClose" (d:doc ""))
     (d:efield "UnderlineInline" (d:doc ""))
     (d:efield "UnderlineInlineOpen" (d:doc ""))
     (d:efield "UnderlineInlineClose" (d:doc ""))
     (d:efield "StrikeOpen" (d:doc ""))
     (d:efield "StrikeClose" (d:doc ""))
     (d:efield "StrikeInline" (d:doc ""))
     (d:efield "StrikeInlineOpen" (d:doc ""))
     (d:efield "StrikeInlineClose" (d:doc ""))
     (d:efield "QuoteOpen" (d:doc ""))
     (d:efield "QuoteClose" (d:doc ""))
     (d:efield "Punctuation" (d:doc ""))
     (d:efield "LinkOpen" (d:doc ""))
     (d:efield "LinkClose" (d:doc ""))
     (d:efield "RawUrl" (d:doc ""))
     (d:efield "LinkTargetOpen" (d:doc ""))
     (d:efield "LinkTargetClose" (d:doc ""))
     (d:efield "LinkInternal" (d:doc "No protocol is used in the link, it is targeting some internal named entry."))
     (d:efield "LinkProtocol" (d:doc "Protocol used by the link - `file:`, `https:` etc."))
     (d:efield "LinkFull" (d:doc "Full token for the link, used in cases where it does not make sense
   to fracture the token - regular https URLs etc."))
     (d:efield "LinkPath" (d:doc "Link path for searches in file"))
     (d:efield "LinkTarget" (d:doc "Target of the link protocol that does not follow regular URI
   encoding scheme - for example `id:`, `elisp`, or `shell` links."))
     (d:efield "LinkExtraSeparator" (d:doc "Separator of the extra content in the link, `::`"))
     (d:efield "LinkExtra" (d:doc "Additional parametrization for the link search"))
     (d:efield "LinkDescriptionOpen" (d:doc ""))
     (d:efield "LinkDescriptionClose" (d:doc ""))
     (d:efield "TextSeparator" (d:doc ""))
     (d:efield "ParagraphStart" (d:doc "Fake token inserted by the lexer to delimit start of the paragraph"))
     (d:efield "ParagraphEnd" (d:doc ""))
     (d:efield "FootnoteStart" (d:doc ""))
     (d:efield "FootnoteEnd" (d:doc ""))
     (d:efield "Word" (d:doc "Regular word in the paragraph"))
     (d:efield "Escaped" (d:doc "Escaped character in plain text - `\\*`, `\\/` etc. Escaped characters and sequences thereof are treated like a regular plain text."))
     (d:efield "DoubleSlash" (d:doc "Put at the end of the lexer first logbook line to separate the  note, otherwise is treated as standalone escaped slash."))
     (d:efield "Newline" (d:doc "Explicit newline a paragraph"))
     (d:efield "SkipSpace" (d:doc ""))
     (d:efield "SkipNewline" (d:doc ""))
     (d:efield "SkipAny" (d:doc ""))
     (d:efield "MaybeWord" (d:doc ""))
     (d:efield "Space" (d:doc "Space in the paragraph"))
     (d:efield "BigIdent" (d:doc "`TODO`, `NOTE` and similar capitalized words"))
     (d:efield "RawText" (d:doc "Unparsed raw text, either as a part of paragraph or some embedded construction such as link address."))
     (d:efield "InlineSrc" (d:doc "Start of an inline source code block: `src_nim[]{}`"))
     (d:efield "InlineCall" (d:doc "Start of an inline call block: `call_name[]{}`"))
     (d:efield "CurlyStart" (d:doc "Start of the curly section of an inline source/call"))
     (d:efield "CurlyEnd" (d:doc "End of the curly section of an inline source/call"))
     (d:efield "SymbolStart" (d:doc "Unquoted `\\symbol` directly in the text"))
     (d:efield "Ident" (d:doc ""))
     (d:efield "DollarOpen" (d:doc "Opening dollar inline latex math"))
     (d:efield "DollarClose" (d:doc "Closing dollar for inline latex math"))
     (d:efield "DoubleDollarOpen" (d:doc "Opening `$` for inline latex"))
     (d:efield "DoubleDollarClose" (d:doc "Closing `$` for inline latex"))
     (d:efield "LatexParOpen" (d:doc "Opening `\\(` for inline latex math"))
     (d:efield "LatexParClose" (d:doc "Closing `\\)` for inline latex math"))
     (d:efield "LatexBraceOpen" (d:doc "Opening `\\[` for inline display latex equation"))
     (d:efield "LatexBraceClose" (d:doc "Closing `\\]` for inline display latex equation"))
     (d:efield "LatexInlineRaw" (d:doc "Content of the brace/par-enclosed math"))
     (d:efield "DoubleAt" (d:doc "Inline backend passthrough `@@`"))
     (d:efield "AtBracket" (d:doc "Inline annotation"))
     (d:efield "AtMention" (d:doc "`@user` mention in the text"))
     (d:efield "HashTag" (d:doc "Start of the inline hashtag `#tag`"))
     (d:efield "HashTagSub" (d:doc "Nested hashtag separator"))
     (d:efield "HashTagOpen" (d:doc "Start of the nested hashtag grop bracket"))
     (d:efield "HashTagClose" (d:doc "End of the nested hashtag group separator"))
     (d:efield "Comma" (d:doc "Comma - punctuation or a syntax element (e.g. for macro arguments)"))
     (d:efield "ParOpen" (d:doc "Paren open - punctuation or a syntax element"))
     (d:efield "ParClose" (d:doc "Paren close - punctuation or a syntax element"))
     (d:efield "Colon" (d:doc ""))
     (d:efield "Circumflex" (d:doc "`^` possible superscript in the text"))
     (d:efield "MacroOpen" (d:doc "Start of the macro call `{{{`"))
     (d:efield "MacroClose" (d:doc "Close of the macro call `}}}`"))
     (d:efield "MetaBraceOpen" (d:doc ""))
     (d:efield "MetaBraceBody" (d:doc ""))
     (d:efield "MetaBraceClose" (d:doc ""))
     (d:efield "MetaArgsOpen" (d:doc ""))
     (d:efield "MetaArgsBody" (d:doc ""))
     (d:efield "MetaArgsClose" (d:doc ""))
     (d:efield "SrcOpen" (d:doc ""))
     (d:efield "SrcName" (d:doc ""))
     (d:efield "SrcArgs" (d:doc ""))
     (d:efield "SrcBody" (d:doc ""))
     (d:efield "SrcClose" (d:doc ""))
     (d:efield "CallOpen" (d:doc ""))
     (d:efield "CallName" (d:doc ""))
     (d:efield "CallInsideHeader" (d:doc ""))
     (d:efield "CallArgs" (d:doc ""))
     (d:efield "EndHeader" (d:doc ""))
     (d:efield "CallClose" (d:doc ""))
     (d:efield "CmdArguments" (d:doc ""))
     (d:efield "TableBegin" (d:doc ""))
     (d:efield "TableEnd" (d:doc ""))
     (d:efield "CellBody" (d:doc "Unformatted table cell body"))
     (d:efield "RowSpec" (d:doc "`#+row` command together with parameters"))
     (d:efield "CellSpec" (d:doc "`#+cell` command with parameters"))
     (d:efield "Content" (d:doc "Temporary token created during initial content lexing"))
     (d:efield "ContentStart" (d:doc "Start of the table cell content section"))
     (d:efield "ContentEnd" (d:doc "End of the table cell content section"))
     (d:efield "PipeOpen" (d:doc ""))
     (d:efield "PipeSeparator" (d:doc "Vertical pipe (`|`) cell separator"))
     (d:efield "PipeClose" (d:doc ""))
     (d:efield "PipeCellOpen" (d:doc ""))
     (d:efield "DashSeparator" (d:doc "Horizontal dash (`---`, `:---`, `---:` or `:---:`) row separator"))
     (d:efield "CornerPlus" (d:doc "Corner plus (`+`)"))
     (d:efield "Command" (d:doc ""))
     (d:efield "CommandArgs" (d:doc ""))
     (d:efield "Body" (d:doc ""))
     (d:efield "LangName" (d:doc ""))
     (d:efield "DoubleAngleOpen" (d:doc "`<<` - open for noweb or anchor placeholder"))
     (d:efield "DoubleAngleClose" (d:doc "`>>` - close for noweb or anchor placeholder"))
     (d:efield "TripleAngleOpen" (d:doc "`<<<` - radio target open"))
     (d:efield "TripleAngleClose" (d:doc "`>>>` - radio target close"))
     (d:efield "AngleOpen" (d:doc "Placeholder open"))
     (d:efield "AngleClose" (d:doc "Placeholder close"))
     (d:efield "TextBlock" (d:doc "Code before noweb placeholder. Requires separate token to handle
   `##<<commented>>` - prefix comment should be duplicated for each
   line of the placeholder expansion."))))

   (d:enum
    "OrgCommandKind" (d:doc "")
    (list
     (d:efield "None" (d:doc ""))
     (d:efield "Include" (d:doc ""))
     (d:efield "Filetags" (d:doc ""))
     (d:efield "Setupfile" (d:doc ""))
     (d:efield "Columns" (d:doc ""))
     (d:efield "OtherProperty" (d:doc ""))
     (d:efield "BeginTable" (d:doc ""))
     (d:efield "EndTable" (d:doc "`#+table`"))
     (d:efield "Row" (d:doc "`#+row`"))
     (d:efield "Cell" (d:doc "`#+cell`"))
     (d:efield "BeginAdmonition" (d:doc ""))
     (d:efield "EndAdmonition" (d:doc ""))
     (d:efield "BeginDynamic" (d:doc ""))
     (d:efield "EndDynamic" (d:doc "`#+begin:`"))
     (d:efield "BeginCenter" (d:doc ""))
     (d:efield "EndCenter" (d:doc "`#+begin_center`"))
     (d:efield "BeginQuote" (d:doc ""))
     (d:efield "EndQuote" (d:doc "`#+quote`"))
     (d:efield "BeginSrc" (d:doc ""))
     (d:efield "EndSrc" (d:doc "`#+begin_src`"))
     (d:efield "BeginExport" (d:doc ""))
     (d:efield "EndExport" (d:doc "`#+end_export`"))
     (d:efield "BeginExample" (d:doc ""))
     (d:efield "EndExample" (d:doc ""))
     (d:efield "BeginDetails" (d:doc ""))
     (d:efield "EndDetails" (d:doc ""))
     (d:efield "BeginSummary" (d:doc ""))
     (d:efield "EndSummary" (d:doc ""))
     (d:efield "LatexClassOptions" (d:doc "`#+latex_class_options`"))
     (d:efield "LatexClass" (d:doc ""))
     (d:efield "LatexCompiler" (d:doc ""))
     (d:efield "AttrLatex" (d:doc "`#+attr_latex:`"))
     (d:efield "AttrImg" (d:doc "`#+attr_img:`"))
     (d:efield "AttrHtml" (d:doc "`#+attr_html:`"))
     (d:efield "HtmlHead" (d:doc "`#+html_head:`"))
     (d:efield "Language" (d:doc "`#+language:`"))
     (d:efield "Options"  (d:doc "`#+options: `"))
     (d:efield "Title"    (d:doc "`#+title:`"))
     (d:efield "Property" (d:doc "`#+property:`"))
     (d:efield "Author"   (d:doc "`#+author:`"))
     (d:efield "Bind"     (d:doc "`#+bind:`"))
     (d:efield "Creator"  (d:doc "`#+creator:`"))
     (d:efield "LatexHeader" (d:doc "`#+latex_header`"))
     (d:efield "Results"  (d:doc "`#+results:`"))
     (d:efield "Call"     (d:doc "`#+call:`"))
     (d:efield "Name"     (d:doc "`#+name:`"))
     (d:efield "Caption"  (d:doc "`#+caption:`"))
     (d:efield "Header"   (d:doc "`#+header:`"))
     (d:efield "TableFormula" (d:doc "`#+tblfm:`"))
     ))

   (d:enum
    "OrgPropertyKind" (d:doc "")
    (list
     (d:efield "Title" (d:doc ""))
     (d:efield "Author" (d:doc ""))
     (d:efield "Date" (d:doc ""))
     (d:efield "Email" (d:doc ""))
     (d:efield "Language" (d:doc ""))
     (d:efield "Url" (d:doc ""))
     (d:efield "SourceUrl" (d:doc ""))
     (d:efield "AttrImg" (d:doc ""))
     (d:efield "Toplevel" (d:doc ""))
     (d:efield "Blocker" (d:doc ""))
     (d:efield "Created" (d:doc ""))
     (d:efield "Unnumbered" (d:doc ""))
     (d:efield "Trigger" (d:doc ""))
     (d:efield "Ordered" (d:doc ""))
     (d:efield "Noblocking" (d:doc ""))
     (d:efield "ExportOptions" (d:doc ""))
     (d:efield "BackendExportOptions" (d:doc ""))
     (d:efield "AttrBackend" (d:doc ""))
     (d:efield "ColumnSpec" (d:doc ""))
     (d:efield "Name" (d:doc ""))
     (d:efield "Caption" (d:doc ""))
     (d:efield "LinkAbbrev" (d:doc ""))
     (d:efield "Filetags" (d:doc ""))
     (d:efield "TagConf" (d:doc ""))
     (d:efield "LatexHeader" (d:doc ""))
     (d:efield "OtherProperty" (d:doc ""))
     (d:efield "Id" (d:doc ""))))

   (d:enum
    "OrgUnnumberedKind" (d:doc "")
    (list
     (d:efield "Notoc" (d:doc ""))
     (d:efield "True" (d:doc ""))
     (d:efield "False" (d:doc ""))))

   (d:enum
    "OrgBlockLexerState" (d:doc "")
    (list
     (d:efield "None" (d:doc ""))
     (d:efield "InHeader" (d:doc ""))
     (d:efield "InBody" (d:doc ""))
     (d:efield "Ended" (d:doc ""))
     (d:efield "Complete" (d:doc ""))))))



(define* (get-concrete-types)
  (remove (lambda (struct) (not (slot-ref struct 'concreteKind))) types))

(define iterate-tree-context (make-fluid '()))
(define* (iterate-object-tree tree callback)
  ;; Trigger object structure iterator callback *before* updating scope values
  (apply callback (list tree))
  (with-fluids ((iterate-tree-context (append (fluid-ref iterate-tree-context) (list tree))))
    ;; Create a new dynamic scope value with the current object
    (cond
     ((instance? tree)
      ;; If any GOOPS object -- walk all slots
      (let* ((class-of-obj (class-of tree))
             (name (class-name class-of-obj))
             (slots (class-slots class-of-obj)))
        (for-each
         (lambda (slot)
           (iterate-object-tree
            (slot-ref tree (slot-definition-name slot)) callback)) slots)))
     ;; Primitive types cannot be walked over, end iteration
     ((or (eq? tree #t)
          (eq? tree #f)
          (string? tree)
          (symbol? tree)))
     ;; Walk over every item in list
     ((list? tree)
      (for-each (lambda (it) (iterate-object-tree it callback)) tree))
     ;; Otherwise, print the value -- if something is missing it will be added later
     (#t (format #t "? ~a\n" tree)))))

(define (get-nested-groups value)
  (remove (lambda (nested) (not (and (is-a? nested <group>) (slot-ref nested 'variantField))))
          (slot-ref value 'nested)))

(define (get-type-group-fields value)
  (map
   (lambda (group)
     ;; (format #t "~a ~a\n" (slot-ref group 'variantName) (slot-ref group 'variantField))
     (d:field (slot-ref group 'variantName)
              (slot-ref group 'variantField)
              (d:doc "")))
   (get-nested-groups value)))

(define base-map
  (let ((base (make-hash-table)))
    (iterate-object-tree
     types
     (lambda (obj)
       (when (is-a? obj <type>)
         (hashv-set! base (slot-ref obj 'name) obj))))
    (hashv-set! base 'Org (d:struct
                           'Org (d:doc "")
                           #:fields
                           (list
                            (d:field "OrgSemPlacement" "placementContext" (d:doc ""))
                            (d:field (t:vec "") "subnodes" (d:doc "")))))
    base))

(define (get-type-base-fields value)
  (apply
   append
   (map (lambda (base-sym)
          (let ((base (hashv-ref base-map base-sym)))
            (if base
                (append (slot-ref base 'fields)
                        (get-type-base-fields base))
                (begin
                  (format #t "No base object for ~a\n" base-sym)
                  (list)))))
        (slot-ref value 'bases))))

(define (get-exporter-methods forward)
  ;; Get exporter boilerplate method definitions (they walk over all fields)
  (let* ((methods (list)))
    (iterate-object-tree
     types
     (lambda (value)
       (when (and (instance? value) (is-a? value <type>))
         (let* ((scope-full (remove
                             (lambda (scope) (not (is-a? scope <type>)))
                             (fluid-ref iterate-tree-context)))
                ;; Parent type scope names
                (scope-names (map (lambda (type) (slot-ref type 'name)) scope-full))
                ;; This type name
                (name (slot-ref value 'name))
                ;; Fully scoped name of the type
                (full-scoped-name (append scope-names (list name)))
                ;; Collect immediate fields from an object
                (fields (remove (lambda (field) (slot-ref field 'isStatic))
                                ;; <struct> direct fields
                                (append (slot-ref value 'fields)
                                        ;; Recursively get base type fields
                                        (get-type-base-fields value)
                                        ;; Fields that were declared from the type group
                                        (get-type-group-fields value))))
                ;; Join scope arguments into the `::' and wrap everything into the `sem::' scope
                (scoped-target (format #f "CR<sem::~{~a~^::~}>" full-scoped-name))
                ;; TODO use properly structured data instead of these strings hacks.
                (decl-scope (if forward "" "Exporter<V, R>::"))
                (t-params (if forward #f (list (d:param "V") (d:param "R"))))
                (variant-methods
                 (map (lambda (group)
                        (d:method "void" (format #f "~avisit" decl-scope) (d:doc "")
                                  #:params t-params
                                  #:arguments
                                  (list (d:ident "R&" "res")
                                        (d:ident
                                         (format #f "CR<sem::~{~a::~}~a>"
                                                 full-scoped-name
                                                 (slot-ref group 'variantName)) "object"))
                                  #:impl
                                  (if forward #f
                                      ;; Use static kind getter to map variant value to
                                      (format #f "visitVariants(res, sem::~{~a::~}~a(object), object);"
                                              full-scoped-name (slot-ref group 'kindGetter)))))
                      (get-nested-groups value)))
                (method
                 (if (eq? 0 (length scope-full))
                     ;; If the object is a toplevel type entry -- provide a name-based `visitXXX'
                     ;; method implementation that will iterate over all fields
                     (d:method
                      "void" (format #f "~avisit~a" decl-scope name) (d:doc "")
                      #:params (if forward #f (list (d:param "V") (d:param "R")))
                      #:arguments (list (d:ident "R&" "res")
                                        ;; `In<>' is defined in the exporter
                                        (d:ident (format #f "In<sem::~a>" name) "object"))
                      #:impl (if forward #f
                                 ;; TODO this data ought to be generated based on the S-expr
                                 ;; builder, not this abominable string formatting. I mean,
                                 ;; it works, but OMG this is ugly.
                                 (format #f "__visit_specific_kind(res, object);\n~a"
                                         (format #f "~{__org_field(res, object, ~a); \n~}"
                                                 (map (lambda (a) (slot-ref a 'name)) fields)))))
                     ;; Otherwise, provide a subtype `visit' method implementation used for
                     ;; nested content definitions
                     (d:method
                      ;; Hacking field visitor name here, TODO -- implement proper scope passing
                      "void" (format #f "~avisit" decl-scope) (d:doc "")
                      #:params t-params
                      #:arguments (list (d:ident "R&" "res")
                                        (d:ident scoped-target "object"))
                      #:impl (if forward #f (format #f "~{__obj_field(res, object, ~a); \n~}"
                                                    (map (lambda (a) (slot-ref a 'name)) fields)))))))
           (set! methods (append methods variant-methods (list method)))))))
    methods))

(define nlp-enums
  (list
   (d:enum
    "NlpDepKind"
    (d:doc "Dependency kind")
    (list
     (d:efield "ROOT" (d:doc ""))
     (d:efield "acl" (d:doc ""))
     (d:efield "advcl" (d:doc ""))
     (d:efield "advmod" (d:doc ""))
     (d:efield "amod" (d:doc ""))
     (d:efield "appos" (d:doc ""))
     (d:efield "aux" (d:doc ""))
     (d:efield "_case" (d:doc ""))
     (d:efield "cc" (d:doc ""))
     (d:efield "ccomp" (d:doc ""))
     (d:efield "compound" (d:doc ""))
     (d:efield "conj" (d:doc ""))
     (d:efield "cop" (d:doc ""))
     (d:efield "csubj" (d:doc ""))
     (d:efield "dep" (d:doc ""))
     (d:efield "det" (d:doc ""))
     (d:efield "discourse" (d:doc ""))
     (d:efield "expl" (d:doc ""))
     (d:efield "fixed" (d:doc ""))
     (d:efield "iobj" (d:doc ""))
     (d:efield "mark" (d:doc ""))
     (d:efield "nmod" (d:doc ""))
     (d:efield "nsubj" (d:doc ""))
     (d:efield "nummod" (d:doc ""))
     (d:efield "obj" (d:doc ""))
     (d:efield "obl" (d:doc ""))
     (d:efield "parataxis" (d:doc ""))
     (d:efield "punct" (d:doc ""))
     (d:efield "ref" (d:doc ""))
     (d:efield "xcomp" (d:doc ""))
     )
    )
   (d:enum
    "NlpPosTag"
    (d:doc "Part of speech tag")
    (list
     (d:efield "ADJP" (d:doc ""))
     (d:efield "ADVP" (d:doc ""))
     (d:efield "ADD" (d:doc ""))
     (d:efield "AFX" (d:doc ""))
     (d:efield "CC" (d:doc ""))
     (d:efield "CD" (d:doc ""))
     (d:efield "CONJP" (d:doc ""))
     (d:efield "DT" (d:doc ""))
     (d:efield "EX" (d:doc ""))
     (d:efield "FRAG" (d:doc ""))
     (d:efield "FW" (d:doc ""))
     (d:efield "HYPH" (d:doc ""))
     (d:efield "IN" (d:doc ""))
     (d:efield "INTJ" (d:doc ""))
     (d:efield "JJ" (d:doc ""))
     (d:efield "JJR" (d:doc ""))
     (d:efield "JJS" (d:doc ""))
     (d:efield "LRB" (d:doc ""))
     (d:efield "LS" (d:doc ""))
     (d:efield "LST" (d:doc ""))
     (d:efield "MD" (d:doc ""))
     (d:efield "META" (d:doc ""))
     (d:efield "NAC" (d:doc ""))
     (d:efield "NFP" (d:doc ""))
     (d:efield "NML" (d:doc ""))
     (d:efield "NN" (d:doc ""))
     (d:efield "NNP" (d:doc ""))
     (d:efield "NNPS" (d:doc ""))
     (d:efield "NNS" (d:doc ""))
     (d:efield "NP" (d:doc ""))
     (d:efield "NPS" (d:doc ""))
     (d:efield "NP_TMP" (d:doc ""))
     (d:efield "PDT" (d:doc ""))
     (d:efield "POS" (d:doc ""))
     (d:efield "PP" (d:doc ""))
     (d:efield "PPZ" (d:doc ""))
     (d:efield "PRN" (d:doc ""))
     (d:efield "PRP" (d:doc ""))
     (d:efield "PRT" (d:doc ""))
     (d:efield "PUNCT_COLON" (d:doc ""))
     (d:efield "PUNCT_COMMA" (d:doc ""))
     (d:efield "PUNCT_PERIOD" (d:doc ""))
     (d:efield "PUNCT_QUOTE_CLOSE" (d:doc ""))
     (d:efield "PUNCT_QUOTE_OPEN" (d:doc ""))
     (d:efield "QP" (d:doc ""))
     (d:efield "RB" (d:doc ""))
     (d:efield "RBR" (d:doc ""))
     (d:efield "RBS" (d:doc ""))
     (d:efield "ROOT" (d:doc ""))
     (d:efield "RP" (d:doc ""))
     (d:efield "RRB" (d:doc ""))
     (d:efield "RRC" (d:doc ""))
     (d:efield "S" (d:doc ""))
     (d:efield "SBAR" (d:doc ""))
     (d:efield "SBARQ" (d:doc ""))
     (d:efield "SENT" (d:doc ""))
     (d:efield "SINV" (d:doc ""))
     (d:efield "SQ" (d:doc ""))
     (d:efield "SYM" (d:doc ""))
     (d:efield "TO" (d:doc ""))
     (d:efield "UCP" (d:doc ""))
     (d:efield "UH" (d:doc ""))
     (d:efield "VB" (d:doc ""))
     (d:efield "VBD" (d:doc ""))
     (d:efield "VBG" (d:doc ""))
     (d:efield "VBN" (d:doc ""))
     (d:efield "VBP" (d:doc ""))
     (d:efield "VBZ" (d:doc ""))
     (d:efield "VH" (d:doc ""))
     (d:efield "VHD" (d:doc ""))
     (d:efield "VHG" (d:doc ""))
     (d:efield "VHN" (d:doc ""))
     (d:efield "VHP" (d:doc ""))
     (d:efield "VHZ" (d:doc ""))
     (d:efield "VP" (d:doc ""))
     (d:efield "VV" (d:doc ""))
     (d:efield "VVD" (d:doc ""))
     (d:efield "VVG" (d:doc ""))
     (d:efield "VVN" (d:doc ""))
     (d:efield "VVP" (d:doc ""))
     (d:efield "VVZ" (d:doc ""))
     (d:efield "WDT" (d:doc ""))
     (d:efield "WHADJP" (d:doc ""))
     (d:efield "WHADVP" (d:doc ""))
     (d:efield "WHNP" (d:doc ""))
     (d:efield "WHPP" (d:doc ""))
     (d:efield "WP" (d:doc ""))
     (d:efield "WP_POS" (d:doc "Possessive wh-pronoun"))
     (d:efield "WRB" (d:doc ""))
     (d:efield "X" (d:doc ""))
     ))))

(define (in-namespace name l)
  (append
   (list (d:pass (format #f "namespace ~a {" name)))
   l
   (list (d:pass "}"))))

(define (with-enum-reflection-api body)
  (append
   (list
    (d:pass "#pragma once")
    (d:pass "#include <hstd/system/basic_templates.hpp>")
    (d:pass "#include <hstd/system/reflection.hpp>")
    (d:pass "#include <hstd/stdlib/Opt.hpp>"))
   body))

(d:full
 (list
  (d:unit
   (d:file "${base}/exporters/exporternlp_enums.hpp"
           (with-enum-reflection-api nlp-enums))

   #:source
   (d:file "${base}/exporters/exporternlp_enums.cpp"
           (append (list
                    (d:pass "#include \"exporternlp_enums.hpp\""))
                   nlp-enums)))
  (d:unit
   (d:file
    "${base}/exporters/Exporter.tcc"
    (append
     (get-exporter-methods #f))))
  (d:unit
   (d:file
    "${base}/exporters/ExporterMethods.tcc"
    (append (get-exporter-methods #t))))
  (let ((full-enums
         (append
          enums
          (list (d:enum
                 (t:osk)
                 (d:doc "")
                 (map (lambda (struct) (d:efield (slot-ref struct 'name) (d:doc ""))) (get-concrete-types)))))))
    (d:unit
     (d:file
      "${base}/sem/SemOrgEnums.hpp"
      (with-enum-reflection-api
       (append
        (list
         (d:pass (format #f "#define EACH_SEM_ORG_KIND(__IMPL) \\\n~{    __IMPL(~a) \\\n~}"
                         (map (lambda (struct) (slot-ref struct 'name)) (get-concrete-types)))))
        full-enums)))
     #:source
     (d:file "${base}/sem/SemOrgEnums.cpp"
             (append
              (list (d:pass "#include \"SemOrgEnums.hpp\""))
              full-enums))
     ))
  (d:unit
   (d:file
    "${base}/sem/SemOrgTypes.hpp"
    (list
     (d:pass "#pragma once")
     (d:include "sem/SemOrgEnums.hpp" #t)
     (d:include "hstd/stdlib/Vec.hpp" #t)
     (d:include "hstd/stdlib/Variant.hpp" #t)
     (d:include "hstd/stdlib/Time.hpp" #t)
     (d:include "hstd/stdlib/Opt.hpp" #t)
     (d:include "hstd/stdlib/Str.hpp" #t)
     (d:include "parse/OrgTypes.hpp" #t)
     (d:include "boost/describe.hpp" #t)
     (d:include "hstd/system/macros.hpp" #t)
     (d:include "functional" #t)
     (d:include "QDateTime" #t)
     (d:include "sem/SemOrgBase.hpp" #t)
     (d:include "sem/SemOrgEnums.hpp" #t)
     (d:namespace "sem" (list (d:group types #:enumName ""))))))))
