#pragma once

#include "sl_object.h"


typedef struct {
  sl_object_t sl_object;
  long long value;
} sl_decimal_t;

int sl_decimal_parse(sl_object_t *obj,const char*str,unsigned int len);
