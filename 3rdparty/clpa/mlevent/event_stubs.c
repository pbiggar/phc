/************************************************************************/
/* The OcamlEvent library                                               */
/*                                                                      */
/* Copyright 2002, 2003, 2004 Maas-Maarten Zeeman. All rights reserved. */
/* See LICENCE for details.                                             */
/************************************************************************/

/* $Id: event_stubs.c,v 1.10 2004/12/18 21:58:25 maas Exp $ */

/* Stub code to interface Ocaml with libevent */

#include <sys/time.h>
#include <stdlib.h>
#include <stdio.h>
#include <event.h>

#include <caml/mlvalues.h>
#include <caml/custom.h>
#include <caml/alloc.h>
#include <caml/memory.h>
#include <caml/callback.h>
#include <caml/fail.h>

#define struct_event_val(v) (*((struct event **)Data_custom_val(v)))
#define Is_some(v) (Is_block(v))

static value * event_cb_closure = NULL;

/* use the error function from the Unix library */
extern void uerror (char * cmdname, value arg) Noreturn;

static void
struct_event_finalize(value ve) 
{
  struct event *ev = struct_event_val(ve);
  
  /* This means that event_set is called. We can assume that there */
  if(event_initialized(ev)) {
    /* */
  }

  free(struct_event_val(ve));
}

static int 
struct_event_compare(value v1, value v2) 
{ 
  struct event *p1 = struct_event_val(v1);
  struct event *p2 = struct_event_val(v2);
  if(p1 == p2) return 0;
  if(p1 < p2) return -1; 
  return 1;
}

static long
struct_event_hash(value v)
{
  return (long) struct_event_val(v);
}

static struct custom_operations struct_event_ops = {
  "struct event",
  struct_event_finalize,
  struct_event_compare,
  struct_event_hash,
  custom_serialize_default,
  custom_deserialize_default
};

/* 
 * This callback calls the ocaml event callback, which will in turn
 * call the real ocaml callback.  
 */
static void
event_cb(int fd, short type, void *arg) 
{
  callback3(*event_cb_closure, 
	    Val_long((long) arg), Val_int(fd), Val_int(type));
}

static void
set_struct_timeval(struct timeval *tv, value vfloat) 
{
  double timeout = Double_val(vfloat);
  tv->tv_sec = (int) timeout;
  tv->tv_usec = (int) (1e6 * (timeout - tv->tv_sec));
}

CAMLprim value
oc_create_event(value unit) 
{
  CAMLparam0();
  CAMLlocal1(ve);
  struct event *e = malloc(sizeof(struct event));
  if (e == NULL) {
      fprintf(stderr, "Memory allocation failure in oc_create_event\n");
      exit(EXIT_FAILURE);
  }

  ve = alloc_custom(&struct_event_ops, sizeof(struct event *), 0, 1);
  struct_event_val(ve) = e;

  CAMLreturn(ve);
}

CAMLprim value
oc_event_id(value vevent)
{
  CAMLparam0();
  CAMLreturn(Val_long((long) struct_event_val(vevent)));
}

CAMLprim value
oc_event_fd(value vevent)
{
  CAMLparam1(vevent);
  CAMLreturn(Val_long(EVENT_FD(struct_event_val(vevent))));
}

CAMLprim value 
oc_event_set(value vevent, value fd, value vevent_flag) 
{ 
  CAMLparam3(vevent, fd, vevent_flag); 

  struct event *event = struct_event_val(vevent); 

  event_set(event, Int_val(fd), Int_val(vevent_flag), 
	    &event_cb, event); 

  CAMLreturn(Val_unit); 
} 

CAMLprim value
oc_event_add(value vevent, value vfloat_option) 
{
  CAMLparam2(vevent, vfloat_option);
  struct event *event = struct_event_val(vevent); 
  struct timeval timeval;
  struct timeval *tv = NULL;

  if Is_some(vfloat_option) {
    set_struct_timeval(&timeval, Field(vfloat_option, 0));
    tv = &timeval;
  } 
  
  if((0 != event_add(event, tv))) {
    uerror("event_add", vevent);
  }

  CAMLreturn(Val_unit);
}

CAMLprim value
oc_event_del(value vevent) 
{
  CAMLparam0();
  struct event *event = struct_event_val(vevent); 

  event_del(event);

  CAMLreturn(Val_unit);
}

CAMLprim value
oc_event_pending(value vevent, value vtype, value vfloat_option) 
{
  CAMLparam3(vevent, vtype, vfloat_option);
  struct event *event = struct_event_val(vevent); 
  struct timeval timeval;
  struct timeval *tv = NULL;
  
  if Is_some(vfloat_option) {
    set_struct_timeval(&timeval, Field(vfloat_option, 0));
    tv = &timeval;
  } 

  event_pending(event, Int_val(vtype), tv);

  CAMLreturn(Val_unit);
}

CAMLprim value
oc_event_loop(value vloop_flag)
{
  CAMLparam1(vloop_flag);

  if((-1 == event_loop(Int_val(vloop_flag)))) {
    uerror("event_dispatch", vloop_flag);
  }
  
  CAMLreturn(Val_unit);
}


CAMLprim value
oc_event_dispatch(value unit) 
{
  CAMLparam1(unit);

  if((-1 == event_dispatch())) {
    uerror("event_dispatch", unit);
  }

  CAMLreturn(Val_unit);
}

/*
 * Initialize the event library
 */
CAMLprim value
oc_event_init(value unit)
{
  CAMLparam1(unit);
  
  /* setup the event callback closure if needed */
  if(event_cb_closure == NULL) {
    event_cb_closure = caml_named_value("event_cb");
    if(event_cb_closure == NULL) {
      invalid_argument("Callback event_cv not initialized.");
    }
  }

  /* and don't forget to initialize libevent */
  event_init();

  CAMLreturn(Val_unit);
}
