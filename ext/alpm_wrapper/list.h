#ifndef _RB_ALPM_LIST_H_
#define _RB_ALPM_LIST_H_

#include "common.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef VALUE (*c_to_ruby_object_helper)(void *);
typedef void * (*ruby_object_to_c_helper)(VALUE);

VALUE alpm_list_to_ruby_array(const alpm_list_t *, list_item_converter);
VALUE ruby_array_to_alpm_list(VALUE);
VALUE str_to_ruby_object(void *);
VALUE pkg_to_ruby_object(void *);
void * ruby_object_to_str(VALUE);
void * ruby_object_to_pkg(VALUE);

#ifdef __cplusplus
}
#endif


#endif