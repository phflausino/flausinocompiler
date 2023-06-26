#ifndef FLAUSINOCOMPILER_H
#define FLAUSINOCOMPILER_H

#include <stdio.h>

enum {
  COMPILER_OK,
  COMPILER_FAILED
};

enum {
  TOKEN_TYPE_NUMBER
};

struct token {
  int type;

  union {
    unsigned int inum;
    unsigned long lnum;
    unsigned long long llnum;
    void* any;
  };
};

struct compiler_process {
  int flags;

  struct compile_input_file {
    FILE* fp;
    char* abs_path;
  } cfile;

  FILE* out_file;
};

int compile_file(char* input, char* output, int flags);
struct compiler_process* compiler_process_create(char* in_file, char* out_file, int flags);

#endif
