
#ifndef COMPLEX_NETWORK_CONSTRUCTOR__HPP
#define COMPLEX_NETWORK_CONSTRUCTOR__HPP

#include <Utilities/FeaturesComplexNetwork.hpp>
#include <QList>
#include <QHash>

class FeatureAbstractKey;
class FeatureFactoryAbstract;
class DatabaseReader;
class CoOcurrenceEquation;

using namespace std;

class ComplexNetworkConstructor{

    private:

        QHash<FeatureAbstractKey, FeaturesComplexNetwork::Node> index;

        FeaturesComplexNetwork &cn;
        DatabaseReader &reader;
        QList<FeatureFactoryAbstract*> extractors;
        CoOcurrenceEquation* reinforcePolicy;
        bool _coOcurrenceStrategyCreated;

        unsigned long long int time=1;
        void makeCoOccurrences(QLinkedList<FeatureAbstractPtr> features, QList<int> &regionsIds);
        void reinforceLink(const FeaturesComplexNetwork::Node& a,const FeaturesComplexNetwork::Node& b, bool isSameLabel);

    public:
        ComplexNetworkConstructor(FeaturesComplexNetwork &cn, DatabaseReader &reader, QList<FeatureFactoryAbstract*> extractors, CoOcurrenceEquation* coOcurrenceEquationPolicy=NULL);
        ~ComplexNetworkConstructor();
        void build();

};

#endif
