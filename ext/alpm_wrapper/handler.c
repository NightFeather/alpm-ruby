#include "alpm_handler.h"
#include "alpm_package.h"

#define ALPM_HANDLER_RUBY_GETTER(name) ( rb_define_method(cALPM_Handler, #name, alpm_handler_get_ ## name, 0 ) )

VALUE cALPM_Handler;

void Init_alpm_handler(void){

  extern VALUE mALPM;

  cALPM_Handler = rb_define_class_under(mALPM, "Handler" , rb_cObject);
  rb_define_alloc_func(cALPM_Handler, alpm_handler_allocate);
  rb_define_method(cALPM_Handler, "initialize", alpm_handler_initialize, -1);


  ALPM_HANDLER_RUBY_GETTER(root);
  ALPM_HANDLER_RUBY_GETTER(dbpath);
  ALPM_HANDLER_RUBY_GETTER(last_error);
  ALPM_HANDLER_RUBY_GETTER(last_error_reason);
  ALPM_HANDLER_RUBY_GETTER(default_siglevel);

  rb_define_method(cALPM_Handler, "load_package_file", alpm_package_load_from_file, -1);
}

RB_COMMON_ALLOC(alpm_handler)

static void alpm_handler_deallocate(void* handler_ptr){
  alpm_release(((rb_alpm_handler*)handler_ptr)->handle);
  free(((rb_alpm_handler*)handler_ptr)->last_error);
  free(((rb_alpm_handler*)handler_ptr));
}

VALUE alpm_handler_initialize(int argc, VALUE* argv, VALUE self){

  VALUE root, dbpath;
  rb_alpm_handler * handler_ptr;
  alpm_handle_t * handle;
  alpm_errno_t * handler_errno_ptr = 0;

  rb_scan_args(argc, argv, "02", &root, &dbpath);

  if(NIL_P(root))   { root = rb_str_new2("/"); }
  if(NIL_P(dbpath)) { dbpath = rb_str_new2("/var/lib/pacman/"); }

  Data_Get_Struct(self, rb_alpm_handler, handler_ptr);

  handler_ptr->handle = alpm_initialize(StringValuePtr(root),StringValuePtr(dbpath),handler_errno_ptr);
  handler_ptr->last_error = handler_errno_ptr;

  return self;
}

static VALUE alpm_handler_get_root(VALUE self){
  rb_alpm_handler * handler_ptr = NULL;
  Data_Get_Struct(self, rb_alpm_handler, handler_ptr);
  return rb_str_new2(alpm_option_get_root(handler_ptr->handle));
}

static VALUE alpm_handler_get_dbpath(VALUE self){
  rb_alpm_handler * handler_ptr = NULL;
  Data_Get_Struct(self, rb_alpm_handler, handler_ptr);
  return rb_str_new2(alpm_option_get_dbpath(handler_ptr->handle));
}

static VALUE alpm_handler_get_last_error(VALUE self){
  rb_alpm_handler * handler_ptr = NULL;
  Data_Get_Struct(self, rb_alpm_handler, handler_ptr);
  return INT2FIX((int)alpm_errno(handler_ptr->handle));
}

static VALUE alpm_handler_get_last_error_reason(VALUE self){
  rb_alpm_handler * handler_ptr = NULL;
  alpm_errno_t error_code = 0;
  Data_Get_Struct(self, rb_alpm_handler, handler_ptr);
  error_code = alpm_errno(handler_ptr->handle);
  if(error_code > 0){
    return rb_str_new2(alpm_strerror(error_code));
  } else {
    return Qnil;
  }
}

static VALUE alpm_handler_get_default_siglevel(VALUE self){
  rb_alpm_handler * handler_ptr = NULL;
  Data_Get_Struct(self,rb_alpm_handler, handler_ptr);
  return INT2FIX((int)alpm_option_get_default_siglevel(handler_ptr->handle));
}