#ifndef STR_DYNAMIC_H
#define STR_DYNAMIC_H

#define REALLOC_SIZE 150

struct str_dynamic {
  char* s;
  int length;
  int realloc_len;
};

struct str_dynamic* create_str_dynamic();
void str_dynamic_add(struct str_dynamic* sd, char c);
void str_dynamic_end(struct str_dynamic* sd);

#endif
