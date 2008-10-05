<!--
	Top-level structure of the phc manuals
	TODO: mention license

	To get HTML output, process this file with	
	
		jade -t sgml -d manual.dsl#html manual.sgml
	
	To get Latex output, process with

		jade -t tex -d manual.dsl#print manual.sgml
		jadetex manual.tex
-->
<!DOCTYPE set PUBLIC "-//phc//DTD DocBook V3.1-Based Extension//EN" "manual.dtd" [
<!-- User manual -->
<!ENTITY userintro SYSTEM "userintro.sgml">
<!ENTITY install SYSTEM "install.sgml">
<!ENTITY runningphc SYSTEM "runningphc.sgml">
<!-- Developers' manual -->
<!ENTITY devintro SYSTEM "devintro.sgml">
<!ENTITY gettingstarted SYSTEM "gettingstarted.sgml">
<!ENTITY treetutorial1 SYSTEM "treetutorial1.sgml">
<!ENTITY treetutorial2 SYSTEM "treetutorial2.sgml">
<!ENTITY treetutorial3 SYSTEM "treetutorial3.sgml">
<!ENTITY treetutorial4 SYSTEM "treetutorial4.sgml">
<!ENTITY treetutorial5 SYSTEM "treetutorial5.sgml">
<!ENTITY treetutorial6 SYSTEM "treetutorial6.sgml">
<!ENTITY grammar SYSTEM "grammar.sgml">
<!ENTITY representingphp SYSTEM "representingphp.sgml">
<!ENTITY limitations SYSTEM "limitations.sgml">
<!ENTITY porting SYSTEM "porting.sgml">
<!ENTITY apioverview SYSTEM "apioverview.sgml">
<!ENTITY maketeatheory SYSTEM "maketeatheory.sgml">
<!-- Couple of macro definitions -->
<!ENTITY phc "<reserved>phc</reserved>">
]>
<set id="manual">
<title>&phc Documentation</title>
<book id="usermanual">
	<title>The &phc User's Manual</title>
	&userintro
	&install
	&runningphc
</book>
<book id="devmanual">
	<title>The &phc Developer's Manual</title>
	&devintro
	<part id="treetutorials">
		<title id="treetutorials.title">Tree Traversal API Tutorials</title>
		&gettingstarted
		&treetutorial1
		&treetutorial2
		&treetutorial3
		&treetutorial4
		&treetutorial5
		&treetutorial6
	</part>
	<part id="reference">
		<title id="reference.title">Reference</title>
		&grammar
		&representingphp
		&limitations
		&apioverview
		&maketeatheory
	</part>
	<part id="guide">
		<!-- TODO: arrange these better -->
		<title id=guide.title>Development guide</title>
		&porting
	</part>

	<!-- TODO: things which should be discussed:
		developing phc:
			- Other IRs
			- testing
			- project page
			- prominent link to contribute
		folds
		describe compilation and generate-c
		None,Node
	-->

</book>
</set>
