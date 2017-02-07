#ifndef _ALPM_HANDLER_H_
#define _ALPM_HANDLER_H_

#include "common.h"

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

static VALUE alpm_handler_get_root(VALUE);
static VALUE alpm_handler_get_dbpath(VALUE);

static VALUE alpm_handler_get_last_error(VALUE);
static VALUE alpm_handler_get_last_error_reason(VALUE);

static VALUE alpm_handler_get_default_siglevel(VALUE);

#ifdef __cplusplus
}
#endif

#endif
