
#ifndef COMPLEX_NETWORK_CONSTRUCTOR__HPP
#define COMPLEX_NETWORK_CONSTRUCTOR__HPP

#include <ComplexNetwork/ComplexNetwork.hpp>
#include <FeatureExtractors/Feature.hpp>
#include "DatabaseReader.hpp"
#include <FeatureExtractors/Region.hpp>
#include "SupervisedImage.hpp"
#include <FeatureExtractors/AreaFeatureFactory.hpp>
#include <QLinkedList>
#include "Link.hpp"
#include <QHash>
#include <unordered_map>
#include <Utilities/FeaturesComplexNetwork.hpp>

using namespace std;

class ComplexNetworkConstructor{

    private:

        QHash<FeatureAbstractKey , node_id> index;

        FeaturesComplexNetwork &cn;
        DatabaseReader &reader;
        QList<FeatureFactoryAbstract*> extractors;
        unsigned long long int time=1;
        void makeCoOccurrences(QLinkedList<FeatureAbstract*> &features, QList<int> &regionsIds);
        /** Esta é a influência do tempo na aprendizagem \f$ \lambda  \f$ */
        float lambda=80;
        /** Esta é a taxa de aprendizagem \f$ \alpha  \f$ */
        float learningRate=0.3;
        float recorrencia(float time);

    public:
        ComplexNetworkConstructor(FeaturesComplexNetwork &cn, DatabaseReader &reader, QList<FeatureFactoryAbstract*> extractors);
        void build();

};

#endif
