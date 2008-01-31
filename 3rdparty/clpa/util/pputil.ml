(* Auxiliary pretty printing functions
 *
 * Author: Peter Hawkins <hawkinsp@cs.stanford.edu>
 *)

open Pp

(* Pretty print a list of items using the given separator *)
let ppListSep (items:doc list) (sep:doc) : doc  =
    match items with
    | []    -> empty
    | i::is -> List.fold_left (fun acc a -> acc ^^ sep ^^ a) i is

