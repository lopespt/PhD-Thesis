#include <stdio.h>
#include <stdlib.h>
#include <ComplexNetwork/ComplexNetwork.hpp>
#include <Utilities/GraphUtilities.hpp>
#include <Utilities/IterativeRandomWalk.hpp>
#include <FeatureExtractors/AreaFeatureFactory.hpp>
#include <FeatureExtractors/LabelFeatureFactory.hpp>
#include <FeatureExtractors/OrientationFeatureFactory.hpp>
#include <Utilities/SupervisedImage.hpp>
#include <opencv/highgui.h>
#include <opencv2/opencv.hpp>
#include <Utilities/VoronoiDiagramGenerator.hpp>
#include <FeatureExtractors/HsvFeatureFactory.hpp>

using namespace cv;
using namespace Voronoi;
using namespace std;


int vec3diff(const Vec3i &a, const Vec3i &b) {
    int r = abs(a[0] - b[0]) + abs(a[1] - b[1]) + abs(a[2] - b[2]);
    printf("%d\n", r);
    return r;
}

int main(int argc, char **argv) {
    AreaFeatureFactory area(20);
    HsvFeatureFactory hsv(10,3,3,100);
    OrientationFeatureFactory orie(10);

    QImageCV original("/Users/wachs/Dropbox/Tese-Guilherme/Implementacoes/Doutorado/cpp/PhD-Thesis/Sources/Tests/Img.png");

    Region a(&original, imread("/Users/wachs/Dropbox/Tese-Guilherme/Implementacoes/Doutorado/cpp/PhD-Thesis/Sources/Tests/Mask1.png", CV_LOAD_IMAGE_GRAYSCALE));
    Region b(&original, imread("/Users/wachs/Dropbox/Tese-Guilherme/Implementacoes/Doutorado/cpp/PhD-Thesis/Sources/Tests/Mask2.png", CV_LOAD_IMAGE_GRAYSCALE));
    Region c(&original, imread("/Users/wachs/Dropbox/Tese-Guilherme/Implementacoes/Doutorado/cpp/PhD-Thesis/Sources/Tests/Mask3.png", CV_LOAD_IMAGE_GRAYSCALE));

    FeatureAbstractPtr fa = area.CreateFromRegion(&a);
    FeatureAbstractPtr fb = area.CreateFromRegion(&b);
    FeatureAbstractPtr fc = area.CreateFromRegion(&c);

    std::cout << fa << endl;
    std::cout << fb << endl;
    std::cout << fc << endl;

    fa = hsv.CreateFromRegion(&a);
    fb = hsv.CreateFromRegion(&b);
    fc = hsv.CreateFromRegion(&c);

    std::cout << fa << endl;
    std::cout << fb << endl;
    std::cout << fc << endl;


    fa = orie.CreateFromRegion(&a);
    fb = orie.CreateFromRegion(&b);
    fc = orie.CreateFromRegion(&c);

    std::cout << fa << endl;
    std::cout << fb << endl;
    std::cout << fc << endl;
}


int main4(int argc, char **argv) {

    SupervisedImage sup("/Users/wachs/SUN/Images/a/airfield/sun_bkoykzhsrosredze.jpg",
                        "/Users/wachs/SUN/Annotations/a/airfield/sun_bkoykzhsrosredze.xml");

    Mat img = imread("/Users/wachs/rect.png", IMREAD_GRAYSCALE);
    namedWindow("win");
    //imshow("win", img.getImage()->getCvBGRImage());

    RegionMask reg(Mat(sup.getImage()->height(), sup.getImage()->width(), CV_8UC1, cvScalarAll(0)));
    circle(reg, sup.getImageCenter(), sup.getImage()->width() / 2, cvScalarAll(255), -1);
    sup.addRegion("Noise", reg);

    namedWindow("win");
    for (int i = 0; i < sup.getRegions().size(); ++i) {
        imshow("win", sup.getRegions()[i].getMask());
        waitKey(0);
    }

    return 0;
}

int main3(int argc, char **argv) {
    Mat src;
    // the first command-line parameter must be a filename of the binary
    // (black-n-white) image
    if (argc != 2 || !(src = imread(argv[1], 1)).data)
        return -1;

    Mat dest = src.clone();
    dest = cvScalarAll(0);

    vector<Point2i> toVisit;
    toVisit.push_back(Point2i(0, 0));

    namedWindow("dest", 1);
    imshow("dest", dest);
    //unsigned int t = 0;

    Point2i n;
    while (!toVisit.empty()) {
        vector<Point2i> neight;
        neight.push_back(toVisit.back());
        if (dest.at<Vec3b>(toVisit.back()) != Vec3b::zeros()) {
            toVisit.pop_back();
            continue;
        }
        toVisit.pop_back();
        Vec3b color;
        color[0] = rand() % 255;
        color[1] = rand() % 255;
        color[2] = rand() % 255;

        while (!neight.empty()) {
            Point2i c = neight.back();
            dest.at<Vec3b>(c) = color;

            //src.at<Vec3b>(c) = {255, 0 ,0};
            /*if(t % 300 == 0){
                imshow( "dest", dest);
                waitKey(1);
                t=0;
            }
            t++;*/
            neight.pop_back();
            for (int i = -1; i <= 1; i++) {
                for (int j = -1; j <= 1; j++) {
                    n.x = c.x + i;
                    n.y = c.y + j;
                    //dest.at<Vec3b>(n) = color;
                    if (n.x >= 0 && n.x < src.cols && n.y >= 0 && n.y < src.rows) {
                        if (src.at<Vec3b>(n) == src.at<Vec3b>(c) && dest.at<Vec3b>(n) == Vec3b::zeros()) {
                            neight.push_back(n);
                        }
                        else if (src.at<Vec3b>(n) != src.at<Vec3b>(c) && dest.at<Vec3b>(n) == Vec3b::zeros()) {
                            toVisit.push_back(n);
                        }
                    }
                }
            }
        }
    }

    namedWindow("Source", 1);
    imshow("dest", dest);
    imshow("Source", src);
    waitKey(0);


    return 0;

    Mat dst = Mat::zeros(src.rows, src.cols, CV_8UC3);

    //src = src == src.at<uchar>(120,220);
    QImageCV cv = QImageCV(argv[1]);
    Region r(&cv, src);

    namedWindow("Source", 1);
    imshow("Source", r.getMask());
    namedWindow("s2", 1);
    imshow("s2", r.getMask());

    vector<vector<cv::Point> > contours;
    vector<Vec4i> hierarchy;

    findContours(src, contours, hierarchy,
                 CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);

    // iterate through all the top-level contours,
    // draw each connected component with its own random color
    int idx = 0;
    for (; idx >= 0; idx = hierarchy[idx][0]) {
        Scalar color(rand() & 255, rand() & 255, rand() & 255);
        drawContours(dst, contours, idx, color, 4, 8, hierarchy);
    }

    namedWindow("Components", 1);
    imshow("Components", dst);
    waitKey(0);
}

int main2(int argc, char **argv) {
    QImage test("/Users/wachs/cores.jpg");
    imshow("teste", Utils::QImage2Mat(test));

    Mat m(400, 400, CV_8UC1, cvScalarAll(0));
    VoronoiDiagramGenerator v;
    float x[] = {2, 8, 300, 10, 15};
    float y[] = {5, 5, 25, 40, 200};

    v.generateVoronoi(x, y, 5, -100, 500, -100, 500);

    float px, py, p2x, p2y;
    v.resetIterator();
    //rectangle(m, cv::Point(0,0), cv::Point(399,399),cvScalarAll(255));
    while (v.getNext(px, py, p2x, p2y)) {
        line(m, cv::Point(px, py), cv::Point(p2x, p2y), cvScalarAll(255), 1);
        //printf("%f %f %f %f\n", px, py, p2x, p2y);
    }
    Mat vor = m.clone();
    for (int i = 0; i < 5; i++) {
        m = vor.clone();
        floodFill(m, cv::Point(x[i], y[i]), cvScalarAll(255));
        erode(m, m, getStructuringElement(MORPH_ERODE, cv::Size(3, 3)));
        dilate(m, m, getStructuringElement(MORPH_DILATE, cv::Size(3, 3)));
        QPolygon pp = Utils::Mask2QPolygon(m);
        for (const QPoint &polyp:pp) {
            circle(m, cv::Point(polyp.x(), polyp.y()), 3, cvScalarAll(128), 2);
            printf("%d %d\n", polyp.x(), polyp.y());
        }
        imshow("win", m);
        waitKey();
    }
    fflush(stdout);


    return 0;
}

