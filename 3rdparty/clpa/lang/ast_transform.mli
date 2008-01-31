(*
 * Various AST transformations for CLPA programs
 *
 * Authors:
 *   Peter Hawkins  <hawkinsp@cs.stanford.edu>
 *
 * Copyright (c) 2005-2006,
 *   The Board of Trustees of The Leland Stanford Junior University
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 
 * 1. Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the following disclaimer.
 * 
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 * 
 * 3. The names of the contributors may not be used to endorse or promote
 * products derived from this software without specific prior written
 * permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *)

(* Quantifier and implication arrow expansion.
 * In this pass we perform the following transformations:
 * - all [X] G is replaced with ~ (some [X] ~G)
 * - G1 => G2 is replaced with ~(G1, ~G2) 
 *  
 * This pass is done before mode checking so we can remove any
 * useless double negations that are introduced by the unfolding process that
 * might make otherwise valid code ill-moded.
 *
 *)
val quant_unfold_rule: Ast.ast_rule -> Ast.ast_rule

(* Double negation elimination.
 *
 * Double negations can make otherwise well-moded programs ill-moded, so we
 * remove them before mode checking.
 *)
val neg_elim_rule: Ast.ast_rule -> Ast.ast_rule
