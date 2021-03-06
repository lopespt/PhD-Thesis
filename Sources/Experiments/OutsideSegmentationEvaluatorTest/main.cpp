#include <Utilities/FeaturesComplexNetwork/FeaturesComplexNetwork.hpp>
#include <FeatureExtractors/HsvFeatureFactory.hpp>
#include <FeatureExtractors/AreaFeatureFactory.hpp>
#include <Segmentation/XorSegmentationEvaluator.hpp>
#include <Utilities/ComplexNetworkConstructor/ComplexNetworkConstructor.hpp>
#include <Utilities/DatabaseReader/KFoldDatabaseReader.hpp>
#include <Utilities/DatabaseReader/SunDatabaseReader.hpp>
#include <Segmentation/VoronoiRandomSegmenter.hpp>
#include <opencv/highgui.h>
#include <opencv2/opencv.hpp>
#include "ConfigFileParser.hpp"

void createKfold(QString kfoldPath, QString sunFolder) {
    SunDatabaseReader sunReader(sunFolder);
    KFoldDatabaseReader reader(sunReader, 0.7);
    reader.save(kfoldPath);
}

void createTrain(KFoldDatabaseReader reader, QString cnPath, QString sunFolder,
                 QList<const FeatureFactoryAbstract *> factories) {
    FeaturesComplexNetwork cn;
    KFoldDatabaseReader::PathDatabaseReader trainReader = reader.getTrainReader();

    ComplexNetworkConstructor constructor(cn, trainReader, factories);
    constructor.build();
    cn.save(cnPath.toStdString().c_str());
}

typedef QPair<SegmentedImage *, float> result;

set<uchar> getUniqueVals(const Mat &m) {
    set<uchar> ret;

    for (int i = 0; i < m.rows; i++) {
        for (int j = 0; j < m.cols; j++) {
            uchar c = m.at<uchar>(i, j);
            ret.insert(c);
        }
    }

    return ret;
}


int main(int argc, char **argv) {
    Mat m = imread(argv[1], CV_LOAD_IMAGE_GRAYSCALE);
    Mat o(m.rows, m.cols, CV_8UC1);

    //namedWindow("win");
    //imshow("win", m);


    //m = m>100;
    //printf("%lu\n", p.size());

    auto s = getUniqueVals(m);
    printf("%lu\n", s.size());
    for (uchar c: s) {
        Mat mm = (m == c);
        if (sum(mm)[0] < 0.1 * mm.cols * mm.rows)
            continue;
        namedWindow("win");
        imshow("win", mm);
        vector<vector<Point> > p;
        vector<Vec4i> h;
        findContours(mm, p, CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE);
        printf("%lu\n", p.size());
        for (int i = 0; i < p.size(); i++) {
            o = Scalar(0);
            drawContours(o, p, i, cvScalarAll(100), -1, 8, h);
            namedWindow("win2");
            imshow("win2", o);
            waitKey(0);
        }
    }
    return 0;
}

int main2(int argc, char **argv) {
    ConfigFileParser parser(argv[1]);
    QList<const FeatureFactoryAbstract *> factories = parser.getFactories();
    QString cnFile = parser.getValue("FeaturesComplexNetwork/file").toString();
    QString images_setFile = parser.getValue("kfold/file").toString();
    QString databasePath = parser.getValue("sun/database_path").toString();
    if (!Utils::fileExists(images_setFile)) {
        createKfold(images_setFile, databasePath);
    }

    KFoldDatabaseReader reader(images_setFile);

    if (!Utils::fileExists(cnFile)) {
        puts("Files reader.kfold and train.cn doesnt exist, creating");
        createTrain(reader, cnFile, databasePath, factories);
    }

    FeaturesComplexNetwork cn;
    cn.load(cnFile.toStdString().c_str(), factories);

    KFoldDatabaseReader::PathDatabaseReader preader = reader.getTestReader();
    int imgn = 1;

    XorSegmentationEvaluator evaluator(cn, factories);
    VoronoiRandomSegmenter v;
    while (preader.hasNext()) {
        QList<result> results;
        SupervisedImage img = preader.readNext();
        printf("Image(%-5d | %-5d): %s\n", imgn, preader.getTotal(), img.getImagePath().toStdString().c_str());
        imgn++;

        if (img.hasError() || img.getRegions().size() < 2)
            continue;

        v.setNumberOfRegions((unsigned int) img.getRegions().size());
        QList<SegmentedImage> seg = v.execute(*img.getImage(), 5);
        //Inserindo a segmentação manual
        seg.append(SegmentedImage(*img.getImage(), img.getRegions()));


        int segNum = 0;
        for (SegmentedImage &s: seg) {
            float grade = evaluator.evaluate(s);
            results.append(result(&s, grade));
            printf("Seg %d = %3.1f\n", segNum + 1, results[segNum].second);
            segNum++;
        }
        qSort(results.begin(), results.end(), [&](const result &a, const result &b) {
            return a.second > b.second;
        });

        int posFound = -1;
        for (unsigned int i = 0; i < results.size(); i++) {
            if (results[i].first == &seg.last()) {
                posFound = i + 1;
            }
        }

        printf("Correct segmentation found at position %d\n", posFound);

        /*for(unsigned int i=0;i<bestImage.getRegions().size();i++){
            bestImage.showRegion(i);
        }*/


    }
    cv::destroyAllWindows();
    return 0;
}
