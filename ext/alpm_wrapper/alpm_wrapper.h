#ifndef _ALPM_WRAPPER_H_
#define _ALPM_WRAPPER_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <alpm.h>
#include <ruby.h>

void Init_alpm_wrapper(void);

#ifdef __cplusplus
}
#endif

#endif
