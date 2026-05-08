#include <stdio.h>

int main() {
    char source[] = "Hello, World! This is a test string for my_strcpy function.\n";
    char destination[101];
    
	for(char *src = source, *dst = destination; *src != '\0';) {
        *(dst++) = *(src++);
    }
    
    printf("拷贝后的字符串: %s", destination);
    
    return 0;
}