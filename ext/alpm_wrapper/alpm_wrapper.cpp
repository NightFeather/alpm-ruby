#include "alpm_wrapper.h"

void Init_alpm_wrapper(void){
  VALUE cALPM;
  cALPM = rb_const_get(rb_cObject, rb_intern("ALPM"));

  rb_define_const(cALPM, "LIB_VERSION", rb_str_new2(alpm_version()));
}
