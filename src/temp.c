#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void) {

    char** buf = (char**) malloc(sizeof(char*) * 2);
    buf[0] = malloc(sizeof(char) * 24);
    buf[1] = malloc(sizeof(char) * 24);
    buf[0] = "hello";
    buf[1] = "world";

    printf("%s %s ", buf[0], buf[1]); 

    char* word = "green";

    memmove(buf[0], word, strlen(word));

    printf("%s %s ", buf[0], buf[1]); 


    return 0;
}