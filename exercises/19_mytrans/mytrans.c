// mytrans.c
#include "myhash.h"
#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void trim(char *str) {
  char *cur = str;
  while(isspace((unsigned char)*cur)) {
    cur++;
  }

  char *end = cur;
  while(*end != '\0') {
    end++;
  }
  end--;
  while(end > cur && isspace((unsigned char)*end))
    *(end--) = '\0';

  while(cur <= end) {
    *(str++) = *(cur++);
  }
  *str = '\0';
}

int load_dictionary(const char *filename, HashTable *table,
                    uint64_t *dict_count) {
  FILE *file = fopen(filename, "r");
  if (!file) {
    perror("无法打开词典文件");
    return -1;
  }

  char line[1024];
  char current_word[100] = {0};
  char current_translation[1024] = {0};
  int in_entry = 0;

  while(fgets(line, sizeof(line), file)) {
    trim(line);
    if(line[0] == '\0')
      continue;

    if(in_entry) {
      if(strncmp(line, "Trans:", 6) == 0) {
        strcpy(current_translation, &line[6]);
        if(hash_table_insert(table, current_word, current_translation)) {
          (*dict_count)++;
        }
        in_entry = 0;
      }
    } else if(line[0] == '#') {
      strcpy(current_word, &line[1]);
      in_entry = 1;
    }
  }
  

  fclose(file);
  return 0;
}
