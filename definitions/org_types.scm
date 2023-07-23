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
 (isVirtual #f)
 (isPureVirtual #f)
 (kind "Method"))

(simple-define-type <file> d:file (path) (entries))
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
    (slot-prepend!
     def 'nested (d:pass (format #f "using ~a::~a;" base base)))
    (when (slot-ref def 'concreteKind)
      (slot-prepend!
       def 'fields
       (d:field (t:osk) "staticKind" (d:doc "Document")
                #:isConst #t
                #:isStatic #t
                ;; #:value (format #f "~a::~a" (t:osk) kind)
                ))
      (slot-prepend!
       def 'methods
       (d:method (t:osk) "getKind" (d:doc "") #:isConst #t #:isVirtual #t #:isPureVirtual #f
                 #:impl (format #f "return ~a::~a;" (t:osk) kind)))
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
                          (d:field "bool" "extendLast" (d:doc "Continue numbering from the previous block instead of starting anew") #:value "false")
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

(define* (get-concrete-types)
  (remove (lambda (struct) (not (slot-ref struct 'concreteKind))) types))

(d:full
 (list
  (d:file
   "${base}/sem/SemOrgEnums.hpp"
   (list
    (d:pass "#pragma once")
    (d:enum
     (t:osk)
     (d:doc "")
     (map (lambda (struct) (d:efield (slot-ref struct 'name) (d:doc ""))) (get-concrete-types)))
    (d:pass (format #f "#define EACH_SEM_ORG_KIND(__IMPL) \\\n~{    __IMPL(~a) \\\n~}"
                    (map (lambda (struct) (slot-ref struct 'name)) (get-concrete-types))))))
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
    (d:pass "namespace sem {")
    (d:group types #:enumName "")
    (d:pass "} // namespace sem")))))
