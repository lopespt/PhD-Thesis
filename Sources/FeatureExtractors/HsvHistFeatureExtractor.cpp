
#include "HsvHistFeatureExtractor.hpp"
#include <opencv2/core/core_c.h>

HsvHistFeatureExtractor::HsvHistFeatureExtractor(){
}

QVector<float> HsvHistFeatureExtractor::doExtraction(const Region* region, int discretization){
    QVector<float> vect(1);

    cv::Mat hsv, src=region->getCvImage();
    cv::cvtColor(src, hsv, CV_BGR2HSV);
    int hbins = discretization;
    int sbins = 3;
    const int channels[] = {0,1};
    cv::MatND hist;
    const int histSize[] = {hbins, sbins};

    float hranges[] = { 0, 180 };
    float sranges[] = { 0, 256 };
    const float* ranges[] = { hranges, sranges };
    cv::calcHist(&hsv, 1, channels, cv::Mat(), hist, 2, histSize, ranges,true,false );

    double maxVal=0;
        cv::minMaxLoc(hist, 0, &maxVal, 0, 0);

    int scale = 10;
    cv::Mat histImg = cv::Mat::zeros(sbins*scale, hbins*10, CV_8UC3);

    for( int h = 0; h < hbins; h++ )
        for( int s = 0; s < sbins; s++ ){
            float binVal = hist.at<float>(h, s);
            int intensity = cvRound(binVal*255/maxVal);
            cv::rectangle( histImg, cv::Point(h*scale, s*scale),
            cv::Point( (h+1)*scale - 1, (s+1)*scale - 1),
            cv::Scalar::all(intensity),
            CV_FILLED );
        }

    //cv::imwrite("imagem.png", histImg);

    return vect;
}


const char* HsvHistFeatureExtractor::getFeatureName(){
    return "AreaFeature";
}

