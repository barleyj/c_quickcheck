#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../inc/quickcheck.h"

int for_all(generator generate, validator validate, disposer dispose) {
  int i;
  int return_value;
  void *value = NULL;

  for (i = 0; i < 100; ++i) {
    (*generate)(&value);
    return_value = (*validate)(&value);
    if(dispose) {
      (*dispose)(&value);
    }
    if(return_value == false) {
      break;
    }
  }

  return return_value;
}
