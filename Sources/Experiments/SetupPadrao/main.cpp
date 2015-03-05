#include <stdio.h>
#include <stdlib.h>
#include <ComplexNetwork/ComplexNetwork.hpp>
#include <Utilities/GraphUtilities.hpp>
#include <Utilities/IterativeRandomWalk.hpp>
#include <FeatureExtractors/FeatureFactoryAbstract.hpp>
#include <FeatureExtractors/AreaFeatureFactory.hpp>
#include <FeatureExtractors/LabelFeatureFactory.hpp>
#include <FeatureExtractors/OrientationFeatureFactory.hpp>
#include <QList>
#include <FeatureExtractors/HsvFeatureFactory.hpp>
#include <QHash>
#include <Utilities/DatabaseReader/SunDatabaseReader.hpp>
#include <Utilities/SupervisedImage.hpp>
#include <Utilities/ComplexNetworkConstructor/ComplexNetworkConstructor.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <QPointF>
#include <QPolygonF>
#include <QRectF>

#include <stdio.h>
#include <Utilities/VoronoiDiagramGenerator.hpp>
#include <Utilities/Utils.hpp>
#include <QImage>

using namespace cv;
int main(int argc, char** argv){
    QImage test("/Users/wachs/cores.jpg");
    imshow("teste", Utils::QImage2Mat(test));

    Mat m(400,400, CV_8UC1, cvScalarAll(0));
    VoronoiDiagramGenerator v;
    float x[] = {2,8,300,10, 15};
    float y[] = {5,5,25,40,200};

    v.generateVoronoi(x,y,5,-100,500,-100,500);

    float px, py, p2x, p2y;
    printf("entrando no while\n");
    v.resetIterator();
    //rectangle(m, cv::Point(0,0), cv::Point(399,399),cvScalarAll(255));
    while(v.getNext(px,py,p2x,p2y)){
        line(m,cv::Point(px,py), cv::Point(p2x,p2y), cvScalarAll(255), 1);
        printf("%f %f %f %f\n", px, py, p2x, p2y);
    }
    Mat vor = m.clone();
    for(int i=0;i<5;i++){
        m = vor.clone();
        floodFill(m,cv::Point(x[i],y[i]), cvScalarAll(255));
        erode(m,m, getStructuringElement(MORPH_ERODE, cv::Size(3,3)));
        dilate(m,m, getStructuringElement(MORPH_DILATE, cv::Size(3,3)));
        QPolygon pp = Utils::Mask2QPolygon(m);
        //QPolygon pp;
        for(const QPoint& polyp:pp){
            circle(m, cv::Point(polyp.x(), polyp.y()), 3, cvScalarAll(128),2);
            printf("%d %d\n", polyp.x(), polyp.y());
        }
        imshow("win", m);
        waitKey();
    }
    fflush(stdout);



    return 0;
}

