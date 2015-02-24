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
#include <opencv/cv.h>
#include <opencv/highgui.h>

int main(int argc, char* argv[]){

    SunDatabaseReader reader("/Users/wachs/SUN/");
    FeaturesComplexNetwork cn;

    HsvFeatureFactory hsv(4,3,1,20);
    QList<const FeatureFactoryAbstract*> facts;
    facts.append(&hsv);

    ComplexNetworkConstructor constr(cn, reader, facts);

    constr.build();

    cn.save("hsv.cn");

    return 0;
}
