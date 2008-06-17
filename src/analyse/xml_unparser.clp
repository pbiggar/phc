import "cfgdot.clp".

using base64.


% Initially, just dump the CFG in any order. After that, we can work on
% putting the CFG back into a list of statements with labels and gotos. Then,
% we merge all functions, and re-read it with --read-xml=clar.

analyze session_name ("cfg").

% Turn this method into XML
cfg_node (nentry{METHOD}),
	to_node (any{METHOD}, NODE), to_generic (NODE, GENERIC),
	to_xml_string (GENERIC, XML),
	+print(XML).



predicate to_xml_string_list (in GENERICS:list[t_generic], out XML:string).
to_xml_string_list ([], "") :- .
to_xml_string_list ([H|T], XML) :- 
	to_xml_string (H, STR),
	to_xml_string_list (T, STRS),
	str_cat (STR, STRS, XML).


% Convert generics to XML
predicate to_xml_string (in GENERIC:t_generic, out XML:string).

to_xml_string (gnode{NODE, NAME, SUBNODES}, XML) :-
	to_xml_string_list (SUBNODES, SUBXML),
	str_cat_list(["<MIR:", NAME, ">\n", SUBXML, "</MIR:", NAME, ">\n"], XML).


predicate to_xml_substring (in LIST:t_generic, out XML:string). 
to_xml_substring (glist{_, []}, "") :- .
to_xml_substring (glist{_, [H|T]}, XML) :-
	to_xml_substring (glist{"", T}, XML_T),
	to_xml_string (H, XML_H),
	str_cat_list ([XML_H, XML_T], XML).
	


to_xml_string (glist{TYPE, LIST}, XML) :-
	to_xml_substring (glist{TYPE, LIST}, SUBXML),
	str_cat_list (["<MIR:", TYPE, "_list>\n", 
						SUBXML, 
						"</MIR:", TYPE, "_list>\n"],
						XML).

	
to_xml_string (gmaybe{NAME, no}, XML) :- 
	str_cat_list (["<MIR:", NAME, " xsi:nil=\"true\" />\n"], XML).

to_xml_string (gmaybe{_, yes{GENERIC}}, XML) :- 
	to_xml_string (GENERIC, XML).

to_xml_string (gint{VALUE}, XML) :-
	tostring (VALUE, XML_VALUE),
	str_cat_list (["<value>", XML_VALUE, "</value>\n"], XML).
to_xml_string (gbool{VALUE}, XML) :-
	tostring (VALUE, XML_VALUE),
	str_cat_list (["<value>", XML_VALUE, "</value>\n"], XML).

to_xml_string (gfloat{VALUE}, XML) :-
	tostring (VALUE, XML_VALUE),
	str_cat_list (["<value>", XML_VALUE, "</value>\n"], XML).

to_xml_string (gstring{VALUE}, XML) :- 
	str_to_base64 (VALUE, BASE64),
	str_cat_list (["<value>", BASE64, "</value>\n"], XML).

to_xml_string (gmarker{NAME, VALUE}, XML) :- 
	tostring (VALUE, XML_VALUE),
	str_cat_list (["<bool><!-- ", NAME, " -->", XML_VALUE, "</bool>\n"], XML).

% debugging
%?- to_xml_string (A, B).

%?- to_node (A, B).
%?- get_type (A, B).
