% 1. make a test CFG
% 2. Get conditions on the CFG
% 3. Put dummy values for liveness/reaching-defs
% 4. Solve it

using intops.
import "../base/utility.clp".
using solve_bitvector.

% TODO: extend with a loop
% 0: entry
% 1: $VAR = 5;
% 2: if ($VAR)
% 3:  $X = 5; // DEAD
% else
% 4:  $Y = 7;
% 5: print ($Y)
% 6: exit
predicate cfg_edge (BB0:int, BB1:int).
predicate cfg_node (BB:int).
predicate branch (STATEMENT:int, COND:string, TRUE:int, FALSE:int) order [STATEMENT, TRUE] [STATEMENT, FALSE].
predicate join_fw (STATEMENT:int, PREDS:list[int]) order [PREDS, STATEMENT].


% Use variable_names as guards
type g_guard = bval[string].

% Get the guard for a statement
predicate guard(in STATMENT:int, out GUARD:g_guard) succeeds [once].


% Create the CFG
+cfg_edge (0,1).
+cfg_edge (1,2).
+cfg_edge (2,3).
+cfg_edge (2,4).
+cfg_edge (3,5).
%+cfg_edge (2,3).
%+cfg_edge (3,4).
+cfg_edge (4,5).
+cfg_edge (5,6).
+branch (2, "VAR", 3, 4).

% Create joins for statements with > 1 predecessor/successor
join_fw (STATEMENT, PREDS) :-
	cfg_edge (_, STATEMENT),
	\/(cfg_edge (PRED, STATEMENT)):list_all (PRED, PREDS),
	int_gt (list_length (PREDS), 1).

%join_bk (STATEMENT, SUCCS) :-
%	cfg_edge (STATEMENT, _),
%	\/(cfg_edge (STATEMENT, SUCC)):list_all (SUCC, SUCCS),
%	int_gt (list_length (SUCCS), 1).


cfg_edge (BB, _), +cfg_node (BB).
cfg_edge (_, BB), +cfg_node (BB).

% Entry is true
+guard (0, #bool_g (true)).

% Entry must be true as well.
%assert guard (6, true).

% Straight-line code
predicate straight_edge (BB0:int, BB1:int).

straight_edge (A, B) :-
	cfg_edge (A, B),
	~branch (A, _, _, _), ~join_fw (B, _).

straight_edge (A, B),
	guard (A, G),
	+guard (B, G).

% Branch
branch (_, COND, TRUE, FALSE),
	TRUE_GUARD = #id_g (COND),
	FALSE_GUARD = #not (TRUE_GUARD),
	+guard (TRUE, TRUE_GUARD),
	+guard (FALSE, FALSE_GUARD).

% Join
join_fw (STATEMENT, PREDS),
	guard_for_list (PREDS, G),
	+guard (STATEMENT, G).

%join_bk (STATEMENT, SUCCS),
%	guard_for_list (SUCCS, G),
%	+guard (STATEMENT, G).


predicate guard_for_list (in STATEMENTS:list[int], out g_guard) succeeds [once].
guard_for_list ([], #bool_g (false)) :- .
guard_for_list ([H|T], #or (guard (H), guard_for_list (T))) :- .


% Live variable analysis
predicate used (STATEMENT:int, VARS:string).
predicate defined (STATEMENT:int, VARS:string).
+defined (1, "VAR").
+defined (3, "X").
+defined (4, "Y").
+used (2, "VAR").
+used (5, "Y").

type live_info = bval[string].

predicate used_g (in STATEMENT:int, out LV:live_info) succeeds [once].

predicate defined_g (in STATEMENT:int, out LV:live_info) succeeds [once].

used (BB, VAR), +used_g (BB, #id_g (VAR)).
cfg_node (BB), ~used (BB, _), +used_g (BB, #bool_g (false)).
defined (BB, VAR), +defined_g (BB, #id_g (VAR)).
cfg_node (BB), ~defined  (BB, _), +defined_g (BB, #bool_g (false)).


predicate live_in (STATEMENT:int, live_info).
predicate live_out (STATEMENT:int, live_info).


+live_in (6, #bool_g (false)).

join_fw (STATEMENT, PREDS),
	list_mem (PREDS, P),
	live_in (STATEMENT, G),
	+live_out (P, G).

straight_edge (BB1, BB2),
	live_in (BB2, LV2),
	+live_out (BB1, LV2).

branch (BB, _, TRUE, FALSE),
	live_in (TRUE, LV_T),
	live_in (FALSE, LV_F),
	+live_out (BB, #or (LV_T, LV_F)).

%LV2/DEF U USE
cfg_node (BB),
	live_out (BB, LV2),
	+live_in (BB, #or (#and (LV2, #or (LV2, #not (defined_g (BB)))), used_g (BB))).

% OK, so there's a problem here. We add !VAR, which later cancels out VAR, even
% though the ordering is wrong. So perhaps we need to predicate each condition
% on its path?	

predicate is_killable (BB:int, VAR:string).

is_killable (BB, VAR) :-
	defined (BB, VAR),
	live_out (BB, G),
	#sat (#and (#id_g (VAR), #not (G))).


?- live_in (A, B).
?- live_out (A, B).
?- defined (A, B).
?- used (A, B).
?- is_killable (BB, X).
