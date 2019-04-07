#include "sl_decimal.h"
#include "lisp.h"
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>

int sl_decimal_parse(sl_object_t *obj, const char *str, unsigned int len) {
  sl_decimal_t *dec = (sl_decimal_t *)obj;
  unsigned int pos = 0;
  long long value = 0;
  bool negtive = false;
  bool valid = false;

  while (pos < len && str[pos] == ' ')
    ++pos;

  if (str[pos] == '-') {
    negtive = true;
    ++pos;
  }

  while (pos < len) {
    if (str[pos] >= '0' && str[pos] <= '9') {
      valid = true;
      value *= 10;
      value += str[pos] - '0';
      if (!negtive && value > (long long)INT_MAX) {
        return -1;
      } else if (negtive && (value > (long long)INT_MAX + 1)) {
        return -1;
      }
    } else {
      if (valid) {
        break;
      } else {
        return -1;
      }
    }
    pos++;
  }

  if (negtive) {
    dec->value = value * -1;
  } else {
    dec->value = value;
  }
  return pos;
}

sl_object_t *sl_decimal_eval(sl_object_t *obj) { return obj; }

void sl_decimal_print(sl_object_t *obj) {
  sl_decimal_t *dec = (sl_decimal_t *)obj;
  printf("%lld\n", dec->value);
}

int sl_decimal_init(sl_object_t *obj) {
  sl_decimal_t *dec = (sl_decimal_t *)obj;
  dec->sl_object.cls = sl_get_class_of_type(SL_DECIMAL);
  dec->value = 0;
  return 0;
}

void sl_decimal_deinit(sl_object_t *obj) {
  sl_decimal_t *dec = (sl_decimal_t *)obj;
  dec->value = 0;
}

SL_CLASS_DEFINE(decimal, DECIMAL);
