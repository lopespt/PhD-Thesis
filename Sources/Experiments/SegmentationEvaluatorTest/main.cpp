#include <Utilities/FeaturesComplexNetwork.hpp>
#include <FeatureExtractors/HsvFeatureFactory.hpp>
#include <Segmentation/EntropyXorSegmentationEvaluator.hpp>
#include <Utilities/ComplexNetworkConstructor/ComplexNetworkConstructor.hpp>
#include <Utilities/DatabaseReader/KFoldDatabaseReader.hpp>
#include <Utilities/DatabaseReader/SunDatabaseReader.hpp>
#include <Segmentation/VoronoiRandomSegmenter.hpp>


void createTrain(QString kfoldPath, QString cnPath, QString sunFolder){
    FeaturesComplexNetwork cn;
    QList<const FeatureFactoryAbstract*> factories;
    HsvFeatureFactory hsv(18,3,3,200);
    factories.append(&hsv);
    SunDatabaseReader sunReader(sunFolder);
    KFoldDatabaseReader reader(sunReader, 0.7);
    reader.save(kfoldPath);
    KFoldDatabaseReader::PathDatabaseReader trainReader = reader.getTrainReader();

    ComplexNetworkConstructor constructor(cn, trainReader,factories);
    constructor.build();
    cn.save(cnPath.toStdString().c_str());
}

int main(int argc, char** argv){
    //createTrain("reader.kfold", "train.cn", "/Users/wachs/SUN/");
    FeaturesComplexNetwork cn;
    QList<const FeatureFactoryAbstract*> factories;
    HsvFeatureFactory hsv(18,3,3,200);
    factories.append(&hsv);
    KFoldDatabaseReader reader("reader.kfold");
    //cn.load("train.cn", factories);

    KFoldDatabaseReader::PathDatabaseReader preader = reader.getTestReader();
    while(preader.hasNext()){
        SupervisedImage img = preader.readNext();
        VoronoiRandomSegmenter v;
        v.setNumberOfRegions(img.getRegions().size());
        auto seg = v.execute(*img.getImage(), 1);

        EntropyXorSegmentationEvaluator evaluator(cn);

        for(const SegmentedImage& s: seg){
            evaluator.evaluate(s);
            /*for(unsigned int i=0;i<s.getRegions().size();i++){
                s.showRegion(i);
            }*/
        }


    }
    return 0;
}
