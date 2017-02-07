#include "handler.h"
#include "package.h"

VALUE cALPM_Package;

void Init_alpm_package(){
  extern VALUE mALPM;
  cALPM_Package = rb_define_class_under(mALPM, "Package", rb_cObject);
  rb_define_alloc_func(cALPM_Package, alpm_package_allocate);

  /* String attributes */
  RB_PACKAGE_GETTER_SET(filename);
  RB_PACKAGE_GETTER_SET(base);
  RB_PACKAGE_GETTER_SET(name);
  RB_PACKAGE_GETTER_SET(version);
  RB_PACKAGE_GETTER_SET(desc);
  RB_PACKAGE_GETTER_SET(url);
  RB_PACKAGE_GETTER_SET(packager);
  RB_PACKAGE_GETTER_SET(md5sum);
  RB_PACKAGE_GETTER_SET(sha256sum);
  RB_PACKAGE_GETTER_SET(arch);
  RB_PACKAGE_GETTER_SET(base64_sig);

  /* off_t -> long -> Numeric */
  RB_PACKAGE_GETTER_SET(size);
  RB_PACKAGE_GETTER_SET(isize);

  /* datetime -> Time */
  RB_PACKAGE_GETTER_SET(builddate);
  RB_PACKAGE_GETTER_SET(installdate);

/*
  RB_PACKAGE_GETTER_SET(origin);
  RB_PACKAGE_GETTER_SET(reason);
  RB_PACKAGE_GETTER_SET(licenses);
  RB_PACKAGE_GETTER_SET(groups);
  RB_PACKAGE_GETTER_SET(depends);
  RB_PACKAGE_GETTER_SET(optdepends);
  RB_PACKAGE_GETTER_SET(conflicts);
  RB_PACKAGE_GETTER_SET(provides);
  RB_PACKAGE_GETTER_SET(deltas);
  RB_PACKAGE_GETTER_SET(replaces);
  RB_PACKAGE_GETTER_SET(files);
  RB_PACKAGE_GETTER_SET(backup);
  RB_PACKAGE_GETTER_SET(db);
  RB_PACKAGE_GETTER_SET(validation);
*/
}

RB_COMMON_ALLOC(alpm_package)

void alpm_package_deallocate(void* handler_ptr){
  if( handler_ptr != NULL ){
    alpm_pkg_free(((rb_alpm_package *)handler_ptr)->handle);
    free(handler_ptr);
  }
}

VALUE alpm_package_load_from_file(int argc, VALUE* argv, VALUE self){

  rb_alpm_handler * rb_handler_ptr = NULL;
  rb_alpm_package * rb_package_ptr = NULL;
  alpm_handle_t * handler_ptr = NULL;
  alpm_pkg_t * package_ptr = NULL;
  alpm_siglevel_t siglevel = ALPM_SIG_PACKAGE_OPTIONAL;

  VALUE filename, full;

  rb_scan_args(argc, argv, "11", &filename, &full);

  if(NIL_P(full)) {  full = INT2NUM(0); }

  Data_Get_Struct(self, rb_alpm_handler, rb_handler_ptr);

  alpm_pkg_load( rb_handler_ptr->handle, StringValuePtr(filename), NUM2INT(full), siglevel, &package_ptr );

  rb_package_ptr = (rb_alpm_package*)malloc(sizeof(rb_alpm_package));

  rb_package_ptr->handle = package_ptr;

  return RB_NEW_PACKAGE_WITH_PTR(rb_package_ptr);
}

RB_PACKAGE_SIMPLE_GETTER_STRING(filename);
RB_PACKAGE_SIMPLE_GETTER_STRING(base);
RB_PACKAGE_SIMPLE_GETTER_STRING(name);
RB_PACKAGE_SIMPLE_GETTER_STRING(version);
RB_PACKAGE_SIMPLE_GETTER_STRING(desc);
RB_PACKAGE_SIMPLE_GETTER_STRING(url);
RB_PACKAGE_SIMPLE_GETTER_STRING(packager);
RB_PACKAGE_SIMPLE_GETTER_STRING(md5sum);
RB_PACKAGE_SIMPLE_GETTER_STRING(sha256sum);
RB_PACKAGE_SIMPLE_GETTER_STRING(arch);
RB_PACKAGE_SIMPLE_GETTER_STRING(base64_sig);

RB_PACKAGE_SIMPLE_GETTER_LONG(size);
RB_PACKAGE_SIMPLE_GETTER_LONG(isize);

RB_PACKAGE_SIMPLE_GETTER_TIME(installdate);
RB_PACKAGE_SIMPLE_GETTER_TIME(builddate);
