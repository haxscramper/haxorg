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

(simple-define-type
 <doc> d:doc
 (brief)
 (full ""))

(simple-define-type
 <type> d:struct
 (name)
 (doc)
 (fields (list))
 (enums (list))
 (methods (list))
 (structs (list))
 (bases (list))
 (concreteKind #t)
 (kind "Struct"))

(simple-define-type
 <group> d:group
 (entries)
 (enumName "")
 (iteratorMacroName "")
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

(simple-define-type
 <field> d:field
 (type)
 (name)
 (doc)
 (value "")
 (kind "Field"))

(simple-define-type <ident> d:ident (type) (name) (value ""))

(define (t:int) "int")
(define (t:str) "QString")
(define (t:vec arg) (format #f "Vec<~a>" arg))
(define* (t:id #:optional target)
  (if target (format #f "SemIdT<~a>" target) "SemId"))
(define* (t:opt arg) (format #f "Opt<~a>" arg))
(define* (t:osk) "OrgSemKind")
(define* (t:cr arg) (format #f "CR<~a>" arg))

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
  )
 #:enumName "OrgSemKind"
 #:iteratorMacroName "EACH_ORG_SEM_KIND"
 )
