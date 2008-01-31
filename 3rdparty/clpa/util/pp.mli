(*  
    $Id: pp.mli,v 1.1.1.1 1999/06/13 12:55:05 lindig Exp $

    This module provides a pretty printer.  Documents are built
    from a set of primitives which later can be formatted for
    different line length.  The pretty printer is intended for tree
    like structures like source code.  It does not provide a two
    dimensional layout like TeX for example.  This pretty printer is
    heavily inspired by a pretty printer  proposed by Philip Wadler in
    his paper "A prettier printer" available from his home page and to 
    appear in the Journal of Functional Programming in 1999. 
*)
(*  From the COPYING file in the original distribution:
    Copyright (c) 1998 Christian Lindig <lindig@ips.cs.tu-bs.de>.
    All rights reserved.

    Redistribution and use in source and binary forms, with or without
    modification, are permitted provided that the following conditions
    are met:

    1. Redistributions of source code must retain the above copyright
       notice, this list of conditions and the following disclaimer.

    2. Redistributions in binary form must reproduce the above
       copyright notice, this list of conditions and the following
       disclaimer in the documentation and/or other materials provided
       with the distribution.

    THIS SOFTWARE IS PROVIDED ``AS IS'' AND ANY EXPRESS OR IMPLIED
    WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
    OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
    DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR AND COPYRIGHT HOLDER BE
    LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY,
    OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
    PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
    PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
    THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR
    TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF
    THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
    SUCH DAMAGE.
*)

type doc
(* [doc] represents documents which can be pretty printed. They are
   constructed from functions provided by this module. *)
    
val empty : doc
(* [empty] is the empty document. *)

val (^^) : doc -> doc -> doc
(* [d1 ^^ d2] is the concatenation of documents [d1] and [d2]. *)

val text : string -> doc
(* [text "hello"] creates a document containing the string ["hello"].
   This operators simply turns strings into documents. *)
   
val break : doc
(* [break] represents a point where the pretty printer can decide
   whether to begin a new line or not. In the former case a newline is
   printed, followed by a number of spaces to indent the next line.
   The number of spaces is controlled by the [nest] operator. When the
   pretty printer does not begin a new line a single space is printed
   for the [break]. *)

val breakWith : string -> doc
(* [breakWith s] acts like [break] except that it is not turned into a
   space or a newline but into [s] or a newline (followed by spaces).
   *)
    
val nest : int -> doc -> doc
(* [nest i doc]: all breaks inside [doc] which are turned into
   newlines will be followed by additional [i] spaces. Nesting adds up: 
   when [doc] contains another [nest j] operator the breaks inside its
   document will follwed by [i+j] spaces. *)
   
val hgrp : doc -> doc
(* [break]s inside a [hgrp] (horizontal group) are never turned into
   newlines, so they always come out as spaces. *)
    
val vgrp : doc -> doc
(* [break]s inside a [vgrp] (vertical group) are always turned onto
   newlines (which are followed by spaces as indicated by [nest]). *)
 
val agrp : doc -> doc
(* The automatic group [agrp] is the most versatile: when the whole
   group including all subgroups fits into one line [break]s come out
   as spaces.  Otherwise [break]s come out as newlines.  However, this
   does not affect subgroups:  their [break]s are considered
   seperately.  *)
 
val fgrp : doc -> doc
(* The break policy inside an [agrp] is fixed for all breaks of the
   group. Inside a flexible group [fgrp] each [break] is considered
   individually: when the document  up to the next [break] fits into the
   current line the [break] comes out as space. Otherwise it comes out
   as newline followed by spaces. *)

val ppToString : int -> doc -> string
(* [ppToString w doc] formats [doc] for line length [w] (> 0) and
   returns it as string. This is not efficient and should be avoided
   for large documents.  The document is considered to be surrounded
   by a virtual [agrp] - if this is not desried it should have itself
   a different group at its outermost level to protect itself from
   the [agrp]. *)

val ppToFile : out_channel -> int -> doc -> unit
(* [ppToFile oc w doc] pretty prints [doc] for line length [w] into an
   output channel [oc]. The document is considered to be surrounded
   by a virtual [agrp] - if this is not desried it should have itself
   a different group at its outermost level to protect itself from
   this [agrp]. *)

(* 
    $Log: pp.mli,v $
    Revision 1.1.1.1  1999/06/13 12:55:05  lindig
    imported sources

    Revision 1.3  1999/01/01 17:05:52  lindig

    Makefile support for generating XML files.

    Revision 1.2  1998/12/30 18:38:00  lindig


    Documentation in mli files proof read and BSD style license added.

    Revision 1.1.1.1  1998/11/15 16:24:08  lindig
    file put into CVS
*)
