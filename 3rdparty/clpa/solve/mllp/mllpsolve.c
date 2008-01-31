/*
 * Authors:
 *   Brian Hackett  <bhackett@stanford.edu>
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
 */

/* OCaml interface to lp_solve */

#include <lp_lib.h>

#include <caml/mlvalues.h>
#include <caml/alloc.h>
#include <caml/memory.h>
#include <caml/fail.h>
#include <assert.h>

#define LP ((lprec*)Field(lpm,0))

// lp_make : int -> int -> lpm
value lp_make(value rows, value cols)
{
  CAMLparam2(rows,cols);
  CAMLlocal1(lp);

  lprec *lpr = make_lp(Int_val(rows),Int_val(cols));
  if (!lpr)
    caml_failwith("LP allocation failed");

  lp = caml_alloc(1,Abstract_tag);
  Store_field(lp,0,(value)lpr);

  CAMLreturn(lp);
}

// lp_delete : lpm -> unit
value lp_delete(value lpm)
{
  CAMLparam1(lpm);
  delete_lp(LP);
  CAMLreturn(Val_unit);
}

// lp_get_nrows : lpm -> int
value lp_get_nrows(value lpm)
{
  CAMLparam1(lpm);
  int rows = get_Nrows(LP);
  CAMLreturn(Val_int(rows));
}

// lp_get_ncols : lpm -> int
value lp_get_ncols(value lpm)
{
  CAMLparam1(lpm);
  int cols = get_Ncolumns(LP);
  CAMLreturn(Val_int(cols));
}

// lp_solve : lpm -> t_lpstatus
value lp_solve(value lpm)
{
  CAMLparam1(lpm);

  enter_blocking_section();
  int result = solve(LP);
  leave_blocking_section();

  // deal with the somewhat wonky return codes of solve()
  switch (result) {
  case OPTIMAL:    CAMLreturn(Val_int(0));  // LP_Optimal
  case INFEASIBLE: CAMLreturn(Val_int(1));  // LP_Infeasible
  case UNBOUNDED:  CAMLreturn(Val_int(2));  // LP_Unbounded
  case DEGENERATE: CAMLreturn(Val_int(3));  // LP_Degenerate
  case SUBOPTIMAL: CAMLreturn(Val_int(4));  // LP_SubOptimal
  case TIMEOUT:    CAMLreturn(Val_int(5));  // LP_TimeOut
  case NOMEMORY:   CAMLreturn(Val_int(6));  // LP_NoMemory
  case NUMFAILURE: CAMLreturn(Val_int(7));  // LP_NumFailure
  case USERABORT:  CAMLreturn(Val_int(8));  // LP_UserAbort
  case PROCFAIL:   CAMLreturn(Val_int(9));  // LP_ProcFail
  case PROCBREAK:  CAMLreturn(Val_int(10)); // LP_ProcBreak
  default:         CAMLreturn(Val_int(11)); // LP_Failure
  }
}

// lp_get_obj : lpm -> float
value lp_get_obj(value lpm)
{
  CAMLparam1(lpm);
  CAMLreturn(caml_copy_double(get_objective(LP)));
}

// lp_get_assign : lpm -> int -> float
value lp_get_assign(value lpm, value col)
{
  CAMLparam2(lpm,col);
  REAL *vals;
  get_ptr_variables(LP,&vals);
  CAMLreturn(caml_copy_double(vals[Int_val(col)-1]));
}

// lp_set_bb_depthlimit : lpm -> int -> unit
value lp_set_bb_depthlimit(value lpm, value limit)
{
  CAMLparam2(lpm,limit);
  set_bb_depthlimit(LP,Int_val(limit));
  CAMLreturn(Val_unit);
}

// lp_set_bb_dir : lpm -> t_lpbranchdir -> unit
value lp_set_bb_dir(value lpm, value dir)
{
  CAMLparam2(lpm,dir);
  set_bb_floorfirst(LP,Int_val(dir));
  CAMLreturn(Val_unit);
}

// lp_set_bb_rule : lpm -> t_lprule -> unit
value lp_set_bb_rule(value lpm, value lprule)
{
  CAMLparam2(lpm,lprule);
  CAMLlocal1(p);
  int rule = Int_val(Field(lprule,0));
  p = Field(lprule,1);
  while (p != Val_int(0)) {
    // convert minor rules into bitflags for rule
    switch (Int_val(Field(p,0))) {
    case 0:  rule |= NODE_WEIGHTREVERSEMODE; break; // LP_WeightReverseMode
    case 1:  rule |= NODE_BRANCHREVERSEMODE; break; // LP_BranchReverseMode
    case 2:  rule |= NODE_GREEDYMODE;        break; // LP_GreedyMode
    case 3:  rule |= NODE_PSEUDOCOSTMODE;    break; // LP_PseudoCostMode
    case 4:  rule |= NODE_DEPTHFIRSTMODE;    break; // LP_DepthFirstMode
    case 5:  rule |= NODE_RANDOMIZEMODE;     break; // LP_RandomizeMode
    case 6:  rule |= NODE_GUBMODE;           break; // LP_GubMode
    case 7:  rule |= NODE_DYNAMICMODE;       break; // LP_DynamicMode
    case 8:  rule |= NODE_RESTARTMODE;       break; // LP_RestartMode
    case 9:  rule |= NODE_BREADTHFIRSTMODE;  break; // LP_BreadthFirstMode
    case 10: rule |= NODE_AUTOORDER;         break; // LP_AutoOrder
    case 11: rule |= NODE_RCOSTFIXING;       break; // LP_RCostFixing
    case 12: rule |= NODE_STRONGINIT;        break; // LP_StrongInit
    default: break;
    }
    p = Field(p,1);
  }
  set_bb_rule(LP,rule);
  CAMLreturn(Val_unit);
}

// lp_set_verbose : lpm -> t_lpverbose -> unit
value lp_set_verbose(value lpm, value verboselevel)
{
  CAMLparam2(lpm,verboselevel);
  set_verbose(LP,Int_val(verboselevel));
  CAMLreturn(Val_unit);
}

// lp_print : lpm -> unit
value lp_print(value lpm)
{
  CAMLparam1(lpm);
  write_LP(LP,stdout);
  CAMLreturn(Val_unit);
}

value lp_print_file(value lpm, value file)
{
  CAMLparam2(lpm,file);
  FILE *fl = fopen(String_val(file),"wb");
  if (fl) {
    write_LP(LP,fl);
    fclose(fl);
  }
  else {
    printf("ERROR: Could not open file for writing LP: %s\n",String_val(file));
  }
  CAMLreturn(Val_unit);
}

// lp_set_timeout : lpm -> int -> unit
value lp_set_timeout(value lpm, value secs)
{
  CAMLparam2(lpm,secs);
  set_timeout(LP,Int_val(secs));
  CAMLreturn(Val_unit);
}

// lp_set_add_rowmode : lpm -> bool -> unit
value lp_set_add_rowmode(value lpm, value addrowmode)
{
  CAMLparam2(lpm,addrowmode);
  set_add_rowmode(LP,Int_val(addrowmode));
  CAMLreturn(Val_unit);
}

// lp_set_bnds_tighter : lpm -> bool -> unit
value lp_set_bnds_tighter(value lpm, value tighter)
{
  CAMLparam2(lpm,tighter);
  set_bounds_tighter(LP,Int_val(tighter));
  CAMLreturn(Val_unit);
}

// lp_get_infinite : lpm -> float
value lp_get_infinite(value lpm)
{
  CAMLparam1(lpm);
  CAMLreturn(caml_copy_double(get_infinite(LP)));
}

// lp_set_infinite : lpm -> float -> unit
value lp_set_infinite(value lpm, value infinity)
{
  CAMLparam2(lpm,infinity);
  set_infinite(LP,Double_val(infinity));
  CAMLreturn(Val_unit);
}

REAL *vals = NULL;
int *nums = NULL;
int vn_size = 0;

#define STORE_LPARR                                          \
  CAMLlocal1(p);                                             \
  int i, size;                                               \
  size = Int_val(Field(lparr,0));                            \
  if (size > vn_size) {                                      \
    vn_size = size;                                          \
    nums = realloc(nums,vn_size*sizeof(int));                \
    vals = realloc(vals,vn_size*sizeof(double));             \
  }                                                          \
  p = Field(lparr,1);                                        \
  for (i = 0; i < size; i++) {                               \
    vals[i] = Double_val(Field(Field(p,0),0));               \
    nums[i] = Int_val(Field(Field(p,0),1));                  \
    p = Field(p,1);                                          \
  }                                                          \
  assert(p == Val_int(0));                                   \

// lp_set_obj : lpm -> t_lparr -> unit
value lp_set_obj(value lpm, value lparr)
{
  CAMLparam2(lpm,lparr);
  STORE_LPARR;
  set_obj_fnex(LP,size,vals,nums);
  CAMLreturn(Val_unit);
}

// lp_maximize_obj : lpm -> unit
value lp_maximize_obj(value lpm)
{
  CAMLparam1(lpm);
  set_maxim(LP);
  CAMLreturn(Val_unit);
}

// lp_minimize_obj : lpm -> unit
value lp_minimize_obj(value lpm)
{
  CAMLparam1(lpm);
  set_minim(LP);
  CAMLreturn(Val_unit);
}

// lp_add_column : lpm -> t_lparr -> unit
value lp_add_column(value lpm, value lparr)
{
  CAMLparam2(lpm,lparr);
  STORE_LPARR;
  add_columnex(LP,size,vals,nums);
  CAMLreturn(Val_unit);
}

// lp_set_column : lpm -> int -> t_lparr -> unit
value lp_set_column(value lpm, value col, value lparr)
{
  CAMLparam3(lpm,col,lparr);
  STORE_LPARR;
  set_columnex(LP,Int_val(col),size,vals,nums);
  CAMLreturn(Val_unit);
}

// lp_del_column : lpm -> int -> unit
value lp_del_column(value lpm, value col)
{
  CAMLparam2(lpm,col);
  del_column(LP,Int_val(col));
  CAMLreturn(Val_unit);
}

#define CST (Int_val(cst) + 1)

// lp_add_row : lpm -> t_lparr -> t_lpcst -> float -> unit
value lp_add_row(value lpm, value lparr, value cst, value rhs)
{
  CAMLparam4(lpm,lparr,cst,rhs);
  STORE_LPARR;
  add_constraintex(LP,size,vals,nums,CST,Double_val(rhs));
  CAMLreturn(Val_unit);
}

// lp_set_row : lpm -> int -> t_lparr -> unit
value lp_set_row(value lpm, value row, value lparr)
{
  CAMLparam3(lpm,row,lparr);
  STORE_LPARR;
  set_rowex(LP,Int_val(row),size,vals,nums);
  CAMLreturn(Val_unit);
}

// lp_set_row_type : lpm -> int -> t_lpcst -> unit
value lp_set_row_type(value lpm, value row, value cst)
{
  CAMLparam3(lpm,row,cst);
  set_constr_type(LP,Int_val(row),CST);
  CAMLreturn(Val_unit);
}

// lp_set_row_rhs : lpm -> int -> float -> unit
value lp_set_row_rhs(value lpm, value row, value rhs)
{
  CAMLparam3(lpm,row,rhs);
  set_rh(LP,Int_val(row),Double_val(rhs));
  CAMLreturn(Val_unit);
}

// lp_del_row : lpm -> int -> unit
value lp_del_row(value lpm, value row)
{
  CAMLparam2(lpm,row);
  del_constraint(LP,Int_val(row));
  CAMLreturn(Val_unit);
}

// lp_set_isbinary : lpm -> int -> bool -> unit
value lp_set_isbinary(value lpm, value col, value isbinary)
{
  CAMLparam3(lpm,col,isbinary);
  set_binary(LP,Int_val(col),Int_val(isbinary));
  CAMLreturn(Val_unit);
}

// lp_set_isint : lpm -> int -> bool -> unit
value lp_set_isint(value lpm, value col, value isint)
{
  CAMLparam3(lpm,col,isint);
  set_int(LP,Int_val(col),Int_val(isint));
  CAMLreturn(Val_unit);
}

// lp_set_issemicont : lpm -> int -> bool -> unit
value lp_set_issemicont(value lpm, value col, value issemicont)
{
  CAMLparam3(lpm,col,issemicont);
  set_semicont(LP,Int_val(col),Int_val(issemicont));
  CAMLreturn(Val_unit);
}

// lp_set_unbnded : lpm -> int -> unit
value lp_set_unbnded(value lpm, value col)
{
  CAMLparam2(lpm,col);
  set_unbounded(LP,Int_val(col));
  CAMLreturn(Val_unit);
}

// lp_set_bnds : lpm -> int -> float -> float -> unit
value lp_set_bnds(value lpm, value col, value lower, value upper)
{
  CAMLparam4(lpm,col,lower,upper);
  set_bounds(LP,Int_val(col),Double_val(lower),Double_val(upper));
  CAMLreturn(Val_unit);
}

// lp_set_lower_bnd : lpm -> int -> float -> unit
value lp_set_lower_bnd(value lpm, value col, value lower)
{
  CAMLparam3(lpm,col,lower);
  set_lowbo(LP,Int_val(col),Double_val(lower));
  CAMLreturn(Val_unit);
}

// lp_set_upper_bnd : lpm -> int -> float -> unit
value lp_set_upper_bnd(value lpm, value col, value upper)
{
  CAMLparam3(lpm,col,upper);
  set_upbo(LP,Int_val(col),Double_val(upper));
  CAMLreturn(Val_unit);
}
