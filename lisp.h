#pragma once

enum {
      SL_DECIMAL,
      SL_LIST,
};

#include "sl_object.h"
#include "sl_decimal.h"
#include "sl_list.h"


int sl_parse(sl_object_t **obj, const char *str, unsigned int len);

