(use-modules (oop goops))

(define-class <type> ()
  (name #:init-keyword #:name)
  (brief-doc #:init-keyword #:brief-doc)
  (members #:init-keyword #:members #:init-value '())
  (bases #:init-keyword #:bases #:init-value '())
  (long-doc #:init-keyword #:long-doc #:init-value ""))

(define* (d:struct name brief-doc
                   #:key
                   (members '())
                   (bases '())
                   (long-doc ""))
  (make <type>
    #:name name
    #:brief-doc brief-doc
    #:members members
    #:bases bases
    #:long-doc long-doc))

(d:struct 'Org "Base class for org mode types" #:bases '(Some))
