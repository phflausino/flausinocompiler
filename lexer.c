#include <stdio.h>
#include <stdlib.h>
#include "compiler.h"
#include "utils/list.h"
#include "utils/str_dynamic.h"

#define NUMERIC_CASE  \
  case '1':           \
  case '2':           \
  case '3':           \
  case '4':           \
  case '5':           \
  case '6':           \
  case '7':           \
  case '8':           \
  case '9'

#define GET_C_IF(sd, condition)                         \
  for(char c = peekc(lp); condition; c = peekc(lp)) {   \
    str_dynamic_add(sd, c);                             \
    c = nextc(lp);                                      \
  }

struct token* create_number_token(struct lex_process* lp) {
  struct token* tk = malloc(sizeof(struct token));
  struct str_dynamic* sd = create_str_dynamic();
  
  GET_C_IF(sd, (c >= '0' && c <= '9'));

  str_dynamic_end(sd);
  tk->type = TOKEN_TYPE_NUMBER;
  tk->llnum = atoll(sd->s);
  return tk;
}

struct token* create_token(struct lex_process* lp);

struct token* handle_white_space(struct lex_process* lp) {
  nextc(lp);
  return create_token(lp);
}

struct token* create_token(struct lex_process* lp) {
  struct token* tk = NULL;
  char c = peekc(lp);
  switch (c) {
    NUMERIC_CASE:
      tk = create_number_token(lp);
      break;

    case ' ':
    case '\t':
      tk = handle_white_space(lp);
      break;

    case EOF: break;

    default:
      printf("Unknow token type");
  }
  return tk;
}

void print_tokens(void* value) {
  struct token* tk = (struct token*)value;
  printf("Token type: %d, value: %lld\n", tk->type, tk->llnum);
}

int lex(struct lex_process* lp) {
  struct token* token = create_token(lp);
  while(token) {
    list_add_node(lp->tokens, token);
    token = create_token(lp);
  }
  list_for_each(lp->tokens, print_tokens);
  return LEXICAL_ANALYSIS_SUCCESS;
}

