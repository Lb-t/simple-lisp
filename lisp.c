#include "lisp.h"

SL_CLASS_DECLARE(decimal);
SL_CLASS_DECLARE(list);

// must in same order with type enum
sl_class_t *const sl_class[] = {SL_CLASS_ENTRY(decimal), SL_CLASS_ENTRY(list),
                                NULL};

int sl_parse(sl_object_t **obj, const char *str, unsigned int len) {
  unsigned int pos = 0;
  *obj = NULL;
  while (pos < len && str[pos] == ' ')
    ++pos;
  if (pos == len) {
    /*all space*/
    return 0;
  }

  if (str[pos] == '(') {
    *obj = sl_object_new(SL_LIST);
  } else if (str[pos] == '\'') {
    // todo:
    return -1;
  } else if (str[pos] >= '0' && str[pos] <= '9') {
    *obj = sl_object_new(SL_DECIMAL);
  } else if (pos + 1 < len && str[pos] == '-' && str[pos + 1] >= '0' &&
             str[pos + 1] <= '9') {
    *obj = sl_object_new(SL_DECIMAL);
  } else if (str[pos] == '\"') {
    // todo:
    return -1;
  } else {
    // todo:
    return pos;
  }

  int res = sl_object_parse(*obj, str + pos, len - pos);
  if (res < 0) {
    sl_object_delete(*obj);
    return -1;
  }

  return pos+res;
}
