(defun org-to-list-sexpr (el history)
  (mapcar (lambda (it) (org-to-simple-sexpr it (cons el history))) el))

(defun org-to-simple-sexpr (el &optional history)
  (unless history (setq history ()))
  (cond
   ((memq el history) "CYCLIC-REFERENCE")
   ((and (stringp el) (text-properties-at 0 el)) (substring-no-properties el))
   ((stringp el) el)
   ((numberp el) el)
   ((symbolp el) el)
   ((keywordp el) el)
   ((bufferp el) (buffer-file-name el))
   ((vectorp el) (org-to-list-sexpr el history))
   ((listp el) (org-to-list-sexpr el history))
   (() t (format "%s" el))))

(defun dump-org-element (path)
  (require 'org-element)
  (require 'cl)
  (save-window-excursion
    (save-excursion
      (with-temp-buffer
        (insert-file-contents path)
        (org-element-parse-buffer)
        (org-to-simple-sexpr (org-element-parse-buffer))))))
