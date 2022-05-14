#include "fileholder.h"

int getfilelen(char *path) {
    FILE *fp = NULL; 
    fp = fopen(path, "rb");
    if (fp == NULL) return -1;
    fseek(fp, 0, SEEK_END);
    int len = ftell(fp);
    fclose(fp);
    //printf("return len: %d\n", len);
    return len; 
}

void read_file(char *path, char *buffer, int len) {
    FILE *fp = NULL; 
    fp = fopen(path, "rb"); 
    fread(buffer, sizeof(char), len, fp);
    fclose(fp);
    //printf("read file\n");
}