#ifndef _RB_ALPM_PACKAGE_H_
#define _RB_ALPM_PACKAGE_H_

#include "common.h"

#ifdef __cplusplus
extern "C" {
#endif

#define RB_NEW_PACKAGE_WITH_PTR(ptr) Data_Wrap_Struct(cALPM_Package, NULL, alpm_package_deallocate, ptr)
#define RB_PACKAGE_GETTER_NAME(name) static VALUE alpm_package_get_ ## name(VALUE)
#define RB_PACKAGE_GETTER_SET(name) rb_define_method(cALPM_Package, #name, alpm_package_get_ ## name, 0 )
#define RB_PACKAGE_SIMPLE_GETTER_STRING(name) static VALUE alpm_package_get_ ## name(VALUE self) {\
  rb_alpm_package * handler;\
  const char * empty_str = "";\
  Data_Get_Struct(self, rb_alpm_package, handler);\
  const char * filename = alpm_pkg_get_ ## name(handler->handle);\
  return rb_str_new2( (filename != NULL) ? filename : empty_str );\
}

#define RB_PACKAGE_SIMPLE_GETTER_INTEGER(name) static VALUE alpm_package_get_ ## name(VALUE self) {\
  rb_alpm_package * handler;\
  Data_Get_Struct(self, rb_alpm_package, handler);\
  return INT2NUM((int)alpm_pkg_get_ ## name(handler->handle));\
}

#define RB_PACKAGE_SIMPLE_GETTER_LONG(name) static VALUE alpm_package_get_ ## name(VALUE self) {\
  rb_alpm_package * handler;\
  Data_Get_Struct(self, rb_alpm_package, handler);\
  return LONG2NUM((long)alpm_pkg_get_ ## name(handler->handle));\
}

#define RB_PACKAGE_SIMPLE_GETTER_TIME(name) static VALUE alpm_package_get_ ## name(VALUE self) {\
  rb_alpm_package * handler;\
  VALUE cTime = rb_const_get(rb_cObject, rb_intern("Time"));\
  alpm_time_t result;\
\
  Data_Get_Struct(self, rb_alpm_package, handler);\
  result = alpm_pkg_get_ ## name(handler->handle);\
\
  return rb_funcall(cTime, rb_intern("at"), 1, LONG2NUM((long)result));\
}

typedef struct {
  alpm_pkg_t * handle;
} rb_alpm_package;

void Init_alpm_package();

static VALUE alpm_package_allocate(VALUE);
void alpm_package_deallocate(void*);

VALUE alpm_package_load_from_file(int, VALUE*, VALUE);

RB_PACKAGE_GETTER_NAME(filename);
RB_PACKAGE_GETTER_NAME(base);
RB_PACKAGE_GETTER_NAME(name);
RB_PACKAGE_GETTER_NAME(version);
RB_PACKAGE_GETTER_NAME(origin);
RB_PACKAGE_GETTER_NAME(desc);
RB_PACKAGE_GETTER_NAME(url);
RB_PACKAGE_GETTER_NAME(builddate);
RB_PACKAGE_GETTER_NAME(installdate);
RB_PACKAGE_GETTER_NAME(packager);
RB_PACKAGE_GETTER_NAME(builddate);
RB_PACKAGE_GETTER_NAME(md5sum);
RB_PACKAGE_GETTER_NAME(sha256sum);
RB_PACKAGE_GETTER_NAME(arch);
RB_PACKAGE_GETTER_NAME(size);
RB_PACKAGE_GETTER_NAME(isize);
RB_PACKAGE_GETTER_NAME(reason);
RB_PACKAGE_GETTER_NAME(licenses);
RB_PACKAGE_GETTER_NAME(groups);
RB_PACKAGE_GETTER_NAME(depends);
RB_PACKAGE_GETTER_NAME(optdepends);
RB_PACKAGE_GETTER_NAME(conflicts);
RB_PACKAGE_GETTER_NAME(provides);
RB_PACKAGE_GETTER_NAME(deltas);
RB_PACKAGE_GETTER_NAME(replaces);
RB_PACKAGE_GETTER_NAME(files);
RB_PACKAGE_GETTER_NAME(backup);
RB_PACKAGE_GETTER_NAME(db);
RB_PACKAGE_GETTER_NAME(base64_sig);
RB_PACKAGE_GETTER_NAME(validation);

#ifdef __cplusplus
}
#endif

#endif
