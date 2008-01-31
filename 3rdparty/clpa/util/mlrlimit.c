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

// wrappers for process control of resource limits

#include <caml/mlvalues.h>
#include <caml/alloc.h>
#include <caml/memory.h>
#include <caml/fail.h>
#include <assert.h>

#include <stdio.h>
#include <sys/resource.h>

int convert_resource(int mlresource)
{
  switch (mlresource) {
  case 0: return RLIMIT_CORE;
  case 1: return RLIMIT_CPU;
  case 2: return RLIMIT_DATA;
  case 3: return RLIMIT_FSIZE;
  case 4: return RLIMIT_NOFILE;
  case 5: return RLIMIT_STACK;
  case 6: return RLIMIT_AS;
  default: printf("Unknown rlimit resource: %d\n", mlresource); return RLIMIT_CORE;
  }
}

value ml_setrlimit(value mlresource, value vtup)
{
  CAMLparam2(mlresource, vtup);

  int resource = convert_resource(Int_val(mlresource));
  struct rlimit rlim;
  rlim.rlim_cur = Int64_val(Field(vtup, 0));
  rlim.rlim_max = Int64_val(Field(vtup, 1));

  int res = setrlimit(resource, &rlim);
  if (res != 0)
    printf("ERROR: setrlimit failed: %d\n",res);

  CAMLreturn(Val_unit);
}

value ml_getrlimit(value mlresource)
{
  CAMLparam1(mlresource);

  int resource = convert_resource(Int_val(mlresource));
  struct rlimit rlim;
  rlim.rlim_cur = 0;
  rlim.rlim_max = 0;

  int res = getrlimit(resource, &rlim);
  if (res != 0)
    printf("ERROR: getrlimit failed: %d\n",res);

  value rettup = caml_alloc_tuple(2);
  Store_field(rettup, 0, caml_copy_int64(rlim.rlim_cur));
  Store_field(rettup, 1, caml_copy_int64(rlim.rlim_max));

  CAMLreturn(rettup);
}

value ml_infiniterlimit(value mlresource)
{
  CAMLparam1(mlresource);

  rlim_t resource = Int_val(mlresource);

  if (resource == RLIM_INFINITY)
    CAMLreturn(Val_true);
  else
    CAMLreturn(Val_false);
}
