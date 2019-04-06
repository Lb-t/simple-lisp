#pragma once
#include "sl_object.h"

typedef struct {
  sl_object_t sl_object;
  list_t element_list;
} sl_list_t;


sl_object_t *sl_list_eval(sl_list_t *expr);
