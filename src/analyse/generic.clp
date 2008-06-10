import "src/generated/MIR.clp".

analyze session_name ("mir").

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


type t_generic ::= gnode{t_Node, list[t_generic]} % { ID, [PARAMS] }
					  | gmarker{bool}
					  | gstring{string}
					  | gint{int}
					  | glist{list[t_generic]}
					  | gmaybe{maybe[t_generic]}.

% Generics needed for this (to later be added straight from the IR with maketea).
%predicate get_type (in NODE:t_any, out TYPE:string).
%predicate unwrap (in WRAPPED:t_any, out UNWRAPPED:t_any).
%predicate sub_nodes (in NODE:t_any, out SUB_NODES:list[mir_type]).

% Generics for unwrap
%unwrap (any{statement_Global{N}}, any{N}) :- N = global_id{_}.
%unwrap (any{statement_Eval_expr{N}}, any{N}) :- N = eval_expr_id {_}.
%unwrap (any{statement_Assign_var{N}}, any{N}) :- N = assign_var_id {_}.
%unwrap (any{variable_name_VARIABLE_NAME{N}}, any{N}) :- N = vARIABLE_NAME_id{_}.
%unwrap (any{expr_Method_invocation{N}}, any{N}) :- N = method_invocation_id{_}.
%unwrap (any{expr_INT{N}}, any{N}) :- N = iNT_id {_}.
%unwrap (any{method_name_METHOD_NAME{N}}, any{N}) :- N = mETHOD_NAME_id{_}.


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
	+to_generic (any{ID}, gnode{node_PHP_script{ID}, [GEN_STATEMENTS]}).

mir()->method(ID, SIGNATURE, OPT_STATEMENTS),
	to_generic (any{SIGNATURE}, GEN_SIG), 
	((OPT_STATEMENTS = yes{STATEMENTS}, statements_to_generic_list (STATEMENTS, GEN_STATEMENTS), GEN_OPT_STATEMENTS = gmaybe{yes{GEN_STATEMENTS}})
		;
	(GEN_OPT_STATEMENTS = gmaybe{no})),
	+to_generic (any{ID}, gnode{node_Method {ID}, [GEN_SIG, GEN_OPT_STATEMENTS]}).

mir()->signature (ID, METHOD_MOD, IS_REF, METHOD_NAME, _),
	to_generic (any{METHOD_MOD}, GEN_METHOD_MOD),
	GEN_IS_REF = gmarker {IS_REF},
	to_generic (any{METHOD_NAME}, GEN_METHOD_NAME),
	+to_generic (any{ID}, gnode{node_Signature {ID}, [GEN_METHOD_MOD, GEN_IS_REF, GEN_METHOD_NAME, glist{[]}]}).

mir()->method_mod (ID, IS_PUBLIC, IS_PROTECTED, IS_PRIVATE, IS_STATIC, IS_ABSTRACT, IS_FINAL),
	GEN_IS_PUBLIC = gmarker{IS_PUBLIC},
	GEN_IS_PROTECTED = gmarker{IS_PROTECTED},
	GEN_IS_PRIVATE = gmarker{IS_PRIVATE},
	GEN_IS_STATIC = gmarker{IS_STATIC},
	GEN_IS_ABSTRACT = gmarker{IS_ABSTRACT},
	GEN_IS_FINAL = gmarker{IS_FINAL},
	+to_generic (any{ID}, gnode{node_Method_mod{ID}, [GEN_IS_PUBLIC, GEN_IS_PROTECTED, GEN_IS_PRIVATE, GEN_IS_STATIC, GEN_IS_ABSTRACT, GEN_IS_FINAL]}).

mir()->mETHOD_NAME (ID, VALUE),
	GEN_VALUE = gstring {VALUE},
	+to_generic (any{ID}, gnode{node_METHOD_NAME {ID}, [GEN_VALUE]}).

mir()->global (ID, VARIABLE_NAME),
	to_generic (any{VARIABLE_NAME}, GEN_VARIABLE_NAME),
	+to_generic (any{ID}, gnode{node_Global {ID}, [GEN_VARIABLE_NAME]}).

to_generic (any{variable_name_VARIABLE_NAME {VARIABLE_NAME}}, GENERIC) :-
	to_generic (any{VARIABLE_NAME}, GENERIC).

to_generic (any{expr_Variable {VARIABLE}}, GENERIC) :-
	to_generic (any{VARIABLE}, GENERIC).

to_generic (any{expr_INT {INT}}, GENERIC) :-
	to_generic (any{INT}, GENERIC).

to_generic (any{expr_Method_invocation {METHOD_INVOCATION}}, GENERIC) :-
	to_generic (any{METHOD_INVOCATION}, GENERIC).

to_generic (any{method_name_METHOD_NAME {METHOD_NAME}}, GENERIC) :-
	to_generic (any{METHOD_NAME}, GENERIC).

to_generic (any{statement_Global {GLOBAL}}, GENERIC) :-
	to_generic (any{GLOBAL}, GENERIC).

to_generic (any{statement_Assign_var {GLOBAL}}, GENERIC) :-
	to_generic (any{GLOBAL}, GENERIC).

to_generic (any{statement_Eval_expr {GLOBAL}}, GENERIC) :-
	to_generic (any{GLOBAL}, GENERIC).

mir()->vARIABLE_NAME (ID, VALUE),
	GEN_VALUE = gstring {VALUE},
	+to_generic (any{ID}, gnode{node_VARIABLE_NAME {ID}, [GEN_VALUE]}).

mir()->assign_var (ID, _, LHS, IS_REF, RHS),
	GEN_TARGET = gmaybe{no}, % TODO
	to_generic (any{LHS}, GEN_LHS),
	GEN_IS_REF = gmarker{IS_REF},
	to_generic (any{RHS}, GEN_RHS),
	+to_generic (any{ID}, gnode{node_Assign_var {ID}, [GEN_TARGET, GEN_LHS, GEN_IS_REF, GEN_RHS]}).

mir()->variable (ID, _, VARIABLE_NAME, _),
	GEN_TARGET = gmaybe{no}, % TODO
	to_generic (any{VARIABLE_NAME}, GEN_VARIABLE_NAME),
	GEN_ARRAY_INDICES = glist{[]},
	+to_generic (any{ID}, gnode{node_Variable {ID}, [GEN_TARGET, GEN_VARIABLE_NAME, GEN_ARRAY_INDICES]}).

mir()->iNT (ID, VALUE),
	GEN_VALUE = gint {VALUE},
	+to_generic (any{ID}, gnode{node_INT {ID}, [GEN_VALUE]}).

mir()->eval_expr (ID, EXPR),
	to_generic (any{EXPR}, GEN_EXPR),
	+to_generic (any{ID}, gnode{node_Eval_expr {ID}, [GEN_EXPR]}).

mir()->method_invocation (ID, _, METHOD_NAME, _),
	GEN_TARGET = gmaybe{no},
	to_generic (any{METHOD_NAME}, GEN_METHOD_NAME),
	+to_generic (any{ID}, gnode{node_Method_invocation {ID}, [GEN_TARGET, GEN_METHOD_NAME, glist{[]}]}).



% Generics for get_type
%mir()->global (ID, _), +get_type (any{ID}, "Global").
%mir()->eval_expr (ID, _), +get_type (any{ID}, "Eval_expr").
%mir()->assign_var(ID, _, _, _, _), +get_type (any{ID}, "Assign_var").
%mir()->vARIABLE_NAME(ID, _), +get_type (any{ID}, "VARIABLE_NAME").
%mir()->method_invocation (ID, _, _, _), +get_type (any{ID}, "Method_invocation").
%mir()->iNT (ID, _), +get_type (any{ID}, "INT").
%mir()->mETHOD_NAME (ID, _), +get_type (any{ID}, "METHOD_NAME").
%mir()->actual_parameter (ID, _, _, _, _), +get_type (any{ID}, "actual_parameter").
%
%% Generics for sub_nodes
%mir()->pHP_script 
%
%mir()->global (ID, VARIABLE_NAME),
%	+sub_nodes (any{ID}, [gnode{VARIABLE_NAME}]).
%
%mir()->eval_expr (ID, EXPR),
%	+sub_nodes (any{ID}, [gnode{EXPR}]).
%
%mir()->assign_var (ID, TARGET, VARIABLE_NAME, BY_REF, EXPR), 
%	+sub_nodes (any{ID}, [gmaybe[TARGET], gnode{VARIABLE_NAME}, gmarker{BY_REF}, gnode{EXPR}]).
%
%mir()->vARIABLE_NAME (ID, VALUE),
%	+sub_nodes (any{ID}, gvalue{VALUE}).
%
%mir()->method_invocation (ID, IS_REF, METHOD_NAME, PARAMS),
%	+sub_nodes (any{ID}, [gnode{METHOD_NAME}, glist{PARAMS}]).
%
%mir()->iNT (ID, VALUE),
%	+sub_nodes (any{ID}, gvalue{VALUE}).
%	
%mir()->mETHOD_NAME (ID, VALUE),
%	+sub_nodes (any{ID}, gvalue{VALUE}).
%
%mir()->actual_parameter (ID, IS_REF, TARGET, VARIABLE_NAME, []),
%	+sub_nodes (any{ID}, [any{VARIABLE_NAME}]).
%
%
%sub_nodes (WRAPPED, SUB_NODES) :-
%	unwrap (WRAPPED, UNWRAPPED),
%	sub_nodes (UNWRAPPED, SUB_NODES).
%
%

?- to_generic (any{pHP_script_id{ID}}, B).
%?- statements_to_generic_list (A, B).
