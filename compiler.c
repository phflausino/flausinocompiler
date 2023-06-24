#include "compiler.h"

int compile_file(char* input, char* output, int flags) {
  struct compiler_process* cp = compiler_process_create(input, output, flags);
  if(!cp)
    return COMPILER_FAILED;

  return COMPILER_OK;
}
