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



% Unparse individual NODE attributes
predicate to_xml_attr (in KEY:string, in VAL:t_Attr, out XML:string).
to_xml_attr (KEY, attr_str{VAL}, XML) :-
	str_cat_list (
		["<attr key=\"", KEY, "\"><string>", VAL, "</string></attr>\n"],
		XML).


to_xml_attr (KEY, attr_int{VAL}, XML) :-
	tostring (VAL, VAL_STRING),
	str_cat_list (
		["<attr key=\"", KEY, "\"><integer>", VAL_STRING, "</integer></attr>\n"],
		XML).

to_xml_attr (KEY, attr_bool{VAL}, XML) :-
	tostring (VAL, VAL_STRING),
	str_cat_list (
		["<attr key=\"", KEY, "\"><bool>", VAL_STRING, "</bool></attr>\n"],
		XML).

% TODO error for attr_unavailable

% Unparse lists of NODE attributes
predicate to_xml_attrs (in NODE:t_Node, out XML:string).
to_xml_attrs (NODE, XML) :-
	\/(mir()->attr(NODE, KEY, VAL), to_xml_attr (KEY, VAL, ATTR_XML)):list_all (ATTR_XML, XMLS),
	(( XMLS = [], XML = "<attrs />\n")
	;
	( XMLS \= [],
	str_cat_list (XMLS, XML_ATTRS),
	str_cat_list (["<attrs>\n", XML_ATTRS, "</attrs>\n"], XML))).


% Unparse lists of NODEs
predicate to_xml_string_list (in GENERICS:list[t_generic], out XML:string).
to_xml_string_list ([], "") :- .
to_xml_string_list ([H|T], XML) :- 
	to_xml_string (H, STR),
	to_xml_string_list (T, STRS),
	str_cat (STR, STRS, XML).


% Unparse generics
predicate to_xml_string (in GENERIC:t_generic, out XML:string).

% Unparse NODEs
to_xml_string (gnode{NODE, NAME, SUBNODES}, XML) :-
	to_xml_string_list (SUBNODES, SUBXML),
	to_xml_attrs (NODE, ATTR_XML),
	str_cat_list([
							"<MIR:", NAME, ">\n",
							ATTR_XML, 
							SUBXML, 
							"</MIR:", NAME, ">\n"
						],
						XML).


% Unparse lists
to_xml_string (glist{TYPE, LIST}, XML) :-
	to_xml_substring (glist{TYPE, LIST}, SUBXML),
	str_cat_list (["<MIR:", TYPE, "_list>\n", 
						SUBXML, 
						"</MIR:", TYPE, "_list>\n"],
						XML).

predicate to_xml_substring (in LIST:t_generic, out XML:string). 
to_xml_substring (glist{_, []}, "") :- .
to_xml_substring (glist{_, [H|T]}, XML) :-
	to_xml_substring (glist{"", T}, XML_T),
	to_xml_string (H, XML_H),
	str_cat_list ([XML_H, XML_T], XML).
	


% Unparse maybes	
to_xml_string (gmaybe{NAME, no}, XML) :- 
	str_cat_list (["<MIR:", NAME, " xsi:nil=\"true\" />\n"], XML).

to_xml_string (gmaybe{_, yes{GENERIC}}, XML) :- 
	to_xml_string (GENERIC, XML).


% Unparse literals
to_xml_string (gint{VALUE}, XML) :-
	tostring (VALUE, XML_VALUE),
	str_cat_list (["<value>", XML_VALUE, "</value>\n"], XML).

% To avoid superfluous differences with phc's unparsed XML, uppercase the first letter.
to_xml_string (gbool{true}, XML) :-
	str_cat_list (["<value>True</value>\n"], XML).
to_xml_string (gbool{false}, XML) :-
	str_cat_list (["<value>False</value>\n"], XML).

to_xml_string (gfloat{VALUE}, XML) :-
	tostring (VALUE, XML_VALUE),
	str_cat_list (["<value>", XML_VALUE, "</value>\n"], XML).

to_xml_string (gstring{VALUE}, XML) :- 
	str_to_base64 (VALUE, BASE64),
	((VALUE = BASE64, ENCODING = "");(VALUE \= BASE64, ENCODING = " encoding=\"base64\"")),
	str_cat_list (["<value", ENCODING, ">", BASE64, "</value>\n"], XML).


% Unparse markers
to_xml_string (gmarker{NAME, VALUE}, XML) :- 
	tostring (VALUE, XML_VALUE),
	str_cat_list (["<bool><!-- ", NAME, " -->", XML_VALUE, "</bool>\n"], XML).
