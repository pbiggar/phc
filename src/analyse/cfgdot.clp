import "cfg.clp".
import "src/generated/MIR.clp".

import "3rdparty/clpa/analysis/base/utility.clp".
using dotty.

% Build a .dot file to view the CFG

% Create dotty nodes and edges
predicate dotty_node (NODE:t_cfg_node, list[t_dg_attr]).
predicate dotty_edge (E1:t_cfg_node, E2:t_cfg_node, list[t_dg_attr]).

% Allow any user to annotation the CFG with strings.
predicate in_annotation (BB:t_cfg_node, ANNOTATION:string).
predicate out_annotation (BB:t_cfg_node, ANNOTATION:string).

% Nodes
dotty_node (N, [dg_attr{"label", NAME}]) :- cfg_node (N), N = nentry{METHOD}, get_method_name (METHOD, NAME).
dotty_node (N, [dg_attr{"label", NAME}]) :- cfg_node (N), N = nexit{METHOD}, get_method_name (METHOD, NAME).

predicate get_method_name (t_Method, string).
get_method_name (METHOD, NAME) :- 
	mir()->method (METHOD, SIG, _), 
	mir()->signature (SIG, _, _, NAME_ID, _), 
	mir()->mETHOD_NAME (NAME_ID, NAME).

% Normal statements (labelled with the SOURCE_REP and [ID])
dotty_node (N, Attrs) :- 
	cfg_node (N), 
	N = nblock{S},
	mir()->source_rep (any{S}, SOURCE),
	tostring (S, SSTRING), str_cat4 (SOURCE, "[", SSTRING, "]", LABEL),
	Attrs = [dg_attr{"label", LABEL}].


% Branches (labelled with the variable name)
dotty_node (N, Attrs) :- 
	cfg_node (N), 
	N = nbranch{B}, 
	mir()->source_rep (any{B}, VARNAME),
	tostring (B, BSTRING), str_cat4 (VARNAME, "\n[", BSTRING, "]", LABEL),
	Attrs = [dg_attr{"label", LABEL}, dg_attr{"shape", "rectangle"}].

% Edges (with labels if any in/out_annotations exist)
dotty_edge (E1, E2, Attrs) :- cfg_edge (E1, E2),
	\/(out_annotation (E1, S1), str_cat (S1, "\n", OUT)):list_all (OUT, OUTS),
	\/(in_annotation (E2, S2), str_cat (S2, "\n", IN)):list_all (IN, INS),
	str_cat_list (OUTS, OUTS_STR), str_cat_list (INS, INS_STR),
	str_cat_list (["OUT:\n-----\n", OUTS_STR, "\n\n\nIN:\n-----\n", INS_STR], LABEL),
	Attrs = [dg_attr{"label", LABEL}].


% Build the dotty graph
dotty_graph (NAME, true, dotgraph{Nodes, Edges}, [], [], []) :-
	((cfg_node (nentry{METHOD}), get_method_name (METHOD, NAME)) ; NAME = "UNKNOWN"),
	\/(dotty_node (DN, NAs), N = dg_node{DN, NAs}):list_all(N, Nodes),
	\/(dotty_edge (DE1, DE2, EAs), E = dg_edge{DE1, DE2, EAs}):list_all(E, Edges).


