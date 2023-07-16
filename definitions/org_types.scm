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
 <type> d:struct
 (name)
 (brief-doc)
 (fields (list))
 (enums (list))
 (methods (list))
 (structs (list))
 (bases (list))
 (long-doc "")
 (kind "Struct"))

(simple-define-type
 <group> d:group
 (entries)
 (kind "Group"))

(simple-define-type
 <method> d:method
 (result)
 (name)
 (arguments (list))
 (is-const #f)
 (is-virtual #f)
 (kind "Method"))

(simple-define-type
 <field> d:field
 (type)
 (name)
 (value "")
 (kind "Field"))

(define (t:int) "int")
(define (t:str) "QString")
(define (t:vec arg) (format #f "Vec<~a>" arg))
(define* (t:id #:optional target)
  (if target (format #f "SemIdT<~a>" target) "SemId"))
(define* (t:opt arg) (format #f "Opt<~a>" arg))

(d:group
 (list
  (d:struct 'Org
            "Base class for org mode types"
            #:methods
            (list
             (d:method "SemOrgKind" "getKind" #:is-virtual #t #:is-const #t)
             (d:method "OrgNodeKind" "getOriginalKind" #:is-const #t))
            #:fields
            (list
             (d:field (t:opt "LineCol") "loc" #:value "std::nullopt"))
            )
  (d:struct 'Stmt
            "Base class for all document-level entries. Note that some node kinds
might also have inline entries (examples include links, source code blocks,
call blocks)"
            #:bases '(Org))
  )
 )
