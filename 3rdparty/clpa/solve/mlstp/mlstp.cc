/* 
 * ML bindings for the STP theorem prover.
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
 */

// Various things that can be tweaked:
static const int GENERATION_CHECKING = 1;
static const int DUMP_QUERIES = 0;
static const char stp_flags[] = "x";

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <stp/c_interface.h>

using namespace std;

extern "C" {
#include <caml/mlvalues.h>
#include <caml/alloc.h>
#include <caml/memory.h>
#include <caml/signals.h>
#include <caml/callback.h>
#include <caml/fail.h>
}

static VC vc;

static void do_vc_init(void) 
{
  vc = vc_createValidityChecker(); 
  for (const char *p = stp_flags; *p; p++) {
    vc_setFlags(*p);
  }
}

/* Hack: we use the following dummy class to run our various initialization
 * processes by creating a single static instance of the class and running
 * our initializers from the constructor */
static class CVCInit {
public:
  CVCInit() { do_vc_init(); }
} VCInit;

static void expr_finalize(value v)
{
    // XXX: Implement me
}

// Optionally we check for use of STP values across a vc_reset(), and report
// an error if it occurs. We check this by attaching a version number to each 
// expression and checking it matches the current version when unboxing 
// expressions.
static int generation = 0;

// Horrible bit of macro hackery to raise an exception during unboxing if 
// we have a version number mismatch.
#define Expr_val(v)					 \
  (static_cast<void> (					 \
    (!GENERATION_CHECKING ||                              \
     ((int *)Data_custom_val(v))[1] == generation) ? 0 :		\
    (caml_raise_with_string(*caml_named_value("Bad generation"), "Error"), 0) \
    ),									\
   ((Expr *)Data_custom_val(v))[0]					\
   )

inline value box_stpexpr(Expr e)
{
  value v;

    if (GENERATION_CHECKING) {
      v = caml_alloc_final(3, expr_finalize, 1, 100);
      ((int *)Data_custom_val(v))[1] = generation;
    } else {
      v = caml_alloc_final(2, expr_finalize, 1, 100);
    }
    Expr_val(v) = e;
    return v;
}

extern "C" {

value mlstp_vc_reset(value unit)
{
    CAMLparam1(unit);
    vc_Destroy(vc);
    if (GENERATION_CHECKING) {
      generation++;
    }
    do_vc_init();
    CAMLreturn(Val_unit);
}


value mlstp_vc_push(value unit)
{
    CAMLparam1(unit);
    vc_push(vc);
    CAMLreturn(Val_unit);
}

value mlstp_vc_pop(value unit)
{
    CAMLparam1(unit);
    vc_pop(vc);
    CAMLreturn(Val_unit);
}

value mlstp_vc_assert(value vb)
{
    CAMLparam1(vb);
    vc_assertFormula(vc, Expr_val(vb));
    CAMLreturn(Val_unit);
}

value mlstp_vc_query(value qe)
{
    int ret;
    CAMLparam1(qe);
    if (DUMP_QUERIES) {
      fflush(stdout);
      vc_printVarDecls(vc);
      vc_printAsserts(vc);
      //    vc_printQuery(vc);
    }
    ret = vc_query(vc, Expr_val(qe));
    CAMLreturn((ret ? Val_true : Val_false));
}

value mlstp_string_of_expr(value ve)
{
    CAMLparam1(ve);
    CAMLlocal1(v);
    char *buf;
    long unsigned int len;
    vc_printExprToBuffer(vc, Expr_val(ve), &buf, &len);
    if (buf == NULL) abort();
    v = caml_copy_string(buf);
    free(buf);
    CAMLreturn(v);
}

value mlstp_string_of_expr2(value ve)
{
    CAMLparam1(ve);
    CAMLlocal1(v);
    char *buf;
    long unsigned int len;
    vc_printQueryStateToBuffer(vc, Expr_val(ve), &buf, &len);
    if (buf == NULL) abort();
    v = caml_copy_string(buf);
    free(buf);
    CAMLreturn(v);
}

value mlstp_get_counterexample(value unit)
{
    CAMLparam1(unit);
    CAMLlocal1(v);
    v = box_stpexpr(vc_getWholeCounterExample(vc));
    CAMLreturn(v);
}

value mlstp_get_term_from_counterexample(value ce, value term)
{
    CAMLparam2(ce, term);
    CAMLlocal1(v);
    v = box_stpexpr(vc_getTermFromCounterExample(vc, Expr_val(term), 
                                                  Expr_val(ce)));
    CAMLreturn(v);
}

value mlstp_print_counterexample(value unit)
{
    CAMLparam1(unit);
    fflush(stdout);
    vc_printCounterExample(vc);
    cout << endl;
    CAMLreturn(Val_unit);
}


/* Boolean values */

value mlstp_get_bval(value qe)
{
    int ret;
    CAMLparam1(qe);
    switch (vc_isBool(Expr_val(qe))) {
    case 0: ret = 0;
    case 1: ret = 1;
    default: ret = 2;
    }
    CAMLreturn(Val_int(ret));
}

value mlstp_bvar_new(value name)
{
    CAMLparam1(name);
    CAMLlocal1(v);
    v = box_stpexpr(vc_varExpr(vc, String_val(name), vc_boolType(vc)));
    CAMLreturn(v);
}

value mlstp_true(value unit)
{
    CAMLparam1(unit);
    CAMLlocal1(v);
    v = box_stpexpr(vc_trueExpr(vc));
    CAMLreturn(v);
}

value mlstp_false(value unit)
{
    CAMLparam1(unit);
    CAMLlocal1(v);
    v = box_stpexpr(vc_falseExpr(vc));
    CAMLreturn(v);
}

value mlstp_bv_new(value name, value nbits)
{
    CAMLparam2(name, nbits);
    CAMLlocal1(v);

    v = box_stpexpr(vc_varExpr(vc, String_val(name), 
			       vc_bvType(vc, Int_val(nbits))));
    CAMLreturn(v);
}

value mlstp_bv_from_int(value nbits, value ival)
{
    CAMLparam2(nbits, ival);
    CAMLlocal1(v);
    v = box_stpexpr(vc_bvConstExprFromInt(vc, Int_val(nbits), Int_val(ival)));
    CAMLreturn(v);
}

value mlstp_bv_nbits(value bv)
{
    CAMLparam1(bv);
    CAMLlocal1(v);
    v = Val_int(getBVInt(getChild(vc_getType(vc, Expr_val(bv)), 0)));
    CAMLreturn(v);
}

value mlstp_int_of_bvec(value bv)
{
    CAMLparam1(bv);
    CAMLlocal1(v);
    v = Val_int(getBVInt(vc_simplify(vc, Expr_val(bv))));
    CAMLreturn(v);
}


#define STP_E_OP(MLFN, STPFN) \
value MLFN(value w)                                 \
{                                                   \
    CAMLparam1(w);                               \
    CAMLlocal1(v);                                  \
    v = box_stpexpr(STPFN(vc, Expr_val(w)));        \
    CAMLreturn(v);                                  \
}

#define STP_EE_OP(MLFN, STPFN) \
value MLFN(value a, value b)                                \
{                                                           \
    CAMLparam2(a,b);                                        \
    CAMLlocal1(v);                                          \
    v = box_stpexpr(STPFN(vc, Expr_val(a), Expr_val(b)));   \
    CAMLreturn(v);                                          \
}

#define STP_EEE_OP(MLFN, STPFN) \
value MLFN(value a, value b, value c)			    \
{                                                           \
    CAMLparam3(a,b,c);					    \
    CAMLlocal1(v);                                          \
    v = box_stpexpr(STPFN(vc, Expr_val(a), Expr_val(b), Expr_val(c)));	\
    CAMLreturn(v);                                          \
}

#define STP_IEE_OP(MLFN, STPFN) \
value MLFN(value a, value b, value c)			    \
{                                                           \
    CAMLparam3(a,b,c);					    \
    CAMLlocal1(v);                                          \
    v = box_stpexpr(STPFN(vc, Int_val(a), Expr_val(b), Expr_val(c)));	\
    CAMLreturn(v);                                          \
}

#define STP_EI_OP(MLFN, STPFN) \
value MLFN(value a, value b)			    \
{                                                           \
    CAMLparam2(a,b);					    \
    CAMLlocal1(v);                                          \
    v = box_stpexpr(STPFN(vc, Expr_val(a), Int_val(b)));	\
    CAMLreturn(v);                                          \
}

#define STP_IE_OP(MLFN, STPFN) \
value MLFN(value a, value b)			    \
{                                                           \
    CAMLparam2(a,b);					    \
    CAMLlocal1(v);                                          \
    v = box_stpexpr(STPFN(vc, Int_val(a), Expr_val(b)));	\
    CAMLreturn(v);                                          \
}

#define STP_EII_OP(MLFN, STPFN) \
value MLFN(value a, value b, value c)			    \
{                                                           \
    CAMLparam3(a,b,c);					    \
    CAMLlocal1(v);                                          \
    v = box_stpexpr(STPFN(vc, Expr_val(a), Int_val(b), Int_val(c)));	\
    CAMLreturn(v);                                          \
}

#define STP_EEI_OP(MLFN, STPFN) \
value MLFN(value a, value b, value c)			    \
{                                                           \
    CAMLparam3(a,b,c);					    \
    CAMLlocal1(v);                                          \
    v = box_stpexpr(STPFN(vc, Expr_val(a), Expr_val(b), Int_val(c)));	\
    CAMLreturn(v);                                          \
}


/* Boolean operations */
STP_E_OP(mlstp_lnot, vc_notExpr);

STP_EE_OP(mlstp_land, vc_andExpr);
STP_EE_OP(mlstp_lor, vc_orExpr);
STP_EE_OP(mlstp_limplies,  vc_impliesExpr);
STP_EE_OP(mlstp_liff, vc_iffExpr);

STP_EEE_OP(mlstp_lite, vc_iteExpr);

/* Bitvector operations */
STP_E_OP(mlstp_bv_from_bexpr, vc_boolToBVExpr);

STP_EE_OP(mlstp_bv_and, vc_bvAndExpr);
STP_EE_OP(mlstp_bv_or,  vc_bvOrExpr);
STP_EE_OP(mlstp_bv_xor, vc_bvXorExpr);
STP_E_OP(mlstp_bv_not,  vc_bvNotExpr);
STP_IE_OP(mlstp_bv_lshift_const,  vc_bvLeftShiftExpr);
STP_IE_OP(mlstp_bv_rshift_const,  vc_bvRightShiftExpr);
STP_IEE_OP(mlstp_bv_lshift, vc_bvVarLeftShiftExpr);
STP_IEE_OP(mlstp_bv_rshift, vc_bvVarRightShiftExpr);
STP_IEE_OP(mlstp_bv_srshift, vc_sbvVarRightShiftExpr);
STP_EEE_OP(mlstp_bv_ite, vc_iteExpr);
STP_EE_OP(mlstp_bv_concat, vc_bvConcatExpr);

STP_EII_OP(mlstp_bv_extract,  vc_bvExtract);
STP_EI_OP(mlstp_bv_bit_extract,  vc_bvBoolExtract);
STP_EI_OP(mlstp_bv_sign_extend,  vc_bvSignExtend);

STP_E_OP(mlstp_bv_negate,  vc_bvUMinusExpr);
STP_IEE_OP(mlstp_bv_plus,  vc_bvPlusExpr);
STP_IEE_OP(mlstp_bv_minus, vc_bvMinusExpr);
STP_IEE_OP(mlstp_bv_mult,  vc_bvMultExpr);
STP_IEE_OP(mlstp_bv_udiv,  vc_bvDivExpr);
STP_IEE_OP(mlstp_bv_umod,  vc_bvModExpr);
STP_IEE_OP(mlstp_bv_sdiv,  vc_sbvDivExpr);
STP_IEE_OP(mlstp_bv_smod,  vc_sbvModExpr);

STP_EE_OP(mlstp_bv_eq, vc_eqExpr);
STP_EE_OP(mlstp_bv_ult, vc_bvLtExpr);
STP_EE_OP(mlstp_bv_ule, vc_bvLeExpr);
STP_EE_OP(mlstp_bv_uge, vc_bvGeExpr);
STP_EE_OP(mlstp_bv_ugt, vc_bvGtExpr);
STP_EE_OP(mlstp_bv_slt, vc_sbvLtExpr);
STP_EE_OP(mlstp_bv_sle, vc_sbvLeExpr);
STP_EE_OP(mlstp_bv_sge, vc_sbvGeExpr);
STP_EE_OP(mlstp_bv_sgt, vc_sbvGtExpr);


/* Arrays */
value mlstp_bva_new(value name, value index_bits, value value_bits)
{
    CAMLparam3(name, index_bits, value_bits);
    CAMLlocal1(v);
    v = box_stpexpr(vc_bvCreateArray(vc, Int_val(index_bits), 
				     Int_val(value_bits), String_val(name)));
    CAMLreturn(v);
}


STP_EEI_OP(mlstp_bva_read, vc_bvArrayRead);
STP_EEE_OP(mlstp_bva_write, vc_bvArrayWrite);
STP_EE_OP(mlstp_bva_eq, vc_eqExpr);

} /* extern "C" */
