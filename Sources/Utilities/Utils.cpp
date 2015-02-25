#include "Utils.hpp"
#include <string.h>


char* Utils::readLine(char *buffer, int i, FILE* f){

    if(fgets(buffer, i, f) != NULL){
        buffer[strlen(buffer)-1]='\0';
        return buffer;
    }

    return NULL;
}


bool Utils::fileExists(char *filename){
    FILE *f = fopen(filename, "r");
    if(f){
        fclose(f);
        return true;
    }
    return false;
}

void warn(const char* format, ...){
    va_list v1;
    va_start(v1, format);
    vfprintf(stderr, format, v1);
    va_end(v1);
}
