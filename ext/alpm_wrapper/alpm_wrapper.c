#include "alpm_wrapper.h"

VALUE mALPM;

void Init_alpm_wrapper(void){

  mALPM = rb_const_get(rb_cObject, rb_intern("ALPM"));

  rb_define_const(mALPM, "LIB_VERSION", rb_str_new2(alpm_version()));

  Init_alpm_handler();
  Init_alpm_package();
}
