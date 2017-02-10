#include "handler.h"
#include "package.h"

/* file-visable namespace */
VALUE cALPM_Handler;


/* setup all things about `ALPM::Package` */
void Init_alpm_handler(void){

  extern VALUE mALPM;

  cALPM_Handler = rb_define_class_under(mALPM, "Handler" , rb_cObject);
  rb_define_alloc_func(cALPM_Handler, alpm_handler_allocate);
  rb_define_method(cALPM_Handler, "initialize", alpm_handler_initialize, -1);


  RB_HANDLER_GETTER_SET(root);
  RB_HANDLER_GETTER_SET(dbpath);
  RB_HANDLER_GETTER_SET(lockfile);

  RB_HANDLER_GETTER_SET(default_siglevel);

  RB_HANDLER_GETTER_SET(last_error);
  RB_HANDLER_GETTER_SET(last_error_reason);

  rb_define_method(cALPM_Handler, "load_package_file", alpm_package_load_from_file, -1);
}

RB_COMMON_ALLOC(alpm_handler)

/* deallocator */
/* Things need to be freed here: */
/* rb_alpm_handler->handle: pointer to alpm_handle_t */
/* rb_alpm_handler: the wrapper itself. */
static void alpm_handler_deallocate(void* handler_ptr){
  alpm_release(((rb_alpm_handler*)handler_ptr)->handle);
  free(handler_ptr);
}

VALUE alpm_handler_initialize(int argc, VALUE* argv, VALUE self){

  VALUE root, dbpath;
  rb_alpm_handler * handler_ptr;
  alpm_handle_t * handle;
  alpm_errno_t * handler_errno_ptr;

  handler_errno_ptr = (alpm_errno_t*)malloc(sizeof(alpm_errno_t));
  *handler_errno_ptr = 0;

  rb_scan_args(argc, argv, "02", &root, &dbpath);

  if(NIL_P(root))   { root = rb_str_new2("/"); }
  if(NIL_P(dbpath)) { dbpath = rb_str_new2("/var/lib/pacman/"); }

  Data_Get_Struct(self, rb_alpm_handler, handler_ptr);

  handler_ptr->handle = alpm_initialize(StringValuePtr(root),StringValuePtr(dbpath),handler_errno_ptr);

  return self;
}

RB_HANDLER_SIMPLE_GETTER_STRING(root);
RB_HANDLER_SIMPLE_GETTER_STRING(dbpath);
RB_HANDLER_SIMPLE_GETTER_STRING(lockfile);

RB_HANDLER_SIMPLE_GETTER_INTEGER(default_siglevel);

static VALUE alpm_handler_get_last_error(VALUE self){
  rb_alpm_handler * handler_ptr = NULL;
  Data_Get_Struct(self, rb_alpm_handler, handler_ptr);
  return INT2NUM((int)alpm_errno(handler_ptr->handle));
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
