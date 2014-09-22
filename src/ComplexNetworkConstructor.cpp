
#include "ComplexNetworkConstructor.hpp"

ComplexNetworkConstructor::ComplexNetworkConstructor(ComplexNetwork<Feature, float> &cn, DatabaseReader &reader, QList<FeatureExtractor*> extractors):cn(cn), reader(reader), extractors(extractors){
}

void ComplexNetworkConstructor::analyseNext(){
    SupervisedImage* img;
    while( (img = reader.readNext()) !=NULL){
        foreach(Region *r, img->getRegions()){
            for(QList<FeatureExtractor*>::iterator i = extractors.begin(); i != extractors.end(); i++){
                Feature f = (*i)->extractFeature(r);
                f.printFeature();
            }
        }
        delete img;
    }
}
