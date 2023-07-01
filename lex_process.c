#include <stdio.h>
#include <stdlib.h>
#include "compiler.h"
#include "utils/list.h"

struct lex_process* lex_process_create(struct compiler_process* compiler) {
  struct lex_process* lp = malloc(sizeof(struct lex_process));
  lp->compiler = compiler;
  lp->tokens = create_list(sizeof(struct token));
  return lp;
}

char nextc(struct lex_process* lp) {
  struct compiler_process* cp = lp->compiler;
  char c = getc(cp->cfile.fp);
  cp->pos.col += 1; 
  if(c == '\n') {
    cp->pos.line += 1;
    cp->pos.col = 1; 
  }
  return c;
}

char peekc(struct lex_process* lp) {
  struct compiler_process* cp = lp->compiler;
  char c = getc(cp->cfile.fp);
  ungetc(c, cp->cfile.fp);
  return c;
}

void pushc(struct lex_process* lp, char c) {
  struct compiler_process* cp = lp->compiler;
  ungetc(c, cp->cfile.fp);
}
