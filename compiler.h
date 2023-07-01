#ifndef FLAUSINOCOMPILER_H
#define FLAUSINOCOMPILER_H

#include <stdio.h>
#include "utils/list.h"

/* Token Related */
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

/* Compiler Process Related */
enum {
  COMPILER_OK,
  COMPILER_FAILED
};
struct pos {
  int line;
  int col;
  char* filename;
};
struct compiler_process {
  int flags;

  struct compile_input_file {
    FILE* fp;
    char* abs_path;
  } cfile;

  struct pos pos;

  FILE* out_file;
};
int compile_file(char* input, char* output, int flags);
struct compiler_process* compiler_process_create(char* in_file, char* out_file, int flags);

/* Lexical Process Related */
enum {
  LEXICAL_ANALYSIS_SUCCESS,
  LEXICAL_ANALYSIS_ERROR,
};
struct lex_process {
  list_ptr tokens;
  struct compiler_process* compiler;
};
struct lex_process* lex_process_create(struct compiler_process* compiler);
int lex(struct lex_process* lp);
char nextc(struct lex_process* lp);
char peekc(struct lex_process* lp);
void pushc(struct lex_process* lp, char c);

#endif
