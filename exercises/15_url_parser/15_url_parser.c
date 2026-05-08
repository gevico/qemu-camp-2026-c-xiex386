#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

/**
 * URL参数解析器
 * 输入：包含http/https超链接的字符串
 * 输出：解析出所有的key-value键值对，每行显示一个
 */

int parse_url(const char* url) {
    int err = 0;
    char *split, *kv_start, *tok;

    if(strncmp(url, "http://", 7) != 0 && strncmp(url, "https://", 8) != 0) {
        err = 1;
        goto exit;
    }
    
    split = strchr(url, '?');
    if(!split) {
        goto exit;
    }

    split++;
    kv_start = malloc((strlen(split) + 1) * split[0]);
    strcpy(kv_start, split);
    tok = strtok(kv_start, "&");
    while(tok) {
        split = strchr(tok, '=');
        if(split) {
            *(split++) = '\0';
            printf("key = %s, value = %s\n", tok, split);
        }
        tok = strtok(NULL, "&");
    }
    free(kv_start);

exit:
    return err;
}

int main() {
    const char* test_url = "https://cn.bing.com/search?name=John&age=30&city=New+York";

    printf("Parsing URL: %s\n", test_url);
    printf("Parameters:\n");

    parse_url(test_url);

    return 0;
}