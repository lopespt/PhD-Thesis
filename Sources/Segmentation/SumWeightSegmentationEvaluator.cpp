//
// Created by Guilherme Wachs on 15/06/15.
//

#include "SumWeightSegmentationEvaluator.h"
#include <SegmentedImage.hpp>

float SumWeightSegmentationEvaluator::evaluate(const SegmentedImage &image) {

    float grade = 0;

    QList<FeaturesComplexNetwork::Node> nodes;
    int found = 0;
    int not_found = 0;

    for(const Region &r : image.getRegions()){
        for(const FeatureFactoryAbstract* f : factories){
            const FeatureAbstractPtr &feat = f->CreateFromRegion(&r);
            const FeaturesComplexNetwork::Node &nodef = cn.getNodeFromFeature(feat);
            if(nodef != INVALID){
                nodes.append(nodef);
                found ++;
            }else{
                not_found++;
            }
        }
    }

    for(QList<FeaturesComplexNetwork::Node>::iterator i = nodes.begin(); i != nodes.end(); i++){
        for(QList<FeaturesComplexNetwork::Node>::iterator j = nodes.begin(); j != nodes.end(); j++){
            if(i != j && cn.arcExists(*i, *j)){
                grade += weights[cn.getArc(*i,*j)];
            }
        }

    }

    grade = grade - not_found;

    return grade;
}
