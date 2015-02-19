#ifndef UTILS_HPP
#define UTILS_HPP

#include <stdio.h>

class Utils
{
public:

    static char* readLine(char* buffer, int size, FILE* f);
    static bool fileExists(char* filename);

};

#endif // UTILS_HPP
