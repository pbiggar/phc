import "src/generated/MIR.clp".

% Generics for Calypso:

% Example:
%gnode {pHP_script{id},
%[
%	gnode {method{id},
%	[
%		gnode{Sig,
%		[
%			gnode{Method_mod,
%			[
%				gmarker{false},
%				gmarker{false},
%				gmarker{false},
%				gmarker{false},
%				gmarker{false},
%				gmarker{false}
%			]},
%			gmarker{false},
%			gnode{METHOD_NAME,
%			[
%				gstring("a")
%			]}
%		]}
%		glist{
%		[
%			gnode{Global,
%			[
%				gnode{Variable_NAME,
%				[
%					gstring {"x"}
%				]}
%			]}
%			...
%			gnode{Assign_var,
%			[
%				gmaybe{yes{gnode{Target,
%				[
%				]}}},
%				gnode{VARIABLE_NAME,
%				[
%					gstring{"x"},
%				]}
%				gmarker{false},
%				gnode{iNT,
%				[
%					gint{5}
%				]}
%			]},
%			gnode{Eval_expr,
%			[
%				gnode{Method_invocation,
%				[
%					gmaybe{no}, % TODO need type info here
%					gnode{METHOD_NAME,
%					[
%						gstring{"x"},
%					]},
%					gnode{Actual_param,
%					[
%						gmarker{false},
%						gmaybe{no},
%						gnode{VARIABLE_NAME,
%						[
%							gstring{"x"},
%						]}
%					]}
%				]}
%			]}
%		]},
%	]},
%]}


type t_generic ::= gnode{t_Node, list[t_generic]}	% a predicate ID, and a list of its arguments
					  | gmarker{bool}							% A Marker
					  | gstring{string}						% A string value
					  | gint{int}								% An int value
					  | glist{list[t_generic]}				% A list of generics
					  | gmaybe{maybe[t_generic]}.			% An optional generic

% Generics needed for this (to later be added straight from the IR with maketea).
predicate get_type (in NODE:t_Node, out TYPE:string).

% Generics
predicate to_generic (in ID:t_any, out GENERIC:t_generic).

% Lists to generic lists
predicate statements_to_generic_list (in IDS:list[t_Statement], out GENERICS:t_generic).
statements_to_generic_list ([], glist{[]}) :- .
statements_to_generic_list ([H|T], glist{GEN_LIST}) :- 
	statements_to_generic_list (T, GEN_T),
	to_generic (any{H}, GEN_H),
	GEN_T = glist{TAIL},
	list_append ([GEN_H], TAIL, GEN_LIST).


mir()->pHP_script(ID, STATEMENTS),
	statements_to_generic_list (STATEMENTS, GEN_STATEMENTS),
	GENERIC = gnode{node_PHP_script{ID}, [GEN_STATEMENTS]},
	+to_generic (any{ID}, GENERIC).

mir()->method(ID, SIGNATURE, OPT_STATEMENTS),
	to_generic (any{SIGNATURE}, GEN_SIG), 
	((OPT_STATEMENTS = yes{STATEMENTS}, statements_to_generic_list (STATEMENTS, GEN_STATEMENTS), GEN_OPT_STATEMENTS = gmaybe{yes{GEN_STATEMENTS}})
		;
	(GEN_OPT_STATEMENTS = gmaybe{no})),
	GENERIC = gnode{node_Method {ID}, [GEN_SIG, GEN_OPT_STATEMENTS]},
	+to_generic (any{ID}, GENERIC),
	+to_generic (any{statement_Method{ID}}, GENERIC).


mir()->signature (ID, METHOD_MOD, IS_REF, METHOD_NAME, _),
	to_generic (any{METHOD_MOD}, GEN_METHOD_MOD),
	GEN_IS_REF = gmarker {IS_REF},
	to_generic (any{METHOD_NAME}, GEN_METHOD_NAME),
	GENERIC = gnode{node_Signature {ID}, [GEN_METHOD_MOD, GEN_IS_REF, GEN_METHOD_NAME, glist{[]}]},
	+to_generic (any{ID}, GENERIC).

mir()->method_mod (ID, IS_PUBLIC, IS_PROTECTED, IS_PRIVATE, IS_STATIC, IS_ABSTRACT, IS_FINAL),
	GEN_IS_PUBLIC = gmarker{IS_PUBLIC},
	GEN_IS_PROTECTED = gmarker{IS_PROTECTED},
	GEN_IS_PRIVATE = gmarker{IS_PRIVATE},
	GEN_IS_STATIC = gmarker{IS_STATIC},
	GEN_IS_ABSTRACT = gmarker{IS_ABSTRACT},
	GEN_IS_FINAL = gmarker{IS_FINAL},
	GENERIC = gnode{node_Method_mod{ID}, [GEN_IS_PUBLIC, GEN_IS_PROTECTED, GEN_IS_PRIVATE, GEN_IS_STATIC, GEN_IS_ABSTRACT, GEN_IS_FINAL]},
	+to_generic (any{ID}, GENERIC).

mir()->mETHOD_NAME (ID, VALUE),
	GEN_VALUE = gstring {VALUE},
	GENERIC = gnode{node_METHOD_NAME {ID}, [GEN_VALUE]},
	+to_generic (any{ID}, GENERIC),
	+to_generic (any{method_name_METHOD_NAME{ID}}, GENERIC).

mir()->global (ID, VARIABLE_NAME),
	to_generic (any{VARIABLE_NAME}, GEN_VARIABLE_NAME),
	GENERIC = gnode{node_Global {ID}, [GEN_VARIABLE_NAME]},
	+to_generic (any{ID}, GENERIC),
	+to_generic (any{statement_Global{ID}}, GENERIC).

mir()->vARIABLE_NAME (ID, VALUE),
	GEN_VALUE = gstring {VALUE},
	GENERIC = gnode{node_VARIABLE_NAME {ID}, [GEN_VALUE]},
	+to_generic (any{ID}, GENERIC),
	+to_generic (any{variable_name_VARIABLE_NAME{ID}}, GENERIC).

mir()->assign_var (ID, _, LHS, IS_REF, RHS),
	GEN_TARGET = gmaybe{no}, % TODO
	to_generic (any{LHS}, GEN_LHS),
	GEN_IS_REF = gmarker{IS_REF},
	to_generic (any{RHS}, GEN_RHS),
	GENERIC = gnode{node_Assign_var {ID}, [GEN_TARGET, GEN_LHS, GEN_IS_REF, GEN_RHS]},
	+to_generic (any{ID}, GENERIC),
	+to_generic (any{statement_Assign_var{ID}}, GENERIC).

mir()->variable (ID, _, VARIABLE_NAME, _),
	GEN_TARGET = gmaybe{no}, % TODO
	to_generic (any{VARIABLE_NAME}, GEN_VARIABLE_NAME),
	GEN_ARRAY_INDICES = glist{[]},
	GENERIC = gnode{node_Variable {ID}, [GEN_TARGET, GEN_VARIABLE_NAME, GEN_ARRAY_INDICES]},
	+to_generic (any{ID}, GENERIC),
	+to_generic (any{expr_Variable{ID}}, GENERIC).


mir()->iNT (ID, VALUE),
	GEN_VALUE = gint {VALUE},
	GENERIC = gnode{node_INT {ID}, [GEN_VALUE]},
	+to_generic (any{ID}, GENERIC),
	+to_generic (any{expr_INT{ID}}, GENERIC).

mir()->eval_expr (ID, EXPR),
	to_generic (any{EXPR}, GEN_EXPR),
	GENERIC = gnode{node_Eval_expr {ID}, [GEN_EXPR]},
	+to_generic (any{ID}, GENERIC),
	+to_generic (any{statement_Eval_expr{ID}}, GENERIC).

mir()->method_invocation (ID, _, METHOD_NAME, _),
	GEN_TARGET = gmaybe{no},
	to_generic (any{METHOD_NAME}, GEN_METHOD_NAME),
	GENERIC = gnode{node_Method_invocation {ID}, [GEN_TARGET, GEN_METHOD_NAME, glist{[]}]},
	+to_generic (any{ID}, GENERIC),
	+to_generic (any{expr_Method_invocation{ID}}, GENERIC).



% Generics for get_type
mir()->global (ID, _),
	+get_type (node_Global{ID}, "Global").

mir()->eval_expr (ID, _),
	+get_type (node_Eval_expr{ID}, "Eval_expr").

mir()->method (ID, _, _),
	+get_type (node_Method {ID}, "Method").

mir()->signature (ID, _, _, _, _),
	+get_type (node_Signature {ID}, "Signature").

mir()->method_mod (ID, _, _, _, _, _, _),
	+get_type (node_Method_mod {ID}, "Method_mod").

mir()->assign_var(ID, _, _, _, _),
	+get_type (node_Assign_var{ID}, "Assign_var").

mir()->vARIABLE_NAME(ID, _),
	+get_type (node_VARIABLE_NAME{ID}, "VARIABLE_NAME").

mir()->method_invocation (ID, _, _, _),
	+get_type (node_Method_invocation{ID}, "Method_invocation").

mir()->iNT (ID, _),
	+get_type (node_INT{ID}, "INT").

mir()->mETHOD_NAME (ID, _),
	+get_type (node_METHOD_NAME{ID}, "METHOD_NAME").

mir()->actual_parameter (ID, _, _, _, _),
	+get_type (node_Actual_parameter{ID}, "actual_parameter").


%?- to_generic (A, B).
