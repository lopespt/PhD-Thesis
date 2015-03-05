#ifndef UTILS_HPP
#define UTILS_HPP

#include <stdio.h>
#include <stdarg.h>
#include <opencv/cv.h>
class QPolygon;
class QImage;
class Utils
{
public:

    static char* readLine(char* buffer, int size, FILE* f);
    static bool fileExists(const char* filename);
    static cv::Mat QImage2Mat(const QImage& img);
    static QPolygon Mask2QPolygon(const cv::Mat& img);
};

void warn(const char* format, ...);
#endif // UTILS_HPP
