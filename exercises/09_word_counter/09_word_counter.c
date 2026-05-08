#include <stdio.h>

int main() {
    char str[]="Don't ask what your country can do for you, but ask what you can do for your country.";
    int wordCount = 0;
    
    int cur_len = 0;
    for(char *ch = str; *ch != '\0'; ch++) {
        if(*ch != ' ') {
            cur_len++;
        } else if(cur_len > 0) {
            wordCount++;
            cur_len = 0;
        }
    }
    if(cur_len > 0) {
        wordCount++;
    }
    
    printf("单词数量: %d\n", wordCount);
    
    return 0;
}