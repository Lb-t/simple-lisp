#include "sl_list.h"
#include "lisp.h"
#include <stdlib.h>

/*initial a empty list*/
int sl_list_init(sl_object_t *obj) {
  sl_list_t *list = (sl_list_t *)obj;
  list->sl_object.cls = sl_get_class_of_type(SL_LIST);
  list_init(&list->element_list);
  return 0;
}

void sl_list_deinit(sl_object_t *obj) {
  sl_list_t *list = (sl_list_t *)obj;
  list_for_each_entry(obj, &list->element_list, sl_object_t, head) {
    obj->cls->vtable.deinit(obj);
  }
}

int sl_list_parse(sl_object_t *obj, const char *str, unsigned int len) {
  sl_list_t *list = (sl_list_t *)obj;
  unsigned int pos = 0;
  while (pos < len && str[pos] == ' ')
    ++pos;

  if (str[pos] != '(') {
    return -1;
  } else {
    ++pos;
  }
  while (pos < len) {
    sl_object_t *obj;
    if (str[pos] == ')') {
      return 0;
    } else {
      int res = sl_parse(&obj, str + pos, len - pos);
      if (res < 0) {
        // todo:errr handler
        return -1;
      } else {
        if (obj) {
          list_insert_tail(&list->element_list, &obj->head);
        }
        pos += res;
      }
    }
  }
  return pos;
}

void sl_list_print(sl_object_t *obj) {
  sl_list_t *list = (sl_list_t *)obj;
  printf("(");
  list_for_each_entry(obj, &list->element_list, sl_object_t, head) {
    obj->cls->vtable.print(obj);
    printf(" ");
  }
  printf(")\n");
}

SL_CLASS_DEFINE(list, LIST);
