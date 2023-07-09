#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
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

#define OPERATOR_CASE \
  case '+':           \
  case '-':           \
  case '*':           \
  case '>':           \
  case '<':           \
  case '^':           \
  case '%':           \
  case '!':           \
  case '=':           \
  case '~':           \
  case '|':           \
  case '&':           \
  case '(':           \
  case '[':           \
  case ',':           \
  case '.':           \
  case '?'

#define SYMBOL_CASE  \
  case '{':          \
  case '}':          \
  case ')':          \
  case ']':          \
  case ':':          \
  case ';':          \
  case '#':          \
  case '\\'         


#define GET_C_IF(sd, condition)                         \
  for(char c = peekc(lp); condition; c = peekc(lp)) {   \
    str_dynamic_add(sd, c);                             \
    c = nextc(lp);                                      \
  }

struct token* create_token(struct lex_process* lp);

struct token* create_number_token(struct lex_process* lp) {
  struct token* tk = malloc(sizeof(struct token));
  struct str_dynamic* sd = create_str_dynamic();
  
  GET_C_IF(sd, (c >= '0' && c <= '9'));

  str_dynamic_end(sd);
  tk->type = TOKEN_TYPE_NUMBER;
  tk->llnum = atoll(sd->s);
  return tk;
}

struct token* create_string_token(struct lex_process* lp) {
  nextc(lp); // skip double quote
  struct token* tk = malloc(sizeof(struct token));
  struct str_dynamic* sd = create_str_dynamic();
  
  /*
   * TODO: handle escapes like \n
   */
  GET_C_IF(sd, (c != '"'));
  nextc(lp); // skip double quote terminator

  tk->type = TOKEN_TYPE_STRING;
  tk->sval = sd->s;
  return tk; 
}

bool op_can_join(char op) {
  switch(op) {
    case '(':
    case '[':
    case ',':
    case '.':
    case '*':
    case '?':
      return false;
    default:
      return true;
  }
}

bool is_single_op(char op) {
  switch(op) {
    case '/':
    OPERATOR_CASE:
      return true;
    default:
      return false;
  }
}

bool is_valid_op(char* op) {
  return (
    S_EQ(op, "+") || 
    S_EQ(op, "-") || 
    S_EQ(op, "*") || 
    S_EQ(op, "/") || 
    S_EQ(op, "!") || 
    S_EQ(op, "^") || 
    S_EQ(op, "+=") || 
    S_EQ(op, "-=") || 
    S_EQ(op, "*=") || 
    S_EQ(op, "/=") || 
    S_EQ(op, ">>") || 
    S_EQ(op, "<<") || 
    S_EQ(op, ">=") || 
    S_EQ(op, "<=") || 
    S_EQ(op, ">") || 
    S_EQ(op, "<") || 
    S_EQ(op, "||") || 
    S_EQ(op, "&&") || 
    S_EQ(op, "|") || 
    S_EQ(op, "&") || 
    S_EQ(op, "++") || 
    S_EQ(op, "--") || 
    S_EQ(op, "=") || 
    S_EQ(op, "!=") || 
    S_EQ(op, "==") || 
    S_EQ(op, "==") || 
    S_EQ(op, "->") ||
    S_EQ(op, "(") ||
    S_EQ(op, "[") ||
    S_EQ(op, ",") ||
    S_EQ(op, ".") ||
    S_EQ(op, "...") ||
    S_EQ(op, "~") ||
    S_EQ(op, "?") ||
    S_EQ(op, "%")
  );   
}

char* op_joined_to_single(struct lex_process* lp, char* op) {
  int size = strlen(op);
  for(int i = size; i >= 1; i--) {
    if(op[i] == '\0')
      continue;
    pushc(lp, (char)op[i]);
  }
  op[1] = '\0';
  return op;
}

struct token* create_op_token(struct lex_process* lp) {
  struct token* tk = malloc(sizeof(struct token));
  struct str_dynamic* sd = create_str_dynamic();
  bool single_op = true;

  char op = nextc(lp);

  str_dynamic_add(sd, op);
  if(op_can_join(op)) {
    char next_op = peekc(lp);
    if(is_single_op(next_op)) {
      str_dynamic_add(sd, nextc(lp));
      single_op = false;
    }
  }
  str_dynamic_end(sd);

  char* final_op = sd->s;

  if(!is_valid_op(final_op)) 
    if(single_op)
      printf("\nINVALID OPERATOR: %s\n", final_op);
    else
      final_op = op_joined_to_single(lp, final_op);

  tk->type = TOKEN_TYPE_OPERATOR;
  tk->sval = final_op;
  return tk;
}

struct token* handle_white_space(struct lex_process* lp) {
  nextc(lp);
  return create_token(lp);
}

struct token* create_symbol_token(struct lex_process* lp) {
  struct token* tk = malloc(sizeof(struct token));
  char c = nextc(lp);
  tk->type = TOKEN_TYPE_SYMBOL;
  tk->cval = c;
  return tk;
}

struct token* create_token(struct lex_process* lp) {
  struct token* tk = NULL;
  char c = peekc(lp);
  switch (c) {
    NUMERIC_CASE:
      tk = create_number_token(lp);
      break;

    OPERATOR_CASE:
      tk = create_op_token(lp);
      break;

    SYMBOL_CASE:
      tk = create_symbol_token(lp);
      break;

    case ' ':
    case '\t':
      tk = handle_white_space(lp);
      break;

    case '"':
      tk = create_string_token(lp);
      break;

    case EOF: break;

    default:
      printf("Unknow token type\n");
  }
  return tk;
}

void print_tokens(void* value) {
  struct token* tk = (struct token*)value;
  if(tk->type == TOKEN_TYPE_STRING || tk->type == TOKEN_TYPE_OPERATOR) 
    printf("Token type: %d, value: %s\n", tk->type, tk->sval);
  else if(tk->type == TOKEN_TYPE_SYMBOL) 
    printf("Token type: %d, value: %c\n", tk->type, tk->cval);
  else
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

