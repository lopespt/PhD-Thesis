#ifndef UTILS_HPP
#define UTILS_HPP

#include <stdio.h>
#include <stdarg.h>

class Utils
{
public:

    static char* readLine(char* buffer, int size, FILE* f);
    static bool fileExists(char* filename);
};

void warn(const char* format, ...);
#endif // UTILS_HPP
