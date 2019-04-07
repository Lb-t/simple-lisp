#include "lisp.h"
#include "string.h"
#include <editline/readline.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_INPUT_LEN 2048

void parse_input(char *buf) {
  sl_object_t *obj;
  int res = sl_parse(&obj, buf, strlen(buf));
  if (res < 0) {
    fprintf(stderr, "parse error.\n");
  } else {
    if (obj) {
      printf("%s\n", obj->cls->type_name);
      sl_object_print(obj);
    }
  }
}

int main(void) {
  printf("Welcom to simple-lisp\n");
  printf("Press C-C to exit.\n");
  char *buf;
  while ((buf = readline("simple-lisp>"))) {
    add_history(buf);
    parse_input(buf);
    free(buf);
  }
  return 0;
}
