#include <Utilities/FeaturesComplexNetwork.hpp>
#include <FeatureExtractors/HsvFeatureFactory.hpp>
#include <FeatureExtractors/AreaFeatureFactory.hpp>
#include <FeatureExtractors/OrientationFeatureFactory.hpp>
#include <Segmentation/EntropyXorSegmentationEvaluator.hpp>
#include <Utilities/ComplexNetworkConstructor/ComplexNetworkConstructor.hpp>
#include <Utilities/DatabaseReader/KFoldDatabaseReader.hpp>
#include <Utilities/DatabaseReader/SunDatabaseReader.hpp>
#include <Segmentation/VoronoiRandomSegmenter.hpp>
#include <Utilities/SupervisedImage.hpp>
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <QPair>
#include "ConfigFileParser.hpp"

void createTrain(QString kfoldPath, QString cnPath, QString sunFolder, QList<const FeatureFactoryAbstract*> factories){
    FeaturesComplexNetwork cn;
    SunDatabaseReader sunReader(sunFolder);
    KFoldDatabaseReader reader(sunReader, 0.7);
    reader.save(kfoldPath);
    KFoldDatabaseReader::PathDatabaseReader trainReader = reader.getTrainReader();

    ComplexNetworkConstructor constructor(cn, trainReader,factories);
    constructor.build();
    cn.save(cnPath.toStdString().c_str());
}

typedef QPair<SegmentedImage*, float> result;

int main(int argc, char** argv){
    ConfigFileParser parser(argv[1]);
    QList<const FeatureFactoryAbstract*> factories = parser.getFactories();
    QString cnFile = parser.getValue("FeaturesComplexNetwork/file").toString();
    QString images_setFile = parser.getValue("kfold/file").toString();
    QString databasePath = parser.getValue("sun/database_path").toString();

    if(!Utils::fileExists(cnFile) || !Utils::fileExists(images_setFile)){
        puts("Files reader.kfold and train.cn doesnt exist, creating");
        createTrain(images_setFile, cnFile, databasePath, factories);
    }
    FeaturesComplexNetwork cn;
    KFoldDatabaseReader reader(images_setFile);
    cn.load(cnFile.toStdString().c_str(), factories);

    KFoldDatabaseReader::PathDatabaseReader preader = reader.getTestReader();
    int imgn = 1;

    while(preader.hasNext()){
        QList<result> results;
        SupervisedImage img = preader.readNext();
        printf("Image(%-5d | %-5d): %s\n", imgn, preader.getTotal(), img.getImagePath().toStdString().c_str());
        imgn++;

        if(img.hasError())
            continue;

        VoronoiRandomSegmenter v;
        v.setNumberOfRegions(img.getRegions().size());
        QList<SegmentedImage> seg = v.execute(*img.getImage(), 5);
        seg.append(SegmentedImage(*img.getImage(), img.getRegions()));
    
        EntropyXorSegmentationEvaluator evaluator(cn, factories);

        int segNum = 0;
        for(SegmentedImage& s: seg){
            float grade = evaluator.evaluate(s);
            results.append(result(&s, grade));
            printf("Seg %d = %3.1f\n", segNum+1, results[segNum].second);
            segNum++;
        }
        qSort(results.begin(), results.end(), [&](const result &a,const result &b){
            return a.second > b.second;
        });

        int posFound = -1;
        for(unsigned int i=0; i< results.size(); i++){
            if( results[i].first == &seg.last()){
                posFound = i+1;
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
