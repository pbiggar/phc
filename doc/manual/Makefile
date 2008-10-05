## Makefile for the phc manual
## Requires docbook, jade, jadetex and docbook-dsssl

html: *.sgml manual.dtd manual.dsl
	jade -t sgml -d manual.dsl#html manual.sgml

manual.tex: *.sgml manual.dtd manual.dsl
	jade -t tex -d manual.dsl#print manual.sgml

manual.dvi: manual.tex
	jadetex manual.tex

manual.ps: manual.dvi
	dvips -o manual.ps manual.dvi

manual.pdf: manual.tex
	pdfjadetex manual.tex

clean:
	rm -f *.html
	rm -f manual.tex manual.dvi manual.ps manual.pdf
	rm -f manual.aux manual.log manual.out

images:
	phc --dump-dot=ast --no-nulls --no-empty-lists code/demo.php | dot -Tjpg -Gsize="12.5,11.3" > img/demo.jpg
