#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "global.h"


int main() {

    printf("head\n"); 
    char *tmp;
    tmp = malloc(17);
    tmp[0] = 0; 
    strcat(tmp, "12356");
    printf("%d %s\n", sizeof(tmp), tmp);

    return 0; 
}