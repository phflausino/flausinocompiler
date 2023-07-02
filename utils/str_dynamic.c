#include <stdlib.h>
#include "str_dynamic.h"

struct str_dynamic* create_str_dynamic() {
  struct str_dynamic* sd = malloc(sizeof(struct str_dynamic)); 
  sd->s = malloc(sizeof(char) * REALLOC_SIZE);
  sd->length = 0;
  sd->realloc_len = REALLOC_SIZE;
  return sd;
}

void str_realloc(struct str_dynamic* sd) {
  size_t curr_byte_size = (sizeof(char) * sd->length);
  size_t new_byte_size = curr_byte_size + (sizeof(char) * REALLOC_SIZE);
  sd->s = realloc(sd->s, new_byte_size);
  sd->realloc_len += REALLOC_SIZE;
}

void check_length(struct str_dynamic* sd) {
  if(sd->length == sd->realloc_len) 
    str_realloc(sd);
};

void str_dynamic_add(struct str_dynamic* sd, char c) {
  check_length(sd);
  sd->s[sd->length] = c;
  sd->length += 1;
}

void str_dynamic_end(struct str_dynamic* sd) {
  check_length(sd);
  sd->s[sd->length] = '\0';
}
