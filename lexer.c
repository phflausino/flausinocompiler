#include <stdio.h>
#include <stdlib.h>
#include "compiler.h"
#include "utils/list.h"

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

struct token* create_number_token(struct lex_process* lp) {
  struct token* tk = malloc(sizeof(struct token));
  char* num_str = malloc(10);
  int i = 0;
  char c = nextc(lp); 
  while(i < 9 && (c >= '0' && c <= '9')) {
   num_str[i] = c;
   ++i;
   c = nextc(lp);
  }
  num_str[9] = '\0';
  tk->type = TOKEN_TYPE_NUMBER;
  tk->llnum = atoll(num_str);
  return tk;
}

struct token* create_token(struct lex_process* lp) {
  struct token* tk = NULL;
  char c = peekc(lp);
  switch (c) {
    NUMERIC_CASE:
      tk = create_number_token(lp);
      break;
    case EOF:
    case ' ':
    case '\t':
      break;
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

