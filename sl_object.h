#pragma once
#include "list.h"

typedef unsigned int sl_type_t;
struct sl_object_s;
typedef struct sl_object_s sl_object_t;
typedef struct {
  int (*init)(sl_object_t *);
  void (*deinit)(sl_object_t *);
  sl_object_t *(*eval)(sl_object_t *);
  int (*parse)(sl_object_t *, const char *, unsigned int);
} sl_vtable_t;

typedef struct {
  char type_name[64];
  sl_type_t type;
  unsigned int size;
  sl_vtable_t vtable;
} sl_class_t;

struct sl_object_s {
  sl_class_t *cls;
  list_head_t head;
};

typedef struct {
  sl_object_t sl_object;
  double value;
} sl_float_t;

#define SL_CLASS_DEFINE(name, NAME)                                            \
  const sl_class_t sl_class_##name##_ = {                                      \
      .type_name = #name,                                                      \
      .vtable = {.init = sl_##name##_init,                                     \
                 .deinit = sl_##name##_deinit,                                 \
                 .parse = sl_##name##_parse},                                  \
      .type = SL_##NAME,                                                       \
      .size = sizeof(sl_##name##_t)};

#define SL_CLASS_DECLARE(name) extern sl_class_t sl_class_##name##_;
#define SL_CLASS_ENTRY(name) (&sl_class_##name##_)

#define sl_get_type(obj) ((obj)->sl_object.cls->type)

sl_object_t *sl_object_new(sl_type_t type);
void sl_object_delete(sl_object_t *object);
sl_class_t *sl_get_class_of_type(sl_type_t type);
int sl_object_parse(sl_object_t *obj, const char *str, unsigned int len);
int sl_object_print(sl_object_t *obj);
