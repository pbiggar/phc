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

// wrappers for in-memory zlib compress/uncompress

#include <caml/mlvalues.h>
#include <caml/alloc.h>
#include <caml/memory.h>
#include <caml/fail.h>
#include <assert.h>

#include <stdlib.h>
#include <string.h>
#include <zlib.h>

value gz_compress(value level, value str)
{
  CAMLparam2(level, str);
  int vlevel = Int_val(level);
  unsigned char *vstr = (unsigned char*)String_val(str);
  unsigned long strlen = string_length(str);

  unsigned long buflen = compressBound(strlen);
  unsigned char *buf = malloc(buflen);
  if (buf == NULL)
    raise_out_of_memory();

  int res = compress2(buf,&buflen,vstr,strlen,vlevel);
  if (res != Z_OK) {
    free(buf);
    raise_out_of_memory();
  }

  value rstr = alloc_string(buflen);
  unsigned char *vrstr = (unsigned char*)String_val(rstr);

  memcpy((void*)vrstr,(const void*)buf,(size_t)buflen);
  free(buf);

  CAMLreturn(rstr);
}

value gz_uncompress(value str)
{
  CAMLparam1(str);
  unsigned char *vstr = (unsigned char*)String_val(str);
  unsigned long strlen = string_length(str);

  unsigned long buflen = strlen, bbuflen;
  unsigned char *buf = NULL;
  int res;
  do {
    buflen *= 2;
    bbuflen = buflen;

    if (buf != NULL)
      free(buf);

    buf = malloc(buflen);
    if (buf == NULL)
      raise_out_of_memory();

    res = uncompress(buf,&bbuflen,vstr,strlen);
  } while (res == Z_BUF_ERROR);

  switch (res) {
  case Z_MEM_ERROR:
    free(buf);
    raise_out_of_memory();
  case Z_DATA_ERROR:
    free(buf);
    invalid_argument("gz_uncompress: corrupt input string");
  case Z_OK:
    break;    // fall-through
  }

  if (bbuflen > Bsize_wsize (Max_wosize) - 1) {
    invalid_argument("gz_uncompress: maximum ocaml string length exceeded");
  }

  value rstr = alloc_string(bbuflen);
  char *vrstr = String_val(rstr);

  memcpy((void*)vrstr,(const void*)buf,(size_t)bbuflen);
  free(buf);

  CAMLreturn(rstr);
}
