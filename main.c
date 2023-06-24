#include <stdio.h>
#include "compiler.h"

int main () {
  int status = compile_file("test.c", "test", 0);
  if(status == COMPILER_OK) 
    printf("All compiled OK\n");
  else if (status == COMPILER_FAILED)
    printf("Could not compile\n");
  else
    printf("Unknown error\n");
  return 0;
}
