#ifndef UTILS_HPP
#define UTILS_HPP

#include <stdio.h>
#include <stdarg.h>
#include <math.h>
#include <opencv/cv.h>
#include <QList>
#include <vector>
#include <QPolygon>
#include <QImage>

using namespace std;

class QPolygon;

class QImage;

class QString;

class Utils {
public:

    static char *readLine(char *buffer, int size, FILE *f);

    static bool fileExists(const char *filename);

    static bool fileExists(QString filename);

    static cv::Mat QImage2Mat(const QImage &img);

    static QPolygon Mask2QPolygon(const cv::Mat &img);

    static QPolygon &Mask2QPolygon(const cv::Mat &img, QPolygon &poly, QList<QPolygon> &holes);

    static cv::Mat &QPolygon2Mask(cv::Mat &img, const QPolygon external, const QList<QPolygon> &holes = QList<QPolygon>());

    static void QPolygon2CvPointArray(const QPolygon &poly, vector<vector<cv::Point> > &outputPoints);

    template<typename T>
    static T &normalizeVector(T a, unsigned int size) {
        double total = 0;
        for (unsigned int i = 0; i < size; i++) {
            total += a[i];
        }

        for (unsigned int i = 0; i < size; i++) {
            a[i] = a[i] / total;
        }

        return a;
    }

    template<template<typename, typename> class C, typename T>
    struct VectorGetter {
        const T &operator()(const C<T, std::allocator<T>> &a, unsigned int index) {
            return a[index];
        }
    };

    template<template<typename, typename> class C, typename T, class G = VectorGetter<C, T>>
    static double entropy(C<T, std::allocator<T>> &a, unsigned int size) {
        G acessor;
        double total = 0;
        for (unsigned int i = 0; i < size; i++) {
            double pi = acessor(a, i);
            if (pi > 0)
                total += pi * log2(pi);
        }
        return -total;

    }

    static QImage Mat2QImage(const cv::Mat3b &src);

    //static QImage Mat2QImage(const cv::Mat_ <double> &src);
};

void warn(const char *format, ...);

#endif // UTILS_HPP
