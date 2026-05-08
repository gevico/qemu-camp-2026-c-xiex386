#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LINE_LENGTH 1024

int parse_replace_command(const char* cmd, char** old_str, char** new_str) {
    if (cmd[0] != 's' || cmd[1] != '/') {
        return -1;
    }

    const char* first_slash = strchr(cmd, '/');
    if(!first_slash)
        return -1;
    const char* second_slash = strchr(first_slash + 1, '/');
    if(!second_slash)
        return -1;
    const char* third_slash = strchr(second_slash + 1, '/');
    if(!third_slash)
        return -1;

    size_t old_len = second_slash - first_slash - 1;
    size_t new_len = third_slash - second_slash - 1;
    *old_str = (char*)malloc(old_len + 1);
    if(!*old_str)
        return -1;
    *new_str = (char*)malloc(new_len + 1);
    if(!*new_str) {
        free(old_str);
        return -1;
    }

    strncpy(*old_str, first_slash + 1, old_len);
    (*old_str)[old_len] = '\0';
    strncpy(*new_str, second_slash + 1, new_len);
    (*new_str)[new_len] = '\0';

    return 0;
}

void replace_first_occurrence(char* str, const char* old, const char* new) {
    size_t old_len = strlen(old), new_len = strlen(new);
    char *occurrence = strstr(str, old), *src_ptr, *dst_ptr;

    if(!occurrence)
        return;

    src_ptr = &occurrence[old_len], dst_ptr = &occurrence[new_len];
    if(old_len < new_len) {
        while(*src_ptr != '\0') {
            src_ptr++, dst_ptr++;
        }
        while(src_ptr >= &occurrence[old_len]) {
            *(dst_ptr--) = *(src_ptr--);
        }
    } else {
        while(*src_ptr != '\0') {
            *(dst_ptr++) = *(src_ptr++);
        }
        *dst_ptr = '\0';
    }
    while(*new != '\0') {
        *(occurrence++) = *(new++);
    }
}

int main(int argc, char* argv[]) {
    const char* replcae_rules = "s/unix/linux/";

    char line[MAX_LINE_LENGTH] = {"unix is opensource. unix is free os."};

    char* old_str = NULL;
    char* new_str = NULL;
    
    if (parse_replace_command(replcae_rules, &old_str, &new_str) != 0) {
        fprintf(stderr, "Invalid replace command format. Use 's/old/new/'\n");
        return 1;
    }

    
    replace_first_occurrence(line, old_str, new_str);
    fputs(line, stdout);

    free(old_str);
    free(new_str);
    return 0;
}
