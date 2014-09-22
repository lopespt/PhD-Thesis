
#ifndef COMPLEX_NETWORK_CONSTRUCTOR__HPP
#define COMPLEX_NETWORK_CONSTRUCTOR__HPP

#include "ComplexNetwork.hpp"
#include "Feature.hpp"
#include "DatabaseReader.hpp"
#include "Region.hpp"
#include "SupervisedImage.hpp"
#include "AreaFeatureExtractor.hpp"
#include <QLinkedList>
#include "Link.hpp"

typedef ComplexNetwork<Feature, Link> t_cn;

class ComplexNetworkConstructor{

    private:
        t_cn &cn;
        DatabaseReader &reader;
        QList<FeatureExtractor*> extractors;
        unsigned long long int time=1;
        void makeCoOccurrences(QLinkedList<Feature> &features);
        float lambda=2;
        float learningRate=0.2;


    public:
        ComplexNetworkConstructor(t_cn &cn, DatabaseReader &reader, QList<FeatureExtractor*> extractors);
        void analyseNext();

};

#endif
