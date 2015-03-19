#include "Utils.hpp"
#include <string.h>
#include <QImage>
#include <opencv/cv.h>
#include <opencv/cxcore.h>
#include <opencv/highgui.h>
#include <vector>
#include <QString>

using namespace std;
char* Utils::readLine(char *buffer, int i, FILE* f){

    if(fgets(buffer, i, f) != NULL){
        buffer[strlen(buffer)-1]='\0';
        return buffer;
    }

    return NULL;
}


bool Utils::fileExists(QString filename){
    return fileExists(filename.toStdString().c_str());
}

bool Utils::fileExists(const char *filename){
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
cv::Mat Utils::QImage2Mat(const QImage& img){
    cv::Mat ret(img.height(), img.width(), CV_8UC4, (uchar*)img.bits(), img.bytesPerLine());
    return ret;
}


QPolygon Utils::Mask2QPolygon(const cv::Mat& img){
    QPolygon ret;
    vector<vector<cv::Point> > contours;
    vector<cv::Vec4i> hierarchy;
    cv::findContours( img.clone(), contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_TC89_KCOS, cv::Point(0, 0) );

    assert(contours.size()>0);

    for(unsigned int i=0;i<contours[0].size();i++){
        ret.append(QPoint(contours[0][i].x,contours[0][i].y));
    }
    return ret;
}











