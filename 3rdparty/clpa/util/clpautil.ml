(* clpautil.ml
 *
 * Miscellaneous utility functions. 
 *)

module OrderedString = struct
  type t = string
  let compare (a:t) (b:t) = compare a b
end

let _ = Random.self_init()

let id x = x

let o f g x = f (g x)
let o3 f g h x = f (g (h x))
let inv f a b = f b a

let fst3 (x,_,_) = x
let snd3 (_,x,_) = x
let thd3 (_,_,x) = x

let get_some = function
    Some x -> x
  | None -> raise Not_found

let prepend lr v = lr := v::!lr

let swap (a,b) = (b,a)

let bytes_per_word = float_of_int (Sys.word_size / 8)

(* for help in using exception stack traces *)

let list_map f x =
  try List.map f x with Stack_overflow -> raise Stack_overflow
let list_fold_right f x y =
  try List.fold_right f x y with Stack_overflow -> raise Stack_overflow
let list_sort f x =
  try List.sort f x with Stack_overflow -> raise Stack_overflow
let list_merge f x y =
  try List.merge f x y with Stack_overflow -> raise Stack_overflow

let (@) a b = try a @ b with Stack_overflow -> raise Stack_overflow

(* folding *)

(* A combined map and fold_left, like in the Mercury standard library *)
let map_foldl (fn:'l -> 'a -> 'm * 'a) (ls:'l list) (a:'a) : ('m list * 'a) =
  let (rms, a') = List.fold_left 
        (fun (ms, a) l -> let (m, a') = fn l a in (m::ms, a')) ([], a) ls in
  (List.rev rms, a')

(* A combined map and filter, like a Haskell list comprehension *)
let map_filter (f:'a -> 'b option) (l:'a list) : ('b list) = 
  let rec map_filter_acc f l ys =
    match l with 
      | [] -> List.rev ys
      | x::xs -> (match f x with 
	  | None -> map_filter_acc f xs ys
	  | Some y -> map_filter_acc f xs (y::ys)
	) in
    map_filter_acc f l []

(* Create a list of n copies of x *)
let rec repeat (x:'a) (n:int) : ('a list) =
  if n < 1 then [] else x::(repeat x (n-1))

(* Search for an element satisfying a two-element predicate in a pair of
 * corresponding lists, raising Not_found if no such element exists *)
let rec find2 (f:'a -> 'b -> bool) (l:'a list) (m:'b list) : 'a * 'b =
  match (l,m) with
    | (x::xs, y::ys) -> if f x y then (x,y) else find2 f xs ys
    | _ -> raise Not_found

let fold_string fn a s =
  let len = String.length s in
  let rec fold a pos =
    if pos = len then a
    else fold (fn a s.[pos]) (pos + 1) in
  fold a 0

let fold_array2 fn a arr0 arr1 =
  if (Array.length arr0 <> Array.length arr1) then invalid_arg "fold_array2";
  let ar = ref a in
  let _ = Array.iteri (fun n _ -> ar := fn !ar arr0.(n) arr1.(n)) arr0 in
    !ar

let compare_lists fn l0 l1 =
  if List.length l0 = List.length l1 then
    List.fold_left2
      (fun cmp a0 a1 -> if cmp <> 0 then cmp else fn a0 a1) 0 l0 l1
  else if List.length l0 < List.length l1 then ~-1 else 1

let compare_arrays fn arr0 arr1 =
  if Array.length arr0 = Array.length arr1 then
    fold_array2
      (fun cmp a0 a1 -> if cmp <> 0 then cmp else fn a0 a1) 0 arr0 arr1
  else if Array.length arr0 < Array.length arr1 then ~-1 else 1

let exists_array fn arr =
  Array.fold_left (fun b -> o ((||) b) fn) false arr

let forall_array fn arr = not (exists_array (o not fn) arr)

let rmdups_list cmp list =
  List.fold_right (fun x xs ->
    match xs with
        [] -> [x]
      | x'::xs -> if cmp x x' = 0 then x'::xs else x::x'::xs) list []

let findopt_list fn list =
  let ro = List.fold_left (fun ro v -> match ro with
                               Some r -> Some r
                             | None -> fn v) None list in
    match ro with
        Some r -> r
      | None -> raise Not_found

let rec find_num fn i n =
  if i >= n then raise Not_found
  else if fn i then i
  else find_num fn (i + 1) n

let rec fold_num fn res i n =
  if i >= n then res
  else fold_num fn (fn i res) (i + 1) n

let rec fold_num_down fn res i n =
  if i <= n then res
  else fold_num_down fn (fn i res) (i - 1) n

let list_iteri fn list =
  for i = 0 to (List.length list - 1) do fn i (List.nth list i) done

(* strings *)

let string_map fn s =
  fold_num_down (fun i rem -> (fn s.[i]) ^ rem) "" (String.length s - 1) ~-1

let string_find s cs =
  let lens = String.length s in
  let lencs = String.length cs in
    find_num (fun i -> cs = String.sub s i lencs) 0 (lens - lencs + 1)

let string_contains s cs =
  try ignore (string_find s cs); true with Not_found -> false

let string_begins s cs =
  try string_find s cs = 0 with Not_found -> false

let sep_string_of_list sep tostring list =
  let buf = Buffer.create 10 in
  let dosep = ref false in
    List.iter (fun x ->
      (if !dosep then Buffer.add_string buf sep);
      dosep := true;
      Buffer.add_string buf (tostring x)) list;
    Buffer.contents buf

let sep_string_of_array sep tostring =
  o (sep_string_of_list sep tostring) Array.to_list

let alloc_string words =
  let bytes = words *. (float_of_int (Sys.word_size / 8)) in
  let kb = 1024. in
  let mb = 1024. *. kb in
  let gb = 1024. *. mb in
  let s = if bytes >= gb then
            Printf.sprintf "%.1fGB" (bytes /. gb)
          else if bytes >= mb then
            Printf.sprintf "%.1fMB" (bytes /. mb)
          else if bytes >= kb then
            Printf.sprintf "%.1fKB" (bytes /. kb)
          else
            Printf.sprintf "%.1fB" bytes in
    Printf.sprintf "%8s" s

let time_string secs =
  let secs = int_of_float secs in
  let hours = secs / 3600 in
  let minmod = (secs mod 3600) / 60 in
  let secmod = secs mod 60 in
  let secsp = if secmod < 10 then "0" else "" in
  let minsp = if minmod < 10 then "0" else "" in
  let s = if hours = 0 then Printf.sprintf "%d:%s%d" minmod secsp secmod
          else Printf.sprintf "%d:%s%d:%s%d" hours minsp minmod secsp secmod in
    Printf.sprintf "%8s" s

let unreachable () = failwith "Unreachable code executed"
