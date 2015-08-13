#include "ComplexNetworkConstructor.hpp"
#include <Utilities/DatabaseReader/DatabaseReader.hpp>
#include <Utilities/SupervisedImage.hpp>
#include <QLinkedList>
#include "AddOneCoOcurrenceEquation.hpp"

mutex ComplexNetworkConstructor::mtx;

ComplexNetworkConstructor::ComplexNetworkConstructor(FeaturesComplexNetwork &cn, DatabaseReader &reader,
                                                     QList<const FeatureFactoryAbstract *> extractors,
                                                     CoOcurrenceEquation *coOcurrenceEquationPolicy) : cn(cn),
                                                                                                       reader(reader),
                                                                                                       extractors(
                                                                                                               extractors),
                                                                                                       reinforcePolicy(
                                                                                                               coOcurrenceEquationPolicy),
                                                                                                       _coOcurrenceStrategyCreated(
                                                                                                               false) {
    if (!reinforcePolicy) {
        reinforcePolicy = new AddOneCoOcurrenceEquation();
        _coOcurrenceStrategyCreated = true;
    }
}

ComplexNetworkConstructor::~ComplexNetworkConstructor() {
    if (_coOcurrenceStrategyCreated)
        delete reinforcePolicy;
}

void ComplexNetworkConstructor::build() {

    unsigned int num = 1;
    while (reader.hasNext()) {
        QList<int> regionsIds;
        QLinkedList<FeatureAbstractPtr> features;
        SupervisedImage img = reader.readNext();
        if (num % 10 == 0)
            printf("Reading image(%u/%d): %s%s\n", num, reader.getTotal(), img.getImagePath().size() > 60 ? "..." : "",
                   img.getImagePath().right(60).toStdString().c_str());

        for (int idx = 0; idx < img.getRegions().size(); idx++) {
            Region r = img.getRegions().at(idx);
            for (QList<const FeatureFactoryAbstract *>::iterator i = extractors.begin(); i != extractors.end(); i++) {
                features.append(move((*i)->CreateFromRegion(&r)));
                regionsIds.append(idx);
            }
        }
        //printf("Nodes: %ld , Edges: %ld\n", cn.getNumNodes(), cn.getNumEdges());
        makeCoOccurrences(features, regionsIds);
        num++;
    }
    fflush(stdout);
    cn.refreshCache();
}

/** Atualiza os pesos as arestas de acordo com a Equação:
 * \f[ w_{i,j} = w_{i,j} + \alpha\left(\frac{\lambda}{\Delta t} - w_{i,j} \right)  \f]
 */
void ComplexNetworkConstructor::makeCoOccurrences(QLinkedList<FeatureAbstractPtr> &features, QList<int> &regionsIds) {

    QLinkedList<FeaturesComplexNetwork::Node> nodes;


    //Cria nós ou pesquisa existentes
    for (auto &f: features) {
        FeaturesComplexNetwork::Node id;
        if (!index.contains(f)) {
            FeatureAbstractPtr temp = f;
            id = cn.addNode(f);
            index.insert(temp, id);
        } else {
            id = index[f];
        }
        nodes.append(id);
    }

    unsigned int i = 0, j = 0;
    for (QLinkedList<FeaturesComplexNetwork::Node>::const_iterator it1 = nodes.begin(); it1 != nodes.end(); it1++) {
        j = i + 1;
        for (QLinkedList<FeaturesComplexNetwork::Node>::const_iterator it2 = it1 + 1; it2 != nodes.end(); it2++) {
            reinforceLink(*it1, *it2, regionsIds[i] == regionsIds[j]);
            if (*it2 != *it1)
                reinforceLink(*it2, *it1, regionsIds[i] == regionsIds[j]);
            this->time++;
            j++;
        }
        i++;
    }
}

void ComplexNetworkConstructor::reinforceLink(const FeaturesComplexNetwork::Node &a,
                                              const FeaturesComplexNetwork::Node &b, bool isSameLabel) {
    if (cn.arcExists(a, b)) {
        Link &e = cn.getArcValue(a, b);
        reinforcePolicy->reWeight(e);
        e.isSameLabel(isSameLabel);
    } else {
        Link l;
        reinforcePolicy->firstWeight(l);
        l.isSameLabel(isSameLabel);
        cn.addArc(a, b, l);
    }
}
