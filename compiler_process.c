#include <stdio.h>
#include <stdlib.h>
#include "compiler.h"

struct compiler_process* compiler_process_create(char* in_file, char* out_file, int flags) {
  FILE* input = fopen(in_file, "r");
  if(!input)
    return NULL;

  FILE* output = NULL;
  if(out_file) {
    output = fopen(out_file, "w");
    if(!output)
      return NULL;
  }

  struct compiler_process* process = calloc(1, sizeof(struct compiler_process));
  process->flags = flags;
  process->cfile.fp = input;
  process->out_file = output;
  return process;
}
