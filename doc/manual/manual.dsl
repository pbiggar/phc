<!DOCTYPE style-sheet PUBLIC "-//James Clark//DTD DSSSL Style Sheet//EN" [
<!ENTITY print-ss PUBLIC "-//Norman Walsh//DOCUMENT DocBook Print Stylesheet//EN" CDATA DSSSL>
<!ENTITY html-ss PUBLIC "-//Norman Walsh//DOCUMENT DocBook HTML Stylesheet//EN" CDATA DSSSL>
]>

<style-sheet>

<style-specification id="print" use="print-stylesheet">
<style-specification-body>

(element application
	(make sequence
		font-family-name: %mono-font-family%
		(process-children)
	)
)

(element reserved 
	(make sequence
		font-weight: 'bold
		(process-children)
	)
)

(element code
	(make sequence
		font-family-name: %mono-font-family%
		(process-children)
	)
)

(element boxed
	(make sequence
		;; This doesn't appear to work
		box-type: 'border
		(process-children)
	)
)

</style-specification-body>
</style-specification>

<style-specification id="html" use="html-stylesheet">
<style-specification-body>

(define xref.with.number.and.title 1)
(define %use-id-as-filename% #t)
(define %html-ext% ".html")
(define (chunk-element-list)
  (list (normalize "preface")
    (normalize "chapter")
    (normalize "appendix")
    (normalize "article")
    (normalize "glossary")
    (normalize "bibliography")
    (normalize "index")
    (normalize "colophon")
    (normalize "setindex")
    (normalize "reference")
    (normalize "refentry")
    (normalize "part")
    (normalize "book") ;; just in case nothing else matches...
    (normalize "set")  ;; sets are definitely chunks...
    ))

(element application
	(make element 
		gi:"tt" 
		(process-children)
	)
)

(element reserved 
	(make element 
		gi:"b" 
		(process-children)
	)
)

(element code
	(make element
		gi:"tt"
		(process-children)
	)
)

(element boxed 
	(make element
		gi:"span"
		attributes: '(("style" "border: solid 1px black; padding: 1px;"))
		(process-children)
	)
)

</style-specification-body>
</style-specification>

<external-specification id="print-stylesheet" document="print-ss">
<external-specification id="html-stylesheet" document="html-ss">

</style-sheet>
