#ifndef _ALPM_HANDLER_H_
#define _ALPM_HANDLER_H_

#include "common.h"

#define RB_HANDLER_ACCESS_NAME(name) static VALUE alpm_handler_get_ ## name(VALUE);\
static VALUE alpm_handler_set_ ## name(VALUE,VALUE)

#define RB_HANDLER_ACCESS_SET(name) rb_define_method(cALPM_Handler, #name, alpm_handler_get_ ## name, 0 );\
rb_define_method(cALPM_Handler, #name"=" , alpm_handler_set_ ## name, 1 )

#define RB_HANDLER_GETTER_NAME(name) static VALUE alpm_handler_get_ ## name(VALUE)
#define RB_HANDLER_GETTER_SET(name) rb_define_method(cALPM_Handler, #name, alpm_handler_get_ ## name, 0 )

#define RB_HANDLER_SIMPLE_GETTER_STRING(name) static VALUE alpm_handler_get_ ## name(VALUE self) {\
  rb_alpm_handler * handler;\
  const char * empty_str = "";\
  Data_Get_Struct(self, rb_alpm_handler, handler);\
  const char * filename = alpm_option_get_ ## name(handler->handle);\
  return rb_str_new2( (filename != NULL) ? filename : empty_str );\
}

#define RB_HANDLER_SIMPLE_SETTER_STRING(name) static VALUE alpm_handler_set_ ## name(VALUE self, VALUE arg) {\
  rb_alpm_handler * handler;\
  Data_Get_Struct(self, rb_alpm_handler, handler);\
  Check_Type(arg, T_STRING);\
  alpm_option_set_ ## name(handler->handle, StringValuePtr(arg));\
  return arg;\
}

#define RB_HANDLER_SIMPLE_GETTER_INTEGER(name) static VALUE alpm_handler_get_ ## name(VALUE self) {\
  rb_alpm_handler * handler;\
  Data_Get_Struct(self, rb_alpm_handler, handler);\
  return INT2NUM((int)alpm_option_get_ ## name(handler->handle));\
}

#define RB_HANDLER_SIMPLE_GETTER_DOUBLE(name) static VALUE alpm_handler_get_ ## name(VALUE self) {\
  rb_alpm_handler * handler;\
  Data_Get_Struct(self, rb_alpm_handler, handler);\
  return rb_float_new((double)alpm_option_get_ ## name(handler->handle));\
}

#define RB_HANDLER_SIMPLE_SETTER_DOUBLE(name) static VALUE alpm_handler_set_ ## name(VALUE self, VALUE arg) {\
  rb_alpm_handler * handler;\
  Data_Get_Struct(self, rb_alpm_handler, handler);\
  Check_Type(arg, T_FLOAT);\
  alpm_option_set_ ## name(handler->handle, NUM2DBL(arg));\
  return arg;\
}

#ifdef __cplusplus
  extern "C" {
#endif

typedef struct {
  alpm_handle_t * handle;
} rb_alpm_handler;

void Init_alpm_handler();
static VALUE alpm_handler_allocate(VALUE);
static void alpm_handler_deallocate(void*);

static VALUE alpm_handler_initialize(int, VALUE*, VALUE);

/* capture string (ro) */
RB_HANDLER_GETTER_NAME(root);
RB_HANDLER_GETTER_NAME(dbpath);
RB_HANDLER_GETTER_NAME(lockfile);

/* capture string (rw) */
RB_HANDLER_ACCESS_NAME(logfile);
RB_HANDLER_ACCESS_NAME(gpgdir);
RB_HANDLER_ACCESS_NAME(arch);
RB_HANDLER_ACCESS_NAME(dbext);

/* capture integer (rw, actual boolean) */
RB_HANDLER_ACCESS_NAME(checkspace);

/* capture double (rw)*/
RB_HANDLER_ACCESS_NAME(deltaratio);

/* capture integer(rw, actual alpm_siglevel_t) */
RB_HANDLER_ACCESS_NAME(default_siglevel);
RB_HANDLER_ACCESS_NAME(local_file_siglevel);
RB_HANDLER_ACCESS_NAME(remote_file_siglevel);

/* capture int-present bool */
RB_HANDLER_GETTER_NAME(usesyslog);

/* capture nodelist */
RB_HANDLER_GETTER_NAME(cachedirs);
RB_HANDLER_GETTER_NAME(hookdirs);

RB_HANDLER_GETTER_NAME(noupgrade);
RB_HANDLER_GETTER_NAME(noextract);
RB_HANDLER_GETTER_NAME(ignorepkg);
RB_HANDLER_GETTER_NAME(assumeinstalled);

static VALUE alpm_handler_get_last_error(VALUE);
static VALUE alpm_handler_get_last_error_reason(VALUE);

static VALUE alpm_handler_get_default_siglevel(VALUE);

#ifdef __cplusplus
}
#endif

#endif
