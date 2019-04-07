#include "sl_object.h"
#include "lisp.h"
#include <stdlib.h>

extern sl_class_t *const sl_class[];

sl_class_t *sl_get_class_of_type(sl_type_t type) { return sl_class[type]; }

sl_object_t *sl_object_new(sl_type_t type) {
  sl_class_t *cls = sl_get_class_of_type(type);
  sl_object_t *object = (sl_object_t *)malloc(cls->size);
  if (cls->vtable.init(object)) {
    free(object);
    return NULL;
  }
  return object;
}

void sl_object_delete(sl_object_t *obj) {
  obj->cls->vtable.deinit(obj);
  free(obj);
}


void sl_object_print(sl_object_t *obj){
  return obj->cls->vtable.print(obj);
  
}

int sl_object_parse(sl_object_t *obj, const char *str, unsigned int len) {
  return obj->cls->vtable.parse(obj, str, len);
}
