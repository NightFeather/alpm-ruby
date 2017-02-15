#ifndef _RB_ALPM_WRAPPER_COMMON_H_
#define _RB_ALPM_WRAPPER_COMMON_H_

#include <alpm.h>
#include <ruby.h>

#define RB_COMMON_ALLOC(name)\
static VALUE name ## _allocate(VALUE klass){\
  rb_ ## name * handler_ptr = NULL;\
  return Data_Make_Struct( klass, rb_ ## name, NULL, name ## _deallocate, handler_ptr);\
}

#ifdef __cplusplus
extern "C" {
#endif

/* define the common namespace */
extern VALUE mALPM;

#ifdef __cplusplus
}
#endif

#endif
