#include "Utils.hpp"
#include <opencv/highgui.h>

using namespace std;

char *Utils::readLine(char *buffer, int i, FILE *f) {

    if (fgets(buffer, i, f) != NULL) {
        buffer[strlen(buffer) - 1] = '\0';
        return buffer;
    }

    return NULL;
}


bool Utils::fileExists(QString filename) {
    return fileExists(filename.toStdString().c_str());
}

bool Utils::fileExists(const char *filename) {
    FILE *f = fopen(filename, "r");
    if (f) {
        fclose(f);
        return true;
    }
    return false;
}

void warn(const char *format, ...) {
    va_list v1;
    va_start(v1, format);
    vfprintf(stderr, format, v1);
    va_end(v1);
}

cv::Mat Utils::QImage2Mat(const QImage &img) {
    cv::Mat ret(img.height(), img.width(), CV_8UC4, (uchar *) img.bits(), img.bytesPerLine());
    return ret;
}


QPolygon Utils::Mask2QPolygon(const cv::Mat &img) {
    QPolygon ret;
    QList<QPolygon> list;

    Mask2QPolygon(img, ret, list);
    return ret;
}

QPolygon &Utils::Mask2QPolygon(const cv::Mat &img, QPolygon &poly, QList<QPolygon> &holes) {
    poly.clear();
    vector<vector<cv::Point> > contours;
    vector<cv::Vec4i> hierarchy;
    cv::findContours(img.clone(), contours, hierarchy, CV_RETR_CCOMP, CV_CHAIN_APPROX_TC89_KCOS, cv::Point(0, 0));

    assert(contours.size() > 0);

    for (unsigned int i = 0; i < contours[0].size(); i++) {
        poly.append(QPoint(contours[0][i].x, contours[0][i].y));
    }

    int idHole = hierarchy[0][2];
    for (; idHole != -1; idHole = hierarchy[idHole][0]) {
        QPolygon pnew;
        for (unsigned int i = 0; i < contours[idHole].size(); i++) {
            pnew.append(QPoint(contours[idHole][i].x, contours[idHole][i].y));
        }
        holes.append(pnew);
    }

    return poly;
}


void Utils::QPolygon2CvPointArray(const QPolygon &poly, vector<vector<cv::Point>> &points) {
    points.clear();
    vector<cv::Point> newPoint;
    for (int i = 0; i < poly.size(); i++) {
        newPoint.push_back(cvPoint(poly[i].x(), poly[i].y()));
    }
    points.push_back(newPoint);
}

cv::Mat &Utils::QPolygon2Mask(cv::Mat &img, const QPolygon external, const QList<QPolygon> &holes) {
    vector<vector<cv::Point> > points;

    QPolygon2CvPointArray(external, points);
    cv::fillPoly(img, points, cvScalarAll(255), 4);

    for (const QPolygon &hole : holes) {
        points.clear();
        QPolygon2CvPointArray(hole, points);
        cv::fillPoly(img, points, cvScalarAll(0), 4);

    }
    return img;
}

