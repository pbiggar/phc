%%
% Authors:
%   Brian Hackett  <bhackett@stanford.edu>
%
% Copyright (c) 2006,
%   The Board of Trustees of The Leland Stanford Junior University
% All rights reserved.
%
% Redistribution and use in source and binary forms, with or without
% modification, are permitted provided that the following conditions are met:
% 
% 1. Redistributions of source code must retain the above copyright notice,
% this list of conditions and the following disclaimer.
% 
% 2. Redistributions in binary form must reproduce the above copyright notice,
% this list of conditions and the following disclaimer in the documentation
% and/or other materials provided with the distribution.
% 
% 3. The names of the contributors may not be used to endorse or promote
% products derived from this software without specific prior written
% permission.
% 
% THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
% AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
% IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
% ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
% LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
% CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
% SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
% INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
% CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
% ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
% POSSIBILITY OF SUCH DAMAGE.
%%

% Loop handling in CFGs.

import "cilcfg.clp".

% PREDICATES

% split func/loop SUM has entry and exit points PIN and POUT
predicate sum_bound(SUM:sum,PIN:pp,POUT:pp) order [PIN,SUM] [POUT,SUM].

% P is in the split body of func/loop SUM, i.e. not contained in any inner loop
predicate sum_body(SUM:sum,P:pp) order [P,SUM].

% P1 is reachable from P0, some path through P0 passes through P1, P1 \= P0
predicate pp_reach(in P0:pp,P1:pp) order [P0,P1].

% P1 is reverse-reachable from P0, some path through P0 passed through P1, P1\=P0
predicate pp_reach_rev(in P0:pp,P1:pp) order [P1,P0].

% P1 is dominated by P0, any path through P1 passed through P0, P1 \= P0
predicate pp_dominate(in P0:pp,P1:pp) order [P0,P1].

% P1 is reverse-dominated by P0, all paths through P1 pass through P0, P1 \= P0
predicate pp_dominate_rev(in P0:pp,P1:pp) order [P1,P0].

% LOOP CONSTRUCTION

% default behavior for loops is to just break the back edges.
% - preserve_loops() preserves the back edges so the final CFG may be cyclic
% - split_loops() splits each loop off into a separate CFG
predicate preserve_loops().
predicate split_loops().

% the default for loops that are split off is to pick points for the loop body
% that minimize the size of the split body. this includes all points which are
% dominated by the loop head and can also reach one of the loop's back edges.
% these can be specified *in addition* to split_loops() to change this behavior
% - nesting_split_loops() picks a body that best approximates the actual
% statement/block nesting of the source code. thus 'return' or other statements
% which cannot reach a back edge will still be in the loop body if they are
% nested within the source program's while/for loop.
% - maximize_split_loops() picks a body of maximum size, including all points
% dominated by the loop head regardless of whether they can reach a back edge
predicate nesting_split_loops().
predicate maximize_split_loops().

% PREDICATES

% nodes and edges after cloning of irreducible loops (if any were found)
predicate cfgn_xirr(P:pp,N:cfg_node).
predicate cfge_xirr(P0:pp,P1:pp,E:cfg_edge).

% nodes and edges after removing loop back edges
predicate cfgn_loop(P:pp,N:cfg_node).
predicate cfge_loop(P0:pp,P1:pp,E:cfg_edge).

% RULES

% loop preservation

% if we're generating a loop-containing final CFG, finalize the original
% nodes/edges and mark the function as irreducible so we don't try to
% do any splitting or back edge breaking
preserve_loops(), cfgn(P,N), +cfgn_final(P,N).
preserve_loops(), cfge(P0,P1,E), +cfge_final(P0,P1,E).

% loop entry points

% drop duplicate loop heads sharing the same entry point (which we might get
% after denop'ing) and pick a canonical one to use
predicate dupe_loop(P:pp,PH:loop).
cfgn(P,nlooph{PH0}), cfgn(P,nlooph{PH1}), lessthan(PH0,PH1), +dupe_loop(P,PH1).

% P is the entry point of potential loop PH
predicate pos_lentry(PH:loop,P:pp).
cfgn(P,nlooph{PH}), ~dupe_loop(P,PH), +pos_lentry(PH,P).

% loop dominators

% potential loop PH does NOT dominate P. start at the function entry point,
% which no loops dominate, and propagate forward, stopping at the loop head
predicate nodom(PH:loop,P:pp).
cfgn(P,nentry), cfgn(_,nlooph{PH}), +nodom(PH,P).
cfge(P0,P1,_), nodom(PH,P0), ~pos_lentry(PH,P0), +nodom(PH,P1).

% loop identification

% P is in the body of loop PH
predicate lbody(PH:loop,P:pp).

% the edge (P0,P1,E) is a back edge on (real) loop PH
predicate backedge(PH:loop,P0:pp,P1:pp,E:cfg_edge).

% identify back edges, those going to a loop head whose source is dominated by
% that loop head. include the degenerate case with self edges on the head
% (in which case nodom is generated for the head)
pos_lentry(PH,P), cfge(XP,P,E), (~nodom(PH,XP); XP=P), +backedge(PH,XP,P,E).

% make sure we got all the back edges. any others are due to irreducible loops
% which we don't handle yet.
predicate lreach(PH:loop,P:pp).
predicate irreducible(PH:loop).
cfge(P0,P1,_), ~backedge(_,P0,P1,_), lreach(PH,P0), +lreach(PH,P1).
pos_lentry(PH,P), +lreach(PH,P), cfge(P0,P,_),
    lreach(PH,P0), ~backedge(PH,P0,P,_), +irreducible(PH).

% get SCCs of loopheads to get the overall irreducible loops. pick one loophead
% HEAD which will be used to represent this irreducible loop. note that this
% process will treat any inner reducible loops as part of the irreducible loop
predicate irreducible_set(PHS:list[loop],HEADPH:loop).
irreducible(PH), pos_lentry(PH,P),
    \/(irreducible(XPH), pos_lentry(XPH,XP),
       lreach(PH,XP), lreach(XPH,P)):list_all(XPH,PHSET), PHSET=[HEAD|_],
    +irreducible_set(PHSET,HEAD).

% recompute nodom for irreducible loops, getting points which are not dominated
% by the collective set of loop heads
predicate nodom_irr(PHS:list[loop],P:pp).
irreducible_set(PHS,_), cfgn(P,nentry), +nodom_irr(PHS,P).
cfge(P0,P1,_), nodom_irr(PHS,P0), ~(pos_lentry(PH,P0), list_mem(PHS,PH)),
    +nodom_irr(PHS,P1).

% get the irreducible loop back edges (well, side edges) going from any point
% dominated by the loop heads to one of the loop heads
predicate backedge_irr(PH:loop,P0:pp,P1:pp,E:cfg_edge).
irreducible_set(PHS,_), list_mem(PHS,PH), pos_lentry(PH,P), cfge(XP,P,E),
    (~nodom_irr(PHS,XP); list_mem(PHS,XPH), pos_lentry(XPH,XP)),
    +backedge_irr(PH,XP,P,E).

% loop body points

% P is the entry point of real loop PH which has a back edge. loops without
% back edges may result from some degenerate cases (do {...} while (0)) or
% 'goto' statements which don't create a loop. also update loophead()
% now that we know where the real loops are
predicate lentry(PH:loop,P:pp).
pos_lentry(PH,P), ~irreducible(PH), backedge(PH,PB,_,_),
    +loophead(PH), +lentry(PH,P), +lbody(PH,PB).
pos_lentry(PH,P), ~irreducible(PH), degenerate_infinite_loop(P),
    +loophead(PH), +lentry(PH,P).
irreducible_set(PHS,HEADPH), list_mem(PHS,PH),
    pos_lentry(PH,P), +loophead(PH), +lentry(HEADPH,P),
    backedge_irr(PH,PB,_,_), +lbody(HEADPH,PB).

predicate lreach_irr(PH:loop,P:pp).
lreach(PH,P), +lreach_irr(PH,P).
irreducible_set(PHS,HEAD), list_mem(PHS,PH), lreach(PH,P), +lreach_irr(HEAD,P).

% propagate lbody information back to the loop entry point
lbody(PH,P1), cfge(P0,P1,_), lreach_irr(PH,P0), +lbody(PH,P0).

% if we are matching the split loops to statement nestings,
% add any potential loop body points that are nested inside the loop itself.
% note that this will only work for while/for loops, not goto-created loops
predicate edge_nest(in E:cfg_edge,PH:loop).
edge_nest(easm{I},PH) :- instr_nest(I,S), stmt_nest_stmt(S,PH).
edge_nest(eset{I},PH) :- instr_nest(I,S), stmt_nest_stmt(S,PH).
edge_nest(ecall{I},PH) :- instr_nest(I,S), stmt_nest_stmt(S,PH).
edge_nest(ebtrue{E},PH) :- branch_nest(E,S), stmt_nest_stmt(S,PH).
edge_nest(ebfalse{E},PH) :- branch_nest(E,S), stmt_nest_stmt(S,PH).
nesting_split_loops(), lreach(PH,P), ~nodom(PH,P), ~cfgn(P,nexit),
    cfge(P,_,E), edge_nest(E,PH), +lbody(PH,P).

% if we are maximizing the size of split loops, add lbody for any point
% dominated by the loop entry (except the function exit)
maximize_split_loops(), lreach_irr(PH,P), ~nodom(PH,P), ~cfgn(P,nexit),
    +lbody(PH,P).

% get the entry, summary, and next-iteration point(s) for a loop.
% where P is an entry point for the loop, SUMP is the point for the summary
% edge if we split the loop off, and NEXTP is for breaking any back edges
% within the loop going to P
predicate loop_entry(PH:loop,P:pp,SUMP:pp,NEXTP:pp).
lentry(PH,P), ~irreducible(PH),
    +loop_entry(PH,P,p_lsum{PH},p_lnext{PH}).
irreducible_set(PHS,HEAD), list_mem(PHS,PH), lentry(PH,P),
    +loop_entry(HEAD,P,p_lsumi{HEAD,P},p_lnexti{HEAD,P}).

% add lbody information for special next/trec/sum/term points
loop_entry(PH,P,SUMP,NEXTP), +lbody(PH,P), lbody(OPH,P),
    +lbody(OPH,NEXTP), +lbody(OPH,p_ltrec{PH}),
    OPH\=PH, +lbody(OPH,SUMP).

% loop backedge removal

% handle individual CFG nodes, dropping the heads of loops missing backedges
cfgn(P,N), N\=nlooph{_}, +cfgn_loop(P,N).
cfgn(P,nlooph{_}), loop_entry(PH,P,_,_), +cfgn_loop(P,nlooph{PH}).

% replace P0->P1 with P0->NP1 to break back edges on loops in the function,
% introducing p_lnext and p_lnexti points
predicate backedge_target(P0:pp,P1:pp,E:cfg_edge,NP1:pp).
cfge(P0,P1,E), loop_entry(PH,P1,_,NEXTP), lbody(PH,P0),
    +backedge_target(P0,P1,E,NEXTP).

% handle individual CFG edges by breaking backedges where applicable
cfge(P0,P1,E), backedge_target(P0,P1,E,NP1), +cfge_loop(P0,NP1,E).
cfge(P0,P1,E), ~backedge_target(P0,P1,E,_), +cfge_loop(P0,P1,E).

% remove cfg_loop nodes/edges going to the loop head, replace with summary
predicate omit_cfgn_splitsum(P:pp,N:cfg_node).
predicate omit_cfge_splitsum(P0:pp,P1:pp,E:cfg_edge).

% remove edges exiting each loop, replace with p_lterm edges
predicate cfge_xloop(P0:pp,P1:pp,E:cfg_edge).
predicate omit_cfge_splitterm(P0:pp,P1:pp,E:cfg_edge).
predicate omit_cfge_splitnest(P0:pp,P1:pp,E:cfg_edge).

% loop splitting

% add the tail recursive invocation(s) for each split loop
split_loops(), cfge_loop(_,P,_), (P=p_lnext{PH}; P=p_lnexti{PH,_}),
    +cfge_xloop(P,p_ltrec{PH},eloop{PH}).
split_loops(), lentry(PH,P), degenerate_infinite_loop(P),
    +cfge_xloop(P,p_ltrec{PH},eloop{PH}).

% to split loops off from the rest of the function body, the loop head PH
% is first replaced with a summary point p_lsum{PH}. for each edge exiting
% the loop to P, an iloop is added from p_lsum{PH} to P, and the target is
% then replaced with the termination point p_lterm{PH,P}, isolating the loop
% body from the rest of the function

% replace the loop head with its summary point
split_loops(), loop_entry(PH,P,SUMP,_), cfgn_loop(P,N), N\=nlooph{PH},
    +omit_cfgn_splitsum(P,N), +cfgn_loop(SUMP,N).
split_loops(), loop_entry(PH,P,SUMP,_), cfge_loop(P0,P,E), ~lbody(PH,P0),
    +omit_cfge_splitsum(P0,P,E), +cfge_loop(P0,SUMP,E).
cfge_loop(P0,P1,E), ~omit_cfge_splitsum(P0,P1,E), +cfge_xloop(P0,P1,E).

% P is an lterm point for PH or a loop within PH
predicate inner_lterm(in PH:loop,in P:pp).
inner_lterm(PH,p_lterm{OPH,_}) :- loop_entry(OPH,EP,_,_), lbody(PH,EP).

% replace exit edges with edges to p_lterm, and add summary edges to the target
split_loops(), loop_entry(PH,_,SUMP,_), lbody(PH,P0), cfge_xloop(P0,P1,E),
    ~lbody(PH,P1), ~inner_lterm(PH,P1),
    +omit_cfge_splitterm(P0,P1,E),
    +cfge_xloop(SUMP,P1,eloop{PH}), +cfge_xloop(P0,p_lterm{PH,P1},E).

% for p_lterm edges exiting from within nested loops, we generate p_lterm edges
% for each level of nesting. get rid of all except for the innermost nesting
cfge_xloop(P0,p_lterm{PH,P1},E), cfge_xloop(P0,p_lterm{PH,p_lterm{_,P1}},E),
    +omit_cfge_splitnest(P0,p_lterm{PH,P1},E).

% finalizing

~preserve_loops(), cfgn_loop(P,N), ~omit_cfgn_splitsum(P,N), +cfgn_final(P,N).
~preserve_loops(), cfge_xloop(P0,P1,E), ~omit_cfge_splitterm(P0,P1,E),
    ~omit_cfge_splitnest(P0,P1,E), +cfge_final(P0,P1,E).

% add iloops aborting the program if a loop has no exit edges (is infinite)
~preserve_loops(), split_loops(), loop_entry(PH,_,SUMP,_),
    ~cfge_xloop(_,p_lterm{PH,_},_),
    +cfge_final(SUMP,p_abort,eloop{PH}).

% get a sum_bound() for the entire function do this after finalization because
% the entry point may also be a loop head and can change during splitting
entry(PIN), exit(POUT), +sum_bound(s_func,PIN,POUT).

% get sum_bound() for each entry and the tail recursive loop exit
~preserve_loops(), split_loops(), loop_entry(PH,P,_,_),
    +sum_bound(s_loop{PH},P,p_ltrec{PH}),

% get sum_bound() for each entry and any loop exit points within nestings
~preserve_loops(), split_loops(), loop_entry(PH,P,_,_),
    cfge_final(_,p_lterm{PH,P1},_),
    +sum_bound(s_loop{PH},P,p_lterm{PH,P1}).

% compute sum_body by following edges forward from func/loop entry points
sum_bound(SUM,P,_), +sum_body(SUM,P).
cfge_final(P0,P1,_), sum_body(SUM,P0), +sum_body(SUM,P1).

% point reachability/dominators

isum(P0,P1,I), ~sum_body(I,P0), +isum_norecurse(P0,P1,I).

% compute point reachability
pp_reach(P0,P1) :- cfge_final(P0,P1,_).
pp_reach(P0,P1) :- pp_reach(P0,MP), cfge_final(MP,P1,_).

pp_reach_rev(P0,P1) :- cfge_final(P1,P0,_).
pp_reach_rev(P0,P1) :- pp_reach_rev(P0,MP), cfge_final(P1,MP,_).

% compute point dominators by taking the negation of pp_nodom
predicate pp_nodom(in P0:pp,P1:pp).
pp_nodom(P0,P1) :- sum_body(SUM,P0), sum_bound(SUM,P1,_), P0\=P1.
pp_nodom(P0,P1) :- pp_nodom(P0,MP), cfge_final(MP,P1,_), P0\=P1.
pp_dominate(P0,P1) :- sum_body(SUM,P0), sum_body(SUM,P1), P0\=P1,
    ~pp_nodom(P0,P1).

predicate pp_nodom_rev(in P0:pp,P1:pp).
pp_nodom_rev(P0,P1) :- sum_body(SUM,P0), sum_bound(SUM,_,P1), P0\=P1.
pp_nodom_rev(P0,P1) :- pp_nodom_rev(P0,MP), cfge_final(P1,MP,_), P0\=P1.
pp_dominate_rev(P0,P1) :- sum_body(SUM,P0), sum_body(SUM,P1), P0\=P1,
    ~pp_nodom_rev(P0,P1).
